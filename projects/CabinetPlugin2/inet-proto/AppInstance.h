

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


#include "../low-level/SmartErrorHandling.h"
#include "../low-level/SmartUtil.h"
//
#include "../alg/Alg_1_8_2.h"
//
#include "../_cpp/SlotApp.h"
#include "../_cpp/SlotAppInstance.h"
//
#include "../_cpp/SlotCSP_CCOM.h"
//
#include "ProtocolDefs.h"
#include "Util.h"


namespace  {

	namespace Protocol {

		class AppCtx : 
			public InstanceCtx<
				AppCtx,
				ApplicationCtx<AppCtx>
			>
		{
		public:
			inline static AppCtx& Instance() 
			{
				static AppCtx s_Instance; 
				return s_Instance; 
			}

			// ----
			// �������� ��� ApplicationCtx 

			inline static string App_GetDescription() throw() 
			{
				string s = _PROTOCOL_PROJECT_DESCRIPTION;
				return s;
			}

			inline static CString App_GetModuleFileName() throw() 
			{
				CString s = _PROTOCOL_MODULE_FILENAME;
				return s;
			}



			// ----
			// �������� ��� ApplicationInstanceCtx

			string GetConfigTag() // final virtual 
			{
				return _W(_PROTOCOL_CONFIG_TAG); 
			}



			// ----
			// ApplicationInstanceCtx

			inline static CString GetRegRoot() 
			{
				try
				{
					CString s = _S("SOFTWARE\\") + _S(__REGISTRY_NAME) + _T("\\") + _S(_CABINET_NAME); 
					return s;
				}
				_Catch()
			}

			string GetDefaultOptionValue(const string& name)
			{
				try
				{
					// ---------------------------------------------------------------------------
					{
						return L"";
					}
				}
				_Catch()
			}

			// ���� ��� URL, ����������� �� ��������� web-������� �������: XSL, ... 

#			ifdef _PROTOCOL_USE_COMMON_URL_BASE
			//
			string CommonUrlBase() 
			{
				try
				{
					string s = GetOption(Get_aCommonUrlBase());
					return s;
				}
				_Catch() 
			}
			//
#			endif

			inline string GetVariable(const string& name) 
			{
				try
				{
					return GetOption(name); 
				}
				_Catch() 
			}

			CString GetVariable(const CString& name,SharedArray<CString>* arr)
			{
				try
				{
					HKEY rootKey = HKEY_CURRENT_USER; 
					CString value = GetVariableForKey(rootKey,name,arr);
					if (arr->Length() > 0) return value;
					//
					rootKey = HKEY_LOCAL_MACHINE; 
					value = GetVariableForKey(rootKey,name,arr);
					if (arr->Length() > 0) return value;
					//
					return value; 
				}
				_Catch() 
			}

			CString GetVariableForKey(HKEY rootKey,const CString& name,SharedArray<CString>* arr) 
			{
				try
				{
					CString rootRegPath = GetRegRoot(); 
					//
					// ----
					// Rx-�������
					//
					if (! arr) throw MethodError(E_POINTER); 
					//
					HRESULT rc = 0; 
					CString value; 
					//
					if (name.Right(5) == _T("Table"))
					{
						SharedArray<Machine::RegValue> values = Machine::ListRegValues(rootKey,
							rootRegPath + _T("\\Settings\\") + name, 
							false,&rc);
						//
						if (values.Length() == 0)
						{
							values = Machine::ListRegValues(rootKey,
								rootRegPath + _T("\\Settings\\") + name, 
								false,&rc); 
						}
						//
						value = _T("");
						for (int k = 0; k < values.Length(); ++k)
						{
							Machine::RegValue& V = values[k];
							//
							if (V.Type == REG_SZ)
							{
								CString v1 = V.vStr;
								v1.Trim();
								if (v1.GetLength() > 0)
								{
									value += V.vStr + _T("\n");
									//
									if (arr != 0) 
									{
										arr->Add(V.vStr);
									}
								}
							}
						}
						return value;
					}
					//
					// ������ ������ ������������� � ���, ��� ���������� �� ������� ��� ����� ������ ��������.
					//
					return _T("");
				}
				_Catch()
			}






			// -----------------------------------------------------------------------------------
			// ���������� �� ��������� ��������� 

			// �������� ���������� ���������
			inline static CString GetEventSourceName() 
			{ 
				if (EventSource::CommonLogName() == _EVT_LOG_NAME) 
				{
					return _PROTOCOL_EVENT_SOURCE; 
				}
				else
				{
					return _T("Application"); 
				}
			}

			// ����������, ������������ ��������� ��������� 
			inline static CString GetFacilityName() { return _PROTOCOL_FACILITY; }

			// ���������� ��� ������
			inline static HRESULT GetErrorCode() { return SLOT_SYNC_ERROR; } // TODO: !

			// ���������� ��� ��������������
			inline static HRESULT GetWarningCode() { return SLOT_SYNC_WARNING; } // TODO: !












			//string App_GetModuleFileName() 
			//{
			//	return _W(_PROTOCOL_MODULE_FILENAME); 
			//}
		};

	} // nemspace Protocol 

} // namespace  
