/*
 SmartCommonCtx.h : ����������� ������ ��������� CommonCtx.

 $Name: work1 $
 $Revision: 1.1.2.1 $
 $Date: 2008/10/10 15:12:24 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

// ATL
//
#include <atlstr.h>

namespace  { 



class CommonCtxInfo 
{
public:
	// ===========================================================================================
	// ���������� �� ��������� ��������� 
	// ----------------------

	// �������� ���������� ���������
	static CString GetEventSourceName() { return _T("All"); }

	// ����������, ������������ ��������� ���������
	static CString GetFacilityName() { return _T("Slot"); }

	// ���������� ��� ������
	static HRESULT GetErrorCode() { return 1; }

	// ���������� ��� ��������������
	static HRESULT GetWarningCode() { return 2; }
};

template<template<class> class _ErrorHandling>
class CommonCtx : public _ErrorHandling<CommonCtxInfo>
{
};



} // namespace  
