#/**********************************************************\ 
#Original Author: Richard Bateman (taxilian)
#
#Created:    Mar 27, 2015
#License:    Dual license model; choose one of two:
#            New BSD License
#            http://www.opensource.org/licenses/bsd-license.php
#            - or -
#            GNU Lesser General Public License, version 2.1
#            http://www.gnu.org/licenses/lgpl-2.1.html
#            
#Copyright 2015 FireBreath development team
#\**********************************************************/

# Written to work with cmake 2.6
cmake_minimum_required (VERSION 2.6)
set (CMAKE_BACKWARDS_COMPATIBILITY 2.6)

include_directories (
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
file (GLOB GENERAL_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    src/*.cpp
)

set(SOURCES
    ${GENERAL_SRC}
)

add_library (boost_regex STATIC ${SOURCES})
set_target_properties(boost_regex PROPERTIES FOLDER "Libraries")

