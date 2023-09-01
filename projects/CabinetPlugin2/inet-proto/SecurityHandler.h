#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


#include <low-level/SmartEToken.h>
//#include <low-level/SmartGOSTR.h>
#include <SlotCSP_CCOM.h>
//
#include <ax/coclasses/AX_SlotClient.h>
//
#include <SlotRequestHandlerImpl.h>

#include <WinCred.h>
#pragma comment(lib, "Credui.lib" )

#pragma comment(lib, "Crypt32.lib" )


namespace  {

	// CSlotSecurityHandler 

	class ATL_NO_VTABLE CSlotSecurityHandler : 
		public CComObjectRootEx<CComSingleThreadModel>, 
		public CComCoClass<CSlotSecurityHandler>, 
		public ISlotRequestHandler, 
		// public IStream, 
		public CSlotRequestHandlerImpl 
	{
	public:
		typedef CSlotRequestHandlerImpl Impl;

		template<class I>
		inline static I* Create() // new reference 
		{
			try
			{
				return Impl::Create<I,CSlotSecurityHandler>(); // new reference 
			}
			_Catch()
		}



	public:
		CSlotSecurityHandler() 
		{
		}

		BEGIN_COM_MAP(CSlotSecurityHandler)
			COM_INTERFACE_ENTRY_IID(__uuidof(ISlotRequestHandler),ISlotRequestHandler) 
		END_COM_MAP()

		DECLARE_PROTECT_FINAL_CONSTRUCT()

		HRESULT FinalConstruct()
		{
			return S_OK;
		}
		
		void FinalRelease() 
		{
		}

	public:
		// Request

		STDMETHOD(get_Request)(IStream** out_stream)
		{
			try
			{
				return Impl::get_Request(out_stream); 
			}
			_ComCatch()
		}

		STDMETHOD(put_Request)(IStream* stream)
		{
			try
			{
				return Impl::put_Request(stream); 
			}
			_ComCatch()
		}

		// -------------------------------------------------------------------------------------------
		// ��������� ��������� 

		CComPtr<ISlotClient> m_Client; 

		ISlotClient* CurrentClient(bool require=true) 
		{
			try
			{
				ISlotClient* client = _Clients().GetClient(Blob(), require); // borrowed reference, activate or not  
				//
				if (! client) 
				{
					if (require) throw MethodError(L"�� ������� ���������� �������"); 
				}
				return client; 
			}
			_Catch() 
		}

		ISlotClient* obs_Client(bool require=true) 
		{
			try
			{
				ISlotClient* client = _Clients().GetClient(Blob(), require); // borrowed reference, activate or not  
				//
				if (! client) 
				{
					if (require) throw MethodError(L"�� ������� ���������� �������"); 
				}
				return client; 
			}
			_Catch() 
		}

		// �������������� XML-��������� CommonKeyInfo ��������� ��������� 
		// 
		inline XmlDocument CommonKeyInfoDocument_RF3a( 
			// �������� � ����� 
			bool useXsl=false, 
			// ���������� ������� 
			bool includeGood=true, 
			const string& onlyThisPkh64=L"", 
			// ���������� �������������� ���������� � ��������� 
			bool addClientInfo=false 
			) 
		{
			try
			{
				XmlDocument d = Instance().CommonKeyInfoDocument(includeGood, onlyThisPkh64); 
				//
				if (addClientInfo)
				{
					Instance().SetClientInfo_CommonKeyInfo(d, _Clients().GetCurrentClient()); 
				}
				//
				if (useXsl) throw MethodError(L"use-xsl option is obsolete"); 
				//
				return d; 
			}
			_Catch() 
		}

		inline XmlDocument CommonKeyInfoDocument_QA( 
			bool addClientInfo=false, 
			bool forceUseXsl=false 
			) 
		{
			try
			{
				bool useXsl = false;
				//
				if (forceUseXsl)
				{
					useXsl = true; 
				}
				else
				{
					string useXslStr; 
					CComBSTR bstrUseXslStr; 
					HRESULT rc = GetQueryParameter(CComBSTR(L"use-xsl"),&bstrUseXslStr); 
					if (rc == S_OK) useXslStr = _W(bstrUseXslStr); 
					//
					useXsl = GetFlagValue(useXslStr); 
				}
				//
				return CommonKeyInfoDocument_RF3a(useXsl, false, L"", addClientInfo); 
			}
			_Catch() 
		}

		//inline XmlDocument Client_GetCommonKeyInfo(const string& pkh64=L"",bool useXsl=true) 
		//{
		//	try
		//	{
		//		CComPtr<IXMLDOMDocument> pXmlDoc;
		//		//
		//		HRESULT rc = Client()->GetCommonKeyInfo(CComBSTR(pkh64),(int)useXsl,&pXmlDoc); 
		//		if (FAILED(rc)) throw MethodError(rc); 
		//		//
		//		////TRACE_LOG1(_T("CommonKeyInfo: pXmlDoc=0x%x"), (int)(IXMLDOMDocument*)pXmlDoc ); 
		//		if (! pXmlDoc) throw MethodError(L"CommonKeyInfo: (�����)"); 
		//		//
		//		XmlDocument d(pXmlDoc); 
		//		//
		//		if (d.IsEmpty()) throw MethodError(L"CommonKeyInfo: �� ������� ��������� XmlDocument"); 
		//		else
		//		{
		//			////TRACE_LOG1(_T("CommonKeyInfo: XmlDocument( 0x%x )"), (int)d.GetXmlObjectInterface() ); 
		//		}
		//		//
		//		return d; 
		//	}
		//	_Catch() 
		//}

		inline string Client_RequestInfoHeaderTemplate(const string& vXslUrl) 
		{
			try
			{
				string s = _W(COMMON_XML_START) + (
					(vXslUrl.GetLength() > 0) ?
						L"<?xml-stylesheet type=\"text/xsl\" href=\"" + vXslUrl + L"\" ?>" :
						L""
					); 
				return s; 
			}
			_Catch() 
		}



		inline HRESULT RequestInfoDocument( 
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
				XmlDocument d = CommonKeyInfoDocument_RF3a(); 
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

		inline string GetKeyInfoXPath(const string& pkh64) 
		{
			try
			{
				string xPath = 
					L"KeyInfo["
					L"RequestInfo/CertificateInfo/@PubKeyHash='" + pkh64 + L"' or "
					L"RequestInfo/CertificateInfo/@PubKeyHash='" + pkh64 + L"='" 
					L"]"
					;
				return xPath; 
			}
			_Catch() 
		}

		inline SharedArray<CString> GetKeyDrives()
		{			
			try
			{
				SharedArray<CString> drives = Machine::ListDrives(DRIVE_REMOVABLE);  
				//
				string K = Instance().GetOption(L"special-102"); 
				if (K.GetLength() > 0)
				{
					drives.Add(_S(K)); 
				}
				//
				return drives; 
			}
			_Catch() 
		}

		inline HRESULT ActiveKeyDocument(const string& pkh64, ISlotClient* client) 
		{
			try
			{
				string xml1 = L"<ActiveKey PubKeyHash=\"" + pkh64 + L"\"/>"; 
				//
				XmlDocument doc; 
				doc.LoadXml(xml1); 
				//
				XmlElement root = doc.DocumentElement(); 
				//
				if (client) 
				{
					int size = 8 * 1024; 
					Blob data; data.Allocate(size); 
					HRESULT rc = client->get_CertificateData(data.GetBuffer(), &size); 
					if (FAILED(rc)) throw MethodError(rc); 
					//
					PCCERT_CONTEXT pCertContext = CertCreateCertificateContext( 
						X509_ASN_ENCODING, 
						data.GetBuffer(),
						size 
						);
					if (pCertContext)
					{
						int nValid = CertVerifyTimeValidity(NULL,pCertContext->pCertInfo); 
						root.SetAttribute(L"Validity", FormatStr(L"%d", (int)nValid)); 
					}
				}
				//
				return Document(doc); 
			}
			_Catch()
		}



		inline void InstallCertificate(Blob pkh, Blob certificate) 
		{
			try
			{
				//XmlDocument d = Instance().PrepareCommonKeyInfo(pkh,Blob(),false, 
				//	Map<string,string>(), false); 
				//
				XmlDocument d = CommonKeyInfoDocument_RF3a(); 
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
				string keyMedia = KeyInfo_E.GetAttribute(L"KeyMediaType"); 
				//
#				ifdef _DEBUG
				int n = certificate.Length(); 
				TRACE_LOG1(L"������ ����� �����������: %d", (int)n ); 
#				endif
				//
				if (keyMedia == _T("eToken"))
				{
					CCOM_Certificate cert;
					cert->Import(certificate);
					//
					XmlElement CertInfo_E = cert->GetXmlInfo(false); 
					//
					string subject; // = L"CN=" + commonName; 
					//
					Instance().PrepareCertAttributesForXml(CertInfo_E, certificate, cert, &subject); 
					//
					//string commonName = CertInfo_E.GetAttribute(L"CommonName"); 
					//
					// Installing 
					//
					string eTokenID = KeyInfo_E.GetAttribute(L"eTokenID"); 
					int key_i = _wtoi(KeyInfo_E.GetAttribute(L"KeyNum"));
					//
					EToken& eToken = EToken::OpenEToken(eTokenID); 
					//////int eTokenSlotId = eToken.SlotId; 
					//
					string certLabel = FormatStr(L" Certificate %d", key_i); 
					//
					//eToken.SearchCert(subject); 
					eToken.SaveObject(certLabel, certificate, CKO_DATA, 0, subject); 
					//
					//int key_i = _wtoi(KeyInfo_E.GetAttribute(L"KeyNum"));
					////
					//PKCS11_Manager::Lock lock;
					//PKCS11_Manager& M = PKCS11_Manager_();
					//M.EnterContext(eTokenSlotId); 
					////
					//string certPath = M.EToken_GetCertPath(eTokenSlotId, key_i); 
					////
					//CStringA certPathA = M.ETokenPath(eTokenSlotId, certPath); 
					//int r1 = CADB_write_file(certPathA.GetBuffer(),
					//	(char*)certificate.GetBuffer(), certificate.Length()); 
					//if (r1 <= 0) 
					//{
					//	int e1 = (int)ERR_get_last_error(); 
					//	string errMsg = FormatStr(L"�� ������� �������� ���� �� eToken: " + _W(certPathA) +
					//		L", ������ CCOM: %d", (int)e1 ); 
					//	throw MethodError(errMsg); 
					//}
					////
					//M.ReleaseContext();
				}
				else // keyMedia == _T("drive")
				{
					CString keyPath = _S(KeyInfo_E.GetAttribute(L"KeyPath"));
					//
					CString certPath = keyPath + _T("\\client.cer"); 
					//
					File f;
					f.OpenToWrite(certPath); 
					f.Replace((char*)certificate.GetBuffer(),certificate.Length()); 
					f.Close();
				}
			}
			_Catch() 
		}






		// ----
		// OnRequest 

		STDMETHOD(OnRequest)(int* out_status,BSTR* out_url,BSTR* out_cachePath,  
			BSTR* out_contentType,IStream** out_stream) 
		{
			try
			{
				SaveOutParameters_(); 
				//
#				ifdef _DEBUG
				{
					//// if (out_status) *out_status = 200; // for tests only! 
					//
					//CREDUI_INFOW info = { sizeof (CREDUI_INFOW) };
					//info.hwndParent = 0; // set to the parent window 
					////
					//SharedArray<wchar_t> userName; userName.Allocate(CREDUI_MAX_USERNAME_LENGTH+1); 
					//SharedArray<wchar_t> userPass; userPass.Allocate(CREDUI_MAX_USERNAME_LENGTH+1); 
					////
					//ZeroMemory(userName.GetBuffer(), userName.Length());
					//ZeroMemory(userPass.GetBuffer(), userPass.Length());
					////
					////DWORD dwR = CredUIPromptForWindowsCredentialsW(&info, 
					////	0, 
					////	userName.GetBuffer(), CREDUI_MAX_USERNAME_LENGTH+1, 
					////	userPass.GetBuffer(), CREDUI_MAX_USERNAME_LENGTH+1, 
					////	0, 
					////	CREDUI_FLAGS_GENERIC_CREDENTIALS
					////	); 
					////
					//DWORD dwR = CredUIPromptForCredentialsW(&info, 
					//	L"server", 0, 0, 
					//	userName.GetBuffer(), CREDUI_MAX_USERNAME_LENGTH+1, 
					//	userPass.GetBuffer(), CREDUI_MAX_USERNAME_LENGTH+1, 
					//	0, 
					//	CREDUI_FLAGS_GENERIC_CREDENTIALS
					//	); 
					//
					//Banach::Khi::Test(); 
					//
					//GOSTR G;
					////G.R3411_94__Test(); 
					////G.R3410_2001__ParameterSet(); 
					//G.R3410_2001__Test();
				}
#				endif
				//
				HRESULT rc;
				//
				CComBSTR bstrV1;
				CComBSTR bstrV2;
				//
				bool useXslFound = false;
				bool useXslParam;
				//
				rc = GetQueryParameter(CComBSTR(L"use-xsl"),&bstrV2);
				if (rc == S_OK) 
				{
					useXslFound = true;
					//
					string s = _W(bstrV2); 
					s.Trim();
					s.MakeLower(); 
					if ((s == L"true") || (s == L"yes") || (s == L"on") || (s == L"1"))
						useXslParam = true; 
					else
						useXslParam = false; 
				}
				else
				{
					useXslParam = false; 
				}
				//
				rc = GetQueryParameter(CComBSTR(L"action"),&bstrV1);
				if (rc != S_OK) throw MethodError(L"�������� action �� ������");
				CString action(bstrV1);
				//
				{
					for (int k = 0; k < 8; k++)
					{
						string name = FormatStr(L"z%d", (int)k );
						rc = GetQueryParameter(CComBSTR(name),&bstrV2); 
						if (rc == S_OK) 
						{
							string z(bstrV2);
							//
							int p1 = z.Find(L":"); 
							if (p1 != -1)
							{
								string eTokenID = z.Left(p1); 
								eTokenID.Trim(); 
								string pin = z.Right(z.GetLength()-p1-1); 
								//
								EToken::SetPin(eTokenID, pin); 
							}
						}
					}
				}
				//
				if (action == L"GenerateRequest")
				{
					// ----
					// �������� ����������, ����������� �� ����
					//
					// bool requestOk = true;
					//
					//CComPtr<IXMLDOMDocument> currentRIXmlDom;
					//rc = m_spDocument->get_RequestInfo(&currentRIXmlDom); 
					//if (rc != S_OK) throw MethodError(rc);
					////
					//XmlDocument currentRI(currentRIXmlDom);
					//
					// OID �������� ���������� �����������:
					rc = GetQueryParameter(CComBSTR(L"pki-policy-oid"),&bstrV2);
					if (rc != S_OK) throw MethodError(L"�������� pki-policy-oid �� ������");
					string pkiPolicyOid(bstrV2);
					//
					if (! (
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
					rc = GetQueryParameter(CComBSTR(L"crypto-system"),&bstrV2);
					if (rc != S_OK) throw MethodError(L"�������� crypto-system �� ������");
					string cryptoSystem = bstrV2;
					//
					if (! (
						(cryptoSystem == L"CryptoCOM")
						)) 
					{
						string msg = L"���������������� ������-�������: %s" + _W(cryptoSystem);
						throw MethodError(msg);
					}
					//
					// ��� ��������� ��������:
					rc = GetQueryParameter(CComBSTR(L"key-media-type"),&bstrV2);
					if (rc != S_OK) throw MethodError(L"�������� key-media-type �� ������");
					string keyMedia = bstrV2;
					//
					//if (! (
					//	(keyMedia == L"eToken") || 
					//	(keyMedia == L"drive") 
					//	)) 
					//{
					//	string msg = L"���������������� ��� ��������: " + keyMedia;
					//	rc = m_spDocument->SetQueryParameterEx(
					//		CComBSTR(L"key-media-type-msg"),CComBSTR(msg),CComBSTR(L"POST"),CComBSTR("text"));
					//	if (rc != S_OK) throw MethodError(rc);
					//	requestOk = false;
					//}
					//
					// ������ �� �������� ��������:
					rc = GetQueryParameter(CComBSTR(L"key-container-pwd"),&bstrV2);
					//if (rc != S_OK) throw MethodError(L"�������� key-container-pwd �� ������");
					string keyContainerPwd = bstrV2;
					//
					rc = GetQueryParameter(CComBSTR(L"key-container-pwd2"),&bstrV2);
					//if (rc != S_OK) throw MethodError(L"�������� key-container-pwd2 �� ������");
					string keyContainerPwd2 = bstrV2;
					//
#					ifdef _DEBUG
					{
						TRACE_LOG1(_T("!ContainerPwd: %s"), _S(keyContainerPwd).GetString() ); 
					}
#					endif
					//
					if (keyMedia == L"eToken") 
					{
						keyContainerPwd = FormatStr(L"%u", (int)RandomInt32() ); 
						keyContainerPwd2 = keyContainerPwd; 
					}
					//
					{
						if (keyContainerPwd.GetLength() == 0)
						{
							string msg = L"������� ������";
							throw MethodError(msg); 
							//rc = m_spDocument->SetQueryParameterEx(
							//	CComBSTR(L"key-container-pwd-msg"),CComBSTR(msg),
							//	CComBSTR(L"POST"),CComBSTR("text"));
							//if (rc != S_OK) throw MethodError(rc);
							//requestOk = false;
						}
						else if (keyContainerPwd2.GetLength() == 0)
						{
							string msg = L"��������� ������ � ��������� ����";
							throw MethodError(msg); 
							//rc = m_spDocument->SetQueryParameterEx(
							//	CComBSTR(L"key-container-pwd-msg"),CComBSTR(msg),
							//	CComBSTR(L"POST"),CComBSTR("text"));
							//if (rc != S_OK) throw MethodError(rc);
							//requestOk = false;
						}
						else if (keyContainerPwd != keyContainerPwd2)
						{
							string msg = L"��������� ������ � ��������� ���� (�������� ������)";
							throw MethodError(msg); 
							//rc = m_spDocument->SetQueryParameterEx(
							//	CComBSTR(L"key-container-pwd-msg"),CComBSTR(msg),
							//	CComBSTR(L"POST"),CComBSTR("text"));
							//if (rc != S_OK) throw MethodError(rc);
							//requestOk = false;
						}
					}
					//
					string msgFieldRequired = L"������������ ����";
					//
					// ���
					//
					CComBSTR bstrFOidName(L"oid."+X500::GetOID(L"_PKI_�������"));
					CComBSTR bstrIOidName(L"oid."+X500::GetOID(L"_PKI_���"));
					CComBSTR bstrOOidName(L"oid."+X500::GetOID(L"_PKI_��������"));
					CComBSTR bstrFMsgName = bstrFOidName; bstrFMsgName += L"-msg";
					CComBSTR bstrIMsgName = bstrIOidName; bstrIMsgName += L"-msg";
					CComBSTR bstrOMsgName = bstrOOidName; bstrOMsgName += L"-msg";
					//
					string Client_F;
					string Client_I;
					string Client_O;
					if (GetQueryParameter(
						bstrFOidName,&bstrV2) == S_OK) 
						Client_F = bstrV2;
					else Client_F = L"";
					if (GetQueryParameter(
						bstrIOidName,&bstrV2) == S_OK) 
						Client_I = bstrV2;
					else Client_I = L"";
					if (GetQueryParameter(
						bstrOOidName,&bstrV2) == S_OK) 
						Client_O = bstrV2;
					else Client_O = L"";
					//
					// ----
					// Extra parameters by CommonName 
					//
					//int keyModeFlags = 0; 
					////
					//int p0 = Client_F.Find(L"//="); 
					//if (p0 != -1)
					//{
					//	string extra = Client_F.Right(Client_F.GetLength()-3); 
					//	//
					//	keyModeFlags = _wtoi(extra); 
					//}
					//
					//if (Client_F.GetLength() == 0)
					//{
					//	rc = m_spDocument->SetQueryParameterEx(
					//		bstrFMsgName,CComBSTR(msgFieldRequired),CComBSTR(L"POST"),CComBSTR("text"));
					//	if (rc != S_OK) throw MethodError(rc);
					//	requestOk = false;
					//}
					//if (Client_I.GetLength() == 0)
					//{
					//	rc = m_spDocument->SetQueryParameterEx(
					//		bstrIMsgName,CComBSTR(msgFieldRequired),CComBSTR(L"POST"),CComBSTR("text"));
					//	if (rc != S_OK) throw MethodError(rc);
					//	requestOk = false;
					//}
					//
					// ----
					// ����� ���������� �����, ���� ���� ������ ����������
					//
					//if (! requestOk)
					//{
					//	SetRedirectUrl(
					//		_T("://.cabinet.ru/protocol/CertRequest.xml?pki-policy-oid=") +
					//		_S(pkiPolicyOid) + 
					//		_T("&handler-progid=Protocol.SecurityHandler&action=CertRequestForm&test=1")
					//		);
					//	//
					//	SetRedirectFlags(GetRedirectFlags() | DocumentHandlerFlag_KeepPost);
					//	//
					//	return S_FALSE;
					//	//
					//	//rc = m_spDocument->ParseRequest(ParseMethodUrl,CComBSTR(url));
					//	//if (rc != S_OK) throw MethodError(rc);
					//	//IXMLDOMDocument* d2 = currentRI.GetXMLDOMDocument();
					//	//rc = m_spDocument->CopyPost(d2);
					//	//if (rc != S_OK) throw MethodError(rc);
					//	//rc = m_spDocument->Load();
					//	//if (rc != S_OK) throw MethodError(rc);
					//}
					//
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
					// * Subject
					//
					NameDescription subject;
					//
					string oid;
					string inputOid;
					string v;
					//
					// ** Email
					//
					oid = X500::GetOID(L"Email");
					inputOid = L"Email";
					if (GetQueryParameter(CComBSTR(L"oid."+inputOid),&bstrV2) == S_OK) v = bstrV2;
					else v = L"";
					if (v.GetLength() > 0)
						subject.SetAttribute(OID(oid),AsnObject(v,AsnObject::BMPString));
					//
					// ** CountryName
					//
					oid = X500::GetOID(L"CountryName");
					//if (GetQueryParameter(CComBSTR(L"..."),&bstrV2) == S_OK) v = bstrV2;
					//else v = L"";
					subject.SetAttribute(OID(oid),AsnObject((string)L"RU",AsnObject::BMPString));
					//
					// ** StateOrProvinceName 
					//
					oid = X500::GetOID(L"StateOrProvinceName");
					if (ur)
					{
						inputOid = X500::GetOID(L"_PKI_�����_��");
						if (GetQueryParameter(CComBSTR(L"oid."+inputOid),&bstrV2) == S_OK) 
							v = bstrV2;
						else v = L"";
					}
					else
					{
						inputOid = X500::GetOID(L"_PKI_�����_��");
						if (GetQueryParameter(CComBSTR(L"oid."+inputOid),&bstrV2) == S_OK) 
							v = bstrV2;
						else v = L"";
					}
					if (v.GetLength() > 0)
						subject.SetAttribute(OID(oid),AsnObject(v,AsnObject::BMPString));
					//
					// ** LocalityName
					//
					oid = X500::GetOID(L"LocalityName");
					string gorod;
					string naselPunkt;
					if (ur)
					{
						if (GetQueryParameter(
							CComBSTR(L"oid."+X500::GetOID(L"_PKI_�����_�����")),&bstrV2) == S_OK) 
							gorod = bstrV2;
						else gorod = L"";
						if (GetQueryParameter(
							CComBSTR(L"oid."+X500::GetOID(L"_PKI_�����_�����")),&bstrV2) == S_OK) 
							naselPunkt = bstrV2;
						else naselPunkt = L"";
					}
					else
					{
						if (GetQueryParameter(
							CComBSTR(L"oid."+X500::GetOID(L"_PKI_�����_�����")),&bstrV2) == S_OK) 
							gorod = bstrV2;
						else gorod = L"";
						if (GetQueryParameter(
							CComBSTR(L"oid."+X500::GetOID(L"_PKI_�����_�����")),&bstrV2) == S_OK) 
							naselPunkt = bstrV2;
						else naselPunkt = L"";
					}
					//
					v = gorod.GetLength() > 0 ? gorod : naselPunkt;
					//
					if (v.GetLength() > 0)
						subject.SetAttribute(OID(oid),AsnObject(v,AsnObject::BMPString)); 
					//
					// ** OrganizationName
					//
					string OrganizationName; 
					//
					oid = X500::GetOID(L"OrganizationName");
					if (ur) // ������� ������������ ����������� 
					{
						if (GetQueryParameter(CComBSTR(L"oid.OrganizationName"),&bstrV2) == S_OK) 
							OrganizationName = bstrV2;
						else OrganizationName = L"";
						v = OrganizationName;
						//
						if (v.GetLength() > 0)
							subject.SetAttribute(OID(oid),AsnObject(v,AsnObject::BMPString));
					}
					//
					// ** CommonName
					//
					string commonName = L"UNKNOWN"; 
					//
					oid = X500::GetOID(L"CommonName");
					if (ur && false) // ���������� ��� ����������� ���� - ��������� �����������!
					{
						string OrganizationName;
						if (GetQueryParameter(CComBSTR(L"OrganizationName"),&bstrV2) == S_OK) 
							OrganizationName = bstrV2;
						else OrganizationName = L"";
						v = OrganizationName;
						//
						commonName = v; 
					}
					else
					{
						v = Client_F;
						if (Client_I.GetLength() > 0) v += L" " + Client_I;
						if (Client_O.GetLength() > 0) v += L" " + Client_O;
						//
						v = v.Trim();
						if (v.GetLength() > 0)
							commonName = v;
					}
					subject.SetAttribute(OID(oid),AsnObject(commonName,AsnObject::BMPString)); 
					//
					R.Subject = subject;
					//
					// * SubjectAltName 
					//
					NameDescription subjectAltName;
					//
					for (X500::OidMap::Iterator i(X500::Oids()); i; ++i)
					{
						string alias = i.Id();
						if (alias.Left(9) == L"_PKI_")
						{
							oid = i;
							if (GetQueryParameter(CComBSTR(L"oid."+oid),&bstrV2) == S_OK) v = bstrV2;
							else v = L"";
							//
							bool use = v.GetLength() > 0;
							use = use && (StartsWith(CString(oid),_T("1.2.643.6.2.1.6.")));
							if (use)
							{
								string oidTail = 
									oid.Right(oid.GetLength()-string(L"1.2.643.6.2.1.6.").GetLength());
								//
								use = (! (
									(oidTail.Left(5) == L"1.101")
									));
							}
							//
							if (use)
							{
								subjectAltName.SetAttribute(OID(oid),AsnObject(v,AsnObject::BMPString));
							}
						}
					}
					//
					R.SubjectAltName = subjectAltName;
//#ifdef _DEBUG
//					string line1 = L"--------------------------------------------------------------------\n";
//					{
//						string msg = R.Dump(); 
//						OutputDebugStringW(line1 + msg + line1); 
//					}
//#endif
					//
					// * CertificatePolicies
					//
					R.RemoveAllPolicies();
					R.AddPolicyToRequest(L"1.2.643.6.2.1.7.1");
					//
//#ifdef _DEBUG
//					{
//						string msg = R.Dump(); 
//						OutputDebugStringW(line1 + msg + line1); 
//					}
//#endif
					//
					// * SubjectExtraInfo
					//
					NameDescription subjectExtraInfo;
					//
					CComPtr<IXMLDOMNode> params_node;
					HRESULT rc = m_Composer->GetParametersXml(CComBSTR(L""), &params_node); 
					if (FAILED(rc)) throw MethodError(rc); 
					//
					XmlNode n(params_node);
					XmlElement params_E(n); 
					XmlNodeList L = params_E.SelectNodes(L"slotrequest:param"); 
					//
					// for (X500::OidMap::Iterator i(X500::Oids()); i; ++i)
					for (int k = 0; k < L.Count(); k++) 
					{
						XmlElement E = L[k]; 
						//
						string name = E.GetAttribute(L"name"); 
						string oid = name; 
						if (name.Left(4) = L"oid.") oid = name.Right(name.GetLength()-4); 
						//
						//string alias = i.Id();
						//if (alias.Left(9) == L"_PKI_")
						{
							//oid = i;
							//
							//if (oid.Find(L".199") != -1)
							//{
							//	int g = 3; 
							//}
							if (GetQueryParameter(CComBSTR(L"oid."+oid),&bstrV2) == S_OK) 
								v = bstrV2;
							else v = L"";
							//
							bool use = v.GetLength() > 0;
							use = use && (StartsWith(CString(oid),_T("1.2.643.6.2.1.6.")));
							if (use)
							{
								string oidTail = 
									oid.Right(oid.GetLength()-string(L"1.2.643.6.2.1.6.").GetLength());
								//
								use = (
									(oidTail.Left(5) == L"1.101") ||
									(oidTail.Left(5) == L"1.199") 
									);
							}
							//
							if (use)
							{
								subjectExtraInfo.SetAttribute(OID(oid),AsnObject(v,AsnObject::BMPString));
							}
						}
					}
					//
					//
					//
					// ----
					// �������� �������� ����� � �������
					//
					Key key;
					TextMap containerFiles;
					CCOM_Key ccom_key;
					///SharedPtr<EToken> eToken;
					//
					ccom_key->InitKeyTime(); // TODO: ���������
					COleDateTime keyTime = ccom_key->GetKeyTime();
					CString keyTimeSuffix = FormatTime_ymd_HMD(
						_S("%02d-%02d-%02d"), _S("-%02d-%02d-%02d") // _T("%y-%m-%d-%H-%M-%S")) 
						,keyTime
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
					PKCS11_Manager& M = PKCS11_Manager::Acquire(); 
					//
					if (cryptoSystem == L"CryptoCOM") 
					{
						containerFiles[_T("kek.opq")] = _T("1");
						containerFiles[_T("masks.db3")] = _T("1");
						containerFiles[_T("mk.db3")] = _T("1");
						containerFiles[_T("rand.opq")] = _T("1");
						//
						// ----
						// ������ ���� 
						//
						if (keyMedia == _T("eToken"))
						{
							CComBSTR bstrV2; 
							//
							rc = GetQueryParameter(CComBSTR(L"eTokenID"),&bstrV2); 
							if (rc == S_OK) eTokenID = _W(bstrV2); 
							//
							rc = GetQueryParameter(CComBSTR(L"DeviceID"),&bstrV2); 
							if (rc == S_OK) eTokenID = _W(bstrV2); 
							//
							if (eTokenID.GetLength() == 0) 
							{
								rc = GetQueryParameter(CComBSTR(L"eToken-slot-id"),&bstrV2); 
								if (rc == S_OK) 
								{
									string eTokenSlotIdStr = _W(bstrV2); 
									//
									XmlDocument tokens = M.GetETokenInfo(L""); 
									//
									XmlNodeList L = tokens.SelectNodes(
										FormatStr(L"/*/EToken[@SlotId='%s']", eTokenSlotIdStr )); 
									//
									if (L.Count() > 0) 
									{
										XmlElement E = L[0]; 
										eTokenID = E.GetAttribute(L"eTokenID"); 
									}
								}
							}
							//
							if (eTokenID.GetLength() == 0) 
							{
								throw MethodError(L"�������� eTokenID, eToken-slot-id ��� DeviceID �� ������"); 
							}
							//
							ccom_key->eTokenID = eTokenID; 
						}
						//
						if (keyMedia == _T("eToken"))
						{
							EToken& eToken = EToken::OpenEToken(eTokenID); 
							//
							eToken.Login(); 
							eToken.EnterContext(); 
							//
							CStringA containerPath = eToken.NewKeyPath( 
								keyContainerPwd, 
								keyTime, 
								commonName, 
								OrganizationName, 
								&key_i 
								); 
							//
							ccom_key->key_i = key_i; 
							//
							CCOMLib::LoginEToken(); 
							//
							ccom_key->CreateIn(_S(containerPath), _S(keyContainerPwd), _T("")); 
							//
							eToken.Key_SetFlag(key_i, _KEY_FLAG_OK); 
						}
						else // keyMedia == _T("drive") 
						{
							// ��� ��������� ��������:
							string driveLetter;
							//
							rc = GetQueryParameter(CComBSTR(L"drive-letter"),&bstrV2); 
							if (rc == S_OK) 
							{
								driveLetter = bstrV2;
								driveLetter.Trim();
							}
							if (driveLetter.GetLength() == 0)
							{
								SharedArray<CString> drives = GetKeyDrives();
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
								Path = Machine::TouchDirectory( _S(driveLetter) + _T(":\\") );
							}
							catch(::::Exception e)
							{
								////OutputDebugString(_S(e.GetXml())); 
								string msg2 = L"���������� �������� ���� �� ����-�������� " + 
									driveLetter + L", ������ � �������� ��������"; 
								Exception e2 = e.AddIfNewSource_(msg2);  
								////OutputDebugString(_S(e2.GetXml())); 
								throw e2; 
							}
							//
							CString certDir = Machine::TouchDirectory( Path + _T("\\Certificates") ); 
							keyPath = Machine::TouchDirectory( certDir + _T("\\") + keyName );
							containerPath = Machine::TouchDirectory( keyPath + _T("\\Container") );
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
					// * ������������ ������� ExtraInfo 
					if (eTokenID.GetLength() > 0) 
					{
						subjectExtraInfo.SetAttribute(
							OID(L"1.2.643.6.2.1.6.1.199.9.3"),AsnObject(eTokenID,AsnObject::BMPString) 
							); 
					}
					//
					AsnObject requestExtra = AsnObject::NewSequence();
					requestExtra.Add(AsnObject(OID(string(L"1.2.643.6.2.1.6.6.1"))));
					requestExtra.Add(subjectExtraInfo.AsnObj());
					//
					//
					//
					// ----
					// * ����������� � ��������� ������ 
					//
					if (cryptoSystem == L"CryptoCOM")
					{
#ifdef _DEBUG
						{
							//Blob requestData = request->GetRequestData();
							//AsnObject requestO(requestData); 
							//OutputDebugStringW(requestO.Dump() + L"\n");
						}
#endif
						//
						request->SignRequest();
						//
#ifdef _DEBUG
						{
							//Blob requestData = request->GetRequestData();
							//AsnObject requestO(requestData); 
							//OutputDebugStringW(requestO.Dump() + L"\n");
							//File f;
							//f.OpenToWrite(_T("D:\\RequestNew.der")); 
							//f.Replace((const char*)requestData.GetBuffer(), requestData.Length()); 
							//f.Close(); 
						}
#endif
						//
						if (keyMedia == _T("eToken"))
						{
							Blob requestData = request->GetRequestData(); 
							Blob requestXData = requestExtra.Encoded(); 
							//
							EToken& eToken = EToken::OpenEToken(eTokenID); 
							//
							string reqLabel = FormatStr(L" Request %d", (int)key_i ); 
							//
							eToken.SaveObject(reqLabel, requestData, CKO_DATA, 0); 
							//
							string reqXLabel = FormatStr(L" Request X %d", (int)key_i ); 
							//
							eToken.SaveObject(reqXLabel, requestXData, CKO_DATA, 0); 
						}
						else // keyMedia == _T("drive") 
						{
							request->SaveRequestDER(
								string(keyPath) + L"\\" + string(keyName) + L"-request.der",
								string(keyPath) + L"\\" + string(keyName) + L"-request.p10"
								);
							//
							// SubjectExtraInfo
							//
							Blob requestExtraData = requestExtra.ToBlob();
							//
							File f;
							f.OpenToWrite( keyPath + _T("\\") + keyName + _T("-x.der") );
							f.Replace((char*)requestExtraData.GetBuffer(),requestExtraData.Length());
							f.Close();
						}
						//
						if (keyMedia == _T("eToken")) 
						{
							EToken& eToken = EToken::OpenEToken(eTokenID); 
							eToken.FlushMeta(); 
							eToken.ReleaseContext(); 
							////M.ReleaseContext(); 
						}
					}
					//
					// ----
					// ���������� ���������� � ��������� ������� 
					//
					{
						string pkh64 = __ToBase64(pkh);
						//
						return RequestInfoDocument(pkh64); 
					}
				}
				else if (action == L"ImportETokenKeyV3")
				{
					CComBSTR bstrV2;
					HRESULT rc;
					//
					string path;
					//
					rc = GetQueryParameter(
						CComBSTR(L"path"),
						&bstrV2
						); 
					if (rc == S_OK) 
					{
						path = bstrV2; 
					}
					//
					string targetPkh64;
					//
					rc = GetQueryParameter(
						CComBSTR(L"pkh"),
						&bstrV2
						); 
					if (rc == S_OK) 
					{
						targetPkh64 = bstrV2; 
						targetPkh64 = __ToBase64(FromBase64String(targetPkh64)); 
					}
					//
					if (targetPkh64.GetLength() == 0)  
					{
						XmlDocument doc;
						doc.Load(path); 						
					}
					//
					return OkDocument(0); 
				}
				else if (action == L"ImportKey")
				{
					CComBSTR bstrV2;
					HRESULT rc;
					//
					// ���� �������������? 
					//
					rc = GetQueryParameter(
						CComBSTR(L"key-media-type"),
						&bstrV2
						); 
					if (rc != S_OK) throw MethodError(L"�������� key-media-type �� ������");
					string keyMediaType = bstrV2;
					//
					int eTokenSLotId = -1;
					//int key_i = -1; 
					//int key_mode = 2; // NEW KEYS 
					CStringA containerPath; 
					PKCS11_Manager* pM = 0;
					//
					if (keyMediaType == L"eToken") 
					{
						pM = &(PKCS11_Manager::Acquire()); 
						//
						HRESULT rc = GetQueryParameter(
							CComBSTR(L"eToken-slot-id"),
							&bstrV2
							); 
						if (rc != S_OK) throw MethodError(L"�������� eToken-slot-id �� ������"); 
						//
						eTokenSLotId = _wtoi(_W(bstrV2)); 
						//
						// pre-login 
						//
						if (GetQueryParameter(CComBSTR(L"pin-code"),&bstrV2) == S_OK)
						{
							string pinCode(bstrV2); 
							//
							if (pinCode.GetLength() > 0) 
							{
								EToken::SetAllPinsTo(pinCode);
							}
							else throw MethodError(L"PinCode �� ������"); 
						}
						else throw MethodError(L"PinCode �� ������ (1)"); 
						//
						//%//
						//pM->LoginEToken(eTokenSLotId); 
						//CCOMLib::LoginEToken(); 
						//
						// open context 
						//
						pM->EnterContext(eTokenSLotId); 
					}
					//
					//
					// ��������� ���������� ��� ������� 
					//
					rc = GetQueryParameter(
						CComBSTR(L"pkh"),
						&bstrV2
						); 
					if (rc != S_OK) throw MethodError(L"�������� pkh �� ������");
					string target_pkh64 = __ToBase64(FromBase64String(_W(bstrV2))); 
					//
					CComPtr<IStream> sourceStream; 
					rc = m_Composer->get_PostStream(&sourceStream); 
					if (FAILED(rc)) throw MethodError(rc); 
					//
					XmlDocument doc;
					doc.LoadStream(sourceStream); 
					//
					// �����������
					//
					XmlNodeList KeyInfo_L = doc.SelectNodes(L"/CommonKeyInfo/KeyInfo"); 
					for (int k = 0; k < KeyInfo_L.Count(); k++)
					{
						XmlElement KeyInfo_E = KeyInfo_L[k]; 
						//
						string pkh64 = __ToBase64(FromBase64String(KeyInfo_E.GetAttribute(L"PubKeyHash"))); 
						if (pkh64 == target_pkh64)
						{
							// ����������� 
							//
							XmlElement Files_E = KeyInfo_E.SelectSingleNode(L"Files"); 
							string keyContainerPwd = Files_E.GetAttribute(L"ContainerPass"); 
								// FormatStr(L"%d", (int)RandomInt32());
							//
							XmlNodeList File_L = KeyInfo_E.SelectNodes(L"Files/File"); 
							for (int j = 0; j < File_L.Count(); j++)
							{
								XmlElement File_E = File_L[j]; 
								string data64 = File_E.InnerText(); 
								data64.Trim();
								if (data64.GetLength() > 0)
								{
									Blob data = FromBase64String(data64); 
									//
									string name = File_E.GetAttribute(L"Name"); 
									//
									if (keyMediaType == L"eToken") 
									{
										//%//
										//string label = pM->GetObjectLabel(L"A", name); 
										//throw MethodError(L"MODE 2"); 
										//pM->SaveObject(eTokenSLotId, label, data, CKO_DATA, 1); 
									}
									else
									{
										string errMsg = 
											_W(L"������ ����� �� �������������� ��� �������� ") + keyMediaType; 
										throw MethodError(errMsg); 
									}
								}
							}
							//
							if (keyMediaType == L"eToken") 
							{
								//%//
								//pM->SetETokenFlags_E(eTokenSLotId, key_i, key_mode, _PRIVATE_META, 
								//	_KEY_FLAG_OK); 
								////
								//pM->ReleaseContext(); 
							}
						}
					}
				}
				//else if (action == L"TestRequest")
				//{
				//	CComBSTR bstrV2;
				//	//
				//	HRESULT rc = GetQueryParameter(
				//		CComBSTR(L"u_"),
				//		&bstrV2
				//		); 
				//	if (rc != S_OK) throw MethodError(L"�������� u_ �� ������");
				//	string url1 = bstrV2;
				//	//
				//	rc = GetQueryParameter(
				//		CComBSTR(L"f_"),
				//		&bstrV2
				//		); 
				//	if (rc != S_OK) throw MethodError(L"�������� f_ �� ������");
				//	string fileName = bstrV2;
				//	//
				//	Protocol::RequestHandler Request; 
				//	string IncomingURL = url1;
				//	string IncomingHeaders = L"";
				//	Request.Open(IncomingURL, requestStream, IncomingHeaders); 
				//	Request.Run(); 
				//	//
				//	return CommonKeyInfoDocument(); 
				//}
				else if (action == L"RemoveCertificate")
				{
					CComBSTR bstrV2;
					HRESULT rc = GetQueryParameter(
						CComBSTR(L"pkh"),
						&bstrV2
						); 
					if (rc != S_OK) throw MethodError(L"�������� pkh �� ������");
					string pkh64 = bstrV2;
					Blob pkh = FromBase64String(pkh64);
					//
					//XmlDocument d = Instance().PrepareCommonKeyInfo(pkh,Blob(),false, 
					//	Map<string,string>(), false 
					//	); 
					//
					XmlDocument d = CommonKeyInfoDocument_RF3a(); 
					//
					//
					//
					// ��� ��������� ��������:
					rc = GetQueryParameter(CComBSTR(L"key-media-type"),&bstrV2);
					if (rc != S_OK) throw MethodError(L"�������� key-media-type �� ������");
					string keyMedia = bstrV2;
					//
					//
					//
					string xPath = GetKeyInfoXPath(pkh64); 
					XmlNodeList L = d.DocumentElement().SelectNodes(xPath); 
					if (L.Count() == 0)
						throw MethodError(L"���������� �� ������: " + _W(pkh64));
					//
					XmlElement KeyInfo_E = L[0];
					//
					if (keyMedia == _T("eToken"))
					{
						string eTokenID = KeyInfo_E.GetAttribute(L"eTokenID"); 
						//
						EToken& eToken = EToken::OpenEToken(eTokenID); 
						eToken.RemoveCert(pkh64); 
					}
					else // keyMedia == _T("drive")
					{
						CString keyPath = _S(KeyInfo_E.GetAttribute(L"KeyPath"));
						//
						SharedArray<CString> certPaths = Machine::ListFiles(keyPath,_T("*.cer")); 
						for (int i = 0; i < certPaths.Length(); ++i)
						{
							CString certPath = certPaths[i];
							if (certPath.Right(4) == _T(".cer"))
							{
								CString bakPath = certPath.Left(certPath.GetLength()-4) + _T("-cert.bak"); 
								CopyFile(certPath,bakPath,FALSE);
								DeleteFile(certPath);
							}
						}
					}
					//
					return Document( CommonKeyInfoDocument_RF3a() ); 
				}
				else if (action == L"Loopback")
				{
					//Protocol::RequestHandler Request; 
					////
					//Request.Open(IncomingURL,PostStream,IncomingHeaders); 
					//Request.Run(); 
					////
					AttachComposer(); 
					rc = m_Composer->Open(); 
					if (FAILED(rc)) throw MethodError(rc); 
					//
					CComPtr<IStream> sourceStream; 
					rc = m_Composer->get_OutStream(&sourceStream); 
					if (FAILED(rc)) throw MethodError(rc); 
					else if (! sourceStream)
					{
						rc = m_Composer->get_PostStream(&sourceStream); 
						if (FAILED(rc)) throw MethodError(rc); 
					}
					//
					if (! sourceStream) throw MethodError(L"������ ������� �����������"); 
					//
					return FileStream(sourceStream); 
				}
				else if (action == L"SystemInfo")
				{
					XmlDocument d_1; 
					d_1.LoadXml(L"<SystemInfo />");
					XmlElement root = d_1.DocumentElement();
					root.InnerText() = Instance().Application().GetInfo();
					//
					return Document(d_1); 
				}
				else if (action == L"CertificateDER")
				{
					CComBSTR bstrV2;
					HRESULT rc = GetQueryParameter(CComBSTR(L"pkh"),&bstrV2);
					if (rc != S_OK) throw MethodError(L"�������� pkh �� ������");
					string pkh64 = bstrV2;
					//
					//rc = m_spDocument->get_LocalPath(&bstrV2);
					//if (rc != S_OK) throw MethodError(rc);
					//CString localPath = _S(bstrV2);
					//
					Blob pkh = FromBase64String(pkh64);
					//
					//XmlDocument d = Instance().PrepareCommonKeyInfo(pkh,Blob(),false, 
					//	Map<string,string>(), false); 
					//
					XmlDocument d = CommonKeyInfoDocument_RF3a(); 
					//
					string xPath = GetKeyInfoXPath(pkh64); 
					XmlNodeList L = d.DocumentElement().SelectNodes(xPath); 
					if (L.Count() == 0)
						throw MethodError(L"���������� �� ������: " + _W(pkh64));
					//
					XmlElement KeyInfo_E = L[0]; 
					string keyMedia = KeyInfo_E.GetAttribute(L"KeyMediaType"); 
					//
					if (keyMedia == _T("eToken"))
					{
						string eTokenID = KeyInfo_E.GetAttribute(L"eTokenID"); 
						// int key_i = _wtoi(KeyInfo_E.GetAttribute(L"KeyNum"));
						//
						//string requestPath = PKCS11_Manager_().EToken_GetCertPath(eTokenSlotId, key_i); 
						//
						OkDocument(-1); 
						//ReturnFile(_S(requestPath),L"application/x-x509-ca-cert");
					}
					else // keyMedia == _T("drive")
					{
						CString keyPath = _S(KeyInfo_E.GetAttribute(L"KeyPath"));
						//
						SharedArray<CString> certPaths = Machine::ListFiles(keyPath,_T("*.cer"));
						if (certPaths.Length() == 0) 
						{
							throw MethodError(L"���� ����������� �� ������: " + _W(pkh64));
						}
						//
						CString certPath = certPaths[0];
						//
						ReturnFile(certPath,L"application/x-x509-ca-cert");
					}
					//
					return S_OK;
				}
				else if (action == L"LoginEToken")
				{
					PKCS11_Manager& M = PKCS11_Manager_(); 
					if (! M.wasInit) 
					{
						throw MethodInfoExc(L"������� eToken �� ����������");  
					}
					//
					string eTokenID; 
					//
					CComBSTR bstrV; 
					HRESULT rc = GetQueryParameter(CComBSTR(L"login-eToken-SerialNumber"),&bstrV); 
					if (rc == S_OK) eTokenID = _W(bstrV); 
					//
					rc = GetQueryParameter(CComBSTR(L"login-eToken-ID"),&bstrV); 
					if (rc == S_OK) eTokenID = _W(bstrV); 
					//
					eTokenID.Trim(); 
					//
					if (eTokenID.GetLength() == 0) throw MethodError(L"�������� eTokenID �� ������"); 
					//
					rc = GetQueryParameter(CComBSTR(L"eToken-pin"),&bstrV); 
					// if (rc != S_OK) throw MethodError(L"�������� eToken-pin �� ������"); 
					if (rc == S_OK)
					{
						string pin1 = _W(bstrV); 
						EToken::SetAllPinsTo(pin1); 
					}
					//
					XmlDocument doc = PKCS11_Manager_().GetETokenInfo(L"", 0); 
					XmlElement docRoot = doc.DocumentElement(); 
					XmlNodeList L = docRoot.SelectNodes(L"/*/EToken[@eTokenID='" + eTokenID + L"']"); 
					if (L.Count() == 0) throw MethodError(L"eToken ID=" + eTokenID + L" �� ������"); 
					//
					//string slotIdStr = ((XmlElement)L[0]).GetAttribute(L"SlotId"); 
					//int slotId = _wtoi(slotIdStr); 
					//
					//%//
					//M.LoginEToken(slotId); 
					//CCOMLib::LoginEToken(); 
					//
					return OkDocument(0); 
				}
				else if (action == L"RequestDER")
				{
					CComBSTR bstrV2;
					HRESULT rc = GetQueryParameter(CComBSTR(L"pkh"),&bstrV2);
					if (rc != S_OK) throw MethodError(L"�������� pkh �� ������");
					string pkh64 = bstrV2;
					//
					//rc = m_spDocument->get_LocalPath(&bstrV2);
					//if (rc != S_OK) throw MethodError(rc);
					//CString localPath = _S(bstrV2);
					//
					Blob pkh = FromBase64String(pkh64);
					//
					//XmlDocument d = Instance().PrepareCommonKeyInfo(pkh,Blob(),false, 
					//	Map<string,string>(), false); 
					//
					XmlDocument d = CommonKeyInfoDocument_RF3a(); 
					//
					XmlElement dRoot = d.DocumentElement(); 
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
					SharedArray<CString> reqPaths = Machine::ListFiles(keyPath,_T("*-request.der"));
					if (reqPaths.Length() == 0) 
					{
						throw MethodError(L"������ �� ������ " + _W(pkh64)); 
					}
					//
					CString reqPath = reqPaths[0];
					//
					ReturnFile(reqPath,L"application/x-x509-der"); 
					//
					////CopyFile(reqPath,localPath,FALSE);
					////rc = m_spDocument->put_ContentType(CComBSTR(L"application/x-x509-der"));
					////if (rc != S_OK) throw MethodError(rc);
					////rc = m_spDocument->UpdateFileParameters();
					////if (rc != S_OK) throw MethodError(rc);
					////rc = m_spDocument->put_Status(200);
					////if (rc != S_OK) throw MethodError(rc);
					//
					return S_OK;
				}
				else if (action == L"UpdateKeys")
				{
					string eTokenID; 
					//
					PKCS11_Manager& M = PKCS11_Manager_(); 
					//
					CComBSTR bstrV2; 
					//
					rc = GetQueryParameter(CComBSTR(L"eTokenID"),&bstrV2); 
					if (rc == S_OK) eTokenID = _W(bstrV2); 
					//
					rc = GetQueryParameter(CComBSTR(L"DeviceID"),&bstrV2); 
					if (rc == S_OK) eTokenID = _W(bstrV2); 
					//
					if (eTokenID.GetLength() == 0) 
					{
						rc = GetQueryParameter(CComBSTR(L"eToken-slot-id"),&bstrV2); 
						if (rc == S_OK) 
						{
							string eTokenSlotIdStr = _W(bstrV2); 
							//
							XmlDocument tokens = M.GetETokenInfo(L""); 
							//
							XmlNodeList L = tokens.SelectNodes(
								FormatStr(L"/*/EToken[@SlotId='%s']", eTokenSlotIdStr )); 
							//
							if (L.Count() > 0) 
							{
								XmlElement E = L[0]; 
								eTokenID = E.GetAttribute(L"eTokenID"); 
							}
						}
					}
					//
					if (eTokenID.GetLength() == 0) 
					{
						throw MethodError(L"�������� eTokenID, eToken-slot-id ��� DeviceID �� ������"); 
					}
					//
					EToken& eToken = EToken::OpenEToken(eTokenID); 
					//
					eToken.Login(); 
					eToken.EnterContext(); 
					//
					CCOMLib::LoginEToken(); 
					//
					eToken.UpdateOldMetaStructures(); 
					//
					eToken.ReleaseContext(); 
					//
					return OkDocument(0); 
				}
				else if (action == L"CRLInfo") 
				{
					//CComBSTR bstrV2;
					//HRESULT rc = GetQueryParameter(CComBSTR(L"pkh"),&bstrV2);
					//if (rc != S_OK) throw MethodError(L"�������� pkh �� ������");
					//string pkh64 = bstrV2;
					//
					XmlDocument d_1 = EToken::ReadCRL_1(); 
					//
					return Document(d_1); 
				}
				else if (action == L"InstallCertificate" || action == L"InstallCertificateXml") 
				{
					CComBSTR bstrV2;
					HRESULT rc = GetQueryParameter(CComBSTR(L"pkh"),&bstrV2);
					if (rc != S_OK) throw MethodError(L"�������� pkh �� ������");
					string pkh64 = bstrV2;
					//
					CComBSTR bstrVCert;
					rc = GetQueryParameter(CComBSTR(L"certificate-data"),&bstrVCert); 
					if (rc != S_OK) throw MethodError(L"�������� certificate-data �� ������");
					string cert64 = _W(bstrVCert);
					//
					string a_1 = cert64.Left(5);
					a_1.Trim();
					if (a_1.Left(1) == L"<" || a_1.GetLength() == 0)
					{
						rc = GetQueryParameterInner(CComBSTR(L"certificate-data"),&bstrVCert); 
						if (rc != S_OK) throw MethodError(L"�������� certificate-data �� ������");
						cert64 = _W(bstrVCert);
					}
					//
					Blob certificateData = FromBase64String(cert64); 
					//
					Blob pkh = FromBase64String(pkh64);
					//
					InstallCertificate(pkh,certificateData); 
					//
					//XmlDocument d_1 = Instance().PrepareCommonKeyInfo(
					//	pkh, Blob(), false, 
					//	Map<string,string>(), false 
					//	); 
					//
					XmlDocument d_1 = CommonKeyInfoDocument_RF3a(); 
					//
					return Document(d_1); 
				}
				else if (action == L"InstallGenCert") 
				{
					CComBSTR bstrVCert;
					HRESULT rc = GetQueryParameter(CComBSTR(L"certificate-data"),&bstrVCert); 
					if (rc != S_OK) throw MethodError(L"�������� certificate-data �� ������");
					string cert64 = _W(bstrVCert);
					Blob certificateData = FromBase64String(cert64); 
					//
					CCOM_CertificateObject certificateObj;
					certificateObj.Import(certificateData); 
					//
					Blob pkh = certificateObj.GetPKH();
					if (pkh.Length() == 0) throw MethodError(L"������ ������ ����������� � �������� ���������"); 
					//
					InstallCertificate(pkh,certificateData); 
					//
					//XmlDocument d_1 = Instance().PrepareCommonKeyInfo(pkh,Blob(),false, 
					//	Map<string,string>(), false); 
					//
					XmlDocument d_1 = CommonKeyInfoDocument_RF3a(); 
					//
					return Document(d_1); 
				}
				else if (action == L"RemoveRequest")
				{
					CComBSTR bstrV2;
					HRESULT rc = GetQueryParameter(CComBSTR(L"pkh"),&bstrV2);
					if (rc != S_OK) throw MethodError(L"�������� pkh �� ������"); 
					string pkh64 = bstrV2;
					//
					Blob pkh = FromBase64String(pkh64);
					//XmlDocument d = Instance().PrepareCommonKeyInfo(pkh,Blob(),false, 
					//	Map<string,string>(), false); 
					XmlDocument d = CommonKeyInfoDocument_RF3a(); 
					//
					string xPath = GetKeyInfoXPath(pkh64); 
					XmlNodeList L = d.DocumentElement().SelectNodes(xPath); 
					if (L.Count() == 0)
						throw MethodError(L"���������� �� ������: " + _W(pkh64));
					//
					XmlElement KeyInfo_E = L[0];
					string keyMedia = KeyInfo_E.GetAttribute(L"KeyMediaType"); 
					//
					if (keyMedia == L"eToken")
					{
						string eTokenID = KeyInfo_E.GetAttribute(L"eTokenID"); 
						//
						//PKCS11_Manager& M = PKCS11_Manager_(); 
						////
						//CComBSTR bstrV2; 
						////
						//rc = GetQueryParameter(CComBSTR(L"eTokenID"),&bstrV2); 
						//if (rc == S_OK) eTokenID = _W(bstrV2); 
						////
						//rc = GetQueryParameter(CComBSTR(L"DeviceID"),&bstrV2); 
						//if (rc == S_OK) eTokenID = _W(bstrV2); 
						////
						//eTokenID.Trim(); 
						////
						//if (eTokenID.GetLength() == 0) throw MethodError(L"�������� eTokenID �� ������"); 
						//
						EToken& eToken = EToken::OpenEToken(eTokenID); 
						eToken.RemoveKey(pkh64); 
						//
						//int eTokenSlotId = _wtoi(KeyInfo_E.GetAttribute(L"ETokenSlotId"));
						//int key_i = _wtoi(KeyInfo_E.GetAttribute(L"KeyNum"));
						////
						//PKCS11_Manager_().ETokenFlagOff(eTokenSlotId, key_i, _KEY_FLAG_OK); 
						////
						//string path = PKCS11_Manager_().EToken_GetKeyContainerPath(eTokenSlotId, key_i); 
						//CStringA pathA = PKCS11_Manager::ETokenPath(eTokenSlotId, path); 
						////
						//CStringA certPathA = pathA + "/fc01"; 
						//CADB_erase_file(certPathA.GetBuffer()); 
						////
						//CStringA certRequestPathA = pathA + "/fe01"; 
						//CADB_erase_file(certRequestPathA.GetBuffer()); 
						////
						//CStringA certRequestXOPathA = pathA + "/fe02"; 
						//CADB_erase_file(certRequestXOPathA.GetBuffer()); 
						////
						//CStringA keyPathA = pathA + "/fa01"; 
						//CADB_erase_file(keyPathA.GetBuffer()); 
						////
						//keyPathA = pathA + "/a001"; 
						//CADB_erase_file(keyPathA.GetBuffer()); 
						////
						//keyPathA = pathA + "/b001"; 
						//CADB_erase_file(keyPathA.GetBuffer()); 
						////
						//keyPathA = pathA + "/c001"; 
						//CADB_erase_file(keyPathA.GetBuffer()); 
						////
						//keyPathA = pathA + "/d001"; 
						//CADB_erase_file(keyPathA.GetBuffer()); 
					}
					else // drive 
					{
						CString keyPath = _S(KeyInfo_E.GetAttribute(L"KeyPath"));
						//
						if (keyPath.Find(_T("\\")) != -1)
						{
							SharedArray<CString> paths = Machine::ListFiles(
								keyPath + _T("\\Container"), _T("*.*"));
							for (int i = 0; i < paths.Length(); ++i)
							{
								CString path = paths[i];
								DeleteFile(path);
							}
							RemoveDirectory(keyPath + _T("\\Container"));
							//
							paths = Machine::ListFiles(keyPath,_T("*.xml"));
							for (int i = 0; i < paths.Length(); ++i)
							{
								CString path = paths[i];
								DeleteFile(path);
							}
							paths = Machine::ListFiles(keyPath,_T("*.p10"));
							for (int i = 0; i < paths.Length(); ++i)
							{
								CString path = paths[i];
								DeleteFile(path);
							}
							paths = Machine::ListFiles(keyPath,_T("*.der"));
							for (int i = 0; i < paths.Length(); ++i)
							{
								CString path = paths[i];
								DeleteFile(path);
							}
							paths = Machine::ListFiles(keyPath,_T("*.cer"));
							for (int i = 0; i < paths.Length(); ++i)
							{
								CString path = paths[i];
								DeleteFile(path);
							}
							paths = Machine::ListFiles(keyPath,_T("*.bak")); 
							for (int i = 0; i < paths.Length(); ++i)
							{
								CString path = paths[i];
								DeleteFile(path);
							}
							RemoveDirectory(keyPath);
						}
					}
					//
					return Document( CommonKeyInfoDocument_RF3a() ); 
				}
				else if (action == L"ListCerts")
				{
					CComBSTR bstrV2;
					HRESULT rc = GetQueryParameter(CComBSTR(L"store-name"),&bstrV2);
					if (rc != S_OK) throw MethodError(L"�������� store-name �� ������"); 
					string storeName(bstrV2);
					//
					string cnSearch;
					rc = GetQueryParameter(CComBSTR(L"cn-search"),&bstrV2);
					if (rc != S_OK) {} 
					else cnSearch = _W(bstrV2);
					//
					bool notOnlyValid = false;
					rc = GetQueryParameter(CComBSTR(L"not-only-valid"),&bstrV2);
					if (rc != S_OK) {} 
					else notOnlyValid = (_W(bstrV2) == L"1");
					//
					// ����������� �����������
					//
					XmlDocument doc;
					doc.LoadXml(L"<Certificates />");
					XmlElement root = doc.SelectSingleNode(L"Certificates"); 
					//
					HANDLE hStoreHandle = NULL;
					PCCERT_CONTEXT pCertContext = NULL;   
					//
					hStoreHandle = CertOpenSystemStoreW(NULL,storeName); 
					if (hStoreHandle)
					{
					}
					else
					{
						HRESULT rc = HRESULT_FROM_WIN32(GetLastError()); 
						throw MethodError(rc);
					}
					//
					pCertContext= CertEnumCertificatesInStore(hStoreHandle,pCertContext); 
					while(pCertContext) 
					{
						bool use = true; 
						//
						if (cnSearch.GetLength() > 0) use = false; 
						//
						//SYSTEMTIME st;
						//FILETIME lft;   
						//FileTimeToLocalFileTime((const FILETIME *)&
						//	pCertContext->pCertInfo->NotBefore, &lft);
						//FileTimeToSystemTime(( const FILETIME *)&
						//	pCertContext->pCertInfo->NotBefore, &st);
						//
						int nValid = CertVerifyTimeValidity(NULL,pCertContext->pCertInfo); 
						//
						// Subject 
						//
						Blob SubjectData;
						DWORD SubjectDataLen= 1024;
						SubjectData.Expand(SubjectDataLen);
						//
						if (!CryptDecodeObject(
							X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
							X509_NAME,
							pCertContext->pCertInfo->Subject.pbData,
							pCertContext->pCertInfo->Subject.cbData,
							0,
							SubjectData.GetBuffer(),
							&SubjectDataLen
							))
						{
							HRESULT rc = HRESULT_FROM_WIN32(GetLastError()); 
							throw MethodError(rc);
						}
						//
						SubjectData.SetSize(SubjectDataLen); 
						CERT_NAME_INFO* pSubject = (CERT_NAME_INFO*)SubjectData.GetBuffer(); 
						//
						string cn;
						//
						for (int k = 0; k < (int)pSubject->cRDN; k++)
						{
							string oid = _W(pSubject->rgRDN[k].rgRDNAttr->pszObjId); 
							//
							if (oid == X500().sCommonNameOid)
							{
								if (pSubject->rgRDN[k].rgRDNAttr->dwValueType == CERT_RDN_PRINTABLE_STRING)
								{
									cn = _W(CStringA(
										(const char*)pSubject->rgRDN[k].rgRDNAttr->Value.pbData,
										(int)pSubject->rgRDN[k].rgRDNAttr->Value.cbData) 
										);
								}
								//
								if (cn.GetLength() > 0)
								{
									use = true; 
									if (cnSearch.GetLength() > 0)
									{
										if (cn.Find(cnSearch) == -1) use = false; 
									}
								}
							}
						}
						//
						if ((nValid != 0) && (!notOnlyValid)) use = false; 
						//
						// �������� � ������ 
						//
						if (use)
						{
							XmlElement E = doc.CreateElement(L"",L"CertificateInfo",L""); 
							root.AppendChild(E); 
							//
							E.SetAttribute(L"CommonName",cn); 
							E.SetAttribute(L"Validity", FormatStr(L"%d", (int)nValid )); 
						}
						//
						pCertContext = CertEnumCertificatesInStore(hStoreHandle,pCertContext); 
					}
					//
					if (!CertCloseStore(hStoreHandle,0))
					{
						// does not matter 
					}
					//
					return Document(doc);
				}
				else if (action == L"RequestInfo")
				{
					CComBSTR bstrV2;
					HRESULT rc = GetQueryParameter(CComBSTR(L"pkh"),&bstrV2); 
					if (rc != S_OK) throw MethodError(L"�������� pkh �� ������"); 
					string pkh64(bstrV2);
					if (pkh64.GetLength() == 0) 
						throw MethodError(L"�������� pkh ����� ��������� ������: (�����)");
					//
					return RequestInfoDocument(pkh64);
				}
				else if (action == L"ClientPKH")
				{
					CComBSTR bstrPkh64; 
					HRESULT rc = CurrentClient()->get_PublicKeyHash(&bstrPkh64);
					if (FAILED(rc)) throw MethodError(rc); 
					//
					string clientPkh64 = _W(bstrPkh64); 
					//
					XmlDocument doc = _Clients().GetClientPkhInfoDocument(clientPkh64); 
					//
					return Document(doc);
				}
				else if (action == L"ETokenDeviceInfo") 
				{
					PKCS11_Manager& M = PKCS11_Manager::Acquire();
					if (! M.wasInit) 
					{
						throw MethodInfoExc(L"������� eToken �� ����������"); 
					}
					//
					// pre-login 
					//
					if (GetQueryParameter(CComBSTR(L"pin-code"),&bstrV2) == S_OK)
					{
						string pinCode(bstrV2); 
						//
						if (pinCode.GetLength() > 0) 
						{
							EToken::SetAllPinsTo(pinCode);
						}
						//else throw MethodError(L"PinCode �� ������"); 
					}
					//else throw MethodError(L"PinCode �� ������ (1)"); 
					//
					CComBSTR loginSlotId; 
					HRESULT rc = GetQueryParameter(CComBSTR(L"login-eToken-slotId"),&loginSlotId);
					if (rc == S_OK) 
					{
						int slotId = -1;
						if (loginSlotId.Length() > 0) slotId = atoi(_A(_W(loginSlotId))); 
						if (slotId != -1)
						{
							EToken& eToken = EToken::OpenEToken(slotId); 
							eToken.Login(); 
							////PKCS11_Manager_().LoginEToken(slotId); 
						}
					}
					//
					// ----
					// ETokenInfo
					//
					bool useXsl = true; // default 
					string vXslUrl = L"/protocol/-protocol-2.xsl";  
					//
					bool useXslParam;
					string vXslUrlParam;
					//
					CComBSTR bstrV2;
					rc = GetQueryParameter(CComBSTR(L"use-xsl"),&bstrV2);
					if (rc == S_OK) 
					{
						string s = _W(bstrV2); 
						s.Trim();
						s.MakeLower(); 
						if ((s == L"true") || (s == L"yes") || (s == L"on") || (s == L"1"))
							useXslParam = true; 
						else
							useXslParam = false; 
					}
					else
					{
						useXslParam = useXsl; // use default 
						vXslUrlParam = vXslUrl; 
					}
					//
					rc = GetQueryParameter(CComBSTR(L"vxsl"),&bstrV2); 
					if (rc == S_OK) 
					{
						vXslUrlParam = _W(bstrV2); 
						if (vXslUrlParam.GetLength() == 0) useXslParam = false; 
					}
					//
					if (useXslParam)
					{
						useXsl = true; 
						vXslUrl = vXslUrlParam; 
					}
					else
					{
						useXsl = false; 
						vXslUrl = L""; 
					}
					//
					// Flags 
					//
					int eTokenFlags = 1; // Only suitable eToken PRO / R2 
					//
					CComBSTR bStreTokenFlags;
					HRESULT rc1 = GetQueryParameter(CComBSTR(L"eToken-flags"),&bStreTokenFlags);
					if (rc1 == S_OK) eTokenFlags = _wtoi(_W(bStreTokenFlags)); 
					//
					XmlDocument doc = PKCS11_Manager_().GetETokenInfo(vXslUrl, eTokenFlags); 
					//
					// ----
					// ��������� �� SerialNumber 
					// 
					string eTokenID; 
					//
					CComBSTR loginETokenSerialNum;
					rc = GetQueryParameter(
						CComBSTR(L"login-eToken-SerialNumber"),
						&loginETokenSerialNum);
					if (rc == S_OK) 
					{
						eTokenID = _W(loginETokenSerialNum); 
					}
					//
					rc = GetQueryParameter(
						CComBSTR(L"login-eToken-ID"),
						&loginETokenSerialNum);
					if (rc == S_OK) 
					{
						eTokenID = _W(loginETokenSerialNum); 
					}
					//
					if (eTokenID.GetLength() > 0) 
					{
						XmlElement root = doc.DocumentElement(); 
						XmlNodeList L = root.SelectNodes(
							L"/*/EToken[@SerialNumber='" + eTokenID + L"']"
							); 
						//
						int slotId = -1;
						if (L.Count() > 0) 
						{
							XmlElement eToken_E = L[0]; 
							//
							slotId = _wtoi(eToken_E.GetAttribute(L"SlotId")); 
						}
						if (slotId != -1)
						{
							EToken& eToken = EToken::OpenEToken(slotId); 
							eToken.Login(); 
							//
							doc = PKCS11_Manager_().GetETokenInfo(vXslUrl, eTokenFlags); 
						}
					}
					//
					return Document(doc);
				}
				//else if (action == L"SetClientPKH")
				//{
				//	Client& client = Client();
				//	//
				//	CComBSTR bstrPkh64;
				//	rc = GetQueryParameter(CComBSTR(L"pkh"),&bstrPkh64);
				//	if (rc != S_OK) throw MethodError(rc);
				//	//
				//	client.GetCabinetApp().SetVariable(_T("client-pkh"),_S(bstrPkh64));
				//	//
				//	return RcReport(S_OK,string(bstrPkh64));
				//}
				else if (action == L"RestoreContainer") 
				{
					CComBSTR bstrPkh64;
					rc = GetQueryParameter(CComBSTR(L"pkh"),&bstrPkh64);
					if (rc != S_OK) throw MethodError(L"�������� pkh �� ������"); 
					//
					string pkh64 = _W(bstrPkh64); 
					Blob pkh = FromBase64String(pkh64); 
					//
					Map<string,string> filter; 
					bool woBin = true; 
					XmlDocument doc = Instance().PrepareCommonKeyInfo_RF1a(
						false,
						filter, 
						woBin
						); 
					//
					XmlNodeList L = doc.SelectNodes(L"/*/KeyInfo[@PubKeyHash='" + pkh64 + L"']"); 
					//
					if (L.Count() == 0) throw MethodError(L"���� pkh=" + pkh64 + L" �� ���������"); 
					//
					string path = ((XmlElement)L[0]).GetAttribute(L"KeyPath"); 
					Instance().RestoreContainer_RF1b(_S(path)); 
					//
					return OkDocument(0);
				}
				else if (action == L"GetActivePKH")
				{
					XmlDocument d = _Clients().GetActivePkhInfo(); 
					return Document(d);
				}
				else if (action == L"SetActivePKH") 
				{
					CComBSTR bstrPkh64;
					rc = GetQueryParameter(CComBSTR(L"pkh"),&bstrPkh64);
					if (rc != S_OK) throw MethodError(L"�������� pkh �� ������");  
					// 
					if (bstrPkh64.Length() == 0) throw MethodError(E_INVALIDARG); 
					string pkh64(bstrPkh64);
					Blob pkh = FromBase64String(pkh64); 
					//
					string pwd; 
					CComBSTR bstrV; 
					if (GetQueryParameter(CComBSTR(L"pwd"),&bstrV) == S_OK)
					{
						pwd = _W(bstrV); 
					}
					//
					_Clients().ActivatePkh(pkh); 
					//
#					ifdef _DEBUG
					{
						string msg1 = L"pkh: " + pkh64 + L"\n";
						//OutputDebugStringW(msg1);
					}
#					endif
					//
					bool useXsl = (!useXslFound) || (useXslFound & useXslParam); 
					//
					bool woBin = false; 
					//
					if (GetQueryParameter(CComBSTR(L"wo-bin"),&bstrV) == S_OK)
					{
						string V = bstrV;
						V.Trim();
						V.MakeLower();
						woBin = (V == L"yes") || (V == L"true") || (V == L"��") || (V == L"1");
					}
					//
					Map<string,string> filter; 
					//
					XmlDocument doc = Instance().PrepareCommonKeyInfo_RF1a(
						useXsl,
						filter, 
						woBin
						); 
					return Document(doc); 
					// return CommonKeyInfoDocument(useXsl); // forse XSL 
				}
				else if (action == L"ActivateKey") 
				{
					CComBSTR bstrPkh64;
					rc = GetQueryParameter(CComBSTR(L"pkh"),&bstrPkh64);
					if (rc != S_OK) throw MethodError(L"�������� pkh �� ������");  
					// 
					if (bstrPkh64.Length() == 0) throw MethodError(E_INVALIDARG); 
					string pkh64__1(bstrPkh64);
					pkh64__1.Trim(); 
					Blob pkh = FromBase64String(pkh64__1); 
					//
					if (pkh.Length() == 0) 
						throw MethodError(L"pkh �����, ��� ��������� ����� �������� ������������ pkh"); 
					//
					string pkh64 = __ToBase64(pkh); 
					//
					XmlDocument deviceInfoDoc = Instance().DeviceInfo(); 
					XmlElement deviceInfo = deviceInfoDoc.DocumentElement(); 
					//
					XmlNodeList L = deviceInfo.SelectNodes(
						L"Device/Keys/Key[@PubKeyHash='" + pkh64 + L"']"); 
					//
					bool doActivation = false; 
					if (L.Count() > 0) 
					{
						XmlElement Key_E = L[0]; 
						//
						bool alreadyActive = false; 
						if (Key_E.HasAttribute(L"IsActive")) 
						{
							string a = Key_E.GetAttribute(L"IsActive"); 
							if (a == L"true") alreadyActive = true; 
						}
						//
						if (! alreadyActive) doActivation = true; 
					}
					else
					{
						string msg = L"���� � pkh='" + pkh64 + L"' �� ��������"; 
						throw MethodError(msg); 
					}
					//
					//string pwd; 
					//CComBSTR bstrV; 
					//if (GetQueryParameter(CComBSTR(L"pwd"),&bstrV) == S_OK)
					//{
					//	pwd = _W(bstrV); 
					//}
					//
					if (doActivation) 
					{
						ISlotClient* client = _Clients().ActivatePkh(pkh); 
						//
						return ActiveKeyDocument(pkh64, client); 
					}
					else
					{
						return ActiveKeyDocument(pkh64, 0); 
					}
					//
#					ifdef _DEBUG
					{
						string msg1 = L"pkh: " + pkh64 + L"\n";
						//OutputDebugStringW(msg1);
					}
#					endif
				}
				else if (action == L"RemovableDrives")
				{
					PKCS11_Manager::Lock lock; 
					//
					XmlDocument doc;
					doc.LoadXml(Instance().DriveInfoTemplate());
					//
					XmlElement DriveInfo_E = doc.DocumentElement();
					//
					SharedArray<CString> drives = GetKeyDrives();
					//
					for (int drive_i = 0; drive_i < drives.Length(); ++drive_i)
					{
						CString letter = drives[drive_i];
						//
						XmlElement Drive_E = doc.CreateElement(L"", L"Drive", L""); 
						Drive_E.SetAttribute(L"letter",string(letter));
						DriveInfo_E.AppendChild(Drive_E);
					}
					//
					return Document(doc);
				}
				else if (action == L"GetTokenMeta")
				{
					PKCS11_Manager M = PKCS11_Manager::Acquire(); 
					//
					string eTokenID; 
					string deviceId; 
					//
					CComBSTR bstrETokenID;
					HRESULT rc = GetQueryParameter(CComBSTR(L"eTokenID"),&bstrETokenID);
					if (rc == S_OK) eTokenID = _W(bstrETokenID); 
					//
					CComBSTR bstrDeviceID;
					rc = GetQueryParameter(CComBSTR(L"DeviceID"),&bstrDeviceID);
					if (rc == S_OK) deviceId = _W(bstrDeviceID); 
					//
					DeviceInfo di; 
					//
					if (deviceId.GetLength() > 0)
					{
						di.SetID(deviceId); 
					}
					else if (eTokenID.GetLength() > 0)
					{
						di.SetIDAndType(eTokenID, _DI_UNK_DEVICE_T_ETOKEN); 
					}
					//
					if (di.Unknown())
					{
						throw MethodError(L"�� ������ �������� DeviceID ��� eTokenID");  
					}
					// 
					string oid;
					string metaLabel; 
					//
					CComBSTR bstrOid; 
					rc = GetQueryParameter(CComBSTR(L"oid"),&bstrOid);
					if (rc == S_OK) oid = _W(bstrOid); 
					//
					CComBSTR bstrLabel; 
					rc = GetQueryParameter(CComBSTR(L"meta-label"),&bstrLabel);
					if (rc == S_OK) metaLabel = _W(bstrLabel); 
					//
					if ((metaLabel.GetLength() == 0) && (oid.GetLength() == 0)) 
					{
						throw MethodError(L"�� ������ �������� meta-label ��� oid"); 
					}
					//
					string label = metaLabel; 
					if (metaLabel.GetLength() > 0)
					{
					}
					else
					{
						label = EToken::MetaOidToLabel(oid); 
					}
					//
					AsnObject O = AsnObject::NewSequence(); 
					//
					if (di.DeviceType == _DI_UNK_DEVICE_T_ETOKEN)
					{
						EToken& eToken = EToken::OpenEToken(eTokenID); 
						if (metaLabel.GetLength() > 0) 
						{
							O = eToken.ReadMetaObjectAsn(metaLabel); 
						}
						else if (oid.GetLength() > 0) 
						{
							O = eToken.ReadMetaObjectOidAsn(oid); 
						}
					}
					else if (di.DeviceType == _DI_UNK_DEVICE_T_RDRIVE)
					{
						Blob Odata = Instance().Drive_ReadObject(di.ID, label); 
						O = AsnObject(Odata); 
					}
					//
					XmlDocument doc = M.AsnDictionaryToXml(O); 
					//
					return Document(doc); 
				}
				else if (action == L"SetTokenMeta")
				{
					PKCS11_Manager M = PKCS11_Manager::Acquire(); 
					//
					string eTokenID; 
					string deviceId; 
					//
					CComBSTR bstrETokenID;
					HRESULT rc = GetQueryParameter(CComBSTR(L"eTokenID"),&bstrETokenID);
					if (rc == S_OK) eTokenID = _W(bstrETokenID); 
					//
					CComBSTR bstrDeviceID;
					rc = GetQueryParameter(CComBSTR(L"DeviceID"),&bstrDeviceID);
					if (rc == S_OK) deviceId = _W(bstrDeviceID); 
					//
					DeviceInfo di; 
					//
					if (deviceId.GetLength() > 0)
					{
						di.SetID(deviceId); 
					}
					else if (eTokenID.GetLength() > 0)
					{
						di.SetIDAndType(eTokenID, _DI_UNK_DEVICE_T_ETOKEN); 
					}
					//
					if (di.Unknown())
					{
						throw MethodError(L"�� ������ �������� DeviceID ��� eTokenID");  
					}
					//
					string oid;
					string metaLabel; 
					//
					CComBSTR bstrOid; 
					rc = GetQueryParameter(CComBSTR(L"oid"),&bstrOid);
					if (rc == S_OK) oid = _W(bstrOid); 
					//
					CComBSTR bstrLabel; 
					rc = GetQueryParameter(CComBSTR(L"meta-label"),&bstrLabel);
					if (rc == S_OK) metaLabel = _W(bstrLabel); 
					//
					if ((metaLabel.GetLength() == 0) && (oid.GetLength() == 0)) 
					{
						throw MethodError(L"�� ������ �������� meta-label ��� oid"); 
					}
					//
					string label = metaLabel; 
					if (metaLabel.GetLength() > 0)
					{
					}
					else
					{
						label = EToken::MetaOidToLabel(oid); 
					}
					//
					CComPtr<IStream> sourceStream; 
					rc = m_Composer->get_PostStream(&sourceStream); 
					if (FAILED(rc)) throw MethodError(L"����������� ������� �������� (ASN XML)"); // MethodError(rc); 
					//
					XmlDocument asnDoc;
					asnDoc.LoadStream(sourceStream); 
					//
					if (di.DeviceType == _DI_UNK_DEVICE_T_ETOKEN)
					{
						EToken& eToken = EToken::OpenEToken(eTokenID); 
						if (metaLabel.GetLength() > 0) 
						{
							int isPrivate; 
							{
								string vStr; 
								CComBSTR V; 
								rc = GetQueryParameter(CComBSTR(L"is-private"),&V);
								if (rc == S_OK) vStr = _W(V); 
								else throw MethodError(L"��������� �������� is-private"); 
								//
								vStr.Trim(); 
								isPrivate = 0; 
								if (vStr == L"1" || vStr == L"true") isPrivate = 1; 
							}
							//
							eToken.SaveMetaObject(metaLabel, (CK_BBOOL)isPrivate, asnDoc); 
							AsnObject O = AsnObject(eToken.ReadMetaObject(metaLabel)); 
							//
							XmlDocument doc = M.AsnDictionaryToXml(O); 
							//
							return Document(doc); 
						}
						else if (oid.GetLength() > 0) 
						{
							eToken.SaveMetaObjectOid(oid, asnDoc); 
							AsnObject O = AsnObject(eToken.ReadMetaObjectOid(oid)); 
							//
							XmlDocument doc = M.AsnDictionaryToXml(O); 
							//
							return Document(doc); 
						}
					}
					else if (di.DeviceType == _DI_UNK_DEVICE_T_RDRIVE)
					{
						AsnObject O = PKCS11_Manager_().XmlToAsnDictionary(asnDoc); 
						Blob Odata = O.Encoded(); 
						//
						Instance().Drive_SaveObject(di.ID, label, Odata); 
						//
						Blob b1 = Instance().Drive_ReadObject(di.ID, label); 
						AsnObject a2(b1); 
						//
						XmlDocument doc = PKCS11_Manager_().AsnDictionaryToXml( 
							a2 
							); 
						//
						return Document(doc); 
					}
				}
				else if (action == L"DeviceInfo")
				{
					return Document(Instance().DeviceInfo()); 
				}
				else if (action == L"CommonKeyInfo")
				{
#					ifdef _DEBUG
					////throw MethodError(L"�������� ������"); 
#					endif
					//
					bool useXsl = true;
					CComBSTR bstrV;
					if (GetQueryParameter(CComBSTR(L"use-xsl"),&bstrV) == S_OK)
					{
						string useXslV = bstrV;
						useXslV.Trim();
						useXslV.MakeLower();
						useXsl = (useXslV == L"yes") || (useXslV == L"true") || (useXslV == L"��") ||
							(useXslV == L"1");
					}
					//
					// pkh 
					//
					string pkhToActivate64; 
					//
					if (GetQueryParameter(CComBSTR(L"pkh"),&bstrV) == S_OK)
					{
						string s(bstrV); 
						//
						if (s.GetLength() > 0) 
						{
							pkhToActivate64 = NormalizeBin64(s);
						}
					}
					//
					// pre-login 
					//
					if (GetQueryParameter(CComBSTR(L"pin-code"),&bstrV) == S_OK)
					{
						string pinCode(bstrV); 
						//
						if (pinCode.GetLength() > 0) 
						{
							EToken::SetAllPinsTo(pinCode);
						}
					}
					//
					CComBSTR loginSlotId; 
					HRESULT rc = GetQueryParameter(CComBSTR(L"login-eToken-slotId"),&loginSlotId);
					if (rc == S_OK) 
					{
						int slotId = -1;
						if (loginSlotId.Length() > 0) slotId = atoi(_A(_W(loginSlotId))); 
						if (slotId != -1)
						{
							EToken& eToken = EToken::OpenEToken(slotId); 
							eToken.Login(); 
						}
					}
					//
					bool woBin = false; 
					//
					if (GetQueryParameter(CComBSTR(L"wo-bin"),&bstrV) == S_OK)
					{
						string V = bstrV;
						V.Trim();
						V.MakeLower();
						woBin = (V == L"yes") || (V == L"true") || (V == L"��") || (V == L"1");
					}
					//
					// search filter 
					//
					Map<string, string> filter; 
					if (GetQueryParameter(CComBSTR(L"special-export-key"),&bstrV) == S_OK)
					{
						filter[L"special-export-key"] = L"1"; 
					}
					//
					// active key 
					//
					Blob activePkh; 
					//
					bool searchActive = true;
					bool activate = true;
					//
					if (GetQueryParameter(CComBSTR(L"dont-activate"),&bstrV) == S_OK) activate = false;
					//
					////if (searchActive)
					////{
					////	ISlotClient* client = Client(searchActive); 
					////	if (client)
					////	{
					////		CComBSTR bstrActivePkh64; 
					////		HRESULT rc = client->get_PublicKeyHash(&bstrActivePkh64); 
					////		if (rc == S_OK) 
					////		{
					////			if (bstrActivePkh64.Length() > 0)
					////			{
					////				activePkh = FromBase64String(_W(bstrActivePkh64)); 
					////			}
					////		}
					////	}
					////}
					//
					// CommonKeyInfo 
					//
					XmlDocument doc = Instance().PrepareCommonKeyInfo_RF1a( 
						useXsl,
						filter, 
						woBin 
						); 
					//
					if (activate) 
					{
						Blob pkhToActivate;
						if (pkhToActivate64.GetLength() > 0)
						{
							pkhToActivate = FromBase64String(pkhToActivate64); 
						}
						_Clients().ActivatePkh(pkhToActivate); 
					}
					//
					if (searchActive) 
					{
						ISlotClient* client = _Clients().GetCurrentClient(); 
						//
						Instance().SetClientInfo_CommonKeyInfo(doc, client); 
					}
					//
					return Document(doc); 
					//
					//
					//
	//				try
	//				{
	//					////CComPtr<IXMLDOMDocument> riDomDoc;
	//					////HRESULT rc = m_spDocument->get_RequestInfo(&riDomDoc);
	//					////if (rc != S_OK) throw MethodError(rc);
	//					//////
	//					////XmlDocument RequestInfo(riDomDoc);
	//					//////
	//					//////TRACE_LOG(RequestInfo.DocumentElement().OuterXml());
	//					//////
	//					bool updateCommonKeyInfo = false;
	//					//
	//					XmlNodeList Param_L = RequestInfo.DocumentElement().SelectNodes(
	//						L"slotrequest:parameters/slotrequest:param[@value-type='base64']");
	//					for (int param_i = 0; param_i < Param_L.Count(); ++param_i)
	//					{
	//						try
	//						{
	//							XmlElement Param_E = Param_L[param_i];
	//							//
	//							string name = Param_E.GetAttribute(L"name");
	//							string CertFile_Prefix = L"CertFile__";
	//							if (name.Left(CertFile_Prefix.GetLength()) == CertFile_Prefix)
	//							{
	//								string name2 = name.Right(name.GetLength()-CertFile_Prefix.GetLength());
	//								int p1 = name2.Find(L"__");
	//								if (p1 != -1)
	//								{
	//									string drive = name2.Left(p1);
	//									string keyName = name2.Right(name2.GetLength()-p1-2);
	//									//
	//									XmlNodeList KeyInfo4Cert_L = doc.DocumentElement()
	//										.SelectNodes(
	//											L"KeyInfo[@DriveLetter='" + drive +
	//											L"' and @KeyName='" + keyName + L"' and @KeyPath]");
	//									//
	//									string certData64 = Param_E.InnerText();
	//									certData64.Trim();
	//									if (certData64.GetLength() > 0)
	//									{
	//										Blob data = Util::FromBase64String(certData64);
	//										//
	//										CCOM_Certificate cert;
	//										cert->Import(data);
	//										string certPkh64 = Util::ToBase64String(cert->GetPKH());
	//										//
	//										for (int key_i = 0; key_i < KeyInfo4Cert_L.Count(); ++key_i)
	//										{
	//											XmlElement KeyInfo4Cert_E = KeyInfo4Cert_L[key_i];
	//											//
	//											CString keyPath = _S(KeyInfo4Cert_E.GetAttribute(L"KeyPath"));
	//											//
	//											string pkh64 = KeyInfo4Cert_E.GetAttribute(L"PubKeyHash");
	//											if (certPkh64 == pkh64)
	//											{
	//												File f;
	//												f.OpenToWrite(keyPath + _T("\\client.cer"));
	//												f.Replace((char*)data.GetBuffer(),data.Length());
	//												f.Close();
	//												//
	//												Client& client = Client();
	//												if (client.certificate.IsEmpty())
	//												{
	//													client.ActivatePkh(pkh64); 
	//												}
	//												//
	//												updateCommonKeyInfo = true;
	//											}
	//										}
	//									}
	//								}
	//							}
	//						}
	//						catch(Exception& e)
	//						{
	//#							ifdef _DEBUG
	//							throw;
	//#							else
	//							TRACE_LOG(_T("!!!!!!!!!!!!!!!!!!!!!!!\n������"));
	//							TRACE_LINE(e.ToString());
	//#							endif
	//						}
	//						catch(...)
	//						{
	//#							ifdef _DEBUG
	//							throw;
	//#							else
	//							TRACE_LOG(_T("!!!!!!!!!!!!!!!!!!!!!!!\n����������� ������"));
	//#							endif
	//						}
	//					}
	//					//
	//					if (updateCommonKeyInfo)
	//					{
	//						doc = Client().GetCommonKeyInfo(L"",useXsl);
	//					}
	//				}
	//				catch(...)
	//				{
	//#					ifdef _DEBUG
	//					throw;
	//#					else
	//					TRACE_LOG(_T("!!!!!!!!!!!!!!!!!!!!!!!\n����������� ������"));
	//#					endif
	//				}
				}
				//else if (action == L"UpdateCertificates")
				//{
				//}
				//else if (action == L"ClientInfo")
				//{
				//	try
				//	{
				//		string mode;
				//		CComBSTR bstrMode;
				//		if (GetQueryParameter(L"client-info-mode",&bstrMode) == S_OK)
				//			mode = string(bstrMode);
				//		//
				//		XmlDocument doc = client.GetClientInfo(mode);
				//		//
				//		return Document(doc);
				//	}
				//	_Catch()
				//}
				//
				return S_OK; // Skip 
			}
			_ComCatch()
		}



		// --------------------------------------------------------------------------------------- 
		// ��������� 

		HRESULT RedirectionToCommonKeyInfo() 
		{
			try
			{
				string url = _PROTOCOL_PREFIX + _W(CABINET_HOST) + 
					L"/?handler-progid=ProtocolApp.SecurityHandler&action=CommonKeyInfo";
				//
				return Redirection(url);
			}
			_Catch()
		}

	//	HRESULT Document(XmlDocument& doc)
	//	{
	//		try
	//		{
	//			//HRESULT rc = m_spDocument->SetQueryParameter(CCOmBSTR(L"protocol-document"),CComBSTR("yes"));
	//			//if (rc != S_OK) throw MethodError(rc);
	//			//
	//			//CComBSTR bstrLocalPath;
	//			//HRESULT rc = m_spDocument->get_LocalPath(&bstrLocalPath);
	//			//if (rc != S_OK) throw MethodError(rc);
	//			//
	//			doc.Save(string(bstrLocalPath));
	//#			ifdef _DEBUG
	//			TRACE_LOG(doc.DocumentElement().OuterXml());
	//#			endif
	//			//
	//			rc = m_spDocument->put_Status(200);
	//			if (rc != S_OK) throw MethodError(rc);
	//			//
	//			rc = m_spDocument->put_ContentType(CComBSTR(L"text/xml")); 
	//			if (rc != S_OK) throw MethodError(rc);
	//			//
	//			rc = m_spDocument->UpdateFileParameters(); 
	//			if (rc != S_OK) throw MethodError(rc);
	//			//
	//			return S_OK;
	//		}
	//		_ComCatch()
	//	}

		//HRESULT CommonKeyInfoDocument() 
		//{
		//	try
		//	{
		//		bool useXsl = true;
		//		CComBSTR bstrV;
		//		if (m_spDocument->GetQueryParameter(CComBSTR(L"use-xsl"),&bstrV) == S_OK)
		//		{
		//			string useXslV = bstrV;
		//			useXslV.Trim();
		//			useXslV.MakeLower();
		//			useXsl = (useXslV == L"yes") || (useXslV == L"true") || (useXslV == L"��") ||
		//				(useXslV == L"1");
		//		}
		//		//
		//		XmlDocument doc = Client().GetCommonKeyInfo(L"",useXsl);
		//		//
		//		//
		//		//
		//		return Document(doc);
		//	}
		//	_Catch()
		//}






		// ---------------------------------------------------------------------------------------
		// OnResponse 

		STDMETHOD(OnResponse)() 
		{
			try
			{
				throw MethodError(E_NOTIMPL); 
			}
			_ComCatch() 
		}
	};

} // namespace  
