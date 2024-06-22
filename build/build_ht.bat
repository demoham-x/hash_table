@echo off
rem Batch file to run Makefile and log the output

rem Check if bin directory exists, create if not
if not exist bin (
    mkdir bin
)
rem Check if Make is available
where make > nul 2>&1
if %errorlevel% neq 0 (
    echo "Error: make is not installed or not in the PATH."
    exit /b 1
)

rem Run the make log target to build and log output
make log

rem Check the build status
if %errorlevel% neq 0 (
    echo "Build failed. Check build.log for details."
    exit /b 1
)

echo "Build successful. Output logged to build.log."
