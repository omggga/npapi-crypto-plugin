#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


// ����� ����� � �������������: 


#include "..\_cpp\CabinetDefs.h"
#include "..\_cpp\CabinetDefs.h"
#include "..\_cpp\Ufml3Defs.h"
#include "..\_cpp\SlotGlossary.h"



// -----------------------------------------------------------------------------------------------
// {{ ��������� ����������

// ----
// Protocol: ����� �����������

#ifndef _EVT_LOG_NAME
#define _EVT_LOG_NAME __NAME
#endif

#ifndef _PROTOCOL_PROJECT_NAME
#define _PROTOCOL_PROJECT_NAME (_T("Protocol"))
#endif

#ifndef _PROTOCOL_PROJECT_DESCRIPTION
#define _PROTOCOL_PROJECT_DESCRIPTION (L"���� [] - ������� ������ �������")
#endif

#ifndef _PROTOCOL_MODULE_FILENAME
#define _PROTOCOL_MODULE_FILENAME (_S(_PROTOCOL_PROJECT_NAME) + _T("App.dll"))
#endif

#ifndef _PROTOCOL_FACILITY
#define _PROTOCOL_FACILITY _PROTOCOL_PROJECT_NAME
#endif

#ifndef _PROTOCOL_EVENT_SOURCE
#define _PROTOCOL_EVENT_SOURCE _PROTOCOL_PROJECT_NAME
#endif

#ifndef _PROTOCOL_SYSMSG_DLL
#define _PROTOCOL_SYSMSG_DLL (_PROTOCOL_PROJECT_NAME + _S("SysMsg.dll"))
#endif

#ifndef FACILITY_PROTOCOL // �� ��������� ���������� �����������
#define FACILITY_PROTOCOL 0xAFA
#endif

#ifndef _AUTO_REG_PROTO_DEFAULTS
// #define _AUTO_REG_PROTO_DEFAULTS 1
#endif

#ifndef _PROTOCOL_PERFORM_APP_FEATURES_AUTO_REGISTRATION
#define _PROTOCOL_PERFORM_APP_FEATURES_AUTO_REGISTRATION 1
#endif

// ���������� ������� ������ � �����
#ifndef _SYS_INFO_DETAILED
#define _SYS_INFO_DETAILED 0
#endif



// ----
// ���� []

#ifndef _PROTOCOL_PROTO_NAME
#define _PROTOCOL_PROTO_NAME (L"")
#endif

#ifndef _PROTOCOL_PREFIX
#define _PROTOCOL_PREFIX (_PROTOCOL_PROTO_NAME + _W(L"://"))
#endif

#ifndef _PUBLIC_CABINET_REQUEST_NSURI
#define _PUBLIC_CABINET_REQUEST_NSURI (L"http://cabinet.example.com/schema/-cabinet/rel-1/")
#endif

#ifndef _SLOTREQUEST_NSURI
#define _SLOTREQUEST_NSURI (L"urn::slot-request")
#endif

#ifndef _SLOT_SYSMSG_NSURI
#define _SLOT_SYSMSG_NSURI (L"urn::sysmsg")
#endif


#ifdef TRACE_LOG_PREFIX
#error ! macro TRACE_LOG_PREFIX already defined
#endif
#ifdef TRACE_LOG_PREFIX_TEXT
#error ! macro TRACE_LOG_PREFIX already defined
#endif
//
#define TRACE_LOG_PREFIX_TEXT _S(_PROTOCOL_PROTO_NAME)
#define TRACE_LOG_PREFIX (_S("[") + TRACE_LOG_PREFIX_TEXT +_T("] "))


#ifndef _KEY_ENCRYPT_METHOD_DUMMY
#define _KEY_ENCRYPT_METHOD_DUMMY 1
#endif

#ifndef _KEY_ENCRYPT_METHOD_ENC_RSA
#define _KEY_ENCRYPT_METHOD_ENC_RSA 7
#endif

#define _KEY_ENCRYPT_METHOD _KEY_ENCRYPT_METHOD_ENC_RSA

// #define _KEY_FOR_CABINET_SERVER 1 

#ifndef _OC_TIMEOUT_CCI
#define _OC_TIMEOUT_CCI (5)
#endif

#ifndef _OC_TIMEOUT_TOKEN_OBJ
#define _OC_TIMEOUT_TOKEN_OBJ (5)
#endif

#ifndef _OC_TIMEOUT_PR_PATH
#define _OC_TIMEOUT_PR_PATH (3)
#endif





// ----
// ������ ������� ������ ������� 

#ifndef _PROTOCOL_DEFAULT_HOST
#define _PROTOCOL_DEFAULT_HOST (L"cabinet.example.com")
#endif

#ifndef _PROTOCOL_DEFAULT_PORT
#define _PROTOCOL_DEFAULT_PORT (443)
#endif



// ----
// UrlCache

#ifndef _URL_CACHE_DEFAULT_URL_BEGIN
#define _URL_CACHE_DEFAULT_URL_BEGIN (_W(_PROTOCOL_PREFIX) + _PROTOCOL_DEFAULT_HOST + L"/")
#endif



// ----
// Web

#ifndef _HTTP_STATUS_UNKNOWN
#define _HTTP_STATUS_UNKNOWN (0)
#endif

#ifndef _PROTOCOL_RSP_HEADER_STATUS_TEXT
#define _PROTOCOL_RSP_HEADER_STATUS_TEXT (L"__status-text__")
#endif

#ifndef _PROTOCOL_RSP_HEADER_RECEIPT_NEEDED
#define _PROTOCOL_RSP_HEADER_RECEIPT_NEEDED (L"X--ReceiptNeeded")
#endif



// ----
// Handlers

#ifndef _PROTOCOL_PROGID_APP
#define _PROTOCOL_PROGID_APP (L"ProtocolApp")
#endif

#ifndef _PROTOCOL_PROGID_APP_V10
#define _PROTOCOL_PROGID_APP_V10 (L"Proto")
#endif

#ifndef _PROTOCOL_PROGID_SecurityHandler
#define _PROTOCOL_PROGID_SecurityHandler (_W(_PROTOCOL_PROGID_APP) + L".SecurityHandler")
#endif

#ifndef _PROTOCOL_PROGID_SecurityHandler_V10
#define _PROTOCOL_PROGID_SecurityHandler_V10 (_W(_PROTOCOL_PROGID_APP_V10) + L".SecurityHandler")
#endif

#ifndef _PROTOCOL_CLIENT_PKH_PARAM
#define _PROTOCOL_CLIENT_PKH_PARAM (L"client-pkh")
#endif

#ifndef _PROTOCOL_ETOKEN_KEY_MODE
#define _PROTOCOL_ETOKEN_KEY_MODE (1)
#endif

#ifndef _PROTOCOL_ETOKEN_KEY_G_MODE
#define _PROTOCOL_ETOKEN_KEY_G_MODE (2)
#endif

#ifndef _DEFAULT_ERR_MEDIA_TYPE
#define _DEFAULT_ERR_MEDIA_TYPE (L"text/xml")  
#endif

#ifndef _OID
#define _OID (L"1.2.643.6.2") 
#endif 



// ----
// �����������

// ���������� ������ ���������� �������� ����������� (������)
#ifndef _PROTOCOL_SPECIAL_REGISTER
#define _PROTOCOL_SPECIAL_REGISTER 1 // TODO: ��������� 0 
#endif



// ----
// XmlContext

#ifndef _PROTOCOL_CONFIG_TAG
#define _PROTOCOL_CONFIG_TAG (L"ProtocolConfig")
#endif

// }} ��������� ����������
// -----------------------------------------------------------------------------------------------






