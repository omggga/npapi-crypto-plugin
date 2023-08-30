/*
 SlotAsn.h : ������� ASN/DER.

 $Name:  $
 $Revision: 1.1.2.4 $
 $Date: 2009/05/26 08:33:47 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

// 
//
//#include <precompile/_security_.h>
//// #include <low-level/SmartRegex.h>
#include "../alg/Alg_1_8_4.h"
#include "SlotUtil.h"

namespace  {



	struct NameDescription;



	// =======================================================================================
	// X.500 attributes

	struct X500
	{
		typedef Map<string,string> OidMap;

		static OidMap& m_Oids() 
		{
			static OidMap s_Oids;
			return s_Oids;
		}

		static OidMap& Oids()
		{
			OidMap& Oids = m_Oids();
			//
			if (Oids.GetSize() == 0) 
			{
				Fill();
			}
			return Oids;
		}

		string sCommonNameOid;
		string sCountryNameOid;
		string sLocalityNameOid;
		string sStateOrProvinceNameOid;
		string sOrganizationNameOid;
		string sOrganizationalUnitNameOid;
		string sTitleOid;
		string sEmailOid;

		string sINN;
		string sOGRN;
		string sSNILS;

		string sSubjectSignTool;
		string sIssuerSignTool;

		string sPolicyKC1; 
		string sPolicyKC2; 

#		define S_INN L"1.2.643.3.131.1.1"
#		define S_OGRN L"1.2.643.100.1"
#		define S_SNILS L"1.2.643.100.3"

		X500()
		{
			sCommonNameOid						= L"2.5.4.3";
			sCountryNameOid						= L"2.5.4.6";
			sLocalityNameOid					= L"2.5.4.7";
			sStateOrProvinceNameOid				= L"2.5.4.8";
			sOrganizationNameOid				= L"2.5.4.10";
			sOrganizationalUnitNameOid			= L"2.5.4.11";
			sTitleOid							= L"2.5.4.12";
			sEmailOid							= L"1.2.840.113549.1.9.1";
			//
			sINN = S_INN;
			sOGRN = S_OGRN;
			sSNILS = S_SNILS;
			//
			sSubjectSignTool = L"1.2.643.100.111";
			sIssuerSignTool = L"1.2.643.100.112";
			//
			sPolicyKC1 = L"1.2.643.100.113.1"; 
			sPolicyKC2 = L"1.2.643.100.113.2"; 
		}	  
		
		static void Fill()
		{
			// ----
			// X.520
			//
			m_Oids()[L"CommonName"]					= L"2.5.4.3";
			m_Oids()[L"SurName"]					= L"2.5.4.4";
			m_Oids()[L"DeviceSerialNumber"]			= L"2.5.4.5";
			//
			m_Oids()[L"CountryName"]				= L"2.5.4.6";
			m_Oids()[L"LocalityName"]				= L"2.5.4.7";
			m_Oids()[L"StateOrProvinceName"]		= L"2.5.4.8";
			m_Oids()[L"StreetAddress"]				= L"2.5.4.9";
			//
			m_Oids()[L"OrganizationName"]			= L"2.5.4.10";
			m_Oids()[L"OrganizationalUnitName"]		= L"2.5.4.11";
			m_Oids()[L"Title"]						= L"2.5.4.12";
			//
			m_Oids()[L"Description"]				= L"2.5.4.13";
			m_Oids()[L"SearchGuide"]				= L"2.5.4.14";
			m_Oids()[L"BusinessCategory"]			= L"2.5.4.15";
			//
			m_Oids()[L"PostalAddress"]				= L"2.5.4.16";
			m_Oids()[L"PostalCode"]					= L"2.5.4.17";
			m_Oids()[L"PostOfficeBox"]				= L"2.5.4.18";
			m_Oids()[L"PhysicalDeliveryOfficeName"]	= L"2.5.4.19";
			//
			m_Oids()[L"TelephoneNumber"]			= L"2.5.4.20";
			m_Oids()[L"TelexNumber"]				= L"2.5.4.21";
			m_Oids()[L"TeletextTerminalIdentifier"]	= L"2.5.4.22";
			m_Oids()[L"FacsimileTelephoneNumber"]	= L"2.5.4.23";
			m_Oids()[L"X21Address"]					= L"2.5.4.24";
			m_Oids()[L"InternationalISDNNumber"]	= L"2.5.4.25";
			m_Oids()[L"RegisteredAddress"]			= L"2.5.4.26";
			m_Oids()[L"DestinationIndicator"]		= L"2.5.4.27";
			//
			m_Oids()[L"PreferedDeliveryMethod"]		= L"2.5.4.28";
			//
			m_Oids()[L"PresentationAddress"]		= L"2.5.4.29";
			m_Oids()[L"SupportedApplicationContext"]= L"2.5.4.30";
			//
			m_Oids()[L"Member"]						= L"2.5.4.31";
			m_Oids()[L"Owner"]						= L"2.5.4.32";
			m_Oids()[L"RoleOccupant"]				= L"2.5.4.33";
			m_Oids()[L"SeeAlso"]					= L"2.5.4.34";
			//
			m_Oids()[L"UserPassword"]				= L"2.5.4.35";
			m_Oids()[L"UserCertificate"]			= L"2.5.4.36";
			m_Oids()[L"CACertificate"]				= L"2.5.4.37";
			m_Oids()[L"AuthorityRevocationList"]	= L"2.5.4.38";
			m_Oids()[L"CertificateRevocationList"]	= L"2.5.4.39";
			m_Oids()[L"CrossCertificatePair"]		= L"2.5.4.40";
			//
			m_Oids()[L"ATName"]						= L"2.5.4.41";
			//
			m_Oids()[L"GivenName"]					= L"2.5.4.42";
			m_Oids()[L"Initials"]					= L"2.5.4.43";
			//
			//
			//
			// ----
			// RSA
			// 
			m_Oids()[L"RSA"]						= L"1.2.840.113549";
			m_Oids()[L"PKCS"]						= L"1.2.840.113549.1";
			m_Oids()[L"RSAHash"]					= L"1.2.840.113549.2";
			m_Oids()[L"RSAEncrypt"]					= L"1.2.840.113549.3";
			//
			m_Oids()[L"PKCS1"]						= L"1.2.840.113549.1.1";
			m_Oids()[L"PKCS2"]						= L"1.2.840.113549.1.2";
			m_Oids()[L"PKCS3"]						= L"1.2.840.113549.1.3";
			m_Oids()[L"PKCS4"]						= L"1.2.840.113549.1.4";
			m_Oids()[L"PKCS5"]						= L"1.2.840.113549.1.5";
			m_Oids()[L"PKCS6"]						= L"1.2.840.113549.1.6";
			m_Oids()[L"PKCS7"]						= L"1.2.840.113549.1.7";
			m_Oids()[L"PKCS8"]						= L"1.2.840.113549.1.8";
			m_Oids()[L"PKCS9"]						= L"1.2.840.113549.1.9";
			m_Oids()[L"PKCS10"]						= L"1.2.840.113549.1.10";
			m_Oids()[L"PKCS11"]						= L"1.2.840.113549.1.11";
			m_Oids()[L"PKCS12"]						= L"1.2.840.113549.1.12";
			//
			m_Oids()[L"RSA_RSA"]					= L"1.2.840.113549.1.1.1";
			m_Oids()[L"RSA_MD2RSA"]					= L"1.2.840.113549.1.1.2";
			m_Oids()[L"RSA_MD4RSA"]					= L"1.2.840.113549.1.1.3";
			m_Oids()[L"RSA_MD5RSA"]					= L"1.2.840.113549.1.1.4";
			m_Oids()[L"RSA_SHA1RSA"]				= L"1.2.840.113549.1.1.5";
			m_Oids()[L"RSA_SETOAEP_RSA"]			= L"1.2.840.113549.1.1.6";
			//
			m_Oids()[L"RSA_DH"]						= L"1.2.840.113549.1.3.1";
			//
			m_Oids()[L"RSA_data"]					= L"1.2.840.113549.1.7.1";
			m_Oids()[L"RSA_signedData"]				= L"1.2.840.113549.1.7.2";
			m_Oids()[L"RSA_enveloppedData"]			= L"1.2.840.113549.1.7.3";
			m_Oids()[L"RSA_signEnvData"]			= L"1.2.840.113549.1.7.4";
			m_Oids()[L"RSA_digestedData"]			= L"1.2.840.113549.1.7.5";
			m_Oids()[L"RSA_hashedData"]				= L"1.2.840.113549.1.7.6";
			m_Oids()[L"RSA_encryptedData"]			= L"1.2.840.113549.1.7.7";
			//
			m_Oids()[L"Email"] 						= L"1.2.840.113549.1.9.1";
			//m_Oids()[L"RSA_emailAddr"]				= L"1.2.840.113549.1.9.1";
			m_Oids()[L"RSA_unstructName"]			= L"1.2.840.113549.1.9.2";
			m_Oids()[L"RSA_contentType"]			= L"1.2.840.113549.1.9.3";
			m_Oids()[L"RSA_messageDigest"]			= L"1.2.840.113549.1.9.4";
			m_Oids()[L"RSA_signingTime"]			= L"1.2.840.113549.1.9.5";
			m_Oids()[L"RSA_counterSign"]			= L"1.2.840.113549.1.9.6";
			m_Oids()[L"RSA_challengePwd"]			= L"1.2.840.113549.1.9.7";
			m_Oids()[L"RSA_unstructAddr"]			= L"1.2.840.113549.1.9.8";
			m_Oids()[L"RSA_extCertAttrs"]			= L"1.2.840.113549.1.9.9";
			m_Oids()[L"RSA_certExtensions"]			= L"1.2.840.113549.1.9.14";
			m_Oids()[L"RSA_SMIMECapabilities"]		= L"1.2.840.113549.1.9.15";
			m_Oids()[L"RSA_preferSignedData"]		= L"1.2.840.113549.1.9.15.1";
			//
			m_Oids()[L"RSA_MD2"]					= L"1.2.840.113549.2.2";
			m_Oids()[L"RSA_MD4"]					= L"1.2.840.113549.2.3";
			m_Oids()[L"RSA_MD5"]					= L"1.2.840.113549.2.4";
			//
			m_Oids()[L"RSA_RC2CBC"]					= L"1.2.840.113549.3.2";
			m_Oids()[L"RSA_RC4"]					= L"1.2.840.113549.3.4";
			m_Oids()[L"RSA_DES_EDE3_CBC"]			= L"1.2.840.113549.3.7";
			m_Oids()[L"RSA_RC5_CBCPad"]				= L"1.2.840.113549.3.9";
			//
			//
			//
			// ----
			// 
			// 
			m_Oids()[L"GOV_PKI_���"]				= S_INN; 
			m_Oids()[L"GOV_PKI_����"]				= S_OGRN; 
			m_Oids()[L"GOV_PKI_�����"]				= S_SNILS;   
			//
			m_Oids()[L""]						= L"1.2.643.6.2";
			m_Oids()[L"_PKI"]					= L"1.2.643.6.2.1";
			m_Oids()[L"_PKI_��������"]			= L"1.2.643.6.2.1.6";
			//
			m_Oids()[L"_PKI_��������_�"]		= L"1.2.643.6.2.1.6.1";
			m_Oids()[L"_PKI_��������������"]	= L"1.2.643.6.2.1.6.1.1";
			m_Oids()[L"_PKI_�����_������������"]= L"1.2.643.6.2.1.6.1.20.1";
			m_Oids()[L"_PKI_�����_�����������"]	= L"1.2.643.6.2.1.6.1.20.2";
			m_Oids()[L"_PKI_�����_�����������"]	= L"1.2.643.6.2.1.6.1.20.3";
			m_Oids()[L"_PKI_�����_��������"]	= L"1.2.643.6.2.1.6.1.20.4";
			m_Oids()[L"_PKI_�����_����������"]	= L"1.2.643.6.2.1.6.1.20.5";
			m_Oids()[L"_PKI_��_���"]			= L"1.2.643.6.2.1.6.1.50.1";
			m_Oids()[L"_PKI_��_����"]			= L"1.2.643.6.2.1.6.1.50.2";
			m_Oids()[L"_PKI_�����_������"]		= L"1.2.643.6.2.1.6.1.100.1";
			m_Oids()[L"_PKI_�����_��"]			= L"1.2.643.6.2.1.6.1.100.2";
			m_Oids()[L"_PKI_�����_�����"]		= L"1.2.643.6.2.1.6.1.100.3";
			m_Oids()[L"_PKI_�����_�����"]		= L"1.2.643.6.2.1.6.1.100.4";
			m_Oids()[L"_PKI_�����_��"]			= L"1.2.643.6.2.1.6.1.100.5";
			m_Oids()[L"_PKI_�����_�����"]		= L"1.2.643.6.2.1.6.1.100.6";
			m_Oids()[L"_PKI_�����_���"]			= L"1.2.643.6.2.1.6.1.100.7";
			m_Oids()[L"_PKI_�����_������"]		= L"1.2.643.6.2.1.6.1.100.8";
			m_Oids()[L"_PKI_�����_����"]		= L"1.2.643.6.2.1.6.1.100.9";
			//
			m_Oids()[L"_PKI_���������_������"]	= L"1.2.643.6.2.1.6.1.101.1";
			m_Oids()[L"_PKI_���������_��"]		= L"1.2.643.6.2.1.6.1.101.2";
			m_Oids()[L"_PKI_���������_�����"]	= L"1.2.643.6.2.1.6.1.101.3";
			m_Oids()[L"_PKI_���������_�����"]	= L"1.2.643.6.2.1.6.1.101.4";
			m_Oids()[L"_PKI_���������_��"]		= L"1.2.643.6.2.1.6.1.101.5";
			m_Oids()[L"_PKI_���������_�����"]	= L"1.2.643.6.2.1.6.1.101.6";
			m_Oids()[L"_PKI_���������_���"]		= L"1.2.643.6.2.1.6.1.101.7";
			m_Oids()[L"_PKI_���������_������"]	= L"1.2.643.6.2.1.6.1.101.8";
			m_Oids()[L"_PKI_���������_����"]	= L"1.2.643.6.2.1.6.1.101.9";
			//
			m_Oids()[L"_PKI_��������_�"]		= L"1.2.643.6.2.1.6.2";
			m_Oids()[L"_PKI_�������"]			= L"1.2.643.6.2.1.6.2.1";
			m_Oids()[L"_PKI_���"]				= L"1.2.643.6.2.1.6.2.2";
			m_Oids()[L"_PKI_��������"]			= L"1.2.643.6.2.1.6.2.3";
			m_Oids()[L"_PKI_������������"]		= L"1.2.643.6.2.1.6.2.4";
			m_Oids()[L"_PKI_�����������"]		= L"1.2.643.6.2.1.6.2.5";
			m_Oids()[L"_PKI_�����_������������"]= L"1.2.643.6.2.1.6.2.20.1";
			m_Oids()[L"_PKI_�����_�����������"]	= L"1.2.643.6.2.1.6.2.20.2";
			m_Oids()[L"_PKI_�����_�����������"]	= L"1.2.643.6.2.1.6.2.20.3";
			m_Oids()[L"_PKI_�����_��������"]	= L"1.2.643.6.2.1.6.2.20.4";
			m_Oids()[L"_PKI_�����_����������"]	= L"1.2.643.6.2.1.6.2.20.5";
			m_Oids()[L"_PKI_��_���"]			= L"1.2.643.6.2.1.6.2.50.1";
			m_Oids()[L"_PKI_�����"]				= L"1.2.643.6.2.1.6.2.50.81";
			m_Oids()[L"_PKI_�����_������"]		= L"1.2.643.6.2.1.6.2.100.1";
			m_Oids()[L"_PKI_�����_��"]			= L"1.2.643.6.2.1.6.2.100.2";
			m_Oids()[L"_PKI_�����_�����"]		= L"1.2.643.6.2.1.6.2.100.3";
			m_Oids()[L"_PKI_�����_�����"]		= L"1.2.643.6.2.1.6.2.100.4";
			m_Oids()[L"_PKI_�����_��"]			= L"1.2.643.6.2.1.6.2.100.5";
			m_Oids()[L"_PKI_�����_�����"]		= L"1.2.643.6.2.1.6.2.100.6";
			m_Oids()[L"_PKI_�����_���"]			= L"1.2.643.6.2.1.6.2.100.7";
			m_Oids()[L"_PKI_�����_������"]		= L"1.2.643.6.2.1.6.2.100.8";
			m_Oids()[L"_PKI_�����_��������"]	= L"1.2.643.6.2.1.6.2.100.9";
			//
			m_Oids()[L"_PKI_�������"]			= L"1.2.643.6.2.1.6.1.199.2";
			//
			m_Oids()[L"_PKI_��������"]			= L"1.2.643.6.2.1.7";
			m_Oids()[L"_PKI_��������_�"]		= L"1.2.643.6.2.1.7.1";
			m_Oids()[L"_PKI_��������_�"]		= L"1.2.643.6.2.1.7.2";
		}

		static string GetOID(string name)
		{
			return (string)Oids()[name];
		}

		static string GetName(string oid)
		{
			for (OidMap::Iterator i(Oids()); i; ++i)
			{
				if (string(i) == oid) return i.Id();
			}
			return string();
		}

		static string GetOIDName(string oid)
		{
			if (Oids().ContainsValue(oid))
			{
				return GetName(oid);
			}
			else
			{
				return L"OID." + (string)oid;
			}
		}

		static string GetExplainedOID(string oid)
		{
			if (Oids().ContainsValue(oid))
			{
				return string(oid)+L" ("+GetName(oid)+L")";
			}
			else
			{
				return oid;
			}
		}
	};

		
		
	// =======================================================================================
	// OID 

	struct OID 
	{
		SharedArray<int> m_values;

		inline void LoadText(string oidStr)
		{
			string s2 = oidStr;
			s2.MakeLower();
			if (s2.Left(4) == L"oid.")
			{
			}
			else if ( s2.Find(L".") == -1 ) // (! Match(_T("^\\d.*$"),CString(s2)))
			{
				oidStr = X500::GetOID(oidStr);
			}
			//
			int values[64];
			int i = 0;
			//
			string r = oidStr;
			int p1 = r.Find(L".");
			while (p1 != -1)
			{
				string s = r.Left(p1);
				int v = _wtoi(s);
				values[i] = v;
				++i;
				r = r.Right(r.GetLength()-p1-1); // (p1+1,r.GetLength()-p1-1)
				p1 = r.Find(L".");
			}
			int v2 = _wtoi(r);
			values[i] = v2;
			++i;
			//
			m_values.Allocate(i);
			for (i = 0; i < m_values.GetSize(); ++i) m_values[i] = values[i];
		}

		OID(string oidStr)
		{
			LoadText(oidStr);
		}

		OID(SharedArray<int> values)
		{
			m_values.Allocate(values.GetSize());
			for (int i = 0; i < m_values.GetSize(); ++i) m_values[i] = values[i];
		}

		OID(SharedArray<int> values,int n)
		{
			m_values.Allocate(n);
			for (int i = 0; i < m_values.GetSize(); ++i) m_values[i] = values[i];
		}

		const OID& operator =(const OID& other)
		{
			m_values.Allocate(other.m_values.GetSize());
			for (int k = 0; k < m_values.GetSize(); ++k)
			{
				m_values[k] = other.m_values[k];
			}
			return other;
		}

		OID(const OID& other)
		{
			operator =(other);
		}

		OID(wchar_t* oidStr)
		{
			LoadText(string(oidStr));
		}

		//object Clone()
		//{
		//	OID newOid = OID.Null;
		//	newOid.m_values = new int[m_values.Length];
		//	for (int k = 0; k < m_values.Length; ++k) newOid.m_values[k] = m_values[k];
		//	return newOid;
		//}

		int operator[](int i)
		{
			return m_values[i];
		}

		int Length() const 
		{
			if (m_values.GetSize() == 0) return 0;
			return m_values.GetSize();
		}

		operator string()
		{
			string oidStr = L"";
			for (int i = 0; i < m_values.GetSize(); ++i)
			{
				if (i > 0) oidStr += L".";
				CStringW item = FormatStr(L"%d", (int)m_values[i] );
				oidStr += item;
			}
			return oidStr;
		}

		OID() // Null
		{
		}

		static OID Null()
		{
			return OID();
		}

		bool IsNull() const 
		{
			return m_values.GetSize() == 0;
		}

		// ���������

		bool operator ==(const OID& rhs) const 
		{
			const OID& lhs = *this;
			//
			if (lhs.IsNull() || rhs.IsNull()) return lhs.IsNull() && rhs.IsNull();
			//
			int l = lhs.Length();
			if (rhs.Length() < l) l = rhs.Length();
			for (int k = 0; k < l; ++k)
			{
				if (lhs.m_values[k] != rhs.m_values[k]) return false;
			}
			return (lhs.Length() == rhs.Length());
		}

		//static bool operator !=(const OID& lhs,const OID& rhs)
		//{
		//	return ! (lhs == rhs);
		//}

		bool operator ==(const string& rhsStr) const
		{
			const OID& lhs = *this;
			//
			if (lhs.IsNull()) return false;
			//
			return lhs == OID(rhsStr);
		}

		//static bool operator !=(const OID& lhs,const string& rhsStr)
		//{
		//	return ! (lhs == rhsStr);
		//}

		// * VS 2003
		//static bool operator ==(const string& lhsStr,const OID& rhs)
		//{
		//	if (rhs.IsNull()) return false;
		//	//
		//	return OID(lhsStr) == rhs;
		//}

		// * VS 
		//////bool operator ==(const string& rhsStr)
		//////{
		//////	if (IsNull()) return false;
		//////	//
		//////	return OID(lhsStr) == rhs;
		//////}

		//static bool operator !=(const string& lhsStr,const OID& rhs)
		//{
		//	return ! (lhsStr == rhs);
		//}

		//bool Equals(object rhs)
		//{ 
		//	if (rhs == null) return IsNull;
		//	return this == rhs.ToString();
		//}

		// ��������

		Blob Encoded(int level=1)
		{
			if (m_values.GetSize() == 0) return Blob();
			//
			Blob data;
			data.Allocate(256);
			int j = 1;
			if (m_values.GetSize() == 1) data[0] = (BYTE)( 40*m_values[0] );
			else
			{
				data[0] = (BYTE)( 40*m_values[0] + m_values[1] );
				for (int k = 2; k < m_values.GetSize(); ++k)
				{
					int v = m_values[k];
					//
					Blob r;
					r.Allocate(32);
					//
					int n = 0;
					while (v >= 128)
					{
						r[n] = (BYTE)( v - 128*(int)(v/128) );
						++n;
						v = (int)(v/128);
					}
					r[n] = (BYTE)( v );
					++n;
					//
					for (int q = 0; q < n; ++q)
					{
						if (q < n-1) data[j] = (BYTE)( 0x80 | r[n-1-q] );
						else data[j] = r[n-1-q];
						++j;
					}
				}
			}
			//
			int n2 = j;
			Blob result;
			result.Allocate(n2);
			for (j = 0; j < n2; ++j) result[j] = data[j];
			return result;
		}
	};



	struct AsnObject
	{
		static const int UNIVERSAL = 0;
		static const int APPLICATION = 1;
		static const int CONTEXT_SPECIFIC = 2;
		static const int PRIVATE = 3;

		static const int BOOLEAN = 1;
		static const int INTEGER = 2;
		static const int BIT_STRING = 3;
		static const int OCTET_STRING = 4;
		static const int _NULL_ = 5;
		static const int OBJECT_IDENTIFIER = 6;
		static const int UTF8String = 12;
		static const int SEQUENCE = 16;
		static const int SET = 17;
		static const int NumericString = 18;
		static const int PrintableString = 19;
		static const int T61String = 20;
		static const int IA5String = 22;
		static const int UTCTime = 23;
		static const int BMPString = 30;

		static const int DefaultStringType = UTF8String;

		Blob m_Encoded;

		int m_AsnClass;
		bool m_IsConstructed;
		int m_ContentLength;
		int m_Length;
		int m_Tag;
		int m_ExtendedTag;

		OID m_Oid;
		int m_Integer;
		COleDateTime m_Time;
		string m_text;

		// int m_Size;
		Blob m_Data;
		int m_UnusedBits;

		static bool& fKeepDeep() 
		{
			static bool s_fKeepDeep;
			return s_fKeepDeep; 
		}

		// ������������� �����-���������

		struct Smart
		{
			SharedPtr<AsnObject> m_this;

			Smart(AsnObject& parent) 
			{
				m_this = SharedPtr<AsnObject>(&parent);
			}

			~Smart()
			{
				m_this.Clear();
			}
		};

		Smart m_smart;

		SharedPtr<AsnObject> GetSmart()
		{
			return SharedPtr<AsnObject>(m_smart.m_this);
		}

		// ������� ��������

		struct P_Children
		{
			struct P_Child
			{
				P_Children& m_children;

				int m_index;

				P_Child(P_Children& children,int i) : m_children(children), m_index(i)
				{
				}

				// Null value 
				P_Child(P_Children& children) : m_children(children), m_index(-1)
				{
				}

				bool IsNull() const
				{
					return m_index == -1; 
				}

				operator AsnObject&()
				{
					if (m_index == -1) 
						throw MethodError(L"ASN Error: We have Null value");
					//
					return m_children.GetChild(m_index);
				}

				AsnObject& operator =(AsnObject& other) 
				{
					if (m_index == -1) 
						throw MethodError(L"ASN Error: Cannot assign to Null value");
					//
					m_children.SetChild(m_index,other);
					return other;
				}

				P_Child& operator =(P_Child& other) 
				{
					operator =((AsnObject&)other);
					return other;
				}
			};

			AsnObject& m_parent;

			SharedArray<SharedPtr<AsnObject> > m_Children;

			P_Children(AsnObject& parent) : m_parent(parent)
			{
			}

			void RemoveItem(int i)
			{
				SharedArray<SharedPtr<AsnObject> > a;
				for (int j = 0; j < i; j++) a.Add(m_Children[j]);
				for (int j = i+1; j < m_Children.Length(); j++) a.Add(m_Children[j]);
				m_Children = a; 
			}

			P_Child operator [](int i)
			{
				return P_Child(*this,i);
			}

			P_Child operator [](OID oid)
			{
				for (int i = 0; i < m_Children.GetSize(); ++i)
				{
					AsnObject& child = GetChild(i);
					OID id = child.ObjectId();
					if (! id.IsNull())
					{
						if (id == oid)
						{
							return P_Child(*this,i);
						}
					}
				}
				return P_Child(*this); // Null 
			}

			P_Child Tagged(int tag)
			{
				for (int i = 0; i < m_Children.GetSize(); ++i)
				{
					AsnObject& child = GetChild(i);
					if (child.m_Tag == tag)
					{
						return P_Child(*this,i);
					}
				}
				return P_Child(*this); // Null 
			}

			P_Child GetOctetString()
			{
				for (int i = 0; i < m_Children.GetSize(); ++i)
				{
					AsnObject& child = GetChild(i);
					if (child.Tag() == OCTET_STRING) return P_Child(*this,i);
				}
				return P_Child(*this); // Null 
			}

			AsnObject& GetChild(int i)
			{
				if ((i < 0) || (i >= m_Children.GetSize())) 
					throw MethodError(HRESULT_FROM_WIN32(ERROR_NOT_FOUND));
				//
				return *( m_Children[i].GetPointee() ); 
			}

			void SetChild(int i,AsnObject& value)
			{
				m_Children[i] = new AsnObject(value);
			}

			P_Children& Free()
			{
				m_Children.Free();
				//
				return *this;
			}

			const P_Children& operator =(const P_Children& other)
			{
				Free();
				// 
				m_Children.Allocate(other.m_Children.GetSize());
				for (int k = 0; k < other.m_Children.GetSize(); ++k)
				{
					m_Children[k] = other.m_Children[k];
				}
				//
				return other;
			}

			int Length() const 
			{
				return m_Children.GetSize();
			}
		}; 

		P_Children Children;

		P_Children::P_Child operator [](int i)
		{
			return Children[i];
		}

		void RemoveItem(int i)
		{
			Children.RemoveItem(i); 
		}



		struct P_Deep
		{
			AsnObject& m_parent;

			SharedPtr<AsnObject> m_pDeep;

			P_Deep(AsnObject& parent) : m_parent(parent)
			{
			}

			operator AsnObject&()
			{
				//if (m_pDeep.IsEmpty()) m_pDeep = new AsnObject();
				//	throw MethodError(_T("ASN Error: Deep is Null"));
				//
				return *( m_pDeep.GetPointee() ); 
			}

			const AsnObject& operator =(const AsnObject& other)
			{
				m_pDeep = new AsnObject(other);
				return other;
			}

			const P_Deep& operator =(const P_Deep& other)
			{
				m_pDeep = other.m_pDeep;
				return other;
			}

			bool IsNull()
			{
				return m_pDeep.IsEmpty();
			}
		};

		P_Deep Deep;

		const AsnObject& operator =(const AsnObject& other)
		{
			m_smart.m_this.Clear();
			m_smart.m_this = other.m_smart.m_this;
			//
			m_Encoded = other.m_Encoded;
			m_AsnClass = other.m_AsnClass;
			m_IsConstructed = other.m_IsConstructed;
			m_ContentLength = other.m_ContentLength;
			m_Length = other.m_Length;
			m_Tag = other.m_Tag;
			m_ExtendedTag = other.m_ExtendedTag;
			Children = other.Children;
			m_Oid = other.m_Oid;
			m_Integer = other.m_Integer;
			m_Time = other.m_Time;
			m_text = other.m_text;
			m_Data = other.m_Data;
			m_UnusedBits = other.m_UnusedBits;
			Deep = other.Deep;
			//
			return other;
		}

#		define MOUNT_PROPERTIES() \
			m_smart(*this), \
			m_IndefiniteLength(false), \
			m_AsnClass(0), \
			m_IsConstructed(false), \
			m_ContentLength(0), \
			m_Length(0), \
			m_Tag(0), \
			m_ExtendedTag(0), \
			m_Integer(0), \
			Children(*this), \
			CP_GOST2001PublicKeyBits(*this), \
			CP_GOST2001PublicKeyOctets(*this), \
			Deep(*this), \
			PublicKey(*this), \
			PublicKeyAlgorithm(*this), \
			CertificateExtensionObject(*this), \
			SubjectAltNameObject(*this), \
			SubjectObject(*this), \
			Subject(*this), \
			SubjectAltName(*this)

		AsnObject(const AsnObject& other) : MOUNT_PROPERTIES()
		{
			operator =(other);
		}

		AsnObject(bool isConstructed,int asnClass,int tag) : MOUNT_PROPERTIES() 
		{
			// m_Encoded = null;
			m_ContentLength = m_Length = m_ExtendedTag = m_Integer = m_UnusedBits = 0;
			m_IndefiniteLength = false;
			//
			m_IsConstructed = isConstructed;
			m_AsnClass = asnClass;
			m_Tag = tag;
		}

		AsnObject(int v) : MOUNT_PROPERTIES() 
		{
			m_AsnClass = UNIVERSAL;
			m_IsConstructed = false;
			m_Tag = INTEGER;
			m_Integer = v;
			m_IndefiniteLength = false;
		}

		inline static AsnObject NewInteger(int v)
		{
			AsnObject o(false, UNIVERSAL, INTEGER); 
			o.m_Integer = v;
			o.m_IndefiniteLength = false;
			return o;
		}

		AsnObject(Blob data) : MOUNT_PROPERTIES() 
		{
			Parse(data);
		}

		AsnObject(Blob data,int start,OID objectId) : MOUNT_PROPERTIES() 
		{
			Parse(data,start,objectId);
		}

		AsnObject(Blob data,int start) : MOUNT_PROPERTIES() 
		{
			Parse(data,start);
		}

		AsnObject Parse(Blob data) 
		{
			return Parse(data,0);
		}

		AsnObject Parse(Blob data,int start)
		{
			return Parse(data,start,OID::Null());
		}

		AsnObject Parse(Blob data,int start,OID objectId)
		{
			int j;
			//
			// m_Encoded = null;
			//
			m_AsnClass = (int)((data[start] & 0xC0) >> 6);
			m_IsConstructed = ((data[start] & 0x20) != 0);
			m_Tag = (int)(data[start] & 0x1F);
			m_ExtendedTag = -1;
			m_IndefiniteLength = false;
			//
			int cntStart;
			int stop = 0;
			//
			cntStart = start+2;
			//
			if (data[start+1] == 0x80)
			{
				cntStart = start+2;
				m_IndefiniteLength = true; 
				//
				m_Length = 0;
			}
			else
			{
				bool shortLength = ((data[start+1] & 0x80) == 0);
				if (shortLength)
				{
					m_ContentLength = (int)(data[start+1] & 0x7F);
					cntStart = start+2;
				}
				else
				{
					int lenBytes = (int)(data[start+1] & 0x7F);
					m_ContentLength = 0;
					for (j = 0; j < lenBytes; ++j) 
						m_ContentLength = 256*m_ContentLength + (int)data[start+2+j];
					cntStart = start+2+lenBytes;
				}
				stop = cntStart + m_ContentLength;
				//
				m_Length = stop - start;
			}
			//
			//Runtime.Echo("Parsing "+m_Tag.ToString()+": "+m_Length.ToString()+", "
			//	+start.ToString()+":"+cntStart.ToString()+" -> "+stop.ToString()
			//	+"   (content length "+m_ContentLength.ToString()+")");
			//
			if (m_IsConstructed)
			{
				bool parseAsSequence = false;
				//
				if (m_AsnClass == UNIVERSAL)
				{
					if (m_Tag == 0 || m_Tag == SEQUENCE || m_Tag == SET) 
					{
						parseAsSequence = true;
					}
					else if (m_Tag == BIT_STRING)
					{
						ReadBitString(data,cntStart,m_ContentLength,&m_Data,&m_UnusedBits);
					}
					else
					{
						string msg = FormatStr(L"ASN Parse Error: Unknown tag %d", (int)m_Tag ); 
						throw MethodError(msg); 
					}
				}
				else
				{
					m_Data.Allocate(m_ContentLength);
					for (j = 0; j < m_ContentLength; ++j) m_Data[j] = data[cntStart+j];
					//
					parseAsSequence = true;
				}
				//
				if (parseAsSequence)
				{
					int childStart = cntStart;
					OID prevOid = OID::Null();
					//
					if (m_IndefiniteLength)
					{
						bool fContinue = !((data[childStart] == 0) && (data[childStart+1] == 0)); 
						//
						while (fContinue) 
						{
							AsnObject child(data,childStart,prevOid);
							Add(child);
							if (child.Tag() == OBJECT_IDENTIFIER) prevOid = child.Oid();
							//
							int dL = child.Length(); 
							childStart += dL;
							//
							fContinue = !((data[childStart] == 0) && (data[childStart+1] == 0)); 
						}
						//
						stop = childStart+2;
						m_Length = stop - start; 
					}
					else
					{
						while (childStart < stop)
						{
							AsnObject child(data,childStart,prevOid);
							Add(child);
							if (child.Tag() == OBJECT_IDENTIFIER) prevOid = child.Oid();
							childStart += child.Length();
						}					
					}
				}
			}
			else
			{
				bool parseAsSequence = false;
				//
				if (m_AsnClass == UNIVERSAL)
				{
					if (m_Tag == OBJECT_IDENTIFIER)
					{
						int start2 = cntStart;
						SharedArray<int> oid; oid.Allocate(64);
						int i = 0;
						while (start2 < stop)
						{
							int v = ReadInteger128(data,&start2);
							if (i == 0)
							{
								int v1 = v/40;
								int v2 = v-40*v1;
								oid[i] = v1;
								++i;
								oid[i] = v2;
								++i;
							}
							else
							{
								oid[i] = v;
								++i;
							}
						}
						m_Oid = OID(oid,i);
					}
					else if (m_Tag == OCTET_STRING)
					{
						m_Data.Allocate(m_ContentLength);
						for (j = 0; j < m_ContentLength; ++j) m_Data[j] = data[cntStart+j];
						m_UnusedBits = 0;
						//
						// Going deep...
						//
						if (! objectId.IsNull())
						{
							if (objectId == (string)L"2.5.29.7" || objectId == (string)L"2.5.29.17" 
								// Subject Alternative Name
								|| objectId == (string)L"2.5.29.15"
								|| objectId == (string)L"1.2.840.113549.1.9.15"
								|| objectId == (string)L"2.5.29.37"
								|| objectId == (string)L"2.5.29.32"
								|| objectId == (string)L"2.5.29.14"
								|| objectId == (string)L"2.5.29.31"
								|| objectId == (string)L"2.5.29.35"
								|| objectId == (string)L"1.2.643.100.111"
								|| objectId == (string)L"1.2.643.100.112"
								|| objectId == (string)L"1.3.6.1.5.5.7.1.1"
								)
							{
								if (objectId == (string)L"2.5.29.7" || objectId == (string)L"2.5.29.17")
								{
//										string path = "z:\\AltName-sample.der";
//										FileStream writer = File.Open(path,FileMode.Create,FileAccess.Write);
//										writer.Write(data,cntStart,m_ContentLength);
//										writer.Close();
								}
								string oid_s = objectId;
								//
								Deep = AsnObject(data,cntStart);
							}
						}
					}
					else if (m_Tag == BIT_STRING)
					{
						ReadBitString(data,cntStart,m_ContentLength,&m_Data,&m_UnusedBits);
					}
					else if (m_Tag == BOOLEAN)
					{
						m_Integer = ReadInteger(data,cntStart,m_ContentLength);
					}
					else if (m_Tag == INTEGER)
					{
						Blob intResult;
						intResult = ReadIntegerBlob(data,cntStart,m_ContentLength,&m_Integer);
						m_Data.Allocate(intResult.Length());
						for (j = 0; j < intResult.Length(); ++j) 
						{
							m_Data[intResult.Length() - 1 - j] = intResult[j];
						}
						//
#						ifdef _DEBUG
						//if (intResult.Length() == 10)
						//{
						//	int x = 1; 
						//}
#						endif
					}
					else if (m_Tag == UTCTime)
					{
						m_Time = ReadUTCTime(data,cntStart,m_ContentLength);
						m_Data.Allocate(m_ContentLength);
						for (j = 0; j < m_Data.Length(); ++j) m_Data[j] = data[cntStart + j];
					}
					else if (m_Tag == IA5String || m_Tag == PrintableString || m_Tag == NumericString)
					{
						m_text = ReadPrintableString(data,cntStart,m_ContentLength);
					}
					else if (m_Tag == BMPString)
					{
						m_text = ReadBMPString(data,cntStart,m_ContentLength);
						m_Data.Allocate(m_ContentLength);
						for (j = 0; j < m_Data.Length(); ++j) m_Data[j] = data[cntStart+j]; // !!!
					}
					else if (m_Tag == UTF8String)
					{
						m_text = ReadUTF8String(data,cntStart,m_ContentLength);
					}
					else if (m_Tag == _NULL_)
					{
					}
					else
					{
						string msg = FormatStr(L"ASN Parse Error: Unknown tag %d", (int)m_Tag ); 
						//throw MethodError(msg);
					}
				}
				else
				{
					if (m_Tag == 0)
					{
						m_ExtendedTag = m_Tag;
						Blob b;
						b.Allocate(m_ContentLength);
						CopyMemory(b.GetBuffer(), data.GetBuffer() + cntStart, m_ContentLength);
						m_text = Util::ASCIIToWideString(b);
						m_Data = b;
					}
					else if (m_Tag == 6)
					{
						m_ExtendedTag = m_Tag;
						Blob b;
						b.Allocate(m_ContentLength);
						CopyMemory(b.GetBuffer(),data.GetBuffer()+cntStart,m_ContentLength);
						m_text = Util::ASCIIToWideString(b);
						m_Data = b;
					}
					else if (m_Tag == 2)
					{
						m_ExtendedTag = m_Tag;
						Blob b;
						b.Allocate(m_ContentLength);
						CopyMemory(b.GetBuffer(),data.GetBuffer()+cntStart,m_ContentLength);
						m_text = Util::ASCIIToWideString(b);
						m_Data = b;
					}
					else 
					{
						string msg = FormatStr(L"ASN Parse Error: Unknown tag %d", (int)m_Tag ); 
						throw MethodError(msg);
					}
					//
					// ��������� ������
					//
					//m_Data.Allocate(m_ContentLength);
					//for (j = 0; j < m_ContentLength; ++j) m_Data[j] = data[cntStart+j];
				}
				//
				if (parseAsSequence)
				{
					int childStart = cntStart;
					OID prevOid = OID::Null();
					while (childStart < stop)
					{
						AsnObject child(data,childStart,prevOid);
						Add(child);
						if (child.Tag() == OBJECT_IDENTIFIER) prevOid = child.Oid();
						childStart += child.Length();
					}					
				}
			}
			//
			return *this;
		}

		Blob ReadIntegerBlob(Blob data,int start,int len,int* out_v)
		{
			Blob result;
			result.Allocate(len);
			//
			int v = 0;
			for (int j = start; j < start+len; ++j)
			{
				(result)[j-start] = data[j];
				//
				if (len <= 2)
				{
					v = 256*v + (int)data[j];
				}
			}
			//
			if (out_v) *out_v = v;
			return result;
		}

		int ReadInteger(Blob data,int start,int len)
		{			
			int v = 0; 
			Blob result = ReadIntegerBlob(data,start,len,&v);
			//
			return v;
		}

		int ReadInteger128(Blob data,int* start)
		{
			int v = 0;
			int j = *start;
			while ((data[j] & 0x80) != 0) 
			{
				v = 128*v + (int)(data[j] & 0x7F);
				++j;
			}
			v = 128*v + (int)data[j];
			//
			*start = j+1;
			return v;
		}

		void ReadBitString(Blob data,int start,int len,
			Blob* out_Data,int* out_UnusedBits)
		{
			*out_UnusedBits = data[start];
			int bitOctetsLen = len-1;
			out_Data->Allocate(bitOctetsLen);
			for (int j = 0; j < bitOctetsLen; ++j) (*out_Data)[bitOctetsLen-1-j] = data[start+1+j];
		}

		COleDateTime ReadUTCTime(Blob data,int cntStart,int len)
		{
			string text = Util::ASCIIToWideString(data.GetBuffer(),cntStart,len);
			//
			// Match m(_T("^\\d{10}Z"),CString(text));
			// (!) if (m.Matched())
			{
				int year = _wtoi(text.Left(2));
				if (year < 70) year = 2000 + year;
				//
				return COleDateTime(
					year
					,_wtoi(text.Left(4).Right(2)) // (text.Substring(2,2))
					,_wtoi(text.Left(6).Right(2)) // (text.Substring(4,2))
					,_wtoi(text.Left(8).Right(2)) // (text.Substring(6,2))
					,_wtoi(text.Left(10).Right(2)) // (text.Substring(8,2))
					,0
					// ,0 // milliseconds
					);
			}
			//
			// Match m2(_T("^\\d{12}Z"),CString(text));
			// (!) if (m2.Matched() || true)
			{
				int year = _wtoi(text.Left(2));
				if (year < 70) year = 2000 + year;
				//
				return COleDateTime(
					year
					,_wtoi(text.Left(4).Right(2)) // (text.Substring(2,2))
					,_wtoi(text.Left(6).Right(2)) // (text.Substring(4,2))
					,_wtoi(text.Left(8).Right(2)) // (text.Substring(6,2))
					,_wtoi(text.Left(10).Right(2)) // (text.Substring(8,2))
					,_wtoi(text.Left(12).Right(2)) // (text.Substring(10,2))
					// ,0 // milliseconds
					);
			}
			//
			throw MethodError(L"ASN Parse Error: Unknown UTCTime format");
		}

	public:
		inline static string ReadBMPString(Blob data,int start,int len)
		{
			string text = L"";
			for (int j = 0; j < len/2; ++j) 
			{
				int code = 256*(int)data[start+2*j] + data[start+2*j+1];
				text += string((wchar_t)code,1);
			}
			return text;
		}

		inline static string ReadUTF8String(Blob data,int cntStart,int len)
		{
			Blob buf;
			buf.Allocate(len);
			CopyMemory(buf.GetBuffer(),data.GetBuffer()+cntStart,len);			
			string text = Util::UTF8ToWideString(buf);
			return text;
		}

		string ReadPrintableString(Blob data,int cntStart,int len)
		{
			string text = Util::ASCIIToWideString(data.GetBuffer(),cntStart,len);
			return text;
		}

		Blob KeyIdentifier()
		{
			if (AsnClass() == UNIVERSAL)
			{
				if (Tag() == OCTET_STRING) 
				{
					return m_Data;
				}
				else if (! Deep.IsNull()) 
				{
					AsnObject& deepO = Deep; 
					//
					if (! (deepO.AsnClass() == UNIVERSAL)) 
						throw MethodError(L"������ ��������� ��� ���������� KeyIdentifier (2)"); 
					//
					if (! (deepO.Tag() == SEQUENCE)) 
						throw MethodError(L"������ ��������� ��� ���������� KeyIdentifier (3)"); 
					//
					if (ChildCount() < 3) 
						throw MethodError(L"������ ��������� ��� ���������� KeyIdentifier (4)"); 
					//
					AsnObject o2 = (*this)[2]; 
					//
					if (o2.m_ExtendedTag != 2) 
						throw MethodError(L"������ ��������� ��� ���������� KeyIdentifier (5)"); 
					//
					return o2.m_Data; 
				}
			}
			//
			return m_Data;
		}



		// -----------------------------------------------------------------------------------
		// ����������� ASN --> DER 

		void Update(int level=0)
		{
			if (m_Encoded.Length() > 0) return;
			//
			string tabs = Tabs(level);
			//
			int childrenDataLen = 0;
			//
			int k,j,s,len;
			//
			if (m_Tag == 30)
			{
				k = 1; 
			}
			//
			for (k = 0; k < ChildCount(); ++k)
			{
				childrenDataLen += ((AsnObject&)(*this)[k]).EncodedLength(level+1);
			}
			//
			int cntLen = 0;
			if (IsConstructed())
			{
				cntLen = childrenDataLen;
				if (IndefiniteLength())
				{
					s = 1;
					m_Encoded.Allocate(1+s+cntLen+2);
					m_Encoded.GetBuffer()[1+s+cntLen] = 0;
					m_Encoded.GetBuffer()[1+s+cntLen+1] = 0;
				}
				else
				{
					s = CntLengthDescriptorSize(cntLen);
					m_Encoded.Allocate(1+s+cntLen);
				}
				//
				int pos = 1+s;
				for (k = 0; k < ChildCount(); ++k)
				{
					AsnObject& child = (*this)[k];
					for (j = 0; j < child.Encoded().Length(); ++j)
					{
						m_Encoded[pos+j] = child.Encoded()[j];
					}
					pos += child.Encoded(level+1).Length();
				}
			}
			else
			{
				if (AsnClass() == UNIVERSAL)
				{
					if (Tag() == PrintableString || Tag() == NumericString)
					{
						Blob b = Util::WideStringToASCII(m_text);
						m_Data.Allocate(b.GetSize());
						CopyMemory(m_Data.GetBuffer(),b.GetBuffer(),b.GetSize());
					}
					else if (Tag() == IA5String)
					{
						if (m_text.GetLength() == 0) 
						{
							Blob b = Util::WideStringToASCII(L"null");
							m_Data.Allocate(b.GetSize());
							CopyMemory(m_Data.GetBuffer(),b.GetBuffer(),b.GetSize());
						}
						else 
						{
							Blob b = Util::WideStringToASCII(m_text);
							m_Data.Allocate(b.GetSize());
							CopyMemory(m_Data.GetBuffer(),b.GetBuffer(),b.GetSize());
						}
					}
					else if (Tag() == UTF8String)
					{
						Blob b = Util::WideStringToUTF8(m_text);
						m_Data.Allocate(b.GetSize());
						CopyMemory(m_Data.GetBuffer(),b.GetBuffer(),b.GetSize());
					}
					else if (Tag() == BMPString)
					{
						Blob b = Util::WideStringToUnicode(m_text);
						m_Data.Allocate(b.GetSize());
						CopyMemory(m_Data.GetBuffer(),b.GetBuffer(),b.GetSize());
					}
					else if (Tag() == INTEGER || Tag() == BOOLEAN)
					{
						if ((m_Integer != 0) || (m_Data.Length() == 0) || (Tag() == BOOLEAN))
						{
							int v = m_Integer;
							s = 0;
							if (v == 0) ++s;
							else
							{
								while (v > 0)
								{
									++s;
									v = (int)(v/256);
								}
							}
							//
							m_Data.Allocate(s);
							v = m_Integer;
							j = 0;
							if (v == 0) m_Data[s-1] = 0;
							else
							{
								while (v > 0)
								{
									m_Data[s-1-j] = (BYTE)( v - 256*(int)(v/256) );
									++j;
									v = (int)(v/256);
								}
							}
						}
					}
					else if (Tag() == UTCTime)
					{
						if (false)
						{
							//// m_text = string(m_Time.Format(_T("%y%m%d%H%M%SZ"))); // ("yyMMddHHmmssZ"); 
							//
							int y = m_Time.GetYear();
							if (y <= 0) y = 0;
							else
								while (y > 100) y -= 100;
							//
							string s_1 = FormatStr(
								L"%02d%02d%02d" // ("yyMMddHHmmssZ") 
								, y
								, m_Time.GetMonth()
								, m_Time.GetDay()
								);
							//
							string s_2 = FormatStr(
								L"%02d%02d%02dZ" // ("yyMMddHHmmssZ") 
								, m_Time.GetHour()
								, m_Time.GetMinute()
								, m_Time.GetSecond()
								);
							//
							m_text = s_1 + s_2;
							//
							// not yyyy !
							Blob b = Util::WideStringToASCII(m_text);
							//
							m_Data.Allocate(b.GetSize());
							CopyMemory(m_Data.GetBuffer(), b.GetBuffer(), b.GetSize());
						}
					}
					else if (Tag() == OBJECT_IDENTIFIER)
					{
						string text = m_Oid.operator string();
						m_Data = m_Oid.Encoded();
					}
					else if (Tag() == OCTET_STRING) 
					{
						bool f;
						if (fKeepDeep())
						{
							f = Deep.IsNull() || m_Data.Length() > 0; 
						}
						else
						{
							f = Deep.IsNull(); 
						}
						//
						if (f) //  
						{
							// m_Data �������� ������
						}
						else
						{
							m_Data = Deep.m_pDeep->Encoded();
						}
					}
					else if (Tag() == BIT_STRING)
					{
						cntLen = m_Data.Length() + 1;
						if (IndefiniteLength())
						{
							s = 1;
							m_Encoded.Allocate(1+s+cntLen+2);
						}
						else
						{
							s = CntLengthDescriptorSize(cntLen);
							m_Encoded.Allocate(1+s+cntLen);
						}
						for (j = 0; j < m_Data.Length(); ++j)
						{
							m_Encoded[1+s+1+j] = m_Data[m_Data.Length()-1-j];
						}
						m_Encoded[1+s] = (byte)m_UnusedBits;
						if (IndefiniteLength())
						{
							m_Encoded[1+s+1+m_Data.Length()] = 0;
							m_Encoded[1+s+1+m_Data.Length()+1] = 0;
						}
					}
					else if (Tag() == _NULL_)
					{
						m_Data.Free();
					}
					else
					{
						string msg = FormatStr(L"ASN Parse Error: Unknown tag %d", (int)m_Tag ); 
						//throw MethodError(msg); 
					}
					//
					if (Tag() != BIT_STRING)
					{
						cntLen = m_Data.Length();
						if (IndefiniteLength())
						{
#							ifdef _DEBUG
							// Runtime.Echo(Dump);
							// TRACE_LOG(Dump());
#							endif
							//
							s = 1;
							m_Encoded.Allocate(1+s+cntLen+2);
						}
						else
						{
							s = CntLengthDescriptorSize(cntLen);
							m_Encoded.Allocate(1+s+cntLen);
						}
						if (Tag() == INTEGER) 
						{
							for (j = 0; j < m_Data.Length(); ++j)
							{
								m_Encoded[1+s+j] = m_Data[m_Data.Length()-1-j];
							}
						}
						else
						{
							for (j = 0; j < m_Data.Length(); ++j)
							{
								m_Encoded[1+s+j] = m_Data[j];
							}
						}
						if (IndefiniteLength())
						{
							m_Encoded[1+s+cntLen] = 0;
							m_Encoded[1+s+cntLen+1] = 0;
						}
					}
				}
				else 
				{
					if (m_Tag == 6 || m_Tag == 0)
					{
						Blob b = Util::WideStringToASCII(m_text);
						m_Data.Allocate(b.GetSize());
						CopyMemory(m_Data.GetBuffer(), b.GetBuffer(), b.GetSize());
						//
						cntLen = m_Data.Length();
						s = CntLengthDescriptorSize(cntLen);
						m_Encoded.Allocate(1 + s + cntLen);
						for (j = 0; j < m_Data.Length(); ++j)
						{
							m_Encoded[1 + s + j] = m_Data[j];
						}
					}
					else if (m_Tag == 2)
					{
						// m_Data.Allocate(b.GetSize());
						// CopyMemory(m_Data.GetBuffer(), b.GetBuffer(), b.GetSize());
						//
						cntLen = m_Data.Length();
						s = CntLengthDescriptorSize(cntLen);
						m_Encoded.Allocate(1 + s + cntLen);
						for (j = 0; j < m_Data.Length(); ++j)
						{
							m_Encoded[1 + s + j] = m_Data[j];
						}
					}
					else
					{
						wchar_t s[1024];
						wprintf(s, L"ASN DER Error: non-UNIVERSAL and not constructed object, tag = %d.", m_Tag);
						throw MethodError(s);
					}
				}
			}
			//
			// ���������� ��������� ������ 
			//
			byte constructedBit = 0;
			if (m_IsConstructed) constructedBit = 0x20;
			m_Encoded[0] = (byte)( (m_AsnClass << 6) | constructedBit | m_Tag );
			//
			if (IndefiniteLength())
			{
				m_Encoded[1] = (byte)0x80;
			}
			else
			{
				if (cntLen < 128)
				{
					m_Encoded[1] = (byte)cntLen;
				}
				else
				{
					s = CntLengthDescriptorSize(cntLen)-1;
					len = cntLen;
					j = 0;
					while (len >= 256)
					{
						m_Encoded[1+s-j] = (byte)( len - 256*((int)(len/256)) );
						len = (int)(len/256);
						++j;
					}
					m_Encoded[1+s-j] = (byte)( len );
					m_Encoded[1] = (byte)( 0x80 | s );
				}
			}
		}

		Blob Encoded(int level=0) 
		{
			Update(level);
			return m_Encoded;
		}

		int EncodedLength(int level=0)
		{
			Update(level);
			return m_Encoded.Length();
		}

		Blob ToBlob()
		{
			DropEncoded();
			return Encoded(); 
		}

		void DropEncoded() 
		{
			m_Encoded.Free();
			if (IsConstructed())
			{
				for (int k = 0; k < ChildCount(); ++k)
				{
					AsnObject& child = (*this)[k];
					child.DropEncoded();
				}
			}
		}

		int CntLengthDescriptorSize(int len)
		{
			if (len < 128) return 1;
			else
			{
				int size = 1;
				while (len >= 256)
				{
					size += 1;
					len = (int)(len/256); 
				}
				size += 1;
				return size;
			}
		}



		// -----------------------------------------------------------------------------------
		// ��������� �� ASN 

		OID ObjectId()
		{
			if (Children.Length() >= 1)
			{
				AsnObject& child = (*this)[0];
				if (child.Tag() == OBJECT_IDENTIFIER)
				{
					return child.Oid();
				}
				else return OID::Null();
			}
			else return OID::Null();
		}

		AsnObject& Tagged(int tag)
		{
			P_Children::P_Child child = Children.Tagged(tag);
			//if (child.IsNull())
			//	throw MethodError(_S("������ tag=%d �� ������") % tag);
			//
			return child;
		}

		AsnObject& OctetString()
		{
			P_Children::P_Child child = Children.GetOctetString();
			if (child.IsNull())
				throw MethodError(L"������ �� ����� ���� ������������ � OctetString"); 
			//
			return child;
		}

		struct OidSet
		{
			static const int Level1Set = 1;
			static const int Level2Set = 2;

			int m_level;
			AsnObject* m_pObject;

			OidSet(AsnObject& o)
			{
				if (o.ChildCount() > 0)
				{
					if (( (AsnObject&)o[0] ).Tag() == OBJECT_IDENTIFIER) m_level = 1;
					else if (( (AsnObject&)o[0] ).ChildCount() > 0)
					{
						if (
							( (AsnObject&)((AsnObject&)o[0])[0] ).Tag() == OBJECT_IDENTIFIER) 
							m_level = 2;
					}
				}
				else
				{
					m_level = 0;
				}
				//
				m_pObject = &o;
			}

			OidSet()
			{
				m_level = 0;
				m_pObject = 0;
			}

			static OidSet Null()
			{
				return OidSet();
			}

			bool operator [](string oid)
			{
				return (*this)[OID(oid)];
			}

			bool operator [](OID oid)
			{
				if (m_level <= 0) return false;
				//
				bool found = false;
				//
				AsnObject& sequence = *m_pObject;
				for (int i = 0; i < sequence.ChildCount(); ++i)
				{
					AsnObject o1(false,UNIVERSAL,_NULL_);
					if (m_level == 1) o1 = sequence[1];
					if (m_level == 2) o1 = ((AsnObject&)sequence[1])[0];
					//
					if (o1.Tag() == OBJECT_IDENTIFIER)
					{
						if (o1.Oid() == oid) found = true;
					}
				}
				//
				return found;
			}

			SharedArray<OID> Oids()
			{
				Map<string,string> oidTable;
				//
				if (m_level <= 0) return SharedArray<OID>();
				//
				AsnObject sequence = *m_pObject;
				for (int i = 0; i < sequence.ChildCount(); ++i)
				{
					AsnObject o1(false,UNIVERSAL,_NULL_);
					if (m_level == 1) o1 = sequence[i];
					if (m_level == 2) o1 = ((AsnObject&)sequence[i])[0];
					//
					if (o1.Tag() == OBJECT_IDENTIFIER)
					{
						oidTable[string(o1.Oid())] = string(o1.Oid());
					}
				}
				//
				SharedArray<OID> oids;
				oids.Allocate(oidTable.GetSize());
				int k = 0;
				for (Map<string,string>::Iterator i(oidTable); i; ++i)
				{
					oids[k] = OID(string(i));
					++k;
				}
				//
				return oids;
			}

			string Text()
			{
				string text = L"";
				SharedArray<OID> oids = Oids();
				for (int k = 0; k < oids.GetSize(); ++k)
				{
					Util::AddText(&text,string(oids[k]));
				}
				return text;
			}
		};



		// -----------------------------------------------------------------------------------
		// ���������� ��� ������� 

		static const int RequestObjectType = 1;
		static const int CertificateObjectType = 2;

		//int ObjectType()
		//{
		//	if (IsSequence() && ChildCount() > 0)
		//	{
		//		// AsnObject t00 = Tagged(0);
		//		AsnObject child0 = (*this)[0];
		//		if (child0.IsSequence())
		//		{
		//			if (! child0.Children.Tagged(3).IsNull())
		//			{
		//				AsnObject t3 = child0.Tagged(3);
		//				if (t3.IsConstructed() && (t3.ChildCount() > 0))
		//				{
		//					if (! child0.Children.Tagged(0).IsNull())
		//					{
		//						return CertificateObjectType;
		//					}
		//					else return 0;
		//				}
		//				return 0;
		//			}
		//			else if (! child0.Children.Tagged(0).IsNull())
		//			{
		//				AsnObject t0 = child0.Tagged(0);
		//				if (t0.IsConstructed() && (t0.ChildCount() > 0))
		//				{
		//					AsnObject child1 = t0[0];
		//					if (child1.IsSequence() && (child1.ChildCount() > 0))
		//					{
		//						if (((AsnObject&)child1[0]).Tag() == OBJECT_IDENTIFIER)
		//						{
		//							if (((AsnObject&)child1[0]).Oid() == (string)L"1.3.6.1.4.1.311.2.1.14") 
		//								return RequestObjectType;
		//							else return 0;
		//						}
		//						else 
		//						{
		//							return 0;
		//						}
		//					}
		//					else
		//					{
		//						return 0;
		//					}
		//				}
		//				else
		//				{
		//					return 0;
		//				}
		//			}
		//			return 0;
		//		}
		//		else return 0;
		//	}
		//	else return 0;
		//}

		int ObjectType()
		{
			if (IsSequence() && ChildCount() > 0)
			{
				// AsnObject t00 = Tagged(0);
				AsnObject child0 = (*this)[0];
				if (child0.IsSequence())
				{
					if (child0.ChildCount() > 0)
					{
						AsnObject t0 = child0.Children[0];
						if (t0.Tag() == AsnObject::INTEGER)
						{
							if (t0.m_Integer == 0)
							{
								return RequestObjectType;
							}
							// else return 0;
						}
						// return 0;
					}
					if (! child0.Children.Tagged(3).IsNull())
					{
						AsnObject t3 = child0.Tagged(3);
						if (t3.IsConstructed() && (t3.ChildCount() > 0))
						{
							if (! child0.Children.Tagged(0).IsNull())
							{
								return CertificateObjectType;
							}
							else return 0;
						}
						return 0;
					}
					return 0;
				}
				else return 0;
			}
			else return 0;
		}



		// -----------------------------------------------------------------------------------
		// ��������

		static AsnObject NewSet()
		{
			return AsnObject(true,UNIVERSAL,SET);
		}

		static AsnObject NewSequence()
		{
			return AsnObject(true,UNIVERSAL,SEQUENCE);
		}

		static AsnObject NewOctetString()
		{
			return AsnObject(false,UNIVERSAL,OCTET_STRING);
		}

		static AsnObject NewNullObject()
		{
			return AsnObject(true,UNIVERSAL,_NULL_);
		}



		// -----------------------------------------------------------------------------------
		// ��������

		int AsnClass()
		{
			return m_AsnClass;
		}

		string AsnClassText()
		{
			if (m_AsnClass == UNIVERSAL) return L"UNIVERSAL";
			else if (m_AsnClass == PRIVATE) return L"PRIVATE";
			else if (m_AsnClass == APPLICATION) return L"APPLICATION";
			else if (m_AsnClass == CONTEXT_SPECIFIC) return L"CONTEXT_SPECIFIC";
			return FormatStr(L"/UNKNOWN(%d)/", (int)m_AsnClass );
		}

		bool IsConstructed()
		{
			return m_IsConstructed;
		}

		bool IsPrimitive()
		{
			return ! m_IsConstructed;
		}

		int Tag() 
		{
			if (m_AsnClass != UNIVERSAL) return 0;
			return m_Tag;
		}

		//struct ChildAssignerByIndex
		//{
		//	AsnObject& m_parent;

		//	int m_index;

		//	ChildAssignerByIndex(AsnObject& parent,int i) : m_parent(parent), m_index(i)
		//	{
		//	}

		//	void operator =(AsnObject& item)
		//	{
		//		if (m_parent.m_Children.ContainsKey(m_index))
		//		{
		//			void* p = m_parent.m_Children[m_index];
		//			delete (AsnObject*)p;
		//		}
		//		m_Children[m_index] = new AsnObject(item); 
		//	}

		//	operator AsnObject&()
		//	{
		//		if (m_parent.m_Children.ContainsKey(m_index))
		//		{
		//			void* p = m_parent.m_Children[m_index];
		//			return *( (AsnObject*)p );
		//		}
		//		else throw MethodError(_T("ASN Error: Not found"));
		//	}
		//};

		//ChildAssignerByIndex operator [](int i)
		//{
		//	return ChildAssignerByIndex(*this,i);
		//}

		int Length() 
		{
			return m_Length;
		}

		int ContentLength() 
		{
			return m_ContentLength;
		}

		int ChildCount() 
		{
			return Children.Length();
		}

		AsnObject& RemoveAllChildren() 
		{
			Children.Free();
			return *this;
		}

		bool IsSequence() 
		{
			return ((AsnClass() == UNIVERSAL) && (Tag() == SEQUENCE));
		}

		bool m_IndefiniteLength;

		bool IndefiniteLength() 
		{
			return m_IndefiniteLength;
		}

		void SetIndefiniteLength(bool value) 
		{
			m_Encoded.Free();
			m_IndefiniteLength = value;
		}

		COleDateTime UtcTime() 
		{
			if (m_Tag != UTCTime) 
			{
				string msg = FormatStr(L"ASN Parse Error: Wrong tag %d", (int)m_Tag ); 
				throw MethodError(msg); 
			}
			//
			return m_Time;
		}

		Blob& Data() 
		{
			return m_Data;
		}

		void SetData(Blob value)
		{
			if (! (
				(Tag() == OCTET_STRING) ||
				(Tag() == BIT_STRING)
				))
			{
				string msg = FormatStr(L"ASN Parse Error: Wrong tag %d", (int)Tag() ); 
				throw MethodError(msg); 
			}
			//
			m_Data.Allocate(value.Length());
			for (int j = 0; j < value.Length(); ++j) m_Data[j] = value[j];
			//
			if (Tag() == BIT_STRING) m_UnusedBits = 0;
		}

		OID Oid() 
		{
			if (Tag() != OBJECT_IDENTIFIER) 
			{
				string msg = FormatStr(L"ASN Parse Error: Wrong tag %d", (int)Tag() ); 
				throw MethodError(msg); 
			}
			//
			return (OID)m_Oid;
		}

		AsnObject(OID oid) : MOUNT_PROPERTIES() 
		{
			m_ContentLength = m_Length = m_ExtendedTag = m_Integer = m_UnusedBits = 0;
			m_IndefiniteLength = false;
			//
			m_IsConstructed = false;
			m_AsnClass = UNIVERSAL;
			m_Tag = OBJECT_IDENTIFIER;
			m_Oid = oid;
		}

		AsnObject& Add(AsnObject child)
		{
			Children[ChildCount()] = child;				
			return *this;
		}

		// ----
		// ��������������

		void SetToString(string v,int tag)
		{
			m_IsConstructed = false;
			m_AsnClass = UNIVERSAL;
			m_Tag = tag;
			m_text = v;
			m_IndefiniteLength = false;
		}

		AsnObject(string v,int tag) : MOUNT_PROPERTIES() 
		{
			SetToString(v,tag);
		}

		AsnObject(string v,OID oid) : MOUNT_PROPERTIES() 
		{
			int tag = DefaultStringType;
			m_IndefiniteLength = false;
			//
			if ((oid == X500().sEmailOid)) tag = BMPString; // IA5String;
			//
			if ((oid == X500().sCountryNameOid)) tag = PrintableString;
			//
			if ((oid == X500().GetOID(L"GOV_PKI_���")) ||
				(oid == X500().GetOID(L"GOV_PKI_����")) ||
				(oid == X500().GetOID(L"GOV_PKI_�����"))) tag = NumericString;
			//
			if ((oid == X500().sCommonNameOid) || 
				(oid == X500().sLocalityNameOid) || 
				(oid == X500().sStateOrProvinceNameOid) || 
				(oid == X500().sOrganizationNameOid) || 
				(oid == X500().sOrganizationalUnitNameOid) || 
				(oid == X500().sTitleOid)) tag = UTF8String;
			//
			SetToString(v,tag);
		}

		AsnObject(string v) : MOUNT_PROPERTIES() 
		{
			SetToString(v,BMPString);
		}



		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// �������� �����������

		bool IsRequest() 
		{
			return ObjectType() == RequestObjectType;
		}

		bool IsCertificate() 
		{
			return ObjectType() == CertificateObjectType;
		}

		// Certificate Extensions 

		struct P_CertificateExtensionObject 
		{
			AsnObject& m_parent;

			P_CertificateExtensionObject(AsnObject& parent) : m_parent(parent) 
			{
			}

			operator AsnObject&()
			{
				AsnObject* requestAttrs = 0;
				if (m_parent.IsCertificate()) 
					requestAttrs = &( ((AsnObject&)m_parent[0]).Tagged(3) );
				else if (m_parent.IsRequest()) 
					requestAttrs = &( ((AsnObject&)m_parent[0]).Tagged(0) );
				//
				if (requestAttrs == 0) 
					throw MethodError(L"ASN Error: No room for certificate extension");
				//
				for (int k = 0; k < requestAttrs->ChildCount(); ++k)
				{
					if (((AsnObject&)(*requestAttrs)[k]).ObjectId() == OID(string(L"1.3.6.1.4.1.311.2.1.14")))
					{
						return ((AsnObject&) ((AsnObject&)(*requestAttrs)[k])[1] )[0];
					}
				}
				throw MethodError(L"ASN Error: No certificate extension object");
			}

			const AsnObject& operator =(const AsnObject& value)
			{
				// TODO: ! 
				return value;
			}
		};

		P_CertificateExtensionObject CertificateExtensionObject; 

		AsnObject& CreateCertificateExtension(string oidStr)
		{
			return CreateCertificateExtension(OID(oidStr));
		}

		AsnObject& CreateCertificateExtension(OID oid)
		{
			AsnObject& extensions = CertificateExtensionObject;
			AsnObject o1 = NewSequence()
				.Add(AsnObject(oid))
				.Add(NewOctetString());
			//
			//int n1 = o1.ChildCount();
			//
			extensions.Add(o1);
			AsnObject& r1 = ((AsnObject&)CertificateExtensionObject).Children[oid];
			//OutputDebugStringW(r1.Dump());
			return r1;
		}

		// Key Usage 

		struct KeyUsageDescription
		{
			static const int KeyUsageDigitalSignature		= 0;
			static const int KeyUsageNonRepudiation			= 1;
			static const int KeyUsageKeyEncipherment		= 2;
			static const int KeyUsageDataEncipherment		= 3;
			static const int KeyUsageKeyAgreement			= 4;
			static const int KeyUsageKeyCertSign			= 5;
			static const int KeyUsageCRLSign				= 6;
			static const int KeyUsageEncipherOnly			= 7;
			static const int KeyUsageDecipherOnly			= 8;

			Blob	m_data;
			UINT		m_bits;

			KeyUsageDescription(AsnObject o) // BitString 
			{
				m_data.Allocate(o.Data().Length());
				for (int j = 0; j < o.Data().Length(); ++j) m_data[j] = o.Data()[j];
				m_bits = ((UINT)m_data[1] << 8) | (UINT)m_data[0];
			}

			bool operator [](int usage)
			{
				return ((m_bits >> usage) & 0x1) != 0;
			}

			string Text()
			{
				string text = L"";
				if ((*this)[KeyUsageDigitalSignature])	Util::AddText(&text,L"DigitalSignature");
				if ((*this)[KeyUsageNonRepudiation])	Util::AddText(&text,L"NonRepudiation");
				if ((*this)[KeyUsageKeyEncipherment])	Util::AddText(&text,L"KeyEncipherment");
				if ((*this)[KeyUsageDataEncipherment])	Util::AddText(&text,L"DataEncipherment");
				if ((*this)[KeyUsageKeyAgreement])		Util::AddText(&text,L"KeyAgreement");
				if ((*this)[KeyUsageKeyCertSign])		Util::AddText(&text,L"KeyCertSign");
				if ((*this)[KeyUsageCRLSign])			Util::AddText(&text,L"CRLSign");
				if ((*this)[KeyUsageEncipherOnly])		Util::AddText(&text,L"EncipherOnly");
				if ((*this)[KeyUsageDecipherOnly])		Util::AddText(&text,L"DecipherOnly");
				return text;
			}
		};

		KeyUsageDescription KeyUsage() 
		{
			if (! IsCertificate()) 
				throw MethodError(L"ASN Error: Not a certificate");
			//
			AsnObject& o1 = ((AsnObject&)CertificateExtensionObject).Children[OID(string(L"2.5.29.15"))];
			return KeyUsageDescription(o1.OctetString().Deep);
		}

		// Subject Key Identifier 

		Blob SKI() 
		{
			if (! IsCertificate()) 
				throw MethodError(L"ASN Error: Not a certificate");
			//
			AsnObject& o1 = ((AsnObject&)CertificateExtensionObject).Children[OID(string(L"2.5.29.14"))];
			return ((AsnObject&)o1.OctetString().Deep).KeyIdentifier();
		}

		// Authority Key Identifier 

		Blob AuthorityKI() 
		{
			if (! IsCertificate()) 
				throw MethodError(L"ASN Error: Not a certificate");
			//
			AsnObject& o1 = ((AsnObject&)CertificateExtensionObject).Children[OID(string(L"2.5.29.35"))];
			return ((AsnObject&) ((AsnObject&)o1.OctetString().Deep)[0] ).KeyIdentifier();
		}

		// Certificate Policies 

		OidSet CertificatePolicies() 
		{
			AsnObject& o1 = ((AsnObject&)CertificateExtensionObject).Children[OID(string(L"2.5.29.32"))];
			return OidSet(o1.OctetString().Deep);
		}

		void RemoveAllPolicies()
		{
			AsnObject& o1 = ((AsnObject&)CertificateExtensionObject).Children[OID(string(L"2.5.29.32"))];
            AsnObject& deep = o1.OctetString().Deep;
			deep.RemoveAllChildren(); 
		}

        void AddPolicyToRequest(string policy)
        {
			AsnObject& o1 = ((AsnObject&)CertificateExtensionObject).Children[OID(string(L"2.5.29.32"))];
            AsnObject& deep = o1.OctetString().Deep;
			deep.Add(
				AsnObject::NewSequence().Add(AsnObject(OID(policy))));
        }

		// SMIME Capabilities 

		OidSet SMIMECapabilities() 
		{
			if (! IsCertificate()) 
				throw MethodError(L"ASN Error: Not a certificate");
			//
			AsnObject& o = ((AsnObject&)CertificateExtensionObject)
				.Children[OID(string("1.2.840.113549.1.9.15"))];
			// if (o == null) return OidSet::Null();
			return OidSet(o.OctetString().Deep);
		}

		// Extended Key usage 

		OidSet ExtendedKeyUsage() 
		{
			if (! IsCertificate()) 
				throw MethodError(L"ASN Error: Not a certificate");
			//
			AsnObject& o = ((AsnObject&)CertificateExtensionObject).Children[OID(string(L"2.5.29.37"))];
			// if (o == null) return OidSet::Null();
			return OidSet(o.OctetString().Deep);
		}



		// Subject 

		struct P_SubjectObject
		{
			AsnObject& m_parent;

			P_SubjectObject(AsnObject& parent) : m_parent(parent)
			{
			}

			operator AsnObject&() 
			{
				if (m_parent.IsCertificate())
				{
					return ((AsnObject&)m_parent[0])[3];
				}
				else if (m_parent.IsRequest())
				{
					return ((AsnObject&)m_parent[0])[1];
				}
				else 
					throw MethodError(L"ASN Error: Neither certifiate nor request");
			}

			const AsnObject& operator =(const AsnObject& value) 
			{
				if (m_parent.IsCertificate())
				{
					AsnObject& o1 = m_parent[0]; 
					AsnObject& o2 = o1[3];
					o2 = AsnObject(value);
				}
				else if (m_parent.IsRequest())
				{
					AsnObject& o1 = m_parent[0]; 
					AsnObject& o2 = o1[1];
					o2 = AsnObject(value);
				}
				else 
					throw MethodError(L"ASN Error: Neither certifiate nor request");
				//
				return value;
			}
		};



		P_SubjectObject SubjectObject;

		struct P_Subject
		{
			AsnObject& m_parent;

			P_Subject(AsnObject& parent) : m_parent(parent)
			{
			}

			operator NameDescription();  

			NameDescription& operator =(NameDescription& value); 
		};

		P_Subject Subject;

		AsnObject& SetSubject(NameDescription v);



		// Subject Alternative Name 

		struct P_SubjectAltNameObject
		{
			AsnObject& m_parent;

			P_SubjectAltNameObject(AsnObject& parent) : m_parent(parent) 
			{
			}

			operator AsnObject&() 
			{
				if (m_parent.IsCertificate())
				{
					AsnObject& E = (AsnObject&)m_parent.CertificateExtensionObject;
					//
					if (!( E.Children[OID(string(L"2.5.29.17"))].IsNull()))
					{
						AsnObject& o = 
						((AsnObject&)m_parent.CertificateExtensionObject)
							.Children[OID(string(L"2.5.29.17"))];
						//OutputDebugStringW(o.Dump()); 
						return o.OctetString().Deep;
					}
					else
					{
						AsnObject& o = 
						((AsnObject&)m_parent.CertificateExtensionObject)
							.Children[OID(string(L"2.5.29.7"))];
						//OutputDebugStringW(o.Dump()); 
						return o.OctetString().Deep;
					}
					// if (o.IsNull()) return SharedPtr<AsnObject>();
				}
				else if (m_parent.IsRequest()) // ���������� ������� ����������� 
				{
					AsnObject& E = (AsnObject&)m_parent.CertificateExtensionObject;
#ifdef _DEBUG
					{
						///OutputDebugStringW(E.Dump() + L"\n");
					}
#endif
					if (!( E.Children[OID(string(L"2.5.29.7"))].IsNull()))
					{
						AsnObject& o = E.Children[OID(string(L"2.5.29.7"))];
						//OutputDebugStringW(o.Dump()); 
						return ((AsnObject&)o.OctetString().Deep).Tagged(4)[0];
					}
					else
					{
						AsnObject& o = E.Children[OID(string(L"2.5.29.17"))];
						//OutputDebugStringW(o.Dump()); 
						return ((AsnObject&)o.OctetString().Deep).Tagged(4)[0];
					}
					// TODO: !!!
					//if (o.IsNull()) o = 
					//	((AsnObject&)m_parent.CertificateExtensionObject)
					//		.Children[OID(string(L"2.5.29.7"))];
					//if (o.IsNull())
					//{
					//	o = m_parent.CreateCertificateExtension(OID(string(L"2.5.29.7")));
					//	o.OctetString().Deep = 
					//		NewSequence.Add(
					//			AsnObject(true,CONTEXT_SPECIFIC,4)
					//				.Add(NewSequence)
					//		);
					//}
				}
				else 
					throw MethodError(L"ASN Error: Neither certifiate nor request");
			}

			const AsnObject& operator =(const AsnObject& value)
			{
				if (m_parent.IsCertificate())
				{
					AsnObject& o = 
						((AsnObject&)m_parent.CertificateExtensionObject)
							.Children[OID(string(L"2.5.29.17"))];
					// TODO: !!!
					//if (o.IsNull()) o = 
					//	((AsnObject&)m_parent.CertificateExtensionObject)
					//		.Children[OID(string(L"2.5.29.7"))];
					//if (o.IsNull()) throw MethodError(_T("ASN Error: !"));
					o.OctetString().Deep = value;
				}
				else if (m_parent.IsRequest()) // ���������� ������� ����������� 
				{
					if (((AsnObject&)m_parent.CertificateExtensionObject)
							.Children[OID(string(L"2.5.29.7"))].IsNull())
					{
						AsnObject& o = m_parent.CreateCertificateExtension((string)L"2.5.29.7");
						AsnObject& o3 = (AsnObject&)o.OctetString().Deep; 
						AsnObject& o3a = o3.Tagged(4); 
						AsnObject& o3b = o3a[0]; 
						o3b = AsnObject(value); 
					}
					else
					{
						AsnObject& E = (AsnObject&)m_parent.CertificateExtensionObject;
						// TRACE_LOG(E.Dump());
						AsnObject& o = E.Children[OID(string(L"2.5.29.7"))];
						AsnObject& o3b = ( ((AsnObject&)o.OctetString().Deep).Tagged(4) )[0]; 
						o3b = AsnObject(value);
					}
					// TODO: !!!
					//if (o.IsNull()) o = 
					//	((AsnObject&)m_parent.CertificateExtensionObject)
					//		.Children[OID(string(L"2.5.29.7"))];
					//if (o.IsNull())
					//{
					//	o = CreateCertificateExtension(L"2.5.29.7");
					//	o.OctetString().Deep = 
					//		NewSequence.Add(
					//			new AsnObject(true,CONTEXT_SPECIFIC,4)
					//				.Add(NewSequence)
					//		);
					//}
				}
				else 
					throw MethodError(L"ASN Error: Neither certifiate nor request");
				//
				return value;
			}

			//bool IsNull()
			//{
			//	SharedPtr<AsnObject> spObject(*this);
			//	return spObject.IsEmpty();
			//}
		};

		P_SubjectAltNameObject SubjectAltNameObject;

		AsnObject& SetSubjectAltName(NameDescription v);

		struct P_SubjectAltName
		{
			AsnObject& m_parent;

			P_SubjectAltName(AsnObject& parent) : m_parent(parent)
			{
			}

			operator NameDescription();

			NameDescription& operator =(NameDescription& value); 
		};

		P_SubjectAltName SubjectAltName;



		// Public Key

		struct P_PublicKey
		{
			AsnObject& m_parent;

			P_PublicKey(AsnObject& parent) : m_parent(parent)
			{
			}

			operator AsnObject&() 
			{
				if (m_parent.IsRequest()) return ((AsnObject&)m_parent[0])[2];
				else if (m_parent.IsCertificate()) return ((AsnObject&)m_parent[0])[6];
				else 
				{
					throw MethodError(L"ASN Error: Nor a request, neither a certificate"); 
				}
			}

			const AsnObject& operator =(const AsnObject& value)
			{
				AsnObject& o1 = ((AsnObject&)m_parent[0])[6];
				o1 = AsnObject(value);
				return value;
			}
		};

		P_PublicKey PublicKey;

		// ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ 
		// 
		// ������������ ���� 

		struct P_CP_GOST2001PublicKeyOctets
		{
			AsnObject& m_parent;

			P_CP_GOST2001PublicKeyOctets(AsnObject& parent) : m_parent(parent) 
			{
			}

			operator Blob()
			{
				AsnObject& o = m_parent.PublicKey;
				AsnObject& o2 = o[1];
				return o2.Data();
			}

			Blob operator =(Blob value)
			{
				AsnObject publicKey = m_parent.PublicKey;
				//
				int j;
				// byte y1;
				//
				((AsnObject&)publicKey[1]).m_Data.Allocate(value.Length());
				//
				for (j = 0; j < 16; ++j) 
				{
					((AsnObject&)publicKey[1]).m_Data[j] = value[31-j];
				}
				for (j = 0; j < 16; ++j) 
				{
					((AsnObject&)publicKey[1]).m_Data[32+j] = value[32+31-j];
				}				
				//
				return value;
			}
		};

		P_CP_GOST2001PublicKeyOctets CP_GOST2001PublicKeyOctets;



		struct P_PublicKeyAlgorithm
		{
			AsnObject& m_parent;

			P_PublicKeyAlgorithm(AsnObject& parent) : m_parent(parent) 
			{
			}

			operator string() 
			{
				AsnObject publicKey = m_parent.PublicKey;
				//
				return ((AsnObject&) ((AsnObject&)publicKey[0])[0] ).m_text;
			}

			const string& operator =(const string& value)
			{
				AsnObject publicKey = m_parent.PublicKey;
				//
				// TODO: � ��� value?
				AsnObject& o1 = ((AsnObject&)publicKey[0])[0];
				o1 = AsnObject(OID(string(L"1.2.643.2.2.98")));
			}
		};

		P_PublicKeyAlgorithm PublicKeyAlgorithm;



		struct P_CP_GOST2001PublicKeyBits
		{
			AsnObject& m_parent;

			P_CP_GOST2001PublicKeyBits(AsnObject& parent) : m_parent(parent) 
			{
			}

			operator Blob()
			{
				return m_parent.CP_GOST2001PublicKeyOctets;
				// TODO: !!!!!!!!!!! 
			}

			Blob operator =(Blob value)
			{
				AsnObject& publicKey = m_parent.PublicKey;
				//
				((AsnObject&)publicKey[1]).m_Data.Allocate(value.Length());
				for (int j = 0; j < value.Length(); ++j) 
					((AsnObject&)publicKey[1]).m_Data[j] = value[j];
				//
				return value;
			}
		};

		P_CP_GOST2001PublicKeyBits CP_GOST2001PublicKeyBits;



		// -----------------------------------------------------------------------------------
		// ����� �� �����

		string Dump()
		{
			return GetDump(0);
		}

		AsnObject& DumpToFile(string path)
		{
			// ... Encoding.GetEncoding("windows-1251").GetBytes(Dump);
			Blob dumpData = Util::WideStringToASCII(Dump());
			//FileStream writer = File.Open(path,FileMode.Create,FileAccess.Write); 
			//writer.Write(dumpData,0,(int)dumpData.Length);
			//writer.Close();
			File f;
			f.Open(CString(path));
			f.Replace((char*)dumpData.GetBuffer(),dumpData.GetSize());
			f.Close();
			return *this;
		}

		AsnObject& SaveToFile(string path)
		{
			Blob dumpData = Encoded();
			//Blob b;
			//b.Allocate(dumpData.Length());
			//CopyMemory(b.GetBuffer(),dumpData.GetBuffer(),dumpData.Length());
			//
			File f;
			f.Open(CString(path));
			f.Replace((char*)dumpData.GetBuffer(),dumpData.Length());
			f.Close();
			return *this;
		}

		string GetDump(int level)
		{
			string tabs = Tabs(level);
			//
			// int j;
			//
			//Blob m_DataBlob;
			//m_DataBlob.Allocate(m_Data.Length());
			//CopyMemory(m_DataBlob.GetBuffer(),m_Data.GetBuffer(),m_Data.Length());
			//
			string dump;
			if (m_AsnClass == UNIVERSAL)
			{
				dump = tabs + GetTagName(m_Tag);
				if (Tag() == OBJECT_IDENTIFIER)
				{
					dump += string(m_Oid);
				}
				else if (m_Tag == INTEGER)
				{
					dump += FormatStr(L" %d", m_Integer );
				}
				else if (m_Tag == BMPString)
				{
					/// Update();
					dump += L" \"" + m_text + L"\" " + string(Util::BlobToHex(m_Data));
				}
				else if (m_Tag == UTF8String)
				{
					dump += L" \""+m_text+L"\"";
				}
				else if (m_Tag == IA5String)
				{
					dump += L" \""+m_text+L"\"";
				}
				else if (m_Tag == PrintableString || m_Tag == NumericString) 
				{
					dump += L" \""+m_text+L"\"";
				}
				else if (m_Tag == OCTET_STRING)
				{
					if (m_Data.Length() == 0) dump += L" null";
					else dump += FormatStr(L" %d", (int)m_Data.Length() );
				}
				else if (m_Tag == BIT_STRING) // 
				{
					int x1 = m_Data.Length()*8-m_UnusedBits;
					int x2 = m_Data.Length();
					//
					string text1 = FormatStr(L"%d", (int)x1 );
					//
					string text = L" " + text1
						+ L": " + FormatStr(L"%d", (int)x2 ) 
						+ L"(" + FormatStr(L"%d", m_UnusedBits ) + L")";
					//
					dump += text;
					dump += L"\r\n" + Tabs(level+1) + string(Util::BlobToHex(m_Data));
				}
				else if (m_Tag == UTCTime)
				{
					CString timeStr_1 = FormatStr(
						_T("%04d-%02d-%02d") // ("YYYY-MM-dd HH:mm:ss") 
						,m_Time.GetYear()
						,m_Time.GetMonth()
						,m_Time.GetDay()
						);
					CString timeStr_2 = FormatStr(
						_T(" %02d:%02d:%02d") // ("YYYY-MM-dd HH:mm:ss") 
						,m_Time.GetHour()
						,m_Time.GetMinute()
						,m_Time.GetSecond()
						);
					CString timeStr = timeStr_1 + timeStr_2; 
					dump += L" " + string(timeStr);
				}
				else
				{
					if (! m_IsConstructed)
					{
						if (m_Data.Length() == 0) dump += L"(unknown) null";
						else dump += FormatStr(L"(unknown) %d", (int)m_Data.Length() );
					}
				}
				dump += ExtraInfo(level+1);
				//
				int u_1;
				if (m_Tag == 30)
				{
					u_1 = 1; 
				}
				//
				if (m_IsConstructed)
				{
					if (m_AsnClass != UNIVERSAL) dump += L" [constructed]";
					for (int i = 0; i < ChildCount(); ++i)
					{
						dump += L"\r\n" + ((AsnObject&)Children[i]).GetDump(level+1);
					}
				}
				//
				if (! Deep.IsNull())
				{
					dump += L"\r\n" + Tabs(level+1) + L"*";
					dump += L"\r\n" + ((AsnObject&)Deep).GetDump(level+1);
					dump += L"\r\n" + Tabs(level+1) + L"~";
				}
			}
			else
			{
				dump = tabs + L"Tag : [" + FormatStr(L"%d", m_Tag ) + L"] " + AsnClassText();
				dump += ExtraInfo(level+1);
				if (m_IsConstructed)
				{
					for (int i = 0; i < ChildCount(); ++i)
					{
						dump += L"\r\n" + ((AsnObject&)Children[i]).GetDump(level+1);
					}
				}
			}
			return dump;
		}

		string ExtraInfo(int level)
		{
			string text = L"";
			//
			OID id = ObjectId();
			//
			if (id == (OID)L"2.5.29.15")
			{
				text += L"\r\n" + Tabs(level) + L"Key Usage: " + KeyUsageDescription(OctetString()).Text();
			}
			else if (id == (OID)L"2.5.29.14")
			{
				Blob SKI = ((AsnObject&)OctetString().Deep).KeyIdentifier();
				Blob SKIBlob;
				SKIBlob.Allocate(SKI.Length());
				CopyMemory(SKIBlob.GetBuffer(),SKI.GetBuffer(),SKI.Length());
				//
				text += L"\r\n" + Tabs(level) + L"SKI: " + string(Util::BlobToHex(SKIBlob)) + 
					L" (" + FormatStr(L"%d", SKI.Length() ) + L")";
			}
			else if (id == (OID)L"2.5.29.35")
			{
				Blob AuthorityKI = ((AsnObject&) ((AsnObject&)OctetString().Deep)[0] ).KeyIdentifier();
				Blob AuthorityKIBlob;
				AuthorityKIBlob.Allocate(AuthorityKI.Length());
				CopyMemory(AuthorityKIBlob.GetBuffer(),AuthorityKI.GetBuffer(),AuthorityKI.Length());
				//
				text += L"\r\n" + Tabs(level) + L"AuthorityKI: " + 
					string(Util::BlobToHex(AuthorityKIBlob)) + 
					L" (" + FormatStr(L"%d", AuthorityKI.Length() ) + L")";
			}
			else if (id == (OID)L"1.2.840.113549.1.9.15")
			{
				text += L"\r\n" + Tabs(level) + L"SMIME: " + OidSet(OctetString().Deep).Text();
			}
			else if (id == (OID)L"2.5.29.32")
			{
				text += L"\r\n" + Tabs(level) + L"CertificatePolicies: " + 
					OidSet(OctetString().Deep).Text();
			}
			else if (id == (OID)L"2.5.29.37")
			{
				text += L"\r\n" + Tabs(level) + L"ExtendedKeyUsage: " + OidSet(OctetString().Deep).Text();
			}
			else if (id == (OID)L"1.2.643.100.111")
			{
				AsnObject& o1 = OctetString().Deep; 
				text += L"\r\n" + Tabs(level) + L"subjectSignTool: \r\n" + o1.GetDump(level+1); 
				//
				if (false)
				{
					AsnObject cspText(string(L"\"��������� CSP\" (������ 3.6)"),AsnObject::UTF8String);
					o1 = cspText;
					//
					Blob b = o1.Encoded(); 
					::File f;
					f.OpenToWrite(_T("C:\\Temp\\subjectSignTool_2.der"));  
					f.Replace((const char*)b.GetBuffer(), b.Length());  
					f.Close();
				}
			}
			else if (id == (OID)L"1.2.643.100.112")
			{
				AsnObject& o1 = OctetString().Deep; 
				text += L"\r\n" + Tabs(level) + L"IssuerSignTool: \r\n" + o1.GetDump(level+1); 
				//
				if (false)
				{
					AsnObject cspText(string(L"\"��������� CSP\" (������ 3.6)"),AsnObject::UTF8String); 
					////AsnObject ss1(string(L"� ��/124-1543 �� 04.10.2010 �."),AsnObject::UTF8String);
					AsnObject ss2(string(L"� ��/121-1857 �� 17.06.2012 �."),AsnObject::UTF8String); 
					AsnObject ss3(string(L"� ��/128-1822 �� 01.06.2012 �."),AsnObject::UTF8String); // false, AsnObject::UTF8String, ... 
					o1[0] = cspText;
					o1[2] = ss2;
					o1[3] = ss3;
					////o1.Add(ss3);
					Blob b = o1.Encoded();
					::File f;
					f.OpenToWrite(_T("C:\\Temp\\IssuerSignTool_2.der"));
					f.Replace((const char*)b.GetBuffer(), b.Length());
					f.Close();
				}
			}
			//
			if (m_ExtendedTag != -1)
			{
				if (m_ExtendedTag == 6)
				{
					text += L"\r\n" + Tabs(level) + L"{6} Url: " + m_text;
				}
			}
			//
			return text;
		}

		string Tabs(int n)
		{
			string tabs = L"";
			for (int k = 0; k < n; ++k) tabs += L"    ";
			return tabs;
		}

		string GetTagName(int tag)
		{
			if (tag == OBJECT_IDENTIFIER) return L"OID.";
			else if (tag == BOOLEAN) return L"Boolean";
			else if (tag == INTEGER) return L"Integer";
			else if (tag == OCTET_STRING) return L"OctetString";
			else if (tag == PrintableString) return L"PrintableString";
			else if (tag == NumericString) return L"NumericString";
			else if (tag == IA5String) return L"IA5String";
			else if (tag == UTF8String) return L"UTF8String";
			else if (tag == BMPString) return L"BMPString";
			else if (tag == _NULL_) return L"Null";
			else if (tag == UTCTime) return L"UTCTime";
			else if (tag == SEQUENCE) return L"Sequence";
			else if (tag == SET) return L"Set";
			else if (tag == BIT_STRING) return L"BitString";
			else return L"Unknown";
		}







		inline static Blob PersonalRequestTemplate()
		{
			if (1 == 1)
			{
			return Util::FromBase64String(
				//L"MIICTDCCAfkCAQAwgdUxKTAnBgkqhkiG9w0BCQEeGgBhAHMAZABhAHMAQABkAHMAYQBkAC4AcgB1"
				//L"MQ0wCwYDVQQGHgQAUgBVMQswCQYDVQQIHgIAMzELMAkGA1UEBx4CADMxETAPBgNVBAoeCAQaBEME"
				//L"OgRDMTUwMwYDVQQDHiwEJARRBDQEQAAgBCQENQQ0BD4EQAQ+BDIAIAREBDUENAQ+BEAEPgQyBDgE"
				//L"RzEbMBkGCCqFAwOBAwEBEg0zMzMzMzMzMzMzMzMzMRgwFgYFKoUDZAESDTMzMzMzMzMzMzMzMzMw"
				//L"YzAcBgYqhQMCAhMwEgYHKoUDAgIjAQYHKoUDAgIeAQNDAARAV54s73QE2QGtinlqQQaLyuhZY3b7"
				//L"GnAwvWCMfjR7NeMurDCpO6f1K8VvkdlkXHaZ5GoeSDHPnc3AUyukqf3vfKCBtjCBswYKKwYBBAGC"
				//L"NwIBDjGBpDCBoTALBgNVHQ8EBAMCBPAwGQYJKoZIhvcNAQkPBAwwCjAIBgYqhQMCAhUwHQYDVR0l"
				//L"BBYwFAYIKwYBBQUHAwIGCCsGAQUFBwMEMCkGA1UdIAQiMCAwCAYGKoUDZHEBMAgGBiqFA2RxAjAK"
				//L"BggqhQMGAgEHATAtBgUqhQNkbwQkDCLQodCa0JfQmCAi0JrRgNC40L/RgtC+LdCa0J7QnCAzLjIi"
				//L"MAoGBiqFAwICAwUAA0EAklYSwyddTt2asjFiFO/Qy1bIvSUz5DN5ZcI+vPVYD/5rFHOaT7E+DYWS"
				//L"F2sjPdwZEqAbh1s7/wS54XL9LS0lkg==");
				L"MIIE7TCCA9kCAQAwgaQxSzBJBgNVBAMeQgQfBEAEOARFBD4ENARMBDoEPgAgBBAEOwQ1BDoEQQQw"
				L"BD0ENARAACAEEAQ7BDUEOgRBBDAEPQQ0BEAEPgQyBDgERzEvMC0GCSqGSIb3DQEJAR4gAHAAcgBp"
				L"AGgAbwBkAGsAbwBAAGYAcgBzAGQALgByAHUxFTATBgNVBAgeDAQcBD4EQQQ6BDIEMDENMAsGA1UE"
				L"Bh4EAFIAVTBjMBwGBiqFAwICEzASBgcqhQMCAiMBBgcqhQMCAh4BA0MABEAWAWYSbOnp9E4d/KOu"
				L"F7ntqLXmbtyPy1rzonp19z8as23gnnbovHEoe/1e9uqFzh9JHG2/d/VQ8ZntdSZ5+dUzoIICxjCC"
				L"AsIGCisGAQQBgjcCAQ4xggKyMIICrjALBgNVHQ8EBAMCBPAwGQYJKoZIhvcNAQkPBAwwCjAIBgYq"
				L"hQMCAhUwHQYDVR0lBBYwFAYIKwYBBQUHAwIGCCsGAQUFBwMEMFAGA1UdIARJMEcwCQYHKoUDAwhk"
				L"ATAKBggqhQMDCGQBATAKBggqhQMDCGQBAjAKBggqhQMDCGQBAzAKBggqhQMDCGQBBDAKBggqhQMD"
				L"CGQBBTCCAhEGA1UdBwSCAggwggIEpIICADCCAfwxGzAZBgNVBAQeEgQfBEAEOARFBD4ENARMBDoE"
				L"PjEcMBoGBFUEKmUeEgQQBDsENQQ6BEEEMAQ9BDQEQDEkMCIGBFUEKmYeGgQQBDsENQQ6BEEEMAQ9"
				L"BDQEQAQ+BDIEOARHMR4wHAYEVQQNZR4UBB8EMARBBD8EPgRABEIAIAQgBCQxGDAWBgRVBA1mHg4A"
				L"KARBBDUEQAQ4BE8AKTEiMCAGBFUEDWceGAA0ADUAIAAwADMAIAA2ADIAMwA0ADYANzFSMFAGBFUE"
				L"DWgeSAQeBBIEFAAgBBEENQRBBDoEQwQ0BD0EOAQ6BD4EMgRBBDoEPgQzBD4AIARABDAEOQQ+BD0E"
				L"MAAgBDMALgQcBD4EQQQ6BDIESzEeMBwGBFUEDWkeFAAwADYALgAwADkALgAyADAAMAAyMS8wLQYD"
				L"VQQJHiYEGwQ1BD0EOAQ9BDMEQAQwBDQEQQQ6BD4ENQAgBEgEPgRBBEEENTEUMBIGBFUECWUeCgAx"
				L"ADEAMgAvADExDDAKBgRVBAlmHgIAMjEQMA4GBFUECWceBgAyADgANTEWMBQGBFUECWUeDAQcBD4E"
				L"QQQ6BDIEMDEuMCwGBFUECWYeJAAoBD0EMARBBDUEOwRRBD0EPQRLBDkAIAQ/BEMEPQQ6BEIAKTEY"
				L"MBYGBFUECWceDgAoBEAEMAQ5BD4EPQApMAkGBSsOAwIdBQADggEBAEbtvGb/LSb6Asj0KZGy1LIH"
				L"17uZmE4sAGcx1n/u1z5S9KWRnhcKa8xcN4aONt6FPLJXiCUsow2T2yL1Ocwek0gSFVNKEzhXcU2w"
				L"OqYY0XsLKw5Al2iZ/XmPazRfx5e1GvpEvzAXWHsQDZbfvRx7g5pKdErc5XjU7kc3mXG3n6hst5Pi"
				L"GDcLA9QM8vZT65AX8mH+UdKnD72/gExX9EqIjWGmpxTb5yn4YoDmPgmNyY2SySZBzFlrNJnaVwg3"
				L"0njVH126bn6bYQMdGTbRryj+tRQEGR2WzHDvUWjzJogM+3Z1ORvXapbbxT6RrwR3v9kLH6YIObxM"
				L"eVwdK4PI36+Ru2A=");
			}
			else
			{
			return Util::FromBase64String(
				L"MIICYTCCAg4CAQAwgewxHzAdBgkqhkiG9w0BCQEWEHByaWhvZGtvQGZyc2QucnUxCzAJBgNVBAYT"
				L"AlJVMRUwEwYDVQQIHgwEHAQ+BEEEOgQyBDAxFTATBgNVBAceDAQcBD4EQQQ6BDIEMDERMA8GA1UE"
				L"Ch4IBB8EIAQhBBQxDTALBgNVBAseBAQYBCIxSzBJBgNVBAMeQgQfBEAEOARFBD4ENARMBDoEPgAg"
				L"BBAEOwQ1BDoEQQQwBD0ENARAACAEEAQ7BDUEOgRBBDAEPQQ0BEAEPgQyBDgERzEfMB0GA1UEDB4W"
				L"BB8EQAQ+BDMEQAQwBDwEPAQ4BEEEQjBjMBwGBiqFAwICEzASBgcqhQMCAiQABgcqhQMCAh4BA0MA"
				L"BEDH6dF5G2ACs9kW7UHsTy2WJRPJX0alvZM89Ew3/6BzjHoBHumImh2MqxuE5wrtXkAJNABSP09U"
				L"CIznuhdSy85SoIG0MIGxBgorBgEEAYI3AgEOMYGiMIGfMA4GA1UdDwEB/wQEAwIE8DAcBgkqhkiG"
				L"9w0BCQ8BAf8EDDAKMAgGBiqFAwICFTAdBgNVHSUEFjAUBggrBgEFBQcDAgYIKwYBBQUHAwQwUAYD"
				L"VR0gBEkwRzAJBgcqhQMDCGQBMAoGCCqFAwMIZAEBMAoGCCqFAwMIZAECMAoGCCqFAwMIZAEDMAoG"
				L"CCqFAwMIZAEEMAoGCCqFAwMIZAEFMAoGBiqFAwICAwUAA0EAPuTJL3qdgJKE1VcWsu2P7BLtOmfw"
				L"1opTS8GqFhK18WJFdempznMphxSk2s44Y4q+SNzJ+bchCMfnFZoOw14fKA==");
			}
		}

		inline static Blob CertificateTemplate()
		{
			return Util::FromBase64String(
				L"MIIFeDCCBGCgAwIBAgIKEWFYNwAAAAAA2jANBgkqhkiG9w0BAQUFADA+MRIwEAYKCZImiZPyLGQB"
				L"GRYCcnUxFDASBgoJkiaJk/IsZAEZFgRmcnNkMRIwEAYDVQQDEwlXaXJ0aDNDQTIwHhcNMDgwNTIy"
				L"MTcwOTE0WhcNMDkwNTIyMTcxOTE0WjB5MQswCQYDVQQGEwJSVTFJMEcGA1UEAwxA0J/RgNC40YXQ"
				L"vtC00YzQutC+INCQ0LvQtdC60YHQsNC90LTRgCDQkNC70LXQutGB0LDQvdC00YDQvtCy0LjRhzEf"
				L"MB0GCSqGSIb3DQEJARYQcHJpaG9ka29AZnJzZC5ydTBjMBwGBiqFAwICEzASBgcqhQMCAiQABgcq"
				L"hQMCAh4BA0MABEAU8+JpV6/vkjxvW/JQPx0fseENeb1gtIrZ8zCVDFl5isfpbu5TnmlR3uvSDTym"
				L"WkJPLaCZIR8sYN+KQRJnJ6Sfo4IC/DCCAvgwCwYDVR0PBAQDAgTwMBkGCSqGSIb3DQEJDwQMMAow"
				L"CAYGKoUDAgIVMB0GA1UdJQQWMBQGCCsGAQUFBwMCBggrBgEFBQcDBDAVBgNVHSAEDjAMMAoGCCqF"
				L"AwYCAQcBMIIBOAYDVR0HBIIBLzCCASukggEnMIIBIzEpMCcGCSqFAwYCAQYCAx4aBBAEOwQ1BDoE"
				L"QQQwBD0ENARABD4EMgQ4BEcxUDBOBgoqhQMGAgEGARQBHkAEIQQyBDgENAQ1BEIENQQ7BEwEQQRC"
				L"BDIEPgAgBD4AIAQyBD0ENQRBBDUEPQQ4BDgAIAQyACAEFQQTBCAELgQbMSEwHwYJKoUDBgIBBgIC"
				L"HhIEEAQ7BDUEOgRBBDAEPQQ0BEAxJDAiBgoqhQMGAgEGAhQBHhQEHwQwBEEEPwQ+BEAEQgAgBCAE"
				L"JDE4MDYGCiqFAwYCAQYBZAEeKAQgBD4EQQRBBDgEOQRBBDoEMARPACAEJAQ1BDQENQRABDAERgQ4"
				L"BE8xITAfBgkqhQMGAgEGAgEeEgQfBEAEOARFBD4ENARMBDoEPjAdBgNVHQ4EFgQUti59rLDJ5KKD"
				L"yuyM7d4GNjzWsRQwHwYDVR0jBBgwFoAU8ys9LwKuq9/jzNrkshgHhHFU2gkwcQYDVR0fBGowaDBm"
				L"oGSgYoYuaHR0cDovL3dpcnRoMy5mcnNkLnJ1L0NlcnRFbnJvbGwvV2lydGgzQ0EyLmNybIYwZmls"
				L"ZTovL1xcd2lydGgzLmZyc2QucnVcQ2VydEVucm9sbFxXaXJ0aDNDQTIuY3JsMIGoBggrBgEFBQcB"
				L"AQSBmzCBmDBJBggrBgEFBQcwAoY9aHR0cDovL3dpcnRoMy5mcnNkLnJ1L0NlcnRFbnJvbGwvd2ly"
				L"dGgzLmZyc2QucnVfV2lydGgzQ0EyLmNydDBLBggrBgEFBQcwAoY/ZmlsZTovL1xcd2lydGgzLmZy"
				L"c2QucnVcQ2VydEVucm9sbFx3aXJ0aDMuZnJzZC5ydV9XaXJ0aDNDQTIuY3J0MA0GCSqGSIb3DQEB"
				L"BQUAA4IBAQBWCQRx9MdjZs1xEOh872XsD2V2GwyNi8qmz7wcxOhqVOhaZ4CBgv5TQGXsZs0ekDZp"
				L"CSCSMdkjItXozxp2fX7mhyoMXjkcJ6CaEbP+kvII467CJx0WMxIXPoHJ7r5wO3VWxqJUldbvypRk"
				L"0hBr6BObUcVatzbOyyvqNT+neEzSNXXBVvXUhOQmJxJls5i8zHX2l87oSS52ZbpuMn9qkx8XwWfp"
				L"RYRxILvlAYJ0itjaZj9aJtcz4l4wIAFkSvvyEm/04evOheGc1d59vTcCtkfpDUeznWfX2WfidMmq"
				L"ZJkDE0cuvieYfNyort8pmZrRMp/Xu5hSuOAdIz1pgYcw/0ZA");
		}





		//AsnObject(XmlElement E)
		//{
		//	Load(E);
		//}

		//AsnObject Load(XmlElement E)
		//{
		//	return Load(E,true);
		//}

		//TextMap m_XmlTags;

		//TextMap m_XmlNs;

		//AsnObject& Load(XmlElement E,bool isRoot)
		//{
		//	m_IndefiniteLength = false;
		//	//
		//	m_XmlTags = new Hashtable();
		//	m_XmlNs = new Hashtable();
		//	//
		//	LoadXmlTags(E);
		//	//
		//	AsnObject result_O = this;
		//	//
		//	m_AsnClass = UNIVERSAL;
		//	m_IsConstructed = true;
		//	m_Tag = SEQUENCE;
		//	//
		//	AsnObject O = null;
		//	if (isRoot)
		//	{
		//		AsnObject meta_o = AsnObject.NewSequence;
		//		AsnObject tags_o = AsnObject.NewSet;
		//		foreach (DictionaryEntry entry in m_XmlTags)
		//		{
		//			AsnObject tag_o = AsnObject.NewSequence;
		//			tag_o.Add(new AsnObject((int)entry.Value)).Add(new AsnObject((string)entry.Key));
		//			tags_o.Add(tag_o);
		//		}
		//		AsnObject nss_o = AsnObject.NewSet;
		//		foreach (DictionaryEntry entry in m_XmlNs)
		//		{
		//			AsnObject ns_o = AsnObject.NewSequence;
		//			ns_o.Add(new AsnObject((int)entry.Value)).Add(new AsnObject((string)entry.Key));
		//			nss_o.Add(ns_o);
		//		}
		//		meta_o.Add(nss_o).Add(tags_o);
		//		//
		//		O = AsnObject.NewSequence;
		//		//
		//		// result_O.m_AsnClass = CONTEXT_SPECIFIC;
		//		result_O.Add(new AsnObject("XML")).Add(meta_o).Add(O);
		//	}
		//	else
		//	{
		//		O = result_O;
		//	}
		//	//
		//	O.Add(new AsnObject((int)m_XmlTags[E.LocalName]))
		//		.Add(new AsnObject(E.LocalName));
		//	//
		//	O.Add(new AsnObject((int)m_XmlNs[E.NamespaceURI]))
		//		.Add(new AsnObject(E.NamespaceURI));
		//	//
		//	AsnObject attrs_O = AsnObject.NewSet;
		//	XmlNodeList L = E.SelectNodes("attribute::*");
		//	for (int i = 0; i < L.Count; ++i)
		//	{
		//		XmlAttribute A = (XmlAttribute)L[i];
		//		attrs_O.Add(AsnObject.NewSequence
		//			.Add(new AsnObject((int)m_XmlTags[A.LocalName]))
		//			.Add(new AsnObject((int)m_XmlNs[A.NamespaceURI]))
		//			.Add(new AsnObject(A.Value))
		//			);
		//	}
		//	O.Add(attrs_O);
		//	//
		//	AsnObject children_O = AsnObject.NewSet;
		//	L = E.SelectNodes("*");
		//	for (int k = 0; k < L.Count; ++k)
		//	{
		//		XmlNode child = L[k];
		//		if (child.NodeType == XmlNodeType.Text)
		//		{
		//			children_O.Add(new AsnObject(((XmlText)child).Value));
		//		}
		//		else if (child.NodeType == XmlNodeType.Element)
		//		{
		//			AsnObject o1 = new AsnObject(true,UNIVERSAL,SEQUENCE);
		//			o1.Load((XmlElement)child,false);
		//			children_O.Add(o1);
		//		}
		//	}
		//	O.Add(children_O);
		//	//
		//	return result_O;
		//}

		//void LoadXmlTags(XmlElement E)
		//{
		//	int k;
		//	//
		//	string name = E.LocalName;
		//	string ns = E.NamespaceURI;
		//	//
		//	m_XmlTags[name] = name.GetHashCode();
		//	m_XmlNs[ns] = ns.GetHashCode();
		//	//
		//	XmlNodeList L = E.SelectNodes("attribute::*");
		//	for (k = 0; k < L.Count; ++k)
		//	{
		//		XmlAttribute A = (XmlAttribute)L[k];
		//		name = A.LocalName;
		//		ns = A.NamespaceURI;
		//		m_XmlTags[name] = name.GetHashCode();
		//		m_XmlNs[ns] = ns.GetHashCode();
		//	}
		//	//
		//	L = E.SelectNodes("*");
		//	for (k = 0; k < L.Count; ++k)
		//	{
		//		LoadXmlTags((XmlElement)L[k]);
		//	}
		//}
	};






	// =======================================================================================
	// NameDescription 

	// *** �����, �������������� ������ Certificate Name, ������� ���������:
	//
	// Sequence
	//     Set
	//         Sequence
	//             OID
	//             Value		(AI5String, PrintableString, UTF8String, UnicodeString)
	//     ...

	struct NameDescription
	{
		SharedPtr<AsnObject> m_spObject;
			
		NameDescription()
		{
			m_spObject = SharedPtr<AsnObject>( new AsnObject(AsnObject::NewSequence()) );
		}

		static NameDescription Null() 
		{
			return NameDescription();
		}

		NameDescription(AsnObject& o)
		{
			m_spObject = new AsnObject(o);
		}

		AsnObject& operator [](string oidStr)
		{
			return P_Attribute(*this,OID(oidStr));
			//return (*this)[OID(oidStr)];
		}

		struct P_Attribute
		{
			NameDescription& m_parent;

			OID m_oid;

			P_Attribute(NameDescription& parent,OID oid) : m_parent(parent), m_oid(oid)
			{
			}

			operator AsnObject&()
			{
				SharedPtr<AsnObject> a = m_parent.GetAttribute(m_oid);
				if (a.GetPointee() == 0)
					throw MethodError(L"ASN Error: Not found");
				//
				return *( a.GetPointee() );
			}

			const AsnObject& operator =(const AsnObject& value)
			{
				m_parent.SetAttribute(m_oid,value);
				return value;
			}
		};

		P_Attribute operator [](OID oid)
		{
			return P_Attribute(*this,oid);
		}

		SharedPtr<AsnObject> GetAttribute(OID oid)
		{
			for (int i = 0; i < m_spObject->Children.Length(); ++i)
			{
				//							AsnObject o = m_object[i].Tagged(0);
				//							if (! o.ObjectId.IsNull)
				//							{
				//								if (o.ObjectId == oid)
				//								{
				//									return o[1].Tagged(0)[0];
				//								}
				//							}
				AsnObject o = ( (AsnObject&)(*( m_spObject.GetPointee() ))[i] )[0];
				if (! o.ObjectId().IsNull())
				{
					if (o.ObjectId() == oid)
					{
						return new AsnObject(o[1]);
					}
				}
			}
			return SharedPtr<AsnObject>();
		}

		void SetAttribute(OID oid,const AsnObject& value)
		{
			bool found = false;
			for (int i = 0; i < m_spObject->Children.Length(); ++i)
			{
				AsnObject& o = ( (AsnObject&)(*( m_spObject.GetPointee() ))[i] )[0];
				if (! o.ObjectId().IsNull())
				{
					if (o.ObjectId() == oid)
					{
						AsnObject& o1 = o[1];
						o1 = AsnObject(value);
						found = true;
					}
				}
			}
			if (! found)
			{
				m_spObject->Add(
					AsnObject::NewSet().Add(
					AsnObject::NewSequence().Add(AsnObject(oid)).Add(value)
					)
				);
			}
		}

		NameDescription Add(OID oid,AsnObject v)
		{
			(*this)[oid] = v;
			return *this;
		}

		NameDescription Add(OID oid,string v)
		{
			(*this)[oid] = AsnObject(v,oid);
			return *this;
		}

		NameDescription& Add(string oidStr,string v)
		{
			OID oid(oidStr);
			(*this)[oid] = AsnObject(v,oid);
			////Runtime.Echo(m_object.Dump);
			return *this;
		}

		NameDescription& RemoveAll()
		{
			m_spObject->RemoveAllChildren();
			return *this;
		}

		string Text()
		{
			string text = L"";
			for (int i = 0; i < m_spObject->ChildCount(); ++i)
			{
				AsnObject& o = (*( m_spObject.GetPointee() ))[i];
				OID childOid = ((AsnObject&)o[0]).ObjectId();
				//
				if (! childOid.IsNull())
				{
					AsnObject& v = ((AsnObject&)o[0])[1];
					Util::AddText(&text,
						L"OID."+string(((AsnObject&)o[0]).ObjectId())+L": "+v.Dump()+L"\r\n");
				}
			}
			return text;
		}

		AsnObject& AsnObj() 
		{
			return *m_spObject.GetPointee();
		}
	};

	inline static string PrepareClientId(SharedArray<string> clientOids)
	{
		try
		{
			stringArray a;
			a.Allocate(clientOids.Length());
			for (int k = 0; k < clientOids.Length(); ++k) a[k] = clientOids[k];
			stringArray sortedClientOids = ::Algorithms::Alg_1_8_4().Sort(a);
			//
			string clientIdText = L"";
			for (int k = 0; k < sortedClientOids.Length(); ++k)
			{
				clientIdText += (string)sortedClientOids[k] + L"\n";
			}
			return clientIdText;
		}
		_FCatch()
	}

	inline static string PrepareClientId(NameDescription& subjectD)
	{
		try
		{
			SharedArray<string> clientOids;
			//
			for (X500::OidMap::Iterator i(X500::Oids()); i; ++i)
			{
				string alias = i.Id();
				string oid = i;
				string v;
				if (alias.Left(9) == L"_PKI_")
				{
					SharedPtr<AsnObject> attr = subjectD.GetAttribute(OID(oid));
					if (! attr.IsEmpty()) v = attr->m_text;
					else v = L"";
					//
					bool use = v.GetLength() > 0;
					use = use && (StartsWith(CString(oid),_T("1.2.643.6.2.1.6")));
					//
					if (use)
					{
						string item = oid + L"=" + v;
						clientOids.Add(item);
					}
				}
			}
			//
			return PrepareClientId(clientOids);
		}
		_FCatch()
	}






	//struct CertRequest
	//{
	//	//Hashtable m_Attributes;

	//	//public Hashtable Attributes
	//	//{
	//	//	get
	//	//	{
	//	//		if (m_Attributes == null) m_Attributes = new Hashtable();
	//	//		//
	//	//		return m_Attributes;
	//	//	}
	//	//}

	//	//public object this[string name]
	//	//{
	//	//	get
	//	//	{
	//	//		return (string)Attributes[(object)name];
	//	//	}
	//	//	set
	//	//	{
	//	//		Attributes[(object)name] = value;
	//	//	}
	//	//}

	//	//public byte[] Request
	//	//{
	//	//	get
	//	//	{
	//	//		return new byte[1];
	//	//	}
	//	//}

	//	inline static Blob PersonalRequestTemplate()
	//	{
	//		get
	//		{
	//			return Slot::Util::FromBase64String(
	//				L"MIICYTCCAg4CAQAwgewxHzAdBgkqhkiG9w0BCQEWEHByaWhvZGtvQGZyc2QucnUxCzAJBgNVBAYT"
	//				L"AlJVMRUwEwYDVQQIHgwEHAQ+BEEEOgQyBDAxFTATBgNVBAceDAQcBD4EQQQ6BDIEMDERMA8GA1UE"
	//				L"Ch4IBB8EIAQhBBQxDTALBgNVBAseBAQYBCIxSzBJBgNVBAMeQgQfBEAEOARFBD4ENARMBDoEPgAg"
	//				L"BBAEOwQ1BDoEQQQwBD0ENARAACAEEAQ7BDUEOgRBBDAEPQQ0BEAEPgQyBDgERzEfMB0GA1UEDB4W"
	//				L"BB8EQAQ+BDMEQAQwBDwEPAQ4BEEEQjBjMBwGBiqFAwICEzASBgcqhQMCAiQABgcqhQMCAh4BA0MA"
	//				L"BEDH6dF5G2ACs9kW7UHsTy2WJRPJX0alvZM89Ew3/6BzjHoBHumImh2MqxuE5wrtXkAJNABSP09U"
	//				L"CIznuhdSy85SoIG0MIGxBgorBgEEAYI3AgEOMYGiMIGfMA4GA1UdDwEB/wQEAwIE8DAcBgkqhkiG"
	//				L"9w0BCQ8BAf8EDDAKMAgGBiqFAwICFTAdBgNVHSUEFjAUBggrBgEFBQcDAgYIKwYBBQUHAwQwUAYD"
	//				L"VR0gBEkwRzAJBgcqhQMDCGQBMAoGCCqFAwMIZAEBMAoGCCqFAwMIZAECMAoGCCqFAwMIZAEDMAoG"
	//				L"CCqFAwMIZAEEMAoGCCqFAwMIZAEFMAoGBiqFAwICAwUAA0EAPuTJL3qdgJKE1VcWsu2P7BLtOmfw"
	//				L"1opTS8GqFhK18WJFdempznMphxSk2s44Y4q+SNzJ+bchCMfnFZoOw14fKA==");
	//		}
	//	}

	//	//public byte[] SignedRequest(CCOM.CCOMKey key)
	//	//{
	//	//	byte[] data = new byte[1024];
	//	//	return data;
	//	//}
	//};













	inline AsnObject::P_Subject::operator NameDescription() 
	{
		AsnObject& o = m_parent.SubjectObject;
		// if (o == null) return null; // TODO: SubjectObject ������ Null? 
		return NameDescription(o);
	}

	inline NameDescription& AsnObject::P_Subject::operator =(NameDescription& value)
	{
		m_parent.SubjectObject = value.AsnObj(); 
		return value;
	}

	inline AsnObject& AsnObject::SetSubject(NameDescription v)
	{
		Subject = v;
		return *this;
	}

	inline AsnObject& AsnObject::SetSubjectAltName(NameDescription v)
	{
		SubjectAltName = v;
		return *this;
	}

	inline AsnObject::P_SubjectAltName::operator NameDescription()
	{
		AsnObject& o = m_parent.SubjectAltNameObject;
		//// TODO: !!!
		//// if (SubjectAltNameObject.IsNull()) return null;
		//AsnObject o(true,UNIVERSAL,((AsnObject&)m_parent.SubjectAltNameObject).Tag());
		//int n = ((AsnObject&)m_parent.SubjectAltNameObject).ChildCount();
		//for (int j = 0; j < n; ++j)
		//{
		//	o.Add(((AsnObject&)m_parent.SubjectAltNameObject)[n-1-j]);
		//}
		return NameDescription(o);
	}

	inline NameDescription& AsnObject::P_SubjectAltName::operator =(NameDescription& value) 
	{
#ifdef _DEBUG
		{
			///OutputDebugStringW(m_parent.Dump() + L"\n"); 
		}
#endif
		//
		m_parent.SubjectAltNameObject = AsnObject(true,UNIVERSAL,value.AsnObj().Tag());
		//
#ifdef _DEBUG
		{
			///OutputDebugStringW(m_parent.Dump() + L"\n"); 
		}
#endif
		//
		for (int j = 0; j < value.AsnObj().ChildCount(); ++j)
		{
			AsnObject& AltName = (AsnObject&)m_parent.SubjectAltNameObject;
			// TRACE_LOG(AltName.Dump());
			AltName.Add(value.AsnObj()[value.AsnObj().ChildCount()-1-j]);
		}
		return value;
	}	




}
