@echo off
setlocal EnableExtensions

if "%~1"=="" goto missing_argument

set "SOURCE=%~f1"
set "EXTENSION=%~x1"
set "OBJECT=%~dpn1.obj"
set "PROGRAM=%~dpn1.exe"
set "VSDEVCMD=D:\VS2026\Common7\Tools\VsDevCmd.bat"

if not exist "%SOURCE%" goto missing_source
if not exist "%VSDEVCMD%" goto missing_environment

call "%VSDEVCMD%" -no_logo -arch=x64
if errorlevel 1 goto environment_failed

where cl.exe >nul 2>&1
if errorlevel 1 goto missing_compiler

if /I "%EXTENSION%"==".cpp" goto build_cpp
if /I "%EXTENSION%"==".c" goto build_c
goto unsupported_extension

:build_cpp
cl.exe /nologo /W4 /permissive- /utf-8 /EHsc /std:c++20 /Zi /Od /diagnostics:caret /FC /Fo:"%OBJECT%" /Fe:"%PROGRAM%" "%SOURCE%"
set "BUILD_EXIT=%ERRORLEVEL%"
goto build_finished

:build_c
cl.exe /nologo /W4 /utf-8 /std:c17 /Zi /Od /diagnostics:caret /FC /Fo:"%OBJECT%" /Fe:"%PROGRAM%" "%SOURCE%"
set "BUILD_EXIT=%ERRORLEVEL%"
goto build_finished

:build_finished
if not "%BUILD_EXIT%"=="0" goto build_failed
echo [OK] Built "%PROGRAM%"
exit /b 0

:build_failed
echo [ERROR] Compiler exited with code %BUILD_EXIT%.
exit /b %BUILD_EXIT%

:missing_argument
echo [ERROR] No source file was provided.
exit /b 2

:missing_source
echo [ERROR] Source file not found: "%SOURCE%"
exit /b 2

:missing_environment
echo [ERROR] Visual Studio environment script not found: "%VSDEVCMD%"
exit /b 3

:environment_failed
echo [ERROR] Visual Studio developer environment initialization failed.
exit /b 4

:missing_compiler
echo [ERROR] cl.exe was not found after developer environment initialization.
exit /b 5

:unsupported_extension
echo [ERROR] Active file must end in .c or .cpp: "%SOURCE%"
exit /b 2
