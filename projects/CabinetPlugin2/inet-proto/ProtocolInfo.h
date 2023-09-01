#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include <ax/coclasses/AX_SlotClient.h>
#include <ax/coclasses/AX_SlotFileReader.h>

using namespace ::;


// ===============================================================================================
// ����� Ufml3MimeFilterInfo

EXTERN_C const IID DIID_IProtocolInfoDi;

class ATL_NO_VTABLE ProtocolInfo : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IProtocolInfo, &IID_IProtocolInfo, &LIBID_ProtocolAppLib>, 
	public CComCoClass<ProtocolInfo, &CLSID_ProtocolInfo> 
{
public:
	ProtocolInfo()
	{
#		ifdef _TRACE_CREATION_EVENTS
		TRACE_LOG(_T("��ProtocolInfo ������")); 
#		endif
	}

	virtual ~ProtocolInfo()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_PROTOCOL) // ������������ rgs-���� 


	BEGIN_COM_MAP(ProtocolInfo)
		COM_INTERFACE_ENTRY(IProtocolInfo)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY_IID(DIID_IProtocolInfoDi, IDispatch)
	END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

	inline Protocol::AppCtx& Instance() 
	{
		return Protocol::AppCtx::Instance(); 
	}


	STDMETHOD(GetVersion)(BSTR inputMsg,BSTR* out_version)
	{
		try
		{
#			ifdef _TRACE_CALLS_2
			TRACE_LOG1(_T("VERSION: Input: %s"), _S(inputMsg).GetString() );
#			endif
			//
			CComBSTR bstrVersion(Instance().Application().GetMyVersion());
			//
			if (out_version) *out_version = bstrVersion.Detach();
			return S_OK;
		}
		_ComCatch() 
	}

	STDMETHOD(ToBase64)(BYTE* data1,int len,BSTR* out_data64) 
	{
		try
		{
			if (len <= 0) throw MethodError(E_INVALIDARG); 
			//
			Blob data;
			data.Allocate(len);
			CopyMemory(data.GetBuffer(),data1,len);
			string s64 = ::::__ToBase64(data);
			CComBSTR bstrData64(s64);
			if (out_data64) *out_data64 = bstrData64.Detach();
			return S_OK;
		}
		_ComCatch() 
	}

	STDMETHOD(FileToBase64)(BSTR bstrPath,BSTR* out_data64) 
	{
		try
		{
			CComBSTR b2(bstrPath);
			CString path(_W(b2));
			//
			if (path.GetLength() <= 3) throw MethodError(E_INVALIDARG); 
			//
			::::File f;
			f.Open(path);
			Blob data = f.ReadAll();
			f.Close();
			//
			string s64 = ::::__ToBase64(data);
			CComBSTR bstrData64(s64);
			if (out_data64) *out_data64 = bstrData64.Detach();
			return S_OK;
		}
		_ComCatch() 
	}

	STDMETHOD(Base64ToFile)(BSTR bstrPath,BSTR data64) 
	{
		try
		{
			CComBSTR bstrPath_(bstrPath); 
			CString path = _S(bstrPath_); 
			if (path.GetLength() <= 3) throw MethodError(E_INVALIDARG);  
			//
			CComBSTR bstrData64(data64);
			string data64Str = _W(bstrData64);
			//
			Blob data = FromBase64String(data64Str); 
			//
			::::File f;
			f.OpenToWrite(path);
			f.Replace((char*)data.GetBuffer(),data.Length()); 
			f.Close();
			//
			return S_OK;
		}
		_ComCatch() 
	}

	STDMETHOD(EncodeAndBase64)(BSTR encName,BSTR bstrText,BSTR* out_data64) 
	{
		try
		{
			BYTE* p;
			int len;
			//
			Blob data;
			CStringW enc = CComBSTR(encName);
			enc.MakeLower(); 
			CComBSTR b(bstrText); 
			//
			if (enc == L"utf-8")
			{
				data = WideStringToUTF8(_W(b)); 
			}
			else if (enc == L"utf-16")
			{
				CStringW textStr(b); 
				data.Allocate(textStr.GetLength() * sizeof(wchar_t)); 
				CopyMemory(data.GetBuffer(),textStr.GetString(),textStr.GetLength() * sizeof(wchar_t)); 
			}
			else if (enc == L"windows-1251")
			{
				CStringA a(_W(b)); // --> windows-1251 
				data.Allocate(a.GetLength()); 
				CopyMemory(data.GetBuffer(),a.GetString(),a.GetLength()); 
			}
			else
			{
				throw MethodError(E_INVALIDARG); 
			}
			//
			p = data.GetBuffer();
			len = data.Length();
			//
			return ToBase64(p,len,out_data64);
		}
		_ComCatch() 
	}

	STDMETHOD(GetFileStream)(BSTR path, IStream** out_stream) 
	{
		try
		{
			if (!out_stream) throw MethodError(E_POINTER); 
			//
			IStream* i = CSlotFileReader::OpenFile<IStream>(_S(CStringW(path)));
			if (!i) throw MethodError(L"Cannot open file: " + _W(path)); 
			//
			CComPtr<IStream> stream;
			stream.Attach( i );
			//
			*out_stream = stream.Detach(); 
			return S_OK; 
		}
		_ComCatch()
	}
};

OBJECT_ENTRY_AUTO(CLSID_ProtocolInfo, ProtocolInfo)
