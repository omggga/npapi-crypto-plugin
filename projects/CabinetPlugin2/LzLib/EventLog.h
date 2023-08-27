#ifndef __LZ_EVENTLOG_H__
#define __LZ_EVENTLOG_H__

#pragma once

#include "argarray.h"

namespace Lz {

class EventLogException : public Lz::AutoArgArray<EventLogException>
{
protected:
	DWORD m_dwEventId;
	WORD m_wType;

public:
	EventLogException(DWORD dwEventId) : m_dwEventId(dwEventId)
	{
		switch( ((m_dwEventId) >> 30) )
		{
		case 0x0 : m_wType = EVENTLOG_SUCCESS; break;
		case 0x1 : m_wType = EVENTLOG_INFORMATION_TYPE; break;
		case 0x2 : m_wType = EVENTLOG_WARNING_TYPE; break;
		default: m_wType = EVENTLOG_ERROR_TYPE;
		}
	}

	DWORD GetEventId() const { return m_dwEventId; }
	WORD GetType() const { return m_wType; }
	WORD GetCategory() const { return 0; }
};

template<class _ClassEventData>
class EventLog : public _ClassEventData
{
protected:
	HANDLE m_hEventLog;

public:
	EventLog()
	{
		m_hEventLog = ::RegisterEventSource(NULL, _ClassEventData::GetSourceName());
		if( m_hEventLog == (HANDLE)ERROR_INVALID_HANDLE )
			m_hEventLog = 0;
	}

	~EventLog()
	{
		if( m_hEventLog ) ::DeregisterEventSource(m_hEventLog);
	}

	BOOL ReportEvent(EventLogException& EvtExcept)
	{
		ArgArrayVector av(EvtExcept.GetArgArray());

		return ::ReportEvent(m_hEventLog,
				EvtExcept.GetType(),
				EvtExcept.GetCategory(), 
				EvtExcept.GetEventId(), 
				NULL, 
				(WORD)av.GetCount(),
				0, 
				av,
				NULL);
	}

	static HRESULT AddEventSource()
	{
		HRESULT hr;
		HKEY hk; 
		DWORD dwData, dwDisp; 
		TCHAR szBuf[MAX_PATH];

		LPCTSTR pszLogName = _ClassEventData::GetLogName();
		LPCTSTR pszSrcName = _ClassEventData::GetSourceName();
		LPCTSTR pszMsgDLL = _ClassEventData::GetMsgDll();
		DWORD  dwNum = _ClassEventData::GetCategoriesCount();

		::StringCbPrintf(szBuf, sizeof(szBuf)-sizeof(TCHAR), _T("SYSTEM\\CurrentControlSet\\Services\\EventLog\\%s\\%s"), pszLogName, pszSrcName);

		hr = RegCreateKeyEx(HKEY_LOCAL_MACHINE, szBuf, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hk, &dwDisp);
		if( hr ) return hr;

		size_t cbMsgDLLSize;
		::StringCbLength(pszMsgDLL,STRSAFE_MAX_CCH,&cbMsgDLLSize);
		hr = RegSetValueEx(hk, _T("EventMessageFile"), 0, REG_EXPAND_SZ, (LPBYTE)pszMsgDLL, (DWORD)(cbMsgDLLSize+sizeof(TCHAR)));
		if( hr ) return hr;

		dwData = EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE | EVENTLOG_INFORMATION_TYPE;

		hr = RegSetValueEx(hk, _T("TypesSupported"), 0, REG_DWORD, (LPBYTE)&dwData, sizeof(DWORD));   
		if( hr ) return hr;

		hr = RegSetValueEx(hk, _T("CategoryMessageFile"), 0, REG_EXPAND_SZ, (LPBYTE)pszMsgDLL, (DWORD)(cbMsgDLLSize+sizeof(TCHAR)));
		if( hr ) return hr;

		hr = RegSetValueEx(hk, _T("CategoryCount"), 0, REG_DWORD, (LPBYTE)&dwNum, sizeof(DWORD));    
		if( hr ) return hr;

		RegCloseKey(hk);
		
		ATLTRACE(_T("EventLog::AddEventSource() hr=S_OK\n"));

		return S_OK;
	}

};

}; // namespace Lz

#endif // __LZ_EVENTLOG_H__
