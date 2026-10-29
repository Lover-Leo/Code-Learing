# Run once on Windows. Python source/config files can then be shared with macOS.
$ErrorActionPreference = 'Stop'
if ($env:OS -ne 'Windows_NT') { throw 'Run this script on Windows.' }
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
[Console]::OutputEncoding = [System.Text.UTF8Encoding]::new($false)
$env:PYTHONUTF8 = '1'
if (-not $env:UV_HTTP_TIMEOUT) { $env:UV_HTTP_TIMEOUT = '1200' }

$codeCandidates = @(
    (Join-Path $env:LOCALAPPDATA 'Programs\Microsoft VS Code\Code.exe'),
    (Join-Path $env:ProgramFiles 'Microsoft VS Code\Code.exe')
)
if (-not (Get-Command code -ErrorAction SilentlyContinue) -and -not ($codeCandidates | Where-Object { Test-Path $_ })) {
    if (-not (Get-Command winget -ErrorAction SilentlyContinue)) { throw 'Install Visual Studio Code, then run this script again.' }
    winget install --id Microsoft.VisualStudioCode --exact --source winget --scope user --accept-package-agreements --accept-source-agreements
    if ($LASTEXITCODE -ne 0) { throw 'VS Code installation failed.' }
}

$taskUvPath = Join-Path $env:USERPROFILE '.local\bin\uv.exe'
if (-not (Test-Path $taskUvPath)) {
    $existingUv = Get-Command uv -ErrorAction SilentlyContinue
    if ($existingUv) { $taskUvPath = $existingUv.Source }
    else {
        $installerFile = Join-Path ([IO.Path]::GetTempPath()) ('python-learning-uv-' + [guid]::NewGuid().ToString() + '.ps1')
        $previousInstallDir, $previousModifyPath = $env:UV_INSTALL_DIR, $env:UV_NO_MODIFY_PATH
        try {
            $env:UV_INSTALL_DIR = Join-Path $env:USERPROFILE '.local\bin'
            $env:UV_NO_MODIFY_PATH = '1'
            Invoke-WebRequest 'https://astral.sh/uv/install.ps1' -UseBasicParsing -OutFile $installerFile
            & $installerFile
            if (-not (Test-Path $taskUvPath)) { throw 'uv installation failed.' }
        }
        finally {
            $env:UV_INSTALL_DIR, $env:UV_NO_MODIFY_PATH = $previousInstallDir, $previousModifyPath
            if (Test-Path $installerFile) { Remove-Item -LiteralPath $installerFile }
        }
    }
}
& $taskUvPath run --python 3.14 --no-project (Join-Path $PSScriptRoot 'configure-python.py')
if ($LASTEXITCODE -ne 0) { throw 'Python setup did not finish; read the error above and rerun after resolving it.' }
Write-Host 'Setup complete. Restart VS Code and its terminals.'
