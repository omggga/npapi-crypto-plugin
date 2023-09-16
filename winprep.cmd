@echo off
setlocal enabledelayedexpansion

pushd "%BUILDDIR%" > NUL
if %errorlevel% == 1 goto builddir_error

REM ** shift off the first 2 params so the rest goes to cmake
shift
shift

REM Remove trailing backslash from FB_ROOT if it exists
IF "%FB_ROOT:~-1%" == "\" SET "FB_ROOT=!FB_ROOT:~0,-1!"

set FB_ROOT_ARG=-DFB_ROOT="%FB_ROOT%"
set PDIR=-DFB_PROJECTS_DIR="%PROJDIR%"

@echo on
cmake -G "%_FB_GEN%" %FB_ROOT_ARG% %CMAKE_PARAMS% "%PROJDIR%"
@echo off

popd
goto end

:builddir_error
echo ERROR: Could not change to %BUILDDIR%
exit /b 1

:end
