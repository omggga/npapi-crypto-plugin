
#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include <slot/cpp/alg/Alg_1_8_4.h>
#include <slot/cpp/alg/Alg_1_8_8.h>
//
using namespace ::::Algorithms;

#include <slot/app/inet-proto/User.h>

namespace  {
namespace Protocol {

	// ===========================================================================================
	// ���������� 

	class Application 
	{
		User* m_pUser;

		CString m_name;

	public:
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// �������� � ���������� ������������

		Application() : m_pUser(0)
		{
		}

		Application(const CString& name) : m_pUser(0), m_name(name) 
		{
		}

		void SetUser(User& user)
		{
			m_pUser = &user;
		}

		void SetName(const CString& name)
		{
			m_name = name;
		}

		bool HasUser()
		{
			return m_pUser;
		}

		User& GetUser()
		{
			if (! HasUser()) throw MethodError(_T("������������ �� �����"));
			//
			return *m_pUser;
		}

		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// �����������

		bool Register()
		{
			try
			{
				if (IsRegistered()) return true; // ������! 
				//
				// ������������ 
				//
				TRACE_LOG(_T("APP:\n������������ �����������..."));
				HKEY rootKey = GetRegistryRootKey();
				CString rootRegPath = GetRegistryRoot();
				//
				// ��������� ������ � ����������
				//
				TRACE_LOG1(_T("���� ���������� � �������: %s"), rootRegPath.GetString() );
				Machine::AddRegKey(rootKey,rootRegPath);
				//
				Machine::SetRegStringValue(rootKey,rootRegPath,
					_T("Application Name"),m_name);
				//
				return false;
			}
			_Catch()
		}

		HKEY GetRegistryRootKey()
		{
			try
			{
				if (m_pUser) return HKEY_CURRENT_USER;
				else return HKEY_LOCAL_MACHINE;
			}
			_Catch()
		}

		CString GetRegistryRoot()
		{
			try
			{
				if (m_name.GetLength() == 0) 
				{
					TRACE_LOG(_T("!!!\n��� ���������� �� ������"));
					throw MethodError(_T("��� ���������� �� ������"));
				}
				//
				HKEY rootKey = GetRegistryRootKey();
				Machine::AddRegKey(rootKey,_T("Software\\"));
				//
				return _T("Software\\\\") + m_name;
			}
			_Catch()
		}

		bool IsRegistered()
		{
			try
			{
				if (m_name.GetLength() == 0) 
				{
					throw MethodError(_T("��� ���������� �� ������"));
				}
				//
				CString testStr;
				try
				{
					testStr =
					Machine::GetRegStringValue(GetRegistryRootKey(),GetRegistryRoot(),
						_T("Application Name"));
				}
				catch(...)
				{
				}
				return (testStr == m_name);
			}
			_Catch()
		}
	};

} // namespace Protocol 
} // namespace 
