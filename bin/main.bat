@echo off

rem Define color codes for Command Prompt
set GREEN=[1;32m
set CYAN=[1;36m
set RED=[1;31m
set YELLOW=[1;33m
set NO_COLOR=[0m

set START_TIME=%TIME%

rem Get the absolute path of the batch script directory
for %%I in ("%~dp0.") do set "BIN_PATH=%%~fI"

rem Build Global
call "%BIN_PATH%\global.bat"

rem Display message: Building main.c
echo %CYAN%== Building main.c%NO_COLOR%

rem Compile the C program
gcc.exe "%BIN_PATH%\..\main.c" "%BIN_PATH%\out\global.o" -o "%BIN_PATH%\..\main.exe"
rem Check if compilation was successful
if not errorlevel 1 (

  rem Display message: Build Succeeded main.c
  echo %GREEN%== Build Succeeded main.c


  rem Display message: Running main.exe
  echo %CYAN%== Running main.exe%NO_COLOR%
  rem Run the compiled program
  "%BIN_PATH%\..\main.exe"
  echo.
  rem Check the error level after running the program
  if errorlevel 1 (
    echo %RED%== Error: Failed to run main.exe%NO_COLOR%
  ) else (
    rem Display message: Finished Running main.exe
    echo %GREEN%== Finished Running main.exe%NO_COLOR%
  )
) else (
  echo %RED%== Error: Compilation of main.exe failed%NO_COLOR%
)

set END_TIME=%TIME%
echo %YELLOW%== Start:%START_TIME% End:%END_TIME% %NO_COLOR%