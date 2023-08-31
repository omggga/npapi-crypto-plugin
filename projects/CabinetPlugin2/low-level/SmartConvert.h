/*
 SmartConvert.h : �����, ����������� ����������������.

 $Name: work1 $
 $Revision: 1.1.2.1 $
 $Date: 2008/05/14 09:28:58 $

 */

#pragma once

#include <slot/cpp/low-level/SmartContert_A.h>

namespace 
{
	struct Convert : public Convert_A 
	{
		inline static bool ToBoolean(const string& value)
		{
			string v = value;
			v.Trim();
			v.MakeLower();
			//
			if (v == L"yes") return true;
			else if (v == L"��") return true;
			else if (v == L"true") return true;
			else if (v == L"1") return true;
			return false;
		}

		inline static int ToInt(const string& value)
		{
			string v = value;
			v.Trim();
			v.MakeLower();
			//
			return _wtoi(v);
		}
	};
} //namespace  
