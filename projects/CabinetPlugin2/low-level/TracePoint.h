/*
 TracePoint.h : ���������� � �������������� � ����, �������.

 $Name: work1 $
 $Revision: 1.1.2.4 $
 $Date: 2008/10/24 07:51:17 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����������� ��� ������������� � TCHAR 

#ifndef __WFILE__
#define __WFILE__ CStringW(__FILE__).GetString()
#endif

#ifdef _UNICODE
#define __TFILE__ __WFILE__
#define __TFUNCTION__ CStringW(__FUNCTION__).GetString()
#else
#define __TFILE__ __FILE__
#define __TFUNCTION__ __FUNCTION__
#endif



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ������� ��� ������������� "�������������� � ����" � ������ ��������� 

#ifdef _DEBUG
#	ifndef _PROVIDE_TRACE_INFO
#	define _PROVIDE_TRACE_INFO
#	endif
#endif

#ifndef TRACE_LOG_PREFIX
#define TRACE_LOG_PREFIX (_T(""))
#endif

#define TRACE_LOG_START (TRACE_LOG_PREFIX + FormatStr(_T("%d"),(int)GetCurrentThreadId()) + _T(" "))

// -----------------------------------------------------------------------------------------------
#ifdef _PROVIDE_TRACE_INFO

#define TRACE_POINT __TFUNCTION__,__LINE__,__TFILE__
#define TRACE_POINT_F __TFUNCTION__ % __LINE__ % __TFILE__
#define TRACE_POINT_SEQ _source,_line,_code_file
#define TRACE_POINT_SEQ_F _source % _line % _code_file
#define TRACE_POINT_SEQUENCE TRACE_POINT_SEQ
#define TRACE_POINT_ARGS const TCHAR* _source,int _line,const TCHAR* _code_file
#define TRACE_POINT_INI_ARGS const TCHAR* _source,int _line,const TCHAR* _code_file
#define TRACE_POINT_TYPES const TCHAR*,int,const TCHAR*
//
#define TRACE_POINT_NOT_USED() PARAMETER_NOT_USED(_source); PARAMETER_NOT_USED(_line); PARAMETER_NOT_USED(_code_file);

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� ������� ������ ������� 

#ifndef NO_TRACE_LOG
#define BASICTRACE(s) { CString sT(s); OutputDebugString(sT.GetString()); }
#else
#define BASICTRACE(s) { }
#endif

#ifndef DEBUG_TRACE_COMMAND
#define DEBUG_TRACE_COMMAND BASICTRACE
#endif

// ----
#ifndef NO_TRACE_LOG

#define TRACE_LOG_(msg,SEQ) { \
	CString report; \
	report = FormatStr(TRACE_LOG_START + _S("----\n") + TRACE_LOG_START + _S("TracePoint: %s, line %d @ %s\n") + TRACE_LOG_START + _S("%s\n"), SEQ, CString(msg).GetString() ); \
	DEBUG_TRACE_COMMAND((const TCHAR*)report); \
}
#define TRACE_LOG(msg) TRACE_LOG_(msg,TRACE_POINT)
#define TRACE_LOG_STR(msg) TRACE_LOG(msg.c_str())

#define TRACE_TEXT_(msg,SEQ,text) { \
	CString report; \
	report = FormatStr(_T("----\nTracePoint: %s, line %d @ %s\n%s\n"), SEQ, CString(msg).GetString() ); \
	text = (const TCHAR*)report; \
}

#define TRACE_LINE_(msg) { \
	CString report; \
	report = FormatStr(TRACE_LOG_START + _T("%s\n"), CString(msg).GetString() ); \
	DEBUG_TRACE_COMMAND((const TCHAR*)report); \
}
#define TRACE_LINE(msg) TRACE_LINE_(msg)
#define TRACE_LINE_STR(msg) TRACE_LOG(msg.c_str())

#else // NO_TRACE_LOG

#define TRACE_LOG_(msg,SEQ) { }
#define TRACE_LOG(msg) { }
#define TRACE_LOG_STR(msg) { }
#define TRACE_TEXT_(msg,SEQ,text) { text = _T(""); }
#define TRACE_LINE_(msg,SEQ) { }
#define TRACE_LINE(msg) { }
#define TRACE_LINE_STR(msg) { }

#endif
// ----

// -----------------------------------------------------------------------------------------------
#else // �� ���������� ���������� � ��������������

#define TRACE_POINT 0
#define TRACE_POINT_F 0
#define TRACE_POINT_SEQ _dummy
#define TRACE_POINT_SEQ_F _dummy
#define TRACE_POINT_SEQUENCE TRACE_POINT_SEQ
#define TRACE_POINT_ARGS int _dummy
#define TRACE_POINT_INI_ARGS int _dummy
#define TRACE_POINT_TYPES int
//
#define TRACE_POINT_NOT_USED() PARAMETER_NOT_USED(_dummy)

// ----
#ifndef NO_TRACE_LOG

#define TRACE_LOG_(msg,SEQ) { }
#define TRACE_LOG(msg) TRACE_LOG_(msg,TRACE_POINT)
#define TRACE_LOG_STR(msg) TRACE_LOG(msg.c_str())
#define TRACE_TEXT_(msg,SEQ,text) { text = CString(msg).GetString(); }

#else // NO_TRACE_LOG

#define TRACE_LOG_(msg,SEQ) { }
#define TRACE_LOG(msg) { }
#define TRACE_LOG_STR(msg) { }
#define TRACE_TEXT_(msg,SEQ,text) { text = _T(""); }

#endif
// ----

#endif
// -----------------------------------------------------------------------------------------------



// -----------------------------------------------------------------------------------------------
#ifndef NO_TRACE_LOG

#define TRACE_LOG1(msg,a1) { \
	CString echo; echo = FormatStr(msg,a1); TRACE_LOG_(echo,TRACE_POINT); }

#define TRACE_LOG2(msg,a1,a2) { \
	CString echo; echo = FormatStr(msg,a1,a2); TRACE_LOG_(echo,TRACE_POINT); }

#define TRACE_LOG3(msg,a1,a2,a3) { \
	CString echo; echo = FormatStr(msg,a1,a2,a3); TRACE_LOG_(echo,TRACE_POINT); }

#define TRACE_LINE1(msg,a1) { \
	CString echo; echo = FormatStr(msg,a1); TRACE_LINE_(echo); }

#define TRACE_LINE2(msg,a1,a2) { \
	CString echo; echo = FormatStr(msg,a1,a2); TRACE_LINE_(echo); }

#define TRACE_LINE3(msg,a1,a2,a3) { \
	CString echo; echo = FormatStr(msg,a1,a2,a3); TRACE_LINE_(echo); }

#else

#define TRACE_LOG1(msg,a1) { }
#define TRACE_LOG2(msg,a1,a2) { }
#define TRACE_LOG3(msg,a1,a2,a3) { }
#define TRACE_LINE1(msg,a1) { }
#define TRACE_LINE2(msg,a1,a2) { }
#define TRACE_LINE3(msg,a1,a2,a3) { }

#endif
// -----------------------------------------------------------------------------------------------



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ������

#ifndef PARAMETER_NOT_USED
#define PARAMETER_NOT_USED(x) { void* _p; _p = (void*)&(x); }
#endif






// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ��������������� ������� �����, ����������� ��������� TRACE_POINT

namespace  {

struct TracePoint
{
	// �������� (��������, ����� ��� �����)
	CString		m_TracePointSource;

	// ������ � �����
	int			m_TracePointLine;

	// ����
	CString		m_TracePointCodeFile;

	TracePoint() 
		: m_TracePointSource(_T("")),
		  m_TracePointLine(-1),
		  m_TracePointCodeFile(_T(""))
	{
	}

#	ifdef _PROVIDE_TRACE_INFO
	TracePoint(TRACE_POINT_INI_ARGS) 
		: m_TracePointSource(_source),
		  m_TracePointLine(_line),
		  m_TracePointCodeFile(_code_file)
	{
	}

	void Init(TRACE_POINT_INI_ARGS) 
	{
		m_TracePointSource = _source;
		m_TracePointLine = _line;
		m_TracePointCodeFile = _code_file;
	}
#	else
	TracePoint(TRACE_POINT_INI_ARGS) 
		: m_TracePointSource(_T("")),
		  m_TracePointLine(_dummy),
		  m_TracePointCodeFile(_T(""))
	{
	}

	void Init(TRACE_POINT_INI_ARGS) 
	{
		m_TracePointLine = _dummy;
	}
#	endif
};

} // namespace  


