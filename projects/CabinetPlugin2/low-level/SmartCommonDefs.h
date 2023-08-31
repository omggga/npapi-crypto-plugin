/*
 SmartCommonDefs.h : ����������� � ��������� ���������� (low-level) 

 $Name: work1 $
 $Revision: 1.1.2.1 $
 $Date: 2008/10/10 15:12:24 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif



// ----
// �����

#ifndef COMMON_XML_START
#define COMMON_XML_START (L"<?xml version=\"1.0\" ?>")
#endif

// ----
// Cabinet 

#ifndef __NAME
#define __NAME (_T(""))
#endif

#ifndef __REGISTRY_NAME
#define __REGISTRY_NAME (_T(""))
#endif

#ifndef _APP_DIR
#define _APP_DIR __NAME
#endif

#ifndef _CABINET_NAME
#define _CABINET_NAME (_T("Cabinet"))
#endif

#ifndef _CABINET_APP_DIR
#define _CABINET_APP_DIR _CABINET_NAME
#endif
