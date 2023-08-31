/*
 SmartPtr.h : ������� ���������� ��������� smart-���������� � ����� ATL.

 ����������� ��������� �����: 

 1) SharedPtr		--- ����������� ���������
 2) SharedArray 	--- ����������� ������ � �������������� ����������� �������

 $Name: work1 $
 $Revision: 1.1.2.3 $
 $Date: 2008/10/10 15:12:24 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include "SmartSimpleErrorHandling.h"
#include "SmartCommonCtx.h"
#include "SmartSynchronization.h"

namespace  {



	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����� SmartPtrCtx

	// �������� ��������� smart-����������

	class SmartPtrCtx : public CommonCtx<SimpleErrorHandling>, public Locking<SmartPtrCtx>
	{
		// =======================================================================================
		// ��������� ���������� ������� 
		// ----------------------	

		// �����-allocator
		typedef SmartMalloc<SynchronizationCtx,SmartHeap> _Allocator;

		// ������, �� �����-allocator
		_Allocator& Allocator() { return Container<_Allocator>(); }

		// ����������� ������ Heap
		static int GetHeapMinSize() { return 0; }

		// ������������ ������ Heap
		static int GetHeapMaxSize() { return 0; }

		// ��������� ������ ������������?
		static bool DoesHeapRequireLowFragmentation() { return true; }

		// ��������� ���������������� ������ � Heap?
		static bool DoesHeapRequireSerialize() { return true; }
	};

	#define SmartPtrLock_() {} // ScopeLock _lock(SmartPtrCtx::GetFamilyRMutex(),INFINITE,TRACE_POINT)






	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����� SharedPtr --- ����������� ���������
	//
	// ������������� ������ ����������� �������� ����������.
	// ������, �� ������� ��������� CSharedPtrT ���������, ����� ������� ������ == 0.
	// ���������� ��������� ����������� ����������� ������� ������� � ������,
	// ����� ������������ ���������� �����.
	// ��� ����������� �������� ������ ��� "�������� ��������" ���������� T*
	// ����� ������������ SharedPtr<T>, � �� T* .

	struct SharedPtrData 
	{
		void* px;

		DWORD* pn;

		SharedPtrData(void* other_px,DWORD* other_pn) : px(other_px), pn(other_pn)
		{
		}
	};

	template<class _P>
	class SharedPtr 
	{
		// friend SharedPtrAccessor;

	protected:
		mutable _P* px;

		mutable DWORD* pn;

	public:
		inline void Clear()
		{
			px = 0;
			pn = 0;
		}

	public:
		inline SharedPtr()
		{
			Clear();
		}

		inline _P* operator =(_P* p)
		{
			SmartPtrLock_();
			//
			Free();
			//
			if (p != 0)
			{
				px = static_cast<_P*>(p);
				pn = new DWORD(1);
			}
			return p;
		}

		inline SharedPtr(_P* p)
		{
			Clear();
			operator =(p);
		}

		template<class _Q>
		inline _Q* operator =(_Q* p)
		{
			if (p) operator =(static_cast<_P*>(p));
			else operator =(0);
			return p;
		}

		template<class _Q>
		inline SharedPtr(_Q* p)
		{
			Clear();
			operator =(p);
		}

		inline const SharedPtr& operator =(const SharedPtr& other)
		{
			SmartPtrLock_();
			//
			Free();
			//
			if (other.px != 0)
			{
				pn = other.pn;
				++(*pn);
				px = other.px;
			}
			//
			return other;
		}
		
		inline SharedPtr(const SharedPtr& other)
		{
			Clear();
			operator =(other);
		}

		template<class _Q>
		inline const SharedPtr<_Q>& operator =(const SharedPtr<_Q>& other_Q)
		{
			SmartPtrLock_();
			//
			Free();
			//
			SharedPtr<_P> other = other_Q.operator SharedPtr<_P>();
			//
			if (other.px != 0)
			{
				pn = other.pn;
				++(*pn);
				px = static_cast<_P*>(other.px);
			}
			//
			return other_Q;
		}

		template<class _Q>
		inline SharedPtr(const SharedPtr<_Q>& other)
		{
			Clear();
			operator =(other);
		}

		inline void Free()
		{
			//// SmartPtrLock_();
			//
			if (px != 0) // *pn != 0
			{
				--(*pn);
				if ((*pn) == 0)
				{
					_P* tpx = px;
					//
					delete pn;
					//
					Clear();
					//
					// ������ ����� ������� ��� ������
					delete tpx;
				}
			}
			//
			// ���������������� smart-���������
			//
			Clear();
		}

		inline virtual ~SharedPtr()
		{
			SmartPtrLock_();
			//StdRMutex& mutex = SmartPtrCtx::GetFamilyRMutex();
			//mutex.Lock();
			//
			Free();
			//
			//mutex.Release();
		}

		// ==============================================================================================
		// ��������� ������� � ��������������
		// ----------------------

	public:
		SharedPtr(SharedPtrData& A)
		{
			Clear();
			if (A.px != 0)
			{
				pn = A.pn;
				++(*pn);
				px = static_cast<_P*>(A.px);
			}
		}

		template<class _Q>
			operator SharedPtr<_Q>() const
		{
			if (px)
			{
				SharedPtrData A(static_cast<_Q*>(px),pn);
				return SharedPtr<_Q>(A);
			}
			else
			{
				return SharedPtr<_Q>();
			}
		}

		inline _P* GetPointee()
		{
			if (px == 0)
			{
				HRESULT rc = E_POINTER;
				SmartPtrCtx::SystemAlarm_(rc);
				throw LowLevelError(rc);
			}
			return px;
		}

		operator const _P*() const
		{
			return px;
		}

		_P* operator ->()
		{
			if (px == 0)
			{
				HRESULT rc = E_POINTER;
				SmartPtrCtx::SystemAlarm_(rc);
				throw LowLevelError(rc);
			}
			return px;
		}

		const _P* operator ->() const
		{
			if (px == 0)
			{
				HRESULT rc = E_POINTER;
				SmartPtrCtx::SystemAlarm_(rc);
				throw LowLevelError(rc);
			}
			return px;
		}

		_P& operator *()
		{
			if (px == 0)
			{
				HRESULT rc = E_POINTER;
				SmartPtrCtx::SystemAlarm_(rc);
				throw LowLevelError(rc);
			}
			return *px;
		}

		inline bool IsEmpty() const
		{
			return (px == 0);
		}

		bool operator !() const
		{
			return IsEmpty();
		}
	};






	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����� SharedArray

	#define NORMAL_REALLOCATION_STEP 256

	template<class _P>
	class SharedArray 
	{
	public:
		typedef _P Pointee;

	protected:
		// ��������� �� ������
		mutable _P* px;

		// ��������� �� ����� ������
		mutable DWORD* pn;

		// ��������� �� (����������) ������ �������
		mutable int* ps;

		// ��������� �� ������ �������������� ����������� �������, *pa >= *ps
		mutable int* pa;

		inline void Clear() const
		{
			px = 0;
			pn = 0;
			ps = 0;
			pa = 0;
		}

	public:
		SharedArray()
		{
			Clear();
		}

		//SharedArray(const BYTE* p)
		//{
		//	Clear();
		//	operator =(p);
		//}

		//SharedArray(const char* p)
		//{
		//	Clear();
		//	operator =(p);
		//}

		//SharedArray(const wchar_t* p)
		//{
		//	Clear();
		//	operator =(p);
		//}

		void Free() const
		{
			// �������� � ������ _�������_ ���������� 
			//
			if (px != 0) // *pn != 0
			{
				--(*pn);
				if (*pn == 0)
				{
					delete[] px;
					delete pn;
					delete ps;
					delete pa;
				}
			}
			//
			// ���������������� smart-������
			//
			Clear();
		}

		virtual ~SharedArray()
		{
			/*
			StdRMutex& m1 = SmartPtrCtx::GetFamilyRMutex();
			ScopeLock_(m1); //*/
			//
			Free();
			//
			// _lock.Release();
		}

	protected:
		int AllocSize(int size) const
		{
			if (size > 1024) return 2*size;
			return (int(size / NORMAL_REALLOCATION_STEP) + 1) * NORMAL_REALLOCATION_STEP;
		}

	public:
		int GetSize() const
		{
			SmartPtrLock_();
			//
			if (ps == 0) // ~ px == 0
			{
				return 0;
			}
			//
			return *ps;
		}

		inline int Length() const 
		{
			return GetSize(); 
		}

		inline void SetSize(int new_size)
		{
			SmartPtrLock_();
			//
			if (px == 0)
			{
				HRESULT rc = E_POINTER; // ����������� ������
				SmartPtrCtx::SystemAlarm_(rc);
				throw LowLevelError(rc);
			}
			//
			if ((*ps) > 0)
			{
				if (new_size < (*ps))
				{
					HRESULT rc = E_ACCESSDENIED; // ������ ��������� ������ �������
					SmartPtrCtx::SystemAlarm_(rc);
					throw LowLevelError(rc);
				}
			}
			//
			if (new_size > (*pa))
			{
				HRESULT rc = E_ACCESSDENIED; // ����� �� �������� ������� �������
				SmartPtrCtx::SystemAlarm_(rc);
				throw LowLevelError(rc);
			}
			//
			*ps = new_size;
		}

		inline void ReduceSize(int new_size)
		{
			SmartPtrLock_();
			//
			if (px == 0)
			{
				HRESULT rc = E_POINTER; // ����������� ������
				SmartPtrCtx::SystemAlarm_(rc);
				throw LowLevelError(rc);
			}
			//
			if (new_size == 0)
			{
				Free(); 
			}
			else
			{
				if ((*ps) > 0)
				{
					if (new_size < (*ps))
					{
						*ps = new_size; 
					}
				}
			}
		}

		inline void Allocate(int size)
		{
			SmartPtrLock_();
			//
			Free();
			//
			int a = AllocSize(size);
			px = new _P[a];
			pn = new DWORD(1);
			ps = new int(size);
			pa = new int(a);
		}

		inline void Allocate(int size,const _P& value)
		{
			Allocate(size);
			Fill(value);
		}

		inline void Fill(const _P& value)
		{
			SmartPtrLock_();
			//
			for (int k = 0; k < (*ps); ++k)
			{
				px[k] = value;
			}
		}

	protected:
		void InternalExpand(int new_size) const
		{
			SmartPtrLock_();
			//
			if (px == 0)
			{
				int new_a = AllocSize(new_size);
				//
				px = new _P[new_a];
				pn = new DWORD(1);
				ps = new int(0);
				pa = new int(new_a);
			}
			else
			{
				if ((*ps) > 0)
				{
					if (new_size < (*ps))
					{
						HRESULT rc = E_INVALIDARG; // ������ ��������� ������
						SmartPtrCtx::SystemAlarm_(rc);
						throw LowLevelError(rc);
					}
				}
				if (new_size <= (*pa))
				{
					return; // ������ ������� ����� ��� ������ ���������� ��������
				}
				//
				_P* old_px = px;
				//
				int new_a = AllocSize(new_size);
				//
				px = new _P[new_a]; 
				//
				CopyMemory(px,old_px,(*ps)*sizeof(_P));
				ZeroMemory((void*)(px+(*ps)),(new_a-*ps)*sizeof(_P));
				//
				delete[] old_px;
				//
				*pa = new_a;
			}
		}

	public:
		inline void Expand(int new_size)
		{
			InternalExpand(new_size);
		}

	protected:
		void InternalReallocate(int new_size) const
		{
			SmartPtrLock_();
			//
			if (ps == 0)
			{
				// Allocate:
				int a = AllocSize(new_size);
				px = new _P[a];
				pn = new DWORD(1);
				ps = new int(new_size);
				pa = new int(a);
				return;
			}
			//
			if (new_size < (*ps))
			{
				HRESULT rc = E_INVALIDARG; // ������ ��������� ������
				SmartPtrCtx::SystemAlarm_(rc);
				throw LowLevelError(rc);
			}
			//
			_P* old_px = px;
			//
			int new_a = AllocSize(new_size);
			//
			if (new_a > *pa)
			{
				px = new _P[new_a];
				// ZeroMemory((void*)(px),new_size*sizeof(_P)); 
				if (false) // (is_class<_P>::value)
				{
					for (int k = 0; k < *ps; ++k)
					{
						px[k] = old_px[k];
					}
				}
				else
				{
					CopyMemory((void*)px,(const void*)old_px,(*ps)*sizeof(_P));
				}
				//
				delete[] old_px;
				//
				*pa = new_a;
			}
			//
			*ps = new_size;
		}

	public:
		inline void Reallocate(int new_size)
		{
			InternalReallocate(new_size);
		}

		inline SharedArray(int size) : px(0)
		{
			Clear();
			Allocate(size);
		}

		const SharedArray& operator =(const SharedArray& other) 
		{
			SmartPtrLock_();
			//
			Free();
			//
			if (other.px != 0)
			{
				pn = other.pn;
				++(*pn);
				px = other.px;
				ps = other.ps;
				pa = other.pa;
			}
			return other;
		}

		inline SharedArray(const SharedArray& other)
		{
			Clear();
			operator =(other);
		}

		// ==============================================================================================
		// ��������� ������� � ��������������
		// ----------------------

		inline operator const _P*() const
		{
			return px;
		}

		inline _P* GetBuffer() // ��������� �������� 
		{
			if (px == 0)
			{
				HRESULT rc = E_POINTER;
				SmartPtrCtx::SystemAlarm_(rc);
				throw LowLevelError(rc);
			}
			return px;
		}

		inline bool IsEmpty() const
		{
			if (ps == 0) // ~ px == 0
			{
				return true;
			}
			return GetSize() == 0;
		}

		inline bool operator !() const
		{
			return IsEmpty();
		}

	protected:
		inline void OutOfBounds(int i) const
		{
			HRESULT rc = HRESULT_FROM_WIN32(ERROR_INVALID_INDEX); 
			CString echo;
			echo = FormatStr(_T("����� �� ������� �������, i < 0, i == %d"), (int)i ); 
			TRACE_LOG(echo);
			SmartPtrCtx::SystemAlarm_(rc);
			throw LowLevelError(rc);
		}

	public:
		_P& operator [](int i)
		{
			if (i < 0)
			{
				OutOfBounds(i);
			}
			if (px == 0)
			{
				Allocate(i+1);
			}
			{
				SmartPtrLock_();
				//
				if (i >= (*ps))
				{
					if ( (i > 3*(*ps)-1) && ((*ps) > 1024) )
					{
						HRESULT rc = E_INVALIDARG; 
						CString echo;
						echo = FormatStr(
							_T("������� ���������� ������� �������, i >= 3*size, i == %d\n")
							_T("���������� ������� ������� Reallocate() ����"), (int)i ); 
						TRACE_LOG(echo);
						SmartPtrCtx::SystemAlarm_(rc);
						throw LowLevelError(rc);
					}
					InternalReallocate(i+1);
				}
				//
				return px[i];
			}
		}

		const _P& operator [](int i) const
		{
			if (i < 0)
			{
				OutOfBounds(i);
			}
			if (px == 0)
			{
				HRESULT rc = E_INVALIDARG; 
				CString echo = _T("������ ����"); 
				TRACE_LOG(echo);
				SmartPtrCtx::SystemAlarm_(rc);
				throw LowLevelError(rc);
			}
			{
				SmartPtrLock_();
				//
				if (i >= (*ps))
				{
					OutOfBounds(i);
				}
				//
				return px[i];
			}
		}

		SharedArray& Add(const _P& value)
		{
			SmartPtrLock_();
			//
			/*
			if (px == 0)
			{
				HRESULT rc = E_POINTER; // ����������� ������
				SmartPtrCtx::SystemAlarm_(rc);
				throw LowLevelError(rc);
			}
			//*/
			//
			(*this)[GetSize()] = value;
			//
			return *this;
		}

		SharedArray& operator +=(SharedArray a2)
		{
			for (int k = 0; k < a2.GetSize(); ++k) Add(a2[k]);
			//
			return *this;
		}



		// ==============================================================================================
		// ������ �� �������� 
		// ----------------------

		//bool IsAString() const
		//{
		//	SmartPtrLock_();
		//	//
		//	if (! ( (is_same<_P,BYTE>::value) || (is_same<_P,char>::value) ) )
		//	{
		//		HRESULT rc = E_ACCESSDENIED;
		//		SmartPtrCtx::SystemAlarm_(rc);
		//		AtlThrow(rc); // ������ ������� ���� �� ����� ���� �������
		//	}
		//	//
		//	if (px == 0) return false; // ������ ���
		//	//
		//	if ((*ps) == 0) return false; // �����
		//	//
		//	if (px[(*ps)-1] == _P(0)) return true;
		//	return false;
		//}

		//inline bool IsAWString() const
		//{
		//	SmartPtrLock_();
		//	//
		//	if (! ( (is_same<_P,wchar_t>::value) ) )
		//	{
		//		HRESULT rc = E_ACCESSDENIED;
		//		SmartPtrCtx::SystemAlarm_(rc);
		//		AtlThrow(rc); // ������ ������� ���� �� ����� ���� �������
		//	}
		//	//
		//	if (px == 0) return false; // ������ ���
		//	//
		//	if ((*ps) == 0) return false; // �����
		//	//
		//	if (px[(*ps)-1] == _P(0)) return true;
		//	return false;
		//}

		inline bool StartsWith(const CStringA& text)
		{
			if (px == 0) return false;
			if (Length() == 0) return false;
			//
			const void* p = (const void*)px;
			//
			return memcmp(p,(const void*)text.GetString(),text.GetLength()) == 0;
		}

	//#ifdef _UNICODE
	//	const char* operator =(const char* text)
	//	{
	//		operator =(CStringA(text));
	//		return text;
	//	}
	//#endif

		//const CStringA& operator =(const CStringA& text)
		//{
		//	SmartPtrLock_();
		//	//
		//	Free();
		//	//
		//	if (! ( (is_same<_P,BYTE>::value) || (is_same<_P,char>::value) ) )
		//	{
		//		HRESULT rc = E_ACCESSDENIED;
		//		SmartPtrCtx::SystemAlarm_(rc);
		//		AtlThrow(rc); // ������ ������� ���� �� ����� ���� �������
		//	}
		//	//
		//	Allocate(text.GetLength()+1);
		//	CopyMemory(px,text.GetString(),text.GetLength()*sizeof(_P));
		//	px[text.GetLength()] = 0;
		//	//
		//	return text;
		//}

		//const wchar_t* operator =(const wchar_t* text)
		//{
		//	operator =(CStringW(text));
		//	return text;
		//}

		//const CStringW& operator =(const CStringW& text)
		//{
		//	SmartPtrLock_();
		//	//
		//	Free();
		//	//
		//	if (! ( (is_same<_P,wchar_t>::value) ) )
		//	{
		//		HRESULT rc = E_ACCESSDENIED;
		//		SmartPtrCtx::SystemAlarm_(rc);
		//		throw LowLevelError(rc); // ������ ������� ���� ������ ��������� ������
		//	}
		//	//
		//	Allocate(text.GetLength()+1);
		//	CopyMemory(px,text.GetString(),text.GetLength()*sizeof(_P));
		//	px[text.GetLength()] = (wchar_t)0;
		//	//
		//	return text;
		//}

		//inline SharedArray(const BSTR& text)
		//{
		//	Clear();
		//	operator =(text);
		//}

		//inline SharedArray(const CComBSTR& text)
		//{
		//	Clear();
		//	operator =(text);
		//}

		//const BSTR& operator =(const BSTR& text)
		//{
		//	operator =(CComBSTR(text));
		//	return text;
		//}

		//const CComBSTR& operator =(const CComBSTR& text)
		//{
		//	SmartPtrLock_();
		//	//
		//	Free();
		//	//
		//	if (! ( (is_same<_P,BYTE>::value) || (is_same<_P,wchar_t>::value) ) )
		//	{
		//		HRESULT rc = E_ACCESSDENIED;
		//		SmartPtrCtx::SystemAlarm_(rc);
		//		throw LowLevelError(rc); // ������ ������� ���� ������ ��������� ������
		//	}
		//	//
		//	if (is_same<_P,BYTE>::value)
		//	{
		//		Allocate(text.Length()*sizeof(wchar_t));
		//		CopyMemory(px,text.m_str,text.Length()*sizeof(wchar_t));
		//	}
		//	else // wchar_t
		//	{
		//		Allocate(text.Length() + 1);
		//		CopyMemory(px,text.m_str,text.Length()*sizeof(wchar_t));
		//		px[text.Length()] = (wchar_t)0;
		//	}
		//	//
		//	return text;
		//}

		//operator CStringA const()
		//{
		//	if (! ( (is_same<_P,BYTE>::value) || (is_same<_P,char>::value) ) )
		//	{
		//		HRESULT rc = E_ACCESSDENIED;
		//		SmartPtrCtx::SystemAlarm_(rc);
		//		throw LowLevelError(rc); // ������ ������� ���� ������ ������������� � ������
		//	}
		//	//
		//	return CStringA((char*)px,*ps);
		//}

		// ==============================================================================================
		// ��������� 
		// ----------------------

		SharedArray& Sort()
		{
			int n = GetSize();
			if (n > 0)
			{
				FastSort(0,n-1);
			}
			return *this;
		}

		void FastSort(int a1,int a2)
		{
			int n = a2-a1+1;
			//
			if (n == 0) 
			{
				throw LowLevelError(E_UNEXPECTED);
			}
			else if (n == 1) return;
			else if (n == 2) 
			{
				_P& x1 = this->operator [](a1);
				_P& x2 = this->operator [](a2);
				//
				if (::operator <=(x1,x2)) return;
				else
				{
					_P y(x2); // TODO: swap 
					x2 = x1;
					x1 = y;
				}
			}
			else if (n == 3) 
			{
				FastSort(a1+1,a2);
				//
				FastSortMerge(a1,a1,a1+1,a2);
			}
			else if (n == 4) 
			{
				FastSort(a1,a1+1);
				FastSort(a2-1,a2);
				//
				FastSortMerge(a1,a1+1,a2-1,a2);
			}
			else
			{
				int H = n/2;
				int m = a1+H;
				//
				FastSort(a1,m-1);
				FastSort(m,a2);
				//
				FastSortMerge(a1,m-1,m,a2);
			}
		}

		void FastSortMerge(int a1,int a2,int b1,int b2)
		{
			// TODO: ��������������?
			//
			int n = a2-a1+1 + b2-b1+1;
			SharedArray<_P> t;
			t.Allocate(n);
			//
			int A = a1;
			int B = b1;
			int k = 0;
			while ((A <= a2) || (B <= b2))
			{
				if (A > a2)
				{
					t[k] = this->operator [](B); ++k;
					++B;
				}
				else if (B > b2)
				{
					t[k] = this->operator [](A); ++k;
					++A;
				}
				else
				{
					_P& x = this->operator [](A);
					_P& y = this->operator [](B);
					//
					if (::operator <=(x,y))
					{
						t[k] = x; ++k;
						++A;
					}
					else
					{
						t[k] = y; ++k;
						++B;
					}
				}
			}
			//
			for (int j = 0; j < n; ++j)
			{
				px[a1+j] = t[j];
			}
		}

		SharedArray& Revert()
		{
			int n = GetSize();
			int m = n/2;
			//
			for (int k = 0; k <=m; ++k)
			{
				int r = n-1-k;
				if (k < r)
				{
					_P& x1 = this->operator [](k);
					_P& x2 = this->operator [](r);
					//
					_P y(x2);
					x2 = x1;
					x1 = y;
				}
			}
			//
			return *this;
		}

		SharedArray CombineEqual()
		{
			Sort();
			//
			SharedArray L;
			for (int k = 0; k < Length(); ++k)
			{
				_P& x1 = this->operator [](k);
				//
				bool add = true;
				//
				if (L.Length() > 0)
				{
					if (x1 == L[L.Length()-1]) add = false;
				}
				//
				if (add)
				{
					L.Add(x1);
				}
			}
			//
			return L;
		}
	};



	//// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	//// HashValue

	//template<class _P>
	//HashType HashValue(const SharedPtr<_P> sp)
	//{
	//	return HashValue((const _P*)sp);
	//}




	// �������

	typedef SharedArray<BYTE> Blob;

	typedef SharedArray<char> CBlobA;

	// typedef SharedArray<wchar_t> CBlobW;
	class CBlobW : public SharedArray<wchar_t>
	{
	public:
		CBlobW()
		{
		}

		//CBlobW(const wchar_t* a1) : SharedArray<wchar_t>(a1)
		//{
		//}

		//template<class A1>
		//	CBlobW(A1 a1) : SharedArray<wchar_t>(a1)
		//{
		//}
	};

	typedef SharedArray<TCHAR> CBlob;



} // namespace  
