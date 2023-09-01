/*
 COM-интерфейс ISlotStreamChannel --- Дополнительный интерфейс для потока чтения из файла или URL.

 $Name: work1 $
 $Revision: 1.1.2.3 $
 $Date: 2008/10/31 15:25:53 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

/* ISlotStreamChannel */

#ifdef AX_ISlotStreamChannel_IDL
[
	object,
	uuid("4EA28DB5-D602-4680-AD41-7A1D3B553F19"),
	oleautomation,	
	helpstring("ISlotStreamChannel Interface"),
	pointer_default(unique)
]
#else
[
	uuid("4EA28DB5-D602-4680-AD41-7A1D3B553F19"),
	helpstring("ISlotStreamChannel Interface")
]
#endif
__interface ISlotStreamChannel : public IUnknown 
{
public:
	// ----
	// Потоки 

	// * Входной поток 

	[propput, helpstring("property InputStream")] STDMETHOD(InputStream)([in] IStream* inStream);
	[propget, helpstring("property InputStream")] STDMETHOD(InputStream)([out,retval] IStream** out_inStream);

	// * Выходной поток 

	[propput, helpstring("property OutStream")] STDMETHOD(OutStream)([in] IStream* outStream);
	[propget, helpstring("property OutStream")] STDMETHOD(OutStream)([out,retval] IStream** out_outStream);
}; 
