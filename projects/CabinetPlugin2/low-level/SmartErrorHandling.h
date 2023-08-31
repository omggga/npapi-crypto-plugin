/*
 ErrorHandling.h : ������� � ������������� �������� ��������� ������.

 $Name: work1 $
 $Revision: 1.1.2.1 $
 $Date: 2008/10/10 15:12:24 $

 ��������!   ������ �� ���������� #pragma once
             
 �������: ������������ ��� ������� ��������� ������:
		  1) Normal
		  2) Simple (���������� ����� ��� ������������� �������� � �.�. ��������)
 */

// �� ���������� #pragma once



#ifndef ErrorHandling_0
#define ErrorHandling_0

// 
//
#include <comdef.h>
//
#include "..\LzLib/ErrorMessage.h"
#include "..\LzLib/EventLog.h"
//
#include "AtlX.h"
#include "SmartEngineering.h"
#include "TracePoint.h"
//
///#include <sys-msg/SlotMsg.h>

#endif // ErrorHandling_0



// -----------------------------------------------------------------------------------------------
#ifndef ErrorHandling_1
#define ErrorHandling_1

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� EventSource

// ������ � ���������� �� ��������� ����� ��������� (������) � �������������� ����������� �������

namespace  {

class EventSource
{
public:
	// ������������� ��� ������ ��������� 
	virtual HRESULT GetErrorCode() =0;
	// ������������� ��� �������������� ���������
	virtual HRESULT GetWarningCode() =0;
	// ������������ ��������� ��� EventLog
	virtual CString GetSourceName() =0;
	// ������������ Facility ��� EventLog
	virtual CString GetFacilityName() =0;

	inline static CString CommonLogName()
	{
		static CString s_LogName;
		//
		if (s_LogName.GetLength() == 0)
		{
			HKEY hKey = 0;
			//
			HRESULT rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
				_T("SYSTEM\\CurrentControlSet\\Services\\EventLog\\") + _S(_EVT_LOG_NAME), 
				0,KEY_QUERY_VALUE,&hKey);
			if (rc == S_OK)
			{
				s_LogName = _EVT_LOG_NAME;
			}
			else
			{
				s_LogName = _T("Application"); 
			}
		}
		//
		return s_LogName; 
	}
};

template<class T>
class DefaultEventSource : public EventSource
{
public:
	// ����������� �� ���������
	DefaultEventSource()
	{
	}
	// ������������� ��� ������ ��������� 
	HRESULT GetErrorCode()
	{
		return T::GetErrorCode();
	}
	// ������������� ��� �������������� ���������
	HRESULT GetWarningCode()
	{
		return T::GetWarningCode();
	}
	// ������������ ��������� ��� EventLog
	CString GetSourceName()
	{
		return T::GetEventSourceName();
	}
	// ������������ Facility ��� EventLog
	CString GetFacilityName()
	{
		return T::GetFacilityName();
	}
};

template<class T,bool bEnable=false>
class EventSourceAdapterImpl
{
public:
	EventSourceAdapterImpl(T* )
	{
	}
	operator EventSource*()
	{
		return 0;
	}
};

template<class T>
class EventSourceAdapterImpl<T,true>
{
	EventSource* m_E;
	//
public:
	EventSourceAdapterImpl(T* obj)
	{
		m_E = static_cast<EventSource*>(obj);
	}
	operator EventSource*()
	{
		return m_E;
	}
};

template<class T>
class EventSourceAdapter
{
	EventSource* m_E;
	//
public:
	EventSourceAdapter(T* obj)
	{
		EventSourceAdapterImpl<T,is_base_of<EventSource,T>::value> a(obj);
		m_E = (EventSource*)a;
	}
	operator EventSource*()
	{
		return m_E;
	}
};

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ���������� ��������� ���������

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� EventSourceProvider

template<class T>
class EventSourceProvider // : public RootEventSource
{
protected:
	// ===========================================================================================
	// �������������
	// ----------------------

	// ��������� ���������� �� ��������� ���������

	static void Init()
	{
		static bool isInited = false;
		//
		if (isInited) return;
		//
		LogName() = EventSource::CommonLogName(); // ����� ��������!
		FacilityName() = T::GetFacilityName();
		SourceName() = T::GetEventSourceName();
		ErrorCode() = T::GetErrorCode();
		WarningCode() = T::GetWarningCode();
		//
		// %systemroot%\\system32
		MsgDll() = _T(""); 
		MsgDll() += FacilityName();
		MsgDll() += _T("Msg.dll");
		//
#		ifdef _DEBUG
		TRACE_LOG(_T("�������� ��������� ��� ") + _S(LogName())+_T(":")+_S(FacilityName())+_T(":")+_S(SourceName()) + _T(" - ") + MsgDll());
#		endif
		//
		isInited = true;
		//
//		try
//		{
//			::Container<Lz::EventLog<EventSourceProvider> >().AddEventSource();
//		}
//		catch(...)
//		{
//#			ifdef _DEBUG
//			TRACE_LOG(_T("�� ������� ���������������� Event Source"));
//#			endif
//		}
	}

public:
	// ===========================================================================================
	// ���������� 
	// ----------------------

	// ������������� ��� ������ ��������� (���������)
	static HRESULT& ErrorCode()
	{
		static HRESULT s_ErrorCode;
		return s_ErrorCode;
	}

	// ������������� ��� �������������� ��������� (���������)
	static HRESULT& WarningCode()
	{
		static HRESULT s_WarningCode;
		return s_WarningCode;
	}

	// ������������ ��������� ��� EventLog (���������)
	static CString& SourceName()
	{
		static CString s_SourceName;
		return s_SourceName;
	}

	// ������������ Facility ��� EventLog (���������)
	static CString& FacilityName()
	{
		static CString s_FacilityName;
		return s_FacilityName;
	}

	// ������������ ������� EventLog (���������)
	static CString& LogName()
	{
		static CString s_LogName;
		return s_LogName;
	}

	// ��� ����� DLL, ����������� �������� ��������� ��� EventLog (���������)
	static CString& MsgDll()
	{
		static CString s_MsgDll;
		return s_MsgDll;
	}

	// ===========================================================================================
	// ���������� � ��������� ��������� ������ � ������������ ��������� Eventlog 
	// ----------------------

	// ������������� ��� ������ ���������
	static HRESULT GetErrorCode()
	{
		Init();
		return ErrorCode();
	}

	// ������������� ��� �������������� ���������
	static HRESULT GetWarningCode()
	{
		Init();
		return WarningCode();
	}

	// ������������ ��������� ��� EventLog
	static CString GetSourceName()
	{
		Init();
		return SourceName();
	}

	// ������������ Facility ��� EventLog
	static CString GetFacilityName()
	{
		Init();
		return FacilityName();
	}

	// ������������ ������� EventLog
	static CString GetLogName()
	{
		Init();
		return LogName();
	}

	// ����� ��������� ��� EventLog
	static DWORD GetCategoriesCount()
	{
		Init();
		return 0;
	}

	// ��� ����� DLL, ����������� �������� ��������� ��� EventLog
	static CString GetMsgDll()
	{
		Init();
		return MsgDll();
	}
};



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ������ EventLog

// ������� ����������� ��������� � EventLog (���������)
inline static int& EventLogLevel()
{
	static int level = 1;
	//
	return level; // (������)
}



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ��������� �� ������� ��������� � EventLog

// ����� ���������� �� ������� ��������� � EventLog
inline static CString& LastErrorMessage() 
{
	static CString message(_T(""));
	//
	return message; // (������)
}



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Severity

enum Severity
{
	Severity_None = 0,
	Severity_Info,
	Severity_Warning,
	Severity_Error
};

} // namespace  

#endif // ErrorHandling_1
// -----------------------------------------------------------------------------------------------



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ��������� ������ ErrorHandling � SimpleErrorHandling

namespace  { 

#ifdef SIMPLE_ERROR_HANDLING
#	ifndef SimpleErrorHandling_class
#	define SimpleErrorHandling_class
#		ifdef _DEBUG
#		pragma message("Including: " __FILE__ " (Simple)")
#		endif
#	define _Include_ErrorHandling_class
#	endif
#else
#	ifndef ErrorHandling_class
#	define ErrorHandling_class
#		ifdef _DEBUG
#		pragma message("Including: " __FILE__ " (Normal)")
#		endif
#	define _Include_ErrorHandling_class
#	endif
#endif

#ifdef _Include_ErrorHandling_class

template<class T>
// template<template<template<class> class> class T>
#ifdef SIMPLE_ERROR_HANDLING
class SimpleErrorHandling
#else
class ErrorHandling
#endif
{
public:
	typedef EventSourceProvider<T> ED;

	typedef DefaultEventSource<T> DEvS;

	static EventSource* dEvS()
	{
		return new DEvS();
	}

	// ===========================================================================================
	// ��������� ������
	// ----------------------

	/*
				==��������� ���������==					==��������� ���������==

		O..		DisplayText								DisplaySysMsg (DisplayError)
		OE.		TextAlarm								SystemAlarm (HandleErrorWithEvent)
		.E.		LogText									LogSysMsg
		O.M		---										DisplayExplained
		.EM		---										LogExplained
		OEM		---										AlarmExplained (HandleErrorExplained)
		
	 */

	// ===========================================================================================
	// ��������� ���������
	// ----------------------

	/* ��������� ��������� ��������� � Debug Output [-TO-]   */

	static HRESULT DisplayText(CString msg,TRACE_POINT_ARGS) // always inline
	{
#		ifdef _DEBUG
		TRACE_LOG_(msg,TRACE_POINT_SEQ);
#		else
		TRACE_POINT_NOT_USED();
#		endif
		//
		LastErrorMessage() = msg;
		//
		return T::GetErrorCode();
	}
#	ifndef DisplayText_
#	ifdef _DEBUG
#	define DisplayText_(msg) DisplayText(msg,TRACE_POINT)
#	else
#		ifdef USE_ERROR_TEXT
#		define DisplayText_(msg) DisplayText(msg,TRACE_POINT)
#		else
#		define DisplayText_(msg) E_FAIL
#		endif
#	endif
#	endif

	/* ��������� ��������� ��������� � Debug Output � ���������� �������� [rTO-]   */

	template<class _RetVal>
	static _RetVal DisplayText(const CString& msg,_RetVal returnValue,TRACE_POINT_ARGS)
	{
#		ifdef _DEBUG
		DisplayText(msg,TRACE_POINT_SEQ);
#		endif
		//
		LastErrorMessage() = msg;
		//
		return returnValue;
	}
#	ifndef DisplayText_rv_
#	ifdef _DEBUG
#	define DisplayText_rv_(msg,value) DisplayText(msg,value,TRACE_POINT)
#	define DisplayText_return_FALSE_(msg) DisplayText(msg,FALSE,TRACE_POINT)
#	define DisplayText_return_TRUE_(msg) DisplayText(msg,TRUE,TRACE_POINT)
#	else
#		ifdef USE_ERROR_TEXT
#		define DisplayText_rv_(msg,value) DisplayText(msg,value,TRACE_POINT)
#		define DisplayText_return_FALSE_(msg) DisplayText(msg,FALSE,TRACE_POINT)
#		define DisplayText_return_TRUE_(msg) DisplayText(msg,TRUE,TRACE_POINT)
#		else
#		define DisplayText_rv_(msg,value) value
#		define DisplayText_return_FALSE_(msg) FALSE
#		define DisplayText_return_TRUE_(msg) TRUE
#		endif
#	endif
#	endif



	/* ���������� ��������� ��������� � Debug Output � Event Log [-TOE%]   */

	static HRESULT TextAlarm(const CString& msg,Severity S,EventSource* E,TRACE_POINT_ARGS)
	{
#		ifdef _DEBUG
		CString echo = msg;
		TRACE_LOG_(msg,TRACE_POINT_SEQ);
#		endif
		//
		CString text; 
		TRACE_TEXT_(msg,TRACE_POINT_SEQ,text); text = CString(_T("\n")) + text;
		//
		LastErrorMessage() = msg;
		//
		if (! E) E = dEvS();
		HRESULT envHR;
		if (S == Severity_Error) envHR = E->GetErrorCode();
		else envHR = E->GetWarningCode();
		delete E;
		//
		Container<Lz::EventLog<ED> >().ReportEvent(
			Lz::EventLogException(envHR) % text.GetString()
			);
		//
		return envHR;
	}
#	ifndef TextAlarm_
#	define TextAlarm_(msg) TextAlarm(msg,Severity_Error,0,TRACE_POINT)
#	define TextWarningAlarm_(msg) TextAlarm(msg,Severity_Warning,0,TRACE_POINT)
#	endif

	/* ���������� ��������� ��������� � Debug Output, Event Log � ���������� �������� [rTOE%]   */

	template<class _RetVal>
	static _RetVal TextAlarm(const CString& msg,Severity S,EventSource* E,_RetVal returnValue,
		TRACE_POINT_ARGS)
	{
#		ifdef _DEBUG
		CString echo = msg;
		TRACE_LOG_(msg,TRACE_POINT_SEQ);
#		endif
		//
		CString text; 
		TRACE_TEXT_(msg,TRACE_POINT_SEQ,text); text = CString("\n") + text;
		//
		LastErrorMessage() = msg;
		//
		if (! E) E = dEvS();
		HRESULT envHR;
		if (S == Severity_Error) envHR = E->GetErrorCode();
		else envHR = E->GetWarningCode();
		delete E;
		//
		Container<Lz::EventLog<ED> >().ReportEvent(
			Lz::EventLogException(envHR) % text.GetString()
			);
		//
		return returnValue;
	}
#	ifndef TextAlarm_rv_
#	define TextAlarm_rv_(msg,value) TextAlarm(msg,Severity_Error,0,value,TRACE_POINT)
#	define TextAlarm_return_FALSE_(msg) TextAlarm(msg,Severity_Error,0,FALSE,TRACE_POINT)
#	define TextAlarm_return_TRUE_(msg) TextAlarm(msg,Severity_Error,0,TRUE,TRACE_POINT)
	//
#	define TextWarningAlarm_rv_(msg,value) TextAlarm(msg,Severity_Warning,0,value,TRACE_POINT)
#	define TextWarningAlarm_return_FALSE_(msg) TextAlarm(msg,Severity_Warning,0,FALSE,TRACE_POINT)
#	define TextWarningAlarm_return_TRUE_(msg) TextAlarm(msg,Severity_Warning,0,TRUE,TRACE_POINT)
#	endif



	/* ���������� ��������� ��������� � Event Log [-T-E%]   */

	static HRESULT LogText(const CString& msg,Severity S,EventSource* E,TRACE_POINT_ARGS)
	{
		LastErrorMessage() = msg;
		//
		if (! E) E = dEvS();
		HRESULT envHR;
		if (S == Severity_Error) envHR = E->GetErrorCode();
		else envHR = E->GetWarningCode();
		//
		Container<Lz::EventLog<ED> >().ReportEvent(
			Lz::EventLogException(envHR) % msg.GetString()
			);
		//
		return envHR;
	}
#	ifndef LogTextError_
#	define LogTextError_(msg) LogText(msg,Severity_Error,0,TRACE_POINT)
#	define LogTextWarning_(msg) LogText(msg,Severity_Warning,0,TRACE_POINT)
#	endif

	/* ���������� ��������� ��������� � Event Log � ���������� �������� [rT-E%]   */

	template<class _RetVal>
	static _RetVal LogText(const CString& msg,Severity S,EventSource* E,_RetVal returnValue,
		TRACE_POINT_ARGS)
	{
		LastErrorMessage() = msg;
		//
		if (! E) E = dEvS();
		HRESULT envHR;
		if (S == Severity_Error) envHR = E->GetErrorCode();
		else envHR = E->GetWarningCode();
		//
		Container<Lz::EventLog<ED> >().ReportEvent(
			Lz::EventLogException(envHR) % msg.GetString()
			);
		//
		return returnValue;
	}
#	ifndef LogTextError_rv_
#	define LogTextError_rv_(msg,value) TextAlarm(msg,Severity_Error,0,value,TRACE_POINT)
#	define LogTextError_return_FALSE_(msg) TextAlarm(msg,Severity_Error,0,FALSE,TRACE_POINT)
#	define LogTextError_return_TRUE_(msg) TextAlarm(msg,Severity_Error,0,TRUE,TRACE_POINT)
	//
#	define LogTextWarning_rv_(msg,value) TextAlarm(msg,Severity_Warning,0,value,TRACE_POINT)
#	define LogTextWarning_return_FALSE_(msg) TextAlarm(msg,Severity_Warning,0,FALSE,TRACE_POINT)
#	define LogTextWarning_return_TRUE_(msg) TextAlarm(msg,Severity_Warning,0,TRUE,TRACE_POINT)
#	endif



	// ==============================================================================================
	// ��������� ���������
	// ----------------------

	/* ��������� ��������� ���������, �������� HRESULT, � Debug Output [-SO-]   */

	static HRESULT DisplaySysMsg(HRESULT rc,TRACE_POINT_ARGS)
	{
#		ifdef _DEBUG
		Lz::ErrorMessage<> m(rc);
		CString echo((LPCTSTR)m);
		echo = CleanUp(echo);
		TRACE_LOG_(echo,TRACE_POINT_SEQ);
		LastErrorMessage() = echo;
#		else
		TRACE_POINT_NOT_USED();
		CString echo;
		echo = FormatStr(_T("HRESULT(%x)"), (int)rc );
		LastErrorMessage() = echo;
#		endif
		//
		return rc;
	}
#	ifndef DisplaySysMsg_
#	ifdef _DEBUG
#	define DisplaySysMsg_(rc) DisplaySysMsg(rc,TRACE_POINT)
#	else
#		ifdef USE_ERROR_TEXT
#		define DisplaySysMsg_(rc) DisplaySysMsg(rc,TRACE_POINT)
#		else
#		define DisplaySysMsg_(rc) rc
#		endif
#	endif
#	endif

	/* �������� ��������� ��������� � Debug Output � ���������� ����������� �������� [rSO-]   */

	template<class _RetVal>
	static _RetVal DisplaySysMsg(HRESULT rc,_RetVal returnValue,TRACE_POINT_ARGS)
	{
#		ifdef _DEBUG
		DisplaySysMsg(rc,TRACE_POINT_SEQ);
#		else
		PARAMETER_NOT_USED(rc);
		TRACE_POINT_NOT_USED();
#		endif
		//
		return returnValue;
	}
#	ifndef DisplaySysMsg_rv_
#	ifdef _DEBUG
#	define DisplaySysMsg_rv_(rc,value) DisplaySysMsg(rc,value,TRACE_POINT)
#	define DisplaySysMsg_return_FALSE_(rc,value) DisplaySysMsg(rc,FALSE,TRACE_POINT)
#	define DisplaySysMsg_return_TRUE_(rc,value) DisplaySysMsg(rc,TRUE,TRACE_POINT)
#	else
#		ifdef USE_ERROR_TEXT
#		define DisplaySysMsg_rv_(rc,value) DisplaySysMsg(rc,value,TRACE_POINT)
#		define DisplaySysMsg_return_FALSE_(rc,value) DisplaySysMsg(rc,FALSE,TRACE_POINT)
#		define DisplaySysMsg_return_TRUE_(rc,value) DisplaySysMsg(rc,TRUE,TRACE_POINT)
#		else
#		define DisplaySysMsg_rv_(rc,value) DisplaySysMsg(rc,value,TRACE_POINT)
#		define DisplaySysMsg_return_FALSE_(rc,value) DisplaySysMsg(rc,FALSE,TRACE_POINT)
#		define DisplaySysMsg_return_TRUE_(rc,value) DisplaySysMsg(rc,TRUE,TRACE_POINT)
#		endif
#	endif
#	endif



	/* ���������� ����� � ��������� ������ (HRESULT) � Debug Output � Event Log [-SOE] */

	static HRESULT SystemAlarm(HRESULT rc,TRACE_POINT_ARGS)
	{
#		ifdef _DEBUG
		Lz::ErrorMessage<> m(rc);
		CString echo((LPCTSTR)m);
		echo = CleanUp(echo);
		TRACE_LOG_(echo,TRACE_POINT_SEQ);
		LastErrorMessage() = echo;
#		else
		TRACE_POINT_NOT_USED();
		CString echo;
		echo = FormatStr(_T("HRESULT(%x)"), (int)rc );
		LastErrorMessage() = echo;
#		endif
		//
		Lz::EventLogException e(rc);
		Container<Lz::EventLog<ED> >().ReportEvent(e);
		//
		return rc;
	}
#	ifndef SystemAlarm_
#	define SystemAlarm_(rc) SystemAlarm(rc,TRACE_POINT)
#	endif

	/* ���������� ����� � ��������� ������ (HRESULT) � Debug Output � Event Log � ���������� �������� [rSOE] */

	template<class _RetVal>
	static _RetVal SystemAlarm(HRESULT rc,_RetVal returnValue,TRACE_POINT_ARGS)
	{
#		ifdef _DEBUG
		Lz::ErrorMessage<> m(rc);
		CString echo((LPCTSTR)m);
		echo = CleanUp(echo);
		TRACE_LOG_(echo,TRACE_POINT_SEQ);
		LastErrorMessage() = echo;
#		else
		TRACE_POINT_NOT_USED();
		CString echo;
		echo = FormatStr(_T("HRESULT(%x)"), (int)rc );
		LastErrorMessage() = echo;
#		endif
		//
		Lz::EventLogException e(rc);
		Container<Lz::EventLog<ED> >().ReportEvent(e);
		//
		return returnValue;
	}
#	ifndef SystemAlarm_rv_
#	ifdef _DEBUG
#	define SystemAlarm_rv_(rc,value) SystemAlarm(rc,value,TRACE_POINT)
#	define SystemAlarm_return_FALSE_(rc) SystemAlarm(rc,FALSE,TRACE_POINT)
#	define SystemAlarm_return_TRUE_(rc) SystemAlarm(rc,TRUE,TRACE_POINT)
#	else
#		ifdef USE_ERROR_TEXT
#		define SystemAlarm_rv_(rc,value) SystemAlarm(rc,value,TRACE_POINT)
#		define SystemAlarm_return_FALSE_(rc) SystemAlarm(rc,FALSE,TRACE_POINT)
#		define SystemAlarm_return_TRUE_(rc) SystemAlarm(rc,TRUE,TRACE_POINT)
#		else
#		define SystemAlarm_rv_(rc,value) value
#		define SystemAlarm_return_FALSE_(rc) FALSE
#		define SystemAlarm_return_TRUE_(rc) TRUE
#		endif
#	endif
#	endif



	/* ���������� ����� � ��������� ������ (HRESULT) � Event Log [-S-E] */

	static HRESULT LogSysMsg(HRESULT rc,TRACE_POINT_ARGS)
	{
#		ifdef _DEBUG
		Lz::ErrorMessage<> m(rc);
		CString echo((LPCTSTR)m);
		echo = CleanUp(echo);
		TRACE_LOG_(echo,TRACE_POINT_SEQ);
		LastErrorMessage() = echo;
#		else
		CString echo;
		echo = FormatStr(_T("HRESULT(%x)"), (int)rc );
		LastErrorMessage() = echo;
#		endif
		//
		Lz::EventLogException e(rc);
		Container<Lz::EventLog<ED> >().ReportEvent(e);
		//
		return rc;
	}
#	ifndef LogSysMsg_
#	define LogSysMsg_(rc) LogSysMsg(rc,TRACE_POINT)
#	endif

	/* ���������� ����� � ��������� ������ (HRESULT) � Event Log � ���������� �������� [rS-E] */

	template<class _RetVal>
	static _RetVal LogSysMsg(HRESULT rc,_RetVal returnValue,TRACE_POINT_ARGS)
	{
#		ifdef _DEBUG
		Lz::ErrorMessage<> m(rc);
		CString echo((LPCTSTR)m);
		echo = CleanUp(echo);
		TRACE_LOG_(echo,TRACE_POINT_SEQ);
		LastErrorMessage() = echo;
#		else
		TRACE_POINT_NOT_USED();
		CString echo;
		echo = FormatStr(_T("HRESULT(%x)"), (int)rc );
		LastErrorMessage() = echo;
#		endif
		//
		Lz::EventLogException e(rc);
		Container<Lz::EventLog<ED> >().ReportEvent(e);
		//
		return returnValue;
	}
#	ifndef LogSysMsg_rv_
#	ifdef _DEBUG
#	define LogSysMsg_rv_(rc,value) LogSysMsg(rc,value,TRACE_POINT)
#	define LogSysMsg_return_FALSE_(rc) LogSysMsg(rc,FALSE,TRACE_POINT)
#	define LogSysMsg_return_TRUE_(rc) LogSysMsg(rc,TRUE,TRACE_POINT)
#	else
#		ifdef USE_ERROR_TEXT
#		define LogSysMsg_rv_(rc,value) LogSysMsg(rc,value,TRACE_POINT)
#		define LogSysMsg_return_FALSE_(rc) LogSysMsg(rc,FALSE,TRACE_POINT)
#		define LogSysMsg_return_TRUE_(rc) LogSysMsg(rc,TRUE,TRACE_POINT)
#		else
#		define LogSysMsg_rv_(rc,value) value
#		define LogSysMsg_return_FALSE_(rc) FALSE
#		define LogSysMsg_return_TRUE_(rc) TRUE
#		endif
#	endif
#	endif



	/* ���������� ����������� (�������������������) ����� � ��������� ������ (HRESULT) 
	   � Debug Output [-SO-%]   */

	static HRESULT DisplayExplained(const CString& msg,HRESULT rc,TRACE_POINT_ARGS)
	{
		Lz::ErrorMessage<> m(rc);
		CString rcMsg((LPCTSTR)m);
		rcMsg = CleanUp(rcMsg);
		CString echo; 
		echo = FormatStr(_T("%s:\n%s"), msg.GetString(), rcMsg.GetString() );
		//
		LastErrorMessage() = msg;
		//
#		ifdef _DEBUG
		TRACE_LOG_(echo,TRACE_POINT_SEQ);
#		endif
		//
		return rc;
	}
#	ifndef DisplayExplained_
#	define DisplayExplained_(msg,rc) DisplayExplained(msg,rc,TRACE_POINT)
#	endif

	/* ���������� ����������� (�������������������) ����� � ��������� ������ (HRESULT) 
	   � Debug Output � ���������� �������� [rSO-%]   */

	template<class _RetVal>
	static _RetVal DisplayExplained(const CString& msg,HRESULT rc,_RetVal returnValue,TRACE_POINT_ARGS)
	{
		Lz::ErrorMessage<> m(rc);
		CString rcMsg((LPCTSTR)m);
		rcMsg = CleanUp(rcMsg);
		CString echo; 
		echo = FormatStr(_T("%s:\n%s"), msg.GetString(), rcMsg.GetString() );
		//
		LastErrorMessage() = echo;
		//
#		ifdef _DEBUG
		TRACE_LOG_(echo,TRACE_POINT_SEQ);
#		else
		TRACE_POINT_NOT_USED();
#		endif
		//
		return returnValue;
	}
#	ifndef DisplayExplained_rv_
#	ifdef _DEBUG
#	define DisplayExplained_rv_(msg,rc,value) DisplayExplained(msg,rc,value,TRACE_POINT)
#	define DisplayExplained_return_FALSE_(msg,rc) DisplayExplained(msg,rc,FALSE,TRACE_POINT)
#	define DisplayExplained_return_TRUE_(msg,rc) DisplayExplained(msg,rc,TRUE,TRACE_POINT)
#	else
#		ifdef USE_ERROR_TEXT
#		define DisplayExplained_rv_(msg,rc,value) DisplayExplained(msg,rc,value,TRACE_POINT)
#		define DisplayExplained_return_FALSE_(msg,rc) DisplayExplained(msg,rc,FALSE,TRACE_POINT)
#		define DisplayExplained_return_TRUE_(msg,rc) DisplayExplained(msg,rc,TRUE,TRACE_POINT)
#		else
#		define DisplayExplained_rv_(msg,rc,value) value
#		define DisplayExplained_return_FALSE_(msg,rc) FALSE
#		define DisplayExplained_return_TRUE_(msg,rc) TRUE
#		endif
#	endif
#	endif



	/* ���������� ����������� (�������������������) ����� � ��������� ������ (HRESULT) 
	   � Debug Output � Event Log [-SOE%]   */

	static HRESULT AlarmExplained(const CString& msg,HRESULT rc,Severity S,EventSource* E,
		TRACE_POINT_ARGS)
	{
		Lz::ErrorMessage<> m(rc);
		CString echo; 
		CString rcMsg((LPCTSTR)m);
		rcMsg = CleanUp(rcMsg);
		echo = FormatStr(_T("%s:\n%s"), msg.GetString(), rcMsg.GetString() ); 
		CString text; 
		TRACE_TEXT_(echo,TRACE_POINT_SEQ,text); text = CString(_T("\n")) + text;
		//
#		ifdef _DEBUG
		TRACE_LOG_(echo,TRACE_POINT_SEQ);
#		endif
		//
		LastErrorMessage() = echo;
		//
		if (! E) E = dEvS();
		HRESULT envHR;
		if (S == Severity_Error) envHR = E->GetErrorCode();
		else envHR = E->GetWarningCode();
		//
		Container<Lz::EventLog<ED> >().ReportEvent(
			Lz::EventLogException(envHR) % text.GetString()
			);
		//
		return rc;
	}
#	ifndef AlarmExplained_
#	define AlarmExplained_(msg,rc) AlarmExplained(msg,rc,Severity_Error,0,TRACE_POINT)
#	define AlarmExplainedWarning_(msg,rc) AlarmExplained(msg,rc,Severity_Error,0,TRACE_POINT)
#	endif

	/* ���������� ����������� (�������������������) ����� � ��������� ������ (HRESULT) 
	   � Debug Output � Event Log � ���������� �������� [rSOE%]   */

	template<class _RetVal>
	static _RetVal AlarmExplained(const CString& msg,HRESULT rc,Severity S,EventSource* E,
		_RetVal returnValue,TRACE_POINT_ARGS)
	{
		Lz::ErrorMessage<> m(rc);
		CString rcMsg((LPCTSTR)m);
		rcMsg = CleanUp(rcMsg);
		CString echo; 
		echo = FormatStr(_T("%s:\n%s"), msg.GetString(), rcMsg.GetString() ); 
		CString text; 
		TRACE_TEXT_(echo,TRACE_POINT_SEQ,text); text = CString(_T("\n")) + text;
		//
#		ifdef _DEBUG
		TRACE_LOG_(echo,TRACE_POINT_SEQ);
#		endif
		//
		LastErrorMessage() = echo;
		//
		if (! E) E = dEvS();
		HRESULT envHR;
		if (S == Severity_Error) envHR = E->GetErrorCode();
		else envHR = E->GetWarningCode();
		//
		Container<Lz::EventLog<ED> >().ReportEvent(
			Lz::EventLogException(envHR) % text.GetString()
			);
		//
		return returnValue;
	}
#	ifndef AlarmExplained_rv_
#	ifdef _DEBUG
#	define AlarmExplained_rv_(msg,rc,value) AlarmExplained(msg,rc,Severity_Error,0,value,TRACE_POINT)
#	define AlarmExplained_return_FALSE_(msg,rc) AlarmExplained(msg,rc,Severity_Error,0,FALSE,TRACE_POINT)
#	define AlarmExplained_return_TRUE_(msg,rc) AlarmExplained(msg,rc,Severity_Error,0,TRUE,TRACE_POINT)
#	else
#		ifdef USE_ERROR_TEXT
#		define AlarmExplained_rv_(msg,rc,value) AlarmExplained(msg,rc,Severity_Error,0,value,TRACE_POINT)
#		define AlarmExplained_return_FALSE_(msg,rc) AlarmExplained(msg,rc,Severity_Error,0,FALSE,TRACE_POINT)
#		define AlarmExplained_return_TRUE_(msg,rc) AlarmExplained(msg,rc,Severity_Error,0,TRUE,TRACE_POINT)
#		else
#		define AlarmExplained_rv_(msg,rc,value) value
#		define AlarmExplained_return_FALSE_(msg,rc) FALSE
#		define AlarmExplained_return_TRUE_(msg,rc) TRUE
#		endif
#	endif
	//
#	ifdef _DEBUG
#	define AlarmExplainedWarning_rv_(msg,rc,value) AlarmExplained(msg,rc,Severity_Warning,0,value,TRACE_POINT)
#	define AlarmExplainedWarning_return_FALSE_(msg,rc) AlarmExplained(msg,rc,Severity_Warning,0,FALSE,TRACE_POINT)
#	define AlarmExplainedWarning_return_TRUE_(msg,rc) AlarmExplained(msg,rc,Severity_Warning,0,TRUE,TRACE_POINT)
#	else
#		ifdef USE_ERROR_TEXT
#		define AlarmExplainedWarning_rv_(msg,rc,value) AlarmExplained(msg,rc,Severity_Warning,0,value,TRACE_POINT)
#		define AlarmExplainedWarning_return_FALSE_(msg,rc) AlarmExplained(msg,rc,Severity_Warning,0,FALSE,TRACE_POINT)
#		define AlarmExplainedWarning_return_TRUE_(msg,rc) AlarmExplained(msg,rc,Severity_Warning,0,TRUE,TRACE_POINT)
#		else
#		define AlarmExplainedWarning_rv_(msg,rc,value) value
#		define AlarmExplainedWarning_return_FALSE_(msg,rc) FALSE
#		define AlarmExplainedWarning_return_TRUE_(msg,rc) TRUE
#		endif
#	endif
#	endif



	/* ���������� ����������� (�������������������) ����� � ��������� ������ (HRESULT) 
	   � Event Log [-S-E%]   */

	static HRESULT LogExplained(const CString& msg,HRESULT rc,Severity S,EventSource* E,
		TRACE_POINT_ARGS)
	{
		Lz::ErrorMessage<> m(rc);
		CString rcMsg((LPCTSTR)m);
		rcMsg = CleanUp(rcMsg);
		CString echo; 
		echo = FormatStr(_T("%s:\n%s"), msg.GetString(), rcMsg.GetString() ); 
		CString text; 
		TRACE_TEXT_(echo,TRACE_POINT_SEQ,text); text = CString(_T("\n")) + text;
		//
		LastErrorMessage() = echo;
		//
		if (! E) E = dEvS();
		HRESULT envHR;
		if (S == Severity_Error) envHR = E->GetErrorCode();
		else envHR = E->GetWarningCode();
		//
		Container<Lz::EventLog<ED> >().ReportEvent(
			Lz::EventLogException(envHR) % text.GetString()
			);
		//
		return rc;
	}
#	ifndef LogExplained_
#	define LogExplained_(msg,rc) LogExplained(msg,rc,Severity_Error,0,TRACE_POINT)
#	define LogExplainedWarning_(msg,rc) LogExplainedWarning(msg,rc,Severity_Error,0,TRACE_POINT)
#	endif

	/* ���������� ����������� (�������������������) ����� � ��������� ������ (HRESULT) 
	   � Event Log � ���������� �������� [rS-E%]   */

	template<class _RetVal>
	static _RetVal LogExplained(const CString& msg,HRESULT rc,Severity S,_RetVal returnValue,TRACE_POINT_ARGS)
	{
		Lz::ErrorMessage<> m(rc);
		CString rcMsg((LPCTSTR)m);
		rcMsg = CleanUp(rcMsg);
		CString echo; 
		echo = FormatStr(_T("%s:\n%s"), msg.GetString(), rcMsg.GetString() ); 
		CString text; 
		TRACE_TEXT_(echo,TRACE_POINT_SEQ,text); text = CString(_T("\n")) + text;
		//
		LastErrorMessage() = echo;
		//
		HRESULT envHR;
		if (S == Severity_Error) envHR = T::GetErrorCode();
		else envHR = T::GetWarningCode();
		//
		Container<Lz::EventLog<ED> >().ReportEvent(
			Lz::EventLogException(envHR) % text.GetString()
			);
		//
		return returnValue;
	}
#	ifndef LogExplained_rv_
#	ifdef _DEBUG
#	define LogExplained_rv_(rc,value) LogExplained(rc,Severity_Error,value,TRACE_POINT)
#	define LogExplained_return_FALSE_(rc) LogExplained(rc,Severity_Error,FALSE,TRACE_POINT)
#	define LogExplained_return_TRUE_(rc) LogExplained(rc,Severity_Error,TRUE,TRACE_POINT)
#	else
#		ifdef USE_ERROR_TEXT
#		define LogExplained_rv_(rc,value) LogExplained(rc,Severity_Error,value,TRACE_POINT)
#		define LogExplained_return_FALSE_(rc) LogExplained(rc,Severity_Error,FALSE,TRACE_POINT)
#		define LogExplained_return_TRUE_(rc) LogExplained(rc,Severity_Error,TRUE,TRACE_POINT)
#		else
#		define LogExplained_rv_(rc,value) value
#		define LogExplained_return_FALSE_(rc) FALSE
#		define LogExplained_return_TRUE_(rc) TRUE
#		endif
#	endif
	//
#	ifdef _DEBUG
#	define LogExplainedWarning_rv_(rc,value) LogExplained(rc,Severity_Warning,value,TRACE_POINT)
#	define LogExplainedWarning_return_FALSE_(rc) LogExplained(rc,Severity_Warning,FALSE,TRACE_POINT)
#	define LogExplainedWarning_return_TRUE_(rc) LogExplained(rc,Severity_Warning,TRUE,TRACE_POINT)
#	else
#		ifdef USE_ERROR_TEXT
#		define LogExplainedWarning_rv_(rc,value) LogExplained(rc,Severity_Warning,value,TRACE_POINT)
#		define LogExplainedWarning_return_FALSE_(rc) LogExplained(rc,Severity_Warning,FALSE,TRACE_POINT)
#		define LogExplainedWarning_return_TRUE_(rc) LogExplained(rc,Severity_Warning,TRUE,TRACE_POINT)
#		else
#		define LogExplainedWarning_rv_(rc,value) value
#		define LogExplainedWarning_return_FALSE_(rc) FALSE
#		define LogExplainedWarning_return_TRUE_(rc) TRUE
#		endif
#	endif
#	endif

	// ������� ������ %i

	static CString CleanUp(const CString& msg)
	{
		CString text(msg);
		//
		if ((text[text.GetLength()-1] == '\n') && (text.GetLength() >= 3))
		{
			text = text.Left(text.GetLength()-2);
		}
		//
		bool bDone = false;
		while (! bDone)
		{
			int pos = text.Find(_T("%"));
			if (pos != -1)
			{
				CString L = text.Left(pos);
				CString R;
				if (text.GetLength()-pos-1 == 0)
				{
				}
				else
				{
					R = text.Right(text.GetLength()-pos-1);
					if ((R[0] == '0') || (R[0] == '1') || (R[0] == '2') || (R[0] == '3'))
					{
						text = L + (R.Right(R.GetLength()-1));
					}
					else
					{
						text = L + R;
					}
				}
			}
			else
			{
				bDone = true;
			}
		}
		//
		return text;
	}



	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// ��������

	static HRESULT DoHandleError(HRESULT rc,TRACE_POINT_ARGS)
	{ 
		if (EventLogLevel() >= 2) return SystemAlarm(rc,TRACE_POINT_SEQ); 
		else return DisplaySysMsg(rc,TRACE_POINT_SEQ); 
	}

	template<class _RetVal>
	static _RetVal DoHandleError(HRESULT rc,_RetVal returnValue,TRACE_POINT_ARGS)
	{ 
		if (EventLogLevel() >= 2) return SystemAlarm(rc,returnValue,TRACE_POINT_SEQ); 
		else return DisplaySysMsg(rc,returnValue,TRACE_POINT_SEQ); 
	}

	template<class _RetVal>
	static _RetVal DoExplainedError(const CString& msg,HRESULT rc,_RetVal value,TRACE_POINT_ARGS) 
	{ 
		if (EventLogLevel() >= 2) return AlarmExplained(msg,rc,value,TRACE_POINT_SEQ); 
		else return DisplayExplained(msg,rc,value,TRACE_POINT,TRACE_POINT_SEQ); 
	}

#	ifndef DisplayError_

#	define DisplayError_(rc) DisplaySysMsg(rc,TRACE_POINT)

#	define SignalError_(rc) DoHandleError(rc,TRACE_POINT);

#	define SignalError_rv_(rc,value) DoHandleError(rc,value,TRACE_POINT);

#	define ExplainedError_rv_(msg,rc,value) DoExplainedError(msg,rc,value,TRACE_POINT)

#	define ExplainedError_return_FALSE_(msg,rc) DoExplainedError(msg,rc,FALSE,TRACE_POINT)

#	define ExplainedError_return_TRUE_(msg,rc) DoExplainedError(msg,rc,TRUE,TRACE_POINT)

#	endif
};

#undef _Include_ErrorHandling_class

#endif // _Include_ErrorHandling_class



} // namespace  
