/*
 Synchronization.h : �������� ������������ � �������������.

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
#include <atlbase.h>
#include <atlalloc.h>

// 
//
#include "SmartVeryLowLevel.h"
#include "SmartMemoryMgr.h"

// TODO: !!! ProtocolSysMsg
#define SLOT_SYNC_ERROR E_ACCESSDENIED
#define SLOT_SYNC_WARNING E_ACCESSDENIED

namespace  { 



	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����� SynchronizationCtx

	// API-�������� �������, ���������� �� �������� � ��������� ����������

	class SynchronizationCtx : public SimpleErrorHandling<SynchronizationCtx>
	{
	public:
		// ==============================================================================================
		// ���������� �� ��������� ��������� 
		// ----------------------

		// �������� ���������� ���������
		static CString GetEventSourceName() { return _T("Synchronization"); }

		// ����������, ������������ ��������� ���������
		static CString GetFacilityName() { return _T("Slot"); }

		// ���������� ��� ������
		static HRESULT GetErrorCode() { return SLOT_SYNC_ERROR; }

		// ���������� ��� ��������������
		static HRESULT GetWarningCode() { return SLOT_SYNC_WARNING; }

		// ==============================================================================================
		// ��������� ���������� ������� 
		// ----------------------	

		// �����-allocator
		typedef SmartMalloc<SynchronizationCtx,SmartHeap> Allocator;

		// ������, �� �����-allocator
		Allocator& GetAllocator() { return Container<Allocator>(); }

		// ����������� ������ Heap
		static SIZE_T GetHeapMinSize() { return 0; }

		// ������������ ������ Heap
		static SIZE_T GetHeapMaxSize() { return 0; }

		// ��������� ������ ������������?
		static bool DoesHeapRequireLowFragmentation() { return true; }

		// ��������� ���������������� ������ � Heap?
		static bool DoesHeapRequireSerialize() { return true; }
	};



	#define SyncPtr SimplePtr



	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
	// ������� ����������                        //
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

	// ����������� Timeout �� ��������� (� msec)
	#define MINIMAL_SYNC_TIMEOUT 10

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����� ScopeLocker

	// ����������� ������� --- ������� ����� ��������, �������������� "���������� ���������".
	// ����� ����� ���������, ���������� ���������.
	// ScopeLocker --- ���������� ���������� ����������.
	// � ������� �� ����� ScopeLock, ������ ����� ������������ �� ��������� ������,
	// ��� ��� � ������ ��������� ������������ ������ ������, ����������� �� ScopeLocker.

	class ScopeLocker : private TracePoint
	{
	protected:
		// ����������� ������� ����� (������ ��������� ��������� ������)
		ScopeLocker(TRACE_POINT_INI_ARGS) : TracePoint(TRACE_POINT_SEQ), m_state(S_OK)
		{ 
		}

		// ��������� ������������ �������� ����� ���������� ��������� �������� 
		// ���������� � ������������ ������.
		HRESULT m_state;

		const TracePoint& GetTracePoint() const
		{
			return *this;
		}

	public:
		// ����������� ���������� ������������ ������ � ������� ����������� ������, ������������ ScopeLocker
		virtual ~ScopeLocker() 
		{ 
			/*
	#		define _TRACE_1 m_TracePointSource,m_TracePointLine,m_TracePointCodeFile
			TRACE_LOG_(_T("Removing ScopeLocker..."),_TRACE_1);
			*/
		}

		// ������ � ��������� ������������ ��������.
		virtual HRESULT& GetLockerState()
		{
			return m_state;
		}
	};

	typedef SyncPtr<ScopeLocker> ScopeLockerPtr;

	// ���������������� ����� "���������� ���������".
	// ����� ����� ���������, ���������� ���������.
	class ScopeLock; 







	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
	// ������ Mutex'��                           //
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����� BasicMutex 

	// �������� ����� Mutex'��

	class BasicMutex
	{
		friend ScopeLock;

	protected:
		// ����������� ������� ����� (������ ��������� ��������� ������)
		BasicMutex() : m_state(S_OK)
		{ 
		}

		virtual ~BasicMutex() { }

		// ���������� ����� ScopeLocker, ���������� ������� Mutex'� � ������ �������� dwTimeOut
		virtual ScopeLockerPtr GetScopeLocker(DWORD dwTimeOut,TRACE_POINT_INI_ARGS) =0;

		// ��������� Mutex'�:
		// S_OK		--- ���������� ���������, ����� ��������������
		// ������	--- ��������� ���������
		//
		HRESULT m_state;

		// ������ � ��������� Mutex'�
		HRESULT& GetMutexState()
		{
			return m_state;
		}

		// ������ � ��������� Mutex'�
		HRESULT SetMutexState(HRESULT rc)
		{
			GetMutexState() = rc;
			return rc;
		}
	};

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����� AbsoluteMutex 

	// �������������� Mutex --- ������ ��������� �����������, �� ��� ��� ���� Mutex �� �����������.
	// (����� �������� ����������� --- �������� ������� ��� ���������� ����������.)

	class AbsoluteMutex : public BasicMutex
	{
	protected:
		// ����������� ������� ����� (������ ��������� ��������� ������)
		AbsoluteMutex() { }

	public:
		virtual ~AbsoluteMutex() { }
	};

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����� RecursiveMutex 

	// ����������� Mutex --- ������ ����������� ��� ���� �������, �������� �� ������-���������,
	// �� �����-�������� ����� ����������� ������������ ���������� ������� Mutex'�,
	// � ��� ����� ��� ����������� ������ ����� ������� �������.
	// (����� �������� ����������� --- �������� ������� ��� ���������� ����������.)

	class RecursiveMutex : public BasicMutex
	{
	protected:
		// ����������� ������� ����� (������ ��������� ��������� ������)
		RecursiveMutex() { }

	public:
		virtual ~RecursiveMutex() { }
	};

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����� TryMutex 

	// Mutex, �������������� "������� ����������":
	// ���� Mutex ��������, �� ����������� � �������� Mutex'�� ���������� �������� ������,
	// ���� Mutex ������������, ������������ ���, ��������������� � ���, ��� Mutex �����.
	// TryMutex �� ��������� ���������� ����������� Mutex'� � ������ �������, �� ����
	// ���������� ������ ������� Mutex ������������ ����� (timeout), �� ��������� 0.1�.
	// (����� �������� ����������� --- �������� ������� ��� ���������� ����������.)

	class TryMutex : public BasicMutex
	{
	protected:
		// ����������� ������� ����� (������ ��������� ��������� ������)
		TryMutex() { }

	public:
		virtual ~TryMutex() { }
	};






	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ������ Mutex'�, �� ������������ ����������� ���������� 

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����� EmptyAMutex

	// ������ AbsoluteMutex

	class EmptyAMutex : public AbsoluteMutex
	{
		typedef SyncPtr<EmptyAMutex> EmptyAMutexPtr;

	public:
		// ���������� ���������� ScopeLocker
		class MutexSLocker : public ScopeLocker
		{
		public:
			MutexSLocker(EmptyAMutex& ,TRACE_POINT_INI_ARGS) : ScopeLocker(TRACE_POINT_SEQ)
			{
			}
		};
		// ������ ����� ScopeLocker Mutex'�
		ScopeLockerPtr GetScopeLocker(DWORD // dwTimeOut
			,TRACE_POINT_INI_ARGS)
		{
			ScopeLockerPtr locker = new MutexSLocker(*this,TRACE_POINT_SEQ);
			return locker;
		}
		// ����� ��������� ������� ��������������� Mutex'�
		static EmptyAMutexPtr Get()
		{
			EmptyAMutexPtr mutex = new EmptyAMutex();
			return mutex;
		}
	};

	typedef SyncPtr<EmptyAMutex> EmptyAMutexPtr;

	// ������ RecursiveMutex

	class EmptyRMutex : public RecursiveMutex
	{
		typedef SyncPtr<EmptyRMutex> EmptyRMutexPtr;

	public:
		// ���������� ���������� ScopeLocker
		class MutexSLocker : public ScopeLocker
		{
		public:
			MutexSLocker(EmptyRMutex& ,TRACE_POINT_INI_ARGS) : ScopeLocker(TRACE_POINT_SEQ)
			{
			}
		};
		// ������ ����� ScopeLocker Mutex'�
		ScopeLockerPtr GetScopeLocker(DWORD // dwTimeOut
			,TRACE_POINT_INI_ARGS)
		{
			ScopeLockerPtr locker = new MutexSLocker(*this,TRACE_POINT_SEQ);
			return locker;
		}
		// ����� ��������� ������� ��������������� Mutex'�
		static EmptyRMutexPtr Get()
		{
			EmptyRMutexPtr mutex = new EmptyRMutex();
			return mutex;
		}
	};

	typedef SyncPtr<EmptyRMutex> EmptyRMutexPtr;

	// ������ TryMutex

	class EmptyTryMutex : public TryMutex
	{
		typedef SyncPtr<EmptyTryMutex> EmptyTryMutexPtr;

	public:
		// ���������� ���������� ScopeLocker
		class MutexSLocker : public ScopeLocker
		{
		public:
			MutexSLocker(EmptyTryMutex& ,TRACE_POINT_INI_ARGS) : ScopeLocker(TRACE_POINT_SEQ)
			{
			}
		};
		// ������ ����� ScopeLocker Mutex'�
		ScopeLockerPtr GetScopeLocker(DWORD // dwTimeOut
			,TRACE_POINT_INI_ARGS)
		{
			ScopeLockerPtr locker = new MutexSLocker(*this,TRACE_POINT_SEQ);
			return locker;
		}
		// ����� ��������� ������� ��������������� Mutex'�
		static EmptyTryMutexPtr Get()
		{
			EmptyTryMutexPtr mutex = new EmptyTryMutex();
			return mutex;
		}
	};

	typedef SyncPtr<EmptyTryMutex> EmptyTryMutexPtr;






	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����������� Mutex'� 

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����� StdAMutex

	// ����������� ���������� AbsoluteMutex

	class StdAMutex : public AbsoluteMutex, virtual private SynchronizationCtx
	{
	public:
		HANDLE m_hMutex;

	protected:
		bool m_bLocked;

		HRESULT AcquireHMutex()
		{
			m_hMutex = CreateMutex(NULL,TRUE,NULL);
			if (m_hMutex == 0)
			{
				HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
				GetMutexState() = rc;
				return SignalError_(rc);
			}
			return S_OK;
		}

	public:
		HRESULT Lock(TRACE_POINT_INI_ARGS)
		{
			TRACE_POINT_NOT_USED();
			//
			HRESULT rc = AcquireHMutex();
			if (rc != S_OK)
			{
				DisplaySysMsg_(rc);
			}
			/*
				DWORD userNameSize = 1024;
				CHeapPtr<TCHAR> userName;
				userName.Allocate(userNameSize);
				GetUserName((TCHAR*)userName,&userNameSize);
				CString echo;
				echo = FormatStr(_T("user is locking mutex %d: %s"), (int)m_hMutex, (const TCHAR*)userName );
				TRACE_LOG(echo);
				//*/
			DWORD dwWaitResult = WaitForSingleObject(m_hMutex,INFINITE);
			switch (dwWaitResult)
			{
				HRESULT rc;
				//
				case WAIT_OBJECT_0:
					m_bLocked = true;
	#				ifdef NORMAL_TRACKING
					if (ShowActivity()) ATLTRACE("AMutex(%d) : locked\n",m_hMutex);
	#				endif
					break;
					//
				case WAIT_TIMEOUT:
					return SetMutexState(TextAlarm_(_T("WaitForSingleObject => WAIT_TIMEOUT")));
					break;
					//
				case WAIT_ABANDONED:
					return SetMutexState(TextAlarm_(_T("WaitForSingleObject => WAIT_ABANDONED")));
					break;
					//
				case WAIT_FAILED:
					rc = GetLastError();
					AlarmExplained_(_T("WaitForSingleObject => WAIT_FAILED"),rc);
					//
				default:
					CString echo;
					echo = FormatStr(_T("����������� ��������� ���������� ������� WaitForSingleObject => %d"), 
						(int)dwWaitResult ); 
					return SetMutexState(TextAlarm_(echo));
			}
			return S_OK;
		}

		HRESULT Release()
		{
			TRACE_LOG("Releasing...");
			if (! m_bLocked)
			{
				/// TextAlarm_(_T("����� �� ������ ���������� � ���������, ����� Mutex �� ������������!"));
				return S_OK;
			}
			//
			if (! ReleaseMutex(m_hMutex)) 
			{ 
				HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
				return SetMutexState(AlarmExplained_(_T("������ ��� ������������ Mutex'�"),rc));
			}
			m_bLocked = false;
			return S_OK;
		}

	public:
		StdAMutex() : m_hMutex(0), m_bLocked(false)
		{
		}

		StdAMutex& operator =(const StdAMutex& )
		{
			TRACE_LOG(_T("������ ���������� ������ ���� StdAMutex"));
			m_hMutex = 0;
			m_bLocked = false;
		}

		virtual ~StdAMutex()
		{
			if (m_bLocked)
			{
				Release();
			}
		}

		// ������� ���������� Mutex'�

		class MutexSLocker : public ScopeLocker
		{
			StdAMutex& m_aMutex;
			//
		public:
			// �����������, ������������ ����������
			MutexSLocker(StdAMutex& aMutex,TRACE_POINT_INI_ARGS) : ScopeLocker(TRACE_POINT_SEQ), m_aMutex(aMutex)
			{
				/*
				CString echo;
				echo = FormatStr(_T("Lockin mutex %d"), (int)aMutex.m_hMutex );
				TRACE_LOG_(echo,TRACE_POINT_SEQ);
				*/
				HRESULT rc = m_aMutex.Lock(TRACE_POINT_SEQ);
				if (rc != S_OK)
				{
					GetLockerState() = rc;
				}
			}
			// ���������� �����������
			inline MutexSLocker& operator =(const MutexSLocker& other)
			{
				m_aMutex = other.m_aMutex;
			}
			// ����������, ��������� ����������
			~MutexSLocker()
			{
				//// TRACE_LOG1(_T("Removing (StdAMutex %d)..."),m_aMutex.m_hMutex);
				//
				HRESULT rc = m_aMutex.Release();
				if (rc != S_OK)
				{
					TextAlarm_(_T("�� ������� ��������� ���������� ����������"));
				}
			}
		};
		ScopeLockerPtr GetScopeLocker(DWORD // dwTimeOut
			,TRACE_POINT_INI_ARGS)
		{
			ScopeLockerPtr locker = new MutexSLocker(*this,TRACE_POINT_SEQ);
			return locker;
		}
	};



	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����� StdRMutex

	// ����������� ���������� ResursiveMutex

	class StdRMutex : public RecursiveMutex, virtual private SynchronizationCtx
	{
	protected:
		HRESULT m_state;

		CRITICAL_SECTION m_CS;

		bool m_bCSInited;

		HRESULT AcquireCriticalSection()
		{
			InitializeCriticalSection(&m_CS);
			m_bCSInited = true;
			return S_OK;
		}

		HRESULT Lock()
		{
			if (m_state != S_OK)
			{
				TextAlarm_(_T("������ � ����������� ���������"));
			}
			//
			HRESULT rc = AcquireCriticalSection();
			if (rc != S_OK)
			{
				m_state = rc;
				return rc;
			}
			//
			EnterCriticalSection(&m_CS);
			//
			return S_OK;
		}

		HRESULT Release()
		{
			// TRACE_LOG("Releasing... (2)");
			if (m_state != S_OK)
			{
				TextAlarm_(_T("������ � ����������� ���������"));
			}
			//
			HRESULT rc = AcquireCriticalSection();
			if (rc != S_OK)
			{
				TextAlarm_(_T("������!"));
				m_state = rc;
				return S_OK; /// rc;
			}
			//
			LeaveCriticalSection(&m_CS);
			//
			return S_OK;
		}

	public:
		StdRMutex() : m_state(S_OK), m_bCSInited(false)
		{
		}

		virtual ~StdRMutex()
		{
			if (m_bCSInited)
			{
				DeleteCriticalSection(&m_CS);
			}
		}

		StdRMutex& operator =(const StdRMutex& )
		{
			TRACE_LOG(_T("������ ���������� ������ ���� StdRMutex"));
			m_state = E_UNEXPECTED;
			m_bCSInited = false;
		}

		// ������� ���������� Mutex'�

		class MutexSLocker : public ScopeLocker
		{
			StdRMutex& m_rMutex;
			//
		public:
			// �����������, ������������ ����������
			MutexSLocker(StdRMutex& rMutex,TRACE_POINT_INI_ARGS) : ScopeLocker(TRACE_POINT_SEQ), m_rMutex(rMutex)
			{
				HRESULT rc = m_rMutex.Lock();
				if (rc != S_OK)
				{
					GetLockerState() = rc;
				}
			}
			// ���������� �����������
			inline MutexSLocker& operator =(const MutexSLocker& other)
			{
				m_rMutex = other.m_rMutex;
			}
			// ����������, ��������� ����������
			~MutexSLocker()
			{
				HRESULT rc = m_rMutex.Release();
				if (rc != S_OK)
				{
					TextAlarm_(_T("�� ������� ��������� ���������� ����������"));
				}
			}
		};
		ScopeLockerPtr GetScopeLocker(DWORD // dwTimeOut
			,TRACE_POINT_INI_ARGS)
		{
			ScopeLockerPtr locker = new MutexSLocker(*this,TRACE_POINT_SEQ);
			return locker;
		}
	};



	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����� StdTryMutex

	// ����������� ���������� TryMutex

	class StdTryMutex : public TryMutex, virtual private SynchronizationCtx
	{
	protected:
		HANDLE m_hMutex;

		bool m_bLocked;

		HRESULT AcquireHMutex()
		{
			m_hMutex = CreateMutex(NULL,FALSE,NULL);
			if (m_hMutex == 0)
			{
				HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
				GetMutexState() = rc;
				SignalError_(rc);
			}
		}

		HRESULT Lock(DWORD dwTimeOut)
		{
			DWORD dwWaitResult = WaitForSingleObject(m_hMutex,dwTimeOut);
			switch (dwWaitResult)
			{
				HRESULT rc;
				//
				case WAIT_OBJECT_0:
					m_bLocked = true;
	#				ifdef NORMAL_TRACKING
					if (ShowActivity()) ATLTRACE("AMutex(%d) : locked\n",m_hMutex);
	#				endif
					break;
					//
				case WAIT_TIMEOUT:
					return SetMutexState(TextAlarm_(_T("WaitForSingleObject => WAIT_TIMEOUT")));
					break;
					//
				case WAIT_ABANDONED:
					return SetMutexState(TextAlarm_(_T("WaitForSingleObject => WAIT_ABANDONED")));
					break;
					//
				case WAIT_FAILED:
					rc = GetLastError();
					AlarmExplained_(_T("WaitForSingleObject => WAIT_FAILED"),rc);
					//
				default:
					CString echo = FormatStr(
						_T("����������� ��������� ���������� ������� WaitForSingleObject => %d"), (int)dwWaitResult );
					return SetMutexState(TextAlarm_(echo));
			}
			return S_OK;
		}

		HRESULT Release()
		{
			TRACE_LOG("Releasing... (3)");
			if (! m_bLocked)
			{
				TextAlarm_(_T("����� �� ������ ���������� � ���������, ����� Mutex �� ������������!"));
				return S_OK;
			}
			//
			if (! ReleaseMutex(m_hMutex)) 
			{ 
				HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
				return SetMutexState(AlarmExplained_(_T("������ ��� ������������ Mutex'�"),rc));
			}
		}

	public:
		StdTryMutex() : m_hMutex(0), m_bLocked(false)
		{
		}

		StdTryMutex& operator =(const StdTryMutex& )
		{
			TRACE_LOG(_T("������ ���������� ������ ���� StdTryMutex"));
			m_hMutex = 0;
			m_bLocked = false;
		}

		virtual ~StdTryMutex()
		{
			if (m_bLocked)
			{
				Release();
			}
		}

		// ������� ���������� Mutex'�

		class MutexSLocker : public ScopeLocker
		{
			StdTryMutex& m_aMutex;
			//
			DWORD m_dwTimeOut;
			//
		public:
			// �����������, ������������ ����������
			MutexSLocker(StdTryMutex& aMutex,DWORD dwTimeOut,TRACE_POINT_INI_ARGS) 
				: ScopeLocker(TRACE_POINT_SEQ), m_aMutex(aMutex), m_dwTimeOut(dwTimeOut)
			{
				HRESULT rc = m_aMutex.Lock(m_dwTimeOut);
				if (rc != S_OK)
				{
					GetLockerState() = rc;
				}
			}
			// ���������� �����������
			inline MutexSLocker& operator =(const MutexSLocker& other)
			{
				m_aMutex = other.m_aMutex;
				m_dwTimeOut = other.m_dwTimeOut;
			}
			// ����������, ��������� ����������
			~MutexSLocker()
			{
				HRESULT rc = m_aMutex.Release();
				if (rc != S_OK)
				{
					TextAlarm_(_T("�� ������� ��������� ���������� ����������"));
				}
			}
		};

		ScopeLockerPtr GetScopeLocker(TRACE_POINT_INI_ARGS)
		{
			TextAlarm_(_T("������� ���� ��������� Timeout"));
			ScopeLockerPtr locker = new MutexSLocker(*this,INFINITE,TRACE_POINT_SEQ);
			return locker; // minimal Timeout
		}
		
		ScopeLockerPtr GetTimeOutScopeLocker(DWORD dwTimeOut,TRACE_POINT_INI_ARGS)
		{
			ScopeLockerPtr locker = new MutexSLocker(*this,dwTimeOut,TRACE_POINT_SEQ);
			return locker;
		}
	};






	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
	// ���������������� ����������               //
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����� ScopeLock

	// ���������������� ����� "���������� ���������".
	// ���� ���������� ������������ ����������� ������� �����. ����� ��������� ���������, 
	// ���������� ���������. ��������� ��������� �������� ���������� ������ � ������������,
	// ����� ������������� ����������, ������� ��������� ���������� ��������� ����������
	// (������� ��� ��� ������ ��������� ������?).

	class ScopeLock
	{
	protected:
		// Timeout, � ������� �������� �� ������� Mutex.
		// ��������� ���� Mutex'�� ���������� ���� ��������.
		DWORD m_dwTimeOut;

		// ����������� ���������� --- ��������� ������, ������������ �� ScopeLocker
		ScopeLockerPtr m_SLocker;

	public:
		// ��������� ������ ��������� Mutex.
		// ��������� TRACE_POINT_ARGS ������ ����� �������� ���������� ����������.
		ScopeLock(BasicMutex& someMutex,DWORD dwTimeOut,TRACE_POINT_INI_ARGS) : m_dwTimeOut(dwTimeOut)
		{
			m_SLocker = someMutex.GetScopeLocker(dwTimeOut,TRACE_POINT_SEQ);
		}
		virtual ~ScopeLock()
		{
			m_SLocker.Free();
		}
		bool Release()
		{
			TRACE_LOG("Releasing... (5)");
			if (m_SLocker)
			{
				m_SLocker.Free();
				return true;
			}
			else return false;
		}

		// ==============================================================================================
		// ��������� 
		// ----------------------

		inline HRESULT GetState()
		{
			return m_SLocker->GetLockerState();
		}
		inline bool IsReady()
		{
			return bool(GetState() == S_OK);
		}
	};

	// ����� ������ ���������� ���������
	//
	#define ScopeLock_(mutex) ScopeLock _lock(mutex,INFINITE,TRACE_POINT)
	#define ScopeLockWithTimeOut_(mutex,dwTO) ScopeLock _lock(mutex,dwTO,TRACE_POINT)
	//
	// ������, ������������ ����������� ����������� ���������� ���������. ������:
	// {
	//     Slock_();
	// }
	//
	#define RLock_() ScopeLock _lock(GetFamilyRMutex(),INFINITE,TRACE_POINT)
	#define RLockWithTimeOut_(dwTO) ScopeLock _lock(GetFamilyRMutex(),dwTO,TRACE_POINT)
	//
	#define SLock_() {} // ScopeLock _lock(Context::GetFamilyRMutex(),INFINITE,TRACE_POINT)
	#define SLockWithTimeOut_(dwTO) ScopeLock _lock(Context::GetFamilyRMutex(),dwTO,TRACE_POINT)

	// ������, ������������ ����������� �������� ���������� ���������.
	//
	#define ALock_() SLock_()
	#define ALockWithTimeOut_(dwTO) SLockWithTimeOut_(dwTO)






	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
	// ���������� �������� ������������          //
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����� SimpleLocking

	// ���������� �������� ������������

	template<class _Object>
	class Locking
	{
	public:
		static StdAMutex& GetFamilyAMutex()
		{
			static StdAMutex s_aMutex;
			return s_aMutex;
		}

		static StdRMutex& GetFamilyRMutex()
		{
			static StdRMutex s_rMutex;
			return s_rMutex;
		}
	};



} // namespace  
