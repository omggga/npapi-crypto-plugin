/*
 SmartInetBase.h : ����������� � ��������� ��� ������ � WinInet. 

 $Name: work1 $
 $Revision: 1.1.2.1 $
 $Date: 2008/10/10 15:12:24 $

 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


// ----
// h 

#include <wininet.h>

#include "SmartException.h"


// ----
// lib

#pragma comment(lib, "Wininet.lib" )


// ----
// �����������

#ifndef INTERNET_ERROR
#define INTERNET_ERROR(x) (HRESULT_FROM_ERROR_OF_FACILITY(x,FACILITY_INTERNET))
#endif

#ifndef LastInternetError
#define LastInternetError() MethodError(INTERNET_ERROR(GetLastError()))
#endif

#ifndef _DEFAULT_AGENT
#define _DEFAULT_AGENT (L".WebClient")
#endif

#ifndef _HTTP_STATUS_UNKNOWN
#define _HTTP_STATUS_UNKNOWN (0)
#endif
