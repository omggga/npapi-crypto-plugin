/*
 SmartWrapper.h : ������ CComPtr, ������������ ����������.

 $Name: work1 $
 $Revision: 1.1.2.3 $
 $Date: 2008/10/16 07:09:28 $

 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include "SmartException.h"

namespace 
{
	// ----
	// ComWrapper 

	template<class _ComObjectInterface>
	class ComWrapper
	{
	public:
		typedef _ComObjectInterface ComInterface;

	protected:
		typedef ComWrapper<ComInterface> Wrapper;

	protected:
		mutable CComPtr<ComInterface> m_p;

	public:
		virtual ~ComWrapper()
		{
		}

		inline virtual void Dispose()
		{
			if (m_p)
			{
				m_p.Release();
			}
		}

		ComWrapper()
		{
		}

		ComWrapper(ComInterface* pObject)
		{
			InitialAssignTo(pObject);
		}

		ComWrapper(const ComWrapper& other)
		{
			InitialAssignTo(other.m_p);
		}

		inline ComInterface* operator =(ComInterface* pObject)
		{
			AssignTo(pObject);
			return pObject;
		}

		inline const ComWrapper& operator =(const ComWrapper& other)
		{
			AssignTo(other);
			return other;
		}

		inline void InitialAssignTo(const ComWrapper& other)
		{
			InitialAssignTo(other.m_p);
		}

		inline void AssignTo(const ComWrapper& other)
		{
			Dispose();
			InitialAssignTo(other);
		}

		inline void InitialAssignTo(ComInterface* pObject)
		{
			try
			{
				if (pObject) m_p.Attach(CComQIPtr<ComInterface>(pObject).Detach());
			}
			_Catch()
		}

		inline void AssignTo(ComInterface* pObject)
		{
			Dispose();
			InitialAssignTo(pObject);
		}

		// ������ ����������

		inline operator ComInterface*()
		{
			return m_p.operator ComInterface*();
		}

		template<class _ComInterface>
		inline _ComInterface* QueryComInterface() // new reference 
		{	
			if (!m_p) 
			{
				return 0;
			}
			else
			{
				return CComQIPtr<_ComInterface>(m_p).Detach();
			}
		}

		template<class _ComInterface>
		inline _ComInterface* QueryComInterfaceIfSet() // new reference 
		{
			if (! m_p) 
			{
				throw MethodError(E_POINTER);
			}
			else
			{
				return CComQIPtr<_ComInterface>(m_p).Detach();
			}
		}

		inline bool IsEmpty() const
		{
			return ! m_p;
		}

		inline void AssertObjectNotEmpty()
		{
			if (! m_p) throw ObjectIsEmpty(); 
		}
	};

} // namespace 
