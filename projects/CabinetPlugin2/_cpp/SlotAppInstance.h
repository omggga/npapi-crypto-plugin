/*
 SlotAppInstance.h : ����������, �������� � ����� ������������. 

 ������ <--> ����������.

 $Name:  $
 $Revision: 1.1.2.6 $
 $Date: 2009/05/26 08:33:18 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


#include "../low-level/SmartMachine.h"
#include "../low-level/SmartUtil.h"
#include "../low-level/SmartUri.h"
#include "../low-level/SmartDeviceInfo.h"
#include "../low-level/SmartPKI.h"
#include "../low-level/SmartOC.h"
#include "../ax/interfaces/ISlotClient.h"
////#include <ax/coclasses/AX_SlotClient.h>
//
#include "SlotSysUtil.h"
#include "SlotCSP_CCOM.h"
#include "SlotXmlCtx.h"
//
#include "../PKI.h"


namespace  {

	static const int InstanceType_User = 1;
	static const int InstanceType_Machine = 2;

	// %%%%
	// ������ ������� ������ �������

	template<
		class _InstanceBase,
		class _ApplicationCtx,
		int _InstanceType=InstanceType_User
	>
	class InstanceCtx : 
		public XmlContext, 
		public SimpleErrorHandling<_InstanceBase> 
	{
	public:
		typedef _ApplicationCtx ApplicationCtx;

		typedef _InstanceBase Base;

		static const int InstanceType = _InstanceType; 

		// ----
		// ���������� 

		inline static ApplicationCtx& GetApplication() 
		{
			static ApplicationCtx s_App; 
			return s_App; 
		}

		inline ApplicationCtx& Application() 
		{
			return GetApplication(); 
		}

		// ----
		// �����

		inline HKEY GetRegRootKey()
		{
			HKEY hKey = NULL;
			//
			if (_InstanceType == InstanceType_Machine)
			{
				hKey = HKEY_LOCAL_MACHINE; 
			}
			else if (_InstanceType == InstanceType_User)
			{
				hKey = HKEY_CURRENT_USER; 
			}
			//
			return hKey;
		}

		CString GetRegRoot() 
		{
			return _InstanceBase::GetRegRoot(); 
		}

		inline string GetOption(const string& name)
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
					CString regPath = GetRegRoot() + _T("\\Settings");
					//
					HKEY root1 = GetRegRootKey();
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
				// XmlConfig
				//
				try
				{
					o_XmlConfig = GetAttribute(name);
				}
				catch(...)
				{
					o_XmlConfig = L"";
				}
				//
				// Default
				//
				try
				{
					o_Default = GetDefaultOptionValue(name);
				}
				catch(...)
				{
					o_Default = L"";
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

		virtual string GetDefaultOptionValue(const string& name) 
		{
			return L""; 
		}



		// ----
		// ��������������� ��������

		inline static const string& Get_aXslUrl() { static string s = aXslUrl; return s; } 



		// ----
		// ��������� ���������� � URL 

		// �������� ����� ������� ������ ������� �� ����� 

		inline CString Home()
		{
			try
			{
				CString d0 = Util::CreateDirectoryAndTest( Util::GetAppDataFolder() + _T("\\") + _APP_DIR );
				if (d0.GetLength() == 0) throw MethodError(E__FILTER_CANNOT_GET_RESOURCE);
				//
				CString dir = Util::CreateDirectoryAndTest( d0 + _T("\\") + _CABINET_APP_DIR );
				if (dir.GetLength() == 0) throw MethodError(E__FILTER_CANNOT_GET_RESOURCE);
				return dir;
			}
			_Catch()
		}

		// ���� ��� URL, ����������� �� ��������� web-������� �������: XSL, ... 

		virtual string CommonUrlBase() // default : ������ ������ 
		{
			return L""; 
		}

		// ����� ��� ��������� ������ 

		inline CString Temp()
		{
			try
			{
				CString dir = Util::CreateDirectoryAndTest( Home() + _T("\\Temp") );
				if (dir.GetLength() == 0) throw MethodError(E_ACCESSDENIED);
				return dir; 
			}
			_Catch()
		}

		// �����, � ������� ��������� ��������� ����� ��� ��������� ������������ ��������� 

		inline CString TempDocs()
		{
			try
			{
				CString dir = Util::CreateDirectoryAndTest( Temp() + _T("\\Documents") );
				if (dir.GetLength() == 0) throw MethodError(E_ACCESSDENIED);
				//
				// �������������� �������� 
				//
				// Raw:
				CString d = Util::CreateDirectoryAndTest( dir + _T("\\Raw") );
				//
				return dir; 
			}
			_Catch()
		}































			// ===================================================================================
			// SecurityHandler

		public:
			////Certificate certificate; 

			inline static string RCXml(HRESULT rc,const string& description)
			{
				string xml_t = L"<?xml version=\"1.0\" ?>\n"
						L"<hr value=\"0x%x\" service-name=\"Protocol\">\n"
						L"%s\n</hr>"
						;
				string xml = FormatStr(xml_t, (int)rc, description.GetString() ); 
				//
				return xml;
			}

			static string& DriveInfoTemplate()
			{
				static string t;
				//
				if (t.GetLength() == 0)
				{
					t = L"<?xml version=\"1.0\" ?>\n"
						L"<DriveInfo>\n"
						L"</DriveInfo>"
						;
				}
				//
				return t;
			}

			static string& DeviceInfoTemplate(bool useXsl=true)
			{
				static string t;
				//
				if (t.GetLength() == 0)
				{
					t = L"<?xml version=\"1.0\" ?>\n"
						L"<DeviceInfo>\n"
						L"</DeviceInfo>"
						;
				}
				//
				return t;
			}

			static string& CommonKeyInfoTemplate(bool useXsl=true)
			{
				static string t;
				//
				if (true) // (t.GetLength() == 0)
				{
					t = L"<?xml version=\"1.0\" ?>\n";
					if (useXsl)
					{
						string xslBase = L""; // _W(L"http://") + _W(_PROTOCOL_DEFAULT_HOST); 
						t += L"<?xml-stylesheet type=\"text/xsl\" href=\"" + xslBase + L"/protocol/-protocol.xsl\" ?>";
					}
					//
					t +=
						L"<CommonKeyInfo xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n"
						L"</CommonKeyInfo>"
						;
				}
				//
				return t;
			}
			




			//string m_ClientPkh;

			//void SetActivePkh(const string& pkh64)
			//{
			//	try
			//	{
			//		ActivatePkh(pkh64);
			//	}
			//	_Catch()
			//}

//			bool ActivatePkh(const string& pkh64)
//			{
//				try
//				{
//					XmlDocument CommonKeyInfo = GetCommonKeyInfo(string(pkh64));
//					//
//#					ifdef _DEBUG
//					///OutputDebugString(_S(CommonKeyInfo.OuterXml())); 
//#					endif
//					//
//					XmlNodeList KeyInfo_L = CommonKeyInfo.DocumentElement().SelectNodes(
//						L"KeyInfo[CertificateInfo]");
//					//
//					bool keyFound = false;
//					for (int k = 0; k < KeyInfo_L.Count() && (! keyFound); ++k)
//					{
//						XmlElement KeyInfo_E = (XmlElement)KeyInfo_L[k];
//						//
//						CString keyPath = _S(KeyInfo_E.GetAttribute(L"KeyPath"));
//						//
//						// ��������� ���������� � �����
//						//
//						SharedArray<CString> pkXmlPaths = Machine::ListFiles(keyPath,_T("*-k.xml"));
//						if (pkXmlPaths.Length() > 0) 
//						{
//							CString pkXmlPath = pkXmlPaths[0];
//							//
//#							ifdef _DEBUG
//							///OutputDebugString(_S(KeyInfo_E.OuterXml())); 
//#							endif
//							//
//							Blob certData = FromBase64String(
//								((XmlElement)KeyInfo_E.SelectSingleNode(L"CertificateInfo")).InnerText()
//								);
//							//
//							// CCOM:
//							//
//							CCOM_Certificate cert;
//							cert->Import(certData);
//							//
//							CString keyInfoPath = pkXmlPath;
//							CString keyContainerPath = keyPath + _T("\\Container");
//							//
//							CCOM_Key key;
//							XmlDocument d;
//							d.Load((string)keyInfoPath);
//							key->SetPath(keyContainerPath);
//							key->SetXmlInfo(d.DocumentElement());
//							cert->SetKey(key);
//							//
//							m_ClientPkh = ToBase64(cert->GetPKH()); 
//							//
//							certificate = cert;
//							keyFound = true;
//							return true; // ������! 
//						}
//					}
//					return false;
//				}
//				_Catch()
//			}

			XmlElement CreateKeyInfo(
				XmlDocument doc,
				const string& cryptoSystem,
				const string& keyMediaType 
				)
			{
				XmlElement keyInfo = doc.CreateElement(L"",L"KeyInfo",L"");
				//
				keyInfo.SetAttribute(L"CryptoSystem",cryptoSystem);
				keyInfo.SetAttribute(L"KeyMediaType",keyMediaType);
				//
				return keyInfo;
			}

			void ByteToStr(
				 DWORD cb, 
				 void* pv, 
				 LPSTR sz)

			{
				try
				{
					//-------------------------------------------------------------------
					// Parameters passed are:
					//    pv -- the Array of BYTES to be converted.
					//    cb -- the number of BYTEs in the array.
					//    sz -- a pointer to the string to be returned.
					//
					//-------------------------------------------------------------------
					//  Declare and initialize local variables.
					//
					BYTE* pb = (BYTE*) pv; // local pointer to a BYTE in the BYTE array
					DWORD i;               // local loop counter
					int b;                 // local variable
					//
					//  Ensure that sz is large enough to hold pv.
					if (strlen(sz) < cb)
					{
						throw MethodError(L"The array of bytes is too long for the allocated string."); 
					}
					//
					//-------------------------------------------------------------------
					//  Begin processing loop.
					//
					for (i = 0; i < cb; i++)
					{
					   b = (*pb & 0xF0) >> 4;
					   *sz++ = (b <= 9) ? b + '0' : (b - 10) + 'A';
					   b = *pb & 0x0F;
					   *sz++ = (b <= 9) ? b + '0' : (b - 10) + 'A';
					   pb++;
					   *sz++ = ' ';
					}
					*sz++ = 0;
				}
				_Catch() 
			}  



			inline string FastRDNString(CERT_RDN_ATTR& attr) 
			{
				try
				{
					string s; 
					//
					Blob data; 
					data.Allocate(attr.Value.cbData); 
					CopyMemory(data.GetBuffer(), attr.Value.pbData, attr.Value.cbData); 
					//
					//CBlobW w;
					//w.Allocate(attr.Value.cbData * 4 + 6); 
					//ZeroMemory(w.GetBuffer(), w.Length()/sizeof(wchar_t)); 
					////
					//ByteToStr(attr.Value.cbData, attr.Value.pbData, w.GetBuffer()); 
					//
					AsnObject o1(data);
					////OutputDebugStringW(o1.Dump()); 
					s = AsnObject::ReadBMPString(data, 0, data.Length()); 
					//
					if (attr.dwValueType == CERT_RDN_BMP_STRING)
					{
						s = AsnObject::ReadBMPString(data, 0, data.Length()); 
					}
					else if (attr.dwValueType == CERT_RDN_UTF8_STRING) 
					{
						s = AsnObject::ReadUTF8String(data, 0, data.Length()); 
					}
					else
					{
						s = _W(
							CStringA((char*)attr.Value.pbData, attr.Value.cbData)
							); 
					}
					//
					return s; 
				}
				_Catch() 
			}

			inline void PrepareCertAttributesForXml(
				XmlElement& CertInfo_E,
				Blob& certData, 
				CCOM_Certificate& cert, 
				string* out_subject=0 
				)
			{
				try
				{
					// ---------------------------------------------------------------------------
					// ��������� ����������� 
					//
					CertInfo_E.SetAttribute(L"IssueDate", 
						FormatUTCTime(cert->m_notBefore)
						);
					CertInfo_E.SetAttribute(L"ExpireDate", 
						FormatUTCTime(cert->m_notAfter) 
						);
					//
					string CNOid = _W(szOID_COMMON_NAME); 
					string orgNameOid = _W(szOID_ORGANIZATION_NAME); 
					string countryOid = _W(szOID_COUNTRY_NAME); 
					string localityOid = _W(szOID_LOCALITY_NAME); 
					//
					string commonName; // = cert->get; 
					string orgName; 
					//
					PCCERT_CONTEXT pCertContext = CertCreateCertificateContext(X509_ASN_ENCODING,
						certData.GetBuffer(),
						certData.Length()
						);
					if (pCertContext)
					{
						int nValid = CertVerifyTimeValidity(NULL,pCertContext->pCertInfo); 
						CertInfo_E.SetAttribute(L"Validity", FormatStr(L"%d", (int)nValid)); 
						//
						CBlobW w1;
						w1.Allocate(1024); 
						ZeroMemory(w1.GetBuffer(), w1.Length()*sizeof(wchar_t)); 
						::CertNameToStrW(pCertContext->dwCertEncodingType, 
							&pCertContext->pCertInfo->Subject, CERT_X500_NAME_STR, w1.GetBuffer(), 1024); 
						//
						string subject1 = w1.GetBuffer(); 
						//
						Blob subjectBuf; 
						subjectBuf.Allocate(pCertContext->pCertInfo->Subject.cbData); 
						CopyMemory(subjectBuf.GetBuffer(), 
							pCertContext->pCertInfo->Subject.pbData, 
							pCertContext->pCertInfo->Subject.cbData); 
						//
						AsnObject subjectO(subjectBuf); 
						//
						string subject; 
						//
						for (int i = 0; i < subjectO.ChildCount(); i++) 
						{
							AsnObject& setO = subjectO[i]; 
							//
							for (int j = 0; j < setO.ChildCount(); j++)
							{
								AsnObject& attr = setO[j]; 
								//
								if (attr.ChildCount() >= 2)
								{
									AsnObject& o0 = attr[0]; 
									AsnObject& o1 = attr[1]; 
									//
									if (o0.Tag() == AsnObject::OBJECT_IDENTIFIER) 
									{
										string oid = o0.Oid(); 
										//
										if (oid == CNOid) 
										{
											commonName = o1.m_text; 
											if (subject.GetLength() > 0) subject += L", "; 
											subject += L"CN=" + commonName; 
										}
										else if (oid == orgNameOid) 
										{
											orgName = o1.m_text; 
											if (subject.GetLength() > 0) subject += L", "; 
											subject += L"O=" + commonName; 
										}
										else if (oid == countryOid) 
										{
											string cName = o1.m_text; 
											if (subject.GetLength() > 0) subject += L", "; 
											subject += L"C=" + cName; 
										}
										else if (oid == localityOid) 
										{
											string localityName = o1.m_text; 
											if (subject.GetLength() > 0) subject += L", "; 
											subject += L"L=" + localityName; 
										}
										else
										{
											if (subject.GetLength() > 0) subject += L", "; 
											subject += oid + L"=" + o1.m_text; 
										}
									}
								}
							}
						}
						//
						//Blob subjectData;
						//DWORD subjectSize = 1024; 
						//subjectData.Allocate(subjectSize); 
						////
						//if (CryptDecodeObjectEx( 
						//	X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, 
						//	X509_NAME, 
						//	pCertContext->pCertInfo->Subject.pbData, 
						//	pCertContext->pCertInfo->Subject.cbData, 
						//	0, 
						//	0, 
						//	subjectData.GetBuffer(), 
						//	&subjectSize
						//	)) 
						//{
						//	CERT_NAME_INFO* pInfo = 
						//		(CERT_NAME_INFO*)subjectData.GetBuffer(); 
						//	//
						//	for (int i = 0; i < pInfo->cRDN; i++)
						//	{
						//		CERT_RDN& rdn = pInfo->rgRDN[i]; 
						//		//
						//		for (int j = 0; j < rdn.cRDNAttr; j++)
						//		{
						//			CERT_RDN_ATTR& attr = rdn.rgRDNAttr[j]; 
						//			//
						//			if (_W(attr.pszObjId) == CNOid) 
						//			{
						//				commonName = FastRDNString(attr); 
						//			}
						//			//
						//			else if (_W(attr.pszObjId) == orgNameOid) 
						//			{
						//				orgName = FastRDNString(attr); 
						//			}
						//		}
						//	}
						//}
						//
						if (out_subject) *out_subject = subject1; 
					}
					//
					CertInfo_E.SetAttribute(L"CommonName", commonName); 
					CertInfo_E.SetAttribute(L"OrganizationName", orgName); 
					//
					// ---------------------------------------------------------------------------
				}
				_Catch()
			}

			//inline void RestoreContainerFile(const CString& path, 
			//	const string& name, XmlElement kRoot) 
			//{
			//	try
			//	{
			//	}
			//	_Catch()
			//}

			inline void RestoreContainer_RF1b(const CString& path) 
			{
				try
				{
					if (path.GetLength() <= 5) return; 
					//
					SharedArray<CString> _Paths = Machine::ListFiles(path,_T("*.xml")); 
					CString keyXmlPath = _Paths[0]; 
					//
					CreateDirectory(path + _T("\\Container"), 0); 
					//
					XmlDocument kDoc;
					kDoc.Load(_W(keyXmlPath)); 
					XmlElement kRoot = kDoc.DocumentElement(); 
					//
					XmlNodeList L = kRoot.SelectNodes(L"/KeyInfo/PSE/File"); 
					for (int k = 0; k < L.Count(); k++)
					{
						XmlElement E = L[k]; 
						//
						string name = E.GetAttribute(L"Name"); 
						string data64 = E.InnerText(); 
						Blob data = FromBase64String(data64); 
						//
						File f;
						f.OpenToWrite(path + _T(L"\\Container\\") + _S(name)); 
						f.Replace((const char*)data.GetBuffer(), data.Length()); 
						f.Close(); 
					}
				}
				_Catch() 
			}

			inline void BackupKeyFiles(const CString& path) 
			{
				try
				{
					CString path1 = path + _T("\\Container\\rand.opq"); 
					CString path2 = path + _T("\\Container\\rand_opq.copy"); 
					if (!Machine::FileExists(path2))
					{
						CopyFile(path1, path2, FALSE); 
					}
				}
				_Catch() 
			}

			XmlElement CreateDriveKeyInfo_RF1a(
				XmlDocument doc, 
				const CString& path, 
				const CString& driveLetter, 
				const CString& keyName, 
				bool woBin 
				)
				// removed: 
				// Blob lookupPkh, 
			{
				try
				{
					XmlElement keyInfo = CreateKeyInfo(doc,L"CryptoCOM",L"drive");
					//
					keyInfo.SetAttribute(L"KeyPath",string(path));
					keyInfo.SetAttribute(L"DriveLetter",string(driveLetter));
					keyInfo.SetAttribute(L"KeyName",string(keyName));
					//
					// ����������� ������� 
					//
					BackupKeyFiles(path); 
					//
					// ��������� ���������� � �����
					//
					string pkh64;
					//
					SharedArray<CString> pkXmlPaths = Machine::ListFiles(path,_T("*-k.xml"));
					if (pkXmlPaths.Length() == 0) 
					{
						keyInfo.SetAttribute(L"KeyTime",L"������ " + (string)keyName);
						// throw MethodError(_S("��� ������ � ����� ") + path);
						//
						// return keyInfo; // empty 
					}
					else
					{
						CString pkXmlPath = pkXmlPaths[0];
						//
						XmlDocument pkInfo;
						pkInfo.Load(string(pkXmlPath));
						XmlElement pkInfo_E = pkInfo.DocumentElement();
						//
						pkh64 = pkInfo_E.GetAttribute(L"PubKeyHash");
						if (pkh64.Right(1) == L"=") pkh64 = pkh64.Left(pkh64.GetLength()-1); 
						keyInfo.SetAttribute(L"PubKeyHash",pkh64);
						//
						//t0 = COleDateTime(...);
						//string datetime_s = string(t0.Format(_T("%Y-%m-%dT%H:%M:%SZ")));
						string datetime_s = pkInfo.DocumentElement().GetAttribute(L"KeyTime"); 
						//
						// ----
						// ��������� KeyInfo
						//
						keyInfo.SetAttribute(L"KeyTime",datetime_s);
						//
						//if (lookupPkh64.Length() > 0)
						//{
						//	string activePkh64 = __ToBase64String(lookupPkh);
						//	if (
						//		(activePkh64 == pkh64) || 
						//		(_W(activePkh64+L"=") == pkh64) || 
						//		(activePkh64 == _W(pkh64+L"="))
						//		)
						//	{
						//		CComBSTR bstrOn(L"true");  
						//		keyInfo.SetAttribute(L"IsActive",CComVariant(bstrOn)); 
						//	}
						//}
					}
					//
					// ----
					// ��������� ����������
					//
					SharedArray<CString> certPaths = Machine::ListFiles(path,_T("*.cer"));
					bool certFound = false;
					for (int i = 0; i < certPaths.Length() && (! certFound); ++i)
					{
						CString certPath = certPaths[i];
						//
						Blob certData;
						::::File f;
						f.Open(certPath);
						certData = f.ReadAll();
						f.Close();
						//
						// CCOM:
						//
						CCOM_Certificate cert;
						try
						{
							cert->Import(certData);
							//
							string certPkh64 = __ToBase64String(cert->GetPKH());
							if (
								((certPkh64 == pkh64) || (certPkh64+L"=" == pkh64) || (certPkh64 == pkh64+L"="))
								|| (pkh64.GetLength() == 0)
								)
							{
								XmlElement CertInfo_E = cert->GetXmlInfo(woBin); 
								CertInfo_E.SetAttribute(L"PubKeyHashUrlEnc",
									UrlEncode(Base64Text_4Url(certPkh64))
									);
								keyInfo.AppendChild(CertInfo_E); 
								//
								certFound = true;
								//
								// ---- 
								// ��������� ����������� 
								//
								PrepareCertAttributesForXml(CertInfo_E, certData, cert); 
							}
						}
						catch(Exception& e)
						{
							TRACE_LOG(e.ToString());
						}
						catch(...)
						{
							TRACE_LOG(_T("����������� ������!"));
						}
					}
					//
					// ��������� ������
					//
					AsnObject request = AsnObject::NewSequence();
					AsnObject requestXO = AsnObject::NewSequence();
					//
					SharedArray<CString> reqPaths = Machine::ListFiles(path,_T("*-request.der")); 
					bool reqFound = false;
					for (int i = 0; i < reqPaths.Length() && (! reqFound); ++i)
					{
						CString reqPath = reqPaths[i];
						//
						Blob reqData;
						::::File f;
						f.Open(reqPath);
						reqData = f.ReadAll();
						f.Close();
						//
						try
						{
							request = AsnObject(reqData);
#ifdef _DEBUG
							{
								//OutputDebugStringW(request.Dump() + L"\n"); 
							}
#endif
							//
							CString reqXOPath = reqPath;
							reqXOPath.Replace(_T("-request.der"),_T("-x.der")); 
							//
							if (Machine::FileExists(reqXOPath))
							{
								Blob reqXOData;
								::::File fXO;
								fXO.Open(reqXOPath);
								reqXOData = fXO.ReadAll();
								fXO.Close();
								//
								requestXO = AsnObject(reqXOData);
							}
							//
							reqFound = true;
						}
						catch(Exception& e)
						{
							TRACE_LOG(e.ToString());
						}
						catch(...)
						{
							TRACE_LOG(_T("����������� ������!")); 
						}
					}
					//
					if (reqFound)
					{
						XmlDocument requestInfo = PKI::GetRequestInfo(request,requestXO);
						XmlElement ri = requestInfo.DocumentElement();
						keyInfo.AppendChild(ri);
						if (! ri.IsEmpty())
						{
							pkh64 = ((XmlElement)ri.SelectSingleNode(L"CertificateInfo"))
								.GetAttribute(L"PubKeyHash");
							//
							keyInfo.SetAttribute(L"PubKeyHash",pkh64);
						}
					}
					//
					return keyInfo;
				}
				catch(Exception& e)
				{
					TRACE_LOG(e.ToString());
				}
				catch(...)
				{
				}
				//
				XmlElement keyInfo = CreateKeyInfo(doc,L"CryptoCOM",L"drive");
				return keyInfo; // empty 
			}

			XmlElement CreateDriveKeyInfo_RF1a_CP(
				XmlDocument doc,
				const string& pkh64_,
				const CString& driveLetter,
				const CString& keyName,
				bool woBin
				)
				// removed: 
				// Blob lookupPkh, 
			{
				try
				{
					XmlElement keyInfo = CreateKeyInfo(doc, L"CryptoCOM", L"drive");
					//
					keyInfo.SetAttribute(L"KeyPath", string(keyName));
					keyInfo.SetAttribute(L"DriveLetter", string(driveLetter));
					keyInfo.SetAttribute(L"KeyName", string(keyName));
					//
					// ��������� ���������� � �����
					//
					SharedArray<string> data = ::PKITools::SearchKey(pkh64_);
					string datetime_s = data[8];
					//
					string pkh64 = pkh64_;
					if (pkh64.Right(1) == L"=") pkh64 = pkh64.Left(pkh64.GetLength() - 1);
					//
					keyInfo.SetAttribute(L"PubKeyHash", pkh64);
					keyInfo.SetAttribute(L"KeyTime", datetime_s);
					//
					string cert64 = data[7];
					if (cert64 != L"")
					{
						Blob certData = FromBase64String(cert64);
						CCOM_Certificate cert;
						try
						{
							cert->Import(certData);
							//
							XmlElement CertInfo_E = cert->GetXmlInfo(woBin);
							CertInfo_E.SetAttribute(L"PubKeyHashUrlEnc",
								UrlEncode(Base64Text_4Url(pkh64))
								);
							keyInfo.AppendChild(CertInfo_E);
						}
						catch (...)
						{
						}
					}
					//
					AsnObject request = AsnObject::NewSequence();
					AsnObject requestXO = AsnObject::NewSequence();
					//
					string req64 = data[6];
					if (req64 != L"")
					{
						Blob reqData = FromBase64String(req64);
						request = AsnObject(reqData);
						XmlDocument requestInfo = PKI::GetRequestInfo(request, requestXO);
						XmlElement ri = requestInfo.DocumentElement();
						keyInfo.AppendChild(ri);
						if (!ri.IsEmpty())
						{
							pkh64 = ((XmlElement)ri.SelectSingleNode(L"CertificateInfo"))
								.GetAttribute(L"PubKeyHash");
							//
							keyInfo.SetAttribute(L"PubKeyHash", pkh64);
						}
					}
					//
					//
					return keyInfo;

//					// string pkh64;
//					//
//					SharedArray<CString> pkXmlPaths = Machine::ListFiles(path, _T("*-k.xml"));
//					if (pkXmlPaths.Length() == 0)
//					{
//						// throw MethodError(_S("��� ������ � ����� ") + path);
//						//
//						// return keyInfo; // empty 
//					}
//					else
//					{
//						CString pkXmlPath = pkXmlPaths[0];
//						//
//						XmlDocument pkInfo;
//						pkInfo.Load(string(pkXmlPath));
//						XmlElement pkInfo_E = pkInfo.DocumentElement();
//						//
//						pkh64 = pkInfo_E.GetAttribute(L"PubKeyHash");
//						if (pkh64.Right(1) == L"=") pkh64 = pkh64.Left(pkh64.GetLength() - 1);
//						//
//						//t0 = COleDateTime(...);
//						//string datetime_s = string(t0.Format(_T("%Y-%m-%dT%H:%M:%SZ")));
//						string datetime_s = pkInfo.DocumentElement().GetAttribute(L"KeyTime");
//						//
//						// ----
//						// ��������� KeyInfo
//						//
//						keyInfo.SetAttribute(L"KeyTime", datetime_s);
//						//
//						//if (lookupPkh64.Length() > 0)
//						//{
//						//	string activePkh64 = __ToBase64String(lookupPkh);
//						//	if (
//						//		(activePkh64 == pkh64) || 
//						//		(_W(activePkh64+L"=") == pkh64) || 
//						//		(activePkh64 == _W(pkh64+L"="))
//						//		)
//						//	{
//						//		CComBSTR bstrOn(L"true");  
//						//		keyInfo.SetAttribute(L"IsActive",CComVariant(bstrOn)); 
//						//	}
//						//}
//					}
//					//
//					// ----
//					// ��������� ����������
//					//
//					SharedArray<CString> certPaths = Machine::ListFiles(path, _T("*.cer"));
//					bool certFound = false;
//					for (int i = 0; i < certPaths.Length() && (!certFound); ++i)
//					{
//						CString certPath = certPaths[i];
//						//
//						Blob certData;
//						::::File f;
//						f.Open(certPath);
//						certData = f.ReadAll();
//						f.Close();
//						//
//						// CCOM:
//						//
//						CCOM_Certificate cert;
//						try
//						{
//							cert->Import(certData);
//							//
//							string certPkh64 = __ToBase64String(cert->GetPKH());
//							if (
//								((certPkh64 == pkh64) || (certPkh64 + L"=" == pkh64) || (certPkh64 == pkh64 + L"="))
//								|| (pkh64.GetLength() == 0)
//								)
//							{
//								XmlElement CertInfo_E = cert->GetXmlInfo(woBin);
//								CertInfo_E.SetAttribute(L"PubKeyHashUrlEnc",
//									UrlEncode(Base64Text_4Url(certPkh64))
//									);
//								keyInfo.AppendChild(CertInfo_E);
//								//
//								certFound = true;
//								//
//								// ---- 
//								// ��������� ����������� 
//								//
//								PrepareCertAttributesForXml(CertInfo_E, certData, cert);
//							}
//						}
//						catch (Exception& e)
//						{
//							TRACE_LOG(e.ToString());
//						}
//						catch (...)
//						{
//							TRACE_LOG(_T("����������� ������!"));
//						}
//					}
//					//
//					// ��������� ������
//					//
//					AsnObject request = AsnObject::NewSequence();
//					AsnObject requestXO = AsnObject::NewSequence();
//					//
//					SharedArray<CString> reqPaths = Machine::ListFiles(path, _T("*-request.der"));
//					bool reqFound = false;
//					for (int i = 0; i < reqPaths.Length() && (!reqFound); ++i)
//					{
//						CString reqPath = reqPaths[i];
//						//
//						Blob reqData;
//						::::File f;
//						f.Open(reqPath);
//						reqData = f.ReadAll();
//						f.Close();
//						//
//						try
//						{
//							request = AsnObject(reqData);
//#ifdef _DEBUG
//							{
//								//OutputDebugStringW(request.Dump() + L"\n"); 
//							}
//#endif
//							//
//							CString reqXOPath = reqPath;
//							reqXOPath.Replace(_T("-request.der"), _T("-x.der"));
//							//
//							if (Machine::FileExists(reqXOPath))
//							{
//								Blob reqXOData;
//								::::File fXO;
//								fXO.Open(reqXOPath);
//								reqXOData = fXO.ReadAll();
//								fXO.Close();
//								//
//								requestXO = AsnObject(reqXOData);
//							}
//							//
//							reqFound = true;
//						}
//						catch (Exception& e)
//						{
//							TRACE_LOG(e.ToString());
//						}
//						catch (...)
//						{
//							TRACE_LOG(_T("����������� ������!"));
//						}
//					}
//					//
//					if (reqFound)
//					{
//						XmlDocument requestInfo = PKI::GetRequestInfo(request, requestXO);
//						XmlElement ri = requestInfo.DocumentElement();
//						keyInfo.AppendChild(ri);
//						if (!ri.IsEmpty())
//						{
//							pkh64 = ((XmlElement)ri.SelectSingleNode(L"CertificateInfo"))
//								.GetAttribute(L"PubKeyHash");
//							//
//							keyInfo.SetAttribute(L"PubKeyHash", pkh64);
//						}
//					}
//					//
//					return keyInfo;
				}
				catch (Exception& e)
				{
					TRACE_LOG(e.ToString());
				}
				catch (...)
				{
				}
				//
				XmlElement keyInfo = CreateKeyInfo(doc, L"CryptoCOM", L"drive");
				return keyInfo; // empty 
			}

			XmlElement AddDriveKeyInfo(XmlElement& CommonKeyInfo_E,const CString& path,
				const CString& driveLetter, const CString& keyName, bool woBin)
			{
				XmlElement keyInfo = CreateDriveKeyInfo(CommonKeyInfo_E.OwnerDocument(),path,
					driveLetter,keyName,Blob(),woBin);
				CommonKeyInfo_E.AppendChild(keyInfo);
				return keyInfo;
			}

			bool AddOneETokenKeyFilePath_M(
				int slotId, 
				int key_i, 
				int key_mode, 
				const string& path, 
				XmlElement filesInfo, 
				XmlDocument doc, 
				const Map<string, string>& filter=Map<string, string>() 
				)
			{
				try
				{
					const int buflen = 16 * 1024; 
					//
					Blob data;
					//
					if (key_mode == 1)
					{
						data.Expand(buflen); 
						//
						CStringA pathA = PKCS11_Manager_().ETokenPath(
							slotId, 
							PKCS11_Manager_().EToken_GetKeyContainerPath_U(slotId, key_i) + L"/" + path 
							); 
						//
						int size = CADB_read_file(pathA.GetBuffer(), (char*)data.GetBuffer(), buflen); 
						if (size > 0)
						{
							data.SetSize(size); 
						}
						else
						{
							return false; 
						}
					}
					else if (key_mode == 2)
					{
						string label = PKCS11_Manager_().GetObjectLabel(L"A", path); 
						throw MethodError(L"MODE 2"); 
						//data = PKCS11_Manager_().ReadObject(slotId, label, 1); 
					}
					//
					if (data.Length() > 0)
					{
						XmlElement File_E = doc.CreateElement(L"", L"File", L""); 
						File_E.InnerText() = ToBase64Padding(data); 
						File_E.SetAttribute(L"Name", _W(path)); 
						//
						filesInfo.AppendChild(File_E); 
						return true; 
					}
					else
					{
						return false; 
					}
				}
				_Catch() 
			}

			bool AddOneETokenKeyFiles_M(
				int slotId, 
				int key_i, 
				int key_mode, 
				XmlElement keyInfo, 
				XmlDocument doc, 
				const Map<string, string>& filter=Map<string, string>() 
				)
			{
				try
				{
					XmlElement filesInfo = doc.CreateElement(L"", L"Files", L""); 
					keyInfo.AppendChild(filesInfo); 
					//
					string p = PKCS11_Manager_().GetETokenPassword(slotId, key_i, key_mode); 
					filesInfo.SetAttribute(L"ContainerPass", p); 
					//
					AddOneETokenKeyFilePath_M(slotId, key_i, key_mode, L"a001", filesInfo, doc, filter); 
					AddOneETokenKeyFilePath_M(slotId, key_i, key_mode, L"b001", filesInfo, doc, filter); 
					AddOneETokenKeyFilePath_M(slotId, key_i, key_mode, L"c001", filesInfo, doc, filter); 
					AddOneETokenKeyFilePath_M(slotId, key_i, key_mode, L"d001", filesInfo, doc, filter); 
					//
					AddOneETokenKeyFilePath_M(slotId, key_i, key_mode, L"fa01", filesInfo, doc, filter); 
					//
					AddOneETokenKeyFilePath_M(slotId, key_i, key_mode, L"fc01", filesInfo, doc, filter); 
					//
					AddOneETokenKeyFilePath_M(slotId, key_i, key_mode, L"fe01", filesInfo, doc, filter); 
					AddOneETokenKeyFilePath_M(slotId, key_i, key_mode, L"fe02", filesInfo, doc, filter); 
					//
					return true; 
				}
				_Catch() 
			}

			bool AddOneETokenCertAndRequestInfo(
				int slotId, 
				int key_i, 
				XmlElement keyInfo, 
				const string& pkh64, 
				XmlDocument doc, 
				Blob lookupPkh, 
				const Map<string, string>& filter=Map<string, string>(), 
				bool woBin=false 
				)
			{
				try
				{
					int buflen = 16 * 1024; 
					//
					bool certFound = false; 
					//
					Blob certData;
					certData.Expand(buflen); 
					CStringA pathA = PKCS11_Manager_().ETokenPath(
						slotId, PKCS11_Manager_().EToken_GetCertPath(slotId, key_i)); 
					//
					int size = CADB_read_file(pathA.GetBuffer(), (char*)certData.GetBuffer(), buflen); 
					if (size > 0)
					{
						certData.SetSize(size); 
						//
						CCOM_Certificate cert;
						try
						{
							cert->Import(certData);
							//
							string certPkh64 = __ToBase64String(cert->GetPKH());
							if (
								((certPkh64 == pkh64) || (certPkh64+L"=" == pkh64) || (certPkh64 == pkh64+L"="))
								|| (pkh64.GetLength() == 0)
								)
							{
								XmlElement CertInfo_E = cert->GetXmlInfo(woBin); 
								CertInfo_E.SetAttribute(L"PubKeyHashUrlEnc",
									UrlEncode(Base64Text_4Url(certPkh64))
									);
								keyInfo.AppendChild(CertInfo_E);
								//
								certFound = true;
								//
								// ---- 
								// ��������� ����������� 
								//
								PrepareCertAttributesForXml(CertInfo_E, certData, cert); 
							}
						}
						catch(Exception& e)
						{
							TRACE_LOG(e.ToString());
						}
						catch(...)
						{
							TRACE_LOG(_T("����������� ������!"));
						}
					}
					//
					// ----
					// ��������� ������
					//
					AsnObject request = AsnObject::NewSequence();
					AsnObject requestXO = AsnObject::NewSequence();
					//
					bool reqFound = false; 
					{
						Blob reqData;
						reqData.Expand(buflen); 
						CStringA pathA = PKCS11_Manager_().ETokenPath(
							slotId, PKCS11_Manager_().EToken_GetRequestPath(slotId, key_i) 
							); 
						//
						int size = CADB_read_file(pathA.GetBuffer(), (char*)reqData.GetBuffer(), buflen); 
						reqData.SetSize(size); 
						//
						try
						{
							request = AsnObject(reqData);
							//
							Blob reqXOData;
							reqXOData.Expand(buflen); 
							CStringA pathA = PKCS11_Manager_().ETokenPath(
								slotId, PKCS11_Manager_().EToken_GetRequestPath_X(slotId, key_i)); 
							//
							int size = CADB_read_file(pathA.GetBuffer(), (char*)reqXOData.GetBuffer(), buflen); 
							reqXOData.SetSize(size); 
							//
							requestXO = AsnObject(reqXOData); 
							//
							reqFound = true;
						}
						catch(Exception& e)
						{
							TRACE_LOG(e.ToString());
						}
						catch(...)
						{
							TRACE_LOG(_T("����������� ������!")); 
						}
					}
					//
					if (reqFound)
					{
						XmlDocument requestInfo = GetRequestInfo(request,requestXO);
						XmlElement ri = requestInfo.DocumentElement();
						keyInfo.AppendChild(ri);
						if (! ri.IsEmpty())
						{
							string pkh64 = ((XmlElement)ri.SelectSingleNode(L"CertificateInfo"))
								.GetAttribute(L"PubKeyHash");
							//
							keyInfo.SetAttribute(L"PubKeyHash",pkh64);
						}
					}
					//
					return certFound; 
				}
				_Catch()
			}

			XmlElement AddOneETokenKeyInfo_M(
				int slotId, 
				int key_i, 
				int key_mode, 
				XmlElement CommonKeyInfo_E, 
				Blob lookupPkh, 
				const Map<string, string>& filter=Map<string, string>() 
				)
			{
				try
				{
					XmlDocument doc = CommonKeyInfo_E.OwnerDocument();
					XmlElement keyInfo = CreateKeyInfo(doc,L"CryptoCOM",L"eToken");
					//
					keyInfo.SetAttribute(L"KeyNum",FormatStr(L"%d", (int)key_i ));
					keyInfo.SetAttribute(L"ETokenSlotId",FormatStr(L"%d", (int)slotId ));
					//keyInfo.SetAttribute(L"KeyName",string(keyName));
					//
					// ��������� ���������� � �����
					//
					string pkh64;
					//
					int buflen = 16 * 1024; 
					Blob keyDataEnv;
					keyDataEnv.Expand(buflen); 
					CStringA pathA = PKCS11_Manager_().ETokenPath(
						slotId, PKCS11_Manager_().EToken_GetKeyPath(slotId, key_i)); 
					//
					int size = CADB_read_file(pathA.GetBuffer(), (char*)keyDataEnv.GetBuffer(), buflen); 
					if (size <= 0) 
					{
						int e1 = (int)ERR_get_last_error(); 
						string errMsg = FormatStr(L"�� ������� ��������� ���� �� eToken: " + _W(pathA) +
							L", ������ CCOM: %d", (int)e1 );
						throw MethodError(errMsg); 
					}
					keyDataEnv.SetSize(size); 
					//
					AsnObject keyDataEnvO(keyDataEnv); 
					AsnObject& keyData = keyDataEnvO[1]; 
					AsnObject& keyAttrs = keyData[0];
					AsnObject& keyValues = keyData[1];
					//
					string keyTime_s = ((AsnObject&)keyAttrs[0]).m_text; 
					//int pkParameters = ((AsnObject&)keyAttrs[1]).m_Integer; 
					//int sBox = ((AsnObject&)keyAttrs[2]).m_Integer; 
					AsnObject& oPKH = keyAttrs[3];
					Blob pkh = oPKH.Data();
					pkh64 = __ToBase64(pkh); 
					string pass = ((AsnObject&)keyAttrs[4]).m_text; 
					//
					AsnObject& oEK = keyValues[0];
					Blob EK = oEK.Data();
					//
					AsnObject& oMac = keyValues[1];
					Blob Mac = oMac.Data();
					//
					AsnObject& oPK = keyValues[2];
					Blob PK = oPK.Data();
					//
					//
					//
					keyInfo.SetAttribute(L"PubKeyHash", pkh64);
					keyInfo.SetAttribute(L"KeyTime", keyTime_s); 
					//
					if (lookupPkh.Length() > 0)
					{
						string activePkh64 = __ToBase64String(lookupPkh);
						if (
							(activePkh64 == pkh64) || 
							(_W(activePkh64+L"=") == pkh64) || 
							(activePkh64 == _W(pkh64+L"="))
							)
						{
							CComBSTR bstrOn(L"true");  
							keyInfo.SetAttribute(L"IsActive",CComVariant(bstrOn)); 
						}
					}
					//
					// ----
					// ����������� ���������� � �����? 
					//
					if (filter.ContainsKey(L"special-export-key"))
					{
						AddOneETokenKeyFiles_M(slotId, key_i, key_mode, keyInfo, doc, filter); 
					}
					//
					// ----
					// ��������� ���������� � ������ 
					//
					AddOneETokenCertAndRequestInfo(slotId, key_i, keyInfo, pkh64, doc, lookupPkh); 
					//
					CommonKeyInfo_E.AppendChild(keyInfo); 
					//
					return keyInfo;
				}
				catch(Exception& e)
				{
					TRACE_LOG(e.ToString());
				}
				catch(...)
				{
				}
				//
				XmlElement keyInfo = CreateKeyInfo(CommonKeyInfo_E.OwnerDocument(),L"CryptoCOM",L"eToken");
				return keyInfo; // empty 
			}

			void AddETokenKeysXmlInfo(
				string eTokenID, 
				int key_mode, 
				XmlElement CommonKeyInfo_E, 
				const Map<string, string>& filter=Map<string, string>() 
				)
			{
				try
				{
					PKCS11_Manager::Lock lock; 
					//
					EToken& eToken = EToken::OpenEToken(eTokenID); 
					//eToken.Login(); // already logged in 
					eToken.AddKeyInfo(CommonKeyInfo_E, filter); 
					//
					//PKCS11_Manager& M = PKCS11_Manager::Acquire(); 
					//M.EnterContext(slotId); 
					////
					//M.LoginEToken(slotId); 
					//CCOMLib::LoginEToken(); 
					////
					//SharedArray<int> keyNums = PKCS11_Manager_().GetETokenKeyNums(slotId, key_mode, 
					//	_PRIVATE_META
					//	); 
					//for (int j = 0; j < keyNums.Length(); j++)
					//{
					//	int key_i = keyNums[j]; 
					//	//
					//	AddOneETokenKeyInfo_M(slotId, key_i, key_mode, CommonKeyInfo_E, lookupPkh, filter); 
					//}
					////
					//M.ReleaseContext(); 
				}
				_Catch()
			}

			void SaveKeyToEToken(
				int slotId, 
				XmlDocument sourceDoc, 
				const Map<string, string>& filter 
				)
			{
				try
				{
					string lookupPkh64; 
					//
					if (filter.ContainsKey(L"lookup-pkh"))
					{
						string v1 = filter[L"lookup-pkh"]; 
						//
						lookupPkh64 = __ToBase64(FromBase64String(v1)); 
					}
					//
					// ����� 
					//
					XmlNodeList L = sourceDoc.SelectNodes(L"/CommonKeyInfo/KeyInfo"); 
					//
					XmlElement KeyInfo; 
					//
					for (int i = 0; i < L.Count(); ++i)
					{
						KeyInfo_E = L[i]; 
						//
						bool use = false; 
						//
						string pkh64 = __ToBase64(FromBase64String(KeyInfo_E.GetAttribute(L"PubKeyHash")));
					}
				}
				_Catch() 
			}

			static string& RequestStatusInfoTemplate() 
			{
				static string t;
				//
				if (t.GetLength() == 0)
				{
					t = L"<?xml version=\"1.0\" ?>\n"
						L"<?xml-stylesheet type=\"text/xsl\" href=\"http://cabinet.example.com/protocol/-cert-request.xsl\" ?>"
						L"<RequestStatusInfo>\n"
						L"</RequestStatusInfo>"
						;
				}
				//
				return t;
			}

			XmlDocument GetRequestReadyInfo(AsnObject& requestO,AsnObject& requestExtra)
			{
				try
				{
					XmlDocument doc;
					doc.LoadXml(RequestStatusInfoTemplate());
					//
					XmlElement RSInfo_E = doc.DocumentElement();
					//
					Algorithms::Alg_1_8_2 a2;
					string pkh64 = a2.Encode(requestO.CP_GOST2001PublicKeyBits);
					Blob pkh = FromBase64String(pkh64);
					pkh64 = ToBase64(pkh);
					RSInfo_E.SetAttribute(L"PubKeyHash",pkh64);
					//
					try
					{
						RSInfo_E.AppendChild(GetRequestInfo(requestO,requestExtra).DocumentElement());
					}
					catch(...)
					{
					}
					//
		#			ifdef _DEBUG
					//TRACE_LOG(doc.DocumentElement().OuterXml());
		#			endif
					return doc;
				}
				_Catch()
			}






			XmlDocument RequestInfoDocument( 
				const string& pkh64 
				) 
			{
				try
				{
					//Blob pkh = FromBase64String(pkh64); 
					//XmlDocument d = Instance().PrepareCommonKeyInfo(pkh,Blob(),false, 
					//	Map<string,string>(), false 
					//	); 
					//
					XmlDocument d = CommonKeyInfoDocument_RF1a(); 
					if (d.IsEmpty())
					{
						throw MethodError(L"CommonKeyInfo: ������� ������ �������� �� Client_GetCommonKeyInfo(pkh64)"); 
					}
					//
	#				ifdef _DEBUG
					{
						///OutputDebugString(_S(d.OuterXml())); 
					}
	#				endif
					//
					XmlElement dRoot = d.DocumentElement();
					//
					string xPath = GetKeyInfoXPath(pkh64); 
					XmlNodeList L1 = dRoot.SelectNodes(xPath);
					//
					long L1_Count = L1.Count();
					//
					if (L1_Count == 0)
						throw MethodError(L"������ �� ������: " + _W(pkh64));
					//
					//
					// ----
					// KeyInfo
					//
					XmlElement KeyInfo_E = (XmlElement)L1[0]; 
					string KeyMedia = KeyInfo_E.GetAttribute(L"KeyMediaType"); 
					//
					Blob reqData; 
					//
					if (KeyMedia == L"eToken")
					{
						string eTokenID = KeyInfo_E.GetAttribute(L"eTokenID"); 
						int key_i = _wtoi(KeyInfo_E.GetAttribute(L"KeyNum"));
						//
						EToken& eToken = EToken::OpenEToken(eTokenID); 
						int eTokenSlotId = eToken.SlotId; 
						//
						string reqLabel = FormatStr(L" Request %d", key_i); 
						//
						SharedArray<Blob> req_a = eToken.FindETokenObjects(eTokenSlotId, 
							CKO_DATA,
							1,
							reqLabel 
							); 
						//
						if (req_a.Length() > 0)
						{
							reqData = req_a[0]; 
						}
					}
					else // drive 
					{
						CString keyPath = _S(KeyInfo_E.GetAttribute(L"KeyPath"));
						//
						SharedArray<CString> reqPaths = Machine::ListFiles(keyPath,_T("*-request.der"));
						if (reqPaths.Length() == 0) 
						{
							throw MethodError(L"������ �� ������ " + _W(pkh64)); 
						}
						//
						CString reqPath = reqPaths[0];
						//
						File rf;
						rf.Open(reqPath);
						reqData = rf.ReadAll(); 
						rf.Close(); 
					}
					//
					//
					// ----
					// ���������� XML � �������
					//
					CComPtr<IXMLDOMNodeList> L;
					HRESULT rc = (KeyInfo_E.GetXmlObjectInterface())->selectNodes(
						CComBSTR(L"RequestInfo")
						,&L);
					if (FAILED(rc)) throw MethodError(rc); 
					//
					long L_Count;
					rc = L->get_length(&L_Count); 
					if (FAILED(rc)) throw MethodError(rc); 
					//
					if (L_Count == 0)
						throw MethodError(L"������ �� ������: " + _W(pkh64)); 
					//
					IXMLDOMNode* L_0;
					rc = L->get_item(0,&L_0);
					if (FAILED(rc)) throw MethodError(rc); 
					//
					XmlElement data_E = d.CreateElement(L"",L"data",L""); 
					data_E.InnerText() = __ToBase64(reqData); 
					//
					CComPtr<IXMLDOMNode> newChild; 
					rc = L_0->appendChild((IXMLDOMNode*)data_E.GetXmlObjectInterface(),&newChild);
					if (FAILED(rc)) throw MethodError(rc); 
					//
					CComBSTR xml1; 
					rc = L_0->get_xml(&xml1);
					if (FAILED(rc)) throw MethodError(rc); 
					//TRACE_LOG(xml1); 
					//
					string vXslUrl;
					CComBSTR bstrVXsl;
					rc = GetQueryParameter(CComBSTR(L"vxsl"),&bstrVXsl);
					//TRACE_LINE(_T("* 1"));
					if (FAILED(rc)) throw MethodError(rc);
					//
					//TRACE_LINE(_T("* 2"));
					if (rc == S_OK) 
					{
						vXslUrl = _W(bstrVXsl); 
					}
					else
					{
	#					ifdef _PROTOCOL_OLD_CERT_REQUEST_XSL
						{
							vXslUrl = L"/protocol/-cert-request.xsl"; 
						}
	#					else
						{
							vXslUrl = L""; 
						}
	#					endif
					}
					//
					//TRACE_LINE(_T("* 3"));
					string h = Client_RequestInfoHeaderTemplate(vXslUrl);  
					string requestInfoXml = h + _W(xml1); 
					//
					//TRACE_LINE(_T("* 4"));
					XmlDocument doc2;
					doc2.LoadXml(requestInfoXml);
					//
					//TRACE_LINE(_T("* 5"));
					XmlElement dRoot2 = doc2.DocumentElement();
					//
					//TRACE_LINE(_T("* 6"));
					dRoot2.SetAttribute(L"PubKeyHashUrlEnc",string(UrlEncode(pkh64))); 
					//
					//TRACE_LINE(_T("* 7"));
					return Document(doc2);
				}
				_Catch() 
			}










			SharedArray<CString> GetKeyDrives()
			{
				try
				{
					bool excludeDiskette = !(
						GetFlagValue(string(GetOption(L"special-101")))
						);
					//
					CString useDrive = _S(GetOption(L"special-102"));
					//
					SharedArray<CString> drives = Machine::ListDrives(DRIVE_REMOVABLE,excludeDiskette,
						useDrive);
					//
					CString addDrivesList = _S(GetOption(L"special-103"));
					SharedArray<CString> addDrives = ExtractDriveList(addDrivesList);
					for (int k = 0; k < addDrives.Length(); ++k)
					{
						drives.Add(addDrives[k]);
					}
					//
					return drives.CombineEqual();
				}
				_Catch()
			}


			SharedArray<CString> GetExtraKeyDrives()
			{
				try
				{
					SharedArray<CString> drives;
					//
					CString usePath = _S(GetOption(L"special-104"));
					//
					if (usePath.GetLength() > 0)
					{
						drives.Add("s104");
					}
					//
					return drives; 
				}
				_Catch() 
			}

			CString ExtraDriveInfoLine(const CString& drive)
			{
				try
				{
					CString info;
					//
					if (drive == _T("s104"))
					{
						CString usePath = _S(GetOption(L"special-104"));
						info = usePath; 
					}
					//
					return info;
				}
				_Catch()
			}

			inline bool DriveIsSpecial_102(const string& letter) 
			{
				try
				{
					CString useDrive = _S(GetOption(L"special-102"));
					//
					return _W(useDrive) == letter; 
				}
				_Catch() 
			}

			SharedArray<CString> ExtractDriveList(const CString& drivesList)
			{
				try
				{
					SharedArray<CString> L = drivesList / _T(",");
					SharedArray<CString> drives;
					for (int k = 0; k < L.Length(); ++k)
					{
						CString drive = L[k];
						if (drive.GetLength() == 1)
						{
							BYTE b = (BYTE)( CStringA(drive)[0] );
							if ((b >= (BYTE)'a') && (b < (BYTE)'z'))
							{
								drives.Add(drive);
							}
						}
					}
					return drives;
				}
				_Catch()
			}

			inline static CRITICAL_SECTION& CriticalSection() 
			{
				static bool crits_f = false;
				static CRITICAL_SECTION crits; 
				if (! crits_f)
				{
					InitializeCriticalSection(&crits); 
					crits_f = true;
				}
				return crits; 
			}

			class Lock
			{
			public:
				Lock()
				{
					EnterCriticalSection(&CriticalSection());
				}

				~Lock()
				{
					LeaveCriticalSection(&CriticalSection());
				}
			};



			public: SharedArray<string> CurrentPubKeyHashList; 

			inline void AnalyzeCommonKeyInfo(XmlDocument doc) 
			{
				try
				{
					XmlElement root = doc.DocumentElement(); 
					//
					CurrentPubKeyHashList.Free(); 
					//
					XmlNodeList L = root.SelectNodes(L"KeyInfo[CertificateInfo]"); 
					//
					for (int k = 0; k < L.Count(); ++k)
					{
						XmlElement KeyInfo_E = L[k]; 
						//
						XmlElement CertificateInfo_E = KeyInfo_E.SelectSingleNode(L"CertificateInfo"); 
						//
						bool use = true; 
						if (CertificateInfo_E.HasAttribute(L"Validity"))
						{
							if (CertificateInfo_E.GetAttribute(L"Validity") != "0") use = false; 
						}
						//
						if (use)
						{
							string pkh64 = KeyInfo_E.GetAttribute(L"PubKeyHash"); 
							CurrentPubKeyHashList.Add(pkh64); 
						}
					}
				}
				_Catch() 
			}

			inline string GetCurrentPKHList() 
			{
				try
				{
					string s; 
					//
					for (int k = 0; k < CurrentPubKeyHashList.Length(); ++k)
					{
						string pkh64 = CurrentPubKeyHashList[k]; 
						//
						if (s.GetLength() > 0) s += L";"; 
						s += pkh64; 
					}
					//
					return s; 
				}
				_Catch() 
			}

			inline Blob GetCurrentPKHBinary() 
			{
				try
				{
					return GetCurrentPKHBinaryList(1); 
				}
				_Catch()
			}

			inline Blob GetCurrentPKHBinaryList(int m=-2) 
			{
				try
				{
					SharedArray<Blob> pkh_a; 
					int len = 0; 
					//
					Blob bin; 
					//
					XmlDocument deviceInfoDoc = DeviceInfo(); 
					XmlElement deviceInfo = deviceInfoDoc.DocumentElement(); 
					XmlNodeList L = deviceInfo.SelectNodes(L"Device/Keys/Key[@Validity='0']"); 
					int M = 0;
					if (L.Count() > 0)
					{
						M = L.Count();
						if (m > 0) if (m < M) M = m;
					}
					//
					for (int k = 0; k < M; k++) 
					{
						XmlElement Key_E = L[k]; 
						//
						string pkh64 = Key_E.GetAttribute(L"PubKeyHash"); 
						Blob pkh = FromBase64String(pkh64); 
						if (pkh.Length() > 0) pkh_a.Add(pkh); 
						len += pkh.Length(); 
					}
					//
					bin.Allocate(len); 
					int p = 0;
					for (int k = 0; k < pkh_a.Length(); k++) 
					{
						Blob pkh = pkh_a[k]; 
						//
						CopyMemory(bin.GetBuffer() + p, pkh.GetBuffer(), pkh.Length()); 
						//
						p += pkh.Length(); 
					}
					return bin; 
				}
				_Catch() 
			}

			inline Blob GetCurrentPKHBinaryList_Obsolete_1() 
			{
				try
				{
					Blob bin; 
					//
					if (CurrentPubKeyHashList.Length() == 0) return bin; 
					//
					int len = FromBase64String(CurrentPubKeyHashList[0]).Length(); 
					//
					bin.Allocate(len * CurrentPubKeyHashList.Length()); 
					BYTE* p = bin.GetBuffer(); 
					//
					for (int k = 0; k < CurrentPubKeyHashList.Length(); ++k)
					{
						string pkh64 = CurrentPubKeyHashList[k]; 
						Blob pkh = FromBase64String(pkh64); 
						//
						if (k * len + pkh.Length() > bin.Length()) 
							throw MethodError(L"������ ������������ ������ PKH (1)"); 
						//
						CopyMemory(p + k * len, pkh.GetBuffer(), pkh.Length()); 
					}
					//
					return bin; 
				}
				_Catch() 
			}

			inline string GetCurrentPKHStr() 
			{
				try
				{
					Blob b = GetCurrentPKHBinary(); 
					string s1;
					if (b.Length() > 0) s1 = ToBase64NoCRLF(b); 
					else s1 = L""; 
					//
					return s1; 
				}
				_Catch() 
			}

			inline string GetCurrentPKHBinaryListStr() 
			{
				try
				{
					Blob b = GetCurrentPKHBinaryList(); 
					string s1;
					if (b.Length() > 0) s1 = ToBase64NoCRLF(b); 
					else s1 = L""; 
					//
					return s1; 
				}
				_Catch() 
			}



			XmlDocument PrepareCommonKeyInfo_RF1a()
			{
				return PrepareCommonKeyInfo_RF1a(false,Map<string,string>(),false);
			}

			XmlDocument PrepareCommonKeyInfo_RF1a(
				bool useXsl, 
				const Map<string, string>& filter, 
				bool woBin
				) 
				// removed: 
				// Blob searchPkh, 
				// Blob activePkh, 
			{
				try
				{
					bool useCache = true; 
					//
					int arg_n = 0; 
					//
					string lookupPkh64; 
					if (filter.ContainsKey(L"lookup-pkh"))
					{
						lookupPkh64 = NormalizeBin64(filter[L"lookup-pkh"]); 
						arg_n++; 
					}
					//
					if (filter.GetSize() > arg_n) useCache = false; 
					//
					string id = _W(L"CommonKeyInfo_A_pkh_") + lookupPkh64; 
					if (useCache)
					{
						XmlDocument cachedDoc;
						if (ObjCache::GetXmlObject(id, cachedDoc))
						{
							return cachedDoc; 
						}
					}
					//
					XmlDocument doc;
					doc.LoadXml(CommonKeyInfoTemplate(useXsl));
					if (doc.IsEmpty())
					{
						throw MethodError(L"�� ������� ��������� CommonKeyInfo (1)"); 
					}
					//
					XmlElement CommonKeyInfo_E = doc.DocumentElement();
					//
					CString keyRootCommonPath = _S(GetOption(L"special-105"));
					CString keyRootPath = _S(GetOption(L"special-104")); 
					if ((keyRootPath.GetLength() == 0) && (keyRootCommonPath.GetLength() > 0)) 
					{
						keyRootPath = keyRootCommonPath + _T("\\") + ::::Util::GetUserName();
					}
					//
					// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					// ������-���
					//
					SharedArray<string> paths;
					SharedArray<string> roots;
					SharedArray<CString> keys = ::PKITools::GetKeysCryptoPro(&paths, &roots);
					//
					for (int k = 0; k < keys.GetSize(); k++)
					{
						CString pkh64 = keys[k];
						CString containerName = paths[k];
						CString drive = roots[k];
						//
						XmlElement keyInfo = CreateDriveKeyInfo_RF1a_CP(doc, pkh64, drive, containerName,
							woBin);
					}
					//
					// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					//
					if (keyRootPath.GetLength() == 0) // 
					{
						// ��������� ���������� � ������ �� ������� ���������
						//
#						ifdef _DEBUG
						{
							TRACE_LINE(_T("��������� ���������� � ������ �� ������� ���������"));
						}
#						endif
						//
						SharedArray<CString> removableDrives = GetKeyDrives();
						//
						for (int drive_i = 0; drive_i < removableDrives.Length(); ++drive_i)
						{
							CString drive = removableDrives[drive_i];
							CString driveRoot = drive + _T(":\\");
							CString Root = driveRoot + _T("");
							//
							if (Machine::DirectoryExists(Root))
							{
								CString certDir = Root + _T("\\Certificates"); 
								//
								if (Machine::DirectoryExists(certDir))
								{
									SharedArray<CString> keyDirs = Machine::ListFiles(certDir);   
									//
									for (int k = 0; k < keyDirs.Length(); ++k)
									{
										CString keyDir = keyDirs[k];
										////TRACE_LOG(keyDir);
										//
										int file_p = -1;
										int p1 = keyDir.Find(_T("\\"));
										while (p1 != -1)
										{
											file_p = p1;
											p1 = keyDir.Find(_T("\\"),p1+1);
										}
										CString keyName;
										if (file_p != -1)
											keyName = keyDir.Right(keyDir.GetLength()-file_p-1);
										else
											keyName = keyDir;
										//
										XmlElement keyInfo = CreateDriveKeyInfo_RF1a(doc,keyDir,drive,keyName,
											woBin);
										//
										if (keyInfo.HasAttribute(L"PubKeyHash")) // ������ ���� 
										{ 
											bool use = true;
											//
											if (lookupPkh64.GetLength() > 0)
											{
												string pkh64a = keyInfo.GetAttribute(L"PubKeyHash");
												string pkh64 = NormalizeBin64(pkh64a); 
												//
												if (pkh64 != lookupPkh64) use = false; 
											}
											//
											if (use)
											{
												CommonKeyInfo_E.AppendChild(keyInfo);
											}
										}
									}
								}
							}
						}
					}
					else // ������ ���� � ����� � �������
					{
						CString Root = keyRootPath + _T("\\");  // 
						//
						if (Machine::DirectoryExists(Root))
						{
							CString certDir = Root + _T("\\Certificates");
							//
							if (Machine::DirectoryExists(certDir))
							{
								SharedArray<CString> keyDirs = Machine::ListFiles(certDir);    
								//
								for (int k = 0; k < keyDirs.Length(); ++k)
								{
									CString keyDir = keyDirs[k];
									///TRACE_LOG(keyDir);
									//
									int file_p = -1;
									int p1 = keyDir.Find(_T("\\"));
									while (p1 != -1)
									{
										file_p = p1;
										p1 = keyDir.Find(_T("\\"),p1+1);
									}
									CString keyName;
									if (file_p != -1)
										keyName = keyDir.Right(keyDir.GetLength()-file_p-1);
									else
										keyName = keyDir;
									//
									XmlElement keyInfo = CreateDriveKeyInfo_RF1a(
										doc, 
										keyDir, 
										_T("."), 
										keyName, 
										woBin 
										);
									//
									if (keyInfo.HasAttribute(L"PubKeyHash")) // ������ ���� 
									{ 
										bool use = true;
										//
										if (lookupPkh64.GetLength() > 0) 
										{
											string pkh64a = keyInfo.GetAttribute(L"PubKeyHash");
											string pkh64 = NormalizeBin64(pkh64a); 
											//
											if (pkh64 != lookupPkh64) use = false; 
										}
										//
										if (use)
										{
											CommonKeyInfo_E.AppendChild(keyInfo);
										}
									}
								}
							}
						}
					}
					//
					bool localKeyX = false;
					{
						XmlNodeList L = CommonKeyInfo_E.SelectNodes(L"*");
						if (L.Count() > 0) localKeyX = true; 
					}
					//
					// ��������� ���������� � ������ �� eToken 
					//
					if (0 == 1)
					{
						try
						{
							// int threadId = (int)GetCurrentThreadId(); 
							XmlDocument doc = PKCS11_Manager_().GetETokenInfo(L""); 
							//
							XmlNodeList L = doc.SelectNodes(L"*/EToken"); 
							//if (L.Count() == 0)
							//{
							//	if (! localKeyX) PKCS11_Manager_().LoginFirstEToken(); 
							//	doc = PKCS11_Manager_().GetETokenInfo(L""); 
							//	L = doc.SelectNodes(L"*/EToken"); 
							//}
							for (int i = 0; i < L.Count(); ++i) 
							{
								XmlElement eToken_E = L[i];
								//
								string eTokenID = eToken_E.GetAttribute(L"eTokenID"); 
								//
								////AddETokenKeysXmlInfo(eTokenID, 1, CommonKeyInfo_E, activePkh, filter); 
								AddETokenKeysXmlInfo(eTokenID, 2, CommonKeyInfo_E, filter); 
							}
						}
						catch(::::Exception e)
						{
							OutputDebugStringW(e.ToString()); 
							//
							OutputDebugStringW(L"%%% (3)"); 
	#						ifdef _DEBUG
							{
								//throw;
							}
	#						endif
							//
							int severityLevel = e.m_SeverityLevel; 
							if (severityLevel == ::::Exception::SeverityError) throw; 
						}
						catch(...) 
						{ 
							OutputDebugStringW(L"%%% (4)"); 
							/// throw; 
						}
						//
						//
						XmlNodeList L = CommonKeyInfo_E.SelectNodes(L"KeyInfo[@KeyMediaType='eToken']"); 
						for (int k = 0; k < L.Count(); k++)
						{
							XmlElement keyInfo = L[k]; 
							//
							XmlNodeList L2 = keyInfo.SelectNodes(L"C0"); 
							if (L2.Count() > 0) 
							{
								XmlElement C0 = L2[0]; 
								//
								string certData64 = C0.InnerText(); 
								certData64.Trim(); 
								if (certData64.GetLength() > 0) 
								{
									Blob certData = FromBase64String(certData64); 
									CCOM_Certificate cert;
									cert->Import(certData); 
									//
									string certPkh64 = __ToBase64String(cert->GetPKH()); 
									//
									XmlElement CertInfo_E = cert->GetXmlInfo(woBin); 
									CertInfo_E.SetAttribute(L"PubKeyHashUrlEnc",
										UrlEncode(Base64Text_4Url(certPkh64))
										);
									keyInfo.AppendChild(CertInfo_E); 
									//
									PrepareCertAttributesForXml(CertInfo_E, certData, cert); 
								}
							}
							for (int k = 0; k < L2.Count(); k++) 
							{
								keyInfo.RemoveChild(L2[k]); 
							}
						}
					}
					//
	//#				ifdef _DEBUG
					//TRACE_LOG(_T("KeyInfo[") + _S(searchPkh64) + _T("]"));  
					//TRACE_LINE(doc.DocumentElement().OuterXml());
	//#				endif
					//
					if (doc.IsEmpty())
					{
						throw MethodError(L"�� ������� ��������� CommonKeyInfo (10)"); 
					}
#					ifdef _DEBUG
					else
					{
						//TRACE_LINE(_T("CommonKeyInfo Document: ") + FormatStr(_T("0x%x"),(int)doc.GetXmlObjectInterface()) )
					}
#					endif
					//
					try
					{
						AnalyzeCommonKeyInfo(doc); 
					}
					catch(::::Exception //e1
						)
					{
					}
					catch(...)
					{
					}
					//
					if (useCache)
					{
						ObjCache::AddXmlObject(id, 2 * _OC_TIMEOUT_CCI, doc); 
					}
					//
					return doc;
				}
				_Catch()
			}

			////ISlotClient* GetCurrentClient() // borrowed reference 
			////{
			////	try
			////	{
			////		ISlotClient* client = ClientMap::Clients().GetClient(Blob(), require); // borrowed reference, activate or not  
			////		return client; 
			////	}
			////	_Catch() 
			////}

			void SetClientInfo_CommonKeyInfo(
				XmlDocument& doc, 
				ISlotClient* client_ 
				)
			{
				try
				{
					// ISlotClient* client = client_ ? client_ : GetCurrentClient(); 
					//
					ISlotClient* client = client_; 
					//
					Blob activePkh; 
					//
					if (client)
					{
						CComBSTR bstrActivePkh64; 
						HRESULT rc = client->get_PublicKeyHash(&bstrActivePkh64); 
						if (rc == S_OK) 
						{
							if (bstrActivePkh64.Length() > 0)
							{
								activePkh = FromBase64String(_W(bstrActivePkh64)); 
							}
						}
					}
					//
					if (activePkh.Length() > 0)
					{
						string activePkh64 = __ToBase64(activePkh); 
						//
						bool done = false; 
						//
						XmlNodeList L = doc.SelectNodes(L"/*/KeyInfo"); 
						for (int k = 0; k < L.Count() && (!done); k++)
						{
							XmlElement keyInfo_E = (XmlElement)L[k]; 
							//
							if (keyInfo_E.HasAttribute(L"PubKeyHash"))
							{
								string currentPkh64 = __ToBase64(FromBase64String(keyInfo_E.GetAttribute(L"PubKeyHash")));
								//
								if (currentPkh64 == activePkh64) 
								{
									done = true; 
									//
									keyInfo_E.SetAttribute(_W(L"Active"), _W(L"true")); 
								}
							}
						}
					}
				}
				_Catch()
			}



			// �������������� XML-��������� CommonKeyInfo ��������� ��������� 
			// 
			inline XmlDocument CommonKeyInfoDocument( 
				// ���������� ������� 
				bool includeGood=true, 
				const string& onlyThisPkh64=L"" 
				) 
			{
				try
				{
					Blob activePkh; 
					//
					Map<string,string> filter; 
					if (includeGood) filter[L"include-good"] = L"1"; 
					if (onlyThisPkh64.GetLength() > 0)
					{
						filter[L"lookup-pkh"] = onlyThisPkh64; 
					}
					//
					bool useCache = true;
					string id = _W(L"CommonKeyInfo_") + 
						L"_pkh" + onlyThisPkh64 + L"_" + 
						(includeGood ? L"1" : L"0" );
					//
					if (!filter.IsEmpty()) useCache = false; 
					//
					if (useCache)
					{
						XmlDocument cachedDoc; 
						if (ObjCache::GetXmlObject(id, cachedDoc))
						{
							return cachedDoc;
						}
					}
					//
					XmlDocument d = Instance().PrepareCommonKeyInfo_RF1a(   
						false, 
						filter, 
						false 
						); 
					//
					if (useCache)
					{
						ObjCache::AddXmlObject(id, _OC_TIMEOUT_CCI, d); 
					}
					//
					return d; 
				}
				_Catch() 
			}



			// -----------------------------------------------------------------------------------
			// 

			//Blob GetActivePkh_1()
			//{
			//	try
			//	{
			//		Blob activePkh; 
			//		//
			//		// ClientMap::Clients().GetCurrentClient
			//		//
			//		if (client)
			//		{
			//			CComBSTR bstrActivePkh64; 
			//			HRESULT rc = client->get_PublicKeyHash(&bstrActivePkh64); 
			//			if (rc == S_OK) 
			//			{
			//				if (bstrActivePkh64.Length() > 0)
			//				{
			//					activePkh = FromBase64String(_W(bstrActivePkh64)); 
			//				}
			//			}
			//		}
			//		//
			//		return activePkh; 
			//	}
			//	_Catch() 
			//}

			inline void DeviceInfo_Key_GU(XmlElement& Key_E) 
			{
				try
				{
					// obsolete:
					//
					string pkh64; 
					if (Key_E.HasAttribute(L"PubKeyHash"))
					{
						pkh64 = Key_E.GetAttribute(L"PubKeyHash"); 
						pkh64 = __ToBase64(FromBase64String(pkh64)); 
					}
					//
					if (pkh64.GetLength() > 0) 
					{
						Blob aPkh = ClientMap::Clients().GetActivePkh_1(); 
						if (aPkh.Length() > 0)
						{
							string aPkh64 = __ToBase64(aPkh); 
							if (pkh64 == aPkh64) 
							{
								Key_E.SetAttribute(L"IsActive", _W(L"true")); 
							}
						}
					}
				}
				_Catch() 
			}

			inline void DeviceInfo_Device_Drive_Expand( 
				XmlElement& Device_E, 
				XmlDocument doc, 
				const string& driveLetter 
				)
			{
				try
				{
					XmlElement RemovableDrive_E = doc.CreateElement(L"", L"RemovableDrive", L""); 
					//
					if (DriveIsSpecial_102(driveLetter)) Device_E.SetAttribute(L"special-102", _W(L"true")); 
					//
					// ----
					// Key folders 
					//
					XmlElement Keys_E = doc.CreateElement(L"", L"Keys", L""); 
					Device_E.AppendChild(Keys_E); 
					//
					CString xDrivePath = ExtraDriveInfoLine(_S(driveLetter)); 
					//
					CString driveRoot;
					if (_S(driveLetter).GetLength() == 1)
					{
						driveRoot = _S(driveLetter) + _T(":\\"); 
					}
					else if (xDrivePath.GetLength() == 1) 
					{
						driveRoot = _S(xDrivePath) + _T(":\\"); 
					}
					else if (xDrivePath.GetLength() > 1) 
					{
						driveRoot = xDrivePath; 
						if (driveRoot[driveRoot.GetLength()] != _T('\\')) driveRoot += _T("\\"); 
					}
					else
					{
						throw MethodError(_W(L"Invalid drive letter: ") + driveLetter); 
					}
					//
					CString Root = driveRoot + _T("");
					//
					if (Machine::DirectoryExists(Root))
					{
						CString certDir = Root + _T("\\Certificates"); 
						//
						if (Machine::DirectoryExists(certDir))
						{
							SharedArray<CString> keyDirs = Machine::ListFiles(certDir);   
							//
							for (int k = 0; k < keyDirs.Length(); ++k)
							{
								CString keyDir = keyDirs[k];
								//
								SharedArray<CString> pkXmlPaths = Machine::ListFiles(keyDir,_T("*-k.xml")); 
								//
								if (pkXmlPaths.Length() > 0)
								{
									XmlDocument keyInfoDoc; 
									CString pkPath = pkXmlPaths[0]; 
									keyInfoDoc.Load(_W(pkPath)); 
									XmlElement keyInfo = keyInfoDoc.DocumentElement(); 
									//
									int file_p = -1;
									int p1 = keyDir.Find(_T("\\"));
									while (p1 != -1)
									{
										file_p = p1;
										p1 = keyDir.Find(_T("\\"),p1+1);
									}
									CString keyName;
									if (file_p != -1)
										keyName = keyDir.Right(keyDir.GetLength()-file_p-1);
									else
										keyName = keyDir;
									//
									bool use = true; 
									//
									string pkh64; 
									//
									if (!keyInfo.HasAttribute(L"PubKeyHash")) 
									{ 
										use = false; 
									}
									else
									{
										pkh64 = keyInfo.GetAttribute(L"PubKeyHash"); 
									}
									//
									// ----
									// ��������� ����������
									//
									Blob certData; 
									CCOM_Certificate cert;
									//
									if (use)
									{
										SharedArray<CString> certPaths = Machine::ListFiles(keyDir,_T("*.cer"));
										bool certFound = false;
										for (int i = 0; i < certPaths.Length() && (! certFound); ++i)
										{
											CString certPath = certPaths[i];
											//
											::::File f;
											f.Open(certPath);
											certData = f.ReadAll();
											f.Close();
											//
											// CCOM:
											//
											try
											{
												cert->Import(certData);
												//
												string certPkh64 = __ToBase64String(cert->GetPKH());
												if (
													((certPkh64 == pkh64) || (certPkh64+L"=" == pkh64) || (certPkh64 == pkh64+L"="))
													|| (pkh64.GetLength() == 0)
													)
												{
													certFound = true;
												}
											}
											catch(Exception& e)
											{
												TRACE_LOG(e.ToString());
											}
											catch(...)
											{
												TRACE_LOG(_T("����������� ������!"));
											}
										}
										//
										if (!certFound) use = false; 
									}
									//
									if (use)
									{
										XmlElement Key_E = doc.CreateElement(L"", L"Key", L""); 
										//
										Key_E.SetAttribute(L"CryptoSystem", _W("CryptoCOM")); 
										Key_E.SetAttribute(L"KeyMediaType", _W("drive")); 
										//
										Key_E.SetAttribute(L"PubKeyHash", pkh64); 
										//
										Key_E.SetAttribute(L"KeyPath", _W(keyDir)); 
										//
										Key_E.SetAttribute(L"KeyName", _W(keyName)); 
										//
										string keyTime = keyInfo.GetAttribute(L"KeyTime"); 
										Key_E.SetAttribute(L"KeyTime", keyTime); 
										//
										// ---- 
										// ���������� 
										//
										PrepareCertAttributesForXml(Key_E, certData, cert); 
										//
										DeviceInfo_Key_GU(Key_E); 
										//
										Keys_E.AppendChild(Key_E); 
									}
								}
							}
						}
					}
					//
					// ----
					// Adding the node 
					//
					Device_E.AppendChild(RemovableDrive_E); 
				}
				_Catch() 
			}

			inline CString Drive_ObjectPathByLabel(const string& driveLetter, const string& label) 
			{
				try
				{
					CString driveRoot = driveLetter + _T(":\\");
					CString Root = driveRoot + _T("");
					CString path = Root + _T("\\") + _S(label) + _T(".der"); 
					//
					return path; 
				}
				_Catch() 
			}

			inline Blob Drive_ReadObject(const string& driveLetter, const string& label) 
			{
				try
				{
					CString path = Drive_ObjectPathByLabel(driveLetter, label); 
					//
					File f;
					f.Open(path); 
					Blob data = f.ReadAll(); 
					f.Close(); 
					//
					return data; 
				}
				_Catch() 
			}

			inline void Drive_SaveObject(const string& driveLetter, const string& label
				, Blob data 
				) 
			{
				try
				{
					CString path = Drive_ObjectPathByLabel(driveLetter, label); 
					//
					File f;
					f.OpenToWrite(path); 
					f.Replace((const char*)data.GetBuffer(), data.Length()); 
					f.Close(); 
				}
				_Catch() 
			}

			XmlElement DeviceInfo_Device_Drive(
				XmlDocument doc, 
				const string& driveLetter 
				)
			{
				try
				{
					XmlElement Device_E = doc.CreateElement(L"", L"Device", L""); 
					Device_E.SetAttribute(_W(L"DeviceType"), _W(L"RemovableDrive")); 
					Device_E.SetAttribute(L"DriveLetter", _W(driveLetter)); 
					Device_E.SetAttribute(L"DeviceID", _W(driveLetter)); 
					//
					DeviceInfo_Device_Drive_Expand(Device_E, doc, driveLetter); 
					//
					return Device_E; 
				}
				_Catch() 
			}

			//inline void Drive_CreateMetaObjects(AsnObject& out_privateMeta, AsnObject& out_freeMeta, 
			//	XmlDocument& deviceInfo) 
			//{
			//	try
			//	{
			//		AsnObject privateMeta; 
			//		AsnObject freeMeta; 
			//		//
			//		//
			//		out_privateMeta = privateMeta; 
			//		out_freeMeta = freeMeta; 
			//	}
			//	_Catch()
			//}

			XmlElement DeviceInfo_Device_eToken(
				XmlDocument doc, 
				XmlElement EToken_E  
				)
			{
				try
				{
					XmlElement Device_E = doc.CreateElement(L"", L"Device", L""); 
					Device_E.SetAttribute(_W(L"DeviceType"), _W(L"eToken"));
					//
					string eTokenID = EToken_E.GetAttribute(L"eTokenID"); 
					//
					Device_E.SetAttribute(L"DeviceID", eTokenID); 
					//
					XmlNode n1 = EToken_E.Clone(); 
					Device_E.AppendChild(n1); 
					//
					EToken& eToken = EToken::OpenEToken(eTokenID); 
					XmlElement Keys_E = eToken.CreateDeviceKeysInfo(doc); 
					{
						XmlNodeList L = Keys_E.SelectNodes(L"Key"); 
						for (int k = 0; k < L.Count(); k++) 
						{
							XmlElement Key_E = L[k]; 
							//
							XmlNodeList L2 = Key_E.SelectNodes(L"C0"); 
							if (L2.Count() > 0) 
							{
								XmlElement C0 = L2[0]; 
								//
								string certData64 = C0.InnerText(); 
								certData64.Trim(); 
								if (certData64.GetLength() > 0)
								{
									Blob certData = FromBase64String(certData64); 
									//
									// ---- 
									// ���������� 
									//
									if (certData.Length() > 0) 
									{
										CCOM_Certificate cert; 
										cert->Import(certData); 
										//
										PrepareCertAttributesForXml(Key_E, certData, cert); 
									}
								}
							}
							for (int j = 0; j < L2.Count(); j++)
							{
								Key_E.RemoveChild(L2[j]); 
							}
						}
					}
					Device_E.AppendChild(Keys_E); 
					//
					///DeviceInfo_Device_eToken_Expand(Device_E, doc, eToken); 
					//
					return Device_E; 
				}
				_Catch() 
			}

			//inline void DeviceInfo_Device_eToken_Expand(
			//	XmlElement& Device_E, 
			//	XmlDocument doc, 
			//	EToken& eToken 
			//	)
			//{
			//	try
			//	{
			//		// ----
			//		// Key folders 
			//		//
			//		XmlElement Keys_E = doc.CreateElement(L"", L"Keys", L""); 
			//		Device_E.AppendChild(Keys_E); 
			//		//
			//		CString driveRoot = _S(driveLetter) + _T(":\\"); 
			//		CString Root = driveRoot + _T("");
			//		//
			//		if (Machine::DirectoryExists(Root))
			//		{
			//			CString certDir = Root + _T("\\Certificates"); 
			//			//
			//			if (Machine::DirectoryExists(certDir))
			//			{
			//				SharedArray<CString> keyDirs = Machine::ListFiles(certDir);   
			//				//
			//				for (int k = 0; k < keyDirs.Length(); ++k)
			//				{
			//					CString keyDir = keyDirs[k];
			//					//
			//					SharedArray<CString> pkXmlPaths = Machine::ListFiles(keyDir,_T("*-k.xml")); 
			//					//
			//					if (pkXmlPaths.Length() > 0)
			//					{
			//						XmlDocument keyInfoDoc; 
			//						CString pkPath = pkXmlPaths[0]; 
			//						keyInfoDoc.Load(_W(pkPath)); 
			//						XmlElement keyInfo = keyInfoDoc.DocumentElement(); 
			//						//
			//						int file_p = -1;
			//						int p1 = keyDir.Find(_T("\\"));
			//						while (p1 != -1)
			//						{
			//							file_p = p1;
			//							p1 = keyDir.Find(_T("\\"),p1+1);
			//						}
			//						CString keyName;
			//						if (file_p != -1)
			//							keyName = keyDir.Right(keyDir.GetLength()-file_p-1);
			//						else
			//							keyName = keyDir;
			//						//
			//						bool use = true; 
			//						//
			//						string pkh64; 
			//						//
			//						if (!keyInfo.HasAttribute(L"PubKeyHash")) 
			//						{ 
			//							use = false; 
			//						}
			//						else
			//						{
			//							pkh64 = keyInfo.GetAttribute(L"PubKeyHash"); 
			//						}
			//						//
			//						// ----
			//						// ��������� ����������
			//						//
			//						Blob certData; 
			//						CCOM_Certificate cert;
			//						//
			//						if (use)
			//						{
			//							SharedArray<CString> certPaths = Machine::ListFiles(keyDir,_T("*.cer"));
			//							bool certFound = false;
			//							for (int i = 0; i < certPaths.Length() && (! certFound); ++i)
			//							{
			//								CString certPath = certPaths[i];
			//								//
			//								::::File f;
			//								f.Open(certPath);
			//								certData = f.ReadAll();
			//								f.Close();
			//								//
			//								// CCOM:
			//								//
			//								try
			//								{
			//									cert->Import(certData);
			//									//
			//									string certPkh64 = __ToBase64String(cert->GetPKH());
			//									if (
			//										((certPkh64 == pkh64) || (certPkh64+L"=" == pkh64) || (certPkh64 == pkh64+L"="))
			//										|| (pkh64.GetLength() == 0)
			//										)
			//									{
			//										certFound = true;
			//									}
			//								}
			//								catch(Exception& e)
			//								{
			//									TRACE_LOG(e.ToString());
			//								}
			//								catch(...)
			//								{
			//									TRACE_LOG(_T("����������� ������!"));
			//								}
			//							}
			//							//
			//							if (!certFound) use = false; 
			//						}
			//						//
			//						if (use)
			//						{
			//							XmlElement Key_E = doc.CreateElement(L"", L"Key", L""); 
			//							//
			//							Key_E.SetAttribute(L"CryptoSystem", _W("CryptoCOM")); 
			//							Key_E.SetAttribute(L"KeyMediaType", _W("drive")); 
			//							//
			//							Key_E.SetAttribute(L"PubKeyHash", pkh64); 
			//							//
			//							Key_E.SetAttribute(L"KeyPath", _W(keyDir)); 
			//							//
			//							Key_E.SetAttribute(L"KeyName", _W(keyName)); 
			//							//
			//							string keyTime = keyInfo.GetAttribute(L"KeyTime"); 
			//							Key_E.SetAttribute(L"KeyTime", keyTime); 
			//							//
			//							// ---- 
			//							// ���������� 
			//							//
			//							PrepareCertAttributesForXml(Key_E, certData, cert); 
			//							//
			//							DeviceInfo_Key_GU(Key_E); 
			//							//
			//							Keys_E.AppendChild(Key_E); 
			//						}
			//					}
			//				}
			//			}
			//		}
			//		//
			//		// ----
			//		// Adding the node 
			//		//
			//		Device_E.AppendChild(RemovableDrive_E); 
			//	}
			//	_Catch() 
			//}

			XmlElement DeviceInfo_Key_Drive(
				XmlDocument doc, 
				const string& driveLetter 
				)
			{
				try
				{
				}
				_Catch() 
			}

			inline void DeviceInfo_GU(XmlElement& Device_E) 
			{
				try
				{
				}
				_Catch() 
			}

			XmlDocument DeviceInfo() 
			{
				try
				{
					// Lock lock;
					//
					XmlDocument doc;
					doc.LoadXml(DeviceInfoTemplate()); 
					if (doc.IsEmpty())
					{
						throw MethodError(L"�� ������� ��������� DeviceInfo (T)");  
					}
					//
					XmlElement DeviceInfo_E = doc.DocumentElement(); 
					//
					SharedArray<CString> removableDrives = GetKeyDrives();
					//
					for (int drive_i = 0; drive_i < removableDrives.Length(); ++drive_i)
					{
						CString driveLetter = removableDrives[drive_i]; 
						//
						XmlElement Device_E = DeviceInfo_Device_Drive(doc, _W(driveLetter)); 
						DeviceInfo_GU(Device_E); 
						DeviceInfo_E.AppendChild(Device_E); 
					}
					//
					SharedArray<CString> xDrives = GetExtraKeyDrives();
					//
					for (int drive_i = 0; drive_i < xDrives.Length(); ++drive_i)
					{
						CString driveLetter = xDrives[drive_i]; 
						//
						XmlElement Device_E = DeviceInfo_Device_Drive(doc, _W(driveLetter)); 
						DeviceInfo_GU(Device_E); 
						DeviceInfo_E.AppendChild(Device_E); 
					}
					//
					try
					{
						XmlDocument d2 = PKCS11_Manager_().GetETokenInfo(L""); 
						//
						XmlNodeList EToken_L = d2.SelectNodes(L"/*/EToken");   
						for (int k = 0; k < EToken_L.Count(); k++) 
						{
							XmlElement EToken_E = EToken_L[k]; 
							//
							XmlElement Device_E = DeviceInfo_Device_eToken(doc, EToken_E); 
							DeviceInfo_GU(Device_E); 
							DeviceInfo_E.AppendChild(Device_E); 
							//
							XmlNodeList Key_L = Device_E.SelectNodes(L"Keys/Key"); 
							for (int i = 0; i < Key_L.Count(); i++)
							{
								XmlElement Key_E = Key_L[i];
								DeviceInfo_Key_GU(Key_E); 
							}
						}
					}
					catch(::::Exception e)
					{
						OutputDebugStringW(e.ToString()); 
						//
						OutputDebugStringW(L"%%% (3)"); 
#						ifdef _DEBUG
						{
							//throw;
						}
#						endif
						//
						int severityLevel = e.m_SeverityLevel; 
						if (severityLevel == ::::Exception::SeverityError) throw; 
					}
					catch(...) 
					{ 
						OutputDebugStringW(L"%%% (4)"); 
						/// throw; 
					}
					//
					// EToken::OutputXml(DeviceInfo_E.OuterXml(), L"DeviceInfo"); 
					//
					return doc; 
				}
				_Catch() 
			}



			// -----------------------------------------------------------------------------------
			// Key management

			// string 


			// -----------------------------------------------------------------------------------
			// �����������

			//void SimpleFindCertificate()
			//{
			//	try
			//	{
			//		// ----
			//		// ���� ���������� �� ����-���������
			//		//
			//		CString clientPkh64 = _S(GetOption(L"client-pkh")); 
			//		//
			//		ActivatePkh(string(clientPkh64));
			//		//
			//		return; // ������ ��������� ���� �� ����������! 
			//		//
			//		//// ----
			//		//// ���� ���������� � ���������������� account'�
			//		////
			//		//CString root = GetCabinetApp().GetRoot();
			//		////
			//		//SharedArray<CString> keyDirs = Machine::ListFilesDeep1(
			//		//	root,_T("*"),_T("\\Certificates"));
			//		////
			//		//bool done = false;
			//		//for (int k = 0; k < keyDirs.Length() && (! done); ++k)
			//		//{
			//		//	CString keyDir = keyDirs[k];
			//		//	//
			//		//	SharedArray<CString> certPaths = Machine::ListFiles(keyDir,_T("*.cer"));
			//		//	for (int i = 0; i < certPaths.Length(); ++i)
			//		//	{
			//		//		CString certPath = certPaths[i];
			//		//		//
			//		//		TRACE_LOG1(_T("������ ����������: %s"), certPath.GetString() );
			//		//		//
			//		//		Blob certData;
			//		//		Slot::File f;
			//		//		f.Open(certPath);
			//		//		certData = f.ReadAll();
			//		//		f.Close();
			//		//		//
			//		//		// CCOM:
			//		//		//
			//		//		CCOM_Certificate cert;
			//		//		cert->Import(certData);
			//		//		//
			//		//		SharedArray<CString> keyInfoPaths = Machine::ListFiles(keyDir,_T("*-k.xml"));
			//		//		if (keyInfoPaths.Length() == 0) 
			//		//			throw MethodError(_S("���� �� ������! ") + cert->SerialNumber);
			//		//		//
			//		//		CString keyInfoPath = keyInfoPaths[0];
			//		//		CString keyContainerPath = keyDir + _T("\\Container");
			//		//		//
			//		//		CCOM_Key key;
			//		//		XmlDocument d;
			//		//		d.Load((string)keyInfoPath);
			//		//		key->SetPath(keyContainerPath);
			//		//		key->SetXmlInfo(d.DocumentElement());
			//		//		cert->SetKey(key);
			//		//		//
			//		//		certificate = cert;
			//		//		return; // ������! 
			//		//	}
			//		//}
			//	}
			//	_Catch()
			//}

			//void FindCertificateBySlot(int slotId)
			//{
			//	try
			//	{
			//	}
			//	_Catch()
			//}

			//bool SetCertificate(const CCOM_Certificate cert)
			//{
			//	certificate = cert;
			//	return true;
			//}











		// ----
		// XML-��������  

		virtual string GetConfigTag() 
		{
			return _W(_PROTOCOL_CONFIG_TAG); 
		}

		inline string ContextXmlTemplate()
		{
			string s = FormatStr(_W(COMMON_XML_START) + L"<%s />", _W(GetConfigTag()).GetString() );
			return s; 
		}

		inline IXMLDOMElement* OpenContextXml() // borrowed 
		{
			try
			{
				if (! m_ContextXml.IsEmpty()) return ContextRoot();
				//
#					if (UFML3_FILTER_CONFIG_USE_FILE == 1)
				{
					CString home = Home();
					//
					CString configDir = Util::CreateDirectoryAndTest( home + _T("\\Config") );
					if (configDir.GetLength() == 0) 
					{
						throw MethodError(E__FILTER_CANNOT_GET_RESOURCE).AddIfNewSource_(configDir); 
					}
					//
					CString filterXmlPath = configDir + _T("\\") + UFML3_FILTER_CONFIG_FILENAME; 
					//
					ContextLoad(filterXmlPath);
				}
#					else
				{
					ContextLoadXmlStr(ContextXmlTemplate());
				}
#					endif
				//
				return ContextRoot();
			}
			_Catch()
		}



		// ----
		// ������������ 

		bool m_Started;

		InstanceCtx()
		{
			// OpenContextXml();
			//
			m_Started = false; 
		}

	public:
		inline static InstanceCtx& InstanceForUser() 
		{
			static InstanceCtx<_InstanceBase,_ApplicationCtx,InstanceType_User> s_Instance;
			return s_Instance; 
		}

		inline static InstanceCtx& InstanceForMachine() 
		{
			static InstanceCtx<_InstanceBase,_ApplicationCtx,InstanceType_Machine> s_Instance;
			return s_Instance; 
		}

		inline static InstanceCtx& Instance() 
		{
			return InstanceForUser(); 
		}



		// ----
		// �������� ��� Application 
		//
		// --> ����� _AppInstance 
	}; 

} // namespace  
