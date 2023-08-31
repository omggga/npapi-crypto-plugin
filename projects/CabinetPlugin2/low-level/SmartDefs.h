/*
 SmartDefs.h : ��������� �����������.

 $Name: work1 $
 $Revision: 1.1.2.3 $
 $Date: 2008/10/10 15:12:24 $

 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include "SmartCommonDefs.h"

#include "SmartPtr.h"
#include "SmartMap.h"

namespace 
{
	// ���������� ��� string

	typedef SharedArray<string> stringArray;

	typedef Map<string,string> stringMap;

} // namespace 
