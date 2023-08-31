/*
 SmartDns.h : ��������� � DNS ��� ������ WinSockets.

 $Name: work1 $
 $Revision: 1.1.2.6 $
 $Date: 2008/10/31 16:00:32 $
 */

#pragma once 

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


#include <low-level/AtlX.h>
#include <low-level/SmartMap.h>
#include <low-level/SmartPtr.h>

#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib" )


namespace  { 

	class DNSUtil
	{
	protected:
		DNSUtil() 
		{
		}

	public:
		inline static SharedArray<string> ResolveHost(const string& host) 
		{
			try
			{
				string name = host; 
				//
				WSADATA wsaData;
				int iResult;
				//int i = 1;
				//
				// Initialize Winsock
				iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
				//
				ADDRINFOW *result = NULL;
				ADDRINFOW *ptr = NULL;
				ADDRINFOW hints;
				//
				ZeroMemory( &hints, sizeof(hints) );
				hints.ai_family = AF_UNSPEC;
				hints.ai_socktype = SOCK_STREAM;
				hints.ai_protocol = IPPROTO_TCP;
				//
				WCHAR *port = L"27015";
				//
				// int r1 = 
				GetAddrInfoW(
					name,
					port,
					&hints,
					&result
					);
				//
				SharedArray<string> hostIps;
				//
				for (ptr = result; ptr != NULL; ptr = ptr->ai_next) 
				{
					unsigned char a1 = ptr->ai_addr->sa_data[2];
					unsigned char a2 = ptr->ai_addr->sa_data[3];
					unsigned char a3 = ptr->ai_addr->sa_data[4];
					unsigned char a4 = ptr->ai_addr->sa_data[5];
					string s = FormatStr(L"%u.%u.%u.%u", (int)a1, (int)a2, (int)a3, (int)a4); 
					hostIps.Add(s); 
				}
				//
				return hostIps; 
			}
			_Catch() 
		}
	};

} // namespace  
