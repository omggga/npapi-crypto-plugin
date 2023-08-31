/*
 SmartSqLite3.h : ������ CComPtr, ������������ ����������.

 $Name: work1 $
 $Revision: 1.1.2.3 $
 $Date: 2008/10/16 07:09:28 $

 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


#include "sqlite3.h"
#pragma comment(lib, "sqlite3.lib" )

#include <low-level/SmartException.h>
#include <low-level/SmartPtr.h>
#include <low-level/SmartMap.h>
#include <ax/coclasses/AX_SlotMemoryReader.h>
#include <ax/coclasses/AX_SlotSqLiteReader.h>


namespace 
{

	struct SQLite3Exception : public ::::Exception 
	{
		int SqLite3_Code;

		string ExtraMsg;

		inline string _SqLite3_MessageText(int r); 

		SQLite3Exception(int r) : ::::Exception(_SqLite3_MessageText(r)) 
		{
			SqLite3_Code = r;
		}

		SQLite3Exception(int r,const string& msg) : ::::Exception(_SqLite3_MessageText(r) + L"; " + msg) 
		{
			SqLite3_Code = r;
			ExtraMsg = msg;
		}

		SQLite3Exception(const SQLite3Exception& other) : ::::Exception(other) 
		{
		}
	};



	// ----
	// Declarations



	// ----
	// Database

	class SQLite3_Transaction;

	class SQLite3_Database 
	{
	public:
		CString m_Path; 

		sqlite3* m_SqLite3_Db;

	protected:
		inline void Clear()
		{
			m_SqLite3_Db = 0; 
		}

	public:
		SQLite3_Database()
		{
			Clear(); 
		}

		inline void Init(const string& path)
		{
			try
			{
				Clear();
				//
				m_Path = path;
				//
				Open();
			}
			_Catch()
		}

		SQLite3_Database(const string& path)
		{
			Init(path); 
		}

		inline bool Open()
		{
			try
			{
				if (Connected()) return true; // ��� ���������! 
				//
				// int flags; 
				//
				{
					int r0 = sqlite3_open(
						_A(m_Path),			/* Database filename (UTF-8) */
						&m_SqLite3_Db		/* OUT: SQLite db handle */
						);
					if (r0 != SQLITE_OK)
					{
						throw SQLite3Exception(r0); 
					}
				}
				//
				if (! Connected())
				{
					throw MethodError(L"�� ������� ���������� ���������� � ��������� ��"); 
				}
				//
				return Connected(); 
			}
			_Catch() 
		}

		inline bool Connected()
		{
			try
			{
				return bool(m_SqLite3_Db != 0); 
			}
			_Catch()
		}

		inline void Disconnect() 
		{
			try
			{
				if (m_SqLite3_Db)
				{
					int r = sqlite3_close(m_SqLite3_Db); 
					if (r != SQLITE_OK)
					{
						throw SQLite3Exception(r);
					}
				}
			}
			_Catch()
		}

		inline void Dispose()
		{
			try
			{
				Disconnect();
				//
				Clear(); 
			}
			_Catch() 
		}



		// ----
		// Managing databases

		class NamedDatabases
		{
		public:
			Map<string,SQLite3_Database* > M;

			~NamedDatabases()
			{
				try
				{
					for (Map<string,SQLite3_Database* >::Iterator i(M); i; ++i)
					{
						delete (SQLite3_Database*)i;
					}
				}
				catch(::::Exception e)
				{
					OutputDebugStringW(e.ToString());
				}
				catch(...)
				{
				}
			}

			SQLite3_Database& operator [](const string& dbName)
			{
				if (!M.ContainsKey(dbName))
				{
					// ������ ���������� 
					//
					string path = dbName;
					SQLite3_Database* p = new SQLite3_Database(path);
					M[dbName] = p;
				}
				if (!M.ContainsKey(dbName))
				{
					throw MethodError(_W(L"No database: ") + dbName);
				}
				SQLite3_Database* p = M[dbName];
				return *p;
			}
		};

		inline static NamedDatabases& _NamedDatabases()
		{
			static NamedDatabases s_NamedDatabases;
			return s_NamedDatabases;
		}

		inline static SQLite3_Database& AcquireNamedDb(const string& dbPath)
		{
			try
			{
				return _NamedDatabases()[dbPath];
			}
			_Catch()
		}

		inline static SQLite3_Database& AcquireSlotDb()
		{
			try
			{
				string dbPath = L"c:\\_cabinet.db";
				//
				return AcquireNamedDb(dbPath); 
			}
			_Catch()
		}




		// ----
		// Transactions

		SQLite3_Transaction BeginTransaction();



	private:
		// ----
		// Low level procedures 

		//void pExecuteStatement(const string& sql)
		//{
		//	try
		//	{
		//		Blob bSql = WideStringToUTF8(sql);
		//		//
		//		sqlite3_stmt* stmt;
		//		const char* zTail;
		//		//
		//		int r1 = sqlite3_prepare(
		//			m_SqLite3_Db,
		//			bSql.GetBuffer(),
		//			bSql.Length(),
		//			&stmt,
		//			&zTail);
		//		if (r1 != SQLITE_OK)
		//		{
		//			throw SQLite3Exception(r);
		//		}
		//		//
		//		int r2;
		//		do
		//		{
		//			if (r2 == SQLITE_DONE)
		//			{
		//			}
		//			else if (r2 == SQLITE_BUSY)
		//			{
		//				Sleep(100);
		//			}
		//			else
		//			{
		//				throw MethodError(FormatStr(L"Strange result: %d", (int)r2));
		//			}
		//		}
		//		while (r2 != SQLITE_DONE);
		//		//

		//	}
		//	_Catch()
		//}



		// ----
		// ��������� ������ � Blob

		// TODO: � command (statement) 

		inline Blob GetBlob(const string& tableName,const string id) 
		{
			try
			{
				Blob data = GetBlob(tableName,id); 
				//
				// ...
			}
			_Catch()
		}

		inline XmlElement GetXml(const string& tableName,string id) 
		{
			try
			{
				Blob data = GetBlob(tableName,id); 
				//
				// ...
			}
			_Catch()
		}

		inline string PutXml(XmlElement) 
		{
			try
			{
				return L""; 
			}
			_Catch() 
		}



		// ----
		// �������������� ������� 

	public:
		inline void ExecuteSQL(const string& sqlText)
		{
			try
			{
				Blob zSql = _UTF8(sqlText); 
				//
				char* errMsgA = 0;
				int r = sqlite3_exec(m_SqLite3_Db, (const char*)zSql.GetBuffer(), NULL, 0, &errMsgA);
				if (r != SQLITE_OK)
				{
					string errMsg = errMsgA ? _W(errMsgA) : L"";
					throw SQLite3Exception(r,errMsg);
				}
				//
				return;
			}
			_Catch()
		}

		inline static void pExecuteSQL(const string& sqlText)
		{
			try
			{
				sqlite3* db = SQLite3_Database::AcquireSlotDb().m_SqLite3_Db; 
				//
				Blob zSql = _UTF8(sqlText); 
				//
				char* errMsgA = 0;
				int r = sqlite3_exec(db, (const char*)zSql.GetBuffer(), NULL, 0, &errMsgA);
				if (r != SQLITE_OK)
				{
					string errMsg = errMsgA ? _W(errMsgA) : L"";
					throw SQLite3Exception(r,errMsg);
				}
				//
				return;
			}
			_Catch()
		}

		inline SharedArray<string> ListTables(const string& condition=L"");

		inline bool TableExists(const string& tableName)
		{
			try
			{
				SharedArray<string> tables = ListTables(L"name='" + tableName + L"'"); 
				bool r = tables.Length() > 0;
				return r;
			}
			_Catch()
		}

		inline void CreateTable(const string& tableName,const string& text); 



		// ---------------------------------------------------------------------------------------
		// Procedures

		inline static void pFinalizeStament(sqlite3_stmt* pStmt)
		{
			try
			{
				int rc = sqlite3_finalize(pStmt);
				if (rc == SQLITE_SCHEMA)
				{
					throw MethodError(L"���������� ����������� ������ � ��");
				}
			}
			_Catch()
		}

		inline static __int64 pFindBlob(sqlite3* db, 
			const string& table, const string& nameField, const string& nameValue, 
			const string& xCond=L"", 
			const string& tName=L"", 
			int* out_t=0 
			)
		{
			try
			{
				string xCol;
				if (tName.GetLength() > 0) xCol = _W(L", ") + tName; 
				//
				string sql = _W(L"SELECT ROWID") + xCol + L" FROM " + table + 
					L" where " + nameField + L"='" + nameValue + L"'"; 
				//
				if (xCond.GetLength() > 0) 
				{
					sql += _W(L" and ") + xCond; 
				}
				//
				Blob zSql = _UTF8(sql);
				//
				sqlite3_stmt* pStmt;
				//
				int rc = sqlite3_prepare(db, (const char*)zSql.GetBuffer(), -1, &pStmt, 0);
				if (rc != SQLITE_OK) 
					throw SQLite3Exception(rc);
				//
				__int64 rowid = -1; 
				//
				rc = sqlite3_step(pStmt);
				if (rc == SQLITE_DONE) 
				{
					// no data
					//
					return -1; // not found 
				}
				else if (rc == SQLITE_ROW)
				{
					rowid = (__int64)sqlite3_column_int64(pStmt, 0);
					//
					if (tName.GetLength() > 0) 
					{
						if (out_t) *out_t = sqlite3_column_int(pStmt, 1); 
					}
				}
				else
				{
					throw SQLite3Exception(rc);
				}
				//
				pFinalizeStament(pStmt); 
				//
				return rowid;
			}
			_Catch() 
		}

		inline static __int64 pInsertZeroBlob(sqlite3* db, const string& table,
			const string& nameField, const string& nameValue, int len, 
			const string& extra_f=L"", const string& extra_v=L"")
		{
			try
			{
				// Inserting new blob 
				{
					string _f = extra_f.GetLength() == 0 ? L"" : _W(L", ") + extra_f; 
					string _v = extra_v.GetLength() == 0 ? L"" : _W(L", ") + extra_v; 
					//
					string sql = _W(L"INSERT INTO " + table + 
						L"(") + nameField + L", v_blob" + _f + L") VALUES(?, ?" + _v + L")";
					Blob zSql = _UTF8(sql);
					//
					sqlite3_stmt* pStmt;
					//
					/* Compile the INSERT statement into a virtual machine. */
					int rc = sqlite3_prepare(db, (const char*)zSql.GetBuffer(), -1, &pStmt, 0);
					if (rc != SQLITE_OK) 
						throw SQLite3Exception(rc);
					//
					Blob zName = _UTF8(nameValue);
					//
					/* Bind the key and value data for the new table entry to SQL variables
					** (the ? characters in the sql statement) in the compiled INSERT 
					** statement. 
					**
					** NOTE: variables are numbered from left to right from 1 upwards.
					** Passing 0 as the second parameter of an sqlite3_bind_XXX() function 
					** is an error.
					*/
					rc = sqlite3_bind_text(pStmt, 1, (const char*)zName.GetBuffer(), -1, SQLITE_STATIC);
					if (rc != SQLITE_OK) 
						throw SQLite3Exception(rc);
					//
					rc = sqlite3_bind_zeroblob(pStmt, 2, len);
					if (rc != SQLITE_OK) 
						throw SQLite3Exception(rc);
					//
					/* Call sqlite3_step() to run the virtual machine. Since the SQL being
					** executed is not a SELECT statement, we assume no data will be returned.
					*/
					rc = sqlite3_step(pStmt);
					if (rc == SQLITE_ROW) 
						throw SQLite3Exception(rc);
					//
					if (rc != SQLITE_DONE) 
						throw SQLite3Exception(rc);
					//
					/* Finalize the virtual machine. This releases all memory and other
					** resources allocated by the sqlite3_prepare() call above.
					*/
					//
					pFinalizeStament(pStmt); 
					//
					/* If sqlite3_finalize() returned SQLITE_SCHEMA, then try to execute
					** the statement again.
					*/
					// ...
				}
				//
				// Finding ROWID 
				return pFindBlob(db, table, nameField, nameValue);
			}
			_Catch()
		}

		inline static void pWriteBlob(sqlite3* db, const string& dbName, const string& table, 
			const string& v_field,
			__int64 rowid, IStream* stream)
		{
			try
			{
				// Opening blob for direct writing 
				//
				Blob zDbName = _UTF8(dbName);
				Blob zTable = _UTF8(table);
				Blob zField = _UTF8(v_field);
				//
				sqlite3_blob* pBlob;
				int rc = sqlite3_blob_open(db, 
					(const char*)zDbName.GetBuffer(), 
					(const char*)zTable.GetBuffer(), 
					(const char*)zField.GetBuffer(), 
					(sqlite3_int64)rowid, 
					1, // read-write 
					&pBlob);
				if (rc != SQLITE_OK) 
					throw SQLite3Exception(rc); 
				//
				const int chunkSize = 2 * 1024; 
				bool done = false;
				int step = 0;
				int pos = 0;
				do
				{
					++step;
					if (step == 128 * 1024)
					{
						throw MethodError(FormatStr(L"��������� ���������� ����� �������� (= %d)",(int)step)); 
					}
					//
					Blob b;
					b.Expand(chunkSize); 
					ULONG bytesRead = chunkSize;
					//
					HRESULT r1 = stream->Read(b.GetBuffer(),chunkSize,&bytesRead); 
					//
					if (r1 == S_FALSE)
					{
						done = true; 
					}
					else if ((r1 == S_OK) || (r1 == E_PENDING))
					{
						if (bytesRead > 0) 
						{
							b.SetSize(bytesRead); 
							//
							int len = bytesRead;
							//
							int rc = sqlite3_blob_write(pBlob, b.GetBuffer(), len, pos);
							if (rc != SQLITE_OK) 
								throw SQLite3Exception(rc); 
							//
							pos += len;
						}
						else // �������, ��� ������ ������ ������! 
							 // ��� ��������� �������� ���������� IStream � Internet-���������� 
						{
							if (r1 == S_OK)
							{
								done = true; 
							}
						}
					}
					else if (FAILED(r1))
					{
						throw MethodError(r1).AddIfNewSource_(L"������ ������ ������"); 
					}
				}
				while (! done);
			}
			_Catch()
		}
	};



	// ----
	// Transaction 

	class SQLite3_Transaction
	{
		friend SQLite3_Database;

		SQLite3_Database& m_Database;

	private:
		SQLite3_Transaction(SQLite3_Database& db) : m_Database(db)
		{
		}

	public:
		SQLite3_Database& GetDatabase()
		{
			return m_Database;
		}

		void Commit()
		{
		}

		void Rollback()
		{
		}

		void Dispose()
		{
			Rollback();
		}
	};



	// ----
	// Statement

	class SQLite3_Command
	{
		SQLite3_Database* m_Db;

		string m_SqlCommand; 

		sqlite3_stmt* m_Stmt;

		int m_State;

		inline void Clear()
		{
			m_Db = 0;
			m_SqlCommand = L"";
			m_Stmt = 0;
			m_State = -1;
		}

	public:
		SQLite3_Command()
		{
			Clear(); 
		}

		inline void Init(SQLite3_Database* db,const string& sqlText)
		{
			try
			{
				Dispose(); 
				//
				m_Db = db; 
				m_SqlCommand = sqlText; 
			}
			_Catch() 
		}

		SQLite3_Command(SQLite3_Database* db,const string& sqlText)
		{
			Clear();
			Init(db,sqlText); 
		}

		inline void Dispose()
		{
			try
			{
				if (m_Db)
				{
					int r = sqlite3_finalize(m_Stmt); 
					if (r != SQLITE_OK)
					{
						throw SQLite3Exception(r);
					}
				}
				//
				Clear(); 
			}
			_Catch()
		}

		inline void ConnectDb()
		{
			try
			{
				if (! m_Db) throw MethodError(L"No Database"); 
				//
				m_Db->Open(); 
			}
			_Catch()
		}

		void Prepare()
		{
			try
			{
				ConnectDb();
				//
				const char* tail = 0;
				//
				CStringA s(m_SqlCommand); 
				//
				int r = sqlite3_prepare(
					m_Db->m_SqLite3_Db,s.GetString(),s.GetLength() 
					,&m_Stmt,&tail
					);
				if (r != SQLITE_OK)
				{
					throw SQLite3Exception(r);
				}
			}
			_Catch() 
		}

		inline static bool WaitForNextRowState(int state)
		{
			try
			{
				bool f = (
					(state == SQLITE_BUSY)
					);
				return f;
			}
			_Catch()
		}

		inline bool WaitForNextRowState()
		{
			return WaitForNextRowState(m_State);
		}

		inline static bool OnRowState(int state)
		{
			try
			{
				bool f = (
					(state == SQLITE_ROW)
					);
				return f;
			}
			_Catch()
		}

		inline bool OnRowState()
		{
			return OnRowState(m_State);
		}

		inline bool Execute()
		{
			try
			{
				// TODO: return if ready
				//
				if (OnRowState()) return true; // ������! 
				//
				if (! m_Stmt) 
				{
					Prepare(); 
				}
				//
				return Step();
			}
			_Catch()
		}

		inline bool Step()
		{
			try
			{
				do
				{
					m_State = sqlite3_step(m_Stmt);
					//
					if (WaitForNextRowState(m_State))
					{
						// ���... 
					}
					else if (m_State == SQLITE_ROW)
					{
						return OnRowState(); // ��������� �� ������� 
					}
					else if (m_State == SQLITE_DONE)
					{
						return OnRowState(); // ���������� 
					}
					else
					{
						throw SQLite3Exception(m_State); 
					}
				}
				while (WaitForNextRowState(m_State)); 
				//
				return OnRowState();
			}
			_Catch()
		}

		inline IStream* Column_Blob_Stream(int iCol)
		{
			try
			{
				if (m_State == SQLITE_ROW) // ������ ���������������� �� ������ 
				{
					CComPtr<ISlotMemoryReader> reader;
					reader.Attach(
						CSlotSqLiteReader::ReadDataBlob<ISlotMemoryReader>(m_Stmt,iCol)
						);
					CComQIPtr<IStream> stream(reader);
					return stream.Detach();
				}
				else if (m_State == SQLITE_DONE)
				{
					throw MethodError(L"�������� ������� ������");
				}
				else if (WaitForNextRowState(m_State))
				{
					Step();
					//
					return Column_Blob_Stream(iCol);
				}
				else
				{
					throw SQLite3Exception(m_State); 
				}
			}
			_Catch()
		}

		inline Blob Column_Blob(int iCol)
		{
			try
			{
				if (m_State == SQLITE_ROW) // ������ ���������������� �� ������ 
				{
					int len = sqlite3_column_bytes(m_Stmt,iCol); 
					const void* buf = sqlite3_column_blob(m_Stmt,iCol); 
					Blob b;
					if (len > 0)
					{
						b.Allocate(len);
						CopyMemory(b.GetBuffer(),buf,len);
					}
					return b;
				}
				else if (m_State == SQLITE_DONE)
				{
					throw MethodError(L"�������� ������� ������");
				}
				else if (WaitForNextRowState(m_State))
				{
					Step();
					//
					return Column_Blob(iCol);
				}
				else
				{
					throw SQLite3Exception(m_State); 
				}
			}
			_Catch()
		}

		inline XmlDocument Column_Xml(int iCol)
		{
			try
			{
				if (m_State == SQLITE_ROW) // ������ ���������������� �� ������ 
				{
					int len = sqlite3_column_bytes(m_Stmt,iCol); 
					const void* buf = sqlite3_column_blob(m_Stmt,iCol); 
					XmlDocument doc;
					if (len > 0)
					{
						CComPtr<IStream> stream;
						stream.Attach(
							CSlotMemoryReader::ReadMemory<IStream>(buf,len)
							);
						//
						doc.LoadStream(stream); 
					}
					return doc;
				}
				else if (m_State == SQLITE_DONE)
				{
					throw MethodError(L"�������� ������� ������");
				}
				else if (WaitForNextRowState(m_State))
				{
					Step();
					//
					return Column_Xml(iCol);
				}
				else
				{
					throw SQLite3Exception(m_State); 
				}
			}
			_Catch()
		}

		inline string Column_Text(int iCol)
		{
			try
			{
				if (m_State == SQLITE_ROW) // ������ ���������������� �� ������ 
				{
					int len = sqlite3_column_bytes(m_Stmt,iCol); 
					unsigned const char* text = sqlite3_column_text(m_Stmt,iCol); 
					string t;
					if (len > 0)
					{
						t = UTF8ToWideString((const char*)text,len);
					}
					return t;
				}
				else if (m_State == SQLITE_DONE)
				{
					throw MethodError(L"�������� ������� ������");
				}
				else if (WaitForNextRowState(m_State))
				{
					Step();
					//
					return Column_Text(iCol);
				}
				else
				{
					throw SQLite3Exception(m_State); 
				}
			}
			_Catch()
		}

		inline int Column_Integer(int iCol)
		{
			try
			{
				if (m_State == SQLITE_ROW) // ������ ���������������� �� ������ 
				{
					int v = sqlite3_column_int(m_Stmt,iCol); 
					return v;
				}
				else if (m_State == SQLITE_DONE)
				{
					throw MethodError(L"�������� ������� ������");
				}
				else
				{
					Step();
					//
					return Column_Integer(iCol);
				}
			}
			_Catch()
		}
	};



	// ----
	// Recordset 

	class Recordset 
	{
	}; 






	// ===========================================================================================
	// ������� 

	inline SQLite3_Transaction ::SQLite3_Database::BeginTransaction()
	{
		try
		{
			return SQLite3_Transaction(*this);
		}
		_Catch()
	}

	inline SharedArray<string> ::SQLite3_Database::ListTables(const string& condition)
	{
		try
		{
			string sql1 = 
				L"SELECT name FROM sqlite_master"
				L" WHERE type='table'" +
				(condition.GetLength() > 0 ? (L" and " + condition) : L"") + 
				L" ORDER BY name"
				;
			//
			SQLite3_Command S(this,sql1);
			//
			S.Execute();
			//
			SharedArray<string> tables;
			// 
			while (S.OnRowState())
			{
				string tableName = S.Column_Text(0);
				tables.Add(tableName); 
				//
				S.Step();
			}
			//
			return tables;
		}
		_Catch() 
	}

	inline void ::SQLite3_Database::CreateTable(const string& tableName,const string& tableDef)
	{
		try
		{
			string sql1 = 
				_W(L"CREATE TABLE ") + tableName + L" " + tableDef
				;
			//
			ExecuteSQL(sql1);
		}
		_Catch()
	}

	inline string ::SQLite3Exception::_SqLite3_MessageText(int r) 
	{
		string msg = FormatStr(L"������ SqLite, ���: %d", (int)r ); 
		//
		msg += L", " + _W(_A(sqlite3_errmsg(SQLite3_Database::AcquireSlotDb().m_SqLite3_Db)));
		//
		return msg; 
	}

} // namespace 
