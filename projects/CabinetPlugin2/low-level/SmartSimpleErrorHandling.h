/*
 SimpleErrorHandling.h : ���������� ������� ��������� ������, ������� ��������� ������
 � ����������� � DebugOutput � ������ � EventLog.

 $Name: work1 $
 $Revision: 1.1.2.1 $
 $Date: 2008/10/10 15:12:24 $

 ��������!   ���� �������� ����������� ��� ������ ���������� #include � �� ���������� #pragma once
 */

// �� ���������� #pragma once

// 
//
#ifdef SIMPLE_ERROR_HANDLING
#include "SmartErrorHandling.h"
#else
#define SIMPLE_ERROR_HANDLING
#include "SmartErrorHandling.h"
#undef SIMPLE_ERROR_HANDLING
#endif
