#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


#include <low-level/SmartWeb.h>
//
#include <inet-proto/Handlers.h>
//
#include <ax/coclasses/AX_SlotClient.h>
#include <ax/coclasses/AX_SlotRequestComposer.h>


namespace  { 

	namespace Protocol {


		// ----
		// Request Cache 

		class RequestCacheEntry
		{
		public:
			string Url; 

			string ETag; 

			string LocalPath; 

			string ContentType; 

			const RequestCacheEntry& operator =(const RequestCacheEntry& other) 
			{
				Url = other.Url;
				ETag = other.ETag; 
				LocalPath = other.LocalPath; 
				//
				return other; 
			}

			RequestCacheEntry(const RequestCacheEntry& other) 
			{
				operator =(other); 
			}

			RequestCacheEntry() 
			{
			}

			RequestCacheEntry(const string& url) 
			{
				AttachToUrl(url); 
			}

			inline void AttachToUrl(const string& url) 
			{
				try
				{
					Url = url; 
					//
					// No actions, since no ETag information 
				}
				_Catch() 
			}

			inline bool FindIECacheEntry() 
			{
				try
				{
					UrlCacheEntry entry(Url); 
					//
					CString path = entry.GetPath(); 
					//
					if (path.GetLength()) 
					{
						LocalPath = _W(path); 
						return true; 
					}
					return false; 
				}
				_Catch() 
			}

			inline void SetETag(const string& eTag, const string& ct) 
			{
				try
				{
					if (FindIECacheEntry()) 
					{
						ETag = eTag; 
						ContentType = ct; 
					}
				}
				_Catch()
			}
		};

		class RequestCache
		{
		public:
			// Instance 

			inline static RequestCache& Instance() 
			{
				try
				{
					static RequestCache s_RequestCache; 
					return s_RequestCache; 
				}
				_Catch() 
			}

			// Data 

			Map<string,RequestCacheEntry> m_Cache; 

			// Methods 

			inline static string GetEntryKey(const string& url, const string& eTag) 
			{
				try
				{
					string key = url + L"; ETag=" + eTag; 
					//
					return key; 
				}
				_Catch() 
			}

			void CreateEntry(const string& url) 
			{
				try
				{
					RequestCacheEntry entry(url); 
					m_Cache[url] = entry; 
				}
				_Catch() 
			}

			RequestCacheEntry GetEntry(const string& url) 
			{
				try
				{
					//LOCK// PKCS11_Manager::Lock lock; 
					//
					if (! m_Cache.ContainsKey(url))
					{
						CreateEntry(url); 
					}
					//
					return m_Cache[url]; 
				}
				_Catch() 
			}

			void SetEntry(const string& url, const RequestCacheEntry& entry) 
			{
				try
				{
					//LOCK// PKCS11_Manager::Lock lock; 
					//
					return m_Cache[url] = entry; 
				}
				_Catch() 
			}
		};



		// ----
		// ����� �������� ��������� ������� 

		class CabinetConnection 
		{
		public:
			string Host;

			int Port;

		protected:
			Web::Agent m_Agent;

			Web::Connection m_Connection;

			inline Protocol::AppCtx& Instance() 
			{
				return Protocol::AppCtx::Instance(); 
			}

			CabinetConnection() : m_Connection(m_Agent) 
			{
				try
				{
					m_Agent.Name = L".Protocol"; 
					//
					string host;
					string portStr;
					//
					//host = _PROTOCOL_DEFAULT_HOST;
					//portStr = _PROTOCOL_DEFAULT_PORT;
					//
					host = Instance().GetOption(L"slot-gate-host");
					portStr = Instance().GetOption(L"slot-gate-secure-port");
					//
					m_Connection.SetHost(host, _wtoi(portStr)); 
					//
					if (Instance().GetOption(L"special-133") != "")	
					{
						m_Connection.SecureStatus = 3;
					}
					//
					//TRACE_LOG1(_T("!!! Port: %d"), (int)m_Connection.Port );
				}
				_Catch()
			}

		public:
			inline static CabinetConnection& Acquire() 
			{
				try
				{
					static CabinetConnection s_Connection;
					return s_Connection; 
				}
				_FCatch()
			}

			inline Web::Connection& GetConnection() 
			{
				try
				{
					return m_Connection; 
				}
				_Catch() 
			}
		};



		// ----
		// ����� ��� ��������� ������ �������

		class RequestHandler
		{
		public:
			// ----
			// ������ 

			// ���� 

			string Url; // ������� �������������� Url (��������, ��������� ��������: Composer.Url) 

			//CComPtr<ISlotDataStreamInfo> RequestInfo; 

			CComPtr<IStream> PostStream;

			Map<string,string> Headers; 

			CComPtr<ISlotRequestComposer> RequestComposer; 

			bool m_ErrorOutputXml; 

			string m_ErrorMediaType; 

			string m_VXslUrl; 

			//string ComposerUrl;

			//CComPtr<IStream> ComposerStream;

			// ����� 

			int Status;

			string OutUrl;

			string OutCachePath; 

			string OutContentType; 

			RequestCacheEntry OutEntry; 

			CComPtr<IStream> OutStream; 



		protected:
			inline Protocol::AppCtx& Instance() 
			{
				return Protocol::AppCtx::Instance(); 
			}

			void Clear() // ~ Init() 
			{
				Status = 0;
				//
				m_SendReceipt = false; 
				m_UrlIsPublic = false; 
				m_UseCache = false; 
				m_UseCachedStream = false; 
				//
				m_ErrorOutputXml = true; 
				m_ErrorMediaType = _DEFAULT_ERR_MEDIA_TYPE; 
			}

		protected:
			// ----
			// ���������� ��������� 

			template<class I>
			inline void SetOutStream(I* stream) 
			{
				try
				{
					if (OutStream) OutStream.Release(); 
					//
					if (stream)
					{
						CComQIPtr<IStream> q(stream);
						if (! q) throw MethodError(E_NOINTERFACE); 
						OutStream.Attach(q.Detach()); 
					}
				}
				_Catch()
			}

			Map<string,string> m_ResponseHeaders; 

			inline void SetOutResponseHeaders(const Map<string,string>& m) 
			{
				try
				{
					m_ResponseHeaders = m; 
				}
				_Catch() 
			}

		public:
			// ----
			// ����������� URL 

			bool m_UrlIsPublic;

			bool m_SendReceipt; 

			bool m_UseCache; 

			bool m_UseCachedStream; 

			string m_CacheId; 

			inline void CheckUrlIsPublic()
			{
				try
				{
					Uri u(Url); 
					//
					{
						bool pub = false; 
						//
						SharedArray<CString> publicRxs;
						CString slotRxLines = Instance().GetVariable(_T("PublicUrlRxTable"),&publicRxs);
						for (int rx_i = 0; rx_i < publicRxs.Length(); ++rx_i)
						{
							CString rx = publicRxs[rx_i];
							if (Match(rx,_S(u.ResourcePath))) 
							{
								pub = true;
							}
						}
						//
						if (u.flagX(L"sign")) pub = false; // non-public 
						//
						if (pub)  m_UrlIsPublic = pub; 
					}
					//
					{
						if (u.Extension == L"ufml3") 
						{
							m_SendReceipt = true; 
						}
					}
				}
				_Catch()
			}



			// ----
			// Client

			CComPtr<ISlotClient> m_Client;

			string m_ClientPkh64;

			Blob m_ClientPkh;

		private:
			inline ISlotClient* Client(bool throwOnCannotConnect=true) // borrowed reference 
			{
				try
				{
					if (! m_Client)
					{
						CComBSTR bstrPkh64; 
						HRESULT rc = RequestComposer->GetParameterAsText(
							CComBSTR(_PROTOCOL_CLIENT_PKH_PARAM),
							&bstrPkh64
							); 
						if (FAILED(rc)) throw MethodError(rc);
						//
						Blob pkh;
						string pkh64; 
						//
						if ((rc == S_OK) && (bstrPkh64.Length() > 0))
						{
							pkh64 = _W(bstrPkh64); 
							pkh = FromBase64String(pkh64); 
						}
						//
						string errMsg_1 = L"���� � ������� ���������� (" + pkh64 + L")"; 
						//
						ISlotClient* client = _Clients().GetClient(pkh,true); // borrowed, don't activate 
						if (! client) 
						{
							if (throwOnCannotConnect) 
							{
								throw MethodError(errMsg_1); 
							}
							else
							{
								return 0; // no client 
							}
						}
						// 
						m_Client.Attach( 
							CComQIPtr<ISlotClient>(client).Detach() 
							); 
						if (! m_Client) throw MethodError(errMsg_1); 
						//
						CComBSTR b2; 
						rc = m_Client->get_PublicKeyHash(&b2); // ��������� ������ 
						if (FAILED(rc)) throw MethodError(rc); 
						if (b2.Length() == 0) throw MethodError(E_UNEXPECTED); 
						//
						m_ClientPkh = FromBase64String(_W(b2)); 
						m_ClientPkh64 = __ToBase64(m_ClientPkh); 
					}
					return m_Client; 
				}
				_Catch() 
			}

		public:
			inline Blob GetPKH()
			{
				try
				{
					Client();
					//
					return m_ClientPkh; 
				}
				_Catch() 
			}

			//inline Blob GetPKH() 
			//{
			//	try
			//	{
			//		CComPtr<ISlotClient> client;
			//		client.Attach(
			//			CSlotClient::GetClient<ISlotClient>() // new reference 
			//			);
			//		if (! client) throw MethodError(E_UNEXPECTED); 
			//		//
			//		CComBSTR bstrPkh64; 
			//		HRESULT rc = client->get_PublicKeyHash(&bstrPkh64); 
			//		if (FAILED(rc)) throw MethodError(rc); 
			//		//
			//		if (bstrPkh64.Length() == 0) throw MethodError(E_UNEXPECTED); 
			//		//
			//		Blob pkh = FromBase64String(string(bstrPkh64)); 
			//		return pkh; 
			//	}
			//	_Catch() 
			//}



			// ----
			// RequestComposer 

			inline void CreateComposer() 
			{
				try
				{
					try
					{
						RequestComposer.Attach(
							CSlotRequestComposer::Create<ISlotRequestComposer>() 
							);
						//
						HRESULT rc = RequestComposer->put_Url(CComBSTR(Url)); 
						if (FAILED(rc)) throw MethodError(rc); 
						//
						HRESULT rc2 = RequestComposer->put_PostStream(PostStream);  
						if (FAILED(rc2)) throw MethodError(rc2); 
						//
						// RequestComposer->Open(); // --- ���������� ������� 
						//
						// ----
						// ����������� ���������, ����������� ���� ���������� 
						//
						{
							CComBSTR bstrVXsl; 
							rc = RequestComposer->GetParameterAsText(CComBSTR(L"vxsl"),&bstrVXsl); 
							if (FAILED(rc)) throw MethodError(rc); 
							//
							if (rc == S_OK && bstrVXsl.Length() > 0)
							{
								m_VXslUrl = _W(bstrVXsl); 
							}
							//
							CComBSTR bstrV3; 
							rc = RequestComposer->GetParameterAsText(CComBSTR(L"error-media-type"),&bstrV3); 
							if (FAILED(rc)) throw MethodError(rc); 
							//
							if (rc == S_OK && bstrV3.Length() > 0) 
							{
								m_ErrorMediaType = _W(bstrV3); 
							}
						}
					}
					_Catch() 
				}
				catch(::::Exception e)
				{
					throw e.SetMediaType(m_ErrorMediaType).SetVXslUrl(m_VXslUrl); 
				}
				catch(...) { throw; }
			}



			void OpenComposer() 
			{
				try
				{
					if (! RequestComposer) throw MethodError(E_POINTER); 
					//
					int requestSecurityStatus; 
					HRESULT rc = RequestComposer->get_SecurityStatus(&requestSecurityStatus); 
					if (FAILED(rc)) throw MethodError(rc); 
					//
					if (requestSecurityStatus != 0 && (!m_UrlIsPublic))
					{
						ISlotClient* client = Client(false); // borrowed, soft client query 
						if (client)
						{
							rc = RequestComposer->put_Client(m_Client); 
							if (FAILED(rc)) throw MethodError(rc); 
						}
					}
					//
					rc = RequestComposer->Open();
					if (FAILED(rc)) throw MethodError(rc);
					//
					CComQIPtr<IStream> requestStream(RequestComposer); 
					if (! requestStream) throw MethodError(E_UNEXPECTED); 
					//
					CComBSTR bstrUrl;
					rc = RequestComposer->get_Url(&bstrUrl);
					if (FAILED(rc)) throw MethodError(rc);
					//
					if (PostStream) PostStream.Release(); 
					//
					PostStream.Attach(requestStream.Detach()); 
				}
				_Catch()
			}



			// ----
			// Request Headers

			inline void SetHeader(const string& name,const string headerValue) 
			{
				try
				{
					Headers[name] = headerValue; 
				}
				_Catch()
			}

			inline CStringA GetHeadersAsText() 
			{
				try
				{
					CStringA s;
					//
					for (Map<string,string>::Iterator i(Headers); i; ++i)
					{
						string headerName = i.Id(); 
						string headerValue = i; 
						//
						CStringA headerLine = _A(headerName) + ": " + _A(headerValue); 
						//
						if (s.GetLength() > 0) s += "\r\n"; 
						//
						s += headerLine; 
					}
					//
					return s;
				}
				_Catch() 
			}



			// ----
			// �������� ������ ������� 

			void SetUrlAndPost(const string& url,IStream* stream) 
			{
				try
				{
					Url = url;
					//
					if (Url.Find(L".xml") != -1) m_UseCache = true; 
					if (stream) m_UseCache = false; 
					//
					if (m_UseCache) 
					{
						string id = GetObjCacheId(); 
						CComPtr<IStream> cachedStream; 
						string contentType; 
						string cachePath; 
						if (ObjCache::GetStreamObject(id, &cachedStream, contentType, cachePath)) 
						{
							OutUrl = Url; 
							OutCachePath = cachePath; 
							OutContentType = contentType; 
							SetOutStream((IStream*)cachedStream); 
							m_UseCachedStream = true; 
							return; 
						}
					}
					//
					// �������������� � ������ (������: ����� �� ������ CLone()) 
					//
					if (PostStream) PostStream.Release(); 
					if (stream)
					{
						CComQIPtr<IStream> q(stream); 
						if (! q) throw MethodError(E_UNEXPECTED); 
						PostStream.Attach(q.Detach()); 
					}
					//
					// ������������ 
					//
					CheckUrlIsPublic();
					//
					CreateComposer(); 
				}
				_Catch()
			}

			inline void ParseHeaders(const string& incHeaders)
			{
				try
				{
					string H = incHeaders; 
					while (H.GetLength() > 0) 
					{
						string line;
						int p0 = H.Find(L"\n"); 
						if (p0 == -1)
						{
							line = H;
							H = L"";
						}
						else
						{
							line = H.Left(p0); 
							H = H.Right(H.GetLength()-p0-1); 
							H.Trim(); 
						}
						//
						line.Trim();
						if (line.GetLength() > 0)
						{
							int p1 = line.Find(L":"); 
							if (p1 != -1)
							{
								string name = line.Left(p1);
								string value = line.Right(line.GetLength()-p1-1); 
								//
								name.Trim();
								value.Trim(); 
								//
								SetHeader(name,value); 
							}
						}
					}
				}
				_Catch() 
			}

			inline void SetParameter(
				const string& source,
				const string& encType,
				const string& name,
				const string& value)
			{
				try
				{
					if (! RequestComposer) throw MethodError(E_NOINTERFACE); 
					//
					HRESULT rc = RequestComposer->SetParameter(
						CComBSTR(source),
						CComBSTR(encType),
						CComBSTR(name),
						CComBSTR(value)
						);
					if (FAILED(rc)) throw MethodError(rc); 
				}
				_Catch()
			}

			inline int GetIntegerOption(const string& name)
			{
				try
				{
					try
					{
						string iStr = Instance().GetOption(name); 
						//
						int i = _wtoi(iStr); 
						//
						return i; 
					}
					catch(...)
					{
						return 0;
					}
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






			inline void Prepare() 
			{
				try
				{
					///Lock lock; 
					//
					CheckUrlIsPublic();
					//
					// ----
					// Cache 
					//
					OutEntry = RequestCache::Instance().GetEntry(Url); 
					//
					int fIfNoneMatch = GetIntegerOption(L"f-header-If-None-Match"); 
					//
					if ((OutEntry.ETag.GetLength() > 0) && (fIfNoneMatch & 0x1))
					{
						SetHeader(L"If-None-Match", OutEntry.ETag); 
						//
						OutCachePath = OutEntry.LocalPath;
						OutContentType = OutEntry.ContentType; 
					}
					//
					//
					if (! m_UrlIsPublic) 
					{			
#						ifdef _DEBUG
						{
							TRACE_LINE(_T("URL is ___SECURE: ") + _S(Url)); 
						}
#						endif
						//
						OpenComposer(); 
						//
						CComPtr<ISlotDataStreamInfo> RequestInfo; 
						if (PostStream)
						{
							CComQIPtr<ISlotDataStreamInfo> q(PostStream); 
							if (q) RequestInfo.Attach(q.Detach()); 
						}
						// TODO: /// if (! RequestInfo) throw MethodError(E_UNEXPECTED); // (���������) 
						//
						// -----------------------------------------------------------------------
						string verStr = SystemInfo::GetProtocolVersion(); 
						SetHeader(L"X--ProtocolVersion", verStr ); 
						//
						string packageStr = Machine::GetCabinetVersion(); 
						SetHeader(L"X--CabinetVersion", verStr ); 
						// -----------------------------------------------------------------------
						//
						string requestDataSource = L"post";
						string contentType = L"text/xml"; // TODO: ��� default 
						//
						if (RequestInfo)
						{
							// ----
							// request-data-source
							//
							{
								requestDataSource = GetStreamParameterAsString( 
									RequestInfo,
									L"request-data-source");
							}
							//
							// ----
							// Content-Type 
							//
							{
								contentType = GetStreamParameterAsString(
									RequestInfo,
									L"content-type");
							}
						}
						//
						if (requestDataSource == L"post")
						{
							Blob certPKH = GetPKH();
							//
							SetHeader(L"X--ClientPublicKeyHash",__ToBase64(certPKH)); 
						}
						//
						//SetHeader(L"X--ClientPKHList", Instance().GetCurrentPKHList()); 
						//
						string s1 = Instance().GetCurrentPKHBinaryListStr(); 
						//string s2 = ToBase64NoPad_NewQuest_1(Instance().GetCurrentPKHBinaryList()); 
						if (s1.GetLength() > 0) 
						{
							SetHeader(L"X--PKHBinaryList", s1 ); 
						}
						//
						if (contentType.GetLength() > 0)
						{
							SetHeader(L"Content-Type",contentType); 
						}
					}
					else
					{
#						ifdef _DEBUG
						{
							TRACE_LINE(_T("URL is PUBLIC: ") + _S(Url)); 
						}
#						endif
					}
				}
				_Catch()
			}



			// ----
			// ������������ 

			RequestHandler()
			{
				try
				{
					Clear(); 
				}
				_Catch() 
			}

			inline void Open(const string& url,IStream* stream=0,const string& incHeaders=L"")
			{
				try
				{
					//LOCK// PKCS11_Manager::Lock lock; 
					//
					Clear(); 
					//
					SetUrlAndPost(url,stream); 
					ParseHeaders(incHeaders); 
				}
				_Catch() 
			}

			RequestHandler(const string& url)
			{
				try
				{
					Clear(); 
					//
					Open(url,0); 
				}
				_Catch() 
			}

			RequestHandler(const string& url,IStream* stream)
			{
				try
				{
					Clear(); 
					//
					Open(url,stream); 
				}
				_Catch() 
			}

			//inline void Open(ISlotRequestComposer* composer)
			//{
			//	try
			//	{
			//		SetComposer(composer); 
			//		OpenComposer(); 
			//	}
			//	_Catch() 
			//}

			//RequestHandler(ISlotRequestComposer* composer)
			//{
			//	try
			//	{
			//		Clear(); 
			//		//
			//		Open(composer); 
			//	}
			//	_Catch() 
			//}

			// ----
			// ��������� ����������� �������� 

			inline void RunHandler(
				const string& handlerProgId, 
				ISlotRequestComposer* composer 
				,int* out_status
				,string* out_url
				,string* out_cachePath
				,string* out_contentType
				,IStream** out_stream 
				) 
			{
				try
				{
					CComQIPtr<IStream> composerStream(composer); 
					if (! composerStream) throw MethodError(E_NOINTERFACE); 
					//
					CComPtr<ISlotRequestHandler> handler; 
					handler.Attach(
						CHandlers::Create<ISlotRequestHandler>(
							handlerProgId,
							composerStream 
							) // new reference 
						);
					if (! handler) throw MethodError(E_UNEXPECTED); 
					//
					CComBSTR bstrOutUrl;
					CComBSTR bstrOutCachePath; 
					CComBSTR bstrOutContentType;
					HRESULT rc = handler->OnRequest(out_status,&bstrOutUrl,&bstrOutCachePath,
						&bstrOutContentType,out_stream); 
					if (FAILED(rc)) throw MethodError(rc); 
					//
					//bool _f1 = (! bstrOutUrl);
					//bool _f2 = (! bstrOutCachePath);
					////
					//TRACE_LOG2(_T("BSTR state: %d, %d"), (int)_f1, (int)_f2 ); 
					//
					if (out_url) 
						*out_url = (! bstrOutUrl) ? L"" : _W(bstrOutUrl); 
					if (out_cachePath) 
						*out_cachePath = (! bstrOutCachePath) ? L"" : _W(bstrOutCachePath); 
					if (out_contentType) 
						*out_contentType = (! bstrOutContentType) ? L"" : _W(bstrOutContentType); 
				}
				_Catch() 
			}

			// ----
			// ��������� ������� 

			//inline int OneRequest(
			//	//
			//	// In
			//	//
			//	CabinetConnection& conn,
			//	const string& url,			// ������� �������������� URL 
			//	IStream* requestStream,		// ISlotRequestComposer, IStream 
			//	//
			//	// Out
			//	//
			//	IStream** out_stream
			//	) 
			//{
			//	try
			//	{
			//		string handlerProdId;
			//		//
			//		// ISlotRequestComposer? 
			//		CComPtr<ISlotRequestComposer> composer;
			//		if (requestStream)
			//		{
			//			CComQIPtr<ISlotRequestComposer> q(requestStream); 
			//			if (q) composer.Attach(q.Detach()); 
			//		}
			//		//
			//		if (composer)
			//		{
			//		}
			//		//
			//		int status = request.Send(); 
			//		//
			//		return status; 
			//	}
			//	_Catch() 
			//}

			string GetRequestParameterAsText(const string& name)
			{
				try
				{
					if (! RequestComposer) throw MethodError(E_NOINTERFACE); 
					// 
					string value; 
					CComBSTR bstrVal; 
					HRESULT rc = RequestComposer->GetParameterAsText(CComBSTR(name),&bstrVal); 
					if (rc == S_OK) value = _W(bstrVal); 
					//
					return value; 
				}
				_Catch()
			}

			void SearchInCache() 
			{
				try
				{
					if (Url.GetLength() == 0) return;
					//
					try
					{
						// RequestCacheEntry entry = RequestCache::Instance().GetEntry(Url); 
					}
					catch(::::Exception e)
					{
#						ifdef _DEBUG
						{
							throw; 
						}
#						else
#						endif
					}
					catch(...)
					{
#						ifdef _DEBUG
						{
							throw; 
						}
#						else
#						endif
					}
				}
				_Catch() 
			}


			inline string GetObjCacheId()
			{
				try
				{
					string id = L"_Pr_Url_" + Url; 
					return id; 
				}
				_Catch()
			}

			void Run()
			{
				try
				{
					try
					{
						// ----
						// ������ 
						//
						Prepare(); // ���������� ����� ��������� ���� ���������� 
						//
						// ----
						// ���������� ������ �� ������ 
						//
						CabinetConnection& C = CabinetConnection::Acquire(); 
						//
						// ���� ��������� ������� 
						//
						Status = 0; // empty status 
						bool redirecting;
						//
						do
						{
							/// TODO: int newStatus = OneRequest(C,Url,PostStream); 
							//
							int newStatus = 0; 
							//
							// ����������� �������
							{
								if (RequestComposer)
								{
									string handlerProgId = GetRequestParameterAsText(L"handler-progid"); 
									//
									if (handlerProgId.GetLength() > 0) // 
									{
										int hOutStatus = 0;
										string hOutUrl; 
										string hOutCachePath; 
										string hOutContentType;
										CComPtr<IStream> hOutStream; 
										//
										RunHandler(handlerProgId,RequestComposer
											,&hOutStatus,&hOutUrl,&hOutCachePath
											,&hOutContentType,&hOutStream 
											); 
										//
										if (hOutStatus) // ������! 
										{
											newStatus = hOutStatus; 
											OutUrl = hOutUrl; 
											OutCachePath = hOutCachePath; 
											OutContentType = hOutContentType; 
											SetOutStream((IStream*)hOutStream); 
										}
									}
								}
							}
							//
							if (newStatus == 0) // || Url.Find(L"GenerateRequest") != -1
							{
								//TRACE_LOG(_S("!!! ") + _S(C.GetConnection().GetAgent().Name)); 
								//
								Web::Request request(C.GetConnection(),Url,PostStream); 
								//
								request.OpenFlags = request.CabinetGateOpenFlags(); 
								//
								request.R.Headers = GetHeadersAsText(); 
								//
								newStatus = request.Send(); 
								//
								//if (newStatus == 407) 
								//{
								//	request.UseProxy(); 
								//}
								if (newStatus == 707) 
								{
								}
								else if (newStatus == 307)
								{
									OutUrl = request.ParseRedirectUrl(); 
									//
									SetUrlAndPost(OutUrl,0); 
									{
										// ... // ��������� POST? 
									}
								}
								else if (newStatus == 304)
								{
									OutUrl = request.R.Location().ReferenceUrl; 
									////OutContentType = request.R.OutContentType; 
									SetOutResponseHeaders(request.R.ResponseHeaders);  
									//
									OutCachePath = OutEntry.LocalPath; 
									//
									CComPtr<IStream> stream; 
									stream.Attach(
										CSlotFileReader::OpenFile<IStream>(_S(OutCachePath))
										);
									SetOutStream((IStream*)stream); 
									//
									Status = 200; 
								}
								else // OK (200) ��� ���� ������: ��������� ��������� � ���������� ������������ 
								{
									OutUrl = request.R.Location().ReferenceUrl; 
									OutContentType = request.R.OutContentType; 
									SetOutResponseHeaders(request.R.ResponseHeaders);  
									SetOutStream(request.GetResponseStream()); 
									//
									if (m_UseCache && (OutContentType == L"text/xml")) 
									{
										ObjCache::AddStreamObject(
											GetObjCacheId(), 
											_OC_TIMEOUT_PR_PATH, OutStream, 
											OutContentType, OutCachePath); 
									}
									//
									for (Map<string,string>::Iterator i(request.R.ResponseHeaders); i; ++i)
									{
										string k = i.Id();
										string v = i; 
										//
										//TRACE_LINE2(_T("%s: %s"), _S(k).GetString(), _S(v).GetString()); 
									}
									//
									if (m_ResponseHeaders.ContainsKey(L"ETag"))
									{
										string eTag = m_ResponseHeaders[L"ETag"]; 
										//
										RequestCacheEntry entry(Url);
										entry.SetETag(eTag, OutContentType); 
										//
										RequestCache::Instance().SetEntry(Url, entry); 
									}
								}
							}
							//
							if (newStatus == 307)
							{
								redirecting = true; 
							}
							else if (newStatus == 407)
							{
								redirecting = true; 
							}
							else if (newStatus == 0)
							{
								throw MethodError(L"������ �� ���������"); 
							}
							else // OK (200) ��� ���� ������: ��������� ��������� � ���������� ������������ 
							{						
								redirecting = false; 
								//
								if (newStatus == 200) 
								{
									SendReceiptIfNeeded(Url); 
								}
							}
							//
							Status = newStatus; 
						}
						while (redirecting);
						//
#						ifdef _DEBUG
						{
							//TRACE_LINE1(_T("������ ������� ���������: %s"), _S(OutUrl).GetString() ); 
						}
#						endif
						//
						// ----
						// ��������� ��������� � �������������� ��������� 
						//
						// OutStream �������� ������ ��� ����������� ������������ 
						// (� ������ ������������� ������ ������ ������������ ����������,
						//  ������� �������������� �� ������ ������ ������������ ��������-���������)
						//
						if (! OutStream) 
						{
							//if (Status != 204)
							//{
								throw MethodError(E_UNEXPECTED); 
							//}
						}
					}
					_Catch()
				}
				catch(::::Exception e)
				{
					Status = 500;
					throw e.SetMediaType(m_ErrorMediaType).SetVXslUrl(m_VXslUrl); 
				}
				catch(...) { throw; }
			}



			// ===================================================================================
			// ��������� 

			inline static string ReceiptXmlTemplate(string& uuid)
			{
				uuid = NewGuidStr();
				//
				return _W(COMMON_XML_START) + 
					L"<envelope"
					L" uuid=\"" + uuid + L"\""
					L" xmlns=\"http://cabinet.example.com/schema/ufml3/rel-1/\""
					L" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\""
					L" xsi:schemaLocation=\"http://cabinet.example.com/schema/ufml3/rel-1/ http://cabinet.example.com/schema/ufml3/rel-1/ufml3.xsd\""
					L">\n"
					L"	<receipt __A__ />"
					L"</envelope>";
			}

			IStream* CloneOutStream() // new reference 
			{
				try
				{
					if (! OutStream) throw MethodError(E_POINTER); 
					//
					CComPtr<IStream> stream; 
					HRESULT rc = OutStream->Clone(&stream); 
					if (FAILED(rc)) throw MethodError(rc); 
					//
					return stream.Detach(); 
				}
				_Catch() 
			}

			inline bool SendReceiptIfNeeded(const string& url)
			{
				try
				{
					Uri u(url); 
					//
					bool sendReceipt = m_ResponseHeaders.ContainsKey(_PROTOCOL_RSP_HEADER_RECEIPT_NEEDED); 
					//// if (!( u.Extension == L"ufml3" )) sendReceipt = false; 
					//
#ifdef _DEBUG
					//return SendReceipt(url); 	
#endif
					//
					if (sendReceipt)
					{
						return SendReceipt(url); 						
					}
					//
					return false;
				}
				_Catch() 
			}

			inline void SignXmlStream(IStream* inputStream0,IStream** out_Stream) 
			{
				try
				{
					if (! inputStream0) throw MethodError(E_POINTER);
					if (! out_Stream) throw MethodError(E_POINTER);
					//
					CComPtr<IStream> inputStream;
					HRESULT rc = inputStream0->Clone(&inputStream);
					if (FAILED(rc)) throw MethodError(rc); 
					//
					CComPtr<ISlotDataStreamInfo> info;
					info.Attach(
						CSlotXmlFilter::CreateXmlFilter<ISlotDataStreamInfo>() // new reference 
						);
					if (! info) throw MethodError(E_UNEXPECTED); 
					//
					rc = info->put_DataStream(inputStream); 
					//
					// Hashing 
					//
					CComQIPtr<ISlotXmlFilter> info_f(info); 
					//
					rc = info_f->Open(); 
					if (FAILED(rc)) throw MethodError(rc); 
					//
					rc = info->get_DataStream(out_Stream); 
					if (FAILED(rc)) throw MethodError(rc); 
				}
				_Catch()
			}

			inline bool SendReceipt(const string& url)
			{
				try
				{
					try
					{
#						ifdef _DEBUG
						//return true;
#						endif
						//
						// ----
						// ��� 
						//
						CComPtr<IStream> stream;
						//// stream.Attach(CloneOutStream()); 
						{
							UrlCacheEntry entry(url); 
							//
							if (! entry.Exists())
							{
								throw MethodError(L"No cache entry (for preparing receipt)");
							}
							//
							CString cachePath = entry.GetPath(); 
							if (cachePath.GetLength() == 0)
							{
								throw MethodError(L"cachePath == <empty>");
							}
							//
							CComPtr<ISlotFileReader> reader;
							reader.Attach(
								CSlotFileReader::Create<ISlotFileReader>() 
								);
							//
							HRESULT rc = reader->put_Path(CComBSTR(_W(cachePath)));
							if (FAILED(rc)) throw MethodError(rc); 
							//
							rc = reader->Open();
							if (FAILED(rc)) throw MethodError(rc); 
							//
							CComQIPtr<IStream> q(reader); 
							if (! q) throw MethodError(E_UNEXPECTED); 
							stream.Attach(q.Detach()); 
						}
						//
						CComPtr<ISlotDataStreamInfo> targetHasherInfo;
						targetHasherInfo.Attach(
							CSlotXmlFilter::CreateHasher<ISlotDataStreamInfo>(
								_HASHER_TYPE_XML_HASH,
								stream,
								true) 
							);
						if (! targetHasherInfo) throw MethodError(E_UNEXPECTED); 
						//
						HRESULT rc = targetHasherInfo->SetDataStreamParameter(
							CComBSTR(L"pi-num"),CComVariant((DWORD)0)); 
						if (FAILED(rc)) throw MethodError(rc); 
						//
						// Hashing 
						//
						CComQIPtr<ISlotXmlFilter> targetHasherInfo_f(targetHasherInfo); 
						//
						rc = targetHasherInfo_f->Open(); 
						if (FAILED(rc)) throw MethodError(rc); 
						//
						CComVariant v;
						rc = targetHasherInfo->GetDataStreamParameter(CComBSTR(L"hash64"),&v); 
						if (v.vt != VT_BSTR) throw MethodError(E_UNEXPECTED); 
						if (FAILED(rc)) throw MethodError(rc); 
						//
						CComVariant v2;
						rc = targetHasherInfo->GetDataStreamParameter(CComBSTR(L"hash-target-uuid"),&v2); 
						if (v2.vt != VT_BSTR) throw MethodError(E_UNEXPECTED); 
						if (FAILED(rc)) throw MethodError(rc); 
						//
						//
						// ----
						// ��������� 
						//
						string receiptUuid;
						string receipt = ReceiptXmlTemplate(receiptUuid);
						//
						string docUuid(v2.bstrVal); 
						string docHash(v.bstrVal); 
						//
						receipt.Replace(L"__A__",
							L"envelope-uuid=\"" + docUuid + L"\" "
							L"envelope-hash=\"" + docHash + L"\" "
							);
						//
#						ifdef _DEBUG
						{
							//OutputDebugString(_S(receipt)); 
						}
#						endif
						//
						// ----
						// ����������� - ��������� ����� ��������� �������������, ��� ����� �������� (post) 
						//
						Blob receiptData = WideStringToUTF8(receipt); 
						//
						CComPtr<IStream> receiptStream_1;
						receiptStream_1.Attach(CSlotMemoryReader::Create<IStream>()); 
						CComQIPtr<ISlotMemoryReader> receiptReader(receiptStream_1);
						//
						rc = receiptReader->put_Size(receiptData.Length()); 
						if (FAILED(rc)) throw MethodError(rc);
						//
						rc = receiptReader->put_Data(receiptData.GetBuffer()); 
						if (FAILED(rc)) throw MethodError(rc);
						//
						// XMLdsig 
						//
						//CComPtr<IStream> receiptStream_2;
						//SignXmlStream(receiptStream_1,&receiptStream_2); 
						//
						// ----
						// ���������� 
						//
						string receiptUrl = Instance().GetOption(L"slot-receipt-url"); 
						//
						RequestHandler R;
						R.Open(receiptUrl,receiptStream_1);  
						////R.SetParameter(L"POST",L"xml",L"__receipt__",rr); // ���� � ��������� 1.0 
						R.Run(); 
						//
						return true; 
					}
					_Catch()
				}
				catch(...)
				{
					throw; // 4 k 2, �������� ��������, 73 
				}
			}
					




			// ===================================================================================
			// ������� ��� ������ ����� 

			inline string GetStreamParameterAsString(ISlotDataStreamInfo* i,const string& name,
				bool* out_found=0)
			{
				try
				{
					if (! i) throw MethodError(E_POINTER); 
					//
					string value; 
					//
					CComVariant v;
					HRESULT rc = i->GetDataStreamParameter(CComBSTR(name),&v); 
					if (rc == S_OK)
					{
						if (v.vt == VT_BSTR)
						{
							value = _W(v.bstrVal); 
							//
							if (out_found) *out_found = true; 
							return value;
						}
					}
					if (out_found) *out_found = false; 
					return value; 
				}
				_Catch() 
			}
		};

	}

} // namespace  
