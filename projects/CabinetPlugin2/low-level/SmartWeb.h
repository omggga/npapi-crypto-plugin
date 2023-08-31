/*
 SmartWeb.h : ������ ��� ������ � WinInet:

	Web-������ 

 $Name: work1 $
 $Revision: 1.1.2.11 $
 $Date: 2009/05/18 12:32:23 $

 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


// ----
// h 

#include <low-level/SmartInetBase.h>
#include <low-level/SmartUri.h>
#include <low-level/SmartUtil.h>
#include <low-level/SmartException.h>
#include <low-level/SmartDns.h>
//
#include <inet-proto/ProtocolUtil.h>
//
#include <dialogs/SlotPswDialog.h>
//
#include <ax/interfaces/ISlotRequestComposer.h>
//
#include <ax/coclasses/AX_SlotFileReader.h>
///#include <ax/coclasses/AX_SlotMultipartReader.h> // � ��������� ������! 


namespace 
{
	namespace Web 
	{
		struct Util
		{
			inline static string HttpQueryInfoAsText(HINTERNET hReq,DWORD id,LPDWORD lpdwIndex=0)
			{
			}

			inline static void GetProxyUserNameAndPassword(
				string& name,string& pass) 
			{
				static string s_ProxyUserName; 
				static string s_ProxyPassword; 
				//
				if (s_ProxyPassword.GetLength() == 0)
				{
					PasswordDialog::GetProxyPassword(
						s_ProxyUserName,s_ProxyPassword
						); 
				}
				name = s_ProxyUserName; 
				pass = s_ProxyPassword; 
			}
		};












		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		// Agent 

		class Agent 
		{
		public:
			string Name;

			int InternetOpenType;

			string Proxy;

			string ProxyBypass;

			string ProxyPassword; 

			int Flags;

		protected:
			HINTERNET m_hInternet;

		public:
			Agent() : m_hInternet(0), 
				InternetOpenType(INTERNET_OPEN_TYPE_PRECONFIG), Flags(0) 
			{
			}

			Agent(const string& name) : m_hInternet(0), 
				InternetOpenType(INTERNET_OPEN_TYPE_PRECONFIG), Flags(0), 
				Name(name) 
			{
			}

			~Agent()
			{
				if (m_hInternet)
				{
					if (! InternetCloseHandle(m_hInternet))
					{
						throw LastInternetError();
					}
				}
			}

			Agent& Direct()
			{
				InternetOpenType = INTERNET_OPEN_TYPE_DIRECT;
				return *this;
			}

			HINTERNET Internet()
			{
				try
				{
					if (! m_hInternet)
					{
						if (InternetOpenType == INTERNET_OPEN_TYPE_PROXY)
						{
							m_hInternet = InternetOpen(_S(Name),InternetOpenType,_S(Proxy),_S(ProxyBypass),
								(DWORD)Flags); 
						}
						else
						{
							m_hInternet = InternetOpen(_S(Name),InternetOpenType,0,0,
								(DWORD)Flags); 
						}
						if (! m_hInternet)
						{
							throw MethodError(L"�� ������ ���������������� ����������� � Internet"); 
							//throw LastInternetError();
						}
					}
					if (! m_hInternet)
					{
						throw MethodError(L"�� ������ ���������������� ����������� � Internet (2)"); 
					}
					return m_hInternet; 
				}
				_Catch()
			}

		//	inline void UseProxy() 
		//	{
		//		try
		//		{
		//			if (! m_hInternet) throw MethodError(E_POINTER); 
		//			//
		//			string proxyUserName; 
		//			string proxyPassword; 
		//			::::Web::Util::GetProxyUserNameAndPassword(
		//				proxyUserName,proxyPassword
		//				);
		//			//
		//			if (proxyPassword.GetLength() == 0) 
		//			{
		//				return; 
		//			}
		//			//
		//			// ----
		//			// Using Proxy 
		//			//
		//			InternetOpenType = INTERNET_OPEN_TYPE_PROXY; 
		//			m_hInternet = 0;
		//			Internet(); 
		//			//
		//			CString proxyPasswordStr = _S(proxyPassword); 
		//			if (! InternetSetOption(m_hInternet,
		//				INTERNET_OPTION_PROXY_PASSWORD,
		//				proxyPassword.GetBuffer(),
		//				proxyPassword.GetLength()*sizeof(TCHAR)
		//				)) 
		//			{
		//				DWORD dwErr = GetLastError();
		//				throw MethodError(INTERNET_ERROR(dwErr)); 
		//			}
		//			//
		//			CString proxyUserNameStr = _S(proxyUserName); 
		//			if (! InternetSetOption(m_hInternet,
		//				INTERNET_OPTION_PROXY_USERNAME,
		//				proxyUserName.GetBuffer(),
		//				proxyUserName.GetLength()*sizeof(TCHAR)
		//				)) 
		//			{
		//				DWORD dwErr = GetLastError();
		//				throw MethodError(INTERNET_ERROR(dwErr)); 
		//			}
		//		}
		//		_Catch() 
		//	}

		protected:
			inline Protocol::AppCtx& Instance() 
			{
				return Protocol::AppCtx::Instance(); 
			}

		public:
			inline bool SetOptionTo(HINTERNET h,
				DWORD opt,
				const string& name,int value=0)
			{
				try
				{
					int v = value;
					if (v == 0)
					{
						string vStr = Instance().GetOption(name); 
						if (vStr.GetLength() > 0)
						{
							v = _wtoi(vStr); 
						}
						else
						{
							v = 0; 
						}
					}
					//
#					ifdef _DEBUG
						LONG dwValue_1 = 0;
						DWORD dwValue_1_Size = 0; 
					{
						HRESULT r0 = InternetQueryOption(h,opt,0,&dwValue_1_Size); 
						if (dwValue_1_Size != sizeof(dwValue_1)) 
							throw MethodError(L"��������� ������ ������"); 
						r0 = InternetQueryOption(h,opt,&dwValue_1,&dwValue_1_Size); 
						//TRACE_LINE2(_T("����� Web: %s --> %d  --  ������� ��������"), _S(name).GetString(), (int)dwValue_1 ); 
					}
#					endif
					//
					if (v == 0) return false; 
					//
					DWORD t = v; 
					BOOL bRet = InternetSetOption(h, 
					   //INTERNET_OPTION_CONNECT_TIMEOUT, 
					   opt, 
					   &t, 4); 
					if (! bRet)
					{
						DWORD dwErr = GetLastError();
						HRESULT r1 = HRESULT_FROM_WIN32(dwErr); 
						string errorMsg = L"������ ��� ��������� ��������� ��������-����������: " + 
							FormatStr(L"0x%x",(int)r1) + L", " + 
							FormatStr(L"0x%x",(int)opt) + L", " + name + L", " + FormatStr(L"%d",(int)v); 
						//
						throw MethodError(errorMsg); 
					}
					//
					return true; 
					//
					////INTERNET_PER_CONN_OPTION_LIST list;
					////ZeroMemory(&list,sizeof(list));
					//////
					////list.dwSize = sizeof(list);
					//////
					////list.pszConnection = NULL;
					//////
					////list.dwOptionCount = 1;
					////list.pOptions = new INTERNET_PER_CONN_OPTION[list.dwOptionCount];
					//////
					////ZeroMemory(&(list.pOptions[0]),sizeof(list.pOptions[0]));
					//////
					////CString s = FormatStr(_T("%d"),(int)v); 
					////list.pOptions[0].dwOption = opt; 
					//////list.pOptions[0].Value.dwValue = (DWORD)v; 
					////list.pOptions[0].Value.pszValue = s.GetBuffer(); 
					//////
					////if (! InternetSetOption(h,INTERNET_OPTION_PER_CONNECTION_OPTION,
					////	(void*)&list,sizeof(list))) 
					////{
					////	DWORD dwErr = GetLastError();
					////	HRESULT r1 = HRESULT_FROM_WIN32(dwErr); 
					////	string errorMsg = L"������ ��� ��������� ��������� ��������-����������: " + 
					////		FormatStr(L"0x%x",(int)opt) + L", " + name + L", " + FormatStr(L"%d",(int)v); 
					////	//
					////	delete[] list.pOptions; 
					////	MethodError(errorMsg).Alarm(); 
					////}
					//////
					////delete[] list.pOptions; 
					////return true; 
				}
				_Catch() 
			}
		};






		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		// Connection 

		class Connection 
		{
		protected:
			Agent& m_Agent;

			Map<string,string> m_Requests;

			string Host;

		public:
			HINTERNET hConnect;

			string HostIp;

			int Port;

			int SecureStatus;

			inline Agent& GetAgent()
			{
				return m_Agent;
			}

			Connection(Agent& agent) : m_Agent(agent), hConnect(0), Port(0) 
			{
				SecureStatus = 1;
			}

			void Open()
			{
				try
				{
					Close();
					//
#					ifdef _DEBUG
					//
						//string Host = L"pcab3"; 
						//int Port = 80; 
					//
#					endif
					//
					hConnect = InternetConnect(m_Agent.Internet()
						,_S(HostIp),(INTERNET_PORT)Port
						,0,0,INTERNET_SERVICE_HTTP,0,0);
					if (! hConnect)
					{
						string errorMsg = L"������ �����������: " + 
							_W(Host) + L" (" + _W(HostIp) + L") " + FormatStr(L"%d",(int)Port) + L""; 
						throw MethodError(errorMsg); 
						//throw LastInternetError();
					}
					//
					// ����� 
					//
					Agent().SetOptionTo(hConnect,INTERNET_OPTION_CONNECT_TIMEOUT
						,L"web-connect-timeout"); 
					Agent().SetOptionTo(hConnect,INTERNET_OPTION_FROM_CACHE_TIMEOUT  
						,L"web-fromcache-timeout"); 
					Agent().SetOptionTo(hConnect,INTERNET_OPTION_RECEIVE_TIMEOUT 
						,L"web-receive-timeout"); 
					Agent().SetOptionTo(hConnect,INTERNET_OPTION_SEND_TIMEOUT 
						,L"web-send-timeout"); 
					//
#					ifdef _DEBUG
					{
					Agent().SetOptionTo(hConnect,INTERNET_OPTION_CONNECT_TIMEOUT
						,L"web-connect-timeout"); 
					Agent().SetOptionTo(hConnect,INTERNET_OPTION_FROM_CACHE_TIMEOUT  
						,L"web-fromcache-timeout"); 
					Agent().SetOptionTo(hConnect,INTERNET_OPTION_RECEIVE_TIMEOUT 
						,L"web-receive-timeout"); 
					Agent().SetOptionTo(hConnect,INTERNET_OPTION_SEND_TIMEOUT 
						,L"web-send-timeout"); 
					}
#					endif
				}
				_Catch()
			}

			inline void OpenIfNotYet()
			{
				try
				{
					if (! hConnect)
					{
						Open();
					}
				}
				_Catch()
			}

			void Close() 
			{
				if (hConnect)
				{
					if (! InternetCloseHandle(hConnect))
					{
						throw LastInternetError();
					}
				}
			}

			~Connection()
			{
				Close();
			}

			HRESULT RegisterRequest(const string& requestId)
			{
				try
				{
					string id = requestId;
					//
					string requestXml = _W(COMMON_XML_START) + L"<request id=\"" + id + L"\" />";
					return S_OK;
				}
				_Catch()
			}

			inline void UnregisterRequest(const string& requestId)
			{
				m_Requests.Remove(requestId);
			}

			inline void CheckIpInfo(const string& IpStr) 
			{
				try
				{
					Machine::AddRegKey(HKEY_CURRENT_USER, _S(L"Software\\")); 
					Machine::AddRegKey(HKEY_CURRENT_USER, _S(L"Software\\\\Cabinet")); 
					Machine::AddRegKey(HKEY_CURRENT_USER, _S(L"Software\\\\Cabinet\\Host")); 
					//
					Machine::AddRegKey(HKEY_CURRENT_USER, _S(L"Software\\\\Cabinet\\Host\\" + Host)); 
					Machine::AddRegKey(HKEY_CURRENT_USER, 
						_S(L"Software\\\\Cabinet\\Host\\" + Host + L"\\" + IpStr)); 
				}
				_Catch() 
			}

			inline void FindIp() 
			{
				try
				{
					HostIp = Host;
					return;
					//
					SharedArray<string> Ips = DNSUtil::ResolveHost(Host); 
					if (Ips.Length() == 0) throw MethodError(L"�� ������� ���������� ����� ���� " + Host); 
					//
					// ��������� IP-������� 
					//
					for (int k = 0; k < Ips.Length(); ++k) 
					{
						string IpStr = Ips[k]; 
						// 
						CheckIpInfo(IpStr); 
					}
					//
					// ����� ������ 
					//
					string IpStr = Ips[0]; 
					//
				}
				_Catch()
			}

			inline void SetHost(const string& host,int port)
			{
				try
				{
					Host = host;
					Port = port;
					//
					FindIp(); 
				}
				_Catch() 
			}
		};








		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		// RequestData 

		class RequestData
		{
			// -----------------------------------------------------------------------------------
			// Default connection 

			static Agent& DefaultAgent()
			{
				static Agent s_DefaultAgent(_DEFAULT_AGENT); 
				//
				return s_DefaultAgent;
			}

			SharedPtr<Connection> m_pDefaultConnection; 

			// -----------------------------------------------------------------------------------
			// Connection

			Connection* m_pConnection; // weak 

			SharedPtr<Uri> m_pLocation;


		public:
			// -----------------------------------------------------------------------------------
			// ���������� ��������� 

			string Id;


			// -----------------------------------------------------------------------------------
			// ��������� ������� 

			string	Host;

			int		Port;


			// -----------------------------------------------------------------------------------
			// ������ ������� 

			CComPtr<IStream> PostStream; 

			int PostLength;

			string Method;

			string	Path;

			CStringA Headers; 

			string Url; 


			// -----------------------------------------------------------------------------------
			// ��������� ������� 

			HINTERNET hReq; 


			// -----------------------------------------------------------------------------------
			// ��������� ������� 

			string HttpStatusStr;

			int HttpStatus;

			// Headers 

			Map<string,string> ResponseHeaders; 

			// �������������� ����� �� ������ UrlCacheEntry 

			CString OutPath; 

			CComPtr<IStream> OutStream;

			string OutContentType; 

			bool OutputIsDownloaded; 



		protected:
			// -----------------------------------------------------------------------------------
			// ������������ 

			inline void SetConnectionTo(Connection& connection) 
			{
				m_pConnection = &connection;
			}

			inline void SetConnectionToDefault() 
			{
				SetConnectionTo(DefaultConnection());
			}

		public:
			RequestData() : hReq(0), 
				m_pConnection(0), 
				PostLength(0), 
				OutputIsDownloaded(false), 
				HttpStatus(_HTTP_STATUS_UNKNOWN) // unknown 
			{
				SetConnectionToDefault();
			}

			RequestData(Connection& connection) : hReq(0), 
				m_pConnection(0), 
				PostLength(0), 
				OutputIsDownloaded(false), 
				HttpStatus(_HTTP_STATUS_UNKNOWN) // unknown 
			{
				SetConnectionTo(connection); 
			}

			inline void Close() 
			{
				try
				{
					GetConnection().UnregisterRequest(Id); 
				}
				_Catch()
			}

			~RequestData()
			{
			}

			// �������� 

			inline void SetLocation(const string& url) 
			{
				Url = url; 
				m_pLocation = new Uri(ParseMethodUrl,url); 
			}

			inline Uri& Location()
			{
				try
				{
					if (m_pLocation.IsEmpty()) 
					{
						throw MethodError(L"������ Web:101"); 
						//throw MethodError(E_POINTER); 
					}
					return *m_pLocation;
				}
				_Catch()
			}

			inline void SetHttpStatus(int status)
			{
				try
				{
					HttpStatus = status;
					HttpStatusStr = FormatStr(L"%d", (int)HttpStatus );
				}
				_Catch()
			}

			inline Connection& GetConnection() 
			{
				try
				{
					if (! m_pConnection) throw MethodError(L"�������� Connection �� ������");
					//
					return *m_pConnection;
				}
				_Catch() 
			}

		protected:
			inline Connection& DefaultConnection()
			{
				if (! m_pDefaultConnection)
				{
					m_pDefaultConnection = new Connection(DefaultAgent()); 
				}
				return *m_pDefaultConnection; 
			}
			
		public:
			// ----
			// POST

			inline void SetPostStream(IStream* stream)
			{
				try
				{
					if (PostStream)
					{
						if ( ((IStream*)PostStream) == stream ) return; // ���������
						//
						PostStream.Release();
					}
					//
					if (stream)
					{
						CComQIPtr<IStream> s2(stream);
						PostStream.Attach(s2.Detach());
					}
				}
				_Catch()
			}

			inline static void FreeSTATSTG(STATSTG& stg)
			{
				if (stg.pwcsName)
				{
					CoTaskMemFree(stg.pwcsName);
				}
			}

			int GetPostLength()
			{
				try
				{
					if (! PostStream) return 0; 
					//
					STATSTG stg;
					ZeroMemory(&stg,sizeof(stg));
					try
					{
#						ifdef _DEBUG
						{
							CComQIPtr<ISlotFileReader> fr(PostStream); 
							if (fr)
							{
								CComBSTR bstrPath; 
								HRESULT rc = fr->get_Path(&bstrPath); 
								if (FAILED(rc)) throw MethodError(rc); 
								TRACE_LINE1(_T("��������� ������ ��������� ������: "), _S(bstrPath).GetString() ); 
							}
							else
							{
								TRACE_LINE(_T("��������� ������ ������������ ������")); 
							}
						}
#						endif
						//
						HRESULT rc = PostStream->Stat(&stg,STATFLAG_NONAME);
						if (FAILED(rc)) 
						{
							throw MethodError(rc);
						}
						//
						__int64 size = stg.cbSize.LowPart | (((__int64)stg.cbSize.HighPart) << 32); 
						//
						FreeSTATSTG(stg);
						//
#						ifdef _DEBUG
						{
							TRACE_LINE1(_T("������: %d"), (int)size ); 
						}
#						endif
						return (int)size;
					}
					catch(...)
					{
						FreeSTATSTG(stg);
						//
						throw;
					}
				}
				_Catch()
			}

			// ----
			// Response 

		public:
			inline void ClearResponseData()
			{
				OutputIsDownloaded = false; 
				//
				OutPath = _T(""); 
				//
				if (OutStream) OutStream.Release(); 
			}

			// Output Stream

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
						if (! q) 
						{
							throw MethodError(L"������ Web:102"); 
							//throw MethodError(E_NOINTERFACE);
						}
						OutStream.Attach(q.Detach());
					}
				}
				_Catch()
			}

			// File 
			
			inline void SetOutFile(const CString& path)
			{
				try
				{
					ClearResponseData(); 
					//
					OutPath = path;
					//
					CComPtr<ISlotFileReader> fr;
					fr.Attach( 
						CSlotFileReader::Create<ISlotFileReader>() // new reference 
						);
					SetOutStream((ISlotFileReader*)fr); 
				}
				_Catch() 
			}
		};













		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		// Request 

		class Request 
		{
		public:
			RequestData R;
			
		public:
			inline Connection& GetConnection()
			{
				return R.GetConnection(); 
			}

			// ������������ 

			inline void SetData(IStream* pSs)
			{
				R.SetPostStream(pSs); 
			}

			inline void Init(IStream* pSs=0)
			{
				try
				{
					SetData(pSs); 
					//
					// Request 
					//
					if (R.Method.GetLength() == 0)
					{
						// ���������� ������������� 
						//
						if (R.PostStream) // ���� ����� ������ ��� �������� �� ������ 
						{
							R.Method = L"POST"; 
						}
						else 
						{
							R.Method = L"GET"; 
						}
					}
					//
					R.Path = R.Location().GatePath;
					R.Host = R.Location().Host;
					R.Port = R.Location().Port;
					//
					R.Id = NewGuidStr(); 
					//
					// Connection
					//
					GetConnection().RegisterRequest(R.Id);
					if (GetConnection().HostIp.GetLength() == 0) // Connection ��������� ���������� � ������� 
					{
						GetConnection().SetHost(R.Host,R.Port); 
					}
					// 
					// Sending
					//
					OpenFlags = DefaultOpenFlags();
					//
					// �������������� ��������� ���������� 
					//
					R.ClearResponseData(); 
				}
				_Catch()
			}

			Request(Connection& connection,const string& url) 
				: R(connection) 
			{
				try
				{
					R.SetLocation(url);
					Init();
				}
				_Catch()
			}

			Request(Connection& connection,const string& url,IStream* pSs) 
				: R(connection) 
			{
				try
				{
					R.SetLocation(url);
					Init(pSs);
				}
				_Catch()
			}

			Request(const string& url) // default Connection 
			{
				try
				{
					R.SetLocation(url);
					Init();
				}
				_Catch()
			}

			Request(const string& url,IStream* pSs) // default Connection 
			{
				try
				{
					R.SetLocation(url);
					Init(pSs);
				}
				_Catch()
			}

			void Close()
			{
				try
				{
					R.Close();
				}
				_Catch()
			}

			~Request()
			{
			}



			// ----
			// �������� ������� 

			DWORD OpenFlags;

			DWORD DefaultOpenFlags()
			{
				DWORD openFlags = 0; 
				return openFlags;
			}

			DWORD CabinetGateOpenFlags()
			{
				DWORD openFlags = INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_AUTO_REDIRECT; 
				return openFlags;
			}

			inline Request& ReloadAlways()
			{
				OpenFlags = OpenFlags | INTERNET_FLAG_RELOAD; 
				return *this;
			}

			inline Request& NoAutoRiderect()
			{
				OpenFlags = OpenFlags | INTERNET_FLAG_NO_AUTO_REDIRECT;
				return *this;
			}

			void FinishRequest() // ��������� ���������� 
			{
			}

			int WritePostStream(int len)
			{
				try 
				{
					if (len == 0) len = R.GetPostLength(); 
					//
					if ((len == 0) || (! R.PostStream)) return 200; // ������! ��� ������ 
					//
#					ifdef _PROTOCOL_TRACE_EVENTS
					TRACE_LINE(_T("WritePostStream: start"));
#					endif
					//
					int step = 0; 
					//
					LARGE_INTEGER m0; 
					m0.QuadPart = 0; 
					ULARGE_INTEGER libNewPos; 
					HRESULT rc = R.PostStream->Seek(m0,FILE_BEGIN,&libNewPos); 
					if (FAILED(rc)) 
					{
						throw MethodError(L"������ Web:103 (���������������� IStream)"); 
						//throw MethodError(rc); 
					}
					//
					const int chunkSize = 2 * 1024; 
					bool done = false;
					do
					{
						++step;
						if (step == 128 * 1024)
						{
							throw MethodError(FormatStr(L"��������� ���������� ����� ����� ������ (%d)",(int)step)); 
						}
						//
						Blob b;
						b.Expand(chunkSize); 
						ULONG bytesRead = chunkSize;
						//
#						ifdef _PROTOCOL_TRACE_EVENTS
						//TRACE_LINE1(_T("WritePostStream: reading %d bytes"), (int)chunkSize );
#						endif
						//
						HRESULT r1 = R.PostStream->Read(b.GetBuffer(),chunkSize,&bytesRead); 
						//
#						ifdef _PROTOCOL_TRACE_EVENTS
						//TRACE_LINE1(_T("WritePostStream:     got %d bytes"), (int)bytesRead ); 
						//OutputDebugString(_S(CStringA((char*)b.GetBuffer(),bytesRead))); 
#						endif
						//
						if (r1 == S_FALSE)
						{
#							ifdef _PROTOCOL_TRACE_EVENTS
							//TRACE_LINE(_T("WritePostStream: --> S_FALSE"));  
#							endif
							//
							done = true; 
						}
						else if ((r1 == S_OK) || (r1 == E_PENDING))
						{
							//if (r1 == S_OK) TRACE_LINE(_T("WritePostStream: --> S_OK")); 
							//if (r1 == E_PENDING) TRACE_LINE(_T("WritePostStream: --> E_PENDING")); 
							if (bytesRead > 0) 
							{
								b.SetSize(bytesRead); 
								//
								DWORD bytesWritten = b.Length(); 
								//
#								ifdef _PROTOCOL_TRACE_EVENTS
								//TRACE_LINE(_T("WritePostStream: InternetWriteFile(")); 
#								endif
								//
								if (! InternetWriteFile(R.hReq,b.GetBuffer(),bytesRead,&bytesWritten)) 
								{
									//TRACE_LINE(_T(")")); 
									DWORD dwErr = GetLastError(); 
									if (dwErr == 12019)
									{
										int status = 407; 
										return status; 
									}
									throw MethodError(FormatStr(L"�� ������� ��������� ������: %d", (int)dwErr )) ; 
								}
								else
								{
#									ifdef _PROTOCOL_TRACE_EVENTS
									//TRACE_LINE(_T(")")); 
#									endif
								}
								if (bytesWritten != bytesRead) 
								{
									throw MethodError(L"������ Web:104"); 
									//throw MethodError(E_UNEXPECTED); 
								}
							}
							else // �������, ��� ������ ������ ������! 
								 // ��� ��������� �������� ���������� IStream � Internet-���������� 
							{
								if (r1 == S_OK)
								{
#									ifdef _PROTOCOL_TRACE_EVENTS
									//TRACE_LINE(_T("WritePostStream: --> S_OK, but 0 bytes Read ~ S_FALSE")); 
#									endif
									//
									done = true; 
								}
							}
						}
						else if (FAILED(r1))
						{
							throw MethodError(r1).AddIfNewSource_(L"������ ������ ������ ��� �������� �� ������"); 
						}
					}
					while(! done);
					//
#					ifdef _PROTOCOL_TRACE_EVENTS
					//TRACE_LINE(_T("WritePostStream: end"));
#					endif
					//
					return 200;
				}
				_Catch() 
			}

			inline Request& SetMethod(const string& meth)
			{
				R.Method = meth; 
				return *this; 
			}

			inline int GetPort()
			{
				return R.Location().Port; 
			}



			// ===================================================================================
			// ��������� ������� � ����� 

			inline void SetResponseHeader(const string& name,const string& headerValue)
			{
				try
				{
					R.ResponseHeaders[name] = headerValue; 
				}
				_Catch() 
			}

			int SendRequest()
			{
				try
				{
					R.OutputIsDownloaded = false; 
					//
					// ��������� ������ 
					//
#					ifdef _PROTOCOL_TRACE_EVENTS
					TRACE_LOG(_S(L"SENDING: ") + _S(R.Location().Path));
#					endif
					//
					if (R.Location().Protocol == L"file") 
					{
						R.SetHttpStatus(200);
						//
						string path = R.Location().Path; 
						const string filePrefix = L"file://";
						if (path.Left(filePrefix.GetLength()) == filePrefix) 
						{
							path = path.Right(path.GetLength() - filePrefix.GetLength()); 
						}
						path.Replace(L"|",L"");
						path.Replace(L"/",L"\\");
						R.SetOutFile(_S(path)); 
					}
					else // ��������-��������� 
					{
#						ifdef _DEBUG
						{
							TRACE_LOG2(_T("!!! Web connection Host, Port: %s, %d"), _S(R.GetConnection().HostIp).GetString(), (int)R.GetConnection().Port );
						}
#						endif
						//
						// Open
						//
#						ifdef _PROTOCOL_TRACE_EVENTS
						//TRACE_LINE(_T("WEB 1"));
#						endif
						//
						R.GetConnection().OpenIfNotYet();
						//
						HINTERNET hC = R.GetConnection().hConnect;
						if (! hC)
						{
							throw MethodError(L"����������� hConnect");
						}
						//
						if (R.GetConnection().SecureStatus == 1)
						{
							if (R.GetConnection().Port != 80)
							{
								OpenFlags = OpenFlags | 
									INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_CN_INVALID; 
							}
						}
						else if (R.GetConnection().SecureStatus == 2)
						{
							OpenFlags = OpenFlags | 
								INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_CN_INVALID; 
						}
						//
						//TRACE_LINE(_T("WEB 2"));
						if (R.Method == L"POST")
						{
							OpenFlags = OpenFlags | INTERNET_FLAG_NO_CACHE_WRITE; 
						}
						//
						R.hReq = HttpOpenRequest(hC,_S(R.Method),_S(R.Path),NULL,
							NULL,NULL,OpenFlags,NULL);
						if (! R.hReq)
						{
							string errorMsg = L"���������� ���������� ���������� � ��������: " + 
								_W(R.Method) + L", " + _W(R.Path) + 
								L", " + FormatStr(L"0x%x",(int)OpenFlags); 
							throw MethodError(errorMsg); 
							//throw LastInternetError(); 
						}
						//
						// ����� 
						//
						Agent().SetOptionTo(R.hReq,INTERNET_OPTION_CONNECT_TIMEOUT
							,L"web-connect-timeout"); 
						//Agent().SetOptionTo(R.hReq,INTERNET_OPTION_FROM_CACHE_TIMEOUT 
						//	,L"web-fromcache-timeout"); 
						//Agent().SetOptionTo(R.hReq,INTERNET_OPTION_RECEIVE_TIMEOUT 
						//	,L"web-receive-timeout"); 
						//Agent().SetOptionTo(R.hReq,INTERNET_OPTION_RECEIVE_TIMEOUT 
						//	,L"web-receive-timeout"); 
						//Agent().SetOptionTo(R.hReq,INTERNET_OPTION_SEND_TIMEOUT 
						//	,L"web-send-timeout"); 
						//
						// Proxy 
						//
						//UseProxy(); 
						//
						// Send
						//
						int len = R.GetPostLength(); 
						//
						Blob b;
						b.Allocate(16*1024); 
						ZeroMemory(b.GetBuffer(),b.Length()); 
						//
						//TRACE_LINE(_T("WEB 5"));
						INTERNET_BUFFERS* pBuffer = (INTERNET_BUFFERS*)b.GetBuffer(); 
						//
#						ifdef _DEBUG
						{
							// TEST: 
							// R.Headers = "Content-Type: text/xml\r\nX--ClientCertificate: CERTIFICATE"; 
						}
#						endif
						//
						//TRACE_LINE(_T("WEB 6"));
						pBuffer->dwStructSize  = sizeof(INTERNET_BUFFERS); 
						pBuffer->Next = NULL;
						pBuffer->lpcszHeader = 
							R.Headers.GetLength() > 0 ? R.Headers.GetString() : 0;///szContentType;
						pBuffer->dwHeadersLength = 
							R.Headers.GetLength() > 0 ? R.Headers.GetLength() : 0;///sizeof(szContentType);
						pBuffer->dwHeadersTotal = 
							R.Headers.GetLength() > 0 ? R.Headers.GetLength() : 0;///sizeof(szContentType);
						pBuffer->lpvBuffer = NULL;
						pBuffer->dwBufferLength = 0;
						pBuffer->dwBufferTotal = len;
						pBuffer->dwOffsetLow = 0;
						pBuffer->dwOffsetHigh = 0;
						//
						////string errorMsg; 
						////errorMsg += L", Headers=" + _W(R.Headers); 
						//////
						////throw MethodError(errorMsg); 
						//
						//TRACE_LINE(_T("WEB 7"));
						if (! HttpSendRequestEx(R.hReq,pBuffer,0,0,0)) // R.GetPostLength() 
						{			
							DWORD dwErr = GetLastError(); 
							string errorMsg = L"������ ��� �������� ������� �� ������: " +   
								FormatStr(L"%d",(int)dwErr); 
							//
							if (dwErr == 12150) 
							{
								errorMsg += 
									FormatStr(L"{dwStructSize=%d, dwBufferTotal=%d", 
										(int)pBuffer->dwStructSize, (int)pBuffer->dwBufferTotal ) + 
									L", Headers=" + _W(R.Headers); 
							}
							//
							throw MethodError(errorMsg); 
							//throw MethodError(INTERNET_ERROR(dwErr)); 
						}
						//
						{
							DWORD dwCode; 
							DWORD dwSize; 
							HttpQueryInfo(R.hReq, 
								HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, 
								&dwCode, &dwSize, NULL);
							//
#							ifdef _DEBUG
							{
								TRACE_LOG(FormatStr(_T("STATUS: %d"), (int)dwCode ));
							}
#							endif
							//
							if (dwCode == HTTP_STATUS_PROXY_AUTH_REQ) 
							{
								//UseProxy(); 
								//
								DWORD dw1;
								do 
								{
									dw1 = InternetErrorDlg (GetDesktopWindow(),
										  R.hReq, ERROR_INTERNET_INCORRECT_PASSWORD,
										  FLAGS_ERROR_UI_FILTER_FOR_ERRORS |
										  FLAGS_ERROR_UI_FLAGS_GENERATE_DATA |
										  FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS, 
										  NULL);
									//
									if (dw1 == ERROR_INTERNET_FORCE_RETRY)
									{
										if (! HttpSendRequestEx(R.hReq,pBuffer,0,0,0)) // R.GetPostLength() 
										{			
											DWORD dwErr = GetLastError(); 
											string errorMsg = L"������ ��� �������� ������� �� ������: " +
												FormatStr(L"%d",(int)dwErr);
											throw MethodError(errorMsg); 
											//throw MethodError(INTERNET_ERROR(dwErr)); 
										}
									}
								}
								while (dw1 == ERROR_INTERNET_FORCE_RETRY);
								//
								//
								HttpQueryInfo(R.hReq, 
									HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, 
									&dwCode, &dwSize, NULL);
								//
#								ifdef _DEBUG
								TRACE_LOG1(_T("HTTP status: %d"), (int)dwCode ); 
#								endif
							}
						}
						//
						TRACE_LINE(_T("WEB 8"));
						if (len > 0) 
						{
							int wStatus = WritePostStream(len); 
							if (wStatus == 407)
							{
								R.SetHttpStatus(wStatus); 
								return wStatus; 
							}
						}
						//
						TRACE_LINE(_T("WEB 9"));
						int step = 0;
						bool closed = false;
						do
						{
							if (! HttpEndRequest(R.hReq,0,0,0)) 
							{
								DWORD dwErr = GetLastError(); 
								//
#								ifdef _DEBUG
								TRACE_LOG1(_T("WinInet error %d"), (int)dwErr);
#								endif
								//
								if (dwErr == 12019)
								{
									int status = 407; 
									R.SetHttpStatus(status); 
									return status; 
								}
								else if (dwErr == 12032) 
								{
									step++;
									if (step == 10) closed = true; 
								}
								else 
								{
									string errorMsg = L"������ ��� �������� ������� �� ������: " + 
										FormatStr(L"%d",(int)dwErr); 
									//
									throw MethodError(errorMsg); 
									//
									//if (dwErr < 12000) 
									//{
									//	HRESULT rc = HRESULT_FROM_WIN32(dwErr); 
									//	throw MethodError(rc); 
									//}
									//throw MethodError(INTERNET_ERROR(dwErr)); 
								}
							}
							else
							{
								closed = true; 
							}
						}
						while (! closed);
						//TRACE_LINE(_T("WEB 15")); 
						//
						//
						//
						// -----------------------------------------------------------------------
						// ����� 
						//
						//
						// ----
						// HTTP_QUERY_STATUS_CODE 
						//
						//TRACE_LINE(_T("WEB 16"));
						DWORD dwStatusCode = 0; 
						{
							DWORD dwSize = sizeof(dwStatusCode);
							if (! HttpQueryInfo(R.hReq,
								HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
								&dwStatusCode,&dwSize,NULL))
							{
								DWORD dwErr = GetLastError(); 
								throw MethodError(INTERNET_ERROR(dwErr)); 
							}
							R.SetHttpStatus(dwStatusCode);
						}
						//
						//
						// ----
						// HTTP_QUERY_STATUS_TEXT
						//
						//TRACE_LINE(_T("WEB 17"));
						string statusText;
						{
							char text[1024]; text[0] = 0;
							DWORD textSize = 1024;
							if (! HttpQueryInfo(R.hReq,HTTP_QUERY_STATUS_TEXT,text,&textSize,NULL)) 
							{
								DWORD dwErr = GetLastError();
								if (dwErr != ERROR_HTTP_HEADER_NOT_FOUND)
								{
									HRESULT rc = INTERNET_ERROR(dwErr);
									throw MethodError(rc); 
								}
							}
							//
							//TRACE_LINE(_T("WEB 18"));
							SetResponseHeader(
								_PROTOCOL_RSP_HEADER_STATUS_TEXT, // ���������� �2 ��������� 3� 
								_W(text));
						}
						//
						if (dwStatusCode == 304) 
						{
							return dwStatusCode; 
						}
						//
						//
						// ----
						// HTTP_QUERY_CONTENT_TYPE 
						//
						//TRACE_LINE(_T("WEB 19"));
						{
							DWORD contentTypeSize = 256;
							CBlobA contentTypeData;
							contentTypeData.Allocate(contentTypeSize);
							if (! HttpQueryInfo(R.hReq,HTTP_QUERY_CONTENT_TYPE ,
								(void*)contentTypeData.GetBuffer(),&contentTypeSize,NULL))
							{
								throw LastInternetError(); 
							}
							R.OutContentType = 
								CString(CStringA(contentTypeData.GetBuffer(),contentTypeSize)); 
						}
						//					
						//
						// ----
						// HTTP_QUERY_CONTENT_ENCODING 
						//
						//TRACE_LINE(_T("WEB 20"));
						{
							DWORD contentEncodingSize = 256;
							CBlobA contentEncodingData;
							contentEncodingData.Allocate(contentEncodingSize);
							if (! HttpQueryInfo(R.hReq,HTTP_QUERY_CONTENT_ENCODING ,
								(void*)contentEncodingData.GetBuffer(),&contentEncodingSize,NULL)) 
							{
								DWORD dwErr = GetLastError();
								if (dwErr == 12150)
								{
									contentEncodingData.Free();
								}
								else
								{
									HRESULT rc = INTERNET_ERROR(dwErr); 
									throw rc; 
								}
							}
							CString contentEncoding;
							if (! contentEncodingData.IsEmpty())
								contentEncoding = 
									CString(CStringA(contentEncodingData.GetBuffer(),contentEncodingSize));
						}
						//
						//
						// ----
						// HTTP_QUERY_RAW_HEADERS_CRLF
						//
						//TRACE_LINE(_T("WEB 21"));
						{
							Blob headerData;
							DWORD headerDataSize = 2*1024;
							headerData.Expand(headerDataSize); 
							if (! HttpQueryInfo(R.hReq,HTTP_QUERY_RAW_HEADERS_CRLF,
								headerData.GetBuffer(),&headerDataSize,NULL))
							{
								DWORD dwErr = GetLastError();
								DWORD insuf_buf = ERROR_INSUFFICIENT_BUFFER; 
								if (dwErr == insuf_buf)
								{
									headerData.Expand(headerDataSize);
									//
									if (! HttpQueryInfo(R.hReq,HTTP_QUERY_RAW_HEADERS_CRLF,
										headerData.GetBuffer(),&headerDataSize,NULL))
									{
										DWORD dwErr = GetLastError();
										{
											HRESULT rc = INTERNET_ERROR(dwErr);
											throw MethodError(rc); 
										}
									}
								}
								else
								{
									HRESULT rc = INTERNET_ERROR(dwErr);
									throw MethodError(rc); 
								}
							}
							headerData.SetSize(headerDataSize); 
							//
//////							CComPtr<ISlotMultipartReader> mpReader;
//////							mpReader.Attach(
//////								CSlotMultipartReader::Create<ISlotMultipartReader>() // new reference 
//////								);
//////							if (! mpReader) throw MethodError(E_UNEXPECTED); 
//////							//
//////							HRESULT rc = mpReader->OpenData(headerData.GetBuffer(),headerData.Length()); 
//////							if (FAILED(rc)) throw MethodError(rc); 
//////							//
//////							HRESULT iteration = S_FALSE;
//////							int i = 0;
//////							CComBSTR bstrHeaderName;
//////							CComVariant vHeaderDescription;
//////							CComVariant vHeaderData;
//////							//
//////							while (
//////								(iteration = mpReader->GetHeader(i,
//////									&bstrHeaderName,&vHeaderDescription,&vHeaderData))
//////								== S_OK)
//////							{
//////								if (FAILED(iteration)) throw MethodError(iteration); 
//////								//
//////#								ifdef _DEBUG
//////								{
//////									TRACE_LOG(_S("header: ") + _S(bstrHeaderName)); 
//////								}
//////#								endif
//////								//
//////							}
							//							
							CStringA rawHeaderA((const char*)headerData.GetBuffer(),headerData.Length()); 
							int p_1 = rawHeaderA.Find(
								_A(_PROTOCOL_RSP_HEADER_RECEIPT_NEEDED) + ":"); 
							if (p_1 != -1) 
							{
								SetResponseHeader(_PROTOCOL_RSP_HEADER_RECEIPT_NEEDED,L"1"); 
							}
							//
							// All Headers 
							{
								while (rawHeaderA.GetLength() > 0)
								{
									int p_0 = rawHeaderA.Find("\n"); 
									//
									string item;
									//
									if (p_0 == -1)
									{
										item = _W(rawHeaderA); 
										rawHeaderA = "";
									}
									else
									{
										item = _W(rawHeaderA.Left(p_0)); 
										rawHeaderA = rawHeaderA.Right(rawHeaderA.GetLength()-p_0-1); 
									}
									item.Trim(); 
									//
									string headerName;
									string headerValue; 
									//
									int p_colon = item.Find(L":"); 
									if (p_colon == -1)
									{
										headerName = item; 
									}
									else
									{
										headerName = item.Left(p_colon); 
										headerValue = item.Right(item.GetLength()-p_colon-1); 
									}
									headerName.Trim();
									headerValue.Trim();
									//
									if (headerName.GetLength() > 0)   
									{
										SetResponseHeader(headerName, headerValue); 
									}
								}
							}
						}
						//
						//
						//
						// ----
						// ��������� �������� � ��������� �� ��������� ����� 
						//
						// SlotFileReader 
						//
						//TRACE_LINE(_T("WEB 22"));
						//
						CComPtr<ISlotFileReader> reader; 
						reader.Attach(
							CSlotFileReader::Create<ISlotFileReader>() // new reference 
							); 
						if (! reader) throw MethodError(E_UNEXPECTED); 
						//
						//string cacheUrl = R.Location().ReferenceUrl;
						//int p1 = cacheUrl.ReverseFind(L'/');
						//if (p1 != -1) cacheUrl = 
						//	cacheUrl.Left(p1) + _W(NewGuidStr()) + L"." + R.Location().Extension; 
						//
#						ifdef _DEBUG
						{
							TRACE_LOG1(_S("R.Url %s"), _S(R.Url).GetString() ); 
							TRACE_LOG1(_S("R.Location().ResourceFile %s"), _S(R.Location().ResourceFile).GetString() ); 
						}
#						endif
						//
						string cacheUrl = R.Url; 
						string cacheFileName = R.Location().ResourceFile; 
						//
						//TRACE_LINE(_T("WEB 23"));
						//
						HRESULT rc = reader->SetCacheUrlExt(
							CComBSTR(cacheUrl) 
							,CComBSTR(cacheFileName)
							);
						if (FAILED(rc)) throw MethodError(rc); 
						//
						try
						{
							rc = reader->WriteOpen();
							if (FAILED(rc)) throw MethodError(rc); 
							//
							CComQIPtr<IStream> writeStream(reader); 
							if (! writeStream) throw MethodError(E_UNEXPECTED); 
							//
							/// InternetQueryDataAvailable(R.hReq,&dwSize,0,0);
							//
							/// int chunkSize = 4 * 1024; 
							DWORD dwSize = 0;
							int pos = 0;
							//
							do
							{
								dwSize = 0;
								if (! InternetQueryDataAvailable(R.hReq,&dwSize,0,0)) 
								{
									throw LastInternetError();
								}
								Blob buf;
								buf.Expand(dwSize+1); 
								ZeroMemory(buf.GetBuffer(),dwSize+1);
								//
								DWORD bytesRead = 0; 
								//
								if (! InternetReadFile(R.hReq,(LPVOID)buf.GetBuffer(),dwSize,&bytesRead))
								{
									throw LastInternetError();
								}
								buf.SetSize(bytesRead); 
								//
								if (bytesRead > 0)
								{
									ULONG bytesWritten = 0; 
									HRESULT r1 = writeStream->Write(buf.GetBuffer(),bytesRead,&bytesWritten); 
									if (FAILED(r1)) throw MethodError(r1); 
									//
									if (bytesWritten != bytesRead) throw MethodError(E_UNEXPECTED); 
									//
									pos += bytesRead;
								}
							} 
							while (dwSize > 0);
							//
							rc = reader->WriteClose(); 
							if (FAILED(rc)) throw MethodError(rc); 
						}
						catch(...)
						{
#							ifdef _DEBUG
							{
								TRACE_LOG(L"�� ������� �������� ����:\n" + cacheUrl + L"\n" + cacheFileName); 
							}
#							endif
						}
						//TRACE_LOG(_T("WEB 30"));
						//
						CComBSTR bstrUrlCachePath_1;
						rc = reader->get_Path(&bstrUrlCachePath_1); 
						if (FAILED(rc)) throw MethodError(rc); 
						//
#ifdef _DEBUG
						{
							TRACE_LOG1(_S("bstrUrlCachePath_1 %s"), _S(_W(bstrUrlCachePath_1)).GetString() ); 
						}
#endif
						//
						// ----
						// ������ ���� ��� ������ 
						//
						CComPtr<ISlotFileReader> reader2; 
						reader2.Attach(
							CSlotFileReader::Create<ISlotFileReader>() // new reference 
							); 
						if (! reader2) throw MethodError(E_UNEXPECTED); 
						//
						rc = reader2->SetCacheUrlExt(
							CComBSTR(cacheUrl) 
							,CComBSTR(cacheFileName)
							);
						if (FAILED(rc)) 
						{
							throw MethodError(rc); 
						}
						//
						rc = reader2->Open(); 
						if (FAILED(rc)) 
						{
							throw MethodError(rc); 
						}
						//
						//
						////// ----
						////// ������ ���� ��� ������ 
						//////
						////CComPtr<ISlotFileReader> reader2; 
						////reader2.Attach(
						////	CSlotFileReader::Create<ISlotFileReader>() // new reference 
						////	); 
						////if (! reader2) throw MethodError(E_UNEXPECTED); 
						//////
						////string cacheUrl_2 = R.Url.Find(L"?") != -1 ? R.Url + L"&_content_=read"
						////	: R.Url + L"?_content_=read"
						////	; 
						//////
						////rc = reader2->SetCacheUrlExt(
						////	CComBSTR(cacheUrl_2) 
						////	,CComBSTR(cacheFileName)
						////	);
						////if (FAILED(rc)) throw MethodError(rc); 
						//////
						////rc = reader2->WriteSetOpen(); 
						////if (FAILED(rc)) throw MethodError(rc); 
						//////
						////CComBSTR bstrUrlCachePath_2; 
						////rc = reader2->get_Path(&bstrUrlCachePath_2);      
						////if (FAILED(rc)) throw MethodError(rc); 
						//////
						////if (! CopyFile(_S(bstrUrlCachePath_1),_S(bstrUrlCachePath_2),FALSE)) 
						////{
						////	HRESULT rc1 = HRESULT_FROM_WIN32(GetLastError()); 
						////	TRACE_LOG1(_S("������ ����������� 0x%x"), (int)rc1 ); 
						////}
						//////
						////if (! Machine::FileExists(_S(bstrUrlCachePath_2)))
						////{
						////	throw MethodError(_W("�� ������� ����������� ����: ") + _W(bstrUrlCachePath_2)); 
						////}
						//////
						////rc = reader2->WriteClose(); 
						////if (FAILED(rc)) throw MethodError(rc); 
						//////
						////rc = reader2->Open(); 
						////if (FAILED(rc)) throw MethodError(rc); 
						//
						// �������������� ������
						//
						//TRACE_LOG(_T("WEB 31"));
						CComQIPtr<IStream> outStream(reader2); 
						if (! outStream) 
						{
							throw MethodError(E_UNEXPECTED); 
						}
						//
						//TRACE_LOG(_T("WEB 32"));
						R.SetOutStream<IStream>(outStream); 
						//TRACE_LOG(_T("WEB 33"));
					}
					//
#					ifdef _DEBUG
					{
						if (R.HttpStatus != 200 && R.HttpStatus != 404)
						{
							TRACE_LOG1(_T("HTTP Status %d"), (int)R.HttpStatus ); 
						}
					}
#					endif
					//
					return R.HttpStatus;
				}
				_Catch()
			}

			int Send() // ���������� HttpStatus		
			{
				try
				{
					if (R.HttpStatus == 0) // ������ ��� �� ����������, ���������! 
					{
						return SendRequest();
					}
					//
					return R.HttpStatus;
				}
				_Catch()
			}

			inline ISequentialStream* GetResponseStream() 
			{
				try
				{
					Send(); // ��������� ������� �� ������, ��� ��� � ����� ������ ������������ 
							// ���������� --- ����� web-�������. 
					//
					if (R.OutputIsDownloaded)
					{
						throw MethodError(L"����� ��� ������"); 
					}
					//
					return R.OutStream; 
				}
				_Catch() 
			}



			// ----
			// Response as Text 

			inline string GetResponseAsText() 
			{
				try
				{
					if (R.OutputIsDownloaded)
					{
						throw MethodError(L"����� ��� ������"); 
					}
					//
					// �������������� ������ 
					//
					ISequentialStream* stream = GetResponseStream(); 
					//
					// ������ ����� 
					//
					Blob responseData;
					bool done;
					do
					{
						done = false;
						//
						int ds = 1024;
						int n = responseData.Length(); 
						responseData.Expand(n + ds);
						ULONG bytesRead = 0;
						HRESULT rc = stream->Read(responseData.GetBuffer() + n,(ULONG)ds,&bytesRead); 
						if (rc == E_PENDING)
						{
							// ���...
						}
						else if (FAILED(rc))
						{
							throw MethodError(rc); 
						}
						else 
						{
							responseData.SetSize(n + (int)bytesRead);
							//
							if (rc == S_FALSE)
							{
								done = true;
							}
						}
					}
					while (! done);
					//
					// �������� ����� �������� (ASCII) 
					//
					CStringA a((const char*)responseData.GetBuffer(),responseData.Length()); 
					string text(a);
					//
					R.OutputIsDownloaded = true; 
					//
					return text; 
				}
				_Catch()
			}

			inline string ParseRedirectUrl() 
			{
				try
				{
					string text = GetResponseAsText(); 
					//
					string url = text; 
					//
					return url; 
				}
				_Catch()
			}

			inline void UseProxy() 
			{
				try
				{
					HINTERNET h = this->GetConnection().hConnect; 
					//
					string proxyUserName; 
					string proxyPassword; 
					::::Web::Util::GetProxyUserNameAndPassword(
						proxyUserName,proxyPassword
						);
					//
					if (proxyPassword.GetLength() == 0) 
					{
						return; 
					}
					//
					// ----
					// Using Proxy 
					//
					string proxyPasswordStr = _W(proxyPassword); 
					if (! InternetSetOption(h,
						INTERNET_OPTION_PROXY_PASSWORD,
						proxyPassword.GetBuffer(),
						proxyPassword.GetLength()*sizeof(wchar_t)
						)) 
					{
						DWORD dwErr = GetLastError();
						throw MethodError(INTERNET_ERROR(dwErr)); 
					}
					//
					string proxyUserNameStr = _W(proxyUserName); 
					if (! InternetSetOption(h,
						INTERNET_OPTION_PROXY_USERNAME,
						proxyUserName.GetBuffer(),
						proxyUserName.GetLength()*sizeof(wchar_t)
						)) 
					{
						DWORD dwErr = GetLastError();
						throw MethodError(INTERNET_ERROR(dwErr)); 
					}
				}
				_Catch() 
			}



		////	// ----
		////	// IUnknown 

		////public:
		////	STDMETHOD(QueryInterface)(REFIID iid,void** ppvObject) throw() 
		////	{
		////		if (! ppvObject) return E_POINTER;
		////		//
		////		if (iid == __uuidof(IUnknown))
		////		{
		////			*ppvObject = (void*)static_cast<IUnknown*>(this);
		////			return S_OK;
		////		}
		////		else if (iid == __uuidof(IStream))
		////		{
		////			*ppvObject = (void*)static_cast<IStream*>(this);
		////			return S_OK;
		////		}
		////		else
		////		{
		////			return E_NOINTERFACE; 
		////		}
		////	}

		////	ULONG STDMETHODCALLTYPE AddRef() throw() 
		////	{
		////		++(R.m_RefNum); 
		////		return R.m_RefNum; 
		////	}

		////	ULONG STDMETHODCALLTYPE Release() ////throw() 
		////	{
		////		try
		////		{
		////			if (R.m_RefNum == 0) throw MethodError(L"������� ����������� ������� �� ���"); 
		////			//
		////			--(R.m_RefNum); 
		////			return R.m_RefNum; 
		////		}
		////		_Catch()
		////	}



			////// ----
			////// ISequentialStream

			////STDMETHOD(Read)(
			////	void *pv,
			////	ULONG cb,
			////	ULONG *pcbRead)
			////{
			////	try
			////	{
			////		int HttpStatus = Send(); 
			////		//
			////		// ������ 
			////		//
			////		if (R.Location().Protocol == L"file") 
			////		{
			////			HRESULT rc = R.FileReader->Read(pv,cb,pcbRead);
			////			if (FAILED(rc)) throw MethodError(rc);
			////			return rc; // S_OK ��� S_FALSE 
			////		}
			////		else // ��������-��������� 
			////		{
			////			throw MethodError(E_NOTIMPL); 
			////		}
			////		//
			////		return S_OK;
			////	}
			////	_ComCatch()
			////}

			////STDMETHOD(Write)(
			////	const void* pv,
			////	ULONG cb,
			////	ULONG* pcbWritten)
			////{
			////	return E_NOTIMPL; 
			////}

			////// ----
			////// IStream

			////HRESULT STDMETHODCALLTYPE Seek( 
			////	/* [in] */ LARGE_INTEGER dlibMove,
			////	/* [in] */ DWORD dwOrigin,
			////	/* [out] */ ULARGE_INTEGER *plibNewPosition) 
			////{
			////	switch (dwOrigin)
			////	{
			////	case FILE_BEGIN:
			////		{
			////			StartRequest();
			////		}
			////		break;
			////	case FILE_CURRENT:
			////		{
			////			throw MethodError(E_NOTIMPL); 
			////		}
			////		break;
			////	case FILE_END:
			////		{
			////			throw MethodError(E_NOTIMPL); 
			////		}
			////		break;
			////	default:
			////		{
			////			throw MethodError(E_NOTIMPL); 
			////		}
			////	}
			////	//
			////	return S_OK;
			////}

			////HRESULT STDMETHODCALLTYPE SetSize( 
			////	/* [in] */ ULARGE_INTEGER libNewSize) 
			////{
			////	return E_NOTIMPL; 
			////}

			////HRESULT STDMETHODCALLTYPE CopyTo( 
			////	/* [unique][in] */ IStream *pstm,
			////	/* [in] */ ULARGE_INTEGER cb,
			////	/* [out] */ ULARGE_INTEGER *pcbRead,
			////	/* [out] */ ULARGE_INTEGER *pcbWritten) 
			////{
			////	return E_NOTIMPL; 
			////}

			////HRESULT STDMETHODCALLTYPE Commit( 
			////	/* [in] */ DWORD grfCommitFlags) 
			////{
			////	return S_OK; // ������ �� ������ 
			////}

			////HRESULT STDMETHODCALLTYPE Revert() 
			////{
			////	return E_NOTIMPL; 
			////}

			////HRESULT STDMETHODCALLTYPE LockRegion( 
			////	/* [in] */ ULARGE_INTEGER libOffset,
			////	/* [in] */ ULARGE_INTEGER cb,
			////	/* [in] */ DWORD dwLockType) 
			////{
			////	return S_OK; // ������ �� ������ 
			////}

			////HRESULT STDMETHODCALLTYPE UnlockRegion( 
			////	/* [in] */ ULARGE_INTEGER libOffset,
			////	/* [in] */ ULARGE_INTEGER cb,
			////	/* [in] */ DWORD dwLockType) 
			////{
			////	return S_OK; // ������ �� ������ 
			////}

			////HRESULT STDMETHODCALLTYPE Stat( 
			////	/* [out] */ STATSTG *pstatstg,
			////	/* [in] */ DWORD grfStatFlag) 
			////{
			////	return E_NOTIMPL; 
			////}

			////HRESULT STDMETHODCALLTYPE Clone( 
			////	/* [out] */ IStream **ppstm) 
			////{
			////	return E_NOTIMPL; 
			////}
		};

		////typedef CComObject<Request> RequestAx;









	} // namespace Web 

} // namespace  
