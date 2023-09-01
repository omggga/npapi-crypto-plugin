/*
 COM-интерфейс ISlotClient --- Персона - клиент системы Личный кабинет с сертификатом 

 $Name: work1 $
 $Revision: 1.1.2.3 $
 $Date: 2008/10/24 07:52:05 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


#include "ISlotSigner.h"


/* ISlotClient */

#ifdef AX_ISlotClient_IDL
[
	object,
	uuid("67727B56-5BF0-4e2c-ABFF-909C02183243"),
	oleautomation,	
	helpstring("ISlotClient Interface"),
	pointer_default(unique)
]
#else
[
	uuid("67727B56-5BF0-4e2c-ABFF-909C02183243"),
	helpstring("ISlotClient Interface")
]
#endif
__interface ISlotClient : public IUnknown 
{
public:
	STDMETHOD(Connect)([in] BSTR clientPkh);

	STDMETHOD(SetKeyPair)([in] IXMLDOMElement* KeyInfo_E, [in] IXMLDOMElement* CertInfo_E);

	[propget, helpstring("property PublicKeyHash")] STDMETHOD(PublicKeyHash)([out,retval] BSTR* out_pkh); 

	[propget, helpstring("property CertificateData")] STDMETHOD(CertificateData)([out] BYTE* out_data,[out] int* out_len);

	[propget, helpstring("property Signer")] STDMETHOD(Signer)([out,retval] ISlotSigner** out_signer); 

	[propget, helpstring("property SignerInfoXData")] STDMETHOD(SignerInfoXData)([out,retval] BSTR* out_SignerInfoXData); 

	[propput, helpstring("property SignerInfoXData")] STDMETHOD(SignerInfoXData)([in] BSTR bstrSignerInfoXData); 

	// ----
	// Общие функции 

	STDMETHOD(GetCommonKeyInfo)([in] BSTR pkh64,[in] int useXsl,
		[out,retval] IXMLDOMDocument** out_document); 
}; 

 

 

