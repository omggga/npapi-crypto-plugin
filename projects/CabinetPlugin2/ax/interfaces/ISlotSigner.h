/*
 COM-интерфейс ISlotSigner --- Интерфей механизма ЭЦП.

 $Name: work1 $
 $Revision: 1.1.2.1 $
 $Date: 2008/10/10 15:09:16 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

/* ISlotSigner */

#ifdef AX_ISlotSigner_IDL
[
	object,
	uuid("1BD5CD1D-DB93-4396-9422-3D71287CD92A"),
	oleautomation,	
	helpstring("ISlotCrypt Interface"),
	pointer_default(unique)
]
#else
[
	uuid("1BD5CD1D-DB93-4396-9422-3D71287CD92A"),
	helpstring("ISlotCrypt Interface")
]
#endif
__interface ISlotSigner : public IUnknown 
{
public:
	STDMETHOD(Start)();

	STDMETHOD(AddBlobk)(
		[in] BYTE* data,
		[in] int size);

	STDMETHOD(GetSignature)(
		[out] BYTE** ppSignature,
		[out] int* pSignatureSize);

	STDMETHOD(GetSignature64)(
		[out] BSTR* out_signature); 

	STDMETHOD(GetSignature64_FCSM)(
		[in] BSTR in_signature, 
		[out] BSTR* out_signature 
		); 
}; 

 

 

