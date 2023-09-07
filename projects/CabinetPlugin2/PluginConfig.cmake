#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for CabinetPlugin2
#
#\**********************************************************/

set(PLUGIN_NAME "CabinetPlugin2")
set(PLUGIN_PREFIX "FCP")
set(COMPANY_NAME "")
set(COMPANY_REVDOMAIN "ru.")

# NOTE: If you are going to deploy your own extension you *must* change the
#       key and ID to your own key and matching ID.  You can use cmake/makeid.py
#       (https://gist.github.com/taxilian/d42b8768b2e3ef5c6998) to generate them
set(PLUGIN_CRX_NAME "${PLUGIN_NAME} Plugin Adapter")
set(PLUGIN_CRX_KEY "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDOqMBmB8ThMqFT3/9s/bfShwIXIlksxCwmo/VJdLScKqCc28xU2WaJmjfV4qa1K9K3SRiDTwpk53alWv/xoRXLjDnnvxmdu9AD57o7DEQAfdSRAv0grVt00/o7oudFaRlyvrHMmvjAM4fTnA3URQfEKz2L2wb/jfJt0ogcnYkWswIDAQAB")
set(PLUGIN_CRX_ID "dlfdfkalmjbghacnadegnkmbcnpmnmfn")
set(PLUGIN_CRX_WYRMHOLE_NAME ${COMPANY_NAME})
set(PLUGIN_CRX_NATIVEHOST_NAME "${COMPANY_REVDOMAIN}.firewyrmhost")

# ActiveX constants:
set(FBTYPELIB_NAME CabinetPlugin2Lib)
set(FBTYPELIB_DESC "CabinetPlugin2 1.0 Type Library")
set(IFBControl_DESC "CabinetPlugin2 Control Interface")
set(FBControl_DESC "CabinetPlugin2 Control Class")
set(IFBComJavascriptObject_DESC "CabinetPlugin2 IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "CabinetPlugin2 ComJavascriptObject Class")
set(IFBComEventSource_DESC "CabinetPlugin2 IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID 2041e46b-51b6-51e8-92f1-756594496f88)
set(IFBControl_GUID ba29b850-c52a-5df6-bb27-78220ee39998)
set(FBControl_GUID 21f111bc-ff24-5151-83b5-333e514cba9f)
set(IFBComJavascriptObject_GUID 7f3e2d99-f26d-52e1-a975-7fc58091b958)
set(FBComJavascriptObject_GUID cc60780e-6006-59d5-b2e6-7a0731b79538)
set(IFBComEventSource_GUID 831ca09d-522f-5cf2-9c01-3a2c4cc69c04)
if ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID fef00766-c5f5-597c-9ee0-aa930f8fb092)
else ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID da124eac-86cf-5c95-9aa5-be9dd7175946)
endif ( FB_PLATFORM_ARCH_32 )

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID ".CabinetPlugin2")
if ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID ".ru/CabinetPlugin2")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID ".ru/CabinetPlugin2_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )

# strings
set(FBSTRING_CompanyName "")
set(FBSTRING_PluginDescription " Docflow Plugin2")
set(FBSTRING_PLUGIN_VERSION "1.0.6.0")
set(FBSTRING_LegalCopyright "Copyright 2016 ")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}")
if (APPLE)
    # On apple, np is not needed
    set(FBSTRING_PluginFileName "${PLUGIN_NAME}")
endif()
set(FBSTRING_ProductName "CabinetPlugin2")
set(FBSTRING_FileExtents "")
if ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "CabinetPlugin2")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "CabinetPlugin2_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )
set(FBSTRING_MIMEType "application/x-cabinetplugin2")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 0)
set(FBMAC_USE_COCOA 0)
set(FBMAC_USE_COREGRAPHICS 0)
set(FBMAC_USE_COREANIMATION 0)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)
