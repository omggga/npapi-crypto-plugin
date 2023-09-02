
#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include <slot/cpp/inet-proto/Defs.h>
#include <slot/cpp/inet-proto/Util.h>
#include <slot/cpp/inet-proto/Application.h>
#include <slot/cpp/inet-proto/User.h>

namespace  {
namespace Protocol {

	// ===========================================================================================
	// ������ �������� (���������� �����) 

	class CabinetApp : public Application
	{
	public:
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// �����������

		inline static CabinetApp& Acquire()
		{
			try
			{
				static CabinetApp s_CabinetApp;
				return s_CabinetApp;
			}
			_FCatch()
		}

		inline static CabinetApp& Acquire4CurrentUser()
		{
			try
			{
				static CabinetApp s_CurrentUserCabinetApp(User::GetCurrentUser());
				return s_CurrentUserCabinetApp;
			}
			_FCatch()
		}

	private:
		CabinetApp()
		{
			try
			{
				SetName(_T("Cabinet"));
			}
			_Catch()
		}

	public:
		CabinetApp(User& user)
		{
			try
			{
				SetName(_T("Cabinet"));
				SetUser(user);
			}
			_Catch()
		}

		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// �����������

		void Register()
		{
			try
			{
				TRACE_LOG(_T("������������ ���������� CabinetApp..."));
				if (Application::Register()) return; // ������! (���������� ��� ����������������)
				//
				// ----
				// �������� ���������� /Cabinet
				//
				TRACE_LOG(_T(">---> �������� ���������� /Cabinet"));
				HKEY rootKey = GetRegistryRootKey();
				CString rootRegPath = GetRegistryRoot();
				//
				Machine::AddRegKey(rootKey,rootRegPath + _T("\\Internet protocol []"));
				//
				CString _PROTOCOL_CLSID = 
					_S("{") + _T(_PROTOCOL_CLSID_STR) + _T("}");
				Machine::SetRegStringValue(rootKey,rootRegPath + _T("\\Internet protocol []"),
					_T("CLSID"),_PROTOCOL_CLSID);
				//
				// �����
				//
				Machine::AddRegKey(rootKey,rootRegPath + _T("\\Settings"));
				//
				// �����������
				//
				Machine::AddRegKey(rootKey,rootRegPath + _T("\\Certificates"));
				//
				// �����
				//
				Machine::AddRegKey(rootKey,rootRegPath + _T("\\Cabinets"));
			}
			_Catch()
		}

		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// ������ 

		// HKEY GetRegistryRootKey() // --- ��� � Application 

		// CString GetRegistryRoot() // --- ��� � Application 

		CString GetVariable(const CString& name,SharedArray<CString>* array=0)
		{
			try
			{
				// ----
				// 1. ������� ����� ���������� � ������� ���������� Cabinet (� ���������������� �������)
				//
				HKEY rootKey = GetRegistryRootKey();
				CString rootRegPath = GetRegistryRoot();
				//
				HRESULT rc = S_OK;
				CString value = Machine::GetRegStringValue(rootKey,rootRegPath + _T("\\Settings"),
					name,false,&rc);
				if (rc == S_OK) return value;
				//
				// ----
				// 2. ������� ��������� ����� ����� ���������� ���������� � �������
				//    � ���������������� ������
				//
				LoadSettingsFromServer();
				//
				rc = S_OK;
				value = Machine::GetRegStringValue(rootKey,rootRegPath + _T("\\Settings"),
					name,false,&rc);
				if (rc == S_OK) return value;
				//
				// ----
				// 3. ������������� ����� ��������� ���������� off-line 
				//    (��� ������� ��� ��������� �� ���������) 
				//
				if (name.Right(5) != _T("Table"))
					SetVariableOffline(name);
				//
				rc = S_OK;
				value = Machine::GetRegStringValue(rootKey,rootRegPath + _T("\\Settings"),
					name,false,&rc);
				if (rc == S_OK) return value;
				//
				// ----
				// Rx-�������
				//
				if (name.Right(5) == _T("Table"))
				{
					SharedArray<Machine::RegValue> values = Machine::ListRegValues(rootKey,
						rootRegPath + _T("\\Settings\\")+name,
						false,&rc);
					//
					if (values.Length() == 0)
					{
						SetVariableOffline(name);
						//
						values = Machine::ListRegValues(rootKey,
							rootRegPath + _T("\\Settings\\")+name,
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
								if (array != 0) 
								{
									array->Add(V.vStr);
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

		void SetVariableOffline(const CString& name)
		{
			try
			{
				// ���� �������� ���������� �� ��������� 
				//
				CString value = GetVariableDefault(name);
				//
				// ������������� �������� ����������
				//
				HKEY rootKey = GetRegistryRootKey();
				CString rootRegPath = GetRegistryRoot();
				//
				if (name.Right(5) == _T("Table"))
				{
					Machine::AddRegKey(rootKey,rootRegPath + _T("\\Settings\\") + name);
					//
					int p1 = value.Find(_T("\n"));
					int i = 0;
					while (p1 != -1)
					{
						CString a = value.Left(p1);
						CString iStr = FormatStr(_T("%d"), (int)i );
						Machine::SetRegStringValue(rootKey,rootRegPath + _T("\\Settings\\") + name,
							iStr,a,false);
						//
						value = value.Right(value.GetLength()-p1-1);
						p1 = value.Find(_T("\n"));
						++i;
					}
				}
				else
				{
					if (value.GetLength() == 0) return;
					//
					HRESULT rc = S_OK;
					Machine::SetRegStringValue(rootKey,rootRegPath + _T("\\Settings"),
						name,value,false,&rc);
					if (rc != S_OK)
					{
						AlarmAboutException( MethodError(rc) );
						return;
					}
				}
			}
			_Catch()
		}

		inline static CString GetVariableDefault(const CString& name)
		{
			try
			{
				//if (name == _T("slot-gate-host") || name == _T("-gate")) return _T("delegation-test");
				//if (name == _T("slot-gate-host") || name == _T("-gate")) return _T("pcab3");
				if (name == _T("slot-gate-host") || name == _T("-gate")) return _T("cabinet.example.com");
				//
				//else if (name == _T("slot-gate-secure-port")) return _T("443"); 
				//else if (name == _T("slot-gate-secure-port")) return _T("8443");
				else if (name == _T("slot-gate-secure-port")) return _T("443");
				//
				else if (name == _T("slot-gate-path")) return _T("/__/");
				else if (name == _T("slot-document-save-prefix")) return _T("@YYYY\\@oper-date\\@doc-prefix"); // ������ �� ������������
				else if (name == _T("slot-oper-date-name")) return _T("@YYYY-@mm-@dd"); // ������ �� ������������
				//
				else if (name == _T("cabinet-host")) return _T("cabinet.example.com");
				//
				else if (name == _T("ptocol-site-location")) return _T("/protocol/");
				//
				else if (name == _T("cabinet-start-path")) 
					return GetVariableDefault(_T("ptocol-site-location")) + _T("Start.xml");
				//
				else if (name == _T("slot-upload-url")) 
					return ProtocolPrefix() + _T("//") + GetVariableDefault("cabinet-host") + 
					_T("/client/in/upload.xml");
				//
				else if (name == _T("slot-receipt-url")) 
					return ProtocolPrefix() + _T("//") + GetVariableDefault("cabinet-host") + 
					_T("/client/in/receipt.xml"); 
				//
				else if (name == _T("client-pkh")) return _T("");
				//
				else if (name == _T("validate-generated-ufml")) return _T("false");
				//
				else if (name == _T("request-filter-xsl-table")) 
					return _T("://cabinet.example.com/protocol/request-filter-xsl-table-001.xsl");
				//
				// Gate
				//
				else if (name == _T("gate-url-strategy")) return _T("keep-path");
				//
				// ActiveX
				//
				else if (name == _T("document-progid")) return _T("Protocol.Document");
				else if (name == _T("local-gate-progid")) return _T("Protocol.LocalGate");
				else if (name == _T("cabinet-gate-progid")) return _T("Protocol.CabinetGate");
				//
				// ----
				// �������
				//
				else if (name == _T("PublicUrlRxTable"))
				{
					return	_T("^/protocol/.*$\n")
							_T("^/schema/.*$\n")
							_T("^/css/.*$\n")
							_T("^/img/.*$\n")
							_T("^/vxsl/.*$\n")
							;
				}
				else if (name == _T("SlotDocumentUrlRxTable")) 
				{
					return	_T("^.*/slotdata/.*$\n")
							_T("^.*/sdoc/.*$\n")
							;
				}
				//
				return _T("");
			}
			_FCatch()
		}

		void SetVariable(const CString& name,const CString& valueToSet)
		{
			try
			{
				CString value = valueToSet;
				//
				// ������������� �������� ����������
				//
				HKEY rootKey = GetRegistryRootKey();
				CString rootRegPath = GetRegistryRoot();
				//
				if (name.Right(5) == _T("Table"))
				{
					Machine::AddRegKey(rootKey,rootRegPath + _T("\\Settings\\") + name);
					//
					int p1 = value.Find(_T("\n"));
					int i = 0;
					while (p1 != -1)
					{
						CString a = value.Left(p1);
						CString iStr = FormatStr(_T("%d"), (int)i );
						Machine::SetRegStringValue(rootKey,rootRegPath + _T("\\Settings\\") + name,
							iStr,a,false);
						//
						value = value.Right(value.GetLength()-p1-1);
						p1 = value.Find(_T("\n"));
						++i;
					}
				}
				else
				{
					HRESULT rc = S_OK;
					Machine::SetRegStringValue(rootKey,rootRegPath + _T("\\Settings"),
						name,value,false,&rc);
					if (rc != S_OK)
					{
						AlarmAboutException( MethodError(rc) );
						return;
					}
				}
			}
			_Catch()
		}

		void LoadSettingsFromServer()
		{
			try
			{
				// TODO: !!!
			}
			_Catch()
		}

		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// ������������ Internet-���������

		inline static CString ProtocolName()
		{
			return _S("");
		}
		inline static CString& ProtocolPrefix()
		{
			static bool inited = false;
			static CString protocolPrefix;
			//
			if (! inited)
			{
				protocolPrefix = ProtocolName() + _T(":");
				inited = true;
			}
			return protocolPrefix;
		}

		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// XML-��������  

		XmlDocument m_CabinetXml;

		XmlDocument GetCabinetXml(bool* out_found=0);

		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// �������� ������� 

		CString m_cabinetRoot;

		CString GetRoot()
		{
			try
			{
				if (m_cabinetRoot.GetLength() > 0) return m_cabinetRoot;
				//
				CString appData = User::GetCurrentUser().GetAppDataFolder();
				if (appData.GetLength() == 0) 
				{
					throw MethodError(_T("����������� ����� ��� ������ ������� ������ �������"));
				}
				//
				m_cabinetRoot = Machine::CreateDirectoryAndTest(appData + _T("\\-SLOT"));
				//
				return m_cabinetRoot;
			}
			_Catch()
		}

		CString GetDocumentsRoot()
		{
			try
			{
				return GetRoot() + _T("\\Documents");
			}
			_Catch()
		}

		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// ����

		inline CString GetDefaultGateHost()
		{
			try
			{
				return GetVariable(_T("slot-gate-host"));
			}
			_FCatch()
		}

		inline int GetDefaultGateSecurePort()
		{
			try
			{
				return _tstoi(GetVariable(_T("slot-gate-secure-port")).GetString());
			}
			_FCatch()
		}
	};

} // namespace Protocol
} // namespace 


