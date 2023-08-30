/*
 SlotPKI.h : ������� ��� ������ � ������� � ������������� ������� ��������. 

 $Name:  $
 $Revision: 1.1.2.4 $
 $Date: 2008/11/01 11:50:37 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


#include <low-level/SmartEToken.h>
#include <low-level/SmartMachine.h>
#include <low-level/SmartUtil.h>
//
#include <SlotSysUtil.h>
#include <SlotCSP_CCOM.h>
#include <SlotXmlStructures.h>


namespace  {

	// ----
	// PKI 

	namespace PKI
	{
		// =======================================================================================
		// ����� �� ��������� 
		// =======================================================================================

		class PKI_Util 
		{
		public: 
			// ===================================================================================
			// ��������������� ������� 

			inline static string RCXml(HRESULT rc,const string& description) throw() 
			{
				string xml_t = _W(COMMON_XML_START) + L"\n" 
						L"<hr value=\"0x%x\" service-name=\"Protocol\">\n"
						L"%s\n"
						L"</hr>"
						;
				string xml = FormatStr(xml_t, (int)rc, description.GetString() ); 
				//
				return xml;
			}

			// ===================================================================================
			// ������������ (machine/user) 
		};















		// =======================================================================================
		// ���������� � ������ � ������������ ������������ ��� ����������� � ������� ������ ������� 
		// =======================================================================================

		class CabinetKeysMgr 
		{
		public:
			inline static CabinetKeysMgr& Acquire() 
			{
				static CabinetKeysMgr s_CabinetKeys; 
				return s_CabinetKeys; 
			}

#			define CabinetKeys_() (::::PKI::CabinetKeysMgr::Acquire()) 



		protected:
			inline Protocol::AppCtx& Instance() 
			{
				return Protocol::AppCtx::Instance(); 
			}



		public:
			// ===================================================================================
			// ���������� � ������ � ������������: ����� XML-������� 

			inline string GetXslUrl( 
				const string& xslUrl,
				const string& xslUrlOption 
				) 
			{
				try
				{
					string myXslUrl = xslUrl.GetLength() > 0 ? xslUrl : Instance().GetOption(xslUrlOption); 
					//
					return myXslUrl; 
				}
				_Catch() 
			}



			inline string GetXslStyleSheetLine(
				const string& xslUrlOption,  
				bool useXsl=false, 
				//
				const string& xslUrl=L"",
				bool useXslBase=false,
				const string& xslBase=L"" 
				)
			{
				try
				{
					string myXslUrl = GetXslUrl(xslUrl,xslUrlOption); 
					//
					string line = XmlStructures::PrepareXslStyleSheetLine( 
						useXsl, 
						//
						myXslUrl, 
						useXslBase, 
						xslBase, 
						//
						Instance().GetOption(L"xsl-base")  
						); 
					//
					return line; 
				}
				_Catch() 
			}



			// ���������� ��������� �� ��������� �� ������ xsl-base � ��������� defaultXslBase � URL 

			inline string GetXslStyleSheetLineWBase(
				const string& xslUrlOption,  
				bool useXsl=false, 
				//
				const string& xslUrl=L"" 
				)
			{
				try
				{
					string line = GetXslStyleSheetLine(xslUrlOption,useXsl,xslUrl,true); 
					//
					return line; 
				}
				_Catch() 
			}






			// ===================================================================================
			// ����������� 

			// -----------------------------------------------------------------------------------
			// ����� ��������� 

			// ����� ������� CertItem, ��������� � Info_E 

			inline static XmlElement NewCertItem(XmlElement Info_E,string xsi_type,bool addTo=true)
			{
				try
				{
					XmlElement CertItem_E = Info_E.OwnerDocument().CreateElement(L"",L"CertItem",L"");
					CertItem_E.SetAttribute(L"xsi:type", xsi_type);
					//
					if (addTo) Info_E.AppendChild(CertItem_E);
					//
					return CertItem_E;
				}
				_Catch() 
			}



			// ����� ������� CertItem, ��������� � CertItem_E 

			inline static XmlElement NewAttributeElement(XmlElement CertItem_E, 
				string name, string value,bool addTo=true)
			{
				try
				{
					XmlElement Attribute_E = CertItem_E.OwnerDocument().CreateElement(L"",L"Attribute",L"");
					Attribute_E.SetAttribute(L"name",name);
					Attribute_E.InnerText() = value; 
					//
					if (addTo) CertItem_E.AppendChild(Attribute_E); 
					//
					return Attribute_E;
				}
				_Catch() 
			}









			// -----------------------------------------------------------------------------------
			// ��������� RequestInfo 

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
					pkh64 = __ToBase64(pkh);
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
#					ifdef _DEBUG
					{
						//OutputDebugString(doc.DocumentElement().OuterXml()); 
					}
#					endif 
					//
					return doc;
				}
				_Catch()
			}



			XmlDocument GetRequestInfo(AsnObject& requestO,AsnObject& requestExtra) 
			{
				try
				{
					XmlDocument doc;
					doc.LoadXml(RequestInfoTemplate(false));
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
						NameDescription subjectExtraInfo(requestExtra[1]);
						for (X500::OidMap::Iterator i(X500::Oids()); i; ++i)
						{
							string alias = i.Id();
							if (alias.Left(9) == L"_PKI_")
							{
								string oid = i;
								//
								SharedPtr<AsnObject> spAttr = subjectExtraInfo.GetAttribute(OID(oid));
								if (! spAttr.IsEmpty())
								{
									NewAttributeElement(Subject_E,L"oid."+oid,spAttr->m_text); 
								}
							}
						}
					}
					//
#					ifdef _DEBUG
					{
						//OutputDebugString(doc.DocumentElement().OuterXml());
					}
#					endif 
					//
					return doc;
				}
				_Catch()
			}












			// ----
			// �����: CommonKeyInfo 

			inline string CommonKeyInfoTemplate(bool useXsl,const string& vXslUrl=L"") 
			{
				try
				{
					string t;
					//
					t = _W(COMMON_XML_START) + L"\n" + 
						GetXslStyleSheetLine(L"common-key-info-vxsl",useXsl,vXslUrl,true) + 
						L"<CommonKeyInfo>\n"
						L"</CommonKeyInfo>"
						;
					//
					return t;
				}
				_Catch() 
			}



			// ----
			// �����: KeyInfo 

			inline string GetKeyInfoXPath(const string& pkh64) 
			{
				try
				{
					Blob pkh = FromBase64String(pkh64); 
					string pkh64ver = __ToBase64(pkh); 
					//
					string xPath = 
						L"KeyInfo["
						L"RequestInfo/CertificateInfo/@PubKeyHash='" + pkh64ver + L"' or "
						L"RequestInfo/CertificateInfo/@PubKeyHash='" + pkh64ver + L"='" 
						L"]"
						;
					return xPath; 
				}
				_Catch() 
			}



			XmlElement CreateKeyInfo(XmlDocument doc, 
				const string& cryptoSystem,
				const string& keyMediaType
				)
			{
				try
				{
					XmlElement keyInfo = doc.CreateElement(L"",L"KeyInfo",L""); 
					//
					keyInfo.SetAttribute(L"CryptoSystem",cryptoSystem);
					keyInfo.SetAttribute(L"KeyMediaType",keyMediaType);
					//
					return keyInfo;
				}
				_Catch() 
			}






			// ----
			// �����: RequestInfo 

			inline string RequestStatusInfoTemplate(bool useXsl=true,const string& vXslUrl=L"")
			{
				try
				{
					string t;
					//
					t = _W(COMMON_XML_START) + L"\n" + 
						GetXslStyleSheetLine(L"request-status-info-vxsl",useXsl,vXslUrl,true) + L"\n" + 
						L"<RequestStatusInfo>\n"
						L"</RequestStatusInfo>"
						;
					//
					return t;
				}
				_Catch() 
			}



			inline string RequestInfoTemplate(bool useXsl,const string& vXslUrl=L"", 
				const string& vXslOption=L"request-info-vxsl" 
				)
			{
				try
				{
					static string t;
					//
					//  xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" 
					//
					t = _W(COMMON_XML_START) + L"\n" + 
						GetXslStyleSheetLineWBase(vXslOption,useXsl,vXslUrl) + L"\n" + 
						L"<RequestInfo>\n"
						L"<CertificateInfo>\n"
						L"</CertificateInfo>\n"
						L"</RequestInfo>"
						;
					//
					return t;
				}
				_Catch() 
			}



			string RequestInfoPrintTemplate(bool useXsl,const string& vXslUrl=L"") 
			{
				try
				{
					return RequestInfoTemplate(useXsl,vXslUrl,L"request-info-print-vxsl"); 
				}
				_Catch() 
			}









			// ===================================================================================
			// ����� 

			// -----------------------------------------------------------------------------------
			// ����� �� �������� ��������� 

			// ----
			// ����� 

			// ������ DriveInfo 

			inline string DriveInfoTemplate(bool useXsl,const string& vXslUrl=L"") 
			{
				try
				{
					string t;
					//
					t = _W(COMMON_XML_START) + L"\n" + 
						GetXslStyleSheetLineWBase(L"drive-info-vxsl",useXsl,vXslUrl) + L"\n" + 
						L"<DriveInfo>\n"
						L"</DriveInfo>"
						;
					//
					return t;
				}
				_Catch() 
			}



			// ----
			// KeyInfo 

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



			SharedArray<CString> GetKeyDrives() 
			{
				try
				{
					bool excludeDiskette = !(
						GetFlagValue(string(Instance().GetOption(L"special-101")))
						);
					//
					CString useDrive = _S(Instance().GetOption(L"special-102"));
					//
					SharedArray<CString> drives = Machine::ListDrives(DRIVE_REMOVABLE,excludeDiskette, 
						useDrive);
					//
					CString addDrivesList = _S(Instance().GetOption(L"special-103"));
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



			SharedArray<int> GetETokeenPorts() 
			{
				try
				{
					SharedArray<int> ports; 
					ports.Add(0); 
					ports.Add(1); 
					return ports; 
				}
				_Catch()
			}



			XmlElement _del_CreateDriveKeyInfo(XmlDocument doc, 
				const CString& path,
				const CString& driveLetter, 
				const CString& keyName 
				)
			{
				try
				{
					XmlElement keyInfo = CreateKeyInfo(doc,L"CryptoCOM",L"drive");
					//
					keyInfo.SetAttribute(L"KeyPath",string(path));
					keyInfo.SetAttribute(L"DriveLetter",string(driveLetter));
					keyInfo.SetAttribute(L"KeyName",string(keyName));
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
						if (lookupPkh.Length() > 0)
						{
							string activePkh64 = __ToBase64String(lookupPkh);
							if (activePkh64 == pkh64)
							{
								CComBSTR bstrOn(L"true");  
								keyInfo.SetAttribute(L"IsActive",CComVariant(bstrOn)); 
							}
						}
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
								XmlElement CertInfo_E = cert->GetXmlInfo(); 
								CertInfo_E.SetAttribute(L"PubKeyHashUrlEnc",
									UrlEncode(Base64Text_4Url(certPkh64))
									);
								keyInfo.AppendChild(CertInfo_E);
								//
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
						XmlDocument requestInfo = GetRequestInfo(request,requestXO);
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
				_Catch() 
			}



			XmlElement AddDriveKeyInfo(XmlElement& CommonKeyInfo_E,
				const CString& path, 
				const CString& driveLetter, const CString& keyName 
				) 
			{
				try
				{
					XmlElement keyInfo = CreateDriveKeyInfo( 
						CommonKeyInfo_E.OwnerDocument(),
						path, 
						driveLetter,
						keyName, 
						Blob()
						);
					CommonKeyInfo_E.AppendChild(keyInfo); 
					return keyInfo;
				}
				_Catch() 
			}


















			// -----------------------------------------------------------------------------------
			// ����� �� eToken 

			// ----
			// �������������� eToken 

			// �����, ������ 

			SharedArray<SharedPtr<EToken> > eToken_GetAll(int* start=0,int* edge=0) 
			{
				try
				{
					SharedArray<SharedPtr<EToken> > eTokens = EToken::All(start,edge); 
					return eTokens; 
				}
				_Catch() 
			}

			inline EToken& eToken_Current() 
			{
				try
				{
					SharedArray<SharedPtr<EToken> > eTokens = eToken_GetAll(); 
					//
					if (eTokens.Length() == 0) 
						throw MethodError(HRESULT_FROM_WIN32(ERROR_NOT_FOUND)); 
					//
					EToken* pToken = eTokens[0].GetPointee(); 
					//
#					ifdef __DEBUG
					{
						pToken->SetPin(L"12345");  
					}
#					endif
					//
					return *pToken; 
				}
				_Catch() 
			}


			// ----
			// StatusObject: ���� ��� ������ � ������� 

#			define ETokenStatus_E_WrongMetaFile				(13000 + 501)
#			define ETokenStatus_E_WrongMetaFileStructure 	(13000 + 502)
#			define ETokenStatus_E_NoMetaFile				(13000 + 503)



			// ---- 
			// ������� �� eToken ��� ������ ���� 

			inline static string eToken_GetRootDir()
			{
				return _ETOKEN_ROOT; 
			}



			// ----
			// ����������-�����  

			string eToken_GetMetaPath(string* out_pRootDir=0) 
			{
				try
				{
					string RootDir = eToken_GetRootDir();
					string MetaPath = L"/" + RootDir + L"/" + _ETOKEN_META_FILE; 
					//
					if (out_pRootDir) *out_pRootDir = RootDir; 
					//
					return MetaPath; 
				}
				_Catch() 
			}



			inline string eToken_InfoXmlTemplate() 
			{
				return _W(COMMON_XML_START) + L"<ETokenInfo />"; 
			}



			SharedArray<string> eToken_FilePrefixTables() 
			{
				try
				{
					SharedArray<string> filePrefixTables; 
					//
					filePrefixTables.Add(L""); 
					filePrefixTables.Add(_ETOKEN_META_FILE_PREFIX); 
				}
				_Catch() 
			}



			SharedArray<string> eToken_SubdirTablePrefix() 
			{
				try
				{
					SharedArray<string> subdirPrefixTables; 
					//
					subdirPrefixTables.Add(L""); 
					subdirPrefixTables.Add(_ETOKEN_META_FILE_PREFIX); 
				}
				_Catch() 
			}



			//XmlDocument eToken_GetFullInfo() 
			//{
			//	try
			//	{
			//		string RootDir; 
			//		string MetaPath = eToken_GetMetaPath(&RootDir);
			//		//
			//		// ��������� ���������� � META 
			//		//
			//		// ... 
			//		// 
			//		// ��������� ���������� � �������� ����������� CCOM 
			//		//
			//		// ��������� ���������� � �������� ����������� �� ���� 
			//		//
			//		EToken& eToken = eToken_Current(); 
			//		//
			//		XmlDocument doc;
			//		doc.LoadXml(ETokenInfoXmlTemplate()); 
			//		//
			//		XmlElement fullInfo_E = eToken.ReadDirectoryContent(doc,
			//			RootDir, 
			//			eToken_FilePrefixTables(),eToken_SubdirTablePrefix(),1,2,true
			//			); 
			//		doc.AppendChild(fullInfo_E);
			//		//
			//		OutputDebugString(_S(doc.OuterXml())); 
			//	}
			//	_Catch() 
			//}



			AsnObject eToken_GetMeta(EToken& eToken,int step=0,string* out_pMetaPath=0) 
			{
				try
				{
					// ����� Meta 
					//
					string MetaPath = eToken_GetMetaPath();
					if (out_pMetaPath) *out_pMetaPath = MetaPath; 
					//
					// �� ���������: NULL -- ��������, ��� ���
					AsnObject MetaO = AsnObject(false,AsnObject::UNIVERSAL,AsnObject::_NULL_); 
					//
					// ����� ���� Meta 
					Blob MetaData;
					MetaData = eToken.ReadFileContent(MetaPath); 
					//
					// ~ if (eToken.FileExists(MetaPath)) 
					if (MetaData.Length() > 0) 
					{
						// ��������� 
						//
						try
						{
							if (MetaData.Length() > 0) 
							{
								MetaO = AsnObject(MetaData); 
							}
						}
						catch(::::Exception e)
						{
							return EToken::NewStatusObject(
								ETokenStatus_E_WrongMetaFileStructure,e.GetStatus()); 
								// ������ ������� 
						}
						catch(...)
						{
							return EToken::NewStatusObject(
								ETokenStatus_E_WrongMetaFileStructure,E_UNEXPECTED); 
								// ������ ������� 
						}
					}
					else
					{
						if (step == 0) // �����, ��� ���� 
						{
							return EToken::NewStatusObject(
								ETokenStatus_E_NoMetaFile,HRESULT_FROM_WIN32(ERROR_NOT_FOUND)); 
						}
						else if (step == 1) // �������, ���� ��� 
						{
							eToken_CreateMeta(eToken); 
							//
							return eToken_GetMeta(eToken,step+1,out_pMetaPath); 
						}
						else
						{
							// return EToken::NewStatusObject(ETokenStatus_E___,E_UNEXPECTED); 
								// ������ �������� ��������� 
							//
							throw MethodError(L"������ �������� ��������� (2)"); 
						}
					}
						////int r0 = CADB_mkdir(MetaDir.GetBuffer());
						////int r1 = CADB_write_file(MetaPath.GetBuffer(),
						////	(char*)MetaData.GetBuffer(),MetaData.Length());
						////if (r1 == 0)
						////{
						////	throw MethodError(L"�� ������� �������� ���� �� eToken (1)")
						////		.AddIfNewSource_(_W(MetaPath));
						////}
					//
					return MetaO;
				}
				_Catch()
			}



			inline void eToken_CreateMetaDir(EToken& eToken) 
			{
				try
				{
					string rootPath = L"/" + eToken_GetRootDir(); 
					//
					eToken.CreateDirectory(rootPath); 
				}
				_Catch()
			}



			void eToken_SaveMeta(EToken& eToken,AsnObject MetaO) 
			{
				try
				{
					// ������ Meta 
					//
					eToken_CreateMetaDir(eToken); // � �����? 
					//
					string MetaPath = eToken_GetMetaPath(); 
					//
					Blob MetaData = MetaO.Encoded();
					//
#					ifdef __DEBUG
					{
						TRACE_LOG(_T("Saving Meta:")); 
						string dump = MetaO.Dump(); 
						//OutputDebugStringW(dump); 
					}
#					endif
					//
					AsnObject statusO = AsnObject::NewNullObject(); 
					eToken.WriteFile(MetaPath,MetaData,&statusO); 
					int status = EToken::GetStatusObjectCode(statusO); 
					if (status != S_OK) 
					{
						string msg = L"�� ������� �������� ���������� � ������ �� eToken (1)"; 
						throw MethodError(msg).AddIfNewSource_(_W(MetaPath));
					}
				}
				_Catch()
			}



			inline AsnObject eToken_NewMeta(
				EToken& // eToken // not used so far 
				) 
			{
				try
				{
					// SEQUENCE -- META
					//		SEQUENCE (pair) -- ������ ������ 
					//			oid.1.2.643.6.2.1.5.3
					//			SEQUENCE
					//				key
					//				key
					//				...
					//		SEQUENCE (pair) -- ������ ������ 
					//			oid.1.2.643.6.2.1.5.4
					//			SEQUENCE
					//				oid.*
					//			SEQUENCE
					//				oid.*
					//			...
					//
					// ----
					// Meta 
					//
					AsnObject MetaO = AsnObject::NewSequence(); 
					//
					// ----
					// ������ ������ 
					//
					MetaO.Add(AsnObject::NewSequence()); 
					//
					AsnObject& keyListPairO = MetaO[0];
					//
					keyListPairO.Add(AsnObject(OID(L"1.2.643.6.2.1.5.3")));
					keyListPairO.Add(AsnObject::NewSequence()); 
					//
					/// AsnObject& keyListO = keyListInfoO[1];  // ��������� ��� ������������ ������ 
					//
					// ----
					// ��������� 
					// 
					return MetaO; 
				}
				_Catch() 
			}



			inline void eToken_CreateMeta(EToken& eToken) 
			{
				try
				{
					AsnObject MetaO = eToken_NewMeta(eToken); 
					eToken_SaveMeta(eToken,MetaO); 
				}
				_Catch() 
			}



			inline AsnObject NewKeyO(const string& dir) 
			{
				try
				{
					AsnObject keyO = AsnObject::NewSequence(); 
					// 
					keyO.Add(AsnObject(_W(dir))); 
					//
					return keyO; 
				}
				_Catch() 
			}



			inline bool ParseKeyO(AsnObject keyO, 
				string* out_pDir=0 
				) 
			{
				try
				{
					if (keyO.Tag() != AsnObject::SEQUENCE) return false; 
					//
					if (keyO.ChildCount() < 1) return false; 
					//
					string dir = keyO.m_text; 
					//
					if (dir.GetLength() == 0) return false; 
					//
					if (out_pDir) *out_pDir = dir; 
					return true; 
				}
				_Catch() 
			}



			SharedArray<string> eToken_GetKeyDirs(EToken& eToken) 
			{
				try
				{
					AsnObject MetaO = eToken_GetMeta(eToken); 
					//
					AsnObject& keyListInfoO = MetaO[0]; 
					//
					AsnObject& keyListO = keyListInfoO[1];  // ��������� ��� ������������ ������ 
					//
					// ���������� ������ 
					//
					SharedArray<string> dirs;
					//
					for (int k = 0; k < keyListO.ChildCount(); ++k) 
					{
						AsnObject& keyO = keyListO[k];
						//
						string dir; 
						//
						if (ParseKeyO(keyO,&dir)) 
						{
							dirs.Add(dir); 
						}
					}
					//
					return dirs;
				}
				_Catch()
			}



			inline string eToken_CreateContainerPath( 
				EToken& eToken, 
				int* out_pIndex=0,
				string* out_pDir=0
				) 
			{
				try
				{
					// Meta 
					//
					string Root = eToken_GetRootDir(); 
					AsnObject MetaO =  eToken_GetMeta(eToken,1); // require 
					//
					// ���������� � ������ 
					//
					AsnObject& keyListInfoO = MetaO[0]; 
					//
					AsnObject& keyListO = keyListInfoO[1];  // ��������� ��� ������������ ������ 
					//
					int n = keyListO.ChildCount(); 
					//
					// ����� ���� 
					//
					string dir = eToken.FormatDir(_W(_ETOKEN_KEYDIR_PREFIX), n ); 
					//
					string keyPath = Root + L"/" + dir; 
					//
					keyListO.Add(NewKeyO(dir)); 
					//
					eToken_SaveMeta(eToken,MetaO); 
					//
					// ������ ����� ��� ������ ���������� � ����� 
					//
					eToken.CreateDirectory(keyPath); 
					//
					if (out_pIndex) *out_pIndex = n; 
					if (out_pDir) *out_pDir = dir;
					return keyPath;
				}
				_Catch()
			}
			
			
			
			// port: -2 �������� ����� ������� ������ �� ������� 

			void eToken_CreateKeyOnEToken(CCOM_Key& ccom_key,int port,const string& pass) 
			{
				try
				{
					EToken& eToken = eToken_Current(); 
					//
					int index; 
					string dir; 
					//
					string keyPath = eToken_CreateContainerPath( 
						eToken, 
						&index,
						&dir
						); 
					//
					CStringA physPath = eToken.GetPhysicalPath(keyPath); 
					//
					ccom_key->CreateIn(_S(keyPath),_S(pass)); 
				}
				_Catch() 
			}



			XmlElement _del_CreateDriveKeyInfo(XmlDocument doc, 
				EToken& eToken, 
				const string& path, 
				const string& keyName 
				)
			{
				try
				{
					XmlElement keyInfo = CreateKeyInfo(doc,L"CryptoCOM",L"eToken");
					//
					keyInfo.SetAttribute(L"KeyPath",string(path));
					keyInfo.SetAttribute(L"DriveLetter",string(L"T"));
					keyInfo.SetAttribute(L"KeyName",string(keyName));
					//
					// ��������� ���������� � �����
					//
					string pkh64;
					//
					//SharedArray<CString> pkXmlPaths = Machine::ListFiles(path,_T("*-k.xml"));
					//if (pkXmlPaths.Length() == 0) 
					//{
					//	keyInfo.SetAttribute(L"KeyTime",L"������ " + (string)keyName);
					//	// throw MethodError(_S("��� ������ � ����� ") + path);
					//	//
					//	// return keyInfo; // empty 
					//}
					//else
					//{
					//	CString pkXmlPath = pkXmlPaths[0];
					//	//
					//	XmlDocument pkInfo;
					//	pkInfo.Load(string(pkXmlPath));
					//	XmlElement pkInfo_E = pkInfo.DocumentElement();
					//	//
					//	pkh64 = pkInfo_E.GetAttribute(L"PubKeyHash");
					//	if (pkh64.Right(1) == L"=") pkh64 = pkh64.Left(pkh64.GetLength()-1); 
					//	keyInfo.SetAttribute(L"PubKeyHash",pkh64);
					//	//
					//	//t0 = COleDateTime(...);
					//	//string datetime_s = string(t0.Format(_T("%Y-%m-%dT%H:%M:%SZ")));
					//	string datetime_s = pkInfo.DocumentElement().GetAttribute(L"KeyTime"); 
					//	//
					//	// ----
					//	// ��������� KeyInfo
					//	//
					//	keyInfo.SetAttribute(L"KeyTime",datetime_s);
					//	//
					//	if (lookupPkh.Length() > 0)
					//	{
					//		string activePkh64 = __ToBase64String(lookupPkh);
					//		if (activePkh64 == pkh64)
					//		{
					//			CComBSTR bstrOn(L"true");  
					//			keyInfo.SetAttribute(L"IsActive",CComVariant(bstrOn)); 
					//		}
					//	}
					//}
					////
					//// ----
					//// ��������� ����������
					////
					//SharedArray<CString> certPaths = Machine::ListFiles(path,_T("*.cer"));
					//bool certFound = false;
					//for (int i = 0; i < certPaths.Length() && (! certFound); ++i)
					//{
					//	CString certPath = certPaths[i];
					//	//
					//	Blob certData;
					//	::::File f;
					//	f.Open(certPath);
					//	certData = f.ReadAll();
					//	f.Close();
					//	//
					//	// CCOM:
					//	//
					//	CCOM_Certificate cert;
					//	try
					//	{
					//		cert->Import(certData);
					//		//
					//		string certPkh64 = __ToBase64String(cert->GetPKH());
					//		if (
					//			((certPkh64 == pkh64) || (certPkh64+L"=" == pkh64) || (certPkh64 == pkh64+L"="))
					//			|| (pkh64.GetLength() == 0)
					//			)
					//		{
					//			XmlElement CertInfo_E = cert->GetXmlInfo(); 
					//			CertInfo_E.SetAttribute(L"PubKeyHashUrlEnc",
					//				UrlEncode(Base64Text_4Url(certPkh64))
					//				);
					//			keyInfo.AppendChild(CertInfo_E);
					//			//
					//			certFound = true;
					//		}
					//	}
					//	catch(Exception& e)
					//	{
					//		TRACE_LOG(e.ToString());
					//	}
					//	catch(...)
					//	{
					//		TRACE_LOG(_T("����������� ������!"));
					//	}
					//}
					////
					//// ��������� ������
					////
					//AsnObject request = AsnObject::NewSequence();
					//AsnObject requestXO = AsnObject::NewSequence();
					////
					//SharedArray<CString> reqPaths = Machine::ListFiles(path,_T("*-request.der"));
					//bool reqFound = false;
					//for (int i = 0; i < reqPaths.Length() && (! reqFound); ++i)
					//{
					//	CString reqPath = reqPaths[i];
					//	//
					//	Blob reqData;
					//	::::File f;
					//	f.Open(reqPath);
					//	reqData = f.ReadAll();
					//	f.Close();
					//	//
					//	try
					//	{
					//		request = AsnObject(reqData);
					//		//
					//		CString reqXOPath = reqPath;
					//		reqXOPath.Replace(_T("-request.der"),_T("-x.der")); 
					//		//
					//		if (Machine::FileExists(reqXOPath))
					//		{
					//			Blob reqXOData;
					//			::::File fXO;
					//			fXO.Open(reqXOPath);
					//			reqXOData = fXO.ReadAll();
					//			fXO.Close();
					//			//
					//			requestXO = AsnObject(reqXOData);
					//		}
					//		//
					//		reqFound = true;
					//	}
					//	catch(Exception& e)
					//	{
					//		TRACE_LOG(e.ToString());
					//	}
					//	catch(...)
					//	{
					//		TRACE_LOG(_T("����������� ������!"));
					//	}
					//}
					////
					//if (reqFound)
					//{
					//	XmlDocument requestInfo = GetRequestInfo(request,requestXO);
					//	XmlElement ri = requestInfo.DocumentElement();
					//	keyInfo.AppendChild(ri);
					//	if (! ri.IsEmpty())
					//	{
					//		pkh64 = ((XmlElement)ri.SelectSingleNode(L"CertificateInfo")) 
					//			.GetAttribute(L"PubKeyHash");
					//		//
					//		keyInfo.SetAttribute(L"PubKeyHash",pkh64);
					//	}
					//}
					//
					return keyInfo;
				}
				_Catch() 
			}





			// -----------------------------------------------------------------------------------
			// �������� ���������� � ������ �� ������ ��������� 

			XmlDocument PrepareCommonKeyInfo( 
				Blob searchPkh=Blob(), 
				Blob activePkh=Blob(), 
				bool useXsl=true 
				) 
			{
				try
				{
					XmlDocument doc;
					doc.LoadXml(CommonKeyInfoTemplate(useXsl));
					if (doc.IsEmpty())
					{
						throw MethodError(L"�� ������� ��������� CommonKeyInfo (1)"); 
					}
					//
					XmlElement CommonKeyInfo_E = doc.DocumentElement();
					//
					CString keyRootCommonPath = _S(Instance().GetOption(L"special-105"));
					CString keyRootPath = _S(Instance().GetOption(L"special-104")); 
					if ((keyRootPath.GetLength() == 0) && (keyRootCommonPath.GetLength() > 0)) 
					{
						keyRootPath = keyRootCommonPath + _T("\\") + ::::Util::GetUserName(); 
					}
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
										TRACE_LOG(keyDir);
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
										XmlElement keyInfo = CreateDriveKeyInfo(doc,keyDir,drive,keyName,
											activePkh);
										//
										if (keyInfo.HasAttribute(L"PubKeyHash")) // ������ ���� 
										{ 
											bool use = true;
											//
											if (searchPkh.Length() > 0)
											{
												string pkh64a = keyInfo.GetAttribute(L"PubKeyHash");
												Blob pkh = FromBase64String(pkh64a); 
												string pkh64 = __ToBase64(searchPkh); 
												//
												string searchPkh64 = __ToBase64(searchPkh); 
												//
												if (pkh64 != searchPkh64) use = false; 
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
						//
						// ----
						// ��������� ���������� � ������ �� eToken 
						//
#						ifdef _DEBUG
						{
							TRACE_LINE(_T("��������� ���������� � ������ �� eToken")); 
						}
#						endif
						//
						SharedArray<SharedPtr<EToken> > eTokens = eToken_GetAll(); 
						//
						for (int drive_i = 0; drive_i < eTokens.Length(); ++drive_i)
						{
							EToken* pToken = eTokens[drive_i].GetPointee(); 
							//
							SharedArray<string> keyDirs = eToken_GetKeyDirs(*pToken); 
							//
							for (int dir_i = 0; dir_i < keyDirs.Length(); ++dir_i) 
							{
								string keyDir = keyDirs[dir_i]; 
								// 
								string keyName = FormatStr(L"eToken:%d",drive_i) + keyDir; 
								//
								XmlElement keyInfo = CreateDriveKeyInfo(doc,*pToken,keyDir,keyName,activePkh); 
								//
								if (keyInfo.HasAttribute(L"PubKeyHash")) // ������ ���� 
								{ 
									bool use = true;
									//
									if (searchPkh.Length() > 0)
									{
										string pkh64a = keyInfo.GetAttribute(L"PubKeyHash");
										Blob pkh = FromBase64String(pkh64a); 
										string pkh64 = __ToBase64(searchPkh); 
										//
										string searchPkh64 = __ToBase64(searchPkh); 
										//
										if (pkh64 != searchPkh64) use = false; 
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
									XmlElement keyInfo = CreateDriveKeyInfo(doc,keyDir,_T("."),keyName,
										activePkh);
									//
									if (keyInfo.HasAttribute(L"PubKeyHash")) // ������ ���� 
									{ 
										bool use = true;
										//
										if (searchPkh.Length() > 0) 
										{
											string pkh64a = keyInfo.GetAttribute(L"PubKeyHash");
											Blob pkh = FromBase64String(pkh64a); 
											string pkh64 = __ToBase64(searchPkh); 
											//
											string searchPkh64 = __ToBase64(searchPkh); 
											//
											if (pkh64 != searchPkh64) use = false; 
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
					// ��������� ���������� � ������ �� eToken
					//
					//for (int port_i = 0; port_i <= 0; ++port_i) 
					//{
					//	EToken eToken(port_i,GetETokenPIN(port_i));
					//	SharedArray<CString> keyNames = eToken.GetTokenKeyNames(port_i); 
					//	//
					//}
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
					return doc;
				}
				_Catch()
			}






			// -----------------------------------------------------------------------------------
			// ���������� ������� � ������������� 

			inline void InstallCertificate(Blob pkh,Blob certificate) 
			{
				try
				{
					XmlDocument d = PrepareCommonKeyInfo(pkh,Blob(),false); 
					//
					XmlElement dRoot = d.DocumentElement(); 
					//
					string pkh64 = __ToBase64(pkh); 
					//
					string xPath = GetKeyInfoXPath(pkh64); 
					XmlNodeList L = dRoot.SelectNodes(xPath);
					if (L.Count() == 0)
						throw MethodError(L"������ �� ������: " + _W(pkh64)); 
					//
					XmlElement KeyInfo_E = L[0];
					//
					CString keyPath = _S(KeyInfo_E.GetAttribute(L"KeyPath"));
					//
					CString certPath = keyPath + _T("\\client.cer"); 
					//
					File f;
					f.OpenToWrite(certPath); 
					f.Replace((char*)certificate.GetBuffer(),certificate.Length()); 
					f.Close();
				}
				_Catch() 
			}




		};

	} // namespace PKI 

} // namespace  



























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












			//inline SharedArray<CString> GetKeyDrives() 
			//{			
			//	try
			//	{
			//		SharedArray<CString> drives = Machine::ListDrives(DRIVE_REMOVABLE); 
			//		//
			//		string K = Instance().GetOption(L"special-102"); 
			//		if (K.GetLength() > 0)
			//		{
			//			drives.Add(_S(K)); 
			//		}
			//		//
			//		return drives; 
			//	}
			//	_Catch() 
			//}


















		//////// =======================================================================================
		//////// ���������� ��� �������� ������ 
		//////// =======================================================================================

		//////class KeyDrive 
		//////{
		//////public:
		//////	virtual ~KeyDrive() 
		//////	{
		//////	}

		//////	virtual GetKeyInfo(
		//////		const string& keyPath, 
		//////		) 
		//////		=0; 
		//////};



		//////// ����������: eToken 

		//////class ETokenKeyDrive 
		//////{
		//////	// ----
		//////	// ������������ ��������� 

		//////public:
		//////	EToken* m_eToken; 

		//////public:
		//////	ETokenKeyDrive(EToken* peToken) 
		//////	{
		//////		try
		//////		{
		//////			if (! peToken) throw MethodError(E_POINTER); 
		//////			//
		//////			m_eToken = peToken; 
		//////		}
		//////		_Catch() 
		//////	}
		//////}; 



		//////// ����������: �������� ���������� 

		//////class DiskKeyDrive 
		//////{
		//////public:
		//////}; 
