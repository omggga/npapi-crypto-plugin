/*
 SmartException.h : ����������.

 $Name: work1 $
 $Revision: 1.1.2.6 $
 $Date: 2009/05/18 13:17:11 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include "AtlX.h"
#include "TracePoint.h"
//
#include "../LzLib/ErrorMessage.h"



#ifndef TRACE_POINT_W
#define TRACE_POINT_W ::::string(__FUNCTION__),__LINE__,::::string(__FILE__)
#endif
//
#ifndef TRACE_POINT_ARGS_W
#define TRACE_POINT_ARGS_W const ::::string& _source,int _line,const ::::string& _code_file
#endif
//
#ifndef TRACE_POINT_SEQ
#define TRACE_POINT_SEQ _source,_line,_code_file
#endif

//#ifndef COMPOSE_EXC_MSG_FOR_HR
//#define COMPOSE_EXC_MSG_FOR_HR(msg,hr,result) { ::::string hrStr = FormatStr(L"0x%x", (int)hr ); \
//	if (::::string(msg).GetLength() == 0) result = hrStr; else result = ::::string(msg) + L", hr=" + hrStr; }
//#endif

#define HRESULT_FROM_ERROR_OF_FACILITY(x,facility) (x <= 0 ? (HRESULT)x : (HRESULT) (((x) & 0x0000FFFF) | (facility << 16) | 0x80000000))



// Facility Protocol 

#ifndef FACILITY_PROTOCOL
#define FACILITY_PROTOCOL 0xAFA
#endif

#define SLOT_COMMON_INFO_HR HRESULT_FROM_ERROR_OF_FACILITY(1,FACILITY_PROTOCOL)

namespace 
{
	// -------------------------------------------------------------------------------------------
	// Util 

	struct ExceptionUtil 
	{
		inline static string SysMsgXmlHeader(int code,
			const COleDateTime& t=COleDateTime::GetCurrentTime(),
			const string& vXslUrl=L"",  
			int sLevel=3 
			) 
		{
			string piPrefixes;
			if (vXslUrl.GetLength() > 0)
			{
				piPrefixes += L"<?xml-stylesheet type=\"text/xsl\" href=\"" + vXslUrl + L"\" ?>"; 
			}
			//
			string sLs = sLevel == 3 ? L"error" :
				(sLevel == 2 ? L"warning" : L"info");
			//
			string tStr = FormatTime_ymd_HMD(_W(L"%04d-%02d-%02d"),_W(L" %02d:%02d:%02d"),t); 
			//
			string s = _W("<?xml version=\"1.0\" ?>") +
				piPrefixes + 
				L"<sysmsg:msg" 
				L" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\""
				L" xmlns:sysmsg=\"" + _SLOT_SYSMSG_NSURI + L"\" " 
				L" xsi:type=\"" + sLs + L"\""  
				L" num=\"" + FormatStr(L"%d",(int)code) + L"\"" 
				L" t=\"" + tStr + L"\"" 
				L">"
				; 
			return s; 
		}
	};






	// -------------------------------------------------------------------------------------------
	// Trace

	// ������� ������ ���� �� ����� ������ ����������? 
	// _TRACE_SHRINK_FILE_PATH == 1 // �������� ������� 

#	ifndef _TRACE_SHRINK_FILE_PATH
#	define _TRACE_SHRINK_FILE_PATH 1
#	endif

	// ������� ������� namespace � ����� ������� (�������) 
	// _TRACE_SHRINK_CPP_NAMESPACE == 1 // �������� ������� 

#	ifndef _TRACE_SHRINK_CPP_NAMESPACE
#	define _TRACE_SHRINK_CPP_NAMESPACE 1
#	endif

	struct Trace
	{
		int m_Length;

		int m_AllocLength;

		string* m_Sources;

		int* m_Lines;

		string* m_Files;

		int* m_Status;

		void Clear()
		{
			m_Length = 0;
			m_AllocLength = 0;
			m_Sources = 0;
			m_Lines = 0;
			m_Files = 0;
			m_Status = 0;
		}

		Trace() 
		{
			Clear();
		}

		~Trace()
		{
			if (m_Sources)
			{
				delete[] m_Sources;
				delete[] m_Lines;
				delete[] m_Files;
				delete[] m_Status;
			}
		}

		Trace(const Trace& other)
		{
			Clear();
			//
			m_Length = other.m_Length;
			m_AllocLength = other.m_AllocLength;
			//
			ReAllocate(m_AllocLength);
			//
			for (int j = 0; j < m_Length; ++j)
			{
				m_Sources[j] = other.m_Sources[j];
				m_Lines[j] = other.m_Lines[j];
				m_Files[j] = other.m_Files[j];
				m_Status[j] = other.m_Status[j];
			}
		}

		inline static int NoStatus() 
		{
			return (int)0; // S_OK 
		}

		Trace(TRACE_POINT_ARGS_W) 
		{
			Clear();
			//
			Add(_source,_line,_code_file,NoStatus()); 
		}

		Trace& Prepend(const string& source,int line,const string& fileName,int status)
		{
			int len = m_Length + 1;
			//
			if (len >= m_AllocLength) ReAllocate(len);
			//
			for (int j = m_Length-1; j >= 0; j--)
			{
				m_Sources[j+1] = m_Sources[j];
				m_Lines[j+1] = m_Lines[j];
				m_Files[j+1] = m_Files[j];
				m_Status[j+1] = m_Status[j];
			}
			m_Sources[0] = source;
			m_Lines[0] = line;
			m_Files[0] = fileName;
			m_Status[0] = status;
			//
			m_Length = len;
			//
			return *this;
		}

		Trace& Add(const string& source,int line,const string& fileName,int status)
		{
			int k = m_Length;
			int len = k + 1;
			//
			if (len >= m_AllocLength) ReAllocate(len);
			//
			AddText(m_Sources,source);
			m_Lines[k] = line;
			AddText(m_Files,fileName);
			m_Status[k] = status;
			//
			m_Length = len;
			//
			return *this;
		}

		Trace& AddIfNewSource(const string& source,int line,const string& fileName,int status)
		{
			string compareToSource;
			if (m_Length > 0)
			{
				compareToSource = m_Sources[m_Length-1];
			}
			//
			bool shouldAdd = true;
			if (compareToSource.GetLength() > 0)
			{
				if (compareToSource == source) shouldAdd = false;
			}
			//
			if (shouldAdd)
			{
				return Add(source,line,fileName,status);
			}
#			ifdef _DEBUG
			{
				TRACE_LINE(GetStructuredText()); 
			}
#			endif
			return *this;
		}

#		define AddIfNewSource_(source) AddIfNewSource(source,__LINE__,::::string(__FILE__))

		inline void AddText(string*& p,const string& value)
		{
			int k = m_Length;
			//
			p[k] = value;
		}

		inline void ReAllocate(int k)
		{
			int len = ((k/16) + 2)*16;
			//
			ReAllocate(len,m_Sources); 
			ReAllocate(len,m_Lines);
			ReAllocate(len,m_Files);
			ReAllocate(len,m_Status);
			//
			m_AllocLength = len;
		}

		inline void ReAllocate(int len,string*& p)
		{
			if (p)
			{
				string* P2 = p;
				p = new string[len];
				for (int j = 0; j < m_Length; ++j) p[j] = P2[j];
				delete[] P2;
			}
			else
			{
				p = new string[len];
			}
		}

		inline void ReAllocate(int len,int*& p)
		{
			if (p)
			{
				int* P2 = p;
				p = new int[len];
				for (int j = 0; j < m_Length; ++j) p[j] = P2[j];
				delete[] P2;
			}
			else
			{
				p = new int[len];
			}
		}



		// ----
		// �������������� : ������ 

		inline static HRESULT MsgStatus() 
		{
			static HRESULT hr = SLOT_COMMON_INFO_HR; 
			return hr; 
		}

		enum RecordType
		{
			RecordType_Source = 1,
			RecordType_Message = 2,
		};

		inline void GetLine(int k, // ����� ������� 
			string& column1_Source,
			string& column2_Line,
			string& column3_File, 
			bool* out_isMsgLine=0 
			) const 
		{
			// ����������� ��� ����������� ������ 
			// 
			if ((k < 0) || (k >= m_Length)) return; // stupid check 
			//
			string& source = m_Sources[k]; 
			int& line = m_Lines[k];
			string& fileName = m_Files[k]; 
			int& status = m_Status[k];
			//
			// �������� ��� ���������? 
			//
			RecordType rt = RecordType_Source; 
			//
			if (status != NoStatus())
			{
				rt = RecordType_Message; 
			}
			//
			//
			// ������� ����������� ����������� 
			//
			string msg;
			string lineText;
			string statusText;
			bool isMsgLine = false;
			//
			if (rt == RecordType_Source)
			{
				msg = _TRACE_SHRINK_FILE_PATH == 1 ? SourceToClassName(source) : source;
				//
				if (line != -1)
				{
					lineText = FormatStr(L"%d", (int)line );
				}
			}
			else if (rt == RecordType_Message)
			{
				::Lz::ErrorMessage<> m((DWORD)status);
				string statusMsg((LPCTSTR)m); 
				if (statusMsg.GetLength() == 0)
				{
					///HRESULT r1 = status;
					///DWORD facility = HRESULT_FACILITY(r1);
					///DWORD dwErr = HRESULT_CODE(r1); 
					//
					statusMsg = FormatStr(L"��� 0x%x", status ); 
				}
				if ((!FAILED(status)) || (status == E_FAIL) || (status == E_UNEXPECTED))
				{
					msg = ((source == statusMsg) || (source.GetLength() == 0)) ? statusMsg : ( 
						source 
						); 
				}
				else
				{
					msg = ((source == statusMsg) || (source.GetLength() == 0)) ? statusMsg : ( 
						statusMsg.GetLength() > 0 ? source + L": " + statusMsg : source 
						); 
				}
				//
				isMsgLine = true;
			}
			//
			msg.Replace(L"<",L"&lt;"); 
			msg.Replace(L">",L"&gt;"); 
			//
			// ��������� ������
			//
			column1_Source = msg; 
			column2_Line = lineText;
			column3_File = _TRACE_SHRINK_FILE_PATH == 1 ? PathToFileName(fileName) : fileName; 
			//
			if (out_isMsgLine) *out_isMsgLine = isMsgLine;
		}



		// ----
		// �������������� : ������ 
		
#		ifndef TraceColumnSize_Source
#		define TraceColumnSize_Source (78)
#		endif

#		ifndef TraceColumnSize_Line
#		define TraceColumnSize_Line 6
#		endif

#		ifndef TraceColumnSize_File
#		define TraceColumnSize_File 56
#		endif

		string Format(int formatType) const 
		{
			if (formatType == 1) // StructuredText 
			{
				return GetStructuredText(); 
			}
			else if (formatType == 2) // ConsoleText 
			{
				int sizes[3];
				sizes[0] = TraceColumnSize_Source;
				sizes[1] = TraceColumnSize_Line;
				sizes[2] = TraceColumnSize_File;
				//
				return GetConsoleText(sizes); 
			}
			else return L"";
		}


		// �������������� � ����� "console" 

		inline static string Crop(const string& text,int len) 
		{
			string s = text; 
			//
			if (s.GetLength() >= len)
			{
				if (len > 4) s = s.Left(len-4) + L"... ";
				else s = s.Left(len-1) + L"~"; 
			}
			while (s.GetLength() < len) s += L" "; 
			//
			return s; 
		}

		inline static string CropLeft(const string& text,int len) 
		{
			string s = text; 
			//
			if (s.GetLength() > len)
			{
				if (len > 3) s = L"..." + s.Left(len-3);
				else s = L"~" + s.Left(len-1); 
			}
			while (s.GetLength() < len) s += L" "; 
			//
			return s; 
		}

		inline string GetConsoleText(int* sizes) const 
		{
			string text;
			for (int k = m_Length-1; k >= 0; k--)
			{
				if (k < m_Length-1) text += L"\n";
				//
				string f1;
				string f2;
				string f3;
				//
				GetLine(k,f1,f2,f3); 
				//
				f1 = CropLeft(f1,sizes[0]); 
				f2 = Crop(f1,sizes[1]); 
				f3 = Crop(f1,sizes[2]); 
				//
				//
				text += f3 + f2 + f1;
			}
			return text;
		}

		string GetStructuredText() const 
		{
			string text;
			//
			for (int k = m_Length-1; k >= 0; k--)
			{
				string line;
				if (m_Lines[k] > 0)
				{
					line = 
						m_Files[k] + L"\t" + 
						FormatStr(L"%d",(int)m_Lines[k]) + L"\t" + 
						m_Sources[k]
						;
				}
				else
				{
					line = 
						m_Files[k] + L"\t\t" + 
						m_Sources[k] 
						;
				}
				if (k < m_Length-1) text += L"\n";
				text += line;
			}
			return text;
		}

		string GetTailText() const
		{
			string text = GetStructuredText(); 
			//
			if (text.GetLength() == 0) return L"";
			else return L"\n" + text;
		}

		string GetTailText(int* sizes) const
		{
			string text = GetConsoleText(sizes);
			//
			if (text.GetLength() == 0) return L"";
			else return L"\n" + text;
		}

		inline string ToString(int formatType=2) const // ConsoleText 
		{
			return Format(formatType); 
		}

		string GetHtml() const 
		{
			string html;
			int i = 0; 
			for (int k = 0; k < m_Length; ++k) 
			{
				string f1;
				string f2;
				string f3;
				bool isMsgLine;
				//
				GetLine(k,f1,f2,f3,&isMsgLine); 
				//
				bool addLine = true;
				//
				if (k == 0)
				{
					if (isMsgLine) addLine = false; 
				}
				//
				if (addLine)
				{
					string rowAttrs;
#					ifdef _DEBUG
					{
						if (i != 0 || true) rowAttrs = L" style=\"display: yes;\"";
					}
#					else
					{
						if (i != 0 || true) rowAttrs = L" style=\"display: none;\"";
					}
#					endif
					//
					string line;
					line = L"<tr " + rowAttrs + L"><td>" + f1 + L"</td><td>" + f2 + L"</td><td>" + f3 + L"</td></tr>"; 
					html += line;
					//
					++i; 
				}
			}
			//
			return html;
		}

		inline string GetXml_SysMsg() const 
		{
			/// int statusCode = GetStatus(); 
			//
			string xml1 = L""; 
			//
			for (int k = 0; k < m_Length; ++k) 
			{
				string f1;
				string f2;
				string f3;
				bool isMsgLine;
				//
				GetLine(k,f1,f2,f3,&isMsgLine);
				//
				bool addLine = true;
				//
				if (k == 0)
				{
					if (isMsgLine) addLine = false; 
				}
				//
				if (isMsgLine)
				{
					string line;
					line = L"<sysmsg:text>" + f1 + L"</sysmsg:text>"; 
					xml1 += line;
				}
				else if (addLine)
				{
					string line;
					line = L"<sysmsg:text obj=\"" + f1 + L"\" ln=\"" + f2 + L"\" loc=\"" + f3 + L"\">" + 
						L"</sysmsg:text>"; 
					xml1 += line;
				}
			}
			//
			return xml1;
		}

		inline static string PathToFileName(const string& path)
		{
			int p1 = path.ReverseFind(L'\\');
			if (p1 == -1)
			{
				return path;
			}
			else
			{
				return path.Right(path.GetLength()-p1-1);
			}
		}

		inline static string SourceToClassName(const string& src)
		{
			int p1 = src.ReverseFind(L':');
			if (p1 == -1)
			{
				return src;
			}
			else
			{
				return src.Right(src.GetLength()-p1-1);
			}
		}



		// ---- 
		// ���������� 

		Trace& Parse(const string& text)
		{
			string data = text;
			//
			if (text.GetLength() == 0) return *this;
			//
			int p1;
			do
			{
				p1 = data.Find(L"\n");
				//
				if (p1 == -1)
				{
					AddLine(data);
				}
				else
				{
					string item = data.Left(p1); 
					AddLine(item);
					data = data.Right(data.GetLength()-p1-1);
				}
			}
			while (p1 != -1);
			//
			return *this;
		}

		Trace& AddLine(const string& line) 
		{
			string item = line;
			item.Trim();
			if (item.GetLength() > 0)
			{
				int p1 = item.Find(L"\t");
				//
				int p2 = -1;
				if (p1 != -1) p2 = item.Find(L"\t",p1+1);
				//
				string source;
				int l = -1;
				string code_file;
				//
				HRESULT itemStatus = NoStatus(); 
				//
				if (p1 == -1) 
				{
					source = item;
					itemStatus = E_FAIL; 
				}
				else 
				{
					source = item.Left(p1);
					if (p2 == -1)
					{
						string s = item.Right(item.GetLength()-p1-1);
						l = _wtoi(s);
					}
					else
					{
						string s = item.Right(item.GetLength()-p1-1);
						string s2 = s.Left(p2-p1-1);
						l = _wtoi(s);
						code_file = s.Right(s.GetLength()-(p2-p1));
					}
				}
				//
				Prepend(source,l,code_file,itemStatus);
			}
			//
			return *this;
		}



		// ----
		// ������ 

		HRESULT GetStatus() const 
		{
			HRESULT status = NoStatus(); 
			for (int k = 0; (k < m_Length) && (status == NoStatus()); ++k)
			{
				HRESULT s1 = (HRESULT)m_Status[k];
				if ((s1 != NoStatus()) && (s1 != MsgStatus()) && (s1 != S_FALSE))
				{
					status = s1;
				}
			}
			return status;
		}

		string GetMsg() const 
		{
			string msg; 
			for (int k = 0; (k < m_Length) && (msg.GetLength() == 0); ++k)
			{
				string f1;
				string f2;
				string f3;
				//
				GetLine(k,f1,f2,f3); 
				//
				if (f1.GetLength() > 0)
				{
					msg = f1;
				}
			}
			return msg;
		}
	};






	// -----------------------------------------------------------------------------------
	// Exception

	class Exception
	{
		Trace m_Trace;

		COleDateTime m_Time; 

	public:
		bool m_OutputXml; 

		string m_VXslUrl; 

		string m_MediaType; 

		int m_SeverityLevel; 

		static const int SeverityInfo = 1;
		static const int SeverityWarning = 2;
		static const int SeverityError = 3;

	public:
		Exception(const string& msg,HRESULT hr=E_UNEXPECTED) 
		{
			SetCurrentTime();
			ReadExtra();
			AddMessage(msg,hr);
		}

		Exception(HRESULT hr) 
		{
			SetCurrentTime();
			ReadExtra();
			AddMessage(L"",hr);
		}

		Exception(const string& msg,HRESULT hr,TRACE_POINT_ARGS_W) 
		{
			SetCurrentTime();
			ReadExtra();
			AddMessage(msg,hr);
			m_Trace.Add(TRACE_POINT_SEQ,Trace::NoStatus());
		}

		Exception(const string& msg,TRACE_POINT_ARGS_W) 
		{
			SetCurrentTime();
			ReadExtra();
			AddMessage(msg,E_FAIL);
			m_Trace.Add(TRACE_POINT_SEQ,Trace::NoStatus());
		}

		Exception(HRESULT hr,TRACE_POINT_ARGS_W) 
		{
			SetCurrentTime();
			ReadExtra();
			AddMessage(L"",hr);
			m_Trace.Add(TRACE_POINT_SEQ,Trace::NoStatus());
		}

		Exception(DWORD rCode,DWORD facility,TRACE_POINT_ARGS_W) 
		{
			SetCurrentTime();
			ReadExtra();
			AddMessage(L"",rCode | facility);
			m_Trace.Add(TRACE_POINT_SEQ,Trace::NoStatus());
		}

		Exception(const Exception& other) : m_Trace(other.m_Trace), m_Time(other.m_Time), 
			m_OutputXml(other.m_OutputXml), m_VXslUrl(other.m_VXslUrl), m_MediaType(other.m_MediaType) 
		{
		}

		const Exception& operator =(const Exception& other) 
		{
			m_Time = other.m_Time; 
			m_Trace = other.m_Trace;
			m_OutputXml = other.m_OutputXml; 
			m_VXslUrl = other.m_VXslUrl; 
			m_MediaType = other.m_MediaType; 
			return other;
		}

		operator HRESULT() const
		{
			return GetStatus();
		}

		HRESULT GetStatus() const 
		{
			HRESULT status = m_Trace.GetStatus(); 
			return status;
		}

		string GetMsg() const 
		{
			string msg = m_Trace.GetMsg(); 
			return msg; 
		}

		inline Exception& OutputXml(bool f=true) 
		{
			m_OutputXml = true; 
			return *this; 
		}

		inline Exception& SetVXslUrl(const string& vXslUrl) 
		{
			m_VXslUrl = vXslUrl; 
			return *this; 
		}

		inline Exception& SetSeverity(int sLevel)
		{
			m_SeverityLevel = sLevel; 
			return *this; 
		}

		inline Exception& SetMediaType(const string& mediaType) 
		{
			m_MediaType = mediaType; 
			return *this; 
		}

		Exception& Add(TRACE_POINT_ARGS_W,HRESULT hr)
		{
			m_Trace.Add(TRACE_POINT_SEQ,hr);
			return *this;
		}

		Exception& AddIfNewSource(TRACE_POINT_ARGS_W,HRESULT hr=(HRESULT)Trace::NoStatus())
		{
			m_Trace.AddIfNewSource(TRACE_POINT_SEQ,hr);
			return *this;
		}

		Exception& Join(const Exception& e2)
		{
			m_Trace.AddIfNewSource(e2.ToString(),-1,L"",Trace::NoStatus());
			return *this;
		}

		////Exception& PushMsg()
		////{
		////	if (m_Msg.GetLength() > 0)
		////	{
		////		Add(m_Msg,-1,L"");
		////		m_Msg = L"";
		////	}
		////	return *this;
		////}

		Exception& AddMessage(const string& msg,HRESULT hr=S_OK)
		{
			///string result;
			///COMPOSE_EXC_MSG_FOR_HR(msg,hr,result);
			//
			if (hr == S_OK || hr == E_FAIL || hr == E_UNEXPECTED)
			{
				if (msg.GetLength() > 0)
				{
					////PushMsg();
					//m_Msg = msg;
					Add(msg,-1,L"",hr);
				}
				else
				{
					Add(msg,-1,L"",hr);
				}
			}
			else
			{
				if (msg.GetLength() > 0) 
				{
					////PushMsg();
					////m_Msg = result;
					Add(msg,-1,L"",hr);
				}
				else
				{
					Add(msg,-1,L"",hr);
				}
			}
			//
			return *this;
		}

#		define CABINETS_STD_MSG_SOURCE L"������ �������"

		void ReadExtra()
		{
			ReadCOMErrorInfo();
		}

		inline void SetCurrentTime() 
		{
			m_OutputXml = false; 
			m_Time = COleDateTime::GetCurrentTime();
			m_MediaType = "text/html"; 
			m_SeverityLevel = SeverityError; // 
		}

		void ReadCOMErrorInfo()
		{
			CComPtr<IErrorInfo> spErrInfo;
			HRESULT rc = GetErrorInfo(0,&spErrInfo);
			if (rc == S_OK)
			{
				CComBSTR bstrSource;
				spErrInfo->GetSource(&bstrSource);
				CComBSTR bstrDescription;
				spErrInfo->GetDescription(&bstrDescription);
				//
				string source(bstrSource.m_str);
				source.Trim();
				string description(bstrDescription.m_str);
				description.Trim();
				//
				if (source.GetLength() > 0 || description.GetLength() > 0)
				{
					string msg;
					string traceMsg;
					//
					int trace_p = description.Find(L"Trace:");
					if (trace_p != -1)
					{
						msg = description.Left(trace_p);
						msg.Trim();
						if (msg.Right(4) == L"----") 
						{
							msg = msg.Left(msg.GetLength()-4);
							msg.Trim();
						}
						traceMsg = description.Right(description.GetLength()-trace_p-6);
						traceMsg.Trim();
					}
					else
					{
						msg = description;
					}
					//
					m_Trace.Parse(traceMsg); 
					//
					if ((source.GetLength() > 0) &&
						(source != CABINETS_STD_MSG_SOURCE)) Add(source,-1,L"",Trace::NoStatus()); 
					//
					if (msg.GetLength() > 0) 
					{
						string statusText;
						//
						int p2 = msg.Find(L"\n");
						if (p2 == -1)
						{
							statusText = FormatStr(L"%d", (int)S_OK );
						}
						else
						{
							statusText = msg.Right(msg.GetLength()-p2-1);
							statusText.Trim();
							msg = msg.Left(p2);
						}
						HRESULT status = E_UNEXPECTED;
						//try
						//{
							status = (HRESULT)_wtoi(statusText);
						//}
						//catch(...) {}
						AddMessage(msg,status);
					}
				}
			}
		}

		Exception& SetCOMErrorInfo() 
		{
			ICreateErrorInfo* pCErrInfo = 0;
			IErrorInfo *pErrInfo = 0;
			//
			string m_errInfo_source = CABINETS_STD_MSG_SOURCE; 
			//
			string m_errInfo_description = L"----\nTrace:\n" + GetStructuredText();
			//
			CComBSTR errSource(m_errInfo_source.GetString());
			CComBSTR errDescription(m_errInfo_description.GetString());
			//
			HRESULT r1 = CreateErrorInfo(&pCErrInfo);
			pCErrInfo->SetSource(errSource);
			pCErrInfo->SetDescription(errDescription);
			r1 = pCErrInfo->QueryInterface(IID_IErrorInfo,(LPVOID FAR*)&pErrInfo);
			if (SUCCEEDED(r1))
			{
				SetErrorInfo(0,pErrInfo);
				pErrInfo->Release();
			}
			pCErrInfo->Release();
			//
			return *this;
		}



		// ----
		// �������������� 

		string GetHtml() const // ~ Format(4) 
		{
			string msgText;
			string traceText;
			string resultText;
			//
			string msg = GetMsg(); 
			//
			msgText = L"<tr><td colspan=\"5\" class=\"errormessage\">" + msg + L"</td></tr>"; 
			//
			traceText = m_Trace.GetHtml();
			//
			resultText = GetTimeStr() + L"\n<br />\n" +
				L"<table class=\"A\">" + msgText + L"\n" + traceText + L"</table>";
			//
			return resultText; 
		}

		string GetXml() const // ~ Format(3) 
		{
			int statusCode = (int)GetStatus(); 
			//
			string xml1 = ExceptionUtil::SysMsgXmlHeader(statusCode,m_Time,m_VXslUrl,m_SeverityLevel); 
			//
			////string msg = GetMsg(); 
			//////
			////if (msg.GetLength() > 0)
			////{
			////	string line;
			////	line = L"<sysmsg:text>" + msg + L"</sysmsg:text>";  
			////	xml1 += line + L"\n"; 
			////}
			//
			xml1 += m_Trace.GetXml_SysMsg(); 
			//
			xml1 += L"</sysmsg:msg>"; 
			//
#			ifdef _DEBUG
			{
				OutputDebugStringW(xml1 + L"\n");  
			}
#			endif
			//
			return xml1;
		}

		string GetConsoleText() const // 
		{
			string msg = GetMsg(); 
			HRESULT status = GetStatus(); 
			//
			string msgText;
			if (status == S_OK)
			{
				if (msg.GetLength() > 0)
				{
					msgText = msg + L"\n\n";
				}
			} 
			else
			{
				msgText = msg + L"\n" + FormatStr(L"%d",(int)status) + L"\n\n";
			}
			//
			return msgText + L"Trace:\n" + m_Trace.ToString(); 
		}

		string GetStructuredText() const // 
		{
			string msg = GetMsg(); 
			//
			string s = msg + m_Trace.GetTailText();
			//
#			ifdef _DEBUG
			///s = L".\n" + s + L"\n.";
#			endif
			//
			return s;
		}

		string Format(int formatType=1) const 
		{
			if (formatType == 1) // StructuredText 
			{
				return GetStructuredText(); 
			}
			else if (formatType == 2) 
			{
				return GetConsoleText(); 
			}
			else if (formatType == 3) // XML 
			{
				return GetXml(); 
			}
			else if (formatType == 4) // HTML 
			{
				return GetHtml();
			}
			return L"";
		}

		inline string GetTimeStr() const 
		{
			string timeStr = FormatStr(L"%02d:%02d:%02d",
				m_Time.GetHour(), 
				m_Time.GetMinute(), 
				m_Time.GetSecond() 
				); 
			//
			string s = FormatStr(L"%02d.%02d.%04d &#160; %s", 
				m_Time.GetDay(), 
				m_Time.GetMonth(), 
				m_Time.GetYear(), 
				timeStr.GetString() 
				); 
			return s; 
		}

		string ToString(int formatType=2) const 
		{
			return Format(formatType);
		}

		// ----
		// Alarm etc.

		Exception& Alarm()
		{
			TRACE_LOG(ToString());
			//
			return *this;
		}
	};



#ifndef		FunctionError
#define		FunctionError(hr) ::::Exception(hr,TRACE_POINT_W)
#endif

#ifndef		FunctionErrorF
#define		FunctionErrorF(hr,facility) ::::Exception(hr,facility,TRACE_POINT_W)
#endif
			
#ifndef		FunctionErrorMsg
#define		FunctionErrorMsg(msg,hr) ::::Exception(string(msg),hr,TRACE_POINT_W)
#endif

#ifndef		MethodError
#define		MethodError(hr) ::::Exception(hr,TRACE_POINT_W)
#endif

#ifndef		MethodWarning
#define		MethodWarning(hr) ::::Exception(hr,TRACE_POINT_W).SetSeverity(::::Exception::SeverityWarning)
#endif

#ifndef		MethodInfoExc
#define		MethodInfoExc(hr) ::::Exception(hr,TRACE_POINT_W).SetSeverity(::::Exception::SeverityInfo)
#endif

#ifndef		MethodErrorF
#define		MethodErrorF(hr,facility) ::::Exception(hr,facility,TRACE_POINT_W)
#endif
			
#ifndef		MethodErrorMsg
#define		MethodErrorMsg(msg,hr) ::::Exception(string(msg),hr,TRACE_POINT_W)
#endif

#ifndef		ObjectIsEmpty
#define		ObjectIsEmpty() FunctionError(E_POINTER);
#endif



#define _Catch() \
	catch(::::Exception& exc) \
	{ \
		throw exc.AddIfNewSource(TRACE_POINT_W); \
	} \
	catch(::::LowLevelError& exc) \
	{ \
		throw MethodError(HRESULT(exc)); \
	} \
	catch(...) \
	{ \
		throw MethodError(E_UNEXPECTED); \
	}

#define _FCatch() \
	catch(::::Exception& exc) \
	{ \
		throw exc.AddIfNewSource(TRACE_POINT_W); \
	} \
	catch(::::LowLevelError& exc) \
	{ \
		throw FunctionError(HRESULT(exc)); \
	} \
	catch(...) \
	{ \
		throw FunctionError(E_UNEXPECTED); \
	}

#define _ComCatch() \
	catch(::::Exception& exc) \
	{ \
		return exc.SetCOMErrorInfo().GetStatus(); \
	} \
	catch(::::LowLevelError& exc) \
	{ \
		return HRESULT(exc); \
	} \
	catch(...) \
	{ \
		return E_UNEXPECTED; \
	}

#define AlarmAboutException(exc) { TRACE_LOG(exc.Format()); }



#define _FilterExceptions() \
	catch(::::Exception& exc) \
	{ \
		throw; \
	} \
	catch(::::LowLevelError& exc) \
	{ \
		throw MethodError(HRESULT(exc)); \
	} \
	catch(CAtlException& exc) \
	{ \
		throw MethodError(HRESULT(exc)); \
	} \
	catch(...) \
	{ \
		throw MethodError(E_UNEXPECTED); \
	}



#define _NewErrorText(msg) (string(L"��� ��������� ����������: ") + msg)

#define _AddMessage(msg) \
	catch(::::Exception& exc) \
	{ \
		throw exc.AddIfNewSource(msg,__LINE__,::::string(__FILE__)); \
	} \
	catch(::::LowLevelError& exc) \
	{ \
		throw MethodError(HRESULT(exc)).AddIfNewSource(_NewErrorText(msg),__LINE__,::::string(__FILE__)); \
	} \
	catch(CAtlException& exc) \
	{ \
		throw MethodError(HRESULT(exc)).AddIfNewSource(_NewErrorText(msg),__LINE__,::::string(__FILE__)); \
	} \
	catch(...) \
	{ \
		throw MethodError(E_UNEXPECTED).AddIfNewSource(_NewErrorText(msg),__LINE__,::::string(__FILE__)); \
	}

#define _AddMessage2(msg_1,msg_2) \
	catch(::::Exception& exc) \
	{ \
		throw exc.AddIfNewSource(msg_1,__LINE__,::::string(__FILE__)).AddIfNewSource(msg_2,__LINE__,::::string(__FILE__)); \
	} \
	catch(::::LowLevelError& exc) \
	{ \
		throw MethodError(HRESULT(exc)).AddIfNewSource(_NewErrorText(msg_1),__LINE__,::::string(__FILE__)).AddIfNewSource(msg_2,__LINE__,::::string(__FILE__)); \
	} \
	catch(CAtlException& exc) \
	{ \
		throw MethodError(HRESULT(exc)).AddIfNewSource(_NewErrorText(msg_1),__LINE__,::::string(__FILE__)).AddIfNewSource(msg_2,__LINE__,::::string(__FILE__)); \
	} \
	catch(...) \
	{ \
		throw MethodError(E_UNEXPECTED).AddIfNewSource(_NewErrorText(msg_1),__LINE__,::::string(__FILE__)).AddIfNewSource(msg_2,__LINE__,::::string(__FILE__)); \
	}

} // namespace  
