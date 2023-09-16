#/**********************************************************\ 
#Original Author: Richard Bateman (taxilian)
#...
#\**********************************************************/

cmake_minimum_required (VERSION 2.6)
set (CMAKE_BACKWARDS_COMPATIBILITY 2.6)

# Determine FB_ROOT
get_filename_component(FB_ROOT ${CMAKE_CURRENT_LIST_FILE} PATH)
Project (FireBreath)

option(FB_AUTO_GIT "Enable automatic git operations." ON)
include(${FB_ROOT}/cmake/common.cmake)

set(FB_EXPORT_FILE ${CMAKE_BINARY_DIR}/FireBreath_Exports.cmake)
file(REMOVE ${FB_EXPORT_FILE})
add_subdirectory(${FB_ROOT}/cmake ${CMAKE_CURRENT_BINARY_DIR}/cmake_common)

if (APPLE)
    clear_xcode_patches()
    add_definitions(-D__ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES=0)
endif()

fb_check_boost()

if (UNIX AND NOT APPLE)
    find_package(Threads REQUIRED)
endif()

if (WITH_SYSTEM_BOOST)
    if (APPLE OR WIN32)
        SET(Boost_USE_STATIC_LIBS ON)
    endif()
    if (WIN32)
        SET(Boost_USE_STATIC_RUNTIME ${WITH_DYNAMIC_MSVC_RUNTIME})
    endif()
endif()

add_boost_library(thread system)

if (UNIX AND NOT APPLE) 
    add_boost_library(regex)
endif()

if (Boost_MAJOR_VERSION GREATER 0 AND Boost_MINOR_VERSION GREATER 47)
    add_boost_library(chrono)
endif()

# Common core projects
add_subdirectory(${FB_ROOT}/src/ScriptingCore ${CMAKE_CURRENT_BINARY_DIR}/ScriptingCore)
add_subdirectory(${FB_ROOT}/src/PluginCore ${CMAKE_CURRENT_BINARY_DIR}/PluginCore)
add_subdirectory(${FB_ROOT}/src/NpapiCore ${CMAKE_CURRENT_BINARY_DIR}/NpapiCore)
add_subdirectory(${FB_ROOT}/src/FireWyrm ${CMAKE_CURRENT_BINARY_DIR}/FireWyrm)

if (WIN32)
    add_subdirectory(${FB_ROOT}/src/ActiveXCore ${CMAKE_CURRENT_BINARY_DIR}/ActiveXCore)
endif()

add_subdirectory(${FB_ROOT}/src/NativeMessageHost ${CMAKE_CURRENT_BINARY_DIR}/NativeMessageHost)

message("Boost includes: ${Boost_INCLUDE_DIRS}")

export_project_dependencies()
