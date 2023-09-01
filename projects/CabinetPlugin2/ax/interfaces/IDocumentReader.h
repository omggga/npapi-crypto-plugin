/*
 COM-интерфейс ISlotCrypt --- Криптографические функции по стандарту ГОСТ Р 34.10-2001.

 $Name: work1 $
 $Revision: 1.1.2.1 $
 $Date: 2008/05/22 14:00:18 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

/* ISlotCrypt */

#ifdef AX_ISlotCrypt_IDL
[
	object,
	uuid("2C0BE425-4E88-45fc-B608-BDCC3411A9CA"),
	oleautomation,	
	helpstring("ISlotCrypt Interface"),
	pointer_default(unique)
]
#else
[
	uuid("2C0BE425-4E88-45fc-B608-BDCC3411A9CA"),
	helpstring("ISlotCrypt Interface")
]
#endif
__interface IDocumentReader : public IUnknown 
{
public:
	[propget, helpstring("property ContentHandler")] STDMETHOD(ContentHandler)([out,retval] IXMLDOMDocument** pVal);
	[propput, helpstring("property ContentHandler")] STDMETHOD(ContentHandler)([in] IXMLDOMDocument* pVal);
}; 

 

 

