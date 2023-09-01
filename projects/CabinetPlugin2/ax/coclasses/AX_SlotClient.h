/*
 AX_SlotClient --- ������ ������� ������ ������� � ������. 

	ISlotSigner		��� �������� ��� 

 $Name:  $
 $Revision: 1.1.2.5 $
 $Date: 2009/05/26 09:06:39 $
 */

#pragma once

#include <map>

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include "../../low-level/SmartUtil.h"
#include "../../low-level/SmartXml.h"
#include "../../low-level/SmartState.h"
//
#include "../../_cpp/SlotCSP_CCOM.h"
//
#include "AX_SlotDataStream.h"
#include "AX_SlotXmlFilter.h"
//
#include "../interfaces/ISlotSigner.h"
#include "../interfaces/ISlotClient.h"



namespace  { 

		static string _xClientDataByPkh(const string& pkh64); 

		class Client_Lock
		{
		public:
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

		//private:
			Client_Lock()
			{
				EnterCriticalSection(&CriticalSection()); 
			}

			~Client_Lock()
			{
				LeaveCriticalSection(&CriticalSection()); 
			}
		};



		//class CabinetClient
		//{
		//private: 
		//	typedef Map<string,CabinetClient> tClientMap; 

		//	inline static tClientMap& Clients() 
		//	{
		//		static tClientMap sClients; 
		//		return sClients; 
		//	}

		//	// ��������� ������� ������ ������ 

		//	inline static void Refresh() 
		//	{
		//		try
		//		{
		//		}
		//		_Catch()
		//	}

		//	struct tState
		//	{
		//		tState()
		//		{
		//			CertListLoaded = false; 
		//		}

		//		bool CertListLoaded; 

		//		COleDateTime CertListTime; 

		//		// ��������� ������� 

		//		inline double CertListDelay()
		//		{
		//			try
		//			{
		//				if (! CertListLoaded) return -1; 
		//				// 
		//				COleDateTime t = COleDateTime::GetCurrentTime(); 
		//				COleDateTimeSpan dt = t - CertListTime; 
		//				return double(dt.GetSeconds()); 
		//			}
		//			_Catch() 
		//		}
		//	};

		//	inline static tState& State() 
		//	{
		//		static tState sState; 
		//		return sState; 
		//	}

		//	// TODO 
		//	//static const double CMaxCertListDelay = 5.0; 

		//	inline static double MaxCertListDelay() 
		//	{
		//		return CMaxCertListDelay; 
		//	}

		//	inline static void NormalRefresh()  
		//	{
		//		try
		//		{
		//			bool fCallRefresh = true; 
		//			//
		//			if (State().CertListLoaded) // mak@setbook.ru 
		//			{
		//				if (State().CertListDelay() < MaxCertListDelay()) 
		//				{
		//					fCallRefresh = false; 
		//				}
		//			}
		//			//
		//			if (fCallRefresh)
		//			{
		//				Refresh(); 
		//			}
		//		}
		//		_Catch()
		//	}

		//public:
		//	inline static CabinetClient* FindClientByPkh(const string& pkh64) // borrowed reference 
		//	{
		//		try
		//		{
		//			NormalRefresh(); 
		//			//
		//		}
		//		_Catch() 
		//	}


		//	// ----
		//	// ������ 

		//	bool m_Connected;

		//	Blob m_Pkh;

		//	XmlElement m_KeyInfo; 

		//	Certificate m_Certificate; 



		//	// ----
		//	// ������������ 

		//	inline void Clear() 
		//	{
		//		m_Connected = false; 
		//		m_dwROTID = 0; 
		//	}
		//}; 










#	define _Clients() (ClientMap::Clients()) 

	// =================================================
	// CSlotClient 

	class ATL_NO_VTABLE CSlotClient : 
		public CComObjectRootEx<CComSingleThreadModel>, 
		public CComCoClass<CSlotClient>, 
		public ISlotClient, 
		public ISlotSigner 
	//
	{
	public:
		template<class I>
		inline static I* Open(const string& pkh64) // new reference or NULL 
		{
			try
			{
				ISlotClient* pClient = __Open__(pkh64); 
				//
				if (pClient)
				{
					CComQIPtr<I> i(pClient); 
					return i.Detach();
				}
				else
				{
					return 0; 
				}
			}
			_Catch()
		}

		template<class I>
		inline static I* OpenNewClient() // new reference or NULL 
		{
			try
			{
				return Open<I>(L""); 
			}
			_Catch()
		}

		inline static ISlotClient* __Open__(const string& pkh64) // new reference 
		{
			try
			{
				//LOCK// 
				Client_Lock lock; 
				//
				TRACE_LINE("[OpenClient] In"); 
				//
				CComPtr<ISlotClient> pClient;   
				//
				//string x;
				//int l = x.GetLength(); 
				//
				string xClientData = _xClientDataByPkh(pkh64); 
				//
				// new CSlotClient object 
				{
					typedef CComObject<CSlotClient> _CoClass;
					_CoClass* pClass;
					HRESULT rc = _CoClass::CreateInstance(&pClass); 
					if (FAILED(rc)) throw MethodError(rc);
					//
					pClass->AddRef();
					//
					CComPtr<ISlotClient> i; 
					rc = pClass->QueryInterface(__uuidof(ISlotClient),(void**)&i); 
					if (FAILED(rc)) throw MethodError(rc);
					//
					pClient.Attach(i.Detach()); 
				}
				//
				if (xClientData != L"")
				//if (xClientData.GetLength() > 0) 
				{
					HRESULT rc1 = pClient->put_SignerInfoXData(CComBSTR(xClientData));   
					if (FAILED(rc1)) throw MethodError(rc1); 
				}
				//
				TRACE_LINE("[OpenClient] Out"); 
				//
				if (pClient)
				{
					return pClient.Detach(); 
				}
				else
				{
					return 0; 
				}
			}
			_Catch() 
		}

		inline static ISlotClient* __OpenCertificateCP__(const string& pkh64) // new reference 
		{
			try
			{
				//LOCK// 
				Client_Lock lock; 
				//
				TRACE_LINE("[OpenClient] In"); 
				//
				CComPtr<ISlotClient> pClient;   
				//
				//string x;
				//int l = x.GetLength(); 
				//
				string xClientData = _xClientDataByPkh(pkh64); 
				//
				// new CSlotClient object 
				{
					typedef CComObject<CSlotClient> _CoClass;
					_CoClass* pClass;
					HRESULT rc = _CoClass::CreateInstance(&pClass); 
					if (FAILED(rc)) throw MethodError(rc);
					//
					pClass->AddRef();
					//
					CComPtr<ISlotClient> i; 
					rc = pClass->QueryInterface(__uuidof(ISlotClient),(void**)&i); 
					if (FAILED(rc)) throw MethodError(rc);
					//
					pClient.Attach(i.Detach()); 
				}
				//
				if (xClientData != L"")
				//if (xClientData.GetLength() > 0) 
				{
					HRESULT rc1 = pClient->put_SignerInfoXData(CComBSTR(xClientData));   
					if (FAILED(rc1)) throw MethodError(rc1); 
				}
				//
				TRACE_LINE("[OpenClient] Out"); 
				//
				if (pClient)
				{
					return pClient.Detach(); 
				}
				else
				{
					return 0; 
				}
			}
			_Catch() 
		}

		//void SaveClient(ISlotClient* client) // new reference 
		//{
		//	try
		//	{
		//		s_ROT_Register(client); 
		//	}
		//	_Catch()
		//}

		template<class I>
		inline static I* FindClientByPkh(const string& pkh64) // new reference or NULL 
		{
			return 0; 
		}









	protected:
		inline static Protocol::AppCtx& Instance() 
		{
			return Protocol::AppCtx::Instance(); 
		}



	protected:
		// ----
		// ������ 

		bool m_Connected;

		Blob m_Pkh;

		XmlElement m_KeyInfo; 

		Certificate m_Certificate; 



		// ----
		// ������������ 

		inline void Clear() 
		{
			m_Connected = false; 
			m_dwROTID = 0; 
		}

		inline void Free() throw() 
		{
			Clear(); 
		}

	public:
		CSlotClient()
		{
			Free(); 
		}

		BEGIN_COM_MAP(CSlotClient)
			COM_INTERFACE_ENTRY_IID(__uuidof(ISlotClient),ISlotClient)
			COM_INTERFACE_ENTRY_IID(__uuidof(ISlotSigner),ISlotSigner)
		END_COM_MAP()

		DECLARE_PROTECT_FINAL_CONSTRUCT()

		HRESULT FinalConstruct()
		{
			return S_OK;
		}

		void FinalRelease() 
		{
			Free();
		}

		~CSlotClient()
		{
			Free(); 
		}



		// ---------------------------------------------------------------------------------------
		// ROT

		DWORD m_dwROTID; 

		void SetROTID(DWORD dwValue)
        {
			m_dwROTID = dwValue;
        }

		inline static void s_ROT_Register(ISlotClient* pSlotClient, const string& pkh64) 
		{
			try
			{
				CComPtr<IRunningObjectTable> pTable;
				if(GetRunningObjectTable(0, &pTable) == S_OK)
				{
					CComBSTR bstrItemName;
					CComPtr<IMoniker> pMoniker;
					char szBuffer[1024];
					//-
					const static wchar_t* szMonikerTemplateName = L" Client Object"; 
					//
					string name = Instance().GetOption(L"client-object-name"); 
					if (name.GetLength() == 0) name = szMonikerTemplateName; 
					//
					//CComBSTR bstrPkh64; 
					//HRESULT rc = pSlotClient->get_PublicKeyHash(&bstrPkh64); 
					//if (FAILED(rc)) throw MethodError(rc); 
					//string pkh64(bstrPkh64); 
					//
					name = name + L" " +  + pkh64; 
					//
					IUnknown* spUnkSite = static_cast<IUnknown*>(pSlotClient); 
					//
					sprintf_s(szBuffer, "%s | %d", _A(name), spUnkSite); 
					bstrItemName = szBuffer;
					if (CreateItemMoniker(NULL, bstrItemName, &pMoniker) == S_OK) 
					{
						DWORD dwRegister;
						if (pTable->Register(1, (IUnknown*)spUnkSite, pMoniker, &dwRegister) == S_OK) 
						{
							//SetROTID(dwRegister);
							ATLTRACE("IIEHelper: the moniker %s has been registered successfully\n", szBuffer); 
						}
						else
						{
							ATLTRACE("IIEHelper: failed to register moniker % s in the ROT\n", szBuffer);
						}
					}
					else
					{
						ATLTRACE("IIEHelper: failed to create moniker %s\n", szBuffer);
					}
				}
				else
				{
					ATLTRACE("IIEHelper: Could not retrieve the ROT pointer\n");
				}
			}
			_Catch() 
		}

		// ---------------------------------------------------------------------------------------
		// ISlotClient 

		STDMETHOD(Connect)(BSTR clientPkh64) 
		{
			try
			{
				if (m_Connected) throw MethodError(E_INVALIDARG); 
				//
				// ----
				// ����...
				//
				//// ROT_Register(); 
				//
				// ----
				// ��������� ������� 
				//
				PKCS11_Manager::Lock lock; 
				//
				string pwd = L""; 
				string pkh64 = _W(CComBSTR(clientPkh64)); 
				int p1 = pkh64.Find(L":"); 
				if (p1 != -1)
				{
					pwd = pkh64.Right(pkh64.GetLength() - 1 - p1); 
					pwd.Trim(); 
					pkh64 = pkh64.Left(p1); 
					pkh64.Trim(); 
				}
				//
				if (! FindCertificate(pkh64, pwd)) 
				{
					if (pkh64.GetLength() > 0)
					{
						return S_FALSE; 
						//throw MethodError(_W("���������� �� ������ (") + _W(pkh64) + _W(")")); 
					}
				}
				//
				m_Connected = true;  
				//
				return S_OK; 
			}
			_ComCatch() 
		}

		STDMETHOD(SetKeyPair)(IXMLDOMElement* pKeyInfo_E, IXMLDOMElement* pCertInfo_E) 
		{
			try
			{
				if (! pKeyInfo_E) throw MethodError(E_INVALIDARG); 
				if (! pCertInfo_E) throw MethodError(E_INVALIDARG); 
				if (m_Connected) throw MethodError(E_INVALIDARG); 
				//
				// ----
				// ��������� ������� 
				//
				//PKCS11_Manager::Lock lock; 
				//
				XmlElement KeyInfo_E(pKeyInfo_E); 
				Blob pkh = FromBase64String(KeyInfo_E.GetAttribute(L"PubKeyHash")); 
				//
				//
				m_Connected = true; 
				//
				return S_OK; 
			}
			_ComCatch() 
		}

		STDMETHOD(get_CertificateData)(BYTE* out_data,int* out_len) 
		{
			try
			{
				if (! out_len) throw MethodError(E_POINTER); 
				//
				HRESULT notFound = HRESULT_FROM_WIN32(ERROR_NOT_FOUND); 
				HRESULT insufficientBuffer = HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER); 
				//
				if (m_Certificate.IsEmpty()) throw MethodError(notFound); 
				Blob certData = m_Certificate->GetCertData(); 
				if (certData.Length() <= 500) 
				{
					throw MethodError(L"������ ������ ����������� (2)"); 
				}
				if (certData.Length() == 0) throw MethodError(notFound); 
				//
				*out_len = certData.Length(); 
				//
				if (! out_data)
				{
					return insufficientBuffer; 
				}
				if (certData.Length() > (*out_len))
				{
					return insufficientBuffer; 
				}
				//
				CopyMemory(out_data,certData.GetBuffer(),certData.Length()); 
				//
				return S_OK; 
			}
			_ComCatch()
		}

		STDMETHOD(get_PublicKeyHash)(BSTR* out_pkh64) 
		{
			try
			{
				if (! out_pkh64) throw MethodError(E_POINTER); 
				//
				if (m_Certificate.IsEmpty()) 
				{
					throw MethodError(L"��� ����������� (1)"); 
					//
					return S_FALSE; 
					//
					//HRESULT notFound = HRESULT_FROM_WIN32(ERROR_NOT_FOUND); 
					//throw MethodError(notFound); 
				}
				Blob pkh = m_Certificate->GetPKH(); 
				if (pkh.Length() == 0) 
				{
					return S_FALSE; 
					//
					//HRESULT notFound = HRESULT_FROM_WIN32(ERROR_NOT_FOUND); 
					//throw MethodError(notFound); 
				}
				//
				string pkh64 = __ToBase64(pkh); 
				//
				CComBSTR bstrPkh64(pkh64);
				*out_pkh64 = bstrPkh64.Detach(); 
				return S_OK; 
			}
			_ComCatch() 
		}

		string m_xClientData;

		STDMETHOD(put_SignerInfoXData)(BSTR bstrSignerInfoXData) 
		{
			try
			{
				m_xClientData = _S(bstrSignerInfoXData);
				return S_OK; 
			}
			_ComCatch() 
		}

		STDMETHOD(get_SignerInfoXData)(BSTR* out_SignerInfoXData) 
		{
			try
			{
				if (! out_SignerInfoXData) throw MethodError(E_POINTER); 
				//

				//
				string signerInfoXData = L""; 
				//
				CComBSTR bstrSignerInfoXData(signerInfoXData);
				*out_SignerInfoXData = bstrSignerInfoXData.Detach(); 
				return S_OK; 
			}
			_ComCatch() 
		}

		STDMETHOD(get_Signer)(ISlotSigner** out_signer)
		{
			try
			{
				if (! out_signer) throw MethodError(E_POINTER); 
				//
				HRESULT notFound = HRESULT_FROM_WIN32(ERROR_NOT_FOUND); 
				//
				if (m_Certificate.IsEmpty()) throw MethodError(notFound); 
				//
				*out_signer = (ISlotSigner*)(m_Certificate.GetPointee());  
				return S_OK; 
			}
			_ComCatch() 
		}



		inline bool FindCertificate(const string& client_pkh64, const string& pwd)
		{
			try
			{
				Blob client_pkh = FromBase64String(client_pkh64); 
				//
				return FindAndActivateCertificate(client_pkh, pwd); 
			}
			_Catch()
		}

		inline bool FindAndActivateCertificate(Blob client_pkh, const string& pwd_1) // , bool activate 
		{
			try
			{
				string pwd = pwd_1;
				if (pwd.GetLength() == 0) pwd = m_xClientData; 
				//
				// if (client_pkh.Length() == 0) throw MethodError(E_INVALIDARG); 
				//
				Map<string,string> filter; 
				// 
				if (client_pkh.Length() > 0 && pwd.GetLength() > 0) 
				{
					filter[L"pwd_" + __ToBase64(client_pkh)] = pwd; 
				}
				//
				XmlDocument CommonKeyInfo = Instance().PrepareCommonKeyInfo_RF1a( 
					// client_pkh, 
					// Blob(), // don't mark active 
					false,
					filter, 
					false 
					);
				//
				XmlNodeList KeyInfo_L = CommonKeyInfo.DocumentElement().SelectNodes( 
					L"KeyInfo[CertificateInfo]");
				//
				string client_pkh64 = __ToBase64(client_pkh); 
				//
				bool keyFound = false;
				for (int k = 0; k < KeyInfo_L.Count() && (! keyFound); ++k)
				{
					try
					{
						XmlElement KeyInfo_E = (XmlElement)KeyInfo_L[k];
						//
						string pkh64 = __ToBase64(FromBase64String(
							KeyInfo_E.GetAttribute(L"PubKeyHash") 
							)); 
						//
						string cn; 
						XmlNodeList cn_L = KeyInfo_E.SelectNodes(
							L"RequestInfo/CertificateInfo/CertItem/Attribute[@name='oid.2.5.4.3']"); 
						if (cn_L.Count() > 0)
						{
							XmlElement cn_E = cn_L[0]; 
							//
							cn = cn_E.InnerText();
							cn.Trim(); 
						}
						//
						string org; 
						XmlNodeList org_L = KeyInfo_E.SelectNodes(
							L"RequestInfo/CertificateInfo/CertItem/Attribute[@name='oid.2.5.4.10']"); 
						if (org_L.Count() > 0)
						{
							XmlElement org_E = org_L[0]; 
							//
							org = org_E.InnerText();
							org.Trim(); 
						}
						//
						string keyMedia = KeyInfo_E.GetAttribute(L"KeyMediaType"); 
						//
						if (keyMedia == L"eToken")
						{
							string eTokenID = KeyInfo_E.GetAttribute(L"eTokenID"); 
							int key_i = _wtoi(KeyInfo_E.GetAttribute(L"KeyNum")); 
							//
							EToken& eToken = EToken::OpenEToken(eTokenID); 
							Blob certData = eToken.ReadCertificate(key_i); 
							//
							if (certData.Length() > 0) 
							{
								CCOM_Certificate cert;
								cert->Import(certData);
								//
								m_Pkh = cert->GetPKH(); 
								string certPkh = __ToBase64(m_Pkh);
								//
								if (client_pkh64 == certPkh || client_pkh64.GetLength() == 0) 
								{
									CCOM_Key key;
									key->LoadETokenKey(eTokenID, key_i);  
									cert->SetKey(key);
									//
									//// ROT_Register(); 
									//
									m_Certificate = cert;
									keyFound = true;
								}
							}
							//
							//// int key_mode = _wtoi(KeyInfo_E.GetAttribute(L"KeyMode")); 
							//int key_mode = 1; 
							////
							//const int buflen = 16 * 1024; 
							////
							//string certPath = PKCS11_Manager_()
							//	.EToken_GetCertPath(eTokenSlotId, key_i); 
							//CStringA certPathA = PKCS11_Manager::ETokenPath(eTokenSlotId, certPath); 
							////
							//Blob certData;
							//certData.Expand(buflen);
							//int r1 = CADB_read_file(certPathA.GetBuffer(), 
							//	(char*)certData.GetBuffer(), buflen); 
							//if (r1 <= -1)
							//{
							//	int e = ERR_get_last_error();
							//	string errMsg = FormatStr(L"������ CCOM: %d", (int)e );
							//	throw MethodError(errMsg); 
							//}
							//certData.SetSize(r1); 
							////
							//// CCOM:
							////
							//CCOM_Certificate cert;
							//cert->Import(certData);
							////
							//CCOM_Key key;
							//key->LoadETokenKey(eTokenSlotId, key_i, key_mode);
							//cert->SetKey(key);
							////
							//m_Pkh = cert->GetPKH(); 
							////
							//m_Certificate = cert;
							//keyFound = true;
							return true; // ������! 
						}
						else // drive 
						{
							CString keyPath = _S(KeyInfo_E.GetAttribute(L"KeyPath"));
							CString driveLetter = _S(KeyInfo_E.GetAttribute(L"DriveLetter"));
							string pkh64 = KeyInfo_E.GetAttribute(L"PubKeyHash");
							//
							// ��������� ���������� � �����
							//
							if (driveLetter == _S("_CryptoPro2012_512"))
							{
								SharedArray<string> data = ::PKITools::SearchKey(pkh64);
								string containerName = data[5];
								Blob certData = FromBase64String(data[7]);
								string datetime_s = data[8];
								string cn = L"";
								string org = L"";
								//
								// CCOM:
								//
								CCOM_Certificate cert;
								cert->Import(certData);
								//
								CCOM_Key key;
								key->SetPath(containerName);
								key->SetCommonName(cn);
								key->SetOrgName(org);
								//key->SetXmlInfo(d.DocumentElement());
								cert->SetKey(key);
								//
								m_Pkh = cert->GetPKH();
								//
								//// ROT_Register(); 
								//
								m_Certificate = cert;
								keyFound = true;
								return true; // ������! 
							}
							else
							{
								SharedArray<CString> pkXmlPaths = Machine::ListFiles(keyPath, _T("*-k.xml"));
								if ((pkXmlPaths.Length() > 0) && (
									(pkh64 == client_pkh64) || (client_pkh.Length() == 0)
									))
								{
									CString pkXmlPath = pkXmlPaths[0];
									//
									Blob certData = FromBase64String(
										((XmlElement)KeyInfo_E.SelectSingleNode(L"CertificateInfo")).InnerText()
										);
									//
									// CCOM:
									//
									CCOM_Certificate cert;
									cert->Import(certData);
									//
									CString keyInfoPath = pkXmlPath;
									CString keyContainerPath = keyPath + _T("\\Container");
									//
									CCOM_Key key;
									XmlDocument d;
									d.Load((string)keyInfoPath);
									key->SetPath(keyContainerPath);
									key->SetCommonName(cn);
									key->SetOrgName(org);
									key->SetXmlInfo(d.DocumentElement());
									cert->SetKey(key);
									//
									m_Pkh = cert->GetPKH();
									//
									//// ROT_Register(); 
									//
									m_Certificate = cert;
									keyFound = true;
									return true; // ������! 
								}
							}
						}
					}
					catch(::::Exception e)
					{
						string msg = L"������ ��� ������ �����������: " + e.ToString() + L"\n"; 
						OutputDebugStringW(msg); 
						throw; 
					}
					catch(...)
					{
						throw MethodError(L"������ (1)"); 
					}
				}
				return false;
			}
			_Catch()
		}



		// ----
		// ��������� ISlotSigner

		STDMETHOD(Start)() 
		{
			try
			{
				if (m_Certificate.IsEmpty()) throw MethodError(E_NOINTERFACE); 
				//
				return m_Certificate->Start(); 
			}
			_ComCatch()
		}

		STDMETHOD(AddBlobk)(
			BYTE* data,
			int size) 
		{
			try
			{
				if (m_Certificate.IsEmpty()) throw MethodError(E_NOINTERFACE); 
				//
				return m_Certificate->AddBlobk(data,size); 
			}
			_ComCatch()
		}

		STDMETHOD(GetSignature)(
			BYTE** ppSignature,
			int* pSignatureSize) 
		{
			try
			{
				if (m_Certificate.IsEmpty()) throw MethodError(E_NOINTERFACE); 
				//
				return m_Certificate->GetSignature(ppSignature,pSignatureSize); 
			}
			_ComCatch()
		}

		STDMETHOD(GetSignature64)(
			BSTR* out_signature) 
		{
			try
			{
				if (m_Certificate.IsEmpty()) throw MethodError(E_NOINTERFACE); 
				//
				return m_Certificate->GetSignature64(out_signature); 
			}
			_ComCatch()
		}

		STDMETHOD(GetSignature64_FCSM)(
			BSTR in_signature, 
			BSTR* out_signature) 
		{
			try
			{
				if (m_Certificate.IsEmpty()) throw MethodError(E_NOINTERFACE); 
				//
				return m_Certificate->GetSignature64_FCSM(in_signature, out_signature); 
			}
			_ComCatch()
		}



		// =======================================================================================
		// ����� ������� (Instance) 

		STDMETHOD(GetCommonKeyInfo)(BSTR pkh64,int useXsl,IXMLDOMDocument** out_document); 

	};
	// CSlotClient 






	






	// ================================================= 
	// ������� �������� 

	struct ClientMap 
	{
		inline static ClientMap& Clients() 
		{
			static ClientMap s_Clients;
			return s_Clients;  
		}

		ISlotClient* GetCurrentClient(bool require=false) // borrowed reference 
		{
			try
			{
				ISlotClient* client = Clients().GetClient(Blob(), require); // borrowed reference, activate or not  
				return client; 
			}
			_Catch() 
		}

		inline static std::map<std::string,std::string>& Passwords() 
		{		
			static std::map<std::string,std::string> P; 
			return P; 
		}

		// ----
		// ������ 

		Map<string,ISlotClient*> s_Map; 

		Blob m_ActivePkh;

		// string m_ActivePkh64;

		///!!!inline ISlotClient* _obs_GetClient(Blob pkh, 
		inline ISlotClient* GetClient(Blob pkh, 
			bool activate=true) // borrowed reference 
		{
			try
			{
				//Blob m_ActivePkh; 
				//string aPkh = DynState::GetParameter("current-client-pkh");   
				//if (aPkh.GetLength() == 0) m_ActivePkh = FromBase64String(aPkh); 
				//
				if (pkh.Length() == 0) // ������� ������, ���� ����� ������ (������ �� ���������) 
				{
					throw MethodError(L"������� ���� �� ��������� �� ��������������");   
					// 
					if (m_ActivePkh.Length() > 0) // ���� �������� ���������� 
					{
						return GetClient(m_ActivePkh, false); // ��� ����������� 
					}
					else
					{
						if (! activate) return 0; 
						//
						CComPtr<ISlotClient> client;
						client.Attach( CSlotClient::OpenNewClient<ISlotClient>() ); 
						if (! client) throw MethodError(E_UNEXPECTED); 
						//
						string S = L""; //// L": " + pwd; 
						// 
						HRESULT rc = client->Connect(CComBSTR(S)); // default client 
						if (FAILED(rc)) throw MethodError(rc); 
						//
						CComBSTR bstrPkh64;
						rc = client->get_PublicKeyHash(&bstrPkh64); 
						if (rc == S_FALSE)
						{
							return 0; // no client 
						}
						if (FAILED(rc)) throw MethodError(rc); 
						//
						string defaultClient_pkh64(bstrPkh64);
						Blob defaultClient_pkh = FromBase64String(defaultClient_pkh64); 
						//
						s_Map[defaultClient_pkh64] = client.Detach(); 
						//
						if (defaultClient_pkh.Length() == 0)
						{
							throw MethodError(E_UNEXPECTED); 
						}
						//
						return GetClient(defaultClient_pkh, activate); //// ((((force activate?)))) 
					}
				}
				else
				{
					string pkh64 = __ToBase64(pkh); 
					//
					//string msg1 = L"pkh: " + pkh64 + L"\n"; 
					////OutputDebugStringW(msg1);
					//
					if (! s_Map.ContainsKey(pkh64)) 
					{
						CComPtr<ISlotClient> client;
						ISlotClient* i = CSlotClient::__Open__(pkh64); 
						if (! i)
						{
							throw MethodError(L"������ ������������� CSlotClient, pkh=" + pkh64); 
						}
						//
						std::string _pkh64((const char*)_A(pkh64)); 
						//
						if (Passwords().find(_pkh64) == Passwords().end())
						{
							throw MethodError(L"�� ������ ������ �� ����"); 
						}
						pkh64 += L":" + _W(_A((Passwords()[_pkh64]).c_str())); 
						HRESULT rc = i->Connect(CComBSTR(pkh64)); 
						if (rc == S_FALSE)
						{
							throw MethodError(L"��� ����������� (2)"); 
						}
						if (FAILED(rc)) throw MethodError(rc); 
						//
						client.Attach( i ); 
						if (! client) throw MethodError(E_UNEXPECTED); 
						//
						//CSlotClient::s_ROT_Register(client, pkh64); 
						//
						s_Map[pkh64] = client.Detach(); 
					}
					//
					if (activate)
					{
						m_ActivePkh = pkh;
						// m_ActivePkh64 = pkh64;
					}
					//
					return s_Map[pkh64]; 
				}
			}
			_Catch()
		}

		inline ISlotClient* ActivatePkh(Blob pkh) // borrowed reference 
		{
			try
			{
				return GetClient(pkh, true); // activate 
			}
			_Catch()
		}

		///!!!inline ISlotClient* _obs_GetClient(Blob pkh, 
		/*
		inline ISlotClient* GetClient_CryptoPro(Blob pkh) // borrowed reference 
		{
			try
			{
				string pkh64 = __ToBase64(pkh);
				ISlotClient* i = CSlotClient::__Open__(pkh64); 
				HRESULT rc = i->Connect(CComBSTR(pkh64));
				if (rc == S_FALSE)
				{
					throw MethodError(L"��� ����������� (2)");
				}
				if (FAILED(rc)) throw MethodError(rc);
				s_Map[pkh64] = client.Detach();
				//
				return s_Map[pkh64];
			}
			_Catch()
		}
		*/

		inline ISlotClient* GetClient(XmlElement KeyInfo_E, XmlElement CertInfo_E) // borrowed reference 
		{
			try
			{
				string pkh64 = __ToBase64(FromBase64String(KeyInfo_E.GetAttribute(L"PubKeyHash"))); 
				//
				if (! s_Map.ContainsKey(pkh64)) 
				{
					CComPtr<ISlotClient> client;
					client.Attach(
						CSlotClient::Open<ISlotClient>(pkh64)
						);
					//
					HRESULT rc = client->SetKeyPair(
						KeyInfo_E.GetXmlObjectInterface(), CertInfo_E.GetXmlObjectInterface()); 
					if (FAILED(rc)) throw MethodError(rc); 
				}
				//
				return s_Map[pkh64]; 
			}
			_Catch()
		}

		static string& SimpleKeyInfoTemplate()
		{
			static string t;
			//
			if (t.GetLength() == 0)
			{
				t = L"<?xml version=\"1.0\" ?>\n"
					L"<KeyInfo>\n"
					L"</KeyInfo>"
					;
			}
			//
			return t;
		}

		inline Blob GetActivePkh_1()
		{
			try
			{
				Blob activePkh; 
				//
				ISlotClient* client = GetCurrentClient(); 
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
				return activePkh; 
			}
			_Catch() 
		}


		inline Blob GetActivePkh() 
		{
			try
			{
				Blob activePkh; 
				string aPkh = DynState::GetParameter(L"current-client-pkh");   
				//
				if (aPkh.GetLength() > 0)
				{
					activePkh = FromBase64String(aPkh); 
				}
				//
				return activePkh; 
			}
			_Catch() 
		}

		XmlDocument GetActivePkhInfo()
		{
			try
			{
				XmlDocument doc;
				doc.LoadXml(SimpleKeyInfoTemplate());
				//
				string aPkh = DynState::GetParameter(L"current-client-pkh");   
				//
				if (aPkh.GetLength() > 0)
				{
					Blob activePkh = FromBase64String(aPkh); 
					//
					XmlElement root = doc.DocumentElement();
					root.SetAttribute(L"PubKeyHash",
						::::__ToBase64(activePkh)
						);
				}
				//
				return doc;
			}
			_Catch();
		}

		XmlDocument GetClientPkhInfoDocument(const string& clientPkh64) 
		{
			try
			{
				if (clientPkh64.GetLength() == 0) throw MethodError(E_INVALIDARG); 
				//
				////ISlotClient client* = GetClient(clientPkh64); // borrowed, don't activate 
				////if (! client) throw MethodError(L"������ �� ������"); 
				//
				XmlDocument doc;
				doc.LoadXml(SimpleKeyInfoTemplate());
				//
				Blob clientPkh = FromBase64String(clientPkh64); 
				//
				string aPkh = DynState::GetParameter(L"current-client-pkh");   
				//
				if (aPkh.GetLength() > 0)
				{
					// Blob activePkh = FromBase64String(aPkh); 
					//
					XmlElement root = doc.DocumentElement();
					root.SetAttribute(L"PubKeyHash",
						::::__ToBase64(clientPkh)
						);
				}
				//
				return doc;
			}
			_Catch() 
		}
	}; 

	static string _xClientDataByPkh(const string& pkh64) 
	{
		try
		{
			string xClientPkh;
			string xClientData;
			//
			{
				Blob aPkh = _Clients().GetActivePkh();
				if (aPkh.Length() > 0)
				{
					ISlotClient* client = _Clients().GetClient(aPkh, false); 
					//
					CComBSTR bstrSignerInfoXData;
					HRESULT rc = client->get_SignerInfoXData(&bstrSignerInfoXData);
					if (FAILED(rc)) throw MethodError(rc); 
					xClientData = _S(bstrSignerInfoXData); 
					xClientPkh = aPkh;
					//
					return xClientData;
				}
			}
			//
			IRunningObjectTable* pTable = 0; 
			//
			if (!FAILED(GetRunningObjectTable(0, &pTable)))
			{
				IEnumMoniker* pEnum;
				if(!FAILED(pTable->EnumRunning(&pEnum)))
				{
					IUnknown* pUnknown = NULL;
					IMoniker* pCurMoniker = NULL;
					//LPMALLOC pMalloc;
					while (pEnum->Next(1, &pCurMoniker, NULL) == S_OK) 
					{
						if(!FAILED(pTable->GetObject(pCurMoniker, &pUnknown)))
						{
							ISlotClient* pSite = NULL;
							if(!FAILED(pUnknown->QueryInterface(
								__uuidof(ISlotClient), 
								(void**)&pSite
								))) 
							{
								CComBSTR bstrPkh64Cur; 
								HRESULT rc = pSite->get_PublicKeyHash(&bstrPkh64Cur); 
								if (FAILED(rc)) throw MethodError(rc); 
								string pkh64Cur(bstrPkh64Cur); 
								//
								bool use = (pkh64 == pkh64Cur) && (rc == S_OK); 
								//
								if (use)
								{
									////pClient.Attach(pSite);   
									//
									xClientPkh = pkh64Cur; 
									//
									CComBSTR bstrSignerInfoXData;
									HRESULT rc = pSite->get_SignerInfoXData(&bstrSignerInfoXData); 
									if (FAILED(rc)) throw MethodError(rc); 
									xClientData = _S(bstrSignerInfoXData); 
								}
								//// pSite->Release(); 
							}
							pUnknown->Release();
						}
						pCurMoniker->Release();
					}
					pEnum->Release();
				}
				pTable->Release();
			}
			//
			return xClientData;
		}
		_Catch() 
	}

} // namespace  







inline STDMETHODIMP ::CSlotClient::GetCommonKeyInfo( 
	BSTR pkh64, 
	int useXsl,IXMLDOMDocument** out_document 
	) 
	// obsolet: 
	// BSTR pkh64, 
{
	try
	{
		CComBSTR bstrPkh64(pkh64); 
		string pkh64Str(bstrPkh64);
		Blob pkh = FromBase64String(pkh64Str); 
		//
		XmlDocument d = Instance().PrepareCommonKeyInfo_RF1a();
		if (d.IsEmpty())
		{
			throw MethodError(L"�� ������� �������� CommonKeyInfo"); 
		}
		//
		////XmlDocument d = Instance().PrepareCommonKeyInfo( 
		////	pkh,
		////	_Clients().m_ActivePkh,
		////	(bool)(useXsl != 0), 
		////	Map<string,string>(), 
		////	false 
		////	); 
		//
		CComQIPtr<IXMLDOMDocument> doc(d.GetXmlObjectInterface());
		if (! doc) throw MethodError(E_NOINTERFACE); 
		//
		////TRACE_LOG1(_T("doc: 0x%x"), (int)(IXMLDOMDocument2*)doc ); 
		//
		if (out_document) *out_document = doc.Detach(); 
		return S_OK; 
	}
	_ComCatch() 
}



