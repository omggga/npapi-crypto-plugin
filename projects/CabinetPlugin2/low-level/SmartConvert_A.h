/*
 SmartConvert_A.h : ������ ����� ������, ������������ ����������������: ������.

 $Name: work1 $
 $Revision: 1.1.2.3 $
 $Date: 2008/10/10 15:12:24 $

 */

#pragma once

#include "AtlX.h"
#include "SmartException.h"

namespace  
{
	struct Convert_A
	{
		inline static string ToString(const VARIANT& v,bool throwOnError=true)
		{
			try
			{
				if (v.vt == VT_BSTR)
				{
					return string(v.bstrVal);
				}
				else
				{
					string msg = FormatStr(
						L"���������� ������������� �������� �������� � ���������� ���� %s", 
						_W(VTText(v.vt)).GetString() 
						);
					throw MethodError(msg);
				}
			}
			_Catch()
		}

		inline static string VTText(VARTYPE vt)
		{
			if (((int)vt & VT_ILLEGAL) == VT_ILLEGAL) return L"VT_ILLEGAL";
			//
			int t = VT_TYPEMASK & (int)vt;
			//
			string msg;
			switch (t)
			{
			case VT_EMPTY:
				msg = L"VT_EMPTY";
				break;
			case VT_NULL:
				msg = L"VT_NULL";
				break;
			case VT_I2:
				msg = L"VT_I2";
				break;
			case VT_I4:
				msg = L"VT_I4";
				break;
			case VT_R4:
				msg = L"VT_R4";
				break;
			case VT_R8:
				msg = L"VT_R8";
				break;
			case VT_CY:
				msg = L"VT_CY";
				break;
			case VT_DATE:
				msg = L"VT_DATE";
				break;
			case VT_BSTR:
				msg = L"VT_BSTR";
				break;
			case VT_DISPATCH:
				msg = L"VT_DISPATCH";
				break;
			case VT_ERROR:
				msg = L"VT_ERROR";
				break;
			case VT_BOOL:
				msg = L"VT_BOOL";
				break;
			case VT_VARIANT:
				msg = L"VT_VARIANT";
				break;
			case VT_UNKNOWN:
				msg = L"VT_UNKNOWN";
				break;
			case VT_DECIMAL:
				msg = L"VT_DECIMAL";
				break;
			case VT_I1:
				msg = L"VT_I1";
				break;
			case VT_UI1:
				msg = L"VT_UI1";
				break;
			case VT_UI2:
				msg = L"VT_UI2";
				break;
			case VT_UI4:
				msg = L"VT_UI4";
				break;
			case VT_I8:
				msg = L"VT_I8";
				break;
			case VT_UI8:
				msg = L"VT_UI8";
				break;
			case VT_INT:
				msg = L"VT_INT";
				break;
			case VT_UINT:
				msg = L"VT_UINT";
				break;
			case VT_VOID:
				msg = L"VT_VOID";
				break;
			case VT_HRESULT:
				msg = L"VT_HRESULT";
				break;
			case VT_PTR:
				msg = L"VT_PTR";
				break;
			case VT_SAFEARRAY:
				msg = L"VT_SAFEARRAY";
				break;
			case VT_CARRAY:
				msg = L"VT_CARRAY";
				break;
			case VT_USERDEFINED:
				msg = L"VT_USERDEFINED";
				break;
			case VT_LPSTR:
				msg = L"VT_LPSTR";
				break;
			case VT_LPWSTR:
				msg = L"VT_LPWSTR";
				break;
			case VT_RECORD:
				msg = L"VT_RECORD";
				break;
			case VT_INT_PTR:
				msg = L"VT_INT_PTR";
				break;
			case VT_UINT_PTR:
				msg = L"VT_UINT_PTR";
				break;
			case VT_FILETIME:
				msg = L"VT_FILETIME";
				break;
			case VT_BLOB:
				msg = L"VT_BLOB";
				break;
			case VT_STREAM:
				msg = L"VT_STREAM";
				break;
			case VT_STORAGE:
				msg = L"VT_STORAGE";
				break;
			case VT_STREAMED_OBJECT:
				msg = L"VT_STREAMED_OBJECT";
				break;
			case VT_STORED_OBJECT:
				msg = L"VT_STORED_OBJECT";
				break;
			case VT_BLOB_OBJECT:
				msg = L"VT_BLOB_OBJECT";
				break;
			case VT_CF:
				msg = L"VT_CF";
				break;
			case VT_CLSID:
				msg = L"VT_CLSID";
				break;
			case VT_VERSIONED_STREAM:
				msg = L"VT_VERSIONED_STREAM";
				break;
			case VT_BSTR_BLOB:
				msg = L"VT_BSTR_BLOB";
				break;
			default:
				{
					msg = FormatStr(L"VTENUM(0x%x)", (int)t );
				}
			}
			//
			if (vt & VT_VECTOR)		msg += L" | VT_VECTOR";
			if (vt & VT_ARRAY)		msg += L" | VT_ARRAY";
			if (vt & VT_BYREF)		msg += L" | VT_BYREF";
			if (vt & VT_RESERVED)	msg += L" | VT_RESERVED";
			//
			return msg;
		}
	};

} //namespace  
