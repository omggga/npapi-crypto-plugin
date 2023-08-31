/*
 File.h : ������� �������� ��������.

 $Name: work1 $
 $Revision: 1.1.2.6 $
 $Date: 2008/11/01 11:51:04 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

// ATL
//
#include <atlfile.h>

// 
//
#include "SmartVeryLowLevel.h"
#include "SmartPtr.h"

namespace  { 



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� File

// ������� �������� ��������

	class File
	{
	protected:
		CString m_path;

		bool m_bLocked;

	public:
		CAtlFile* m_spFile;

	protected:
		void Free()
		{
			if (m_spFile) 
			{
				m_spFile->Close(); 
				LogClose(); 
				delete m_spFile;
			}
			m_spFile = 0;
			m_path = _T("");
		}

		void Renew()
		{
			Free();
			m_spFile = new CAtlFile();
		}

	public:
		File() : m_spFile(0), m_bLocked(false)
		{
		}

		~File()
		{
			Close();
		}

		inline void LogOpen()
		{
#			ifdef _DEBUG
			//TRACE_LINE(_T("@ ") + _S(m_path)); 
#			endif
		}

		inline void LogClose()
		{
#			ifdef _DEBUG
			//TRACE_LINE(_T("~ ") + _S(m_path)); 
#			endif
		}

		void Open(const CString& path
			, DWORD flags_a=FILE_READ_DATA 
			, DWORD flags_m=FILE_SHARE_READ 
			, DWORD flags_o=OPEN_EXISTING 
			) 
		{
			try
			{
				try
				{
					Renew();
					//
					m_path = path;
					//
					LogOpen(); 
					//
					HRESULT rc = m_spFile->Create(m_path,
						flags_a,
						flags_m,
						flags_o
						); 
					if (rc != S_OK)
					{
						throw MethodError(rc);
					}
				}
				_Catch() 
			}
			_AddMessage(_W(m_path))
		}

		void OpenToRead(const CString& path) 
		{
			Open(path
				, FILE_READ_DATA 
				, FILE_SHARE_READ 
				, OPEN_EXISTING 
				); 
		}

		void OpenToWrite(const CString& path) 
		{
			Open(path
				, GENERIC_WRITE | GENERIC_READ 
				, FILE_SHARE_WRITE | FILE_SHARE_READ 
				, OPEN_ALWAYS 
				); 
		}

		void Close()
		{
			Free();
		}

		ULONGLONG LockTail(int lockSize)
		{
			if (m_bLocked) return 0;
			//
			ULONGLONG fileSize = 0;
			//
			bool bReady = false;
			//
			HRESULT rc;
			//
			while (! bReady)
			{
				rc = m_spFile->GetSize(fileSize);
				if (rc != S_OK)
				{
					//return HandleError_(rc);
					TRACE_LOG("Error"); return 0;
				}
				//
				rc = m_spFile->LockRange(fileSize,lockSize);
				if (rc != S_OK)
				{
					//return HandleError_(rc);
					TRACE_LOG("Error"); return 0;
				}
				m_bLocked = true;
				///m_pos = fileSize;
				//
				ULONGLONG fileSize_2;
				rc = m_spFile->GetSize(fileSize_2);
				if (rc != S_OK)
				{
					//return HandleError_(rc);
					TRACE_LOG("Error"); return 0;
				}
				if (fileSize == fileSize_2)
				{
					bReady = true;
				}
				else
				{
					rc = m_spFile->UnlockRange(fileSize,lockSize);
					if (rc != S_OK)
					{
						///m_state = rc;
						TRACE_LOG("Error"); return 0;
						//return HandleError_(rc);
					}
					m_bLocked = false;
				}
			}
			return fileSize;
		}

		void Unlock(ULONGLONG start,int size)
		{
			if (! m_bLocked) return;
			//
			m_spFile->UnlockRange(start,ULONGLONG(size));
		}

		ULONGLONG Append(const CString& text) 
		{
			try
			{
				CStringA textA(text); // Windows-1251 
				//
				// Locking
				//
				ULONGLONG pos = LockTail(textA.GetLength());
				m_spFile->SetSize(pos+textA.GetLength());
				//
				HRESULT rc = m_spFile->Seek(pos,FILE_BEGIN);
				if (FAILED(rc)) throw MethodError(rc); 
				//
				rc = m_spFile->Write((const void*)textA.GetString(),textA.GetLength());
				if (FAILED(rc)) throw MethodError(rc); 
				//
				Unlock(pos,textA.GetLength());
				//
				return pos;
			}
			_Catch() 
		}

		void Touch()
		{
			try
			{
				CStringA dummy(""); 
				HRESULT rc = m_spFile->Write(dummy.GetBuffer(),0); 
				if (FAILED(rc)) throw MethodError(rc); 
			}
			_Catch()
		}

		void Write(const CString& text,ULONGLONG start=0) 
		{
			CStringA textA(text); // Windows-1251 
			//
			HRESULT rc;
			rc = m_spFile->LockRange(start,text.GetLength());
			rc = m_spFile->Seek(start,FILE_BEGIN);
			rc = m_spFile->Write((const void*)textA.GetString(),textA.GetLength());
			rc = m_spFile->UnlockRange(start,text.GetLength());
		}

		void Replace(const CString& text)
		{
			try
			{
				CStringA textA(text);
				//
				// Locking
				//
				ULONGLONG pos = 0;
				///m_spFile->LockRange(pos,textA.GetLength());
				HRESULT rc = m_spFile->SetSize(pos+textA.GetLength());
				if (FAILED(rc)) throw MethodError(rc); 
				//
				rc = m_spFile->Seek(pos,FILE_BEGIN);
				if (FAILED(rc)) throw MethodError(rc); 
				//
				rc = m_spFile->Write((const void*)textA.GetString(),textA.GetLength());
				if (FAILED(rc)) throw MethodError(rc); 
				//
				///Unlock(pos,textA.GetLength());
			}
			_Catch()
		}

		void Replace(const char* buf,int size,int start=0)
		{
			try
			{
				// Locking
				//
				ULONGLONG pos = start;
				///m_spFile->LockRange(pos,size);
				m_spFile->SetSize(pos+size);
				//
				HRESULT rc = m_spFile->Seek(pos,FILE_BEGIN);
				if (rc != S_OK)
				{
					TRACE_LOG1(_T("������ ��� ������ CAtlFile::Seek: 0x%x"), (int)rc );
					Unlock(pos,size);
					return;
				}
				rc = m_spFile->Write((const void*)buf,size);
				if (rc != S_OK)
				{
					TRACE_LOG1(_T("������ ��� ������ CAtlFile::Write: 0x%x"), (int)rc );
					Unlock(pos,size);
					return;
				}
				//
				///Unlock(pos,size);
			}
			_Catch()
		}

		Blob ReadAll()
		{
			Blob data;
			int S = 0;
			//
			HRESULT rc;
			DWORD size = 1024;
			DWORD readSize = size;
			char* buf = new char[size];
			rc = m_spFile->Seek(0,FILE_BEGIN);
			if (rc != S_OK)
			{
				TRACE_LOG1(_T("������ ��� ������ CAtlFile::Seek: 0x%x"), (int)rc );
				return Blob();
			}
			//
			while (readSize == size)
			{
				rc = m_spFile->Read((void*)buf,size,readSize);
				if (rc != S_OK)
				{
					TRACE_LOG1(_T("������ ��� ������ CAtlFile::Seek: 0x%x"), (int)rc );
					return Blob();
				}
				if (readSize > 0)
				{
					data.Expand(S+readSize);
					CopyMemory(data.GetBuffer()+S,buf,readSize); 
					S += readSize;
					data.SetSize(S);
				}
			}
			delete[] buf;
			//
			//Blob data;
			//data.Allocate(textA.GetLength());
			//CopyMemory(data.GetBuffer(),textA.GetString(),textA.GetLength());
			//
			return data;
		}

		Blob Read(int start,int len_,int* out_bytesRead=0)
		{
			const int chunk_0 = 4 * 1024; 
			//
			int len = len_;
			if (len == 0) 
			{
				if (out_bytesRead) *out_bytesRead = 0;
				return Blob(); 
			}
			//
			int chunk = chunk_0;
			if (chunk > len) chunk = len; 
			//
			Blob data;
			int S = 0; // 0 <= S <= len // ������� � data 
			//
			HRESULT rc0 = m_spFile->Seek(start,FILE_BEGIN);
			if (FAILED(rc0)) throw MethodError(rc0); 
			//
			do
			{
				Blob buf;
				buf.Allocate(chunk);
				//
				HRESULT rc;
				DWORD bytesRead = 0;
				do
				{
					int size = chunk;
					if (S + size > len) size = len - S;
					//
					if (size == 0)
					{
						bytesRead = 0; 
						rc = S_OK; 
					}
					else // size > 0 
					{
						rc = m_spFile->Read(buf.GetBuffer(),size,bytesRead); 
						if (rc == E_PENDING)
						{
							// ���... 
#							ifdef _DEBUG
							TRACE_LINE(_T("File: ���...")); 
#							endif
						}
						if (FAILED(rc)) throw MethodError(rc); 
						//
						// ---- 
						// � ������ ������... 
						//
						//// if (FAILED(rc)) throw MethodError(rc); 
					}
				}
				while (rc == E_PENDING); 
				//
				if (bytesRead > 0) 
				{
					data.Expand(S+bytesRead);
					CopyMemory(data.GetBuffer()+S,buf.GetBuffer(),bytesRead); 
					S += bytesRead;
					data.SetSize(S); // new value of S 
				}
				else
				{
					len = S; 
				}
			}
			while (S < len);
			//
			if (out_bytesRead) *out_bytesRead = len; 
			return data;
		}

		Blob GetSHA1()
		{
			HCRYPTPROV new_CSP = 0;
			//
			if (! CryptAcquireContext(
				&new_CSP, 
				NULL, 
				NULL, 
				PROV_RSA_FULL, 
				CRYPT_VERIFYCONTEXT)) 
			{
				TRACE_LOG1(_T("������ ��� ������ CryptAcquireContext: 0x%x"), (int)GetLastError() );
				return Blob();
			}
			//
			HCRYPTHASH hash = 0;
			if (! CryptCreateHash(new_CSP,CALG_SHA1,0,0,&hash))
			{
				TRACE_LOG1(_T("������ ��� ������ CryptCreateHash: 0x%x"), (int)GetLastError() );
				return Blob();
			}
			//
			HRESULT rc;
			DWORD size = 1024;
			DWORD readSize = size;
			char* buf = new char[size];
			rc = m_spFile->Seek(0,FILE_BEGIN);
			if (rc != S_OK)
			{
				TRACE_LOG1(_T("������ ��� ������ CAtlFile::Seek: 0x%x"), (int)rc );
				return Blob();
			}
			//
			while (readSize == size) 
			{
				rc = m_spFile->Read((void*)buf,size,readSize);
				if (rc != S_OK)
				{
					TRACE_LOG1(_T("������ ��� ������ CAtlFile::Seek: 0x%x"), (int)rc );
					return Blob();
				}
				if (readSize > 0)
				{
					if (! CryptHashData(hash,(BYTE*)buf,readSize,0))
					{
						TRACE_LOG1(_T("������ ��� ������ CryptHashData: 0x%x"), (int)GetLastError() );
						return Blob();
					}
				}
			}
			delete[] buf;
			//
			DWORD dwDigestedSize = 0;
			if(! CryptGetHashParam(hash,
				HP_HASHVAL,
				0,
				&dwDigestedSize,
				0))
			{
				TRACE_LOG1(_T("������ ��� ������ CryptGetHashParam: 0x%x"), (int)GetLastError() );
				return Blob();
			}
			//
			Blob digest;
			digest.Allocate(dwDigestedSize); 
			//
			if(! CryptGetHashParam(hash,
				HP_HASHVAL,
				digest.GetBuffer(),
				&dwDigestedSize,
				0))
			{
				TRACE_LOG1(_T("������ ��� ������ CryptGetHashParam: 0x%x"), (int)GetLastError() );
				return Blob();
			}
			//
			return digest;
		}

		//////CString ReadAsString()
		//////{
		//////	return CString(Convert<Blob,CString>((const Blob&)ReadAll()));
		//////}

		// ����� �������

		static Blob ReadFile(const CString& path)
		{
			File f;
			f.Open(path);
			Blob data = f.ReadAll();
			f.Close();
			return data;
		}













		////void OpenLog(const CString& localPath,const CString& fileExt=_T("log")) 
		////{
		////	CString SLOTHOME = GetSLOTHOME();
		////	if (SLOTHOME.GetLength() > 0)
		////	{
		////		CString logsPath = SLOTHOME + _T("\\logs"); 
		////		CreateDirectory(logsPath,0);
		////		CString path;
		////		path = FormatStr(_T("%s\\%s.%s"), logsPath.GetString(), localPath.GetString(), fileExt.GetString() ); 
		////		Open(path);
		////	}
		////}

		////void OpenActionLog(const CString& localPath,const CString& fileExt=_T("log"),
		////	const CString& dirName=_T(""))
		////{
		////	CString SLOTHOME = GetSLOTHOME();
		////	if (SLOTHOME.GetLength() > 0)
		////	{
		////		CString logsPath = SLOTHOME + _T("\\logs");
		////		CreateDirectory(logsPath,0);
		////		CString actionsPath = logsPath + _T("\\actions");
		////		CreateDirectory(actionsPath,0);
		////		if (dirName.GetLength() > 0)
		////		{
		////			actionsPath = actionsPath + _T("\\") + dirName;
		////			CreateDirectory(actionsPath,0);
		////		}
		////		CString path;
		////		path = FormatStr(_T("%s\\%s.%s"), actionsPath.GetString(), localPath.GetString(), fileExt.GetString() ); 
		////		Open(path);
		////	}
		////}

		
		
	//#	define BAD_SLOTHOME _T("C:\\Temp\\_SLOTHOME")
	//	static CString GetSLOTHOME()
	//	{
	//		static CString SLOTHOME;
	//		//
	//		if (SLOTHOME.GetLength() == 0)
	//		{
	//			// TODO: ���� � �������...
	//			//
	//			HKEY hkSLOTHOME;
	//			LONG rc = 
	//				RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("SOFTWARE\\\\Slot"),0,KEY_QUERY_VALUE,&hkSLOTHOME);
	//			if (rc != ERROR_SUCCESS)
	//			{
	//				TRACE_LOG(_T("�� ������ ������� ���� ������� ��� SLOTHOME"));
	//				return CheckPath(BAD_SLOTHOME);
	//			}
	//			//
	//			CHeapPtr<BYTE> buf;
	//			DWORD bufSize = 4096;
	//			buf.Allocate(bufSize);
	//			SecureZeroMemory((BYTE*)buf,bufSize*sizeof(BYTE));
	//			DWORD kType = REG_SZ;
	//			rc = RegQueryValueEx(hkSLOTHOME,_T("SlotHome"),0,&kType,(BYTE*)buf,&bufSize);
	//			if (rc != ERROR_SUCCESS)
	//			{
	//				TRACE_LOG(_T("�� ������� ������� �������� SlotHome"));
	//				return CheckPath(BAD_SLOTHOME);
	//			}
	//			if (kType != REG_SZ)
	//			{
	//				TRACE_LOG(_T("�������� ��� �������� ��� SlotHome"));
	//				return CheckPath(BAD_SLOTHOME);
	//			}
	//			SLOTHOME = CString((TCHAR*)(BYTE*)buf);
	//			//// TRACE_LOG1(_T("SLOTHOME �� �������!   '%s'"), SLOTHOME.GetString());
	//			if (SLOTHOME.GetLength() > 0) return CheckPath(SLOTHOME);
	//			//
	//			// ���� ��������...
	//			//
	//			SLOTHOME.GetEnvironmentVariable(_T("SLOTHOME")); 
	//			if (SLOTHOME.GetLength() > 0) return CheckPath(SLOTHOME);
	//		}
	//		//
	//		return CheckPath(SLOTHOME);
	//	}
	//
	//	static CString CheckPath(const CString& path)
	//	{
	//		CString path1(path);
	//		//
	//		while (path1[path1.GetLength()-1] == _T('\\'))
	//		{
	//			path1 = path1.Left(path1.GetLength()-1);
	//		}
	//		//
	//		if (path1.GetLength() == 0)
	//		{
	//			path1 = _T("C:\\Temp\\_1");
	//		}
	//		//
	//		return path1;
	//	}
	};

} // namespace  
