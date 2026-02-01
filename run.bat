@echo off
title Cortex Build System

:: Terminate any running instances
taskkill /IM Cortex.exe /F >nul 2>&1

echo Compiling Cortex OS...

:: Compile source files
gcc main.c nn.c -o Cortex
if %errorlevel% neq 0 (
    echo [ERROR] Compilation failed.
    exit /b %errorlevel%
)

:: Build successful - Launching
echo Launching Cortex...
.\Cortex