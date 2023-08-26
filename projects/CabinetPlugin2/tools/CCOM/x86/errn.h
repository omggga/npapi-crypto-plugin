/*
* $Revision: 1.5 $
* $Date: 2012/10/06 12:39:23 $
* crypto/err/errn.h
*/

#ifndef _HEADER_ERRN_H
#define _HEADER_ERRN_H

/* 
*	Коды ошибок
*/
#define E_OK						0	/* нет ошибок */
#define E_PARAMS					1	/* ошибка при задании параметров */
#define E_IO						2	/* ошибка ввода/вывода */
#define E_INVALID_MAC				3	/* ошибка при проверке MAC */
#define E_RNG_NOT_INITED			4	/* генератор случайных чисел не инициализирован */
#define E_PSE_CORRUPT				5	/* ошибка чтения ключевого контейнера */
#define E_RNG						6	/* ошибка генератора случайных чисел */
#define E_SIGNATURE_FAILURE			7	/* цифровая подпись не подтверждена */
#define E_PRIV_KEY					8	/* ошибка чтения приватного ключа */
#define E_UALG						9	/* неизвестный идентификатор алгоритма */
#define E_UMODE						10	/* неизвестный режим */
#define E_MALLOC					11	/* ошибка выделения памяти */
#define E_INTERNAL					12	/* внутренняя ошибка */
#define E_UPARAMS					13	/* неизвестный идентификатор параметров */
#define E_KEY_GEN					14	/* ошибка при генерации ключа */
#define E_VERIFY					15	/* ошибка при проверке подписи */
#define E_SIGN						16	/* ошибка при формировании подписи */
#define E_PUB_KEY					17	/* ошибка чтения открытого ключа */
#define E_SEC_KEY					18	/* ошибка чтения секретного ключа */
#define E_KEYS_MISMATCH				19	/* несоответствие ключей */
#define E_UFORMAT					20	/* неизвестный формат */
#define E_UENCODING					21	/* неизвестная кодировка */
#define E_CANCELED					22	/* операция прервана */
#define E_READ						23	/* ошибка чтения файла */
#define E_WRITE						24	/* ошибка записи файла */
#define E_NOT_FOUND					25	/* файл не найден */
#define E_EXISTS					26	/* файл существует */
#define E_LOCK						27	/* ошибка блокировки */
#define E_ACCESS					28	/* ошибка доступа */
#define E_BUSY						29	/* файл/устройство занято */	
#define E_NOT_SUPPORTED				30	/* операция не поддерживается */
#define E_ENCODE					31	/* ошибка при кодировании */
#define E_DECODE					32	/* ошибка при декодировании */
#define E_ENCRYPT					33	/* ошибка при зашифровании */
#define E_DECRYPT					34	/* ошибка при расшифровании */
#define E_COMPRESS					35	/* ошибка при компресии */
#define E_DECOMPRESS				36	/* ошибка при декомпрессии */
#define E_NOT_SIGNED				37	/* не обнаружена подпись */
#define E_NOT_ENCRYPTED				38	/* данные не зашифрованы */
#define E_NOT_AUTHENTICATED			39	/* данные не аутентифицированы */
/* 40-50 зарезервированы */
#define E_UNKNOWN_CA				51	/* не найден ключ доверенного CA */
#define E_PRIV_KEY_NOT_FOUND		52	/* не найден приватный ключ */	
#define E_CERT_NOT_FOUND			53	/* не найден сертификат */
#define E_CRL_NOT_FOUND				54	/* не найден CRL */
#define E_PRIV_KEY_NOT_VALID		55	/* приватный ключ недействителен */	
#define E_CERT_NOT_VALID			56  /* сертификат недействителен */
#define E_CERT_EXPIRED				57  /* период действия сертификата истек */
#define E_CRL_NOT_VALID				58	/* CRL недействителен */
#define E_CRL_EXPIRED				59	/* период действия CRL истек */
#define E_CERT_REVOKED				60	/* сертификат отозван */
#define E_CERT_UNSUPPORTED			61	/* неподдерживаемый тип сертификата */
#define E_CERT_VERIFY				62	/* ошибка при проверке подписи сертификата */
#define E_CRL_VERIFY				63	/* ошибка при проверке подписи CRL */
/* 64-70 зарезервированы */
#define E_CONNECT					71	/* ошибка при установлении исходящего соединения */
#define E_ACCEPT					72	/* ошибка при установлении входящего соединения */
#define E_TIMEOUT					73	/* таймаут */
#define E_INVALID_ADDRESS			74	/* неверный адрес */
#define E_ABORTED					75	/* соединение разорвано */
#define E_SSL_CONNECT				76	/* ошибка при установлении исходящего SSL-соединения */
#define E_SSL_ACCEPT				77	/* ошибка при установлении входящего SSL-соединения */
#define E_SSL_HANDSHAKE				78	/* ошибка при SSL-рукопожатии */
#define E_SSL_READ					79	/* ошибка чтения данных SSL */
#define E_SSL_WRITE					80	/* ошибка записи данных SSL */
#define E_SSL_CLOSE_NOTIFY			81	/* SSL-соединение завершено */	
#define E_SHARED_CIPHER				82	/* ошибка согласования набора алгоритмов */
#define E_CERT_TYPE					83	/* ошибочный тип сертификата */
#define E_CERT_USAGE				84	/* ошибочное назначение сертификата */
#define E_AUTHENTICATION			85	/* ошибка аутентификации */
#define E_AUTHENTICATION_REQUIRED	86	/* требуется аутентификация */		
#define E_PROTOCOL					87	/* ошибочный протокол */
#define E_PROTOCOL_VERSION			88	/* ошибочная версия протокола */
#define E_UNEXPECTED_MESSAGE		89	/* неожиданное сообщение */
#define E_OVERFLOW					90	/* переполнение данных */
#define E_ILLEGAL_STATE				91	/* операция не готова к выполнению */

#endif	/* _HEADER_ERRN_H */

