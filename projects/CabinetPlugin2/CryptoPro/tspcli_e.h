//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define FACILITY_TSPCLI                  0x210


//
// Define the severity codes
//


//
// MessageId: TSPCLI_ERROR_HTTP
//
// MessageText:
//
// HTTP error occurred while sending request
//
#define TSPCLI_ERROR_HTTP                0xC2100100L

//
// MessageId: TSPCLI_ERROR_PolicyDeniedAuthType
//
// MessageText:
//
// Specified authentication type prohibited by group policy
//
#define TSPCLI_ERROR_PolicyDeniedAuthType 0xC2100101L

//
// MessageId: TSPCLI_ERROR_PolicyDeniedProxyAuthType
//
// MessageText:
//
// Specified proxy authentication type prohibited by group policy
//
#define TSPCLI_ERROR_PolicyDeniedProxyAuthType 0xC2100102L

//
// MessageId: TSPCLI_ERROR_PolicyDeniedURL
//
// MessageText:
//
// Specified time-stamp authority prohibited by group policy
//
#define TSPCLI_ERROR_PolicyDeniedURL     0xC2100103L

//
// MessageId: TSPCLI_ERROR_PolicyDeniedNonce
//
// MessageText:
//
// Nonce usage prohibited by group policy
//
#define TSPCLI_ERROR_PolicyDeniedNonce   0xC2100104L

//
// MessageId: TSPCLI_ERROR_PolicyDeniedHashAlg
//
// MessageText:
//
// Specified hash algorithm prohibited by group policy
//
#define TSPCLI_ERROR_PolicyDeniedHashAlg 0xC2100110L

//
// MessageId: TSPCLI_ERROR_PolicyDeniedPolicyID
//
// MessageText:
//
// Specified PolicyID prohibited by group policy
//
#define TSPCLI_ERROR_PolicyDeniedPolicyID 0xC2100111L

//
// MessageId: TSPCLI_ERROR_IncorrectNonce
//
// MessageText:
//
// The values of request's and stamp's "Nonce" fields are not equal.
//
#define TSPCLI_ERROR_IncorrectNonce      0xC2100120L

//
// MessageId: TSPCLI_ERROR_AddressIsEmpty
//
// MessageText:
//
// The URL of TSP service is not specified
//
#define TSPCLI_ERROR_AddressIsEmpty      0xC2100121L

//
// MessageId: TSPCLI_ERROR_ExpiredStamp
//
// MessageText:
//
// The time stamp is expired (ProducedAt value)
//
#define TSPCLI_ERROR_ExpiredStamp        0xC2100122L

//
// MessageId: TSPCLI_ERROR_DataHashIsEmpty
//
// MessageText:
//
// Request does not contain data hash
//
#define TSPCLI_ERROR_DataHashIsEmpty     0xC2100123L

//
// MessageId: TSPCLI_ERROR_UnsuccessfullResponse
//
// MessageText:
//
// TSA response is unsuccessfull
//
#define TSPCLI_ERROR_UnsuccessfullResponse 0xC2100124L

