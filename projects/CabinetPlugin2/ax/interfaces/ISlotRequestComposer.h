/*
 COM-��������� ISlotRequestComposer --- ��������� ��� ����������� slotrequest:request 
	�� ��������� ������, ������� URL. 

 ���������� ���������� ������ ������������ ����������:
	
	IStream		��� ���������� � ������ ������ ��������������� XML-������� 

 $Name: work1 $
 $Revision: 1.1.2.3 $
 $Date: 2008/11/01 11:50:20 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


#include <ax/interfaces/ISlotClient.h>


/* ISlotFileReader */

#ifdef AX_ISlotRequestComposer_IDL
[
	object,
	uuid("32AF8281-2EC0-41fa-9AD9-B239CDC26030"),
	oleautomation,	
	helpstring("ISlotRequestComposer Interface"),
	pointer_default(unique)
]
#else
[
	uuid("32AF8281-2EC0-41fa-9AD9-B239CDC26030"),
	helpstring("ISlotRequestComposer Interface")
]
#endif
__interface ISlotRequestComposer : public IUnknown 
{
public:
	// URL 

	[propput, helpstring("property Url")] STDMETHOD(Url)([in] BSTR value);
	[propget, helpstring("property Url")] STDMETHOD(Url)([out,retval] BSTR* out_value);

	// PostStream --- ����� ������ 

	[propput, helpstring("property PostStream")] STDMETHOD(PostStream)([in] IStream* value);
	[propget, helpstring("property PostStream")] STDMETHOD(PostStream)([out,retval] IStream** out_value);

	// Client, SecurityStatus, PKH

	[propget, helpstring("property SecurityStatus")] STDMETHOD(SecurityStatus)([out,retval] int* out_status);

	[propput, helpstring("property Client")] STDMETHOD(Client)([in] ISlotClient* value);
	[propget, helpstring("property Client")] STDMETHOD(Client)([out,retval] ISlotClient** out_value);

	// ��������� 

	STDMETHOD(SetParameter)([in] BSTR source,[in] BSTR encType,[in] BSTR name,[in] BSTR value); 
	STDMETHOD(GetParameterAsText)([in] BSTR name,[out,retval] BSTR* value); 
	STDMETHOD(GetParameterAsInnerText)([in] BSTR name,[out,retval] BSTR* value); 
	STDMETHOD(GetParametersXml)([in] BSTR name,[out,retval] IXMLDOMNode** value); 
	//STDMETHOD(GetParameterAsXmlElement)([in] BSTR name,[out,retval] IXMLDOMElement* value); 

	// ��������� ����� ������, �������������� request. 
	// ����� ������ ����� ������ �������� �����, �������� ���������. 

	STDMETHOD(Open)();

	[propget, helpstring("property OutStream")] STDMETHOD(OutStream)([out,retval] IStream** out_value);
}; 



namespace  {

	enum PostContentStructure
	{
		PostContentStructure_SlotRequest = 0x100, 
		//
		PostContentStructure_Data = 1,
		PostContentStructure_Multipart = 2,
		PostContentStructure_Xml = 3,
		PostContentStructure_XmlSlotRequest = 3 | 0x100,
	};

} // namespace  
