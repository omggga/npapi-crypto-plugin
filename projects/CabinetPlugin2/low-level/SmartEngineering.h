/*
 Engineering.h : ����������� C++.

 $Name: work1 $
 $Revision: 1.1.2.1 $
 $Date: 2008/10/10 15:12:24 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

namespace  { 



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ������� ���������

// ����������� �-���-��������� ������ ���������� ������

template<class T>
T& Container()
{
	static T s;
	return s;
}

// ����������� �-���-��������� ���������� ������, ��������� ��������

template<class T,int index>
T& Container()
{
	static T s;
	return s;
}



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����������� �������

class NoClass
{
};

template<class T1=NoClass>
class NoT1 : public NoClass
{
};

template<class T1=NoClass,class T2=NoClass>
class NoT2 : public NoClass
{
};

template<class T1=NoClass,class T2=NoClass,class T3=NoClass>
class NoT3 : public NoClass
{
};



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����������� �������� ������� 

template<class _Head>
class EmptyChainNode : public _Head
{
};



} // namespace  
