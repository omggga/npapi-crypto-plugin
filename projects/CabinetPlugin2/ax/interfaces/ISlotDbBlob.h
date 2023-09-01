/*
 COM-интерфейс для потокового обращения к Blob'у локальной базы данных ЛК.

 $Name: work1 $
 $Revision: 1.1.2.2 $
 $Date: 2008/10/24 07:52:05 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

/* ISlotDbBlob */

#ifdef AX_ISlotDbBlob_IDL
[
	object,
	uuid("07AF379F-50C6-4851-AA75-8CECB0D46D01"),
	oleautomation,	
	helpstring("ISlotDbBlob Interface"),
	pointer_default(unique)
]
#else
[
	uuid("07AF379F-50C6-4851-AA75-8CECB0D46D01"),
	helpstring("ISlotDbBlob Interface")
]
#endif
__interface ISlotDbBlob : public IUnknown 
{
public:
	STDMETHOD(Open)([in] BSTR bStrDbName, [in] BSTR bStrTable, [in] BSTR bStrNField, [in] BSTR bStrNValue,
		[in] BSTR bStrVField, [in] int len);
	//
	[propget, helpstring("property BlobStream")] STDMETHOD(BlobStream)([out,retval] IStream** out_stream); 
	[propget, helpstring("property Local")] STDMETHOD(Local)([out,retval] int* out_local); 
	[propget, helpstring("property Revalidate")] STDMETHOD(Revalidate)([out,retval] int* out_revalidate); 
	//
	STDMETHOD(Close)(); 
	STDMETHOD(Start)(); 
}; 
// ISlotDbBlob 
