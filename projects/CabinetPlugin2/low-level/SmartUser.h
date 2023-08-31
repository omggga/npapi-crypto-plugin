/*
 User.h : Account ������������.

 $Name: work1 $
 $Revision: 1.1.2.2 $
 $Date: 2008/10/10 15:12:24 $

 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include <low-level/SmartMachine.h>

namespace  { 

	// ===========================================================================================
	// ��������� ������������ (�� ��������� ������������� �������� ������������) 

	class User
	{
		CString m_appDataFolder;

	public:
		inline static User& GetCurrentUser()
		{
			static User s_User; // �� ��������� ����������� ��������� ������������� �������� ������������
			return s_User;
		}

		CString GetAppDataFolder()
		{
			try
			{
				if (m_appDataFolder.GetLength() > 0) return m_appDataFolder;
				//
				HRESULT rc = S_OK;
				CString applicationData = Machine::GetRegStringValue(HKEY_CURRENT_USER,
					_T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders"),
					_T("AppData"),false,&rc);
				applicationData.Trim();
				//
				if (applicationData.GetLength() > 0) 
				{
					CString v = Machine::ExpandEnvVars(applicationData);
					if (v.GetLength() > 0) 
					{
						applicationData = Machine::CreateDirectoryAndTest(v);
					}
				}
				//
				// ----
				// ��������� ���������: %USERPROFILE%\\Application Data
				//
				if (applicationData.GetLength() == 0)
				{
					CString USERPROFILE;
					try 
					{
						USERPROFILE.GetEnvironmentVariable(_T("USERPROFILE"));
					}
					catch(...) 
					{ 
					}
					if (USERPROFILE.GetLength() > 0)
					{
						applicationData = 
							Machine::CreateDirectoryAndTest(USERPROFILE + _T("\\Application Data"));
					}
				}
				//
				// ----
				// ���������������: C:\\
				//
				if (applicationData.GetLength() == 0)
				{
					CString systemDrive;
					try
					{
						systemDrive.GetEnvironmentVariable(_T("SystemDrive"));
					}
					catch(...)
					{
					}
					if (systemDrive.GetLength() > 0)
					{
						applicationData = 
							Machine::TestDirectory(systemDrive+_T("\\"),_T("-SLOT"),false);
					}
				}
				//
				// ----
				// ���������
				//
				return applicationData;
			}
			_Catch()
		}
	};

} // namespace  
