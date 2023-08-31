/*
 SmartUrlCache.h : ������ ��� ������ � ������������ ������� Internet. 

 $Name: work1 $
 $Revision: 1.1.2.5 $
 $Date: 2009/05/18 13:17:11 $

 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


#include "SmartInetBase.h"


#ifndef _URL_CACHE_INFO_SIZE
#define _URL_CACHE_INFO_SIZE (2*1024) 
#endif

#ifndef _URL_CACHE_DEFAULT_URL_BEGIN
#define _URL_CACHE_DEFAULT_URL_BEGIN (L"http://cache..ru/")
#endif


namespace 
{

	// =======================================================================================
	// ��������� ����� 

	class UrlCacheEntry
	{
	protected:
		string m_Url;			// URL 

		bool m_DeleteOnClose; 

		string m_Extension;

		string m_FileName;

		bool m_Exists;			// � ���� ���� ���������� ����� 

		CString m_Path;			// %UserProfile%\Local Settings\Temporary Internet Files\...

	protected:
		// ----
		// ��������� ������� ������� 

		inline string UrlEcho() 
		{
			string echo = L"URL: " + (m_Url.GetLength() > 0 ? m_Url : L"(���)"); 
			return echo; 
		}

		inline string ObjectEcho() 
		{
			return UrlEcho(); 
		}

		inline void SetEmpty() 
		{
			m_Exists = false; 
			m_Path = _T(""); 
		}

		inline void SetPath(const CString& path) 
		{
			if (path.GetLength() <= 3) 
			{
				SetEmpty(); 
				throw MethodError(L"�������� ����: " + _W(path)); 
			}
			//
			m_Path = path; 
			m_Exists = true; 
		}

		void Lookup()
		{
			try
			{
				try
				{
					DWORD cacheEntrySize = _URL_CACHE_INFO_SIZE;
					Blob cacheEntryBuf;
					cacheEntryBuf.Allocate(cacheEntrySize);
					if (! GetUrlCacheEntryInfo(_S(m_Url), 
						(INTERNET_CACHE_ENTRY_INFO*)cacheEntryBuf.GetBuffer(),&cacheEntrySize)) 
					{
						DWORD dwErr = GetLastError();
						if (dwErr != ERROR_FILE_NOT_FOUND)
						{
							throw MethodError(INTERNET_ERROR(dwErr)); 
						}
						else
						{
							SetEmpty(); 
							return;
						}
					}
					INTERNET_CACHE_ENTRY_INFO* cacheEntry = 
						(INTERNET_CACHE_ENTRY_INFO*)cacheEntryBuf.GetBuffer(); 
					//
					m_Path = cacheEntry->lpszLocalFileName; 
					m_Exists = true;
				}
				_Catch()
			}
			_AddMessage(ObjectEcho()) 
		}

	public:
		// ----
		// ��������� 

		inline bool Exists()
		{
			return m_Exists; 
		}

		inline CString GetPath()
		{
			try
			{
				try
				{
					if (! m_Exists) 
					{
						throw MethodError(string(L"��������� ����� � ���� IE �����������"))
							.AddIfNewSource_(L"\n" + _W(m_Url)); 
					}
					//
#					ifdef _DEBUG
					{
						TRACE_LINE1(_T("UrlCacheEntry:  Url: %s"), _S(m_Url).GetString() ); 
						TRACE_LINE1(_T("UrlCacheEntry: Path: %s"), _S(m_Path).GetString() ); 
					}
#					endif
					//
					return m_Path;
				}
				_Catch()
			}
			_AddMessage(ObjectEcho()) 
		}

		inline string GetUrl() 
		{
			return m_Url; 
		}

		inline void SetDeleteOnClose(bool f=true) 
		{
			m_DeleteOnClose = f; 
		}

		inline bool GetDeleteOnClose() 
		{
			return m_DeleteOnClose; 
		}

		inline void Unlock()
		{
			try
			{
				if (m_Exists)
				{
					if (! UnlockUrlCacheEntryFile(_S(m_Url),0)) 
					{
						DWORD dwErr = GetLastError(); 
						if (dwErr != 2)
						{
							throw MethodError(INTERNET_ERROR(dwErr)); 
						}
					}
				}
			}
			_Catch()
		}



		// ----
		// �������� / ����������� � Entry

		inline void SetFileName(const string& fileName) 
		{
			try
			{
				try
				{
					m_FileName = fileName; 
					//
					int p1 = m_FileName.ReverseFind(L'.'); 
					if (p1 != 0) m_Extension = m_FileName.Right(m_FileName.GetLength()-p1-1); 
					//
					{
						//p1 = m_url.ReverseFind(_T('/'));
						//if (p1 != -1)
						//{
						//	m_url = m_url.Left(p1+1) + m_fileName;
						//}
						//
						//Lookup();
					}
				}
				_Catch()
			}
			_AddMessage2(L"������ ��� ��������� �����: " + fileName, ObjectEcho())
		}

	protected:
		inline void CreateNew() 
		{
			try
			{
				//if (! ::DeleteUrlCacheEntry(_S(m_Url))) 
				//{
				//	///throw LastInternetError(); 
				//}
				//
				DWORD cacheEntrySize = _URL_CACHE_INFO_SIZE;
				Blob cacheEntry;
				cacheEntry.Allocate(cacheEntrySize);
				TCHAR localPathBuf[MAX_PATH + 1];
				localPathBuf[0] = 0;
				if (! ::CreateUrlCacheEntry(_S(m_Url),0,_S(m_Extension),localPathBuf,0)) 
				{
					throw LastInternetError(); 
				}
				SetPath(localPathBuf); 
			}
			_Catch() 
		}

	public:
		inline void Create(bool deleteOnCreate)
		{
			try
			{
				/// if (m_Exists) return; // ��� ���������� 
				//
				if (deleteOnCreate)
				{
					Delete(); 
				}
				//
				CreateNew(); 
			}
			_Catch()
		}

		inline static void OleDateTimeToFileTime(const COleDateTime& oTime,FILETIME& Ft
			,bool convertLocal) 
		{
			try
			{
				SYSTEMTIME St;
				oTime.GetAsSystemTime(St);
				//
				if (convertLocal)
				{
					FILETIME Ft_1;
					SystemTimeToFileTime(&St,&Ft_1);
					//
					LocalFileTimeToFileTime(&Ft_1,&Ft);
				}
				else
				{
					SystemTimeToFileTime(&St,&Ft);
				}
			}
			_Catch() 
		}

		void Commit(
			FILETIME& expireFt,
			FILETIME& lastModifiedFt,
			DWORD entryType
			) 
		{
			try
			{
				FILETIME ft_expire; 
				ZeroMemory(&ft_expire,sizeof(ft_expire)); 
				//
				SYSTEMTIME st0;
				GetSystemTime(&st0);
				FILETIME ft0; 
				SystemTimeToFileTime(&st0,&ft0);
				if (! ::CommitUrlCacheEntry(
					_S(m_Url),
					m_Path,
					expireFt, //ft_expire,	// Expire 
					lastModifiedFt, //ft_expire,		// LastModified 
					entryType,
					0,//(LPBYTE)"HTTP/1.0 200 OK\r\n\r\n",
					0,//20,
					_S(m_Extension),
					_S(m_Url))) 
				{
					HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
					throw MethodError(rc);
				}
			}
			_Catch()
		}

		void Commit(
			const COleDateTime& expireTime,
			const COleDateTime& lastModifiedTime,
			DWORD flags
			) 
		{
			try
			{
				FILETIME expireFt;
				OleDateTimeToFileTime(expireTime,expireFt,false); 
				//
				FILETIME lastModifiedFt;
				OleDateTimeToFileTime(lastModifiedTime,lastModifiedFt,false); 
				//
				COleDateTime __t_exp(expireFt);
				string __t_exp_s = FormatStr(
					L"%02d%02d%02dZ" // ("yyMMddHHmmssZ") 
					,__t_exp.GetHour()
					,__t_exp.GetMinute()
					,__t_exp.GetSecond()
					);				
				//
				COleDateTime __t_m(lastModifiedFt);
				string __t_m_s = FormatStr(
					L"%02d%02d%02dZ" // ("yyMMddHHmmssZ") 
					,__t_m.GetHour()
					,__t_m.GetMinute()
					,__t_m.GetSecond()
					);				
				//
				Commit(expireFt,lastModifiedFt,flags); 
			}
			_Catch()
		}

		void Commit_SetLifePeriod(int lifePeriodInSeconds,
			const COleDateTime& t=COleDateTime::GetCurrentTime()) 
		{
			try
			{
				////COleDateTimeSpan span(0,0,0,lifePeriodInSeconds); 
				COleDateTimeSpan span(0,1,0,0); 
				//
				COleDateTime t2 = t + span; 
				//
				CString t2_s = FormatTime_ymd_HMD(_S("%04d-%02d-%02d"),_S("%02d:%02d:%02d"),t2); 
				//TRACE_LINE(t2_s);
				CString t_s = FormatTime_ymd_HMD(_S("%04d-%02d-%02d"),_S("%02d:%02d:%02d"),t); 
				//TRACE_LINE(t_s);
				//
				Commit(t2,t,
					NORMAL_CACHE_ENTRY 
					// | STICKY_CACHE_ENTRY
					); 
			}
			_Catch() 
		}

		////void SetExpiration(int exemptionDelta,const COleDateTime& expirationTime,
		////	const COleDateTime& curTime=COleDateTime::GetCurrentTime())
		////{
		////	try
		////	{
		////		INTERNET_CACHE_ENTRY_INFO info;
		////		info.dwStructSize = sizeof(INTERNET_CACHE_ENTRY_INFO);
		////		info.dwExemptDelta = exemptionDelta;
		////		//
		////		SYSTEMTIME expSt;
		////		expirationTime.GetAsSystemTime(expSt);
		////		SystemTimeToFileTime(&expSt,&info.ExpireTime);
		////		//
		////		SYSTEMTIME curSt;
		////		curTime.GetAsSystemTime(curSt);
		////		SystemTimeToFileTime(&curSt,&info.LastSyncTime);
		////		//
		////		// if (! ::SetUrlCacheEntryInfo(m_url,&info,CACHE_ENTRY_EXEMPT_DELTA_FC);
		////		// ............................................................................. 
		////	}
		////	_Catch()
		////}



		// ----
		// �������� Entry 

		void Delete()
		{
			try
			{
				try
				{
					if (! DeleteUrlCacheEntry(_S(m_Url)))
					{
						DWORD dwErr = GetLastError(); 
						if (dwErr != 2)
						{
							throw MethodError(INTERNET_ERROR(dwErr)); 
						}
					}
					//
					SetEmpty(); 
				}
				_Catch()
			}
			_AddMessage(ObjectEcho())
		}

//#		ifdef _PROTOCOL_IMPL_URLCACHE_CLEANUP_F
		//
		inline static void CleanupUrl(const string& url)
		{
			try
			{
				try
				{
					if (! DeleteUrlCacheEntry(_S(url))) 
					{
						throw LastInternetError();
					}
				}
				_Catch()
			}
			_AddMessage(L"�� ������� ������� CacheEntry: " + _W(url)) 
		}
		//
//#		endif



		// ----
		// ������������ 
	protected: 
		inline void Clear() 
		{
			m_Exists = false;
			m_DeleteOnClose = false; 
		}

		inline void Free() 
		{
			if (m_DeleteOnClose && m_Exists) 
			{
				Delete(); 
			}
			//
			// ������������ �������� 
			//
			// (���) 
			//
			Clear(); 
		}

		inline void Dispose() 
		{
			Free(); 
		}

	public:
		UrlCacheEntry(const string& url) : m_Url(url)
		{
			try
			{
				Clear();
				Lookup();
			}
			_Catch()
		}

		UrlCacheEntry(const string& url,const string& ext) : m_Url(url), m_Extension(ext)
		{
			try
			{
				Clear(); 
				Lookup();
			}
			_Catch()
		}
	};

} // namespace  
