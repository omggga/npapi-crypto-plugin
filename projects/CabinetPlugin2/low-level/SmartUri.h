/*
 SmartUri.h : ������������� �������. 

 $Name:  $
 $Revision: 1.1.2.4 $
 $Date: 2009/05/26 12:48:11 $

 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include "SmartException.h"
#include "SmartMap.h"

#define ArchiveGroup_Archive	1
#define ArchiveGroup_Cache		2

// CABINET 

#define CABINET_PROTOCOL_NAME L""
#define CABINET_HOST L"cabinet.example.com"

#define CABINET_DEFAULT_PATH L"/fact/slot/rpt-fund.xml" // ��� ������������ 
// TODO: ���������������� � ������� � ���������

namespace 
{

	// ===========================================================================================
	// ��������������� ������� 

	inline static string UrlDecode(const string& in_request) 
	{
		try
		{
			string request(in_request); 
			//
			int step = 0;
			int p1;
			do
			{
				++step;
				//
				int n = request.GetLength(); 
				//
				p1 = request.Find(L"%"); 
				//
				if ((p1 != -1) && (p1 <= n-1-2))
				{
					string pattern = request.Mid(p1,3); 
					//
					BYTE b1 = (BYTE)request.GetString()[p1+1];
					BYTE b2 = (BYTE)request.GetString()[p1+2];
					//
					int d1 = ByteToHexDigit(b1); 
					int d2 = ByteToHexDigit(b2); 
					//
					string sym = L"";
					//
					if ( (d1 != -1) && (d2 != -1) )
					{
						wchar_t S = (wchar_t)( (d1 << 4) | d2 ); 
						//
						sym = CStringW(S,1); 
					}
					//
					if (p1 == n-3) request = request.Left(request.GetLength()-3) + _W(sym);
					else request.Replace(pattern,sym); 
				}
				if (step <= 10) 
				{
					//TRACE_LINE(_S(request)); 
				}
			}
			while ((p1 != -1) && (step < 100));
			//
			return request; 
		}
		_Catch() 
	}

	inline static string UrlEncode(const string& request,
		DWORD flags=ICU_BROWSER_MODE
		)  
	{
		try
		{
			if (request.GetLength() == 0) return L""; 
			//
			CBlobW b;
			DWORD len = request.GetLength()*3 + 16; 
			b.Expand(len); 
			if (! InternetCanonicalizeUrlW(request,b.GetBuffer(),&len,flags))
			{
				DWORD dwErr = GetLastError(); 
				throw MethodError(HRESULT_FROM_WIN32(dwErr)); 
			}
			b.SetSize(len); 
			//
			return string(b.GetBuffer(),len); 
		}
		_Catch() 
	}
















	// ===========================================================================================
	// URI 

	enum ParseMethod 
	{
		ParseMethodUrl		= 1,
		ParseMethodPath		= 2
	};

	// URI 

	struct Uri
	{
		const string& CabinetProtocolName()
		{
			static bool ready = false;
			static string value;
			//
			if (! ready)
			{
				value = CABINET_PROTOCOL_NAME; 
				ready = true;
			}
			return value;
		}

		const string& CabinetProtocolPrefix()
		{
			static bool ready = false;
			static string value;
			//
			if (! ready)
			{
				value = CabinetProtocolName() + L":"; 
				ready = true;
			}
			return value;
		}

		const string& CabinetHost()
		{
			static bool ready = false;
			static string value;
			//
			if (! ready)
			{
				value = CABINET_HOST; 
				ready = true;
			}
			return value;
		}



		// ----
		// ������

		string Protocol;			// , http, https, file, ...

		string Path;				// ���� (������ �������): /...

		string GatePath;			// ���� �� �����: /folder/file.xml ��� /_gw_/?__path__=...

		// �������������� �������� ���������

		string Host;				// ����, ������������ ������������� (��� ������� �� �����) 

		int Port;					// ����, ������������ ������������� 

		// ----
		// ����������� ������ ������� 

		string ReferenceUrl;		// "��������� URL" --- ������������� ������������� ������� � ����� IE

		string OriginalExtension;	// ���������� ����� � �������

		string Extension;			// ���������� ����� � ������� � lower case

		string Name;				// ��� ����� ������� 

		string ResourcePath;		// ������ Web-���� � ������� (/...), ��� ���������� �������

		string ResourceFile;		// ��� ����� ������� ����� ���������� /

		string ResourceFileId;		// ��� ����� �������, ������������� ��� ��������� �������������
									// ���� ResourceFile, ���� "__index__", ���� ResourceFile == ""

		string ResourceDir;			// RequestPath ��� "/" + ResourceFile;

		string Query;				// ��������� (������) ������� 

		string QueryId;				// ���� == Query, ���� ������� ������, ���� Query 
									// �� ����������� ��� �������������. 

	protected:
		inline void Clear() 
		{
			Port = 0; 
		}

	public:
		// ----
		// ������������ 

		Uri()
		{
			Clear(); 
		}

		Uri(const string& requestStr)
		{
			ParseRequest(ParseMethodUrl,requestStr);
		}

		Uri(int parseMethod,const string& requestStr)
		{
			ParseRequest(parseMethod,requestStr); 
		}

		inline static string NormalizeLocalPath(const string& in_path) 
		{
			try
			{
				string path = in_path;
				//
				if (path.Left(2) == L"//") path = path.Right(path.GetLength() - 2); 
				//
				while (path.Find(L'/') != -1)
				{
					path.Replace(L'/',L'\\'); 
				}
				while (path.Find(L'|') != -1)
				{
					path.Replace(L'|',L':'); 
				}
				return path; 
			}
			_Catch() 
		}

		void ParseRequest(int parseMethod,const string& requestStr) 
		{
			try
			{
				// ������ ���������� 
				//
				string pathOrOther(requestStr);
				string url;
				//
				if (parseMethod == ParseMethodUrl)
				{
					url = pathOrOther; // ����� �����������... 
				}
				else if (parseMethod == ParseMethodPath)
				{
					Protocol = CabinetProtocolName();
					Port = 80;
					Path = pathOrOther;
					Host = CabinetHost();
					//
					// ��������� ��������������� � ������� Path 
				}
				//
				// ������ URL 
				//
				url.Trim();
				//
				if (url.GetLength() > 0)
				{
					string hostAndPath = url;
					//
					int p1 = url.Find(L":");
					if (p1 == -1) // ��� �����������, ��������������� ��������, => ��� ��������� 
					{
					}
					else
					{
						// ���� ��������
						//
						string left = url.Left(p1);
						if (left.GetLength() > 0)
						{
							int p11 = left.Find(L"/");
							if (p11 == -1) // not found 
							{
								Protocol = left;
								hostAndPath = url.Right(url.GetLength() - p1 - 1);
							}
							else // ����������� ������ ���� ���� 
							{
							}
						}
						else
						{
						}
					}
					//
					// �������� ����������� ������ �������������� 
					//
					if (Protocol.GetLength() == 0)
					{
						Protocol = CabinetProtocolName();
					}
					url = hostAndPath;
					//
					// ��������: Protocol 
					//
					if (Protocol == L"file")
					{
						Host = "";
						Port = 0;
						Path = NormalizeLocalPath(url);
						ReferenceUrl = L"file://" + Path;
						return; 
					}
					else // ��������-�����: http, https, ftp, , ...
					{
					}
					//
					// ��������� ��������-����� 
					//
					url.Trim();
					//
					string r1 = url;
					//
					int p12 = url.Find(L"//");
					if ((p12 == -1) || (p12 > 0)) // ��������� ��������? 
					{
						throw MethodError(L"��������� ������ URL (�.�. �� ��������������)");
					}
					else // "//" ������� 
					{
						r1 = url.Right(url.GetLength() - p12 - 2); 
					}
					//
					// ���� Host + �������� 
					//
					string hostAndPort;
					//
					int p2 = r1.Find(L"/");
					if (p2 == -1) 
					{
						hostAndPort = r1;
						Path = L"/"; // ���� �� ������� �� ���������
					}
					else 
					{
						hostAndPort = r1.Left(p2);
						Path = r1.Right(r1.GetLength()-p2);
					}
					//
					int p3 = hostAndPort.Find(L":");
					if (p3 == -1)
					{
						Host = hostAndPort;
						Port = 80;
					}
					else
					{
						Host = hostAndPort.Left(p3);
						Port = _wtoi(hostAndPort.Right(hostAndPort.GetLength()-p3-1));
						if ((Port < 80) || (Port > 16*1024))
						{
							// TODO: ! 
							///DepoTextWarning1(_T("��������� �������� ������ �����: %d"),(int)serverPort);
							Port = 80;
						}
					}
				}
				//
				// ��������: Protocol, Host, Post, Path 
				//
				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				// ��������� ����
				//
				if (Path == L"/")
				{
					//// if (Protocol == CabinetProtocolName()) Path = CABINET_DEFAULT_PATH;
				}
				//
				int p1 = Path.Find(L"?");
				if (p1 == -1)
				{
					ResourcePath = Path;
					Query = L"";
				}
				else
				{
					ResourcePath = Path.Left(p1);
					Query = Path.Right(Path.GetLength()-p1-1); // ��� ����� '?' 
				}
				//
				//
				// ������������ ����
				//
				if (ResourcePath.GetLength() > 0)
				if (ResourcePath.Find(L"/",1) == -1)
				{
					//// ResourcePath = L"/protocol/" + ResourcePath;
				}
				if (StartsWith(ResourcePath,L"/protocol/") && (ResourcePath.Find(L".") == -1))
				{
					ResourcePath += L".xml";
				}
				//
				Path = Query.GetLength() > 0 ? 
					ResourcePath + L"?" + Query :
					ResourcePath;
				//
				GatePath = Path; 
				//
				// ���� � �������: ����, ���, ����������
				//
				if (ExtractTextFromRight(ResourcePath,L'/',0,&ResourceFile))
				{
				}
				else
				{
					ResourceFile = ResourcePath;
				}
				//
				// ��� � ���������� 
				//
				if (ExtractTextFromRight(ResourceFile,L'.',&Name,&Extension))
				{
				}
				else
				{
					Name = ResourceFile;
					Extension = _T("r");
				}
				OriginalExtension = Extension;
				Extension.MakeLower();
				//
				// *v* stupid check
				if (ResourcePath.GetLength() < ResourceFile.GetLength()+1)
					throw MethodError(L"�������� ������ � ��������� ResourcePath!");
				//
				ResourceDir = ResourcePath.Left(ResourcePath.GetLength()-1-ResourceFile.GetLength());
				//
				// *v* stupid check
				if (ResourcePath != (ResourceDir + L"/" + ResourceFile) )
					throw MethodError(L"�������� ������ � ��������� ResourcePath!");
				//
				// ----
				// ��������� "���������" URL 
				//
				if (Port == 80)
				{
					ReferenceUrl = CabinetProtocolPrefix() + L"//" + Host + Path;
				}
				else
				{
					string PortStr = FormatStr(L"%d", (int)Port ); 
					ReferenceUrl = CabinetProtocolPrefix() + L"//" + Host + L":" + PortStr + Path;
				}
			}
			_Catch()
		}






		// ---------------------------------------------------------------------------------------
		// ����������� ����������� 

		// ----
		// Query 

	protected:
		string Query_N;

		inline static const string& __AMP__() 
		{
			static string s___AMP__ = L"__AMP__"; 
			return s___AMP__; 
		}

		inline void QueryEncodeValue1(string& value)
		{
			try
			{
				// &amp; --> __AMP__
				//
				value.Replace(L"&amp;",__AMP__()); 
			}
			_Catch() 
		}

		inline void QueryDecodeValue1(string& value)
		{
			try
			{
				// __AMP__ --> &amp;
				//
				value.Replace(__AMP__(),L"&amp;"); 
				//
				value = UrlDecode(value); 
			}
			_Catch() 
		}

		inline void PrepareNormalizedQuery()
		{
			try
			{
				if (Query_N.GetLength() > 0) return; 
				//
				Query_N = Query; 
				//
				QueryEncodeValue1(Query_N); 
			}
			_Catch() 
		}

	public:
		inline bool flagX(const string& name) 
		{
			try
			{
				string a = name + L"="; 
				int p0 = Query.Find(a);
				if (p0 == -1) return false; 
				//
				string Q = Query.Right(Query.GetLength()-p0-a.GetLength()); 
				int p1 = Q.Find(L"&"); 
				if (p1 != -1)
				{
					Q = Q.Left(p1); 
				}
				Q.Trim(); 
				return Q == L"1" || Q == L"true" || Q == L"yes" || Q == L"on"; 
			}
			_Catch()
		}

	public:
		void ParseQuery_I_Start(int& position) 
		{
			try
			{
				PrepareNormalizedQuery(); 
				//
				position = 0; // position --- ���������� � ������ Query  
			}
			_Catch() 
		}

		bool ParseQuery_I_Get(int& position,string& name,string& value) 
		{
			try
			{
				if (position >= Query_N.GetLength()) // ���������� ��������� 
				{
					return false; 
				}
				//
				// ��������� �������� 
				//
				int new_position = -1; 
				int value_boundary = -1; 
				int p_equals = -1; 
				//
				int p1 = Query_N.Find(L'&',position); 
				if (p1 == -1) 
				{
					new_position = Query_N.GetLength(); 
					value_boundary = new_position; 
				}
				else
				{
					new_position = p1 + 1;
					value_boundary = p1; 
				}
				//
				if (value_boundary == position) // ������ �������: ...&&...
				{
					name = L""; 
					value = L""; 
				}
				else
				{
					int len = value_boundary - position; 
					//
					p_equals = Query_N.Find(L'=',position);
					if (p_equals != -1)
					{
						if (p_equals >= value_boundary) p_equals = -1; 
					}
					//
					if (p_equals == -1) // ��� ����� '=' 
					{
						name = Query_N.Mid(position,len); 
						value = L""; 
					}
					else // $name=$value
					{
						name = p_equals-position == 0 ? 
							L"" : Query_N.Mid(position,p_equals-position); 
						//
						string v = value_boundary-p_equals-1 <= 0 ? 
							L"" : Query_N.Mid(p_equals+1,value_boundary-p_equals-1); 
						//
						QueryDecodeValue1(v); 
						//
						value = v; 
					}
				}
				//
				position = new_position; 
				return true; // ���������� ������� 
			}
			_Catch() 
		}

		void ParseQuery_ToDictionary() 
		{
			try
			{
				throw MethodError(E_NOTIMPL); 
			}
			_Catch() 
		}
	};

} // namespace  
