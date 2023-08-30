/*
 SlotApp.h : ����� ����������� ����������.

 ����� Util

 $Name: work1 $
 $Revision: 1.1.2.2 $
 $Date: 2008/10/30 14:08:34 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


#include "../low-level/SmartMachine.h"


namespace  {

	template<
		class _App
	>
	class ApplicationCtx
	{
	public:
		typedef _App App;

		// ----
		// ���������� � ������� � ���������� 

		inline string GetAppName() throw() 
		{
			string name = _W(App::App_GetModuleFileName());
			if (name.Right(4) == L".dll") name = name.Left(name.GetLength()-4);
			return name; 
		}

		inline string GetAppDescription() throw() 
		{
			return _W(App::App_GetDescription()); 
		}

		inline string GetModuleFileName() throw()
		{
			return _W(App::App_GetModuleFileName());			
		}



		// ----
		// ���������� � ������� � ����������: ��������� 

		inline string GetMyVersion() 
		{
			try
			{
				HMODULE hModule = GetModuleHandle(_A(GetModuleFileName()));
				TCHAR mfName[1024];
				::GetModuleFileName(hModule,mfName,1024);
				//
				CString myVersion = ::::SystemInfo::GetFileVersionStr(
					_S(mfName), ::::SystemInfo::CUR_DIR 
					);
				//
				return _W(myVersion); 
			}
			_Catch()
		}

		inline string GetInfo() throw() 
		{
			try
			{
				string I;
				//
				// ----
				// ���������� Ufml3Filter 
				//
				I = L"������\t" + GetAppName();
				//
				HMODULE hModule = GetModuleHandle(_PROTOCOL_MODULE_FILENAME);
				TCHAR mfName[1024];
				::GetModuleFileName(hModule,mfName,1024);
				//
				string mfInfo = L" \t" + _W(mfName); 
				//
				I += L"\n" + mfInfo;
				//
				I += L"\n��������\t" + GetAppDescription();  
				//
				// ----
				// ���������� � ������ 
				//
				string machineInfo;
				//
				SYSTEM_INFO si;
				ZeroMemory(&si,sizeof(si));
				GetSystemInfo(&si);
				{
					string paText;
					//
					switch (si.wProcessorArchitecture)
					{
					case PROCESSOR_ARCHITECTURE_AMD64:		paText = L"AMD64"; break; 
					case PROCESSOR_ARCHITECTURE_IA64:		paText = L"IA64"; break; 
					case PROCESSOR_ARCHITECTURE_INTEL:		paText = L"x86"; break; 
					case PROCESSOR_ARCHITECTURE_UNKNOWN:	paText = L"Unknown processor"; break; 
					}
					//
					AppendText(machineInfo,paText,L", "); 
				}
				//
				// ----
				// ������ �������� 
				//
				CString myVersion = ::::SystemInfo::GetFileVersionStr( 
					_S(mfName), ::::SystemInfo::CUR_DIR 
					);
				//
				string myVersionInfo = L"������\t" + _W(myVersion); 
				//
				I += L"\n" + myVersionInfo;
				//
				// ----
				// ���������� �� Ingetnet Explorer 
				//
				CString ieVersion = Machine::GetRegStringValue(HKEY_LOCAL_MACHINE,
					_T("Software\\Microsoft\\Internet Explorer"),_T("Version"),
					false);
				//
				string ieInfo = L"Internet Explorer\t" + _W(ieVersion); 
				//
				I += L"\n" + ieInfo; 
				//
				// ----
				// ���������� � MSXML 
				//
				string msxmlVersions;
				//
				CString msxml6V = ::::SystemInfo::GetFileVersionStr(
					_T("msxml6.dll"), ::::SystemInfo::SYS_DIR
					);
				if (msxml6V.GetLength() > 0) msxmlVersions += _W(msxml6V);
				//
				string msxmlInfo = L"MS XML\t" + msxmlVersions; 
				//
				I += L"\n" + msxmlInfo; 
				//
				// ----
				// ���������� �� ������������ ������� 
				//
				string osInfo;
				//
				string osDescription = ::::SystemInfo::GetOSDescription();
				//
				osInfo = L"������������ �������\t" + osDescription; 
				//
				I += L"\n" + osInfo;
				//
				// ----
				// ��������� ����������
				//
#				if (_SYS_INFO_DETAILED == 1)
				{
					// ----
					// ���������� � ����� 
					//
					string hostDescription = ::::SystemInfo::GetHostDescription(); 
					//
					string hostInfo = L"���������\t" + hostDescription; 
					//
					I += L"\n" + hostInfo;
					//
					// ----
					// ���������� � ������������ 
					//
					string userDescription = ::::SystemInfo::GetUserDescription(); 
					//
					string userInfo = L"������������\t" + userDescription; 
					//
					I += L"\n" + userInfo;
				}
#				endif
				//
				//
				//
				// ----
				// ���������� ������� 
				//
				return I;
			}
			catch(...)
			{
				string I;
				//
				I = L"������\t" + GetAppName() + L"\n" + 
					L"��������\t" + GetAppDescription() + L"\n" + 
					L"������ ��� ������������ ���������� � �������\t"
					;
				//
				return I;
			}
		}



	protected:
		inline static void AppendText(string& text,const string& item,const string& sep) throw()
		{
			if (text.GetLength() > 0)
			{
				text += sep; 
			}
			//
			text += item; 
		}
	};

} // namespace  
