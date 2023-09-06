
#pragma once 

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include "ProtocolAppDefs.h"			// ��������� ����������, ATL

#include "low-level\AtlX.h"					// ATL � ���� ����������� �������

#include "inet-proto\ProtocolDefs.h"	// �������: Protocol, 

// ----
// low-level

#include "low-level\TracePoint.h"
#include "low-level\SmartException.h"
#include "low-level\SmartText.h"
#include "low-level\SmartPtr.h"
#include "low-level\SmartFile.h"
#include "low-level\SmartMap.h"
#include "low-level\SmartUtil.h"
#include "low-level\SmartDefs.h"

//using namespace ;

// XmlLite

#include <xmllite.h>
#pragma comment(lib, "xmllite.lib" )

// ActiveX 

#include "ProtocolApp.h"
