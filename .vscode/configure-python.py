"""Configure the current user's Python learning environment on macOS or Windows."""
from __future__ import annotations

import copy
import ctypes
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

DEFAULT_FOLDER = '${userHome}/.local/share/venvs/python-default'
EXTENSIONS = ('ms-python.python', 'ms-python.debugpy', 'ms-python.vscode-python-envs', 'ms-python.vscode-pylance')
WINDOWS = sys.platform == 'win32'


def parse_jsonc(text):
    """Read VS Code JSON with comments/trailing commas, preserving quoted text."""
    text = text.lstrip('\ufeff')
    cleaned = []
    i = 0
    quoted = False
    while i < len(text):
        char = text[i]
        if quoted:
            cleaned.append(char)
            if char == '\\' and i + 1 < len(text):
                i += 1
                cleaned.append(text[i])
            elif char == '"':
                quoted = False
        elif char == '"':
            quoted = True
            cleaned.append(char)
        elif text[i:i+2] == '//':
            while i < len(text) and text[i] != '\n':
                i += 1
            cleaned.append('\n')
            continue
        elif text[i:i+2] == '/*':
            end = text.find('*/', i + 2)
            if end < 0:
                raise ValueError('Unclosed JSON comment')
            cleaned.append(' ')
            i = end + 2
            continue
        else:
            cleaned.append(char)
        i += 1
    text = ''.join(cleaned)
    cleaned = []
    i = 0
    quoted = False
    while i < len(text):
        char = text[i]
        if quoted:
            cleaned.append(char)
            if char == '\\' and i + 1 < len(text):
                i += 1
                cleaned.append(text[i])
            elif char == '"':
                quoted = False
        elif char == '"':
            quoted = True
            cleaned.append(char)
        elif char == ',':
            next_index = i + 1
            while next_index < len(text) and text[next_index].isspace():
                next_index += 1
            if next_index == len(text) or text[next_index] not in '}]':
                cleaned.append(char)
        else:
            cleaned.append(char)
        i += 1
    return json.loads(''.join(cleaned))


def build_preferences(settings, keybindings):
    if not isinstance(settings, dict) or not isinstance(keybindings, list):
        raise ValueError('Unexpected VS Code settings/keybindings structure')
    settings, keybindings = copy.deepcopy(settings), copy.deepcopy(keybindings)
    settings['python.defaultInterpreterPath'] = DEFAULT_FOLDER
    settings['python.terminal.executeInFileDir'] = True
    launch = settings.setdefault('launch', {'version': '0.2.0', 'configurations': []})
    old_names = {'Mac global: debug Python', 'Windows global: debug Python', 'Python global: debug current file'}
    existing = launch.setdefault('configurations', [])
    existing[:] = [c for c in existing if c.get('name') not in old_names]
    existing.insert(0, {
        'name': 'Python global: debug current file', 'type': 'debugpy', 'request': 'launch',
        'program': '${file}', 'python': '${command:python.interpreterPath}',
        'cwd': '${fileDirname}', 'console': 'integratedTerminal', 'justMyCode': True,
    })
    ignored = settings.get('settingsSync.ignoredSettings', [])
    if isinstance(ignored, list):
        settings['settingsSync.ignoredSettings'] = [s for s in ignored if s != 'python.defaultInterpreterPath']
    shortcuts = [
        {'key': 'f5', 'command': 'debugpy.debugInTerminal', 'when': 'editorTextFocus && editorLangId == python && !inDebugMode'},
        {'key': 'ctrl+f5', 'command': 'python.execInTerminal', 'when': 'editorTextFocus && editorLangId == python'},
    ]
    for shortcut in shortcuts:
        if shortcut not in keybindings:
            keybindings.append(shortcut)
    return settings, keybindings


def code_command():
    if not WINDOWS:
        code = shutil.which('code') or '/Applications/Visual Studio Code.app/Contents/Resources/app/bin/code'
        if Path(code).is_file():
            return [code], dict(os.environ)
    else:
        roots = [Path(os.environ.get('LOCALAPPDATA', str(Path.home()/'AppData/Local')))/'Programs/Microsoft VS Code',
                 Path(os.environ.get('ProgramFiles', 'C:/Program Files'))/'Microsoft VS Code']
        found = shutil.which('code')
        if found:
            roots.insert(0, Path(found).resolve().parent.parent)
        for root in roots:
            executable, cli = root/'Code.exe', root/'resources/app/out/cli.js'
            if executable.is_file() and cli.is_file():
                env = dict(os.environ, ELECTRON_RUN_AS_NODE='1')
                return [str(executable), str(cli)], env
    raise RuntimeError('VS Code was not found; install VS Code and run this setup again.')


def configure_path(home, env_dir):
    env_bin = env_dir/('Scripts' if WINDOWS else 'bin')
    additions = [str(env_bin), str(home/'.local/bin')]
    os.environ['PATH'] = os.pathsep.join(additions + [os.environ.get('PATH', '')])
    if WINDOWS:
        import winreg
        with winreg.CreateKey(winreg.HKEY_CURRENT_USER, 'Environment') as key:
            try:
                previous, kind = winreg.QueryValueEx(key, 'Path')
            except FileNotFoundError:
                previous, kind = '', winreg.REG_EXPAND_SZ
            excluded = {os.path.normcase(os.path.normpath(p)) for p in additions}
            kept = [p for p in previous.split(';') if p and os.path.normcase(os.path.normpath(os.path.expandvars(p))) not in excluded]
            winreg.SetValueEx(key, 'Path', 0, winreg.REG_EXPAND_SZ, ';'.join(additions + kept))
        result = ctypes.c_size_t()
        notify = ctypes.windll.user32.SendMessageTimeoutW
        notify.argtypes = [ctypes.c_void_p, ctypes.c_uint, ctypes.c_size_t, ctypes.c_wchar_p, ctypes.c_uint, ctypes.c_uint, ctypes.POINTER(ctypes.c_size_t)]
        notify.restype = ctypes.c_ssize_t
        notify(0xffff, 0x1a, 0, 'Environment', 2, 5000, ctypes.byref(result))
    else:
        additions.append('/Applications/Visual Studio Code.app/Contents/Resources/app/bin')
        block = '''# >>> Python development environment >>>
typeset -U path PATH
path=("$HOME/.local/share/venvs/python-default/bin" "$HOME/.local/bin" "/Applications/Visual Studio Code.app/Contents/Resources/app/bin" $path)
if [[ -n "${VIRTUAL_ENV:-}" && -x "$VIRTUAL_ENV/bin/python" ]]; then
    path=("$VIRTUAL_ENV/bin" $path)
fi
export PATH
# <<< Python development environment <<<'''
        for name in ['.zprofile', '.zshrc']:
            target = home/name
            text = target.read_text() if target.exists() else ''
            begin, end = '# >>> Python development environment >>>', '# <<< Python development environment <<<'
            if begin in text and end in text:
                first = text.index(begin)
                last = text.index(end, first) + len(end)
                desired = text[:first] + block + text[last:]
            else:
                desired = text.rstrip() + ('\n\n' if text.strip() else '') + block + '\n'
            if desired != text:
                target.write_text(desired)


def main():
    if sys.platform not in ('darwin', 'win32'):
        raise RuntimeError('This setup supports macOS and Windows.')
    home = Path.home()
    env_dir = home/'.local/share/venvs/python-default'
    python = env_dir/('Scripts/python.exe' if WINDOWS else 'bin/python')
    uv = shutil.which('uv') or str(home/'.local/bin'/('uv.exe' if WINDOWS else 'uv'))
    command, code_env = code_command()
    if not python.exists():
        if env_dir.exists():
            raise RuntimeError(f'An incomplete environment already exists at {env_dir}; it was left untouched.')
        subprocess.run([uv, 'venv', '--python', '3.14', '--seed', str(env_dir)], check=True)
    version = subprocess.check_output([str(python), '-c', 'import platform; print(platform.python_version())'], text=True).strip()
    if not version.startswith('3.14.'):
        raise RuntimeError(f'Existing learning environment uses {version}; it was left untouched.')
    subprocess.run([str(python), '-m', 'pip', '--version'], check=True)
    user = (Path(os.environ['APPDATA'])/'Code/User') if WINDOWS else (home/'Library/Application Support/Code/User')
    settings_path, keys_path = user/'settings.json', user/'keybindings.json'
    original = {p: p.read_bytes() if p.exists() else None for p in (settings_path, keys_path)}
    settings = parse_jsonc(original[settings_path].decode('utf-8')) if original[settings_path] else {}
    keys = parse_jsonc(original[keys_path].decode('utf-8')) if original[keys_path] else []
    settings, keys = build_preferences(settings, keys)
    changes = {settings_path: json.dumps(settings, ensure_ascii=False, indent=4)+'\n', keys_path: json.dumps(keys, ensure_ascii=False, indent=4)+'\n'}
    backup_root = home/'.local/state/python-setup'
    backup_root.mkdir(parents=True, exist_ok=True)
    backup = Path(tempfile.mkdtemp(prefix='cross-platform-', dir=backup_root))
    for p, data in original.items():
        if data is not None:
            (backup/p.name).write_bytes(data)
    for name in ('.zprofile', '.zshrc'):
        p = home/name
        if not WINDOWS and p.exists():
            (backup/name).write_bytes(p.read_bytes())
    configure_path(home, env_dir)
    for p, text in changes.items():
        if (p.read_bytes() if p.exists() else None) != original[p]:
            raise RuntimeError(f'{p} changed during setup; refusing to overwrite it.')
        p.parent.mkdir(parents=True, exist_ok=True)
        if not p.exists() or p.read_text() != text:
            p.write_text(text, encoding='utf-8')
    installed = subprocess.check_output(command+['--list-extensions'], env=code_env, text=True).lower().splitlines()
    if any(e not in installed for e in EXTENSIONS):
        subprocess.run(command+['--install-extension', 'ms-python.python'], env=code_env, check=True)
        installed = subprocess.check_output(command+['--list-extensions'], env=code_env, text=True).lower().splitlines()
        for extension in EXTENSIONS:
            if extension not in installed:
                subprocess.run(command+['--install-extension', extension], env=code_env, check=True)
    subprocess.run([str(python), '-c', 'import ssl, sqlite3, venv; print("Python environment OK")'], check=True)
    print(f'Python {version}: {python}')
    print(f'VS Code user settings configured. Backup: {backup}')
    print('Restart VS Code and its terminals. If previously selected, choose this environment with Python: Select Interpreter.')


if __name__ == '__main__':
    main()
