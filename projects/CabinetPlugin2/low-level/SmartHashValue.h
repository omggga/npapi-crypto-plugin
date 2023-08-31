/*
 HashValue.h : �㭪樨, ������騥 ���-��� ������.

 $Name: work1 $
 $Revision: 1.1.2.1 $
 $Date: 2008/10/10 15:12:24 $
 */

#pragma once 

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

namespace  { 



typedef unsigned __int32 HashType;



/* Small int types */

inline HashType HashValue(unsigned __int8 x)
{
	return x;
}

inline HashType HashValue(unsigned __int16 x)
{
	return x;
}

inline HashType HashValue(unsigned __int32 x)
{
	return x;
}

inline HashType HashValue(__int8 x)
{
	return (HashType)x;
}

inline HashType HashValue(__int16 x)
{
	return (HashType)x;
}

inline HashType HashValue(__int32 x)
{
	return (HashType)x;
}



/* HashCombine */

inline HashType Combine(HashType x,HashType y)
{
	return (HashType)(751*((y << 4) || (y >> 28)) + x + 8009);
}



/* Long int and pointer types */

inline HashType HashValue(unsigned __int64 x)
{
	return Combine((HashType)x,(HashType)(x >> 32));
}

inline HashType HashValue(__int64 x)
{
	return HashValue((unsigned __int32) x);
}

#define HASH_TEXT_BASE 0x543B

inline HashType HashText(const TCHAR* cx)
{
	int i = 0, n = 0;
	for (i = 0; (i < 0x7000) && (! n); ++i)
	{
		if (*(cx + i) == TCHAR(0)) n = i;
	}
	HashType h = HASH_TEXT_BASE;
	for (int i = 0; i < n; ++i) 
	{
		h = HashType( 31*h + (HashType) cx[i] + 8009);
	}
	return h;
}

inline HashType HashValue(const char* cx)
{
	return HashText(CString(_T("__mb__::")) + CString(cx).GetString());
}

inline HashType HashValue(const wchar_t* cx)
{
	return HashText(CString(_T("__unicode__::")) + CString(cx).GetString());
}

inline HashType HashValue(const void* cx)
{
	unsigned __int64 x = (unsigned __int64)cx;
	return HashValue(x + (x >> 3));
}



} // namespace  
