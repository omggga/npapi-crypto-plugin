/*
 Alg_Common --- ����� ����������� ������ slot/cpp/alg.

 $Name: work1 $
 $Revision: 1.1.2.2 $
 $Date: 2008/05/20 12:39:18 $
 */

#pragma once

#include "../low-level/SmartPtr.h"
#include "../low-level/SmartMap.h"
#include "../low-level/SmartDefs.h"

namespace  
{
	namespace Algorithms 
	{

		struct NamespaceUriLexicon
		{
			inline static const string& XmlnsNs() 
			{ 
				static string nsUri = L"http://www.w3.org/2000/xmlns/"; 
				return nsUri;
			} 
		};

	} // namespace Algorithm 

} // namespace  
