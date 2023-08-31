/*
 SmartUrlCache.h : ������ ��� ������ � ������������ ������� Internet. 

 $Name: work1 $
 $Revision: 1.1.2.3 $
 $Date: 2009/05/18 12:32:28 $

 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


#include "SmartPtr.h"
#include "SmartMachine.h"
#include "SmartUrlCache.h"


#ifndef _MULTIWRITER_TEMP_INF_LIFETIME
#define _MULTIWRITER_TEMP_INF_LIFETIME (86400) // in seconds 
#endif


namespace  
{
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// Writer

	// ����� Writer : ������������� �������� ������ ������ � ����.
	// ���� ����� ���� ������ ���� ��� ������������ � URL � ���� IE.

	class MultiWriter 
	{
	protected:
		CString m_Path; 

		CString m_Base; 

		CString m_FileName;

		SharedPtr<::::UrlCacheEntry> m_pEntry; 

		bool m_DeleteEntryOnRelease; 

		::::File m_File;

		CString m_TargetPath; 

		int m_Position;

		bool m_Open; // ������ �������� ���� 

		string m_Id; 

	public:
		bool On; 

	protected:
		inline void Clear() 
		{
			m_Open = false;
			m_Position = 0; 
			//
			m_Base = _T("");
			m_FileName = _T("");
			m_Path = _T("");
			m_TargetPath = _T("");
			m_DeleteEntryOnRelease = false; 
		}

		inline void ReleaseEntry() 
		{
			if (! m_pEntry.IsEmpty()) 
			{
				if (m_DeleteEntryOnRelease) 
				{
					m_pEntry->Delete(); 
				}
				m_pEntry.Free(); 
			}
		}

		inline void Free() 
		{
			ReleaseEntry(); 
			//
			Clear(); 
		}

		inline bool InUrlCache() 
		{
			return ! m_pEntry.IsEmpty(); 
		}

	protected:
		inline void OpenPhysicalPath() 
		{
			try
			{
				if (m_pEntry)
				{
					m_pEntry->Unlock(); 
				}
				m_File.OpenToWrite(m_Path); 
				m_Position = 0; 
				m_File.Touch(); 
				//
#				ifdef _DEBUG
				{
					//TRACE_LINE(_T("   --> ") + m_Path)
				}
#				endif
			}
			_Catch()
		}

	public:
		// �������� ������ ���� ���� ������ ���� ������ ���������� �� ����������� ������ 

		inline void Open() 
		{
			try
			{
				if (! m_Open)
				{
#					ifdef _DEBUG
					//TRACE_LINE(_T("Writer : ��������� ") + m_Path);
#					endif
					//
					if (m_Path.GetLength() <= 2)
					{
						throw MethodError(E_INVALIDARG).AddIfNewSource_(L"�� ������ ���� ��� ������ �����"); 
					}
					//
					// ��������� 
					//
					if (! InUrlCache())
					{
						///Machine::SafeRemoveFile(m_Path); 
					}
					//
					OpenPhysicalPath(); 
					//
					m_Open = true; // ���� ������ 
				}
			}
			_Catch()
		}

		inline void SetOpen(bool fOpen)
		{
			try
			{
				if (fOpen) // open 
				{
					if (m_Path.GetLength() <= 2)
					{
						throw MethodError(E_INVALIDARG).AddIfNewSource_(L"�� ������ ���� ��� ������ �����"); 
					}
					//
					// ������ �� ������ (m_Path) ����� �������������� ������� ��������, ������ �������� m_Open 
					//
					m_Open = true; // ���� ������ 
				}
				else // close 
				{
					Close(); 
				}
			}
			_Catch() 
		}

	public:
		MultiWriter()
		{
			Clear(); 
		}

		// ��������� (�������) ������� ������ ������ � ������������� ��������� ��������� � ����������� ������� 

		inline void Dispose() 
		{
			try
			{
				Close(); 
				//
				// ����������� ������� 
				//
				Free(); 
			}
			_Catch()
		}

		virtual ~MultiWriter() 
		{
			Dispose(); 
		}

		// ������� ������ ������ ������ 

		inline void SetPath(const CString& targetPath,const CString& tempPath=_T(""))
		{
			try
			{
				Dispose();	// ���� ������ ��� ����� ������ ����, �������, ��� ������ ���������, 
							// � ��������� ���������� ����. 
				//
				CString path_1 = tempPath.GetLength() > 0 ? tempPath : targetPath; 
				//
				m_Path = path_1;	// � ����� ������� ������ ������ � ���� m_Path, ���� ����� ������ 
									// ��� ����������� ������ ������. 
				//
				m_TargetPath = targetPath; 
			}
			_Catch()
		}

		inline void SetBase(const CString& base) 
		{
			try
			{
				if (m_Open)
				{
					throw MethodError(E_INVALIDARG).AddIfNewSource_(L"��������� � �������� ������"); 
				}
				//
				if (m_Base.GetLength() > 0)
				{
					if (m_Base != base)
					{
						throw MethodError(E_INVALIDARG).AddIfNewSource_(L"����� ��� ������"); 
					}
				}
				//
				if (base.GetLength() <= 2)
				{
					m_Base = _T(""); 
				}
				else
				{
					m_Base = base;
				}
			}
			_Catch()
		}

#		ifdef _PROTOCOL_IMPL_URLCACHE_CLEANUP_F
		//
		inline void CleanupUrl(const string& url) 
		{
			try
			{
				//return; 
				UrlCacheEntry::CleanupUrl(url); 
			}
			_Catch()
		}
		//
#		endif 

		inline void SetFileName(const CString& fileName) 
		{
			try
			{
				try
				{
					if (m_pEntry)
					{
						m_pEntry->SetFileName(_W(fileName)); 
						//
						return;
					}
					//
					if (m_Base.GetLength() <= 0)
					{
						m_FileName = fileName; // ��� URL 
						//
						return;
					}
					//
					Dispose(); // ����� �� ������ m_FileName �� Dispose() 
					//
					m_FileName = fileName;
					SetPath(m_Base + _T("\\") + m_FileName); 
				}
				_Catch()
			}
			_AddMessage(L"������ ��� ������� ���������� ��� �����: " + _W(fileName)) 
		}

	public:
		
		// ������� ������ ������ ������ (���� � ���� IE) 

		inline void SetUrl(const string& url,const CString& targetPath=_T(""),
			const string& fileName=L"") 
		{
			try
			{
				try
				{
					if (! m_pEntry.IsEmpty()) 
					{
						throw MethodError(E_FAIL).AddIfNewSource_(L"URL ��� ������"); 
					}
					//
					if (fileName.GetLength() > 0)
					{
						this->SetFileName(_S(fileName)); 
					}
					//
					{
						///UrlCacheEntry::CleanupUrl(url); 
					}
					//
					m_pEntry = new UrlCacheEntry(url); 
					if (m_FileName.GetLength() > 0)
					{
						m_pEntry->SetFileName(_W(m_FileName)); 
					}
					//////m_pEntry->Delete(); 
					m_pEntry->Create(false); // true => Delete() 
					m_Path = m_pEntry->GetPath(); 
					//
					if (targetPath.GetLength() > 0)
					{
						m_TargetPath = targetPath; 
					}
					else
					{
						m_TargetPath = m_Path; 
					}
				}
				_Catch() 
			}
			_AddMessage(L"������ ��� ������� ���������� URL: " + _W(url) + (targetPath == _T("") ? L"" : _W(L" (") + _W(targetPath) + L")") ) 
		}

		inline string GetUrl() 
		{
			try
			{
				static const string emptyUrl = L""; 
				//
				if (m_pEntry.IsEmpty()) return emptyUrl; 
				//
				string url = m_pEntry->GetUrl(); 
				return url; 
			}
			_Catch()
		}



		inline CString GetTargetPath() 
		{
			try
			{
				if (m_TargetPath.GetLength() <= 3)
				{
					throw MethodError(L"�������� TargetPath �� ��������� ��� ���������: " + _W(m_TargetPath)); 
				}
				//
				return m_TargetPath; 
			}
			_Catch() 
		}



		inline UrlCacheEntry* GetEntry() 
		{
			UrlCacheEntry* p = NULL; 
			//
			if (m_pEntry)
			{
				p = m_pEntry.GetPointee(); 
			}
			//
			return p; 
		}



		inline string CreateTempFileInUrlCache() // --> URL 
		{
			try
			{
				Dispose(); 
				//
				// ����� ���� 
				//
				m_Id = NewGuidStr(); 
				//
				string url = _URL_CACHE_DEFAULT_URL_BEGIN + L"_temp_/" + m_Id + L".txt"; 
				//
				SetUrl(url); 
				//
				return url; 
			}
			_Catch()
		}



		inline void SetDeleteEntryOnRelease(bool fDel) 
		{
			m_DeleteEntryOnRelease = fDel; 
		}



		// ----
		// ������� 

		// ������ �� ������ ������? 

		inline bool Writing() 
		{
			try
			{
				return bool(m_Path.GetLength() > 0); 
			}
			_Catch() 
		}

		// ----
		// �������� 

		// ��������� (�������) ������� ������ ������ � ������������� ��������� ���������, 
		// ��������� ��������� �����. 

		inline CString Close() // ~ Commit() // ��� ����� �������� ������ � ��������, ��� entry: ������+commit 
		{
			try
			{
				CString currentPath = m_Path; 
				//
				try
				{
					if (m_Open)
					{
#						ifdef _DEBUG
						CString sStr = FormatStr(_T("%d"), (int)m_Position); 
						//TRACE_LINE(_T("Writer : ~~��������� (") + sStr + _T(") ") + m_Path);
#						endif
						m_File.Close(); 
						//
						// URL 
						//
						if (! m_pEntry.IsEmpty()) 
						{
							m_pEntry->Commit_SetLifePeriod(_MULTIWRITER_TEMP_INF_LIFETIME); 
						}
						//
						// ���������� 
						//
						if (m_Path != m_TargetPath) 
						{
							if (Machine::FileExists(m_TargetPath)) // ������� ���� m_TargetPath, ���� ���������� 
							{
								bool canDel = true; 
								//
								if (m_TargetPath.GetLength() <= 3) canDel = false;
								if (m_TargetPath.Right(1) == _T("\\")) canDel = false;
								if (m_TargetPath.Find(_T("*")) != -1) canDel = false;
								//
								if (canDel) 
								{
									if (! DeleteFile(m_TargetPath)) 
									{
										HRESULT rc = HRESULT_FROM_WIN32(GetLastError()); 
										throw MethodError(rc); 
									}
								}
							}
							//
							if (! MoveFile(m_Path,m_TargetPath)) 
							{
								HRESULT rc = HRESULT_FROM_WIN32(GetLastError()); 
								throw MethodError(rc); 
							}
						}
						//
						m_Open = false; // ���� ������ 
					}
				}
				catch(...)
				{
					Dispose();
					//
					throw;
				}
				//
				return currentPath; 
			}
			_Catch()
		}

		inline CString Move(const CString& dstPath) 
		{
			try
			{
				m_TargetPath = dstPath;
				//
				return Close(); 
			}
			_Catch()
		}

		static const int DataEncoding_Text = 1;
		static const int DataEncoding_Base64 = 2;
		static const int DataEncoding_BSTR = 3;

		inline void AddBinary(const char* p,UINT size)
		{
			try
			{
				if (size > 0)
				{
					m_File.Replace(p,size,m_Position); 
					//
					m_Position += size; 
				}
			}
			_Catch()
		}

		inline void AddData64(const string& text)
		{
			try
			{
				return AddText(text,DataEncoding_Base64);
			}
			_Catch()
		}

		inline void AddBSTR(BSTR text)
		{
			try
			{
				Open(); 
				//
				UINT size = SysStringLen(text) * sizeof(wchar_t);
				const char* p = (const char*)(const void*)text;
				//
				AddBinary(p,size); 
			}
			_Catch()
		}

		inline void AddText(const string& text,int de=DataEncoding_Text) 
		{
			try
			{
				Open(); 
				//
				int size = 0;
				const char* p = 0;
				//
				Blob b;
				//
				if (de == DataEncoding_Text)
				{
					size = text.GetLength()*sizeof(wchar_t);
					p = (const char*)(const void*)text.GetString();
				}
				else if (de == DataEncoding_Base64)
				{
					b = ::::FromBase64String(text);
					p = (const char*)b.GetBuffer();
					size = b.Length(); 
				}
				//
				AddBinary(p,size); 
			} 
			_Catch()
		}



		// �������� ������ �� ������ � ���� 

		void WriteStream(IStream* stream) 
		{
			try
			{
				if (! stream)	// ������ ���������� 
				{
					Open();		// ������ ������ ����
								// ��������� ����������� ���������� ������ 
					return; 
				}
				//
				// ----
				// ������ �� ������ 
				// 
				Open(); 
				//
				LARGE_INTEGER m0;
				m0.QuadPart = 0; 
				ULARGE_INTEGER libNewPos;
				HRESULT rc = stream->Seek(m0,FILE_BEGIN,&libNewPos); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				const int chunkSize = 4 * 1024; 
				const int pauseMs = 10; 
				//
				int pos = 0; 
				//
				HRESULT r1; 
				do
				{
					Blob b;
					b.Allocate(chunkSize); 
					ULONG bytesRead = 0; 
					r1 = stream->Read(b.GetBuffer(),(ULONG)chunkSize,&bytesRead); 
					if (r1 == E_PENDING) 
					{
						Sleep(pauseMs);
						r1 = S_OK; 
					}
					else if (r1 == S_FALSE) 
					{
						// ������ ��������� 
					}
					else if (FAILED(r1)) 
					{
						throw MethodError(r1); 
					}
					else // S_OK
					{
						if (bytesRead > 0) 
						{
							m_File.Replace((const char*)b.GetBuffer(),bytesRead,pos);  
							pos += bytesRead; 
							r1 = S_OK; // �� ������ ������ 
						}
						else
						{
							r1 = S_FALSE; 
						}
					}
				}
				while (r1 == S_OK); 
			}
			_Catch()
		}
	};

} // namespace  
