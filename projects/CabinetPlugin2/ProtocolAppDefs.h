

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif



// ----
// ������ Window etc.

#ifndef STRICT
#define STRICT
#endif

#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0500		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
#define _WIN32_WINNT 0x0502	// Change this to the appropriate value to target Windows 2000 or later.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			
#define _WIN32_IE 0x0600	// IE 6 ��� ����� ������� ������.
#endif







// ----
// ���������� C++

#pragma warning(disable: 4100 4127 4995)



// ----
// ��������� ������� 

#define _PROVIDE_TRACE_INFO


