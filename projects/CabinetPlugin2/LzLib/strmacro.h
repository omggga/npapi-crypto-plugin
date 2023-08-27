#ifndef __LZ_STRMACRO_H__
#define __LZ_STRMACRO_H__

#pragma once

#include <strsafe.h>

#define _HR2STR(hr, pstr) TCHAR pstr[12]; ::StringCchPrintf(pstr, 12, _T("%#I32x"), hr);

#endif // __LZ_STRMACRO_H__
