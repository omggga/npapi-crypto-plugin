
#pragma once

#include "Alg_Common.h"

namespace 
{
	namespace Algorithms
	{
		/// <summary>
		/// ���-������� SHA1.
		/// </summary>
		class Alg_1_8_2
		{
		public:
			Alg_1_8_2()
			{
			}

			string EncodeText(string text)
			{
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
				return Encode(b);
			}

			string Encode(Blob data)
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
					throw Exception(L"�� ������� ��������� ������-���������");
				}
				//
				HCRYPTHASH hHash;
				//
				if (! CryptCreateHash(
					hCryptProv, 
					CALG_SHA1, 
					0, 
					0, 
					&hHash)) 
				{
					throw Exception(L"���������� ������� ���");
				}
				//
				if(! CryptHashData(
					hHash, 
					data.GetBuffer(), 
					(DWORD)data.Length(), 
					0)) 
				{
					throw Exception(L"���������� ��������� ���");
				}
				//
				DWORD dwDigestedSize;
				//
				if(! CryptGetHashParam(hHash,
					HP_HASHVAL,
					0,
					&dwDigestedSize,
					0))
				{
					throw Exception(L"���������� ������� �������� ����");
				}
				//
				Blob dataDigested;
				dataDigested.Allocate(dwDigestedSize);
				//
				if(! CryptGetHashParam(hHash,
					HP_HASHVAL,
					dataDigested.GetBuffer(),
					&dwDigestedSize,
					0))
				{
					throw Exception(L"���������� ������� �������� ����");
				}
				//
				CryptReleaseContext(hCryptProv,0);
				//
				return ToBase64Padding(dataDigested);
			}
			
			string EncodeFile(string path)
			{
				::::File f;
				f.Open(_S(path));
				Blob data = f.ReadAll();
				return Encode(data);
			}
		};
	}
}
