/**********************************************************\ 
Original Author: Richard Bateman (taxilian)

Created:    Oct 16, 2009
License:    Dual license model; choose one of two:
            New BSD License
            http://www.opensource.org/licenses/bsd-license.php
            - or -
            GNU Lesser General Public License, version 2.1
            http://www.gnu.org/licenses/lgpl-2.1.html

Copyright 2009 Richard Bateman, Firebreath development team
\**********************************************************/

#include <typeinfo>
#include "JSObject.h"

#include "precompiled_headers.h" // On windows, everything above this line in PCH
#include "NPJavascriptObject.h"
#include "NPPromise.h"
#include "Deferred.h"

using namespace FB::Npapi;

NPJavascriptObject *NPJavascriptObject::NewObject(const NpapiBrowserHostPtr& host, const FB::JSAPIWeakPtr& api, bool auto_release/* = false*/)
{
    NPJavascriptObject *obj = static_cast<NPJavascriptObject *>(host->CreateObject(&NPJavascriptObjectClass));

    if (obj) { // There are certain cases where this may have failed;
               // If obj is null, return null; it's probably during shutdown
        obj->setAPI(api, host);
        obj->m_autoRelease = auto_release;
        if (auto_release) {
            // If we're autoreleasing it we need to autoretain it
            FB::JSAPIPtr api_strong(api.lock());
            if (api_strong) {
                host->retainJSAPIPtr(api_strong);
            }
        }
    }
    return obj;
}

bool NPJavascriptObject::isNPJavaScriptObject(const NPObject* const npo)
{
    return npo->_class == &NPJavascriptObjectClass;
}

NPJavascriptObject::NPJavascriptObject(NPP npp)
    : m_valid(true), m_autoRelease(false)
{
    m_sharedRef = std::make_shared<FB::ShareableReference<NPJavascriptObject> >(this);
}

NPJavascriptObject::~NPJavascriptObject(void)
{
    if (m_autoRelease && !m_browser.expired() && !m_api.expired()) {
        // If the JSAPI object is still around and we're set to autorelease, tell the BrowserHost
        // that we're done with it.  Otherwise it's either gone or we don't control its lifecycle
        getHost()->releaseJSAPIPtr(m_api.lock());
    }
}

void NPJavascriptObject::setAPI(const FB::JSAPIWeakPtr& api, const NpapiBrowserHostPtr& host)
{
    m_api = api;
    m_browser = host;
}

void NPJavascriptObject::Invalidate()
{
    m_valid = false;
    try {
        if (!m_api.expired())
            getAPI()->invalidate();
    } catch(const std::bad_cast&) {
    }
}

bool NPJavascriptObject::HasMethod(NPIdentifier name)
{
    if (!isValid()) return false;
    try {
        std::string mName = getHost()->StringFromIdentifier(name);
        if (mName == "toString"
            || mName == "addEventListener"
            || mName == "removeEventListener") return true;
        return getAPI()->HasMethod(mName);
    } catch (const std::exception& e) {
        if (!m_browser.expired())
            getHost()->SetException(this, e.what());
        return false;
    }
}
FB::variant NPJavascriptObject::addEventListener(const std::vector<FB::variant> args) {
    if (isValid() && args.size() > 1 && args.size() < 4) {
        try {
            std::string evtName = "on" + args[0].convert_cast<std::string>();
            FB::JSObjectPtr method(args[1].convert_cast<FB::JSObjectPtr>());
            getAPI()->registerEventMethod(evtName, method);
            return FB::variant();
        } catch (const std::bad_cast& e) {
            throw FB::invalid_arguments(e.what());
        }
    } else {
        throw FB::invalid_arguments();
    }
}

FB::variant NPJavascriptObject::removeEventListener( const std::vector<FB::variant> args )
{
    if (isValid() && args.size() > 1 && args.size() < 4) {
        try {
            std::string evtName = "on" + args[0].convert_cast<std::string>();
            FB::JSObjectPtr method(args[1].convert_cast<FB::JSObjectPtr>());
            getAPI()->unregisterEventMethod(evtName, method);
            return FB::variant();
        } catch (const std::bad_cast& e) {
            throw FB::invalid_arguments(e.what());
        }
    } else {
        throw FB::invalid_arguments();
    }
}

void NPJavascriptObject::setPromise(FB::variantPromise promise, NPVariant *result) {
    auto npPromise = NPPromise::create(getHost(), promise);
    OBJECT_TO_NPVARIANT(npPromise->getNPPromise(), *result);
}

bool NPJavascriptObject::Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    VOID_TO_NPVARIANT(*result);
    if (!isValid()) return false;
    try {
        std::string mName;
        NpapiBrowserHostPtr browser(getHost());
        if (name) {
            mName = browser->StringFromIdentifier(name);
        }
        std::vector<FB::variant> vArgs;
        for (unsigned int i = 0; i < argCount; i++) {
            vArgs.emplace_back(browser->getVariant(&args[i]));
        }

        // Default method call
        FB::variantPromise ret;
        if (mName == "addEventListener") {
            ret = addEventListener(vArgs);
        } else if (mName == "removeEventListener") {
            ret = removeEventListener(vArgs);
        } else {
            ret = getAPI()->Invoke(mName, vArgs);
        }
        setPromise(ret, result);
        return true;
    } catch (const std::exception& e) {
        auto ep = std::current_exception();
        try {
            FB::variantDeferred dfd;
            dfd.reject(ep);
            setPromise(dfd.promise(), result);
            return true;
        } catch (...) {
            return false;
        }
    }
}

bool NPJavascriptObject::InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    return Invoke(nullptr, args, argCount, result);
}

bool NPJavascriptObject::HasProperty(NPIdentifier name)
{
    if (!isValid()) return false;
    try {
        NpapiBrowserHostPtr browser(getHost());
        // Handle numeric identifiers
        if(!browser->IdentifierIsString(name)) {
            int32_t sIdx = browser->IntFromIdentifier(name);
            return getAPI()->HasProperty(sIdx);
        }

        std::string sName(browser->StringFromIdentifier(name));
        // We check for events of that name as well in order to allow setting of an event handler in the
        // old javascript style, i.e. plugin.onload = function() .....;

        return !HasMethod(name) && getAPI()->HasProperty(sName);
    } catch (const std::exception& e) {
        if (!m_browser.expired()) 
            getHost()->SetException(this, e.what());
        return false;
    }
}

bool NPJavascriptObject::GetProperty(NPIdentifier name, NPVariant *result)
{
    if (!isValid()) return false;
    try {
        NpapiBrowserHostPtr browser(getHost());
        FB::variantPromise ret;
        if (browser->IdentifierIsString(name)) {
            std::string sName(browser->StringFromIdentifier(name));
            ret = getAPI()->GetProperty(sName);
        } else {
            ret = getAPI()->GetProperty(browser->IntFromIdentifier(name));
        }

        setPromise(ret, result);
        return true;
    } catch (const std::exception& e) {
        auto ep = std::current_exception();
        FB::variantDeferred dfd;
        dfd.reject(ep);
        setPromise(dfd.promise(), result);
        return false;
    }
}

bool NPJavascriptObject::SetProperty(NPIdentifier name, const NPVariant *value)
{
    if (!isValid()) return false;
    try {
        NpapiBrowserHostPtr browser(getHost());
        FB::variant arg = browser->getVariant(value);
        if (browser->IdentifierIsString(name)) {
            std::string sName(browser->StringFromIdentifier(name));
            getAPI()->SetProperty(sName, arg);
        } else {
            getAPI()->SetProperty(browser->IntFromIdentifier(name), arg);
        }
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

bool NPJavascriptObject::RemoveProperty(NPIdentifier name)
{
    if (!isValid()) return false;
    try {
        NpapiBrowserHostPtr browser(getHost());
        if (browser->IdentifierIsString(name)) {
            std::string sName(browser->StringFromIdentifier(name));
            getAPI()->RemoveProperty(sName);
        } else {
            getAPI()->RemoveProperty(browser->IntFromIdentifier(name));
        }
        return true;
    } catch (const std::exception& e) {
        if (!m_browser.expired())
            getHost()->SetException(this, e.what());
        return false;
    }
}

bool NPJavascriptObject::Enumeration(NPIdentifier **value, uint32_t *count)
{
    if (!isValid()) return false;
    try {
        std::vector<std::string> memberList;
        getAPI()->getMemberNames(memberList);
        *count = memberList.size() + 2;
        NPIdentifier *outList(nullptr);

        NpapiBrowserHostPtr browser(getHost());
        outList = (NPIdentifier*)browser->MemAlloc((uint32_t)(sizeof(NPIdentifier) * *count));
        
        for (uint32_t i = 0; i < memberList.size(); i++) {
            outList[i] = browser->GetStringIdentifier(memberList.at(i).c_str());
        }
        outList[memberList.size()] = browser->GetStringIdentifier("addEventListener");
        outList[memberList.size() + 1] = browser->GetStringIdentifier("removeEventListener");
        *value = outList;
        return true;
    } catch (const std::exception& e) {
        *count = 0;
        if (!m_browser.expired())
            getHost()->SetException(this, e.what());
        return false;
    }
}


/****************************************************************************\
  These are the static functions given to the browser in the NPClass struct.
  You might look at these as the "entry points" for the NPJavascriptObject
\****************************************************************************/

NPObject *NPJavascriptObject::_Allocate(NPP npp, NPClass *aClass)
{
    return (NPObject *)new NPJavascriptObject(npp);
}

void NPJavascriptObject::_Deallocate(NPObject *npobj)
{
    delete static_cast<NPJavascriptObject *>(npobj);
}

void NPJavascriptObject::_Invalidate(NPObject *npobj)
{
    NPJavascriptObject *obj = static_cast<NPJavascriptObject *>(npobj);
    obj->Invalidate();
}

bool NPJavascriptObject::_HasMethod(NPObject *npobj, NPIdentifier name)
{
    NPJavascriptObject *obj = static_cast<NPJavascriptObject *>(npobj);
    return obj->HasMethod(name);
}

bool NPJavascriptObject::_Invoke(NPObject *npobj, NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    NPJavascriptObject *obj = static_cast<NPJavascriptObject *>(npobj);
    return obj->Invoke(name, args, argCount, result);
}

bool NPJavascriptObject::_InvokeDefault(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    NPJavascriptObject *obj = static_cast<NPJavascriptObject *>(npobj);
    return obj->InvokeDefault(args, argCount, result);
}

bool NPJavascriptObject::_HasProperty(NPObject *npobj, NPIdentifier name)
{
    NPJavascriptObject *obj = static_cast<NPJavascriptObject *>(npobj);
    return obj->HasProperty(name);
}

bool NPJavascriptObject::_GetProperty(NPObject *npobj, NPIdentifier name, NPVariant *result)
{
    NPJavascriptObject *obj = static_cast<NPJavascriptObject *>(npobj);
    return obj->GetProperty(name, result);
}

bool NPJavascriptObject::_SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value)
{
    NPJavascriptObject *obj = static_cast<NPJavascriptObject *>(npobj);
    return obj->SetProperty(name, value);
}

bool NPJavascriptObject::_RemoveProperty(NPObject *npobj, NPIdentifier name)
{
    NPJavascriptObject *obj = static_cast<NPJavascriptObject *>(npobj);
    return obj->RemoveProperty(name);
}

bool NPJavascriptObject::_Enumeration(NPObject *npobj, NPIdentifier **value, uint32_t *count)
{
    NPJavascriptObject *obj = static_cast<NPJavascriptObject *>(npobj);
    return obj->Enumeration(value, count);
}

bool NPJavascriptObject::_Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    return false;
}

// This defines the "entry points"; it's how the browser knows how to create the object
// when you call NPN_CreateObject, and how it knows how to call functions on it
NPClass NPJavascriptObject::NPJavascriptObjectClass = {
    NP_CLASS_STRUCT_VERSION_CTOR,
    NPJavascriptObject::_Allocate,
    NPJavascriptObject::_Deallocate,
    NPJavascriptObject::_Invalidate,
    NPJavascriptObject::_HasMethod,
    NPJavascriptObject::_Invoke,
    NPJavascriptObject::_InvokeDefault,
    NPJavascriptObject::_HasProperty,
    NPJavascriptObject::_GetProperty,
    NPJavascriptObject::_SetProperty,
    NPJavascriptObject::_RemoveProperty,
    NPJavascriptObject::_Enumeration,
    NPJavascriptObject::_Construct
};
