/*
 SlotEToken.h : ������� ��� ������ � eToken ��� ������ ���������� CryptoCOM.

 $Name:  $
 $Revision: 1.1.2.2 $
 $Date: 2008/10/10 15:38:07 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

// CCOM
//
#ifdef WIN64
//#	include <tools/CCOM/x64/cc_3_2_9.h>
#	include <tools/CCOM/ccevp.h>
#else // WIN32
//#	include <tools/CCOM/ccom.h>
#	include "../tools/CCOM/x86/ccevp.h"
#endif
//
#include "../tools/CCOM/ccom_extra.h"
#include "../tools/eToken/pkcs11.h"
#include "../tools/eToken/eTSAPI.h"

// 
//
#include "../_cpp/SlotUtil.h"
#include "../_cpp/SlotAsn.h"
///#include <alg/Alg_1_8_8.h>
///#include <resources/er_slot.h>
#include "SmartXml.h"
#include "SmartPKI.h"
#include "SmartOC.h"
//#include <dialogs/SlotPswDialog.h>

#pragma comment(lib, "Winscard.lib" )


#define _ETOKEN_ROOT (L"f45d")
#define _ETOKEN_META_FILE_PREFIX (L"ff")
#define _ETOKEN_CNTDIR_PREFIX (L"a")
#define _ETOKEN_KEYDIR_PREFIX (L"b")
//
#define _ETOKEN_META_FILE (L"ff01")
////#define _ETOKEN_FREEMETA_FILE (L"ff06")
//
////#define _ETOKEN_PORT_START (0)
////#define _ETOKEN_PORT_EDGE (1)

#ifndef _MAX_TOKEN_SLOT 
#define _MAX_TOKEN_SLOT 1 
#endif 

#ifndef _ETOKEN_PATH_LEN
#define _ETOKEN_PATH_LEN (4)
#endif

////#ifndef _PRIVATE_META
////#define _PRIVATE_META (0)
////#endif
////
////#ifndef _FREE_META
////#define _FREE_META (1)
////#endif
////
#ifndef ETokenLabelDelim
#define ETokenLabelDelim (L",")
#endif
////
////#ifndef ETokenKeyMode_CCOMFS
////#define ETokenKeyMode_CCOMFS (1)
////#endif
////
////#ifndef ETokenKeyMode_PKCS11
////#define ETokenKeyMode_PKCS11 (2)
////#endif

#define _KEY_OBJ_I_FLAGS		0	// ��������� ����� ����� 
#define _KEY_OBJ_I_PASSWORD		1
#define _KEY_OBJ_I_PRVKEY		3

namespace  {



	// ===========================================================================================
	// PKCS#11 

	// ��������������� ������ eToken PKCS11 API
	
	struct PKCS11_eToken 
	{
		static const int NoSlotId = -1;

		int SlotId;

		bool LoggedIn; 

		CK_SESSION_HANDLE hSession; 

		void* pseCtx; 

		// string Pin; 

		inline void Clear()
		{
			SlotId = NoSlotId; 
			LoggedIn = false; 
			hSession = 0; 
			pseCtx = 0; 
		}

		PKCS11_eToken() 
		{
			Clear(); 
		}

		const PKCS11_eToken& operator =(const PKCS11_eToken& other) 
		{
			SlotId = other.SlotId;
			LoggedIn = other.LoggedIn; 
			hSession = other.hSession; 
			pseCtx = other.pseCtx; 
			//
			return other; 
		}

		PKCS11_eToken(const PKCS11_eToken& other) 
		{
			Clear(); 
			//
			operator =(other); 
		}

		inline void Disconnect() 
		{
			try
			{
				// ..... 
				//
				// Clear(); 
			}
			_Catch() 
		}

		~PKCS11_eToken() 
		{
			Disconnect(); 
		}

		inline bool IsPresent()
		{
			return SlotId == NoSlotId; 
		}
	};



	class PKCS11_Manager 
	{
	///private:
	public:
		SharedArray<PKCS11_eToken> PKCS11_eTokens; 

		PKCS11_eToken& PKCS11_eToken_BySlot(int slotId)
		{
			try
			{
				// Touch_eToken(slotId);
				//
				PKCS11_eToken& eToken = PKCS11_eTokens[slotId]; 
				//
				return eToken; 
			}
			_Catch() 
		}

		inline Map<int, int>& ThreadId_eToken_Glossary() 
		{
			static Map<int, int> s_Glossary; 
			return s_Glossary; 
		}

		inline void EnterContext(int slotId) 
		{
			try
			{ 
				int threadId = (int)GetCurrentThreadId();
				ThreadId_eToken_Glossary()[threadId] = slotId; 
			}
			_Catch() 
		}

		inline void ReleaseContext() 
		{
			try
			{ 
				int threadId = (int)GetCurrentThreadId();
				if (ThreadId_eToken_Glossary().ContainsKey(threadId)) 
				{
					ThreadId_eToken_Glossary().Remove(threadId); 
				}
			}
			_Catch() 
		}

		inline Map<int, string>& CtxPwdGlossary() 
		{
			static Map<int, string> s_CtxPwdGlossary; 
			return s_CtxPwdGlossary; 
		}

		inline void EnterCtxPwdContext(void* pseCtx, const string& p) 
		{
			try
			{ 
				int threadId = (int)GetCurrentThreadId();
				CtxPwdGlossary()[threadId] = p; 
				//
				// TODO !!!
				//
				//int r1 = PSE_CTX_set_passwd_callback(pseCtx, PKCS11_Manager::key_container_pwd_cb); 
				//if (r1 == 0)
				//{
				//	int e1 = ERR_get_last_error(); 
				//	string msg = FormatStr(L"Error in PSE_CTX_set_passwd_callback: %d", (int)e1 ); 
				//	throw MethodError(msg); 
				//}
			}
			_Catch() 
		}

		inline void ReleaseCtxPwdContext() 
		{
			try
			{ 
				int threadId = (int)GetCurrentThreadId();
				if (CtxPwdGlossary().ContainsKey(threadId))
				{
					CtxPwdGlossary().Remove(threadId); 
				}
			}
			_Catch() 
		}

		inline string ContextCtxPwd() 
		{
			try
			{
				int threadId = (int)GetCurrentThreadId();
				if (CtxPwdGlossary().ContainsKey(threadId))
				{
					return CtxPwdGlossary()[threadId]; 
				}
				else
				{
					throw MethodError(L"�������� ���������� ��������� ���������� �� ��������������� (TH)"); 
				}
			}
			_Catch() 
		}



		inline static int 
#			ifdef WIN64
			WINAPI 
#			else
#			endif
			key_container_pwd_cb(char *buf, int num, int w, void *u) 
		{
			try
			{
				CStringA p(PKCS11_Manager::Acquire().ContextCtxPwd());
				memcpy(buf, p.GetString(), p.GetLength());
				buf[p.GetLength()] = 0;
				//
				return p.GetLength(); 
			}
			_Catch() 
		}


	public:
		inline static CRITICAL_SECTION& CriticalSection() 
		{
			static bool crits_f = false;
			static CRITICAL_SECTION crits; 
			if (! crits_f)
			{
				InitializeCriticalSection(&crits); 
				crits_f = true;
			}
			return crits; 
		}

		class Lock
		{
		public:
			Lock()
			{
				EnterCriticalSection(&CriticalSection());
			}

			~Lock()
			{
				LeaveCriticalSection(&CriticalSection());
			}
		};

		inline static PKCS11_Manager& Acquire() 
		{
			static SharedPtr<PKCS11_Manager> pkcs11Ptr;
			//
			//!//Lock lock;
			//
			if (pkcs11Ptr.IsEmpty())
			{
				pkcs11Ptr = new PKCS11_Manager();
			}
			PKCS11_Manager& pkcs11 = *pkcs11Ptr;
			return pkcs11; 
		}

#		define PKCS11_Manager_() PKCS11_Manager::Acquire() 

	public:
		// ----
		// ������ 

		CString m_DllPath; 

		CK_FUNCTION_LIST_PTR	pFunctionList;

		CK_C_GetFunctionList	pGFL; 

	public:
		bool					wasInit; 

		HANDLE					hThread; 

		inline void Clear() 
		{
			m_DllPath = _T("etpkcs11.DLL"); 
			//
			/// f_C_GetFunctionList = NULL; 
			f_SAPI_GetTokenInfo = NULL;
			//
			pFunctionList = 0; 
			pGFL = 0; 
			wasInit = false; 
			hThread = 0; 
		}

		// ---- 
		// ����� ������� PKCS#11 

		static DWORD __stdcall TokenNotifyThread(void*) 
		{
			try
			{
				PKCS11_Manager& ET = Acquire(); 
				//
				while (true) 
				{
					DWORD slotId;
					int res = ET.pFunctionList->C_WaitForSlotEvent(0, &slotId, 0); 
					//
					if (res == CKR_OK) 
					{
						///displaysTokenInfo(slotId);
					}
					else 
					{
						OutputDebugStringW(L"\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
							L"!!!\n������ ��� ��������� ������� eToken"); 
						throw MethodError(L"������ ��� ��������� ������� eToken");  
					}
					//
					Sleep(100); 
				}
				return 0;
			}
			_Catch() // TODO: ���������������� ::Exception 
		}

		// ----
		// ������ 

		HINSTANCE ETSAPI_hLib; 

		typedef CK_RV (*t_SAPI_GetTokenInfo)(CK_SLOT_ID, CK_ATTRIBUTE_PTR, CK_ULONG);

		t_SAPI_GetTokenInfo f_SAPI_GetTokenInfo;

		typedef CK_RV (*t_SAPI_SetTokenName)(CK_SLOT_ID, CK_CHAR_PTR);

		t_SAPI_SetTokenName f_SAPI_SetTokenName;

		inline void LoadETSAPI()
		{
			try
			{
				CString path = _T("etsapi.dll"); 
				ETSAPI_hLib = LoadLibrary(path); 
				if (! ETSAPI_hLib) 
				{
					throw MethodInfoExc(L"������ eToken: ���������� " + _W(path) + L" �����������"); 
				}
				//
				(FARPROC&)f_SAPI_GetTokenInfo = GetProcAddress(ETSAPI_hLib, "SAPI_GetTokenInfo");
				if (! f_SAPI_GetTokenInfo) 
				{
					throw MethodInfoExc(L"������ eToken: function: SAPI_GetTokenInfo"); 
				}
				//
				(FARPROC&)f_SAPI_SetTokenName = GetProcAddress(ETSAPI_hLib, "SAPI_SetTokenName");
				if (! f_SAPI_SetTokenName) 
				{
					throw MethodInfoExc(L"������ eToken: function: SAPI_SetTokenName"); 
				}
			}
			_Catch() 
		}

		XmlElement OutName(XmlElement& E, const char* name) // starts attribute by name 
		{
			try
			{
				XmlDocument doc = E.OwnerDocument(); 
				XmlElement A = doc.CreateElement(L"",L"Attribute",L""); 
				//
				A.SetAttribute(L"Name",_W(_A(name))); 
				//
				E.AppendChild(A); 
				//
				return A; 
			}
			_Catch() 
		}

		BOOL CheckEmpty(CK_ATTRIBUTE* attr) // detect if attribute value is empty
		{
			try
			{
				if (attr->ulValueLen > 0) return FALSE;
				else return TRUE;
			}
			_Catch() 
		}

		void OutString(XmlElement& E,CK_ATTRIBUTE* attr,const char* name) // print attribute value as a string
		{ 
			try
			{
				XmlElement A = OutName(E,name);
				if (! CheckEmpty(attr)) 
				{
					A.InnerText() = _W(_A((const char*)attr->pValue));  
				}
				E.AppendChild(A); 
			}
			_Catch() 
		}

		void OutVersion(XmlElement& E,CK_ATTRIBUTE* attr,const char* name) // print attribute value as CK_VERSION
		{ 
			try
			{
				XmlElement A = OutName(E,name);
				if (! CheckEmpty(attr)) 
				{
					CK_VERSION* v = (CK_VERSION*)attr->pValue;
					A.SetAttribute(L"Major",FormatStr(L"%d", v->major)); 
					A.SetAttribute(L"Minor",FormatStr(L"%d", v->minor)); 
				}
				E.AppendChild(A); 
			}
			_Catch() 
		}

		void OutDecimal(XmlElement& E,CK_ATTRIBUTE* attr,const char* name) // print attribute value as a decimal number
		{ 
			try
			{
				XmlElement A = OutName(E,name);
				if (! CheckEmpty(attr)) 
				{
					A.InnerText() = FormatStr(L"%d", *((int*)attr->pValue) ); 
					//
					// Specials 
					//
					if (attr->type == CKA_SAPI_COLOR) 
					{
						string color; 
						string cssColor; 
						//
						switch (*((int*)attr->pValue)) 
						{
						case CK_SAPI_COLOR_RED:
							color = L"red"; break; 
						case CK_SAPI_COLOR_BLUE:
							color = L"blue"; break; 
						case CK_SAPI_COLOR_GREEN:
							color = L"green"; break; 
						case CK_SAPI_COLOR_TANGERINE:
							color = L"tangerine"; cssColor = L"#FFA500"; break; 
						case CK_SAPI_COLOR_ICE:
							color = L"ice"; cssColor = L"#FEFEFF"; break; 
						case CK_SAPI_COLOR_PURPLE:
							color = L"purple"; cssColor = L"#800080"; break; 
						case CK_SAPI_COLOR_LIME:
							color = L"lime"; cssColor = L"#BFFF00"; break; 
						case CK_SAPI_COLOR_PINK:
							color = L"pink"; cssColor = L"#FFC0CB"; break; 
						case CK_SAPI_COLOR_BLACK:
							color = L"black"; break; 
						}
						//
						if (cssColor.GetLength() == 0) cssColor = color; 
						//
						if (color.GetLength() > 0) 
						{
							A.SetAttribute(L"Color", color); 
							A.SetAttribute(L"CssColor", cssColor); 
						}
					}
				}
				E.AppendChild(A); 
			}
			_Catch() 
		}

		void OutHex(XmlElement& E,CK_ATTRIBUTE* attr,const char* name)  // print attribute value as a hexadecimal number
		{ 
			try
			{
				XmlElement A = OutName(E,name); 
				if (! CheckEmpty(attr)) 
				{
					A.InnerText() = FormatStr(L"%d", int(*((unsigned int*)attr->pValue)) ); 
					A.SetAttribute(L"Hex", FormatStr(L"0x%08x", int(*((unsigned int*)attr->pValue)) )); 
				}
				E.AppendChild(A); 
			}
			_Catch() 
		}

		void OutDate(XmlElement& E,CK_ATTRIBUTE* attr,const char* name)  // print attribute value as CK_DATE
		{ 
			try
			{
				XmlElement A = OutName(E,name);
				if (! CheckEmpty(attr)) 
				{
					CK_DATE* d = (CK_DATE*)attr->pValue; 
					string dateStr = FormatStr(L"%c%c.%c%c",
						d->day[0], d->day[1], 
						d->month[0], d->month[1] 
						) 
					+ FormatStr(L".%c%c%c%c", 
						d->year[0], d->year[1], d->year[2], d->year[3] 
						); 
					A.InnerText() = dateStr; 
				}
				E.AppendChild(A); 
			}
			_Catch() 
		}

		void OutArray(XmlElement& E, CK_ATTRIBUTE* attr, const char* name)  
			// print attribute value as an array of bytes
		{ 
			try
			{
				XmlElement A = OutName(E,name);
				if (! CheckEmpty(attr)) 
				{
					XmlDocument doc = E.OwnerDocument(); 
					//
					string hexStr = L""; 
					for (CK_ULONG i = 0; i < attr->ulValueLen; i++) 
					{
						hexStr += FormatStr(L"%02x", int(((BYTE*)(attr->pValue))[i]) ); 
						//
						XmlElement Byte_E = doc.CreateElement(L"",L"Byte",L""); 
						Byte_E.SetAttribute(L"Value",FormatStr(L"%u", int(((BYTE*)(attr->pValue))[i]) )); 
						A.AppendChild(Byte_E); 
					}
					A.InnerText() = hexStr; 
					A.SetAttribute(L"Hex",hexStr); 
				}
				E.AppendChild(A); 
			}
			_Catch() 
		}

		void OutBoolean(XmlElement& E,CK_ATTRIBUTE* attr, const char* name) // print boolean attribute value
		{ 
			try
			{
				XmlElement A = OutName(E,name);
				if (! CheckEmpty(attr)) 
				{
					A.InnerText() = _W(*((CK_BBOOL*)attr->pValue) ? L"true" : L"false"); 
				}
				E.AppendChild(A); 
			}
			_Catch() 
		}

		CK_ATTRIBUTE* FindAttr(CK_ATTRIBUTE* Template, int nTemplate, CK_ATTRIBUTE_TYPE type)
		{
			try
			{
				for (int i = 0; i < nTemplate; i++, Template++)
				{
					if (Template->type == type) return Template;
				}
				return NULL;
			}
			_Catch() 
		}

		void ReadTokenInfo_SAPI(XmlElement& eToken_E,CK_SLOT_ID SlotID)
		{
			try
			{
				char product_name[256];
				char model[256];
				char hw_internal[256];
				char card_id[256];
				char serial[256];
				//
				CK_ULONG fw_revision;
				CK_ULONG case_model;
				CK_ULONG token_id;
				CK_ULONG card_type;
				CK_ULONG color;
				//
				CK_VERSION fw_version;
				CK_VERSION hw_version;
				CK_VERSION card_version;
				//
				CK_DATE production_date;
				//
				CK_BBOOL has_battery;
				CK_BBOOL has_lcd;
				CK_BBOOL has_user;
				CK_BBOOL has_so;
				CK_BBOOL fips;
				CK_BBOOL fips_supported;
				CK_BBOOL init_pin_req;
				CK_BBOOL rsa_2048;
				CK_BBOOL rsa_2048_supported;
				CK_BBOOL hmac_sha1;
				CK_BBOOL hmac_sha1_supported;
				CK_BBOOL real_color;
				CK_BBOOL may_init;
				//
				// template declaration
				CK_ATTRIBUTE Template[] = 
				{
					{CKA_SAPI_PRODUCT_NAME,        product_name,         sizeof(product_name)},
					{CKA_SAPI_MODEL,               model,                sizeof(model)},
					{CKA_SAPI_FW_VERSION,          &fw_version,          sizeof(CK_VERSION)},
					{CKA_SAPI_FW_REVISION,         &fw_revision,         sizeof(CK_ULONG)},
					{CKA_SAPI_HW_VERSION,          &hw_version,          sizeof(CK_VERSION)},
					{CKA_SAPI_HW_INTERNAL,         hw_internal,          sizeof(hw_internal)},
					{CKA_SAPI_PRODUCTION_DATE,     &production_date,     sizeof(CK_DATE)},
					{CKA_SAPI_CASE_MODEL,          &case_model,          sizeof(CK_ULONG)},
					{CKA_SAPI_TOKEN_ID,            &token_id,            sizeof(CK_ULONG)},
					{CKA_SAPI_CARD_ID,             card_id,              sizeof(card_id)},
					{CKA_SAPI_CARD_TYPE,           &card_type,           sizeof(CK_ULONG)},
					{CKA_SAPI_CARD_VERSION,        &card_version,        sizeof(CK_VERSION)},
					{CKA_SAPI_SERIAL,              serial,               sizeof(serial)},
					{CKA_SAPI_COLOR,               &color,               sizeof(CK_ULONG)},
					{CKA_SAPI_HAS_BATTERY,         &has_battery,         sizeof(CK_BBOOL)},
					{CKA_SAPI_HAS_LCD,             &has_lcd,             sizeof(CK_BBOOL)},
					{CKA_SAPI_HAS_USER,            &has_user,            sizeof(CK_BBOOL)},
					{CKA_SAPI_HAS_SO,              &has_so,              sizeof(CK_BBOOL)},
					{CKA_SAPI_FIPS,                &fips,                sizeof(CK_BBOOL)},
					{CKA_SAPI_FIPS_SUPPORTED,      &fips_supported,      sizeof(CK_BBOOL)},
					{CKA_SAPI_INIT_PIN_REQ,        &init_pin_req,        sizeof(CK_BBOOL)},
					{CKA_SAPI_RSA_2048,            &rsa_2048,            sizeof(CK_BBOOL)},
					{CKA_SAPI_RSA_2048_SUPPORTED,  &rsa_2048_supported,  sizeof(CK_BBOOL)},
					{CKA_SAPI_HMAC_SHA1,           &hmac_sha1,           sizeof(CK_BBOOL)},
					{CKA_SAPI_HMAC_SHA1_SUPPORTED, &hmac_sha1_supported, sizeof(CK_BBOOL)},
					{CKA_SAPI_REAL_COLOR,          &real_color,          sizeof(CK_BBOOL)},
					{CKA_SAPI_MAY_INIT,            &may_init,            sizeof(CK_BBOOL)},
				};
				//
				// size of template
				int nTemplate = sizeof(Template)/sizeof(CK_ATTRIBUTE);
				//
				// acquire all attributes
				if (CKR_OK != f_SAPI_GetTokenInfo(SlotID, Template, nTemplate)) 
				{
					throw MethodError(L"������: SAPI_GetTokenInfo");
				}
				//
				CK_ATTRIBUTE* attr;
				//
				// printing
				attr = FindAttr(Template, nTemplate, CKA_SAPI_PRODUCT_NAME);         OutString (eToken_E, attr, "CKA_SAPI_PRODUCT_NAME");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_MODEL);                OutString (eToken_E, attr, "CKA_SAPI_MODEL");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_FW_VERSION);           OutVersion(eToken_E, attr, "CKA_SAPI_FW_VERSION");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_FW_REVISION);          OutDecimal(eToken_E, attr, "CKA_SAPI_FW_REVISION");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_HW_VERSION);           OutVersion(eToken_E, attr, "CKA_SAPI_HW_VERSION");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_HW_INTERNAL);          OutArray  (eToken_E, attr, "CKA_SAPI_HW_INTERNAL");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_PRODUCTION_DATE);      OutDate   (eToken_E, attr, "CKA_SAPI_PRODUCTION_DATE");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_CASE_MODEL);           OutDecimal(eToken_E, attr, "CKA_SAPI_CASE_MODEL");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_TOKEN_ID);             OutHex    (eToken_E, attr, "CKA_SAPI_TOKEN_ID");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_CARD_ID);              OutArray  (eToken_E, attr, "CKA_SAPI_CARD_ID");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_CARD_TYPE);            OutDecimal(eToken_E, attr, "CKA_SAPI_CARD_TYPE");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_CARD_VERSION);         OutVersion(eToken_E, attr, "CKA_SAPI_CARD_VERSION");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_SERIAL);               OutArray  (eToken_E, attr, "CKA_SAPI_SERIAL");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_COLOR);                OutDecimal(eToken_E, attr, "CKA_SAPI_COLOR");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_HAS_BATTERY);          OutBoolean(eToken_E, attr, "CKA_SAPI_HAS_BATTERY");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_HAS_LCD);              OutBoolean(eToken_E, attr, "CKA_SAPI_HAS_LCD");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_HAS_USER);             OutBoolean(eToken_E, attr, "CKA_SAPI_HAS_USER");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_HAS_SO);               OutBoolean(eToken_E, attr, "CKA_SAPI_HAS_SO");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_FIPS);                 OutBoolean(eToken_E, attr, "CKA_SAPI_FIPS");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_FIPS_SUPPORTED);       OutBoolean(eToken_E, attr, "CKA_SAPI_FIPS_SUPPORTED");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_INIT_PIN_REQ);         OutBoolean(eToken_E, attr, "CKA_SAPI_INIT_PIN_REQ");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_RSA_2048);             OutBoolean(eToken_E, attr, "CKA_SAPI_RSA_2048");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_RSA_2048_SUPPORTED);   OutBoolean(eToken_E, attr, "CKA_SAPI_RSA_2048_SUPPORTED");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_HMAC_SHA1);            OutBoolean(eToken_E, attr, "CKA_SAPI_HMAC_SHA1");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_HMAC_SHA1_SUPPORTED);  OutBoolean(eToken_E, attr, "CKA_SAPI_HMAC_SHA1_SUPPORTED");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_REAL_COLOR);           OutBoolean(eToken_E, attr, "CKA_SAPI_REAL_COLOR");
				attr = FindAttr(Template, nTemplate, CKA_SAPI_MAY_INIT);             OutBoolean(eToken_E, attr, "CKA_SAPI_MAY_INIT");
			}
			_Catch() 
		}

	public:
		XmlDocument GetUserAuthContextInfo(const string& vXslUrl) 
		{
			try
			{
				XmlDocument doc;
				//
				//
				return doc;
			}
			_Catch();
		}


	public:
		// ----
		// eToken

//#		define _ETOKEN_ROOT L"f45d"
//#		define _ETOKEN_META_FILE L"f001"
//#		define _ETOKEN_KEYDIR_PREFIX L"a"

		inline static CStringA ETokenPath__(int port, const string& path)
		{
			return FormatStr("etoken%d:/" + _A(path) ,(int)port ); 
		}

		inline static CStringA ETokenPath__2(int port, const string& path)
		{
			return "etoken:/" + _A(path); 
		}

		inline static string RootPath()
		{
			return _W(_ETOKEN_ROOT); 
		}

		inline static string MetaPath(int isFreeEtc)
		{
			string path;
			if (isFreeEtc == 0)
			{
				path = RootPath() + L"/" + _W(_ETOKEN_META_FILE); 
			}
			else
			{
				// path = RootPath() + L"/" + _W(_ETOKEN_FREEMETA_FILE); 
			}
			return path; 
		}

#		define OID__META (L"1.2.643.6.2.1.5.2")
#		define OID__FREEMETA (L"1.2.643.6.2.1.5.6")
#		define OID__ETCH (L"1.2.643.6.2.1.5.81")
#		define OID_KEY_LIST_INFO (L"1.2.643.6.2.1.5.3")
#		define OID_KEY_LIST (L"1.2.643.6.2.1.5.3.11")
#		define OID_KEY_ENV (L"1.2.643.6.2.1.5.4") 

	private:
		// typedef SharedArray<AsnObject> METAObjects; // (Meta, FREEMeta) 

	public:
		inline static void OutputObject(const string& title, AsnObject& o) 
		{
#				ifdef _DEBUG
				{
					OutputDebugStringW(FormatStr(L"----\n%s\n", title )); 
					OutputDebugStringW(o.Dump() + L"\n"); 
				}
#				endif
		}

	public:
	///private:

#		define _KEY_FLAG_OK 1
#		define _KEY_FLAG_TODELETE 2
#		define _KEY_FLAG_REMOVED 8







		// ������������� ��������� eToken 

		inline void CheckInit() 
		{
			if (wasInit) return; 
			else
			{
				Init(); 
				//
				if (! wasInit)
				{
					throw MethodInfoExc(L"������� eToken �� ����������"); 
				}
			}
		}

		inline void Init() 
		{
			try
			{
				//!//Lock lock; 
				//
				HINSTANCE hLib = LoadLibrary(m_DllPath); 
				//
#				ifdef _DEBUG
				if (hLib == NULL)
#				else
				if (hLib == NULL)
#				endif
				{
					//throw MethodInfoExc(L"������ eToken: ���������� " + _W(m_DllPath) + L" �����������"); 
					throw MethodInfoExc(L"������� eToken �� ����������"); 
				}
				//
				(FARPROC&)pGFL = GetProcAddress(hLib, "C_GetFunctionList"); 
				if (pGFL == NULL) 
				{
					throw MethodInfoExc(L"������ eToken: (2)"); 
				}
				//
				// Get the function list 
				//
				if (CKR_OK != pGFL(&pFunctionList))
				{
					throw MethodInfoExc(L"������ eToken: (3)"); 
				}
				//
				// Initialize the PKCS #11 library 
				//
				if (CKR_OK != pFunctionList->C_Initialize (0))
				{
					throw MethodInfoExc(L"������ eToken: function: C_Initialize"); 
				}                 
				//
				CK_INFO info;
				if (CKR_OK != pFunctionList->C_GetInfo (&info))
				{
					throw MethodInfoExc(L"������ eToken: function: C_GetInfo");  
				}
				//
				//
				// ----
				// ETSAPI / SAPI 
				//
				LoadETSAPI(); 
				//
				wasInit = true; 
				//
				//TRACE_LINE(_T("----\neTokens ready")); // ������! 
			}
			catch(::::Exception e) 
			{
				if (e.m_SeverityLevel == ::::Exception::SeverityError)
				{
					throw;
				}
				//
				TRACE_LOG(e.ToString()); 
			}
			catch(...)
			{
				throw MethodError(L"����������� ������"); 
			}
		}

		PKCS11_Manager() 
		{
			try
			{
				Clear(); 
				//
				Init(); 
			}
			_Catch() 
		}

	public:
		// ----
		// ������ ������� ���������� � eToken (public) 

#		ifndef _ONLY_SUPPORTED_TOKENS 
#		define _ONLY_SUPPORTED_TOKENS 1 
#		endif 

		XmlDocument GetETokenInfo(const string& vXslUrl, int flags=1, 
			int targetSlotId=-1
			) 
		{
			CheckInit(); 
			//
			Lock lock;
			//
			bool useCache = true; 
			if (vXslUrl.GetLength() > 0) useCache = false; 
			//
			string id = _W(L"ETokenInfo_slot") + FormatStr(L"%d", targetSlotId) + L"_" + FormatStr(L"%d", flags); 
			//
			if (useCache)
			{
				XmlDocument cachedInfo;
				if (ObjCache::GetXmlObject(id, cachedInfo))
				{
					return cachedInfo; 
				}
			}
			//
			try
			{
#				ifdef _DEBUG
				TRACE_LINE(_T("! GetETokenInfo: In")); 
#				endif
				//
				string xmlStr = _W(COMMON_XML_START) + 
					(vXslUrl.GetLength() > 0 ? L"\n<?xml-stylesheet type=\"text/xsl\" href=\"" +
						vXslUrl + L"\"?>" : L""
					) + _W(L"\n<ETokenDeviceInfo />") 
					; 
				XmlDocument doc;
				doc.LoadXml(xmlStr); 
				XmlElement root_E = doc.DocumentElement(); 
				//
				// ----
				// ����� 
				//
				// PKCS11_Manager& M = PKCS11_Manager::Acquire(); 
				//
				//
				//
				CK_ULONG n1 = 16;
				SharedArray<CK_SLOT_ID> slotIdList;
				slotIdList.Allocate(n1);
				CK_RV r1 = pFunctionList->C_GetSlotList(1, slotIdList.GetBuffer(),
                    &n1);
				if (r1)
				{
					throw MethodError(L"Error in C_GetSlotList"); 
				}
				//
				// for (int slotId = 0; slotId <= _MAX_TOKEN_SLOT; ++slotId) 
				//
				//
				for (int slotIndexId = 0; slotIndexId < (int)n1; slotIndexId++) 
				{
					int slotId = slotIdList[slotIndexId]; 
					//
					bool useSlot = (targetSlotId == -1) || ((targetSlotId != -1) && (slotId == targetSlotId)); 
					//
					if (useSlot)
					{
#						ifdef _DEBUG
						TRACE_LINE1(_T("! GetETokenInfo: slotId: %d"), (int)slotId ); 
#						endif
						//
						CK_SLOT_INFO slot_info;
						if (CKR_OK == pFunctionList->C_GetSlotInfo (slotId, &slot_info))
						{
							XmlElement eToken_E = doc.CreateElement(L"",L"EToken",L""); 
							//
							if (slot_info.flags & CKF_TOKEN_PRESENT) 
							{
								string rDevAttr = slot_info.flags & CKF_REMOVABLE_DEVICE ? L"1" : L"0"; 
								//
								eToken_E.SetAttribute(L"SlotId",FormatStr(L"%d",slotId)); 
								eToken_E.SetAttribute(L"RemovableDevice",rDevAttr); 
								//
								// eToken info 
								//
								CK_TOKEN_INFO token_info;
								if (CKR_OK != pFunctionList->C_GetTokenInfo(slotId, &token_info)) 
								{
									throw MethodError(FormatStr(L"���������� eToken �������: %d", (int)slotId ));
								}
								else
								{
									if (slotId == 0)
									{
										/// SAPI_SetTokenName(L"eQQQ"); 
									}
									//
									string label = _W(CStringA((char*)token_info.label,
										(int)sizeof(token_info.label))); 
									label.Trim();
									//
									string labelExtra;
									{
										int p = label.Find(ETokenLabelDelim); 
										if (p != -1) 
										{
											labelExtra = label.Right(label.GetLength()-p-_W(ETokenLabelDelim).GetLength()); 
											labelExtra.Trim(); 
											//
											label = label.Left(p); 
											label.Trim(); 
										}
									}
									//
									string manufacturerID = _W(CStringA((char*)token_info.manufacturerID,
										(int)sizeof(token_info.manufacturerID))); 
									manufacturerID.Trim();
									//
									string model = _W(CStringA((char*)token_info.model,
										(int)sizeof(token_info.model))); 
									model.Trim(); 
									//
									string serialNumber = _W(CStringA((char*)token_info.serialNumber,
										(int)sizeof(token_info.serialNumber))); 
									serialNumber.Trim(); 
									//
									string hardwareVersion = FormatStr(L"%d.%d",
										(int)token_info.hardwareVersion.major,
										(int)token_info.hardwareVersion.minor);
									//
									string firmwareVersion = FormatStr(L"%d.%d",
										(int)token_info.firmwareVersion.major,
										(int)token_info.firmwareVersion.minor);
									//
									//CK_ATTRIBUTE a; 
									//a.type = ; 
									//SAPI_OTP_GetAttributeValue(hSession,&a,1); 
									//
									string pinInitedAttr = token_info.flags & CKF_USER_PIN_INITIALIZED ? L"1" : L"0"; 
									string loginRequiredAttr = token_info.flags & CKF_LOGIN_REQUIRED ? L"1" : L"0"; 
									//string pinEnteredAttr = (!(token_info.flags & CKF_LOGIN_REQUIRED)) ? L"1" : L"0"; 
									//
									eToken_E.SetAttribute(L"Label",label); 
									if (labelExtra.GetLength() > 0) 
										eToken_E.SetAttribute(L"OrgLabel",labelExtra); 
									eToken_E.SetAttribute(L"ManufacturerID",manufacturerID); 
									eToken_E.SetAttribute(L"Model",model); 
									eToken_E.SetAttribute(L"SerialNumber",serialNumber); 
									eToken_E.SetAttribute(L"eTokenID",serialNumber); 
									eToken_E.SetAttribute(L"HardwareVersion",hardwareVersion); 
									eToken_E.SetAttribute(L"FirmwareVersion",firmwareVersion); 
									eToken_E.SetAttribute(L"PinInitialized",pinInitedAttr); 
									eToken_E.SetAttribute(L"LoginRequired",loginRequiredAttr); 
									//
									eToken_E.SetAttribute(L"PinEntered",_W(L"0")); 
									//
									ReadTokenInfo_SAPI(eToken_E,slotId); 
									//
									PKCS11_eToken& t = PKCS11_eTokens[slotId]; 
									//
									if (t.hSession) // TODO: ��� ��? 
									{
										eToken_E.SetAttribute(L"PinEntered",_W(L"1")); 
									}
									//
									root_E.AppendChild(eToken_E); 
								}
							}
						}
					}
				}
				//
				// ---- 
				// Post-������ 
				//
#				ifdef _DEBUG
				TRACE_LINE(_T("! GetETokenInfo: Post-������")); 
#				endif
				//
				int i = -1;
				int n = 0;
				int iFirstSlot = -1;
				//
				XmlNodeList L = doc.SelectNodes(L"/*/EToken");
				for (int k = 0; k < L.Count(); ++k) 
				{
					XmlElement n1 = L[k]; 
					//
					string slotIdStr = n1.GetAttribute(L"SlotId");
					string name = n1.GetAttribute(L"Label");
					name.MakeUpper(); 
					//
					if (name == L"") 
					{
						if (n == 0)
						{
							i = _wtoi(slotIdStr);
						}
						++n;
						//
						if (n == 1) iFirstSlot = _wtoi(slotIdStr);
					}
					else 
					{
						if (iFirstSlot == -1) iFirstSlot = _wtoi(slotIdStr);
					}
				}
				//
				root_E.SetAttribute(L"Num", FormatStr(L"%d", (int)n ));
				//
				if (n == 1)
				{
					root_E.SetAttribute(L"Unique", _W(L"true"));
					root_E.SetAttribute(L"SelectedSlotId", FormatStr(L"%d", (int)i ));
				}
				else if (L.Count() == 1)
				{
					root_E.SetAttribute(L"Unique", _W(L"true"));
					root_E.SetAttribute(L"SelectedSlotId", FormatStr(L"%d", (int)iFirstSlot ));
				}
				//
#				ifdef _DEBUG
				{
					//OutputDebugString(_S(root_E.OuterXml())); 
				}
#				endif
				//
#				ifdef _DEBUG
				TRACE_LINE(_T("! GetETokenInfo: Out")); 
#				endif
				//
				if (useCache)
				{
					ObjCache::AddXmlObject(id, _OC_TIMEOUT_TOKEN_OBJ, doc); 
				}
				//
				return doc; 
			}
			_Catch() 
		}



		// ----
		// AsnObject <--> XML 

#ifndef AsnNsUri
#define AsnNsUri (L"urn::asn")
#endif

		inline static bool AsnTagIsText(int m_Tag) 
		{
			try
			{
				bool f = false; 
				//
				if (m_Tag == AsnObject::UTF8String) f = true; 
				if (m_Tag == AsnObject::BMPString) f = true; 
				if (m_Tag == AsnObject::IA5String) f = true; 
				if (m_Tag == AsnObject::PrintableString) f = true; 
				//
				return f; 
			}
			_Catch() 
		}

		inline XmlElement AsnObjToXmlElement(AsnObject& O, XmlDocument doc)
		{
			try
			{
				string name = L"object"; 
				string oid; 
				//
				//int t = 0;
				if (O.ChildCount() == 2)
				{
					AsnObject& child1 = O[0]; 
					//AsnObject& child2 = O[1]; 
					//
					if (child1.Tag() == AsnObject::OBJECT_IDENTIFIER) 
					{
						oid = child1.Oid(); 
					}
					else
					{
						name = L"sequence"; 
					}
				}
				else if (O.ChildCount() > 0) 
				{
					name = L"sequence"; 
				}
				else
				{
					if (O.AsnClass() == AsnObject::UNIVERSAL && O.m_Tag == AsnObject::SEQUENCE) 
					{
						name = L"sequence"; 
					}
				}
				//
				XmlElement E = doc.CreateElement(L"asn", name, AsnNsUri); 
				//
				if (oid.GetLength() > 0) E.SetAttribute(L"oid", oid); 
				//
				if (name == L"sequence") 
				{
					for (int k = 0; k < O.ChildCount(); k++)
					{
						AsnObject& child = O[k]; 
						XmlElement childE = AsnObjToXmlElement(child, doc); 
						E.AppendChild(childE); 
					}
				}
				else if (oid.GetLength() > 0) 
				{
					XmlElement childE = AsnObjToXmlElement(O[1], doc); 
					E.AppendChild(childE); 
				}
				else
				{
					string tagName = (O.m_Tag == AsnObject::OBJECT_IDENTIFIER) ? L"Oid" :
						_W(O.GetTagName(O.m_Tag)); 
					//
					E.SetAttribute(L"AsnClass", _W(O.AsnClassText())); 
					E.SetAttribute(L"Tag", tagName); 
					//
					if (O.AsnClass() == AsnObject::UNIVERSAL) 
					{
						if (O.m_Tag == AsnObject::INTEGER) 
						{
							E.SetAttribute(L"IntegerV", FormatStr(L"%d", (int)O.m_Integer )); 
						}
						if (O.m_Tag == AsnObject::OBJECT_IDENTIFIER) 
						{
							E.SetAttribute(L"OidV", (string)(O.m_Oid) ); 
						}
						else if (AsnTagIsText(O.m_Tag)) 
						{
							E.SetAttribute(L"TextV", O.m_text); 
						}
						else if (O.m_Tag == AsnObject::UTCTime) 
						{
							E.SetAttribute(L"DateTimeV", O.m_text); 
						}
						else if (O.m_Tag == AsnObject::BOOLEAN) 
						{
							string fStr = (O.m_Integer != 0) ? L"true" : L"false"; 
							E.SetAttribute(L"BooleanV", fStr); 
						}
						else if (O.m_Tag == AsnObject::OCTET_STRING) 
						{
							//try
							//{
							//	AsnObject o2(O.Data()); 
							//	XmlElement childE = AsnObjToXmlElement(o2, doc); 
							//	E.AppendChild(childE); 
							//}
							//catch(...)
							//{
							//	string dataStr = __ToBase64(O.Data()); 
							//	E.InnerText() = dataStr; 
							//}
							//
							if (!O.Deep.IsNull()) 
							{
								try
								{
									XmlElement childE = AsnObjToXmlElement(O.Deep, doc); 
									E.AppendChild(childE); 
								}
								catch(...)
								{
								}
							}
							else
							{
								string dataStr = __ToBase64(O.Data()); 
								E.InnerText() = dataStr; 
							}
						}
						else if (O.m_Tag == AsnObject::BIT_STRING) 
						{
							string dataStr = __ToBase64(O.Data()); 
							E.InnerText() = dataStr; 
						}
						else
						{
							//if (O.Data().Length() > 0) 
							//{
							//	try
							//	{
							//		AsnObject o2(O.Data()); 
							//		XmlElement childE = AsnObjToXmlElement(o2, doc); 
							//		E.AppendChild(childE); 
							//	}
							//	catch(...)
							//	{
							//		string dataStr = __ToBase64(O.Data()); 
							//		E.InnerText() = dataStr; 
							//	}
							//}
						}
					}
					else
					{
						//if (O.Data().Length() > 0) 
						//{
						//	try
						//	{
						//		AsnObject o2(O.Data()); 
						//		XmlElement childE = AsnObjToXmlElement(o2, doc); 
						//		E.AppendChild(childE); 
						//	}
						//	catch(...)
						//	{
						//		string dataStr = __ToBase64(O.Data()); 
						//		E.InnerText() = dataStr; 
						//	}
						//}
					}
				}
				// 
				return E; 
			}
			_Catch()
		}

		inline XmlDocument AsnDictionaryToXml(AsnObject& O)
		{
			try
			{
				bool useCache = true;
				string sha1 = ::::Algorithms::Alg_1_8_2().Encode(O.Encoded());
				string id = _W(L"AsnDictionaryToXml_") + sha1; 
				double dt = 10 * _OC_TIMEOUT_TOKEN_OBJ; 
				//
				if (useCache)
				{
					XmlDocument d;
					if (ObjCache::GetXmlObject(id, d))
					{
						return d; 
					}
				}
				//
#				ifdef _DEBUG
				{
					OutputObject(L"AsnDictionary:", O); 
				}
#				endif 
				//
				XmlDocument doc;
				doc.LoadXml(L"<asn:envelope xmlns:asn=\"" + _W(AsnNsUri) + L"\" />"); 
				//
				XmlElement asnEnv = doc.DocumentElement(); 
				//
				XmlElement E = AsnObjToXmlElement(O, doc); 
				asnEnv.AppendChild(E); 
				//
				if (useCache)
				{
					ObjCache::AddXmlObject(id, dt, doc); 
				}
				//
				return doc; 
			}
			_Catch()
		}

		inline AsnObject XmlElementToAsnDict(XmlElement E) 
		{
			try
			{
				if (E.LocalName() == L"envelope")
				{
					XmlElement E1 = E.SelectSingleNode(L"/*/*"); 
					return XmlElementToAsnDict(E1); 
				}
				//
				AsnObject O = AsnObject(false, AsnObject::UNIVERSAL, AsnObject::_NULL_); 
				//
				// attributes 
				string tag; 
				string oid; 
				tag = E.LocalName(); 
				if (E.HasAttribute(L"oid")) oid = E.GetAttribute(L"oid"); 
				//
				if (tag == L"object")
				{
					if (oid.GetLength() > 0)
					{
						O = AsnObject::NewSequence(); 
						O.Add(AsnObject(OID(oid))); 
						//
						XmlNodeList L = E.SelectNodes(L"*"); 
						for (int k = 0; k < L.Count(); k++)
						{
							XmlElement child = L[k];
							AsnObject childO = XmlElementToAsnDict(child); 
							O.Add(childO); 
						}
					}
					else
					{
						if (E.HasAttribute(L"AsnClass") && E.HasAttribute(L"Tag")) 
						{
							string asnClass = E.GetAttribute(L"AsnClass"); 
							string tag = E.GetAttribute(L"Tag"); 
							//
							if (asnClass == L"UNIVERSAL") 
							{
								if (tag == L"Integer") 
								{
									O = AsnObject(false, AsnObject::UNIVERSAL, AsnObject::INTEGER); 
									O.m_Integer = _wtoi(E.GetAttribute(L"IntegerV")); 
								}
								else if (tag == L"UTF8String") 
								{
									string v = E.GetAttribute(L"TextV"); 
									//
									O = AsnObject(false, AsnObject::UNIVERSAL, AsnObject::UTF8String); 
									O.m_text = v; 
								}
								else if (tag == L"BMPString") 
								{
									string v = E.GetAttribute(L"TextV"); 
									//
									O = AsnObject(false, AsnObject::UNIVERSAL, AsnObject::BMPString); 
									O.m_text = v; 
								}
								else if (tag == L"OctetString") 
								{
									string v = E.InnerText(); 
									//
									O = AsnObject(false, AsnObject::UNIVERSAL, AsnObject::OCTET_STRING); 
									O.m_Data = FromBase64String(v); 
								}
							}
							else
							{
							}
						}
					}
				}
				else if (tag == L"sequence") 
				{
					O = AsnObject::NewSequence(); 
					//
					XmlNodeList L = E.SelectNodes(L"*"); 
					for (int k = 0; k < L.Count(); k++)
					{
						XmlElement child = L[k];
						AsnObject childO = XmlElementToAsnDict(child); 
						O.Add(childO); 
					}
				}
				//
				return O; 
			}
			_Catch() 
		}

		inline AsnObject XmlToAsnDictionary(XmlDocument asnDoc) 
		{
			try
			{
				XmlElement root = asnDoc.DocumentElement(); 
				AsnObject O = XmlElementToAsnDict(root); 
				//
#				ifdef _DEBUG
				{
					OutputObject(L"XmlToAsnDictionary:", O); 
				}
#				endif
				//
				return O; 
			}
			_Catch() 
		}
	};











	// ===========================================================================================

	struct EToken 
	{
		// ---- 
		// Common structures 

		inline static CRITICAL_SECTION& CriticalSection() 
		{
			static bool crits_f = false;
			static CRITICAL_SECTION crits; 
			if (! crits_f)
			{
				InitializeCriticalSection(&crits); 
				crits_f = true;
			}
			return crits; 
		}

		class Lock
		{
		public:
			Lock()
			{
				EnterCriticalSection(&CriticalSection());
			}

			~Lock()
			{
				LeaveCriticalSection(&CriticalSection());
			}
		};

		// ----
		// EToken glossary 

		inline static Map<int,int>& ContextETokenSlotMap___()
		{
			static Map<int,int> m_ThreadToSlotId; 
			return m_ThreadToSlotId; 
		}

		inline static Map<int,EToken>& eTokenBySlotGlossary()
		{
			static Map<int,EToken> m_Glossary; 
			return m_Glossary; 
		}

		typedef Map<string,SharedPtr<EToken> > eTokenGlossaryType; 

		inline static eTokenGlossaryType& eTokenGlossary() 
		{
			static eTokenGlossaryType m_Glossary; 
			return m_Glossary; 
		}

		inline static EToken& OpenEToken(int eTokenSlotId) 
		{
			try
			{
				for (eTokenGlossaryType::Iterator i(eTokenGlossary()); i; ++i) 
				{
					SharedPtr<EToken> p_eToken = i; 
					//
					if (p_eToken->SlotId == eTokenSlotId) 
					{
						return *(p_eToken.GetPointee()); 
					}
				}
				//
				string msg = FormatStr(L"eToken SlotId=%d not found", (int)eTokenSlotId );  
				throw MethodError(msg); 
			}
			_Catch() 
		}

		inline static EToken& OpenEToken(const string& eTokenID) 
		{
			try
			{
				Lock lock; 
				//
				eTokenGlossaryType& m_Glossary = eTokenGlossary(); 
				if (!m_Glossary.ContainsKey(eTokenID))
				{
					XmlDocument doc = PKCS11_Manager_().GetETokenInfo(L""); 
					XmlElement docRoot = doc.DocumentElement(); 
					XmlNodeList L = docRoot.SelectNodes(L"/*/EToken[@eTokenID='" + eTokenID + L"']"); 
					if (L.Count() == 0) throw MethodError(L"eToken ID=" + eTokenID + L" not found"); 
					//
					XmlElement eTokenInfo = L[0]; 
					//
					m_Glossary[eTokenID] = SharedPtr<EToken>(new EToken()); 
					SharedPtr<EToken> pp1 = m_Glossary[eTokenID]; 
					EToken* p_eToken = pp1.GetPointee(); 
					p_eToken->Connect(eTokenInfo); 
					//SharedPtr<EToken> pp2 = m_Glossary[eTokenID]; 
					//EToken* p_eToken2 = pp2.GetPointee(); 
					//EToken& eT2 = *p_eToken2; 
				}
				SharedPtr<EToken> pp1 = m_Glossary[eTokenID]; 
				EToken& eToken = *(pp1.GetPointee()); 
				return eToken; 
			}
			_Catch()
		}

		inline static EToken GetEmpty(int slotId) 
		{
			try
			{
				return EToken(-1, slotId); 
			}
			_Catch() 
		}



		// ======================================================================================= 
		// ---- 
		// Data 

		int SlotId; 
		string eTokenID; 

		string Pin; 
		string UserPass; 
		string AdmPass; 

		XmlElement Info; 

		// Device 

		bool LoggedIn; 

		CK_SESSION_HANDLE hSession; 

		// Key infrastructure 

		mutable Map<string, SharedPtr<AsnObject> > m_Objects; 

		int keyNum; 

		bool needUpdate; 

		// ---- 
		// Methods 

		inline void Clear() 
		{
			SlotId = -1; 
			keyNum = -1;
			needUpdate = false; 
			LoggedIn = false; 
			hSession = NULL; 
			fMetaConnected = false; 
			fMetaPrivateActive = false; 
			//
			m_inConversion = false; 
		}

		EToken()
		{
			Clear(); 
		}

		//EToken(const AsnObject& o_0, const AsnObject& o_1) 
		//{
		//	AsnObject& p0 = *(m_Objects[0]); p0 = o_0; 
		//	//
		//	AsnObject& p1 = *(m_Objects[1]); p1 = o_1; 
		//	//
		//	Parse(); 
		//}

		const EToken& operator =(const EToken& other) 
		{
			Clear(); 
			//
			SlotId = other.SlotId; 
			eTokenID = other.eTokenID; 
			//
			Pin = other.Pin; 
			UserPass = other.UserPass; 
			AdmPass = other.AdmPass; 
			//
			keyNum = other.keyNum; 
			needUpdate = other.needUpdate; 
			//
			LoggedIn = other.LoggedIn; 
			hSession = other.hSession; 
			//
			return other; 
		}

		EToken(const EToken& other) 
		{
			operator =(other); 
		}

		EToken(int specialMode, int slotId_) 
		{
			Clear(); 
			//
			SlotId = slotId_; 
		}

		inline bool IsPresent() 
		{
			return eTokenID.GetLength() > 0; 
		}

		// ---- 
		// ����������� 

		inline void Connect(XmlElement eTokenInfo) 
		{
			try
			{
				Lock lock; 
				//
				Info = eTokenInfo; 
				//
				SlotId = _wtoi(Info.GetAttribute(L"SlotId")); 
				//
				string SlotIdStr = FormatStr(L"%d", SlotId); 
				XmlNodeList L = eTokenInfo.SelectNodes(L"/*/EToken[@SlotId = '" + SlotIdStr + L"']"); 
				if (L.Count() == 0) throw MethodError(L"eToken: SlotId=" + SlotIdStr + L" not found"); 
				//
				pSetInfo(L[0]); 
				//
				Open(); 
			}
			_Catch() 
		}

		//inline void Connect(int SlotId_, XmlDocument eTokenInfo) 
		//{
		//	try
		//	{
		//		Lock lock; 
		//		// 
		//		SlotId = SlotId_; 
		//		//
		//		string SlotIdStr = FormatStr(L"%d", SlotId); 
		//		XmlNodeList L = eTokenInfo.SelectNodes(L"/*/EToken[@SlotId = '" + SlotIdStr + L"']"); 
		//		if (L.Count() == 0) throw MethodError(L"eToken: SlotId=" + SlotIdStr + L" not found"); 
		//		//
		//		SetInfo(L[0]); 
		//	}
		//	_Catch() 
		//}

		inline void pSetInfo(XmlElement Info_) 
		{
			try
			{
				Info = Info_; 
				//
				// Parameters 
				//
				SlotId = _wtoi(Info.GetAttribute(L"SlotId")); 
				eTokenID = Info.GetAttribute(L"eTokenID"); 
			}
			_Catch() 
		}

		inline void SetPass(const string& userPass_, const string& admPass_=L"") 
		{
			try
			{
				UserPass = userPass_; 
				if (admPass_.GetLength() > 0) AdmPass = admPass_; 
			}
			_Catch() 
		}
		
		inline void RemovePin() 
		{
			Pin = L""; 
		}



		// ---- 
		// ����������� 

		inline void Open() 
		{
			try
			{
				if (hSession) return; // ������! 
				//
				// ��������� ������, ����� ��������� C_Login 
				//
				CK_RV rv = PKCS11_Manager_().pFunctionList->C_OpenSession(
					SlotId,
					CKF_RW_SESSION | CKF_SERIAL_SESSION, /// CK_FLAGS flags, /* from CK_SESSION_INFO */ 
					0, /// CK_VOID_PTR           pApplication,  /* passed to callback */
					0, /// CK_NOTIFY             Notify,        /* callback function */
					&hSession      /* gets session handle */
					);
				if (rv != 0) 
				{
					hSession = NULL; 
					//
					throw MethodError(L"������ eToken: function: C_OpenSession"); 
				}
			}
			_Catch()
		}

		inline void Login() 
		{
			try
			{
				if (LoggedIn) return; // ������! 
				//
				if (! hSession) throw MethodError(L"hSession == 0"); 
				//
				// ��������� ������, ����� ��������� C_Login 
				//
				CK_RV rv = PKCS11_Manager_().pFunctionList->C_OpenSession(
					SlotId,
					CKF_RW_SESSION | CKF_SERIAL_SESSION, /// CK_FLAGS flags, /* from CK_SESSION_INFO */ 
					0, /// CK_VOID_PTR           pApplication,  /* passed to callback */
					0, /// CK_NOTIFY             Notify,        /* callback function */
					&hSession      /* gets session handle */
					);
				if (rv != 0) 
				{
					throw MethodError(L"������ eToken: function: C_OpenSession"); 
				}
				//
				CStringA admPassA(AdmPass);
				CStringA userPassA(UserPass);
				//
				if (AdmPass.GetLength() == 0)
				{
					if (UserPass.GetLength() == 0)
					{
						if (Pin.GetLength() > 0)
						{
							userPassA = _A(Pin); 
						}
						else
						{
							userPassA = _A(""); // _A(PasswordDialog::GetDevicePIN(L"eToken")); 
							if (userPassA == "__CANCELED__") 
							{
								throw MethodError(L"���� PIN-���� �������"); 
							}
							Pin = _W(userPassA); 
						}
					}
				}
				//
				admPassA = userPassA;
				//
				rv = PKCS11_Manager_().pFunctionList->C_Login(hSession, CKU_USER, 
					(CK_CHAR*)userPassA.GetBuffer(), userPassA.GetLength() 
					); 
				//
				if (rv == CKR_USER_PIN_NOT_INITIALIZED)
				{
					CK_RV rv = PKCS11_Manager_().pFunctionList->C_Login(hSession, CKU_SO, 
						(CK_CHAR*)admPassA.GetBuffer(), admPassA.GetLength() 
						); 
					if (rv != 0) 
					{
						RemovePin(); 
						throw MethodError(FormatStr(L"������ eToken: function: C_Login: %d", (int)rv ));  
					}
					//
					rv = PKCS11_Manager_().pFunctionList->C_InitPIN(hSession, 
						(CK_CHAR*)userPassA.GetBuffer(), userPassA.GetLength() 
						); 
					if (rv != 0) 
					{
						RemovePin(); 
						throw MethodError(FormatStr(L"������ eToken: function: C_InitPIN: %d", (int)rv ));  
					}
					//
					rv = PKCS11_Manager_().pFunctionList->C_Logout(hSession); 
					if (rv != 0) 
					{
						RemovePin(); 
						throw MethodError(FormatStr(L"������ eToken: function: C_Logout: %d", (int)rv ));      
					}
					//
					rv = PKCS11_Manager_().pFunctionList->C_Login(hSession, CKU_USER, 
						(CK_CHAR*)userPassA.GetBuffer(), userPassA.GetLength() 
						); 
					if (rv != 0) 
					{
						RemovePin(); 
						throw MethodError(FormatStr(L"������ eToken: function: C_Login: %d", (int)rv ));  
					}
				}
				else if (rv != 0) 
				{
					RemovePin(); 
					throw MethodError(FormatStr(L"������ eToken: function: C_Login: %d", (int)rv ));   
				}
				//
				LoggedIn = true; 
			}
			_Catch() 
		}

		//inline PKCS11_eToken& ContextEToken()  
		//{
		//	try
		//	{
		//		return eTokens[ContextSlotId()]; 
		//	}
		//	_Catch() 
		//}

		inline static int ContextSlotId() 
		{
			try
			{
				int threadId = (int)GetCurrentThreadId();
				if (PKCS11_Manager_().ThreadId_eToken_Glossary().ContainsKey(threadId))
				{
					return PKCS11_Manager_().ThreadId_eToken_Glossary()[threadId]; 
				}
				else
				{
					throw MethodError(L"�������� eToken �� ��������������� (TH)"); 
				}
			}
			_Catch() 
		}

		inline static string ContextPin() 
		{
			try
			{
				int slotId = ContextSlotId(); 
				//
				EToken& eToken = EToken::OpenEToken(slotId); 
				//
				if (!eToken.IsPresent())
				{
					string errMsg = FormatStr(L"eToken slotId=%d �� ���������", (int)slotId ); 
					throw MethodError(errMsg); 
				}
				return eToken.Pin; 
			}
			_Catch() 
		}

		inline static void SetPin(const string& eTokenID, const string& pinValue) 
		{
			try
			{
				EToken& eToken = EToken::OpenEToken(eTokenID); 
				eToken.Pin = pinValue; 
			}
			_Catch() 
		}

		//inline void RemovePin(int slotId) 
		//{
		//	try
		//	{
		//		PKCS11_eToken& eToken = eTokenBySlot(slotId); 
		//		eToken.Pin = L""; 
		//	}
		//	_Catch() 
		//}

		inline static void SetAllPinsTo(const string& pinValue) 
		{
			try
			{
				for (int k = 0; k <= _MAX_TOKEN_SLOT; k++)
				{
					EToken& eToken = EToken::OpenEToken(k); 
					eToken.Pin = pinValue; 
				}
				//
				//try
				//{

				//}
				//catch(::Exception e)
				//{
				//	OutputDebugStringW(e.ToString() + L"\n!!!\n"); 
				//}
				//catch(...)
				//{
				//	OutputDebugStringW(L"!!!\nProtocol: ����������� ������!!!\n"); 
				//}
			}
			_Catch()
		}

		inline static int etoken_passwd_cb(char *buf, int num, int w, void *userdata)
		{
			try
			{
				//int j;
				//
				CStringA p(ContextPin());
				memcpy(buf, p.GetString(), p.GetLength());
				buf[p.GetLength()] = 0;
				//
				return p.GetLength(); 
			}
			_Catch() 
		}

		inline void EnterContext() 
		{
			try
			{
				PKCS11_Manager_().EnterContext(SlotId); 
			}
			_Catch() 
		}

		inline void ReleaseContext() 
		{
			try
			{
				PKCS11_Manager_().EnterContext(SlotId); 
			}
			_Catch() 
		}






		// =======================================================================================
		// PKI

		inline CStringA ETokenPath(const string& path) 
		{
			int port = SlotId; 
			return FormatStr("etoken%d:/" + _A(path) ,(int)port ); 
		}



		// ----
		// Objects 

		inline void CreateETokenObject(int slotId, 
			CK_ULONG classType,
			CK_BBOOL isToken,
			CK_BBOOL isPrivate,
			const string& label,
			const string& subject,
			Blob value, 
			CK_ULONG certType=CKC_X_509
			)
		{
			try
			{
				PKCS11_Manager_().CheckInit(); 
				//
				/// EToken& t = eTokens[slotId]; 
				//
				RemoveObject(SlotId, CKO_DATA, 1, label); 
				//
				//SharedArray<Blob> a1 = FindETokenObjects(slotId, CKO_DATA, isToken, label); 
				//if (a1.Length() > 0)
				//{
				//	// deleting old object...
				//	//
				//}
				//
				//CK_BBOOL bFalse    = 0;
				//CK_BBOOL bTrue     = 1;
				//CK_ULONG classType = CKO_CERTIFICATE;
				//CK_ULONG certType2  = CKC_X_509;
				//CK_OBJECT_HANDLE certObj; 
				//CStringA label1("Signing Certificate");
				//CStringA subject1("CN=������ ��CN=Users,DC=,DC=ru"); 
				//
				CK_OBJECT_HANDLE Obj; 
				CStringA label1(label);
				CStringA subject1(subject); 
				//
				CK_ATTRIBUTE m_cert[] = 
					{
						{CKA_CLASS, &classType, sizeof(classType)},
						{CKA_TOKEN, &isToken, sizeof(isToken)},
						{CKA_PRIVATE, &isPrivate, sizeof(isPrivate)},
						{CKA_LABEL, label1.GetBuffer(), label1.GetLength()},
						{CKA_CERTIFICATE_TYPE, &certType, sizeof(certType)},
						{CKA_SUBJECT, subject1.GetBuffer(), subject1.GetLength()},
						{CKA_VALUE, value.GetBuffer(), value.Length()}
					};
				//
				CK_ATTRIBUTE m_0[] = 
					{
						{CKA_CLASS, &classType, sizeof(classType)},
						{CKA_TOKEN, &isToken, sizeof(isToken)},
						{CKA_PRIVATE, &isPrivate, sizeof(isPrivate)},
						{CKA_LABEL, label1.GetBuffer(), label1.GetLength()},
						{CKA_VALUE, value.GetBuffer(), value.Length()}
					};
				//
				CK_ATTRIBUTE* m = (classType == CKO_CERTIFICATE) ? m_cert : m_0;
				int mSize = (classType == CKO_CERTIFICATE) ? sizeof(m_cert) : sizeof(m_0);
				//
				CK_RV rv = PKCS11_Manager_().pFunctionList->C_CreateObject(hSession, 
					m, mSize/sizeof(CK_ATTRIBUTE), 
					&Obj); 
				if (rv != 0) 
				{
					throw MethodError(FormatStr(L"������ eToken: function: C_CreateObject: %d", (int)rv )); 
				}
			}
			_Catch()
		}

		inline SharedArray<Blob> FindCertObjects(int slotId, 
			CK_ULONG classType,
			CK_BBOOL isToken,
			const string& search 
			) 
		{
			try
			{
				PKCS11_Manager_().CheckInit(); 
				//
				Lock lock; 
				//
				// EToken& t = eTokens[slotId]; 
				//
				CStringA label1(search); 
				//
				SharedArray<Blob> result; 
				//
				CK_ATTRIBUTE search_template[]  = 
				{ 
					//{CKA_CLASS,            &classType , sizeof(classType)},
					//{CKA_CERTIFICATE_TYPE, &certType,   sizeof(certType)},
					{CKA_TOKEN,            &isToken,      sizeof(isToken)  },
					//{CKA_LABEL, label1.GetBuffer(), label1.GetLength()} 	
					//{CKA_SUBJECT, label1.GetBuffer(), label1.GetLength()} 	
				};
				//
				CK_OBJECT_HANDLE hObject;
				CK_ULONG foundObjects = 0;
				//
				int r0 = PKCS11_Manager_().pFunctionList->C_FindObjectsInit(
					hSession, 
					search_template, sizeof(search_template)/sizeof(search_template[0])
					);
				//
				if (CKR_OK == r0)
				{
					bool firstTime = true;
					while ((PKCS11_Manager_().pFunctionList->C_FindObjects(
						hSession, &hObject, 1, &foundObjects) == CKR_OK)
						&& foundObjects > 0)
					{
						if (firstTime)
						{
							// printf ("           <List of Certificate information>\n");
							firstTime = false;
						}
						//
						// Get some attributes: certificate Issuer,Subject,Value attributes...
						//
						CK_ATTRIBUTE V[] = 
						{
							{ CKA_LABEL,   NULL, 0 },
							{ CKA_VALUE,   NULL, 0 },
							{ CKA_CERTIFICATE_TYPE,   NULL, 0 },
						};
						//
						Blob labelValue;
						int labelLen = 0;
						Blob value;
						int valueLen = 0; 
						Blob ctValue;
						int ctLen = 0;
						//
						if (CKR_OK == PKCS11_Manager_().pFunctionList->C_GetAttributeValue(
							hSession, 
							hObject, 
							V, sizeof(V)/sizeof(V[0])
							))
						{
							labelLen = V[0].ulValueLen;
							labelValue.Expand(labelLen);
							V[0].pValue = labelValue.GetBuffer();
							//
							valueLen = V[1].ulValueLen;
							value.Expand(valueLen);
							V[1].pValue = value.GetBuffer();
							//
							ctLen = V[2].ulValueLen;
							ctValue.Expand(valueLen);
							V[2].pValue = value.GetBuffer();
						}
						//
						if (CKR_OK == PKCS11_Manager_().pFunctionList->C_GetAttributeValue(
							hSession, 
							hObject, 
							V, sizeof(V)/sizeof(V[0])
							))
						{
							//CopyMemory(labelValue.GetBuffer(), V[0].pValue, labelLen);  
							labelValue.SetSize(labelLen);
							//
							//CopyMemory(value.GetBuffer(), V[0].pValue, valueLen); 
							value.SetSize(valueLen);
							//
							result.Add(value); 
						}
					}
				}
				PKCS11_Manager_().pFunctionList->C_FindObjectsFinal(hSession);
				//
				return result; 
			}
			_Catch()
		}

		Map<string,Blob> m_ConstantData; 

		inline void FlushConstantData() 
		{
			try
			{
				m_ConstantData.RemoveAll(); 
			}
			_Catch() 
		}

		inline bool ConstantDataSearch(const string& search) 
		{
			try
			{
				bool searchForData = false; 
				if (search.Find(L"Request") != -1) searchForData = true; 
				if (search.Find(L"Certificate") != -1) searchForData = true; 
				//
				return searchForData; 
			}
			_Catch() 
		}

		inline SharedArray<Blob> FindETokenObjects(int slotId, 
			CK_ULONG classType,
			CK_BBOOL isToken,
			const string& search 
			) 
		{
			try
			{
				bool useCache = true; 
				//
				string id = _W(L"eTokenObject_slot") + 
					FormatStr(L"%d", SlotId) + 
					L"_cl" + FormatStr(L"%d", (int)classType) + 
					L"_istok" + FormatStr(L"%d", (int)isToken) + 
					L"_search" + search 
					; 
				//
				if (useCache)
				{
					XmlDocument d; 
					if (ObjCache::GetXmlObject(id, d))
					{
						XmlElement root = d.DocumentElement();
						XmlNodeList data_L = root.SelectNodes(L"*"); 
						SharedArray<Blob> a;
						for (int k = 0; k < data_L.Count(); k++)
						{
							XmlElement data_E = data_L[k]; 
							Blob data = FromBase64String(data_E.InnerText()); 
							a.Add(data); 
						}
						return a; 
					}
				}
				//
				//
				//
				Map<string,Blob>& M = m_ConstantData; 
				//
				string dataId = FormatStr(L"%d", slotId) + L"/" + search; 
				if (true) // (ConstantDataSearch(search)) 
				{
					if (M.ContainsKey(dataId)) 
					{
						SharedArray<Blob> result; 
						Blob b = M[dataId]; 
						if (b.Length() > 0) result.Add(b); 
						return result; 
					}
				}
				//
				PKCS11_Manager_().CheckInit(); 
				//
				// Lock lock; 
				//
				// EToken& t = eTokens[slotId]; 
				//
				CStringA label1(search); 
				//
				SharedArray<Blob> result; 
				//
				CK_ATTRIBUTE search_template[]  = 
				{ 
					//{CKA_CLASS,            &classType , sizeof(classType)},
					//{CKA_CERTIFICATE_TYPE, &certType,   sizeof(certType)},
					//{CKA_TOKEN,            &isToken,      sizeof(isToken)  },
					{CKA_LABEL, label1.GetBuffer(), label1.GetLength()} 	
				};
				//
				CK_OBJECT_HANDLE hObject;
				CK_ULONG foundObjects = 0;
				//
				//OutputDebugStringW(L"C_FindObjectsInit: " + search + L" {"); 
				int r0 = PKCS11_Manager_().pFunctionList->C_FindObjectsInit(
					hSession, 
					search_template, sizeof(search_template)/sizeof(search_template[0])
					);
				//OutputDebugStringW(L"}\n"); 
				//
				try
				{
					if (CKR_OK == r0)
					{
						bool firstTime = true;
						//OutputDebugStringW(L"C_FindObjects{"); 
						int r2 = PKCS11_Manager_().pFunctionList->C_FindObjects(
							hSession, &hObject, 1, &foundObjects
							);
						//
						if ((!(r2 == CKR_OK)) || (foundObjects == 0)) 
						{
							Blob empty = Blob(); 
							M[dataId] = empty; 
							Blob b2 = M[dataId];
						}
						//
						while ((r2 == CKR_OK) && foundObjects > 0 && firstTime)
						{
							//OutputDebugStringW(L"} OK\n"); 
							if (firstTime)
							{
								// printf ("           <List of Certificate information>\n");
								firstTime = false;
							}
							//
							// Get some attributes: certificate Issuer,Subject,Value attributes...
							//
							CK_ATTRIBUTE V[] = 
							{
								{ CKA_LABEL,   NULL, 0 },
								{ CKA_VALUE,   NULL, 0 },
							};
							//
							Blob labelValue;
							int labelLen = 0;
							Blob value;
							int valueLen = 0; 
							//
							if (CKR_OK == PKCS11_Manager_().pFunctionList->C_GetAttributeValue(
								hSession, 
								hObject, 
								V, sizeof(V)/sizeof(V[0])
								))
							{
								labelLen = V[0].ulValueLen;
								labelValue.Expand(labelLen);
								V[0].pValue = labelValue.GetBuffer();
								//
								valueLen = V[1].ulValueLen;
								value.Expand(valueLen);
								V[1].pValue = value.GetBuffer();
							}
							else
							{
								throw MethodError(L"Attribute not found for '" + search + L"'"); 
							}
							//
							if (CKR_OK == PKCS11_Manager_().pFunctionList->C_GetAttributeValue(
								hSession, 
								hObject, 
								V, sizeof(V)/sizeof(V[0])
								))
							{
								//CopyMemory(labelValue.GetBuffer(), V[0].pValue, labelLen);  
								labelValue.SetSize(labelLen);
								//
								//CopyMemory(value.GetBuffer(), V[0].pValue, valueLen); 
								value.SetSize(valueLen);
								//
								result.Add(value); 
							}
							else
							{
								throw MethodError(L"Attribute not found for '" + search + L"'"); 
							}
							//
							r2 = PKCS11_Manager_().pFunctionList->C_FindObjects(
								hSession, &hObject, 1, &foundObjects
								);
						}
						//OutputDebugStringW(L"ready\n"); 
					}
					PKCS11_Manager_().pFunctionList->C_FindObjectsFinal(hSession);
					//OutputDebugStringW(L"C_FindObjectsFinal OK\n"); 
				}
				catch(...)
				{
					PKCS11_Manager_().pFunctionList->C_FindObjectsFinal(hSession);
					//OutputDebugStringW(L"C_FindObjectsFinal OK\n"); 
				}
				//
				if (result.Length() > 0)
				{
					Blob data = result[0]; 
					if (true) // (data.Length() > 0) 
					{
						M[dataId] = data; 
					}
				}
				else
				{
					M[dataId] = Blob();
				}
				//
				if (useCache)
				{
					XmlDocument d;
					d.LoadXml(L"<data-array />"); 
					XmlElement root = d.DocumentElement();
					for (int k = 0; k < result.Length(); k++) 
					{
						Blob data = result[k]; 
						XmlElement data_E = d.CreateElement(L"", L"data", L""); 
						data_E.InnerText() = __ToBase64(data);
						root.AppendChild(data_E); 
					}
					ObjCache::AddXmlObject(id, _OC_TIMEOUT_TOKEN_OBJ, d); 
				}
				//
				return result; 
			}
			_Catch()
		}

		inline string GetObjectLabel(const string& cat, const string& name) 
		{
			try
			{
				string label = _W(L" ") + cat + L" " + name; 
				return label; 
			}
			_Catch()
		}

		inline SharedArray<Blob> RemoveObject(int slotId, 
			CK_ULONG classType,
			CK_BBOOL isToken,
			const string& search 
			) 
		{
			try
			{
				PKCS11_Manager_().CheckInit(); 
				//
				Lock lock; 
				//
				CStringA label1(search); 
				//
				SharedArray<Blob> result; 
				//
				CK_ATTRIBUTE search_template[]  = 
				{ 
					{CKA_LABEL, label1.GetBuffer(), label1.GetLength()} 	
				};
				//
				CK_OBJECT_HANDLE hObject = 0;
				CK_ULONG foundObjects = 0;
				bool foundOne = false; 
				//
				int r0 = PKCS11_Manager_().pFunctionList->C_FindObjectsInit(
					hSession, 
					search_template, sizeof(search_template)/sizeof(search_template[0])
					);
				//
				if (CKR_OK == r0)
				{
					bool firstTime = true;
					while ((PKCS11_Manager_().pFunctionList->C_FindObjects(
						hSession, &hObject, 1, &foundObjects) == CKR_OK)
						&& foundObjects > 0 
						&& (!foundOne))
					{
						if (firstTime)
						{
							// printf ("           <List of Certificate information>\n");
							firstTime = false;
						}
						if (hObject) foundOne = true; 
						//
						// Get some attributes: certificate Issuer,Subject,Value attributes...
						//
						CK_ATTRIBUTE V[] = 
						{
							{ CKA_LABEL,   NULL, 0 },
							{ CKA_VALUE,   NULL, 0 },
						};
						//
						Blob labelValue;
						int labelLen = 0;
						Blob value;
						int valueLen = 0; 
						//
						if (CKR_OK == PKCS11_Manager_().pFunctionList->C_GetAttributeValue(
							hSession, 
							hObject, 
							V, sizeof(V)/sizeof(V[0])
							))
						{
							labelLen = V[0].ulValueLen;
							labelValue.Expand(labelLen);
							V[0].pValue = labelValue.GetBuffer();
							//
							valueLen = V[1].ulValueLen;
							value.Expand(valueLen);
							V[1].pValue = value.GetBuffer();
						}
						//
						if (CKR_OK == PKCS11_Manager_().pFunctionList->C_GetAttributeValue(
							hSession, 
							hObject, 
							V, sizeof(V)/sizeof(V[0])
							))
						{
							//CopyMemory(labelValue.GetBuffer(), V[0].pValue, labelLen);  
							labelValue.SetSize(labelLen);
							//
							//CopyMemory(value.GetBuffer(), V[0].pValue, valueLen); 
							value.SetSize(valueLen);
							//
							result.Add(value); 
						}
					}
				}
				PKCS11_Manager_().pFunctionList->C_FindObjectsFinal(hSession);
				//
				if (foundOne)
				{
					if (CKR_OK != PKCS11_Manager_().pFunctionList->C_DestroyObject(
						hSession
						,hObject))
					{
						throw MethodError(L"eToken: ������ ��� �������� ������� '" + search + L"'"); 
					}
				}
				//
				return result; 
			}
			_Catch()
		}

		inline void SearchCert(const string& subject) 
		{
			try
			{
			SharedArray<Blob> a1 = FindCertObjects(SlotId, 
				CKO_CERTIFICATE,
				1,
				subject 
				); 
			}
			_Catch() 
		}

		inline void SaveObject(
			const string& label, 
			Blob value, 
			CK_ULONG classType, 
			CK_BBOOL isPrivate, 
			const string& subject=L""
			) 
		{
			try
			{
				//CK_BBOOL bFalse    = 0; 
				CK_BBOOL bTrue     = 1; 
				//
				CreateETokenObject(SlotId, 
					classType,
					bTrue,
					isPrivate,
					label,
					subject,
					value, 
					CKC_VENDOR_DEFINED
					);
			}
			_Catch() 
		}

		inline static XmlDocument ObjectXml(Blob b)
		{
			try
			{
				XmlDocument d;
				d.LoadXml(L"<data />"); 
				XmlElement root = d.DocumentElement();
				root.InnerText() = __ToBase64(b); 
				return d; 
			}
			_Catch() 
		}

		inline Blob ReadObject(
			const string& label, 
			CK_ULONG classType 
			) 
		{
			try
			{
				bool useCache = true; 
				//
				string id = _W(L"eTokenObject_slot") + 
					FormatStr(L"%d", SlotId) + 
					L"_cl" + FormatStr(L"%d", (int)classType) + 
					L"_label" + label 
					; 
				//
				if (useCache)
				{
					XmlDocument d; 
					if (ObjCache::GetXmlObject(id, d))
					{
						XmlElement root = d.DocumentElement();
						Blob data = FromBase64String(root.InnerText()); 
						return data; 
					}
				}
				//
				//CK_BBOOL bFalse    = 0; 
				//CK_BBOOL bTrue     = 1; 
				//
				Blob result; 
				//
				SharedArray<Blob> a1 = FindETokenObjects(SlotId, classType, 1, label); 
				if (a1.Length() > 0)
				{
					result = a1[0]; 
				}
				else
				{
					//result = Blob(); 
				}
				//
				if (useCache) 
				{
					XmlDocument d = ObjectXml(result); 
					ObjCache::AddXmlObject(id, _OC_TIMEOUT_TOKEN_OBJ, d); 
				}
				//
				return result; 
			}
			_Catch() 
		}

		static int WINAPI getch_cb(int c,int step,int from,
	#		ifdef WIN64
			void*
	#		else
			char* 
	#		endif
			//userdata
			)
		{
			///TRACE_LOG(_T("getch_cb"));
			char cc[64];
			cc[0] = (char)c;
			cc[1] = '\n';
			if (cc[0] == '\n') return -1;
			return (int)(char)cc[0];
		}

		inline void Init_CADB() 
		{
			try
			{
				static BYTE x[1024];
				static char buf[1024];
				//
				//CADB_init(); 
				//
				CCOM_Init(); 
				//
				// --> PSE context 
				// 
				//int r0 = PSE_pseudo_rand_init(0,0,0,&getch_cb,0);
				//if (r0 == 0)
				//{
				//	//long e1 = ERR_get_last_error();
				//	//if (e1 != 0) throw CComExceptionI(e1);
				//}
			}
			_Catch() 
		}

		inline void CheckForConversion() 
		{
			try
			{
				bool needConversion_v1 = false; 
				try
				{
					XmlDocument doc = PKCS11_Manager_().GetETokenInfo(L""); 
					//
					//XmlNodeList L = doc.SelectNodes(L"/*/EToken[@PinEntered = '1']"); 
					//if (L.Count() > 0) return; 
					//
					XmlNodeList L = doc.SelectNodes(
						L"/*/EToken[@Label = '' and @eTokenID='" + eTokenID + L"']" 
						); 
					if (L.Count() > 0) needConversion_v1 = true; 
				}
				catch(...) { }
				//
				string oAutoUpdate = PKI::GetOption(L"etoken-auto-convert-1"); 
				oAutoUpdate.Trim(); 
				if (oAutoUpdate == L"0") needConversion_v1 = false; 
				//
				if (needConversion_v1) 
				{
					Login();
					EnterContext(); 
					//
					Init_CADB(); 
					//
					// TODO !!!
					// ETOKEN_set_passwd_callback(EToken::etoken_passwd_cb);					
					//
					UpdateOldMetaStructures(); 
					//
					ReleaseContext(); 
				}
			}
			_Catch() 
		}

		bool m_inConversion; 

		inline Blob ReadMetaObject(const string& label) 
		{
			try
			{
				//CK_BBOOL bFalse    = 0; 
				//CK_BBOOL bTrue     = 1; 
				//
				CK_ULONG classType = CKO_DATA; 
				//
				SharedArray<Blob> a1 = FindETokenObjects(SlotId, classType, 1, label); 
				if (a1.Length() > 0)
				{
					return a1[0]; 
				}
				else
				{
					if (! m_inConversion) 
					{
						if (label == GetMetaLabelOid(OID__FREEMETA)) 
						{
							m_inConversion = true; 
							//
							CheckForConversion(); 
							//
							m_inConversion = false; 
						}
					}
					return Blob(); 
				}
			}
			_Catch() 
		}

		inline AsnObject ReadMetaObjectAsn(const string& label) 
		{
			try
			{
				Blob dataO = ReadMetaObject(label); 
				if (dataO.Length() == 0) 
				{
					string msg = L"�� ������� ������� ������ " + label; 
					throw MethodError(msg); 
				}
				return AsnObject(dataO); 
			}
			_Catch()
		}

		inline static string ShortenOid(const string& oid) 
		{
			try
			{
				string Oid = _OID; 
				//
				if (oid.Left(Oid.GetLength()) == Oid) 
				{ 
					string shortOid = Oid + oid.Right(oid.GetLength()-Oid.GetLength()); 
					return shortOid; 
				}
				else
				{
					return oid; 
				}
			}
			_Catch() 
		}

		inline static string MetaOidToLabel(const string& oid_, CK_BBOOL* out_isPrivate=0) 
		{
			try
			{
				string label; 
				CK_BBOOL isPrivate = 0; 
				//
				string oid = ShortenOid(oid_); 
				//
				if (oid == ShortenOid(OID__META)) 
				{
					label = GetMetaLabelOid(OID__META); 
					isPrivate = 1; 
				}
				else if (oid == ShortenOid(OID__FREEMETA)) 
				{
					label = GetMetaLabelOid(OID__FREEMETA); 
					isPrivate = 0; 
				}
				else if (oid == ShortenOid(OID__ETCH)) 
				{
					label = GetMetaLabelOid(OID__ETCH); 
					isPrivate = 0; 
				}
				else
				{
					string msg = L"Unknown oid=" + oid + L" for meta label"; 
					throw MethodError(msg); 
				}
				//
				if (out_isPrivate) *out_isPrivate = isPrivate; 
				return label; 
			}
			_Catch() 
		}

		inline Blob ReadMetaObjectOid(const string& oid, bool createNew=false) 
		{
			try
			{
				CK_BBOOL isPrivate; 
				string label = MetaOidToLabel(oid, &isPrivate); 
				//
				if (isPrivate) 
				{
					Login(); 
				}
				//
				Blob data = ReadMetaObject(label); 
				//
				if (data.Length() == 0 && createNew)
				{
					AsnObject O = CreateNewMeta_(oid); 
					data = O.ToBlob(); 
					//
					SaveObject(label, data, CKO_DATA, isPrivate); 
					//
					data = ReadMetaObject(label); 
				}
				//
				if (isPrivate && (oid == _W(OID__META))) 
				{
				}
				//
				return data; 
			}
			_Catch() 
		}

		inline AsnObject ReadMetaObjectOidAsn(const string& oid) 
		{
			try
			{
				Blob dataO = ReadMetaObjectOid(oid); 
				if (dataO.Length() == 0) 
				{
					string msg = L"�� ������� ������� ������ oid." + oid; 
					throw MethodError(msg); 
				}
				return AsnObject(dataO); 
			}
			_Catch()
		}

		inline XmlDocument ReadMetaObjectOidAsXml(const string& oid, bool createNew=false) 
		{
			try
			{
				PKCS11_Manager& M = PKCS11_Manager_(); 
				//
				XmlDocument doc; 
				//
				Blob dataO = ReadMetaObjectOid(oid, createNew); 
				AsnObject O(false, AsnObject::UNIVERSAL, AsnObject::_NULL_); 
				if (dataO.Length() > 0)
				{
					O = AsnObject(dataO); 
					doc = M.AsnDictionaryToXml(O); 
				}
				//
				return doc; 
			}
			_Catch() 
		}

		bool fMetaConnected; 
		bool fMetaPrivateActive; 

		XmlDocument m_FreeMeta; 
		XmlDocument m_PrivateMeta; 

		inline void ConnectMeta(bool privateA=false, bool createNew=false) 
		{
			try
			{
				if (!fMetaConnected) // ���������: �� ������ free meta, ���� ��������� ���������� private meta 
				{
					m_FreeMeta = ReadMetaObjectOidAsXml(OID__FREEMETA, createNew); 
					//
					if (!m_FreeMeta.IsEmpty())
					{
						fMetaConnected = true; 
					}
				}
				//
				if (privateA)
				{
					m_PrivateMeta = ReadMetaObjectOidAsXml(OID__META, true); 
					fMetaPrivateActive = true; 
				}
			}
			_Catch() 
		}

		inline void DisconnectMeta() 
		{
			try
			{
				fMetaPrivateActive = false; 
				fMetaConnected = false; 
			}
			_Catch() 
		}

		inline XmlDocument GetFreeMeta(bool createNew=false) 
		{
			try
			{
				if (!fMetaConnected)
				{
					ConnectMeta(false, createNew); 
				}
				return m_FreeMeta; 
			}
			_Catch() 
		}

		inline XmlDocument GetPrivateMeta() 
		{
			try
			{
				if ((!fMetaConnected) || (!fMetaPrivateActive))
				{
					ConnectMeta(true, true); 
				}
				return m_PrivateMeta; 
			}
			_Catch() 
		}

		inline void FlushMeta() 
		{
			try
			{
				FlushConstantData(); 
				//
				if (fMetaConnected) 
				{
					if (fMetaPrivateActive) 
					{
						if (!m_PrivateMeta.IsEmpty())
						{
							SaveMetaObjectOid(OID__META, m_PrivateMeta); 
						}
					}
					//
					if (!m_FreeMeta.IsEmpty())
					{
						SaveMetaObjectOid(OID__FREEMETA, m_FreeMeta); 
					}
				}
			}
			_Catch() 
		}

		inline XmlElement GetFreeKeyList(bool createNew=false) 
		{
			try
			{
#ifdef _DEBUG
				if (createNew) 
				{
					TRACE_LOG(L"!"); 
				}
#endif
				XmlDocument doc = GetFreeMeta(createNew); 
				if (doc.IsEmpty()) return XmlElement(); 
				//
				XmlElement root = doc.DocumentElement(); 
				XmlNodeList L = root.SelectNodes(L"//asn:object[@oid='" + _W(OID_KEY_LIST) + L"']"); 
				if (L.Count() == 0) 
				{
					if (createNew)
					{
						throw MethodError(L"�������������� FreeMeta: " + _W(OID_KEY_LIST)); 
					}
					else
					{
						return XmlElement(); 
					}
				}
				//
				XmlElement keyList_E = L[0]; 
				//
				XmlNodeList L2 = keyList_E.SelectNodes(L"asn:sequence"); 
				if (L2.Count() == 0) 
					throw MethodError(L"�������������� FreeMeta: " + _W(OID_KEY_LIST) + L"/sequence"); 
				//
				return keyList_E; 
			}
			_Catch() 
		}

		inline XmlElement GetPrivateKeyList() 
		{
			try
			{
				XmlDocument doc = GetPrivateMeta(); 
				XmlElement root = doc.DocumentElement(); 
				XmlNodeList L = root.SelectNodes(L"//asn:object[@oid='" + _W(OID_KEY_LIST) + L"']"); 
				if (L.Count() == 0) throw MethodError(L"�������������� FreeMeta: " + _W(OID_KEY_LIST)); 
				//
				XmlElement keyList_E = L[0]; 
				//
				XmlNodeList L2 = keyList_E.SelectNodes(L"asn:sequence"); 
				if (L2.Count() == 0) 
					throw MethodError(L"�������������� FreeMeta: " + _W(OID_KEY_LIST) + L"/sequence"); 
				//
				return keyList_E; 
			}
			_Catch() 
		}

		inline XmlElement GetKeyList_S0(XmlElement& keyList_E, const string& label) 
		{
			try
			{
				XmlNodeList L0 = keyList_E.SelectNodes(L"asn:sequence"); 
				if (L0.Count() == 0) 
					throw MethodError(L"�������� ��������� ������ ������ (" + label + L"): " 
					+ _W(OID_KEY_LIST) + L"/sequence"); 
				//
				XmlElement S0 = L0[0]; 
				//
				return S0; 
			}
			_Catch() 
		}

		inline XmlElement GetFreeKey(int key_i) 
		{
			try
			{
				XmlElement keyList_E = GetFreeKeyList(); 
				//
				XmlElement S0 = GetKeyList_S0(keyList_E, L"free"); 
				//
				XmlNodeList L = S0.SelectNodes(
					FormatStr(L"asn:sequence[position() = %d]", (int)(key_i+1) )); 
				//
				if (L.Count() == 0) 
					throw MethodError(_W(FormatStr("���� � %d �� ������ (free)", (int)key_i ))); 
				//
				XmlElement key_E = L[0]; 
				//
				int v1 = ReadIntegerObjectInS(key_E, 0); 
				if (key_i != v1) throw MethodError(L"��������� ������ �����"); 
				//
				return key_E; 
			}
			_Catch() 
		}

		inline XmlElement GetPrivateKey(int key_i) 
		{
			try
			{
				XmlElement keyList_E = GetPrivateKeyList(); 
				//
				XmlElement S0 = GetKeyList_S0(keyList_E, L"private"); 
				//
				XmlNodeList L = S0.SelectNodes(
					FormatStr(L"asn:sequence[position() = %d]", (int)(key_i+1) )); 
				//
				if (L.Count() == 0) 
					throw MethodError(_W(FormatStr("���� � %d �� ������ (private)", (int)key_i ))); 
				//
				XmlElement key_E = L[0]; 
				//
				int v1 = ReadIntegerObjectInS(key_E, 0); 
				if (key_i != v1) throw MethodError(L"��������� ������ �����"); 
				//
				return key_E; 
			}
			_Catch() 
		}

		inline int GetKeyIndex(const string& pkh64) 
		{
			try
			{
				string pkh64_n = __ToBase64(FromBase64String(pkh64));
				//
				XmlElement keyList_E = GetFreeKeyList();  
				//
				XmlNodeList L = keyList_E.SelectNodes(L"asn:sequence/asn:sequence"); 
				//
				for (int key_i = 0; key_i < L.Count(); key_i++) 
				{
					XmlElement key_E = L[key_i]; 
					string pkh64_cur = ReadTextObjectInS(key_E, 2); 
					string pkh64_cur_n = __ToBase64(FromBase64String(pkh64_cur));
					//
					if (pkh64_n == pkh64_cur_n) return key_i; 
				}
				//
				return -1; 
			}
			_Catch() 
		}

		inline void RemoveCert(const string& pkh64) 
		{
			try
			{
				int key_i = GetKeyIndex(pkh64); 
				if (key_i < 0) throw MethodError(L"Key PKH=" + pkh64 + L" not found"); 
				//
				Login(); 
				//
				string certLabel = FormatStr(L" Certificate %d", key_i); 
				//
				RemoveObject(SlotId, CKO_DATA, 1, certLabel); 
			}
			_Catch() 
		}

		inline void RemoveKey(const string& pkh64) 
		{
			try
			{
				int key_i = GetKeyIndex(pkh64); 
				if (key_i < 0) throw MethodError(L"Key PKH=" + pkh64 + L" not found"); 
				//
				Login(); 
				//
				/// int flags = Key_GetFlags(key_i); 
				Key_UnsetFlag(key_i, _KEY_FLAG_OK); 
				//
				string requestLabel = FormatStr(L" Request %d", key_i); 
				RemoveObject(SlotId, CKO_DATA, 1, requestLabel);  
				//
				string requestXLabel = FormatStr(L" Request X %d", key_i); 
				RemoveObject(SlotId, CKO_DATA, 1, requestXLabel);  
				//
				string certLabel = FormatStr(L" Certificate %d", key_i); 
				RemoveObject(SlotId, CKO_DATA, 1, certLabel);  
				// 
				FlushMeta(); 
			}
			_Catch() 
		}

		inline string Key_GetPassword(int key_i) 
		{
			try
			{
				XmlElement key_E = GetPrivateKey(key_i); 
				//
				string psw = ReadTextObjectInS(key_E, 1); 
				//
				return psw; 
			}
			_Catch() 
		}

		inline void SaveMetaObject(const string& label, CK_BBOOL isPrivate, XmlDocument asnDoc) 
		{
			try
			{
				AsnObject O = PKCS11_Manager_().XmlToAsnDictionary(asnDoc); 
				//
				//if (isPrivate) 
				{
					//O.Update(); 
					////OutputDebugStringW(O.Dump()); 
				}
				Blob Odata = O.ToBlob(); 
				//
				SaveObject(label, Odata, CKO_DATA, isPrivate); 
			}
			_Catch()
		}

		inline void SaveMetaObjectOid(const string& oid, XmlDocument asnDoc) 
		{
			try
			{
				CK_BBOOL isPrivate = 0; 
				string label = MetaOidToLabel(oid, &isPrivate); 
				//
				SaveMetaObject(label, isPrivate, asnDoc); 
			}
			_Catch()
		}

		XmlElement CreateDeviceKeysInfo(XmlDocument doc) 
		{
			try
			{
				PKCS11_Manager::Lock lock; 
				//
				XmlElement Keys_E = doc.CreateElement(L"", L"Keys", L""); 
				//
				XmlElement keyList_E = GetFreeKeyList(true); 
				//
				if (keyList_E.IsEmpty()) return Keys_E; 
				//
				XmlElement S0 = GetKeyList_S0(keyList_E, L"free"); 
				//
				XmlNodeList L = S0.SelectNodes(L"asn:sequence"); 
				//
				for (int key_i = 0; key_i < L.Count(); key_i++) 
				{
					XmlElement __key_E = L[key_i]; 
					//
					int flags = Key_GetFlags(key_i); 
					//
					if (flags & _KEY_FLAG_OK) 
					{
						string pkh64 = ReadTextObjectInS(__key_E, 2); 
						string keyTimeZ = ReadTextObjectInS(__key_E, 3); 
						string commonName = ReadTextObjectInS(__key_E, 4); 
						string orgName = ReadTextObjectInS(__key_E, 5); 
						//
						XmlElement Key_E = doc.CreateElement(L"", L"Key", L""); 
						Key_E.SetAttribute(L"PubKeyHash", _W(pkh64)); 
						Key_E.SetAttribute(L"KeyTime", _W(keyTimeZ)); 
						Key_E.SetAttribute(L"CommonName", _W(commonName)); 
						Key_E.SetAttribute(L"OrganizationName", _W(orgName)); 
						//
						{
							// Sleep(1000);
							// bool x = false;
							Blob certData = ReadCertificate(key_i); // , &x
							if (certData.Length() > 0) 
							{
								XmlElement C0 = doc.CreateElement(L"", L"C0", L""); 
								C0.InnerText() = __ToBase64(certData); 
								Key_E.AppendChild(C0); 
							}
						}
						//
						Keys_E.AppendChild(Key_E); 
					}
				}
				//
				return Keys_E; 
			}
			_Catch() 
		}

		inline Blob ReadCertificate(int key_i) 
		{
			try
			{
				string certLabel = FormatStr(L" Certificate %d", key_i); 
				//
				SharedArray<Blob> cert_a = FindETokenObjects(SlotId, 
					CKO_DATA,
					1,
					certLabel 
					); 
				if (cert_a.Length() > 0) 
				{
					Blob certData = cert_a[0]; 
					//
					return certData; 
				}
				//
				// default ie empty 
				return Blob(); 
			}
			_Catch() 
		}



		// ----
		// CRL 
		 
		inline static XmlDocument ReadCRL_1()
		{
			try
			{
				File f;
				f.Open(_S("f:\\dev\\cabinet-ca.crl")); 
				Blob b = f.ReadAll(); 
				AsnObject crl(b); 
				f.Close();
				//
				AsnObject crl_0 = crl[0];
				AsnObject listO = crl_0[5]; 
				//
				string crl_s = crl.Dump();
#				ifdef _DEBUG
				{
					//OutputDebugStringW(crl_s);
				}
#				endif
				//
				XmlDocument d;
				d.LoadXml(L"<CRLInfo><CertList /></CRLInfo>");
				XmlElement root = d.DocumentElement();
				//
				XmlElement CertList_E = root.SelectSingleNode(L"/*/CertList"); 
				//
				for (int j = 0; j < listO.ChildCount(); j++)
				{
					AsnObject itemO = listO[j];
					//
					AsnObject o1 = itemO[0];
					AsnObject o2 = itemO[1];
					//
					Blob who_b = o1.Data();
					COleDateTime t = o2.m_Time;
					//
					XmlElement item_E = d.CreateElement(L"", L"CertStateItem", L""); 
					//
					string s1 = GetHexBwd(who_b); 
					item_E.SetAttribute(_W(L"SerialNumber"), s1); 
					//
					string s2 = t.Format(_S("%A, %B %d, %Y, %H:%M:%S")); 
					item_E.SetAttribute(_W(L"ItemTime"), s2); 
					//
					CertList_E.AppendChild(item_E); 
				}
				//
				return d; 
			}
			_Catch() 
		}



		// ---- 
		// META 

		inline AsnObject CreateNewMeta() 
		{
			try
			{
				return CreateNewMeta_(OID__META); 
			}
			_Catch() 
		}

		inline AsnObject CreateNewFREEMeta() 
		{
			try
			{
				return CreateNewMeta_(OID__FREEMETA); 
			}
			_Catch() 
		}

		inline AsnObject CreateNewMeta_(const string& metaOid) 
		{
			try
			{
				if (metaOid == OID__ETCH) 
				{
					AsnObject O = AsnObject::NewSequence(); 
					//
					O.Add(AsnObject(_W(L"������� ����������� ������"))); 
					O.Add(AsnObject::NewSequence()); 
					//
					return O; 
				}
				//
				AsnObject MetaO = AsnObject::NewSequence();
				//
				// Key Info
				//
				// ���������� ���������! 
				////AsnObject KeyListPair = AsnObject::NewSequence();
				////KeyListPair.Add(AsnObject::NewInteger(0)); // � ������ 0 ������ 
				////KeyListPair.Add(AsnObject::NewSequence());
				//
				AsnObject KeyListO = AsnObject::NewSequence();
				////KeyListO.Add(KeyListPair);
				//
				AsnObject KeyListInfoPair = AsnObject::NewSequence(); 
				KeyListInfoPair.Add(AsnObject(OID(OID_KEY_LIST)));
				KeyListInfoPair.Add(KeyListO);
				//
				AsnObject KeyListInfoO = AsnObject::NewSequence();
				KeyListInfoO.Add(AsnObject(OID(OID_KEY_LIST_INFO))); 
				KeyListInfoO.Add(KeyListInfoPair); 
				//
				//  Meta
				//
				MetaO.Add(AsnObject(OID(metaOid))); 
				MetaO.Add(KeyListInfoO); 
				//
				return MetaO; 
			}
			_Catch()
		}

		string EToken_GetOldKeyPath(int slotId, int key_i) 
		{
			try
			{
				return FormatStr(_W(_ETOKEN_ROOT) + L"/" + _ETOKEN_KEYDIR_PREFIX + L"%03d", key_i)
					+ L"/fa01"; 
			}
			_Catch()
		}


		string EToken_GetOldCertPath(int slotId, int key_i) 
		{
			try
			{
				return FormatStr(_W(_ETOKEN_ROOT) + L"/" + _ETOKEN_KEYDIR_PREFIX + L"%03d", key_i)
					+ L"/fc01"; 
			}
			_Catch()
		}

		string EToken_GetOldRequestPath(int slotId, int key_i) 
		{
			try
			{
				return FormatStr(_W(_ETOKEN_ROOT) + L"/" + _ETOKEN_KEYDIR_PREFIX + L"%03d", key_i)
					+ L"/fe01"; 
			}
			_Catch()
		}

		string EToken_GetOldRequestPath_X(int slotId, int key_i) 
		{
			try
			{
				return FormatStr(_W(_ETOKEN_ROOT) + L"/" + _ETOKEN_KEYDIR_PREFIX + L"%03d", key_i)
					+ L"/fe02"; 
			}
			_Catch()
		}

		inline void UpdateOldMetaStructures() 
		{
			try
			{
				CStringA metaPathA = PKCS11_Manager::ETokenPath__(
					SlotId, PKCS11_Manager::MetaPath(0)); // private 

				XmlElement keyList_E = GetFreeKeyList(true); 
				//
				// ----
				// ������������ 
				//
				XmlDocument chDoc = ReadMetaObjectOidAsXml(OID__ETCH, true); 
				XmlElement ch = chDoc.DocumentElement(); 
				//
				XmlElement ch_S = ch.SelectSingleNode(L"*/asn:sequence"); 
				//
				// AsnObject oldMetaO = MetaObject_E_1_(SlotId); 
				//
				bool needFlush = false; 
				//
				//int size = CADB_file_size(metaPathA.GetBuffer()); 
				Blob b;
				b.Allocate(16 * 1024);
				//int r2 = 
				CADB_read_file(metaPathA.GetBuffer(), (char*)b.GetBuffer(), b.Length()); 
				//int e1 = ERR_get_last_error(); 
				AsnObject MetaO(b);
				//
				AsnObject& KeyListInfoO = MetaO.Children[OID(OID_KEY_LIST_INFO)]; 
				AsnObject& KeyListO = KeyListInfoO.Children[OID(OID_KEY_LIST)];
				//
				AsnObject& KeysO = ((AsnObject&) KeyListO[1])[0]; 
				//
				int keyNum = ((AsnObject&) KeysO[0]).m_Integer; 
				AsnObject& keySeq = KeysO[1]; 
				for (int i = 0; i < keyNum; i++)
				{
					AsnObject& k = keySeq[i]; 
					if (k.IsConstructed())
					{
						if (k.ChildCount() > 0)
						{
							int flags = ((AsnObject&)k[0]).m_Integer; 
							if (flags & _KEY_FLAG_OK ) 
							{
								// PKCS11_Manager::OutputObject(L"KEY record (old format meta)", k ); 
								// keyNums.Add(i); 
								//
								string keyContainerPwd = ((AsnObject&)k[1]).m_text; 
								//
								bool key_f = false; 
								bool req_f = false; 
								bool reqX_f = false; 
								bool cert_f = false; 
								//
								AsnObject keyO = AsnObject::NewSequence(); 
								AsnObject reqO = AsnObject::NewSequence(); 
								Blob requestData; 
								Blob reqXData; 
								Blob certData; 
								//
								try
								{
									CStringA keyPathA = ETokenPath(EToken_GetOldKeyPath(SlotId, i) ); 
									//
									Blob bKey; 
									int size = CADB_file_size(keyPathA.GetBuffer()); 
									bKey.Allocate(size);
									int r3 = CADB_read_file(keyPathA.GetBuffer(), 
										(char*)bKey.GetBuffer(), bKey.Length()); 
									//int e3 = ERR_get_last_error(); 
									if (r3 > 0)
									{
										keyO = AsnObject(bKey);
										////PKCS11_Manager::OutputObject(L"KEY object", keyO ); 
										key_f = true; 
									}
								}
								catch(...) { }
								//
								try
								{
									CStringA pathA = ETokenPath(EToken_GetOldRequestPath(SlotId, i) ); 
									//
									Blob b; 
									int size = CADB_file_size(pathA.GetBuffer()); 
									if (size > 0)
									{
										b.Allocate(size);
										// int r3 = 
										CADB_read_file(pathA.GetBuffer(), 
											(char*)b.GetBuffer(), b.Length()); 
										//int e3 = ERR_get_last_error(); 
										requestData = b; 
										reqO = AsnObject(requestData); 
										////PKCS11_Manager::OutputObject(L"REQUEST object", reqO ); 
										req_f = true; 
									}
								}
								catch(...) { }
								//								
								try
								{
									CStringA pathA = ETokenPath(EToken_GetOldRequestPath_X(SlotId, i) ); 
									//
									Blob b; 
									int size = CADB_file_size(pathA.GetBuffer()); 
									if (size > 0)
									{
										b.Allocate(size); 
										// int r3 = 
										CADB_read_file(pathA.GetBuffer(), 
											(char*)b.GetBuffer(), b.Length()); 
										//int e3 = ERR_get_last_error(); 
										reqXData = b;
										//PKCS11_Manager::OutputObject(L"REQUEST object", reqXO ); 
										reqX_f = true; 
									}
								}
								catch(...) { }
								//								
								try
								{
									CStringA pathA = ETokenPath(EToken_GetOldCertPath(SlotId, i) ); 
									//
									Blob b; 
									int size = CADB_file_size(pathA.GetBuffer()); 
									if (size > 0)
									{
										b.Allocate(size); 
										//int r3 = 
										CADB_read_file(pathA.GetBuffer(), 
											(char*)b.GetBuffer(), b.Length()); 
										//int e3 = ERR_get_last_error(); 
										certData = b; 
										//PKCS11_Manager::OutputObject(L"REQUEST object", certO ); 
										cert_f = true; 
									}
								}
								catch(...) { }
								//								
								if (key_f && req_f && reqX_f) 
								{
									NameDescription subject = reqO.Subject;
									SharedPtr<AsnObject> spAttr = subject.GetAttribute(OID(X500().sCommonNameOid)); 
									string CN = spAttr->m_text; 
									//
									string orgName; 
									spAttr = subject.GetAttribute(OID(X500().sOrganizationNameOid)); 
									if (! spAttr.IsEmpty())
									{
										orgName = spAttr->m_text; 
									}
									//
									AsnObject keyDataEnvO = keyO; 
									AsnObject& keyData = keyDataEnvO[1]; 
									AsnObject& keyAttrs = keyData[0];
									AsnObject& keyValues = keyData[1];
									//
									string keyTime_s = ((AsnObject&)keyAttrs[0]).m_text; 
									//int pkParameters = ((AsnObject&)keyAttrs[1]).m_Integer; 
									//int sBox = ((AsnObject&)keyAttrs[2]).m_Integer; 
									AsnObject& oPKH = keyAttrs[3];
									Blob pkh = oPKH.Data();
									string pkh64 = __ToBase64(pkh); 
									string pass = ((AsnObject&)keyAttrs[4]).m_text; 
									//
									AsnObject& oEK = keyValues[0];
									Blob EK = oEK.Data();
									//
									AsnObject& oMac = keyValues[1];
									Blob Mac = oMac.Data();
									//
									AsnObject& oPK = keyValues[2];
									Blob PK = oPK.Data();
									//
									bool addKey_f = true; 
									//
									if (! keyList_E.IsEmpty()) 
									{
										/// throw MethodError(L"���������� ���������� �����������. �� eToken ������������ �����, ��������� �� ����� �����"); 
										//
										XmlElement S0 = GetKeyList_S0(keyList_E, L"free");  
										//
										XmlNodeList L = S0.SelectNodes(L"asn:sequence"); 
										//
										for (int key_i = 0; key_i < L.Count(); key_i++) 
										{
											XmlElement __key_E = L[key_i]; 
											//
											string ex_pkh64 = ReadTextObjectInS(__key_E, 2); 
											if (ex_pkh64 == pkh64) 
											{
												addKey_f = false; 
											}
										} 
									}
									//
									XmlNodeList L1 = ch_S.SelectNodes(
										L"asn:object[@TextV='" + pkh64 + L"']" 
										); 
									if (L1.Count() > 0) addKey_f = false; 
									//
									if (addKey_f) 
									{
										int key_i = 0;  
										CStringA pathA = NewKeyPath_tS(
											keyContainerPwd, 
											keyTime_s, 
											CN, 
											orgName, 
											&key_i 
											); 
										//
										XmlElement privateKey_E = GetPrivateKey(key_i); 
										XmlDocument doc = privateKey_E.OwnerDocument(); 
										//
										//OutputDebugStringW(privateKey_E.OuterXml()); 
										//
										XmlElement new_prvKey_E = PKCS11_Manager_().AsnObjToXmlElement(
											keyO, doc); 
										//
										XmlNodeList L1 = privateKey_E.SelectNodes(L"*"); 
										XmlNode prvKey_E = L1[1]; 
										privateKey_E.ReplaceChild(new_prvKey_E, prvKey_E); 
										//
										// Request and Certificate 
										//
										if (req_f)
										{
											string reqLabel = FormatStr(L" Request %d", (int)key_i ); 
											SaveObject(reqLabel, requestData, CKO_DATA, 0); 
										}
										//
										if (reqX_f) 
										{
											string reqXLabel = FormatStr(L" Request X %d", (int)key_i ); 
											SaveObject(reqXLabel, reqXData, CKO_DATA, 0); 
										}
										//
										if (cert_f) 
										{
											string certLabel = FormatStr(L" Certificate %d", (int)key_i ); 
											SaveObject(certLabel, certData, CKO_DATA, 0); 
										}
										//
										XmlElement E = CreateTextObject(chDoc, pkh64); 
										ch_S.AppendChild(E); 
										//
										needFlush = true; 
									}
								}
							}
						}
					}
				}
				//
				if (needFlush) 
				{
					SaveMetaObjectOid(OID__ETCH, chDoc); 
					//
					FlushMeta(); 
				}
			}
			_Catch() 
		}

		//////inline void LoadKeys(XmlDocument doc)
		//////{
		//////	try
		//////	{
		//////		XmlElement root = doc.DocumentElement(); 
		//////		XmlNodeList L = root.SelectNodes(L"/*/KeyInfo[CertificateInfo]"); 
		//////		for (int key_i = 0; key_i < L.Count(); key_i++) 
		//////		{
		//////			XmlElement KeyInfo_E = L[key_i]; 
		//////			//
		//////			string pkh = KeyInfo_E.GetAttribute(L"PubKeyHash"); 
		//////			//
		//////			// ...
		//////			//
		//////			NameDescription subject = reqO.Subject;
		//////			SharedPtr<AsnObject> spAttr = subject.GetAttribute(OID(X500().sCommonNameOid)); 
		//////			string CN = spAttr->m_text; 
		//////			//
		//////			string orgName; 
		//////			spAttr = subject.GetAttribute(OID(X500().sOrganizationNameOid)); 
		//////			if (! spAttr.IsEmpty())
		//////			{
		//////				orgName = spAttr->m_text; 
		//////			}
		//////			//
		//////			AsnObject keyDataEnvO = keyO; 
		//////			AsnObject& keyData = keyDataEnvO[1]; 
		//////			AsnObject& keyAttrs = keyData[0];
		//////			AsnObject& keyValues = keyData[1];
		//////			//
		//////			string keyTime_s = ((AsnObject&)keyAttrs[0]).m_text; 
		//////			//int pkParameters = ((AsnObject&)keyAttrs[1]).m_Integer; 
		//////			//int sBox = ((AsnObject&)keyAttrs[2]).m_Integer; 
		//////			AsnObject& oPKH = keyAttrs[3];
		//////			Blob pkh = oPKH.Data();
		//////			string pkh64 = __ToBase64(pkh); 
		//////			string pass = ((AsnObject&)keyAttrs[4]).m_text; 
		//////			//
		//////			AsnObject& oEK = keyValues[0];
		//////			Blob EK = oEK.Data();
		//////			//
		//////			AsnObject& oMac = keyValues[1];
		//////			Blob Mac = oMac.Data();
		//////			//
		//////			AsnObject& oPK = keyValues[2];
		//////			Blob PK = oPK.Data();
		//////			//
		//////			bool addKey_f = true; 
		//////			//
		//////			if (! keyList_E.IsEmpty()) 
		//////			{
		//////				/// throw MethodError(L"���������� ���������� �����������. �� eToken ������������ �����, ��������� �� ����� �����"); 
		//////				//
		//////				XmlElement S0 = GetKeyList_S0(keyList_E, L"free");  
		//////				//
		//////				XmlNodeList L = S0.SelectNodes(L"asn:sequence"); 
		//////				//
		//////				for (int key_i = 0; key_i < L.Count(); key_i++) 
		//////				{
		//////					XmlElement __key_E = L[key_i]; 
		//////					//
		//////					string ex_pkh64 = ReadTextObjectInS(__key_E, 2); 
		//////					if (ex_pkh64 == pkh64) 
		//////					{
		//////						addKey_f = false; 
		//////					}
		//////				} 
		//////			}
		//////			//
		//////			XmlNodeList L1 = ch_S.SelectNodes(
		//////				L"asn:object[@TextV='" + pkh64 + L"']" 
		//////				); 
		//////			if (L1.Count() > 0) addKey_f = false; 
		//////			//
		//////			if (addKey_f) 
		//////			{
		//////				int key_i = 0;  
		//////				CStringA pathA = NewKeyPath_tS(
		//////					keyContainerPwd, 
		//////					keyTime_s, 
		//////					CN, 
		//////					orgName, 
		//////					&key_i 
		//////					); 
		//////				//
		//////				XmlElement privateKey_E = GetPrivateKey(key_i); 
		//////				XmlDocument doc = privateKey_E.OwnerDocument(); 
		//////				//
		//////				//OutputDebugStringW(privateKey_E.OuterXml()); 
		//////				//
		//////				XmlElement new_prvKey_E = PKCS11_Manager_().AsnObjToXmlElement(
		//////					keyO, doc); 
		//////				//
		//////				XmlNodeList L1 = privateKey_E.SelectNodes(L"*"); 
		//////				XmlNode prvKey_E = L1[1]; 
		//////				privateKey_E.ReplaceChild(new_prvKey_E, prvKey_E); 
		//////				//
		//////				// Request and Certificate 
		//////				//
		//////				if (req_f)
		//////				{
		//////					string reqLabel = FormatStr(L" Request %d", (int)key_i ); 
		//////					SaveObject(reqLabel, requestData, CKO_DATA, 0); 
		//////				}
		//////				//
		//////				if (reqX_f) 
		//////				{
		//////					string reqXLabel = FormatStr(L" Request X %d", (int)key_i ); 
		//////					SaveObject(reqXLabel, reqXData, CKO_DATA, 0); 
		//////				}
		//////				//
		//////				if (cert_f) 
		//////				{
		//////					string certLabel = FormatStr(L" Certificate %d", (int)key_i ); 
		//////					SaveObject(certLabel, certData, CKO_DATA, 0); 
		//////				}
		//////				//
		//////				XmlElement E = CreateTextObject(chDoc, pkh64); 
		//////				ch_S.AppendChild(E); 
		//////				//
		//////				needFlush = true; 
		//////			}
		//////		}
		//////	}
		//////	_Catch() 
		//////}

		//inline void Parse() 
		//{
		//	try
		//	{
		//		AsnObject& MetaO = m_Objects[_PRIVATE_META]; 
		//		AsnObject& FreeO = m_Objects[_FREE_META]; 
		//		//
		//		AsnObject& MetaO_KeyListInfo = MetaO.Children[OID(OID_KEY_LIST_INFO)]; 
		//		AsnObject& MetaO_KeyList = MetaO_KeyListInfo.Children[OID(OID_KEY_LIST)];
		//		AsnObject& MetaO_Keys = ((AsnObject&) MetaO_KeyList[1])[0];
		//		int MetaO_keyNum = ((AsnObject&) MetaO_Keys[0]).m_Integer; 
		//		AsnObject& MetaO_keySeq = MetaO_Keys[1]; 
		//		//
		//		AsnObject& FreeO_KeyListInfo = FreeO.Children[OID(OID_KEY_LIST_INFO)]; 
		//		AsnObject& FreeO_KeyList = FreeO_KeyListInfo.Children[OID(OID_KEY_LIST)];
		//		AsnObject& FreeO_Keys = ((AsnObject&) FreeO_KeyList[1])[0];
		//		int FreeO_keyNum = ((AsnObject&) FreeO_Keys[0]).m_Integer; 
		//		AsnObject& FreeO_keySeq = FreeO_Keys[1]; 
		//		//
		//		if (FreeO_keyNum < MetaO_keyNum)
		//		{
		//			for (int key_i = FreeO_keyNum; key_i < MetaO_keyNum; key_i++)
		//			{
		//				AsnObject f = AsnObject::NewSequence
		//			}
		//			//
		//			needUpdate = true; 
		//		}
		//	}
		//	_Catch() 
		//}

		inline static string GetMetaLabelOid(const string& oid) 
		{
			try
			{
				string label;
				if (oid == _W(OID__FREEMETA)) label = L" Cabinet F"; 
				else if (oid == _W(OID__META)) label = L" Cabinet"; 
				else if (oid == _W(OID__ETCH)) label = L" Conv History"; 
				return label; 
			}
			_Catch() 
		}
//
//		inline void SaveMeta_M(int slotId, int key_mode, int isFree, AsnObject& MetaO)
//		{
//			try
//			{
//				Lock lock; 
//				//
//				Blob MetaData = MetaO.ToBlob(); 
//				//
//				string label = GetMetaLabel(isFree); 
//				//
//#				ifdef _DEBUG
//				{
//					PKCS11_Manager::OutputObject(label, MetaO); 
//				}
//#				endif
//				//
//				if (key_mode == 1)
//				{
//					CStringA metaPathA = PKCS11_Manager::ETokenPath(slotId, PKCS11_Manager::MetaPath(isFree)); 
//					//
//					 CStringA rootPathA = PKCS11_Manager::ETokenPath(slotId, PKCS11_Manager::RootPath()); 
//					 int r0 = CADB_mkdir(rootPathA.GetBuffer()); 
//					 if (r0 != 1)
//					 {
//						int e1 = ERR_get_last_error();
//						string errMsg = FormatStr(L"������ CCOM: %d (CADB_mkdir)", (int)e1 ); 
//						throw MethodError(errMsg); 
//					 }
//					
//					//int r01 = 
//						CADB_is_dir("etoken:/f45d/"); 
//					
//					int n = MetaData.Length(); 
//					int r1 = CADB_write_file(metaPathA.GetBuffer(), 
//						(char*)MetaData.GetBuffer(), n); 
//					if (r1 <= 0)
//					{
//						int e1 = ERR_get_last_error();
//						string errMsg = FormatStr(L"������ CCOM: %d (CADB_write_file)", (int)e1 );
//						throw MethodError(errMsg); 
//					}
//				}
//				else
//				{
//					CK_BBOOL isPrivate = 1; 
//					if (isFree == 1) isPrivate = 0;
//					//
//					//SaveObject(slotId, label, MetaData, CKO_DATA, isPrivate); 
//				}
//			}
//			_Catch()
//		}

		AsnObject MetaObject_E_1_(int slotId) 
		{
			try
			{
				//int key_mode = 1; 
				//
				//CStringA metaPathA = PKCS11_Manager::ETokenPath__(
				//	slotId, PKCS11_Manager::MetaPath(0)); // private 
				CStringA metaPathA = PKCS11_Manager::ETokenPath__2(
					slotId, PKCS11_Manager::MetaPath(0)); // private 
				//
				//if (CADB_file_exists(metaPathA.GetBuffer()))
				//{
					//int size = CADB_file_size(metaPathA.GetBuffer()); 
					Blob b;
					b.Allocate(16 * 1024);
					//int r1 = 
					CADB_read_file(metaPathA.GetBuffer(), (char*)b.GetBuffer(), b.Length()); 
					//int e1 = ERR_get_last_error(); 
					AsnObject MetaO(b);
					//
					return MetaO;
				//}
				//else
				//{
				//	return AsnObject::NewSequence(); 
				//}
			}
			_Catch() 
		}

		//AsnObject MetaObject_E_2_(int slotId, int isFreeEtc, bool mount=true) 
		//{
		//	try
		//	{
		//		int key_mode = 2; 
		//		//
		//		string l1 = GetMetaLabel(isFreeEtc); 
		//		//
		//		Blob MetaData = ReadObject(slotId, l1, CKO_DATA); 
		//		//
		//		if (MetaData.Length() > 0) 
		//		{
		//			AsnObject MetaO(MetaData);
		//			//
		//			return MetaO;
		//		}
		//		else
		//		{
		//			if (!mount)
		//			{
		//				return AsnObject(false, AsnObject::UNIVERSAL, AsnObject::_NULL_); 
		//			}
		//			//
		//			MountMetaObjects(slotId, key_mode); 
		//			//
		//			return MetaObject_E_1_(slotId, isFreeEtc, false); 
		//		}
		//	}
		//	_Catch() 
		//}

		inline void AddKeyInfo( 
			XmlElement& CommonKeyInfo_E, 
			// Blob lookupPkh, 
			const Map<string, string>& filter 
			) 
		{
			try
			{
				//PKCS11_Manager& M = PKCS11_Manager_(); 
				////
				//Blob freeMetaData = ; 
				////
				//AsnObject freeMeta(freeMetaData); 
				//// 
				//XmlDocument doc = GetFreeMeta(); // M.AsnDictionaryToXml(freeMeta); 
				//if (freeMetaData.Length() == 0) return; // No keys! 
				////
				//XmlElement root = doc.DocumentElement(); 
				//
				XmlElement keyList_E = GetFreeKeyList(); 
				//
				if (!keyList_E.IsEmpty())
				{
					////OutputXml(keyList_E.OuterXml(), L"keyList_E"); 
					//
					XmlNodeList L = keyList_E.SelectNodes(
						L"asn:sequence/asn:sequence"); // ���� ������� �������� ����� 
					int n = L.Count(); 
					for (int k = 0; k < n; k++)
					{
						int flags = Key_GetFlags(k); 
						//
						if (flags & _KEY_FLAG_OK) 
						{
							AddOneKeyInfo(CommonKeyInfo_E, k, filter); 
						}
					} 
				}
			}
			_Catch() 
		}

		inline XmlElement CreateKeyInfo(XmlDocument doc, 
			const string& cryptoSystem, 
			const string& keyMediaType)
		{
			XmlElement keyInfo = doc.CreateElement(L"",L"KeyInfo",L"");
			//
			keyInfo.SetAttribute(L"CryptoSystem",cryptoSystem);
			keyInfo.SetAttribute(L"KeyMediaType",keyMediaType);
			//
			return keyInfo;
		}

		inline void AddOneKeyInfo(XmlElement& CommonKeyInfo_E, 
			int key_i, 
			const Map<string,string>& filter
			) 
		{
			try
			{
				XmlDocument doc = CommonKeyInfo_E.OwnerDocument();
				XmlElement keyInfo = CreateKeyInfo(doc,L"CryptoCOM",L"eToken");
				//
				keyInfo.SetAttribute(L"KeyNum",FormatStr(L"%d", (int)key_i ));
				keyInfo.SetAttribute(L"ETokenSlotId",FormatStr(L"%d", (int)SlotId ));
				keyInfo.SetAttribute(L"eTokenID", eTokenID); 
				//keyInfo.SetAttribute(L"KeyName",string(keyName));
				//
				// ��������� ���������� � �����
				//
				//string pkh64;
				//
				//XmlElement key_E = GetPrivateKey(key_i); 
				//OutputXml(key_E.OuterXml(), L"key_E"); 
				//
				//XmlElement keyEnv_E = key_E.SelectSingleNode(
				//	_W(L"asn:object[@oid='") + OID_KEY_ENV + L"']"); 
				////
				//XmlElement pkh_oE = keyEnv_E.SelectSingleNode(
				//	L"asn:sequence[position()=1]/asn:sequence[position()=1]"
				//	L"/asn:object[position()=4]"
				//	); 
				//pkh64 = pkh_oE.InnerText(); 
				////
				//XmlElement time_oE = keyEnv_E.SelectSingleNode(
				//	L"asn:sequence[position()=1]/asn:sequence[position()=1]"
				//	L"/asn:object[position()=1]"
				//	); 
				//string keyTime_s = time_oE.GetAttribute(L"TextV"); 
				//
				//int pkParameters = ((AsnObject&)keyAttrs[1]).m_Integer; 
				//int sBox = ((AsnObject&)keyAttrs[2]).m_Integer; 
				//AsnObject& oPKH = keyAttrs[3];
				//Blob pkh = oPKH.Data();
				//pkh64 = __ToBase64(pkh); 
				//string pass = ((AsnObject&)keyAttrs[4]).m_text; 
				////
				//AsnObject& oEK = keyValues[0];
				//Blob EK = oEK.Data();
				////
				//AsnObject& oMac = keyValues[1];
				//Blob Mac = oMac.Data();
				////
				//AsnObject& oPK = keyValues[2];
				//Blob PK = oPK.Data();
				//
				//
				//
				XmlElement key_E = GetFreeKey(key_i); 
				string pkh64 = ReadTextObjectInS(key_E, 2); 
				string keyTime_s = ReadTextObjectInS(key_E, 3); 
				//
				keyInfo.SetAttribute(L"PubKeyHash", pkh64);
				keyInfo.SetAttribute(L"KeyTime", keyTime_s); 
				//
				//if (lookupPkh.Length() > 0)
				//{
				//	string activePkh64 = __ToBase64String(lookupPkh);
				//	if (
				//		(activePkh64 == pkh64) || 
				//		(_W(activePkh64+L"=") == pkh64) || 
				//		(activePkh64 == _W(pkh64+L"="))
				//		)
				//	{
				//		CComBSTR bstrOn(L"true");  
				//		keyInfo.SetAttribute(L"IsActive",CComVariant(bstrOn)); 
				//	}
				//}
				//
				// ----
				// ����������� ���������� � �����? 
				//
				//%//
				//if (filter.ContainsKey(L"special-export-key"))
				//{
				//	AddOneETokenKeyFiles_M(slotId, key_i, key_mode, keyInfo, doc, filter); 
				//}
				//
				// ----
				// ��������� ���������� � ������ 
				//
				AddOneReqAndCertInfo(keyInfo, key_i, pkh64, doc); 
				//
				CommonKeyInfo_E.AppendChild(keyInfo); 
				//
				//return keyInfo;
			}
			_Catch() 
		}

		inline void AddOneReqAndCertInfo( 
			XmlElement& keyInfo, 
			int key_i, 
			const string& pkh64, 
			XmlDocument doc 
			) 
		{
			try
			{
				int buflen = 16 * 1024; 
				//
				bool certFound = false; 
				//
				Blob certData;
				certData.Expand(buflen); 
				//
				string certLabel = FormatStr(L" Certificate %d", key_i); 
				//
				SharedArray<Blob> cert_a = FindETokenObjects(SlotId, 
					CKO_CERTIFICATE,
					1,
					certLabel 
					); 
				if (cert_a.Length() > 0) 
				{
					certData = cert_a[0]; 
					//
					XmlElement C0 = doc.CreateElement(L"", L"C0", L""); 
					C0.InnerText() = __ToBase64(certData); 
					keyInfo.AppendChild(C0);
					//
					certFound = true;
					///CCOM_Certificate cert;
					//try
					//{
						///cert->Import(certData);
						//
						//string certPkh64 = __ToBase64String(cert->GetPKH());
						//if (
						//	((certPkh64 == pkh64) || (certPkh64+L"=" == pkh64) || (certPkh64 == pkh64+L"="))
						//	|| (pkh64.GetLength() == 0)
						//	)
						//{
							//
							// ---- 
							// ��������� ����������� 
							//
							//PrepareCertAttributesForXml(CertInfo_E, certData, cert); 
						//}
					//}
					//catch(Exception& e)
					//{
					//	TRACE_LOG(e.ToString()); 
					//	throw; 
					//}
					//catch(...)
					//{
					//	throw MethodError(_T("����������� ������!")); 
					//}
				}
				//
				// ----
				// ��������� ������
				//
				AsnObject request = AsnObject::NewSequence();
				AsnObject requestXO = AsnObject::NewSequence();
				//
				bool reqFound = false; 
				{
					Blob reqData;
					reqData.Expand(buflen); 
					//
					string reqLabel = FormatStr(L" Request %d", key_i); 
					//
					SharedArray<Blob> req_a = FindETokenObjects(SlotId, 
						CKO_DATA,
						1,
						reqLabel 
						); 
					//
					if (req_a.Length() > 0)
					{
						Blob reqData = req_a[0]; 
						//
						request = AsnObject(reqData);
						//
						Blob reqXOData;
						string reqXLabel = FormatStr(L" Request X %d", key_i); 
						//
						SharedArray<Blob> reqx_a = FindETokenObjects(SlotId, 
							CKO_DATA,
							1,
							reqXLabel 
							); 
						//
						if (reqx_a.Length() > 0) 
						{
							reqXOData = reqx_a[0]; 
							requestXO = AsnObject(reqXOData); 
						}
						//
						reqFound = true;
					}
				}
				//
				if (reqFound)
				{
					XmlDocument requestInfo = PKI::GetRequestInfo(request, requestXO);
					XmlElement ri = requestInfo.DocumentElement();
					keyInfo.AppendChild(ri);
					if (! ri.IsEmpty())
					{
						string pkh64 = ((XmlElement)ri.SelectSingleNode(L"CertificateInfo"))
							.GetAttribute(L"PubKeyHash");
						//
						keyInfo.SetAttribute(L"PubKeyHash",pkh64);
					}
				}
				//
				// return certFound; 
			}
			_Catch() 
		}

		inline int Key_GetFlags(int key_i) 
		{
			try
			{
				XmlElement key_E = GetFreeKey(key_i); 
				//
				int flags = ReadIntegerObjectInS(key_E, 1); 
				//
				return flags; 
			}
			_Catch() 
		}

		inline void Key_SetFlag(int key_i, int flag) 
		{
			try
			{
				int flags = Key_GetFlags(key_i); 
				flags = flags | flag; 
				//
				Key_SetFlags(key_i, flags); 
			}
			_Catch() 
		}

		inline void Key_UnsetFlag(int key_i, int flag) 
		{
			try
			{
				int flags = Key_GetFlags(key_i); 
				if (flags & flag) flags = flags ^ flag; 
				//
				Key_SetFlags(key_i, flags); 
			}
			_Catch() 
		}

		inline void Key_SetFlags(int key_i, int flags) 
		{
			try
			{
				XmlElement key_E = GetFreeKey(key_i); 
				//
				WriteIntegerObjectInS(key_E, 1, flags); 
			}
			_Catch() 
		}





		// --------------------------------------------------------------------------------------- 
		// Keys 

		//inline AsnObject& Key_pFindObjectInMeta(AsnObject& MetaO, int i) 
		//{
		//	try
		//	{
		//		AsnObject& KeyListInfoO = MetaO.Children[OID(OID_KEY_LIST_INFO)]; 
		//		AsnObject& KeyListO = KeyListInfoO.Children[OID(OID_KEY_LIST)];
		//		AsnObject& KeySeqO = (AsnObject&) KeyListO[1]; 
		//		AsnObject& keyO = KeySeqO[i]; 
		//		//
		//		return keyO; 
		//	}
		//	_Catch() 
		//}

		//inline AsnObject& Key_pGetObject(int key_i, int index) 
		//{
		//	AsnObject& MetaO = GetMetaObject(index); 
		//	//
		//	AsnObject& keyO = Key_pFindObjectInMeta(MetaO, key_i); 
		//	//
		//	return keyO; 
		//}

		//inline AsnObject& Key_GetPrivateObject(int key_i) 
		//{
		//	AsnObject& keyO = Key_pGetObject(key_i, _PRIVATE_META); 
		//	return keyO; 
		//}

		//inline AsnObject& Key_GetFreeObject(int key_i) 
		//{
		//	AsnObject& keyO = Key_pGetObject(key_i, _FREE_META); 
		//	return keyO; 
		//}

		//inline void ETokenFlagOff(int slotId, int key_i, int key_mode, int isFreeEtc, int f) 
		//{
		//	try
		//	{
		//		AsnObject& k = Key_GetFreeObject(key_i); 
		//		//
		//		int flags = ((AsnObject&)k[_KEY_OBJ_I_FLAGS]).m_Integer; 
		//		//
		//		flags = flags & (! f); 
		//		((AsnObject&)k[_KEY_OBJ_I_FLAGS]).m_Integer = flags; 
		//		//
		//		// saving...
		//		// 
		//		SaveMeta(); 
		//	}
		//	_Catch() 
		//}

		//string EToken_NewPath_A(int slotId, int key_mode, int* out_id=0, const string& keyContainerPwd=L"") 
		//{
		//	try
		//	{
		//		string path; 
		//		//
		//		if (key_mode == 1 || key_mode == 2)
		//		{
		//			int id = EToken_NewKeyId(slotId, key_mode, keyContainerPwd); 
		//			//
		//			string P = EToken_GetKeyContainerPath_U(slotId, id); 
		//			//
		//			if (out_id) *out_id = id; 
		//			//
		//			path = _W(ETokenPath(slotId, P));
		//		}
		//		else
		//		{
		//			string errMsg = FormatStr(L"��������� �������� KeyMode=%d", (int)key_mode );  
		//			throw MethodError(errMsg); 
		//		}
		//		//
		//		return path; 
		//	}
		//	_Catch() 
		//}

		int ReadIntegerObjectInS(XmlElement E, int i) 
		{
			try
			{
				XmlNodeList L = E.SelectNodes(L"asn:object"); 
				XmlElement A = L[i]; 
				//
				if (A.GetAttribute(L"Tag") == L"Integer") 
				{
					string vStr = A.GetAttribute(L"IntegerV"); 
					return _wtoi(vStr); 
				}
				else
				{
					throw MethodError(L"��������� ���"); 
				}
			}
			_Catch()
		}

		inline void WriteIntegerObjectInS(XmlElement E, int i, int v) 
		{
			try
			{
				XmlNodeList L = E.SelectNodes(L"asn:object"); 
				XmlElement A = L[i]; 
				//
				if (A.GetAttribute(L"Tag") == L"Integer") 
				{
					string vStr = FormatStr(L"%d", (int)v );
					A.SetAttribute(L"IntegerV", vStr); 
				}
				else
				{
					throw MethodError(L"��������� ���"); 
				}
			}
			_Catch()
		}

		string ReadTextObjectInS(XmlElement E, int i) 
		{
			try
			{
				XmlNodeList L = E.SelectNodes(L"asn:object"); 
				XmlElement A = L[i]; 
				//
				//if (PKCS11_Manager_().AsnTagIsText(A.GetAttribute(L"Tag"))) 
				if (true)
				{
					string vStr = A.GetAttribute(L"TextV"); 
					return vStr; 
				}
				else
				{
					throw MethodError(L"��������� ���"); 
				}
			}
			_Catch()
		}

		inline void WriteTextObjectInS(XmlElement E, int i, const string& v) 
		{
			try
			{
				XmlNodeList L = E.SelectNodes(L"asn:object"); 
				XmlElement A = L[i]; 
				//
				//if (AsnTagIsText(A.GetAttribute(L"Tag"))) 
				if (true)
				{
					A.SetAttribute(L"TextV", v); 
				}
				else
				{
					throw MethodError(L"��������� ���"); 
				}
			}
			_Catch()
		}

		XmlElement CreateIntegerObject(XmlDocument doc, int x) 
		{
			try
			{
				XmlElement A = doc.CreateElement(L"asn", L"object", AsnNsUri); 
				A.SetAttribute(L"AsnClass", _W(L"UNIVERSAL")); 
				A.SetAttribute(L"Tag", _W(L"Integer")); 
				A.SetAttribute(L"IntegerV", FormatStr(L"%d", (int)x )); 
				return A; 
			}
			_Catch()
		}

		XmlElement CreateTextObject(XmlDocument doc, const string& text) 
		{
			try
			{
				XmlElement A = doc.CreateElement(L"asn", L"object", AsnNsUri); 
				A.SetAttribute(L"AsnClass", _W(L"UNIVERSAL")); 
				A.SetAttribute(L"Tag", _W(L"UTF8String")); 
				A.SetAttribute(L"TextV", text); 
				return A; 
			}
			_Catch()
		}

		XmlElement CreateFreeKeyObject(XmlDocument doc, int key_i) 
		{
			try
			{
				XmlElement E = doc.CreateElement(L"asn", L"sequence", AsnNsUri); 
				//
				XmlElement A0 = CreateIntegerObject(doc, key_i);	// index 
				XmlElement A1 = CreateIntegerObject(doc, 0);		// flags 
				XmlElement A2 = CreateTextObject(doc, L"?");		// pkh64 
				XmlElement A3 = CreateTextObject(doc, L"?");		// keyTimeStr 
				XmlElement A4 = CreateTextObject(doc, L"?");		// CN 
				XmlElement A5 = CreateTextObject(doc, L"?");		// O 
				//
				E.AppendChild(A0); 
				E.AppendChild(A1); 
				E.AppendChild(A2); 
				E.AppendChild(A3); 
				E.AppendChild(A4); 
				E.AppendChild(A5); 
				//
				return E; 
			}
			_Catch()
		}

		XmlElement CreatePrivateKeyObject(XmlDocument doc, int key_i) 
		{
			try
			{
				XmlElement E = doc.CreateElement(L"asn", L"sequence", AsnNsUri); 
				//
				XmlElement A0 = CreateIntegerObject(doc, key_i);	// index 
				XmlElement A1 = CreateTextObject(doc, L"");			// password 
				//
				E.AppendChild(A0); 
				E.AppendChild(A1); 
				//
				return E; 
			}
			_Catch()
		}

		inline static void OutputXml(const string& xml1, const string& title=L"XML") 
		{
			try
			{
				string echo = L"\n" + title + L" : \n" + xml1 + L"\n"; 
				OutputDebugStringW(echo); 
			}
			_Catch() 
		}

		CStringA NewKeyPath(
			const string& keyContainerPwd, 
			const COleDateTime& t, 
			const string& commonName, 
			const string& orgName, 
			int* out_key_i 
			) 
		{
			try
			{
				string t_s = PKI::LocalTimeToTimeStr(t); 
				return NewKeyPath_tS(keyContainerPwd, t_s, commonName, orgName, out_key_i); 
			}
			_Catch() 
		}

		CStringA NewKeyPath_tS(
			const string& keyContainerPwd, 
			const string& t_s, 
			const string& commonName, 
			const string& orgName, 
			int* out_key_i 
			) 
		{
			try
			{
				Lock lock; 
				//
				CStringA containerPathA; 
				//
				XmlElement keyList_E = GetFreeKeyList(true); 
				XmlDocument freeMetaDoc = keyList_E.OwnerDocument(); 
				XmlElement S0 = GetKeyList_S0(keyList_E, L"free"); 
				//
				XmlElement privateKeyList_E = GetPrivateKeyList(); 
				XmlDocument privateMetaDoc = privateKeyList_E.OwnerDocument(); 
				XmlElement privateS0 = GetKeyList_S0(privateKeyList_E, L"private"); 
				//
				//OutputXml(keyList_E.OuterXml(), L"free key list"); 
				//OutputXml(privateKeyList_E.OuterXml(), L"private key list"); 
				//
				XmlNodeList L = keyList_E.SelectNodes(L"asn:sequence/asn:sequence"); 
				//
				int n = L.Count(); 
				//
				int key_i = n; 
				if (out_key_i) *out_key_i = key_i; 
				//
				{
					XmlNodeList L1 = S0.SelectNodes(L"asn:sequence"); 
					if (L1.Count() != key_i) 
						throw MethodError(L"��������� ������ ����� (free)"); 
					//
					L1 = privateS0.SelectNodes(L"asn:sequence"); 
					if (L1.Count() != key_i) 
						throw MethodError(L"��������� ������ ����� (private)"); 
				}
				//
				XmlElement key_E = CreateFreeKeyObject(freeMetaDoc, key_i); 
				XmlElement privateKey_E = CreatePrivateKeyObject(privateMetaDoc, key_i); 
				//
				// Extra parameters 
				//
				WriteTextObjectInS(key_E, 3, t_s); 
				//
				WriteTextObjectInS(key_E, 4, commonName); 
				WriteTextObjectInS(key_E, 5, orgName); 
				//
				//OutputXml(key_E.OuterXml(), L"free key i"); 
				//OutputXml(privateKey_E.OuterXml(), L"private key i"); 
				//
				//OutputXml(keyList_E.OuterXml(), L"free key list"); 
				//OutputXml(privateKeyList_E.OuterXml(), L"private key list"); 
				//
				S0.AppendChild(key_E); 
				privateS0.AppendChild(privateKey_E); 
				//
				//OutputXml(keyList_E.OuterXml(), L"free key list"); 
				//OutputXml(privateKeyList_E.OuterXml(), L"private key list"); 
				//
				//SaveMetaObjectOid(OID__META, privateMetaDoc); 
				//SaveMetaObjectOid(OID__FREEMETA, freeMetaDoc); 
				//
				containerPathA = ETokenPath(EToken_GetKeyContainerPath_U(key_i)); 
				//
				return containerPathA; 
			}
			_Catch() 
		}

		void SetKeyTime(
			int key_i, 
			const COleDateTime& t 
			) 
		{
			try
			{
				string t_s = PKI::LocalTimeToTimeStr(t); 
				//
				XmlElement key_E = GetFreeKey(key_i); 
				//
				WriteTextObjectInS(key_E, 3, t_s); 
			}
			_Catch() 
		}

		inline static string EToken_GetKeyContainerPath_U(int key_i)  
		{
			try
			{
				return FormatStr(_W(_ETOKEN_ROOT) + L"/" + _ETOKEN_KEYDIR_PREFIX + L"%03d", key_i); 
			}
			_Catch()
		}

		// Structure update 

		inline void UpdateStructure_1() 
		{
			try
			{
				try 
				{
					// ������������ ����  Meta 
					//
				}
				catch(::Exception e1) 
				{
					string msg = L"���������� ���������� ����������� ������ �� eToken:\n" + e1.ToString(); 
					OutputDebugStringW(msg + L"\n"); 
				}
				catch(...)
				{
					// ���������� ���������� ����������� 
				}
			}
			_Catch() 
		}

		inline void UpdateStructure() 
		{
			try
			{
				UpdateStructure_1(); 
			}
			_Catch() 
		}








		//string EToken_NewPath_2(int slotId, int* out_id=0, const string& keyContainerPwd=L"") 
		//{
		//	try
		//	{
		//		int id = EToken_NewKeyId(slotId, 2, keyContainerPwd); 
		//		//
		//		string path = EToken_GetKeyContainerPath_U(slotId, id); 
		//		//
		//		if (out_id) *out_id = id;
		//		return path; 
		//	}
		//	_Catch()
		//}

		//string EToken_NewPath_M(int slotId, int key_mode, int* out_id=0, const string& keyContainerPwd=L"") 
		//{
		//	try
		//	{
		//	}
		//	_Catch()
		//}

		//SharedArray<int> GetETokenKeyNums(int slotId, int key_mode, int isFreeEtc) 
		//{
		//	try
		//	{
		//		SharedArray<int> keyNums;
		//		//
		//		//AsnObject MetaO = 
		//		//	(key_mode == 1) ? 
		//		//	MetaObject_E_1(slotId, isFreeEtc, false) : 
		//		//	MetaObject_E_2(slotId, isFreeEtc, false); 
		//		////
		//		//if (MetaO.Tag() == AsnObject::_NULL_)
		//		//{
		//		//	return keyNums; 
		//		//}
		//		////
		//		//AsnObject& KeyListInfoO = MetaO.Children[OID(OID_KEY_LIST_INFO)];
		//		//AsnObject& KeyListO = KeyListInfoO.Children[OID(OID_KEY_LIST)];
		//		////
		//		//AsnObject& KeysO = ((AsnObject&) KeyListO[1])[0];
		//		////
		//		//int keyNum = ((AsnObject&) KeysO[0]).m_Integer; 
		//		//AsnObject& keySeq = KeysO[1]; 
		//		//for (int i = 0; i < keyNum; i++)
		//		//{
		//		//	AsnObject& k = keySeq[i]; 
		//		//	if (k.IsConstructed())
		//		//	{
		//		//		if (k.ChildCount() > 0)
		//		//		{
		//		//			int flags = ((AsnObject&)k[0]).m_Integer;
		//		//			if (flags & _KEY_FLAG_OK)
		//		//			{
		//		//				keyNums.Add(i); 
		//		//			}
		//		//		}
		//		//	}
		//		//}
		//		//
		//		return keyNums; 
		//	}
		//	_Catch()
		//}

		//inline void CreateNewKeyObject_M(
		//	// in 
		//	const string& keyContainerPwd, 
		//	//
		//	// out 
		//	AsnObject& k0,
		//	AsnObject& k1
		//	)
		//{
		//	try
		//	{
		//		// ----
		//		// Private part 
		//		//
		//		k0 = AsnObject::NewSequence(); // container for new key 
		//		//
		//		int flags = 0; 
		//		k0.Add(AsnObject::NewInteger(flags)); 
		//		k0.Add(AsnObject(keyContainerPwd)); 
		//		//
		//		// ----
		//		// Free part 
		//		//
		//		k1 = AsnObject::NewSequence(); 
		//		//
		//		flags = _KEY_FLAG_TODELETE; 
		//		k1.Add(AsnObject::NewInteger(flags)); 
		//	}
		//	_Catch()
		//}

		//inline SharedArray<string> LabelTuple(const string& CNLabel, const string& OLabel) 
		//{
		//	try
		//	{
		//		SharedArray<string> a;
		//		a.Add(CNLabel); 
		//		a.Add(OLabel); 
		//		return a; 
		//	}
		//	_Catch()
		//}

		//inline void SetKeyObject(int slotId, int key_mode, int index, 
		//	AsnObject& metaO, int key_i, AsnObject& k 
		//	) 
		//{
		//	try
		//	{
		//		AsnObject& KeyListInfoO = metaO.Children[OID(OID_KEY_LIST_INFO)]; 
		//		AsnObject& KeyListO = KeyListInfoO.Children[OID(OID_KEY_LIST)];
		//		//
		//		AsnObject& KeysO = ((AsnObject&) KeyListO[1])[0];
		//		//
		//		int keyNum = ((AsnObject&) KeysO[0]).m_Integer; 
		//		AsnObject& keySeq = KeysO[1]; 
		//		//
		//		keySeq.Add(k); 
		//		((AsnObject&) KeysO[0]).m_Integer = keyNum + 1; 
		//	}
		//	_Catch() 
		//}






		//inline int EToken_NewKeyId(int slotId, int key_mode, const string& keyContainerPwd=L"") 
		//{
		//	try
		//	{
		//		return -1; 
		//		//%//...
		//		//// ----
		//		//// Meta Object 
		//		////
		//		//METAObjects m = MetaObjects(slotId, key_mode); 
		//		////
		//		//AsnObject& MetaO = m[0]; 
		//		//AsnObject& FreeO = m[1]; 
		//		////
		//		//// new Id for the key 
		//		//{
		//		//}
		//		////
		//		////AsnObject MetaO = MetaObject_E_M(slotId, key_mode, _PRIVATE_META); 
		//		////int len_1 = MetaO.ToBlob().Length();
		//		////
		//		//////AsnObject& KeyListInfoO = MetaO.Children[OID(OID_KEY_LIST_INFO)]; 
		//		//////AsnObject& KeyListO = KeyListInfoO.Children[OID(OID_KEY_LIST)];
		//		////////
		//		//////AsnObject& KeysO = ((AsnObject&) KeyListO[1])[0];
		//		////////OutputObject(L"KeyListO", KeyListO);
		//		////////OutputObject(L"KeysO", KeysO);
		//		////////
		//		//////int keyNum = ((AsnObject&) KeysO[0]).m_Integer; 
		//		//////AsnObject& keySeq = KeysO[1]; 
		//		////
		//		//// new key 
		//		////
		//		//AsnObject k0 = AsnObject::NewSequence(); 
		//		//AsnObject k1 = AsnObject::NewSequence(); 
		//		//CreateNewKeyObject_M(keyContainerPwd, k0, k1); // container for new key 
		//		////
		//		//SetKeyObject(slotId, key_mode, 0, MetaO, key_i, k0); 
		//		//SetKeyObject(slotId, key_mode, 1, FreeO, key_i, k1); 
		//		////
		//		//SaveMeta_META(slotId, key_mode, m); 
		//		////
		//		//////keySeq.Add(k1); 
		//		//////((AsnObject&) KeysO[0]).m_Integer = keyNum + 1; 
		//		////
		//		//// saving...
		//		//// 
		//		////int len_2 = MetaO.ToBlob().Length();
		//		////
		//		////CStringA metaPathA = ETokenPath(slotId, MetaPath()); 
		//		////int size1 = CADB_file_size(metaPathA.GetBuffer()); 
		//		////
		//		//return keyNum; 
		//	}
		//	_Catch()
		//}

		////string EToken_GetKeyPath(int slotId, int key_i) 
		////{
		////	try
		////	{
		////		return FormatStr(_W(_ETOKEN_ROOT) + L"/" + _ETOKEN_KEYDIR_PREFIX + L"%03d", key_i)
		////			+ L"/fa01"; 
		////	}
		////	_Catch()
		////}

		//string EToken_GetCertPath(int slotId, int key_i) 
		//{
		//	try
		//	{
		//		return FormatStr(_W(_ETOKEN_ROOT) + L"/" + _ETOKEN_KEYDIR_PREFIX + L"%03d", key_i)
		//			+ L"/fc01"; 
		//	}
		//	_Catch()
		//}

		//string EToken_GetRequestPath(int slotId, int key_i) 
		//{
		//	try
		//	{
		//		return FormatStr(_W(_ETOKEN_ROOT) + L"/" + _ETOKEN_KEYDIR_PREFIX + L"%03d", key_i)
		//			+ L"/fe01"; 
		//	}
		//	_Catch()
		//}

		//string EToken_GetRequestPath_X(int slotId, int key_i) 
		//{
		//	try
		//	{
		//		return FormatStr(_W(_ETOKEN_ROOT) + L"/" + _ETOKEN_KEYDIR_PREFIX + L"%03d", key_i)
		//			+ L"/fe02"; 
		//	}
		//	_Catch()
		//}

		////void DeleteFile(int slotId, const string& path) 
		////{
		////	try
		////	{
		////		CStringA pathA = ETokenPath(slotId, path); 
		////		CADB_erase_file(pathA.GetBuffer()); 
		////	}
		////	_Catch()
		////}
	}; 

















} // namespace Slot









