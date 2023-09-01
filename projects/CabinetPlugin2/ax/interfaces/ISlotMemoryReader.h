/*
 COM-���������� ��������, ����������� IStream.

 $Name: work1 $
 $Revision: 1.1.2.2 $
 $Date: 2008/10/24 07:52:05 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

/* IMemoryReader */

#ifdef AX_ISlotMemoryReader_IDL
[
	object,
	uuid("D348019B-29F4-4045-8F32-134FC8567679"),
	oleautomation,	
	helpstring("IMemoryReader Interface"),
	pointer_default(unique)
]
#else
[
	uuid("D348019B-29F4-4045-8F32-134FC8567679"),
	helpstring("IMemoryReader Interface")
]
#endif
__interface ISlotMemoryReader : public IUnknown 
{
public:
	[propput, helpstring("property Data")] STDMETHOD(Data)([in] BYTE* data);
	[propput, helpstring("property Size")] STDMETHOD(Size)([in] int size);
	[propput, helpstring("property Blob")] STDMETHOD(Blob)([in] BYTE* pBlob);
}; 
// IMemoryReader 
