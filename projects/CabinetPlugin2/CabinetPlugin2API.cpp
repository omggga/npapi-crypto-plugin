/**********************************************************\

  Auto-generated CabinetPlugin2API.cpp

\**********************************************************/

//#include "cades.h"
#include "Windows.h"
#   include <wincrypt.h>
#   include <prsht.h>
#include "CryptoPro\WinCryptEx.h"

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"
#include <future>

#include "CabinetPlugin2API.h"



#include "ProtocolAppPrecompile.h" // precompiled 
// #include "Resource.h"

#define _KEY_FOR_CABINET_SERVER

/*
#include <low-level/SmartVeryLowLevel.h>
#include <low-level/SmartException.h>
#include <low-level/SmartPtr.h>
#include <low-level/SmartUtil.h>
*/

#include "low-level/SmartEToken.h"
//#include <low-level/XmlDSigHelper33.h>
#include "_cpp/SlotCSP_CCOM.h"
//
#include "ax/coclasses/AX_SlotClient.h"
#include "ax/coclasses/AX_SlotDataStream.h"
#include "ax/coclasses/AX_SlotXmlFilter.h"

#include "PKI.h"

#pragma comment(lib, "Crypt32.lib" )

using namespace ;



///////////////////////////////////////////////////////////////////////////////
/// @fn FB::variant CabinetPlugin2API::echo(const FB::variant& msg)
///
/// @brief  Echos whatever is passed from Javascript.
///         Go ahead and change it. See what happens!
///////////////////////////////////////////////////////////////////////////////
FB::variant CabinetPlugin2API::echo(const FB::variant& msg)
{
    static int n(0);
    fire_echo("So far, you clicked this many times: ", n++); 

    // return "foobar";
    return msg;
}

///////////////////////////////////////////////////////////////////////////////
/// @fn FB::variant CabinetPlugin2API::echo(const FB::variant& msg)
///
/// @brief  Echos whatever is passed from Javascript but asynchronously;
///         This is a great example of how async resolution works
///////////////////////////////////////////////////////////////////////////////
FB::variantPromise CabinetPlugin2API::echoSlowly(const FB::variant& a)
{
    FB::variantDeferred dfd;

    auto callback = [dfd, a]() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        dfd.resolve(a);
    };

    std::async(callback);

    return dfd.promise();
}


///////////////////////////////////////////////////////////////////////////////
/// @fn CabinetPlugin2Ptr CabinetPlugin2API::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
CabinetPlugin2Ptr CabinetPlugin2API::getPlugin()
{
    CabinetPlugin2Ptr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

// Read/Write property testString
std::string CabinetPlugin2API::get_testString()
{
    return m_testString;
}

void CabinetPlugin2API::set_testString(const std::string& val)
{
    m_testString = val;
}

// Read-only property version
std::string CabinetPlugin2API::get_version()
{
    return FBSTRING_PLUGIN_VERSION;
}

void CabinetPlugin2API::testEvent()
{
    fire_test();
}






//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// LK stuff 

FB::variant CabinetPlugin2API::get_drives()
{
	try
	{
		// return "test!";
		// 
		SharedArray<string> drives = PKITools::GetKeyDrives();
		//
		string driveLetters = L"[";
		for (int i = 0; i < drives.GetSize(); i++)
		{
			if (i > 0) driveLetters += L", ";
			driveLetters += string(L"\"") + drives[i] + L"\"";
		}
		driveLetters += L"]";
		//
		std::string result = _A(driveLetters);
		//
		return prepareString(result);
	}
	catch (::::Exception e)
	{
		std::wstring r = L"{\"error\": \"" + _W(e.GetMsg()) + "\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
	catch (...)
	{
		std::wstring r = L"{\"error\": \"unknown exception\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
}

FB::variant CabinetPlugin2API::getKeys(const std::string& driveLetterStr)
{
	try
	{
		string driveLetter(_A(driveLetterStr.c_str()));
		//
		SharedArray<string> keys = PKITools::GetKeys(driveLetter);
		//
		string keysA = L"";
		for (int i = 0; i < keys.GetSize(); i++)
		{
			if (i > 0) keysA += L", ";
			keysA += keys[i];
		}
		//
		std::string result = _A(keysA);
		//
		return prepareString(result);
	}
	catch (::::Exception e)
	{
		std::wstring r = L"{\"error\": \"" + _W(e.GetMsg()) + "\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
	catch (...)
	{
		std::wstring r = L"{\"error\": \"unknown exception\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
}

//FB::variant getCSPKeys(const std::string& searchStr)
//{
//	try
//	{
//		string driveLetter(_A(driveLetterStr.c_str()));
//		//
//		SharedArray<string> keys = PKITools::GetKeys(driveLetter);
//		//
//		string keysA = L"";
//		for (int i = 0; i < keys.GetSize(); i++)
//		{
//			if (i > 0) keysA += L", ";
//			keysA += keys[i];
//		}
//		//
//		std::string result = _A(keysA);
//		//
//		return prepareString(result);
//	}
//	catch (::::Exception e)
//	{
//		std::wstring r = L"{\"error\": \"" + _W(e.GetMsg()) + "\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
//		return prepareString(r);
//	}
//	catch (...)
//	{
//		std::wstring r = L"{\"error\": \"unknown exception\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
//		return prepareString(r);
//	}
//}

FB::variant CabinetPlugin2API::getKeyContainers(const std::string& searchStr)
{
	try
	{
		string search(_A(searchStr.c_str()));
		//
		SharedArray<string> keyContainers = PKITools::GetKeyContainers2001(search);
		//
		string keysA = L"";
		for (int i = 0; i < keyContainers.GetSize(); i++)
		{
			if (i > 0) keysA += L", ";
			keysA += keyContainers[i];
		}
		//
		std::string result = _A(keysA);
		//
		return prepareString(result);
	}
	catch (::::Exception e)
	{
		std::wstring r = L"{\"error\": \"" + _W(e.GetMsg()) + "\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
	catch (...)
	{
		std::wstring r = L"{\"error\": \"unknown exception\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
}


FB::variant CabinetPlugin2API::get_commonKeyInfo()
{
	try
	{
		string result = _W(PKITools::GetCommonKeyInfoJSON());
		//
		return prepareString(result);
	}
	catch (::::Exception e)
	{
		std::string result = _A(e.GetMsg());
		return prepareString(result);
	}
	catch (...)
	{
		string r = L"{\"error\": \"unknown exception\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
}


FB::variant CabinetPlugin2API::installCertificate(const std::string& cert64Str, const std::string& pkh64Str)
{
	try
	{
		string certificate64(cert64Str.c_str());
		string pkh64(pkh64Str.c_str());
		//string serialNumber(sn.c_str());
		//string driveLetter(driveLetterStr.c_str());
		//
		PKITools::InstallCertificate(certificate64, pkh64/*, serialNumber, driveLetter*/);
		//
		string result = pkh64;
		return prepareString(result);
	}
	catch (::::Exception e)
	{
		std::wstring r = L"{\"error\": \"" + _W(e.GetMsg()) + "\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
	catch (...)
	{
		std::wstring r = L"{\"error\": \"unknown exception\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
}

FB::variant CabinetPlugin2API::checkCertificate(const std::string& pkh64Str)
{
	try
	{
		string pkh64(pkh64Str.c_str());
		//string serialNumber(sn.c_str());
		//string driveLetter(driveLetterStr.c_str());
		//
		string certificate64 = PKITools::GetCertificate(pkh64/*, serialNumber, driveLetter*/);
		//
		std::string result = (certificate64.GetLength() > 0) ? "1" : "0";
		//
		return prepareString(result);
	}
	catch (::::Exception e)
	{
		std::wstring r = L"{\"error\": \"" + _W(e.GetMsg()) + "\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
	catch (...)
	{
		std::wstring r = L"{\"error\": \"unknown exception\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
}

FB::variant CabinetPlugin2API::removeKey(const std::string& pkh64Str)
{
	try
	{
		// TODO: %%% 
		string pkh64(pkh64Str.c_str());
		//string serialNumber(sn.c_str());
		//string driveLetter(driveLetterStr.c_str());
		//
		string r = PKITools::RemoveKey(pkh64/*, serialNumber, driveLetter*/);
		//
		std::string result(_A(r));
		return prepareString(result);
	}
	catch (::::Exception e)
	{
		std::wstring r = L"{\"error\": \"" + _W(e.GetMsg()) + "\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
	catch (...)
	{
		std::wstring r = L"{\"error\": \"unknown exception\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
}

FB::variant CabinetPlugin2API::removeKeyFromDisk(const std::string& pkh64Str)
{
	try
	{
		string pkh64(pkh64Str.c_str());
		//string serialNumber(sn.c_str());
		//string driveLetter(driveLetterStr.c_str());
		//
		PKITools::RemoveKeyFromDisk(pkh64/*, serialNumber, driveLetter*/);
		//
		std::string result("1");
		return prepareString(result);
	}
	catch (::::Exception e)
	{
		std::wstring r = L"{\"error\": \"" + _W(e.GetMsg()) + "\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
	catch (...)
	{
		std::wstring r = L"{\"error\": \"unknown exception\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
}

FB::variant CabinetPlugin2API::removeCertificate(const std::string& pkh64Str)
{
	try
	{
		string pkh64(pkh64Str.c_str());
		//string serialNumber(sn.c_str());
		//string driveLetter(driveLetterStr.c_str());
		//
		PKITools::RemoveCertificate(pkh64/*, serialNumber, driveLetter*/);
		//
		std::string result("");
		return prepareString(result);
	}
	catch (::::Exception e)
	{
		std::wstring r = L"{\"error\": \"" + _W(e.GetMsg()) + "\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
	catch (...)
	{
		std::wstring r = L"{\"error\": \"unknown exception\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
}





FB::variant CabinetPlugin2API::newCertRequest(
	const std::wstring& dNameStr, const std::string& iv, const std::string& driveLetterStr
	)
{
	try
	{
		// OutputDebugStringW((const wchar_t*)dNameStr.c_str());

		// return "2015-01-13 (1)";   
		//
		string dNameMap(dNameStr.c_str());
		string driveLetter(driveLetterStr.c_str());

		// return "DN=" + dNameStr; 
		SharedArray<string> m = PKITools::ParseDN(dNameMap);

		if (driveLetter.Left(string(L"_CryptoPro").GetLength()) == L"_CryptoPro")
		{
			Blob reqData;
			AsnObject requestO = PKITools::newCertRequestCryptoPro(driveLetter, m, iv, reqData);
			//
			string pkh64;
			string algS;
			string paramsS;
			string pubS;
			//
			string reqStr = __ToBase64(reqData);
			//
			FB::VariantList result;
			PKITools::prepareRequest(requestO, algS, paramsS, pubS, reqStr, pkh64);
			result.push_back(prepareString(reqStr));
			result.push_back(prepareString(std::string(_A(pkh64))));
			result.push_back(prepareString(algS));
			result.push_back(prepareString(paramsS));
			result.push_back(prepareString(pubS));
			//
			fire_certgenerated(result);
			//
			return result;
		}


		//return "DN=" + dNameStr; 

		string pkiPolicyOid(L"1.2.643.6.2.1.7.1");
		//
		if (!(
			(pkiPolicyOid == L"1.2.643.6.2.1.7.1") ||
			(pkiPolicyOid == L"1.2.643.6.2.1.7.2")
			))
		{
			string msg = L"���������������� ��������: " + pkiPolicyOid;
			throw MethodError(msg);
			//rc = m_spDocument->SetQueryParameterEx(
			//	CComBSTR(L"pki-policy-oid-msg"),CComBSTR(msg),CComBSTR(L"POST"),CComBSTR("text"));
			//if (rc != S_OK) throw MethodError(rc);
			//requestOk = false;
		}
		//
		// ������-�������:
		string cryptoSystem = L"CryptoCOM";
		//
		if (!(
			(cryptoSystem == L"CryptoCOM")
			))
		{
			string msg = L"���������������� ������-�������: %s" + _W(cryptoSystem);
			throw MethodError(msg);
		}
		//
		string keyMedia = L"drive";
		//
		// ===============================================
		// ������ �� �������� ��������:
		//
		string keyContainerPwd = L"";
		keyContainerPwd = PKITools::GetDNElement(m, L"password");
		if (keyContainerPwd == L"__NO_PASSWORD__") keyContainerPwd = L"";
		//
		string keyContainerPwd2 = keyContainerPwd;
		//
		if (keyMedia == L"eToken")
		{
			keyContainerPwd = FormatStr(L"%u", (int)RandomInt32());
			keyContainerPwd2 = keyContainerPwd;
		}
		//
		string msgFieldRequired = L"������������ ����";
		//
		// ���
		//
		string Client_F; // = L"������";
		string Client_I; // = L"����";
		string Client_O; // = L"��������";
		//
		string INN = PKITools::GetDNElement(m, L"1.2.643.3.131.1.1"); // L"11111111";
		string OGRN = PKITools::GetDNElement(m, L"1.2.643.100.1"); // L"2222222222";
		string SNILS = PKITools::GetDNElement(m, L"1.2.643.100.3");
		//
		// ----
		// Extra parameters by CommonName 
		//
		//
		// ----
		// ������ ������ 
		//
		bool ur = (pkiPolicyOid == X500::GetOID(L"_PKI_��������_�"));
		//
		CertRequest request = new CertRequestObject();
		AsnObject& R = request->GetRequest();
		//
		// * Subject CSP tool (!) , since 2013 
		//
		//AsnObject cspText(string(L"\"��������� CSP\" (������ 3.6)"),AsnObject::UTF8String);   
		AsnObject cspText(string(L"���� \"������-��� 3.2\""), AsnObject::UTF8String);
		//
		AsnObject& oSubjectSignTool = R.CreateCertificateExtension(X500().sSubjectSignTool);
		//AsnObject& o3 = (AsnObject&)oSubjectSignTool.OctetString().Deep; 
		//AsnObject& o2 = ((AsnObject&)oSubjectSignTool[1]).OctetString().Deep; 
		int n1 = oSubjectSignTool.ChildCount();
		AsnObject& o1 = oSubjectSignTool[0];
		//OutputDebugStringW(o1.Dump());
		((AsnObject&)oSubjectSignTool[1]).Deep = cspText;
		//OutputDebugStringW(oSubjectSignTool.Dump());
		//
		// * Subject
		//
		// return "DN=" + dNameStr + " (2k)"; 
		NameDescription subject;
		//
		string oid;
		string inputOid;
		string v;
		//
		Client_F = PKITools::GetDNElement(m, L"CLF");
		Client_I = PKITools::GetDNElement(m, L"CLI");
		Client_O = PKITools::GetDNElement(m, L"CLO");
		string givenNames = Client_I;
		if (Client_O.GetLength() > 0) givenNames += L" " + Client_O;
		//
		// ** CommonName
		//
		string commonName = L"UNKNOWN";
		//
		oid = X500::GetOID(L"CommonName");
		commonName = PKITools::GetDNElement(m, L"O"); // = L"";
		//
		// !!!
		// commonName = dName;
		subject.SetAttribute(OID(oid), AsnObject(commonName, AsnObject::BMPString));
		//
		// ** FIO
		//
		oid = X500::GetOID(L"SurName");
		subject.SetAttribute(OID(oid), AsnObject(Client_F, AsnObject::BMPString));
		//
		oid = X500::GetOID(L"GivenName");
		subject.SetAttribute(OID(oid), AsnObject(givenNames, AsnObject::BMPString));
		//
		// ** Email
		//
		oid = X500::GetOID(L"Email");
		v = PKITools::GetDNElement(m, L"E"); // = L"user@test-testovich.ru";
		subject.SetAttribute(OID(oid), AsnObject(v, AsnObject::BMPString));
		//
		// ** CountryName
		//
		oid = X500::GetOID(L"CountryName");
		//if (GetQueryParameter(CComBSTR(L"..."),&bstrV2) == S_OK) v = bstrV2;
		//else v = L"";
		subject.SetAttribute(OID(oid), AsnObject(
			// (string)L"RU"
			PKITools::GetDNElement(m, L"C")
			, AsnObject::BMPString));
		//
		// ** StateOrProvinceName 
		//
		oid = X500::GetOID(L"StateOrProvinceName");
		v = L"";
		if (PKITools::DNElementProvided(m, L"S"))
		{
			v = PKITools::GetDNElement(m, L"S"); // = "������"; 
		}
		if (v.GetLength() > 0)
			subject.SetAttribute(OID(oid), AsnObject(v, AsnObject::BMPString));
		//
		// ** LocalityName
		//
		oid = X500::GetOID(L"LocalityName");
		string gorod = PKITools::GetDNElement(m, L"L"); // = L"������";
		string naselPunkt;
		//
		v = gorod.GetLength() > 0 ? gorod : naselPunkt;
		//
		if (v.GetLength() > 0)
			subject.SetAttribute(OID(oid), AsnObject(v, AsnObject::BMPString));
		//
		// ** Street address
		//
		oid = X500::GetOID(L"StreetAddress");
		string streetaddr = PKITools::GetDNElement(m, L"1.2.643.6.2.1.6.1.100.6"); // �����
		string dom = PKITools::GetDNElement(m, L"1.2.643.6.2.1.6.1.100.7");
		string korpus = PKITools::GetDNElement(m, L"1.2.643.6.2.1.6.1.100.8");
		string kvo = PKITools::GetDNElement(m, L"1.2.643.6.2.1.6.1.100.9");
		//
		if (dom.GetLength() > 0) streetaddr += L", " + dom;
		if (korpus.GetLength() > 0) streetaddr += L", " + korpus;
		if (kvo.GetLength() > 0) streetaddr += L", " + kvo;
		//
		subject.SetAttribute(OID(oid), AsnObject(streetaddr, AsnObject::BMPString));
		//
		// ** Title
		//
		string title = PKITools::GetDNElement(m, L"T");;
		oid = X500::GetOID(L"Title");
		subject.SetAttribute(OID(oid), AsnObject(title, AsnObject::BMPString));
		//
		// ** OrganizationName
		//
		string OrganizationName;
		//
		oid = X500::GetOID(L"OrganizationName");
		if (ur) // ������� ������������ ����������� 
		{
			v = PKITools::GetDNElement(m, L"O"); // = L"";
												 //
			OrganizationName = v;

			if (v.GetLength() > 0)
				subject.SetAttribute(OID(oid), AsnObject(v, AsnObject::BMPString));
		}
		//
		// ** OrganizationUnitName
		//
		oid = X500::GetOID(L"OrganizationalUnitName");
		if (ur) // ������� ������������ ����������� 
		{
			v = PKITools::GetDNElement(m, L"OU"); 
			if (v.GetLength() > 0)
				subject.SetAttribute(OID(oid), AsnObject(v, AsnObject::BMPString));
		}
		//
		// ** INN, OGRN, SNILS 
		//
		if (INN.GetLength() > 10) INN = INN.Right(10);
		OutputDebugStringW(INN);
		//
		if (INN.GetLength() > 0)
		{
			string INN_v = INN;
			while (INN_v.GetLength() < 12) INN_v = L"0" + INN_v;
			subject.SetAttribute(OID(X500().sINN), AsnObject(INN_v, AsnObject::NumericString));
		}
		if (OGRN.GetLength() > 0)
		{
			subject.SetAttribute(OID(X500().sOGRN), AsnObject(OGRN, AsnObject::NumericString));
		}
		if (SNILS.GetLength() > 0)
		{
			subject.SetAttribute(OID(X500().sSNILS), AsnObject(SNILS, AsnObject::NumericString));
		}
		//
		R.Subject = subject;
		//
		// * SubjectAltName 
		//
		NameDescription subjectAltName;
		//
		string xOIDs[64];
		string xOIDValues[64];
		//
		int n = 0;
		xOIDs[n++] = X500::GetOID(L"_PKI_�������");
		xOIDs[n++] = X500::GetOID(L"_PKI_���");
		xOIDs[n++] = X500::GetOID(L"_PKI_��������");
		//
		xOIDs[n++] = X500::GetOID(L"_PKI_�����_������������");
		xOIDs[n++] = X500::GetOID(L"_PKI_�����_�����������");
		xOIDs[n++] = X500::GetOID(L"_PKI_�����_�����������");
		xOIDs[n++] = X500::GetOID(L"_PKI_�����_��������");
		xOIDs[n++] = X500::GetOID(L"_PKI_�����_����������");
		//
		xOIDs[n++] = X500::GetOID(L"_PKI_��������������");
		//
		xOIDs[n++] = X500::GetOID(L"_PKI_��_���");
		xOIDs[n++] = X500::GetOID(L"_PKI_��_����");
		//
		xOIDs[n++] = X500::GetOID(L"_PKI_�����_������������");
		xOIDs[n++] = X500::GetOID(L"_PKI_�����_�����������");
		xOIDs[n++] = X500::GetOID(L"_PKI_�����_�����������");
		xOIDs[n++] = X500::GetOID(L"_PKI_�����_��������");
		xOIDs[n++] = X500::GetOID(L"_PKI_�����_����������");
		//
		xOIDs[n++] = X500::GetOID(L"_PKI_�����_������");
		xOIDs[n++] = X500::GetOID(L"_PKI_�����_��");
		xOIDs[n++] = X500::GetOID(L"_PKI_�����_�����");
		xOIDs[n++] = X500::GetOID(L"_PKI_�����_�����");
		xOIDs[n++] = X500::GetOID(L"_PKI_�����_��");
		xOIDs[n++] = X500::GetOID(L"_PKI_�����_�����");
		xOIDs[n++] = X500::GetOID(L"_PKI_�����_���");
		xOIDs[n++] = X500::GetOID(L"_PKI_�����_������");
		xOIDs[n++] = X500::GetOID(L"_PKI_�����_����");
		//
		subjectAltName.SetAttribute(OID(X500::GetOID(L"_PKI_��_���"))
			, AsnObject(INN, AsnObject::BMPString));
		subjectAltName.SetAttribute(OID(X500::GetOID(L"_PKI_��_����"))
			, AsnObject(OGRN, AsnObject::BMPString));
		//
		//
		R.SubjectAltName = subjectAltName;
		//
		//
		//
		//
		//
		// * CertificatePolicies
		//
		R.RemoveAllPolicies();
		R.AddPolicyToRequest(X500().sPolicyKC1);
		R.AddPolicyToRequest(X500().sPolicyKC2);
		R.AddPolicyToRequest(L"1.2.643.6.2.1.7.1");
		//
		AsnObject& oExtensions = ((AsnObject&)R[0]).Tagged(0);
		AsnObject& oExtensions_0 = oExtensions[0];
		AsnObject& oExtensions_0_1 = oExtensions_0[1];
		AsnObject& oExtensions_0_1_0 = oExtensions_0_1[0];
		//OutputDebugStringW(L"\n-----------------------------------------------------\n" + 
		//		oExtensions_0_1_0.Dump() + L"\n"); 
		AsnObject& oConstraints = oExtensions_0_1_0; // oExtensions_0_1.Children[OID(L"2.5.29.19")];
													 //
		AsnObject s1 = AsnObject::NewSequence();
		s1.Add(AsnObject(OID(L"2.5.29.19")));
		AsnObject oFalse(false, AsnObject::UNIVERSAL, AsnObject::BOOLEAN);
		oFalse.m_Integer = 0;
		s1.Add(oFalse);
		Blob buf;
		buf.Allocate(10);
		buf[0] = 0x04; buf[1] = 0x08; buf[2] = 0x30; buf[3] = 0x06;
		buf[4] = 0x01; buf[5] = 0x01; buf[6] = 0xFF; buf[7] = 0x02;
		buf[8] = 0x01; buf[9] = 0x00;
		AsnObject p1(buf);
		s1.Add(p1);
		//
		//
		//
		// ----
		// �������� �������� ����� � ������� 
		//
		Key key;
		//*
		TextMap containerFiles;
		CCOM_Key ccom_key;
		//*/
		///SharedPtr<EToken> eToken;
		//
		//*
		ccom_key->InitKeyTime(); // TODO: ���������
		COleDateTime keyTime = ccom_key->GetKeyTime();
		//*/
		CString keyTimeSuffix = //_S("15-01-12-18-28-36"); 
			FormatTime_ymd_HMD(
				_S("%02d-%02d-%02d"), _S("-%02d-%02d-%02d") // _T("%y-%m-%d-%H-%M-%S")) 
				, keyTime
				);
		//
		CString keyName = _T("-") + keyTimeSuffix;
		//
		CString keyPath;
		CString containerPath;
		//
		string eTokenID;
		int key_i = -1;
		//
		// PKCS11_Manager& M = PKCS11_Manager::Acquire(); 
		//
		//return jstring();
		// return jstring((const wchar_t*)keyName);
		//
		HRESULT rc = 0;
		//
		// return "test 1"; 
		//
		if (cryptoSystem == L"CryptoCOM")
		{
			containerFiles[_T("kek.opq")] = _T("1");
			containerFiles[_T("masks.db3")] = _T("1");
			containerFiles[_T("mk.db3")] = _T("1");
			containerFiles[_T("rand.opq")] = _T("1");
			//
			if (keyMedia == _T("eToken"))
			{
			}
			else // keyMedia == _T("drive") 
			{
				// ��� ��������� ��������:
				//
				if (driveLetter.GetLength() == 0)
				{
					SharedArray<CString> drives = PKITools::GetKeyDrives();
					//
					if (drives.Length() == 0) throw MethodError(L"��� ����-���������");
					//
					driveLetter = string(_S(drives[0]));
				}
				else
				{
				}
				//
				CString Path;
				try
				{
					Path = Machine::TouchDirectory(_S(driveLetter) + _T(":\\"));
				}
				catch (::::Exception e)
				{
					////OutputDebugString(_S(e.GetXml())); 
					string msg2 = L"���������� �������� ���� �� ����-�������� " +
						driveLetter + L", ������ � �������� ��������";
					Exception e2 = e.AddIfNewSource_(msg2);
					////OutputDebugString(_S(e2.GetXml())); 
					throw e2;
				}
				//
				CString certDir = Machine::TouchDirectory(Path + _T("\\Certificates"));
				keyPath = Machine::TouchDirectory(certDir + _T("\\") + keyName);
				containerPath = Machine::TouchDirectory(keyPath + _T("\\Container"));
				//
				ccom_key->CreateIn(containerPath, _S(keyContainerPwd), _T(""));
			}
			//
			key = (Key)ccom_key;
		}
		//
		request->SetKey(key);
		//
		// ������ ����� ����� - �����, ��������� � �������� �����, - ��� ���������������� PKH.
		//
		Blob pkh = key->GetPKH();
		// CString pkhStr = Util::BlobToHex(pkh);
		std::string pkh64 = _A(__ToBase64(pkh));
		PKITools::Passwords()[pkh64] = _A(keyContainerPwd);
		//
		// CString keyDir = Machine::TouchDirectory( certDir+_T("\\")+pkhStr );
		//
		if (cryptoSystem == L"CryptoCOM")
		{
			XmlElement keyInfo = ccom_key->GetXmlInfo();
			//
#ifdef _DEBUG
			//OutputDebugStringW(L"\nXml KeyInfo:\n" + keyInfo.OuterXml() + L"\n"); 
#endif
			//
			if (keyMedia == _T("eToken"))
			{
				ccom_key->SaveKeyToEToken();
			}
			else // keyMedia == _T("drive")
			{
				::::File keyXml;
				keyXml.OpenToWrite(keyPath + _T("\\") + keyName + _T("-k.xml"));
				keyXml.Replace(
					_S("<?xml version=\"1.0\" encoding=\"windows-1251\" ?>") +
					(CString)keyInfo.OuterXml());
				keyXml.Close();
			}
		}
		//
		// ----
		// * ����������� � ��������� ������ 
		//
		string pkh64Str;
		string algS;
		string paramsS;
		string pubS;
		//
		string reqStr;
		//
		FB::VariantList result;
		//
		if (cryptoSystem == L"CryptoCOM")
		{
			//
			request->SignRequest(string(keyPath) + L"\\" + string(keyName) + L"-request.der"); 
			Blob requestData = request->GetRequestData(); // request->GetRequest().Encoded()
			reqStr = _A(__ToBase64(requestData));
			//
			if (keyMedia == _T("eToken"))
			{
			}
			else // keyMedia == _T("drive") 
			{
				request->SaveRequestDER(
					string(keyPath) + L"\\" + string(keyName) + L"-request.der",
					string(keyPath) + L"\\" + string(keyName) + L"-request.p10"
					);
			}
			// 
			AsnObject requestO(requestData);
			//
			PKITools::prepareRequest(requestO, algS, paramsS, pubS, reqStr, pkh64Str);

			//AsnObject& o_0 = (AsnObject&)requestO[0];
			//AsnObject& o_0_1 = (AsnObject&)o_0[1];
			//AsnObject& o_0_2 = (AsnObject&)o_0[2];
			//AsnObject& o_0_2_0 = (AsnObject&)o_0_2[0];
			//AsnObject& o_0_2_0_0 = (AsnObject&)o_0_2_0[0];
			//AsnObject& o_0_2_0_1 = (AsnObject&)o_0_2_0[1];
			//AsnObject& o_0_2_0_1_0 = (AsnObject&)o_0_2_0_1[0];
			//AsnObject& o_0_2_0_1_1 = (AsnObject&)o_0_2_0_1[1];
			//AsnObject& o_0_2_1 = (AsnObject&)o_0_2[1];
			//{
			//	string alg1 = o_0_2_0_0.Oid();
			//	string alg2 = o_0_2_0_1_0.Oid();
			//	string alg3 = o_0_2_0_1_1.Oid();
			//	algS = alg1;
			//	paramsS = alg2 + L", " + alg3;
			//	pubS = __ToBase64(o_0_2_1.Data());
			//}
			////
			//if (keyMedia == _T("eToken"))
			//{
			//}
		}
		//
		// ----
		// ���������� ���������� � ��������� �������
		//
		result.push_back(prepareString(reqStr));
		result.push_back(prepareString(pkh64));
		result.push_back(prepareString(algS));
		result.push_back(prepareString(paramsS));
		result.push_back(prepareString(pubS));
		//
		fire_certgenerated(result);
		//
		//{
		//	string pkh64 = __ToBase64(pkh);
		//	//
		//	FB::VariantList result;
		//	result.push_back(prepareString(reqStr));
		//	result.push_back(prepareString(std::string(_A(pkh64))));
		//	result.push_back(prepareString(algS));
		//	result.push_back(prepareString(paramsS));
		//	result.push_back(prepareString(pubS));
		//	//
		//	fire_certgenerated(result);
		//}
		//
		return result;
	}
	catch (::::Exception e)
	{
		//std::string result = _A(e.GetMsg());
		std::wstring r = L"{\"error\": \"" + _W(e.GetMsg()) + "\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
	catch (...)
	{
		std::wstring r = L"{\"error\": \"unknown exception\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
}

FB::variant CabinetPlugin2API::getCertData(const std::string& pkh64Str)
{
	try
	{
		string pkh64(pkh64Str.c_str());
		//
		std::wstring result = _W(PKITools::GetCommonKeyInfoJSON(pkh64));
		//
		return prepareString(result);
	}
	catch (::::Exception e)
	{
		std::wstring r = L"{\"error\": \"" + _W(e.GetMsg()) + "\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
	catch (...)
	{
		std::wstring r = L"{\"error\": \"unknown exception\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
}
















// ===============================================================================================
// SIGNING 

FB::variant CabinetPlugin2API::setPassword(
	const std::string& pkh64, 
	const std::string& pwd)
{
	try
	{
		//string serialNumber(sn.c_str());
		//string driveLetter(driveLetterStr.c_str());
		//
		if (pwd.size() > 0)
		{
			PKITools::Passwords()[pkh64] = pwd;
		}
		//
		getAuthToken_Y(pkh64, true, pkh64);
		//
		std::wstring result = L"{\"rc\": \"1\", \"pkh\": \"" + _W(pkh64.c_str()) + L"\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		//
		return prepareString(result);
	}
	catch (::::Exception e)
	{
		std::wstring r = L"{\"error\": \"" + _W(e.GetMsg()) + "\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
	catch (...)
	{
		std::wstring r = L"{\"error\": \"unknown exception\", \"function\": \"" + _W(__FUNCTION__) + "\"}";
		return prepareString(r);
	}
}

FB::variant CabinetPlugin2API::getAuthToken_Y(const std::string& pkh64Str, bool normalErrors
	, const std::string& data64Str, bool test)
{
	try
	{
		auto m = PKITools::SearchKey(_W(pkh64Str.c_str()));
		auto driveLetter = m[0];
		string pkh_ = m[1];
		if (pkh_ == L"")
			throw MethodError(L"���� �� ������");
		std::string pass;
		//
		if (driveLetter.Left(_W(L"_CryptoPro").GetLength()) == L"_CryptoPro")
		{
			// drived by CSP
			//
			::::ClientMap::Passwords()[pkh64Str] = pass;
		}
		else
		{
			if (PKITools::Passwords().find(pkh64Str) == PKITools::Passwords().end())
			{
				throw MethodError(L"���������� ������� ������!");
			}
			pass = PKITools::Passwords()[pkh64Str];
			//
			::::ClientMap::Passwords()[pkh64Str] = pass;
		}
		//
		string pkh64(pkh64Str.c_str());
		Blob pkh = FromBase64String(pkh64);
		//
		string data64_(data64Str.c_str());
		Blob data = FromBase64String(data64_);
		//
		// if (test) throw MethodError(L"_A_");
		//
		string a = PKITools::CreateSimpleSignature64(
			_W(pkh64Str.c_str()), _W(pass.c_str())
			, L"", L"", data);
		//
		std::wstring result = 
			std::wstring(L"{\"token\": \"") + std::wstring((const wchar_t*)a) + L"\"}"; 
		//
		return prepareString(result);
	}
	catch (::::Exception e)
	{
		if (normalErrors) throw;
		std::wstring r = L"{\"error\": \"" + _W(e.GetMsg()) + "\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
	catch (...)
	{
		if (normalErrors) throw;
		std::wstring r = L"{\"error\": \"unknown exception\", \"function\": \"" + _W(__FUNCTION__) + "\"}";
		return prepareString(r);
	}
}

FB::variant CabinetPlugin2API::getAuthToken_Ym(const std::string& pkh64Str
	, bool normalErrors
	, const std::string& data64Str, bool test)
{
	try
	{
		if (PKITools::Passwords().find(pkh64Str) == PKITools::Passwords().end())
		{
			throw MethodError(L"���������� ������� ������!");
		}
		std::string pass = PKITools::Passwords()[pkh64Str];
		//
		::::ClientMap::Passwords()[pkh64Str] = pass;
		//
		string pkh64(pkh64Str.c_str());
		Blob pkh = FromBase64String(pkh64);
		//
		string data64_(data64Str.c_str());
		Blob data = FromBase64String(data64_); 
		//
		if (test) throw MethodError(L"_A_");
		//
		int p, certSize;
		wchar_t pStr[64];
		//string a = PKITools::CreateSimpleSignature64(_W(pkh64Str.c_str()), _W(pass.c_str())
		//	, L"", L"", data);
		//
		// TODO: %%% !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//
		//string a = PKITools::CreateCMSSignature64(
		//	_W(pkh64Str.c_str()), _W(pass.c_str())
		//	, Blob(), true, data, &p, &certSize);
		//
		string a = PKITools::CreateCMSSignature64(
			_W(pkh64Str.c_str()), _W(pass.c_str())
			, data, true, Blob(), &p, &certSize);

		wchar_t* a2 = new wchar_t[a.GetLength() + 1];
		int i = 0;
		for (int j = 0; j < a.GetLength(); j++)
		{
			if (a[j] != '\r' && a[j] != '\n')
				a2[i++] = a[j];
		}
		a2[i++] = 0;

		swprintf(pStr, L"%d", p);
		pStr[63] = 0;
		std::wstring _pStr(pStr);

		//char msg2[1024];
		//sprintf(msg2, "Certificate position: %d", (int)p);
		//throw MethodError(_W(msg2));
		if (p < 0)
			throw MethodError(string(L"������� �� �������� ����������� (* !!! *) ") + pStr);
		//
		//Blob b = FromBase64String(a);
		//int suffix = b.GetSize() - p - certSize;
		//Blob m;
		//m.Allocate(b.Length() - certSize);
		//memcpy(m.GetBuffer(), b.GetBuffer(), p);
		//memcpy(m.GetBuffer() + p, b.GetBuffer() + p + certSize, suffix);
		//a = __ToBase64(m);
		//
		std::wstring result = 
			std::wstring(L"{\"token\": \"") + 
			PKITools::escapeJSON(std::wstring((const wchar_t*)a2)) + 
			std::wstring(L"\", \"p\": \"") + 
			_pStr + 
			std::wstring(L"\"}");
		//
		delete[] a2;
		//
		return prepareString(result);
	}
	catch (::::Exception e)
	{
		if (normalErrors) throw;
		std::wstring r = L"{\"error\": \"" + _W(e.GetMsg()) + "\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
	catch (...)
	{
		if (normalErrors) throw;
		std::wstring r = L"{\"error\": \"unknown exception\", \"function\": \"" + _W(__FUNCTION__) + "\"}";
		return prepareString(r);
	}
}

FB::variant CabinetPlugin2API::getAuthToken_(const std::string& pkh64Str
	, bool normalErrors
	, const std::string& data64Str)
{
	try
	{
		//if (PKITools::Passwords().find(pkh64Str) == PKITools::Passwords().end())
		//{
		//	throw MethodError(L"���������� ������� ������!");
		//}
		std::string pass = PKITools::Passwords()[pkh64Str];
		//
		::::ClientMap::Passwords()[pkh64Str] = pass;
		//
		string pkh64(pkh64Str.c_str());
		Blob pkh = FromBase64String(pkh64);
		//
		string data64_(data64Str.c_str());
		Blob data = FromBase64String(data64_);
		if (data.Length() == 0)
		{
			std::wstring r = L"{\"error\": \"BAD DATA\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
			return prepareString(r);
		}
		//
		string a = PKITools::CreateCMSSignature64(
			_W(pkh64Str.c_str()), _W(pass.c_str())
			, Blob(), true, data);
		std::wstring result((const wchar_t*)(L"{\"token\": \"") + 
			PKITools::escapeJSON(std::wstring((const wchar_t*)a)) + L"\"}");
		//
		return prepareString(result);
	}
	catch (::::Exception e)
	{
		if (normalErrors) throw;
		std::wstring r = L"{\"error\": \"" + _W(e.GetMsg()) + "\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
	catch (...)
	{
		if (normalErrors) throw;
		std::wstring r = L"{\"error\": \"unknown exception\", \"function\": \"" + _W(__FUNCTION__) + "\"}";
		return prepareString(r);
	}
}

FB::variant CabinetPlugin2API::getAuthToken(const std::string& pkh64Str)
{
	return getAuthToken_Y(pkh64Str, false, pkh64Str);
}

FB::variant CabinetPlugin2API::getAuthToken2(const std::string& pkh64Str, const std::string& data)
{
	return getAuthToken_(pkh64Str, false, data);
}

FB::variant CabinetPlugin2API::getAuthToken3(const std::string& pkh64Str, const std::string& data)
{
	return getAuthToken_Ym(pkh64Str, false, data, false /*test*/);
}

FB::variant CabinetPlugin2API::getRcptSign(const std::string& pkh64Str, const std::string& digest2001, const std::string& digest2012256)
{
	return getAuthToken_Ym(pkh64Str, false, digest2012256, false /*test*/);
}






FB::variant CabinetPlugin2API::signXml(
	const std::string& pkh64, 
	const std::string& inputXml)
{
	try
	{
		HRESULT rc = S_OK;
		//
		//
		Blob pkh = FromBase64String(string(pkh64.c_str()));
		ISlotClient* client = _Clients().GetClient(pkh, true); // borrowed reference, activate or not  
																  //
		CComQIPtr<ISlotSigner> pSigner(client);
		//
		// string path(L"D:\\dev\\PKI.xml");
		//
		//CComPtr<IStream> stream;
		////
		//CComPtr<ISlotFileReader> m;
		//m.Attach(
		//	CSlotFileReader::OpenFile<ISlotFileReader>(_S(path))
		//	);
		//CComQIPtr<IStream> q(m);
		//stream.Attach(q.Detach());
		// 
		// ------------------------------------------------------------
		// Signing 
		// 
		ISlotDataStreamInfo* xmlFilter = CSlotXmlFilter::CreateXmlFilter<ISlotDataStreamInfo>();
		if (!xmlFilter) throw MethodError(E_UNEXPECTED);
		//
		rc = xmlFilter->SetDataStreamParameter(
			CComBSTR(L"client"),
			CComVariant((IUnknown*)client)
			);
		if (FAILED(rc)) throw MethodError(rc);
		//
		CComPtr<ISlotDataStreamInfo> dataStreamInfo;
		dataStreamInfo.Attach(
			CSlotDataStream::CreateDataStream<ISlotDataStreamInfo>(L"text/xml") // new reference 
			);
		if (!dataStreamInfo) throw MethodError(E_UNEXPECTED);
		//
		CComBSTR bstrYes(L"yes");
		rc = xmlFilter->SetDataStreamParameter(
			CComBSTR(L"-xml-sign"),
			CComVariant(bstrYes)
			);
		if (FAILED(rc)) throw MethodError(rc);
		//
		rc = dataStreamInfo->SetDataStreamParameter(
			CComBSTR(SLOT_DATA_STREAM_OUTPUT_FILTER_PARAM),
			CComVariant((IUnknown*)xmlFilter)
			);
		if (FAILED(rc)) throw MethodError(rc);
		//
		// �������������� m_OutStream 
		//
		CComQIPtr<IStream> outStream(dataStreamInfo);
		if (!outStream) throw MethodError(E_NOINTERFACE);
		//
		// ��������� ��������� 
		//
		//CComPtr<ISlotMemoryReader> m; 
		//m.Attach(
		//	CSlotMemoryReader::ReadMemory<ISlotMemoryReader>((const void*)documentMem, doculentMemLen)   
		//	);
		//CComQIPtr<IStream> q(m);
		//stream.Attach(q.Detach()); 
		//
		return prepareString(L"Success");
	}
	catch (::::Exception e)
	{
		std::wstring r = L"{\"error\": \"" + _W(e.GetMsg()) + "\", \"function\": \"" + _W(__FUNCTION__) + L"\"}";
		return prepareString(r);
	}
	catch (...)
	{
		std::wstring r = L"{\"error\": \"unknown exception\", \"function\": \"" + _W(__FUNCTION__) + "\"}";
		return prepareString(r);
	}
}

int CabinetPlugin2API::setCallback(const FB::JSObjectPtr& callback)
{
	m_CallBack = callback;
	return 0;
}

FB::variant CabinetPlugin2API::hexToBase64(const std::string& dataStr)
{
	int n = dataStr.size() / 2;
	if (n == 0) return std::string("");
	//
	Blob data;
	data.Allocate(n);
	unsigned char c;
	//
	for (int i = 0; i < n; i++)
	{
		c = (::ByteToHexDigit(dataStr.c_str()[2 * i]) << 4) | ::ByteToHexDigit(dataStr.c_str()[2 * i + 1]);
		data[i] = c;
	}
	//
	std::string result = _A(__ToBase64(data));
	//
	return prepareString(result);
}

inline std::string CabinetPlugin2API::prepareString(const wchar_t* r)
{
	Blob b = WideStringToUTF8(r);
	char* buf = new char[b.Length() + 1];
	memcpy(buf, (const BYTE*)b, b.Length());
	buf[b.Length()] = 0;
	return std::string(buf);
}

inline std::string CabinetPlugin2API::prepareString(const std::string& r)
{
	return prepareString(_W(r.c_str()));
}









