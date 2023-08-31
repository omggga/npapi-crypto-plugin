/*
 SmartHeaders.h : ��������� �������.

 $Name: work1 $
 $Revision: 1.1.2.6 $
 $Date: 2008/10/31 16:00:32 $
 */

#pragma once 

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


#include <low-level/AtlX.h>
#include <low-level/SmartMap.h>
#include <low-level/SmartPtr.h>


namespace  { 

	class Headers
	{
	public:
		Map<string,string> M; 

		inline void Clear()
		{
			try
			{
				M.RemoveAll();
			}
			_Catch()
		}

		void ParseWebResponse(CStringA rawHeaderA) 
		{
			try
			{
				CStringA hA = rawHeaderA;
				while (hA.GetLength() > 0)
				{
					CStringA item;
					//
					int p1 = hA.Find("\n");
					if (p1 == -1)
					{
						item = hA;
						hA = "";
					}
					else
					{
						item = rawHeaderA.Left(p1);
						hA = rawHeaderA.Right(rawHeaderA.GetLength() - p1 - 1);
					}
					//
					item.Trim();
					//
					int p2 = item.Find(":");
					if (p2 != -1) // delimiter found 
					{
						string name = _W(item.Left(p2));
						string v = _W(item.Right(item.GetLength() - p2 - 1));
						v.Trim();
						//
						M[name] = v;
					}
				}
			}
			_Catch()
		}

		inline bool ContainsHeader(const string& name)
		{
			try
			{
				return M.ContainsKey(name);
			}
			_Catch() 
		}

		inline string GetHeader(const string& name)
		{
			try
			{
				return M[name];
			}
			_Catch() 
		}
	};

} // namespace  
