#if !defined(INC_LZEXCEPTION_h_)
#define INC_LZEXCEPTION_h_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern CStdString GetComErrorMsg(_com_error& comerr);

class CLzLastErrorException
{
protected:
	DWORD m_ErrCode;

public:
	CLzLastErrorException();
	CLzLastErrorException(DWORD dwErrCode) { m_ErrCode = dwErrCode; };

	void Msg(LPCTSTR pTitle);
	static void Msg(DWORD dwErrCode, LPCTSTR pTitle);
	void GetMsg(CStdString& msg);
	static void GetMsg(DWORD dwErrCode, CStdString& msg);
};

class CLzExceptionCOM
{
protected:
	HRESULT m_hr;

public:
	CLzExceptionCOM(HRESULT hr) { m_hr = hr; };
	
	HRESULT GetResult() { return m_hr; };

	static HRESULT GetMsg(CStdString& msg);
};


inline void LzExCOM(HRESULT hr)
{
	if( FAILED(hr) )
		throw CLzExceptionCOM(hr);
}

inline void ChkComErr(HRESULT hr) throw(_com_error)
{
	if( FAILED(hr) )
	{
		IErrorInfo* pei = NULL;

		if( SUCCEEDED(::GetErrorInfo(0, &pei)) && pei )
		{
			throw _com_error(hr, pei, FALSE);
		}
	}
}

#endif // !defined(INC_LZEXCEPTION_h_)
