/*
 SlotXmlStructures.h : ������ �������� XML-����������� 

 $Name:  $
 $Revision: 1.1.2.2 $
 $Date: 2008/10/24 07:48:40 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


#include <low-level/SmartXml.h> 


namespace  {

	namespace XmlStructures 
	{

		inline string PrepareXslUrl( 
			const string& xslUrl,
			bool useXslBase=false,
			const string& xslBase=L"",
			const string& presetXslBase=L""
			) 
		{
			try
			{
				if (xslUrl.GetLength() == 0) return L""; 
				//
				string base;
				//
				if (useXslBase) 
				{
					if (xslBase.GetLength() > 0)
					{
						base = xslBase; 
					}
					else
					{
						base = presetXslBase; 
					}
				}
				//
				string url;
				//
				if (base.GetLength() > 0)
				{
					url = base + xslUrl; 
				}
				else
				{
					url = xslUrl; 
				}
				//
				return url; 
			}
			_Catch() 
		}

		inline string PrepareXslStyleSheetLine(
			bool useXsl,
			//
			const string& xslUrl=L"",
			bool useXslBase=false,
			const string& xslBase=L"",
			const string& presetXslBase=L"" 
			)
		{
			try
			{
				string url = useXsl ? PrepareXslUrl(xslUrl,useXslBase,xslBase,presetXslBase) : L""; 
				//
				string s;
				//
				if (url.GetLength() > 0) 
				{
					s = 
						L"<?xml-stylesheet"
							L" type=\"text/xsl\""
							L" href=\"" + xslBase + _W(_PKI_CKI_XSL_REL_PATH) + L"\"" 
						L" ?>"
						; 
				}
				//
				return s; 
			}
			_Catch() 
		}

	} // namespace XmlStructures 

} // namespace  
