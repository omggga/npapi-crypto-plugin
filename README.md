## Requirements:

* Microsoft Visual Studio 13.0+
* Microsoft SDK
* Windows Driver Kit 8.1
* WiX 3.6 - 3.11 (https://wixtoolset.org/releases/)
* CMake version 2.8.7 or later (Binary distribution)
```
Make sure to grab the Binary distribution (cmake-ver-win32-x86.exe).
Download from here: : http://www.cmake.org/cmake/resources/software.html
When asked, tell the installer to add cmake to your system path
The Cygwin version of CMake does not work, but you can use the Windows version from inside Cygwin
```

**Important to know!**
Each initialization and each build, cmake remakes paths and dependencies, so you can't edit them directly!
Also, due to this, there are big doubts that it can be updated for a ci build.

All changes in the plugin must be made in the plugin folder projects\Plugin, then call prep build.cmd (more below) and build the sln generated in the build folder. Only this way!

_In theory_, firebreath finds the correct paths for dependencies like cmake, driver kit, etc. in PATH during the first project build.


## Sequential build of the CabinetPlugin2 project through Firebreath:

##### 1. git clone

##### 2. Testing FireBreath:
Call the command `prepVisualStudio.cmd "Visual Studio 14 2015" examples\EchoTestPlugin EchoPlugin`  
where  
"Visual Studio 14 2015" - the version for which the build is made  

If cmd worked successfully, a folder EchoPlugin with the project will appear in the initial plugin folder. Go inside, launch the studio and *.sln, build it.
If all 15 projects of the solution were successfully built, it means firebreath is set up correctly.

If it did not build, it means that something is not set up correctly from external dependencies, it is important to pay attention to:

* Is cmake correctly specified in vcxproj EchoTestPlugin, for example at the address C:\Program Files\CMake\bin\cmake.exe. If cmake does not find or specifies a crooked/not real path, it means cmake is installed incorrectly and PATH variables are not specified!
* Windows Driver Kit 8.1 must be exactly 8.1, if another version, you need to change the line in Win.cmake, there is a hardcode `KitsRoot81`:  
`GET_FILENAME_COMPONENT(WINKIT_DIR "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows Kits\\Installed Roots;KitsRoot81]" REALPATH CACHE)`

##### 3. We build the current version of the project  projects\CabinetPlugin2:

We skip the initial stage of generating the basic plugin structure through `fbgen.py`, since we already performed this task and we already have a ready-made project.

Next, we execute the command from the firebreath folder:  
`prepVisualStudio.cmd "Visual Studio 14 2015" projects\CabinetPlugin2 CabinetPlugin2`  
where  
"Visual Studio 14 2015" - the version for which the build is made 
projects\CabinetPlugin2 - the project that needs to be built
build - the folder where the finished project will be placed

**What this command does**:  
It generates a project in the \build folder, so after any changes in the main plugin files at the address projects\Plugin, you need to restart this command!

**Important!** The build folder in the Firebreath directory must be absent! If it is there, you need to delete it before running the script. Otherwise, the build will fail due to the presence of the build folder.
We get a ready-made project in the \build folder

It is worth noting that the instructions on the firebreath website are outdated, as they are designed for 32-bit NPAPI plugins (concerns for example Debug and others)


Also, it is important to note about cmake:
* CMake uses absolute paths to generate the project files, so if you move the FireBreath tree you will need to re-run your "prep" command.
* Once changes are made, the "prep" command should be run again so that cmake can generate the updated project files. 

Every time we modify the project/build in a new ecosystem, etc., we must first execute `prepVisualStudio.cmd`!  


##### 4. Go to build, launch *.sln plugin  

##### 5. Build the solution


## Errors FAQ:

#### prepVisualStudio.cmd

1. `signtool not found`
You need to check the presence of microsoft sdk and window driver kit and their paths in the registry in the file  `\cmake\Win.cmake`  
```
GET_FILENAME_COMPONENT(WINSDK_DIR "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Microsoft SDKs\\Windows;CurrentInstallFolder]" REALPATH CACHE)
GET_FILENAME_COMPONENT(WINKIT_DIR "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows Kits\\Installed Roots;KitsRoot81]" REALPATH CACHE)
```
