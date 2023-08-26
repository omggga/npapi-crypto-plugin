
#ifndef _WINCSP_H_INCLUDED
#define _WINCSP_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#if defined( DEVL ) && !defined( CSP_EXPORT )
#define CSP_EXPORT DECLSPEC_IMPORT
#elif !defined( CSP_EXPORT )
#define CSP_EXPORT extern
#endif

typedef BOOL (WINAPI *CRYPT_VERIFY_IMAGE_A)(LPCSTR  szImage, CONST BYTE *pbSigData);
typedef void (WINAPI *CRYPT_RETURN_HWND)(HWND *phWnd);

/*! 
 * \ingroup ProCSPData
 *
 * \brief ��������� VTABLEPROVSTRUC �������� ��������� �� callback �������, ������� ����� ���� ������������ ������� ���������������� (CSP).
 *
 * \note ��������� �� ��������� VTABLEPROVSTRUC �������� ������ �� ����� ������ ������� CPAcquireContext. 
 * ���� ����� ��������� ���������� ��� ���������� ������, 
 * ���������� ���������� ����������� ��������. 
 * ������������� ��������� �� �������, ������������ � ��������� � ���� �������, ����� ���� ������������ �� ��� ��� 
 * ���� �� ��������� ������ � �����������������.
 * ��� �������������� ������ (DLL), ������� ���������� ��������������� ����� ���� ���������, ��� � �������� ������.
 * ���� ��������� ������������� ������� � �������������� ������� LoadLib, ����� ��������� ������� �������������� �������.
 * ��������������� ����� ����������� ����� ��������, ��������� ��������� �� ������� FuncVerifyImage, ��� �������� � ��������� �������:
 * \code
 * BOOL (FARPROC *ProvVerifyImage)(LPCSTR lpszImage, BYTE *pSigData);
 * BYTE bSignature[72];
 * 
 * // "ProvVerifyImage" has been set to "pVTable->FuncVerifyImage"
 * // within the CPAcquireContext function.
 * 
 * // Load the C:\Winnt40\System32\signature.sig file into the 
 * // bSignature buffer. During development, this file is created 
 * // with the Sign.exe utility.
 * ...
 * 
 * // Verify the signature on the C:\Winnt40\System32\Signature.dll file.
 * if(RCRYPT_FAILED(ProvVerifyImage("c:\\winnt40\\system32\\signature.dll",
 *                                  bSignature)) {
 *     SetLastError(NTE_BAD_SIGNATURE);
 *    return CRYPT_FAILED;
 * }
 * 
 * // Load the DLL with the LoadLib function, then acquire pointers to 
 * // the member functions with the GetProcAddress function.
 * ...
 * \endcode
 */
typedef struct _VTABLEPROVSTRUC {
    DWORD   Version; 
                /*!< DWORD ��������, ������������ ������ ���������.
                 * ������������ ��� ������ ���������. Microsoft� Windows NT� ������ 4.0 and 
                 * Microsoft� Windows� 95 ���������� ������ 1, 
                 * ������� �������� ������ ��� ������ �����: 
                 * \b Version, \b FuncVerifyImage, \b FuncReturnhWnd. 
                 * ������ 2 ������������ � Windows 98. ������������ ������ ����� ������ 
                 * ��������� (��� \b pszProvName). ������ 3 ������������ � Windows 2000. 
                 * ��� �������� ��� ���� ������ ���������. 
                 */
    CRYPT_VERIFY_IMAGE_A FuncVerifyImage;
      							/*�������� � MSDN*/
                /*!< ��������� �� callback �������, ������������ ��� �������� ��� ������. 
                 * ��. ����������.
                 */
    CRYPT_RETURN_HWND    FuncReturnhWnd;
                /*!< ��������� �� callback �������, ������������ ���������� � ����������� ����. 
                 * ���������� ���� ����� ����������� ��� �������������� � ������������� 
                 * ����� Microsoft� Win32�. 
                 */
    DWORD   dwProvType; 
                /*!< ������ ������ 2 � 3. ��������, ������������ ��� ����������������. ���������� 
                 * ��������� ���� �����������������:
                 * \arg PROV_GOST_DH
                 * \arg PROV_GOST_94_DH
                 * \arg PROV_GOST_2001_DH
                 * \arg PROV_RSA_FULL
                 * \arg PROV_RSA_SIG
                 * \arg PROV_DSS
                 * \arg PROV_FORTEZZA
                 * \arg PROV_MS_EXCHANGE
                 */
    BYTE    *pbContextInfo; 
                /*!< ������ ������ 2 � 3. ��������� �� ������ ����������� ����������. 
                 * ���������� \b pbContextInfo � \b cbContextInfo ���������� ������ 
                 * ������������ ����������,
                 * ����������� ��� ������ ������� \ref #CPSetProvParam � ���������� 
                 * PP_CONTEXT_INFO. 
                 */
    DWORD   cbContextInfo;
                /*!< ������ ������ 2 � 3. ��������, ������������ ���������� ��������� 
                 * � ������� \b pbContextInfo. */
    LPSTR   pszProvName;
                /*!< ������ ������ 3. ������, ���������� ��� ����������. */
} VTABLEPROVSTRUC, *PVTABLEPROVSTRUC;

#ifdef UNIX 
#define WINCSP_CONST
#else
#define WINCSP_CONST CONST
#endif

CSP_EXPORT BOOL WINAPI CPAcquireContext (
    /* [out] */ HCRYPTPROV *phProv,
    /* [string][in] */ CHAR *pszContainer,
    /* [in] */ DWORD dwFlags,
    /* [in] */ PVTABLEPROVSTRUC pVTable);

CSP_EXPORT BOOL WINAPI CPReleaseContext (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ DWORD dwFlags);

CSP_EXPORT BOOL WINAPI CPGetProvParam ( 
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ DWORD dwParam,
    /* [size_is][out] */ BYTE *pbData,
    /* [out][in] */ DWORD *pdwDataLen,
    /* [in] */ DWORD dwFlags);

CSP_EXPORT BOOL WINAPI CPSetProvParam (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ DWORD dwParam,
    /* [size_is][in] */ BYTE *pbData,
    /* [in] */ DWORD dwFlags);

CSP_EXPORT BOOL WINAPI CPGenKey (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ ALG_ID AlgId,
    /* [in] */ DWORD dwFlags,
    /* [out] */ HCRYPTKEY *phKey);

CSP_EXPORT BOOL WINAPI CPDestroyKey (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTKEY hKey);

CSP_EXPORT BOOL WINAPI CPCreateHash (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ ALG_ID AlgId,
    /* [in] */ HCRYPTKEY hKey,
    /* [in] */ DWORD dwFlags,
    /* [out] */ HCRYPTHASH *phHash);

CSP_EXPORT BOOL WINAPI CPDestroyHash (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTHASH hHash);

CSP_EXPORT BOOL WINAPI CPEncrypt (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTKEY hKey,
    /* [in] */ HCRYPTHASH hHash,
    /* [in] */ BOOL Final,
    /* [in] */ DWORD dwFlags,
    /* [size_is][out][in] */ BYTE *pbData,
    /* [out][in] */ DWORD *pdwDataLen,
    /* [in] */ DWORD dwBufLen);

CSP_EXPORT BOOL WINAPI CPDecrypt (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTKEY hKey,
    /* [in] */ HCRYPTHASH hHash,
    /* [in] */ BOOL Final,
    /* [in] */ DWORD dwFlags,
    /* [full][size_is][out][in] */ BYTE *pbData,
    /* [out][in] */ DWORD *pdwDataLen);

CSP_EXPORT BOOL WINAPI CPDeriveKey (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ ALG_ID AlgId,
    /* [in] */ HCRYPTHASH hBaseData,
    /* [in] */ DWORD dwFlags,
    /* [out] */ HCRYPTKEY *phKey);

CSP_EXPORT BOOL WINAPI CPDuplicateKey (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTKEY hKey,
    /* [full][in] */ DWORD *pdwReserved,
    /* [in] */ DWORD dwFlags,
    /* [out] */ HCRYPTKEY *phKey);

CSP_EXPORT BOOL WINAPI CPDuplicateHash (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTHASH hHash,
    /* [full][in] */ DWORD *pdwReserved,
    /* [in] */ DWORD dwFlags,
    /* [out] */ HCRYPTHASH *phHash);

CSP_EXPORT BOOL WINAPI CPExportKey (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTKEY hKey,
    /* [in] */ HCRYPTKEY hExpKey,
    /* [in] */ DWORD dwBlobType,
    /* [in] */ DWORD dwFlags,
    /* [full][size_is][out][in] */ BYTE *pbData,
    /* [out][in] */ DWORD *pdwDataLen);

CSP_EXPORT BOOL WINAPI CPGenRandom (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ DWORD dwLen,
    /* [size_is][out][in] */ BYTE *pbBuffer);

CSP_EXPORT BOOL WINAPI CPGetHashParam (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTHASH hHash,
    /* [in] */ DWORD dwParam,
    /* [full][size_is][out][in] */ BYTE *pbData,
    /* [out][in] */ DWORD *pdwDataLen,
    /* [in] */ DWORD dwFlags);

CSP_EXPORT BOOL WINAPI CPGetKeyParam (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTKEY hKey,
    /* [in] */ DWORD dwParam,
    /* [full][size_is][out][in] */ BYTE *pbData,
    /* [out][in] */ DWORD *pdwDataLen,
    /* [in] */ DWORD dwFlags);

CSP_EXPORT BOOL WINAPI CPGetUserKey (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ DWORD dwKeySpec,
    /* [out] */ HCRYPTKEY *phUserKey);

CSP_EXPORT BOOL WINAPI CPHashData (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTHASH hHash,
    /* [full][size_is][in] */ WINCSP_CONST BYTE *pbData,
    /* [in] */ DWORD dwDataLen,
    /* [in] */ DWORD dwFlags);

CSP_EXPORT BOOL WINAPI CPHashSessionKey (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTHASH hHash,
    /* [in] */ HCRYPTKEY hKey,
    /* [in] */ DWORD dwFlags);

CSP_EXPORT BOOL WINAPI CPImportKey (
    /* [in] */ HCRYPTPROV hProv,
    /* [full][size_is][in] */ WINCSP_CONST BYTE *pbData,
    /* [in] */ DWORD dwDataLen,
    /* [in] */ HCRYPTKEY hImpKey,
    /* [in] */ DWORD dwFlags,
    /* [out] */ HCRYPTKEY *phKey);

CSP_EXPORT BOOL WINAPI CPSetHashParam (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTHASH hHash,
    /* [in] */ DWORD dwParam,
    /* [size_is][in] */ BYTE *pbData,
    /* [in] */ DWORD dwFlags);

CSP_EXPORT BOOL WINAPI CPSetKeyParam (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTKEY hKey,
    /* [in] */ DWORD dwParam,
    /* [size_is][in] */ BYTE *pbData,
    /* [in] */ DWORD dwFlags);

CSP_EXPORT BOOL WINAPI CPSignHash (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTHASH hHash,
    /* [in] */ DWORD dwKeySpec,
    /* [string][full][in] */ LPCWSTR sDescription,
    /* [in] */ DWORD dwFlags,
    /* [size_is][out][in] */ BYTE *pbSignature,
    /* [out][in] */ DWORD *pdwSigLen);

CSP_EXPORT BOOL WINAPI CPVerifySignature (
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTHASH hHash,
    /* [size_is][in] */ WINCSP_CONST BYTE *pbSignature,
    /* [in] */ DWORD dwSigLen,
    /* [in] */ HCRYPTKEY hPubKey,
    /* [string][full][in] */ LPCWSTR sDescription,
    /* [in] */ DWORD dwFlags);

/*======================================================*/
/* ������������� � ��������� ���������������� */

/*------------------------------------------------------*/
/* ����������� ������� CPAcquireContext*/
typedef BOOL (WINAPI *CPAcquireContext_t) (
    HCRYPTPROV *phProv,       /* out*/
    CHAR *pszContainer,       /* in, out*/
    DWORD dwFlags,            /* in*/
    PVTABLEPROVSTRUC pVTable  /* in*/
);

/*------------------------------------------------------*/
/* ����������� ������� CPReleaseContext */
typedef BOOL (WINAPI *CPReleaseContext_t) (
    HCRYPTPROV hProv,  /* in*/
    DWORD dwFlags      /* in*/
);

/*------------------------------------------------------*/
/* ����������� ������� CPGetProvParam */
typedef BOOL (WINAPI *CPGetProvParam_t) (
    HCRYPTPROV hProv,  /* in*/
    DWORD dwParam,     /* in*/
    BYTE *pbData,      /* out*/
    DWORD *pdwDataLen, /* in, out*/
    DWORD dwFlags      /* in*/
);

/*------------------------------------------------------*/
/* ����������� ������� CPSetProvParam */
typedef BOOL (WINAPI *CPSetProvParam_t) (
    HCRYPTPROV hProv,  /* in*/
    DWORD dwParam,     /* in*/
    BYTE *pbData,      /* in*/
    DWORD dwFlags      /* in*/
);

/*======================================================*/
/* ������� ��������� � ������ � ������� */

/*------------------------------------------------------*/
/* ����������� ������� CPGenKey */
typedef BOOL (WINAPI *CPGenKey_t) (
    HCRYPTPROV hProv,     /* in*/
    ALG_ID Algid,         /* in*/
    DWORD dwFlags,        /* in*/
    HCRYPTKEY *phKey     /* out*/
);

/*------------------------------------------------------*/
/* ����������� ������� CPDestroyKey */
typedef BOOL (WINAPI *CPDestroyKey_t) (
    HCRYPTPROV hProv,  /* in*/
    HCRYPTKEY  hKey    /* in*/
);

/*------------------------------------------------------*/
/* ����������� ������� CPDeriveKey */
typedef BOOL (WINAPI *CPDeriveKey_t) ( 
	HCRYPTPROV hProv,		/* in*/
	ALG_ID AlgId,			/* in*/
	HCRYPTHASH hBaseData,	/* in*/
	DWORD dwFlags,			/* in*/
	HCRYPTKEY *phKey		/* out*/
);

/*------------------------------------------------------*/
/* ����������� ������� CPDuplicateKey */
typedef BOOL (WINAPI *CPDuplicateKey_t) ( 
	HCRYPTPROV hProv,		/* in*/
	HCRYPTKEY hKey,			/* in*/
	DWORD *pdwReserved,		/* in*/
	DWORD dwFlags,			/* in*/
	HCRYPTKEY *phKey		/* out*/
);

/*------------------------------------------------------*/
/* ����������� ������� CPExportKey */
typedef BOOL (WINAPI *CPExportKey_t) (
    HCRYPTPROV hProv,      /* in*/
    HCRYPTKEY hKey,        /* in*/
    HCRYPTKEY hPubKey,     /* in*/
    DWORD dwBlobType,      /* in*/
    DWORD dwFlags,         /* in*/
    BYTE *pbData,          /* out*/
    DWORD *pdwDataLen	   /* in, out*/
);

/*------------------------------------------------------*/
/* ����������� ������� CPGenRandom */
typedef BOOL (WINAPI *CPGenRandom_t) ( 
	HCRYPTPROV hProv,		/* in*/
	DWORD dwLen,			/* in*/
	BYTE *pbBuffer			/* in, out*/
);

/*------------------------------------------------------*/
/* ����������� ������� CPGetKeyParam*/
typedef BOOL (WINAPI *CPGetKeyParam_t) (
    HCRYPTPROV hProv,       /* in*/
    HCRYPTKEY hKey,         /* in*/
    DWORD dwParam,          /* in*/
    BYTE *pbData,           /* out*/
    DWORD *pdwDataLen,      /* in, out*/
    DWORD dwFlags           /* in*/
);

/*------------------------------------------------------*/
/* ����������� ������� CPGetUserKey */
typedef BOOL (WINAPI *CPGetUserKey_t) (
    HCRYPTPROV hProv,      
    DWORD dwKeySpec,       
    HCRYPTKEY *phUserKey   
);

/*------------------------------------------------------*/
/* ����������� ������� CPImportKey */
typedef BOOL (WINAPI *CPImportKey_t) (
    HCRYPTPROV hProv,       /* in*/
    WINCSP_CONST BYTE *pbData,     /* in*/
    DWORD  dwDataLen,       /* in*/
    HCRYPTKEY hPubKey,      /* in*/
    DWORD dwFlags,          /* in*/
HCRYPTKEY *phKey        /* out*/
);

/*------------------------------------------------------*/
/* ����������� ������� CPSetKeyParam*/
typedef BOOL (WINAPI *CPSetKeyParam_t) (
    HCRYPTPROV hProv,       /* in*/
    HCRYPTKEY hKey,         /* in*/
    DWORD dwParam,          /* in*/
    BYTE *pbData,           /* in*/
    DWORD dwFlags           /* in*/
);

/*======================================================*/
/* ������� ����������/������������� ������ */

/*------------------------------------------------------*/
/* ����������� ������� CPEncrypt*/
typedef BOOL (WINAPI *CPEncrypt_t) ( 
	HCRYPTPROV hProv,		/* in*/
	HCRYPTKEY hKey,			/* in*/
	HCRYPTHASH hHash,		/* in*/
	BOOL Final,				/* in*/
	DWORD dwFlags,			/* in*/
	BYTE *pbData,			/* in, out*/
	DWORD *pdwDataLen,		/* in, out*/
	DWORD dwBufLen			/* in*/
);

/*------------------------------------------------------*/
/* ����������� ������� CPDecrypt*/
typedef BOOL (WINAPI *CPDecrypt_t) (
	HCRYPTPROV hProv,		/* in*/
	HCRYPTKEY hKey,			/* in*/
	HCRYPTHASH hHash,		/* in*/
	BOOL Final,				/* in*/
	DWORD dwFlags,			/* in*/
	BYTE *pbData,			/* in, out*/
	DWORD *pdwDataLen		/* in, out*/
);

/*======================================================*/
/* ������� ����������� � ��� */

/*------------------------------------------------------*/
/* ����������� ������� CPCreateHash */
typedef BOOL (WINAPI *CPCreateHash_t) (
    HCRYPTPROV hProv,    /* in*/
    ALG_ID Algid,        /* in*/
    HCRYPTKEY hKey,      /* in*/
    DWORD dwFlags,       /* in*/
    HCRYPTHASH *phHash   /* out*/
);

/*------------------------------------------------------*/
/* ����������� ������� CPDestroyHash */
typedef BOOL (WINAPI *CPDestroyHash_t) (
    HCRYPTPROV hProv, /* in*/
    HCRYPTHASH hHash  /* in*/
);

/*------------------------------------------------------*/
/* ����������� ������� CPDuplicateHash */
typedef BOOL (WINAPI *CPDuplicateHash_t) ( 
	HCRYPTPROV hProv, 
	HCRYPTHASH hHash,		/* in*/ 
	DWORD *pdwReserved,		/* in*/
	DWORD dwFlags,			/* in*/
	HCRYPTHASH *phHash		/* out*/
);

/*------------------------------------------------------*/
/* ����������� ������� CPGetHashParam */
typedef BOOL (WINAPI *CPGetHashParam_t) (
    HCRYPTPROV hProv,        /* in*/
    HCRYPTHASH hHash,        /* in*/
    DWORD dwParam,           /* in*/
    BYTE *pbData,            /* out*/
    DWORD *pdwDataLen,       /* in, out*/
    DWORD dwFlags            /* in*/
);

/*------------------------------------------------------*/
/* ����������� ������� CPHashData */
typedef BOOL (WINAPI *CPHashData_t) (
    HCRYPTPROV hProv,       /* in*/
    HCRYPTHASH hHash,       /* in*/
    WINCSP_CONST BYTE *pbData,     /* in*/
    DWORD dwDataLen,        /* in*/
    DWORD dwFlags           /* in*/
);

/*------------------------------------------------------*/
/* ����������� ������� CPHashSessionKey */
typedef BOOL (WINAPI *CPHashSessionKey_t) ( 
	HCRYPTPROV hProv,		/* in*/
	HCRYPTHASH hHash,		/* in*/
	HCRYPTKEY hKey,			/* in*/
	DWORD dwFlags			/* in*/
);

/*------------------------------------------------------*/
/* ����������� ������� CPGetHashParam */
typedef BOOL (WINAPI *CPSetHashParam_t) (
    HCRYPTPROV hProv,        /* in*/
    HCRYPTHASH hHash,        /* in*/
    DWORD dwParam,           /* in*/
    BYTE *pbData,            /* out*/
    DWORD dwFlags            /* in*/
);

/*------------------------------------------------------*/
/* ����������� ������� CPSignHash */
typedef BOOL (WINAPI *CPSignHash_t) (
    HCRYPTPROV hProv,           /* in*/
    HCRYPTHASH hHash,           /* in*/
    DWORD dwKeySpec,            /* in*/
    LPCWSTR sDescription,       /* in*/
    DWORD dwFlags,              /* in*/
    BYTE *pbSignature,          /* out*/
    DWORD *pdwSigLen            /* in, out*/
);

/*------------------------------------------------------*/
/* ����������� ������� CPVerifySignature */
typedef BOOL (WINAPI *CPVerifySignature_t) (
    HCRYPTPROV hProv,         /* in*/
    HCRYPTHASH hHash,         /* in*/
    WINCSP_CONST BYTE *pbSignature,  /* in*/
    DWORD dwSigLen,           /* in*/
    HCRYPTKEY hPubKey,        /* in*/
    LPCWSTR sDescription,     /* in*/
    DWORD dwFlags             /* in*/
);

/* ������������� � ��������� ���������������� */
typedef struct _CSP_FUNCTION_TABLE {
    CPAcquireContext_t	AcquireContext;
    CPReleaseContext_t	ReleaseContext;
    CPGetProvParam_t	GetProvParam;
    CPSetProvParam_t	SetProvParam;
    CPGenKey_t		GenKey;
    CPDestroyKey_t	DestroyKey;
    CPDeriveKey_t	DeriveKey;
    CPDuplicateKey_t	DuplicateKey;
    CPExportKey_t	ExportKey;
    CPGenRandom_t	GenRandom; 
    CPGetKeyParam_t	GetKeyParam;
    CPGetUserKey_t	GetUserKey;
    CPImportKey_t	ImportKey;
    CPSetKeyParam_t	SetKeyParam;
    CPEncrypt_t		Encrypt;
    CPDecrypt_t		Decrypt;
    CPCreateHash_t	CreateHash;
    CPDestroyHash_t	DestroyHash;
    CPDuplicateHash_t	DuplicateHash;
    CPGetHashParam_t	GetHashParam;
    CPHashData_t	HashData;
    CPHashSessionKey_t	HashSessionKey; 
    CPSetHashParam_t	SetHashParam;
    CPSignHash_t	SignHash;
    CPVerifySignature_t	VerifySignature;
} CSP_FUNCTION_TABLE, *PCSP_FUNCTION_TABLE;

CSP_EXPORT PCSP_FUNCTION_TABLE WINAPI CPGetFunctionTable (void);

typedef PCSP_FUNCTION_TABLE (WINAPI *CPGetFunctionTable_t) (void);

#ifdef __cplusplus
}
#endif

#endif /* _WINCSP_H_INCLUDED */
