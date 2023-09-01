
#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include "resource.h"       // main symbols

#include <slot/cpp/inet-proto/CabinetApp.h>
#include <slot/cpp/inet-proto/Client.h>
#include <slot/cpp/inet-proto/UrlCache.h>
#include <slot/cpp/inet-proto/IDocument.h>
#include <slot/cpp/inet-proto/IDocumentHandler.h>
#include <slot/cpp/inet-proto/IGate.h>
//
#include <slot/cpp/alg/Alg_1_8_2.h>
#include <slot/cpp/alg/Alg_1_8_5.h>
#include <slot/cpp/alg/Alg_1_8_8.h>
//
using namespace ::;
using namespace ::::Protocol;
using namespace ::::Algorithms;



// CDocument
[
	coclass,
	threading("apartment"),
	vi_progid("Protocol.Document"),
	progid("Protocol.Document.1"),
	version(1.0),
	uuid("8C91539A-F059-46BC-B304-1CEA8F0E8A05"),
	default(IDocument),
	helpstring("Document Class provided by [] Internet protocol")
]
class ATL_NO_VTABLE CDocument : 
	public IDocument
{
public:
	CDocument()
	{
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

protected:
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// ������

	RequestInfo m_RequestInfo;

	RequestInfo m_DocumentInfo;

public:
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// ����� IDocument 

	// RequestInfo

	STDMETHOD(get_RequestInfo)(IXMLDOMDocument** pVal)
	{
		try
		{
			if (! pVal) return E_POINTER;
			//
			IXMLDOMDocument* out_value;
			//
			if (m_RequestInfo.Document.IsEmpty())
			{
				out_value = 0;
			}
			else
			{
				CComQIPtr<IXMLDOMDocument> doc(m_RequestInfo.Document.GetXMLDOMDocument());
				out_value = doc.Detach();
			}
			*pVal = out_value;
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(put_RequestInfo)(IXMLDOMDocument* pVal)
	{
		try
		{
			m_RequestInfo.New();
			m_RequestInfo.Document.Dispose();
			//
			if (pVal)
			{
				CComQIPtr<IXMLDOMDocument> doc(pVal);
				m_RequestInfo.Document = pVal;
			}
			return S_OK;
		}
		_ComCatch()
	}



	// DocumentInfo

	STDMETHOD(get_DocumentInfo)(IXMLDOMDocument** pVal)
	{
		try
		{
			if (! pVal) return E_POINTER;
			//
			IXMLDOMDocument* out_value;
			//
			if (m_DocumentInfo.Document.IsEmpty())
			{
				out_value = 0;
			}
			else
			{
				CComQIPtr<IXMLDOMDocument> doc(m_DocumentInfo.Document.GetXMLDOMDocument());
				out_value = doc.Detach();
			}
			*pVal = out_value;
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(put_DocumentInfo)(IXMLDOMDocument* pVal)
	{
		try
		{
			m_DocumentInfo.New();
			m_DocumentInfo.Document.Dispose();
			//
			if (pVal)
			{
				CComQIPtr<IXMLDOMDocument> doc(pVal);
				m_DocumentInfo.Document = pVal;
			}
			return S_OK;
		}
		_ComCatch()
	}



	// Status

	inline int GetStatus()
	{
		return m_DocumentInfo.GetResponseStatus();
	}

	STDMETHOD(get_Status)(int* pVal) 
	{
		try
		{
			if (!pVal) throw MethodError(E_POINTER);
			//
			*pVal = GetStatus();
			return S_OK;
		}
		_ComCatch()
	}
	
	STDMETHOD(get_Decision)(int* pVal)
	{
		try
		{
			if (!pVal) throw MethodError(E_POINTER);
			//
			int status = GetStatus();
			//
			int decision = Decision_Unknown;
			//
			if (status == 200)
			{
				// ������!
				decision = Decision_Ok;
			}
			else if (status >= 400) // 4xx, 5xx, ... 
			{
				// ������,- ���������������!
				decision = Decision_Ok;
			}
			else if (status == 307)
			{
				decision = Decision_Redirect;
			}
			else
			{
				throw MethodError(_S("���������������� HTTP-��� %d") % (int)status );
			}
			//
			*pVal = decision;
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(get_ResponseHeaderLocation)(BSTR* pVal) 
	{
		try
		{
			if (!pVal) throw MethodError(E_POINTER);
			//
			string location = m_DocumentInfo.GetResponseHeader(L"Location");
			//
			*pVal = CComBSTR(location).Detach();
			return S_OK;
		}
		_ComCatch()
	}
	
	STDMETHOD(get_ResultCachePath)(BSTR* pVal)
	{
		try
		{
			if (!pVal) throw MethodError(E_POINTER);
			//
			string cachePath;
			string referenceUrl = m_DocumentInfo.GetResponseReferenceUrl();
			UrlCacheEntry entry(_S(referenceUrl));
			if (entry.Exists())
			{
				cachePath = entry.GetPath();
			}
			else
			{
				string localPath = m_DocumentInfo.GetResponseLocalPath();
				if (localPath.GetLength() == 0) throw MethodError(_T("�������� ����������� � ������\n") + _S(referenceUrl));
				entry.Create();
				CString cachePath = entry.GetPath();
				if (!CopyFile(_S(localPath),cachePath,FALSE)) // overwriting 
				{
					HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
					throw MethodError(rc);
				}
			}
			//
			*pVal = CComBSTR(cachePath).Detach();
			return S_OK;
		}
		_ComCatch()
	}
	
	STDMETHOD(get_NextRequestKeepsPost)(int* pVal) 
	{
		try
		{
			if (!pVal) throw MethodError(E_POINTER);
			//
			int keepPost = _Convert_::ToInt(m_DocumentInfo.GetResponseHeader(L"keep-post"));
			//
			*pVal = keepPost;
			return S_OK;
		}
		_ComCatch()
	}
	
	STDMETHOD(get_NextRequestInfo)(IXMLDOMDocument** pVal) 
	{
		try
		{
			if (!pVal) throw MethodError(E_POINTER);
			//
			XmlDocument nextRI_doc = m_DocumentInfo.GetParameterAsXmlDocument(
				L"next-request-info",L"",L"headers");
			if (nextRI_doc.IsEmpty())
			{
				*pVal = 0;
			}
			else
			{
				CComQIPtr<IXMLDOMDocument> doc(nextRI_doc.GetXMLDOMDocument());
				*pVal = doc.Detach();
			}
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(get_ReferenceUrl(BSTR* pVal))
	{
		try
		{
			if (!pVal) throw MethodError(E_POINTER);
			//
			string referenceUrl = m_DocumentInfo.GetResponseReferenceUrl();
			//
			*pVal = CComBSTR(referenceUrl).Detach();
			return S_OK;
		}
		_ComCatch()
	}



	// Load

	STDMETHOD(Load)()
	{
		try
		{
			Client& client = Client::Acquire();
			//
			string localGateProgId = (string)client.GetVariable(_T("local-gate-progid"));
			if (localGateProgId.GetLength() == 0) 
				throw MethodError(_T("����������� �������� local-gate-progid"));
			//
			CComPtr<IGate> localGate;
			HRESULT rc = localGate.CoCreateInstance(localGateProgId);
			if (rc != S_OK) throw MethodError(rc);
			//
			CComPtr<IXMLDOMDocument> doc;
			rc = localGate->ProcessRequest(m_RequestInfo.Document.GetXMLDOMDocument(),&doc);
			if (rc != S_OK) throw MethodError(rc);
			//
			m_DocumentInfo.Document = (IXMLDOMDocument*)doc;
			//
			return S_OK;
		}
		_ComCatch()
	}
};
