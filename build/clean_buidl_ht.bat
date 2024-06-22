@echo off

rem Clean the project (remove object files and executable)
echo Cleaning project...
make clean

rem Check if make is available
where make > nul 2>&1
if %errorlevel% neq 0 (
    echo "Error: make is not installed or not in the PATH."
    exit /b 1
)

echo "Clean successful."
