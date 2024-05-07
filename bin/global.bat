@echo off
setlocal EnableDelayedExpansion

rem Define color codes for Command Prompt
set GREEN=[1;32m
set CYAN=[1;36m
set RED=[1;31m
set NO_COLOR=[0m


rem Get the absolute path of the batch script directory
for %%I in ("%~dp0.") do set "BIN_PATH=%%~fI"

echo %CYAN%== Building global%NO_COLOR%

rem Compile vector.c into vector.o
gcc.exe -c -Wno-implicit-function-declaration "%BIN_PATH%\..\global\vector\vector.c" -o "%BIN_PATH%\out\vector.o"
if errorlevel 1 (
  echo %RED%== Error: Compilation of vector.c failed%NO_COLOR%
  exit /b 1
)

rem Compile stack.c into stack.o
gcc.exe -c -Wno-implicit-function-declaration "%BIN_PATH%\..\global\stack\stack.c" -o "%BIN_PATH%\out\stack.o"
if errorlevel 1 (
  echo %RED%== Error: Compilation of stack.c failed%NO_COLOR%
  exit /b 1
)

rem Compile sl_list.c into sl_list.o
gcc.exe -c -Wno-implicit-function-declaration "%BIN_PATH%\..\global\SL_list\list.c" -o "%BIN_PATH%\out\SL_list.o"
if errorlevel 1 (
  echo %RED%== Error: Compilation of sl_list.c failed%NO_COLOR%
  exit /b 1
)

rem Compile dl_list.c into dl_list.o
gcc.exe -c -Wno-implicit-function-declaration "%BIN_PATH%\..\global\DL_list\list.c" -o "%BIN_PATH%\out\DL_list.o"
if errorlevel 1 (
  echo %RED%== Error: Compilation of dl_list.c failed%NO_COLOR%
  exit /b 1
)

rem Compile csl_list.c into csl_list.o
gcc.exe -c -Wno-implicit-function-declaration "%BIN_PATH%\..\global\CSL_list\list.c" -o "%BIN_PATH%\out\CSL_list.o"
if errorlevel 1 (
  echo %RED%== Error: Compilation csl_list.o failed%NO_COLOR%
  exit /b 1
)

@REM rem Compile queue.c into queue.o
@REM gcc.exe -c -Wno-implicit-function-declaration "%BIN_PATH%\..\global\queue\queue.c" -o "%BIN_PATH%\out\queue.o"
@REM if errorlevel 1 (
@REM   echo %RED%== Error: Compilation of queue.c failed%NO_COLOR%
@REM   exit /b 1
@REM )

rem Combine vector.o and stack.o into global.o
ld.exe -r "%BIN_PATH%\out\vector.o" "%BIN_PATH%\out\stack.o" "%BIN_PATH%\out\SL_list.o" "%BIN_PATH%\out\DL_list.o" "%BIN_PATH%\out\CSL_list.o"  -o "%BIN_PATH%\out\global.o"
if errorlevel 1 (
  echo %RED%== Error: Linking failed%NO_COLOR%
  exit /b 1
)

echo %GREEN%== Build Succeeded global%NO_COLOR%


