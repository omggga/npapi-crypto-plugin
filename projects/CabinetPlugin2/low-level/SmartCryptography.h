/*
 Cryptography.h : ���������� ������-��������.

 $Name: work1 $
 $Revision: 1.1.2.2 $
 $Date: 2008/10/10 15:12:24 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

// Windows
//
#include <Wincrypt.h>

// 
//
#include "SmartPtr.h"

namespace  {



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� AuxCrypto

class AuxCrypto
{
public:
	AuxCrypto()
	{
	}

	HRESULT AcquireCSP(HCRYPTPROV* out_pCSP)
	{
		if (out_pCSP == 0) return E_POINTER;
		//
		HCRYPTPROV new_CSP = 0;
		//
		if (CryptAcquireContext(
			&new_CSP, 
			NULL, 
			NULL, 
			PROV_RSA_FULL, 
			CRYPT_VERIFYCONTEXT)) 
		{
		}
		else
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}
		//
		if (new_CSP == 0) return E_FAIL;
		//
		*out_pCSP = new_CSP;
		//
		return S_OK;
	}

	HCRYPTPROV& GetCSPData()
	{
		static HCRYPTPROV s_pCSP = 0;
		return s_pCSP;
	}

	HCRYPTPROV GetAuxCSP()
	{
		HCRYPTPROV& CSP = GetCSPData();
		if (! CSP)
		{
			HRESULT rc = AcquireCSP(&CSP);
			if (FAILED(rc))
			{
				TRACE_LOG(_T("�� ������ ���������� ��������������� CSP!"));
			}
		}
		return CSP;
	}
};




} // namespace  
