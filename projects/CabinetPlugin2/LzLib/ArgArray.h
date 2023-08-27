#ifndef __LZ_ARGARRAY_H__
#define __LZ_ARGARRAY_H__

#pragma once

#include <strsafe.h>
#include <atlcoll.h>

namespace Lz {

class ArgArrayVector;

class ArgArray
{
typedef CAutoVectorPtr<TCHAR> _PtrClass;
typedef CAtlArray< _PtrClass, CAutoVectorPtrElementTraits<TCHAR> > _ArrayClass;
protected:
	_ArrayClass m_Array;

public:
	ArgArray() {}

	//ArgArray(ArgArray& args) // copy constructor
	//{
	//	for(UINT i = 0; i < args.m_Array.GetCount(); i++)
	//		m_Array.Add(args.m_Array.GetAt(i));
	//}

	size_t GetCount() { return m_Array.GetCount(); }

	ArgArray& Append(LPCTSTR sz)
	{
		_PtrClass ptr;
		size_t cch;
		
		if( sz && *sz && SUCCEEDED(::StringCchLength(sz, STRSAFE_MAX_CCH, &cch)) )
		{
			cch++;
			ptr.Allocate(cch);
			::StringCchCopy(ptr, cch, sz);
		}

		m_Array.Add(ptr);

		return (*this);  
	}

	ArgArray& operator %(LPCTSTR sz)
	{
		return Append(sz);  
	}

	friend class ArgArrayVector;
};

class ArgArrayVector
{
typedef CAutoVectorPtr<LPCTSTR> _PtrClass;

protected:
	_PtrClass m_apVector;
	size_t m_nCount;

	void Init(ArgArray& args)
	{
		m_nCount = args.GetCount();
		if( m_nCount > 0 )
		{
			m_apVector.Allocate(m_nCount);

			for(UINT i = 0; i < m_nCount; i++)
				m_apVector.m_p[i] = args.m_Array[i];
		}
	}

public:

	ArgArrayVector(ArgArray& args)
	{
		Init(args);
	}

	ArgArrayVector(ArgArray* pArgs) : m_nCount(0)
	{
		if( pArgs )
			Init(*pArgs);
	}

	size_t GetCount() { return m_nCount; }

	operator LPCTSTR*() { return m_apVector; }
};

template<class T>
class AutoArgArray
{
protected:
	CAutoPtr<ArgArray> m_apArgArray;

	void CreateArgArray()
	{
		if( !m_apArgArray )
			m_apArgArray.Attach(new ArgArray);
	}

public:

#ifndef UNICODE
	T& operator %(LPCWSTR sz)
	{
		CreateArgArray();

		CAtlStringA str(sz);

		m_apArgArray->Append((LPCTSTR)str);

		return *((T*)this);  
	}
#endif // #ifndef UNICODE

	T& operator %(LPCTSTR sz)
	{
		CreateArgArray();

		m_apArgArray->Append(sz);

		return *((T*)this);  
	}

	T& operator %(UINT n)
	{
		CreateArgArray();

		TCHAR pstr[20];
		::StringCchPrintf(pstr, 20, _T("%u"), n);

		m_apArgArray->Append(pstr);

		return *((T*)this);  
	}


	ArgArray* GetArgArray() { return m_apArgArray; }
};


}; // namespace Lz

#endif // __LZ_ARGARRAY_H__
