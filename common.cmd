@echo off
setlocal enabledelayedexpansion

set FB_ROOT="%~dp0"
set RUN_FROM=%CD%
set _SHIFTTOK=0

:: Check first parameter for project directory or set default
if not "%~1"=="" (
    if not "%~1:~0,1%"=="-" (
        set PROJDIR=%1
        shift
        set _SHIFTTOK=1
    )
) else (
    set PROJDIR="%RUN_FROM%\projects"
)

:: Check second parameter for build directory or set default
if not "%~1"=="" (
    if not "%~1:~0,1%"=="-" (
        set BUILDDIR=%1
        shift
        set _SHIFTTOK=2
    )
) else (
    if /I %PROJDIR%==examples (
        echo Building examples
        set BUILDDIR="%RUN_FROM%\buildex"
    ) else (
        set BUILDDIR="%RUN_FROM%\build"
    )
)

:: Ensure project directory exists
if not exist %PROJDIR% (
    echo ERROR: Project directory %PROJDIR% does not exist.  usage: prep[ver].cmd [project dir] [build dir]
    exit /B 2
)

:: Get full paths for directories
pushd "%PROJDIR%" > NUL
set PROJDIR="%CD%"
popd > NUL

mkdir "%BUILDDIR%" 2>NUL
pushd "%BUILDDIR%" > NUL
if %errorlevel% == 1 goto error
set BUILDDIR="%CD%"
popd > NUL

:: Extract remaining parameters for CMake
for /f "tokens=%_SHIFTTOK%*" %%a in ('echo.%*') do set CMAKE_PARAMS=%%b

echo Using projects in: %PROJDIR%
echo Generating build files in: %BUILDDIR%
echo NOTE: The build files in %BUILDDIR% should *NEVER* be modified directly.
echo When needed, make project changes in cmake files and re-run this script.
echo   Project-specific cmake files are found in [plugin dir]\CMakeLists.txt and 
echo   [plugin dir]\Win\projectDef.cmake.
echo Note that parameters for cmake should be enclosed in double quotes, e.g. "-DVERBOSE=1"
echo CMAKE parameters: %CMAKE_PARAMS%
exit /B 0

:error
echo "Could not create build directory %BUILDDIR%"
exit /B 2
