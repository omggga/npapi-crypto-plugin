/*
 SmartRegex.h : ������� ������ ��� ������ � ����������� �����������.

 $Name: work1 $
 $Revision: 1.1.2.4 $
 $Date: 2009/05/18 13:17:11 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

// ATL
//
#pragma warning(push)
#pragma warning(disable: 4018) 
#include <atlrx.h>
#include <atlcoll.h>
#pragma warning(pop)

// 
//
#include <low-level/SmartCommonCtx.h>
#include <low-level/SmartPtr.h>

namespace  { 



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� RECharTraits

#ifdef _UNICODE
typedef CAtlRECharTraitsW RECharTraits;
#else
typedef CAtlRECharTraitsA RECharTraits;
#endif



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� RegExp

class Match;

class RegExp
{
	friend Match;

protected:
	SharedPtr<CAtlRegExp<RECharTraits> > m_e;

public:
	enum Status
	{
		Status_OK			= 0,
		Status_ParseError	= 1
	}
	m_status;

	RegExp(const CString& regx)
	{
		m_e = new CAtlRegExp<RECharTraits>;
		REParseError status = m_e->Parse((const TCHAR*)regx);
		if (REPARSE_ERROR_OK != status)
		{
			m_status = Status_ParseError;
			throw MethodError(string(L"������ ������� ����������� ���������"));
		}
		m_status = Status_OK;
	}

	static CString Replace(const CString& regx,const CString& sub,const CString& input,
		bool replaceAll=true,
		bool* out_pMatched=0);
};



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� Match

class Match
{
protected:
	SharedPtr<CAtlRegExp<RECharTraits> > m_e;

	SharedArray<CString> m_parts;

	BOOL m_matched;

public:
	enum Status
	{
		Status_OK			= 0,
		Status_ParseError	= 1
	}
	m_status;

	Match(RegExp& r,const CString& input)
	{
		if (r.m_status != RegExp::Status_OK)
		{
			m_status = (Status)(int)r.m_status;
			return;
		}
		//
		m_e = r.m_e;
		CAtlREMatchContext<RECharTraits> mc;
		m_matched = m_e->Match((const TCHAR*)input,&mc); 
		LoadParts(&mc);
		m_status = Status_OK;
	}

	Match(const CString& regx,const CString& input)
	{
		RegExp r(regx);
		if (r.m_status != RegExp::Status_OK)
		{
			m_status = (Status)(int)r.m_status;
			return;
		}
		//
		m_e = r.m_e;
		CAtlREMatchContext<RECharTraits> mc;
		m_matched = m_e->Match((const TCHAR*)input,&mc); 
		LoadParts(&mc);
		m_status = Status_OK;
	}

	virtual ~Match()
	{
	}

	void LoadParts(CAtlREMatchContext<RECharTraits>* m_mc)
	{
		if (m_parts.GetSize() > 0) return;
		//
		// (����������� ������ ��������� ���������)
		//
		// ��������� ��������� ���������� ���������
		//
		// const int u = sizeof(CAtlREMatchContext<RECharTraits>::RECHAR);
		//
		ULONG n = m_mc->m_uNumGroups;
		m_parts.Allocate(n);
		for (int k = 0; k < (int)n; ++k)
		{
			const CAtlREMatchContext<RECharTraits>::RECHAR* p1 = 0;
			const CAtlREMatchContext<RECharTraits>::RECHAR* p2 = 0;
			m_mc->GetMatch(k, &p1, &p2);
			int n1 = int((p2-p1));
			CString s((TCHAR*)p1,n1);
			m_parts[k] = s; // ��������! ����� ��������� ���������� 
		}
	}

	operator SharedArray<CString>()
	{
		// ��������� ���������
		//
		if (m_status != Status_OK) return SharedArray<CString>();
		//
		// ���������, �������� �� ����� ��� ���������� ���������?
		//
		if (! m_matched)
		{
			///!!! Context::DisplayText_(_T("����� �� �������� ��� ���������� ���������"));
			return SharedArray<CString>();
		}
		//
		return m_parts;
	}

	inline BOOL Matched() const
	{
		if (m_status != Status_OK)
		{
			throw MethodError(string(L"������ � ����������� ���������"));
		}
		//
		return m_matched;
	}

	inline operator BOOL() const
	{
		return Matched();
	}

	inline BOOL operator !() const
	{
		return ! Matched();
	}
};



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ������ ������ RegExp

inline 
CString RegExp::Replace(const CString& pattern,
					   const CString& sub,
					   const CString& input,
					   bool replaceAll,
					   bool* out_pMatched)
{
	CString text = input;
	//
	CString regx = FormatStr(_T("^{.*}{%s}{.*}"), (const TCHAR*)pattern );
	//
	bool matched = false;
	//
	bool done = false;
	while (! done)
	{
		Match m(regx.GetString(),text.GetString());
		if (m)
		{
			matched = true;
			SharedArray<CString> parts(m);
			text = FormatStr(_T("%s%s%s"), (const TCHAR*)parts[0], (const TCHAR*)sub, (const TCHAR*)parts[2] );
		}
		else done = true;
		//
		if (! replaceAll) done = true;
	}
	//
	if (out_pMatched) *out_pMatched = matched;
	return text;
}



} // namespace  
