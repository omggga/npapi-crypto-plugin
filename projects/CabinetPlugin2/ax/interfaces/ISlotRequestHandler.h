/*
 COM-��������� ISlotRequestHandler --- ��������� ����������� ������� / ���������.

 $Name: work1 $
 $Revision: 1.1.2.1 $
 $Date: 2008/10/16 07:08:51 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#define SlotRequestHandlerFlag_KeepPost 0x0002

/* IDocumentHandler */

#ifdef AX_ISlotRequestHandler_IDL
[
	object,
	uuid("A36B3D62-D479-4bde-9700-D54442E96F3C"),
	oleautomation,	
	helpstring("ISlotRequestHandler Interface"),
	pointer_default(unique)
]
#else
[
	uuid("A36B3D62-D479-4bde-9700-D54442E96F3C"),
	helpstring("ISlotRequestHandler Interface")
]
#endif
__interface ISlotRequestHandler : public IUnknown 
{
public:
	// �������� 
	//
	[propget, helpstring("property Request")] STDMETHOD(Request)([out, retval] IStream** out_pRequest);
	[propput, helpstring("property Request")] STDMETHOD(Request)([in] IStream* request);
	//
	// ��������� ������� / ��������� 
	//
	STDMETHOD(OnRequest)([out] int* out_status,[out] BSTR* out_url,[out] BSTR* out_cachePath, 
		[out] BSTR* out_contentType,[out] IStream** out_stream); 
	//
	STDMETHOD(OnResponse)(); 
}; 
// ISlotRequestHandler  
