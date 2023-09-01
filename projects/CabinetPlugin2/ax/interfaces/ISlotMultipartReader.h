/*
 COM-интерфейс ISlotMultipartReader --- Интерфейс для чтения multipart/formdata. 

 $Name: work1 $
 $Revision: 1.1.2.1 $
 $Date: 2008/10/10 15:09:16 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

/* ISlotFileReader */

#ifdef AX_ISlotMultipartReader_IDL
[
	object,
	uuid("CACDAC5C-8F48-4cf9-981A-B49D63002972"),
	oleautomation,	
	helpstring("ISlotMultipartReader Interface"),
	pointer_default(unique)
]
#else
[
	uuid("CACDAC5C-8F48-4cf9-981A-B49D63002972"),
	helpstring("ISlotMultipartReader Interface")
]
#endif
__interface ISlotMultipartReader : public IUnknown 
{
public:
	// Входящие данные 

	[propput, helpstring("property Boundary")] STDMETHOD(Boundary)([in] BSTR boundary);

	STDMETHOD(Open)([in] IStream* inputStream);
	STDMETHOD(OpenData)([in] BYTE* data,[in] int len);

	// Headers 

	STDMETHOD(GetHeader)([in] int index,
		[out] BSTR* name,[out] VARIANT* description,[out] VARIANT* data);
}; 

 

 

