/*
 AtlX.h : ���������� � ATL 

 $Name: work1 $
 $Revision: 1.1.2.3 $
 $Date: 2008/10/16 07:09:28 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

// ----
// ����������� ����������� ATL 

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit
// turns off ATL's hiding of some common and often safely ignored warning messages

#define _ATL_ALL_WARNINGS

// ----
// ATL

#include <atlbase.h>
#include <atlcom.h>
#include <atlwin.h>
#include <atltypes.h>
#include <atlctl.h>
#include <atlhost.h>

#include <comdef.h>

#include <ATLComTime.h>

#include <atlstr.h>

#include <strsafe.h>
#pragma comment(lib, "strsafe.lib" )

using namespace ATL;



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ������

#ifdef _A
#error slot: Macro _A already defined
#endif
//
#define _A(x) (CStringA(x))

#ifdef _W
#error slot: Macro _W already defined
#endif
//
#define _W(x) (CStringW(x))

#ifdef _S
#error slot: Macro _S already defined
#endif
//
#define _S(x) (CString(x))

// ������ UNICODE

namespace  { 
	typedef CStringW string;
}

// ===============================================================================================
// ���������

// ----
// (A)

inline static CStringA operator <(const CStringA& a,int n)
{
	int l = a.GetLength();
	if (l == 0) return a;
	if (n != l)
	{
		while (n < 0) n += l;
		while (n >= l) n -= l;
	}
	return a.Left(n);
}

inline static CStringA operator >(const CStringA& a,int n)
{
	int l = a.GetLength();
	if (l == 0) return a;
	if (n != l)
	{
		while (n < 0) n += l;
		while (n >= l) n -= l;
	}
	return a.Right(n);
}

// ��������� ������ item n ��� 

inline static CStringA operator *(const CStringA& item,int n)
{
	CStringA s;
	for (int k = 0; k < n; k++)
	{
		s += item;
	}
	return s;
}


// ----
// (W)

inline static CStringW operator <(const CStringW& a,int n)
{
	int l = a.GetLength();
	if (l == 0) return a;
	if (n != l)
	{
		while (n < 0) n += l;
		while (n >= l) n -= l;
	}
	return a.Left(n);
}

inline static CStringW operator >(const CStringW& a,int n)
{
	int l = a.GetLength();
	if (l == 0) return a;
	if (n != l)
	{
		while (n < 0) n += l;
		while (n >= l) n -= l;
	}
	return a.Right(n);
}

// ��������� ������ item n ��� 

inline static CStringW operator *(const CStringW& item,int n)
{
	CStringW s;
	for (int k = 0; k < n; k++)
	{
		s += item;
	}
	return s;
}



// ===============================================================================================
// ������� 

// � �������� namespace 

// ----
// (A)

inline static bool StartsWith(const CStringA& a,const CStringA& pattern)
{
	return (a.Left(pattern.GetLength())) == pattern;
}

inline static bool EndsWith(const CStringA& a,const CStringA& pattern)
{
	return (a.Right(pattern.GetLength())) == pattern;
}

inline static bool ExtractTextFromRight(const CStringA& in_text,char sep,
										CStringA* out_left=0,
										CStringA* out_right=0,
										CStringA* out_rightWithSep=0)
{
	CStringA text = in_text;
	//
	int p = text.ReverseFind(sep);
	if (p == -1) // not found
	{
		if (out_left) *out_left = CStringA();
		if (out_right) *out_right = CStringA();
		if (out_rightWithSep) *out_rightWithSep = CStringA();
		return false;
	}
	else
	{
		if (out_left) 
		{
			if (p > 0) *out_left = text.Left(p);
			else *out_left = CStringA();
		}
		if (out_right)
		{
			if (p < text.GetLength()-1) *out_right = text.Right(text.GetLength() - p - 1);
			else *out_right = CStringA();
		}
		if (out_rightWithSep)
		{
			if (p < text.GetLength()-1) *out_rightWithSep = text.Right(text.GetLength() - p); // ������� sep 
			else *out_rightWithSep = CStringA(sep);
		}
		return true;
	}
}


// ----
// (W)

inline static bool StartsWith(const CStringW& a,const CStringW& pattern)
{
	return (a.Left(pattern.GetLength())) == pattern;
}

inline static bool EndsWith(const CStringW& a,const CStringW& pattern)
{
	return (a.Right(pattern.GetLength())) == pattern;
}

inline static bool ExtractTextFromRight(const CStringW& in_text,char sep,
										CStringW* out_left=0,
										CStringW* out_right=0,
										CStringW* out_rightWithSep=0)
{
	CStringW text = in_text;
	//
	int p = text.ReverseFind(sep);
	if (p == -1) // not found
	{
		if (out_left) *out_left = CStringW();
		if (out_right) *out_right = CStringW();
		if (out_rightWithSep) *out_rightWithSep = CStringW();
		return false;
	}
	else
	{
		if (out_left) 
		{
			if (p > 0) *out_left = text.Left(p);
			else *out_left = CStringW();
		}
		if (out_right)
		{
			if (p < text.GetLength()-1) *out_right = text.Right(text.GetLength() - p - 1);
			else *out_right = CStringW();
		}
		if (out_rightWithSep)
		{
			if (p < text.GetLength()-1) *out_rightWithSep = text.Right(text.GetLength() - p); // ������� sep 
			else *out_rightWithSep = CStringW(sep);
		}
		return true;
	}
}





















// ===============================================================================================
// Safe Format � �������������� StringCchPrintf 

#ifndef _SIMPLE_STR_MAX
#define _SIMPLE_STR_MAX (1024 * 6)
#endif


// ----
// 1

template<typename A1>
inline static CStringA FormatStr(const char* formatStr,A1 a1)
{
	const int size = _SIMPLE_STR_MAX;
	char s[size];
	HRESULT rc = StringCchPrintfA(s,size,formatStr,a1); 
	if (rc == S_OK)
	{
		return s;
	}
	else if (STRSAFE_E_INVALID_PARAMETER)
	{
		OutputDebugString(_T("������ � StringCchPrintf: STRSAFE_E_INVALID_PARAMETER\n"));
	}
	else if (STRSAFE_E_INSUFFICIENT_BUFFER)
	{
		OutputDebugString(_T("������ � StringCchPrintf: STRSAFE_E_INSUFFICIENT_BUFFER\n"));
	}
	else
	{
		TCHAR errNumStr[265];
#		ifdef _UNICODE
		{
			_itow_s((int)rc,errNumStr,16);
		}
#		else
		{
			_itoa_s((int)rc,errNumStr,16);
		}
#		endif
		OutputDebugString(_T("����������� ������ � StringCchPrintf: HRESULT: 0x"));
		OutputDebugString(errNumStr);
		OutputDebugString(_T("\n"));
	}
	return "";
}

template<typename A1>
inline static CStringW FormatStr(const wchar_t* formatStr,A1 a1)
{
	const int size = _SIMPLE_STR_MAX;
	wchar_t s[size];
	HRESULT rc = StringCchPrintfW(s,size,formatStr,a1); 
	if (rc == S_OK)
	{
		return s;
	}
	else if (STRSAFE_E_INVALID_PARAMETER)
	{
		OutputDebugString(_T("������ � StringCchPrintf: STRSAFE_E_INVALID_PARAMETER\n"));
	}
	else if (STRSAFE_E_INSUFFICIENT_BUFFER)
	{
		OutputDebugString(_T("������ � StringCchPrintf: STRSAFE_E_INSUFFICIENT_BUFFER\n"));
	}
	else
	{
		TCHAR errNumStr[265];
#		ifdef _UNICODE
		{
			_itow_s((int)rc,errNumStr,16);
		}
#		else
		{
			_itoa_s((int)rc,errNumStr,16);
		}
#		endif
		OutputDebugString(_T("����������� ������ � StringCchPrintf: HRESULT: 0x"));
		OutputDebugString(errNumStr);
		OutputDebugString(_T("\n"));
	}
	return L"";
}



// ----
// 2  2

template<typename A1,typename A2>
inline static CStringA FormatStr(const char* formatStr,A1 a1,A2 a2)
{
	const int size = _SIMPLE_STR_MAX;
	char s[size];
	HRESULT rc = StringCchPrintfA(s,size,formatStr,a1,a2); 
	if (rc == S_OK)
	{
		return s;
	}
	else if (STRSAFE_E_INVALID_PARAMETER)
	{
		OutputDebugString(_T("������ � StringCchPrintf: STRSAFE_E_INVALID_PARAMETER\n"));
	}
	else if (STRSAFE_E_INSUFFICIENT_BUFFER)
	{
		OutputDebugString(_T("������ � StringCchPrintf: STRSAFE_E_INSUFFICIENT_BUFFER\n"));
	}
	else
	{
		TCHAR errNumStr[265];
#		ifdef _UNICODE
		{
			_itow_s((int)rc,errNumStr,16);
		}
#		else
		{
			_itoa_s((int)rc,errNumStr,16);
		}
#		endif
		OutputDebugString(_T("����������� ������ � StringCchPrintf: HRESULT: 0x"));
		OutputDebugString(errNumStr);
		OutputDebugString(_T("\n"));
	}
	return "";
}

template<typename A1,typename A2>
inline static CStringW FormatStr(const wchar_t* formatStr,A1 a1,A2 a2)
{
	const int size = _SIMPLE_STR_MAX;
	wchar_t s[size];
	HRESULT rc = StringCchPrintfW(s,size,formatStr,a1,a2); 
	if (rc == S_OK)
	{
		return s;
	}
	else if (STRSAFE_E_INVALID_PARAMETER)
	{
		OutputDebugString(_T("������ � StringCchPrintf: STRSAFE_E_INVALID_PARAMETER\n"));
	}
	else if (STRSAFE_E_INSUFFICIENT_BUFFER)
	{
		OutputDebugString(_T("������ � StringCchPrintf: STRSAFE_E_INSUFFICIENT_BUFFER\n"));
	}
	else
	{
		TCHAR errNumStr[265];
#		ifdef _UNICODE
		{
			_itow_s((int)rc,errNumStr,16);
		}
#		else
		{
			_itoa_s((int)rc,errNumStr,16);
		}
#		endif
		OutputDebugString(_T("����������� ������ � StringCchPrintf: HRESULT: 0x"));
		OutputDebugString(errNumStr);
		OutputDebugString(_T("\n"));
	}
	return L"";
}



// ----
// 3  3  3

template<typename A1,typename A2,typename A3>
inline static CStringA FormatStr(const char* formatStr,A1 a1,A2 a2,A3 a3)
{
	const int size = _SIMPLE_STR_MAX;
	char s[size];
	HRESULT rc = StringCchPrintfA(s,size,formatStr,a1,a2,a3); 
	if (rc == S_OK)
	{
		return s;
	}
	else if (STRSAFE_E_INVALID_PARAMETER)
	{
		OutputDebugString(_T("������ � StringCchPrintf: STRSAFE_E_INVALID_PARAMETER\n"));
	}
	else if (STRSAFE_E_INSUFFICIENT_BUFFER)
	{
		OutputDebugString(_T("������ � StringCchPrintf: STRSAFE_E_INSUFFICIENT_BUFFER\n"));
	}
	else
	{
		TCHAR errNumStr[265];
#		ifdef _UNICODE
		{
			_itow_s((int)rc,errNumStr,16);
		}
#		else
		{
			_itoa_s((int)rc,errNumStr,16);
		}
#		endif
		OutputDebugString(_T("����������� ������ � StringCchPrintf: HRESULT: 0x"));
		OutputDebugString(errNumStr);
		OutputDebugString(_T("\n"));
	}
	return "";
}

template<typename A1,typename A2,typename A3>
inline static CStringW FormatStr(const wchar_t* formatStr,A1 a1,A2 a2,A3 a3)
{
	const int size = _SIMPLE_STR_MAX;
	wchar_t s[size];
	HRESULT rc = StringCchPrintfW(s,size,formatStr,a1,a2,a3); 
	if (rc == S_OK)
	{
		return s;
	}
	else if (STRSAFE_E_INVALID_PARAMETER)
	{
		OutputDebugString(_T("������ � StringCchPrintf: STRSAFE_E_INVALID_PARAMETER\n"));
	}
	else if (STRSAFE_E_INSUFFICIENT_BUFFER)
	{
		OutputDebugString(_T("������ � StringCchPrintf: STRSAFE_E_INSUFFICIENT_BUFFER\n"));
	}
	else
	{
		TCHAR errNumStr[265];
#		ifdef _UNICODE
		{
			_itow_s((int)rc,errNumStr,16);
		}
#		else
		{
			_itoa_s((int)rc,errNumStr,16);
		}
#		endif
		OutputDebugString(_T("����������� ������ � StringCchPrintf: HRESULT: 0x"));
		OutputDebugString(errNumStr);
		OutputDebugString(_T("\n"));
	}
	return L"";
}



// ----
// 4  4  4  4 

template<typename A1,typename A2,typename A3,typename A4>
inline static CStringA FormatStr(const char* formatStr,A1 a1,A2 a2,A3 a3,A4 a4)
{
	const int size = _SIMPLE_STR_MAX;
	char s[size];
	HRESULT rc = StringCchPrintfA(s,size,formatStr,a1,a2,a3,a4); 
	if (rc == S_OK)
	{
		return s;
	}
	else if (STRSAFE_E_INVALID_PARAMETER)
	{
		OutputDebugString(_T("������ � StringCchPrintf: STRSAFE_E_INVALID_PARAMETER\n"));
	}
	else if (STRSAFE_E_INSUFFICIENT_BUFFER)
	{
		OutputDebugString(_T("������ � StringCchPrintf: STRSAFE_E_INSUFFICIENT_BUFFER\n"));
	}
	else
	{
		TCHAR errNumStr[265];
#		ifdef _UNICODE
		{
			_itow_s((int)rc,errNumStr,16);
		}
#		else
		{
			_itoa_s((int)rc,errNumStr,16);
		}
#		endif
		OutputDebugString(_T("����������� ������ � StringCchPrintf: HRESULT: 0x"));
		OutputDebugString(errNumStr);
		OutputDebugString(_T("\n"));
	}
	return "";
}

template<typename A1,typename A2,typename A3,typename A4>
inline static CStringW FormatStr(const wchar_t* formatStr,A1 a1,A2 a2,A3 a3,A4 a4)
{
	const int size = _SIMPLE_STR_MAX;
	wchar_t s[size];
	HRESULT rc = StringCchPrintfW(s,size,formatStr,a1,a2,a3,a4); 
	if (rc == S_OK)
	{
		return s;
	}
	else if (STRSAFE_E_INVALID_PARAMETER)
	{
		OutputDebugString(_T("������ � StringCchPrintf: STRSAFE_E_INVALID_PARAMETER\n"));
	}
	else if (STRSAFE_E_INSUFFICIENT_BUFFER)
	{
		OutputDebugString(_T("������ � StringCchPrintf: STRSAFE_E_INSUFFICIENT_BUFFER\n"));
	}
	else
	{
		TCHAR errNumStr[265];
#		ifdef _UNICODE
		{
			_itow_s((int)rc,errNumStr,16);
		}
#		else
		{
			_itoa_s((int)rc,errNumStr,16);
		}
#		endif
		OutputDebugString(_T("����������� ������ � StringCchPrintf: HRESULT: 0x"));
		OutputDebugString(errNumStr);
		OutputDebugString(_T("\n"));
	}
	return L"";
}



// ----
// 5  5  5  5  5 

template<typename A1,typename A2,typename A3,typename A4,typename A5>
inline static CStringA FormatStr(const char* formatStr,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5)
{
	const int size = _SIMPLE_STR_MAX;
	char s[size];
	HRESULT rc = StringCchPrintfA(s,size,formatStr,a1,a2,a3,a4,a5); 
	if (rc == S_OK)
	{
		return s;
	}
	else if (STRSAFE_E_INVALID_PARAMETER)
	{
		OutputDebugString(_T("������ � StringCchPrintf: STRSAFE_E_INVALID_PARAMETER\n"));
	}
	else if (STRSAFE_E_INSUFFICIENT_BUFFER)
	{
		OutputDebugString(_T("������ � StringCchPrintf: STRSAFE_E_INSUFFICIENT_BUFFER\n"));
	}
	else
	{
		TCHAR errNumStr[265];
#		ifdef _UNICODE
		{
			_itow_s((int)rc,errNumStr,16);
		}
#		else
		{
			_itoa_s((int)rc,errNumStr,16);
		}
#		endif
		OutputDebugString(_T("����������� ������ � StringCchPrintf: HRESULT: 0x"));
		OutputDebugString(errNumStr);
		OutputDebugString(_T("\n"));
	}
	return "";
}

template<typename A1,typename A2,typename A3,typename A4,typename A5>
inline static CStringW FormatStr(const wchar_t* formatStr,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5)
{
	const int size = _SIMPLE_STR_MAX;
	wchar_t s[size];
	HRESULT rc = StringCchPrintfW(s,size,formatStr,a1,a2,a3,a4,a5); 
	if (rc == S_OK)
	{
		return s;
	}
	else if (STRSAFE_E_INVALID_PARAMETER)
	{
		OutputDebugString(_T("������ � StringCchPrintf: STRSAFE_E_INVALID_PARAMETER\n"));
	}
	else if (STRSAFE_E_INSUFFICIENT_BUFFER)
	{
		OutputDebugString(_T("������ � StringCchPrintf: STRSAFE_E_INSUFFICIENT_BUFFER\n"));
	}
	else
	{
		TCHAR errNumStr[265];
#		ifdef _UNICODE
		{
			_itow_s((int)rc,errNumStr,16);
		}
#		else
		{
			_itoa_s((int)rc,errNumStr,16);
		}
#		endif
		OutputDebugString(_T("����������� ������ � StringCchPrintf: HRESULT: 0x"));
		OutputDebugString(errNumStr);
		OutputDebugString(_T("\n"));
	}
	return L"";
}



















inline static CStringA FormatTime_ymd_HMD(const CStringA& f_1,const CStringA& f_2,
										  const COleDateTime& t)
{
	CStringA tStr_1 = FormatStr(f_1
						,t.GetYear()
						,t.GetMonth()
						,t.GetDay()
						);
	//
	CStringA tStr_2 = FormatStr(f_2
						,t.GetHour()
						,t.GetMinute()
						,t.GetSecond()
						);
	//
	CStringA tStr = tStr_1 + tStr_2; 
	return tStr; 
}

inline static CStringW FormatTime_ymd_HMD(const CStringW& f_1,const CStringW& f_2,
										  const COleDateTime& t)
{
	CStringW tStr_1 = FormatStr(f_1	
						,t.GetYear()
						,t.GetMonth()
						,t.GetDay()
						);
	//
	CStringW tStr_2 = FormatStr(f_2
						,t.GetHour()
						,t.GetMinute()
						,t.GetSecond()
						);
	//
	CStringW tStr = tStr_1 + tStr_2; 
	return tStr; 
}
