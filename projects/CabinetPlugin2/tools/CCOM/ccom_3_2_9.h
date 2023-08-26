/*
* $Revision: 1.61 $
* $Date: 2007/10/26 09:40:34 $
*/
/* 
* ccom.h
* Crypto-COM 3.2 header file
* Copyright (C) 1997-2006 Signal-COM
*/

#ifndef _CCOM_H
#define _CCOM_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdio.h>
	
#define GOSTS				void
#define ECGOST				void
#define GOSTS_SIGN			void
#define ECGOST_SIGN			void
#define PSE				void
#define PSE_CTX				void
#define GOSTS_DH			void
#define ECGOST_DH			void
#define GOSTE_CTX			void
#define GOSTH_CTX			void
#define GOSTE_KEY			void
	
#define ECGOST_PRIV_MAXLEN		32
#define ECGOST_PRIV_LENGTH		ECGOST_PRIV_MAXLEN
#define ECGOST_PUB_MAXLEN		65
#define ECGOST_PUB_LENGTH		ECGOST_PUB_MAXLEN
#define ECGOST_SIGN_LENGTH		64

#define GOSTS_P_MAXLEN          	128
#define GOSTS_Q_MAXLEN          	32
#define GOSTS_A_MAXLEN          	GOSTS_P_MAXLEN
#define GOSTS_X_MAXLEN         		GOSTS_Q_MAXLEN
#define GOSTS_Y_MAXLEN          	GOSTS_P_MAXLEN
#define GOSTS_SIGN_MAXLEN       	(GOSTS_Q_MAXLEN*2)
#define GOSTS_SIGN_LENGTH       	GOSTS_SIGN_MAXLEN

#define GOSTS_P_LENGTH          	GOSTS_P_MAXLEN
#define GOSTS_Q_LENGTH          	GOSTS_Q_MAXLEN
#define GOSTS_A_LENGTH          	GOSTS_A_MAXLEN
#define GOSTS_X_LENGTH          	GOSTS_X_MAXLEN
#define GOSTS_Y_LENGTH          	GOSTS_Y_MAXLEN

#define GOSTE_ENCRYPT			1		/* зашифрование */
#define GOSTE_DECRYPT			0		/* расшифрование */

#define GOSTE_BLOCK			8		/* Длина блока информации
							   для режима простой замены (в байтах) */
#define GOSTE_IV_LENGTH			GOSTE_BLOCK	/* Длина синхропосылки */
#define GOSTE_KEY_MAXLEN		32		/* Длина ключа (в байтах) */
#define GOSTE_KEY_LENGTH		GOSTE_KEY_MAXLEN

#define GOSTE_MODE_ECB			0
#define GOSTE_MODE_GAMMA		1
#define GOSTE_MODE_GFB			2
#define GOSTE_MODE_MAC			3
#define GOSTE_MODE_CBC			4			/* CryptoPro */
#define GOSTE_MODE_CP_GFB		5			/* CryptoPro, obsolete */
#define GOSTE_MODE_CNT			GOSTE_MODE_GAMMA	/* CryptoPro */
#define GOSTE_MODE_CFB			GOSTE_MODE_GFB		/* CryptoPro */
#define GOSTE_MODE_MASK			0xff

#define MESH_MODE_OFF			0
#define MESH_MODE_KEY			0x100
#define MESH_MODE_IV			0x200
#define MESH_MODE_ON			(MESH_MODE_KEY|MESH_MODE_IV)
#define GOSTE_MODE_MESH_MASK		0x300
	
#define GOSTE_SBOX_LENGTH		64			/* Длина узлов замены */
#define GOSTH_SBOX_LENGTH		GOSTE_SBOX_LENGTH
#define GOSTS_SBOX_LENGTH		GOSTE_SBOX_LENGTH

#define GOSTE_MAC_BITLENGTH		32		/* in bits */
#define GOSTE_MAC_LENGTH		4		/* in bytes */

#define GOSTH_CBLOCK			32

#define GOSTH_BLOCK_LENGTH		GOSTH_CBLOCK
#define GOSTH_DIGEST_LENGTH		32

#define GOST_PRIV_MAXLEN		32
#define GOST_OPAQUE_LENGTH		(GOST_PRIV_MAXLEN + GOSTE_MAC_LENGTH)	/* 36 */
#define GOSTE_OPAQUE_LENGTH		GOST_OPAQUE_LENGTH
#define GOSTS_OPAQUE_LENGTH		GOST_OPAQUE_LENGTH
#define ECGOST_OPAQUE_LENGTH		GOST_OPAQUE_LENGTH

#define MKEY_FORMAT_ID			0x22
#define MKEY_MASK_MIN			2
#define MKEY_MASK_MAX			8
#define MKEY_MASK_NUM			MKEY_MASK_MAX
#define MKEY_MASK_LENGTH		GOSTE_KEY_MAXLEN
#define MKEY_MASKS_MAXLEN		(MKEY_MASK_LENGTH*(MKEY_MASK_NUM-1))
#define MKEY_MAXLEN			(MKEY_MASKS_MAXLEN+GOST_OPAQUE_LENGTH+2)
	
#define CCOM31_OPAQUE_LENGTH		36
#define CCOM30_OPAQUE_LENGTH		42	/* tvm 23.07.2002 */

#define GOSTE_SS_CHECK_MAGIC            0x84cd758aL
#define GOSTE_GAMMA_CHECK_MAGIC         0x3778bd50L
#define GOSTE_GFB_CHECK_MAGIC           0x350a2401L
#define GOSTE_MAC_CHECK_MAGIC           0x58be994cL
#define GOSTH_CHECK_MAGIC               0x0b97afc4L
#define GOSTS_SIGN_CHECK_MAGIC          0x8ff7ff6aL
#define GOSTS_VERIFY_CHECK_MAGIC        0x313f8441L
#define GOSTS_DH_CHECK_MAGIC            0x91998aacL
#define GOSTS_EG_CHECK_MAGIC            0x41e03922L
#define ECGOST_CHECK_MAGIC				0x99ca3c9eL
#define ECDH_CHECK_MAGIC				0x682796e2L

/*
 *	Идентификаторы параметров ГОСТ Р 34.10-94 и DH
 */
#define GOSTS_PARAMS_SC			1
#define GOSTS_PARAMS_SC_DH		2
#define GOSTS_PARAMS_CP_A		3
#define GOSTS_PARAMS_CP_B		4
#define GOSTS_PARAMS_CP_C		5
#define GOSTS_PARAMS_CP_D		6
#define GOSTS_PARAMS_CP_XA		7
#define GOSTS_PARAMS_CP_XB		8
#define GOSTS_PARAMS_CP_XC		9
#define GOSTS_PARAMS_TEST		10				// использовать только в целях тестирования
#define GOSTS_PARAMS_DEFAULT		GOSTS_PARAMS_SC

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
#define ECGOST_PARAMS_TEST		17				// использовать только в целях тестирования
#define ECGOST_PARAMS_DEFAULT		ECGOST_PARAMS_SC

/*
 *	Идентификаторы узлов замены для ГОСТ Р 34.11-94
 */
#define GOSTH_SBOX_SC			21
#define GOSTH_SBOX_CP			22
#define GOSTH_SBOX_TEST			23				// использовать только в целях тестирования
#define GOSTH_SBOX_DEFAULT		GOSTH_SBOX_SC

/*
 *	Идентификаторы узлов замены для ГОСТ 28147-89
 */
#define GOSTE_SBOX_SC			31				// не использовать для шифрования данных после 31.03.2009
#define GOSTE_SBOX_CP_A			32
#define GOSTE_SBOX_CP_B			33
#define GOSTE_SBOX_CP_C			34
#define GOSTE_SBOX_CP_D			35
#define GOSTE_SBOX_TEST			GOSTH_SBOX_TEST	// использовать только в целях тестирования
#define GOSTE_SBOX_DEFAULT		GOSTE_SBOX_SC	// не использовать для шифрования данных после 31.03.2009

#define GOSTS_FLAG_PRESIGN		0x01
#define ECGOST_FLAG_PRESIGN		GOSTS_FLAG_PRESIGN
#define ECGOST_FLAG_COMPRESS		0x02

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

/// AA !!! // #ifdef _WIN32
#ifndef WIN64
#error __________________________WIN32!!!
#    ifndef _KERNEL
#        include <windows.h>
#        define WINAPI_CALLBACK	WINAPI
#    else
#        define NO_WINAPI
#    endif
#else
#	pragma message("ccom.h: x64 platform!")
#endif /* _WIN32 */


/// AA !!! // #if !defined(_WIN32) || defined(NO_WINAPI)
#if defined(WIN64) || defined(NO_WINAPI)
#undef WINAPI
#define WINAPI
#endif /* _WIN32 */

#if defined(NO_WINAPI) || defined(NO_WINAPI_CALLBACK)
#undef WINAPI_CALLBACK
#define WINAPI_CALLBACK
#endif

/*
 *	Структура для хранения секретного ключа
 */
typedef struct opaque_priv_key_t
{
	unsigned char priv	[GOST_PRIV_MAXLEN];
	unsigned char mac	[GOSTE_MAC_LENGTH];
} OPAQUE_PRIV_KEY;

/* 
 *	Генерация ключей по ГОСТ Р 34.10-2001 
 */
int 
WINAPI
ECGOST_generate_key (
	PSE *pse,			/* ключевой контейнер */
	int paramsID,			/* идентификатор параметров */
	OPAQUE_PRIV_KEY *priv,		/* секретный ключ */
	unsigned char *pub,		/* открытый ключ */
	int *pub_len,			/* длина открытого ключа */
	int flags			/* флаги */
	);

/* 
 *	Генерация открытого ключа ГОСТ Р 34.10-2001 
 */
int WINAPI
ECGOST_generate_public_key (
	PSE *pse,
	int paramsID,
	OPAQUE_PRIV_KEY *priv, 
	unsigned char *pub, 
	int *pub_len, 
	int flags
	);
							/*
 *	Создание контекста подписи
 */
ECGOST_SIGN * 
WINAPI 
ECGOST_SIGN_new (
	void
	);
/*
 *	Освобождение контекста подписи
 */
void 
WINAPI 
ECGOST_SIGN_free (
	ECGOST_SIGN *x
	);
/*
 *	Очистка контекста подписи
 */
void 
WINAPI 
ECGOST_SIGN_clean (
	ECGOST_SIGN *x
	);
/*
 *	Инициализация подписи
 */
int 
WINAPI 
ECGOST_sign_init (
	ECGOST_SIGN *ctx,	/* контекст подписи */
	PSE *pse,		/* ключевой контейнер */
	int paramsID,		/* идентификатор параметров ключей */
	OPAQUE_PRIV_KEY *x,	/* секретный ключ */
	int sbox,		/* итентификатор параметров хэширования */
	unsigned char *h0,	/* начальный вектор хэширования */
	int flags		/* флаги */
	);
/*
 *	Инициализация проверки подписи
 */
int 
WINAPI 
ECGOST_verify_init (
	ECGOST_SIGN *ctx,	/* контекст подписи */
	int paramsID,		/* идентификатор параметров ключа */
	unsigned char *pub,	/* открытый ключ */
	int sbox,		/* идентификатор параметров для хэширования */
	unsigned char *h0	/* начальный вектор хэширования */
	);
/*
 *	Хэширование данных
 */
void 
WINAPI 
ECGOST_update (
	ECGOST_SIGN *ctx,	/* контекст подписи */
	unsigned char *data,	/* данные */
	int len			/* дина данных в байтах */
	);
/*
 *	Формирование подписи
 */
int 
WINAPI 
ECGOST_sign_final (
	ECGOST_SIGN *ctx,	/* контекст подписи */
	unsigned char *sign,	/* буфер для подписи */ 
	int *siglen		/* длина подписи */
	);
/*
 *	Проверка подписи
 */
int 
WINAPI 
ECGOST_verify_final (
	ECGOST_SIGN *ctx,	/* контекст подписи */
	unsigned char *sign,	/* подпись */ 
	int siglen		/* длина подписи */
	);
/*
 *	Формирование подписи для заданного хэш-значения
 */
int 
WINAPI 
ECGOST_sign_digest (
	PSE *pse,		/* ключевой контейнер */
	int paramsID,		/* идентификатор параметров ключа */
	OPAQUE_PRIV_KEY *x, 	/* секретный ключ */
	unsigned char *md,	/* хэш-значение */
	unsigned char *sign,	/* буфер для подписи */	
	int *siglen		/* длина подписи */
	);
/*
 *	Проверка подписи для заданного хэш-значения
 */
int 
WINAPI 
ECGOST_verify_digest (
	int paramsID,		/* идентификатор параметров ключа */
	unsigned char *pub,	/* открытый ключ */
	unsigned char *md,	/* хэш-значение */
	unsigned char *sign,	/* подпись */ 
	int siglen		/* длина подписи */
	);
/*
 *	Создание контекста ECDH
 */
ECGOST_DH * 
WINAPI 
ECGOST_DH_new (
	int params		/* идентификатор параметров */
	);
/*
 *	Освобождение контекста ECDH
 */
void 
WINAPI 
ECGOST_DH_free (
	ECGOST_DH *dh		/* контекст */
	);
/*
 *	Генерация ключей ECDH
 *	pse, priv и pub используются только в 
 *	ephemeral-static и static-static режимах
 */
int 
WINAPI 
ECGOST_DH_generate_key (
	ECGOST_DH *dh,		/* контекст */
	PSE *pse,		/* ключевой контейнер */
	OPAQUE_PRIV_KEY *priv,	/* секретный ключ */
	unsigned char *pub,	/* открытый ключ */
	unsigned char *trans,	/* открытый ключ */
	int *trans_len,		/* длина открытого ключа */
	int flags		/* флаги */
	);
/*
 *	Вычисление общего секрета по ECDH
 */
int 
WINAPI 
ECGOST_DH_compute_key (
	ECGOST_DH *dh,		/* контекст */
	unsigned char *trans,	/* открытый ключ */
	unsigned char *key,	/* общий секрет */
	int *key_len		/* длина общего секрета */
	);
/*
 *	Вычисление общего секрета по ECDH
 */
int 
WINAPI 
ECGOST_DH_compute_shared_secret(
	ECGOST_DH *dh,		/* контекст */
	unsigned char *trans	/* открытый ключ */
	);
/*
 *	Формирование сеансового ключа ГОСТ 28147-89
 */
GOSTE_KEY * 
WINAPI 
ECGOST_DH_get_secret_key (
	ECGOST_DH *dh,		/* контекст */
	int sbox,			/* итентификатор параметров хэширования */
	long flags,
	void *userdata
	);
/*
 *	Создание контекста подписи ГОСТ Р 34.10-94
 */ 
void * 
WINAPI 
GOSTS_SIGN_new (
	void
	);
/*
 *	Освобождение контекста подписи ГОСТ Р 34.10-94
 */ 
void 
WINAPI 
GOSTS_SIGN_free (
	GOSTS_SIGN *sign
	);
/*
 *	Очистка контекста подписи ГОСТ Р 34.10-94
 */ 
void 
WINAPI 
GOSTS_SIGN_clean (
	GOSTS_SIGN *sign
	);
/*
 *	Генерация ключей ГОСТ Р 34.10-94
 */ 
int 
WINAPI 
GOSTS_generate_key (
	PSE *pse,		/* ключевой контейнер */
	int paramsID,		/* идентификатор параметров */
	OPAQUE_PRIV_KEY *priv,	/* секретный ключ */
	unsigned char *pub	/* открытый ключ */
	);

/*
 *	Генерация открытого ключа ГОСТ Р 34.10-94
 */ 
int WINAPI 
GOSTS_generate_public_key (
	PSE *pse,
	int paramsID, 
	OPAQUE_PRIV_KEY *priv,
	unsigned char *pub
	);
						   
/*
 *	Инициализация подписи
 */
int 
WINAPI 
GOSTS_sign_init (
	GOSTS_SIGN *ctx,	/* контекст */
	PSE *pse,		/* ключевой контейнер */
	int paramsID,		/* идентификатор параметров ключа */
	OPAQUE_PRIV_KEY *x,	/* секретный ключ */
	int sbox,		/* идентификатор параметров хэширования */
	unsigned char *h0,	/* начальный вектор хэширования */
	int flags
	);
/*
 *	Инициализация проверки подписи
 */
int 
WINAPI 
GOSTS_verify_init (
	GOSTS_SIGN *ctx,	/* контекст */
	int paramsID,		/* идентификатор параметров ключа */
	unsigned char *pub,	/* открытый ключ */
	int sbox,		/* идентификатор параметров хэширования */
	unsigned char *h0	/* начальный вектор хэширования */
	);
/*
 *	Хэширование данных
 */					   
void 
WINAPI 
GOSTS_update(
	GOSTS_SIGN *ctx,	/* контекст */
	unsigned char *data,	/* данные */
	int len			/* длина данных */
	);

#define GOSTS_sign_update(ctx, data,len)        GOSTS_update(ctx, data,len)
#define GOSTS_verify_update(ctx, data,len)      GOSTS_update(ctx, data,len)

/*
 *	Формирование подписи
 */
int 
WINAPI 
GOSTS_sign_final(
	GOSTS_SIGN *ctx,	/* контекст */
	unsigned char *sign,	/* буфер для подписи */
	int *siglen		/* длина подписи */
	);
/*
 *	Проверка подписи
 */
int 
WINAPI 
GOSTS_verify_final(
	GOSTS_SIGN *ctx,	/* контекст */
	unsigned char *sign,	/* подпись */
	int siglen		/* длина подписи */
	);
/*
 *	Формирование подписи для заданного хэш-значения
 */
int 
WINAPI 
GOSTS_sign_digest (
	PSE *pse,		/* ключевой контейнер */
	int paramsID,		/* идентификатор параметров ключа */
	OPAQUE_PRIV_KEY *x,	/* секретный ключ */
	unsigned char *md,	/* хэш-значение */
	unsigned char *sign,	/* буфер для подписи */
	int *siglen		/* длина подписи */
	);
/*
 *	Проверка подписи для заданного хэш-значения
 */
int 
WINAPI 
GOSTS_verify_digest (
	int paramsID,		/* идентификатор параметров ключа */
	unsigned char *y,	/* открытый ключ */
	unsigned char *md,	/* хэш-значение */
	unsigned char *sign,	/* подпись */
	int siglen		/* длина подписи */
	);

/* Создание контекста Diffie-Hellman */
GOSTS_DH * 
WINAPI 
GOSTS_DH_new(
	int paramsID		/* идентификатор параметров */
	);

#define GOSTS_DH_init()			GOSTS_DH_new(GOSTS_PARAMS_SC_DH)

/*
 *	Освобождение контекста DH
 */
void 
WINAPI 
GOSTS_DH_free(
	GOSTS_DH *dh		/* контекст */
	);
/*
 *	Генерация ключей DH
 */
int 
WINAPI 
GOSTS_DH_generate_key (
	GOSTS_DH *dh,		/* контекст */
	unsigned char *trans	/* открытый ключ (для передачи) */
	);
/*
 *	Вычисление общего секрета по алгоритму DH
 */
int 
WINAPI 
GOSTS_DH_compute_key (
	GOSTS_DH *dh,		/* контекст */
	unsigned char *trans,	/* открытый ключ */
	unsigned char *key	/* общий секрет */
	);
/*
 *	Вычисление общего секрета по алгоритму DH
 */
int 
WINAPI 
GOSTS_DH_compute_shared_secret (
	GOSTS_DH *dh,		/* контекст */
	unsigned char *trans	/* открытый ключ */
	);

/*
 *	Формирование сеансового ключа ГОСТ 28147-89
 */
GOSTE_KEY * 
WINAPI 
GOSTS_DH_get_secret_key (
	GOSTS_DH *dh,		/* контекст */
	int sbox,			/* итентификатор параметров хэширования */
	long flags,
	void *userdata
	);

/* ElGamal */
#define GOSTS_EG_init()		GOSTS_DH_new(GOSTS_PARAMS_SC)
#define GOSTS_EG_free(ctx)	GOSTS_DH_free(ctx)

/*
 *	Генерация ключей для алгоритма ElGamal
 */
int 
WINAPI 
GOSTS_EG_generate_key (
	GOSTS_DH *dh,		/* контекст */
	unsigned char *pub,	/* открытый ключ противоположной стрроны */
	unsigned char *trans,	/* наш открытый ключ */
	unsigned char *key	/* общий секрет */
	);
/*
 *	Вычисление общего секрета по алгоритму ElGamal
 */
int 
WINAPI 
GOSTS_EG_compute_key (
	GOSTS_DH *dh,		/* контекст */
	PSE *pse,		/* ключевой контейнер */
	OPAQUE_PRIV_KEY *priv,	/* секретный ключ */
	unsigned char *trans,	/* открытый ключ противоположной стороны */
	unsigned char *key	/* общий секрет */
	);

/*
 *	Вычисление общего секрета по алгоритму ElGamal
 */
int 
WINAPI 
GOSTS_EG_compute_shared_secret (
	GOSTS_DH *dh,		/* контекст */
	PSE *pse,		/* ключевой контейнер */
	OPAQUE_PRIV_KEY *priv,	/* секретный ключ */
	unsigned char *pub,	/* открытый ключ */
	unsigned char *trans	/* открытый ключ противоположной стороны */
	);


/* 
*	Выделение памяти для ключа ГОСТ 28147-89
*/
GOSTE_KEY * 
WINAPI 
GOSTE_KEY_new(void);
/* 
*	Очистка ключа ГОСТ 28147-89
*/
void 
WINAPI 
GOSTE_KEY_clean(GOSTE_KEY *x);
/* 
*	Освобождение ключа ГОСТ 28147-89
*/
void 
WINAPI 
GOSTE_KEY_free(GOSTE_KEY *x);
/* 
*	Инициализация ключа ГОСТ 28147-89
*/
int 
WINAPI 
GOSTE_KEY_init(
	GOSTE_KEY *key, 
	const unsigned char *k
	);

/* 
 *	Создание контекста ГОСТ 28147-89 
 */
GOSTE_CTX * 
WINAPI 
GOSTE_new (
	void
	);
/*
 *	Очистка контекста ГОСТ 28147-89 
 */
void 
WINAPI 
GOSTE_clean (
	GOSTE_CTX *ctx
	);
/*
 *	Освобождение контекста ГОСТ 28147-89 
 */
void 
WINAPI 
GOSTE_free (
	GOSTE_CTX *ctx
	);
/*
 *	Инициализация зашифрования/расшифрования
 */
int 
WINAPI 
GOSTE_init (
	GOSTE_CTX *x,			/* контекст */
	int mode,			/* режим */
	int encrypt,			/* зашифрование или расшифрование */
	const unsigned char *key,	/* ключ */
	const unsigned char *iv,	/* синхропосылка */
	int sbox			/* идентификатор узлов замены */
	);
/*
 *	Инициализация зашифрования/расшифрования по ГОСТ 28147-89
 */
int WINAPI 
GOSTE_init_ex (
	GOSTE_CTX *x,			/* контекст */
	int mode,			/* режим */
	int encrypt,			/* зашифрование или расшифрование */
	GOSTE_KEY *key,				/* дескриптор ключа */
	const unsigned char *iv,	/* синхропосылка */
	int sbox			/* идентификатор узлов замены */
	);
/*
 *	Зашифрование/расшифрование
 */
int 
WINAPI 
GOSTE_update (
	GOSTE_CTX *x,			/* контекст */
	unsigned char *in,		/* входные данные */
	unsigned char *out,		/* выходные данные */
	int nbytes			/* длина входных данных в байтах */
	);

/*
 *	Инициализация ГОСТ 28147-89 а режиме простой замены
 */ 
int 
WINAPI 
GOSTE_simple_subst_init (
	GOSTE_CTX *ctx, 
	int work,  
	const unsigned char *key, 
	const unsigned char *sbox
	);
/*
 *	Зашифрование/расшифрование блоками
 */
int 
WINAPI 
GOSTE_simple_subst_update (
	GOSTE_CTX *ctx, 
	unsigned char *in, 
	unsigned char *out, 
	int nblocks			/* число блоков */
	);
/*
 *	Зашифрование/расшифрование
 */
int 
WINAPI 
_GOSTE_simple_subst_update(
	GOSTE_CTX *x, 
	unsigned char *in, 
	unsigned char *out, 
	int nbytes
	);

/*
 *	Инициализация ГОСТ 28147-89 а режиме гаммирования
 */ 
int 
WINAPI 
GOSTE_gamma_init (
	GOSTE_CTX *ctx, 
	const unsigned char *key, 
	const unsigned char *sync, 
	const unsigned char *sbox
	);
/*
 *	Зашифрование/расшифрование
 */
int 
WINAPI 
GOSTE_gamma_update (
	GOSTE_CTX *ctx, 
	unsigned char *in, 
	unsigned char *out, 
	int nbytes
	);

#define GOSTE_gamma(c,i,o,n) GOSTE_gamma_update(c,i,o,n)

/*
 *	Инициализация ГОСТ 28147-89 а режиме гаммирования
 *	с обратной связью
 */ 
int 
WINAPI 
GOSTE_gamma_fb_init (
	GOSTE_CTX *ctx, 
	const unsigned char *key, 
	const unsigned char *sync, 
	const unsigned char *sbox
	);
/*
 *	Зашифрование
 */
int 
WINAPI 
GOSTE_gamma_fb_encrypt (
	GOSTE_CTX *ctx, 
	unsigned char *in, 
	unsigned char *out, 
	int nbytes
	);
/*
 *	Расшифрование
 */
int 
WINAPI 
GOSTE_gamma_fb_decrypt (
	GOSTE_CTX *ctx, 
	unsigned char *in, 
	unsigned char *out, 
	int nbytes
	);

/*
 *	Инициализация ГОСТ 28147-89 а режиме выработки имитовставки
 */ 
int 
WINAPI 
GOSTE_mac_init (
	GOSTE_CTX *ctx, 
	const unsigned char *key, 
	const unsigned char *sbox
	);
/*
 *	Инициализация ГОСТ 28147-89 а режиме выработки имитовставки
 */ 
int 
WINAPI 
GOSTE_mac_init_ex(
	GOSTE_CTX *ctx, 
	const unsigned char *key, 
	const unsigned char *sync, 
	const unsigned char *sbox
	);
/*
 *	Обработка данных
 */
int 
WINAPI 
GOSTE_mac_update (
	GOSTE_CTX *ctx, 
	unsigned char *buf, 
	int nbytes
	);
/*
 *	Получение значения имитовставки
 */
int 
WINAPI 
GOSTE_mac_final (
	GOSTE_CTX *ctx, 
	unsigned char *mac, 
	int nbits			/* в битах, max 32 */
	);
/*
 *	Вычисление имитовставки
 */
unsigned char * 
WINAPI 
GOSTE_mac(
	GOSTE_CTX *x, 
	unsigned char *d, int n, 
	unsigned char *key, 
	unsigned char *sbox, 
	unsigned char *mac
	);
/*
 *	Инициализация ГОСТ 28147-89 а режиме CBC
 */ 
int 
WINAPI 
GOSTE_cbc_init(
	GOSTE_CTX *x, 
	int work, 
	const unsigned char *key, 
	const unsigned char *sync, 
	const unsigned char *sbox
	);
/*
 *	Зашифрование/расшифрование блоками
 */
int 
WINAPI 
GOSTE_cbc_update(
	GOSTE_CTX *x, 
	unsigned char *in, 
	unsigned char *out, 
	int nblocks
	);
/*
 *	Зашифрование/расшифрование
 */
int 
WINAPI 
_GOSTE_cbc_update(
	GOSTE_CTX *x, 
	unsigned char *in, 
	unsigned char *out, 
	int nbytes
	);

/*
 *	Выработка случайных чисел
 */
int 
WINAPI 
RAND_bytes(
	unsigned char *buf,	/* буфер для заполнения */
	int num			/* длина буфера в байтах */
	);

/* 
 *	Генерация ключа ГОСТ 28147-89
 */
#define GOSTE_keygen(k)   RAND_bytes(k, 32)

/*
 *	Инициализация ГОСТ Р 34.11-94	
 */
GOSTH_CTX * 
WINAPI 
GOSTH_new(
	void
	);
/*
 *	Освобождение контекста ГОСТ Р 34.11-94
 */
void 
WINAPI 
GOSTH_free(
	GOSTH_CTX *
	);
/*
 *	Очистка контекста ГОСТ Р 34.11-94
 */
void 
WINAPI 
GOSTH_clean(
	GOSTH_CTX *
	);
/*
 *	Инициализация хэширования
 */
int 
WINAPI 
GOSTH_hash_init(
	GOSTH_CTX *x,			/* контекст */
	const unsigned char *iv,	/* начальный вектор, 32 байта */
	int sbox			/* идентификатор узлов замены */
	);
/*
 *	КриптоПро совместимая инициализация хэширования
 *	(должна использоваться, если данные могут быть нулевой длины)
 */
int 
WINAPI 
CP_GOSTH_hash_init(
	GOSTH_CTX *x,			/* контекст */
	const unsigned char *iv,	/* начальный вектор, 32 байта */
	int sbox			/* идентификатор узлов замены */
	);
/*
 *	Инициализация хэширования
 *	(устаревшая функция)
 */
int 
WINAPI 
GOSTH_init(
	GOSTH_CTX *ctx,
	unsigned char *h0, 
	unsigned char *sbox
	);
/*
 *	КриптоПро совместимая инициализация хэширования
 */
int 
WINAPI 
CP_GOSTH_init(
	GOSTH_CTX *ctx,
	unsigned char *h0, 
	unsigned char *sbox
	);
/*
 *	Хэширования данных
 */
int 
WINAPI 
GOSTH_update(
	GOSTH_CTX *ctx,			/* контекст */ 
	unsigned char *data,		/* данные */
	int nbytes			/* длина данных в байтах */
	);
/*
 *	Получение хэш-значения
 */
int 
WINAPI 
GOSTH_final(
	GOSTH_CTX *ctx,			/* контекст */
	unsigned char *md		/* буфер для хэш-значения, 32 байта */
	);
/*
 *	Хэширование данных
 */
unsigned char * 
WINAPI 
GOSTH(
	 unsigned char *d,		/* данные */
	 int n,				/* число байт */
	 unsigned char *h0, 
	 unsigned char *sbox, 
	 unsigned char *md
	 );

/*
 *	Вычисляет хэш-значение для заданного файла
 */
unsigned char * 
WINAPI 
GOSTH_file_digest(
	unsigned char *fname, 
	unsigned char *md, 
	int sbox
	);
				  
/*
 *	Инициализация ГОСТ 28147-89 в режиме 
 *	гаммирования с обратной связью 
 *	(будет использован алгоритм key meshing: GOSTE_MODE_MESH)
 */
int 
WINAPI 
CP_GOSTE_gamma_fb_init(
	GOSTE_CTX *x, 
	const unsigned char *key, 
	const unsigned char *sync, 
	const unsigned char *sbox
	);
/*
 *	Зашифрование
 */
int 
WINAPI 
CP_GOSTE_gamma_fb_encrypt(
	GOSTE_CTX *x, 
	unsigned char *in, 
	unsigned char *out, 
	int nbytes
	);
/*
 *	Расшифрование
 */
int 
WINAPI 
CP_GOSTE_gamma_fb_decrypt(
	GOSTE_CTX *x, 
	unsigned char *in, 
	unsigned char *out, 
	int nbytes);
/*
 *	Инициализация ГОСТ 28147-89 в режиме 
 *	выработки имитовставки 
 *	(будет использован алгоритм key meshing: GOSTE_MODE_KEY_MESH)
 */
int 
WINAPI 
CP_GOSTE_mac_init(
	GOSTE_CTX *x, 
	const unsigned char *key,
	const unsigned char *sync, 
	const unsigned char *sbox
	);
/*
 *	Обработка данных
 */
int 
WINAPI 
CP_GOSTE_mac_update(
	GOSTE_CTX *x, 
	unsigned char *in, 
	int nbytes
	);
/*
 *	Получение имитовставки
 */
int 
WINAPI 
CP_GOSTE_mac_final(
	GOSTE_CTX *x, 
	unsigned char *mac, 
	int nbits			/* число бит 1...32 */
	);
/*
 *	Диверсификация ключа
 */
unsigned char * 
WINAPI 
CP_GOSTE_key_diversify(
	unsigned char *ukm, 
	unsigned char *key, 
	unsigned char *out, 
	unsigned char *sbox
	);
/*
 *	Key meshing
 */
int 
WINAPI 
CP_GOSTE_key_mesh(
	GOSTE_CTX *x			/* контекст шифрования */
	);


/*
 *	Инициализация библиотеки
 */
void 
WINAPI 
CADB_init(
	void
	);
/*
 *	Завершение работы с библиотекой
 */
void 
WINAPI 
CADB_close(
	void
	);

/*
 *	Установка кода ошибки
 *	может использоваться для сброса (code = 0)
 */
void 
WINAPI 
ERR_set_last_error(
	unsigned long code
	);
/*
 *	Получение кода ошибки
 */
unsigned long 
WINAPI 
ERR_get_last_error(
	void
	);
/*
 *	Очистка стека ошибок
 */
void 
WINAPI 
ERR_remove_state(
	unsigned long pid		/* если 0 - текущий поток */
	);
/*
 *	Печать стека ошибок в поток
 */
void 
WINAPI 
ERR_print_errors_fp(
	FILE *fp
	);
/*
 *	Печать стека ошибок в файл
 */
void 
WINAPI 
ERR_print_errors_file(
	char *fname
	);
/*
 *	Печать стека ошибок в буфер
 *	Буфер выделяется динамически и должен быть освобожден!
 */
unsigned char * 
WINAPI 
ERR_get_errors(
	void
	);
/*
 *	Чтение ключевого контейнера
 */
void * 
WINAPI 
PSE_init(
	char *privpath, 
	char *masks, 
	int mlen, 
	int sbox
	);
/*
 *	Освобождение ключевого контейнера
 */
void 
WINAPI 
PSE_close(
	void *pse
	);
/*
 *	Генерация KEK
 */
int 
WINAPI 
PSE_generate_kek(
	void *x, 
	char *buf
	);
/*
 *	Загрузка KEK
 */
int 
WINAPI 
PSE_load_kek(
	void *x, 
	unsigned char *buf
	);
/*
 *	Генерация и маскирование главного ключа
 */
int 
WINAPI 
PSE_generate_mkey(
	char *path, 
	unsigned char *masks, 
	int *mlen, 
	int sbox
	);
/*
 *	Инициализация аппаратного ГСЧ
 */
int 
WINAPI 
PSE_rand_init_hardware(
	unsigned char *types
	);
/*
 *	Инициализация программного ГСЧ от аппаратного
 */
int 
WINAPI 
PSE_pseudo_rand_init_hardware(
	unsigned char *types
	);
/*
 *	Инициализация программного ГСЧ
 */
int 
WINAPI 
PSE_pseudo_rand_init(
	void *x, 
	char *buf, 
	int *save, 
	int (WINAPI *rand_callback)(int,int,int,void *), 
	char *userdata
	);
/*
 *	Проверка состояния ГСЧ
 */
int 
WINAPI 
PSE_rand_inited(
	void
	);
/*
 *	Получение типа ГСЧ
 */
int 
WINAPI 
PSE_get_rand_type(
	void
	);
/*
 *	Сохранение вектора состояния ГСЧ
 */
int 
WINAPI 
PSE_rand_save_state(
	void *x, 
	char *buf
	);
/*
 *	Очистка контекста ГСЧ и выключение
 */
void 
WINAPI 
PSE_rand_close(
	void
	);
/*
 *	Получение типа аппаратного ГСЧ
 */
int 
WINAPI 
PSE_get_hwrand_type(
	void
	);


/*
 *	Создание контекста ключевого контейнера
 */
PSE_CTX * 
WINAPI 
PSE_CTX_new(
	void
	);
/*
 *	Освобождение контекста ключевого контейнера
 */
void 
WINAPI 
PSE_CTX_free(
	PSE_CTX *x
	);
/*
 *	Получение ключевого контейнера
 *	Возвращает PSE
 */
void * 
WINAPI 
PSE_CTX_get_pse(
	void *x			/* PSE_CTX */
	);
/*
 *	Установка числа масок главного ключа
 */
int 
WINAPI 
PSE_CTX_set_masks_num(
	void *_x, 
	int num
	);
/*
 *	Установка базового пути к ключевому контейнеру
 */
int 
WINAPI 
PSE_CTX_set_path(
	PSE_CTX *x, 
	char *path, 
	int len
	);

#define PSE_CTX_set_buf_path(x, buf, len)	PSE_CTX_set_path((x), (buf), (len))

/*
 *	Установка ф-ии обратного вызова для инициализации ГСЧ
 */
int 
WINAPI 
PSE_CTX_set_rand_callback(
	PSE_CTX *x, 
	int (WINAPI *cb)(int c, int step, int from, void *u)
	);
/*
 *	Установка ф-ии обратного вызова для ввода пароля
 *	(не используется в Крипто-КОМ)
 */
int 
WINAPI 
PSE_CTX_set_passwd_callback(
	PSE_CTX *x, 
	int (*cb)(char *buf, int num, int w, void *u)
	);
/*
 *	Установка пользовательских данных для пароля
 */
int 
WINAPI 
PSE_CTX_set_user_data(
	PSE_CTX *x, 
	void *userdata);	/* passwd_callback */
/*
 *	Установка пользовательских данных инициализации ГСЧ
 */
int 
WINAPI 
PSE_CTX_set_rand_user_data(
	PSE_CTX *x, 
	void *userdata
	);
/*
 *	Установка данных для eToken
 */
int 
WINAPI 
PSE_CTX_set_etoken(
	PSE_CTX *x, 
	char *pin, 
	int len, 
	long flags
	);
/*
 *	Установка пароля
 *	(не используется в Крипто-КОМ)
 */
int 
WINAPI 
PSE_CTX_set_passwd(
	PSE_CTX *x, 
	char *passwd, 
	int len
	);
/*
 *	Установка пути к главному ключу
 */
int 
WINAPI 
PSE_CTX_set_mk_path(
	PSE_CTX *x, 
	char *path, 
	int len
	);
/*
 *	Установка пути к мфскам главного ключа
 */
int 
WINAPI 
PSE_CTX_set_masks_path(
	PSE_CTX *x, 
	char *path, 
	int len
	);
/*
 *	Установка пути к KEK
 */
int 
WINAPI 
PSE_CTX_set_kek_path(
	PSE_CTX *x, 
	char *path, 
	int len
	);
/*
 *	Установка пути к вектору состояния ГСЧ
 */
int 
WINAPI 
PSE_CTX_set_rand_path(
	PSE_CTX *x, 
	char *path, 
	int len
	);
/*
 *	Установка главного ключа
 */
int 
WINAPI 
PSE_CTX_set_mkey(
	PSE_CTX *x, 
	char *buf, 
	int len
	);
/*
 *	Установка масок главного ключа
 */
int 
WINAPI 
PSE_CTX_set_masks(
	PSE_CTX *x, 
	char *buf, 
	int len
	);

/*
 *	Установка KEK
 */
int 
WINAPI 
PSE_CTX_set_kek(
	PSE_CTX *x, 
	char *buf, 
	int len
	);
/*
 *	Установка вектора состояния ГСЧ
 */
int 
WINAPI 
PSE_CTX_set_rand(
	PSE_CTX *x, 
	char *buf, 
	int len
	);
/*
 *	Установка узлов замены (может использоваться только при генерации PSE)
 */
int 
WINAPI 
PSE_CTX_set_sbox(
	void *_x,
	int id
	);
/*
 *	Получение главного ключа
 */
int 
WINAPI 
PSE_CTX_get_mkey(
	PSE_CTX *x, 
	char *buf, 
	int *len
	);
/*
 *	Получение масок главного ключа
 */
int 
WINAPI 
PSE_CTX_get_masks(
	PSE_CTX *x, 
	char *buf, 
	int *len
	);
/*
 *	Получение KEK
 */
int 
WINAPI 
PSE_CTX_get_kek(
	PSE_CTX *x, 
	char *buf, 
	int *len
	);
/*
 *	Получение вектора состояния ГСЧ
 */
int 
WINAPI 
PSE_CTX_get_rand(
	PSE_CTX *x, 
	char *buf, 
	int *len
	);
/*
 *	Генерация ключевого контейнера
 */
int 
WINAPI 
PSE_CTX_generate(
	PSE_CTX *x
	);
/*
 *	Сохранение ключевого контейнера
 */
int 
WINAPI 
PSE_CTX_write(
	PSE_CTX *x
	);
/*
 *	Чтение ключевого контейнера
 */
int 
WINAPI 
PSE_CTX_read(
	PSE_CTX *x
	);

/*
 *	Создание структуры для хранения секретного ключа
 */
OPAQUE_PRIV_KEY * 
WINAPI 
OPAQUE_PRIV_KEY_new(
	void
	);
/*
 *	Освобождение структуры для хранения секретного ключа
 */
void 
WINAPI 
OPAQUE_PRIV_KEY_free(
	OPAQUE_PRIV_KEY *x
	);
/*
 *	Получение зашифрованного секретного ключа
 */
void * 
WINAPI 
OPAQUE_PRIV_KEY_get_priv_key(
	OPAQUE_PRIV_KEY *x
	);
/*
 *	Получение имитовставки от секретного ключа
 */
void * 
WINAPI 
OPAQUE_PRIV_KEY_get_mac(
	OPAQUE_PRIV_KEY *x
	);

/*
 *	Установка функции обратного вызова для ввода пароля 
 *	к eToken
 */
void 
WINAPI 
ETOKEN_set_passwd_callback(
	int (*cb)(char *,int,int,void *)
	);
/*
 *	Установка информационной функции обратного вызова для 
 *	Touch Memory
 */
void 
WINAPI 
TOUCH_MEMORY_set_info_callback(
	int (*cb)(short, short, short)
	);

/*
 *	Инвертирование данных	
 */
void * 
WINAPI 
CCLIB_invert(
	void *m,	/* указатель на данные */
	int l		/* длина в байтах */
	);

/* Test functions */
int WINAPI GOSTE_test(void);
int WINAPI GOSTH_test(void);
int WINAPI GOSTS_test(void);
int WINAPI GOSTS_DH_test(void);
int WINAPI GOSTS_EG_test(void);
int WINAPI ECGOST_test(void);
int WINAPI ECGOST_DH_test(void);
int WINAPI CCLIB_test_all(void);

/* Check functions */
int WINAPI GOSTE_simple_subst_check(void *ctx);
int WINAPI GOSTE_gamma_check(void *ctx);
int WINAPI GOSTE_gamma_fb_check(void *ctx);
int WINAPI GOSTE_mac_check(void *ctx);
int WINAPI GOSTH_check(void *ctx);

int WINAPI GOSTS_sign_check(void *ctx);
int WINAPI GOSTS_verify_check(void *ctx);
int WINAPI GOSTS_DH_check(void *dh);
int WINAPI GOSTS_EG_check(void *dh);
int WINAPI ECGOST_check(void *_ec);
#define ECGOST_sign_check(e)	ECGOST_check((e))
int WINAPI ECGOST_check_verify(void *_ec);
int WINAPI ECGOST_DH_check(void *dh);

int WINAPI CCLIB_check_ram(void *buf, int len);
int WINAPI CCLIB_check_environment(void);

/* Auxilary functions */
void WINAPI CCLIB_display(char *head, unsigned char *buf, int ln);
void WINAPI CCLIB_display_c(char *head, unsigned char *buf, int ln);
void WINAPI CCLIB_display_byte(char *head, unsigned char *buf, int ln);

void WINAPI CCLIB_dump(char *head, unsigned char *buf, int ln);
void WINAPI CCLIB_dump_fp(void *fp, char *head, unsigned char *buf, int ln);

int WINAPI CCOM_init(void);
void WINAPI CCOM_close(void);

/*
 *	Отладочные функции
 */
void WINAPI CCOM_set_leaks_file(char *path);
void WINAPI CCOM_set_leaks_fp(void *fp);

/*
 *	Освобождение памяти
 */
void WINAPI CCLIB_mem_free(void *ptr);
/*
 *	Освобождение памяти с очисткой
 */
void WINAPI CCLIB_mem_clear_free(void *ptr, int len);

/* Parameters */
unsigned char * WINAPI GOSTS_get_p_parameter(void);
unsigned char * WINAPI GOSTS_get_q_parameter(void);
unsigned char * WINAPI GOSTS_get_a_parameter(void);
unsigned char * WINAPI GOSTS_get_test_p_parameter(void);
unsigned char * WINAPI GOSTS_get_test_q_parameter(void);
unsigned char * WINAPI GOSTS_get_test_a_parameter(void);
unsigned char * WINAPI GOSTS_get_dh_p_parameter(void);
unsigned char * WINAPI GOSTS_get_dh_a_parameter(void);
unsigned char * WINAPI GOSTE_get_sbox(void);
unsigned char * WINAPI GOSTH_get_sbox(void);
unsigned char * WINAPI GOSTH_get_test_sbox(void);
unsigned char * WINAPI CCLIB_get_copyright(void);
unsigned char * WINAPI CCLIB_get_lastupdate(void);
unsigned char * WINAPI GOSTH_nid2sbox(int nid);
unsigned char * WINAPI GOSTE_nid2sbox (int nid);

unsigned char * WINAPI CP_GOSTH_get_sbox(void);
unsigned char * WINAPI CP_GOSTE_get_sbox(void);
int  WINAPI CP_GOSTE_set_sbox(int nid);
unsigned char * WINAPI CP_GOSTE_get_sbox_A(void);
unsigned char * WINAPI CP_GOSTE_get_sbox_B(void);
unsigned char * WINAPI CP_GOSTE_get_sbox_C(void);
unsigned char * WINAPI CP_GOSTE_get_sbox_D(void);
unsigned char * WINAPI CP_GOSTE_nid2sbox(int nid);
int  WINAPI CP_GOSTE_sbox2nid(unsigned char *sbox);
unsigned char * WINAPI CP_R3410_get_p_parameter(int set);
unsigned char * WINAPI CP_R3410_get_q_parameter(int set);
unsigned char * WINAPI CP_R3410_get_a_parameter(int set);

#ifdef  __cplusplus
}
#endif
#endif	/* _CCOM_H */


