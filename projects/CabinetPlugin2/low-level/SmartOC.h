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

// 
//
#include "SmartUtil.h"
#include "SmartException.h"
#include "SmartPtr.h"
#include "SmartMap.h"
#include "SmartXml.h"

namespace 
{
//#	define UseOCLocking

	class OCLock
	{
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

	public:
		OCLock()
		{
#	ifdef UseOCLocking
			EnterCriticalSection(&CriticalSection());
#	endif
		}

		~OCLock()
		{
#	ifdef UseOCLocking
			LeaveCriticalSection(&CriticalSection());
#	endif
		}
	};

	struct CacheObjectEntry
	{
		void* Pointer;

		string Id;

		COleDateTime t; 

		double dt; 

		inline void SetCurrentTime()
		{
			t = COleDateTime::GetCurrentTime(); 
			dt = 10; 
		}

		CacheObjectEntry(const string& id, double dtInSec) 
		{
			Pointer = 0; 
			//
			SetCurrentTime();
			//
			Id = id;
			dt = dtInSec; 
		}

		virtual ~CacheObjectEntry()
		{
		}
	};

	struct XmlObjectEntry : public CacheObjectEntry 
	{
		XmlObjectEntry(const string& id, double dtInSec, XmlDocument doc) : CacheObjectEntry(id,dtInSec) 
		{
			try
			{
				XmlDocument* doc_p = new XmlDocument(); 
				*doc_p = doc; 
				Pointer = static_cast<void*>(doc_p);
			}
			_Catch() 
		}

		~XmlObjectEntry()
		{
			try
			{
				if (Pointer)
				{
					XmlDocument* doc_p = static_cast<XmlDocument*>(Pointer);
					delete doc_p; 
				}
			}
			_Catch()
		}

		XmlDocument Document()
		{
			try
			{
				if (!Pointer) throw MethodError(L"No document!"); 
				//
				XmlDocument* doc_p = static_cast<XmlDocument*>(Pointer);
				return *doc_p; 
			}
			_Catch()
		}
	};

	struct StreamObjectEntry : public CacheObjectEntry
	{
		string ContentType; 
		string CachePath; 

		StreamObjectEntry(const string& id, double dtInSec, 
			IStream* stream, 
			const string& cType_, const string& cPath_ 
			) : CacheObjectEntry(id,dtInSec) 
		{
			try
			{
				if (!stream) throw MethodError(L"Stream == NULL"); 
				//
				ContentType = cType_;
				CachePath = cPath_;
				//
				CComPtr<IStream>* stream_p = new CComPtr<IStream>(); 
				(*stream_p).Attach(CComQIPtr<IStream>(stream).Detach()); 
				Pointer = static_cast<void*>(stream_p);
			}
			_Catch() 
		}

		~StreamObjectEntry()
		{
			try
			{
				if (Pointer)
				{
					CComPtr<IStream>* stream_p = static_cast<CComPtr<IStream>*>(Pointer);
					delete stream_p; 
				}
			}
			_Catch()
		}

		IStream* Stream() // new reference 
		{
			try
			{
				if (!Pointer) throw MethodError(L"No stream!"); 
				//
				CComPtr<IStream>* stream_p = static_cast<CComPtr<IStream>*>(Pointer);
				CComQIPtr<IStream> q(*stream_p); 
				return q.Detach(); 
			}
			_Catch()
		}
	};

	struct ObjCache
	{
		inline static ObjCache& Instance()
		{
			static ObjCache s_ObjCache;
			return s_ObjCache;
		}

		inline static Map<string,CacheObjectEntry*>& M() 
		{
			static Map<string,CacheObjectEntry*> s_M;
			return s_M;
		}

		inline static CacheObjectEntry* f_GetEntry(const string& id)
		{
			try
			{
				if (M().ContainsKey(id))
				{
					CacheObjectEntry* entryOld = M()[id];
					COleDateTime& oldTime = entryOld->t;
					double dt = entryOld->dt;
					//
					COleDateTimeSpan s = COleDateTime::GetCurrentTime() - oldTime;
					double actualDt = s.GetTotalSeconds();
					if (actualDt > dt)
					{
						M().Remove(id); 
						return NULL;
					}
					else
					{
						return entryOld; 
					}
				}
				else
				{
					return NULL; 
				}
			}
			_Catch() 
		}

		inline static  CacheObjectEntry* GetEntry(const string& id) 
		{
			try
			{
				OCLock lock;
				//
				return f_GetEntry(id); 
			}
			_Catch() 
		}

		inline static bool AddEntry(CacheObjectEntry* entry)
		{
			try
			{
				if (!entry) throw MethodError(L"entry == NULL");
				//
				OCLock lock;
				//
				string id = entry->Id; 
				//
				CacheObjectEntry* entryOld =  f_GetEntry(id);
				if (entryOld)
				{
					return false; // exists and valid (not expired) 
				}
				else
				{
					M()[id] = entry; 
					return true; 
				}
			}
			_Catch()
		}

		inline static bool AddXmlObject(const string& id, double dtInSec, XmlDocument doc)
		{
			try
			{
				XmlObjectEntry* eXml = new XmlObjectEntry(id, dtInSec, doc); 
				return AddEntry(eXml); 
			}
			_Catch()
		}

		inline static bool AddStreamObject(const string& id, double dtInSec, IStream* stream,
			const string& contentType, const string& cachePath)
		{
			try
			{
				StreamObjectEntry* eXml = new StreamObjectEntry(id, dtInSec, stream,
					contentType, cachePath
					); 
				return AddEntry(eXml); 
			}
			_Catch()
		}

		inline static bool GetXmlObject(const string& id, XmlDocument& outDoc)
		{
			try
			{
				CacheObjectEntry* entry = GetEntry(id); 
				if (entry)
				{
					XmlObjectEntry* eXml = static_cast<XmlObjectEntry*>(entry);
					outDoc = eXml->Document(); 
					return true; 
				}
				else
				{
					return false;
				}
			}
			_Catch()
		}

		inline static bool GetStreamObject(const string& id, IStream** outStream, 
			string& outContentType, string& outCachePath 
			)
		{
			try
			{
				if (!outStream) throw MethodError(E_POINTER); 
				//
				CacheObjectEntry* entry = GetEntry(id); 
				if (entry)
				{
					StreamObjectEntry* eXml = static_cast<StreamObjectEntry*>(entry);
					outContentType = eXml->ContentType;
					outCachePath = eXml->CachePath;
					*outStream = eXml->Stream(); // returns new reference 
					return true; 
				}
				else
				{
					return false;
				}
			}
			_Catch()
		}
	};
}
