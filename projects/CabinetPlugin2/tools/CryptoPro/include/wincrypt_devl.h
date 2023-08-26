#ifndef WINCRYPT_DEVL_H
#define WINCRYPT_DEVL_H

#ifndef _FILETIME_
#define _FILETIME_
typedef struct _FILETIME
    {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
    } 	FILETIME;

typedef struct _FILETIME *PFILETIME;
typedef struct _FILETIME *LPFILETIME;
#endif // !_FILETIME
typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

#pragma warning( push )
#pragma warning( disable: 4201 )
#include <WinCrypt.h>
#pragma warning( pop )
#endif /* WINCRYPT_DEVL_H */
