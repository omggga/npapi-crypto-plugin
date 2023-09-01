/*
 COM-интерфейс ISlotDataStreamInfo --- Интерфейс, который снабжает IStream / ISequentialStream
	информацией о свойствах передаваемых данных: Content Type и другие сведения.

 $Name: work1 $
 $Revision: 1.1.2.1 $
 $Date: 2008/10/10 15:09:16 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

/* ISlotFileReader */

#ifdef AX_ISlotDataStreamInfo_IDL
[
	object,
	uuid("7F4313A8-4716-4010-AB5C-04BC49DEF810"),
	oleautomation,	
	helpstring("ISlotDataStreamInfo Interface"),
	pointer_default(unique)
]
#else
[
	uuid("7F4313A8-4716-4010-AB5C-04BC49DEF810"),
	helpstring("ISlotDataStreamInfo Interface")
]
#endif
__interface ISlotDataStreamInfo : public IUnknown 
{
public:
	STDMETHOD(GetDataStreamParameter)([in] BSTR name,[out,retval] VARIANT* out_value);
	STDMETHOD(SetDataStreamParameter)([in] BSTR name,[in] VARIANT value);

	// Быстрый доступ к некоторым свойствам 

	[propput, helpstring("property ContentType")] STDMETHOD(ContentType)([in] BSTR contentType);
	[propget, helpstring("property ContentType")] STDMETHOD(ContentType)([out,retval] BSTR* out_contentType);

	// Управление

	[propput, helpstring("property DataStream")] STDMETHOD(DataStream)([in] IStream* dataStream);
	[propget, helpstring("property DataStream")] STDMETHOD(DataStream)([out,retval] IStream** out_dataStream);
}; 
