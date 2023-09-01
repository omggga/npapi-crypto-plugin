/*
 AX_SlotRequestComposer --- ���������� ���������� ISlotRequestComposer ��� ����������� slotrequest:request 
	�� ��������� ������, ������� URL. 

 ���������� ������������ ���������� (�� QueryInterface):
	
	IStream		��� ���������� � ������ ������ ��������������� XML-������� 

 $Name: work1 $
 $Revision: 1.1.2.7 $
 $Date: 2008/11/01 11:50:28 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include <low-level/SmartUtil.h>
#include <low-level/SmartXml.h>
#include <low-level/SmartWeb.h>
//
#include <ax/coclasses/AX_SlotDataStream.h>
#include <ax/coclasses/AX_SlotXmlFilter.h>
//
#include <ax/interfaces/ISlotRequestComposer.h>



namespace  { 

	// =================================================
	// ���������� ISlotRequestComposer

	// CSlotRequestComposer 
	class ATL_NO_VTABLE CSlotRequestComposer : 
		public CComObjectRootEx<CComSingleThreadModel>, 
		public CComCoClass<CSlotRequestComposer//, &CLSID_SlotRequestComposer
		>, 
		public ISlotRequestComposer, 
		public IStream
	//
	{
	public:
		template<class I>
		inline static I* Create() // new reference 
		{
			try
			{
				typedef CComObject<CSlotRequestComposer> _CoClass;
				_CoClass* pClass;
				HRESULT rc = _CoClass::CreateInstance(&pClass);
				if (FAILED(rc)) throw MethodError(rc);
				//
				pClass->AddRef();
				//
				CComPtr<I> i;
				rc = pClass->QueryInterface(__uuidof(I),(void**)&i); 
				if (FAILED(rc)) throw MethodError(rc);
				//
				pClass->Release();
				pClass = NULL;
				//
				return i.Detach();
			}
			_Catch()
		}



	protected:
		// ----
		// ������ 

		// ���� 

		string m_Url;

		Uri m_Uri; 

		CComPtr<IStream> m_PostStream; 

		// ������ 

		bool m_Ready; 

		int m_PostStreamAssignCount; 

		// ���������� �� XML-������� 

		string m_RootLocalName; 

		string m_RootNsUri; 

		// ������

		CComPtr<ISlotClient> m_Client; 

		// ����� 

		CComPtr<ISlotFileReader> m_OutFileReader; // ������ ������� 

		CComPtr<IStream> m_OutStream; 

		// slotrequest:info 

		XmlDocument m_Info; 
		XmlDocument m_InfoByUrl; 

		XmlElement m_Info_E;



		// ----
		// ������������ 

		inline void Clear() 
		{
			m_Ready = false; 
			m_PostStreamAssignCount = 0; 
		}

		inline void Free() throw() 
		{
			Clear(); 
		}

	public:
		CSlotRequestComposer()
		{
			Free(); 
		}

		BEGIN_COM_MAP(CSlotRequestComposer)
			COM_INTERFACE_ENTRY_IID(__uuidof(ISlotRequestComposer),ISlotRequestComposer)
			COM_INTERFACE_ENTRY_IID(__uuidof(IStream),IStream)
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

		~CSlotRequestComposer()
		{
			Free(); 
		}



		// ----
		// ����: URL, GET 

		inline static const string& SlotRequestNsUri() 
		{
			static string s = _SLOTREQUEST_NSURI; 
			return s; 
		}

		inline const string& InfoTemplate() 
		{
			static string s = 
				_W(COMMON_XML_START) + 
				L"<?-xml-sign-next ?>" 
				L"<slotrequest:info \n"
				L"    xmlns:slotrequest=\"" + SlotRequestNsUri() + L"\" \n"
				L"    uuid=\"__uuid__\" \n"
				L"    >\n"
				L"<slotrequest:parameters>\n"
				L"</slotrequest:parameters>\n"
				L"<slotrequest:headers />\n"
				L"</slotrequest:info>"
				; 
			return s; 
		}

		inline string GetNewInfoXml() 
		{
			string s = InfoTemplate(); 
			s.Replace(L"__uuid__",_W(NewGuidStr())); 
			return s; 
		}

		XmlElement GetPXml(const string& name
			, const string& value
			, const string& source
			, const string& valueEnc)
		{
			XmlElement PXml = m_Info.CreateElement(L"slotrequest", L"param", SlotRequestNsUri());
			string nsURI = PXml.NamespaceURI();
			PXml.SetAttribute(L"name", name);
			PXml.SetAttribute(L"source", source);
			PXml.SetAttribute(L"value-type", valueEnc);
			PXml.InnerText() = value; // TODO: ��������� �� ������� xml escape 
			return PXml;
		}

		inline void AddParameter_GET(XmlElement& parameters_E,const string& name,const string& value) 
		{
			try
			{
				if (name.GetLength() > 0) 
				{
					XmlElement param_E = GetPXml(name,value,L"GET",L"text"); 
					//
					parameters_E.AppendChild(param_E); 
				}
			}
			_Catch() 
		}

		// ��������� 

		STDMETHOD(SetParameter)(BSTR source,BSTR encType,BSTR name,BSTR value) 
		{
			try
			{
				XmlElement parameters_E = (XmlElement)m_Info_E.SelectSingleNode(L"slotrequest:parameters"); 
				//
				XmlElement param_E = GetPXml(_W(name),_W(value),_W(source),_W(encType)); 
				//
				parameters_E.AppendChild(param_E); 
				//
				return S_OK; 
			}
			_ComCatch()
		}

		STDMETHOD(GetParametersXml)(BSTR name, IXMLDOMNode** value) 
		{
			try
			{
				XmlNodeList p_L = m_Info_E.SelectNodes(
					L"slotrequest:parameters"); 
				//
				XmlNode params_node = p_L[0]; 
				//
				IXMLDOMNode* i = params_node.QueryComInterface<IXMLDOMNode>();
				//
				if (value) *value = i; 
				return S_OK; 
			}
			_ComCatch()
		}

		STDMETHOD(GetParameterAsText)(BSTR name,BSTR* value) 
		{
			try
			{
				CComBSTR bstrName(name); 
				//
				XmlNodeList p_L = m_Info_E.SelectNodes(
					L"slotrequest:parameters/slotrequest:param[@name='" + _W(bstrName) + L"']"); 
				//
#				ifdef _DEBUG
				{
					//OutputDebugStringW(m_Info_E.OuterXml()); 
				}
#				endif
				//
				string val;
				//
				if (p_L.Count() > 0)
				{
					XmlNode param_node = p_L[0]; 
					string vStr = param_node.InnerText(); 
					CComBSTR s(vStr); 
					val = s; 
				}
				//
				if (val.GetLength() == 0)
				{
					XmlElement rootE = m_InfoByUrl.DocumentElement(); 
					//
					XmlNodeList p_L = rootE.SelectNodes(
						L"slotrequest:parameters/slotrequest:param[@name='" + _W(bstrName) + L"']"); 
					//
					if (p_L.Count() > 0)
					{
						XmlNode param_node = p_L[0]; 
						string vStr = param_node.InnerText(); 
						CComBSTR s(vStr); 
						val = s; 
					}
				}
				//
				if (val.GetLength() > 0)
				{
					CComBSTR s(val); 
					if (value) *value = s.Detach(); 
					return S_OK; 
				}
				else
				{
					CComBSTR empty(L"");
					if (value) *value = empty.Detach(); 
					return S_FALSE;
				}
			}
			_ComCatch()
		}

		STDMETHOD(GetParameterAsInnerText)(BSTR name,BSTR* value) 
		{
			try
			{
				CComBSTR bstrName(name); 
				//
				XmlNodeList p_L = m_Info_E.SelectNodes(
					L"slotrequest:parameters/slotrequest:param[@name='" + _W(bstrName) + L"']/*"); 
				//
#				ifdef _DEBUG
				{
					//OutputDebugStringW(m_Info_E.OuterXml()); 
				}
#				endif
				//
				if (p_L.Count() > 0)
				{
					XmlNode param_node = p_L[0]; 
					string vStr = param_node.InnerText(); 
					CComBSTR s(vStr); 
					if (value) *value = s.Detach(); 
					return S_OK; 
				}
				else
				{
					CComBSTR empty(L"");
					if (value) *value = empty.Detach(); 
					return S_FALSE;
				}
			}
			_ComCatch()
		}






		inline void ParseUrl(const string& url) 
		{
			try
			{
				// ----
				// ��������� url 
				//
				if (url.GetString() == 0) throw MethodError(E_INVALIDARG); 
				//
				m_Uri.ParseRequest(ParseMethodUrl,url); 
				//
				//
				//
				// ----
				// �������� ���������� URL (GET � �.�.) � slotrequest:info 
				//
				if (m_Info.IsEmpty())
				{
					m_Info.LoadXml(GetNewInfoXml()); 
				}
				SetInfoDocumentDetails(); 
				//
				XmlElement parameters_E = (XmlElement)m_Info_E.SelectSingleNode(L"slotrequest:parameters"); 
				//
				// ----
				// Query 
				//
				int position; 
				m_Uri.ParseQuery_I_Start(position); 
				//
				string name; 
				string value; 
				//
				while (m_Uri.ParseQuery_I_Get(position,name,value)) 
				{
					AddParameter_GET(parameters_E,name,value);
				}
				//
				// ----
				// �������� ��������� 
				//
				{
					CComBSTR bs(m_Uri.ResourcePath); 
					m_Info_E.SetAttribute(L"path",CComVariant(bs)); 
				}
				{
					CComBSTR bs(m_Uri.Query); 
					m_Info_E.SetAttribute(L"query",CComVariant(bs)); 
				}
				//
				m_InfoByUrl = m_Info; 
			}
			_Catch()
		}

		inline int GetSecurityStatus() 
		{
			try
			{
				return 1; 
			}
			_Catch() 
		}

		STDMETHOD(get_SecurityStatus)(int* out_status)
		{
			try
			{
				if (out_status) *out_status = GetSecurityStatus(); 
				return S_OK; 
			}
			_ComCatch() 
		}



		inline Protocol::AppCtx& Instance() 
		{
			return Protocol::AppCtx::Instance(); 
		}

		inline void AppendHeader(XmlElement& headers_E, XmlDocument& doc, 
			const string& headerName, const string& headerValue 
			)
		{
			try
			{
				XmlElement header_E = doc.CreateElement(
					L"slotrequest", L"header", SlotRequestNsUri() 
					);
				//
				header_E.SetAttribute(_W(L"name"), headerName); 
				header_E.SetAttribute(_W(L"value-type"), _W(L"text")); 
				header_E.SetAttribute(_W(L"source"), _W(L"Headers")); 
				//
				headers_E.AppendChild(header_E); 
			}
			_Catch() 
		}

		inline void AppendHeaderToInfo(const string& headerName, const string& headerValue 
			)
		{
			try
			{
				XmlDocument doc = m_Info; 
				//
				////string xml1 = m_Info.OuterXml(); 
				XmlNodeList headers_L = m_Info.SelectNodes(L"/*/slotrequest:headers"); 
				if (headers_L.Count() == 0) 
				{
					XmlElement headers_E = m_Info.CreateElement( 
						L"slotrequest", L"headers", SlotRequestNsUri() 
						);
					//
					XmlElement root = m_Info.DocumentElement(); 
					root.AppendChild(headers_E); 
					//
					headers_L = m_Info.SelectNodes(L"/*/slotrequest:headers"); 
					if (headers_L.Count() == 0) 
						throw MethodError(L"headers element not found"); 
				}
				XmlElement headers_E = headers_L[0]; 
				//
				AppendHeader(headers_E, doc, headerName, headerValue); 
			}
			_Catch() 
		}

		inline void SetExtraHeaders_1() 
		{
			try
			{
				XmlDocument doc = m_Info; 
				//
				////string xml1 = m_Info.OuterXml(); 
				XmlNodeList headers_L = m_Info.SelectNodes(L"/*/slotrequest:headers"); 
				if (headers_L.Count() == 0) 
				{
					XmlElement headers_E = m_Info.CreateElement( 
						L"slotrequest", L"headers", SlotRequestNsUri() 
						);
					//
					XmlElement root = m_Info.DocumentElement(); 
					root.AppendChild(headers_E); 
					//
					headers_L = m_Info.SelectNodes(L"/*/slotrequest:headers"); 
					if (headers_L.Count() == 0) 
						throw MethodError(L"headers element not found"); 
				}
				XmlElement headers_E = headers_L[0]; 
				//
				string s1 = Instance().GetCurrentPKHBinaryListStr(); 
				AppendHeader(headers_E, doc, L"X--PKHBinaryList", s1); 
			}
			_Catch() 
		}




	protected:
		// ----
		// ��������� 

		inline void OpenFileReader() 
		{
			try
			{
				HRESULT rc = m_OutFileReader->Open(); 
				if (FAILED(rc)) throw MethodError(rc); 
			}
			_Catch() 
		}

	public:
		inline void OpenRequestFile() 
		{
			try
			{
				string requestContentType; 
				string requestDataSource;
				//
				if (m_PostStream)
				{
#					ifdef _DEBUG
					{
						TRACE_LINE(_T("PostStream ����������� => ��������� ����� ��� ������")); 
					}
#					endif
					//
					requestContentType = L"text/xml"; // TODO: Content-Type!!!
					requestDataSource = L"post";
					//
					if (m_OutStream) m_OutStream.Release(); 
					//
					CComQIPtr<IStream> stream(m_PostStream); 
					if (! stream) throw MethodError(E_NOINTERFACE); 
					//
					m_OutStream.Attach(stream); 
				}
				else
				{
					// ----
					// ������ ����� ������ ������� 
					//
#					ifdef _DEBUG
					{
						TRACE_LINE(_T("������ POST ����� ����������� �� XML-����� ��������� RequestInfo")); 
					}
#					endif
					//
					OpenFileReader(); 
					//
					requestContentType = L"text/xml"; 
					requestDataSource = L"slot-request-info"; 
					//
					CComQIPtr<IStream> q(m_OutFileReader); 
					if (! q) throw MethodError(E_UNEXPECTED); 
					//
					if (m_OutStream) m_OutStream.Release(); 
					//
					m_OutStream.Attach(q.Detach()); 
				}
				//
				// ----
				// DataStreamInfo 
				//
				CComPtr<ISlotDataStreamInfo> dataStreamInfo;
				dataStreamInfo.Attach(
					CSlotDataStream::CreateDataStream<ISlotDataStreamInfo>(requestContentType) // new reference 
					); 
				if (! dataStreamInfo) throw MethodError(E_UNEXPECTED); 
				//
				CComBSTR bstrRDS(requestDataSource); 
				HRESULT rc = dataStreamInfo->SetDataStreamParameter( 
					CComBSTR(L"request-data-source"),
					CComVariant(bstrRDS) 
					);
				if (FAILED(rc)) throw MethodError(rc); 
				//
				rc = dataStreamInfo->put_DataStream(m_OutStream); // ��������� ����� ����� � �������� ������� 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				// ----
				// ���������� SlotXmlFilter 
				//
				bool filtrate = true; 
				//
				if (this->m_Uri.Path.Find(L"receipt") != -1)
				{
					//filtrate = false; 
				}
				if (this->m_Uri.Path.Find(L"upload-") != -1)
				{
					filtrate = false; 
				}
				//
				if (filtrate) 
				{
#					ifdef _DEBUG
					{
						TRACE_LINE(_T("���������...")); 
					}
#					endif
					//
					ISlotDataStreamInfo* xmlFilter = CSlotXmlFilter::CreateXmlFilter<ISlotDataStreamInfo>(); 
					if (! xmlFilter) throw MethodError(E_UNEXPECTED); 
					//
					if (GetSecurityStatus() != 0)
					{
						if (m_Client)
						{
							rc = xmlFilter->SetDataStreamParameter(
								CComBSTR(L"client"), 
								CComVariant((IUnknown*)m_Client) 
								);
							if (FAILED(rc)) throw MethodError(rc); 
						}
						else
						{
							throw MethodError(L"��������� ���� ��� ������� � ������� ��������"); 
						}
						//
						CComBSTR bstrYes(L"yes"); 
						rc = xmlFilter->SetDataStreamParameter(
							CComBSTR(L"-xml-sign"), 
							CComVariant(bstrYes) 
							);
						if (FAILED(rc)) throw MethodError(rc); 
					}
					//
					rc = dataStreamInfo->SetDataStreamParameter(
						CComBSTR(SLOT_DATA_STREAM_OUTPUT_FILTER_PARAM), 
						CComVariant((IUnknown*)xmlFilter) 
						);
					if (FAILED(rc)) throw MethodError(rc); 
					//
					// �������������� m_OutStream 
					//
					if (m_OutStream) m_OutStream.Release(); 
					//
					//rc = dataStreamInfo->get_DataStream(&m_OutStream); // �������� ����� ����� ��� ���������� ���������� 
					//if (FAILED(rc)) throw MethodError(rc); 
					//
					CComQIPtr<IStream> stream(dataStreamInfo); 
					if (! stream) throw MethodError(E_NOINTERFACE); 
					m_OutStream.Attach(stream.Detach()); 
				}
			}
			_Catch() 
		}



	public:
		// ----
		// ISlotRequestComposer 

		STDMETHOD(put_Url)(BSTR value)
		{
			try
			{
				CComBSTR bstrValue(value); 
				m_Url = string(bstrValue); 
				//
				if (m_Url.GetLength() == 0) throw MethodError(E_INVALIDARG);  
				//
				ParseUrl(m_Url); 
				//
				SetExtraHeaders_1(); 
						string s1 = Instance().GetCurrentPKHBinaryListStr(); 
						AppendHeaderToInfo(L"X--PKH", s1); 
				//
				return S_OK;
			}
			_ComCatch()
		}

		STDMETHOD(get_Url)(BSTR* out_value)
		{
			try
			{
				if (! out_value) throw MethodError(E_POINTER); 
				//
				CComBSTR v(m_Url);
				*out_value = v.Detach(); 
				return S_OK;
			}
			_ComCatch()
		}

		STDMETHOD(put_Client)(ISlotClient* value)
		{
			try
			{
				if (m_Client) m_Client.Release(); 
				//
				CComQIPtr<ISlotClient> client(value); 
				if (! client) throw MethodError(E_UNEXPECTED); 
				//
				m_Client.Attach(client.Detach());
				//
				return S_OK;
			}
			_ComCatch()
		}

		STDMETHOD(get_Client)(ISlotClient** out_value)
		{
			try
			{
				if (! out_value) throw MethodError(E_POINTER); 
				//
				if (m_Client)
				{
					CComPtr<ISlotClient> q(m_Client); 
					if (out_value) *out_value = q.Detach(); 
				}
				else
				{
					if (out_value) *out_value = 0; 
				}
				return S_OK;
			}
			_ComCatch()
		}

		PostContentStructure DiscoverPostContentStructure(IStream* stream)
		{
			try
			{
				if (! stream) throw MethodError(E_POINTER); 
				//
				LARGE_INTEGER m0;
				m0.QuadPart = 0; 
				ULARGE_INTEGER libNewPos;
				HRESULT rc = stream->Seek(m0,FILE_BEGIN,&libNewPos); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				PostContentStructure S = PostContentStructure_Data; 
				//
				Blob b;
				b.Allocate(18); 
				ULONG n = 0; 
				rc = stream->Read(b.GetBuffer(),b.Length(),&n); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
#				ifdef _DEBUG
				{
					TRACE_LINE1(_T("������� %d ���� ��� ������� ����������� ������"),n); 
					//
					Blob b_2;
					b_2.Allocate(n);
					CopyMemory(b_2.GetBuffer(),b.GetBuffer(),n); 
					for (int j = 0; j < (int)n; ++j) if (b_2[j] < 0x20) b_2[j] = '.'; 
					CStringA a((char*)b_2.GetBuffer(),n); 
					//
					TRACE_LINE(_S(a)); 
				}
#				endif
				//
				if (n < 5) 
				{
					// ----
					// ��������� ������ � ������� 
					//
					rc = stream->Seek(m0,FILE_BEGIN,&libNewPos); 
					if (FAILED(rc)) throw MethodError(rc); 
					//
					return S;
				}
				//
				string begin;
				//
				BYTE b0 = b[0];
				BYTE b1 = b[1];
				//
				if ((b0 == 0xFE) && (b1 == 0xFF)) // UTF-16 big-endian 
				{
					throw MethodError(E_INVALIDARG); 
				}
				else if ((b0 == 0xFF) && (b1 == 0xFE)) // UTF-16 little-endian 
				{
					begin = CStringW((const wchar_t*)(b.GetBuffer() + sizeof(wchar_t)),
						(b.Length()/sizeof(wchar_t)) - 1
						); 
				}
				else if (b0 == 0xEF)
				{
					throw MethodError(E_INVALIDARG); 
				}
				else
				{
					begin = _W(CStringA((const char*)b.GetBuffer(),n)); 
				}
				//
				if ((begin.Left(5) == L"<?xml") || (begin.Find(L"<") != -1)) 
				//if ((begin.Left(5) == L"<?xml")) 
				{
					S = PostContentStructure_Xml;
					//
					if (CSlotXmlFilter::IfSlotRequest(stream
						,&m_RootLocalName,&m_RootNsUri))
					{
						S = PostContentStructure_XmlSlotRequest; 
					}
				}
				//
				// ----
				// ��������� ������ � ������� 
				//
				rc = stream->Seek(m0,FILE_BEGIN,&libNewPos); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				return S; 
			}
			_Catch() 
		}

		inline void SetInfoDocumentDetails()
		{
			try
			{
				m_Info_E = m_Info.DocumentElement(); 
			}
			_Catch() 
		}

		inline void SetInfoDocument(XmlDocument doc)
		{
			try
			{
				m_Info = doc; 
				//
				SetInfoDocumentDetails(); 
			}
			_Catch() 
		}

		inline string GetNewUfml3FileEnvelope() 
		{
			string s = _W(COMMON_XML_START) +
				L"<envelope"
				L" xmlns=\"http://cabinet.example.com/schema/ufml3/rel-1/\""
				L" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\""
				L" uuid=\"" + NewGuidStr() +  L"\""
				L" xsi:schemaLocation=\"http://cabinet.example.com/schema/ufml3/rel-1/"
					L" http://cabinet.example.com/schema/ufml3/rel-1/ufml3.xsd\""
				L">"
				L"<file xsi:type=\"t601\">"
				L"<description></description>"
				L"<data></data>"
				L"</file>"
				L"</envelope>"
				;
			return s; 
			//
			// content-type="application/vnd.ms-excel" name="541_080908sber-1.xls" fund-num="131" form="651"
		}

		STDMETHOD(put_PostStream)(IStream* stream)
		{
			try
			{
				++m_PostStreamAssignCount; 
				if (m_PostStreamAssignCount == 10) 
				{
					throw MethodError(L"�������� ������ �������� ��� ��������� XML-��������"); 
				}
				//
				if (m_PostStream) 
				{
					m_PostStream.Release(); 
				}
				//
				if (stream)
				{
					// ��������� ����������� ����������� � ������ ������, - ���� ������� ���, 
					// �������� ������ �� ��������� ���� � ��������� ����� ������ �� �����. 
					// 
					ULARGE_INTEGER newPos;
					HRESULT rc;
					do
					{
						LARGE_INTEGER beginPos;
						beginPos.QuadPart = 0; 
						rc = stream->Seek(beginPos,FILE_BEGIN,&newPos); // ��������� ������������� ���� 
					}
					while (rc == E_PENDING);
					//
					if (rc == E_NOTIMPL)
					{
#						ifdef _DEBUG
						{
							TRACE_LINE(_T("����� �� ������������ ������� ����������� => ��������")); 
						}
#						endif
						//
						IStream* fileStream = CSlotFileReader::Create<IStream>(); // new reference 
						if (! fileStream) throw MethodError(E_UNEXPECTED); 
						//
						CComQIPtr<ISlotFileReader> fileReader(fileStream);
						if (! fileReader) throw MethodError(E_UNEXPECTED); 
						//
						HRESULT r2 = fileReader->CreateInCache(); 
						if (FAILED(r2)) throw MethodError(r2); 
						//
						r2 = fileReader->WriteStream(stream); 
						if (FAILED(r2)) throw MethodError(r2); 
						//
						m_PostStream.Attach(fileStream); 
					}
					else if (FAILED(rc)) 
					{
						throw MethodError(rc); 
					}
					else // S_OK 
					{
#						ifdef _DEBUG
						{
							TRACE_LINE(_T("����� ������������ ������� �����������")); 
						}
#						endif
						//
						// ����� �������� � ������� stream 
						//
						CComQIPtr<IStream> q(stream); 
						if (! q) throw MethodError(E_UNEXPECTED); 
						m_PostStream.Attach(q.Detach()); 
					}
					//
					//
					// ----
					// ���������� ��� ����������� 
					//
					PostContentStructure S = PostContentStructure_Data;
					try
					{
						S = DiscoverPostContentStructure(stream); 
					}
					catch(::::Exception& e)
					{
						TRACE_LOG(e.ToString()); 
						throw; 
					}
					// 
					if (S == PostContentStructure_XmlSlotRequest)
					{
						XmlDocument ri;
						ri.LoadStream(m_PostStream); 
						//
						SetInfoDocument(ri); 
						//
#						ifdef _DEBUG
						{
							TRACE_LINE(_T("���������� PostStream: ����� ������������ XML-�������� RequestInfo")); 
						}
#						endif
						//
						if (m_PostStream) m_PostStream.Release(); 
						//
						return S_OK;
					}
					else if ((m_RootLocalName == L"request") && 
						(m_RootNsUri == _W(_PUBLIC_CABINET_REQUEST_NSURI)))
					{
						XmlDocument cabRequest;
						cabRequest.LoadStream(m_PostStream); 
						//
						if (m_PostStream) m_PostStream.Release(); // ��������� ����� ����� ������ 
						//
						XmlNodeList upload_L = cabRequest.SelectNodes(
							L"/cabrequest:request/cabrequest:upload"); 
						//
						// ----
						// ������ �� �������� ��������� 
						//
						if (upload_L.Count() > 0) 
						{
							XmlElement E = (XmlElement)upload_L[0]; 
							//
							string uploadType = L"ufml3";
							if (E.HasAttribute(L"type"))
							{
								uploadType = E.GetAttribute(L"type"); 
							}
							//
							string path;
							Blob data;
							//
							if (E.HasAttribute(L"path"))
							{
								path = E.GetAttribute(L"path"); 
							}
							else
							{
								XmlNodeList L = E.SelectNodes(L"cabrequest:data"); 
								if (L.Count() > 0)
								{
									string data64 = ((XmlElement)L[0]).InnerText();
									if (data64.GetLength() > 0) data = FromBase64String(data64); 
								}
							}
							//
							// ��������� ���� 
							//
							CComQIPtr<IStream> stream;
							if (data.Length() > 0)
							{
								stream.Attach( CSlotMemoryReader::ReadBlob<IStream>(data) ); 
							}
							else if (path.GetLength() > 0)
							{
								stream.Attach( CSlotFileReader::OpenFile<IStream>(_S(path)) );
							}
							if (! stream) throw MethodError(E_NOINTERFACE); 
							//
							// ��������� ���� ��� �������� 
							//
							if (uploadType == L"file") 
							{
								XmlDocument doc;
								doc.LoadXml(GetNewUfml3FileEnvelope()); 
								//
								string contentType = L"application/octet-stream"; // !!! 
								//
								string fundNum = E.GetAttribute(L"fund-num");
								string form = E.GetAttribute(L"form");
								//
								string name = L"";
								int p1 = path.ReverseFind(L'\\'); 
								if (p1 == -1) p1 = path.ReverseFind(L'/'); 
								if (p1 != -1) name = path.Right(path.GetLength()-p1-1); 
								if (name.GetLength() == 0) throw MethodError(E_INVALIDARG); 
								//
								string description;
								{
									XmlElement r_descr_E = (XmlElement)E.SelectSingleNode(
										L"cabrequest:description"); 
									description = r_descr_E.InnerText(); 
								}
								//
								// ----
								// ������ 
								//
								Blob file_data = ReadAllFromStream(stream); 
								//
								// ----
								// ��������� �������� 
								//
								XmlElement file_E = (XmlElement)doc.SelectSingleNode(L"/ufml:envelope/ufml:file"); 
								//
								file_E.SetAttribute(L"content-type",contentType); 
								file_E.SetAttribute(L"name",name); 
								file_E.SetAttribute(L"form",form); 
								file_E.SetAttribute(L"fund-num",fundNum); 
								//
								XmlElement description_E = (XmlElement)file_E.SelectSingleNode(L"ufml:description"); 
								description_E.InnerText() = description;
								//
								XmlElement data_E = (XmlElement)file_E.SelectSingleNode(L"ufml:data"); 
								if (file_data.Length() > 0) data_E.InnerText() = __ToBase64(file_data); 
								//
								{
									CComPtr<ISlotFileReader> fr; 
									fr.Attach( CSlotFileReader::Create<ISlotFileReader>() ); 
									//
									HRESULT rc = fr->CreateInCache(); 
									if (FAILED(rc)) throw MethodError(rc); 
									//
									rc = fr->WriteXmlDocument(doc.GetXmlObjectInterface()); 
									if (FAILED(rc)) throw MethodError(rc); 
									//
									CComQIPtr<IStream> docStream(fr); 
									if (! docStream) throw MethodError(E_UNEXPECTED); 
									//
									// ����������� ����� ����� ��� POST 
									//
									rc = put_PostStream(docStream); 
									if (FAILED(rc)) throw MethodError(rc); 
								}
							}
						}
						//
						return S_OK; 
					}
					else if (S == PostContentStructure_Data)
					{
						string time_s = COleDateTime::GetCurrentTime().Format("%A, %B %d, %Y, %H:%M:%S"); 
						Blob signedInfo_b = WideStringToUTF8(time_s); 
						if (m_Client)
						{
							CComQIPtr<ISlotSigner> pSigner(m_Client);
							//
							HRESULT rc = pSigner->Start();
							if (FAILED(rc)) throw MethodError(rc);
							//
							int len = signedInfo_b.Length(); 
							rc = pSigner->AddBlobk(signedInfo_b.GetBuffer(),len); 
							if (FAILED(rc)) throw MethodError(rc);
							//
							CComBSTR bstrOriginalSig(_W("")); 
							CComBSTR bstrSignature64;
							rc = pSigner->GetSignature64_FCSM(bstrOriginalSig, &bstrSignature64);
							if (FAILED(rc)) throw MethodError(rc);
							//
							string s0 = _W(bstrSignature64); 
							AppendHeaderToInfo(L"X--AuthToken", s0); 
						}
						//
						// ----
						string s1 = Instance().GetCurrentPKHBinaryListStr(); 
						AppendHeaderToInfo(L"X--PKH", s1); 
					}
				}
				//
				return S_OK;
			}
			_ComCatch()
		}

		STDMETHOD(get_PostStream)(IStream** out_stream)
		{
			try
			{
				if (! out_stream) throw MethodError(E_POINTER); 
				//
				if (m_PostStream)
				{
					CComQIPtr<IStream> stream(m_PostStream); 
					*out_stream = stream.Detach(); 
				}
				else
				{
					*out_stream = 0; 
				}
				return S_OK;
			}
			_ComCatch()
		}

		STDMETHOD(get_OutStream)(IStream** out_stream)
		{
			try
			{
				if (! out_stream) throw MethodError(E_POINTER); 
				//
				if (m_OutStream)
				{
					CComQIPtr<IStream> stream(m_OutStream); 
					*out_stream = stream.Detach(); 
				}
				else
				{
					*out_stream = 0; 
				}
				return S_OK;
			}
			_ComCatch()
		}



		inline void AdjustClientInfo()
		{
			try
			{
				// ----
				// PKH
				//
				if (m_Info_E.IsEmpty()) throw MethodError(E_UNEXPECTED); 
				//
				if (m_Client)
				{
					CComBSTR bstrPkh; 
					HRESULT rc = m_Client->get_PublicKeyHash(&bstrPkh); 
					if (FAILED(rc)) throw MethodError(rc);
					//
					bool authenticated = false;
					if (rc == S_OK)
					{
						if (bstrPkh.Length() > 0) 
						{
							m_Info_E.SetAttribute(L"client-pkh",CComVariant(bstrPkh)); 
							authenticated = true; 
						}
					}
					//
					if (! authenticated)
					{
						ThrowErrorMessage(
							L"����������� ����,"
							L" ����������� ��� ����������� � ������� ������ �������"); 
					}
				}
			}
			_Catch() 
		}



		inline void SetErrorEnv() 
		{
			try
			{
			}
			_Catch() 
		}

		inline void ThrowErrorMessage(const string& msg) 
		{
			try
			{
				SetErrorEnv(); 
				//
				throw MethodError(msg); 
			}
			_Catch() 
		}



		// ��������� ������, ������������ ������������ ����������� ���������� ������ <slotrequest:info ... />  

		inline void CreateTempFile() 
		{
			try
			{
				if (! m_OutFileReader)
				{
					m_OutFileReader.Attach( CSlotFileReader::Create<ISlotFileReader>() ); 
				}
				//
				HRESULT rc = m_OutFileReader->CreateInCache(); 
				if (FAILED(rc)) throw MethodError(rc); 
			}
			_Catch()
		}

		inline void CopyInfoToFile() 
		{
			try
			{
				IUnknown* infoUnk = static_cast<IUnknown*>((IXMLDOMNode*)m_Info); 
				//
				HRESULT rc = m_OutFileReader->WriteXmlDocument(infoUnk); 
				if (FAILED(rc)) throw MethodError(rc); 
			}
			_Catch() 
		}

		inline void CopyInfoToTempFile() 
		{
			try
			{
				CreateTempFile(); 
				//
				CopyInfoToFile();
			}
			_Catch() 
		}

		STDMETHOD(Open)()
		{
			try
			{
#				ifdef _DEBUG
				{
					TRACE_LINE(_T("SlotRequestComposer: ���������...")); 
				}
#				endif
				//
				if (m_Ready) return S_OK; // ��� ������� 
				//
				// -----------------------------------------------------------------------------------
				// ���������
				//
				// ----
				// 1. ��������� ��������� URL � GET 
				//
				{
					// URL ���������������� � ������ ������ �������� �������� ParseUrl() 
				}
				//
				// ----
				// 2. ����������� �������� ������, ���� ����� 
				//
				{
				}
				//
				// ----
				// 3. ����������� ��������� URL ��� POST 
				//
				{
					AdjustClientInfo(); 
				}
				//
				//
				//
				// -----------------------------------------------------------------------------------
				// ������������� ��������������� ��������� 
				//
				// ���������: ���������� ��������� �� ��������� ���� 
				{
					CopyInfoToTempFile();
					//
					// ��������� ������ �� ������ 
					//
					OpenRequestFile(); 
				}
				//
				m_Ready = true; 
				//
				return S_OK;
			}
			_ComCatch() 
		}






		// ----
		// IStream

		STDMETHOD(Read)(
			void *pv,
			ULONG cb,
			ULONG *pcbRead)
		{
			try
			{
				if (! m_OutStream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = m_OutStream->Read(pv,cb,pcbRead); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		STDMETHOD(Write)(
			const void* pv,
			ULONG cb,
			ULONG* pcbWritte)
		{
			try
			{
				if (! m_OutStream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = m_OutStream->Write(pv,cb,pcbWritte); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		HRESULT STDMETHODCALLTYPE Seek( 
			/* [in] */ LARGE_INTEGER dlibMove,
			/* [in] */ DWORD dwOrigin,
			/* [out] */ ULARGE_INTEGER *plibNewPosition) 
		{
			try
			{
				if (! m_OutStream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = m_OutStream->Seek(dlibMove,dwOrigin,plibNewPosition); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		HRESULT STDMETHODCALLTYPE SetSize( 
			/* [in] */ ULARGE_INTEGER libNewSize) 
		{
			try
			{
				if (! m_OutStream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = m_OutStream->SetSize(libNewSize); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		HRESULT STDMETHODCALLTYPE CopyTo( 
			/* [unique][in] */ IStream *pstm,
			/* [in] */ ULARGE_INTEGER cb,
			/* [out] */ ULARGE_INTEGER *pcbRead,
			/* [out] */ ULARGE_INTEGER *pcbWritten) 
		{
			try
			{
				if (! m_OutStream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = m_OutStream->CopyTo(pstm,cb,pcbRead,pcbWritten); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		HRESULT STDMETHODCALLTYPE Commit( 
			/* [in] */ DWORD grfCommitFlags) 
		{
			try
			{
				if (! m_OutStream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = m_OutStream->Commit(grfCommitFlags); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		HRESULT STDMETHODCALLTYPE Revert() 
		{
			try
			{
				if (! m_OutStream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = m_OutStream->Revert(); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		HRESULT STDMETHODCALLTYPE LockRegion( 
			/* [in] */ ULARGE_INTEGER libOffset,
			/* [in] */ ULARGE_INTEGER cb,
			/* [in] */ DWORD dwLockType) 
		{
			try
			{
				if (! m_OutStream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = m_OutStream->LockRegion(libOffset,cb,dwLockType); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		HRESULT STDMETHODCALLTYPE UnlockRegion( 
			/* [in] */ ULARGE_INTEGER libOffset,
			/* [in] */ ULARGE_INTEGER cb,
			/* [in] */ DWORD dwLockType) 
		{
			try
			{
				if (! m_OutStream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = m_OutStream->UnlockRegion(libOffset,cb,dwLockType); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		HRESULT STDMETHODCALLTYPE Stat( 
			/* [out] */ STATSTG *pstatstg,
			/* [in] */ DWORD grfStatFlag) 
		{
			try
			{
				if (! m_OutStream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = m_OutStream->Stat(pstatstg,grfStatFlag); 
				//if (FAILED(rc)) throw MethodError(rc); 
#				ifdef _DEBUG
				if (FAILED(rc))
				{
					TRACE_LOG(_T("������: ") + _S(MethodError(rc).ToString())); 
				}
#				endif
				return rc; 
			}
			_ComCatch() 
		}

		HRESULT STDMETHODCALLTYPE Clone( 
			/* [out] */ IStream **ppstm) 
		{
			try
			{
				try
				{
					if (! ppstm) throw MethodError(E_POINTER); 
					//
					if (! m_OutStream) throw MethodError(E_NOINTERFACE); 
					//
					CComPtr<IStream> S;
					S.Attach( Create<IStream>() ); 
					//
					CSlotRequestComposer* pInfo = static_cast<CSlotRequestComposer*>((IStream*)S); 
					//
					CComPtr<IStream> cloned; 
					HRESULT rc = m_OutStream->Clone(&cloned); 
					if (FAILED(rc)) throw MethodError(rc); 
					if (! cloned) throw MethodError(E_UNEXPECTED); 
					//
					pInfo->m_OutStream.Attach( cloned.Detach() ); 
					//
					*ppstm = S.Detach(); 
					return S_OK; 
				}
				_ComCatch() 
			}
			_ComCatch() 
		}
	};
	// CSlotRequestComposer 

} // namespace  
