/*
 SlotSysUtil.h : ����� ��������� ��������� ������� ��� ������� ������ �������.

 ����� Util

 $Name: work1 $
 $Revision: 1.1.2.2 $
 $Date: 2008/10/24 07:48:40 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


// -----
// h

#include "../low-level/AtlX.h"
#include "../low-level/SmartText.h"
#include "../low-level/SmartPtr.h"
#include "../low-level/SmartMap.h"
//// #include <low-level/SmartRegex.h>
// TODO: �������� �� SmartInf.h
//
#include "SlotLowLevel.h"


#ifndef CP_UNICODE
#define CP_UNICODE 0
#endif


namespace  { 



	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ����� Util

	// ����� ����������� � ��������������� ������� ����� 

	class Util : public LowLevel 
	{
	private:
		Util() 
		{
			LoadGlobals();
		}

		static Util& Acquire()
		{
			static Util s_util;
			return s_util;
		}

	protected:
		typedef TextMap GlobalsMapType;

		GlobalsMapType m_globals;

		void LoadGlobals()
		{
			if (! m_globals.IsEmpty()) return;
		}

	public:
		static Util& SetGlobal(const CString& name,const CString& value)
		{
			Util& U = Acquire();
			U.m_globals[name] = value;
			return U;
		}

		// �������������� ������, ����������� ��������, �������� ����������� �����������

		static CString Expand(const CString& textToExpand)
		{
			Util& B = Acquire();
			// ---------------------------------------------------------------------------------------
			
			CString text(textToExpand);
			
			bool done = false;
			while (! done)
			{
				bool applied = false;
				for (GlobalsMapType::Iterator i(B.m_globals); i; ++i)
				{
					bool matched;
					CString regx = i.Id();
					CString sub = i;
					text = text; //(!) RegExp::Replace(regx,sub,text,true,&matched);
					if (matched) applied = true;
				}
				if (! applied) done = true;
			}
			
			return text;
		}

		inline static CString GetUserName()
		{
			try
			{
				TCHAR userName[256];
				DWORD userNameSize = 256;
				if (! ::GetUserName(userName,&userNameSize)) 
				{
					throw MethodError(HRESULT_FROM_WIN32(GetLastError()));
				}
				//
				CString userNameStr(userName);
				//
				return userNameStr;
			}
			_Catch()
		}



		// ===========================================================================================
		// ��������� � �������������� ������ 

		inline static CString BlobToHex(Blob b,bool rotate=false)
		{
			CString S;
			for (int j = 0; j < b.GetSize(); ++j)
			{
				if (j > 0) S += _T("");
				CString a;
				if (rotate) a = FormatStr(_S("%02x"), (int)b[b.GetSize()-1-j] ); 
				else a = FormatStr(_S("%02x"), (int)b[j] ); 
				S += a.GetString();
			}
			return S;
		}

		static CStringW BlobToHexW(Blob b,bool rotate=false)
		{
			return CStringW(BlobToHex(b,rotate)); 
		}

		static Blob HexToBlob(const CString& Str,bool rotate=false)
		{
			Blob SN;
			
			CStringA S(Str);
			S.MakeUpper();
			int n = int(S.GetLength() / 2);
			if (2*n != S.GetLength()) throw FunctionError(string(L"��������� ����� ���������� ������������� �����"));
			SN.Allocate(n);
			
			BYTE* p = (BYTE*)S.GetString();
			
			for (int j = 0; j < n; ++j)
			{
				int c1 = (int)(unsigned char)p[2*j];
				int c2 = (int)(unsigned char)p[2*j+1];
				int d1 = -1;
				int d2 = -1;
				if ((c1 >= 0x30) && (c1 <= 0x39)) d1 = c1 - 0x30;
				else
				if ((c1 >= 0x41) && (c1 <= 0x46)) d1 = c1 - 0x41 + 10;
				
				if ((c2 >= 0x30) && (c2 <= 0x39)) d2 = c2 - 0x30;
				else
				if ((c2 >= 0x41) && (c2 <= 0x46)) d2 = c2 - 0x41 + 10;
				
				if ((d1 >= 0) && (d2 >= 0))
				{
					if (rotate) (SN.GetBuffer())[n-1-j] = BYTE(16*d1 + d2);
					else (SN.GetBuffer())[j] = BYTE(16*d1 + d2);
				}
				else throw FunctionError(string(L"������ � ��������� ������������� �����"));
			}
			
			return SN;
		}

		static CString StringToHex(const CString& S)
		{
			CStringA a(S);
			Blob b; b.Allocate(a.GetLength());
			CopyMemory(b.GetBuffer(),a.GetString(),a.GetLength());
			return BlobToHex(b);
		}

		static CString HexToString(const CString& hex)
		{
			Blob b = HexToBlob(hex);
			CStringA a((const char*)b.GetBuffer(),b.GetSize());
			return CString(a);
		}

		static void AddText(CStringW* text,const CStringW& item)
		{
			AddText(text,item,L", ");
		}

		static void AddText(CStringW* text,const CStringW& item,const CStringW& sep)
		{
			if (text->GetLength() > 0) (*text) += sep;
			(*text) += item;
		}

		inline static CString OIDStart()
		{ 
			return _T("1.2.643.6.2");
		}

		inline static CString PKIOIDStart()
		{ 
			return OIDStart() + _T(".1");
		}

		inline static CString PKIAttrOIDStart()
		{ 
			return OIDStart() + _T(".1.6");
		}

		inline static CString PKIPolicyOIDStart()
		{ 
			return OIDStart() + _T(".1.7");
		}

		inline static CString PKIPolicyJur()
		{
			return PKIPolicyOIDStart() + _T(".2");
		}

		inline static CString PKIPolicyPhys()
		{
			return PKIPolicyOIDStart() + _T(".2");
		}

		inline static bool IsPKIAttrOIDName(const CString& oidName)
		{
			CString start = CString("OID.") + PKIAttrOIDStart();
			return (oidName.Left(start.GetLength()).CompareNoCase(start) == 0);
		}

		inline static bool IsPKIAttrJurOIDName(const CString& oidName)
		{
			CString start = CString("OID.") + PKIAttrOIDStart() + _T(".1");
			return (oidName.Left(start.GetLength()).CompareNoCase(start) == 0);
		}

		inline static bool IsPKIAttrPhysOIDName(const CString& oidName)
		{
			CString start = CString("OID.") + PKIAttrOIDStart() + _T(".2");
			return (oidName.Left(start.GetLength()).CompareNoCase(start) == 0);
		}

		inline static bool IsOIDName(const CString& oidName)
		{
			return (oidName.Left(4).CompareNoCase(_T("OID.")) == 0);
		}

		static CString OIDFromName(const CString& oidName)
		{
			CString oid;
			if ((oidName.Left(4)).CompareNoCase(_T("OID.")) == 0) oid = oidName.Right(oidName.GetLength()-4);
			else oid = _T("");
			return oid;
		}

		static void ParseAttributeString(SharedArray<CString>& a,const CString& s)
		{
			int p1 = -1;
			int state = 0;
			TCHAR parSym = 0;
			for (int j = 0; j < s.GetLength() && (p1 == -1); ++j)
			{
				TCHAR sym = s[j];
				if (sym == _S("\"")[0])
				{
					if (state == 0) 
					{
						state = 1;
						parSym = sym;
					}
					else if (state == 1)
					{
						if (sym == parSym)
						{
							p1 = j+1;
						}
					}
				}
				else if (sym == _T('\''))
				{
					if (state == 0) 
					{
						state = 1;
						parSym = sym;
					}
					else if (state == 1)
					{
						if (sym == parSym)
						{
							p1 = j+1;
						}
					}
				}
			}
			//
			if (p1 != -1)
			{
				CString part = s.Left(p1); 
				part.Trim();
				CString s2 = s.Right(s.GetLength()-p1); 
				s2.Trim();
				//
				a.Add(part);
				ParseAttributeString(a,s2);
			}
		}

		static SharedArray<CString> ParseAttributeString(const CString& s)
		{
			SharedArray<CString> a;
			//
			ParseAttributeString(a,s);
			//
			return a;
		}

		static void ParseAttributeStringEx(TextMap& results,const CString& s)
		{
			SharedArray<CString> a;
			//
			ParseAttributeString(a,s);
			//
			for (int k = 0; k < a.GetSize(); ++k)
			{
				CString s = a[k];
				int p0 = s.Find(_T("="));
				if (p0 != -1)
				{
					CString name = s.Left(p0);
					CString r = s.Right(s.GetLength()-p0-1);
					r.Trim();
					if (r.GetLength() > 0)
					{
						if (r[0] == _T('"')) r =  r.Right(r.GetLength()-1);
					}
					if (r.GetLength() > 0)
					{
						if (r[r.GetLength()-1] == _T('"')) r =  r.Left(r.GetLength()-1);
					}
					results[name] = r;
				}
			}
		}



		// ===========================================================================================
		// ��������� ��������� ���������� 

		inline static CStringW DecodeToWideString(Blob b,DWORD codePage)
		{
			try
			{
				if (b.IsEmpty()) 
					return L"";
				//
				CBlobW u;
				int size1 = MultiByteToWideChar(codePage,MB_ERR_INVALID_CHARS,
					(char*)b.GetBuffer(),b.GetSize(),
					0,0);
				if (! size1)
				{
					HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
					throw FunctionError(rc);
				}
				u.Allocate(size1);
				size1 = MultiByteToWideChar(codePage,MB_ERR_INVALID_CHARS,
					(char*)b.GetBuffer(),b.GetSize(),
					u.GetBuffer(),u.GetSize());
				if (! size1)
				{
					HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
					throw FunctionError(rc);
				}
				//
				CStringW uValue(u.GetBuffer(),u.GetSize());
				// TRACE_LOG2(_T("Converted: %d, %s"), (int)size1, CString(uValue).GetString() );
				//
				return uValue;
			}
			_FCatch()
		}

		inline static CStringW CodePageToEncoding(DWORD codePage)
		{
			try
			{
				switch(codePage)
				{
				case CP_UNICODE:
					return L"utf-16";
				case CP_UTF8:
					return L"utf-8";
				case 1251:
					return L"windows-1251";
				default:
					throw MethodError(_W(_S(_S("���������������� CODE PAGE: %d") % (int)codePage)));
				}
			}
			_FCatch()
		}

		inline static DWORD EncodingNameToCodePage(const string& encoding)
		{
			try
			{
				string enc = encoding;
				enc.MakeLower();
				DWORD codePage; 
				if (enc == L"utf-16") codePage = CP_UNICODE;
				else if (enc == L"utf-8") codePage = CP_UTF8;
				else if (enc == L"windows-1251") codePage = 1251;
				else
				{
					throw MethodError(_W("���������������� ���������: ") + _W(encoding));
				}
				return codePage;
			}
			_FCatch()
		}

		inline static CStringW DecodeToWideString(Blob b,const string& encoding)
		{
			try
			{
				return DecodeToWideString(b,EncodingNameToCodePage(encoding));
			}
			_FCatch()
		}

		inline static CStringW UTF8ToWideString(Blob b)
		{
			try
			{
				// TRACE_LOG1(_T("UTF-8: %s"), (const TCHAR*)BlobToHex(b) );
				//			 
				CBlobW u;
				int size1 = MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,
					(char*)b.GetBuffer(),b.GetSize(),
					0,0);
				if (! size1)
				{
					HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
					throw FunctionError(rc);
				}
				u.Allocate(size1);
				size1 = MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,
					(char*)b.GetBuffer(),b.GetSize(),
					u.GetBuffer(),u.GetSize());
				if (! size1)
				{
					HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
					throw FunctionError(rc);
				}
				
				CStringW uValue(u.GetBuffer(),u.GetSize());
				// TRACE_LOG2(_T("Converted: %d, %s"), (int)size1, CString(uValue).GetString() );
				
				return uValue;
			}
			_FCatch()
		}

		inline static CStringW UTF8ToWideString(const BYTE* buf, int len)
		{
			try
			{
				// TRACE_LOG1(_T("UTF-8: %s"), (const TCHAR*)BlobToHex(b) );
				//			 
				CBlobW u;
				int size1 = MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,
					(const char*)buf,len,
					0,0);
				if (! size1)
				{
					HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
					throw FunctionError(rc);
				}
				u.Allocate(size1);
				size1 = MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,
					(const char*)buf,len,
					u.GetBuffer(),u.GetSize());
				if (! size1)
				{
					HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
					throw FunctionError(rc);
				}
				
				CStringW uValue(u.GetBuffer(),u.GetSize());
				// TRACE_LOG2(_T("Converted: %d, %s"), (int)size1, CString(uValue).GetString() );
				
				return uValue;
			}
			_FCatch()
		}

		static CStringW UTF8ToWideString(CBlobA& bA)
		{
			Blob b;
			b.Allocate(bA.GetSize());
			CopyMemory(b.GetBuffer(),bA.GetBuffer(),bA.GetSize());
			return UTF8ToWideString(b);
		}

		static CStringW UTF8ToWideString(const CRYPT_DATA_BLOB& bC)
		{
			Blob b;
			b.Allocate(bC.cbData);
			CopyMemory(b.GetBuffer(),bC.pbData,bC.cbData);
			return UTF8ToWideString(b);
		}

		template<class _A>
		static CString UTF8ToString(_A a)
		{
			return UTF8ToWideString(a);
		}

		static Blob WideStringToUTF8(const CStringW& text)
		{
			try
			{
				if (text.GetLength() == 0) return Blob();
				//
				Blob b;
				int size1 = WideCharToMultiByte(CP_UTF8,0, // WC_COMPOSITECHECK
					text.GetString(),text.GetLength(),0,0,
					0,0);
				if (! size1)
				{
					HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
					throw FunctionError(rc);
				}
				b.Allocate(size1);
				size1 = WideCharToMultiByte(CP_UTF8,0,
					text.GetString(),text.GetLength(),(char*)b.GetBuffer(),b.GetSize(),
					0,0);
				if (! size1)
				{
					HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
					throw FunctionError(rc);
				}
				return b;
			}
			_FCatch()
		}

		static Blob WideStringToUnicode(const CStringW& text)
		{
			try
			{
				Blob b;
				b.Allocate(text.GetLength()*sizeof(wchar_t));
				BYTE* p1 = b.GetBuffer();
				const BYTE* p2 = (const BYTE*)text.GetString();
				for (int j = 0; j < text.GetLength(); ++j)
				{
					p1[2*j] = p2[2*j+1];
					p1[2*j+1] = p2[2*j];
				}
				//CopyMemory(b.GetBuffer(),text.GetString(),text.GetLength()*sizeof(wchar_t));
				return b;
			}
			_FCatch()
		}

		static CStringW ASCIIToWideString(Blob& b,int start=0,int len=-1)
		{
			if (len == -1) len = b.GetSize();
			//
			CBlobA textBuf;
			textBuf.Allocate(len+1);
			CopyMemory(textBuf.GetBuffer(),b.GetBuffer()+start,len);
			textBuf[len] = 0;
			CStringW text(CStringA(textBuf.GetBuffer()));
			return text;
		}

		static CStringW ASCIIToWideString(void* p,int start,int len)
		{
			CBlobA textBuf;
			textBuf.Allocate(len+1);
			CopyMemory(textBuf.GetBuffer(),((BYTE*)p)+start,len);
			textBuf[len] = 0;
			CStringW text(CStringA(textBuf.GetBuffer()));
			return text;
		}

		static Blob WideStringToASCII(const CStringW& text)
		{
			CStringA textA(text);
			//
			Blob b;
			b.Allocate(textA.GetLength());
			CopyMemory(b.GetBuffer(),(const void*)textA.GetString(),textA.GetLength());
			return b;
		}

		static Blob FromBase64String(const CStringW& data64)
		{
			CStringA a(data64);
			a.Trim();
			//
			if (a.GetLength() == 0) return Blob();
			//
			Blob data;
			int size = a.GetLength()+512;
			data.Expand(size);
			Base64Decode(a.GetString(),a.GetLength(),data.GetBuffer(),&size);
			data.SetSize(size);
			return data;
		}

		static CStringW ToBase64String(Blob data)
		{
			if (data.Length() == 0) return L"";
			//
			CBlobA a;
			int len = 2*data.Length()+512;
			a.Expand(len);
			Base64Encode(data.GetBuffer(),data.Length(),a.GetBuffer(),&len,0);
			a.SetSize(len);
			return CStringW( CStringA(a.GetBuffer(),a.Length()) );
		}

		inline static Blob ReadLineA(char* a,int& start,int len,Blob& lineTail)
		{
			bool stop = false;
			bool reading = true;
			int eofline = -1;
			int pos;
			int newStart = 0;
			int eofl_n = 0;
			lineTail.Free();
			for (pos = start; pos < len && (! stop); ++pos)
			{
				char sym = a[pos];
				if ((sym == 0x0D) || (sym == 0x0A))
				{
					if (eofl_n < 2)
					{
						lineTail.Expand(eofl_n+1);
						lineTail[eofl_n] = (BYTE)sym;
						lineTail.SetSize(eofl_n+1);
						//
						if (eofl_n == 0) eofline = pos;
						//
						++eofl_n;
						//
						if (reading)
						{
						}
						reading = false;
					}
					else
					{
						stop = true;
						newStart = pos;
					}
				}
				else
				{
					if (! reading) 
					{
						stop = true;
						newStart = pos;
					}
				}
			}
			if (newStart == 0)
			{
				newStart = len;
			}
			if (reading)
			{
				eofline = len;
			}
			Blob line;
			if (start >= newStart) 
			{
			}
			else 
			{
				line.Allocate(eofline-start);
				CopyMemory(line.GetBuffer(),a+start,line.Length());
			}
			start = newStart;
			return line;
		}

	#	define STREAM_READER_BUF_MAX 2048

		struct StreamReader
		{
			IStream* stream;

			bool eof;

			Blob buf;

			int p0;

			int next_p0;

			StreamReader(IStream* stm) : stream(stm), eof(false)
			{
				p0 = 0;
				next_p0 = 0;
			}

			char operator [](int pos)
			{
				if ((p0 == 0) && (next_p0 == 0))
				{
					Read();
				}
				else if ((pos >= p0 + buf.Length()) && (buf.Length() > 0))
				{
					Read();
				}
				//
				if ((pos >= p0) && (pos < p0 + buf.Length()))
				{
					return (char)buf[pos-p0];
				}
				else if ((pos >= p0) && (buf.Length() == 0))
				{
					eof = true;
					return 0;
				}
				else 
				{
					throw MethodError(string(L"����� �� ������� ������"));
				}
			}

			bool Eof()
			{
				return eof;
			}

			void Read()
			{
				try
				{
					if (! buf.IsEmpty()) buf.Free();			
					buf.Expand(STREAM_READER_BUF_MAX);
					//
					p0 = next_p0;
					//
					ULONG read;
					HRESULT rc = stream->Read(buf.GetBuffer(),STREAM_READER_BUF_MAX,&read);
					if ((rc != S_OK) && (rc != S_FALSE)) 
						throw MethodError(rc);
					//
					TRACE_LOG2(_T("������: %d, %d"), (int)p0, (int)read );
					//
					if ((read > 0) && (rc == S_OK)) 
					{
						buf.SetSize(read);
						next_p0 += read;
					}
					else 
					{
						buf.SetSize(STREAM_READER_BUF_MAX);
						buf.Free();
					}
				}
				catch(::::Exception& e)
				{
					TRACE_LOG(e.ToString());
					throw e;
				}
				catch(...)
				{
					throw;
				}
			}
		};

		inline static Blob ReadLineA(StreamReader& a,int& start,Blob& lineTail,bool* streamEof)
		{
			bool stop = false;
			bool reading = true;
			int eofline = -1;
			int pos;
			int newStart = 0;
			int eofl_n = 0;
			Blob line;
			lineTail.Free();
			for (pos = start; !a.Eof() && (! stop); ++pos)
			{
				char sym = a[pos];
				if (! a.Eof())
				{
					if ((sym == 0x0D) || (sym == 0x0A))
					{
						line[pos-start] = (BYTE)sym;
						//
						if (eofl_n < 2)
						{
							lineTail.Expand(eofl_n+1);
							lineTail[eofl_n] = (BYTE)sym;
							lineTail.SetSize(eofl_n+1);
							//
							if (eofl_n == 0) 
								eofline = pos;
							//
							++eofl_n;
							//
							if (reading)
							{
							}
							reading = false;
						}
						else
						{
							stop = true;
							newStart = pos;
						}
					}
					else
					{
						if (! reading) 
						{
							stop = true;
							newStart = pos;
						}
						else
						{
							line[pos-start] = (BYTE)sym;
						}
					}
					//if ((pos < eofline) || (eofline == -1))
					//	line[pos-start] = (BYTE)sym;
				}
				else
				{
	#				ifdef _DEBUG
					///TRACE_LOG2(_T("��������� %d ���� �� ������ 0x%x"), (int)pos, (int)a.stream);
	#				endif
				}
			}
			*streamEof = a.Eof();
			//
			if (newStart == 0)
			{
				newStart = -1;
			}
			if (reading)
			{
				eofline = pos;
			}
			start = newStart;
			return line;
		}

		inline static void ReadHeaderA(Map<CStringA,CStringA>& headerData,const CStringA& headerStr)
		{
			CStringA name;
			//
			int p1 = headerStr.Find(":");
			if (p1 == -1)
			{
				name = headerStr;
			}
			else
			{
				name = headerStr.Left(p1);
				//
				CStringA headerV = headerStr.Right(headerStr.GetLength()-p1-1).Trim();
				//
				// CStringA V;
				int i = 0;
				int p2;
				do
				{
					p2 = headerV.Find(";");
					//
					CStringA assignment;
					//
					if (p2 == -1)
					{
						assignment = headerV;
					}
					else
					{
						assignment = headerV.Left(p2);
						headerV = headerV.Right(headerV.GetLength()-p2-1);
					}
					//
					assignment.Trim();
					//
					CStringA attributeName;
					CStringA attributeValue;
					//
					int p3 = assignment.Find("=");
					if (i == 0) p3 = -1;
					if (p3 == -1)
					{
						if (i == 0)
						{
							attributeName = "__header-value__";
							attributeValue = assignment;
						}
						else
						{
							attributeName = assignment;
							attributeValue = "1";
						}
					}
					else
					{
						attributeName = assignment.Left(p3);
						attributeValue = assignment.Right(assignment.GetLength()-p3-1);
						attributeValue.Trim();
						if (attributeValue.Left(1) == "\"") 
							attributeValue = attributeValue.Right(attributeValue.GetLength()-1);
						if (attributeValue.Right(1) == "\"") 
							attributeValue = attributeValue.Left(attributeValue.GetLength()-1);
					}
					headerData[attributeName] = CStringA(attributeValue);
					++i;
				}
				while(p2 != -1);
			}
			headerData["__header-name__"] = name;
		}



		// ===========================================================================================
		// ��������� ������� ��� XML 

		inline static CString XmlEncodeAttributeText(const CString& in_text)
		{
			CString text = in_text;
			//
			text.Replace(_T("="),_T("&eq;"));
			text.Replace(_T("<"),_T("&lt;"));
			text.Replace(_T(">"),_T("&gt;"));
			text.Replace(_T("\""),_T("&quot;"));
			text.Replace(_T("&"),_T("&amp;"));
			//
			return text;
		}

		inline static int HexDigitToInt(unsigned char digit)
		{
			if ((digit >= 0x30) && (digit <= 0x39))
			{
				return digit - 0x30;
			}
			else if ((digit >= 0x41) && (digit <= 0x46))
			{
				return 10 + digit - 0x41;
			}
			else if ((digit >= 0x61) && (digit <= 0x66))
			{
				return 10 + digit - 0x61;
			}
			else return 0;
		}



		// ===========================================================================================
		// Web 

		inline static void ParseQuery(Map<CStringA,CStringA>& data,const CStringA& Query)
		{
			try
			{
				SharedArray<CStringA> A = ParseQuery(Query);
				//
				for (int k = 0; k < A.GetSize(); ++k)
				{
					CStringA item = A[k];
					//
					int eq_p = item.Find("=");
					if (eq_p == -1)
					{
						data[item] = "1";	
					}
					else
					{
						CStringA name = item.Left(eq_p);
						CStringA value = item.Right(item.GetLength()-eq_p-1); 
						data[name] = value;
					}
				}
			}
			_FCatch()
		}

		inline static SharedArray<CStringA> ParseQuery(const CStringA& Query)
		{
			try
			{
				SharedArray<CStringA> A;
				//
				CString item;
				int k = 0;
				for (int j = 0; j < Query.GetLength(); ++j)
				{
					TCHAR ch = Query[j];
					if (ch == '&')
					{
						if (Query.Right(Query.GetLength()-j).Left(5) == "&amp;")
						{
							item += CStringA(Query[j],1);
						}
						else
						{
							A[k] = item;
							++k;
							item = "";
						}
					}
					else 
					{
						item += CStringA(Query[j],1);
					}
				}
				if (item.GetLength() > 0)
				{
					A[k] = item;
					++k;
					item = "";
				}
				//
				return A;
			}
			_FCatch()
		}

		inline static Blob UrlDecodeToBytes(const CStringA& text)
		{
			CStringA s = text;
			//
			Blob value;
			int state = 0;
			int code = 0;
			for (int j = 0; j < s.GetLength(); ++j)
			{
				char sym = s[j];
				//
				if (sym == '%')
				{
					if (state == 1) 
					{
						value[value.Length()] = (unsigned char)sym;
						state = 0;
					}
					else state = 1;
				}
				else
				{
					if (state == 0)
					{
						if (sym == '+') value[value.Length()] = (unsigned char)' ';
						else value[value.Length()] = (unsigned char)sym;
					}
					else if (state == 1)
					{
						code = HexDigitToInt((unsigned char)sym);
						state = 2;
					}
					else if (state == 2)
					{
						code = 16*code + HexDigitToInt((unsigned char)sym);
						value[value.Length()] = (unsigned char)code;
						state = 0;
					}
				}
			}
			return value;
		}

		inline static string UrlDecode(const CStringA& s,const string& encodingName)
		{
			Blob value = UrlDecodeToBytes(s);
			string text;
			//
			string encName = encodingName;
			encName.MakeLower();
			//
			if (encodingName == "utf-8")
			{
				if (value.IsEmpty()) return string();
				text = UTF8ToWideString(value);
			}
			else if (encodingName == "utf-16")
			{
				if (value.IsEmpty()) return string();
				text = string((const wchar_t*)value.GetBuffer(),(int)value.Length()/2);
			}
			else if (encodingName == "windows-1251")
			{
				if (value.IsEmpty()) return string();
				text = string(CStringA((const char*)value.GetBuffer(),(int)value.Length()));
			}
			else
			{
				throw FunctionError(_W(_S(_S("���������������� ��������� %s") % CString(encName).GetString() )));
			}
			return text;
		}

		//inline static string UrlEncode(const string& text)
		//{
		//	string E = text;
		//	//
		//	E.Replace(L"+",L"%2B");
		//	E.Replace(L"=",L"%3D");
		//	//
		//	return E;
		//}

		inline static CStringW PathToFileName(const CStringW& path)
		{
			int p1 = path.ReverseFind(L'\\');
			if (p1 == -1) return path;
			else return path.Right(path.GetLength()-p1-1);
		}



		// ===========================================================================================
		// ������� ������������ 

		inline static Blob GetSHA1(const CString& text)
		{
			CStringW textW(text);
			//
			HCRYPTPROV new_CSP = 0;
			//
			if (! CryptAcquireContext(
				&new_CSP, 
				NULL, 
				NULL, 
				PROV_RSA_FULL, 
				CRYPT_VERIFYCONTEXT)) 
			{
				TRACE_LOG1(_T("������ ��� ������ CryptAcquireContext: 0x%x"), (int)GetLastError() );
				return Blob();
			}
			//
			HCRYPTHASH hash = 0;
			if (! CryptCreateHash(new_CSP,CALG_SHA1,0,0,&hash))
			{
				TRACE_LOG1(_T("������ ��� ������ CryptCreateHash: 0x%x"), (int)GetLastError() );
				return Blob();
			}
			//
			BYTE* buf = (BYTE*)textW.GetBuffer();
			DWORD size = textW.GetLength()*sizeof(wchar_t);
			//
			if (! CryptHashData(hash,(BYTE*)buf,size,0))
			{
				TRACE_LOG1(_T("������ ��� ������ CryptHashData: 0x%x"), (int)GetLastError() );
				return Blob();
			}
			//
			DWORD dwDigestedSize = 0;
			if(! CryptGetHashParam(hash,
				HP_HASHVAL,
				0,
				&dwDigestedSize,
				0))
			{
				TRACE_LOG1(_T("������ ��� ������ CryptGetHashParam: 0x%x"), (int)GetLastError() );
				return Blob();
			}
			//
			Blob digest;
			digest.Allocate(dwDigestedSize); 
			//
			if(! CryptGetHashParam(hash,
				HP_HASHVAL,
				digest.GetBuffer(),
				&dwDigestedSize,
				0))
			{
				TRACE_LOG1(_T("������ ��� ������ CryptGetHashParam: 0x%x"), (int)GetLastError() );
				return Blob();
			}
			//
			return digest;
		}

		inline static CString GetSHA1Str(const CString& text)
		{
			return ::::Util::BlobToHex(GetSHA1(text),false);
		}

		static string NewGuidStr()
		{
			try
			{
				UUID guid = GUID_NULL; 
				//HRESULT hr =	
					::UuidCreate(&guid); 
				//
				unsigned char* GUIDA;
				UuidToStringA(&guid,&GUIDA);
				string GUIDs((TCHAR*)GUIDA);
				RpcStringFreeA(&GUIDA);
				return GUIDs;
			}
			_Catch()
		}



		// ===========================================================================================
		// �������� �������
		
		inline static bool DirectoryExists(const CString& path)
		{
			try
			{
				HANDLE h = CreateFile(path,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING
					,FILE_FLAG_BACKUP_SEMANTICS,0);
				if (h == INVALID_HANDLE_VALUE) 
				{
	#					ifdef _DEBUG
					HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
					AlarmAboutException( FunctionError(rc) );
	#					endif
					return false;
				}
				CloseHandle(h);
				return true;
			}
			_FCatch()
		}
	};



} // namesapce  
