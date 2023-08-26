/*
* $Id: ccevp.h,v 1.4 2012/10/06 12:38:11 tvm Exp $
*/
#ifndef _HEADER_CCEVP_H
#define _HEADER_CCEVP_H

#ifdef	__cplusplus
extern "C" {
#endif
	
#ifdef _WIN32
#ifndef _KERNEL
#include <windows.h>
#define WINAPI_CALLBACK	WINAPI
#else /* _KERNEL */
#define NO_WINAPI
#endif /* _KERNEL */
#else /* _WIN32 */
#define NO_WINAPI
#endif /* _WIN32 */

#if !defined(_WIN32) || defined(NO_WINAPI)
#undef WINAPI
#define WINAPI
#endif

#if defined(NO_WINAPI) || defined(NO_WINAPI_CALLBACK)
#undef WINAPI_CALLBACK
#define WINAPI_CALLBACK
#endif

#define GOSTE_MODE_ECB			0
#define GOSTE_MODE_GAMMA		1
#define GOSTE_MODE_GFB			2
#define GOSTE_MODE_MAC			3
#define GOSTE_MODE_CBC			4
#define GOSTE_MODE_CNT			GOSTE_MODE_GAMMA
#define GOSTE_MODE_CFB			GOSTE_MODE_GFB

#define MESH_MODE_OFF			0
#define MESH_MODE_KEY			0x100
#define MESH_MODE_IV			0x200
#define MESH_MODE_ON			(MESH_MODE_KEY|MESH_MODE_IV)
	
/*
 *	Идентификаторы параметров ГОСТ Р 34.10-94
 */
#define GOSTS_PARAMS_SC			1
#define GOSTS_PARAMS_CP_A		3
#define GOSTS_PARAMS_CP_B		4
#define GOSTS_PARAMS_CP_C		5
#define GOSTS_PARAMS_CP_D		6
#define GOSTS_PARAMS_CP_XA		7
#define GOSTS_PARAMS_CP_XB		8
#define GOSTS_PARAMS_CP_XC		9

/*
 *	Идентификаторы параметров ГОСТ Р 34.10-2001
 */
#define ECGOST_PARAMS_SECP256R1	11
#define ECGOST_PARAMS_SC		ECGOST_PARAMS_SECP256R1
#define ECGOST_PARAMS_CP_A		12
#define ECGOST_PARAMS_CP_B		13
#define ECGOST_PARAMS_CP_C		14
#define ECGOST_PARAMS_CP_XA		15
#define ECGOST_PARAMS_CP_XB		16

/*
 *	Идентификаторы узлов замены для ГОСТ Р 34.11-94
 */
#define GOSTH_SBOX_SC			21
#define GOSTH_SBOX_CP			22

/*
 *	Идентификаторы узлов замены для ГОСТ 28147-89
 */
#define GOSTE_SBOX_CP_A			32
#define GOSTE_SBOX_CP_B			33
#define GOSTE_SBOX_CP_C			34
#define GOSTE_SBOX_CP_D			35
#define GOSTE_SBOX_TC26_A		36
#define GOSTE_SBOX_TC26_B		37
#define GOSTE_SBOX_TC26_C		38
#define GOSTE_SBOX_TC26_D		39
#define GOSTE_SBOX_TC26_E		40
#define GOSTE_SBOX_TC26_F		41

#define CCOM_UNDEFINED				(-1)

#ifndef HEADER_CCEVP_LOCAL_H
#define CCOM_SECRET_KEY_CTX			void
#define CCOM_KEY_PAIR_CTX			void
#define CCOM_PRIVATE_KEY_CTX		void
#define CCOM_PUBLIC_KEY_CTX			void
#define CCOM_PSE_CTX				void
#define CCOM_CIPHER_CTX				void
#define CCOM_DIGEST_CTX				void
#define CCOM_HMAC_CTX				void
#define CCOM_SIGN_CTX				void
#define CCOM_KEY_AGREE_CTX			void
#define CCOM_KEY_DERIVE_CTX			void
#define CCOM_KEY_WRAP_CTX			void
#endif

#define CCOM_ALG_TYPE_CIPHER		0x00010000
#define CCOM_ALG_TYPE_DIGEST		0x00020000
#define CCOM_ALG_TYPE_SIGN			0x00040000
#define CCOM_ALG_TYPE_KEY_AGREE		0x00080000
#define CCOM_ALG_TYPE_KEY_DERIVE	0x00100000
#define CCOM_ALG_TYPE_KEY_WRAP		0x00200000
	
CCOM_SECRET_KEY_CTX * WINAPI CCOM_SecretKeyGenerate(int alg);
CCOM_SECRET_KEY_CTX * WINAPI CCOM_SecretKeyRandomBytes(int len);
int WINAPI CCOM_SecretKeyGetLength(CCOM_SECRET_KEY_CTX *ctx);
int WINAPI CCOM_SecretKeyFree(CCOM_SECRET_KEY_CTX *ctx);

#define CCOM_CIPHER_GOST28147_89				(CCOM_ALG_TYPE_CIPHER | 1)

#define CCOM_CIPHER_DECRYPT						0
#define CCOM_CIPHER_ENCRYPT						1

#define GOSTE_MODE_ECB							0
#define GOSTE_MODE_GAMMA						1
#define GOSTE_MODE_GFB							2
#define GOSTE_MODE_MAC							3
#define GOSTE_MODE_CBC							4
#define GOSTE_MODE_CNT							GOSTE_MODE_GAMMA
#define GOSTE_MODE_CFB							GOSTE_MODE_GFB

#define CCOM_CIPHER_MODE_ECB					GOSTE_MODE_ECB
#define CCOM_CIPHER_MODE_CNT					GOSTE_MODE_CNT
#define CCOM_CIPHER_MODE_CTR					CCOM_CIPHER_MODE_CNT
#define CCOM_CIPHER_MODE_CFB					GOSTE_MODE_CFB
#define CCOM_CIPHER_MODE_CBC					GOSTE_MODE_CBC
#define CCOM_CIPHER_MODE_MAC					GOSTE_MODE_MAC

#define CCOM_CIPHER_NO_PADDING					0
#define CCOM_CIPHER_ZERO_PADDING				1
#define CCOM_CIPHER_PKCS5_PADDING				2

#define GOSTE_SBOX_CP_A							32
#define GOSTE_SBOX_CP_B							33
#define GOSTE_SBOX_CP_C							34
#define GOSTE_SBOX_CP_D							35
#define GOSTE_SBOX_TC26_A						36
#define GOSTE_SBOX_TC26_B						37
#define GOSTE_SBOX_TC26_C						38
#define GOSTE_SBOX_TC26_D						39
#define GOSTE_SBOX_TC26_E						40
#define GOSTE_SBOX_TC26_F						41

#define CCOM_GOST28147_89_SBOX_A				GOSTE_SBOX_CP_A
#define CCOM_GOST28147_89_SBOX_B				GOSTE_SBOX_CP_B
#define CCOM_GOST28147_89_SBOX_C				GOSTE_SBOX_CP_C
#define CCOM_GOST28147_89_SBOX_D				GOSTE_SBOX_CP_D
#define CCOM_GOST28147_89_SBOX_SC				GOSTE_SBOX_SC
#define CCOM_GOST28147_89_SBOX_TEST				GOSTE_SBOX_TEST
#define CCOM_GOST28147_89_SBOX_TC26_A			GOSTE_SBOX_TC26_A
#define CCOM_GOST28147_89_SBOX_TC26_B			GOSTE_SBOX_TC26_B
#define CCOM_GOST28147_89_SBOX_TC26_C			GOSTE_SBOX_TC26_C
#define CCOM_GOST28147_89_SBOX_TC26_D			GOSTE_SBOX_TC26_D
#define CCOM_GOST28147_89_SBOX_TC26_E			GOSTE_SBOX_TC26_E
#define CCOM_GOST28147_89_SBOX_TC26_F			GOSTE_SBOX_TC26_F

#define CCOM_GOST28147_89_KEY_LENGTH			32
#define CCOM_GOST28147_89_IV_LENGTH				8
#define CCOM_GOST28147_89_MAC_LENGTH			4

#define CCOM_CIPHER_SET_GOST28147_89_SBOX		0
#define CCOM_CIPHER_GET_GOST28147_89_SBOX		1
#define CCOM_CIPHER_SET_GOST28147_89_MESH_MODE	2
#define CCOM_CIPHER_GET_GOST28147_89_MESH_MODE	3

#define CCOM_CIPHER_GOST28147_89_MESH_MODE_1K	MESH_MODE_ON
#define CCOM_CIPHER_GOST28147_89_MESH_MODE_4M	MESH_MODE_OFF
#define CCOM_CIPHER_GOST28147_89_DATA_LIMIT		(1024 * 1024 * 4)

CCOM_CIPHER_CTX * WINAPI CCOM_CipherNew(int alg, int mode);
long WINAPI CCOM_CipherCtrl(CCOM_CIPHER_CTX *ctx, int cmd, long num, void *arg);
int WINAPI CCOM_CipherInit(CCOM_CIPHER_CTX *ctx, CCOM_SECRET_KEY_CTX *key, char *iv, int opmode);

int WINAPI CCOM_CipherInitEncrypt(CCOM_CIPHER_CTX *ctx, CCOM_SECRET_KEY_CTX *key, char *iv);
int WINAPI CCOM_CipherInitDecrypt(CCOM_CIPHER_CTX *ctx, CCOM_SECRET_KEY_CTX *key, char *iv);
int WINAPI CCOM_CipherUpdate(CCOM_CIPHER_CTX *ctx, char *out, int *outl, char *in, int inl);
int WINAPI CCOM_CipherFinal(CCOM_CIPHER_CTX *ctx, char *out, int *outl);

int WINAPI CCOM_CipherInitMAC(CCOM_CIPHER_CTX *ctx, CCOM_SECRET_KEY_CTX *key, char *iv);
int WINAPI CCOM_CipherUpdateMAC(CCOM_CIPHER_CTX *ctx, char *in, int inl);
int WINAPI CCOM_CipherFinalMAC(CCOM_CIPHER_CTX *ctx, char *out, int *outl);

int WINAPI CCOM_CipherGetKeyLength(CCOM_CIPHER_CTX *ctx);
int WINAPI CCOM_CipherGetBlockLength(CCOM_CIPHER_CTX *ctx);
int WINAPI CCOM_CipherGetIVLength(CCOM_CIPHER_CTX *ctx);
int WINAPI CCOM_CipherGetMACLength(CCOM_CIPHER_CTX *ctx);

CCOM_CIPHER_CTX * WINAPI CCOM_CipherCloneMAC(CCOM_CIPHER_CTX *ctx);
int WINAPI CCOM_CipherFree(CCOM_CIPHER_CTX *ctx);

#define CCOM_DIGEST_GOSTR3411_94_CP			(CCOM_ALG_TYPE_DIGEST | 1)
#define CCOM_DIGEST_GOSTR3411_94_SC			(CCOM_ALG_TYPE_DIGEST | 2)
#define CCOM_DIGEST_GOSTR3411_94_TEST		(CCOM_ALG_TYPE_DIGEST | 3)
#define CCOM_DIGEST_GOSTR3411_94			CCOM_DIGEST_GOSTR3411_94_CP
#define CCOM_DIGEST_STRIBOG_256				(CCOM_ALG_TYPE_DIGEST | 4)
#define CCOM_DIGEST_STRIBOG_512				(CCOM_ALG_TYPE_DIGEST | 5)

#define CCOM_GOSTR3411_94_SBOX_CP			GOSTH_SBOX_CP
#define CCOM_GOSTR3411_94_SBOX_SC			GOSTH_SBOX_SC
#define CCOM_GOSTR3411_94_SBOX_TEST			GOSTH_SBOX_TEST

#define CCOM_DIGEST_SET_GOSTR3411_94_SBOX	0
#define CCOM_DIGEST_GET_GOSTR3411_94_SBOX	1
#define CCOM_DIGEST_SET_INVERT_DIGEST		2

#define CCOM_DIGEST_MAX_LENGTH				64

CCOM_DIGEST_CTX * WINAPI CCOM_DigestNew(int alg);
long WINAPI CCOM_DigestCtrl(CCOM_DIGEST_CTX *ctx, int cmd, long num, void *arg);
int WINAPI CCOM_DigestInit(CCOM_DIGEST_CTX *ctx);
int WINAPI CCOM_DigestUpdate(CCOM_DIGEST_CTX *ctx, char *in, int inl);
int WINAPI CCOM_DigestFinal(CCOM_DIGEST_CTX *ctx, char *out, int *outl);
int WINAPI CCOM_DigestReset(CCOM_DIGEST_CTX *ctx);
int WINAPI CCOM_DigestFree(CCOM_DIGEST_CTX *ctx);
int WINAPI CCOM_DigestGetBlockLength(CCOM_DIGEST_CTX *ctx);
int WINAPI CCOM_DigestGetDigestLength(CCOM_DIGEST_CTX *ctx);
CCOM_DIGEST_CTX * WINAPI CCOM_DigestClone(CCOM_DIGEST_CTX *ctx);

CCOM_HMAC_CTX * WINAPI CCOM_HMACNew(int alg);
int WINAPI CCOM_HMACInit(CCOM_HMAC_CTX *ctx, CCOM_SECRET_KEY_CTX *key);
int WINAPI CCOM_HMACUpdate(CCOM_HMAC_CTX *ctx, char *in, int inl);
int WINAPI CCOM_HMACFinal(CCOM_HMAC_CTX *ctx, char *out, int *outl);
int WINAPI CCOM_HMACReset(CCOM_HMAC_CTX *ctx);
int WINAPI CCOM_HMACFree(CCOM_HMAC_CTX *ctx);
int WINAPI CCOM_HMACGetBlockLength(CCOM_HMAC_CTX *ctx);
int WINAPI CCOM_HMACGetHMACLength(CCOM_HMAC_CTX *ctx);
CCOM_HMAC_CTX * WINAPI CCOM_HMACClone(CCOM_HMAC_CTX *ctx);

CCOM_PSE_CTX * WINAPI CCOM_PSENew(void);
int WINAPI CCOM_PSEFree(CCOM_PSE_CTX *ctx);
int WINAPI CCOM_PSESetPath(CCOM_PSE_CTX *ctx, char *path);
int WINAPI CCOM_PSESetMkeyPath(CCOM_PSE_CTX *ctx, char *path);
int WINAPI CCOM_PSESetMasksPath(CCOM_PSE_CTX *ctx, char *path);
int WINAPI CCOM_PSESetKEKPath(CCOM_PSE_CTX *ctx, char *path);
int WINAPI CCOM_PSESetRandPath(CCOM_PSE_CTX *ctx, char *path);
int WINAPI CCOM_PSESetMkey(CCOM_PSE_CTX *ctx, char *buf, int len);
int WINAPI CCOM_PSESetMasks(CCOM_PSE_CTX *ctx, char *buf, int len);
int WINAPI CCOM_PSESetKEK(CCOM_PSE_CTX *ctx, char *buf, int len);
int WINAPI CCOM_PSESetRand(CCOM_PSE_CTX *ctx, char *buf, int len);
int WINAPI CCOM_PSEGetMkey(CCOM_PSE_CTX *ctx, char *buf, int *len);
int WINAPI CCOM_PSEGetMasks(CCOM_PSE_CTX *ctx, char *buf, int *len);
int WINAPI CCOM_PSEGetKEK(CCOM_PSE_CTX *ctx, char *buf, int *len);
int WINAPI CCOM_PSEGetRand(CCOM_PSE_CTX *ctx, char *buf, int *len);
int WINAPI CCOM_PSESetPasswordCallback(CCOM_PSE_CTX *ctx, int (*cb)(char *, int, int, void *), void *userdata);
int WINAPI CCOM_PSESetRandCallback(CCOM_PSE_CTX *ctx, int (WINAPI *cb)(int, int, int, void *), void *userdata);
int WINAPI CCOM_PSESetDeviceCallback(CCOM_PSE_CTX *ctx, int (WINAPI *cb)(char *path, void *u), void *userdata);
int WINAPI CCOM_PSESetLockCallback(CCOM_PSE_CTX *ctx, void (*cb)(int type));
int WINAPI CCOM_PSESetPassword(CCOM_PSE_CTX *ctx, char *passwd, int len);
int WINAPI CCOM_PSERead(CCOM_PSE_CTX *ctx);
int WINAPI CCOM_PSEWrite(CCOM_PSE_CTX *ctx);
int WINAPI CCOM_PSEGenerate(CCOM_PSE_CTX *ctx);
int WINAPI CCOM_PSEErase(CCOM_PSE_CTX *ctx);

#define CCOM_GOSTR3410_94					(CCOM_ALG_TYPE_SIGN | 1)
#define CCOM_GOSTR3410_2001					(CCOM_ALG_TYPE_SIGN | 2)

#define CCOM_GOSTR3410_94_PARAMS_SC			GOSTS_PARAMS_SC
#define CCOM_GOSTR3410_94_PARAMS_CP_A		GOSTS_PARAMS_CP_A
#define CCOM_GOSTR3410_94_PARAMS_CP_B		GOSTS_PARAMS_CP_B
#define CCOM_GOSTR3410_94_PARAMS_CP_C		GOSTS_PARAMS_CP_C
#define CCOM_GOSTR3410_94_PARAMS_CP_D		GOSTS_PARAMS_CP_D
#define CCOM_GOSTR3410_94_PARAMS_CP_XA		GOSTS_PARAMS_CP_XA
#define CCOM_GOSTR3410_94_PARAMS_CP_XB		GOSTS_PARAMS_CP_XB
#define CCOM_GOSTR3410_94_PARAMS_CP_XC		GOSTS_PARAMS_CP_XC

#define CCOM_GOSTR3410_2001_PARAMS_SC		ECGOST_PARAMS_SC
#define CCOM_GOSTR3410_2001_PARAMS_SECP256R1	ECGOST_PARAMS_SC
#define CCOM_GOSTR3410_2001_PARAMS_CP_A		ECGOST_PARAMS_CP_A
#define CCOM_GOSTR3410_2001_PARAMS_CP_B		ECGOST_PARAMS_CP_B
#define CCOM_GOSTR3410_2001_PARAMS_CP_C		ECGOST_PARAMS_CP_C
#define CCOM_GOSTR3410_2001_PARAMS_CP_XA	ECGOST_PARAMS_CP_XA
#define CCOM_GOSTR3410_2001_PARAMS_CP_XB	ECGOST_PARAMS_CP_XB

#define CCOM_PKEY_SET_PARAMETERS			0
#define CCOM_PKEY_GET_PARAMETERS			1

#define CCOM_PRIVATE_KEY_PKCS8				0
#define CCOM_PRIVATE_KEY_RAW				1
#define CCOM_PUBLIC_KEY_RAW					2
#define CCOM_PUBLIC_KEY_SPKI				3

CCOM_KEY_PAIR_CTX * WINAPI CCOM_KeyPairNew(void);	// TODO: alg, params
int WINAPI CCOM_KeyPairFree(CCOM_KEY_PAIR_CTX *ctx);
int WINAPI CCOM_KeyPairSetPSE(CCOM_KEY_PAIR_CTX *ctx, CCOM_PSE_CTX *pse);
int WINAPI CCOM_KeyPairGenerate(CCOM_KEY_PAIR_CTX *ctx, int alg, int params);
CCOM_PRIVATE_KEY_CTX * WINAPI CCOM_KeyPairGetPrivateKey(CCOM_KEY_PAIR_CTX *ctx);
CCOM_PUBLIC_KEY_CTX * WINAPI CCOM_KeyPairGetPublicKey(CCOM_KEY_PAIR_CTX *ctx);
int WINAPI CCOM_IsKeyPair(CCOM_PRIVATE_KEY_CTX *priv, CCOM_PUBLIC_KEY_CTX *pub);


CCOM_PRIVATE_KEY_CTX * WINAPI CCOM_PrivateKeyNew(void);
int WINAPI CCOM_PrivateKeyFree(CCOM_PRIVATE_KEY_CTX *ctx);
int WINAPI CCOM_PrivateKeySetPSE(CCOM_PRIVATE_KEY_CTX *ctx, CCOM_PSE_CTX *pse);
int WINAPI CCOM_PrivateKeySetPasswordCallback(CCOM_PRIVATE_KEY_CTX *ctx, int (*cb)(char *, int, int, void *), void *userdata);
int WINAPI CCOM_PrivateKeySetPassword(CCOM_PRIVATE_KEY_CTX *ctx, char *passwd, int len);
int WINAPI CCOM_PrivateKeySetPath(CCOM_PRIVATE_KEY_CTX *ctx, char *path);

int WINAPI CCOM_PrivateKeySetEncoded(CCOM_PRIVATE_KEY_CTX *ctx, char *buf, int len);
int WINAPI CCOM_PrivateKeyRead(CCOM_PRIVATE_KEY_CTX *ctx);
int WINAPI CCOM_PrivateKeyReadRaw(CCOM_PRIVATE_KEY_CTX *ctx, int alg, int params);

int WINAPI CCOM_PrivateKeyGetEncoded(CCOM_PRIVATE_KEY_CTX *ctx, char *buf, int *len, int type);
int WINAPI CCOM_PrivateKeyWrite(CCOM_PRIVATE_KEY_CTX *ctx);
int WINAPI CCOM_PrivateKeyWriteRaw(CCOM_PRIVATE_KEY_CTX *ctx);

int WINAPI CCOM_PrivateKeyGetAlgorithm(CCOM_PRIVATE_KEY_CTX *ctx);
int WINAPI CCOM_PrivateKeyGetParameters(CCOM_PRIVATE_KEY_CTX *ctx);
CCOM_PUBLIC_KEY_CTX * WINAPI CCOM_PrivateKeyGetPublicKey(CCOM_PRIVATE_KEY_CTX *ctx);

CCOM_PUBLIC_KEY_CTX * WINAPI CCOM_PublicKeyNew(void);
int WINAPI CCOM_PublicKeyFree(CCOM_PUBLIC_KEY_CTX *ctx);
int WINAPI CCOM_PublicKeySetPath(CCOM_PUBLIC_KEY_CTX *ctx, char *path);

int WINAPI CCOM_PublicKeySetEncoded(CCOM_PUBLIC_KEY_CTX *ctx, char *buf, int len);
int WINAPI CCOM_PublicKeyRead(CCOM_PUBLIC_KEY_CTX *ctx);
int WINAPI CCOM_PublicKeyReadCertificate(CCOM_PUBLIC_KEY_CTX *ctx);
int WINAPI CCOM_PublicKeyReadRaw(CCOM_PUBLIC_KEY_CTX *ctx, int alg, int params);

int WINAPI CCOM_PublicKeyGetEncoded(CCOM_PUBLIC_KEY_CTX *ctx, char *buf, int *len, int type);
int WINAPI CCOM_PublicKeyWrite(CCOM_PUBLIC_KEY_CTX *ctx);
int WINAPI CCOM_PublicKeyWriteRaw(CCOM_PUBLIC_KEY_CTX *ctx);

int WINAPI CCOM_PublicKeyGetAlgorithm(CCOM_PUBLIC_KEY_CTX *ctx);
int WINAPI CCOM_PublicKeyGetParameters(CCOM_PUBLIC_KEY_CTX *ctx);


CCOM_SIGN_CTX * WINAPI CCOM_SignNew(CCOM_PRIVATE_KEY_CTX *pkey);
int WINAPI CCOM_SignFree(CCOM_SIGN_CTX *ctx);
int WINAPI CCOM_SignInit(CCOM_SIGN_CTX *ctx);
int WINAPI CCOM_SignUpdate(CCOM_SIGN_CTX *ctx, char *in, int inl);
int WINAPI CCOM_SignFinal(CCOM_SIGN_CTX *ctx, char *out, int *outl);
int WINAPI CCOM_SignDigest(CCOM_SIGN_CTX *ctx, char *md, int mdl, char *sig, int *sigl);
int WINAPI CCOM_SignGetSignatureLength(CCOM_SIGN_CTX *ctx);
int WINAPI CCOM_SignGetDigestAlgorithm(CCOM_SIGN_CTX *ctx);
int WINAPI CCOM_SignSetDigestAlgorithm(CCOM_SIGN_CTX *ctx, int alg);

CCOM_SIGN_CTX * WINAPI CCOM_VerifyNew(CCOM_PUBLIC_KEY_CTX *pkey);
int WINAPI CCOM_VerifyFree(CCOM_SIGN_CTX *ctx);
int WINAPI CCOM_VerifyInit(CCOM_SIGN_CTX *ctx);
int WINAPI CCOM_VerifyUpdate(CCOM_SIGN_CTX *ctx, char *in, int inl);
int WINAPI CCOM_VerifyFinal(CCOM_SIGN_CTX *ctx, char *sig, int sigl);
int WINAPI CCOM_VerifyDigest(CCOM_SIGN_CTX *ctx, char *md, int mdl, char *sig, int sigl);
int WINAPI CCOM_VerifyGetSignatureLength(CCOM_SIGN_CTX *ctx);
int WINAPI CCOM_VerifyGetDigestAlgorithm(CCOM_SIGN_CTX *ctx);
int WINAPI CCOM_VerifySetDigestAlgorithm(CCOM_SIGN_CTX *ctx, int alg);

#define CCOM_KEY_AGREE_ECDH								(CCOM_ALG_TYPE_KEY_AGREE | 1)
#define CCOM_KEY_AGREE_VKO_GOSTR3410_2001				(CCOM_ALG_TYPE_KEY_AGREE | 2)

#define CCOM_VKO_GOSTR3410_2001_UKM_LENGTH				8

CCOM_KEY_AGREE_CTX * WINAPI CCOM_KeyAgreeNew(void);
int WINAPI CCOM_KeyAgreeFree(CCOM_KEY_AGREE_CTX *ctx);

int WINAPI CCOM_KeyAgreeGenerateKeyPair(CCOM_KEY_AGREE_CTX *ctx, int alg, int params);
int WINAPI CCOM_KeyAgreeSetKeyPair(CCOM_KEY_AGREE_CTX *ctx, CCOM_PRIVATE_KEY_CTX *priv, CCOM_PUBLIC_KEY_CTX *pub);
int WINAPI CCOM_KeyAgreeSetPrivateKey(CCOM_KEY_AGREE_CTX *ctx, CCOM_PRIVATE_KEY_CTX *priv);
int WINAPI CCOM_KeyAgreeSetPeerPublicKey(CCOM_KEY_AGREE_CTX *ctx, CCOM_PUBLIC_KEY_CTX *pub);
CCOM_PUBLIC_KEY_CTX * WINAPI CCOM_KeyAgreeGetPublicKey(CCOM_KEY_AGREE_CTX *ctx);
CCOM_SECRET_KEY_CTX * WINAPI CCOM_KeyAgreeComputeSharedSecret(CCOM_KEY_AGREE_CTX *ctx, int alg, void *params);

#define CCOM_KEY_DERIVE_DUMMY							(CCOM_ALG_TYPE_KEY_DERIVE | 1)
#define CCOM_KEY_DERIVE_GOST28147_89_DUMMY				(CCOM_ALG_TYPE_KEY_DERIVE | 2)
#define CCOM_KEY_DERIVE_X942_WITH_GOSTR3411_94_SC		(CCOM_ALG_TYPE_KEY_DERIVE | 3)
#define CCOM_KEY_DERIVE_TLS_PRF_WITH_GOSTR3411_94_SC	(CCOM_ALG_TYPE_KEY_DERIVE | 4)
#define CCOM_KEY_DERIVE_TLS_PRF_WITH_GOSTR3411_94_CP	(CCOM_ALG_TYPE_KEY_DERIVE | 5)
#define CCOM_KEY_DERIVE_TLS_PRF_WITH_GOSTR3411_94		CCOM_KEY_DERIVE_TLS_PRF_WITH_GOSTR3411_94_CP	

CCOM_KEY_DERIVE_CTX * WINAPI CCOM_KeyDeriveNew(int alg);
int WINAPI CCOM_KeyDeriveFree(CCOM_KEY_DERIVE_CTX *ctx);
int WINAPI CCOM_KeyDerive(CCOM_KEY_DERIVE_CTX *ctx, CCOM_SECRET_KEY_CTX *secret, int outl, void *seed, int seedl);
int WINAPI CCOM_KeyDeriveGetAvailable(CCOM_KEY_DERIVE_CTX *ctx);
CCOM_SECRET_KEY_CTX * WINAPI CCOM_KeyDeriveGetSecretKey(CCOM_KEY_DERIVE_CTX *ctx, int length);
CCOM_SECRET_KEY_CTX * WINAPI CCOM_KeyDeriveGenerateSecretKey(CCOM_KEY_DERIVE_CTX *ctx, int alg);
int WINAPI CCOM_KeyDeriveGetIV(CCOM_KEY_DERIVE_CTX *ctx, char *iv, int ivl);

#define CCOM_KEY_WRAP_GOST28147_89_SIMPLE				(CCOM_ALG_TYPE_KEY_WRAP | 1)
#define CCOM_KEY_WRAP_GOST28147_89_RFC3217				(CCOM_ALG_TYPE_KEY_WRAP | 2)
#define CCOM_KEY_WRAP_GOST28147_89_RFC4357				(CCOM_ALG_TYPE_KEY_WRAP | 3)
#define CCOM_KEY_WRAP_GOST28147_89_RFC4357_SIMPLE		(CCOM_ALG_TYPE_KEY_WRAP | 4)

#define CCOM_KEY_WRAP_SET_GOST28147_89_SBOX				0
#define CCOM_KEY_WRAP_GET_GOST28147_89_SBOX				1

CCOM_KEY_WRAP_CTX * WINAPI CCOM_KeyWrapNew(int alg);
int WINAPI CCOM_KeyWrapInit(CCOM_KEY_WRAP_CTX *ctx, CCOM_SECRET_KEY_CTX *kek);
long WINAPI CCOM_KeyWrapCtrl(CCOM_KEY_WRAP_CTX *ctx, int cmd, long num, void *arg);
int WINAPI CCOM_KeyWrap(CCOM_KEY_WRAP_CTX *ctx, CCOM_SECRET_KEY_CTX *cek, char *iv, char *out, int *outl);
CCOM_SECRET_KEY_CTX * WINAPI CCOM_KeyUnwrap(CCOM_KEY_WRAP_CTX *ctx, char *in, int inl);
int WINAPI CCOM_KeyWrapFree(CCOM_KEY_WRAP_CTX *ctx);
int WINAPI CCOM_KeyWrapGetIVLength(CCOM_KEY_WRAP_CTX *ctx);
int WINAPI CCOM_KeyWrapGetWrappedLength(CCOM_KEY_WRAP_CTX *ctx);

/*
 *	Идентификаторы типов ДСЧ
 */
#define RAND_TYPE_NONE			0
#define RAND_TYPE_CRYPTON		1
#define RAND_TYPE_CRYPTON_EMULATOR	2
#define RAND_TYPE_ACCORD		3
#define RAND_TYPE_SABLE			4
#define RAND_TYPE_DEMO			5	/* tvm 30.01.04 */
#define RAND_TYPE_GAMMA			6

int WINAPI CCOM_RandomInited(void);	// TODO: убрать
int WINAPI CCOM_RandomGetType(void);
int WINAPI CCOM_RandomInit(CCOM_PSE_CTX *ctx);
int WINAPI CCOM_RandomClose(void);
int WINAPI CCOM_RandomBytes(void *ptr, int len);

int WINAPI CCOM_ErrorCheck(void);
void WINAPI CCOM_ErrorClear(void);
char * WINAPI CCOM_ErrorGetString(void);
unsigned long WINAPI CCOM_GetLastError(void);
void WINAPI CCOM_SetLastError(unsigned long err);
unsigned long WINAPI CCOM_GetLastTokenError(void);
void WINAPI CCOM_SetLastTokenError(unsigned long err);

char * WINAPI CCOM_Dump(char *head, char *buf, int ln);
void WINAPI CCOM_Free(void *p);
int WINAPI CCOM_FileErase(char *path);					// TODO

int WINAPI CCOM_Init(void);
int WINAPI CCOM_Close(void);
int WINAPI CCOM_Inited(void);
const char * WINAPI CCOM_GetVersion(void);
int WINAPI CCOM_SelfTest(void);

#define CCOM_ENCODING_ANSI      1
#define CCOM_ENCODING_OEM       3
#define CCOM_ENCODING_UTF8      5

int WINAPI CCOM_SetInputEncoding(int symset);
int WINAPI CCOM_SetOutputEncoding(int symset);

void WINAPI CCOM_TokenSetPasswordCallback(int (*cb)(char *, int, int, void *));

#ifdef  __cplusplus
}
#endif
#endif	/* _HEADER_CCEVP_H */
