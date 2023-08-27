#ifndef __LZ_ERRORMESSAGE_H__
#define __LZ_ERRORMESSAGE_H__

#pragma once

//#include <atlsimpstr.h>
#include <strsafe.h>
#include <lmerr.h>

#include "argarray.h"
//#include "./exception.h"

#define ERRMSG_MSMQ_DLL TEXT("MQUTIL.DLL")
#define ERRMSG_NETMSG_DLL TEXT("NETMSG.DLL")
#define ERRMSG_URLMON_DLL TEXT("URLMON.DLL")
#define ERRMSG_WEBMSG_DLL TEXT("WebMsg.DLL")

#define FACILITY_WEB 0xAFF

#define ERRMSG_LANGID MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)

namespace Lz {

static bool SetErrorInfo(LPCWSTR description);
inline HRESULT CreateErrorInfo(LPCWSTR description, IErrorInfo** ppIErrorInfo);

//__declspec(noinline) inline bool SetErrorInfo(LPCWSTR description)
__declspec(noinline)
static bool SetErrorInfo(LPCWSTR description)
{
	CComPtr<IErrorInfo> spIErrorInfo;

	CreateErrorInfo(description, &spIErrorInfo);

	if( spIErrorInfo )
	{
		::SetErrorInfo(0, spIErrorInfo);
		return true;
	}

	return false;
};

inline HRESULT CreateErrorInfo(LPCWSTR description, IErrorInfo** ppIErrorInfo)
{
	CComPtr<ICreateErrorInfo> spICreateErrorInfo;

	if( SUCCEEDED(::CreateErrorInfo(&spICreateErrorInfo)) && spICreateErrorInfo )
	{
		spICreateErrorInfo->SetDescription(const_cast<LPWSTR>(description));

		return spICreateErrorInfo.QueryInterface(ppIErrorInfo);
	}

	return E_FAIL;
};

class ErrorMessageModule
{
protected:
	bool m_bRelease;
	HMODULE m_hModule;
public:
	ErrorMessageModule(HRESULT hr) : m_bRelease(true), m_hModule(0)
	{
		if( HRESULT_FACILITY(hr) == FACILITY_MSMQ )
			m_hModule = ::LoadLibrary(ERRMSG_MSMQ_DLL);
		else if( HRESULT_FACILITY(hr) == FACILITY_WEB )
			m_hModule = ::LoadLibrary(ERRMSG_WEBMSG_DLL);
		else if( HRESULT_FACILITY(hr) == FACILITY_INTERNET && HRESULT_CODE(hr) < 0x3FF )
			m_hModule = ::LoadLibrary(ERRMSG_URLMON_DLL);
		else if( hr >= NERR_BASE && hr <= MAX_NERR )
			m_hModule = ::LoadLibrary(ERRMSG_NETMSG_DLL);
	}

	virtual ~ErrorMessageModule()
	{
		if( m_bRelease && m_hModule != 0 )
			::FreeLibrary(m_hModule);
	}

	operator LPCVOID () { return m_hModule; }
};

template<class TModClass=ErrorMessageModule>
class ErrorMessage
{
protected:
	CHeapPtr< TCHAR, CLocalAllocator > m_pMsg;
	CComPtr<IErrorInfo> m_spIErrorInfo;

public:
	ErrorMessage() {}

	ErrorMessage(LPCTSTR szMsg)
	{
		size_t char_count;
		PrepareBuf();

		if( SUCCEEDED(::StringCchLength(szMsg, STRSAFE_MAX_CCH, &char_count)) && char_count > 0 )
		{
			char_count++;
			m_pMsg.AllocateBytes(char_count*sizeof(TCHAR));
			::StringCchCopy((LPTSTR)m_pMsg, char_count, szMsg);
		}
	}

	ErrorMessage(DWORD dwMessageId)
	{
		GetMessage(dwMessageId);
	}

	ErrorMessage(DWORD dwMessageId, ArgArray* pArgArray)
	{
		GetMessage(dwMessageId, pArgArray);
	}

	LPCTSTR GetMessage(DWORD dwMessageId, ArgArray* pArgArray)
	{
		if( pArgArray )
		{
			ArgArrayVector av(*pArgArray);
			return GetMessage(dwMessageId, av);
		}
		else
		{
			return GetMessage(dwMessageId);
		}
	}

	LPCTSTR GetMessage(DWORD dwMessageId, LPCTSTR* pArgVector)
	{
		DWORD dwFlag = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_ARGUMENT_ARRAY;

		TModClass mod(dwMessageId);

		dwFlag |= ( (LPCVOID)mod ? FORMAT_MESSAGE_FROM_HMODULE : FORMAT_MESSAGE_FROM_SYSTEM );

		PrepareBuf();

		::FormatMessage(dwFlag, (LPCVOID)mod, dwMessageId, ERRMSG_LANGID, (LPTSTR)&m_pMsg, 0, (va_list*)pArgVector);

		return m_pMsg;
	}

	ErrorMessage(_com_error& e)
	{
		m_spIErrorInfo.Attach(e.ErrorInfo());
		GetMessage(e.Error(), m_spIErrorInfo);
	}

	/*
	ErrorMessage(::Lz::Exception& e)
	{
		GetMessage(e.m_Error.hr, e.GetErrorInfo(), e.GetArgArray());
	}
	*/

	LPCTSTR GetMessage(HRESULT hr, IErrorInfo* pIErrorInfo, ArgArray* pArgArray = NULL)
	{
		if( pIErrorInfo )
		{
			CComBSTR descr;
			pIErrorInfo->GetDescription(&descr);
			return GetMessage(descr);
		}
		else
			GetMessage(hr, pArgArray);

		return NULL;
	}

	LPCTSTR GetMessage(BSTR bstrMsg)
	{
		PrepareBuf();
		
		UINT lenW = ::SysStringLen(bstrMsg);

		if( lenW > 0 )
		{
			UINT lenA = lenW * sizeof(TCHAR);
			m_pMsg.AllocateBytes(lenA+1);
			((LPTSTR)m_pMsg)[lenA] = 0x0;
			::WideCharToMultiByte(_AtlGetConversionACP(), 0, bstrMsg, lenW, (LPTSTR)m_pMsg, lenA, NULL, NULL);
		}

		return m_pMsg;
	}

	LPCTSTR GetMessage(DWORD dwMessageId, bool bArgs = false, ... )
	{
		DWORD dwFlag = FORMAT_MESSAGE_ALLOCATE_BUFFER;

		TModClass mod(dwMessageId);

		dwFlag |= ( (LPCVOID)mod ? FORMAT_MESSAGE_FROM_HMODULE : FORMAT_MESSAGE_FROM_SYSTEM );

		PrepareBuf();

		if( bArgs )
		{
			va_list args;
			va_start( args, bArgs );

			::FormatMessage(dwFlag, (LPCVOID)mod, dwMessageId, ERRMSG_LANGID, (LPTSTR)&m_pMsg, 0, &args);

			va_end( args );
		}
		else
		{
			::FormatMessage(dwFlag|FORMAT_MESSAGE_IGNORE_INSERTS, (LPCVOID)mod, dwMessageId, ERRMSG_LANGID, (LPTSTR)&m_pMsg, 0, NULL);
		}

		return m_pMsg;
	}

	bool SetErrorInfo()
	{
		if( m_spIErrorInfo )
			return SUCCEEDED(::SetErrorInfo(0, m_spIErrorInfo));
		else if( (TCHAR*)m_pMsg )
			return Lz::SetErrorInfo(CComBSTR((LPTSTR)m_pMsg));

		return false;
	}

	operator LPCTSTR() { return m_pMsg; }

protected:
	void PrepareBuf() { if( (TCHAR*)m_pMsg ) m_pMsg.Free(); };
};

}; // namespace Lz

#endif // __LZ_ERRORMESSAGE_H__
