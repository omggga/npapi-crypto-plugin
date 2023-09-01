/*
 AX_SlotDbBlob --- ����� ��� Blob / ��������� ���� ������ ��. 

 $Name: work1 $
 $Revision: 1.1.2.3 $
 $Date: 2008/11/01 11:50:28 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include <low-level/AtlX.h>
#include <low-level/SmartPtr.h>
#include <low-level/SmartSqLite3.h>
//
#include <ax/interfaces/ISlotDbBlob.h>

using namespace ;



// =================================================
// ���������� ISlotDatabase

// CSlotDbBlob 
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
class ATL_NO_VTABLE CSlotDbBlob : 
	public CComObjectRootEx<CComSingleThreadModel>, 
	public CComCoClass<CSlotMemoryReader>, 
	public ISlotDbBlob,  
	public IStream 
//
#endif
{
public:
	typedef CSlotDbBlob Me; 

	template<class I>
	inline static I* GetBlob(sqlite3* db, 
		BSTR bStrDbName, BSTR bStrTable, BSTR bStrNField, BSTR bStrNValue, 
		BSTR bStrVField, int len) // new reference 
	{
		try
		{
			typedef CComObject<CSlotDbBlob> _CoClass;
			_CoClass* pClass;
			HRESULT rc = _CoClass::CreateInstance(&pClass);
			if (FAILED(rc)) 
				throw MethodError(rc);
			//
			pClass->AddRef();
			//
			CComPtr<I> i;
			rc = pClass->QueryInterface(__uuidof(I),(void**)&i);
			if (FAILED(rc)) throw MethodError(rc);
			//
			{
				CComPtr<ISlotDbBlob> iBlob;
				rc = pClass->QueryInterface(__uuidof(ISlotDbBlob),(void**)&iBlob);
				if (FAILED(rc)) throw MethodError(rc);
				//
				rc = iBlob->Open(bStrDbName, bStrTable, bStrNField, bStrNValue, bStrVField, len);
				if (FAILED(rc)) throw MethodError(rc);
			}
			//
			pClass->Release();
			pClass = NULL;
			//
			return i.Detach();
		}
		_Catch()
	}

	template<class I>
	inline static I* GetBlob(sqlite3* db, 
		const string& dbName, const string& table, 
		const string& nField, const string& nValue, 
		const string& vField, int len) // new reference 
	{
		CComBSTR bStrDbName(dbName);
		CComBSTR bStrTable(table);
		CComBSTR bStrNField(nField);
		CComBSTR bStrNValue(nValue);
		CComBSTR bStrVField(vField);
		//
		return GetBlob<I>(db, bStrDbName, bStrTable, bStrNField, bStrNValue, bStrVField, len);
	}

protected:
	// ----
	// ������ 

	sqlite3* m_Db;

	sqlite3_blob* pBlob;

	int Position;

	int Size;

	bool IsLocal;

	bool Revalidate;

	// ��������

	CComBSTR m_bStrDbName;
	CComBSTR m_bStrTable;
	CComBSTR m_bStrNField;
	CComBSTR m_bStrNValue;
	CComBSTR m_bStrVField;
	int m_Len;


	// ----
	// ����� ������ 

	inline void Clear()
	{
		m_Db = 0;
		m_Len = 0;
		pBlob = 0;
		IsLocal = false;
		Revalidate = true; 
	}

	inline void Free() 
	{
		Close(); 
	}

	inline void _Close()
	{
		if (Started())
		{
			sqlite3_blob_close(pBlob);
			pBlob = 0;
		}
	}

	inline void FindDb()
	{
		if (m_Db) return;
		//
		m_Db = SQLite3_Database::AcquireSlotDb().m_SqLite3_Db; 
	}

	inline bool Started()
	{
		return (pBlob != 0);
	}

public:
	CSlotDbBlob()
	{
		Clear(); 
	}

	BEGIN_COM_MAP(CSlotDbBlob)
		COM_INTERFACE_ENTRY_IID(__uuidof(ISlotDbBlob),ISlotDbBlob)
		COM_INTERFACE_ENTRY_IID(__uuidof(IStream),IStream)
		COM_INTERFACE_ENTRY_IID(__uuidof(ISequentialStream),IStream)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		try
		{
			FindDb(); 
			//
			return S_OK;
		}
		_Catch()
	}

	void FinalRelease() 
	{
		Free();
	}



	// ----
	// Reading and Writing 

	inline void Begin()
	{
		try
		{
			Position = 0;
			Size = -1; // unknown 
			//
			_Open();
		}
		_Catch()
	}



public:
	// ----
	// ISlotDbBlob 

	STDMETHOD(Open)(BSTR bStrDbName, BSTR bStrTable, BSTR bStrNField, BSTR bStrNValue, 
		BSTR bStrVField, int len) 
	{
		try
		{
			FindDb();
			//
			m_bStrDbName = bStrDbName;
			m_bStrTable = bStrTable;
			m_bStrNField = bStrNField;
			m_bStrNValue = bStrNValue;
			m_bStrVField = bStrVField;
			m_Len = len;
			//
			Begin(); 
			//
			return S_OK;
		}
		_ComCatch()
	}

	void _Open() 
	{
		try
		{
			string dbName(m_bStrDbName);
			string table(m_bStrTable);
			string nField(m_bStrNField);
			string nValue(m_bStrNValue);
			string vField(m_bStrVField);
			//
			int lm_t;
			//
			__int64 rowid = SQLite3_Database::pFindBlob(m_Db, table, nField, nValue, L"" 
				, L"lm_t", &lm_t 
				); 
			//
			COleDateTime now = COleDateTime::GetCurrentTime(); 
			int now_t = 100 * now.m_dt;
			//
			if (rowid == -1) // not found 
			{
				if (m_Len > 0)
				{
					string lm_tStr = FormatStr(L"%f", (double)now_t ); 
					rowid = SQLite3_Database::pInsertZeroBlob(m_Db, table, nField, nValue, m_Len 
						, L"lm_t", lm_tStr); 
				}
			}
			else
			{
				IsLocal = true; 
				//
				int dt = now_t - lm_t; 
				if (dt < 10) 
				{
					Revalidate = false; 
				}
			}
			if (m_Len == 0) return; 
			//
			// ----
			// Opening blob for direct writing or reading 
			//
			Blob zDbName = _UTF8(dbName);
			Blob zTable = _UTF8(table);
			Blob zField = _UTF8(vField);
			//
			int rc = sqlite3_blob_open(m_Db, 
				(const char*)zDbName.GetBuffer(), 
				(const char*)zTable.GetBuffer(), 
				(const char*)zField.GetBuffer(), 
				(sqlite3_int64)rowid, 
				1, // read-write 
				&pBlob);
			if (rc != SQLITE_OK) 
				throw SQLite3Exception(rc); 
			//
			Size = sqlite3_blob_bytes(pBlob); 
			//
			// test: // rc = sqlite3_blob_write(pBlob, zDbName.GetBuffer(), 4, 0); 
		}
		_Catch() 
	}

	STDMETHOD(get_BlobStream)(IStream** out_stream) 
	{
		try
		{
			if (! Started()) 
			{
				throw MethodError(L"��������� ��������� (���������� ������� ������)"); 
			}
			//
			CComQIPtr<IStream> stream(this);
			//
			if (out_stream) *out_stream = stream.Detach();
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(get_Local)(int* out_local) 
	{
		try
		{
			if (out_local) *out_local = IsLocal ? 1 : 0;
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(get_Revalidate)(int* out_revalidate) 
	{
		try
		{
			if (out_revalidate) *out_revalidate = Revalidate ? 1 : 0;
			return S_OK;
		}
		_ComCatch() 
	}

	STDMETHOD(Start)()
	{
		try
		{
			Begin(); 
			//
			return S_OK; 
		}
		_ComCatch() 
	}

	STDMETHOD(Close)() 
	{
		try
		{
			_Close(); 
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
			TRACE_LINE(_T("blob:read{"));
			//
			if (! pv) 
				throw MethodError(E_POINTER);
			//
			if (! Started())
			{
				TRACE_LINE(_T("}"));
				if (pcbRead) *pcbRead = 0;
				return S_FALSE;
				//
				//Begin();
				//throw MethodError(L"��������� ���������"); 
			}
			//
			if (Size < 0)
			{
				Size = sqlite3_blob_bytes(pBlob);
			}
			//
			if (Size >= 0) // size is known
			{
				if (Position >= Size) 
				{
					TRACE_LINE(_T("}"));
					if (pcbRead) *pcbRead = 0;
					return S_FALSE;
				}
			}
			//
			if (cb <= 0) 
			{
				TRACE_LINE(_T("}"));
				if (pcbRead) *pcbRead = 0;
				return S_OK;
			}
			//
			int cbRead = 0;
			//
			if (Size >= 0) // size is known
			{
				int cbAvail = Size - Position;
				cbRead = cbAvail;
				//
				if ((int)cb < cbAvail)
				{
					cbRead = cb;
				}
				if (cbRead <= 0) 
				{
					TRACE_LINE(_T("}"));
					if (pcbRead) *pcbRead = 0;
					return S_FALSE;
				}
				//
				// Blob b;
				// b.Allocate(cbRead);
				//
				int r = sqlite3_blob_read(pBlob, pv, cbRead, Position);
				if (r != SQLITE_OK) 
					throw SQLite3Exception(r); 
				//
				Position += cbRead;
				//
				if (Position == Size)
				{
					_Close(); 
				}
			}
			else
			{
				throw MethodError(L"Size is unknown");
			}
			//
			TRACE_LINE(_T("}"));
			if (pcbRead) *pcbRead = cbRead;
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(Write)(void const* pv,ULONG cb,ULONG* pcbWritten) 
	{
		try
		{
			if (! pv) 
				throw MethodError(E_POINTER);
			if (cb <= 0) return S_OK; 
			//
			int r = sqlite3_blob_write(pBlob, pv, cb, Position); 
			if (r != SQLITE_OK) 
			{
				throw SQLite3Exception(r); 
			}
			//
			Position += cb;
			//
			if (pcbWritten) *pcbWritten = cb;
			return S_OK;
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
			CComPtr<IStream> iBlob; 
			iBlob.Attach(
				GetBlob<IStream>(m_Db, 
					m_bStrDbName, m_bStrTable, m_bStrNField, m_bStrNValue, m_bStrVField, m_Len) // new reference 
				);
			if (! iBlob) throw MethodError(E_UNEXPECTED); 
			//
			*ppstm = iBlob.Detach();
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
			pstatstg->cbSize.LowPart = Size; 
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
				Position = move; 
				//
				if (Position == 0)
				{
					if (! Started())
					{
						Begin(); 
					}
				}
			}
			else if (dwOrigin == FILE_CURRENT)
			{
				Position += move; 
			}
			else if (dwOrigin == FILE_END)
			{
				Position = Size >= 0 ? Size : 0; 
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
// ISlotDatabase


