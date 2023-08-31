/*
 SmartState.h : ������������ ���������. 

 $Name: work1 $
 $Revision: 1.1.2.6 $
 $Date: 2008/10/31 16:00:32 $
 */

#pragma once 

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


#include "AtlX.h"
#include "SmartMap.h"
#include "SmartPtr.h"



namespace  { 

	class DynState
	{
	protected:
		DynState() 
		{
		}

		typedef Map<string,string> t_Glossary;

		inline static t_Glossary& _Glossary() 
		{
			try
			{
				static t_Glossary G;
				return G;
			}
			_Catch() 
		}

	public:
		inline static void SetParameter(const string& name, const string& value) 
		{
			try
			{
				_Glossary()[name] = value;
			}
			_Catch()
		}

		inline static string GetParameter(const string& name) 
		{
			try
			{
				string value;
				if (_Glossary().ContainsKey(name))
				{
					value = _Glossary()[name]; 
				}
				return value; 
			}
			_Catch()
		}
	};
}
