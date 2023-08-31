/*
 SmartUtil.h : ��������� �������.

 $Name: work1 $
 $Revision: 1.1.2.6 $
 $Date: 2008/10/31 16:00:32 $
 */

#pragma once 

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


// ----
// h

#include <atlenc.h> // TODO: Base64 streams...
#include "AtlX.h"


// ----
// lib 

#pragma comment(lib, "RpcRT4.lib" )
#pragma comment(lib, "Version.lib" )


#ifndef VER_SUITE_STORAGE_SERVER
#define VER_SUITE_STORAGE_SERVER (0x00002000)
#endif

#ifndef VER_SUITE_COMPUTE_SERVER
#define VER_SUITE_COMPUTE_SERVER (0x00004000)
#endif


namespace  { 

	
	static string NewGuidStr()
	{
		try
		{
			UUID guid = GUID_NULL; 
			::UuidCreate(&guid); 
			//
			unsigned char* GUIDA;
			UuidToStringA(&guid,&GUIDA);
			string GUIDs((TCHAR*)GUIDA);
			RpcStringFreeA(&GUIDA);
			return GUIDs;
		}
		_Catch()
	}




	// ===================================================================================
	// ��������� ��������� ��������� 
	
	inline static int ByteToHexDigit(BYTE b)
	{
		if ((b >= 0x30) && (b <= 0x39)) 
		{
			return b - 0x30; 
		}
		if ((b >= 0x41) && (b <= 0x46)) 
		{
			return b - 0x41 + 10; 
		}
		if ((b >= 0x61) && (b <= 0x66)) 
		{
			return b - 0x61 + 10; 
		}
		else
		{
			return -1; 
		}
	}

	inline static string GetHex(BYTE b)
	{
		try
		{
			string s = FormatStr(L"%02x", (int)b);
			return s;
		}
		_Catch()
	}

	inline static string GetHex(Blob buf)
	{
		try
		{
			string s;
			for (int i = 0; i < buf.Length(); i++)
			{
				s += GetHex(buf[i]);
			}
			return s;
		}
		_Catch()
	}

	inline static string GetHexBwd(Blob buf)
	{
		try
		{
			string s;
			int n = buf.Length(); 
			for (int i = 0; i < n; i++)
			{
				s += GetHex(buf[n-1-i]);
			}
			return s;
		}
		_Catch()
	}

	inline static Blob StringToBytes(const string& data)
	{
		Blob bytes;
		bytes.Allocate(data.GetLength() * 2);
		for (int k = 0; k < data.GetLength(); ++k) 
		{
			wchar_t sym = data[k];
			ULONG code = sym;
			bytes[2*k+1] = (BYTE)(code & 0x00ff);
			bytes[2*k] = (BYTE)((code & 0xff00) >> 8);
		}
		return bytes;
	}

	inline static string ToBase64NoPad(Blob data)
	{
		int len = data.Length()*2 + 256;
		char* s = new char[len];
		Base64Encode(data.GetBuffer(), data.Length()
			, s, &len
			, ATL_BASE64_FLAG_NOPAD 
			);
		string result(CStringA(s,len));
		delete[] s;
		return result;
	}

	inline static string ToBase64NoPadNoCRLF(Blob data)
	{
		int len = data.Length()*2 + 256;
		char* s = new char[len];
		Base64Encode(data.GetBuffer(), data.Length()
			, s, &len
			, ATL_BASE64_FLAG_NOPAD | ATL_BASE64_FLAG_NOCRLF 
			);
		string result(CStringA(s,len));
		delete[] s;
		return result;
	}

	inline static string ToBase64NoCRLF(Blob data)
	{
		int len = data.Length()*2 + 256;
		char* s = new char[len];
		Base64Encode(data.GetBuffer(), data.Length()
			, s, &len
			, ATL_BASE64_FLAG_NOCRLF 
			);
		string result(CStringA(s,len));
		delete[] s;
		return result;
	}

	inline static string ToBase64NoPad_NewQuest_1(Blob data)
	{
		const DWORD paddingFlags = CRYPT_STRING_NOCR; 
		//
		DWORD dest_size = 0;
		DWORD dest_write = 0;
		if (!::CryptBinaryToStringW(data.GetBuffer(), data.Length(), CRYPT_STRING_BASE64 | paddingFlags
			, NULL, &dest_size))
		{
			HRESULT rc = HRESULT_FROM_WIN32(GetLastError()); 
			throw MethodError(rc); 
		}
		CBlobW r;
		r.Allocate(dest_size+1); 
		r[r.Length()-1] = 0; 
		//
		dest_write = dest_size; 
		//
		if (!::CryptBinaryToStringW(data.GetBuffer(), data.Length(), CRYPT_STRING_BASE64 | paddingFlags
			, r.GetBuffer(), &dest_write))
		{
			HRESULT rc = HRESULT_FROM_WIN32(GetLastError()); 
			throw MethodError(rc); 
		}
		//
		string result(r.GetBuffer()); 
		result.Trim(); 
		return result;
	}

	inline static string ToBase64Padding(Blob data)
	{
		int len = data.Length()*2 + 256;
		char* s = new char[len];
		Base64Encode(data.GetBuffer(),data.Length(),s,&len,0);
		string result(CStringA(s,len));
		delete[] s;
		return result;
	}

	inline static string __ToBase64(Blob data)
	{
		return ToBase64Padding(data);
	}

	inline static string __ToBase64String(Blob data)
	{
		return __ToBase64(data); 
	}

	inline static string ToBase64_4Url(Blob data)
	{
		return ToBase64NoPad(data); 
	}

	inline static Blob FromBase64String(const string& data64) 
	{
		try
		{
			CStringA a(data64);
			int size = data64.GetLength() + 256;
			BYTE* buf = new BYTE[size];
			if (Base64Decode(a.GetString(),a.GetLength(),buf,&size)) 
			{
				Blob data;
				data.Allocate(size);
				CopyMemory(data.GetBuffer(),buf,size);
				delete[] buf;
				return data;
			}
			else
			{
				string msg = L"������ ��� ������������� base64, ����� '" + data64 + L"'"; 
				throw MethodError(msg); 
			}
		}
		_Catch()
	}

	inline static string NormalizeBin64(const string& v1) 
	{
		try
		{
			Blob b = FromBase64String(v1); 
			string v2 = __ToBase64(b); 
			return v2; 
		}
		_Catch() 
	}

	inline static string Base64Text_4Url(const string& data64)
	{
		return ToBase64_4Url(
			FromBase64String(data64)
			);
	}

	inline static ULONG RandomInt32()
	{
		HCRYPTPROV hCryptProv;
		//
		if (! CryptAcquireContext(
			&hCryptProv, 
			NULL, 
			NULL, 
			PROV_RSA_FULL, 
			CRYPT_VERIFYCONTEXT)) 
		{
			throw MethodError(L"������ ��� ������ CryptAcquireContext");
		}
		//
		ULONG v;
		//
		if (! CryptGenRandom(hCryptProv,sizeof(v),(BYTE*)&v))
		{
			throw MethodError(L"������ ��� ������ CryptGenRandom");
		}
		//
		CryptReleaseContext(hCryptProv,0);
		//
		return v;
	}

	inline static bool GetFlagValue(const string& value) 
	{
		try
		{
			string v = value;
			v.Trim();
			v.MakeLower();
			//
			bool x = false;
			if ((v == L"true") || (v == L"1") || (v == L"-1") || (v == L"yes") || (v == L"��") || (v == L"on"))
			{
				x = true; 
			}
			return x;
		}
		_Catch()
	}













	// ===========================================================================================
	// ��������� ��������� ���������� 

	inline static CStringW DecodeToWideString(Blob b,DWORD codePage)
	{
		try
		{
			if (b.IsEmpty()) 
				return L"";
			//
			CBlobW u;
			int size1 = MultiByteToWideChar(codePage,MB_ERR_INVALID_CHARS,
				(char*)b.GetBuffer(),b.GetSize(),
				0,0);
			if (! size1)
			{
				HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
				throw FunctionError(rc);
			}
			u.Allocate(size1);
			size1 = MultiByteToWideChar(codePage,MB_ERR_INVALID_CHARS,
				(char*)b.GetBuffer(),b.GetSize(),
				u.GetBuffer(),u.GetSize());
			if (! size1)
			{
				HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
				throw FunctionError(rc);
			}
			//
			CStringW uValue(u.GetBuffer(),u.GetSize());
			// TRACE_LOG2(_T("Converted: %d, %s"), (int)size1, CString(uValue).GetString() );
			//
			return uValue;
		}
		_FCatch()
	}

	inline static CStringW CodePageToEncoding(DWORD codePage)
	{
		try
		{
			switch(codePage)
			{
			//case CP_UNICODE:
			//	return L"utf-16";
			case CP_UTF8:
				return L"utf-8";
			case 1251:
				return L"windows-1251";
			default:
				throw MethodError(L"���������������� CODE PAGE: ___d");
			}
		}
		_FCatch()
	}

	inline static DWORD EncodingNameToCodePage(const string& encoding)
	{
		try
		{
			string enc = encoding;
			enc.MakeLower();
			DWORD codePage; 
			//if (enc == L"utf-16") codePage = CP_UNICODE;
			if (enc == L"utf-8") codePage = CP_UTF8;
			else if (enc == L"windows-1251") codePage = 1251;
			else
			{
				throw MethodError(L"���������������� ���������: " + _W(encoding));
			}
			return codePage;
		}
		_FCatch()
	}

	inline static CStringW DecodeToWideString(Blob b,const string& encoding)
	{
		try
		{
			return DecodeToWideString(b,EncodingNameToCodePage(encoding));
		}
		_FCatch()
	}

	inline static CStringW UTF8ToWideString(Blob b)
	{
		try
		{
			// TRACE_LOG1(_T("UTF-8: %s"), (const TCHAR*)BlobToHex(b) );
			//			 
			CBlobW u;
			int size1 = MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,
				(char*)b.GetBuffer(),b.GetSize(),
				0,0);
			if (! size1)
			{
				HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
				throw FunctionError(rc);
			}
			u.Allocate(size1);
			size1 = MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,
				(char*)b.GetBuffer(),b.GetSize(),
				u.GetBuffer(),u.GetSize());
			if (! size1)
			{
				HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
				throw FunctionError(rc);
			}
			
			CStringW uValue(u.GetBuffer(),u.GetSize());
			// TRACE_LOG2(_T("Converted: %d, %s"), (int)size1, CString(uValue).GetString() );
			
			return uValue;
		}
		_FCatch()
	}

	static CStringW UTF8ToWideString(CBlobA& bA)
	{
		Blob b;
		b.Allocate(bA.GetSize());
		CopyMemory(b.GetBuffer(),bA.GetBuffer(),bA.GetSize());
		return UTF8ToWideString(b);
	}

	static CStringW UTF8ToWideString(const CRYPT_DATA_BLOB& bC)
	{
		Blob b;
		b.Allocate(bC.cbData);
		CopyMemory(b.GetBuffer(),bC.pbData,bC.cbData);
		return UTF8ToWideString(b);
	}

	template<class _A>
	static CString UTF8ToString(_A a)
	{
		return UTF8ToWideString(a);
	}

	static Blob WideStringToUTF8(const CStringW& text)
	{
		try
		{
			if (text.GetLength() == 0) return Blob();
			//
			Blob b;
			int size1 = WideCharToMultiByte(CP_UTF8,0, // WC_COMPOSITECHECK
				text.GetString(),text.GetLength(),0,0,
				0,0);
			if (! size1)
			{
				HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
				throw FunctionError(rc);
			}
			b.Allocate(size1);
			size1 = WideCharToMultiByte(CP_UTF8,0,
				text.GetString(),text.GetLength(),(char*)b.GetBuffer(),b.GetSize(),
				0,0);
			if (! size1)
			{
				HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
				throw FunctionError(rc);
			}
			return b;
		}
		_FCatch()
	}

	inline static string FormatUTCTime(COleDateTime t)
	{
		try
		{
			string t_s_1 = FormatStr(L"%04d-%02d-%02d", t.GetYear(), t.GetMonth(), t.GetDay() );
			string t_s_2 = FormatStr(L"T%02d:%02d:%02dZ", t.GetHour(), t.GetMinute(), t.GetSecond() );
			//
			string t_s = t_s_1 + t_s_2; 
			//
			return t_s;
		}
		_FCatch()
	}

	inline static string Translit(const string& input)
	{
		try
		{
			static Map<int, string> T;
			//
			if (T.GetSize() == 0)
			{
				T[(int)L'�'] = L"a";
				T[(int)L'�'] = L"b";
				T[(int)L'�'] = L"v";
				T[(int)L'�'] = L"g";
				T[(int)L'�'] = L"d";
				T[(int)L'�'] = L"e";
				T[(int)L'�'] = L"e";
				T[(int)L'�'] = L"zh";
				T[(int)L'�'] = L"z";
				T[(int)L'�'] = L"i";
				T[(int)L'�'] = L"j";
				T[(int)L'�'] = L"k";
				T[(int)L'�'] = L"l";
				T[(int)L'�'] = L"m";
				T[(int)L'�'] = L"n";
				T[(int)L'�'] = L"o";
				T[(int)L'�'] = L"p";
				T[(int)L'�'] = L"r";
				T[(int)L'�'] = L"s";
				T[(int)L'�'] = L"t";
				T[(int)L'�'] = L"u";
				T[(int)L'�'] = L"f";
				T[(int)L'�'] = L"kh";
				T[(int)L'�'] = L"ts";
				T[(int)L'�'] = L"ch";
				T[(int)L'�'] = L"sh";
				T[(int)L'�'] = L"sch";
				T[(int)L'�'] = L"";
				T[(int)L'�'] = L"y";
				T[(int)L'�'] = L"";
				T[(int)L'�'] = L"e";
				T[(int)L'�'] = L"yu";
				T[(int)L'�'] = L"ya";
				//
				T[(int)L'�'] = L"A";
				T[(int)L'�'] = L"B";
				T[(int)L'�'] = L"V";
				T[(int)L'�'] = L"G";
				T[(int)L'�'] = L"D";
				T[(int)L'�'] = L"E";
				T[(int)L'�'] = L"E";
				T[(int)L'�'] = L"Zh";
				T[(int)L'�'] = L"Z";
				T[(int)L'�'] = L"I";
				T[(int)L'�'] = L"J";
				T[(int)L'�'] = L"K";
				T[(int)L'�'] = L"L";
				T[(int)L'�'] = L"M";
				T[(int)L'�'] = L"N";
				T[(int)L'�'] = L"O";
				T[(int)L'�'] = L"P";
				T[(int)L'�'] = L"R";
				T[(int)L'�'] = L"S";
				T[(int)L'�'] = L"T";
				T[(int)L'�'] = L"U";
				T[(int)L'�'] = L"F";
				T[(int)L'�'] = L"Kh";
				T[(int)L'�'] = L"Ts";
				T[(int)L'�'] = L"Ch";
				T[(int)L'�'] = L"Sh";
				T[(int)L'�'] = L"Sch";
				T[(int)L'�'] = L"";
				T[(int)L'�'] = L"Y";
				T[(int)L'�'] = L"";
				T[(int)L'�'] = L"E";
				T[(int)L'�'] = L"Yu";
				T[(int)L'�'] = L"Ya";
			}
			//
			string s;
			const wchar_t* p = input.GetString();
			for (int j = 0; j < input.GetLength(); j++) 
			{
				wchar_t sym = p[j];
				if (T.ContainsKey(sym))
				{
					s += (string)T[sym];
				}
				else
				{
					s += string(sym, 1); 
				}
			}
			//
			return s; 
		}
		_Catch()
	}










	inline static Blob ReadAllFromStream(IStream* stream) 
	{
		try
		{
			// Sleep(20000); 
			//
			if (! stream) throw MethodError(E_INVALIDARG);   
			//
			LARGE_INTEGER m0;
			m0.QuadPart = 0;
			ULARGE_INTEGER libNewPos;
			HRESULT r0 = stream->Seek(m0,FILE_BEGIN,&libNewPos); 
			if (r0 == E_NOTIMPL)
			{
				// ������ � ������� ������� 
			}
			else if (FAILED(r0)) 
			{
				throw MethodError(r0); 
			}
			//
			Blob data;
			int pos = 0; 
			HRESULT r1 = S_OK; 
			do
			{
				int chunkSize = 4 * 1024; 
				Blob chunk;
				chunk.Expand(chunkSize); 
				//
				ULONG bytesRead; 
				r1 = stream->Read(chunk.GetBuffer(),chunkSize,&bytesRead); 
				if ((r1 == E_PENDING) || (r1 == S_FALSE) || (r1 == S_OK)) // �� ���� ���� ������� ������! 
				{
					if ((r1 == S_OK) && (bytesRead == 0)) // => S_FALSE 
					{
						r1 = S_FALSE; 
					}
					else if ((r1 == E_PENDING) && (bytesRead == 0))
					{
						// �������� 
					}
					//
					if (bytesRead > 0)
					{
						data.Expand(pos + bytesRead); 
						CopyMemory(data.GetBuffer() + pos,chunk.GetBuffer(),bytesRead);
						data.SetSize(pos + bytesRead); 
						pos += bytesRead; 
					}
				}
				else 
				{
					throw MethodError(r1); 
				}
			}
			while ((r1 == S_OK) || (r1 == E_PENDING)); 
			//
			if (FAILED(r1)) throw MethodError(r1); 
			//
			return data; 
		}
		_Catch() 
	}






	// ===================================================================================
	// ��������� � ��������� 

	inline static SharedArray<string> ArrayMerge(SharedArray<string> a, SharedArray<string> b)
	{
		try
		{
			SharedArray<string> r;
			r.Allocate(a.Length()); 
			//
			for (int j = 0; j < a.Length(); ++j)
			{
				r[j] = a[j];
			}
			//
			for (int k = 0; k < b.Length(); ++k)
			{
				string x = b[k];
				//
				bool f = false; 
				for (int j = 0; j < a.Length() && (!f); j++)
				{
					string y = a[j]; 
					if (y == x) f = true; 
				}
				if (!f)
				{
					a.Add(x); 
				}
			}
			//
			return r; 
		}
		_Catch()
	}






















	// ===========================================================================================
	// ���������� � ������� 

#	ifndef _NOT_DEFINE_WINDOWS_PRODUCT_CODES
	//
#	define PRODUCT_BUSINESS 0x00000006
#	define PRODUCT_BUSINESS_N 0x00000010
#	define PRODUCT_CLUSTER_SERVER 0x00000012
#	define PRODUCT_DATACENTER_SERVER 0x00000008
#	define PRODUCT_DATACENTER_SERVER_CORE 0x0000000C
#	define PRODUCT_DATACENTER_SERVER_CORE_V 0x00000027
#	define PRODUCT_DATACENTER_SERVER_V 0x00000025
#	define PRODUCT_ENTERPRISE 0x00000004
#	define PRODUCT_ENTERPRISE_N 0x0000001B
#	define PRODUCT_ENTERPRISE_SERVER 0x0000000A
#	define PRODUCT_ENTERPRISE_SERVER_CORE 0x0000000E
#	define PRODUCT_ENTERPRISE_SERVER_CORE_V 0x00000029
#	define PRODUCT_ENTERPRISE_SERVER_IA64 0x0000000F
#	define PRODUCT_ENTERPRISE_SERVER_V 0x00000026
#	define PRODUCT_HOME_BASIC 0x00000002
#	define PRODUCT_HOME_BASIC_N 0x00000005
#	define PRODUCT_HOME_PREMIUM 0x00000003
#	define PRODUCT_HOME_PREMIUM_N 0x0000001A
#	define PRODUCT_HOME_SERVER 0x00000013
#	define PRODUCT_HYPERV 0x0000002A
#	define PRODUCT_MEDIUMBUSINESS_SERVER_MANAGEMENT 0x0000001E
#	define PRODUCT_MEDIUMBUSINESS_SERVER_MESSAGING 0x00000020
#	define PRODUCT_MEDIUMBUSINESS_SERVER_SECURITY 0x0000001F
#	define PRODUCT_SERVER_FOR_SMALLBUSINESS 0x00000018
#	define PRODUCT_SERVER_FOR_SMALLBUSINESS_V 0x00000023
#	define PRODUCT_SMALLBUSINESS_SERVER 0x00000009
#	define PRODUCT_STANDARD_SERVER 0x00000007
#	define PRODUCT_STANDARD_SERVER_CORE 0x0000000D
#	define PRODUCT_STANDARD_SERVER_CORE_V 0x00000028
#	define PRODUCT_STANDARD_SERVER_V 0x00000024
#	define PRODUCT_STARTER 0x0000000B
#	define PRODUCT_STORAGE_ENTERPRISE_SERVER 0x00000017
#	define PRODUCT_STORAGE_EXPRESS_SERVER 0x00000014
#	define PRODUCT_STORAGE_STANDARD_SERVER 0x00000015
#	define PRODUCT_STORAGE_WORKGROUP_SERVER 0x00000016
#	define PRODUCT_UNDEFINED 0x00000000
#	define PRODUCT_ULTIMATE 0x00000001
#	define PRODUCT_ULTIMATE_N 0x0000001C
#	define PRODUCT_WEB_SERVER 0x00000011
#	define PRODUCT_WEB_SERVER_CORE 0x0000001D
	//
#	endif

#	ifndef SM_SERVERR2
#	define SM_SERVERR2             89
#	endif



	struct SystemInfo
	{
		typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);

		typedef BOOL (WINAPI *PGPI)(DWORD, DWORD, DWORD, DWORD, PDWORD);

		inline static string GetOSDescription() throw() 
		{
			string osDescr = L"Microsoft ";
			//
			// SYSTEM_INFO
			//
			SYSTEM_INFO si;
			ZeroMemory(&si,sizeof(si));
			//
			PGNSI pGNSI = (PGNSI)GetProcAddress(
				GetModuleHandle(_T("kernel32.dll")),"GetNativeSystemInfo"
				);
			if (pGNSI) pGNSI(&si);
			else 
				GetSystemInfo(&si);
			//
			//
			// OSVERSIONINFO
			//
			OSVERSIONINFOEX osvi;
			ZeroMemory(&osvi,sizeof(osvi));
			osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
			//
			if (GetVersionEx((OSVERSIONINFO*)&osvi))
			{
				if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0)
				{
					if (osvi.wProductType == VER_NT_WORKSTATION) osDescr += L"Windows Vista ";
					else osDescr += L"Windows Server 2008 ";
					//
					DWORD dwProductType;
					//
					PGPI pGPI = (PGPI)GetProcAddress(
						GetModuleHandle(_T("kernel32.dll")),"GetProductInfo"
						);
					//
					pGPI(6, 0, 0, 0, &dwProductType);
					//
					switch (dwProductType)
					{
					case PRODUCT_ULTIMATE:
					   osDescr += L"Ultimate Edition";
					   break;
					case PRODUCT_HOME_PREMIUM:
					   osDescr += L"Home Premium Edition";
					   break;
					case PRODUCT_HOME_BASIC:
					   osDescr += L"Home Basic Edition";
					   break;
					case PRODUCT_ENTERPRISE:
					   osDescr += L"Enterprise Edition";
					   break;
					case PRODUCT_BUSINESS:
					   osDescr += L"Business Edition";
					   break;
					case PRODUCT_STARTER:
					   osDescr += L"Starter Edition";
					   break;
					case PRODUCT_CLUSTER_SERVER:
					   osDescr += L"Cluster Server Edition";
					   break;
					case PRODUCT_DATACENTER_SERVER:
					   osDescr += L"Datacenter Edition";
					   break;
					case PRODUCT_DATACENTER_SERVER_CORE:
					   osDescr += L"Datacenter Edition (core installation)";
					   break;
					case PRODUCT_ENTERPRISE_SERVER:
					   osDescr += L"Enterprise Edition";
					   break;
					case PRODUCT_ENTERPRISE_SERVER_CORE:
					   osDescr += L"Enterprise Edition (core installation)";
					   break;
					case PRODUCT_ENTERPRISE_SERVER_IA64:
					   osDescr += L"Enterprise Edition for Itanium-based Systems";
					   break;
					case PRODUCT_SMALLBUSINESS_SERVER:
					   osDescr += L"Small Business Server";
					   break;
					//case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
					//   osDescr += L"Small Business Server Premium Edition";
					//   break;
					case PRODUCT_STANDARD_SERVER:
					   osDescr += L"Standard Edition";
					   break;
					case PRODUCT_STANDARD_SERVER_CORE:
					   osDescr += L"Standard Edition (core installation)";
					   break;
					case PRODUCT_WEB_SERVER:
					   osDescr += L"Web Server Edition";
					   break;
					}
				}
				//
				if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
				{
					if (GetSystemMetrics(SM_SERVERR2)) 
					{
						osDescr += L"Windows Server 2003 R2, ";
					}
					else if (osvi.wSuiteMask == VER_SUITE_STORAGE_SERVER) 
					{
						osDescr += L"Windows Storage Server 2003";
					}
					else if (osvi.wProductType == VER_NT_WORKSTATION && 
						si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
					{
						osDescr += L"Windows XP Professional x64 Edition"; 
					}
					else 
					{
						osDescr += L"Windows Server 2003, ";
					}
					//
					// Test for the server type 
					//
					if (osvi.wProductType != VER_NT_WORKSTATION)
					{
						if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
						{
							if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
								osDescr += L"Datacenter Edition for Itanium-based Systems";
							else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
								osDescr += L"Enterprise Edition for Itanium-based Systems";
						}
						else if (si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)
						{
							if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
								osDescr += L"Datacenter x64 Edition";
							else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
								osDescr += L"Enterprise x64 Edition";
							else 
								osDescr += L"Standard x64 Edition";
						}
						else
						{
							if (osvi.wSuiteMask & VER_SUITE_COMPUTE_SERVER)
								osDescr += L"Compute Cluster Edition";
							else if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
								osDescr += L"Datacenter Edition";
							else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
								osDescr += L"Enterprise Edition";
							else if ( osvi.wSuiteMask & VER_SUITE_BLADE )
								osDescr += L"Web Edition";
							else 
								osDescr += L"Standard Edition";
						}
					}
				}

				if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)
				{
					osDescr += L"Windows XP ";
					//
					if (osvi.wSuiteMask & VER_SUITE_PERSONAL)
						osDescr += L"Home Edition";
					else 
						osDescr += L"Professional";
				}
				//
				if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
				{
					osDescr += L"Windows 2000 ";
					//
					if (osvi.wProductType == VER_NT_WORKSTATION)
					{
						osDescr += "Professional";
					}
					else 
					{
						if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
							osDescr += L"Datacenter Server";
						else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
							osDescr += L"Advanced Server";
						else 
							osDescr += L"Server";
					}
				}
				//
				// Include service pack (if any) and build number 
				//
				size_t szCSDVersionSize = 0;
				StringCchLength(osvi.szCSDVersion,1024,&szCSDVersionSize); 
				if (szCSDVersionSize > 0)
				{
					osDescr += L" " + string(_S(osvi.szCSDVersion));
				}
				//
				if (osvi.dwBuildNumber)
				{
					osDescr += FormatStr(L" (build %d)", (int)osvi.dwBuildNumber );
				}
			}
			//
			return osDescr; 
		}



		inline static string GetHostDescription() throw()
		{
			string host;
			//
			TCHAR hostBuf[1024];
			hostBuf[0] = 0;
			DWORD hostBufSize = sizeof(hostBuf);
			//
			if (GetComputerNameEx(
				ComputerNameDnsFullyQualified, 
				hostBuf,
				&hostBufSize))
			{
				host = _W(hostBuf);
			}
			//
			return host;
		}



		inline static string GetUserDescription() throw()
		{
			TCHAR userName[1024];
			userName[0] = 0;
			DWORD userNameSize = sizeof(userName);
			GetUserName(userName,&userNameSize); 
			return string(_S(userName));
		}



		inline static string InfoToHtmlInfo(const string& info) throw() 
		{
			string s = info;
			//
			if (s.Right(1) == L"\n") s = s.Left(s.GetLength()-1);
			//
			s.Replace(L"\t",L"</td><td>");
			//
			s.Replace(L"\n",L"</td></tr><tr><td>");
			//
			s = L"<tr><td>" + s + L"</td></tr>";
			//
			return s;
		}



		inline static string GetDllVersionStr(const CString& path) throw() 
		{
			DWORD dwMajor = 0;
			DWORD dwMinor = 0;
			DWORD dwBuildNumber = 0;
			//
			GetDllVersion(path,dwMajor,dwMinor,dwBuildNumber); 
			//
			string versionStr = FormatStr(L"%d.%d.%d", (int)dwMajor, (int)dwMinor, (int)dwBuildNumber );
			return versionStr; 
		}

		inline static void GetDllVersion(const CString& path,
			DWORD &dwMajor, DWORD &dwMinor, DWORD &dwBuildNumber
			) throw() 
		{
			dwMajor = 0;
			dwMinor = 0;
			dwBuildNumber = 0;
			//
			HINSTANCE hDllInst = LoadLibrary(_S(path)); 
			if(hDllInst) 
			{  
				DLLGETVERSIONPROC pDllGetVersion = (DLLGETVERSIONPROC)GetProcAddress(hDllInst, 
					"DllGetVersion");
				//
				if(pDllGetVersion) 
				{    
					DLLVERSIONINFO    dvi;
					ZeroMemory(&dvi, sizeof(dvi));
					dvi.cbSize = sizeof(dvi);
					//
					HRESULT hr = (*pDllGetVersion)(&dvi);
					//
					if(SUCCEEDED(hr)) 
					{ 
						dwMajor = dvi.dwMajorVersion;
						dwMinor = dvi.dwMinorVersion;
						dwBuildNumber = dvi.dwBuildNumber;
					}
					//
					FreeLibrary(hDllInst); 
				}
			}
			//
			//////if (dwMajor == 0)
			//////{
			//////	GetFileVersion(_S(path),SYS_DIR,dwMajor,dwMinor,dwBuildNumber);
			//////}
		}



		typedef enum 
		{  
			WIN_DIR,	// Windows directory (e.g.: "C:\Windows\")
            SYS_DIR,	// Windows system directory (e.g.: "C:\Windows\System")
            CUR_DIR,	// Current directory (e.g.: ".")
            NO_DIR		// No directory (path in file name)
		}
        FileLocationType;   // Possible ways to add a path prefix to a file

		inline static CString GetFileVersionStr(LPCTSTR fileName,FileLocationType FileLoc)
		{
			CString path = fileName;
			if (path.Find(_T(':')) == -1) path = FixFilePath(fileName, FileLoc);  
			//
			if (path.GetLength() == 0) return _T("");
			//
			DWORD dwVerHnd = 0;
			//
			DWORD dwVerInfoSize = GetFileVersionInfoSize(path,&dwVerHnd); 
			//
			if (! dwVerInfoSize)     
			{
				return _T(""); 
			}
			//
			BYTE vData[2048];
			ZeroMemory(vData,sizeof(vData));
			//
			if (! GetFileVersionInfo(path,dwVerHnd,dwVerInfoSize,vData)) 
			{
				return _T(""); 
			}
			//
			VS_FIXEDFILEINFO* pFfi = 0;
			UINT versionLen = sizeof(pFfi); 
			//
			if (! VerQueryValue(vData,
				_T("\\"),
				(LPVOID*)&pFfi, &versionLen)) 
			{
				return _T(""); 
			}
			//
			CString version; 
			if (pFfi)
			{
				int v_1 = ((int)pFfi->dwProductVersionMS) >> 16;
				int v_2 = ((int)pFfi->dwProductVersionMS) & 0x00ff;
				int v_3 = ((int)pFfi->dwProductVersionLS) >> 16;
				int v_4 = ((int)pFfi->dwProductVersionLS) & 0x00ff;
				//
				version = FormatStr(_T("%d.%d.%d"), v_1, v_2, v_3 ) + 
					FormatStr(_T(".%d"), v_4 );
			}
			return version;
		}

		inline static string GetProtocolVersion() 
		{
			try
			{
				HMODULE hModule = GetModuleHandle(_PROTOCOL_MODULE_FILENAME);
				TCHAR mfName[1024];
				::GetModuleFileName(hModule,mfName,1024); 
				//
				string verStr = _W(GetFileVersionStr( 
					_S(mfName), ::::SystemInfo::CUR_DIR 
					)); 
				return verStr; 
			}
			_Catch() 
		}

		inline static string GetAjaxDllVersion() 
		{
			try
			{
				HMODULE hModule = GetModuleHandle(L"ajax.dll");
				if (!hModule) return L"unknown"; 
				TCHAR mfName[1024];
				::GetModuleFileName(hModule,mfName,1024); 
				//
				string verStr = _W(GetFileVersionStr( 
					_S(mfName), ::::SystemInfo::CUR_DIR 
					)); 
				return verStr; 
			}
			_Catch() 
		}



		inline static CString FixFilePath(LPCTSTR fileName,FileLocationType FileLoc) throw() 
		{
			TCHAR buf[2048];
			//
			switch (FileLoc) 
			{
				case WIN_DIR:
					if (! GetWindowsDirectory(buf,sizeof(buf)))
					{
						return _T(""); 
					}
					break;
					//
				case SYS_DIR:
					if (! GetSystemDirectory(buf,sizeof(buf)))
					{
						return _T(""); 
					}
					break;
					//
				case CUR_DIR:
					if (! GetCurrentDirectory(sizeof(buf),buf)) 
					{
						return _T(""); 
					}
					break;
					//
				case NO_DIR:
					{
						return _T(""); 
					}
					break;
					//
				default:
					{
						return _T(""); 
					}
			}
			CString path = _S(buf) + _S("\\") + fileName;
			return path;
		}
	};

} // namespace  
