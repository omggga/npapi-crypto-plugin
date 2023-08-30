/*
 SlotLowLevel.h : �������������� ������� �����.

 $Name: work1 $
 $Revision: 1.1.2.2 $
 $Date: 2008/10/10 15:38:23 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

// 
//
#include "../low-level/SmartSimpleErrorHandling.h"
#include "../low-level/SmartVeryLowLevel.h"

namespace  { 



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� LowLevel

// �������������� ������� �����

class LowLevel 
{
public:
	// ==============================================================================================
	// ���������� �� ��������� ��������� 
	// ----------------------

	// �������� ���������� ���������
	static CString GetEventSourceName() { return _T(":slot:lowlevel"); }

	// ����������, ������������ ��������� ���������
	static CString GetFacilityName() { return _T(":slot"); }

	// ���������� ��� ������
	static HRESULT GetErrorCode() { return E_FAIL; }

	// ���������� ��� ��������������
	static HRESULT GetWarningCode() { return E_FAIL; }

protected:
	typedef CommonCtx<SimpleErrorHandling> _ErrorHandling;

public:
	// ���������� SLOTHOME

	// ��������� �����

	//inline static CString GetTempPath()
	//{
	//	static CString s_tempPath;
	//	//
	//	if (s_tempPath.GetString() == 0)
	//	{
	//		CreateDirectory(_T("C:\\Temp"),0);
	//		CreateDirectory(_T("C:\\Temp\\Slot"),0);
	//		//
	//		s_tempPath = _T("C:\\Temp\\Slot");
	//	}
	//	//
	//	return s_tempPath;
	//}

	// �������� ������������ ��������� ����

	inline static CString CheckPath(const CString& path)
	{
		CString path1(path);
		//
		while (path1[path1.GetLength()-1] == _T('\\'))
		{
			path1 = path1.Left(path1.GetLength()-1);
		}
		//
		if (path1.GetLength() == 0)
		{
			path1 = _T("C:\\Temp\\_1");
		}
		//
		return path1;
	}
};



} // namesapce  
