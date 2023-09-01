/*
 AX_SlotDatabase --- ��������� ���� ������ ��. 

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
#include <ax/interfaces/ISlotDatabase.h>
#include <ax/interfaces/ISlotDbBlob.h>
//
#include <ax/coclasses/AX_SlotDbBlob.h>

using namespace ;



// =================================================
// ���������� ISlotDatabase

// CSlotDatabase 
class ATL_NO_VTABLE CSlotDatabase : 
	public CComObjectRootEx<CComSingleThreadModel>, 
	public CComCoClass<CSlotMemoryReader>, 
	public ISlotDatabase 
{
public:
	typedef CSlotDatabase Me; 

	template<class I>
	inline static I* Acquire() // new reference 
	{
		try
		{
			typedef CComObject<CSlotDatabase> _CoClass;
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

	sqlite3* m_Db;



	// ----
	// ����� ������ 

	inline void Clear()
	{
		m_Db = 0;
	}

	inline void FindDb()
	{
		if (m_Db) return;
		//
		m_Db = SQLite3_Database::AcquireSlotDb().m_SqLite3_Db;
	}

	inline void Free()
	{
		Clear(); 
	}

public:
	CSlotDatabase()
	{
		Clear(); 
	}

	BEGIN_COM_MAP(CSlotDatabase)
		COM_INTERFACE_ENTRY_IID(__uuidof(ISlotDatabase),ISlotDatabase)
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
		_ComCatch() 
	}

	void FinalRelease() 
	{
		Free();
	}



public:
	// ----
	// ISlotDatabase 

	STDMETHOD(SaveDataFromStream)(BSTR bStrName, IStream* stream)
	{
		try
		{
			string name(bStrName);
			//
			FindDb();
			//
			__int64 rowid = SQLite3_Database::pInsertZeroBlob(m_Db, L"x_cache", L"name", name, -1);
			SQLite3_Database::pWriteBlob(m_Db, L"main", L"x_cache", L"v_blob", rowid, stream); 
		}
		_ComCatch()
	}

	STDMETHOD(GetBlobStream)(BSTR bStrDbName, BSTR bStrTable, BSTR bStrNField, BSTR bStrNValue, 
		BSTR bStrVField, IStream** stream)
	{
		try
		{ 
			FindDb();
			//
			//string dbName(bStrDbName);
			//string table(bStrTable);
			//string nField(bStrNField);
			//string nValue(bStrNValue);
			//string vField(bStrVField);
			//
			CComPtr<ISlotDbBlob> iBlob;
			iBlob.Attach(
				CSlotDbBlob::GetBlob<ISlotDbBlob>(m_Db, bStrDbName, bStrTable, bStrNField, bStrNValue,
					bStrVField, -1)
				);
			////
			//HRESULT rc = iBlob->Open(bStrDbName, bStrTable, bStrNField, bStrNValue, bStrVField);
			//if (FAILED(rc)) throw MethodError(rc);
			//
			return iBlob->get_BlobStream(stream);
		}
		_ComCatch()
	}
};
// ISlotDatabase


