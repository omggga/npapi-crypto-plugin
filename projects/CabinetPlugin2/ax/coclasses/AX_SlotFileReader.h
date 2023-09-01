/*
 AX_SlotFileReader --- ���������� ������ ������ �� ����� ��� URL.

 $Name: work1 $
 $Revision: 1.1.2.5 $
 $Date: 2008/11/01 11:50:28 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include "../../low-level/SmartWriter.h"
//
#include "../interfaces/ISlotFileReader.h"


#ifndef SLOT_FILE_READER_CHUNK_SIZE
#define SLOT_FILE_READER_CHUNK_SIZE (4 * 1024)
#endif


// =================================================
// ���������� ISlotFileReader

namespace  {

// CSlotFileReader 
#ifdef _FILE_READER_PUBLIC_AX
[
	coclass,
	threading("apartment"),
	vi_progid(".FileReader"),
	progid(".FileReader.1"),
	version(1.0),
	uuid("53A17B22-B889-485b-8447-BDD2B53E0370"),
	default(ISlotFileReader),
	helpstring(".FileReader Class")
]
class ATL_NO_VTABLE CSlotFileReader : public ISlotFileReader, public IStream 
//
#else
//
class ATL_NO_VTABLE CSlotFileReader : 
	public CComObjectRootEx<CComSingleThreadModel>, 
	public CComCoClass<CSlotFileReader>, 
	public ISlotFileReader,
	public IStream 
//
#endif
{
public:
	template<class I>
	inline static I* Create() // new reference 
	{
		try
		{
			typedef CComObject<CSlotFileReader> _CoClass;
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

	template<class I>
	inline static I* OpenFile(const CString& path) // new reference 
	{
		try
		{
			CComPtr<I> i;
			i.Attach( Create<I>() ); 
			if (! i) throw MethodError(E_UNEXPECTED); 
			//
			CComQIPtr<ISlotFileReader> reader(i);
			if (! reader) throw MethodError(E_UNEXPECTED); 
			//
			HRESULT rc = reader->put_Path(CComBSTR(_W(path))); 
			if (FAILED(rc)) throw MethodError(rc);
			//
			rc = reader->Open(); // ��������� �� ������
			if (FAILED(rc)) throw MethodError(rc); 
			//
			return i.Detach(); 
		}
		_Catch() 
	}

public:
	enum States
	{
		State_0 = 0,
		State_Connected,
		State_Reading
	};

protected:
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// File 

	// ���� 

	CString m_Path; 

	// Reader 
	
	States m_State; 

	// ������ 

	::::File f;

	int m_Position;

	int m_Size; 

	int m_ChunkSize;



	// ----
	// Writer 

	::::MultiWriter m_Writer; 



	// ----
	// ����� ������ 

	inline void SetDefaultChunkSize()
	{
		m_ChunkSize = SLOT_FILE_READER_CHUNK_SIZE;  
	}

	inline void Clear() 
	{
		m_Position = 0;
		m_Size = 0; 
		//
		m_State = State_0; 
		//
		SetDefaultChunkSize(); 
	}

	inline void Free()
	{
		f.Close();
		//TRACE_LINE1(_T("close : %s"), _S(m_Path).GetString() ); 
		m_State = State_0; 
		//
		Clear();
	}



public:
	CSlotFileReader()
	{
		Clear(); 
	}

	BEGIN_COM_MAP(CSlotFileReader)
		COM_INTERFACE_ENTRY_IID(__uuidof(ISlotFileReader),ISlotFileReader)
		COM_INTERFACE_ENTRY_IID(__uuidof(IStream),IStream)
		COM_INTERFACE_ENTRY_IID(__uuidof(ISequentialStream),IStream)
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

	~CSlotFileReader()
	{
		Free(); 
	}



protected:
	// ----
	// �������� 

	inline void SetPath(const CString& path) 
	{
		try
		{
			Free(); 
			//
			// ������������� ����� ���� 
			//
			if (path.GetLength() <= 2) throw MethodError(E_INVALIDARG); 
			//
			m_Path = path; 
			m_State = State_Connected;
		}
		_Catch()
	}

	inline void SetCacheUrl() 
	{
		try
		{
			m_Path = m_Writer.GetTargetPath(); 
			m_State = State_Connected; 
		}
		_Catch() 
	}

	inline void SetCacheUrl(const string& url,const string& fileName=L"") 
	{
		try
		{
			Free(); 
			//
			// MultiWriter: 
			{
				m_Writer.SetUrl(url,_T(""),fileName); 
				//
				bool fDelEntryOnRelease_d = false;///true; // default 
				m_Writer.SetDeleteEntryOnRelease(fDelEntryOnRelease_d); 
			}
			//
			SetCacheUrl(); 
		}
		_Catch() 
	}

	static const int CacheEntryFlag_DeleteOnRelease = 1; 

	inline void SetCacheEntryFlag(int flagType,int value) 
	{
		try
		{
			if (flagType == CacheEntryFlag_DeleteOnRelease) 
			{
				// MultiWriter: 
				{
					bool fDelEntryOnRelease = (bool)(value != 0); 
					m_Writer.SetDeleteEntryOnRelease(fDelEntryOnRelease); 
				}
			}
		}
		_Catch() 
	}



public:
	// ----
	// ISlotFileReader 

	// -------------------------------------------------------------------------------------------
	// ������� ��� ������ 

	STDMETHOD(put_Path)(BSTR path) 
	{
		try
		{
			SetPath(_S(path)); 
			//
			return S_OK; 
		}
		_ComCatch()
	}

	STDMETHOD(get_Path)(BSTR* out_path) 
	{
		try
		{
			if (! out_path) throw MethodError(E_POINTER); 
			//
			CComBSTR v(m_Path);
			*out_path = v.Detach();
			return S_OK; 
		}
		_ComCatch() 
	}



	// ��������� ����� �� ������ 

	STDMETHOD(Open)() // ��������������� � ������ 
	{
		try
		{
			f.Close();
			//
			f.Open(m_Path); 
			//TRACE_LINE1(_T("open  : %s"), _S(m_Path).GetString() ); 
			m_Position = 0;
			m_Size = Machine::GetFileSize(m_Path); 
			//
			return S_OK;
		}
		_ComCatch()
	}



	// -------------------------------------------------------------------------------------------
	// ������ ��� �������� ����� 

	// �������� � ��������� ������ � IE Cache 

	STDMETHOD(CreateInCache)() 
	{
		try
		{
			// MultiWriter:
			{
				m_Writer.CreateTempFileInUrlCache(); 
			}
			SetCacheUrl(); 
			//
			return S_OK; 
		}
		_ComCatch()
	}
	
	STDMETHOD(put_CacheUrl)(BSTR url) 
	{
		try
		{
			SetCacheUrl(string(url)); 
			//
			return S_OK; 
		}
		_ComCatch()
	}
	
	STDMETHOD(SetCacheUrlExt)(BSTR url,BSTR ext) 
	{
		try
		{
			SetCacheUrl(string(url),string(ext)); 
			//
			return S_OK; 
		}
		_ComCatch()
	}

	STDMETHOD(get_CacheUrl)(BSTR* out_cacheUrl) 
	{
		try
		{
			if (! out_cacheUrl) throw MethodError(E_POINTER); 
			//
			string url;
			if (! m_Writer.GetEntry())
			{
				url = m_Writer.GetEntry()->GetUrl(); 
			}
			CComBSTR v(url);
			if (out_cacheUrl) *out_cacheUrl = v.Detach();
			return S_OK; 
		}
		_ComCatch() 
	}

	//STDMETHOD(CreateTempFile)()
	//{
	//}

	//STDMETHOD(CreateUrlCacheFile)(BSTR* urlPrefix)
	//{
	//	try
	//	{
	//	}
	//	_ComCatch()
	//}



	// �������� ������ �� ������ � ���� 

	STDMETHOD(WriteStream)(IStream* stream)
	{
		try
		{
			// ���� ������ ���� ������ ������� 
			//
			m_Writer.WriteStream(stream); 
			//
			m_Writer.Close(); // ��������� ��� ����, ��� ������ � ���� ����������� (f.Close() �� ������ ����) 
			//
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(WriteXmlDocument)(IUnknown* documentUnk)
	{
		CString path = m_Writer.GetTargetPath();
		try
		{
			try
			{
				if (! documentUnk) throw MethodError(E_POINTER); 
				//
				CComQIPtr<IXMLDOMDocument> document(documentUnk); 
				if (! document) throw MethodError(E_NOINTERFACE); 
				//
				// ----
				// ���������� 
				//
				// MultiWriter ��������� � ���������, ����� ���� ����������, �� ���� �� ������ �� ������ 
				//
				//m_Writer.SetOpen(true); 
				m_Writer.Open(); 
				//
				CComBSTR bstrPath(path); 
				//
				CComPtr<IStream> ms;
				HRESULT rc = CreateStreamOnHGlobal(0,TRUE,&ms); 
				//
				//rc = document->save(CComVariant(bstrPath)); 
				rc = document->save(CComVariant(ms)); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				LARGE_INTEGER m0;
				m0.QuadPart = 0; 
				ULARGE_INTEGER libNewPos;
				rc = ms->Seek(m0,FILE_BEGIN,&libNewPos); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				m_Writer.WriteStream(ms); 
				//
				m_Writer.Close(); // ��������� ��� ����, ��� ������ � ���� ����������� (f.Close() �� ������ ����) 
				//
				return S_OK;
			}
			_AddMessage(L"������ ��� ������ �����: " + _W(path))
		}
		_ComCatch()
	}

	STDMETHOD(WriteOpen)()
	{
		try
		{
			m_Writer.Open(); 
			//
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(WriteSetOpen)()
	{
		try
		{
			m_Writer.SetOpen(true); 
			//
			return S_OK;
		}
		_ComCatch()
	}






	// ----
	// ISequentialStream

	STDMETHOD(Read)(
		void *pv,
		ULONG cb,
		ULONG *pcbRead)
	{
		try
		{
			if (cb <= 0) return S_OK; // ������ �� ������ 
			//
			// ������ 
			//
			if (m_Size == 0)
			{
				Open(); 
			}
			//
			int len = cb;
			if (m_Position + len > m_Size) len = m_Size - m_Position;
			if (len == 0)
			{
				if (pcbRead) *pcbRead = len; 
				return S_FALSE; // ������ ��������� 
			}
			//
			int bytesRead = 0;
			Blob data = f.Read(m_Position,len,&bytesRead); 
			if (bytesRead != len) 
			{
				throw MethodError(E_UNEXPECTED); 
			}
			if (bytesRead > (int)cb) 
			{
				throw MethodError(E_UNEXPECTED); 
			}
			//
			if (data.Length() > 0)
			{
				int n = bytesRead; 
				int wrong_n = data.Length();
				if (wrong_n != n)
				{
					string errorMsg = FormatStr(
						L"������ ��� ����������� ������� ������: %d --- %d", wrong_n, n );
					throw MethodError(errorMsg); 
				}
				CopyMemory(pv,data.GetBuffer(),n); 
				//
				m_Position += data.Length(); 
				if (m_Position == m_Size)
				{
					f.Close(); 
				}
			}
			//
			if (pcbRead) *pcbRead = (ULONG)data.Length(); 
			if (data.Length() > 0)
			{
				return S_OK;
			}
			else
			{
				return S_FALSE;
			}
		}
		_ComCatch()
	}

	STDMETHOD(WriteClose)() 
	{
		try
		{
			m_Writer.Close(); 
			//
			return S_OK; 
		}
		_ComCatch() 
	}

	STDMETHOD(Write)(
		const void* pv,
		ULONG cb,
		ULONG* pcbWritten)
	{
		try
		{
			// ���������� 
			//
			// MutliWriter:
			{
				m_Writer.Open(); 
				//
				// ������
				//
				if (cb <= 0) return S_OK; 
				//
				m_Writer.AddBinary((const char*)pv,cb); 
			}
			if (pcbWritten) *pcbWritten = cb; 
			return S_OK; 
		}
		_ComCatch()
	}



	// ----
	// IStream

	HRESULT STDMETHODCALLTYPE Seek( 
		/* [in] */ LARGE_INTEGER dlibMove,
		/* [in] */ DWORD dwOrigin,
		/* [out] */ ULARGE_INTEGER *plibNewPosition) 
	{
		switch (dwOrigin)
		{
		case FILE_BEGIN:
			{
				// TODO: !!! 
				m_Position = dlibMove.LowPart;
				//
				if (m_Position == 0)
				{
					f.Close();
					f.Open(m_Path);
				}
			}
			break;
		case FILE_CURRENT:
			{
				throw MethodError(E_NOTIMPL); 
			}
			break;
		case FILE_END:
			{
				throw MethodError(E_NOTIMPL); 
			}
			break;
		default:
			{
				throw MethodError(E_NOTIMPL); 
			}
		}
		//
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE SetSize( 
		/* [in] */ ULARGE_INTEGER libNewSize) 
	{
		return E_NOTIMPL; 
	}

	HRESULT STDMETHODCALLTYPE CopyTo( 
		/* [unique][in] */ IStream *pstm,
		/* [in] */ ULARGE_INTEGER cb,
		/* [out] */ ULARGE_INTEGER *pcbRead,
		/* [out] */ ULARGE_INTEGER *pcbWritten) 
	{
		return E_NOTIMPL; 
	}

	HRESULT STDMETHODCALLTYPE Commit( 
		/* [in] */ DWORD grfCommitFlags) 
	{
		return S_OK; // ������ �� ������ 
	}

	HRESULT STDMETHODCALLTYPE Revert() 
	{
		return E_NOTIMPL; 
	}

	HRESULT STDMETHODCALLTYPE LockRegion( 
		/* [in] */ ULARGE_INTEGER libOffset,
		/* [in] */ ULARGE_INTEGER cb,
		/* [in] */ DWORD dwLockType) 
	{
		return S_OK; // ������ �� ������ 
	}

	HRESULT STDMETHODCALLTYPE UnlockRegion( 
		/* [in] */ ULARGE_INTEGER libOffset,
		/* [in] */ ULARGE_INTEGER cb,
		/* [in] */ DWORD dwLockType) 
	{
		return S_OK; // ������ �� ������ 
	}

	HRESULT STDMETHODCALLTYPE Stat( 
		/* [out] */ STATSTG *pstatstg,
		/* [in] */ DWORD grfStatFlag) 
	{
		try
		{
			ZeroMemory(pstatstg,sizeof(STATSTG));
			//
			pstatstg->cbSize.QuadPart = 0;
			pstatstg->cbSize.LowPart = Machine::GetFileSize(m_Path); 
			//
			return S_OK; 
		}
		_ComCatch()
	}

	HRESULT STDMETHODCALLTYPE Clone( 
		/* [out] */ IStream **ppstm) 
	{
		try
		{
			if (! ppstm) throw MethodError(E_POINTER); 
			//
			CComPtr<IStream> stream;
			stream.Attach(
				CSlotFileReader::Create<IStream>()  
				);
			if (! stream) throw MethodError(E_UNEXPECTED); 
			//
			CComQIPtr<ISlotFileReader> fileReader(stream); 
			if (! fileReader) throw MethodError(E_UNEXPECTED); 
			//
			HRESULT rc = fileReader->put_Path(CComBSTR(m_Path)); 
			if (FAILED(rc)) throw MethodError(rc); 
			//
			rc = fileReader->Open();
			if (FAILED(rc)) throw MethodError(rc); 
			//
			*ppstm = stream.Detach(); 
			return S_OK; 
		}
		_ComCatch() 
	}
};
// CSlotFileReader 

} // namespace  
