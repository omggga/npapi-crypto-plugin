/*
 VeryLowLevel.h : ����������� ����������� ��� ������������� � ��������� �������.

 $Name: work1 $
 $Revision: 1.1.2.1 $
 $Date: 2008/10/10 15:12:24 $

 ��������!   � ������� ������ ������������ ������� �����������, ��������� 
 �� ����������� ��������� �������������� ��������.

 ������������ ������:

 LowLevelError			���������� �� ���� CAtlException
 SimplePtr				������� ������������� ���������

 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

// ATL
//
#include <atlexcept.h>

// 
//
#include "AtlX.h"
#include "TracePoint.h"
#include "SmartCommonCtx.h"
#include "SmartSimpleErrorHandling.h"

namespace  { 



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� LowLevelError

struct LowLevelError : public CAtlException
{
	template<class A1>
	LowLevelError(A1 a1) : CAtlException(a1)
	{
	}
};



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� SimplePtr

// "������������" (�������������) ��������� ��� ������������� �������� ������� ������:
// ������������� � ���� ������ ����������� ���, ��� ������, ������������ � �����������
// ������� ���������������� ����������, �� ����� �� ������������, ��������� �� ��� �� ����������.
// ������� ��� ��������� ��������� ����� ������������ �������������� ����� SimplePtr.
// ����� ������������ ��������: Syncronization
// (�� ���� ����� ���������� �� ����������������� ������ ������������� ��������.)

template<class _P>
class SimplePtr 
{
protected:
	typedef CommonCtx<SimpleErrorHandling> _Ctx;

	// TODO: Allocator!

	mutable _P* m_p;

public:
	inline SimplePtr() : m_p(0)
	{
	}

	inline void operator =(_P* p)
	{
		Free();
		m_p = p;
	}

	template<class _Q>
	inline void operator =(_Q* p)
	{
		Free();
		m_p = static_cast<_P*>(p);
	}

	template<class _Q>
	inline SimplePtr(_Q* p) : m_p(0)
	{
		operator =(p);
	}

	inline SimplePtr(const SimplePtr& other) : m_p(0)
	{
		operator =(other);
	}

	inline const SimplePtr& operator =(const SimplePtr& other)
	{
		Free();
		m_p = other.m_p;
		other.m_p = 0;
		return other;
	}

	template<class _Q>
	inline SimplePtr(const SimplePtr<_Q>& other) : m_p(0)
	{
		operator =(other);
	}

	template<class _Q>
	inline const SimplePtr<_Q>& operator =(const SimplePtr<_Q>& other)
	{
		Free();
		if (other.m_p)
		{
			m_p = static_cast<_P*>(other.m_p);
			other.m_p = 0;
		}
		else m_p = 0;
		return other;
	}

	inline operator bool() const
	{
		return m_p;
	}

	inline operator _P*()
	{
		// ������� ������: ��� ����������� ��������������� � ���, ��� m_p == 0
		return m_p;
	}

	inline _P* operator ->()
	{
		return operator _P*();
	}

	~SimplePtr()
	{
		Free();
	}

	inline void Free()
	{
		if (m_p)
		{
			delete m_p;
			m_p = 0;
		}
	}
}; 
// class SimplePtr



} // namespace  
