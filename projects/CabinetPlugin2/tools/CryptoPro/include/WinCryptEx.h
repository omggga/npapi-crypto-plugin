#ifndef _WINCRYPTEX_H_INCLUDED
#define _WINCRYPTEX_H_INCLUDED

#if 0
#define CP_DEF_PROV_A "Crypto-Pro Cryptographic Service Provider"  // ���������� ���, ���. CP_GR3410_94_PROV
#define CP_DEF_PROV_W L"Crypto-Pro Cryptographic Service Provider"

#define CP_GR3410_94_PROV_A "Crypto-Pro GOST R 34.10-94 Cryptographic Service Provider"
#define CP_GR3410_94_PROV_W L"Crypto-Pro GOST R 34.10-94 Cryptographic Service Provider"

#define CP_GR3410_2001_PROV_A "Crypto-Pro GOST R 34.10-2001 Cryptographic Service Provider"
#define CP_GR3410_2001_PROV_W L"Crypto-Pro GOST R 34.10-2001 Cryptographic Service Provider"
#endif

#define CP_SMARTCARD_PROV_A "Crypto-Pro SmartCard CSP"
#define CP_SMARTCARD_PROV_W L"Crypto-Pro SmartCard CSP"

#define CP_KC1_GR3410_94_PROV_A "Crypto-Pro GOST R 34.10-94 KC1 CSP"
#define CP_KC1_GR3410_94_PROV_W L"Crypto-Pro GOST R 34.10-94 KC1 CSP"

#define CP_KC1_GR3410_2001_PROV_A "Crypto-Pro GOST R 34.10-2001 KC1 CSP"
#define CP_KC1_GR3410_2001_PROV_W L"Crypto-Pro GOST R 34.10-2001 KC1 CSP"

#define CP_KC2_GR3410_94_PROV_A "Crypto-Pro GOST R 34.10-94 KC2 CSP"
#define CP_KC2_GR3410_94_PROV_W L"Crypto-Pro GOST R 34.10-94 KC2 CSP"

#define CP_KC2_GR3410_2001_PROV_A "Crypto-Pro GOST R 34.10-2001 KC2 CSP"
#define CP_KC2_GR3410_2001_PROV_W L"Crypto-Pro GOST R 34.10-2001 KC2 CSP"

#define PH_GR3410_94_PROV_A "Phoenix-CS GOST R 34.10-94 Cryptographic Service Provider"
#define PH_GR3410_94_PROV_W L"Phoenix-CS GOST R 34.10-94 Cryptographic Service Provider"

#define PH_GR3410_2001_PROV_A "Phoenix-CS GOST R 34.10-2001 Cryptographic Service Provider"
#define PH_GR3410_2001_PROV_W L"Phoenix-CS GOST R 34.10-2001 Cryptographic Service Provider"

#ifdef UNICODE 
#define CP_DEF_PROV CP_DEF_PROV_W 
//#define CP_GR3410_94_PROV CP_KC1_GR3410_94_PROV_W
//#define CP_GR3410_2001_PROV CP_KC1_GR3410_2001_PROV_W
#define CP_SMARTCARD_PROV CP_SMARTCARD_PROV_W
#define CP_KC1_GR3410_94_PROV CP_KC1_GR3410_94_PROV_W
#define CP_KC1_GR3410_2001_PROV CP_KC1_GR3410_2001_PROV_W
#define CP_KC2_GR3410_94_PROV CP_KC2_GR3410_94_PROV_W
#define CP_KC2_GR3410_2001_PROV CP_KC2_GR3410_2001_PROV_W
#define PH_GR3410_94_PROV PH_GR3410_94_PROV_W
#define PH_GR3410_2001_PROV PH_GR3410_2001_PROV_W
#else 
#define CP_DEF_PROV CP_DEF_PROV_A 
//#define CP_GR3410_94_PROV CP_KC1_GR3410_94_PROV_A
//#define CP_GR3410_2001_PROV CP_KC1_GR3410_2001_PROV_A
#define CP_SMARTCARD_PROV CP_SMARTCARD_PROV_A
#define CP_KC1_GR3410_94_PROV CP_KC1_GR3410_94_PROV_A
#define CP_KC1_GR3410_2001_PROV CP_KC1_GR3410_2001_PROV_A
#define CP_KC2_GR3410_94_PROV CP_KC2_GR3410_94_PROV_A
#define CP_KC2_GR3410_2001_PROV CP_KC2_GR3410_2001_PROV_A
#define PH_GR3410_94_PROV PH_GR3410_94_PROV_A
#define PH_GR3410_2001_PROV PH_GR3410_2001_PROV_A
#endif

/*
 * ???? ���� ��������� PROV_GOST_DH �������� ��������������,
 * �.�. PROV_GOST_DH == 2 == PROV_RSA_SIG
 * ����������� PROV_GOST_94_DH ��� PROV_GOST_2001_DH
 */
#define PROV_GOST_DH 2

/*+
 * �� 09.07.01 � Platform SDK ��������� ������������������ 
 * CSP - PROV_RSA_AES == 24
 *
 * � ������ ���  PROV_GOST_* ��� ��������� ����� �� ��������� [53..89]
 */
#define PROV_GOST_94_DH 71
#define PROV_GOST_2001_DH 75

/* �������������� ���� �����������.
 * � Platform SDK ���������� ������ CRYPT_ASN_ENCODING (1),
 * CRYPT_NDR_ENCODING (2) � �������� ���� 0x10000 (PKCS7). */
#define CRYPT_XER_ENCODING (8)

/* �������������� ����� AcquireContext. ���������� ��������� ����������������. */
#define CRYPT_GENERAL 0x4000

/* ��������� ���������������� ������ */
#define USERKEY_KEYEXCHANGE			AT_KEYEXCHANGE
#define USERKEY_SIGNATURE			AT_SIGNATURE
#define USERKEY_SIMMERYMASTERKEY		27
/* Algorithm types */
#define ALG_TYPE_GR3410				(7 << 9)
/* GR3411 sub-ids */
#define ALG_SID_GR3411				30
/* G28147 sub_ids */
#define ALG_SID_G28147				30
#define ALG_SID_PRODIVERS			38
#define ALG_SID_RIC1DIVERS			40
/* Export Key sub_id */
#define ALG_SID_PRO_EXP				31
#define ALG_SID_SIMPLE_EXP			32
/* Hash sub ids */
#define ALG_SID_GR3410				30
#define ALG_SID_G28147_MAC			31
#define ALG_SID_TLS1_MASTER_HASH		32

/* GOST_DH sub ids */
#define ALG_SID_DH_EX_SF			30
#define ALG_SID_DH_EX_EPHEM			31
#define ALG_SID_PRO_AGREEDKEY_DH		33
#define ALG_SID_PRO_SIMMETRYKEY			34
#define ALG_SID_GR3410EL			35
#define ALG_SID_DH_EL_SF			36
#define ALG_SID_DH_EL_EPHEM			37


#define CALG_GR3411 \
    (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_GR3411)

#define CALG_G28147_MAC \
    (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_G28147_MAC)

#define CALG_G28147_IMIT \
    CALG_G28147_MAC

#define CALG_GR3410 \
    (ALG_CLASS_SIGNATURE | ALG_TYPE_GR3410 | ALG_SID_GR3410)

#define CALG_GR3410EL \
    (ALG_CLASS_SIGNATURE | ALG_TYPE_GR3410 | ALG_SID_GR3410EL)

#define CALG_G28147 \
    (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK | ALG_SID_G28147)

#define CALG_DH_EX_SF \
    (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_DH | ALG_SID_DH_EX_SF)

#define CALG_DH_EX_EPHEM \
    (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_DH | ALG_SID_DH_EX_EPHEM)

#define CALG_DH_EX \
    CALG_DH_EX_SF

#define CALG_DH_EL_SF \
    (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_DH | ALG_SID_DH_EL_SF)

#define CALG_DH_EL_EPHEM \
    (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_DH | ALG_SID_DH_EL_EPHEM)

#define CALG_PRO_AGREEDKEY_DH \
    (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_BLOCK | ALG_SID_PRO_AGREEDKEY_DH)

#define CALG_PRO_EXPORT \
    (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK | ALG_SID_PRO_EXP)

#define CALG_SIMPLE_EXPORT \
    (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK | ALG_SID_SIMPLE_EXP)

#define CALG_SIMMETRYKEY \
    CALG_G28147
    /* (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK | ALG_SID_SIMMETRYKEY) */

#define CALG_TLS1_MASTER_HASH \
    (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_TLS1_MASTER_HASH)

#define CALG_TLS1_MAC_KEY \
    (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_SECURECHANNEL | ALG_SID_SCHANNEL_MAC_KEY)

#define CALG_TLS1_ENC_KEY \
    (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_SECURECHANNEL | ALG_SID_SCHANNEL_ENC_KEY)

#define CALG_PRO_DIVERS \
    (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK | ALG_SID_PRODIVERS)
#define CALG_RIC_DIVERS \
    (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK | ALG_SID_RIC1DIVERS)
#define CALG_OSCAR_DIVERS CALG_RIC_DIVERS


#define CRYPT_ALG_PARAM_OID_GROUP_ID            20


#define CRYPT_PROMIX_MODE 0x00000001
#define CRYPT_SIMPLEMIX_MODE 0x00000000

/*��� ��������� ����� ��� �������������� ������ � ������� 
    ������� CPImportKey � ������ ����� ������� CALG_PRO_EXPORT*/
#define DIVERSKEYBLOB	0x70

/* �������������� ��������� ���������������� */
#define PP_LAST_ERROR 90
#define PP_ENUMOIDS_EX 91
#define PP_HASHOID 92
#define PP_CIPHEROID 93                                  
#define PP_SIGNATUREOID 94
#define PP_DHOID 95
#define PP_RESERVED1 96
#define PP_BIO_STATISTICA_LEN 97
#define PP_REBOOT 98
/*��������� �������� ������������ ��� ������� �� ���������, �������� �� WIN32*/
/*#define PP_ANSILASTERROR 99*/
#define PP_RANDOM 100
#define PP_DRVCONTAINER	101
#define PP_MUTEX_ARG	102
#define PP_ENUM_HASHOID 103
#define PP_ENUM_CIPHEROID 104
#define PP_ENUM_SIGNATUREOID 105
#define PP_ENUM_DHOID	106
#define PP_SET_PIN 107
#define PP_CHANGE_PIN 108
#define PP_HCRYPTPROV 109
#define PP_SELECT_CONTAINER 110
#define PP_FQCN 111
#define PP_CHECKPUBLIC 112
#define PP_ADMIN_CHECKPUBLIC 113
#define PP_ENUMREADERS 114
#define PP_CACHE_SIZE 115
#define PP_NK_SYNC 117
#define PP_INFO 118
#define PP_PIN_INFO 120
#define PP_PASSWD_TERM 123
#define PP_SAME_MEDIA 124
#define PP_DELETE_KEYSET 125
#define PP_DELETE_SAVED_PASSWD 126
#define PP_VERSION_TIMESTAMP 127
#define PP_SECURITY_LEVEL 129
#define PP_FAST_CODE 131
#define PP_CONTAINER_EXTENSION 132
#define PP_ENUM_CONTAINER_EXTENSION 133
#define PP_CONTAINER_EXTENSION_DEL 134
#define PP_CONTAINER_DEFAULT 135
#define PP_LCD_QUERY 136
#define PP_ENUM_LOG 137
#define PP_VERSION_EX 138

/* ����, ������������ ��� ������������ �����������, ��� ���������:
    Fully Qualified Container Name */
#define CRYPT_FQCN 0x10
/* ����, ������������ ��� ������������ �����������, ��� ����������
    ��������� ���������� ���� ����������� ����� �������� �������. 
    � ������ ���������� ���������� ������ ��� ���������� �����,
    ����� ����������� ������ ���������� ������� ��� ����������. */
#define CRYPT_UNIQUE 0x08

/* ���� ������������ ��� ������������ ������� �������,
   ��� ���������� ������������ � ���������� �������. */
#define CRYPT_FINISH 0x04

/* ����, ��� ������ PP_DELETE_ERROR � �������� ���������� ������������
    �� ����� ������ ��������� �� ������. */
#define CRYPT_DELETEKEYSET_PART 0x1


/* �������������� ��������� ������� ���� */
#define HP_HASHSTARTVECT 0x0008
#define HP_HASHCOPYVAL	 0x0009
#define HP_OID 0x000a
#define HP_OPEN 0x000B
#define HP_OPAQUEBLOB 0x000C

/* �������������� ��������� ����� */
#define KP_SV KP_IV
#define KP_MIXMODE 101
#define KP_OID 102
#define KP_HASHOID 103
#define KP_CIPHEROID 104
#define KP_SIGNATUREOID 105
#define KP_DHOID 106
#define KP_KC1EXPORT	0x800000f0

/* ����� ���� ������
 * ����������� ����� ������, ������������ �����
 * CryptGetProvParam(PP_LAST_ERROR) */
/* ���� ������ ��� */
#define GPE_FAIL_TESTBUFFER 0x0301
#define GPE_FAIL_STATBUFFER 0x0401
#define GPE_DIFERENT_PARAMETERS 0x0501
/* ���� ������ ������� ���� 28147-89 */
#define GPE_CORRUPT_KEYCONTEXT 0x0102
#define	GPE_CHECKPROC_GAMMING_CNT 0x0402
#define	GPE_CHECKPROC_ENCRYPT_CFB 0x0502
#define GPE_SECURITY_LEVEL 0x600

/* ��� ������ �������� ������� �������� � ����������� ��� ��������
 * ���������� */
#define GPE_CHECKCARRIER 0x0805
/* ���� ������ ������� ������� */
#define GPE_CORRUPT_KEYPAIR_INFO 0x0104
/* ��� ������ ������� ������������ */
#define GPE_CHECKPROC_TESTFAIL 0x0704
#define GPE_RANDOMFAIL 0x0604
/* ��� ���������� ������������������ ��������� ���������  */
#define GPE_NO_CERTSEED 0x0901

/* OID for Signature 512*/
#define OID_Sg64_Test	    "1.2.643.2.2.32.0" 	/*Test*/
#define OID_SgDH64_VerbaO   "1.2.643.2.2.32.1" 	/*VerbaO*/

/* CRYPT_PRIVATE_KEYS_ALG_OID_GROUP_ID */
#define szOID_CP_GOST_PRIVATE_KEYS_V1 "1.2.643.2.2.37.1"
#define szOID_CP_GOST_PRIVATE_KEYS_V2 "1.2.643.2.2.37.2"
#define szOID_CP_GOST_PRIVATE_KEYS_V2_FULL "1.2.643.2.2.37.2.1"
#define szOID_CP_GOST_PRIVATE_KEYS_V2_PARTOF "1.2.643.2.2.37.2.2"

/* CRYPT_HASH_ALG_OID_GROUP_ID */
#define szOID_CP_GOST_R3411 "1.2.643.2.2.9"

/* CRYPT_ENCRYPT_ALG_OID_GROUP_ID */
#define szOID_CP_GOST_28147 "1.2.643.2.2.21"

/* CRYPT_PUBKEY_ALG_OID_GROUP_ID */
#define szOID_CP_GOST_R3410 "1.2.643.2.2.20"
#define szOID_CP_GOST_R3410EL "1.2.643.2.2.19"
#define szOID_CP_DH_EX "1.2.643.2.2.99"
#define szOID_CP_DH_EL "1.2.643.2.2.98"

/* CRYPT_SIGN_ALG_OID_GROUP_ID */
#define szOID_CP_GOST_R3411_R3410 "1.2.643.2.2.4"
#define szOID_CP_GOST_R3411_R3410EL "1.2.643.2.2.3"

/* CRYPT_ENHKEY_USAGE_OID_GROUP_ID */
#define szOID_KP_TLS_PROXY "1.2.643.2.2.34.1"
#define szOID_KP_RA_CLIENT_AUTH "1.2.643.2.2.34.2"
#define szOID_KP_WEB_CONTENT_SIGNING "1.2.643.2.2.34.3"
#define szOID_KP_RA_ADMINISTRATOR "1.2.643.2.2.34.4"
#define szOID_KP_RA_OPERATOR "1.2.643.2.2.34.5"

/* Our well-known policy ID */
#define szOID_CEP_BASE_PERSONAL	"1.2.643.2.2.38.1"
#define szOID_CEP_BASE_NETWORK	"1.2.643.2.2.38.2"

/* OID for HASH */
#define OID_HashTest "1.2.643.2.2.30.0"
#define OID_HashVerbaO "1.2.643.2.2.30.1"	/* ���� � 34.11-94, ��������� �� ��������� */
#define OID_HashVar_1 "1.2.643.2.2.30.2"
#define OID_HashVar_2 "1.2.643.2.2.30.3"
#define OID_HashVar_3 "1.2.643.2.2.30.4"
#define OID_HashVar_Default OID_HashVerbaO

/* OID for Crypt */
#define OID_CryptTest "1.2.643.2.2.31.0"
#define OID_CipherVerbaO "1.2.643.2.2.31.1"	/* ���� 28147-89, ��������� �� ��������� */
#define OID_CipherVar_1 "1.2.643.2.2.31.2"	/* ���� 28147-89, ��������� ���������� 1 */
#define OID_CipherVar_2 "1.2.643.2.2.31.3" 	/* ���� 28147-89, ��������� ���������� 2 */
#define OID_CipherVar_3 "1.2.643.2.2.31.4"	/* ���� 28147-89, ��������� ���������� 3 */
#define OID_CipherVar_Default OID_CipherVerbaO
#define OID_CipherOSCAR "1.2.643.2.2.31.5"	/* ���� 28147-89, ��������� ����� 1.1 */
#define OID_CipherTestHash "1.2.643.2.2.31.6"	/* ���� 28147-89, ��������� ����� 1.0 */
#define OID_CipherRIC1 "1.2.643.2.2.31.7"	/* ���� 28147-89, ��������� ��� 1 */
/* OID for Signature 1024*/
#define OID_SignDH128VerbaO   "1.2.643.2.2.32.2" 	/*VerbaO*/
#define OID_Sign128Var_1   "1.2.643.2.2.32.3" 
#define OID_Sign128Var_2   "1.2.643.2.2.32.4" 
#define OID_Sign128Var_3   "1.2.643.2.2.32.5" 
/* OID for DH 1024*/
#define OID_DH128Var_1   "1.2.643.2.2.33.1" 
#define OID_DH128Var_2   "1.2.643.2.2.33.2" 
#define OID_DH128Var_3   "1.2.643.2.2.33.3" 

#define OID_ECCTest3410 "1.2.643.2.2.35.0"      /* ���� � 34.10-2001, �������� ��������� */
#define OID_ECCSignDHPRO "1.2.643.2.2.35.1"	/* ���� � 34.10-2001, ��������� �� ��������� */
#define OID_ECCSignDHOSCAR "1.2.643.2.2.35.2"	/* ���� � 34.10-2001, ��������� ����� 2.x */
#define OID_ECCSignDHVar_1 "1.2.643.2.2.35.3"	/* ���� � 34.10-2001, ��������� ������� 1 */
#define OID_ECCDHPRO "1.2.643.2.2.36.0"		/* ���� � 34.10-2001, ��������� ������ �� ��������� */
#define OID_ECCDHPVar_1 "1.2.643.2.2.36.1"	/* ���� � 34.10-2001, ��������� ������ 1 */


#define X509_GR3410_PARAMETERS ((LPCSTR) 5001)
#define OBJ_ASN1_CERT_28147_ENCRYPTION_PARAMETERS ((LPCSTR) 5007)

/* �������� ��� ������������� � ������� 1.1*/
#define OID_SipherVerbaO	OID_CipherVerbaO
#define OID_SipherVar_1		OID_CipherVar_1 
#define OID_SipherVar_2		OID_CipherVar_2 
#define OID_SipherVar_3		OID_CipherVar_3 
#define OID_SipherVar_Default	OID_CipherVar_Default

#define ASN1OID_CP_DH_EX ASN1_OBJID_CP_DH_EX
#define ASN1OID_CP_DH_EL ASN1_OBJID_CP_DH_EL

/* ����� ���������� "������������" �� ���� 28147-89.*/
/*! \ingroup ProCSPData 
 *  \def CRYPT_MODE_CNT
 *  \brief ����� ���������� "�������������" �� ���� 28147-89 
 */
#define CRYPT_MODE_CNT          CRYPT_MODE_OFB       // GOST 28147-89 in "gammirovanie" (counter) mode

/* ����� ���������� ����� ��� ���� 28147, ������� � ������.*/
/*! \ingroup ProCSPData 
 *  \def SECRET_KEY_LEN
 *  \brief ����� � ������ ����� ���� 28147-89 � ��������� ������ 
 * ���� � 34.10-94 � ���� � 28147-89.
 */
#define SECRET_KEY_LEN		32

/*! \ingroup ProCSPData 
 *  \def G28147_KEYLEN
 *  \brief ����� � ������ ����� ���� 28147-89.
 * \ref SECRET_KEY_LEN
 */
#define G28147_KEYLEN        SECRET_KEY_LEN

/*! \ingroup ProCSPData
 *  \def EXPORT_IMIT_SIZE 
 *  \brief ����� � ������ ������������ ��� �������/�������� 
 */
#define EXPORT_IMIT_SIZE		4

/*! \ingroup ProCSPData 
 *  \def SEANCE_VECTOR_LEN
 *  \brief �����  � ������ ������� ������������ ��������� 
 */
#define SEANCE_VECTOR_LEN		8


/* ��������� � ��������� ��� ���� �������� ������� �*/
/* ��������� ������������� ������*/

/*! \ingroup ProCSPData 
 *  \def GR3410_1_MAGIC
 *  \brief ������� ������ ���� � 34.10-94 � ���� � 34.10-2001
 */
#define GR3410_1_MAGIC			0x3147414D
#define GR3410_2_MAGIC			GR3410_1_MAGIC//0x3145474a
	
#define DH_1_MAGIC			GR3410_1_MAGIC
#define DH_2_MAGIC			GR3410_1_MAGIC
#define DH_3_MAGIC			GR3410_1_MAGIC

/*! \ingroup ProCSPData 
 *  \def G28147_MAGIC
 *  \brief ������� ������ ���� 28147-89 � ������ ������ TLS
 */
#define G28147_MAGIC			0x374a51fd
#define SIMPLEBLOB_MAGIC		G28147_MAGIC
#define G28147_OPAQUEMAGIC		0x374a51fe
/*! \ingroup ProCSPData 
 *  \def DIVERS_MAGIC
 *  \brief ������� ��������� ����� ������� �������������� ����� 
 */
#define DIVERS_MAGIC			0x31564944

/*! \ingroup ProCSPData 
 *  \def BLOB_VERSION
 *  \brief ������� �������� ������ ��������� �����.
 */
#define BLOB_VERSION			(BYTE)0x20


/* ����������� ��� */
#define VER_TYPE_DEBUG 1
#define VER_TYPE_RELEASE 0

#define VER_ARCH_IA32 0
#define VER_ARCH_IA64 1
#define VER_ARCH_SPARC32 2
#define VER_ARCH_SPARC64 3

#define VER_OS_WINDOWS 0
#define VER_OS_SOLARIS 1
#define VER_OS_FREEBSD 2
#define VER_OS_LINUX 3


typedef struct PROV_PP_VERSION_EX_ {

    DWORD Version;
    DWORD Build;
    DWORD TypeDebRel;
    DWORD Architecture;
    DWORD OS;
} PROV_PP_VERSION_EX;


/* ����������� ��� ��������� SIMPLEBLOB*/
/* ��������� SIMPLEBLOB*/
/*!
 * \ingroup ProCSPData
 *
 * \brief ��������� CRYPT_SIMPLEBLOB_HEADER �������� ����������� ��������� BLOBHEADER � 
 * ��������� � ������ ���� \b pbData ��������� ����� ���� SIMPLEBLOB ��� ������ "��������� CSP".
 *
 * \req_wincryptex
 * \sa _PUBLICKEYSTRUC
 * \sa PCRYPT_SIMPLEBLOB
 * \sa CPExportKey
 * \sa CPGetKeyParam
 */
typedef struct CRYPT_SIMPLEBLOB_HEADER_ {
    BLOBHEADER BlobHeader;
                    /*!< ����� ��������� ��������� �����. ���������� �������� �����
                     * ������������ � �������� �����. ��. \ref _PUBLICKEYSTRUC.
                     */
    DWORD Magic;
                    /*!< ������� ������ �� ���� 28147-89 ��� ������ ������ TLS,
                     * ��������������� � \ref G28147_MAGIC.
                     */
    ALG_ID EncryptKeyAlgId;
                    /*!< ���������� �������� �������� �����. ���� �������� ��������
                     * ���������� ����� ��������. ��. \ref #CPGetKeyParam.
                     */
} CRYPT_SIMPLEBLOB_HEADER;
/*!
 * \ingroup ProCSPData
 *
 * \brief ��������������� (�. �. ���������������� ���������) CRYPT_SIMPLEBLOB ��������� ��������� �������� ����
 * ���� SIMPLEBLOB ��� ������ "��������� CSP". ��� ���� ���� ��������������� 
 * ��������� �� ������� ����� � ��������� � ������� ������� ���� (ASN1 DER). ������� ������� ���� ��������, 
 * ��� ����� 0x12345678 ����� �������� � ���� 0x12 0x34 0x56 0x78 � ������� �� Intell ������� 
 * ���� � ������: 0x78 0x56 0x34 0x12.
 *
 * \req_wincryptex
 * \sa CRYPT_SIMPLEBLOB_HEADER
 * \sa CPExportKey
 * \sa CPGetKeyParam
 */
typedef struct CRYPT_SIMPLEBLOB_ {
    CRYPT_SIMPLEBLOB_HEADER tSimpleBlobHeader;
                    /*!< ����� ��������� ��������� ����� ���� SIMPLEBLOB "��������� CSP".
                     */
    BYTE    bSV[SEANCE_VECTOR_LEN];
                    /*!< ������ ������������ ��� ��������� CALG_PRO_EXPORT. 
                     * ��. \ref SEANCE_VECTOR_LEN.
                     */
    BYTE    bEncryptedKey[G28147_KEYLEN];
                    /*!< ������������� ���� ���� 28147-89.
                     * ��. \ref G28147_KEYLEN.
                     */
    BYTE    bMacKey[EXPORT_IMIT_SIZE];
                    /*!< ������������ �� ���� 28147-89 �� ����. ��������������
                     * �� ������������ � ����������� ����� �������������.
                     * ��. \ref EXPORT_IMIT_SIZE.
                     */
    BYTE    bEncryptionParamSet[1];
                    /*!< �������� ASN1 ��������� � DER ���������, ������������ 
                     * ��������� ���������� ���������� ���� 28147-89:
                     * \code
                     *      encryptionParamSet
                     *          OBJECT IDENTIFIER (
                     *              id-Gost28147-89-TestParamSet |      -- Only for tests use
                     *              id-Gost28147-89-CryptoPro-A-ParamSet |
                     *              id-Gost28147-89-CryptoPro-B-ParamSet |
                     *              id-Gost28147-89-CryptoPro-C-ParamSet |
                     *              id-Gost28147-89-CryptoPro-D-ParamSet |
                     *              id-Gost28147-89-CryptoPro-Simple-A-ParamSet |
                     *              id-Gost28147-89-CryptoPro-Simple-B-ParamSet |
                     *              id-Gost28147-89-CryptoPro-Simple-C-ParamSet |
                     *              id-Gost28147-89-CryptoPro-Simple-D-ParamSet
                     * \endcode
                     */
}   CRYPT_SIMPLEBLOB, *PCRYPT_SIMPLEBLOB;

typedef struct _CRYPT_OPAQUEBLOB_1 { 
    CRYPT_SIMPLEBLOB_HEADER tSimpleBlobHeader;
                    /*!< ����� ��������� ��������� ����� ���� SIMPLEBLOB "��������� CSP".
                     */
    BYTE    bSV[SEANCE_VECTOR_LEN];
                    /*!< ������ ������������ ��� ��������� CALG_PRO_EXPORT. 
                     * ��. \ref SEANCE_VECTOR_LEN.
                     */
    BYTE    bEncryptedKey[G28147_KEYLEN];
                    /*!< ������������� ���� ���� 28147-89.
                     * ��. \ref G28147_KEYLEN.
                     */
    BYTE    bMacKey[EXPORT_IMIT_SIZE];
                    /*!< ������������ �� ���� 28147-89 �� ����. ��������������
                     * �� ������������ � ����������� ����� �������������.
                     * ��. \ref EXPORT_IMIT_SIZE.
                     */
    BYTE    bEncryptedInitKey[G28147_KEYLEN];
                    /*!< ������������� ���� ���� 28147-89.
                     * ��. \ref G28147_KEYLEN.
                     */
    BYTE    bMacInitKey[EXPORT_IMIT_SIZE];
                    /*!< ������������ �� ���� 28147-89 �� ����. ��������������
                     * �� ������������ � ����������� ����� �������������.
                     * ��. \ref EXPORT_IMIT_SIZE.
                     */
      /*����������� ����*/
   BYTE    bCurrentIV[SEANCE_VECTOR_LEN];
                    /*!< ������ ������������ ���������. 
                     * ��. \ref SEANCE_VECTOR_LEN.
                     */
    BYTE    bChainBlock[8];
                    /*!< ���� ����������. ������������� ����� ������� �� ������ ����������.
                     * 
                     */
    BYTE    bAccCiphertextLen[sizeof(DWORD)];
                    /*!< ����������� ����� ������������ ������. 
                     * 
                     */
    BYTE    bCipherMode[sizeof(DWORD)];
    BYTE    bMixMode[sizeof(DWORD)];
    BYTE    bFlags[4];
    BYTE    bPaddingMode[sizeof(DWORD)];
    BYTE    bAlgId[sizeof(ALG_ID)];
    BYTE    bCommonFlags[4];
    BYTE    bCheckSum[sizeof(DWORD)];
    BYTE    bEncryptionParamSet[1];
                    /*!< �������� ASN1 ��������� � DER ���������, ������������ 
                     * ��������� ���������� ���������� ���� 28147-89:
                     * \code
                     *      encryptionParamSet
                     *          OBJECT IDENTIFIER (
                     *              id-Gost28147-89-TestParamSet |      -- Only for tests use
                     *              id-Gost28147-89-CryptoPro-A-ParamSet |
                     *              id-Gost28147-89-CryptoPro-B-ParamSet |
                     *              id-Gost28147-89-CryptoPro-C-ParamSet |
                     *              id-Gost28147-89-CryptoPro-D-ParamSet |
                     *              id-Gost28147-89-CryptoPro-Simple-A-ParamSet |
                     *              id-Gost28147-89-CryptoPro-Simple-B-ParamSet |
                     *              id-Gost28147-89-CryptoPro-Simple-C-ParamSet |
                     *              id-Gost28147-89-CryptoPro-Simple-D-ParamSet
                     * \endcode
                     */
}   CRYPT_OPAQUEBLOB_1;

typedef struct _CRYPT_OPAQUEBLOB_2 { 
    CRYPT_SIMPLEBLOB_HEADER tSimpleBlobHeader;
                    /*!< ����� ��������� ��������� ����� ���� SIMPLEBLOB "��������� CSP".
                     */
    void * hKey;
    BYTE    bCheckSum[sizeof(DWORD)];
} CRYPT_OPAQUEBLOB_2;

typedef union _PCRYPT_OPAQUEBLOB_ {
    CRYPT_OPAQUEBLOB_1 * pb1;
    CRYPT_OPAQUEBLOB_2 * pb2;
}   PCRYPT_OPAQUEBLOB;
typedef union _CRYPT_OPAQUEBLOB_ {
    CRYPT_OPAQUEBLOB_1  b1;
    CRYPT_OPAQUEBLOB_2  b2;
}   CRYPT_OPAQUEBLOB;
				   
typedef struct _CRYPT_OPAQUEHASHBLOB { 
    CRYPT_SIMPLEBLOB_HEADER tSimpleBlobHeader;
                    /*!< ����� ��������� ��������� ����� ���� SIMPLEBLOB "��������� CSP".
                     */
   BYTE    ImitVal[8];
   BYTE    bCurrKey[G28147_KEYLEN];
                    /*!< ������������� ���� ���� 28147-89.
                     * ��. \ref G28147_KEYLEN.
                     */
      /*����������� ����*/
    BYTE    bChainBlock[8];
                    /*!< ���� ����������. ������������� ����� ������� �� ������ ����������.
                     * 
                     */
    BYTE    bAccCiphertextLen[sizeof(DWORD)];
                    /*!< ����������� ����� ������������ ������. 
                     * 
                     */
    BYTE    bFlags[4];
    BYTE    bMixMode[sizeof(DWORD)];
    BYTE    bHFlags[4];
    BYTE    bCheckSum[sizeof(DWORD)];
}   CRYPT_OPAQUEHASHBLOB_1;




/*!
 * \ingroup ProCSPData
 *
 * \brief ��������� CRYPT_PUBKEYPARAM �������� ������� ������ 
 * �� ���� � 34.10-94 ��� ���� � 34.10-2001.
 *
 * \req_wincryptex
 * \sa CRYPT_PUBKEY_INFO_HEADER
 * \sa CPExportKey
 * \sa CPGetKeyParam
 */
typedef struct _CRYPT_PUBKEYPARAM_ {
    DWORD Magic;
                    /*!< ������� ������ �� ���� � 34.10-94 ��� ���� � 34.10-2001
                     * ��������������� � \ref GR3410_1_MAGIC.
                     */
    DWORD BitLen;
                    /*!< ����� ��������� ����� � �����.
                     */
} CRYPT_PUBKEYPARAM, *LPCRYPT_PUBKEYPARAM;

/* ��������� PUBLICKEYBLOB � PRIVATEKEYBLOB*/
/*!
 * \ingroup ProCSPData
 *
 * \brief ��������� CRYPT_PUBKEY_INFO_HEADER �������� ���������
 * ����� ��������� ����� ��� ����� �������� ����
 * �� ���� � 34.10-94 ��� ���� � 34.10-2001.
 *
 * \req_wincryptex
 * \sa _PUBLICKEYSTRUC
 * \sa CRYPT_PUBKEYPARAM
 * \sa CPExportKey
 * \sa CPGetKeyParam
 */
typedef struct CRYPT_PUBKEY_INFO_HEADER_ {
    BLOBHEADER BlobHeader;
                    /*!< ����� ��������� ��������� �����. ���������� ��� ��� � �������� �����
                     * ������������ � �������� �����. ��� �������� ������ �������� 
                     * ����� ������, ���� CALG_GR3410, ���� CALG_GR3410EL. ��� �������� 
                     * ��� �������� �������� � ����������. ��. \ref _PUBLICKEYSTRUC.
                     */
    CRYPT_PUBKEYPARAM KeyParam;
                    /*!< �������� ������� � ������ ������ ���� � 34.10-94 � ���� � 34.10-2001.
                     */
} CRYPT_PUBKEY_INFO_HEADER;

/*!
 * \ingroup ProCSPData
 *
 * \brief ��������������� CRYPT_PUBLICKEYBLOB ��������� ��������� �������� ����
 * ���� PUBLICKEYBLOB ��� ������ "��������� CSP". ��� ���� ���� ��������������� 
 * ��������� �� ������� ����� � ��������� � ������� ������� ���� (ASN1 DER). ������� ������� ���� ��������, 
 * ��� ����� 0x12345678 ����� �������� � ���� 0x12 0x34 0x56 0x78 � ������� �� Intell ������� 
 * ���� � ������: 0x78 0x56 0x34 0x12.
 *
 * \req_wincryptex
 * \sa CRYPT_PUBKEY_INFO_HEADER
 * \sa CPExportKey
 * \sa CPGetKeyParam
 */
typedef struct CRYPT_PUBLICKEYBLOB_ {
    CRYPT_PUBKEY_INFO_HEADER tPublicKeyParam;
                    /*!< ����� ��������� ��������� ����� ���� PUBLICKEYBLOB "��������� CSP".
                     */
    BYTE    bASN1GostR3410_94_PublicKeyParameters[1/*������������*/];
                    /*!< �������� ASN1 ��������� � DER ���������, ������������ 
                     * ��������� ��������� �����:
                     * \code
                     *      GostR3410-94-PublicKeyParameters ::=
                     *           SEQUENCE {
                     *              publicKeyParamSet
                     *                  OBJECT IDENTIFIER (
                     *                      id-GostR3410-94-TestParamSet |      -- Only for tests use
                     *                      id-GostR3410-94-CryptoPro-A-ParamSet |
                     *                      id-GostR3410-94-CryptoPro-B-ParamSet |
                     *                      id-GostR3410-94-CryptoPro-C-ParamSet |
                     *                      id-GostR3410-94-CryptoPro-D-ParamSet |
                     *                      id-GostR3410-94-CryptoPro-XchA-ParamSet |
                     *                      id-GostR3410-94-CryptoPro-XchB-ParamSet |
                     *                      id-GostR3410-94-CryptoPro-XchC-ParamSet
                     *                  ),
                     *              digestParamSet
                     *                  OBJECT IDENTIFIER (
                     *                      id-GostR3411-94-TestParamSet |      -- Only for tests use
                     *                      id-GostR3411-94-CryptoProParamSet
                     *                  ),
                     *              encryptionParamSet
                     *                  OBJECT IDENTIFIER (
                     *                      id-Gost28147-89-TestParamSet |      -- Only for tests use
                     *                      id-Gost28147-89-CryptoPro-A-ParamSet |
                     *                      id-Gost28147-89-CryptoPro-B-ParamSet |
                     *                      id-Gost28147-89-CryptoPro-C-ParamSet |
                     *                      id-Gost28147-89-CryptoPro-D-ParamSet |
                     *                      id-Gost28147-89-CryptoPro-Simple-A-ParamSet |
                     *                      id-Gost28147-89-CryptoPro-Simple-B-ParamSet |
                     *                      id-Gost28147-89-CryptoPro-Simple-C-ParamSet |
                     *                      id-Gost28147-89-CryptoPro-Simple-D-ParamSet
                     *                  ) OPTIONAL
                     *          }
                     * \endcode
                     */
    BYTE    bPublicKey[1/*������������*/];
                    /*!< �������� �������� ���� � ������� ������������� (ASN1 DER). 
                     * ����� ������� ����� tPublicKeyParam.KeyParam.BitLen/8.
                     */
}   CRYPT_PUBLICKEYBLOB, *PCRYPT_PUBLICKEYBLOB;

/*!
 * \ingroup ProCSPData
 *
 * \brief ��������������� CRYPT_PRIVATEKEYBLOB ��������� ��������� �������� ����
 * ���� PRIVATEKEYBLOB ��� ������ "��������� CSP". ��� ���� ���� ��������������� 
 * ��������� �� ������� ����� � ��������� � ������� ������� ���� (ASN1 DER). ������� ������� ���� ��������, 
 * ��� ����� 0x12345678 ����� �������� � ���� 0x12 0x34 0x56 0x78 � ������� �� Intell ������� 
 * ���� � ������: 0x78 0x56 0x34 0x12.
 *
 * \req_wincryptex
 * \sa CRYPT_PUBKEY_INFO_HEADER
 * \sa CPExportKey
 * \sa CPGetKeyParam
 */
typedef struct CRYPT_PRIVATEKEYBLOB_ {
    CRYPT_PUBKEY_INFO_HEADER tPublicKeyParam;
                    /*!< ����� ��������� ��������� ����� ���� PRIVATEKEYBLOB "��������� CSP".
                     */
    BYTE    bExportedKeys[1/* ������ ������.*/];
	/*
	KeyTransferContent ::=
	SEQUENCE {
	    encryptedPrivateKey  GostR3410EncryptedKey,
	    privateKeyParameters PrivateKeyParameters,
	}
	KeyTransfer ::=
	SEQUENCE {
	    keyTransferContent       KeyTransferContent,
	    hmacKeyTransferContent   Gost28147HMAC
	}
	*/
}   CRYPT_PRIVATEKEYBLOB, *PCRYPT_PRIVATEKEYBLOB;

/* ����������� ��� ��������� DIVERSBLOB*/
/*!
 * \ingroup ProCSPData
 *
 * \brief ��������� CRYPT_DIVERSBLOB ��������� ����
 * ���� DIVERSBLOB ��� ��������� �������������� ������ ��������� CSP.
 * ��� ���� ���� ���������������
 * ��������� �� ������� ����� � ��������� � ������� ������� ���� (ASN1 DER). ������� ������� ���� ��������, 
 * ��� ����� 0x12345678 ����� �������� � ���� 0x12 0x34 0x56 0x78 � ������� �� Intell ������� 
 * ���� � ������: 0x78 0x56 0x34 0x12.
 *
 * \req_wincryptex    
 * \sa CPImportKey
 */
typedef struct _CRYPT_DIVERSBLOBHEADER {
    BLOBHEADER BlobHeader;
                /*!< ����� ��������� �����, ������������������ ����.
                 *  ���������� �������� ����������������� �����.
                 */
    ALG_ID      aiDiversAlgId;
                /*!< ���������� �������� �������������� �����.
                 */
    DWORD       dwDiversMagic;
                /*!< ������� �������������� �����,
                 * ��������������� � \ref DIVERS_MAGIC.
                 */
   /*    BYTE        *pbDiversData;
                !< ��������� �� ������, �� ������� ����������������� ����.
                 */
    DWORD       cbDiversData;
                /*!< ����� ������, �� ������� ����������������� ����.
                 */
} CRYPT_DIVERSBLOBHEADER, *LPCRYPT_DIVERSBLOBHEADER;

typedef struct _CRYPT_DIVERSBLOB {
    CRYPT_DIVERSBLOBHEADER DiversBlobHeader;
                /*!< ����� ��������� �����, �������D���������� ����.
                 *  ���������� �������� ����������������� �����.
                 */
    BYTE        bDiversData[4/*�������� 40*/];
                /*!< ������, �� ������� ����������������� ����.
                 */
} CRYPT_DIVERSBLOB, *LPCRYPT_DIVERSBLOB;

/*! \brief ��� ������: ������ ��� pin */
#define CRYPT_PIN_PASSWD 0 
/*! \brief ��� ������: ��� ���������� ������������
     ������������ ��� ����������. */
#define CRYPT_PIN_ENCRYPTION 1
/*! \brief ��� ������: �������� ���������� �� ����� �� HANDLE.
     ������������ ����� �����������. */
#define CRYPT_PIN_NK 2
/*! \brief ��� ������: ���������� */
#define CRYPT_PIN_UNKNOWN 3
/*! \brief ��� ������: ��� � �������� ���������� � ����. */
#define CRYPT_PIN_QUERY 4 
/*! \brief ��� ������: �������� ������. */
#define CRYPT_PIN_CLEAR 5
/*! \brief ��� ������: ������������ ���������� �������. */
#define CRYPT_PIN_HARDWARE_PROTECTION 6

/*!
 * \ingroup ProCSPData
 *
 * \brief ��������� �������� ���������� ��� ������� ������ ����������
 *
 * \req_wincryptex
 * \sa CPSetProvParam
 */
typedef struct CRYPT_PIN_NK_PARAM_ {
    short n; /*!< ���������� ������������ ������. */
    short k; /*!< ���������� ������ ��� ��������. */
    HCRYPTPROV *parts; /*!< HANDLE ������ ����������. */
} CRYPT_PIN_NK_PARAM;

/*!
 * \brief ��������� �������� ������, pin-����, ����� ����������,
 *  HANDLE ���������� ��� ����� ������.
 */
typedef union CRYPT_PIN_SOURCE_ { 
    char *passwd; /*!< ������, PIN-���, ��� ����������. */
    HCRYPTPROV prov; /*!< HANDLE ����������. */
    CRYPT_PIN_NK_PARAM nk_handles; /*!< �������� �� NK �� HANDLE */
} CRYPT_PIN_SOURCE;

/*!
 * \ingroup ProCSPData
 *
 * \brief ��������� �������� ���������� ���:
 *  1) ����� ������ ����������, 
 *  2) �������� ������� ������� � ���������� (���, handle, ������), �� ����� �������� 
 *     ����������� ���������� ������� ����������.
 *
 * \req_wincryptex
 * \sa CPSetProvParam
 */
typedef struct CRYPT_PIN_PARAM_ {
    BYTE type; 
    /*!< ��� ������.
 *  CRYPT_PIN_PASSWD - ������ ��� PIN,
 *  CRYPT_PIN_ENCRYPTION - HANDLE ���������� ������������.
 *  CRYPT_PIN_QUERY - ��� � �������� ���������� � ����,
 *  CRYPT_PIN_CLEAR - �������� ������.
 *  CRYPT_PIN_NK - ������� �� ����� k �� n
 */
     CRYPT_PIN_SOURCE dest; /*!< ������ ���������������� ���� */
} CRYPT_PIN_PARAM;

/*!
 * \ingroup ProCSPData
 *
 * \brief ��������� ��������� ���������� � ���������� ������������ �� �����.
 *
 * \req_wincryptex
 * \sa CPSetProvParam
 */
typedef struct CRYPT_NK_INFO_PARAM_ {
    short n; /*!< ���������� ������, �� ������� �������� ���������. */
    short k; /*!< ���������� ������, ����������� ��� ��������� ������. */
    char parts[1]; /*!< ������������������ n ASCIIZ �����. */
} CRYPT_NK_INFO_PARAM;

/*!
 * \ingroup ProCSPData
 *
 * \brief ��������� ��������� ���������� � ������ �� ���������.
 *
 * \req_wincryptex
 * \sa CPSetProvParam
 */
typedef struct CRYPT_PASSWD_INFO_PARAM_ {
    unsigned min_passwd_length; /*!< ����������� ���������� ������ ������. */
    unsigned max_passwd_length; /*!< ������������ ���������� ������ ������. */
    unsigned passwd_type; /*!< ��� ������. */
} CRYPT_PASSWD_INFO_PARAM;

#define CSP_INFO_SIZE sizeof(CSP_INFO)

typedef union CRYPT_PIN_INFO_SOURCE_ {
    CRYPT_PASSWD_INFO_PARAM passwd;
    CRYPT_NK_INFO_PARAM nk_info;
    char encryption[1];
} CRYPT_PIN_INFO_SOURCE;

typedef struct CRYPT_PIN_INFO_ {
    BYTE type; 
    /*!< ��� ������.
 *  CRYPT_PIN_UNKNOWN - ��� ����������
 *  CRYPT_PIN_PASSWD - ������ ��� PIN,
 *  CRYPT_PIN_ENCRYPTION - HANDLE ���������� ������������.
 *  CRYPT_PIN_NK - ������� �� ����� k �� n
 *  CRYPT_PIN_HARDWARE_PROTECTION - ��� ������ ������������ ���������� �������
 */
     CRYPT_PIN_INFO_SOURCE dest; /*!< ������ ���������������� ���� */
} CRYPT_PIN_INFO;

typedef struct CRYPT_CACHE_SIZE_ {
    DWORD cache_size; /*!< ������ ����. */
    DWORD max_cache_size; /*!< ������������ ������ ���. */
    BOOL is_writable; /*!< ��. CACHE_RO  */
} CRYPT_CACHE_SIZE;

#define CSP_INFO_FREE_SPACE	(0)	/* ��������� ����� �� /var � bytes */
#define CSP_INFO_NUMBER_UL	(1)	/* "\\local\\number_UL" --- ���������� ���������� ������ �� */
#define CSP_INFO_NUMBER_SIGNS	(2)     /* "\\local\\number_signs" --- ���������� �������� ������� */
#define CSP_INFO_KCARDS_CHANGES	(3)     /* "\\local\\Kcard_changes" --- ���������� ���������� � ��������� ��� ���� ������ "�" */
#define CSP_INFO_NUMBER_KCARDS	(4)     /* "\\local\\number_Kcard_sessions" --- ���������� ���������� � ��������� ��� ���� ������ "�" */
#define CSP_INFO_FUTURE_SIZE	(10)
typedef struct
{
  WORD version;		/* ������ CSP */
  DWORD time;		/* time_t */
  DWORD keys_remaining;	/* ������� ���� */
  DWORD future[CSP_INFO_FUTURE_SIZE];
} CSP_INFO;

/* ����� ���������� ����� ��� ���� 28147, ������� � ������.*/

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_DEFAULT
 *  \brief �������� ��������� \ref CSP_FAST_CODE. ������������ 
 *  ��� ������� �������������� �� ���������.
 *  �� ���������� Intel Pentium 4 � ������ ��������� �������
 *  ��������� ����� ������������ ����� ������� �������� ����������.
 *  ������, � ������ ���� �� �� ������������ �������� Linux, 
 *  FreeBSD, Solaris ��������� ������� ��������� ����� 
 *  �������� ���������� ������� ����������, ��� ��� �������
 *  ������ ����� FPU � ������ ���� ���������� ������ � 
 *  �� Windows.
 */
#define CSP_FAST_CODE_DEFAULT	(1U<<31)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_NO
 *  \brief �������� ��������� \ref CSP_FAST_CODE. ������������ 
 *  ��� ���������� ���� ��� ���������� SSE2.
 */
#define CSP_FAST_CODE_NO	(1<<30)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_USER
 *  \brief �������� ��������� \ref CSP_FAST_CODE. ������������ 
 *  ��� ������� ����������������� ������� FPU.
 *  �������� ������ � ������ ���� ��. � ������ ��� ���������
 *  � ������ ���� �� ��� ������ ���� ��������� \ref CSP_FAST_CODE
 *  ������ ��������� ������ ������� ������� � ������������ 
 *  ������������ FPU ���������� Intel Pentium 4.
 *  �� ������ ����������� ��������� ������� ��������� �� 
 *  ������ �� ������ �������� ����������. 
 */
#define CSP_FAST_CODE_USER	(1<<29)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_GET_FN
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ������������ ��� ����������� ������� ������ ������������� ������� �������.
 */
#define CSP_FAST_CODE_GET_FN	(1<<28)


/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_GET_SETFN
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ������������ ��� �����������, ����� �� ��������� .
 *  ��������� ������� ��� �� ������ ������.
 */
#define CSP_FAST_CODE_GET_SETFN	(1<<27)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_E_ECB
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ������������ ��� ����, ��� ��������, ����� ��� 
 *  ����������� � ������� ������������ �� ECB
 *  ����� 1 � ������ �������� ���� ������ �������, 
 *  � 0 �����.
 */
#define CSP_FAST_CODE_E_ECB	(1)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_E_CBC
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ������������ ��� ����, ��� ��������, ����� ��� 
 *  ����������� � ������� ������������ �� CBC
 *  ����� 1 � ������ �������� ���� ������ �������, 
 *  � 0 �����.
 */
#define CSP_FAST_CODE_E_CBC	(1<<1)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_E_OFB
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ������������ ��� ����, ��� ��������, ����� ��� 
 *  ����������� � ������� ������������ �� OFB
 *  ����� 1 � ������ �������� ���� ������ �������, 
 *  � 0 �����.
 */
#define CSP_FAST_CODE_E_OFB	(1<<2)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_D_OFB
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ������������ ��� ����, ��� ��������, ����� ��� 
 *  ����������� � ������� ������������� �� OFB
 *  ����� 1 � ������ �������� ���� ������ �������, 
 *  � 0 �����.
 */
#define CSP_FAST_CODE_D_OFB	(1<<2)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_E_CFB
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ������������ ��� ����, ��� ��������, ����� ��� 
 *  ����������� � ������� ������������ �� CFB
 *  ����� 1 � ������ �������� ���� ������ �������, 
 *  � 0 �����.
 */
#define CSP_FAST_CODE_E_CFB	(1<<3)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_D_ECB
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ������������ ��� ����, ��� ��������, ����� ��� 
 *  ����������� � ������� ������������� �� ECB
 *  ����� 1 � ������ �������� ���� ������ �������, 
 *  � 0 �����.
 */
#define CSP_FAST_CODE_D_ECB	(1<<4)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_D_CBC
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ������������ ��� ����, ��� ��������, ����� ��� 
 *  ����������� � ������� ������������� �� CBC
 *  ����� 1 � ������ �������� ���� ������ �������, 
 *  � 0 �����.
 */
#define CSP_FAST_CODE_D_CBC	(1<<5)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_D_CFB
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ������������ ��� ����, ��� ��������, ����� ��� 
 *  ����������� � ������� ������������� �� CFB
 *  ����� 1 � ������ �������� ���� ������ �������, 
 *  � 0 �����.
 */
#define CSP_FAST_CODE_D_CFB	(1<<6)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_MD_ECB
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ������������ ��� ����, ��� ��������, ����� ��� 
 *  ����������� � ������� ������������ �����
 *  ����� 1 � ������ �������� ���� ������ �������, 
 *  � 0 �����.
 */
#define CSP_FAST_CODE_MD_ECB	(1<<7)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_GR3411SP
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ������������ ��� ����, ��� ��������, ����� ��� 
 *  ����������� � ���������� ������� �����������.
 *  ���� ��������������� ������ � ������ ���� ��.
 *  ����� 1 � ������ �������� ���� ������ �������, 
 *  � 0 �����.
 */
#define CSP_FAST_CODE_GR3411SP	(1<<8)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_GR3411H
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ������������ ��� ����, ��� ��������, ����� ��� 
 *  ����������� � ������� �����������.
 *  ���� ��������������� ������ � ������ ���� ��.
 *  ����� 1 � ������ �������� ���� ������ �������, 
 *  � 0 �����.
 */
#define CSP_FAST_CODE_GR3411H	(1<<9)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_GR3411HV
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ������������ ��� ����, ��� ��������, ����� ��� 
 *  ����������� � ������� �������� ����.
 *  ���� ��������������� ������ � ������ ���� ��.
 *  ����� 1 � ������ �������� ���� ������ �������, 
 *  � 0 �����.
 */
#define CSP_FAST_CODE_GR3411HV	(1<<10)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_HASH
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ������������ ��� ����, ��� ��������, ����� ��� 
 *  ����������� � ������� ���-��������������.
 *  ����� 1 � ������ �������� ���� ������ �������, 
 *  � 0 �����.
 */
#define CSP_FAST_CODE_HASH	(1<<11)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_IMIT
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ������������ ��� ����, ��� ��������, ����� ��� 
 *  ����������� � ������� ��������� ������������.
 *  ����� 1 � ������ �������� ���� ������ �������, 
 *  � 0 �����.
 */
#define CSP_FAST_CODE_IMIT	(1<<12)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_MULT
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ������������ ��� ����, ��� ��������, ����� ��� 
 *  ����������� � ������� ���������.
 *  ����� 1 � ������ �������� ���� ������ �������, 
 *  � 0 �����.
 */
#define CSP_FAST_CODE_MULT	(1<<13)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_MULT_ATT
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ������������ ��� ����, ��� ��������, ����� ��� ����������� 
 *  � �������� ��������� � UNIX-��������� ��������.
 *  ����� 1 � ������ �������� ���� ������ �������, 
 *  � 0 �����.
 */
#define CSP_FAST_CODE_MULT_ATT	(1<<14)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_ALL_ENCRYPT
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ���������� ��� ����� ������� ������������.
 */
#define CSP_FAST_CODE_ALL_ENCRYPT (CSP_FAST_CODE_E_ECB|CSP_FAST_CODE_E_CBC|CSP_FAST_CODE_E_OFB|CSP_FAST_CODE_E_CFB)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_ALL_DECRYPT
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ���������� ��� ����� ������� �������������.
 */
#define CSP_FAST_CODE_ALL_DECRYPT (CSP_FAST_CODE_D_ECB|CSP_FAST_CODE_D_CBC|CSP_FAST_CODE_D_OFB|CSP_FAST_CODE_D_CFB)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_ALL_HASH
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ���������� ��� ����� ������� �����������.
 */
#define CSP_FAST_CODE_ALL_HASH (CSP_FAST_CODE_HASH|CSP_FAST_CODE_GR3411SP|CSP_FAST_CODE_GR3411H|CSP_FAST_CODE_GR3411HV)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_ALL_MULT
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ���������� ��� ����� ������� ���������.
 */
#define CSP_FAST_CODE_ALL_MULT (CSP_FAST_CODE_MULT|CSP_FAST_CODE_MULT_ATT)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_ALL_CRYPT
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ���������� ��� ����� ������� ����������.
 */
#define CSP_FAST_CODE_ALL_CRYPT (CSP_FAST_CODE_ALL_ENCRYPT|CSP_FAST_CODE_ALL_DECRYPT|CSP_FAST_CODE_MD_ECB|CSP_FAST_CODE_IMIT)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_ALL_FUNCTIONS
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ���������� ��� ����� ������������� ������� ����������������.
 */
#define CSP_FAST_CODE_ALL_FUNCTIONS (CSP_FAST_CODE_ALL_CRYPT|CSP_FAST_CODE_ALL_HASH|CSP_FAST_CODE_ALL_MULT)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_ALL_KERNEL_FUNCTIONS
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ���������� ��� ����� ������������� ������� 
 *  ���������������� ������ ���� ��.
 */
#define CSP_FAST_CODE_ALL_KERNEL_FUNCTIONS (CSP_FAST_CODE_ALL_CRYPT|CSP_FAST_CODE_ALL_HASH)

/*! \ingroup ProCSPData 
 *  \def CSP_FAST_CODE_ALL_USER_FUNCTIONS
 *  \brief �������� ��������� \ref CSP_FAST_CODE. 
 *  ���������� ��� ����� ������������� ������� 
 *  ���������������� ����������������� ������.
 */
#define CSP_FAST_CODE_ALL_USER_FUNCTIONS (CSP_FAST_CODE_ALL_CRYPT|CSP_FAST_CODE_HASH|CSP_FAST_CODE_ALL_MULT)


/* ����, ������������ ��� ������ PP_FAST_CODE, ����������� ������� ����
   ��� ���� ������� ���������� � ������ ���� ��.*/
#define CRYPT_FAST_CODE_ALL_KERNEL_FUNCTIONS	1

/* ����, ������������ ��� ������ PP_FAST_CODE, ����������� ������� ����
   ��� ���� ������� ���������� � ������ ������������.*/
#define CRYPT_FAST_CODE_ALL_USER_FUNCTIONS	2

/* ����, ������������ ��� ������ PP_FAST_CODE, ����������� ������� ����
   ��� ���� ������� ����������.*/
#define CRYPT_FAST_CODE_ALL_FUNCTIONS		(CRYPT_FAST_CODE_ALL_KERNEL_FUNCTIONS|CRYPT_FAST_CODE_ALL_USER_FUNCTIONS)

/* ����, ������������ ��� ������ PP_FAST_CODE, ����������� 
   ��������� ����������� ����������.*/
#define CRYPT_FAST_CODE_GET_SETFN		8

/*!
 * \ingroup ProCSPData
 *
 * \brief ��������� ��������� ������� ������� � ������������ SSE2.
 *
 * \req_wincryptex
 * \sa CPSetProvParam 
 * \sa CPGetProvParam 
 */
typedef struct CSP_FAST_CODE_ {
    DWORD UsesFunctions;
		/*!< ������������ ��������, ����� ���� ����� \ref CSP_FAST_CODE_DEFAULT, 
		 *   \ref CSP_FAST_CODE_NO, \ref CSP_FAST_CODE_USER ��� ������ ������� 
		 *   \ref CPSetProvParam. 
		 *   � ������ ���� ������� ���������� ���������� �� ������������, 
		 *   � ��������� ����������� ����� ��������� �� ������� ������������. 
		 *   \ref CSP_FAST_CODE_USER ����������� ������ � ������ ���� ��!
		 *   ��� ������������� � ������� \ref CPGetProvParam, � ��������� ������������ 
		 *   �����, ������������ ����� ���������� �� ���������� ��� �������. 
		 *   ��������, ����� ������� ��������� �� ���������� ���, ����������
		 *   �� ������ \e dwFlags.
		 *   ���� � ������ ���� ���������������� ������� ������� ���� �����������,
		 *   �� �������� ����� �� ����� ����������� ������ ������ ��������!
		 *   � ��������� ������ ������� ���������� ����� ��-�������� �������� 
		 *   ���������� �� ������ ������� ��� ���������� ����������������� 
		 *   ��������. ��� ��������� ������ �������� ������� ������� 
		 *   \ref CPSetProvParam  � ���������� PP_FAST_CODE, ��������� 
		 *   � ��������� UsesFunctions=\ref CSP_FAST_CODE_DEFAULT.
		 *   ���� �������� ���� CRYPT_FAST_CODE_GET_SETFN, ��� ������ 
		 *   \ref CSP_FAST_CODE_GET_SETFN ����� ���������� � 1, ���� ��������� ����� ������������ 
		 *   ������� ���, � 0 - �����. ���� ���������� ���� CRYPT_FAST_CODE_ALL_FUNCTIONS ,
		 *   ����� ����������� ��� �������, � �� ������ ����� ����������� ��� ����� 
		 *   \ref CSP_FAST_CODE_E_ECB, \ref CSP_FAST_CODE_E_CBC, \ref CSP_FAST_CODE_E_OFB,
		 *   \ref CSP_FAST_CODE_E_CFB, \ref CSP_FAST_CODE_D_ECB, \ref CSP_FAST_CODE_D_CBC,
		 *   \ref CSP_FAST_CODE_D_OFB, \ref CSP_FAST_CODE_D_CFB, \ref CSP_FAST_CODE_MD_ECB,	
		 *   \ref CSP_FAST_CODE_GR3411SP, \ref CSP_FAST_CODE_GR3411H, \ref CSP_FAST_CODE_GR3411HV,
		 *   \ref CSP_FAST_CODE_HASH, \ref CSP_FAST_CODE_IMIT, \ref CSP_FAST_CODE_MULT,
		 *   � 1, ���� ��������������� ������� ���������� ������� ���, � 0 - �����.
		 *   � ������ ������������ ������� ������ �����  CRYPT_FAST_CODE_ALL_FUNCTIONS 
		 *   ������������ CRYPT_FAST_CODE_ALL_USER_FUNCTIONS, � � ������ ���� �� -
		 *   CRYPT_FAST_CODE_ALL_KERNEL_FUNCTIONS. �� ������ ���� \ref CSP_FAST_CODE_ALL_FUNCTIONS
		 *   ����� 1, ���� ������� ��� �������� �� ���� ��������� ��������, � 0 ���� ���� �� ���� 
		 *   �� ��������� ������� �� ���������.
		 *   ��������� ����������� ������ ������������.
		 */
    /* ��� ���� ����������� (������������ ������ � SetProvParam),
     * ������� ������ ���� ���������� - �� �� �� ���������� � 
     * GetProvParam.
     */
    int (*kernel_fpu_begin)(char * buf, size_t sz, unsigned int bl_len); 
		/*!< ��������� �� ������� ������� SSE2. 
		 *   ������������ ������ � ������ ���� ��!
		 *   ������� ������ ���������� 1, ���� ������ ������,
		 *   0, ���� ������ �� ������. �� ���� ������� �����
 		 *   ���������� ��������� �� �����, ����������� ���
                 *   ���������� �������� ���������, ����������� ������, 
                 *   � ������ ����������. ������ ������ ���������� 
 		 *   �� ������ ���������. ���������� �� �� ���������
                 *   512 ����. ������ �������� - �������� ��������,
                 *   ������ ����� ����, ������������ ��� �������� 
                 *   ����������. ������ �������� ����� ��� ����������,
                 *   ������� �� ����������� SSE2.
		 */
    int (*kernel_fpu_end)(char *, size_t);
		/*!< ��������� �� ������� ������������ SSE2. 
		 *   ������������ ������ � ������ ���� ��!
		 *   ������ ��� ��������� ��� � kernel_fpu_begin.
		 *   ������� ���������� 1, ���� ������� ���������� SSE2,
		 *   � 0 � ��������� ������.  ���� ������� kernel_fpu_begin 
                 *   ������� 0, �� kernel_fpu_end ���������� �� �����! 
		 */
} CSP_FAST_CODE;


typedef struct CRYPT_LCD_QUERY_PARAM_ {
  const char *message;
} CRYPT_LCD_QUERY_PARAM;

/*! \defgroup ProCSPEx �������������� ��������� � �����������
 *\ingroup ProCSP
 * ������ ������ �������� ����������� ��������������� � ����������, 
 * ������������ � ���������������� "��������� CSP".
 *
 * \{
 */

/*! \page DP1 �������������� ���������� ����������������
 * 
 * <table>
 * <tr><th>�������������</th><th>�������� ��������������</th></tr>
 * <tr><td>CALG_GR3411</td><td>������������� ��������� ����������� �� ���� � 34.11-94.</td></tr>
 * <tr><td>CALG_G28147_MAC</td><td>������������� ��������� ����������� �� ���� 28147-89.</td></tr>
 * <tr><td>CALG_G28147_IMIT </td><td>�� �� �����, ��� � CALG_G28147_MAC (���������� ������).</td></tr>
 * <tr><td> CALG_GR3410 </td><td> ������������� ��������� ��� �� ���� � 34.10-94. </td></tr>
 * <tr><td> CALG_GR3410EL </td><td> ������������� ��������� ��� �� ���� � 34.10-2001.</td></tr>
 * <tr><td>CALG_G28147</td><td>������������� ��������� ���������� �� ���� 28147-89. </td></tr>
 * <tr><td>CALG_DH_EX_SF </td><td>������������� ��������� ������ ������ �� �����-�������� �� ���� ��������� ����� ������������. </td></tr>
 * <tr><td>CALG_DH_EX_EPHEM </td><td>������������� CALG_DH_EX ��������� ������ ������ �� �����-�������� �� ���� ��������� ����� ��������� ����. �������� ���� ���������� �� ���� � 34.10 94.</td></tr>
 * <tr><td>CALG_DH_EX </td><td>������������� CALG_DH_EX ��������� ������ ������ �� �����-�������� �� ���� ��������� ����� ������������. �������� ���� ���������� �� ���� � 34.10 94. </td></tr>
 * <tr><td>CALG_DH_EL_SF </td><td>������������� ��������� ������ ������ �� �����-�������� �� ���� ��������� ����� ������������. �������� ���� ���������� �� ���� � 34.10 2001.</td></tr>
 * <tr><td> CALG_DH_EL_EPHEM</td><td> ������������� ��������� ������ ������ �� �����-�������� �� ���� ��������� ����� ��������� ����. �������� ���� ���������� �� ���� � 34.10 2001.</td></tr>
 * <tr><td>CALG_PRO_AGREEDKEY_DH</td><td>������������� ��������� ��������� ����� ������ ����� �� �����-��������. </td></tr>
 * <tr><td>CALG_PRO_EXPORT </td><td> ������������� ��������� ����������� �������� �����.</td></tr>
 * <tr><td>CALG_SIMPLE_EXPORT </td><td>������������� ��������� �������� �������� �����. </td></tr>
 * <tr><td>CALG_SIMMETRYKEY </td><td> ������������� ��������� ���������� �� ���� 28147-89.</td></tr>
 * <tr><td> CALG_TLS1_MASTER_HASH</td><td>������������� ��������� ��������� ������� MASTER_HASH ��������� TLS 1.0.</td></tr>
 * <tr><td> CALG_TLS1_MAC_KEY</td><td>������������� ��������� ��������� ����� ����������� ��������� TLS 1.0. </td></tr>
 * <tr><td>CALG_TLS1_ENC_KEY </td><td> ������������� ��������� ��������� ����� ���������� ��������� TLS 1.0.</td></tr>
 * <tr><td> CALG_PRO_DIVERS</td><td>������������� ��������� ��������� �������������� �����.</td></tr>
 * <tr><td> CALG_RIC_DIVERS</td><td>������������� ��������� ��� �������������� �����. </td></tr>
 *</table>
 */

/*! \page DP2 ������ ����������
 * <table>
 * <tr><th>��������</th><th>�������� ���������</th></tr>
 * <tr><td>CRYPT_PROMIX_MODE </td><td>������� ������� ����������/������������� �� ���� 28147-89 � ��������������� ����� ����� ������ 1 �� �������������� ���������� </td></tr>
 * <tr><td>CRYPT_SIMPLEMIX_MODE </td><td>������� ������� ����������/������������� �� ���� 28147-89 ��� �������������� ����� � �������� ��������� ����������</td></tr>
 *</table>
*/

/*! \page DP3 ��������� ����������������
 * <table>
 * <tr><th>��������</th><th>�������� ���������</th></tr>
 * <tr><td>PP_ENUMOIDS_EX</td><td>�������� �������� ��������������� ��������, ������������ � ����������������</td></tr>
 * <tr><td>PP_HASHOID</td><td>�������� �/��� ������������� �������� � ���������� OID ���� ������ ������� ����������� ���� � 34.11-94 ��� ������������ ������������������ ���������</td></tr>
 * <tr><td>PP_CIPHEROID</td><td>�������� �/��� ������������� �������� � ���������� OID ���� ������ ��������� ���������� ���� 28147-89 ��� ������������ ������������������ ��������� </td></tr>
 * <tr><td>PP_SIGNATUREOID</td><td>�������� �/��� ������������� �������� � ���������� OID ���������� �������� ������� ��� ������������ ������������������ ��������� </td></tr>
 * <tr><td>PP_DHOID </td><td>�������� �/��� ������������� �������� � ���������� OID ���������� ��������� �����-�������� ��� ������������ ������������������ ���������  </td></tr>
 * <tr><td>PP_CHECKPUBLIC </td><td>���� �������� ��������� �����. ���� ���� ����������, �������������� �������� �������������� ������� ��������� ����� </td></tr>
 * <tr><td>PP_RANDOM</td><td>�������� �/��� ������������� ���� ���� SIMPLEBLOB ��� ������������� ��� � �������� ����������</td></tr>
 * <tr><td>PP_DRVCONTAINER </td><td>�������� ��������� (handle) ���������� � ��������</td></tr>
 * <tr><td>PP_MUTEX_ARG</td><td>�������������� ������������� ������� ���������������� � ���������� ����������</td></tr>
 * <tr><td>PP_ENUM_HASHOID</td><td>�������� �������� ��������������� ����������������� ��������, ��������� � �������� ����������� </td></tr>
 * <tr><td>PP_ENUM_CIPHEROID</td><td>�������� �������� ��������������� ����������������� ��������, ��������� � �������� ����������  </td></tr>
 * <tr><td>PP_ENUM_SIGNATUREOID</td><td>�������� �������� ��������������� ����������������� ��������, ��������� � �������� �������� �������</td></tr>
 * <tr><td>PP_ENUM_DHOID</td><td>�������� �������� ��������������� ����������������� ��������, ��������� � ���������� �����-��������  </td></tr>
 *</table>
*/

/*! \page DP4 ��������� �������������� �������� ������   
 * <table>
 * <tr><th>��������</th><th>�������� ���������</th></tr>
 * <tr><td>DIVERSKEYBLOB</td><td>��� ��������� ����� ��� �������������� ������ � ������� 
    ������� CPImportKey � ������ CALG_PRO_EXPORT</td></tr>
 *</table>
*/

/*! \page DP5 �������������� ��������� ������� ����������� 
 * <table>
 * <tr><th>��������</th><th>�������� ���������</th></tr>
 * <tr><td>HP_HASHSTARTVECT</td><td>��������� ������ ������� �����������, ��������������� �����������</td></tr>
 * <tr><td>HP_OID</td><td>������ ���� ������ ������� �����������</td></tr>
 *</table>
*/

/*! \page DP6 �������������� ��������� ������
 * <table>
 * <tr><th>��������</th><th>�������� ���������</th></tr>
 * <tr><td>KP_IV </td><td>��������� ������ ������������� ��������� ���������� ���� 28147-89</td></tr>
 * <tr><td>KP_MIXMODE</td><td>���������� ������������� �������������� ����� ����� ��������� 1�� ���������� � ������� ����������/������������� � ���������� ������������ ��������� ���� 28147-89 </td></tr>
 * <tr><td>KP_OID</td><td>������ ���� ������ ������� �����������</td></tr>
 * <tr><td>KP_HASHOID</td><td>������������� ���� ������ ������� ����������� ���� � 34.11-94</td></tr>
 * <tr><td>KP_CIPHEROID</td><td>������������� ���� ������ ��������� ���������� ���� 28147-89</td></tr>
 * <tr><td>KP_SIGNATUREOID</td><td>������������� ���������� �������� �������</td></tr>
 * <tr><td>KP_DHOID</td><td>������������� ���������� ��������� �����-��������</td></tr>
 *</table>
*/

/*! \ingroup ProCSPEx �������������� ���� ������ ����������������
 * <table>
 * <tr><th>��������</th><th>�������� ���������</th></tr>
 * <tr><td>GPE_FAIL_TESTBUFFER</td><td>������������������ ��� �� ������ �������������� �������� �� ��������� 1 ��</td></tr>
 * <tr><td>GPE_FAIL_STATBUFFER</td><td>������������������ ��� �� ������ �������������� �������� �� ��������� 18 ��</td></tr>
 * <tr><td>GPE_DIFERENT_PARAMETERS</td><td>������������ ��������� </td></tr>
 * <tr><td>GPE_CORRUPT_KEYCONTEXT </td><td>�������� ����������� ������ ��������� ���� 28147-89 </td></tr>
 * <tr><td>GPE_CHECKPROC_GAMMING_CNT </td><td>������ � ������ ������������ ��������� ���� 28147-89 </td></tr>
 * <tr><td>GPE_CHECKPROC_ENCRYPT_CFB </td><td>������ � ������ ������������ � �������� ��������������� ���� 28147-89</td></tr>
 * <tr><td>GPE_CHECKCARRIER </td><td>��� �������� ��������� ���������� � ����������� ����������� ��� �������� �������� ��������</td></tr>
 * <tr><td>GPE_CORRUPT_KEYPAIR_INFO </td><td>�������� �������� ���� �������� ������� </td></tr>
 * <tr><td>GPE_CHECKPROC_TESTFAIL </td><td>������ ��� ������������ ������� ���������������� </td></tr>
 * <tr><td>GPE_RANDOMFAIL</td><td>������ � ���������������� ��� </td></tr>
 * <tr><td>GPE_SECURITY_LEVEL</td><td>��������� ����� ������ ������� ������������</td></tr>
 *</table>
 *
 *
 * ���� ������ ������������ 4 ������� � ��������� pbData ������� CryptGetProvParam() ��� �������� ��������� hProv=PP_LAST_ERROR.
*/

/*! \page DP8 ��������� �������������� ����������������� ���������� ����������
 * <table>
 * <tr><th>��������</th><th>������</th><th>�������� ���������</th></tr>
 * <tr><td>szOID_CP_GOST_28147</td><td>"1.2.643.2.2.21"</td><td>�������� ���������� ���� 28147-89</td></tr>
 * <tr><td>szOID_CP_GOST_R3411</td><td>"1.2.643.2.2.9"</td><td>������� ����������� ���� � 34.11-94</td></tr>
 * <tr><td>szOID_CP_GOST_R3410</td><td>"1.2.643.2.2.20"</td><td>�������� ���� � 34.10-94, ������������ ��� ��������/������� ������</td></tr>
 * <tr><td>szOID_CP_GOST_R3410EL</td><td>"1.2.643.2.2.19"</td><td>�������� ���� � 34.10-2001, ������������ ��� ��������/������� ������</td></tr>
 * <tr><td>szOID_CP_DH_EX</td><td>"1.2.643.2.2.99"</td><td>�������� �����-�������� �� ���� ������������� �������</td></tr>
 * <tr><td>szOID_CP_DH_EL</td><td>"1.2.643.2.2.98"</td><td>�������� �����-�������� �� ���� ������������� ������</td></tr>
 * <tr><td>szOID_CP_GOST_R3411_R3410</td><td>"1.2.643.2.2.4"</td><td>�������� �������� ������� ���� � 34.10-94</td></tr>
 * <tr><td>szOID_CP_GOST_R3411_R3410EL</td><td>"1.2.643.2.2.3"</td><td>�������� �������� ������� ���� � 34.10-2001</td></tr>
 * <tr><td>szOID_KP_TLS_PROXY</td><td>"1.2.643.2.2.34.1"</td><td>����� TLS-�������</td></tr>
 * <tr><td>szOID_KP_RA_CLIENT_AUTH</td><td>"1.2.643.2.2.34.2"</td><td>������������� ������������ �� ������ �����������</td></tr>
 * <tr><td>szOID_KP_WEB_CONTENT_SIGNING</td><td>"1.2.643.2.2.34.3"</td><td>������� ����������� ������� ��������</td></tr>
 *</table>
*/

/*! \page DP9 �������������� ����������������� ���������� ����������
 * <table>
 * <tr><th>��������</th><th>������</th><th>�������� ���������</th></tr>
 * <tr><td>OID_HashTest</td><td>"1.2.643.2.2.30.0"</td><td>�������� ���� ������</td></tr>
 * <tr><td>OID_HashVerbaO</td><td>"1.2.643.2.2.30.1"</td><td>���� ������ ������� �����������, ������� "�����-�"</td></tr>
 * <tr><td>OID_HashVerba_1</td><td>"1.2.643.2.2.30.2"</td><td>���� ������ ������� �����������, ������� 1</td></tr>
 * <tr><td>OID_HashVerba_2</td><td>"1.2.643.2.2.30.3"</td><td>���� ������ ������� �����������, ������� 2</td></tr>
 * <tr><td>OID_HashVerba_3</td><td>"1.2.643.2.2.30.4"</td><td>���� ������ ������� �����������, ������� 3</td></tr>
 * <tr><td>OID_HashVar_Default</td><td>"1.2.643.2.2.30.1"</td><td>���� ������ ������� �����������, ���������� �������. � �������� ����������� ������������ ���� ������ ��������  "�����-�"</td></tr>
 * <tr><td>OID_CryptTest</td><td>"1.2.643.2.2.31.0"</td><td>�������� ���� ������ ��������� ����������</td></tr>
 * <tr><td>OID_CipherVerbaO</td><td>"1.2.643.2.2.31.1"</td><td>���� ������ ��������� ����������,������� "�����-�"</td></tr>
 * <tr><td>OID_CipherVerba_1</td><td>"1.2.643.2.2.31.2"</td><td>���� ������ ��������� ����������,������� 1</td></tr>
 * <tr><td>OID_CipherVerba_2</td><td>"1.2.643.2.2.31.3"</td><td>���� ������ ��������� ����������,������� 2</td></tr>
 * <tr><td>OID_CipherVerba_3</td><td>"1.2.643.2.2.31.4"</td><td>���� ������ ��������� ����������,������� 3</td></tr>
 * <tr><td>OID_CipherVar_Default</td><td>"1.2.643.2.2.31.0"</td><td>���� ������ ������� ��������� ����������, ���������� �������. � �������� ����������� ������������ ���� ������ ��������  "�����-�</td></tr>
 * <tr><td>OID_CipherOSCAR</td><td>"1.2.643.2.2.31.5" </td><td>���� ������, ������� ����� ���������</tr>
 * <tr><td>OID_CipherTestHash</td><td>"1.2.643.2.2.31.6" </td><td>���� ������, ������������ ��� ���������� � ������������</td></tr>
 * <tr><td>OID_SignDH128VerbaO</td><td>"1.2.643.2.2.32.2"</td><td>��������� P,Q,A �������� ������� ���� � 34.10-94, ������� "�����-�". ����� �������������� ����� � ��������� �����-��������</td></tr>
 * <tr><td>OID_SignDH128Verba_1</td><td>"1.2.643.2.2.32.3"</td><td>��������� P,Q,A �������� ������� ���� � 34.10-94, ������� 1. ����� �������������� ����� � ��������� �����-��������</td></tr>
 * <tr><td>OID_SignDH128Verba_2</td><td>"1.2.643.2.2.32.4"</td><td>��������� P,Q,A �������� ������� ���� � 34.10-94, ������� 2. ����� �������������� ����� � ��������� �����-��������</td></tr>
 * <tr><td>OID_SignDH128Verba_3</td><td>"1.2.643.2.2.32.5"</td><td>��������� P,Q,A �������� ������� ���� � 34.10-94, ������� 3. ����� �������������� ����� � ��������� �����-��������</td></tr>
 * <tr><td>OID_DH128Var_1 </td><td>"1.2.643.2.2.33.1" </td><td>��������� P,Q,A ��������� �����-�������� �� ���� ���������������� �������, ������� 1</td></tr>
 * <tr><td>OID_DH128Var_2 </td><td>"1.2.643.2.2.33.2" </td><td>��������� P,Q,A ��������� �����-�������� �� ���� ���������������� �������, ������� 2</td></tr>
 * <tr><td>OID_DH128Var_3 </td><td>"1.2.643.2.2.33.3" </td><td>��������� P,Q,A ��������� �����-�������� �� ���� ���������������� �������, ������� 3</td></tr>
 * <tr><td>OID_ECCTest3410</td><td>"1.2.643.2.2.35.0"</td><td>�������� ��������� a, b, p,q, (x,y) ��������� ���� � 34.10-2001 </td></tr>
 * <tr><td>OID_ECCSignDHPRO </td><td>"1.2.643.2.2.35.1"</td><td>��������� a, b, p,q, (x,y) �������� ������� � ��������� �����-�������� �� ���� ��������� ���� � 34.10-2001, ������� ���������������� </td></tr>
 * <tr><td>OID_ECCSignDHOSCAR</td><td>"1.2.643.2.2.35.2"</td><td>��������� a, b, p,q, (x,y) �������� ������� � ��������� �����-�������� �� ���� ��������� ���� � 34.10-2001, ������� ����� ���������</td></tr>
 * <tr><td>OID_ECCDHPRO </td><td>"1.2.643.2.2.36.0"</td><td> ��������� a, b, p,q, (x,y) ��������� �����-�������� �� ���� ��������� ���� � 34.10-2001, ������� ����������������. ������������ �� �� ���������, ��� � � ��������������� OID_ECCSignDHPRO</td></tr>
 * <tr><td>OID_ECCSignDHVar1</td><td>"1.2.643.2.2.35.3"</td><td>��������� a, b, p,q, (x,y) �������� ������� � ��������� �����-�������� �� ���� ��������� ���� � 34.10-2001.</td></tr>
 *</table>
 * 
*/

/*! \} */

typedef struct CONTAINER_EXTENSION_ {
    BOOL bCritical;
    DWORD cbExtension;
    BYTE pbExtension[1];
    char sOid[1]; /* No alignment */
} CONTAINER_EXTENSION;

#endif /* _WINCRYPTEX_H_INCLUDED */
