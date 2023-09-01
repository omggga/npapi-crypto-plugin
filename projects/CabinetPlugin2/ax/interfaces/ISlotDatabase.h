/*
 COM-��������� ��� ���������� ��������� ����� ������ ��.

 $Name: work1 $
 $Revision: 1.1.2.2 $
 $Date: 2008/10/24 07:52:05 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

/* ISlotDatabase */

#ifdef AX_ISlotDatabase_IDL
[
	object,
	uuid("54B29F97-8383-4074-89F1-7D9A1E06BF50"),
	oleautomation,	
	helpstring("ISlotDatabase Interface"),
	pointer_default(unique)
]
#else
[
	uuid("54B29F97-8383-4074-89F1-7D9A1E06BF50"),
	helpstring("ISlotDatabase Interface")
]
#endif
__interface ISlotDatabase : public IUnknown 
{
public:
	STDMETHOD(SaveDataFromStream)([in] BSTR name, [in] IStream* stream); 

	STDMETHOD(GetBlobStream)([in] BSTR bStrDbName, [in] BSTR bStrTable, 
		[in] BSTR bStrNField, [in] BSTR bStrNValue, 
		[in] BSTR bStrVField, [out] IStream** stream);
}; 
// IMemoryReader 
