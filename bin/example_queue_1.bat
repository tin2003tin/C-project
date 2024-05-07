@echo off

rem Define color codes for Command Prompt
set GREEN=[1;32m
set CYAN=[1;36m
set RED=[1;31m
set YELLOW=[1;33m
set NO_COLOR=[0m

set STRUC=queue
set EXAMPLE_FILE=example_1.c
set OUTPUT_FILE=example_queue_1.exe

set START_TIME=%TIME%

rem Get the absolute path of the batch script directory
for %%I in ("%~dp0.") do set "BIN_PATH=%%~fI"

rem Build Global
call "%BIN_PATH%\global.bat"

rem Display message: Building EXAMPLE_FILE
echo %CYAN%== Building %EXAMPLE_FILE%%NO_COLOR%

rem Compile the C program
gcc.exe "%BIN_PATH%\..\global\%STRUC%\test\%EXAMPLE_FILE%" "%BIN_PATH%\out\global.o" -o "%BIN_PATH%\out\%OUTPUT_FILE%"

rem Check if compilation was successful
if not errorlevel 1 (

  rem Display message: Build Succeeded EXAMPLE_FILE
  echo %GREEN%== Build Succeeded %EXAMPLE_FILE%


  rem Display message: Running OUTPUT_FILE
  echo %CYAN%== Running %OUTPUT_FILE%%NO_COLOR%

  rem Run the compiled program
  "%BIN_PATH%\out\%OUTPUT_FILE%"
  echo.
  rem Check the error level after running the program
  if errorlevel 1 (
    echo %RED%== Error: Failed to run %OUTPUT_FILE%%NO_COLOR%
  ) else (
    rem Display message: Finished Running %OUTPUT_FILE%
    echo %GREEN%== Finished Running %OUTPUT_FILE%%NO_COLOR%
  )
) else (
  echo %RED%== Error: Compilation of %OUTPUT_FILE% failed%NO_COLOR%
)

set END_TIME=%TIME%
echo %YELLOW%== Start:%START_TIME% End:%END_TIME% %NO_COLOR%