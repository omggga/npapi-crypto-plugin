/*
 COM-интерфейс ISlotXmlFilter --- Интерфей управления классом CSlotXmlFilter: 

	* Доступ к контексту XML-фильтра 

 $Name: work1 $
 $Revision: 1.1.2.1 $
 $Date: 2008/10/10 15:09:16 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

/* ISlotXmlFilter */

#ifdef AX_ISlotXmlFilter_IDL
[
	object,
	uuid("BBAC1F52-2559-4f1d-BAAC-C0110F2831FC"),
	oleautomation,	
	helpstring("ISlotXmlFilter Interface"),
	pointer_default(unique)
]
#else
[
	uuid("BBAC1F52-2559-4f1d-BAAC-C0110F2831FC"),
	helpstring("ISlotXmlFilter Interface")
]
#endif
__interface ISlotXmlFilter : public IUnknown 
{
public:
	STDMETHOD(Open)(); // Открываем фильтр, обрабатываем данные 

	[propput, helpstring("property OutStream")] STDMETHOD(OutStream)([in] IStream* outStream);
	[propget, helpstring("property OutStream")] STDMETHOD(OutStream)([out,retval] IStream** out_outStream);
}; 

 

 

