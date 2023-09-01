
#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include <low-level/SmartUri.h>
//
#include <inet-proto/AppInstance.h>
#include <inet-proto/InetProtoImpl.h>
#include <inet-proto/ProtocolRequest.h>



namespace  {

	// ===========================================================================================
	// ��Protocol

	class ATL_NO_VTABLE Protocol : 
		public CComObjectRootEx<CComSingleThreadModel>,
		public CComCoClass<Protocol, &CLSID_Protocol>, 
		public IProtocol, 
		public IInternetProtocol,
		public IInternetProtocolInfo, 
		//public IInternetProtocolSink,
		public InternetProtocolImpl<Protocol>
	{
	public:
		typedef InternetProtocolImpl<Protocol> Impl; 

		// ----
		// �������� ��� InternetProtocolImpl

		CString InternetProtocolName() // final virtual 
		{
			return _PROTOCOL_PROJECT_NAME; 
		}



		// ----
		// ������������ 

		inline void Free()
		{
			///Request.RemoveTempFiles(); // TODO: temporary files ? 
			//
			Impl::Free();
		}

		Protocol()
		{
			Clear();
			//
	#		if (_TRACE_CREATION_EVENTS == 1)
			{
				///TRACE_LOG(_S("�������� �������� ") + _S(InternetProtocolName()) + _T(" ������")); 
			}
	#		endif
		}

		virtual ~Protocol()
		{
		}


		BEGIN_COM_MAP(Protocol)
			COM_INTERFACE_ENTRY_IID(IID_IInternetProtocol, IInternetProtocol)
			COM_INTERFACE_ENTRY_IID(IID_IInternetProtocolRoot, IInternetProtocol)
			COM_INTERFACE_ENTRY_IID(IID_IInternetProtocolInfo, IInternetProtocolInfo)
			//COM_INTERFACE_ENTRY_IID(IID_IInternetProtocolSink, IInternetProtocolSink)
		END_COM_MAP()


		DECLARE_PROTECT_FINAL_CONSTRUCT()

		HRESULT FinalConstruct()
		{
			try
			{
				SysInfo = Instance().Application().GetInfo(); 
				return S_OK;
			}
			_ComCatch() 
		}
		
		void FinalRelease() 
		{
			Free();
		}

		DECLARE_REGISTRY_RESOURCEID(IDR_PROTOCOL)



		// ----
		// �������������� �������� [] ������� �������� 

		Protocol::RequestHandler Request; 




		// ----
		// ��������� ���������� ������� 

	protected:
		inline void PrepareResult_InStart() 
		{
			try
			{
				// SetOutStream(Request.OutStream); // ���������� �������� ����� � ����� ������ ������ ������ 
				//
				SetOutUrl(Request.OutUrl,IncomingURL);
				SetOutStatus(Request.Status); 
				//
				CString cachePath = SetOutStreamToCache(OutUrl); 
				if (cachePath.GetLength() == 0)
				{
					throw MethodError(L"cachePath == <empty>");
				}
				//
				SetOutCachePath(cachePath); 
				if (cachePath.GetLength() == 0)
				{
					throw MethodError(L"this.CachePath == <empty>");
				}
				//
				SetOutContentType(Request.OutContentType); 
				//
				ReturnData(); 
			}
			_Catch()
		}

		inline void PrepareResult_InRead() 
		{
			try
			{
				throw MethodError(E_NOTIMPL); 
			}
			_Catch()
		}

	public:
		// ----
		// IInternetProtocol interface

	public:
		// ----
		// IInternetProtocol interface

		STDMETHOD(Start)(
				LPCWSTR szUrl,
				IInternetProtocolSink *pIProtSink,
				IInternetBindInfo *pIBindInfo,
				DWORD grfSTI,
				HANDLE_PTR dwReserved)
		{
			try
			{
				Protocol::RequestHandler::Lock lock; 
				//
#				ifdef _DEBUG
				{
					//throw MethodError(L"TEST_REPORT"); 
				}
#				endif
				//
#				ifdef _DEBUGGG
				{
					EToken::ReadCRL_1();
					//
					int x1 = -2146697191; 
					HRESULT rc1 = x1;
					TRACE_LOG1(_T("RC = 0x%x"), (int)rc1 ); 
					//
					HRESULT rc = -2146697210;
					TRACE_LOG1(_T("RC = 0x%x"), (int)rc );
					//
					//TRACE_LOG(_S("\n!\n") + _S(szUrl)); 
					//
					//CCOM_KeyObject k;
					////
					//string pwd = L"TeStPwd_1"; 
					//string testStr = L"����� ������� ������ �� ����������"; 
					//Blob data;
					//data.Allocate(testStr.GetLength() * sizeof(wchar_t)); 
					//CopyMemory(data.GetBuffer(), testStr.GetString(), data.Length()); 
					//Blob enc1 = k.EncryptWithPass(data, pwd); 
					//Blob data2 = k.DecryptWithPass(enc1, pwd + L";", true);
					//Blob s2;
					//s2.Allocate(data2.Length() + sizeof(wchar_t));
					//CopyMemory(s2.GetBuffer(), data2.GetBuffer(), data2.Length());
					//((wchar_t*)s2.GetBuffer())[data2.Length() / sizeof(wchar_t)] = 0;
					//string testStr2 = (wchar_t*)s2.GetBuffer();
				}
				//
				//HRESULT rc1 = -2147012851;
				//DWORD err1 = 0xffff & rc1;
				//
				//HRESULT rc2 = 0xE0000001;
				//
#				endif
				//
				// ----
				// ���� 
				//
				//HRESULT rc1 = 0x800700005;
				//string rc1Str = MethodError(rc1).ToString(); 
				//TRACE_LOG(rc1Str);
				//
#				ifdef _DEBUG
				{
					string line = _W(L"URL: ") + _W(szUrl); 
					//OutputDebugStringW(line + L"\n"); 
				}
#				endif
				//
				Impl::Init(szUrl,pIProtSink,pIBindInfo,grfSTI,dwReserved);    
				//
				// ----
				// ���������� � ������� 
				//				
				Request.Open(IncomingURL,PostStream,IncomingHeaders);  // 8-926-751-23-06 
				if (Request.m_UseCachedStream)
				{
					PrepareResult_InStart(); 
					return S_OK;
				}
				Request.Run(); 
				//
				// ----
				// ��������� 
				//
				PrepareResult_InStart(); 
				//
				return S_OK;
			}
			catch(::::Exception e)
			{
				//TRACE_LOG(_T("::::Exception"));  
				//e.AddIfNewSource(TRACE_POINT_W); 
				return SetError(e); 
			}
			catch(...)
			{
				//TRACE_LOG(_T("Exception (Unknown)"));
				return SetError(MethodError(E_UNEXPECTED)); 
			}
		}

		STDMETHOD(Continue)(PROTOCOLDATA *pStateInfo)
		{
			try
			{
				return Impl::Continue(pStateInfo);
			}
			_ComCatch()
		}
		
		STDMETHOD(Abort)(HRESULT hrReason,DWORD dwOptions)
		{
			try
			{
				return Impl::Abort(hrReason,dwOptions); 
			}
			_ComCatch()
		}

		STDMETHOD(Terminate)(DWORD dwOptions)
		{
			try
			{
				return Impl::Terminate(dwOptions);
			}
			_ComCatch()
		}

		STDMETHOD(Suspend)()
		{
			try
			{
				return Impl::Suspend();
			}
			_ComCatch()
		}
		
		STDMETHOD(Resume)()
		{
			try
			{
				return Impl::Resume();
			}
			_ComCatch()
		}

		STDMETHOD(Read)(void *pv,ULONG cb,ULONG *pcbRead) 
		{
			try
			{
				try
				{
					return Impl::Read(pv,cb,pcbRead);
				}
				catch(::::Exception e)
				{
					TRACE_LOG(_T("Read error! (2)"));
					//TRACE_LOG(_T("������ ������:\n") + _S(e.ToString())); 
					throw; 
				}
				catch(...)
				{
					TRACE_LOG(_T("Unexpected read error!")); 
				}
			}
			_ComCatch()
		}

		STDMETHOD(Seek)(
				LARGE_INTEGER dlibMove,
				DWORD dwOrigin,
				ULARGE_INTEGER *plibNewPosition)
		{
			try
			{
				return Impl::Seek(dlibMove,dwOrigin,plibNewPosition);
			}
			_ComCatch()
		}

		STDMETHOD(LockRequest)(DWORD dwOptions) 
		{
			return Impl::LockRequest(dwOptions);
		}

		STDMETHOD(UnlockRequest)() 
		{
			return Impl::UnlockRequest();
		}






		// =======================================================================================
		// IInternetProtocolInfo

		virtual HRESULT STDMETHODCALLTYPE ParseUrl( 
			LPCWSTR pwzUrl,
			PARSEACTION ParseAction,
			DWORD dwParseFlags,
			LPWSTR pwzResult,
			DWORD cchResult,
			DWORD *pcchResult,
			DWORD dwReserved)
		{
			try
			{
				// TRACE_LOG(_S("!\n!\n!\n") + _S(_W(pwzUrl)));
				//
				switch( ParseAction )
				{
				case PARSE_SECURITY_URL: 
					StringCchCopyW(pwzResult, cchResult, L"://cabinet.example.com");
					break;
				case PARSE_SECURITY_DOMAIN:
					//StringCchCopyW(pwzResult, cchResult, L"file:///c|"); // L"file:///c|" 
					StringCchCopyW(pwzResult, cchResult, L"://cabinet.example.com"); // L"file:///c|" 
					break;
				case PARSE_CANONICALIZE:
					return INET_E_DEFAULT_ACTION;
				default:
					return INET_E_DEFAULT_ACTION;
				}
				StringCchLengthW(pwzResult, cchResult, (size_t*)pcchResult);
				*pcchResult += 2;
				return S_OK;
			}
			_ComCatch() 
		}

		virtual HRESULT STDMETHODCALLTYPE CombineUrl( 
			LPCWSTR pwzBaseUrl,
			LPCWSTR pwzRelativeUrl,
			DWORD dwCombineFlags,
			LPWSTR pwzResult,
			DWORD cchResult,
			DWORD *pcchResult,
			DWORD dwReserved)
		{
			try
			{
				return INET_E_DEFAULT_ACTION;
			}
			_ComCatch() 
		}

		virtual HRESULT STDMETHODCALLTYPE CompareUrl( 
			LPCWSTR pwzUrl1,
			LPCWSTR pwzUrl2,
			DWORD dwCompareFlags)
		{
			try
			{
				return INET_E_DEFAULT_ACTION; 
			}
			_ComCatch() 
		}

		virtual HRESULT STDMETHODCALLTYPE QueryInfo( 
			LPCWSTR pwzUrl, 
			QUERYOPTION QueryOption,
			DWORD dwQueryFlags, 
			LPVOID pBuffer,
			DWORD cbBuffer,
			DWORD *pcbBuf,
			DWORD dwReserved)
		{
			try
			{
				HRESULT rc = INET_E_DEFAULT_ACTION;
				//
				if (QueryOption == QUERY_CONTENT_TYPE)
				{
					if (CStringW(pwzUrl) == L"__url__")
					{
						*pcbBuf = IncomingURL.GetLength()*sizeof(wchar_t);
						CopyMemory(pBuffer,IncomingURL.GetString(),*pcbBuf);
						return S_OK;
					}
				}
				//
				return rc;
			}
			_ComCatch() 
			//
			//
			////if (QueryOption == QUERY_CONTENT_TYPE)
			////{
			////	static CStringA contentType("text/xml");
			////	pBuffer = (void*)new char[contentType.GetLength()+1];
			////	((char*)pBuffer)[contentType.GetLength()] = 0;
			////	CopyMemory((char*)pBuffer,contentType.GetBuffer(),contentType.GetLength());
			////	*pcbBuf = contentType.GetLength()+1;
			////	CString Option(_T("Content-Type!"));
			////	rc = S_OK;
			////}
			////if (QueryOption == QUERY_CAN_NAVIGATE)
			////{
			////	*((int*)pBuffer) = int(false);
			////	*pcbBuf = sizeof(int);
			////	CString Option(_T("Can navigate"));
			////	echo.Format("%s: %d",Option.GetString(),*((int*)pBuffer));
			////	rc = S_OK;
			////}
			////if (QueryOption == QUERY_USES_NETWORK)
			////{
			////	*((int*)pBuffer) = int(true);
			////	*pcbBuf = sizeof(int);
			////	CString Option(_T("Uses network"));
			////	echo.Format("%s: %d",Option.GetString(),*((int*)pBuffer));
			////	rc = S_OK;
			////}
			////if (QueryOption == QUERY_IS_INSTALLEDENTRY)
			////{
			////	*((int*)pBuffer) = int(false);
			////	*pcbBuf = sizeof(int);
			////	CString Option(_T("Is installed entry"));
			////	echo.Format("%s: %d",Option.GetString(),*((int*)pBuffer));
			////	rc = S_OK;
			////}
			//if (QueryOption == QUERY_USES_CACHE)
			//{
			//	*((int*)pBuffer) = int(false);
			//	*pcbBuf = sizeof(int);
			//	CString Option(_T("Uses cache"));
			//	echo.Format("%s: %d",Option.GetString(),*((int*)pBuffer));
			//	rc = S_OK;
			//}
			//else if (QueryOption == QUERY_IS_SECURE)
			//{
			//	*((int*)pBuffer) = int(true);
			//	*pcbBuf = sizeof(int);
			//	CString Option(_T("Secure"));
			//	echo.Format("%s: %d",Option.GetString(),*((int*)pBuffer));
			//	rc = S_OK;
			//}
			//else if (QueryOption == QUERY_IS_SAFE)
			//{
			//	*((int*)pBuffer) = int(false);
			//	*pcbBuf = sizeof(int);
			//	CString Option(_T("Safe"));
			//	echo.Format("%s: %d",Option.GetString(),*((int*)pBuffer));
			//	rc = S_OK;
			//}
			//else
			//{
			//	echo.Format(_T("Option: %d (%d)"),(int)QueryOption,(int)cbBuffer);
			//	rc = CoInternetQueryInfo(pwzUrl,QueryOption,dwQueryFlags,pBuffer,cbBuffer,
			//		pcbBuf,dwReserved);
			//}
			// ATLTRACE(_T("QI <\n"));
			//return rc;
		}






		// =======================================================================================
		// IInternetProtocolSink interface

		STDMETHOD(Switch)(PROTOCOLDATA __RPC_FAR *pProtocolData) 
		{
			try
			{
				return Impl::Switch(pProtocolData);
			}
			_ComCatch()
		}

		STDMETHOD(ReportProgress)(ULONG ulStatusCode, LPCWSTR szStatusText) 
		{
			try
			{
				return Impl::ReportProgress(ulStatusCode,szStatusText);
			}
			_ComCatch()
		}

		STDMETHOD(ReportData)(DWORD grfBSCF, ULONG ulProgress, ULONG ulProgressMax) 
		{
			try
			{
				return Impl::ReportData(grfBSCF,ulProgress,ulProgressMax);
			}
			_ComCatch()
		}

		STDMETHOD(ReportResult)(HRESULT hrResult, DWORD dwError, LPCWSTR szResult) 
		{
			try
			{
				return Impl::ReportResult(hrResult,dwError,szResult); 
			}
			_ComCatch()
		}
	};

	OBJECT_ENTRY_AUTO(CLSID_Protocol, Protocol)
} // namespace  
