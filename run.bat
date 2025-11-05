@echo off

REM === Step 1: Compile main.cpp into social_network.exe ===
g++ -std=c++17 -O2 -Wall main.cpp -o social_network.exe

REM === Step 2: Check if compilation failed ===
IF ERRORLEVEL 1 (
    echo Compilation failed!
    pause
    exit /b
)

REM === Step 3:  Run the program ===
social_network.exe
