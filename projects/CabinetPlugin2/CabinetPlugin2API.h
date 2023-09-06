/**********************************************************\

  Auto-generated CabinetPlugin2API.h

\**********************************************************/

#include <string>
#include <sstream>
#include <objbase.h>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "CabinetPlugin2.h"

#ifndef H_CabinetPlugin2API
#define H_CabinetPlugin2API

// This macro defines CabinetPlugin2APIPtr, CabinetPlugin2APIWeakPtr,
// CabinetPlugin2APIConstPtr, and CabinetPlugin2APIWeakConstPtr
FB_FORWARD_PTR(CabinetPlugin2API);

class CabinetPlugin2API : public FB::JSAPIAuto
{
public:
    ////////////////////////////////////////////////////////////////////////////
    /// @fn CabinetPlugin2API::CabinetPlugin2API(const CabinetPlugin2Ptr& plugin, const FB::BrowserHostPtr host)
    ///
    /// @brief  Constructor for your JSAPI object.
    ///         You should register your methods, properties, and events
    ///         that should be accessible to Javascript from here.
    ///
    /// @see FB::JSAPIAuto::registerMethod
    /// @see FB::JSAPIAuto::registerProperty
    /// @see FB::JSAPIAuto::registerEvent
    ////////////////////////////////////////////////////////////////////////////
    CabinetPlugin2API(const CabinetPlugin2Ptr& plugin, const FB::BrowserHostPtr& host) :
        m_plugin(plugin), m_host(host)
    {
		CoInitialize(0);

        registerMethod("echo", make_method(this, &CabinetPlugin2API::echo));
        registerMethod("echoSlowly", make_method(this, &CabinetPlugin2API::echoSlowly));
        registerMethod("testEvent", make_method(this, &CabinetPlugin2API::testEvent));
		registerMethod("getKeys", make_method(this, &CabinetPlugin2API::getKeys));
		registerMethod("newCertRequest", make_method(this, &CabinetPlugin2API::newCertRequest));
		registerMethod("installCertificate", make_method(this, &CabinetPlugin2API::installCertificate));
		registerMethod("checkCertificate", make_method(this, &CabinetPlugin2API::checkCertificate));
		registerMethod("removeCertificate", make_method(this, &CabinetPlugin2API::removeCertificate));
		registerMethod("removeKey", make_method(this, &CabinetPlugin2API::removeKey));
		registerMethod("removeKeyFromDisk", make_method(this, &CabinetPlugin2API::removeKeyFromDisk));
		registerMethod("setPassword", make_method(this, &CabinetPlugin2API::setPassword));
		registerMethod("getAuthToken", make_method(this, &CabinetPlugin2API::getAuthToken));
		registerMethod("getAuthToken2", make_method(this, &CabinetPlugin2API::getAuthToken2));
		registerMethod("getAuthToken3", make_method(this, &CabinetPlugin2API::getAuthToken3));
		registerMethod("getCertData", make_method(this, &CabinetPlugin2API::getCertData));
		registerMethod("hexToBase64", make_method(this, &CabinetPlugin2API::hexToBase64));
		registerMethod("signXml", make_method(this, &CabinetPlugin2API::signXml));
		//
		// registerMethod("getKeyContainers", make_method(this, &CabinetPlugin2API::getKeyContainers));
		//
		registerMethod("setCallback", make_method(this, &CabinetPlugin2API::setCallback));

        // Read-write property
        registerProperty("testString",
                         make_property(this,
                                       &CabinetPlugin2API::get_testString,
                                       &CabinetPlugin2API::set_testString));

        // Read-only property
        registerProperty("version", make_property(this, &CabinetPlugin2API::get_version));
		registerProperty("drives", make_property(this, &CabinetPlugin2API::get_drives));
		registerProperty("commonKeyInfo", make_property(this, &CabinetPlugin2API::get_commonKeyInfo));

		// Events
		registerEvent(std::wstring(L"oncertgenerated"));
	}

    ///////////////////////////////////////////////////////////////////////////////
    /// @fn CabinetPlugin2API::~CabinetPlugin2API()
    ///
    /// @brief  Destructor.  Remember that this object will not be released until
    ///         the browser is done with it; this will almost definitely be after
    ///         the plugin is released.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~CabinetPlugin2API() {};

    CabinetPlugin2Ptr getPlugin();

    // Read/Write property ${PROPERTY.ident}
    std::string get_testString();
    void set_testString(const std::string& val);

    // Read-only property ${PROPERTY.ident}
    std::string get_version();
	FB::variant get_drives();
	FB::variant get_commonKeyInfo();

    // Method echo
    FB::variant echo(const FB::variant& msg);
    // Method echo slowly (async echo)
    FB::variantPromise echoSlowly(const FB::variant& a);
	FB::variant getKeys(const std::string& driveLetterStr);
	FB::variant getCSPKeys();
	FB::variant preareRequest(const std::wstring& dNameStr, const std::string& iv, const std::string& driveLetter);
	FB::variant newCertRequest(const std::wstring& dNameStr, const std::string& iv, const std::string& driveLetter);
	FB::variant installCertificate(const std::string& cert64Str, const std::string& pkh64Str);
	FB::variant checkCertificate(const std::string& pkh64Str);
	FB::variant removeCertificate(const std::string& pkh64Str);
	FB::variant removeKey(const std::string& pkh64Str);
	FB::variant removeKeyFromDisk(const std::string& pkh64Str);
	FB::variant setPassword(const std::string& pkh64Str, const std::string& pwd);
	FB::variant getAuthToken_(const std::string& pkh64Str, bool normalErrors = true, const std::string& data = std::string());
	FB::variant getAuthToken_Y(const std::string& pkh64Str, bool normalErrors = true, const std::string& data64Str = std::string(), bool test = false);
	FB::variant getAuthToken_Ym(const std::string& pkh64Str, bool normalErrors = true, const std::string& data64Str = std::string(), bool test = false);
	FB::variant getAuthToken(const std::string& pkh64Str);
	FB::variant getAuthToken2(const std::string& pkh64Str, const std::string& data);
	FB::variant getAuthToken3(const std::string& pkh64Str, const std::string& data);
	FB::variant getRcptSign(const std::string& pkh64Str, const std::string& digest2001, const std::string& digest2012256);
	FB::variant getCertData(const std::string& pkh64Str);
	FB::variant hexToBase64(const std::string& dataStr);
	FB::variant signXml(const std::string& pkh64, const std::string& inputXml);
	//
	int setCallback(const FB::JSObjectPtr& callback);
	//
	FB::variant getKeyContainers(const std::string& searchStr);

    // Event helpers
    FB_JSAPI_EVENT(test, 0, ());
    FB_JSAPI_EVENT(echo, 2, (const FB::variant&, const int));
	FB_JSAPI_EVENT(certgenerated, 1, (const FB::variant&));

    // Method test-event
    void testEvent();

private:
    CabinetPlugin2WeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    std::string m_testString;

	FB::JSObjectPtr m_CallBack;

	std::string prepareString(const wchar_t* r);

	std::string prepareString(const std::string& r);

	inline std::string prepareString(const std::wstring& r)
	{
		return prepareString(r.c_str());
	}
};

#endif // H_CabinetPlugin2API

