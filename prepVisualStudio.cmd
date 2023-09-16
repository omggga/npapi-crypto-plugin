@echo off 
setlocal enableextensions enabledelayedexpansion

REM Check if 1st parameter is Visual Studio cmake generator name
echo "%~1" | findstr /c:"Visual Studio" >nul 
if errorlevel 1 goto args_count_wrong 

REM Set generator 
set _FB_GEN="%~1"
set ALL_ARG=%*
call set ALL_BUT_FIRST_ARG=%%ALL_ARG:%_FB_GEN%=%%

call "%~dp0common.cmd" %ALL_BUT_FIRST_ARG%
if %errorlevel% == 2 exit /b 1
call "%~dp0winprep.cmd"
exit /b 0

:args_count_wrong
REM Show usage message and list available Visual Studio cmake generators
echo Usage %0 "visual studio cmake generator" [project dir] [build dir]  
echo The available Visual Studio cmake generators are : 
cmake --help | FINDSTR "Visual Optional"
exit /b 1
