#/**********************************************************\ 
# Auto-generated Windows project definition file for the
# CabinetPlugin2 project
#\**********************************************************/

# Windows template platform definition CMake file
# Included from ../CMakeLists.txt

# remember that the current source dir is the project root; this file is in Win/
file (GLOB PLATFORM RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    Win/[^.]*.cpp
    Win/[^.]*.h
    Win/[^.]*.rc
    Win/[^.]*.cmake
    )

# use this to add preprocessor definitions
add_definitions(
    /D "_ATL_STATIC_REGISTRY"
)

SOURCE_GROUP(Win FILES ${PLATFORM})

set (SOURCES
    ${SOURCES}
    ${PLATFORM}
    )

add_windows_plugin(${PROJECT_NAME} SOURCES)

message("=============== Setting CCOM lib ===============")
set (ccom33 ${FireBreath_SOURCE_DIR}/ccom)
target_link_libraries(${PROJECT_NAME} ${PLUGIN_INTERNAL_DEPS} debug "${ccom33}/ccom33.lib")

# This is an example of how to add a build step to sign the plugin DLL before
# the WiX installer builds.  The first filename (certificate.pfx) should be
# the path to your pfx file.  If it requires a passphrase, the passphrase
# should be located inside the second file. If you don't need a passphrase
# then set the second filename to "".  If you don't want signtool to timestamp
# your DLL then make the last parameter "".
#
# Note that this will not attempt to sign if the certificate isn't there --
# that's so that you can have development machines without the cert and it'll
# still work. Your cert should only be on the build machine and shouldn't be in
# source control!
# -- uncomment lines below this to enable signing --
#firebreath_sign_plugin(${PROJECT_NAME}
#    "${CMAKE_CURRENT_SOURCE_DIR}/sign/certificate.pfx"
#    "${CMAKE_CURRENT_SOURCE_DIR}/sign/passphrase.txt"
#    "http://timestamp.verisign.com/scripts/timestamp.dll")

# add library dependencies here; leave ${PLUGIN_INTERNAL_DEPS} there unless you know what you're doing!
target_link_libraries(${PROJECT_NAME}
    ${FB_PLUGIN_LIBRARIES}
    )

set(WIX_HEAT_FLAGS
    -gg                 # Generate GUIDs
    -srd                # Suppress Root Dir
    -cg PluginDLLGroup  # Set the Component group name
    -dr INSTALLDIR      # Set the directory ID to put the files in
    )
get_plugin_path(PLUGIN_FILEPATH ${PROJECT_NAME})
get_filename_component(PLUGIN_PATH ${PLUGIN_FILEPATH} DIRECTORY)

file(COPY ${FireBreath_SOURCE_DIR}/auto/CabinetPlugin2_auto.wxs DESTINATION ${FireBreath_SOURCE_DIR}/${PLUGIN_NAME}/)
file(COPY ${FireBreath_SOURCE_DIR}/ccom/ccom.dll DESTINATION ${FireBreath_SOURCE_DIR}/${PLUGIN_NAME}/Debug)
file(COPY ${FireBreath_SOURCE_DIR}/ccom/ccom.dll.sig DESTINATION ${FireBreath_SOURCE_DIR}/${PLUGIN_NAME}/Debug)
file(COPY ${FireBreath_SOURCE_DIR}/ccom/ccom.dll DESTINATION ${FireBreath_SOURCE_DIR}/${PLUGIN_NAME}/Release)
file(COPY ${FireBreath_SOURCE_DIR}/ccom/ccom.dll.sig DESTINATION ${FireBreath_SOURCE_DIR}/${PLUGIN_NAME}/Release)

add_wix_installer( ${PLUGIN_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/Win/WiX/CabinetPlugin2Installer.wxs
    PluginDLLGroup
    ${PLUGIN_PATH}
    $<TARGET_FILE:${PROJECT_NAME}>
    ${PROJECT_NAME}
    )

firebreath_sign_file("${PLUGIN_NAME}_WiXInstall"
    "${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/${PLUGIN_NAME}.msi"
    "${CMAKE_CURRENT_SOURCE_DIR}/sign/certificate1.pfx"
    "${CMAKE_CURRENT_SOURCE_DIR}/sign/passphrase1.txt"
    "http://timestamp.verisign.com/scripts/timestamp.dll")

# This is an example of how to add a build step to sign the WiX installer
# -- uncomment lines below this to enable signing --
#firebreath_sign_file("${PLUGIN_NAME}_WiXInstall"
#    "${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/${PLUGIN_NAME}.msi"
#    "${CMAKE_CURRENT_SOURCE_DIR}/sign/certificate.pfx"
#    "${CMAKE_CURRENT_SOURCE_DIR}/sign/passphrase.txt"
#    "http://timestamp.verisign.com/scripts/timestamp.dll")

# This is an example of how to create a cab
# -- uncomment lines below this to enable signing --
#create_cab(${PLUGIN_NAME}
#    ${CMAKE_CURRENT_SOURCE_DIR}/Win/Wix/CabinetPlugin2.ddf
#    ${CMAKE_CURRENT_SOURCE_DIR}/Win/Wix/CabinetPlugin2.inf
#    ${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/
#    ${PROJECT_NAME}_WiXInstallExe
#    )
