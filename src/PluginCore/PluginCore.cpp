/**********************************************************\
Original Author: Richard Bateman (taxilian)

Created:    Oct 19, 2009
License:    Dual license model; choose one of two:
            New BSD License
            http://www.opensource.org/licenses/bsd-license.php
            - or -
            GNU Lesser General Public License, version 2.1
            http://www.gnu.org/licenses/lgpl-2.1.html

Copyright 2009 PacketPass, Inc and the Firebreath development team
\**********************************************************/

#include "PluginWindow.h"
#include "JSAPI.h"
#include "variant_list.h"
#include "FactoryBase.h"
#include "BrowserHost.h"
#include "DOM/Window.h"
#include "logging.h"
#include "precompiled_headers.h" // On windows, everything above this line in PCH

#include "PluginCore.h"

using namespace FB;

/***************************\
 Static initialization stuff
\***************************/

volatile int PluginCore::ActivePluginCount = 0;

std::string PluginCore::OS;
std::string PluginCore::Browser;
void PluginCore::setPlatform(std::string opsys, std::string browser)
{
    PluginCore::OS = opsys;
    PluginCore::Browser = browser;
    FBLOG_INFO("PluginCore", "os: " << opsys << "; browser: " << browser);
}

/***************************\
     Regular Class Stuff
\***************************/

PluginCore::PluginCore() : m_paramsSet(false), m_Window(NULL),
    m_windowLessParam(boost::indeterminate), m_scriptingOnly(false)
{
    FB::Log::initLogging();
    // This class is only created on the main UI thread,
    // so there is no need for mutexes here
    ++PluginCore::ActivePluginCount;
}

PluginCore::~PluginCore()
{
    // Tell the host that the plugin is shutting down
    if(m_host) {
        m_host->shutdown();
    }

    // This class is only destroyed on the main UI thread,
    // so there is no need for mutexes here
    --PluginCore::ActivePluginCount;
}

void PluginCore::setParams(const FB::VariantMap& inParams)
{
    for (FB::VariantMap::const_iterator it = inParams.begin(); it != inParams.end(); ++it)
    {
        std::string key(it->first);
        try {
            std::string value(it->second.convert_cast<std::string>());
            if (key.substr(0, 2) == "on") {
                FB::JSObjectPtr tmp;
                auto dfd = m_host->getDOMWindow()->getProperty<FB::JSObjectPtr>(value);
                auto selfPtr(shared_from_this());

                dfd.done([=](FB::JSObjectPtr tmp) -> void {
                    m_params[key] = tmp;
                });

                FBLOG_TRACE("PluginCore", "Found <param> event handler: " << key);
            } else {
                m_params[key] = it->second;
            }
        } catch (const std::exception &ex) {
            FBLOG_WARN("PluginCore", "Exception processing <param> " << key << ": " << ex.what());
            m_params[it->first] = it->second;
        }
    }
}

boost::optional<std::string> PluginCore::getParam(std::string key) {
    boost::optional<std::string> rval;
    FB::VariantMap::const_iterator fnd = m_params.find(key.c_str());
    if (fnd != m_params.end())
        rval.reset(fnd->second.convert_cast<std::string>());
    return rval;
}

FB::variant FB::PluginCore::getParamVariant( std::string key )
{
    FB::VariantMap::const_iterator fnd = m_params.find(key.c_str());
    if (fnd != m_params.end())
        return fnd->second;
    return FB::variant();
}

// If you override this, you probably want to call it again, since this is what calls back into the page
// to indicate that we're done.
bool PluginCore::setReady()
{
    bool rval = false;
    FBLOG_TRACE("PluginCore", "Plugin Ready");
    try {
        FB::VariantMap::iterator fnd = m_params.find("onload");
        if (fnd != m_params.end()) {
            FB::JSObjectPtr method = fnd->second.convert_cast<FB::JSObjectPtr>();
            if (method) {
                FBLOG_TRACE("PluginCore", "InvokeDelayed(onload)");
                m_host->delayedInvoke(250, method, FB::VariantList{ getRootJSAPI() });
                rval = true;
            }
        }
    } catch(...) {
        // Usually this would be if it isn't a JSObjectPtr or the object can't be called
    }
    onPluginReady();
    return rval;
}

bool PluginCore::isWindowless()
{
    if (boost::indeterminate(m_windowLessParam)) {
        // initialise m_windowLessParam (defaulting to not windowless)
        m_windowLessParam = false;
        FB::VariantMap::iterator itr = m_params.find("windowless");
        if (itr != m_params.end()) {
            try {
                m_windowLessParam = itr->second.convert_cast<bool>();
            } catch (const FB::bad_variant_cast& ex) {
                FB_UNUSED_VARIABLE(ex);
            }
       }
    }
    return m_windowLessParam;
}

void FB::PluginCore::SetWindow( PluginWindow *win )
{
    FBLOG_TRACE("PluginCore", "Window Set");
    if (m_Window && m_Window != win) {
        ClearWindow();
    }
    m_Window = win;
    win->AttachObserver(this);
}

void FB::PluginCore::ClearWindow()
{
    FBLOG_TRACE("PluginCore", "Window Cleared");
    if (m_Window) {
        m_Window->DetachObserver(this);
        m_Window = NULL;
    }
}

std::string FB::PluginCore::negotiateDrawingModel()
{
    return "";
}
