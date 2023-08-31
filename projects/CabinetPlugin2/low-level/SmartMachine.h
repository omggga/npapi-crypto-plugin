/*
 Machine.h : ������� ��� ������� � ����������: ������, �������� �������.

 $Name: work1 $
 $Revision: 1.1.2.3 $
 $Date: 2008/11/05 17:14:30 $

 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

// Release tuning
//
#ifndef _DEBUG // #if Release
//
#ifdef _TRACE_REGISTRY_READS
#undef _TRACE_REGISTRY_READS
#endif
//
#endif

#include <Winbase.h>

namespace  { 

	// ===========================================================================================
	// ������ 

	class Machine
	{
		Machine()
		{
		}

	public:
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// ������

		inline static void AddRegKey(HKEY rootKey,const CString& keyName)
		{
			try
			{
				HKEY hKey = 0;
				try
				{
					LONG rc = RegOpenKeyEx(rootKey,keyName,0,KEY_QUERY_VALUE,&hKey);
					if (rc != ERROR_SUCCESS)
					{
						DWORD disposition;
						LONG rc2 = RegCreateKeyEx(rootKey,keyName,0,0,0,
							KEY_READ|KEY_WRITE,0,&hKey,&disposition);
						if (rc2 != ERROR_SUCCESS)
						{
							HRESULT hr = HRESULT_FROM_WIN32(rc2);
							throw FunctionError(hr);
						}
					}
					//
					if (hKey) RegCloseKey(hKey);
				}
				catch(...)
				{
					if (hKey) RegCloseKey(hKey);
					//
					throw;
				}
			}
			_FCatch()
		}

		inline static void MountCabinetSettingsKey(HKEY rootKey=HKEY_CURRENT_USER)
		{
			try
			{
				AddRegKey(rootKey, _T("SOFTWARE\\")); 
				AddRegKey(rootKey, _T("SOFTWARE\\\\Cabinet")); 
				AddRegKey(rootKey, _T("SOFTWARE\\\\Cabinet\\Settings")); 
			}
			_FCatch()
		}

		inline static void SetRegBinaryValue(HKEY rootKey,
			const CString& keyName, const CString& attrName, Blob value,
			bool throwOnError = true, HRESULT* pResult = 0)
		{
			try
			{
				HKEY hKey = 0;
				try
				{
					LONG r1 = RegOpenKeyEx(rootKey, keyName, 0, KEY_SET_VALUE, &hKey);
					if (r1 != ERROR_SUCCESS)
					{
						HRESULT hr = HRESULT_FROM_WIN32(r1);
						if (!throwOnError)
						{
							if (pResult) *pResult = hr;
						}
						throw FunctionError(hr);
					}
					//
					LONG r2 = RegSetValueEx(
						hKey,
						attrName,
						0,
						REG_BINARY,
						value.GetBuffer(),
						value.Length()
						);
					if (r2 != ERROR_SUCCESS)
					{
						HRESULT hr = HRESULT_FROM_WIN32(r2);
						if (!throwOnError)
						{
							if (pResult) *pResult = hr;
						}
						throw FunctionError(hr);
					}
					if (pResult) *pResult = S_OK;
					//
					if (hKey) RegCloseKey(hKey);
				}
				catch (...)
				{
					if (hKey) RegCloseKey(hKey);
					//
					throw;
				}
			}
			_FCatch()
		}

		inline static Blob GetRegBinaryValue(HKEY rootKey, const CString& keyName,
			const CString& attrName, bool throwOnError = true, HRESULT* pResult = 0)
		{
			try
			{
			HKEY hKey = 0;
			try
			{
				LONG r1 = RegOpenKeyEx(rootKey, keyName, 0, KEY_QUERY_VALUE, &hKey);
				if (r1 != ERROR_SUCCESS)
				{
					HRESULT hr = HRESULT_FROM_WIN32(r1);
					if (!throwOnError)
					{
						if (pResult) *pResult = hr;
						//
#							ifdef _TRACE_REGISTRY_READS
						TRACE_LINE(_T("(������ ����������)"));
#							endif
						//
						return Blob();
					}
					throw FunctionError(hr);
				}
				//
				//{
				//	//TCHAR    achKey[1024];   // buffer for subkey name
				//	//DWORD    cbName;                   // size of name string 
				//	TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
				//	DWORD    cchClassName = MAX_PATH;  // size of class string 
				//	DWORD    cSubKeys = 0;               // number of subkeys 
				//	DWORD    cbMaxSubKey;              // longest subkey size 
				//	DWORD    cchMaxClass;              // longest class string 
				//	DWORD    cValues;              // number of values for key 
				//	DWORD    cchMaxValue;          // longest value name 
				//	DWORD    cbMaxValueData;       // longest value data 
				//	DWORD    cbSecurityDescriptor; // size of security descriptor 
				//	FILETIME ftLastWriteTime;      // last write time 

				//	DWORD i, retCode;

				//	TCHAR  achValue[1024];
				//	DWORD cchValue = 1024;

				//	// Get the class name and the value count. 
				//	retCode = RegQueryInfoKey(
				//		hKey,                    // key handle 
				//		achClass,                // buffer for class name 
				//		&cchClassName,           // size of class string 
				//		NULL,                    // reserved 
				//		&cSubKeys,               // number of subkeys 
				//		&cbMaxSubKey,            // longest subkey size 
				//		&cchMaxClass,            // longest class string 
				//		&cValues,                // number of values for this key 
				//		&cchMaxValue,            // longest value name 
				//		&cbMaxValueData,         // longest value data 
				//		&cbSecurityDescriptor,   // security descriptor 
				//		&ftLastWriteTime);       // last write time 
				//								 //
				//	if (retCode != 0)
				//	{
				//		TRACE_LOG("Error! ))");
				//	}
				//	//
				//	if (cValues)
				//	{
				//		//printf( "\nNumber of values: %d\n", cValues);

				//		for (i = 0, retCode = ERROR_SUCCESS; i<cValues; i++)
				//		{
				//			cchValue = 1024;
				//			achValue[0] = '\0';
				//			retCode = RegEnumValue(hKey, i,
				//				achValue,
				//				&cchValue,
				//				NULL,
				//				NULL,
				//				NULL,
				//				NULL);

				//			if (retCode == ERROR_SUCCESS)
				//			{
				//				//_tprintf(TEXT("(%d) %s\n"), i+1, achValue); 
				//			}
				//		}
				//	}
				//}
				//
				BYTE data[64*1024];
				DWORD dataSize = 64*1024;
				DWORD dataType;
				LONG r2 = RegQueryValueEx(
					hKey,
					attrName,
					0,
					&dataType,
					data,
					&dataSize
					);
				if (r2 != ERROR_SUCCESS)
				{
					HRESULT hr = HRESULT_FROM_WIN32(r2);
					if (!throwOnError)
					{
						if (pResult) *pResult = hr;
						//
#							ifdef _TRACE_REGISTRY_READS
						TRACE_LINE(_T("(������ ����������)"));
#							endif
						//
						return Blob();
					}
					throw FunctionError(hr);
				}
				//
				Blob b;
				b.Allocate(dataSize);
				CopyMemory(b.GetBuffer(), data, dataSize);
				if (pResult) *pResult = S_OK;
				//
				if (hKey) RegCloseKey(hKey);
				//
#					ifdef _TRACE_REGISTRY_READS
				//TRACE_LINE1(_T("��������: "), _S(value).GetString() );
#					endif
				//
				return b;
			}
			catch (...)
			{
				if (hKey) RegCloseKey(hKey);
				//
				throw;
			}
			}
			_FCatch()
		}
		
		inline static void SetRegStringValue(HKEY rootKey,
			const CString& keyName,const CString& attrName,const CString& value,
			bool throwOnError=true,HRESULT* pResult=0)
		{
			try
			{
				HKEY hKey = 0;
				try
				{
					LONG r1 = RegOpenKeyEx(rootKey,keyName,0,KEY_SET_VALUE,&hKey);
					if (r1 != ERROR_SUCCESS)
					{
						HRESULT hr = HRESULT_FROM_WIN32(r1);
						if (! throwOnError)
						{
							if (pResult) *pResult = hr;
						}
						throw FunctionError(hr);
					}
					//
					LONG r2 = RegSetValueEx(
						hKey,
						attrName,
						0,
						REG_SZ,
						(const BYTE*)value.GetString(),
						(value.GetLength()+1) * sizeof(TCHAR)
						);
					if (r2 != ERROR_SUCCESS)
					{
						HRESULT hr = HRESULT_FROM_WIN32(r2);
						if (! throwOnError)
						{
							if (pResult) *pResult = hr;
						}
						throw FunctionError(hr);
					}
					if (pResult) *pResult = S_OK;
					//
					if (hKey) RegCloseKey(hKey);
				}
				catch(...)
				{
					if (hKey) RegCloseKey(hKey);
					//
					throw;
				}
			}
			_FCatch()
		}

		inline static CString GetRegStringValue(HKEY rootKey,const CString& keyName,
			const CString& attrName,bool throwOnError=true,HRESULT* pResult=0)
		{
			try
			{
//#				ifdef _DEBUG
//				{
//					HKEY rootKey = HKEY_LOCAL_MACHINE;
//					HKEY hKey = 0;
//					wchar_t* 
//						keyName = L"Software\\\\Cabinet\\Settings";
//					LONG r1 = RegOpenKeyExW(rootKey,keyName,0,KEY_QUERY_VALUE,&hKey);
//					//
//					if (r1 != ERROR_SUCCESS)
//					{
//						TRACE_LOG(L"Error! ))");
//					}
//					//
//						TCHAR    achKey[1024];   // buffer for subkey name
//						DWORD    cbName;                   // size of name string 
//						TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
//						DWORD    cchClassName = MAX_PATH;  // size of class string 
//						DWORD    cSubKeys=0;               // number of subkeys 
//						DWORD    cbMaxSubKey;              // longest subkey size 
//						DWORD    cchMaxClass;              // longest class string 
//						DWORD    cValues;              // number of values for key 
//						DWORD    cchMaxValue;          // longest value name 
//						DWORD    cbMaxValueData;       // longest value data 
//						DWORD    cbSecurityDescriptor; // size of security descriptor 
//						FILETIME ftLastWriteTime;      // last write time 
// 
//						DWORD i, retCode; 
// 
//						TCHAR  achValue[1024]; 
//						DWORD cchValue = 1024; 
// 
//						// Get the class name and the value count. 
//						retCode = RegQueryInfoKey(
//							hKey,                    // key handle 
//							achClass,                // buffer for class name 
//							&cchClassName,           // size of class string 
//							NULL,                    // reserved 
//							&cSubKeys,               // number of subkeys 
//							&cbMaxSubKey,            // longest subkey size 
//							&cchMaxClass,            // longest class string 
//							&cValues,                // number of values for this key 
//							&cchMaxValue,            // longest value name 
//							&cbMaxValueData,         // longest value data 
//							&cbSecurityDescriptor,   // security descriptor 
//							&ftLastWriteTime);       // last write time 
//						//
//						if (retCode != 0)
//						{
//							TRACE_LOG("Error! ))");
//						}
//				}
//#				endif
				//
				HKEY hKey = 0;
				try
				{
					LONG r1 = RegOpenKeyEx(rootKey,keyName,0,KEY_QUERY_VALUE| KEY_ENUMERATE_SUB_KEYS,&hKey);
					if (r1 != ERROR_SUCCESS)
					{
						HRESULT hr = HRESULT_FROM_WIN32(r1);
						if (! throwOnError)
						{
							if (pResult) *pResult = hr;
							//
#							ifdef _TRACE_REGISTRY_READS
							TRACE_LINE(_T("(������ ����������)"));
#							endif
							//
							return _T("");
						}
						throw FunctionError(hr);
					}
					//
					{
						//TCHAR    achKey[1024];   // buffer for subkey name
						//DWORD    cbName;                   // size of name string 
						TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
						DWORD    cchClassName = MAX_PATH;  // size of class string 
						DWORD    cSubKeys=0;               // number of subkeys 
						DWORD    cbMaxSubKey;              // longest subkey size 
						DWORD    cchMaxClass;              // longest class string 
						DWORD    cValues;              // number of values for key 
						DWORD    cchMaxValue;          // longest value name 
						DWORD    cbMaxValueData;       // longest value data 
						DWORD    cbSecurityDescriptor; // size of security descriptor 
						FILETIME ftLastWriteTime;      // last write time 
 
						DWORD i, retCode; 
 
						TCHAR  achValue[1024]; 
						DWORD cchValue = 1024; 
 
						// Get the class name and the value count. 
						retCode = RegQueryInfoKey(
							hKey,                    // key handle 
							achClass,                // buffer for class name 
							&cchClassName,           // size of class string 
							NULL,                    // reserved 
							&cSubKeys,               // number of subkeys 
							&cbMaxSubKey,            // longest subkey size 
							&cchMaxClass,            // longest class string 
							&cValues,                // number of values for this key 
							&cchMaxValue,            // longest value name 
							&cbMaxValueData,         // longest value data 
							&cbSecurityDescriptor,   // security descriptor 
							&ftLastWriteTime);       // last write time 
						//
						if (retCode != 0)
						{
							TRACE_LOG("Error! ))");
						}
						//
						//if (cValues) 
						//{
						//	//printf( "\nNumber of values: %d\n", cValues);

						//	for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++) 
						//	{ 
						//		cchValue = 1024; 
						//		achValue[0] = '\0'; 
						//		retCode = RegEnumValue(hKey, i, 
						//			achValue, 
						//			&cchValue, 
						//			NULL, 
						//			NULL,
						//			NULL,
						//			NULL);
 
						//		if (retCode == ERROR_SUCCESS ) 
						//		{ 
						//			//_tprintf(TEXT("(%d) %s\n"), i+1, achValue); 
						//		} 
						//	}
						//}
					}
					//
					BYTE data[1024];
					DWORD dataSize = 1024;
					DWORD dataType;
					LONG r2 = RegQueryValueEx(
						hKey,
						attrName,
						0,
						0, // &dataType,
						data,
						&dataSize
						);
					if (r2 != ERROR_SUCCESS)
					{
						HRESULT hr = HRESULT_FROM_WIN32(r2);
						if (! throwOnError)
						{
							if (pResult) *pResult = hr;
							//
#							ifdef _TRACE_REGISTRY_READS
							TRACE_LINE(_T("(������ ����������)"));
#							endif
							//
							return _T("");
						}
						throw FunctionError(hr);
					}
					//
					CBlob b;
					b.Allocate(dataSize+sizeof(TCHAR));
					CopyMemory(b.GetBuffer(),data,dataSize);
					((TCHAR*)(b.GetBuffer()+dataSize))[0] = 0;
					CString value((const TCHAR*)data);
					if (pResult) *pResult = S_OK;
					//
					if (hKey) RegCloseKey(hKey);
					//
#					ifdef _TRACE_REGISTRY_READS
					//TRACE_LINE1(_T("��������: "), _S(value).GetString() );
#					endif
					//
					return value;
				}
				catch(...)
				{
					if (hKey) RegCloseKey(hKey);
					//
					throw;
				}
			}
			_FCatch()
		}

		inline static void SetRegDWORDValue(HKEY rootKey,
			const CString& keyName, const CString& attrName, DWORD value, 
			bool throwOnError=true, HRESULT* pResult=0) 
		{
			try
			{
				HKEY hKey = 0;
				try
				{
					LONG r1 = RegOpenKeyEx(rootKey,keyName,0,KEY_SET_VALUE,&hKey);
					if (r1 != ERROR_SUCCESS)
					{
						HRESULT hr = HRESULT_FROM_WIN32(r1);
						if (! throwOnError)
						{
							if (pResult) *pResult = hr;
						}
						throw FunctionError(hr);
					}
					//
					LONG r2 = RegSetValueEx(
						hKey,
						attrName,
						0,
						REG_DWORD,
						(const BYTE*)&value,
						sizeof(DWORD)
						);
					if (r2 != ERROR_SUCCESS)
					{
						HRESULT hr = HRESULT_FROM_WIN32(r2);
						if (! throwOnError)
						{
							if (pResult) *pResult = hr;
						}
						throw FunctionError(hr);
					}
					if (pResult) *pResult = S_OK;
					//
					if (hKey) RegCloseKey(hKey);
				}
				catch(...)
				{
					if (hKey) RegCloseKey(hKey);
					//
					throw;
				}
			}
			_FCatch()
		}

		inline static DWORD GetRegDWORDValue(HKEY rootKey,
			const CString& keyName,
			const CString& attrName,
			bool throwOnError=true,
			HRESULT* pResult=0)
		{
			try
			{
				HKEY hKey = 0;
				try
				{
					LONG r1 = RegOpenKeyEx(rootKey,keyName,0,KEY_QUERY_VALUE,&hKey);
					if (r1 != ERROR_SUCCESS)
					{
						HRESULT hr = HRESULT_FROM_WIN32(r1);
						if (! throwOnError)
						{
							if (pResult) *pResult = hr;
							//
#							ifdef _TRACE_REGISTRY_READS
							TRACE_LINE(_T("(������ ����������)"));
#							endif
							//
							return (DWORD)-1; 
						}
						throw FunctionError(hr);
					}
					//
					BYTE data[1024];
					DWORD dataSize = 1024;
					DWORD dataType;
					LONG r2 = RegQueryValueEx(
						hKey,
						attrName,
						0,
						&dataType,
						data,
						&dataSize
						);
					if (r2 != ERROR_SUCCESS)
					{
						HRESULT hr = HRESULT_FROM_WIN32(r2);
						if (! throwOnError)
						{
							if (pResult) *pResult = hr;
							//
#							ifdef _TRACE_REGISTRY_READS
							TRACE_LINE(_T("(������ ����������)"));
#							endif
							//
							return (DWORD)-1;
						}
						throw FunctionError(hr);
					}
					//
					Blob b;
					b.Allocate(dataSize); 
					CopyMemory(b.GetBuffer(), data, dataSize); 
					DWORD value = *((DWORD*)(b.GetBuffer())); 
					//
					return value;
				}
				catch(...)
				{
					if (hKey) RegCloseKey(hKey);
					//
					throw;
				}
			}
			_FCatch()
		}

		inline static SharedArray<CString> ListRegKeys(HKEY rootKey,const CString& keyName,
			bool throwOnError=true,HRESULT* pResult=0)
		{
			try
			{
				SharedArray<CString> childKeyNames;
				HKEY hKey = 0;
				try
				{
					LONG r1 = RegOpenKeyEx(rootKey,keyName,0,
						KEY_QUERY_VALUE|KEY_ENUMERATE_SUB_KEYS ,&hKey);
					if (r1 != ERROR_SUCCESS)
					{
						HRESULT hr = HRESULT_FROM_WIN32(r1);
						if (! throwOnError)
						{
							if (pResult) *pResult = hr;
							return childKeyNames;
						}
						throw FunctionError(hr);
					}
					//
					DWORD n; // ����� �������� ����� 
					wchar_t achClass[MAX_PATH] = L"";
					DWORD cchClassName = MAX_PATH;
					LONG r2 = RegQueryInfoKey(hKey,achClass,&cchClassName,0,&n,0,0,0,0,0,0,0);
					if (r2 != ERROR_SUCCESS)
					{
						HRESULT hr = HRESULT_FROM_WIN32(r2);
						if (! throwOnError)
						{
							if (pResult) *pResult = hr;
							if (hKey) RegCloseKey(hKey);
							return childKeyNames;
						}
						throw FunctionError(hr);
					}
					//
					const long MAX_KEY_LENGTH = 16383;
					wchar_t subKey[MAX_KEY_LENGTH];
					DWORD cbName = MAX_KEY_LENGTH;
					FILETIME ftLastWriteTime;
					for (int i = 0; i<n; i++)
					{
						cbName = MAX_KEY_LENGTH;
						LONG r4 = RegEnumKeyExW(hKey, i,
							subKey,
							&cbName,
							NULL,
							NULL,
							NULL,
							&ftLastWriteTime);
						if (r4 == ERROR_SUCCESS)
						{
							// _tprintf(TEXT("(%d) %s\n"), i + 1, achKey); 
							childKeyNames.Add(subKey);
						}
					}
					//
					//bool done;
					//int i = 0;
					//do
					//{
					//	DWORD nameSize = 1024;
					//	TCHAR name[1024];
					//	LONG r3 = RegEnumKeyEx(hKey,i,name,&nameSize,0,0,0,0);
					//	if (r3 == ERROR_NO_MORE_ITEMS)
					//	{
					//		done = true;
					//	}
					//	if (r3 < 0)
					//	{
					//		HRESULT hr = HRESULT_FROM_WIN32(r3);
					//		if (! throwOnError)
					//		{
					//			if (pResult) *pResult = hr;
					//			if (hKey) RegCloseKey(hKey);
					//			return childKeyNames;
					//		}
					//		throw FunctionError(hr);
					//	}
					//	else // SUCCESS
					//	{						
					//		name[nameSize] = 0;
					//		childKeyNames.Add(name);
					//		//
					//		done = false;
					//	}
					//	++i;
					//}
					//while (! done);
					//
					if (hKey) RegCloseKey(hKey);
					//
					return childKeyNames;
				}
				catch(...)
				{
					if (hKey) RegCloseKey(hKey);
					//
					throw;
				}
			}
			_FCatch()
		}

		struct RegValue		
		{
			DWORD Type;
			CString vStr;
			int vInt;
			Blob vBinary;

			RegValue()
			{
				Type = REG_BINARY;
			}

			const RegValue& operator =(const RegValue& other)
			{
				Type = other.Type;
				vStr = other.vStr;
				vInt = other.vInt;
				vBinary.Allocate(other.vBinary.Length());
				CopyMemory(vBinary.GetBuffer(),(const BYTE*)other.vBinary,other.vBinary.Length());
				return *this;
			}

			RegValue(const RegValue& other)
			{
				operator =(other);
			}

			void SetType(DWORD valueType)
			{
				if (vBinary.IsEmpty())
				{
					Type = REG_BINARY;
					return;
				}
				int n = vBinary.Length();
				//
				if (vBinary.Length() == 0)
				{
					Type = REG_BINARY;
					return;
				}
				//
				try
				{
					Type = valueType;
					if (Type == REG_SZ)
					{
						CBlob b;
						b.Allocate(n/sizeof(TCHAR) + 1);
						CopyMemory((void*)b.GetBuffer(),vBinary.GetBuffer(),sizeof(TCHAR)*(n/sizeof(TCHAR)));
						b.GetBuffer()[n] = (TCHAR)0;
						vStr = CString((const TCHAR*)b);
					}
					else if (Type == REG_DWORD)
					{
						if (n < sizeof(DWORD)) throw MethodError(L"��������� ������ ��� DWORD!");
						//
						DWORD dwValue = *( (const DWORD*)(const void*)(const BYTE*)vBinary );
						vInt = (int)dwValue;
					}
					else
					{
						Type = REG_BINARY;
					}
				}
				catch(Exception& e)
				{
					TRACE_LOG(e.ToString());
				}
				catch(...)
				{
					Type = REG_BINARY;
					vBinary = Blob();
				}
			}
		};

		inline static SharedArray<RegValue> ListRegValues(HKEY rootKey,const CString& keyName,
			bool throwOnError=true,HRESULT* pResult=0)
		{
			try
			{
				SharedArray<RegValue> results;
				HKEY hKey = 0;
				try
				{
					// ��������� ����, � ������� ����� ������������� ��������
					//
					LONG r1 = RegOpenKeyEx(rootKey,keyName,0,KEY_QUERY_VALUE,&hKey);
					if (r1 != ERROR_SUCCESS)
					{
						HRESULT hr = HRESULT_FROM_WIN32(r1);
						if (! throwOnError)
						{
							if (pResult) *pResult = hr;
							return results;
						}
						throw FunctionError(hr);
					}
					//
					DWORD n; // ����� �������� (���������) 
					LONG r2 = RegQueryInfoKey(hKey,0,0,0,0,0,0,&n,0,0,0,0);
					if (r2 != ERROR_SUCCESS)
					{
						HRESULT hr = HRESULT_FROM_WIN32(r2);
						if (! throwOnError)
						{
							if (pResult) *pResult = hr;
							if (hKey) RegCloseKey(hKey);
							return results;
						}
						throw FunctionError(hr);
					}
					//
					bool done;
					int i = 0;
					do
					{
						DWORD nameSize = 1024;
						TCHAR name[1024];
						DWORD valueType = REG_BINARY;
						DWORD dataSize = 4096;
						Blob data;
						data.Expand(dataSize);
						LONG r3 = RegEnumValue(hKey,i,name,&nameSize,0,&valueType
							,data.GetBuffer(),&dataSize);
						if (r3 == ERROR_NO_MORE_ITEMS)
						{
							done = true;
						}
						if (r3 != ERROR_SUCCESS)
						{
							HRESULT hr = HRESULT_FROM_WIN32(r3);
							if (! throwOnError)
							{
								if (pResult) *pResult = hr;
								if (hKey) RegCloseKey(hKey);
								return results;
							}
							throw FunctionError(hr);
						}
						else // SUCCESS
						{	
							data.SetSize(dataSize);
							//
							RegValue& value = results[i];
							value.vBinary.Allocate(data.Length());
							CopyMemory(value.vBinary.GetBuffer(),data.GetBuffer(),data.Length());
							//
							value.SetType(valueType);
							//
							done = false;
						}
						++i;
						if (i == (int)n) done = true;
					}
					while (! done);
					//
					if (hKey) RegCloseKey(hKey);
					//
					return results;
				}
				catch(...)
				{
					if (hKey) RegCloseKey(hKey);
					//
					throw;
				}
			}
			_FCatch()
		}

		inline static string GetCabinetVersion() 
		{
			try
			{
				CString keyName = _T("SOFTWARE\\\\Cabinet"); 
				CString attrName = _T("Version"); 
				//
				string vStr = _W(GetRegStringValue(
					HKEY_CURRENT_USER,
					keyName,
					attrName, false)); 
				vStr.Trim(); 
				//
				if (vStr.GetLength() > 0) return vStr; 
				//
				vStr = _W(GetRegStringValue(
					HKEY_LOCAL_MACHINE,
					keyName,
					attrName, false)); 
				vStr.Trim(); 
				//
				return vStr; 
			}
			_Catch() 
		}




		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// ��������� ���������

		inline static CString ExpandEnvVars(const CString& value)
		{
			try
			{
				CString s = value;
				//
				bool done = false;
				while (! done)
				{
					int p0 = s.Find(_T("%"));
					if (p0 == -1)
					{
						done = true;
					}
					else
					{
						CString r = s.Right(s.GetLength()-p0-1);
						int p1 = r.Find(_T("%"));
						if (p1 == -1)
						{
							done = true;
						}
						else
						{
							CString varName = r.Left(p1);
							CString rr = r.Right(r.GetLength()-p1-1);
							//
							CString varVal;
							try
							{
								varVal.GetEnvironmentVariable(varName);
							}
							catch(...)
							{
							}
							//
							s = s.Left(p0) + varVal + rr;
						}
					}
				}
				//
				return s;
			}
			_FCatch()
		}

		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// �������� ������� � ������ ����������

		inline static int GetFileSize(const CString& path)
		{
			try
			{
				HANDLE hFile = CreateFile(path,
					FILE_READ_ATTRIBUTES,
					FILE_SHARE_READ,
					0,
					OPEN_EXISTING,
					0,0);
				int size = (int)::GetFileSize(hFile,0); 
				if (hFile) CloseHandle(hFile);
				return size;
			}
			_Catch()
		}

		inline static bool PathIsDirectory(const CString& path)
		{
			try
			{
				DWORD a = GetFileAttributes(path);
				return (a & FILE_ATTRIBUTE_DIRECTORY) != 0;
			}
			_Catch()
		}

		inline static CString CreateDirectoryAndTest(const CString& path)
		{
			try
			{
				if (path.GetLength() == 0) return path;
				//
				if (! CreateDirectory(path,0))
				{
					DWORD dwErr = GetLastError();
					if (dwErr != ERROR_ALREADY_EXISTS)
					{
						HRESULT rc = HRESULT_FROM_WIN32(dwErr);
						AlarmAboutException( FunctionError(rc) );
						return _T("");
					}
				}
				//
				CString testDir = path + _T("\\__test__");
				if (! CreateDirectory(testDir,0))
				{
					DWORD dwErr = GetLastError();
					if (dwErr != ERROR_ALREADY_EXISTS)
					{
						HRESULT rc = HRESULT_FROM_WIN32(dwErr);
						AlarmAboutException( FunctionError(rc) );
						return _T("");
					}
				}
				else
				{
					RemoveDirectory(testDir);
				}
				//
				return path;
			}
			_FCatch()
		}

		inline static CString TouchDirectory(const CString& path) 
		{
			try
			{
				CString P = Machine::CreateDirectoryAndTest( path );
				if (P.GetLength() == 0) 
				{
					string msg = FormatStr(L"������ ��� �������� ����� '%s'", _W(path).GetString() );
					::::Exception e = FunctionError(msg);
					////OutputDebugString(_S(e.GetXml())); 
					throw e; 
				}
				return path;
			}
			_Catch() 
		}

		inline static CString TestDirectory(const CString& path,const CString& dirName=_T("__test__"),
			bool removeTestDir=true)
		{
			try
			{
				if (path.GetLength() == 0) return path;
				//
				CString testDir = path + dirName;
				if (! CreateDirectory(testDir,0))
				{
					DWORD dwErr = GetLastError();
					if (dwErr != ERROR_ALREADY_EXISTS)
					{
						HRESULT rc = HRESULT_FROM_WIN32(dwErr);
						AlarmAboutException( FunctionError(rc) );
						return _T("");
					}
				}
				else
				{
					if (removeTestDir) RemoveDirectory(testDir);
				}
				//
				return path;
			}
			_FCatch()
		}

		inline static void CreateDirectoriesForFile(const CString& path,const CString& begin) 
		{
			int slash_p = -1;
			int p = path.Find(_T("\\"));
			while (p != -1)
			{
				slash_p = p;
				p = path.Find(_T("\\"),p+1);
			}
			if (slash_p == -1) throw FunctionError(L"��������� ������ ����");
			//
			CString dir = path.Left(slash_p);
			//
			CreateDirectories(dir,begin);
		}

		inline static void CreateDirectories(const CString& path,const CString& begin) 
		{
			if (begin.GetLength() == 0) throw FunctionError(L"��������� �������� ��������� begin");
			//
			CString b = begin;
			if (b.Right(1) != _T("\\")) b += _T("\\");
			//
			CString relPath = path.Right(path.GetLength()-b.GetLength());
			//
			int p = relPath.Find(_T("\\"));
			while (p != -1)
			{
				CString name = relPath.Left(p);
				CString dir = b + name;
				TouchDirectory(dir);
				//
				b = dir+_T("\\");
				relPath = relPath.Right(relPath.GetLength()-name.GetLength()-1);
				p = relPath.Find(_T("\\"));
			}
			CString dir = TouchDirectory(b + relPath);
		}

		// ���� ���� � �����

		inline static CString FindFile(const CString& root,const CString& searchOrName,bool inSubFolders=false)
		{
			try
			{
				CString name = searchOrName;
				name.MakeLower();
				//
				bool useSearch = (name.Find(_T("*")) != -1);
				CString search = useSearch ? name : _T("*");
				SharedArray<CString> L = ListFiles(root,search);
				if (useSearch) 
				{
					if (L.Length() > 0) return L[0];
				}
				else
				{
					for (int k = 0; k < L.Length(); ++k)
					{
						CString path = root + _T("\\") + _S(L[k]);
						if (PathIsDirectory(path))
						{
							if (inSubFolders)
							{
								CString path_2 = FindFile(path,searchOrName,inSubFolders);
								if (path_2.GetLength() != 0) return path_2;
							}
						}
						else
						{
							if (_S(L[k]) == name) return path;
						}
					}
				}
				return _T("");
			}
			_Catch()
		}

		inline static bool FileExists(const CString& path)
		{
			try
			{
				HANDLE h = CreateFile(path,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
				if (h == INVALID_HANDLE_VALUE) 
				{
#					ifdef _DEBUG
					HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
					AlarmAboutException( FunctionError(rc) );
#					endif
					return false;
				}
				CloseHandle(h);
				return true;
			}
			_FCatch()
		}

		inline static bool DirectoryExists(const CString& path)
		{
			try
			{
//				HANDLE h = CreateFile(path,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING
//					,FILE_FLAG_BACKUP_SEMANTICS,0);
//				if (h == INVALID_HANDLE_VALUE) 
//				{
//#					ifdef _DEBUG
//					HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
//					AlarmAboutException( FunctionError(rc) );
//#					endif
//					return false;
//				}
//				CloseHandle(h);
//				return true;
				//
				DWORD attribs = ::GetFileAttributes(path);
				if (attribs == INVALID_FILE_ATTRIBUTES) 
				{
					return false;
				}
				return true;
			}
			_FCatch()
		}

		inline static SharedArray<CString> ListFiles(const CString& root,const CString& search=_T("*")
			,SharedArray<CString>* names = NULL 
			)
		{
			try
			{
				SharedArray<CString> result;
				//
				CString dirAll = root + _T("\\") + search;
				WIN32_FIND_DATA _f_data;
				HANDLE _f = FindFirstFile(dirAll,&_f_data);
				bool done = false;
				while ((_f != INVALID_HANDLE_VALUE) & (! done))
				{
					CString file(_f_data.cFileName);
					//
					if (file.Left(1) != _T("."))
					{
						CString path = root + _T("\\") + file; 
						result.Add(path);
						if (names) (*names).Add(file); 
					}
					//
					if (! FindNextFile(_f,&_f_data)) done = true;
				}
				// if (_f) 					if (_f != INVALID_HANDLE_VALUE) CloseHandle(_f);
				//
				return result;
			}
			_FCatch()
		}



		inline static SharedArray<CString> ListFilesDeep1(const CString& root
			,const CString& search=_T("*")
			,const CString& prefix=_T("")
			)
		{
			try
			{
				SharedArray<CString> result;
				//
				CString dirAll = root + _T("\\*");
				WIN32_FIND_DATA _f_data;
				HANDLE _f = FindFirstFile(dirAll,&_f_data);
				bool done = false;
				while ((_f != INVALID_HANDLE_VALUE) & (! done))
				{
					CString folder(_f_data.cFileName);
					//
					if (folder.Left(1) != _T("."))
					{
						CString folder_search_path = root + _T("\\") + folder + prefix;
						//
						CString search_dirAll = folder_search_path + _T("\\") + search;
						WIN32_FIND_DATA _search_f_data;
						HANDLE _search_f = FindFirstFile(search_dirAll,&_search_f_data);
						bool done = false;
						while ((_search_f != INVALID_HANDLE_VALUE) & (! done))
						{
							CString search_file(_search_f_data.cFileName);
							//
							if (search_file.Left(1) != _T("."))
							{
								CString path = folder_search_path + _T("\\") + search_file;
								result.Add(path);
							}
							//
							if (! FindNextFile(_search_f,&_search_f_data)) done = true;
						}
					}
					//
					if (! FindNextFile(_f,&_f_data)) done = true;
				}
				//
				return result;
			}
			_FCatch()
		}



		// ����� 

		inline static bool SafeRemoveFile(const CString& filePathToDelete
			// { ������
			,bool fileOnDisk=true
			// } ������
			)
		{
			try
			{
				bool canDelete = true;
				//
				CString path = filePathToDelete;
				path.Trim(); 
				//
				if (path.GetLength() <= 3)
				{
					canDelete = false; 
				}
				//
				if (path.Find(_T('*')) != -1) canDelete = false; 
				//
				if (fileOnDisk)
				{
					if (path.Left(1) == _T("\\")) canDelete = false; 
					if (path[2] != _T(':')) canDelete = false; 
				}
				//
				if (canDelete)
				{
					if (! DeleteFile(path)) 
					{
						HRESULT rc = HRESULT_FROM_WIN32(GetLastError()); 
						throw MethodError(rc); 
					}
				}
				//
				return canDelete; 
			}
			_Catch() 
		}

		// �����

		inline static SharedArray<CString> ListDrives(UINT flags,bool excludeDiskette=true,
			const CString& useDrive=_T(""))
		{
			try
			{
				SharedArray<CString> drives;
				//
				if (useDrive.GetLength() > 0)
				{
					drives.Add(useDrive);
					return drives;
				}
				//
				DWORD driveMask = GetLogicalDrives();
				char letter = 'A';
				//
				for (int i = 0; i < 16; ++i)
				{
					if (driveMask & 0x1)
					{
						CString drive = _S(CStringA(&letter,1));
						UINT driveType = GetDriveType(drive + _T(":\\"));
						//
						// ��������� removable
						//
						bool include = false;
						//
						if ((driveType == flags) || (! flags))
						{
							include = true;
							if (false)
							if (flags == DRIVE_REMOVABLE)
							{
								ULARGE_INTEGER FreeBytesAvailable;
								ULARGE_INTEGER TotalNumberOfBytes;
								ULARGE_INTEGER TotalNumberOfFreeBytes;
								//
								if (GetDiskFreeSpaceEx(
									drive + _T(":\\"),
									&FreeBytesAvailable,
									&TotalNumberOfBytes,
									&TotalNumberOfFreeBytes
									))
								{
									if (
										(TotalNumberOfBytes.HighPart == 0) && 
										(TotalNumberOfBytes.LowPart <= 2*1024*1024)
										)
									{
										include = false;
									}
								}
							}
							//
							if (excludeDiskette)
							{
								if (! bool((driveType & DRIVE_FIXED) == DRIVE_FIXED))
								{
									if ((drive == _T("A")) || (drive == _T("B"))) include = false;
								}
							}
						}
						//
						if (useDrive.GetLength() > 0)
						{
							include = (useDrive == drive);
						}
						//
						if (include)
						{
							drives.Add(drive);
						}
					}
					//
					driveMask  = driveMask >> 1;
					letter += 1;
				}
				//
				return drives;
			}
			_FCatch()
		}

		//inline static SharedArray<CString> ListVolumes()
		//{
		//	try
		//	{
		//		TCHAR volName[256];
		//		DWORD volNameSize = 256;
		//		HANDLE h = 0;
		//		do
		//		{
		//			if (h == 0) h = FindFirstVolume(volName,volNameSize);
		//			else 
		//			{
		//				if (! FindNextVolume(h,volName,volNameSize))
		//				{
		//					h = INVALID_HANDLE_VALUE;
		//				}
		//			}
		//			//
		//			if (h != INVALID_HANDLE_VALUE)
		//			{
		//				// �����������
		//				//
		//				TRACE_LOG(volName);
		//				//
		//				// ��������� � ������
		//				//
		//			}
		//		}
		//		while(h != INVALID_HANDLE_VALUE);
		//	}
		//	_FCatch()
		//}
	};

} // namespace  
