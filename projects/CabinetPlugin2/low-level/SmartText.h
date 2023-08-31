/*
 SmartText.h : ��������� ��������� ���������.

 $Name: work1 $
 $Revision: 1.1.2.4 $
 $Date: 2008/10/10 16:37:07 $

 ��� String:
 1) ����������� ���
 2) ������� ���������� - ���������� ������� � �.�.
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

// ATL
//
#include <atlstr.h>

// 
//
#include "AtlX.h"
#include "SmartException.h"
#include "SmartMap.h"

namespace  { 



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ������������ TextUtil

namespace TextUtil
{

	inline static CStringA BlobToCStringA(const Blob& blob)
	{
		CStringA s((const char*)(const BYTE*)blob,blob.GetSize());
		return s;
	}

	inline static CStringW BlobToCStringW(const Blob& blob)
	{
		return CStringW(BlobToCStringA(blob));
	}

	inline static CStringA CBlobAToCStringA(const CBlobA& blob)
	{
		CStringA s((const char*)blob,blob.GetSize());
		return s;
	}

	inline static CStringW CBlobAToCStringW(const CBlobA& blob)
	{
		return CStringW(CBlobAToCStringA(blob));
	}

	inline static CStringW CBlobWToCStringW(const CBlobW& blob)
	{
		CStringW s((const wchar_t*)blob,blob.GetSize());
		return s;
	}

	inline static CStringA CBlobWToCStringA(const CBlobW& blob)
	{
		return CStringA(CBlobWToCStringW(blob));
	}


		
	inline static void ExtractNums(SharedArray<int>& nums,const CString& s,int start) 
	{
		int n = s.GetLength();
		//
		int x = 0;
		//
		int k = start;
		while (k < n)
		{
			TCHAR sym = s.GetString()[k];
			if (sym == _T('.'))
			{
				nums.Add(x);
				ExtractNums(nums,s,k+1);
				return;
			}
			else
			{
				if (x != -1)
				{
					int y = (int)(unsigned char)sym - 0x30;
					if ((y >= 0) && (y <= 9)) x = 10*x + y;
					else x = -1;
				}
			}
			++k;
		}
		nums.Add(x);
	}



	inline static SharedArray<int> ToNums(const CString& s) 
	{
		SharedArray<int> nums;
		//
		ExtractNums(nums,s,4);
		//
		CString msg;
		for (int k = 0; k < nums.GetSize(); ++k)
		{
			TCHAR item[_SIMPLE_STR_MAX];
			StringCchPrintf(item,_SIMPLE_STR_MAX, _T(".%d"), (int)nums[k] );
			msg += item;
		}
		//
		return nums;
	}

} // namespace TextUtil 






// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ��������� CString 



class FormatObject
{
protected:
	CString m_fmt;

	SharedArray<CString> m_types;

	SharedArray<CString> m_names;

	SharedArray<Blob> m_values;

	TextMap* m_pDict;

	int n;

	int pos;

	mutable CBlobA m_vaList;

	bool m_formatting;

	static bool IsFormatChar(TCHAR sym)
	{
		return (
			(sym == _T('s')) || (sym == _T('S')) ||
			(sym == _T('d')) || (sym == _T('u')) ||
			(sym == _T('x')) || (sym == _T('f'))
		);
	}

	void Clear()
	{
		m_pDict = 0;
		m_formatting = false;
	}

	void Parse()
	{
		n = 0;
		pos = 0;
		m_vaList.Expand(1024);
		//
		int state = 0;
		bool f_1 = false;
		//
		CString new_fmt;
		CString name;
		//
		int n2 = 0;
		for (int k = 0; k < m_fmt.GetLength(); ++k)
		{
			TCHAR sym = m_fmt[k];
			if (state == 0)
			{
				if (sym == _T('%'))
				{
					state = 1;
					f_1 = true;
				}
				else
				{
					f_1 = false;
				}
				new_fmt += CString(sym,1);
			}
			else if (state == 1)
			{
				if ( (sym == _T('{')) && f_1 )
				{
					state = 2;
				}
				else if ( (sym == _T('%')) && f_1 )
				{
					state = 0;
					new_fmt += CString(sym,1);
				}
				else if (IsFormatChar(sym))
				{
					m_types.Add(CString(sym));
					++n2;
					state = 0;
					name = _T("");
					//
					new_fmt += CString(sym,1);
				}
				else
				{
					new_fmt += CString(sym,1);
				}
				f_1 = false;
			}
			else if (state == 2)
			{
				if (sym == _T('}'))
				{
					m_names[n2] = name;
					state = 1;
				}
				else
				{
					name += CString(sym,1);
				}
			}
			else
			{
				string msg;
				msg = FormatStr(L"��������� ���������: %d", (int)state );
				throw MethodError(msg);
			}
		}
		if (state != 0) throw MethodError(string("��������� ��������� �� ���������� �������"));
		//
		m_fmt = new_fmt;
	}

public:
	FormatObject(const CString& fmt) : m_fmt(fmt)
	{
		Clear();
		Parse();
	}

	virtual ~FormatObject()
	{
		if (m_pDict) delete m_pDict;
	}

	operator CString() 
	{
		m_formatting = true;
		//
		if (m_pDict) AddDictValues();
		//
		CString text;
		va_list L = (char*)m_vaList.GetBuffer();
		TCHAR s[_SIMPLE_STR_MAX]; 
		HRESULT rc = StringCchPrintf(s,_SIMPLE_STR_MAX,m_fmt,L); // FormatV 
		if (rc == S_OK)
		{
			text = s;
		}
		else
		{
			// text = _T(""); 
		}
		//
		m_formatting = false;
		return text;
	}

	void CheckLinear()
	{
		if (m_formatting) return;
		//
		if (m_pDict)
		{
			string msg = L"��� �������������� �� �������";
			throw MethodError(msg);
		}
	}

	FormatObject& Add(const CString& x)
	{
		CheckLinear();
		CString t = m_types[n];
		if (t.CompareNoCase(_T("s")) == 0)
		{
			Blob b;
			b.Allocate( sizeof(TCHAR) * (x.GetLength()+1) );
			CopyMemory(b.GetBuffer(),x.GetString(),b.GetSize()-sizeof(TCHAR));
			for (int j1 = 1; j1 <= sizeof(TCHAR); ++j1) b.GetBuffer()[b.GetSize()-j1] = 0;
			m_values[n] = b;
			//
			m_vaList.Expand(pos+16);
			char* vaList = m_vaList.GetBuffer();
			const TCHAR* p = (TCHAR*)b.GetBuffer();
			memcpy((void*)( vaList + pos ),(const void*)( &p ),sizeof(p));
			pos += sizeof(p);
			m_vaList.SetSize(pos);
			++n;
		}
		else
		{
			string msg = FormatStr(
				L"��������� ��� CString ��� ��������� N %d: '%s' (%s)", (int)n, _W(t).GetString(), _W(x).GetString() );
			throw MethodError(msg);
		}
		return *this;
	}

	FormatObject& Add(int x)
	{
		CheckLinear();
		CString t = m_types[n];
		if ( (t.Compare(_T("d")) == 0) || (t.Compare(_T("u")) == 0) || (t.Compare(_T("x")) == 0) )
		{
			m_vaList.Expand(pos+16);
			char* vaList = m_vaList.GetBuffer();
			int* start = (int*)( (void*)( vaList + pos ) );
			*start = (int)x;
			pos += sizeof(*start);
			m_vaList.SetSize(pos);
			++n;
		}
		else
		{
			string msg;
			msg = FormatStr(L"��������� ��� int ��� ��������� '%s'", _W(t).GetString() );
			throw MethodError(msg);
		}
		return *this;
	}

	FormatObject& Add(double x)
	{
		CheckLinear();
		CString t = m_types[n];
		if ( (t.Compare(_T("f")) == 0) )
		{
			m_vaList.Expand(pos+16);
			char* vaList = m_vaList.GetBuffer();
			double* start = (double*)( (void*)( vaList + pos ) );
			*start = (double)x;
			pos += sizeof(*start);
			m_vaList.SetSize(pos);
			++n;
		}
		else
		{
			string msg;
			msg = FormatStr(L"��������� ��� int ��� ��������� '%s'", _W(t).GetString() );
			throw MethodError(msg);
		}
		return *this;
	}

	void AddDictValues() 
	{
		for (int k = 0; k < m_types.GetSize(); ++k)
		{
			CString t = m_types[k];
			CString name = m_names[k];
			//
			if (name.GetLength() == 0) throw MethodError(string(L"������ ��� �������� ������� ��������������"));
			//
			CString v0 = (*m_pDict)[name];
			//
			if ( (t.CompareNoCase(_T("s")) == 0) )
			{
				Add(v0);
			}
			else if ( (t.Compare(_T("d")) == 0) || (t.Compare(_T("u")) == 0) || (t.Compare(_T("x")) == 0) )
			{
				Add(_tstoi(v0.GetString()));
			}
			else if ( (t.Compare(_T("f")) == 0) )
			{
				Add(_tstof(v0.GetString()));
			}
			else
			{
				string msg;
				msg = FormatStr(L"��������������� ��� ��������� ��������������: '%s'", _W(t).GetString() );
				throw MethodError(msg);
			}
		}
	}

	FormatObject& Set(TextMap& dict)
	{
		if (n > 0)
		{
			string msg;
			msg = L"��� ����������� �������� ������ ��������������";
			throw MethodError(msg);
		}
		m_pDict = new TextMap(dict);
	}
};



class Format
{
	SharedPtr<FormatObject> m_f;

public:
	Format(const CString& fmt) : m_f(new FormatObject(fmt))
	{
	}

	operator CString() 
	{
		return m_f->operator CString();
	}

	//operator ExceptionByMsg() 
	//{
	//	return ExceptionByMsg(CString(*this)); 
	//}

	template<class _A>
	Format& Add(_A x)
	{
		try
		{
			m_f->Add(x);
			return *this;
		}
		_Catch()
	}

	//Format& Add(const CString& x)
	//{
	//	m_f->Add(x);
	//	return *this;
	//}

	//Format& Add(double x)
	//{
	//	m_f->Add(x);
	//	return *this;
	//}

	//Format& Add(float x)
	//{
	//	m_f->Add(x);
	//	return *this;
	//}

	//Format& Add(int x)
	//{
	//	m_f->Add(x);
	//	return *this;
	//}

	//Format& Add(const TCHAR* x)
	//{
	//	m_f->Add(x);
	//	return *this;
	//}

	template<class _A>
	Format& Set(_A x)
	{
		m_f->Set(x);
		return *this;
	}

	template<class _A>
	Format& operator %(_A x)
	{
		try
		{
			return Add(x);
		}
		_Catch()
	}
};



//template<class _A>
//Format operator %(const CString& fmt,_A x)
//{
//	return Format(fmt).Add(x);
//}

inline Format operator %(const CString& fmt,const CString& x)
{
	//try
	//{
		return Format(fmt).Add(x);
	//}
	//_FCatch()
}

inline Format operator %(const CString& fmt,double x)
{
	try
	{
		return Format(fmt).Add(x);
	}
	_FCatch()
}

inline Format operator %(const CString& fmt,float x)
{
	try
	{
		return Format(fmt).Add((double)x);
	}
	_FCatch()
}

inline Format operator %(const CString& fmt,int x)
{
	try
	{
		return Format(fmt).Add(x);
	}
	_FCatch()
}

inline Format operator %(const CString& fmt,DWORD x)
{
	try
	{
		return Format(fmt).Add((int)x);
	}
	_FCatch()
}

inline Format operator %(const CString& fmt,const TCHAR* x)
{
	try
	{
		return Format(fmt).Add(CString(x));
	}
	_FCatch()
}

inline Format operator %(const TCHAR* fmt,const CString& x)
{
	try
	{
		return Format(fmt).Add(x);
	}
	_FCatch()
}














// ===============================================================================================
// ��������� ������� � ��������� 

inline static Format operator <<(const CString& fmt,Map<CString,CString>& x)
{
	try
	{
		return Format(fmt).Set(x);
	}
	_FCatch()
}




inline static bool operator <=(const CString& lhs,const CString& rhs) 
{
	using namespace TextUtil;
	//
	bool isOID = false;
	if ((lhs.Left(4).CompareNoCase(_T("OID.")) == 0) &&
		(rhs.Left(4).CompareNoCase(_T("OID.")) == 0))
	{
		isOID = true;
	}
	//
	if (isOID)
	{
		SharedArray<int> nums = ToNums(lhs);
		SharedArray<int> rhs_nums = ToNums(rhs);
		//
		//if (nums.GetSize() < rhs_nums.GetSize()) return true;
		//else if (nums.GetSize() > rhs_nums.GetSize()) return false;
		//else
		{
			int k = 0;
			while (k < nums.GetSize())
			{
				int n1 = nums[k];
				int n2 = rhs_nums[k];
				if (n1 < n2) return true;
				else if (n1 > n2) return false;
				++k;
			}
		}
		if (nums.GetSize() < rhs_nums.GetSize()) return true;
		else if (nums.GetSize() > rhs_nums.GetSize()) return false;
		return true; // =
	}
	//
	int k = 0;
	while (true)
	{
		if (lhs.GetLength() == k)
		{
			if (rhs.GetLength() == k) return true; // equal
			else return true;
		}
		CString x(lhs.GetString() + k,1);
		CString y(rhs.GetString() + k,1);
		if (x < y) return true;
		if (x > y) return false;
		//
		// continue...
		++k;
	}
}



inline static bool operator <(const CString& lhs,const CString& rhs) 
{
	using namespace TextUtil;
	//
	bool isOID = false;
	if ((lhs.Left(4).CompareNoCase(_T("OID.")) == 0) &&
		(rhs.Left(4).CompareNoCase(_T("OID.")) == 0))
	{
		isOID = true;
	}
	//
	if (isOID)
	{
		SharedArray<int> nums = ToNums(lhs);
		SharedArray<int> rhs_nums = ToNums(rhs);
		//
		//if (nums.GetSize() < rhs_nums.GetSize()) return true;
		//else if (nums.GetSize() > rhs_nums.GetSize()) return false;
		//else
		{
			int k = 0;
			while (k < nums.GetSize())
			{
				int n1 = nums[k];
				int n2 = rhs_nums[k];
				if (n1 < n2) return true;
				else if (n1 > n2) return false;
				++k;
			}
		}
		if (nums.GetSize() < rhs_nums.GetSize()) return true;
		else if (nums.GetSize() > rhs_nums.GetSize()) return false;
		return false; // =
	}
	//
	int k = 0;
	while (true)
	{
		if (lhs.GetLength() == k)
		{
			if (rhs.GetLength() == k) return false; // equal
			else return true;
		}
		CString x(lhs.GetString() + k,1);
		CString y(rhs.GetString() + k,1);
		if (x.Compare(y) < 0) return true;
		if (x.Compare(y) > 0) return false;
		//
		// continue...
		++k;
	}
}











// ���������

// (A)

inline CStringA& UCFirst(CStringA& s)
{
	if (s.GetLength() > 0)
	{
		s.MakeLower();
		CStringA s1 = s.Left(1);
		s1.MakeUpper();
		s.GetBuffer()[0] = s1[0];
	}
	return s;
}

inline CStringA Join(const SharedArray<CStringA> a,const CStringA& sep)
{
	CStringA result;
	for (int k = 0; k < a.GetSize(); ++k)
	{
		if (k > 0) result += sep;
		//
		result += CStringA(a[k]);
	}
	return result;
}

inline CStringA operator *(const SharedArray<CStringA> a,const CStringA& sep)
{
	return Join(a,sep);
}

inline SharedArray<CStringA> operator /(const CStringA& s,const CStringA& sep)
{
	// ���������� ���������� ��������� split'�:
	// ���� ������ �����, �� �������, ��� ��������� - ������.
	//
	SharedArray<CStringA> v;
	//
	if (s.GetLength() == 0) return v;
	//
	CStringA text = s;
	//
	int n = 0;
	int start = 0;
	bool bContinue = true;
	//
	while (bContinue)
	{
		int pos = text.Find(sep,start);
		if (pos == -1)
		{
			bContinue = false;
		}
		else if (pos + sep.GetLength() == text.GetLength())
		{
			++n;
			bContinue = false;
		}
		else
		{
			++n;
			start = pos + sep.GetLength();
		}
	}
	++n; // number of items == number of separators + 1
	v.Allocate(n);
	//
	bContinue = true;
	//
	int i = 0;
	while (bContinue)
	{
		int pos = text.Find(sep);
		if (pos == -1)
		{
			v[i] = text;
			++i;
			bContinue = false;
		}
		else
		{
			v[i] = text.Left(pos);
			++i;
			if (pos + sep.GetLength() < text.GetLength())
			{
				text = text.Right(text.GetLength() - pos - sep.GetLength());
				// ...and continue
			}
			else
			{
				v[i] = CStringA();
				++i;
				bContinue = false;
			}
		}
	}
	//
	return v;
}

// (W)

inline CStringW& UCFirst(CStringW& s)
{
	if (s.GetLength() > 0)
	{
		s.MakeLower();
		CStringW s1 = s.Left(1);
		s1.MakeUpper();
		s.GetBuffer()[0] = s1[0];
	}
	return s;
}

inline CStringW Join(const SharedArray<CStringW> a,const CStringW& sep)
{
	CStringW result;
	for (int k = 0; k < a.GetSize(); ++k)
	{
		if (k > 0) result += sep;
		//
		result += CStringW(a[k]);
	}
	return result;
}

inline CStringW operator *(const SharedArray<CStringW> a,const CStringW& sep)
{
	return Join(a,sep);
}

inline SharedArray<CStringW> operator /(const CStringW& s,const CStringW& sep)
{
	// ���������� ���������� ��������� split'�:
	// ���� ������ �����, �� �������, ��� ��������� - ������.
	//
	SharedArray<CStringW> v;
	//
	if (s.GetLength() == 0) return v;
	//
	CStringW text = s;
	//
	int n = 0;
	int start = 0;
	bool bContinue = true;
	//
	while (bContinue)
	{
		int pos = text.Find(sep,start);
		if (pos == -1)
		{
			bContinue = false;
		}
		else if (pos + sep.GetLength() == text.GetLength())
		{
			++n;
			bContinue = false;
		}
		else
		{
			++n;
			start = pos + sep.GetLength();
		}
	}
	++n; // number of items == number of separators + 1
	v.Allocate(n);
	//
	bContinue = true;
	//
	int i = 0;
	while (bContinue)
	{
		int pos = text.Find(sep);
		if (pos == -1)
		{
			v[i] = text;
			++i;
			bContinue = false;
		}
		else
		{
			v[i] = text.Left(pos);
			++i;
			if (pos + sep.GetLength() < text.GetLength())
			{
				text = text.Right(text.GetLength() - pos - sep.GetLength());
				// ...and continue
			}
			else
			{
				v[i] = CStringW();
				++i;
				bContinue = false;
			}
		}
	}
	//
	return v;
}



} // namespace  
