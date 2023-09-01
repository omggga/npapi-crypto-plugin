/*
 AX_SlotXmlFilter.h --- ���������� ������ ������ XML: 

	����������� processing-instructions: 

	<?-xml-fragment ?>		source-url="..." - ���� � �����, xpath="..." - ��� ��������� 

	<?-xml-data ?>			source-url="..." - ���� � �����, type="..." - 'Text' ��� 'CData' 

	<?-xml-sign-next ?>		��������� ��������� ������� / pkh="(base64)" 

 $Name: work1 $
 $Revision: 1.1.2.4 $
 $Date: 2009/05/18 13:21:31 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include <xmllite.h>

#include "../../low-level/SmartMap.h"
#include "../../low-level/SmartXml.h"
#include "../../low-level/SmartUtil.h"

#include "../../alg/Alg_1_8_2.h"
#include "../../alg/Alg_1_8_4.h"

#include "../../inet-proto/AppInstance.h"

#include "AX_SlotDataStream.h"

#include "../interfaces/ISlotClient.h"
#include "../interfaces/ISlotDataStreamInfo.h"
#include "../interfaces/ISlotXmlFilter.h"


//#ifndef _HASHER_TYPE_XML_SIGNATURE
//#define _HASHER_TYPE_XML_SIGNATURE (L"1.2.643.6.2.1.8.8") 
//#endif 

#ifndef _HASHER_TYPE_XML_COLLECT_NS
#define _HASHER_TYPE_XML_COLLECT_NS (L"collect-ns")
#endif 

#ifndef _HASHER_TYPE_XML_NORMALIZE
#define _HASHER_TYPE_XML_NORMALIZE (L"1.2.643.6.2.1.8.1")
#endif 

#ifndef _HASHER_TYPE_XML_HASH
#define _HASHER_TYPE_XML_HASH (L"1.2.643.6.2.1.8.1+sha1+base64")
#endif 


namespace  {

	// =================================================
	// ���������� XML-�������:
	//		ISlotDataStreamInfo	- ��� ����������� ��������� XML-��������� 
	//		IStream				- �������������� �������� � ����� ������ 
	//		IXmlWriter 

	class ATL_NO_VTABLE CSlotXmlFilter : 
		public CComObjectRootEx<CComSingleThreadModel>, 
		public CComCoClass<CSlotXmlFilter>, 
		public ISlotDataStreamInfo, 
		public ISlotXmlFilter, 
		public ISAXContentHandler, 
		public IXmlWriter // ��������� ������������� 
	{
	public:
		template<class I>
		inline static I* Create() // new reference 
		{
			try
			{
				typedef CComObject<CSlotXmlFilter> _CoClass; 
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

		// ������ ����������� ������ XML --> XML  

		template<class I>
		inline static I* CreateXmlFilter() // new reference 
		{
			try
			{
				return Create<I>(); // �� ��������� �������� ������ ����� ������ 
			}
			_Catch()
		}

		// ������ ������ XML-hasher'� 

		template<class I>
		inline static I* CreateHasher(const string& hashType,
			IStream* inputStream=0, 
			bool signDocument=false
			) // new reference 
		{
			try
			{
				CComPtr<I> i;
				i.Attach( Create<I>() ); // attaching new reference 
				//
				// Hasher 
				//
				CComQIPtr<ISlotDataStreamInfo> streamInfo(i); 
				if (! i) throw MethodError(E_NOINTERFACE); 
				//
				CComBSTR bstrHashType(hashType); 
				HRESULT rc = streamInfo->SetDataStreamParameter(
					CComBSTR(L"hash-type"),
					CComVariant(bstrHashType)
					); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				if (signDocument)
				{
					CComBSTR bstrYes(L"yes"); 
					//
					CComBSTR bstrHashType(hashType); 
					HRESULT rc = streamInfo->SetDataStreamParameter(
						CComBSTR(L"-xml-sign"),
						CComVariant(bstrYes)
						); 
					if (FAILED(rc)) throw MethodError(rc); 
				}
				//
				if (inputStream) // ����� �������, ��� ��������� ����� ���������� ������� 
				{
					// ����� put_DataStream ��������� ����������� ����� ������� Open() 
					//
					CComPtr<IStream> s2;
					HRESULT rc1 = inputStream->Clone(&s2); 
					if (FAILED(rc1)) 
					{
						throw MethodError(L"������ SlotXmlFilter:301"); 
						//throw MethodError(rc1); 
					}
					//
					rc1 = streamInfo->put_DataStream((IStream*)s2); 
					if (FAILED(rc1)) 
					{
						throw MethodError(L"������ SlotXmlFilter:302"); 
						//throw MethodError(rc1); 
					}
				}
				//
				return i.Detach(); 
			}
			_Catch()
		}

		// ������ ������ ��� ������ PI 

		template<class I>
		inline static I* CreatePISearch(const string& PIName,IStream* inputStream=0 ) // new reference 
		{
			try
			{
				CComPtr<I> i;
				i.Attach( Create<I>() ); // attaching new reference 
				//
				// PI Search 
				//
				CComQIPtr<ISlotDataStreamInfo> streamInfo(i); 
				if (! i) throw MethodError(E_NOINTERFACE); 
				//
				CComBSTR bstrPIName(PIName);
				HRESULT rc = streamInfo->SetDataStreamParameter(CComBSTR(L"search-pi"),CComVariant(bstrPIName)); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				if (inputStream) // ����� �������, ��� ��������� ����� ���������� ������� 
				{
					// ����� put_DataStream ��������� ����������� ����� ������� Open() 
					//
					CComPtr<IStream> s2;
					HRESULT rc1 = inputStream->Clone(&s2); 
					if (FAILED(rc1)) 
					{
						throw MethodError(L"������ SlotXmlFilter:303"); 
						//throw MethodError(rc1); 
					}
					//
					rc1 = streamInfo->put_DataStream((IStream*)s2); 
					if (FAILED(rc1)) 
					{
						throw MethodError(L"������ SlotXmlFilter:304"); 
						//throw MethodError(rc1); 
					}
				}
				//
				return i.Detach(); 
			}
			_Catch()
		}

		// ������ ������ ��� ������ ��������

		inline static bool SearchRoot(IStream* inputStream,
			const string& rootLocalName, 
			const string& rootUri, 
			string* out_RootLocalName=0,
			string* out_RootNsUri=0 
			)
		{
			try
			{
				if (! inputStream) throw MethodError(E_POINTER); 
				//
				CComPtr<ISlotXmlFilter> filter;
				filter.Attach( Create<ISlotXmlFilter>() ); // attaching new reference 
				//
				// Root Search 
				//
				CComQIPtr<ISlotDataStreamInfo> streamInfo(filter); 
				if (! streamInfo) throw MethodError(E_NOINTERFACE); 
				//
				CComBSTR bstrName(rootLocalName);
				HRESULT rc = streamInfo->SetDataStreamParameter(
					CComBSTR(L"search-root-local-name"),
					CComVariant(bstrName)
					); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				CComBSTR bstrNsUri(rootUri);
				rc = streamInfo->SetDataStreamParameter(
					CComBSTR(L"search-root-ns"),
					CComVariant(bstrNsUri)
					); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				{
					CComPtr<IStream> s2;
					HRESULT rc = inputStream->Clone(&s2); 
					if (FAILED(rc)) 
					{
						throw MethodError(L"������ SlotXmlFilter:305"); 
						//throw MethodError(rc); 
					}
					//
					rc = streamInfo->put_DataStream((IStream*)s2); 
					if (FAILED(rc)) 
					{
						throw MethodError(L"������ SlotXmlFilter:306"); 
						//throw MethodError(rc); 
					}
				}
				//
				{
					HRESULT rc = filter->Open(); 
					if (FAILED(rc)) throw MethodError(rc); 
				}
				//
				CComVariant v;
				string vStr; 
				rc = streamInfo->GetDataStreamParameter(
					CComBSTR(L"root-found"),&v); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				if (out_RootLocalName)
				{
					HRESULT rc = streamInfo->GetDataStreamParameter(
						CComBSTR(L"root-local-name"),&v); 
					if (FAILED(rc)) throw MethodError(rc); 
					vStr = L""; 
					if (v.vt == VT_BSTR) vStr = _W(CComBSTR(v.bstrVal)); 
					//
					*out_RootLocalName = vStr; 
				}
				//
				if (out_RootNsUri)
				{
					HRESULT rc = streamInfo->GetDataStreamParameter(
						CComBSTR(L"root-ns-uri"),&v); 
					if (FAILED(rc)) throw MethodError(rc); 
					vStr = L""; 
					if (v.vt == VT_BSTR) vStr = _W(CComBSTR(v.bstrVal)); 
					//
					*out_RootNsUri = vStr; 
				}
				//
				return (rc == S_OK); 
			}
			_Catch()
		}

		inline static bool IfSlotRequest(IStream* stream
			,string* out_RootLocalName=0,string* out_RootNsUri=0)
		{
			try
			{
				return SearchRoot(stream,L"info",L"urn::slot-request"
					,out_RootLocalName,out_RootNsUri); 
			}
			_Catch()
		}



	protected:
		// ----
		// ������ 

		// ���� 

		CComPtr<IStream> m_InputStream; // �������� ����� ���������������� XML-��������� 

		// ��������� 

		CComPtr<ISlotDataStreamInfo> m_Info; 

		bool m_WriteXmlOutput; 

		// ������ 

		CComPtr<ISlotClient> m_Client; 

		// ��������� 

		// XML: 

		CComPtr<IXmlWriter> m_XmlWriter; // �������� ������������ XML (����� � ���� ��� ������ ������) 

		CComPtr<IStream> m_OutStream; // ����� ��������������� ��������� (������) 

		bool m_IsOpen; 

		// PI: 

		string m_PIName; 

		// Search Root 

		string m_SearchRootName; 
		string m_SearchRootNsUri; 

		// Signature

		bool m_SignDocumentRoot; 

		// ����������� �������� ��������� ���������� 
		
		bool m_F_skipCurrent; 
		bool m_F_skipNext; 
		int m_F_skipElementLevel; 
		bool m_F_skipX509Cert; 

		string m_elementUuid; 
		string m_elementHash64; 


		// ----
		// ������������ 

		inline void Clear() 
		{
			m_Level = 0; 
			m_SignatureLevel = -1; 
			m_PINum = 0; 
			m_WriteXmlOutput = true; 
			m_HashOn = false; 
			m_SignDocumentRoot = false;
			m_IsOpen = false; 
			//
			// ����������� �������� ��������� ���������� 
			//
			m_F_skipCurrent = false; 
			m_F_skipNext = false; 
			m_F_skipElementLevel = -1; 
			m_F_skipX509Cert = false; 
		}

		inline void Free() 
		{
			// ...
			//
			Clear();
		}

		inline void SetInputStream(IStream* stream) 
		{
			try
			{
				if (! stream) throw MethodError(E_INVALIDARG); 
				//
				if (m_InputStream) m_InputStream.Release(); 
				//
				if (stream)
				{
					CComQIPtr<IStream> q(stream); 
					if (! q) throw MethodError(E_NOINTERFACE); 
					m_InputStream.Attach(q.Detach()); 
				}
			}
			_Catch() 
		}

		inline static int SearchPIByNameInStream(IStream* stream,const string& piName)
		{
			try
			{
				CComPtr<ISlotDataStreamInfo> searchPi;
				searchPi.Attach(
					CreatePISearch<ISlotDataStreamInfo>(piName,stream) // new reference 
					);
				if (! searchPi) throw MethodError(E_UNEXPECTED); 
				//
				CComQIPtr<ISlotXmlFilter> searchPi_f(searchPi);
				if (! searchPi_f) throw MethodError(E_UNEXPECTED); 
				//
				HRESULT rc = searchPi_f->Open(); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				CComVariant v;
				rc = searchPi->GetDataStreamParameter(CComBSTR(L"search-pi-result"),&v); 
				if (FAILED(rc)) throw MethodError(rc); 
				if (v.vt != VT_BSTR) throw MethodError(E_UNEXPECTED); 
				//
				int n = _wtoi(v.bstrVal); 
				//
				return (int)n; 
			}
			_Catch() 
		}

		inline int SearchPIByName(const string& piName) 
		{
			try
			{
				return SearchPIByNameInStream(m_InputStream,piName); 
			}
			_Catch() 
		}

		inline static int SearchHashInStream(IStream* stream,const string& piName, 
			string& m_elementHash64, string& m_elementUuid)
		{
			try
			{
				CComPtr<ISlotDataStreamInfo> searchPi;
				searchPi.Attach(
					CreatePISearch<ISlotDataStreamInfo>(piName,stream) // new reference 
					);
				if (! searchPi) throw MethodError(E_UNEXPECTED); 
				//
				CComQIPtr<ISlotXmlFilter> searchPi_f(searchPi);
				if (! searchPi_f) throw MethodError(E_UNEXPECTED); 
				//
				HRESULT rc = searchPi_f->Open(); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				CComVariant v;
				rc = searchPi->GetDataStreamParameter(CComBSTR(L"search-pi-result"),&v); 
				if (FAILED(rc)) throw MethodError(rc); 
				if (v.vt != VT_BSTR) throw MethodError(E_UNEXPECTED); 
				//
				int n = _wtoi(v.bstrVal); 
				if (n != 0)
				{
					rc = searchPi->GetDataStreamParameter(CComBSTR(L"search-element-hash"),&v); 
					if (rc == S_OK) m_elementHash64 = _W(v.bstrVal); 
					//
					rc = searchPi->GetDataStreamParameter(CComBSTR(L"search-element-uuid"),&v); 
					if (rc == S_OK) m_elementUuid = _W(v.bstrVal); 
				}
				//
				return (int)n; 
			}
			_Catch() 
		}




		// ----
		// ��������� ��������� 

		inline void Start()
		{
			try
			{
				HRESULT rc; 
				//
				Clear();
				//
				CheckWriteXmlOutput(); 
				CheckPISearch(); 
				CheckHasher(); 
				//
				if (fWriteXmlOutput() || fHasher()) 
				{
					if (!m_OutStream)
					{
						// ----
						// ������ ��������� ���� ��� ������ ��������������� ��������� 
						//
						//
						CComPtr<ISlotFileReader> outFileReader; 
						outFileReader.Attach(
							CSlotFileReader::Create<ISlotFileReader>() // new reference 
							);
						if (! outFileReader) throw MethodError(E_UNEXPECTED); 
						//
						HRESULT rc = outFileReader->CreateInCache(); 
						if (FAILED(rc)) throw MethodError(rc); 
						//
						// ����� ��� ������ 
						//
						CComQIPtr<IStream> oStream(outFileReader); 
						if (! oStream) throw MethodError(E_UNEXPECTED); 
						//
						if (m_OutStream) m_OutStream.Release(); 
						//
						m_OutStream.Attach(oStream.Detach()); 
						//
						//// �������� ����� ������������ ������������ ��� ������ 
						////
						//CComQIPtr<IStream> writerStream(outFileReader); 
						//if (! writerStream) throw MethodError(E_UNEXPECTED); 
					}
					//
					//
					//
					// ----
					// ������ XmlWriter
					//
					if (m_XmlWriter) m_XmlWriter.Release(); 
					//
					if (fWriteXmlOutput()) 
					{
						// ����� �� ����������� ������ 
						{
							bool fSignXml = true; 
							CComVariant _v; 
							rc = GetDataStreamParameter(CComBSTR(L"-xml-sign"),&_v); 
							fSignXml = (rc == S_OK); 
							//
							if (fSignXml) 
							{
								SearchHashInStream(m_InputStream, L"-element-hash", 
									m_elementHash64, m_elementUuid); 
								//
								if (! SearchPIByName(L"-xml-sign-next")) 
								{
									m_SignDocumentRoot = true; 
								}
								//
								if (SearchPIByName(L"-skip-X509Certificate")) 
								{
									m_F_skipX509Cert = true; 
								}
							}
						}
						// 
						// ������ ����������� XmlWriter 
						//
						rc = CreateXmlWriter(__uuidof(IXmlWriter),(void**)&m_XmlWriter,NULL); 
						if (FAILED(rc)) throw MethodError(rc); 
						if (! m_XmlWriter) 
						{
							throw MethodError(E_UNEXPECTED); 
						}
						//
						rc = m_XmlWriter->SetOutput( (IUnknown*)(IStream*)m_OutStream ); 
						if (FAILED(rc)) throw MethodError(rc); 
					}
					else if (fHasher()) 
					{
						// ����� �� ����������� ������ 
						{
							bool fSignXmlRoot = true; 
							CComVariant _v; 
							rc = GetDataStreamParameter(CComBSTR(L"-xml-sign"),&_v); 
							fSignXmlRoot = (rc == S_OK); 
							//
							if (fSignXmlRoot) 
							{
								m_SignDocumentRoot = true; 
								//
								Hasher_StartDocument(); 
								m_HashOn = true; 
							}
						}
						//
						CComQIPtr<IXmlWriter> w(this); 
						if (! w) throw MethodError(E_NOINTERFACE); 
						m_XmlWriter.Attach(w.Detach()); 
						//
						if (! m_XmlWriter) throw MethodError(E_UNEXPECTED); 
						//
						// ��������� �������� 
						//						
					}
				}
				else if (fSearchPI()) 
				{
					m_SearchPIName = m_PIName; 
					m_SearchPINum = 0;
				}
			}
			_Catch() 
		}

		inline void Parse() 
		{
			try
			{
				// ������������ �������� �������� 
				// 
				CComPtr<ISAXXMLReader> xmlReader; 
				HRESULT rc = xmlReader.CoCreateInstance(MSXML2_SAXREADER_ProgId); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
//#				ifdef _DEBUG
//				{
//					LARGE_INTEGER m0;
//					m0.QuadPart = 0;
//					ULARGE_INTEGER npos;
//					rc = m_InputStream->Seek(m0,FILE_BEGIN,&npos);
//					if (FAILED(rc)) throw MethodError(rc); 
//					//
//					File f;
//					f.OpenToWrite(_T("d:\\stream-data.xml")); 
//					//
//					Blob responseData;
//					bool done;
//					do
//					{
//						done = false;
//						//
//						int ds = 1024;
//						int n = responseData.Length(); 
//						responseData.Expand(n + ds);
//						ULONG bytesRead = 0;
//						HRESULT rc = m_InputStream->Read(responseData.GetBuffer() + n,(ULONG)ds,&bytesRead); 
//						if (rc == E_PENDING)
//						{
//							// ���...
//						}
//						else if (FAILED(rc))
//						{
//							throw MethodError(rc); 
//						}
//						else 
//						{
//							responseData.SetSize(n + (int)bytesRead);
//							//
//							if (rc == S_FALSE)
//							{
//								done = true;
//							}
//						}
//					}
//					while (! done);
//					//
//					f.Replace((const char*)responseData.GetBuffer(), responseData.Length()); 
//					//
//					f.Close(); 
//				}
//#				endif
				//
				LARGE_INTEGER m0;
				m0.QuadPart = 0;
				ULARGE_INTEGER npos;
				rc = m_InputStream->Seek(m0,FILE_BEGIN,&npos);
				if (FAILED(rc)) throw MethodError(rc); 
				//
				rc = xmlReader->putContentHandler((ISAXContentHandler*)this); 
				if (FAILED(rc)) throw MethodError(rc);
				//
				rc = xmlReader->parse(CComVariant( (IStream*)m_InputStream )); // ����� � m_OutStream 
				if (FAILED(rc)) 
				{
					throw MethodError(rc); 
				}
				//
				// ��������� � ������... 
				//
				if (fWriteXmlOutput())
				{
					if (! m_OutStream) 
					{
						throw MethodError(E_UNEXPECTED); 
					}
					CComQIPtr<ISlotFileReader> outFileReader(m_OutStream); 
					if (outFileReader) // ���� ����� m_OutStream ���������� �� ������ ��� ISlotFileReader 
					{
						rc = outFileReader->WriteClose(); // ����� ��������� 
						if (FAILED(rc)) throw MethodError(rc); 
					}
					rc = outFileReader->Open(); 
					if (FAILED(rc)) throw MethodError(rc); 
				}
			}
			_Catch() 
		}

		STDMETHOD(Open)() 
		{
			try
			{
				if (m_IsOpen) return S_OK; // ������! 
				//
				// ��������� SlotXmlFilter: � ���������� ���������� (IStream*)m_OutStream 
				//
				Start(); 
				//
				// ������ ��������������� XML-��������, ��������� � ���������� �������������� �������� � ���� 
				//
				Parse(); // ���������: (IStream*)m_OutFileReader 
				//
				m_IsOpen = true; 
				return S_OK; 
			}
			_ComCatch() 
		}

		STDMETHOD(put_OutStream)(IStream* outStream) 
		{
			try
			{
				if (m_OutStream) m_OutStream.Release(); 
				// 
				if (outStream)
				{
					CComQIPtr<IStream> q(outStream);
					m_OutStream.Attach(q.Detach()); 
				}
				return S_OK; 
			}
			_ComCatch() 
		}

		STDMETHOD(get_OutStream)(IStream** out_outStream) 
		{
			try
			{
				if (!out_outStream) throw MethodError(E_INVALIDARG); 
				//
				if (m_OutStream)
				{
					CComQIPtr<IStream> q(m_OutStream); 
					*out_outStream = q.Detach(); 
				}
				else
				{
					*out_outStream = 0; 
				}
				return S_OK; 
			}
			_ComCatch() 
		}



	public:
		CSlotXmlFilter()
		{
			Clear(); 
		}

		BEGIN_COM_MAP(CSlotXmlFilter)
			COM_INTERFACE_ENTRY_IID(__uuidof(ISlotDataStreamInfo),ISlotDataStreamInfo)
			COM_INTERFACE_ENTRY_IID(__uuidof(ISlotXmlFilter),ISlotXmlFilter)
		END_COM_MAP()

		DECLARE_PROTECT_FINAL_CONSTRUCT()

		HRESULT FinalConstruct()
		{
			m_Info.Attach(
				CSlotDataStream::Create<ISlotDataStreamInfo>() // new reference 
				); 
			//
			return S_OK;
		}

		void FinalRelease() 
		{
			Free();
		}



	public:
		// ---------------------------------------------------------------------------------------
		// ISlotDataStreamInfo 

		STDMETHOD(put_DataStream)(IStream* inputStream) 
		{
			try
			{
				if (! inputStream) throw MethodError(E_POINTER); 
				//
				CComQIPtr<IStream> q(inputStream); 
				if (! q) throw MethodError(E_NOINTERFACE); 
				m_InputStream.Attach(q.Detach()); 
				//
				// ��������� � �������� m_Info; 
				//
				if (m_Info)
				{
					HRESULT rc = m_Info->put_DataStream(m_InputStream); 
					if (FAILED(rc)) throw MethodError(rc); 
				}
				//
				return S_OK; 
			}
			_ComCatch()
		}

		STDMETHOD(get_DataStream)(IStream** out_dataStream) 
		{
			try
			{
				if (! out_dataStream) throw MethodError(E_POINTER); 
				//
				// ���� ���������� ��������� SlotXmlFilter
				//
				HRESULT rc = Open(); // � ���������� ���������� (IStream*)m_OutStream 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				// ���������� m_OutStream 
				//
				CComPtr<IStream> stream;
				if (m_OutStream) 
				{
					CComQIPtr<IStream> q(m_OutStream); 
					if (! q) throw MethodError(E_NOINTERFACE); 
					stream.Attach(q.Detach()); 
				}
				//
				if (stream)
				{
					*out_dataStream = stream.Detach(); 
				}
				else
				{
					*out_dataStream = NULL; 
				}
				return S_OK; 
			}
			_ComCatch() 
		}



		// ��������� 

		STDMETHOD(GetDataStreamParameter)(BSTR name,VARIANT* out_value)
		{
			try
			{
				if (! out_value) throw MethodError(E_POINTER); 
				//
				string n(name); 
				//
				if (n == SLOT_XML_FILTER_IN_STREAM_PARAM) 
				{
					if (m_InputStream)
					{
						CComVariant v((IUnknown*)(IStream*)m_InputStream); 
						if (out_value) 
						{
							HRESULT rc = v.Detach(out_value); 
							if (FAILED(rc)) throw MethodError(rc); 
						}
						return S_OK; 
					}
					else
					{
						return S_FALSE; // not found 
					}
				}
				else
				{
					if (! m_Info) throw MethodError(HRESULT_FROM_WIN32(ERROR_NO_DATA)); 
					//
					HRESULT rc = m_Info->GetDataStreamParameter(name,out_value); 
					if (FAILED(rc)) throw MethodError(rc); 
					return rc; // found or not? 
				}
			}
			_ComCatch() 
		}

		CComPtr<ISlotSigner> m_Client_Signer; 

		Blob m_Client_Certificate;

		inline void LoadClientData() 
		{
			try
			{
				//LOCK// PKCS11_Manager::Lock lock;
				//
				{
					if (m_Client_Signer) m_Client_Signer.Release(); 
					m_Client_Certificate.Free(); 
				}
				//
				// ----
				// Signer 
				//
				m_Client_Signer.Attach(
					Client_GetSigner_1() 
					);
				//
				// ----
				// Certificate 
				//
				m_Client_Certificate = Client_GetCertData_1(); 
			}
			_Catch() 
		}

		ISlotSigner* Client_GetSigner() // new reference (!) 
		{
			try
			{
				//LOCK// PKCS11_Manager::Lock lock;
				//
				if (! m_Client_Signer) return 0; 
				//
				CComQIPtr<ISlotSigner> q(m_Client_Signer); 
				//
				return q.Detach(); 
			}
			_Catch() 
		}

		Blob Client_GetCertData() 
		{
			try
			{
				return m_Client_Certificate; 
			}
			_Catch()
		}

		STDMETHOD(SetDataStreamParameter)(BSTR name,VARIANT v)
		{
			try
			{
				string n(name); 
				//
				if (n == SLOT_XML_FILTER_IN_STREAM_PARAM) 
				{
					if (m_InputStream) m_InputStream.Release(); 
					//
					if (v.vt == VT_UNKNOWN) 
					{
						if (v.punkVal)
						{
							CComQIPtr<IStream> stream(v.punkVal); 
							if (! stream) throw MethodError(E_NOINTERFACE); 
							//
							HRESULT rc = put_DataStream(stream); // ~ put_InputStream 
							if (FAILED(rc)) throw MethodError(rc); 
							return rc; 
						}
						else
						{
							throw MethodError(E_INVALIDARG); 
						}
					}
					else
					{
						throw MethodError(E_INVALIDARG); 
					}
					//
					return S_OK; 
				}
				else if (n == L"client") 
				{
					if (m_Client) m_Client.Release(); 
					//
					if (v.vt == VT_UNKNOWN) 
					{
						if (v.punkVal)
						{
							CComQIPtr<ISlotClient> client(v.punkVal); 
							if (! client) throw MethodError(E_NOINTERFACE); 
							//
							m_Client.Attach(client.Detach()); 
							//
							LoadClientData(); 
							//
							return S_OK; 
						}
						else
						{
							throw MethodError(E_INVALIDARG); 
						}
					}
					else
					{
						throw MethodError(E_INVALIDARG); 
					}
				}
				else
				{
					if (! m_Info) throw MethodError(HRESULT_FROM_WIN32(ERROR_NO_DATA)); 
					//
					HRESULT rc = m_Info->SetDataStreamParameter(name,v); 
					if (FAILED(rc)) throw MethodError(rc); 
					return rc; 
				}
			}
			_ComCatch() 
		}

		inline string GetParameter(const string& n)
		{
			try
			{
				CComVariant v; 
				HRESULT r = GetDataStreamParameter(CComBSTR(n),&v); 
				if (r == S_OK)
				{
					if (v.vt == VT_BSTR)
					{
						string value(v.bstrVal); 
						return value; 
					}
					else
					{
						throw MethodError(E_INVALIDARG); 
					}
				}
				else
				{
					throw MethodError(HRESULT_FROM_WIN32(ERROR_NOT_FOUND)); 
				}
			}
			_Catch() 
		}

		inline bool Parameters_ContainsKey(const string& n)
		{
			try
			{
				CComVariant v; 
				HRESULT r = GetDataStreamParameter(CComBSTR(n),&v); 
				if (r == S_OK) return true; 
				return false; 
			}
			_Catch() 
		}

		STDMETHOD(get_ContentType)(BSTR* out_contentType)
		{
			try
			{
				if (! m_Info) throw MethodError(HRESULT_FROM_WIN32(ERROR_NO_DATA)); 
				//
				HRESULT rc = m_Info->get_ContentType(out_contentType); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		STDMETHOD(put_ContentType)(BSTR contentType)
		{
			try
			{
				if (! m_Info) throw MethodError(HRESULT_FROM_WIN32(ERROR_NO_DATA)); 
				//
				HRESULT rc = m_Info->put_ContentType(contentType); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		inline void CheckWriteXmlOutput() 
		{
			try
			{
				if (Parameters_ContainsKey(L"write-xml-output"))
				{
					string vStr = GetParameter(L"write-xml-output"); 
					m_WriteXmlOutput = GetFlagValue(vStr); 
				}
			}
			_Catch() 
		}

		inline void CheckPISearch() 
		{
			try
			{
				if (Parameters_ContainsKey(L"search-pi"))
				{
					m_PIName = GetParameter(L"search-pi"); 
				}
				//
				if (Parameters_ContainsKey(L"search-root-local-name"))
				{
					m_SearchRootName = GetParameter(L"search-root-local-name"); 
				}
				if (Parameters_ContainsKey(L"search-root-ns"))
				{
					m_SearchRootNsUri = GetParameter(L"search-root-ns"); 
				}
			}
			_Catch() 
		}

		inline void CheckHasher() 
		{
			try
			{
				if (Parameters_ContainsKey(L"hash-type"))
				{
					m_HashType = GetParameter(L"hash-type"); 
					//
					if (Parameters_ContainsKey(L"hash-target-uuid"))
					{
						m_HashTargetUuid = GetParameter(L"hash-target-uuid"); 
						if (m_HashTargetUuid == L"")
						{
							m_HashTargetUuid = "1"; 
						}
					}
				}
			}
			_Catch() 
		}

		inline bool fWriteXmlOutput() 
		{
			return m_WriteXmlOutput &&
				!( fSearchPI() || fHasher() ); 
		}

		inline bool fSearchPI() 
		{
			return ((m_PIName.GetLength() > 0) || (m_SearchRootName.GetLength() > 0)); 
		}

		inline bool fHasher() 
		{
			return m_HashType.GetLength() > 0; 
		}






		// ---------------------------------------------------------------------------------------
		// ��������� ISAXContentHandler
		// ��������� XML-��������, ����������� ����������� ���������� ( processing-instructions ) 

		SharedArray<string> m_NamespaceMappings; // 2k --> �������, 2k+1 --> NamespaceUri 

		inline void Sax_AddNsMapping(const string& prefix,const string& nsUri) 
		{
			try
			{
				int n = m_NamespaceMappings.Length(); 
#				ifdef _DEBUG
				{
					if ((n % 2) != 0) throw MethodError(E_UNEXPECTED); 
				}
#				endif
				//
				m_NamespaceMappings[n] = prefix; 
				m_NamespaceMappings[n+1] = nsUri; 
			}
			_Catch() 
		}

		inline void Sax_RemoveNsMapping(const string& prefix) 
		{
			try
			{
				int n = m_NamespaceMappings.Length() / 2; 
				for (int k = n-1; k >= 0; --k)
				{
					string& prefix_1 = m_NamespaceMappings[2*k]; 
					//string& nsUri_1 = m_NamespaceMappings[2*k+1]; 
					//
					if (prefix_1 == prefix) 
					{
						for (int j = 2*(k+1); j < 2*n; ++j) 
						{
							m_NamespaceMappings[j-2] = m_NamespaceMappings[j]; 
						}
						m_NamespaceMappings.ReduceSize(2*(n-1)); 
						return; // ������! 
					}
				}
				throw MethodError(HRESULT_FROM_WIN32(ERROR_NOT_FOUND)); 
			}
			_Catch() 
		}

		inline const string& Sax_JoinPrefixNsUri(
			int action, // 1 -- �������-->NsUri, 2 -- NsUri-->������� 
			const string& prefix,const string& nsUri
			) 
		{
			try
			{
				int n = m_NamespaceMappings.Length() / 2; 
				for (int k = n-1; k >= 0; --k)
				{
					string& prefix_1 = m_NamespaceMappings[2*k]; 
					string& nsUri_1 = m_NamespaceMappings[2*k+1]; 
					//
					if (action == 1) // �������-->NsUri 
					{
						if (prefix_1 == prefix) return nsUri_1; 
					}
					else if (action == 2) // NsUri-->������� 
					{
						if (nsUri_1 == nsUri) return prefix_1; 
					}
				}
				throw MethodError(HRESULT_FROM_WIN32(ERROR_NOT_FOUND)); 
			}
			_Catch()
		}

		inline const string& Sax_PrefixToNsUri(const string& prefix) 
		{
			try
			{
				return Sax_JoinPrefixNsUri(1,prefix,L""); 
			}
			_Catch() 
		}

		inline static const string& XmlnsNsUri()
		{
			static string s_NsUri = L"http://www.w3.org/2000/xmlns/"; 
			return s_NsUri; 
		}

		inline const string& Sax_NsUriToPrefix(const string& nsUri) 
		{
			static string empty;
			static string xmlnsNsUri = L"http://www.w3.org/2000/xmlns/"; 
			//
			static string xmlnsPrefix = L"xmlns"; 
			//
			try
			{
				if (nsUri.GetLength() == 0) // L"" 
				{
					return empty; 
				}
				else if (nsUri == xmlnsNsUri) 
				{
					return xmlnsPrefix; 
				}
				//
				return Sax_JoinPrefixNsUri(2,L"",nsUri); 
			}
			_Catch() 
		}

		SharedArray<string> m_DefaultNamespaceArray; 

		inline void Sax_SetDefaultNamespace(const string& nsUri) 
		{
			try
			{
				int n = m_DefaultNamespaceArray.Length(); 
				m_DefaultNamespaceArray[n] = nsUri; 
			}
			_Catch() 
		}

		inline void Sax_InitNamespaces() 
		{
			try
			{
				Sax_AddNsMapping(L"",L""); 
				//
				Sax_SetDefaultNamespace(L""); 
			}
			_Catch() 
		}

		int m_Level; 

		inline void Sax_StartDocument() 
		{
			try
			{
				Sax_InitNamespaces(); 
				//
				m_Level = 0; 
				m_PINum = 0; 
				//
				if (fWriteXmlOutput()) 
				{
					HRESULT rc = m_XmlWriter->WriteStartDocument(XmlStandalone_Omit); 
					if (FAILED(rc)) throw MethodError(rc); 
				}
			}
			_Catch() 
		}

		inline void Sax_StartElement(
			const string& prefix,
			const string& localName,
			const string& nsUri, 
			ISAXAttributes __RPC_FAR *pAttributes
			) 
		{
			try
			{
				if (localName == "X509Certificate")
				{
					if (m_F_skipX509Cert)
					{
						ActivateSkipNextElement(); 
					}
				}
				//
				// ---- 
				// ��������� � �������������� ��������(�) : Output 
				// 
				if (fSearchPI())
				{
					// Root 
					//
					if (m_Level == 0)
					{
						if (localName == m_SearchRootName)
						{
							if (nsUri == m_SearchRootNsUri)
							{
								CComBSTR bstrYes(L"1"); 
								HRESULT rc = SetDataStreamParameter(
									CComBSTR(L"root-found"),
									CComVariant(bstrYes)
									); 
								if (FAILED(rc)) throw MethodError(rc); 
							}
						}
						//
						CComBSTR bstrRootLocalName(localName); 
						HRESULT rc = SetDataStreamParameter(
									CComBSTR(L"root-local-name"),
									CComVariant(bstrRootLocalName)
									); 								
						if (FAILED(rc)) throw MethodError(rc); 
						//
						CComBSTR bstrRootNsUri(nsUri); 
						rc = SetDataStreamParameter(
									CComBSTR(L"root-ns-uri"),
									CComVariant(bstrRootNsUri)
									); 								
						if (FAILED(rc)) throw MethodError(rc); 
					}
				}
				else if (fWriteXmlOutput())
				{
					bool doWrite = true;
					//
					if (m_F_skipNext) doWrite = false; 
					//
					if (doWrite)
					{
						HRESULT rc = m_XmlWriter->WriteStartElement(prefix,localName,nsUri); 
						if (FAILED(rc)) throw MethodError(rc); 
						//
						// ��������
						{
							int n = 0;
							HRESULT rc = pAttributes->getLength(&n);
							if (FAILED(rc)) throw MethodError(rc);
							//
							for (int k = 0; k < n; ++k)
							{
								const wchar_t* pwchLocalName = 0;
								int cchLocalName = 0;
								rc = pAttributes->getLocalName(k,&pwchLocalName,&cchLocalName);
								if (FAILED(rc)) throw MethodError(rc);
								string a_LocalName(pwchLocalName,cchLocalName); 
								//
								const wchar_t* pwchUri = 0;
								int cchUri = 0;
								rc = pAttributes->getURI(k,&pwchUri,&cchUri);
								if (FAILED(rc)) throw MethodError(rc);
								string a_Uri(pwchUri,cchUri); 
								//
								const wchar_t* pwchValue = 0;
								int cchValue = 0;
								rc = pAttributes->getValue(k,&pwchValue,&cchValue);
								if (FAILED(rc)) throw MethodError(rc);
								string a_Value(pwchValue,cchValue); 
								//
								string a_Prefix = Sax_NsUriToPrefix(a_Uri); 
								//
								bool add = true; 
								if (a_Uri == XmlnsNsUri()) add = false; 
								//
								if (add) 
								{
									rc = m_XmlWriter->WriteAttributeString(a_Prefix,a_LocalName,a_Uri,a_Value); 
									if (FAILED(rc)) 
									{
										throw MethodError(rc); 
									}
								}
								//
								////string a = a_QName + L"=\"" + a_Value + L"\"";
								//////
								////if (attributes.GetLength() > 0) attributes += L" ";
								////attributes += a; 
							}
						}
					}
				}
				else if (fHasher()) 
				{
					Hasher_StartElement(prefix,localName,nsUri,pAttributes); 
				}
				//
				if (fWriteXmlOutput() || fHasher())
				{
					if (m_SignDocumentRoot && (m_Level == 0)) 
					{
						Sax_PI(L"-xml-sign-next", L""); 
						//m_SignatureLevel = 0; 
					}
				}
				//
				++m_Level; 
			}
			_Catch() 
		}

		inline void Sax_WriteSignatureElement() 
		{
			try
			{
				HRESULT rc = m_XmlWriter->WriteRaw(m_SignatureXmlRaw.GetBuffer()); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				m_HashTargetUuid = L""; 
			}
			_Catch() 
		}

		inline void Sax_EndElement(
			const string& prefix,
			const string& localName,
			const string& nsUri 
			) 
		{
			try
			{
				--m_Level; 
				//
				if (fWriteXmlOutput())
				{
					bool doWrite = true; 
					//
					if (m_F_skipNext) 
					{
						if (m_F_skipElementLevel != -1)
						{
							if (m_Level > m_F_skipElementLevel)
							{
								doWrite = false; 
							}
							if (m_Level == m_F_skipElementLevel)
							{
								doWrite = false; 
								//
								m_F_skipCurrent = false; 
								m_F_skipNext = false; 
								m_F_skipElementLevel = -1; 
							}
							else
							{
								// �� ���� �������� ��� �������� 
								//
								m_F_skipCurrent = false; 
								m_F_skipNext = false; 
								m_F_skipElementLevel = -1; 
							}
						}
					}
					//
					// ---- 
					// ��������� � �������������� ��������(�) : Output 
					//
					if ((m_Level) == m_SignatureLevel) 
					{
						// ��������� �������! 
						//
						Sax_WriteSignatureElement(); 
					}
					//
					if (doWrite)
					{
						HRESULT rc = m_XmlWriter->WriteEndElement(); // prefix,localName,nsUri 
						if (FAILED(rc)) throw MethodError(rc); 
					}
				}
				else if (fHasher()) 
				{
					Hasher_EndElement(prefix,localName,nsUri); 
					//
					if ((m_Level) == m_SignatureLevel) 
					{
						m_HashOn = false; 
					}
				}
			}
			_Catch() 
		}

		inline void Sax_AddTextChunk(const wchar_t __RPC_FAR *pwchChars,int cchChars) 
		{
			try
			{
				// fWriteXmlOutput() ��������������� 
				//
				HRESULT rc = m_XmlWriter->WriteChars(pwchChars,cchChars); 
				if (FAILED(rc)) throw MethodError(rc); 
			}
			_Catch() 
		}

		inline void Sax_AddText(const wchar_t __RPC_FAR *pwchChars,int cchChars) 
		{
			try
			{
				if (fWriteXmlOutput()) 
				{
					// ---- 
					// ��������� � �������������� ��������(�) : Output 
					// 
					Sax_AddTextChunk(pwchChars,cchChars); 
				}
				if (fHasher())
				{
					if (! m_HashOn) return;
					//
					if (m_HashType == _HASHER_TYPE_XML_HASH)
					{
						string textToHash(pwchChars,cchChars);
						textToHash.Trim(); 
						Hasher_AdjustText(textToHash); 
						Hasher_SHA1AddText(textToHash); 
					}
				}
			}
			_Catch() 
		}



		inline void ActivateSkipNextElement()
		{
			try
			{
				m_F_skipNext = true; 
				m_F_skipElementLevel = m_Level; 
			}
			_Catch()
		}









		int m_PINum;

		int m_SignatureLevel; 

		string m_SignatureXmlRaw; 

		inline void SetElementUuid(const string& uuid)
		{
			try
			{
				m_elementUuid = uuid; 
				//
				CComBSTR bstrYes(m_elementUuid); 
				HRESULT rc = SetDataStreamParameter(
					CComBSTR(L"search-element-uuid"),
					CComVariant(bstrYes)
					); 
				if (FAILED(rc)) throw MethodError(rc); 
			}
			_Catch()
		}

		inline void SetElementHash(const string& data_s)
		{
			try
			{
				string h64;
				string uuid;
				int p1 = data_s.Find(L"@"); 
				if (p1 != -1)
				{
					h64 = data_s.Left(p1); 
					h64.Trim(); 
					//
					uuid = data_s.Right(data_s.GetLength()-p1-1);
					uuid.Trim(); 
					//
					SetElementUuid(uuid); 
				}
				else
				{
					h64 = data_s; 
					//
					if (m_elementUuid.GetLength() == 0)
					{
						throw MethodError(L"���������� @Uuid"); 
					}
				}
				//
				m_elementHash64 = h64; 
				//
				CComBSTR bstrYes(m_elementHash64); 
				HRESULT rc = SetDataStreamParameter(
					CComBSTR(L"search-element-hash"),
					CComVariant(bstrYes)
					); 
				if (FAILED(rc)) throw MethodError(rc); 
			}
			_Catch()
		}

		inline void Sax_PI(const string& PI, const wchar_t* piData) 
		{
			try
			{
				if (fWriteXmlOutput())
				{
					if (PI == L"-skip-next-element")
					{
						ActivateSkipNextElement();
					}
					else if (PI == L"-skip-tag")
					{
						string tag(piData); 
						tag.Trim();
						//
						if (tag == L"X509Certificate") 
						{
							m_F_skipX509Cert = true; 
						}
					}
					else if (PI == L"-element-uuid")
					{
						string data_s(piData); 
						data_s.Trim(); 
						//
						SetElementUuid(data_s);
					}
					else if (PI == L"-element-hash")
					{
						string data_s(piData); 
						data_s.Trim(); 
						//
						SetElementHash(data_s); 
					}
					else if (PI == L"-xml-sign-next")
					{
						// ----
						// Target Hash 
						//
						string targetUuid;
						string targetHash64; 
						//
						if (m_elementHash64.GetLength() > 0) 
						{
							targetUuid = m_elementUuid; 
							targetHash64 = m_elementHash64; 
							if (m_elementUuid.GetLength() == 0)
							{
								throw MethodError(L"����������� @Uuid (2)"); 
							}
						}
						else
						{
							CComPtr<ISlotDataStreamInfo> targetHasherInfo;
							targetHasherInfo.Attach(
								CreateHasher<ISlotDataStreamInfo>(_HASHER_TYPE_XML_HASH,m_InputStream,
								m_SignDocumentRoot) 
								);
							if (! targetHasherInfo) throw MethodError(E_UNEXPECTED); 
							//
							HRESULT rc = targetHasherInfo->SetDataStreamParameter(
								CComBSTR(L"pi-num"),CComVariant((DWORD)m_PINum)); 
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
							// ----
							// XMLdsig 
							//
							string _targetUuid( v2.bstrVal );
							string _targetHash64( v.bstrVal ); 
							//
							targetUuid = _targetUuid;
							targetHash64 = _targetHash64; 
						}
						//
						COleDateTime t0 = COleDateTime::GetCurrentTime(); 
						m_SignatureXmlRaw = GetXmlSignature(targetUuid,targetHash64,t0); 
						//
						// ----
						// ������������� ������� 
						//
						m_SignatureLevel = m_Level; 
					}
					else
					{
						// ������ �� ������ 
						//
						HRESULT rc = m_XmlWriter->WriteProcessingInstruction(
							PI, piData
							);
						if (FAILED(rc)) throw MethodError(rc); 
					}
				}
				else if (fHasher())
				{
					if ((m_HashType == _HASHER_TYPE_XML_HASH) || 
						(m_HashType == _HASHER_TYPE_XML_COLLECT_NS))
					{
						if (PI == L"-xml-sign-next")
						{
							int expectedPINum = -1;
							if (Parameters_ContainsKey(L"pi-num"))
							{
								expectedPINum = _wtoi(GetParameter(L"pi-num")); 
							}
							//
							if (expectedPINum >= 0)
							{
								if ((m_PINum == expectedPINum) || (m_SignDocumentRoot)) 
								{
									Hasher_StartDocument(); 
									m_HashOn = true; 
									m_SignatureLevel = m_Level; 
								}
							}
							else
							{
								TRACE_LOG(_T("Strange expectedPINum")); 
							}
						}
					}
					else
					{
					}
				}
				else if (fSearchPI()) 
				{
					if (PI == m_SearchPIName)
					{
						++m_SearchPINum; 
					}
					//
					// Special behavior 
					//
					if (PI == L"-element-uuid")
					{
						string data_s(piData); 
						data_s.Trim(); 
						//
						SetElementUuid(data_s);
					}
					else if (PI == L"-element-hash")
					{
						string data_s(piData); 
						data_s.Trim(); 
						//
						SetElementHash(data_s); 
					}
				}
				//
				++m_PINum; 
			}
			_Catch()
		}






		// ----
		// ISAXContentHandler 

		virtual HRESULT STDMETHODCALLTYPE putDocumentLocator(
			ISAXLocator __RPC_FAR *pLocator)
		{
			try
			{
				return S_OK; // no actions 
			}
			_Catch() 
		}

		virtual HRESULT STDMETHODCALLTYPE startDocument()
		{
			try
			{
				Sax_StartDocument(); 
				//
				return S_OK;
			}
			_ComCatch() 
		}
        
		virtual HRESULT STDMETHODCALLTYPE endDocument()
		{
			try
			{
				if (fWriteXmlOutput()) 
				{
					HRESULT rc = m_XmlWriter->WriteEndDocument(); 
					if (FAILED(rc)) throw MethodError(rc); 
					//
					rc = m_XmlWriter->Flush(); 
					if (FAILED(rc)) throw MethodError(rc); 
				}
				else if (fHasher()) 
				{
					Hasher_EndDocument(); 
				}
				else if (fSearchPI()) 
				{
					CComVariant piNumVar((DWORD)m_SearchPINum); 
					HRESULT rc = SetDataStreamParameter(CComBSTR(L"search-pi-result"),piNumVar); 
					if (FAILED(rc)) throw MethodError(rc); 
				}
				//
				return S_OK;
			}
			_ComCatch() 
		}
        
		virtual HRESULT STDMETHODCALLTYPE startPrefixMapping( 
			const wchar_t __RPC_FAR *pwchPrefix,
			int cchPrefix,
			const wchar_t __RPC_FAR *pwchUri,
			int cchUri)
		{
			try
			{
				string prefix(pwchPrefix,cchPrefix); 
				string nsUri(pwchUri,cchUri); 
				//
				Sax_AddNsMapping(prefix,nsUri); 
				//
				return S_OK;
			}
			_ComCatch() 
		}
        
		virtual HRESULT STDMETHODCALLTYPE endPrefixMapping( 
			const wchar_t __RPC_FAR *pwchPrefix,
			int cchPrefix)
		{
			try
			{
				string prefix(pwchPrefix,cchPrefix); 
				//
				Sax_RemoveNsMapping(prefix); 
				//
				return S_OK;
			}
			_ComCatch() 
		}



		virtual HRESULT STDMETHODCALLTYPE startElement( 
			const wchar_t __RPC_FAR *pwchNamespaceUri,
			int cchNamespaceUri,
			const wchar_t __RPC_FAR *pwchLocalName,
			int cchLocalName,
			const wchar_t __RPC_FAR *pwchRawName,
			int cchRawName,
			ISAXAttributes __RPC_FAR *pAttributes)
		{
			try
			{
				string nsUri(pwchNamespaceUri,cchNamespaceUri); 
				string localName(pwchLocalName,cchLocalName); 
				//string rawName(pwchRawName,cchRawName); 
				//
				const string& prefix = Sax_NsUriToPrefix(nsUri); 
				//
				Sax_StartElement(prefix,localName,nsUri,pAttributes); 
				//
				return S_OK;
			}
			_ComCatch() 
		}



		virtual HRESULT STDMETHODCALLTYPE endElement( 
			const wchar_t __RPC_FAR *pwchNamespaceUri,
			int cchNamespaceUri,
			const wchar_t __RPC_FAR *pwchLocalName,
			int cchLocalName,
			const wchar_t __RPC_FAR *pwchRawName,
			int cchRawName)
		{
			try
			{
				string nsUri(pwchNamespaceUri,cchNamespaceUri); 
				string localName(pwchLocalName,cchLocalName); 
				//string rawName(pwchRawName,cchRawName); 
				//
				const string& prefix = Sax_NsUriToPrefix(nsUri); 
				//
				Sax_EndElement(prefix,localName,nsUri); 
				//
				return S_OK;
			}
			_ComCatch() 
		}
        


		virtual HRESULT STDMETHODCALLTYPE characters( 
			const wchar_t __RPC_FAR *pwchChars,
			int cchChars)
		{
			try
			{
				Sax_AddText(pwchChars,cchChars); 
				//
				return S_OK;
			}
			_ComCatch() 
		}
        


		virtual HRESULT STDMETHODCALLTYPE ignorableWhitespace( 
			const wchar_t __RPC_FAR *pwchChars,
			int cchChars)
		{
			try
			{
				return S_OK;
			}
			_ComCatch() 
		}
        


		virtual HRESULT STDMETHODCALLTYPE processingInstruction( 
			const wchar_t __RPC_FAR *pwchTarget,
			int cchTarget,
			const wchar_t __RPC_FAR *pwchData,
			int cchData)
		{
			try
			{
				string PIName(pwchTarget,cchTarget); 
				string PIData(pwchData,cchData); 
				//
				Sax_PI(PIName, PIData); 
				//
				return S_OK;
			}
			_ComCatch() 
		}
        


		virtual HRESULT STDMETHODCALLTYPE skippedEntity( 
			const wchar_t __RPC_FAR *pwchName,
			int cchName)
		{
			try
			{
				return S_OK;
			}
			_ComCatch() 
		}






		// ---------------------------------------------------------------------------------------
		// IXmlWriter --- ��������� ��� ������ ������ hasher'�� 

	protected:
		// ----
		// Hasher 

		string m_HashType; 

		// Search PI 

		int m_SearchPINum;

		string m_SearchPIName; 

		// XML-������: 
			
		string m_HashTargetUuid; 

		bool m_HashOn; 

		int m_HashFirstElement; 

		// ������� Namespaces 

		int m_NsNum; 

		CComPtr<ISlotDataStreamInfo> m_NsGlossary; 

		string m_NsAttributes; 

		// SHA1 

		HCRYPTPROV hCryptProv;
		HCRYPTHASH hHash;

		inline void Hasher_SHA1Create()
		{
			try
			{
				if (! CryptAcquireContext(
					&hCryptProv, 
					NULL, 
					NULL, 
					PROV_RSA_FULL, 
					CRYPT_VERIFYCONTEXT)) 
				{
					throw Exception(L"�� ������� ��������� ������-���������");
				}
				//
				if (! CryptCreateHash(
					hCryptProv, 
					CALG_SHA1, 
					0, 
					0, 
					&hHash)) 
				{
					throw Exception(L"���������� ������� ���");
				}
			}
			_Catch() 
		}

		inline void Hasher_SHA1AddText(const string& text)
		{
			try
			{
				if (text.GetLength() == 0) return;
				//
				Blob data = WideStringToUTF8(text);
				////data.Allocate(text.GetLength()); 
				////CopyMemory((void*)data.GetBuffer(),(const BYTE*)text.GetString(),
				////	text.GetLength()*sizeof(wchar_t));
				//
				if(! CryptHashData(
					hHash, 
					(const BYTE*)data.GetBuffer(), 
					(DWORD)data.Length(), 
					0)) 
				{
					HRESULT rc = HRESULT_FROM_WIN32(GetLastError()); 
					throw MethodError(rc);
				}
				//
#				ifdef _DEBUG
				///TRACE_LINE(_T("H: ") + _S(text)); 
#				endif
			}
			_Catch()
		}

		inline string Hasher_SHA1Calculate()
		{
			try
			{
				if (! hHash) return L"";
				//
				DWORD dwDigestedSize;
				//
				if(! CryptGetHashParam(hHash,
					HP_HASHVAL,
					0,
					&dwDigestedSize,
					0))
				{
					throw Exception(L"���������� ������� �������� ����");
				}
				//
				Blob dataDigested;
				dataDigested.Allocate(dwDigestedSize);
				//
				if(! CryptGetHashParam(hHash,
					HP_HASHVAL,
					dataDigested.GetBuffer(),
					&dwDigestedSize,
					0))
				{
					throw Exception(L"���������� ������� �������� ����");
				}
				//
				CryptReleaseContext(hCryptProv,0);
				//
				return ToBase64Padding(dataDigested);
			}
			_Catch()
		}

		// Namespace Glossary 

		inline string GetNsGlossaryPrefix(const string& nsUri) 
		{
			try
			{
				if (! m_NsGlossary) return L""; 
				//
				CComVariant v; 
				HRESULT rc = m_NsGlossary->GetDataStreamParameter(CComBSTR(nsUri),&v); 
				if (FAILED(rc)) throw MethodError(rc); 
				if (v.vt != VT_BSTR) throw MethodError(E_INVALIDARG); 
				//
				string value(v.bstrVal); 
				//
				return value; 
			}
			_Catch() 
		}

	public:
		inline void Hasher_StartDocument() 
		{
			try
			{
				if (m_HashOn) return; // ������! 
				//
				m_HashFirstElement = true; 
				//
				if (m_HashType == _HASHER_TYPE_XML_COLLECT_NS) 
				{
					m_NsNum = 1; 
					//
					m_NsArray = SharedArray<string>(); 
					//
					m_NsAttributes = L""; 
					//
					//CComBSTR bstrNs0(L"ns0"); 
					////
					//HRESULT rc = SetDataStreamParameter(CComBSTR(L""),CComVariant(bstrNs0)); 
					//if (FAILED(rc)) throw MethodError(rc); 
					////
					//m_NsNum = 2; 
				}
				else if (m_HashType == _HASHER_TYPE_XML_HASH) 
				{
					// ----
					// �������� Namespaces 
					//
					if (m_NsGlossary) m_NsGlossary.Release(); 
					//
					m_NsGlossary.Attach(
						CreateHasher<ISlotDataStreamInfo>(_HASHER_TYPE_XML_COLLECT_NS,m_InputStream,
							m_SignDocumentRoot) 
						);
					if (! m_NsGlossary) throw MethodError(E_UNEXPECTED); 
					//
					HRESULT rc = m_NsGlossary->SetDataStreamParameter(
						CComBSTR(L"pi-num"),CComVariant((DWORD)m_PINum)); 
					if (FAILED(rc)) throw MethodError(rc); 
					//
					// Hashing 
					//
					CComQIPtr<ISlotXmlFilter> ns_f(m_NsGlossary); 
					//
					rc = ns_f->Open(); // �������� 
					if (FAILED(rc)) throw MethodError(rc); 
					//
					//
					// ----
					// ��������� ��������� ����������� 
					//
					Hasher_SHA1Create(); 
				}
				else if (m_HashType == _HASHER_TYPE_XML_NORMALIZE) 
				{
				}
			}
			_Catch() 
		}

		inline void Hasher_AddNsToGlossary_2(const string& nsUri)
		{
			try
			{
				if (! Parameters_ContainsKey(nsUri))
				{
					string nsKey = FormatStr(L"ns%d", m_NsNum); 
					CComBSTR bstrNsKey(nsKey); 
					//
					HRESULT rc = SetDataStreamParameter(CComBSTR(nsUri),CComVariant(bstrNsKey)); 
					if (FAILED(rc)) throw MethodError(rc); 
					//
					if (m_NsAttributes.GetLength() > 0) m_NsAttributes += L" "; 
					//
					m_NsAttributes += _W(L"xmlns:") + nsKey + L"=\"" + nsUri + L"\""; 
					//
					++m_NsNum; 
				}
			}
			_Catch()
		}

		SharedArray<string> m_NsArray;

		inline void Hasher_AddNsToGlossary(const string& nsUri)
		{
			const string xmlnsUri = L"http://www.w3.org/2000/xmlns/";
			//
			try
			{
				bool add = true;
				for (int i = 0; i < m_NsArray.Length(); ++i)
				{
					if (string(m_NsArray[i]) == nsUri) add = false;
				}
				if (nsUri == xmlnsUri)
				{
					add = false; 
				}
				if (add)
				{
					m_NsArray.Add(nsUri); 
				}
			}
			_Catch()
		}

		inline void Hasher_StartElement( 
			const string& prefix,
			const string& localName,
			const string& nsUri, 
			ISAXAttributes __RPC_FAR *pAttributes
			) 
		{
			const string xmlnsUri = L"http://www.w3.org/2000/xmlns/"; 
			//
			try
			{
				if (! m_HashOn) return; 
				//
				if (m_HashType == _HASHER_TYPE_XML_COLLECT_NS) 
				{
					Hasher_AddNsToGlossary(nsUri); 
					//
					// ��������
					{
						int n = 0;
						HRESULT rc = pAttributes->getLength(&n);
						if (FAILED(rc)) throw MethodError(rc);
						//
						for (int k = 0; k < n; ++k)
						{
							const wchar_t* pwchUri = 0;
							int cchUri = 0;
							rc = pAttributes->getURI(k,&pwchUri,&cchUri);
							if (FAILED(rc)) throw MethodError(rc);
							//
							string attrNsUri(pwchUri,cchUri);
							//
							Hasher_AddNsToGlossary(attrNsUri); 
						}
					}
				}
				else if (m_HashType == _HASHER_TYPE_XML_HASH) 
				{
					string p_1 = GetNsGlossaryPrefix(nsUri); 
					//
					string attributes;
					if (m_HashFirstElement) 
					{
						attributes += GetNsGlossaryPrefix(L"__ns_attributes__"); 
						m_HashFirstElement = false; 
					}
					//
					// ��������
					try
					{
						int n = 0;
						HRESULT rc = pAttributes->getLength(&n);
						if (FAILED(rc)) throw MethodError(rc);
						//
						SharedArray<string> _A;
						Map<string,string> _V;
						//
						for (int k = 0; k < n; ++k)
						{
							const wchar_t* pwchLocalName = 0;
							int cchLocalName = 0;
							rc = pAttributes->getLocalName(k,&pwchLocalName,&cchLocalName);
							if (FAILED(rc)) throw MethodError(rc);
							string a_LocalName(pwchLocalName,cchLocalName); 
							//
							const wchar_t* pwchUri = 0;
							int cchUri = 0;
							rc = pAttributes->getURI(k,&pwchUri,&cchUri);
							if (FAILED(rc)) throw MethodError(rc);
							string a_Uri(pwchUri,cchUri); 
							//
							const wchar_t* pwchValue = 0;
							int cchValue = 0;
							rc = pAttributes->getValue(k,&pwchValue,&cchValue);
							if (FAILED(rc)) throw MethodError(rc);
							string a_Value(pwchValue,cchValue); 
							//
							if (a_Uri != xmlnsUri)
							{
								string p_2 = GetNsGlossaryPrefix(string(pwchUri,cchUri)); 
								//
								string aQName = p_2 + L":" + a_LocalName;
								//
								if (aQName != L"")
								{
									_A.Add(aQName);
									_V[aQName] = Hasher_EncodeAttribute(a_Value); 
								}
							}
							//
							// Target Uuid
							//
							if (a_LocalName == L"uuid")
							{
								if ((m_SignatureLevel == m_Level) ||
									( (m_SignDocumentRoot) && (m_Level == 0) ))
								{
									if (a_LocalName == L"uuid")
									{
										m_HashTargetUuid = a_Value; 
										//
										CComBSTR bstrTargetUuid(m_HashTargetUuid);
										HRESULT rc = SetDataStreamParameter(
											CComBSTR(L"hash-target-uuid"),
											CComVariant(bstrTargetUuid)); 
										if (FAILED(rc)) throw MethodError(rc); 
									}
								}
							}
						}
						//
						_A = Algorithms::Alg_1_8_4().Sort(_A); 
						//
						for (int k = 0; k < _A.Length(); ++k)
						{
							string aQName = _A[k];
							string a_Value = _V[aQName];
							//
							string a = aQName + L"=\"" + a_Value + L"\"";
							//
							if (attributes.GetLength() > 0) attributes += L" ";
							attributes += a; 
						}
					}
					catch(::::Exception e)
					{
						TRACE_LOG(e.ToString()); 
						throw;
					}
					catch(...)
					{
						throw;
					}
					//
					string text = L"<" + p_1 + L":" + localName;
					if (attributes.GetLength() > 0) text += L" " + attributes;
					text += L">"; 
					//
					Hasher_SHA1AddText(text); 
				}
				else if (m_HashType == _HASHER_TYPE_XML_NORMALIZE) 
				{
				}
			}
			_Catch() 
		}

		inline void Hasher_EndElement(
			const string& prefix,
			const string& localName,
			const string& nsUri) 
		{
			try
			{
				if (! m_HashOn) return; 
				//
				if (m_HashType == _HASHER_TYPE_XML_HASH) 
				{
					string p_1 = GetNsGlossaryPrefix(nsUri); 
					//
					string text = L"</" + p_1 + L":" + localName + L">"; 
					Hasher_SHA1AddText(text); 
				}
				else if (m_HashType == _HASHER_TYPE_XML_NORMALIZE) 
				{
				}
			}
			_Catch() 
		}

		inline void Hasher_EndDocument()
		{
			try
			{
				if (m_HashType == _HASHER_TYPE_XML_COLLECT_NS) 
				{
					Algorithms::Alg_1_8_4 alg; 
					//
					m_NsArray = alg.Sort(m_NsArray); 
					//
					for (int i = 0; i < m_NsArray.Length(); ++i)
					{
						string nsUri_1 = m_NsArray[i]; 
						Hasher_AddNsToGlossary_2(nsUri_1); 
					}
					//
					CComBSTR bstrNsAttributes(m_NsAttributes); 
					HRESULT rc = SetDataStreamParameter(
						CComBSTR(L"__ns_attributes__"),
						CComVariant(bstrNsAttributes)
						); 
					if (FAILED(rc)) throw MethodError(rc); 
				}
				else if (m_HashType == _HASHER_TYPE_XML_HASH) 
				{
					string hash64 = Hasher_SHA1Calculate(); 
					//
					CComBSTR bstrHash64(hash64); 
					HRESULT rc = SetDataStreamParameter(
						CComBSTR(L"hash64"),
						CComVariant(bstrHash64)
						); 
					if (FAILED(rc)) throw MethodError(rc); 
				}
			}
			_Catch()
		}

		STDMETHOD(SetOutput)(IUnknown* streamUnk) 
		{
			try
			{
				if (! streamUnk) throw MethodError(E_INVALIDARG); 
				//
				CComQIPtr<IStream> stream(streamUnk);
				if (! stream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = put_DataStream(stream); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		STDMETHOD(GetProperty)(UINT,LONG_PTR*) 
		{
			try
			{
				return E_NOTIMPL; 
			}
			_ComCatch() 
		}

		STDMETHOD(SetProperty)(UINT,LONG_PTR) 
		{
			try
			{
				return E_NOTIMPL; 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteAttributes)(IXmlReader*,BOOL) 
		{
			try
			{
				return E_NOTIMPL; 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteAttributeString)(LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR) 
		{
			try
			{
				return E_NOTIMPL; 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteCData)(LPCWSTR) 
		{
			try
			{
				return S_OK; // skip so far ( * ) 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteCharEntity)(WCHAR) 
		{
			try
			{
				return S_OK; // skip 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteChars)(const WCHAR*,UINT) 
		{
			try
			{
				return E_NOTIMPL; 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteComment)(LPCWSTR) 
		{
			try
			{
				return S_OK; // skip so far ( * ) 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteDocType)(LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR) 
		{
			try
			{
				return S_OK; // skip 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteElementString)(LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR) 
		{
			try
			{
				return E_NOTIMPL; 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteEndDocument)() 
		{
			try
			{
				return S_OK; // no actions 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteEndElement)() 
		{
			try
			{
				return E_NOTIMPL; 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteEntityRef)(LPCWSTR) 
		{
			try
			{
				return S_OK; // skip 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteFullEndElement)() 
		{
			try
			{
				return E_NOTIMPL; 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteName)(LPCWSTR) 
		{
			try
			{
				return E_NOTIMPL; 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteNmToken)(LPCWSTR) 
		{
			try
			{
				return E_NOTIMPL; 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteNode)(IXmlReader*,BOOL) 
		{
			try
			{
				return E_NOTIMPL; 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteNodeShallow)(IXmlReader*,BOOL) 
		{
			try
			{
				return E_NOTIMPL; 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteProcessingInstruction)(LPCWSTR,LPCWSTR) 
		{
			try
			{
				return S_OK; // skip 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteQualifiedName)(LPCWSTR,LPCWSTR) 
		{
			try
			{
				return E_NOTIMPL; 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteRaw)(LPCWSTR) 
		{
			try
			{
				return E_NOTIMPL; // �� ������ ������������ 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteRawChars)(const WCHAR *,UINT) 
		{
			try
			{
				return E_NOTIMPL; // �� ������ ������������ 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteStartDocument)(XmlStandalone) 
		{
			try
			{
				return S_OK; // no actions 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteStartElement)(LPCWSTR,LPCWSTR,LPCWSTR) 
		{
			try
			{
				return E_NOTIMPL; 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteString)(LPCWSTR) 
		{
			try
			{
				return E_NOTIMPL; 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteSurrogateCharEntity)(WCHAR,WCHAR) 
		{
			try
			{
				return S_OK; // skip 
			}
			_ComCatch() 
		}

		STDMETHOD(WriteWhitespace)(LPCWSTR) 
		{
			try
			{
				return S_OK; // skip 
			}
			_ComCatch() 
		}

		STDMETHOD(Flush)() 
		{
			try
			{
				return S_OK; // no actions 
			}
			_ComCatch() 
		}






		// ---------------------------------------------------------------------------------------
		// XMLdsig

		inline ISlotClient* Client() 
		{
			try
			{
				if (! m_Client) throw MethodError(E_INVALIDARG);
				//
				return m_Client; 
			}
			_Catch() 
		}


		inline ISlotSigner* Client_GetSigner_1() // new reference 
		{
			try
			{
				if (! m_Client) throw MethodError(E_INVALIDARG);
				//
				CComPtr<ISlotSigner> signer;
				//
				HRESULT rc = m_Client->get_Signer(&signer); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				if (! signer) throw MethodError(E_UNEXPECTED); 
				//
				return signer.Detach(); 
			}
			_Catch() 
		}

		inline Blob Client_GetCertData_1() 
		{
			try
			{
				if (! m_Client) throw MethodError(E_INVALIDARG);
				//
				Blob certData;
				int certDataLen = 6 * 1024; 
				certData.Expand(certDataLen); 
				HRESULT rc = m_Client->get_CertificateData(certData.GetBuffer(),&certDataLen); 
				if (rc == HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER))
				{
					certData.Expand(certDataLen); 
					rc = m_Client->get_CertificateData(certData.GetBuffer(),&certDataLen); 
				}
				if (FAILED(rc)) throw MethodError(rc);
				//
				certData.SetSize(certDataLen); 
				//
				if (certData.Length() <= 500) 
				{
					throw MethodError(L"������ ������ ����������� (3)"); 
				}
				//
				return certData;
			}
			_Catch()
		}

		inline static const string& XmlDsigNs()
		{
			static string s = L"http://www.w3.org/2000/09/xmldsig#"; 
			return s;
		}

		inline static const string& XmlDseNs()
		{
			static string s = L"http://cabinet.example.com/schema/xmldsigext-/rel-1/";
			return s;
		}

		string GetXmlSignature(
			const string& targetUuid,
			const string& hash64,
			const COleDateTime& t
			)
		{
			try
			{
				// �����
				//
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
				//string t_s_1_ = FormatStr(L"%04d-%02d-%02d", t.GetYear(), t.GetMonth(), t.GetDay() );
				//string t_s_2_ = FormatStr(L"T%02d:%02d:%02dZ", t.GetHour(), t.GetMinute(), t.GetSecond() );
				//
				string t_s_1 = FormatStr(L"%04d-%02d-%02d", (int)ut.wYear, (int)ut.wMonth, (int)ut.wDay );
				string t_s_2 = FormatStr(L"T%02d:%02d:%02dZ", (int)ut.wHour, (int)ut.wMinute, (int)ut.wSecond );
				//
				string t_s = t_s_1 + t_s_2; 
				//
				// Signature
				//
				string signatureUuid = NewGuidStr(); 
				//
				// KeyInfo
				//
				string keyInfoUuid = NewGuidStr();
				//
				Blob certData = Client_GetCertData();
				string certificate64 = ToBase64Padding(certData); 
				//
				string x509;
				if (m_F_skipX509Cert)
				{
					CCOM_Certificate C;
					C->Import(certData); 
					//
					Blob pkh = C->GetPKH(); 
					string pkh64 = __ToBase64(pkh); 
					//
					x509 = L"<dse:PublicKeyHash>" + pkh64 + L"</dse:PublicKeyHash>"; 
				}
				else
				{
					x509 = L"<dsig:X509Certificate>" + certificate64 + L"</dsig:X509Certificate>"; 
				}
				//
				// Properties
				//
				string propertiesUuid = NewGuidStr(); 
				//
				//
				// ----
				// ���������� ����� ��������� 
				//
				// KeyInfo
				//
				string keyInfoHash64;
				{
					string normalCertificate64 = certificate64;
					Hasher_AdjustText(normalCertificate64);
					//
					string normalKeyInfo = 
					 _W(L"<ns2:KeyInfo") +
						L" xmlns:ns1=\"\""
						L" xmlns:ns2=\"" + XmlDsigNs() + L"\""
						L" ns1:Id=\"uuid." + keyInfoUuid + L"\">"
						L"<ns2:X509Data>" + 
						L"<ns2:X509Certificate>" + normalCertificate64 + L"</ns2:X509Certificate>" + 
						L"</ns2:X509Data>"
						L"</ns2:KeyInfo>"
						;
					Blob normalKeyInfo_b = WideStringToUTF8(normalKeyInfo);
					//normalKeyInfo_b.Allocate(normalKeyInfo.GetLength()*sizeof(wchar_t));
					//CopyMemory(normalKeyInfo_b.GetBuffer(),normalKeyInfo.GetString(),normalKeyInfo_b.Length());
					keyInfoHash64 = Algorithms::Alg_1_8_2().Encode(normalKeyInfo_b); 
					//
#					ifdef _DEBUG
					{
						//OutputDebugString(_T("\n\n"));
						//OutputDebugString(_S(normalKeyInfo)); 
					}
#					endif
				}
				//
				// Properties
				//
				string propertiesHash64;
				{
					string properties = 
						L"<ns3:SignatureProperties"
						L" xmlns:ns1=\"\""
						L" xmlns:ns2=\"" + XmlDseNs() + L"\""
						L" xmlns:ns3=\"" + XmlDsigNs() + L"\""
						L" ns1:Id=\"SignatureProperties." + propertiesUuid + L"\">"
						L"<ns3:SignatureProperty"
						L" ns1:Target=\"#uuid." + signatureUuid + L"\">"
						L"<ns2:Events"
						L" ns1:SignatureTime=\"" + t_s + L"\">"
						L"</ns2:Events>"
						L"<ns2:MetaInfo>"
						L"<ns2:Method"
						L" ns1:Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.9.1\""
						L" ns1:Name=\"Validate\"" 
						L">"
						L"</ns2:Method>"
						L"<ns2:Method"
						L" ns1:Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.5\""
						L" ns1:Name=\"Analyze\""
						L">"
						L"</ns2:Method>"
						L"<ns2:Method"
						L" ns1:Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.6\""
						L" ns1:Name=\"Report\""
						L">"
						L"</ns2:Method>"
						L"</ns2:MetaInfo>"
						L"</ns3:SignatureProperty>"
						L"</ns3:SignatureProperties>"
						;
					Blob properties_b = WideStringToUTF8(properties);
					//Blob properties_b;
					//properties_b.Allocate(properties.GetLength()*sizeof(wchar_t));
					//CopyMemory(properties_b.GetBuffer(),properties.GetString(),properties_b.Length());
					propertiesHash64 = Algorithms::Alg_1_8_2().Encode(properties_b); 
					//
#					ifdef _DEBUG
					{
						//OutputDebugString(_T("\n\n"));
						//OutputDebugString(_S(properties)); 
					}
#					endif
				}
				//
				// SignedInfo 
				//
				Blob signedInfo_b;
				{
					string signedInfo = 
						L"<ns2:SignedInfo"
						L" xmlns:ns1=\"\""
						L" xmlns:ns2=\"" + XmlDsigNs() + L"\">"
						//
						L"<ns2:CanonicalizationMethod"
						L" ns1:Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.1\">"
						L"</ns2:CanonicalizationMethod>"
						//
						L"<ns2:SignatureMethod"
						L" ns1:Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.3\">"
						L"</ns2:SignatureMethod>"
						//
						L"<ns2:Reference"
						L" ns1:URI=\"#xpointer(//*[@uuid='" + targetUuid + L"'])\">"
						L"<ns2:Transforms>"
						L"<ns2:Transform" 
						L" ns1:Algorithm=\"http://www.w3.org/2000/09/xmldsig#enveloped-signature\">"
						L"</ns2:Transform>" 
						L"</ns2:Transforms>"
						L"<ns2:DigestMethod"
						L" ns1:Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.2\">"
						L"</ns2:DigestMethod>"
						L"<ns2:DigestValue>" + hash64 + 
						L"</ns2:DigestValue>" 
						L"</ns2:Reference>"
						//
						L"<ns2:Reference"
						L" ns1:URI=\"#uuid." + keyInfoUuid + L"\">"
						L"<ns2:DigestMethod"
						L" ns1:Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.2\">"
						L"</ns2:DigestMethod>"
						L"<ns2:DigestValue>" + keyInfoHash64 + 
						L"</ns2:DigestValue>" 
						L"</ns2:Reference>" 
						//
						L"<ns2:Reference"
						L" ns1:URI=\"#SignatureProperties." + propertiesUuid + L"\">" 
						L"<ns2:DigestMethod" 
						L" ns1:Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.2\">"
						L"</ns2:DigestMethod>"
						L"<ns2:DigestValue>" + propertiesHash64 + 
						L"</ns2:DigestValue>"
						L"</ns2:Reference>"
						L"</ns2:SignedInfo>"
						;
					signedInfo_b = WideStringToUTF8(signedInfo);
					//signedInfo_b.Allocate(signedInfo.GetLength()*sizeof(wchar_t));
					//CopyMemory(signedInfo_b.GetBuffer(),signedInfo.GetString(),signedInfo_b.Length());
					//
#					ifdef _DEBUG
					{
						//OutputDebugString(_T("\n\n"));
						//OutputDebugString(_S(signedInfo)); 
					}
#					endif
				}
				//
				//
				// ----
				// �������
				//
				string signature64; 
				{
					CComPtr<ISlotSigner> pSigner;
					pSigner.Attach( Client_GetSigner() ); 
					//
					HRESULT rc = pSigner->Start();
					if (FAILED(rc)) throw MethodError(rc);
					//
					rc = pSigner->AddBlobk(signedInfo_b.GetBuffer(),signedInfo_b.Length()); 
					if (FAILED(rc)) throw MethodError(rc);
					//
					CComBSTR bstrSignature64;
					rc = pSigner->GetSignature64(&bstrSignature64);
					if (FAILED(rc)) throw MethodError(rc);
					//
					signature64 = _W(bstrSignature64); 
				}
				//
				//
				// ----
				// XMLdsig
				//
				string xmlSignature = _W(L"") + 
				L"<dsig:Signature"
				L" xmlns:dsig=\"http://www.w3.org/2000/09/xmldsig#\""
				L" xmlns:dse=\"http://cabinet.example.com/schema/xmldsigext-/rel-1/\""
				L" Id=\"uuid." + signatureUuid + L"\">\n" 
				L"	<dsig:SignedInfo>\n"
				L"		<dsig:CanonicalizationMethod"
						L" Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.1\" />\n"
				L"		<dsig:SignatureMethod"
						L" Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.3\" />\n"
				L"		<dsig:Reference URI=\"#xpointer(//*[@uuid='" + targetUuid + L"'])\">\n"
				L"			<dsig:Transforms>\n"
				L"				<dsig:Transform" 
							L" Algorithm=\"http://www.w3.org/2000/09/xmldsig#enveloped-signature\" />\n"
				L"			</dsig:Transforms>\n"
				L"			<dsig:DigestMethod"
						L" Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.2\" />\n"
				L"			<dsig:DigestValue>" + hash64 + L"</dsig:DigestValue>\n" 
				L"		</dsig:Reference>\n"
				L"		<dsig:Reference URI=\"#uuid." + keyInfoUuid + L"\">\n"
				L"			<dsig:DigestMethod"
						L" Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.2\" />\n"
				L"			<dsig:DigestValue>" + keyInfoHash64 + L"</dsig:DigestValue>\n" 
				L"		</dsig:Reference>\n" 
				L"		<dsig:Reference URI=\"#SignatureProperties." + propertiesUuid + L"\">\n" 
				L"			<dsig:DigestMethod" 
						L" Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.2\" />\n"
				L"			<dsig:DigestValue>" + propertiesHash64 + L"</dsig:DigestValue>\n"
				L"		</dsig:Reference>\n"
				L"	</dsig:SignedInfo>\n"
				L"	<dsig:SignatureValue>" + signature64 + L"</dsig:SignatureValue>\n"
				L"	<dsig:KeyInfo Id=\"uuid." + keyInfoUuid + L"\">\n"
				L"		<dsig:X509Data>\n" + 
				x509 +
				L"		</dsig:X509Data>\n"
				L"	</dsig:KeyInfo>\n"
				L"	<dsig:Object>\n"
				L"		<dsig:SignatureProperties Id=\"SignatureProperties." + propertiesUuid + L"\">\n"
				L"			<dsig:SignatureProperty Target=\"#uuid." + signatureUuid + L"\">\n"
				L"				<dse:Events SignatureTime=\"" + t_s + L"\" />\n"
				L"				<dse:MetaInfo>\n"
				L"					<dse:Method Name=\"Validate\"" 
							L" Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.9.1\" />\n"
				L"					<dse:Method Name=\"Analyze\""
							L" Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.5\" />\n"
				L"					<dse:Method Name=\"Report\""
							L" Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.6\" />\n"
				L"				</dse:MetaInfo>\n"
				L"			</dsig:SignatureProperty>\n"
				L"		</dsig:SignatureProperties>\n"
				L"	</dsig:Object>\n"
				L"</dsig:Signature>\n"
				;
				//
#				ifdef _DEBUG
				{
					//OutputDebugString(_T("\n\n"));
					//OutputDebugString(_S(xmlSignature)); 
				}
#				endif
				//
				return xmlSignature; 
			}
			_Catch()
		}



		inline static string p_GetXmlSignature(
			const string& targetUuid,
			const string& hash64,
			const COleDateTime& t, 
			//
			Blob certData, 
			bool m_F_skipX509Cert, 
			ISlotSigner* pSigner 
			)
		{
			try
			{
				// �����
				//
				string t_s_1 = FormatStr(L"%04d-%02d-%02d", t.GetYear(), t.GetMonth(), t.GetDay() );
				string t_s_2 = FormatStr(L"T%02d:%02d:%02dZ", t.GetHour(), t.GetMinute(), t.GetSecond() );
				//
				string t_s = t_s_1 + t_s_2; 
				//
				// Signature
				//
				string signatureUuid = NewGuidStr(); 
				//
				// KeyInfo
				//
				string keyInfoUuid = NewGuidStr();
				//
				/// Blob certData = Client_GetCertData();
				string certificate64 = ToBase64Padding(certData); 
				//
				string x509;
				if (m_F_skipX509Cert)
				{
					CCOM_Certificate C;
					C->Import(certData); 
					//
					Blob pkh = C->GetPKH(); 
					string pkh64 = __ToBase64(pkh); 
					//
					x509 = L"<dse:PublicKeyHash>" + pkh64 + L"</dse:PublicKeyHash>"; 
				}
				else
				{
					x509 = L"<dsig:X509Certificate>" + certificate64 + L"</dsig:X509Certificate>"; 
				}
				//
				// Properties
				//
				string propertiesUuid = NewGuidStr(); 
				//
				//
				// ----
				// ���������� ����� ��������� 
				//
				// KeyInfo
				//
				string keyInfoHash64;
				{
					string normalCertificate64 = certificate64;
					Hasher_AdjustText(normalCertificate64);
					//
					string normalKeyInfo = 
					 _W(L"<ns2:KeyInfo") +
						L" xmlns:ns1=\"\""
						L" xmlns:ns2=\"" + XmlDsigNs() + L"\""
						L" ns1:Id=\"uuid." + keyInfoUuid + L"\">"
						L"<ns2:X509Data>" + 
						L"<ns2:X509Certificate>" + normalCertificate64 + L"</ns2:X509Certificate>" + 
						L"</ns2:X509Data>"
						L"</ns2:KeyInfo>"
						;
					Blob normalKeyInfo_b = WideStringToUTF8(normalKeyInfo);
					//normalKeyInfo_b.Allocate(normalKeyInfo.GetLength()*sizeof(wchar_t));
					//CopyMemory(normalKeyInfo_b.GetBuffer(),normalKeyInfo.GetString(),normalKeyInfo_b.Length());
					keyInfoHash64 = Algorithms::Alg_1_8_2().Encode(normalKeyInfo_b); 
					//
#					ifdef _DEBUG
					{
						//OutputDebugString(_T("\n\n"));
						//OutputDebugString(_S(normalKeyInfo)); 
					}
#					endif
				}
				//
				// Properties
				//
				string propertiesHash64;
				{
					string properties = 
						L"<ns3:SignatureProperties"
						L" xmlns:ns1=\"\""
						L" xmlns:ns2=\"" + XmlDseNs() + L"\""
						L" xmlns:ns3=\"" + XmlDsigNs() + L"\""
						L" ns1:Id=\"SignatureProperties." + propertiesUuid + L"\">"
						L"<ns3:SignatureProperty"
						L" ns1:Target=\"#uuid." + signatureUuid + L"\">"
						L"<ns2:Events"
						L" ns1:SignatureTime=\"" + t_s + L"\">"
						L"</ns2:Events>"
						L"<ns2:MetaInfo>"
						L"<ns2:Method"
						L" ns1:Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.9.1\""
						L" ns1:Name=\"Validate\"" 
						L">"
						L"</ns2:Method>"
						L"<ns2:Method"
						L" ns1:Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.5\""
						L" ns1:Name=\"Analyze\""
						L">"
						L"</ns2:Method>"
						L"<ns2:Method"
						L" ns1:Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.6\""
						L" ns1:Name=\"Report\""
						L">"
						L"</ns2:Method>"
						L"</ns2:MetaInfo>"
						L"</ns3:SignatureProperty>"
						L"</ns3:SignatureProperties>"
						;
					Blob properties_b = WideStringToUTF8(properties);
					//Blob properties_b;
					//properties_b.Allocate(properties.GetLength()*sizeof(wchar_t));
					//CopyMemory(properties_b.GetBuffer(),properties.GetString(),properties_b.Length());
					propertiesHash64 = Algorithms::Alg_1_8_2().Encode(properties_b); 
					//
#					ifdef _DEBUG
					{
						//OutputDebugString(_T("\n\n"));
						//OutputDebugString(_S(properties)); 
					}
#					endif
				}
				//
				// SignedInfo 
				//
				Blob signedInfo_b;
				{
					string signedInfo = 
						L"<ns2:SignedInfo"
						L" xmlns:ns1=\"\""
						L" xmlns:ns2=\"" + XmlDsigNs() + L"\">"
						//
						L"<ns2:CanonicalizationMethod"
						L" ns1:Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.1\">"
						L"</ns2:CanonicalizationMethod>"
						//
						L"<ns2:SignatureMethod"
						L" ns1:Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.3\">"
						L"</ns2:SignatureMethod>"
						//
						L"<ns2:Reference"
						L" ns1:URI=\"#xpointer(//*[@uuid='" + targetUuid + L"'])\">"
						L"<ns2:Transforms>"
						L"<ns2:Transform" 
						L" ns1:Algorithm=\"http://www.w3.org/2000/09/xmldsig#enveloped-signature\">"
						L"</ns2:Transform>" 
						L"</ns2:Transforms>"
						L"<ns2:DigestMethod"
						L" ns1:Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.2\">"
						L"</ns2:DigestMethod>"
						L"<ns2:DigestValue>" + hash64 + 
						L"</ns2:DigestValue>" 
						L"</ns2:Reference>"
						//
						L"<ns2:Reference"
						L" ns1:URI=\"#uuid." + keyInfoUuid + L"\">"
						L"<ns2:DigestMethod"
						L" ns1:Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.2\">"
						L"</ns2:DigestMethod>"
						L"<ns2:DigestValue>" + keyInfoHash64 + 
						L"</ns2:DigestValue>" 
						L"</ns2:Reference>" 
						//
						L"<ns2:Reference"
						L" ns1:URI=\"#SignatureProperties." + propertiesUuid + L"\">" 
						L"<ns2:DigestMethod" 
						L" ns1:Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.2\">"
						L"</ns2:DigestMethod>"
						L"<ns2:DigestValue>" + propertiesHash64 + 
						L"</ns2:DigestValue>"
						L"</ns2:Reference>"
						L"</ns2:SignedInfo>"
						;
					signedInfo_b = WideStringToUTF8(signedInfo);
					//signedInfo_b.Allocate(signedInfo.GetLength()*sizeof(wchar_t));
					//CopyMemory(signedInfo_b.GetBuffer(),signedInfo.GetString(),signedInfo_b.Length());
					//
#					ifdef _DEBUG
					{
						//OutputDebugString(_T("\n\n"));
						//OutputDebugString(_S(signedInfo)); 
					}
#					endif
				}
				//
				//
				// ----
				// �������
				//
				string signature64; 
				{
					/// CComPtr<ISlotSigner> pSigner;
					/// pSigner.Attach( Client_GetSigner() ); 
					//
					HRESULT rc = pSigner->Start();
					if (FAILED(rc)) throw MethodError(rc);
					//
					rc = pSigner->AddBlobk(signedInfo_b.GetBuffer(),signedInfo_b.Length()); 
					if (FAILED(rc)) throw MethodError(rc);
					//
					CComBSTR bstrSignature64;
					rc = pSigner->GetSignature64(&bstrSignature64);
					if (FAILED(rc)) throw MethodError(rc);
					//
					signature64 = _W(bstrSignature64); 
				}
				//
				//
				// ----
				// XMLdsig
				//
				string xmlSignature = _W(L"") + 
				L"<dsig:Signature"
				L" xmlns:dsig=\"http://www.w3.org/2000/09/xmldsig#\""
				L" xmlns:dse=\"http://cabinet.example.com/schema/xmldsigext-/rel-1/\""
				L" Id=\"uuid." + signatureUuid + L"\">\n" 
				L"	<dsig:SignedInfo>\n"
				L"		<dsig:CanonicalizationMethod"
						L" Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.1\" />\n"
				L"		<dsig:SignatureMethod"
						L" Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.3\" />\n"
				L"		<dsig:Reference URI=\"#xpointer(//*[@uuid='" + targetUuid + L"'])\">\n"
				L"			<dsig:Transforms>\n"
				L"				<dsig:Transform" 
							L" Algorithm=\"http://www.w3.org/2000/09/xmldsig#enveloped-signature\" />\n"
				L"			</dsig:Transforms>\n"
				L"			<dsig:DigestMethod"
						L" Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.2\" />\n"
				L"			<dsig:DigestValue>" + hash64 + L"</dsig:DigestValue>\n" 
				L"		</dsig:Reference>\n"
				L"		<dsig:Reference URI=\"#uuid." + keyInfoUuid + L"\">\n"
				L"			<dsig:DigestMethod"
						L" Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.2\" />\n"
				L"			<dsig:DigestValue>" + keyInfoHash64 + L"</dsig:DigestValue>\n" 
				L"		</dsig:Reference>\n" 
				L"		<dsig:Reference URI=\"#SignatureProperties." + propertiesUuid + L"\">\n" 
				L"			<dsig:DigestMethod" 
						L" Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.2\" />\n"
				L"			<dsig:DigestValue>" + propertiesHash64 + L"</dsig:DigestValue>\n"
				L"		</dsig:Reference>\n"
				L"	</dsig:SignedInfo>\n"
				L"	<dsig:SignatureValue>" + signature64 + L"</dsig:SignatureValue>\n"
				L"	<dsig:KeyInfo Id=\"uuid." + keyInfoUuid + L"\">\n"
				L"		<dsig:X509Data>\n" + 
				x509 +
				L"		</dsig:X509Data>\n"
				L"	</dsig:KeyInfo>\n"
				L"	<dsig:Object>\n"
				L"		<dsig:SignatureProperties Id=\"SignatureProperties." + propertiesUuid + L"\">\n"
				L"			<dsig:SignatureProperty Target=\"#uuid." + signatureUuid + L"\">\n"
				L"				<dse:Events SignatureTime=\"" + t_s + L"\" />\n"
				L"				<dse:MetaInfo>\n"
				L"					<dse:Method Name=\"Validate\"" 
							L" Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.9.1\" />\n"
				L"					<dse:Method Name=\"Analyze\""
							L" Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.5\" />\n"
				L"					<dse:Method Name=\"Report\""
							L" Algorithm=\"http://cabinet.example.com/info/OID/1.2.643.6.2.1.8.6\" />\n"
				L"				</dse:MetaInfo>\n"
				L"			</dsig:SignatureProperty>\n"
				L"		</dsig:SignatureProperties>\n"
				L"	</dsig:Object>\n"
				L"</dsig:Signature>\n"
				;
				//
#				ifdef _DEBUG
				{
					//OutputDebugString(_T("\n\n"));
					//OutputDebugString(_S(xmlSignature)); 
				}
#				endif
				//
				return xmlSignature; 
			}
			_Catch()
		}



		inline static void Hasher_AdjustText(string& textToHash) 
		{
			try
			{
				//// ������! // textToHash.Replace(L" ",L"");
				//
				textToHash.Replace(L"\t",L"");
				textToHash.Replace(L"\n",L"");
				textToHash.Replace(L"\r",L"");
			}
			_Catch() 
		}

		string Hasher_EncodeAttribute(const string& attrValue)
		{
			string v = attrValue;
			//
			v.Replace(L"\"", L"&quot;");
			v.Replace(L"<", L"&lt;");
			v.Replace(L">", L"&gt;");
			//
			return v;
		}
	};
	// CSlotXmlFilter 

} // namespace  
