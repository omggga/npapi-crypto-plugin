/*
 SmartPKI.h : PKI-�������������� ����.

 $Name:  $
 $Revision: 1.1.2.2 $
 $Date: 2008/10/10 15:38:07 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

// 
//
#include "../_cpp/SlotUtil.h"
#include "../_cpp/SlotAsn.h"
#include "SmartUtil.h"
#include "SmartUri.h"
#include "SmartXml.h"
#include "../alg/Alg_1_8_2.h"

namespace  {



	// ===========================================================================================
	// PKCS#11 

	// ��������������� ������ eToken PKCS11 API
	
	class PKI 
	{
	public:
		static string& RequestInfoHeaderTemplate()
		{
			static string t;
			//
			if (t.GetLength() == 0) // http://cabinet.example.com
			{
				t = L"<?xml version=\"1.0\" ?>\n"
					L"<?xml-stylesheet type=\"text/xsl\" href=\"/protocol/-cert-request.xsl\" ?>"
					;
			}
			//
			return t;
		}

		static string& RequestInfoTemplate()
		{
			static string t;
			//
			if (t.GetLength() == 0)
			{
				t = RequestInfoHeaderTemplate() +
					L"<RequestInfo>\n"
					L"<CertificateInfo xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n"
					L"</CertificateInfo>\n"
					L"</RequestInfo>"
					;
			}
			//
			return t;
		}

		inline static XmlElement NewCertItem(XmlElement Info_E, string xsi_type)
		{
			XmlElement CertItem_E = Info_E.OwnerDocument().CreateElement(L"",L"CertItem",L"");
			CertItem_E.SetAttribute(L"xsi:type", xsi_type);
			Info_E.AppendChild(CertItem_E);
			return CertItem_E;
		}

		inline static XmlElement NewAttributeElement(XmlElement CertItem_E, string name, string value)
		{
			XmlElement Attribute_E = CertItem_E.OwnerDocument().CreateElement(L"",L"Attribute",L"");
			Attribute_E.SetAttribute(L"name",name);
			Attribute_E.InnerText() = value;
			CertItem_E.AppendChild(Attribute_E);
			return Attribute_E;
		}

		inline static XmlDocument GetRequestInfo(AsnObject& requestO,AsnObject& requestExtra)
		{
			try
			{
				XmlDocument doc;
				doc.LoadXml(RequestInfoTemplate());
				//
				XmlElement CertInfo_E = doc.DocumentElement().SelectSingleNode(L"CertificateInfo");
				//
				Blob pk = requestO.CP_GOST2001PublicKeyBits;
				Algorithms::Alg_1_8_2 a2;
				string pkh64 = a2.Encode(pk);
				Blob pkh = FromBase64String(pkh64);
				pkh64 = __ToBase64(pkh);
				CertInfo_E.SetAttribute(L"PubKeyHash",pkh64);
				CertInfo_E.SetAttribute(L"PubKeyHashUrlEnc",
					UrlEncode(Base64Text_4Url(pkh64)) 
					);
				//
				string pkValueText;
				for (int j = 0; j < pk.Length(); ++j)
				{
					if (j > 0) pkValueText += " ";
					string v = FormatStr(L"%02x", (int)(pk[pk.Length()-1-j]) );
					pkValueText += v;
				}
				CertInfo_E.SetAttribute(L"PubKeyText",pkValueText);
				//
				AsnObject r_0 = requestO[0];
				AsnObject r_0_2 = r_0[2];
				AsnObject r_0_2_0 = r_0_2[0];
				//
				string pkOid = ((AsnObject&)r_0_2_0[0]).m_Oid;
				CertInfo_E.SetAttribute(L"PubKeyOid",pkOid);
				//
				AsnObject r_0_2_0_1 = r_0_2_0[1];
				string pkParamText;
				for (int i = 0; i < r_0_2_0_1.ChildCount(); ++i)
				{
					if (i > 0) pkParamText += L", ";
					pkParamText += string( ((AsnObject&)r_0_2_0_1[i]).m_Oid );
				}
				CertInfo_E.SetAttribute(L"PubKeyParamText",pkParamText);
				//
				// Subject
				//
				XmlElement Subject_E = NewCertItem(CertInfo_E,L"CertSubject");
				XmlElement Issuer_E = NewCertItem(CertInfo_E,L"CertIssuer");
				XmlElement Policies_E = NewCertItem(CertInfo_E,L"CertPolicies");
				//
				//TRACE_LOG(requestO.Dump());
				NameDescription subject = requestO.Subject;
				NameDescription subjectAltName = requestO.SubjectAltName;
				//
				for (X500::OidMap::Iterator i(::X500::Oids()); i; ++i)
				{
					string alias = i.Id();
					if (true)
					{
						string oid = i;
						//
						SharedPtr<AsnObject> spAttr = subject.GetAttribute(OID(oid));
						if (! spAttr.IsEmpty())
						{
							NewAttributeElement(Subject_E,L"oid."+oid,spAttr->m_text);
						}
					}
				}
				//
				for (X500::OidMap::Iterator i(X500::Oids()); i; ++i)
				{
					string alias = i.Id();
					if (alias.Left(9) == L"_PKI_")
					{
						string oid = i;
						//
						SharedPtr<AsnObject> spAttr = subjectAltName.GetAttribute(OID(oid));
						if (! spAttr.IsEmpty())
						{
							NewAttributeElement(Subject_E,L"oid."+oid,spAttr->m_text);
						}
					}
				}
				//
				if (requestExtra.Tag() == AsnObject::SEQUENCE)
				if (requestExtra.ChildCount() >= 2)
				{
					//for (int k = 0; k < requestExtra.ChildCount(); k++)
					//{
					//	AsnObject& itemO = requestExtra[k]; 
					//	//
					//	AsnObject& itemOs = itemO[0]; 
					//	//
					//	OID oid = ((AsnObject&)itemOs[0]).m_Oid; 
					//	string text = ((AsnObject&)itemOs[1]).m_text; 
					//	//
					//	NewAttributeElement(Subject_E, L"oid."+(string)oid, text);
					//}
					//
					//NameDescription subjectExtraInfo(requestExtra[1]);
					//
					AsnObject& attrO = requestExtra[1]; 
					//
					for (int i = 0; i < attrO.Children.Length(); ++i)
					{
						AsnObject o = ( (AsnObject&)(attrO)[i] )[0];
						if (! o.ObjectId().IsNull())
						{
							OID oid = o.ObjectId(); 
							string text = AsnObject(o[1]).m_text; 
							NewAttributeElement(Subject_E, L"oid."+(string)oid, text);
						}
					}
					//
					//for (X500::OidMap::Iterator i(X500::Oids()); i; ++i)
					//{
					//	string alias = i.Id();
					//	if (alias.Left(9) == L"_PKI_")
					//	{
					//		string oid = i;
					//		//
					//		SharedPtr<AsnObject> spAttr = subjectExtraInfo.GetAttribute(OID(oid));
					//		if (! spAttr.IsEmpty())
					//		{
					//			NewAttributeElement(Subject_E,L"oid."+oid,spAttr->m_text);
					//		}
					//	}
					//}
				}
				//
	#			ifdef _DEBUG
				//TRACE_LOG(doc.DocumentElement().OuterXml());
	#			endif
				return doc;
			}
			_Catch()
		}



		inline static string LocalTimeToTimeStr(const COleDateTime& t) 
		{
			try
			{
				SYSTEMTIME st;
				t.GetAsSystemTime(st);
				//
				TIME_ZONE_INFORMATION timeZoneInformation; 
				GetTimeZoneInformation(&timeZoneInformation); 
				//
				SYSTEMTIME ut; 
				//
				TzSpecificLocalTimeToSystemTime(
					&timeZoneInformation,
					&st, &ut); 
				//
				string t_s_1 = FormatStr(L"%04d-%02d-%02d", (int)ut.wYear, (int)ut.wMonth, (int)ut.wDay );
				string t_s_2 = FormatStr(L"T%02d:%02d:%02dZ", (int)ut.wHour, (int)ut.wMinute, (int)ut.wSecond );
				//
				string t_s = t_s_1 + t_s_2; 
				//
				return t_s; 
			}
			_Catch() 
		}






		// ----
		// Registry 

		inline static CString GetRegRoot()  
		{
			try
			{
				CString s = _S("Software\\") + _S(__REGISTRY_NAME) + _T("\\") + _S(_CABINET_NAME); 
				return s;
			}
			_Catch()
		}

		inline static string GetOption(const string& name)
		{
			try
			{
				string o_Registry;
				string o_XmlConfig;
				string o_Default;
				//
				// Registry
				//
				try
				{
					CString regPath = _T("\\Settings");
					//
					HKEY root1 = HKEY_LOCAL_MACHINE;
					//
					HRESULT rc = S_OK;
					o_Registry = Machine::GetRegStringValue(root1,regPath,_S(name),false,&rc);
					//
					if (o_Registry.GetLength() == 0)
					{
						if (root1 == HKEY_CURRENT_USER)
						{
							HKEY root2 = HKEY_LOCAL_MACHINE; 
							o_Registry = Machine::GetRegStringValue(root2,regPath,_S(name),false,&rc);
						}
					}
				}
				catch(...)
				{
					o_Registry = L"";
				}
				//
				// Result
				//
				if (o_Registry.GetLength() > 0) return o_Registry;
				//
				if (o_XmlConfig.GetLength() > 0) return o_XmlConfig;
				//
				return o_Default;
			}
			_Catch()
		}

		inline int GetOptionAsInteger(const string& name)
		{
			try
			{
				const int defaultIntegerValue = 0;
				const int emptyIntegerValue = 0;
				//
				try
				{
					if (name == L"") return emptyIntegerValue;
					//
					string s = GetOption(name);
					int v = _wtoi(s);
					return v;
				}
				catch(...)
				{
				}
				//
				return defaultIntegerValue;
			}
			_Catch()
		}
	};
}
