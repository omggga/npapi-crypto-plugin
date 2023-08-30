/*
 SlotRequestHandlerImpl.h : ���������� ����� ������� ��� ���������� ISlotRequestHandlerImpl. 

 $Name: work1 $
 $Revision: 1.1.2.3 $
 $Date: 2008/11/01 11:50:37 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include <low-level/SmartUtil.h>
#include <SlotSysUtil.h>

#include <ax/coclasses/AX_SlotMemoryReader.h>
#include <ax/coclasses/AX_SlotFileReader.h>

namespace  {

	class CSlotRequestHandlerImpl 		
	{
	public:
		template<class I,class Handler>
		inline static I* Create() // new reference 
		{
			try
			{
				typedef CComObject<Handler> _CoClass; 
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
		inline Protocol::AppCtx& Instance() 
		{
			return Protocol::AppCtx::Instance(); 
		}



	protected:
		string m_Url;

		CComPtr<IStream> m_Request;

		CComPtr<ISlotRequestComposer> m_Composer;

		inline void AttachComposer() 
		{
			try
			{
				if (m_Composer) return; 
				//
				{
					CComQIPtr<ISlotRequestComposer> q(m_Request); 
					if (! q) throw MethodError(E_NOINTERFACE); 
					m_Composer.Attach(q.Detach()); 
				}
				//
				if (! m_Composer) throw MethodError(E_NOINTERFACE); 
			}
			_Catch()
		}

		inline HRESULT GetQueryParameter(BSTR name,BSTR* out_value)
		{
			try
			{
				AttachComposer(); 
				//
				HRESULT rc = m_Composer->GetParameterAsText(name,out_value); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		inline HRESULT GetQueryParameterInner(BSTR name,BSTR* out_value)
		{
			try
			{
				AttachComposer(); 
				//
				HRESULT rc = m_Composer->GetParameterAsInnerText(name,out_value); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}



	public:
		// ----
		// ISlotRequestHandler 

		virtual STDMETHODIMP get_Request(IStream** pRequest) 
		{ 
			try 
			{ 
				if (! pRequest) throw MethodError(E_POINTER); 
				if (! m_Request) 
				{ 
					*pRequest = 0; 
				} 
				else 
				{ 
					CComQIPtr<IStream> q(m_Request); 
					*pRequest = q.Detach(); 
				} 
				return S_OK; 
			} 
			_ComCatch() 
		} 
	 
		virtual STDMETHODIMP put_Request(IStream* request) 
		{ 
			try 
			{ 
				if (m_Request) m_Request.Release(); 
				if (request) 
				{ 
					CComQIPtr<IStream> q(request); 
					m_Request.Attach(q.Detach()); 
					//
					// TODO: Url?
					//
					CComQIPtr<ISlotRequestComposer> composer(m_Request); 
					if (composer)
					{
						CComBSTR bstrUrl; 
						HRESULT rc = composer->get_Url(&bstrUrl); 
						if (FAILED(rc)) throw MethodError(rc); 
						//
						m_Url = _W(bstrUrl); 
					}
				} 
				return S_OK; 
			} 
			_ComCatch() 
		}



		// ��������� ������� 

		virtual STDMETHODIMP OnRequest() 
		{ 
			try 
			{ 
				return S_FALSE; // Skip 
			} 
			_ComCatch() 
		}

		virtual STDMETHODIMP OnResponse() 
		{ 
			try 
			{ 
				return S_FALSE; // Skip 
			} 
			_ComCatch() 
		}



		// =======================================================================================
		// ������ ���������� 

		int* m_OutStatus;
		BSTR* m_OutUrl;
		BSTR* m_OutCachePath; 
		BSTR* m_OutContentType;
		IStream** m_OutStream;

		inline void SaveOutParameters(int* out_status,BSTR* out_url,BSTR* out_cachePath,
			BSTR* out_contentType,IStream** out_stream)
		{
			m_OutStatus = out_status;
			m_OutUrl = out_url;
			m_OutCachePath = out_cachePath; 
			m_OutContentType = out_contentType;
			m_OutStream = out_stream; 
		}

#		define SaveOutParameters_() { SaveOutParameters(out_status,out_url,out_cachePath,out_contentType,out_stream); } 

		inline void PutOutParameters(int status,const string& url,const string& outCachePath=L"",
			const string& contentType=L"",
			IStream* stream=0
			)
		{
			if (m_OutStatus) *m_OutStatus = status;
			if (m_OutUrl) *m_OutUrl = CComBSTR(url).Detach();
			if (m_OutCachePath) *m_OutCachePath = CComBSTR(outCachePath).Detach(); 
			if (m_OutContentType) *m_OutContentType = CComBSTR(contentType).Detach();
			//
			if (stream)
			{
				if (m_OutStream) *m_OutStream = CComQIPtr<IStream>(stream).Detach(); 
			}
		}

		HRESULT Redirection(const string& url) 
		{
			try
			{
				PutOutParameters(307,url); 
				//
				return S_OK; 
			}
			_Catch() 
		}

		HRESULT Document(XmlDocument document) 
		{
			try
			{
				CComPtr<IXMLDOMDocument> pXmlDoc;
				pXmlDoc.Attach(
					document.QueryComInterface<IXMLDOMDocument>() // new reference 
					);
				if (! pXmlDoc) throw MethodError(E_UNEXPECTED); 
				//
				// ���������� 
				//
				CComPtr<ISlotFileReader> f;
				f.Attach(
					CSlotFileReader::Create<ISlotFileReader>() // new reference 
					);
				if (! f) throw MethodError(E_UNEXPECTED); 
				//
				string fileName;
				string cacheUrl; 
				{
					//string m_Id = NewGuidStr(); 
					//string fileName = m_Id + L".xml"; 
					//string cacheUrl = _URL_CACHE_DEFAULT_URL_BEGIN + L"_temp_/" + fileName; 
				}
				{
					fileName = L"page.xml"; 
					cacheUrl = m_Url; 
				}
				//
				HRESULT rc = f->SetCacheUrlExt(
					CComBSTR(cacheUrl) 
					,CComBSTR(fileName) 
					);
				if (FAILED(rc)) throw MethodError(rc); 
				//
				rc = f->WriteXmlDocument((IXMLDOMDocument*)pXmlDoc); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				CComBSTR bstrPath; 
				rc = f->get_Path(&bstrPath);
				string cachePath(bstrPath); 
				//
				CComQIPtr<IStream> outStream(f); 
				if (! outStream) throw MethodError(E_UNEXPECTED);
				//
				PutOutParameters(200,L"",cachePath,L"text/xml"); 
				if (m_OutStream) *m_OutStream = outStream.Detach(); 
				return S_OK; 
			}
			_Catch() 
		}

		HRESULT OkDocument(int rc) 
		{
			try
			{
				string docXml = FormatStr(L"<result rc=\"%d\" />", (int)rc ); 
				XmlDocument doc;
				doc.LoadXml(docXml); 
				return Document(doc); 
			}
			_Catch() 
		}

		HRESULT FileStream(IStream* stream) 
		{
			try
			{
				// ���������� 
				//
				CComPtr<ISlotFileReader> f;
				f.Attach(
					CSlotFileReader::Create<ISlotFileReader>() // new reference 
					);
				if (! f) throw MethodError(E_UNEXPECTED); 
				//
				string fileName;
				string cacheUrl; 
				{
					//string m_Id = NewGuidStr(); 
					//string fileName = m_Id + L".xml"; 
					//string cacheUrl = _URL_CACHE_DEFAULT_URL_BEGIN + L"_temp_/" + fileName; 
				}
				{
					fileName = L"page.xml"; 
					cacheUrl = m_Url; 
				}
				//
				HRESULT rc = f->SetCacheUrlExt(
					CComBSTR(cacheUrl) 
					,CComBSTR(fileName) 
					);
				if (FAILED(rc)) throw MethodError(rc); 
				//
				rc = f->WriteStream(stream); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				CComBSTR bstrPath; 
				rc = f->get_Path(&bstrPath);
				string cachePath(bstrPath); 
				//
				CComQIPtr<IStream> outStream(f); 
				if (! outStream) throw MethodError(E_UNEXPECTED); 
				//
				PutOutParameters(200,L"",cachePath,L"text/xml"); 
				if (m_OutStream) *m_OutStream = outStream.Detach(); 
				return S_OK; 
			}
			_Catch() 
		}

		inline HRESULT ReturnFile(const CString& path,const string& contentType)
		{
			try
			{
				throw MethodError(E_NOTIMPL); 
			}
			_Catch() 
		}
	};

} // namespace  
