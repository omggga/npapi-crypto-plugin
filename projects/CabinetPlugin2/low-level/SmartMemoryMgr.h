/*
 SmartMemoryMgr.h : ������� ��� ���������� �������.

 $Name: work1 $
 $Revision: 1.1.2.1 $
 $Date: 2008/10/10 15:12:24 $

 ������:
 http://www.microsoft.com/rus/msdn/magazine/archive/2003-06/core_api_full.asp
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include "SmartSimpleErrorHandling.h"

// TODO: !!! ProtocolSysMsg
#define SLOT_MEMORY_ERROR E_ACCESSDENIED
#define SLOT_MEMORY_WARNING E_ACCESSDENIED
#define SLOT_MEMORY_BAD_ALLOC E_ACCESSDENIED
#define SLOT_MEMORY_ERROR E_ACCESSDENIED

namespace  {



	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����� MemoryCtx

	// API-�������� �������, ���������� �� ���������� �������

	class MemoryCtx : public SimpleErrorHandling<MemoryCtx>
	{
	public:
		// ==============================================================================================
		// ���������� �� ��������� ��������� 
		// ----------------------

		// �������� ���������� ���������
		static CString GetEventSourceName() { return _T(":memory"); }

		// ����������, ������������ ��������� ���������
		static CString GetFacilityName() { return _T(":slot"); }

		// ���������� ��� ������
		static HRESULT GetErrorCode() { return SLOT_MEMORY_ERROR; }

		// ���������� ��� ��������������
		static HRESULT GetWarningCode() { return SLOT_MEMORY_WARNING; }
	};



	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����� Heap

	// ���������: 'Heap' ������.

	class Heap
	{
	public:
		// �������� ���� ������
		virtual void* Allocate(int nBytes) =0;

		// �������� ���� ������ ������� �������
		virtual void* ReAllocate(void* p,int nBytes) =0;

		// ����������� ���� ������
		virtual HRESULT Free(void* p) =0;
	};



	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����� SmartHeap

	// ������� ��� ����������� 'Heap'.

	class SmartHeap : public Heap, virtual private MemoryCtx
	{
	protected:
		// ��������� 'Heap'
		HANDLE m_heap;

		// ������������ ������������������� 'Heap'?
		bool m_bLowFragmentation;

		// ��������� ������ ���������������� ������ � 'Heap'?
		bool m_bSerialize;

		SIZE_T m_minSize;
		
		SIZE_T m_maxSize;

		HRESULT Create()
		{
			static bool s_bNoLFHReported = false;
			//
			if (m_heap)
			{
				return S_OK;
			}
			//
			// ������
			//
			DWORD dwOptions = 0;
			if (! m_bSerialize) dwOptions = dwOptions | HEAP_NO_SERIALIZE;
			//
			m_heap = HeapCreate(dwOptions,m_minSize,m_maxSize);
			if (! m_heap)
			{
				HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
				return SignalError_(rc);
			}
			if (m_bLowFragmentation)
			{
				ULONG heapInfo = 2;
				if (! HeapSetInformation(m_heap,HeapCompatibilityInformation,&heapInfo,sizeof(heapInfo)))
				{
					// HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
					if (! s_bNoLFHReported)
					{
						// HandleError_(rc);
						DisplayText_(_T("���������� ������������ LFH, ���������� ����������� Heap"));
						s_bNoLFHReported = true;
					}
					// => ���������� ����������� Heap...
				}
			}
			return S_OK;
		}

	public:
		SmartHeap(SIZE_T minSize,SIZE_T maxSize,bool bLowFragmentation=false,bool bSerialize=true) 
			: m_heap(0), m_bLowFragmentation(bLowFragmentation), m_bSerialize(bSerialize),
			m_minSize(minSize), m_maxSize(maxSize)
		{
			if (m_bLowFragmentation)
			{
				if (! m_bSerialize)
				{
					TextAlarm_(_T("������������������� 'Heap' ������� �������� ������������������ �������"));
				}
				m_bSerialize = true;
			}
		}

		// ----
		// Heap

		// �������� ���� ������
		void* Allocate(int nBytes)
		{
			HRESULT rc = Create();
			if (rc != S_OK)
			{
				return SignalError_rv_(rc,(void*)0);
			}
			void* p = HeapAlloc(m_heap,0,(SIZE_T)nBytes);
			if (p == 0)
			{
				SystemAlarm_(SLOT_MEMORY_BAD_ALLOC);
			}
			return p;
		}

		// �������� ���� ������ ������� �������
		void* ReAllocate(void* p,int nBytes)
		{
			if (! p) return SignalError_rv_(E_POINTER,(void*)0);
			if (nBytes <= 0) return SignalError_rv_(E_INVALIDARG,(void*)0);
			//
			HRESULT rc = Create();
			if (rc != S_OK)
			{
				return SignalError_rv_(rc,(void*)0);
			}
			void* new_p = HeapReAlloc(m_heap,0,p,(SIZE_T)nBytes);
			if (new_p == 0)
			{
				SystemAlarm_(SLOT_MEMORY_BAD_ALLOC); // ���������� 0
			}
			return new_p;
		}

		// ����������� ���� ������
		HRESULT Free(void* p)
		{
			if (p == 0)
			{
				// ������� ���������
				//
				return S_OK;
			}
			if (! HeapFree(m_heap,0,p))
			{
				HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
				return SignalError_(rc);
			}
			return S_OK;
		}
	};



	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����� SmartMalloc

	// ���������� ��������� ������ � 'Heap' ��� ������ T �� ������ _Heap (��������, SmartHeap). 
	// T --- ������������ �����-��������, ������� ����� ������������ SmartMalloc, 
	//       � ����� ����������� ������, �������� ��������� ���������� �������. 

	template<class T,class _Heap>
	class SmartMalloc : virtual private MemoryCtx
	{
	protected:
		struct _HeapPtr
		{
			_Heap* m_p;

			inline _HeapPtr() : m_p(0)
			{
			}

			inline void operator =(_Heap* p)
			{
				if (m_p) delete m_p;
				m_p = p;
			}

			inline bool IsEmpty() const
			{
				return m_p == 0;
			}

			inline operator _Heap*()
			{
				return m_p;
			}

			~_HeapPtr()
			{
				if (m_p) delete m_p;
			}
		};

		inline static _Heap& AcquireHeap()
		{
			static _HeapPtr spHeap;
			//
			if (_HeapPtr.IsEmpty())
			{
				spHeap = new _Heap(
					T::GetHeapMinSize(),T::GetHeapMaxSize(),
					T::DoesHeapRequireLowFragmentation(),T::DoesHeapRequireSerialize()
					);
			}
			//
			return *((_Heap*)spHeap);
		}

	public:
		// �������� ���� ������
		inline static void* Allocate(size_t nBytes)
		{
			return AcquireHeap().Allocate(nBytes);
		}

		// �������� ���� ������ ������� �������
		inline static void* Reallocate(void* p,size_t n)
		{
			return AcquireHeap().ReAllocate(p,nBytes);
		}

		// ����������� ���� ������
		inline static void Free(void* p)
		{
			HRESULT rc = AcquireHeap().Free(p);
			if (rc != S_OK)
			{
				SignalError_(rc);
			}
		}

		/* ����������� ����������� */

		inline static void* LFAllocate(SIZE_T nBytes)
		{
			void* p = 0;
			bool done = false;
			bool first_step = true;
			while (! done)
			{
				p = Allocate(nBytes);
				if (p != 0)	
				{
					done = true;
				}
				else
				{
					CString echo;
					//
					p = Allocate(2*nBytes);
					if (p != 0)	
					{
						done = true;
					}
					else
					{
						p = Allocate(4*nBytes);
						if (p != 0)
						{
							done = true;
						}
					}
				}
				first_step = false;
			}
			return p;
		}
	};
} // namespace  
