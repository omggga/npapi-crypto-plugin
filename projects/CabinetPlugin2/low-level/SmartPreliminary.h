/*
 SmartPreliminary.h : Определения прекомпилятора, включаемые раньше любых других определений и файлов
					  (входит в файлы *Precompile.h, которые включаются в StdAfx.h)

 $Name: work1 $
 $Revision: 1.1.2.1 $
 $Date: 2008/10/10 15:12:24 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#pragma warning(disable: 4100 4127 4995)
