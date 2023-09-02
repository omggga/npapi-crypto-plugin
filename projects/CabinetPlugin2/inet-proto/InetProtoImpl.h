
#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include <Urlmon.h>

#include <ax/coclasses/AX_SlotMemoryReader.h>
#include <ax/coclasses/AX_SlotFileReader.h>

namespace 
{
	template<
		class _Parent
	>
	class InternetProtocolImpl 
	{
	protected:
		inline Protocol::AppCtx& Instance() 
		{
			return Protocol::AppCtx::Instance(); 
		}

	public:
		typedef _Parent Parent;



		// ----
		// ������ ��������-��������� 

		bool IsMIMEFilter;							// MIME-������ ��� ������� �������� ��������? 

		DWORD GrfSTI;								// STI flags 

		PROTOCOLFILTERDATA* ProtFiltData;			// ������ (�������������) ��������� 

		CComPtr<IInternetBindInfo> iBindInfo;		// ���������� � ��������� ������� 

		DWORD BindFlags;

		BINDINFO BindInfo;

		DWORD CodePage;

		CComPtr<IStream> PostStream;

		string IncomingHeaders; 

		string IncomingContentType;					// Content-Type ��� �������

		string IncomingURL;							// �������������� URL 

		CComPtr<IInternetProtocol> IncomingProtocol;	// ��������, ���������� ������ �������� 

		// ���������

		string OutUrl;

		CString OutCachePath; 

		string OutContentType;

		CComPtr<IStream> OutStream; 

		CComQIPtr<IInternetProtocolSink> OutgoingProtocolSink;	// ��������� ��� ������ ���������� 



		// ----
		// ���������� � ��������� 

		virtual CString InternetProtocolName() =0;




		// ----
		// ������������ 

		inline void Clear()
		{
#			ifdef _PROTOCOL_TRACE_EVENTS
			{
				//TRACE_LINE(_T("[]: Clear - In"));
				//
				// {
				//		WE ARE TESTING SUPER GIT MERGE!!! 
				// }
			}
#			endif
			//
			IsMIMEFilter = false; // undefined 
			//
			IncomingURL = L"";
			IncomingContentType = L"";
			//
			GrfSTI = 0;
			ProtFiltData = 0;
			BindFlags = 0;
			ZeroMemory(&BindInfo,sizeof(BindInfo));
			//
			CodePage = CP_UTF8;
			//
			// ����� ��������� ������ 
			//
			// HRESULT r1 = 0xe00000001;
			//
			ErrorMsgPos = 0;
			m_OutStatus = 200;
			//
#			ifdef _PROTOCOL_TRACE_EVENTS
			{
				//TRACE_LINE(_T("[]: Clear - Out"));
			}
#			endif
		}

		inline void Free()
		{
#			ifdef _PROTOCOL_TRACE_EVENTS
			{
				//TRACE_LINE(_T("[]: Free - In"));
			}
#			endif
			//
			if (BindInfo.cbSize > 0)
			{
				//TRACE_LINE(_T("Free")); 
				ReleaseBindInfo(&BindInfo);
			}
			//
			if (OutgoingProtocolSink) OutgoingProtocolSink.Release();  
			//
			Clear();
			//
#			ifdef _PROTOCOL_TRACE_EVENTS
			{
				//TRACE_LINE(_T("[]: Free - Out"));
			}
#			endif
		}

		InternetProtocolImpl()
		{
			Clear();
		}

		virtual ~InternetProtocolImpl() 
		{
#			ifdef _PROTOCOL_TRACE_EVENTS
			{
				TRACE_LINE(_T("[]: ~Impl"));
			}
#			endif
		}



		// ---- 
		// ��������� ������� ������� 

		inline static string GetBindString(IInternetBindInfo *pIBindInfo,BINDSTRING bs)
		{
			try
			{
				string r;
				//
				if (! pIBindInfo) return r; 
				//
#				ifdef _DEBUG
				if (bs == BINDSTRING_HEADERS)
				{
					//TRACE_LOG(_T("Headers!")); 
				}
#				endif
				//
				LPOLESTR u = 0; 
				ULONG fetched = 0; 
				HRESULT hr = pIBindInfo->GetBindString(bs, &u, 1, &fetched); 
				if (FAILED(hr)) 
				{
					///DWORD dwErr = 0xffff & hr;
					fetched = 0;
				}
				//
				if (fetched == 1) 
				{ 
					r = CStringW(u); 
				}
				if (u)
				{
					CoTaskMemFree(u); 
				}
				//
				return r;
			}
			_Catch()
		}




		// ----
		// ��������� �������

		void Init(
			LPCWSTR szUrl,
            IInternetProtocolSink *pIProtSink,
            IInternetBindInfo *pIBindInfo,
            DWORD grfSTI,
            DWORD dwReserved)
		{
			try
			{
#				ifdef _PROTOCOL_TRACE_EVENTS
				{
					TRACE_LINE(_T("[]: Init - In")); 
				}
#				endif
				//
#				ifdef _TRACE_CALLS_2
				{
					///TRACE_LOG1(_T("In: %s"), _S(szUrl).GetString() ); 
				}
#				endif
				//
				//
				//
				Free();
				//
				//
				//
				// ----
				// ��������� ��������� ������� 
				//
				// STI
				//
				GrfSTI = grfSTI;
				//
				// IInternetProtoccolSink
				//
				if (pIProtSink)
				{

					OutgoingProtocolSink = pIProtSink;
					//OutgoingProtocolSink.Attach(
					//	CComQIPtr<IInternetProtocolSink>(pIProtSink).Detach()
					//	);
				}
				//
				// IInternetBindInfo 
				//
				if (pIBindInfo)
				{
					iBindInfo.Attach(CComQIPtr<IInternetBindInfo>(pIBindInfo).Detach());
				}
				//
				// PROTOCOLFILTERDATA
				//
				ProtFiltData = (PROTOCOLFILTERDATA*) (__int64)dwReserved; 
				//
				// Incoming Content-Type � URL, � ����� ��� ������ ��������� (������ ��� ��������) 
				//
				if (grfSTI & PI_FILTER_MODE) // MIME-������ 
				{
					IsMIMEFilter = true; 
					//
					if (szUrl) IncomingContentType = string(szUrl);
					//
					if (iBindInfo && (IncomingURL.GetLength() == 0))
					{
						IncomingURL = GetBindString(iBindInfo,BINDSTRING_URL); 
					}
				}
				else // Internet protocol : ������� ��������-�������� 
				{
					IsMIMEFilter = false; 
					//
					if (szUrl) IncomingURL = string(szUrl); 
				}
				//
				IncomingHeaders = GetBindString(iBindInfo,BINDSTRING_HEADERS); 
				if (IncomingHeaders.GetLength() == 0)
				{
					IncomingHeaders = "Content-Type: text/xml"; 
				}
				//
				////CheckUrlIsPublic(); // --> Protocol 
				//
				//
				//
				// ----
				// BINDINFO: ������ ������ �� ����� 
				//
				BindFlags = 0;
				ZeroMemory(&BindInfo,sizeof(BindInfo));
				if (iBindInfo)
				{
					BindInfo.cbSize = sizeof(BINDINFO);
					//
					HRESULT rc = iBindInfo->GetBindInfo(&BindFlags,&BindInfo);
					if (rc != S_OK) 
					{
						BindInfo.cbSize = 0;
						throw MethodError(rc);
					}
					//
					CodePage = BindInfo.dwCodePage; // ��������� �������
					//
					if (BindInfo.dwBindVerb == BINDVERB_POST) 
					{
						int dataT = BindInfo.stgmedData.tymed;
						//
						if (dataT == TYMED_NULL)
						{
							// ��������: PostStream = NULL 
						}
						else if (dataT == TYMED_HGLOBAL)
						{
#							ifdef _DEBUG
							{
								TRACE_LINE(_T("�������� ������ POST ���� HGLOBAL")); 
							}
#							endif
							//
							HGLOBAL h1 = BindInfo.stgmedData.hGlobal;
							//
							BYTE* postData = (BYTE*)h1;
							int postLength = (int)BindInfo.cbstgmedData;
							//
							CComPtr<ISlotMemoryReader> reader;
							reader.Attach(
								CSlotMemoryReader::Create<ISlotMemoryReader>()
								);
							//
							HRESULT rc = reader->put_Data(postData);
							if (FAILED(rc)) throw MethodError(rc); 
							//
							rc = reader->put_Size(postLength);
							if (FAILED(rc)) throw MethodError(rc); 
							//
							CComQIPtr<IStream> q(reader);
							if (! q) throw MethodError(E_UNEXPECTED); 
							PostStream.Attach(q.Detach());
						}
						else if (dataT == TYMED_ISTREAM)
						{
#							ifdef _DEBUG
							{
								TRACE_LINE(_T("�������� ������ POST ���� IStream")); 
							}
#							endif
							//
							IStream* stream = BindInfo.stgmedData.pstm; 
							CComQIPtr<IStream> q(stream); 
							if (! q) throw MethodError(E_NOINTERFACE); 
							PostStream.Attach(q.Detach()); 
						}
						else if (dataT == TYMED_FILE)
						{
#							ifdef _DEBUG
							{
								TRACE_LINE(_T("�������� ������ POST ���� File")); 
							}
#							endif
							//
							string path(BindInfo.stgmedData.lpszFileName); 
							//
							CComPtr<ISlotFileReader> reader;
							reader.Attach(
								CSlotFileReader::Create<ISlotFileReader>() 
								);
							//
							HRESULT rc = reader->put_Path(CComBSTR(path));
							if (FAILED(rc)) throw MethodError(rc); 
							//
							rc = reader->Open();
							if (FAILED(rc)) throw MethodError(rc); 
							//
							CComQIPtr<IStream> q(reader); 
							if (! q) throw MethodError(E_UNEXPECTED); 
							PostStream.Attach(q.Detach()); 
						}
						else
						{
							CString msg = FormatStr(
								_S("����������� �������� BindInfo.stgmedData.tymed = %d"), 
								(int)BindInfo.stgmedData.tymed
								);
							//
							throw MethodError(_W(msg));
						}
					}
					else
					{
						// GET etc.: ���������� ������ URL 
					}
				}
				else
				{
					///ProtocolTextWarning(_T("BINDINFO �����������"));
				}
				//
#				ifdef _PROTOCOL_TRACE_EVENTS
				{
					TRACE_LINE(_T("[]: Init - Out"));
				}
#				endif
			}
			_Catch()
		}



		////////void CopyPost() 
		////////{
		////////	try
		////////	{
		////////		if (PostStream)
		////////		{
		////////			string id = NewGuidStr();
		////////			string url = GetDefaultUrlStart() + L"/" + id + L".txt"; 
		////////			UrlCacheEntry entry(_S(url));
		////////			//
		////////			entry.Create();
		////////			CString path_2 = entry.GetPath(); 
		////////			//
		////////			CComPtr<ISlotFileReader> reader_2;
		////////			reader_2.Attach(
		////////				CSlotFileReader::Create<ISlotFileReader>() 
		////////				);
		////////			//
		////////			HRESULT rc = reader_2->put_CacheUrl(CComBSTR(url)); 
		////////			if (FAILED(rc)) throw MethodError(rc);
		////////			//
		////////			rc = reader_2->WriteStream(PostStream); 
		////////			if (FAILED(rc)) throw MethodError(rc);
		////////			//
		////////			CComQIPtr<IStream> stream_2(reader_2);
		////////			if (stream_2) throw MethodError(E_UNEXPECTED); 
		////////			//
		////////			PostStream.Release();
		////////			PostStream.Attach(stream_2.Detach()); 
		////////		}
		////////	}
		////////	_Catch() 
		////////}



		// ----
		// ��������� 

		inline void SetOutUrl(const string& url,const string& OriginalUrl)
		{
			try
			{
				OutUrl = url; 
				if (OutUrl.GetLength() == 0) OutUrl = OriginalUrl; 
				//
				if (! OutgoingProtocolSink) 
				{
#					ifdef _PROTOCOL_TRACE_EVENTS
					//TRACE_LOG(_T("OutgoingProtocolSink == 0")); 
#					endif
					//
					throw MethodError(E_UNEXPECTED); 
				}
				//
				if (OutUrl != OriginalUrl)
				{
#					ifdef _PROTOCOL_TRACE_EVENTS
					//TRACE_LOG(_S("Redirecting   !!!   URL=") + _S(OutUrl)); 
#					endif
					//
					string newUrl = url; 
					//
					if (newUrl.Left(1) == L"/") newUrl = _PROTOCOL_DEFAULT_HOST + newUrl; 
					//
					HRESULT rc = OutgoingProtocolSink->ReportProgress(
						BINDSTATUS_REDIRECTING,
						newUrl
						);
					if (FAILED(rc)) throw MethodError(rc);
				}
				else
				{
					//TRACE_LOG(_T("(no redir)")); 
				}
			}
			_Catch()
		}

		int m_OutStatus;

		inline void SetOutStatus(int status)
		{
			if (status == 0) m_OutStatus = 200; 
			m_OutStatus = status; 
		}

		inline void SetOutContentType(const string& contentType) 
		{
			try
			{
				OutContentType = contentType; 
				//
				ReportOutContentType();
			}
			_Catch() 
		}

		inline void SetOutCachePath(const CString& path) 
		{
			try
			{
				OutCachePath = path; 
			}
			_Catch() 
		}

		inline void ReturnData() 
		{
			try
			{
#				ifdef _PROTOCOL_TRACE_EVENTS 
				{
					TRACE_LINE(_T("[]: ReturnData - In"));
				}
#				endif
				//
				HRESULT rc; 
				//
				{
					//CComQIPtr<ISlotFileReader> f = CSlotFileReader::Create<ISlotFileReader>(); 
					//f->put_Path(CComBSTR("D:\\test.xml")); 
					//f->Open(); 
					//CComQIPtr<IStream> stream(f);
					//if (OutStream) OutStream.Detach(); 
					//OutStream.Attach(stream.Detach()); 
				}
				//
				//TRACE_LINE(_T("* 35"));
				if (! OutgoingProtocolSink) throw MethodError(E_UNEXPECTED); 
				if (! iBindInfo) throw MethodError(E_UNEXPECTED); 
				//
				if ((BindFlags & BINDF_NEEDFILE) == BINDF_NEEDFILE) 
				{
					rc = OutgoingProtocolSink->ReportProgress(BINDSTATUS_USINGCACHEDCOPY,0); 
					if (FAILED(rc)) throw MethodError(rc); 
				}
				//TRACE_LINE1(_T("OutgoingProtocolSink: 0x%x"), (int)(IInternetProtocolSink*)OutgoingProtocolSink );
				// 
				//TRACE_LINE(_T("* 36"));
				if (OutCachePath.GetLength() > 0) 
				{
					CStringW cachePathW(OutCachePath); 
					//cachePathW = L"D:\\test.xml";
					//
#					ifdef _DEBUG
					TRACE_LINE(_T("* cache path: ") + _S(cachePathW) );
#					endif
					//
					if (OutgoingProtocolSink)
					{
						rc = OutgoingProtocolSink->ReportProgress(BINDSTATUS_CACHEFILENAMEAVAILABLE, 
							cachePathW);
						if (FAILED(rc)) throw MethodError(rc); 
						//TRACE_LINE(_T("* 37"));
					}
					else
					{
#						ifdef _PROTOCOL_TRACE_EVENTS
						TRACE_LINE(_T("OutgoingProtocolSink == 0 @ ReportProgress")); 
#						endif
					}
				}
				//TRACE_LINE1(_T("OutgoingProtocolSink: 0x%x"), (int)(IInternetProtocolSink*)OutgoingProtocolSink );
				//
				//rc = OutgoingProtocolSink->ReportData(
				//	BSCF_FIRSTDATANOTIFICATION //| 
				//	//BSCF_LASTDATANOTIFICATION | 
				//	//BSCF_DATAFULLYAVAILABLE
				//	, 0, 100);
				//TRACE_LINE(_T("* 38_"));
				//
				if (! OutStream)
				{
					throw MethodError(L"OutStream == 0");
				}
				//
				//TRACE_LINE(_T("* 38"));
				if (OutgoingProtocolSink)
				{
					rc = OutgoingProtocolSink->ReportData(
						//BSCF_FIRSTDATANOTIFICATION | 
						//BSCF_LASTDATANOTIFICATION | 
						BSCF_DATAFULLYAVAILABLE, 100, 100);
					//TRACE_LINE(_T("* 38a"));
					if (FAILED(rc)) throw MethodError(rc);
				}
				else
				{
#					ifdef _PROTOCOL_TRACE_EVENTS
					TRACE_LINE(_T("OutgoingProtocolSink == 0 @ ReportData")); 
#					endif
				}
				//
				//TRACE_LINE(_T("* 39"));
				if (OutgoingProtocolSink)
				{
					rc = OutgoingProtocolSink->ReportResult(S_OK,m_OutStatus,L"OK");
					if (FAILED(rc)) throw MethodError(rc);
				}
				else
				{
#					ifdef _PROTOCOL_TRACE_EVENTS
					TRACE_LINE(_T("OutgoingProtocolSink == 0 @ ReportResult")); 
#					endif
				}
				//TRACE_LINE(_T("* 40"));
				//
#				ifdef _PROTOCOL_TRACE_EVENTS
				{
					TRACE_LINE(_T("[]: ReturnData - Out"));
				}
#				endif
			}
			_Catch() 
		}

		inline void SetOutStream(IStream* stream) 
		{
			try
			{
				if (OutStream) OutStream.Release(); 
				//
				if (stream) 
				{
					CComQIPtr<IStream> q(stream); 
					if (! q) throw MethodError(E_UNEXPECTED); 
					OutStream.Attach(q.Detach()); 
				}
				else
				{
					//TRACE_LOG(_T("stream == 0"));
				}
				//
#				ifdef _DEBUG
				//
				if (false) 
				{
					CComPtr<ISlotMemoryReader>	r;
					r.Attach(CSlotMemoryReader::Create<ISlotMemoryReader>());
					string test = _W(COMMON_XML_START) + L"<test>TEST</test>"; 
					Blob b = WideStringToUTF8(test);
					r->put_Blob((BYTE*)&b);
					if (OutStream) OutStream.Release(); 
					OutStream.Attach( CComQIPtr<IStream>(r).Detach() ); 
				}
				//
				if (false)
				{
					CComPtr<ISlotFileReader>	r;
					r.Attach(CSlotFileReader::Create<ISlotFileReader>());
					string path = L"d:\\CertRequest.xml"; 
					r->put_Path(CComBSTR(path));
					r->Open(); 
					if (OutStream) OutStream.Release(); 
					OutStream.Attach( CComQIPtr<IStream>(r).Detach() ); 
				}
				//
				if (false)
				{
					string path = L"d:\\CertRequest.xml"; 
					::::File f;
					f.Open(_S(path));
					Blob b = f.ReadAll();
					f.Close(); 
					//
					CComPtr<ISlotMemoryReader>	r;
					r.Attach(CSlotMemoryReader::Create<ISlotMemoryReader>());
					string test = _W(COMMON_XML_START) + L"<test>TEST</test>"; 
					r->put_Blob((BYTE*)&b);
					if (OutStream) OutStream.Release(); 
					OutStream.Attach( CComQIPtr<IStream>(r).Detach() ); 
				}
#				endif
			}
			_Catch()
		}



		inline CString SetOutStreamToCache(const string& url) 
		{
			try
			{
				UrlCacheEntry entry(url); 
				//
				if (! entry.Exists())
				{
					//TRACE_LINE(_T("NO ENTRY!"));
					//return OutCachePath; 
					//
					throw MethodError(L"No cache entry!");
				}
				//
				CString cachePath = entry.GetPath(); 
				if (cachePath.GetLength() == 0)
				{
					throw MethodError(L"cachePath == <empty>");
				}
				//
				OutCachePath = cachePath;
				//
				CComPtr<ISlotFileReader> reader;
				reader.Attach(
					CSlotFileReader::Create<ISlotFileReader>() // new reference 
					);
				if (! reader) throw MethodError(E_UNEXPECTED); 
				//
				HRESULT rc = reader->put_Path(CComBSTR(cachePath)); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				rc = reader->Open(); 
				if (FAILED(rc)) 
				{
					TRACE_LOG(_T("�� ������� ������� cache-���� ��� ������")); 
					throw MethodError(rc).AddIfNewSource_(L"�� ������� ������� cache-���� ��� ������\n" + _W(cachePath) + L"\nURL: " + OutUrl ); 
				}
				//
				// IStream 
				//
				CComQIPtr<IStream> stream(reader);
				if (! stream)
				{
					throw MethodError(L"stream == <empty>");
				}
				//
				SetOutStream(stream); 
				//
				return cachePath; 
			}
			_Catch()
		}



		inline void ReportOutContentType() 
		{
			try
			{
#				ifdef _DEBUG
				{
					TRACE_LINE(_T("OutContentType: ") + _S(OutContentType) ); 
				}
#				endif
				//
				if (! OutgoingProtocolSink) return; 
				//
				HRESULT rc = OutgoingProtocolSink->ReportProgress(
					BINDSTATUS_VERIFIEDMIMETYPEAVAILABLE, 
					OutContentType 
					//L"text/html"
					);
				if (FAILED(rc)) throw MethodError(rc); 
			}
			_Catch() 
		}

		inline void ReportOnResult_All()
		{
			try
			{
				ReportOutUrl();
				ReportOutContentType(); // ��� ������� ����� ������� ����������� ������ ���������� �� ������ 
			}
			_Catch()
		}



	public:
		string SysInfo;

	protected:
		// ----
		// ����������� ���������� �� ������ 

		CStringW ErrorContentType;

		Blob ErrorMsgData; 

		int ErrorMsgPos; 

		HRESULT SetError(const char* p,int size) throw() 
		{
			try 
			{
				//TRACE_LOG(_T("Error!")); 
				//
				ErrorMsgData.Allocate(size);
				CopyMemory(ErrorMsgData.GetBuffer(),p,size); 
				//
				// -----
				// !!!!!
				// ���������� ��������� 
				//
				CComPtr<ISlotMemoryReader> mReader;
				mReader.Attach( CSlotMemoryReader::Create<ISlotMemoryReader>() ); 
				if (! mReader) throw MethodError(E_UNEXPECTED); 
				//
				HRESULT rc = mReader->put_Size(ErrorMsgData.Length()); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				rc = mReader->put_Data(ErrorMsgData.GetBuffer()); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				CComQIPtr<IStream> mStream(mReader); 
				if (! mStream) throw MethodError(E_UNEXPECTED); 
				//
				int errStatus = 500;
				if (Instance().GetOption(L"special-125") != "")
				{
					errStatus = 200; 
				}
				SetOutStatus(errStatus);
				SetOutStream(mStream); 
				SetOutContentType(ErrorContentType); 
				//
				ReturnData(); 
				//
				return S_OK;
			}
			catch(::::Exception e)
			{
				TRACE_LOG(_S(e.ToString())); 
				// 
				return E_UNEXPECTED; 
			}
			catch(...)
			{
				return E_UNEXPECTED; 
			}
		}

		inline CStringA GetCss() 
		{
			CStringA css = "table.A {\n"
				"  margin: 1em 1em 1em 0;\n"
				"  background: #f9f9f9;\n"
				"  border: 1px #aaaaaa solid;\n"
				"  border-collapse: collapse;\n"
				"}\n"
				"\n"
				"table.A th, table.A td {\n"
				"  border: 1px #aaaaaa solid;\n"
				"  padding: 0.2em;\n"
				"}\n"
				"\n"
				"table.A th {\n"
				"  background: #f2f2f2;\n"
				"  text-align: center;\n"
				"}\n"
				"\n"
				"table.A caption {\n"
				"  margin-left: inherit;\n"
				"  margin-right: inherit;\n"
				"}\n"
				"\n"
				"td.errormessage {\n"
				"  color: #000077;\n"
				"  font-weight: bold;\n"
				"}\n"
				;
			//
			return css;
		}

		HRESULT SetError(const ::::Exception& exc) throw() 
		{
			try 
			{
				//TRACE_LOG(_T("Error! (2)")); 
				//
				//TRACE_LOG(exc.GetMsg()); 
				//TRACE_LOG(_T("��������� ������ !!!!!!!!!!!!!")); 
				//
				// ----
				// ���������� �� ������ 
				//
				CStringA outHtml;
				//
				string mediaType = exc.m_MediaType; 
				//
				// ----
				// ����� � ��������� ������� 
				//
				string sysInfoText = SysInfo;
				//
				string outReport = exc.GetConsoleText() + sysInfoText;  
				//
				// ----
				// ����� ��� ����������� ������������ 
				//
				const char* p;
				int size; 
				//
				Blob data; 
				string response;
				//
				if (mediaType == L"text/xml") 
				{
					ErrorContentType = L"text/xml"; 
					//
					response = exc.GetXml(); 
				}
				else if (mediaType == L"text/plain") 
				{
					ErrorContentType = L"text/plain"; 
					//
					response = exc.GetMsg(); 
				}
				else // (mediaType == L"text/html") 
				{
					ErrorContentType = L"text/html"; 
					//
					string sysInfoHtml = ::::SystemInfo::InfoToHtmlInfo(sysInfoText);
					//
					string report = sysInfoText;
					//
					// TODO: !!! Client().LogTextError_(_S(report));
					//
					/// TRACE_LOG(report); 
					//
					// ----
					// EMail
					//
					string eMail = L"mailto:test@test.com"; 
					//
					try
					{
						eMail = Instance().GetOption(L"slot-report-email"); 
					}
					catch(...)
					{
					}
					//
					// ----
					// Report system 
					//
					string c_reportServiceUrl = L"https://cabinet.example.com/gate/report-system/"; 
					//
					try
					{
						string reportServiceUrl = Instance().GetOption(L"slot-report-service-url"); 
						reportServiceUrl = c_reportServiceUrl; 
						//
						// Document 
						//
						CComPtr<IStream> requestStream; 
						//
						Protocol::RequestHandler Request; 
						string IncomingHeaders = L"";
						Request.Open(reportServiceUrl, requestStream, IncomingHeaders); 
						Request.Run(); 
					}
					catch(...)
					{
					}
					//
					//
					//
					// ----
					// �������� � ��������� ������� 
					//
					//
					//
					//
					// ----
					// �������� � HTML 
					//
					string msgW = exc.GetHtml();
					//
					CStringA msgA(msgW); 
					//
					CStringA htmlSysInfoA(sysInfoHtml); 
					//
					string htmlFilterInfo = L"<table class=\"A\">\n" 
						//L"<tr><td>Content-Type</td><td>" + IncomingContentType + L"</td></tr>\n"
						; 
					//
					if (IncomingURL.GetLength() > 0)
					{
						htmlFilterInfo += L"<tr><td>URL</td><td>" + IncomingURL + L"</td></tr>"; 
					}
					//
					htmlFilterInfo += L"</table>\n";
					//
					CStringA htmlFilterInfoA(htmlFilterInfo); 
					//
					CStringA titleA = "������ ��� ����������� ���������"; 
					//
					CStringA dataA = 
						"<h1>" + titleA + "</h1>\n"
						+ msgA + "\n"
						"<h4>������ ���������</h4>\n"
						+ htmlFilterInfoA + 
						"<div style=\"display: " + 
#						ifdef _DEBUG
						""
#						else
						"none" 
#						endif
						+ ";\">" 
						"<h4>���������� � �������</h4>\n" 
						"<table class=\"A\">\n"
						+ htmlSysInfoA +
						"</table>\n" 
						"</div>" 
						;
					//
					CStringA dataToMail = dataA; 
					dataToMail.Replace("&","&amp;");
					dataToMail.Replace("<","&lt;");
					dataToMail.Replace(">","&gt;");
					dataToMail.Replace("\"","&quot;"); 
					//
					CStringA htmlA = 
						"<html>\n"
							"<head>\n"
								"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></meta>\n"
								"<style type=\"text/css\">\n" +
								GetCss() +
								"</style>\n"
								"<title>" + titleA + " - �� - ����</title>\n"
							"</head>\n"
							"<body>\n" +
							dataA + 
							"<form action=\"" + _A(eMail) + "\" method=\"POST\" >\n" 
							"<input type=\"hidden\" name=\"ErrorInfo\" value=\"__DATA_TO_MAIL__\"></input>\n" 
							"<input type=\"submit\" value=\"��������� ���������� ������������\"></input>\n" 
							"</form>\n"
							"</body>\n"
						"</html>"
						;
					//
					htmlA.Replace("__DATA_TO_MAIL__",dataToMail); 
					//
					response = _W(htmlA);
				}
				//
#				ifdef _DEBUG
				{
					//OutputDebugString(_S(response)); 
				}
#				endif 
				//
				data = WideStringToUTF8(response); // ���������� response 
				//
				size = data.Length(); 
				p = (char*)data.GetBuffer(); 
				//
				return SetError(p,size); 
			}
			catch(::::Exception e)
			{
				TRACE_LOG(_S(e.ToString())); 
				// 
				return E_UNEXPECTED; 
			}
			catch(...)
			{
				return E_UNEXPECTED; 
			}
		}

		
	
		// ----
		// ��������������� ������� 

		inline static void Log(const CStringW& text) throw() 
		{
			// TRACE_LOG(text);
			// TODO: Util::Log(text);
		}

		inline static const string& GetProtocolPrefix() 
		{
			static string s_Prefix = _PROTOCOL_PREFIX;
			return s_Prefix; 
		}

		inline static const string& GetDefaultUrlStart() 
		{
			static string s_DefaultUrlStart = GetProtocolPrefix() + _PROTOCOL_DEFAULT_HOST;
			return s_DefaultUrlStart; 
		}






		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		// ���������� ���������� 

		inline void FreeProtocolData()
		{
			try
			{
				OutStream.Release(); 
			}
			_Catch() 
		}

		STDMETHOD(Continue)(PROTOCOLDATA *pStateInfo)
		{
			try
			{
				if (IncomingProtocol)
				{
					return IncomingProtocol->Continue(pStateInfo); 
				}
				return S_OK;
			}
			_ComCatch() 
		}
		
		STDMETHOD(Abort)(HRESULT hrReason,DWORD dwOptions)
		{
			try
			{
				if (IncomingProtocol)
				{
					return IncomingProtocol->Abort(hrReason, dwOptions); 
				}
				return S_OK; 
			}
			_ComCatch()
		}

		STDMETHOD(Terminate)(DWORD dwOptions)
		{
			try
			{
				//TRACE_LINE(_T("Terminate")); 
				//if (OutStream)
				//{
				//	OutStream.Release(); 
				//}
				//if (OutgoingProtocolSink)
				//{
				//	OutgoingProtocolSink.Release();
				//}
				if (IncomingProtocol)
				{
					IncomingProtocol->Terminate(dwOptions);
				}
				return S_OK;
			}
			_ComCatch()
		}

		STDMETHOD(Suspend)()
		{
			try
			{
				if (IncomingProtocol)
				{
					return IncomingProtocol->Suspend();
				}
				//TRACE_LOG(_T("Suspending...")); 
				//return E_FAIL;
				return S_OK; 
			}
			_ComCatch()
		}
		
		STDMETHOD(Resume)()
		{
			try
			{
				if (IncomingProtocol)
				{
					return IncomingProtocol->Resume();
				}
				return S_OK; 
			}
			_ComCatch()
		}

		virtual HRESULT Filter_Read(void *pv,ULONG cb,ULONG *pcbRead) // default : returns E_NOTIMPL 
		{
			try
			{
				throw MethodError(E_NOTIMPL); 
			}
			_Catch() 
		}

		int m_Pos;

		STDMETHOD(Read)(void *pv,ULONG cb,ULONG *pcbRead) 
		{
			try
			{
#				ifdef _PROTOCOL_TRACE_EVENTS
				{
					TRACE_LINE(_T("[]: Read - In"));
				}
#				endif
				//
				HRESULT rc = S_FALSE; 
				//
				//if (IsMIMEFilter)
				//{
				//	HRESULT rc;
				//	if (! ErrorMsgData.IsEmpty())
				//	{
				//		if (ErrorMsgPos >= ErrorMsgData.Length()) return S_FALSE;
				//		//
				//		if (cb <= 0)  return S_OK;
				//		//
				//		if (ErrorMsgPos == 0)
				//		{
				//			OutgoingProtocolSink->ReportProgress(
				//				BINDSTATUS_VERIFIEDMIMETYPEAVAILABLE, 
				//				ErrorContentType 
				//				);
				//		}
				//		//
				//		int size = ErrorMsgData.Length();
				//		if (size > (int)cb) size = cb;
				//		//
				//		CopyMemory(pv,ErrorMsgData.GetBuffer(),size); 
				//		//
				//		ErrorMsgPos += size; 
				//		//
				//		if (pcbRead) *pcbRead = size; 
				//		rc = S_FALSE;
				//	}
				//	else
				//	{
				//		return Filter_Read(pv,cb,pcbRead);
				//	}
				//	return rc;
				//}
				//else // Internet protocol 
				//{
					// TODO: read from OutgoingStream 
					//
#					ifdef _PROTOCOL_TRACE_EVENTS
					CString msg_1 = FormatStr(_S("Reading: %d, "), (int)cb) + _S(OutUrl); 
					TRACE_LINE(msg_1); 
					TRACE_LINE(_T("Reading")); 
#					endif
					//
					rc = OutStream->Read(pv,cb,pcbRead); 
					//TRACE_LOG(_T("Read: (4)"));
					if (FAILED(rc)) throw MethodError(rc); 
					//TRACE_LOG(_T("Read: (5)"));
				//}
				//
#				ifdef _PROTOCOL_TRACE_EVENTS
				{
					TRACE_LINE(_T("[]: Read - Out"));
				}
#				endif
				//
				return rc; 
			}
			catch(::::Exception e)
			{
				TRACE_LOG(_T("Read error! (e)"));
				//
				HRESULT hr(e);
				//
				TRACE_LOG(e.ToString()); 
				//
				return FAILED(hr) ? hr : E_FAIL; 
			}
			catch(...)
			{
				TRACE_LOG(_T("Read error! (unexpected)"));
				return E_UNEXPECTED;
			}
		}

		STDMETHOD(Seek)(
				LARGE_INTEGER dlibMove,
				DWORD dwOrigin,
				ULARGE_INTEGER *plibNewPosition)
		{
			try
			{
#				ifdef _PROTOCOL_TRACE_EVENTS
				{
					TRACE_LINE(_T("[]: Seek - In"));
				}
#				endif
				//
				throw MethodError(E_NOTIMPL); 
			}
			_ComCatch()
		}

		STDMETHOD(LockRequest)(DWORD dwOptions) 
		{
			return S_OK;
		}

		STDMETHOD(UnlockRequest)() 
		{
			return S_OK;
		}



		// ----
		// IInternetProtocolSink interface

		STDMETHOD(Switch)(PROTOCOLDATA __RPC_FAR *pProtocolData) 
		{
			try
			{
#				ifdef _PROTOCOL_TRACE_EVENTS
				{
					TRACE_LINE(_T("[]: Switch - In"));
				}
#				endif
				//
				if (OutgoingProtocolSink)
				{
					return OutgoingProtocolSink->Switch(pProtocolData);
				}
				else
				{
					if (IsMIMEFilter)
					{
						throw MethodError(E_FAIL); 
					}
				}
				return S_OK;
			}
			_ComCatch()
		}

		STDMETHOD(ReportProgress)(ULONG ulStatusCode, LPCWSTR szStatusText) 
		{
			try
			{
#				ifdef _PROTOCOL_TRACE_EVENTS
				{
					TRACE_LINE2(_T("[]: ReportProgress - In, %d, '%s'"), (int)ulStatusCode, _S(szStatusText).GetString() );
				}
#				endif
				//
				if (OutgoingProtocolSink)
				{
					return OutgoingProtocolSink->ReportProgress(ulStatusCode,szStatusText);
				}
				else
				{
					if (IsMIMEFilter)
					{
						throw MethodError(E_FAIL); 
					}
				}
				return S_OK;
			}
			_ComCatch()
		}

		STDMETHOD(ReportData)(DWORD grfBSCF,ULONG ulProgress,ULONG ulProgressMax) 
		{
			try
			{
#				ifdef _PROTOCOL_TRACE_EVENTS
				{
					TRACE_LINE2(_T("[]: ReportData - In, %d, %d"), (int)ulProgress, (int)ulProgressMax );
				}
#				endif
				//
				if (OutgoingProtocolSink)
				{
					return OutgoingProtocolSink->ReportData(grfBSCF,ulProgress,ulProgressMax);
				}
				else
				{
					if (IsMIMEFilter)
					{
						throw MethodError(E_FAIL); 
					}
				}
				return S_OK;
			}
			_ComCatch()
		}

		STDMETHOD(ReportResult)(HRESULT hrResult,DWORD dwError,LPCWSTR szResult) 
		{
			try
			{
#				ifdef _PROTOCOL_TRACE_EVENTS
				{
					TRACE_LINE3(_T("[]: ReportResult - In, 0x%x, %d, '%s'"), (int)hrResult, (int)dwError, _S(szResult).GetString() );
				}
#				endif
				//
				if (OutgoingProtocolSink)
				{
					return OutgoingProtocolSink->ReportResult(hrResult,dwError,szResult);
				}
				else
				{
					if (IsMIMEFilter)
					{
						throw MethodError(E_FAIL); 
					}
				}
				return S_OK;
			}
			_ComCatch()
		}
	};

} // namespace  
