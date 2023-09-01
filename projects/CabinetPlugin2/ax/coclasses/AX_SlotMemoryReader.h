/*
 AX_SlotMemoryReader --- ���������� ������ ������ ���������������� ������� � ������ ��� �������������. 

 $Name: work1 $
 $Revision: 1.1.2.3 $
 $Date: 2008/11/01 11:50:28 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include "../../low-level/AtlX.h"
#include "../../low-level/SmartPtr.h"
//
#include "../interfaces/ISlotMemoryReader.h"



// =================================================
// ���������� ISlotFileReader

// CSlotMemoryReader 
#ifdef _MEMORY_READER_PUBLIC_AX
[
	coclass,
	threading("apartment"),
	vi_progid(".FileReader"),
	progid(".FileReader.1"),
	version(1.0),
	uuid("53A17B22-B889-485b-8447-BDD2B53E0370"),
	default(ISlotMemoryReader),
	helpstring(".FileReader Class")
]
class ATL_NO_VTABLE CSlotMemoryReader : public ISlotMemoryReader, public IStream 
//
#else
//
class ATL_NO_VTABLE CSlotMemoryReader : 
	public CComObjectRootEx<CComSingleThreadModel>, 
	public CComCoClass<CSlotMemoryReader>, 
	public ISlotMemoryReader,
	public IStream
//
#endif
{
public:
	typedef CSlotMemoryReader Me; 

	template<class I>
	inline static I* Create() // new reference 
	{
		try
		{
			typedef CComObject<CSlotMemoryReader> _CoClass;
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
	inline static I* ReadBlob(::::Blob data) // new reference 
	{
		try
		{
			CComPtr<I> i;
			i.Attach( Create<I>() ); 
			if (! i) throw MethodError(E_UNEXPECTED); 
			//
			CComQIPtr<ISlotMemoryReader> reader(i);
			if (! reader) throw MethodError(E_UNEXPECTED); 
			//
			HRESULT rc = reader->put_Blob((BYTE*)&data); 
			if (FAILED(rc)) throw MethodError(rc);
			//
			return i.Detach(); 
		}
		_Catch() 
	}

	template<class I>
	inline static I* ReadMemory(const void* buf,int len) // new reference 
	{
		try
		{
			CComPtr<I> i;
			i.Attach( Create<I>() ); 
			if (! i) throw MethodError(E_UNEXPECTED); 
			//
			CComQIPtr<ISlotMemoryReader> reader(i);
			if (! reader) throw MethodError(E_UNEXPECTED); 
			//
			HRESULT rc = reader->put_Data((BYTE*)buf); 
			if (FAILED(rc)) throw MethodError(rc);
			//
			rc = reader->put_Size((int)len); 
			if (FAILED(rc)) throw MethodError(rc);
			//
			return i.Detach(); 
		}
		_Catch() 
	}

protected:
	// ----
	// ������ 

	BYTE* m_Data;

	int m_Size;

	::::Blob m_Blob; 

	int m_Position;

	int m_ChunkSize;



	// ----
	// ����� ������ 

	inline void SetDefaultChunkSize()
	{
		m_ChunkSize = 1024; // SLOT_FILE_READER_CHUNK_SIZE; 
	}

	inline void Clear()
	{
		m_Data = NULL;
		m_Size = 0;
		m_Position = 0;
		//
		SetDefaultChunkSize();
	}

	inline void Free()
	{
		// ...
		//
		Clear(); 
	}



public:
	CSlotMemoryReader()
	{
		Free(); 
	}

	BEGIN_COM_MAP(CSlotMemoryReader)
		COM_INTERFACE_ENTRY_IID(__uuidof(ISlotMemoryReader),ISlotMemoryReader)
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



public:
	// ----
	// IMemoryReader 

	STDMETHOD(put_Data)(BYTE* data)
	{
		try
		{
			m_Data = data;
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(put_Size)(int size) 
	{
		try
		{
			m_Size = size;
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(put_Blob)(BYTE* pBlob)
	{
		try
		{
			if (! pBlob) throw MethodError(E_INVALIDARG); 
			//
			m_Blob = *((::::Blob*)(void*)pBlob); 
			//
			m_Data = m_Blob.GetBuffer(); 
			m_Size = m_Blob.Length(); 
			//
			return S_OK; 
		}
		_ComCatch() 
	}



	// ----
	// ISequentialStream

	STDMETHOD(Read)(void* pv,ULONG cb,ULONG* pcbRead) 
	{
		try
		{
			if (! m_Data) 
				throw MethodError(E_POINTER);
			//
			if ((! pv) || (! pcbRead)) throw 
				MethodError(E_POINTER);
			//
			if (m_Position >= m_Size) 
			{
				if (pcbRead) *pcbRead = 0;
				return S_FALSE;
			}
			//
			if (cb <= 0) 
			{
				if (pcbRead) *pcbRead = 0;
				return S_OK;
			}
			//
			int cbAvail = m_Size - m_Position;
			int cbRead = cbAvail;
			//
			if ((int)cb < cbAvail)
			{
				cbRead = cb;
			}
			if (cbRead <= 0) 
			{
				if (pcbRead) *pcbRead = 0;
				return S_FALSE;
			}
			//
			CopyMemory(pv,m_Data+m_Position,cbRead); 
			m_Position += cbRead;
			//
			if (pcbRead) *pcbRead = cbRead;
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(Write)(void const* pv,ULONG cb,ULONG* pcbWritten) 
	{
		try
		{
			return E_NOTIMPL; 
		}
		_ComCatch()
	}



	// ----
	// IStream 

	STDMETHOD(Clone)(IStream** ppstm)
	{
		try
		{
			if (! ppstm) throw MethodError(E_POINTER);
			//
			CComPtr<ISlotMemoryReader> reader; 
			reader.Attach(
				Create<ISlotMemoryReader>() // new reference 
				);
			if (! reader) throw MethodError(E_UNEXPECTED); 
			//
			HRESULT rc = reader->put_Data(m_Data); 
			if (FAILED(rc)) throw MethodError(rc); 
			//
			rc = reader->put_Size(m_Size); 
			if (FAILED(rc)) throw MethodError(rc); 
			//
			CComQIPtr<IStream> stream(reader); 
			if (! stream) throw MethodError(E_NOINTERFACE); 
			//
			*ppstm = stream.Detach();
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(Commit)(DWORD grfCommitFlags) 
	{
		try
		{
			return S_OK; // no actions
		}
		_ComCatch()
	}

	STDMETHOD(CopyTo)(IStream* pstm,
		ULARGE_INTEGER cb,
		ULARGE_INTEGER* pcbRead,
		ULARGE_INTEGER* pcbWritten)
	{
		try
		{
			return E_NOTIMPL;
		}
		_ComCatch()
	}

	STDMETHOD(LockRegion)(ULARGE_INTEGER libOffset,ULARGE_INTEGER cb,DWORD dwLockType) 
	{
		try
		{
			return S_OK; // no actions
		}
		_ComCatch()
	}

	STDMETHOD(UnlockRegion)(ULARGE_INTEGER libOffset,ULARGE_INTEGER cb,DWORD dwLockType) 
	{
		try
		{
			return S_OK; // no actions
		}
		_ComCatch()
	}

	STDMETHOD(Revert)()
	{
		try
		{
			return E_NOTIMPL;
		}
		_ComCatch()
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
			pstatstg->cbSize.LowPart = m_Size; 
			//
			return S_OK; 
		}
		_ComCatch()
	}

	STDMETHOD(Seek)( 
		LARGE_INTEGER dlibMove, 
		DWORD dwOrigin, 
		ULARGE_INTEGER* plibNewPosition)
	{
		try
		{
			if (! plibNewPosition) throw MethodError(E_POINTER); // ����� STG_E_INVALIDPOINTER
			//
			if (dlibMove.HighPart != 0) throw MethodError(E_NOTIMPL);
			//
			int move = dlibMove.LowPart;
			//
			if (dwOrigin == FILE_BEGIN)
			{
				m_Position = move; 
			}
			else if (dwOrigin == FILE_CURRENT)
			{
				m_Position += move; 
			}
			else if (dwOrigin == FILE_END)
			{
				m_Position = m_Size; 
			}
			else
			{
				throw MethodError(E_INVALIDARG); 
			}
			return S_OK; 
		}
		_ComCatch()
	}

	HRESULT STDMETHODCALLTYPE SetSize( 
		/* [in] */ ULARGE_INTEGER libNewSize) 
	{
		return E_NOTIMPL; 
	}
};
// CSlotMemoryReader 


















//
//
//// CMemoryReaderStream
//[
//	coclass,
//	threading("apartment"),
//	vi_progid("Protocol.MemoryReaderStream"),
//	progid("Protocol.MemoryReaderStream.1"),
//	version(1.0),
//	uuid("7E42AA79-1342-45d2-B6F9-B79820A2CF21"),
//	default(IDocument),
//	helpstring(".Protocol.MemoryReaderStream Class")
//]
//class ATL_NO_VTABLE CMemoryReaderStream : public IStream, public IMemoryReader 
//{
//public:
//	CMemoryReaderStream()
//	{
//		m_Data = 0;
//		m_Size = 0;
//		m_Pos = 0;
//	}
//
//	DECLARE_PROTECT_FINAL_CONSTRUCT()
//
//	HRESULT FinalConstruct()
//	{
//		return S_OK;
//	}
//	
//	void FinalRelease() 
//	{
//	}
//
//protected:
//	void* m_Data;
//
//	int m_Size;
//
//	int m_Pos;
//
//public:
//};
//// CLocalGate
