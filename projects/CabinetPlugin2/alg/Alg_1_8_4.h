
#pragma once

#include "Alg_Common.h"

namespace 
{
	namespace Algorithms
	{
		/// <summary>
		/// ��������� ����������.
		/// </summary>
		class Alg_1_8_4
		{
		public:
			Alg_1_8_4()
			{
			}

			stringArray Sort(stringArray A)
			{
				stringArray array = A;
				//
				for (int i = 0; i < array.Length()-1; ++i)
				{
					string x = array[i];
					//
					// ������� ����������� ������� ����� array[i+1],...,array[array.Length-1]
					//
					int min_k = i+1;
					string m_y = array[i+1];
					//
					for (int k = i+2; k < array.Length(); ++k)
					{
						if (LessThan(array[k],m_y))
						{
							min_k = k;
							m_y = array[k];
						}
					}
					//
					if (LessThan(m_y,x))
					{
						array[i] = m_y;
						array[min_k] = x;
					}
				}
				//
				return array;
			}

			bool LessThan(string x,string y)
			{
				for (int i = 0; (i < x.GetLength()) && (i < y.GetLength()); ++i)
				{
					if (CharLessThan(x[i],y[i])) return true; // x < y
					if (CharLessThan(y[i],x[i])) return false; // x > y
				}
				if (x.GetLength() < y.GetLength()) return true; // x < y
				if (x.GetLength() > y.GetLength()) return false; // x > y
				return false; // ������ x � y ���������
			}

			bool CharLessThan(wchar_t X,wchar_t Y)
			{
				string russianABC = RussianABC();
				string latinABC = LatinABC();
				string digits = Digits();
				//
				int Xclass = 0;
				int Yclass = 0;
				//
				if (digits.Find(X) != -1) Xclass = 1;
				if (latinABC.Find(X) != -1) Xclass = 2;
				if (russianABC.Find(X) != -1) Xclass = 3;
				//
				if (digits.Find(Y) != -1) Yclass = 1;
				if (latinABC.Find(Y) != -1) Yclass = 2;
				if (russianABC.Find(Y) != -1) Yclass = 3;
				//
				if (Xclass < Yclass) return true; // X < Y
				if (Xclass > Yclass) return false; // X > Y 
				//
				if (Xclass == 1)
				{
					int Xpos = digits.Find(X);
					int Ypos = digits.Find(Y);
					return Xpos < Ypos;
				}
				else if (Xclass == 2)
				{
					int Xpos = latinABC.Find(X);
					int Ypos = latinABC.Find(Y);
					return Xpos < Ypos;
				}
				else if (Xclass == 2)
				{
					int Xpos = latinABC.Find(X);
					int Ypos = latinABC.Find(Y);
					return Xpos < Ypos;
				}
				else // (Xclass == 0)
				{
					long Xcode = (long)X;
					long Ycode = (long)Y;
					return Xcode < Ycode;
				}
			}

			string& RussianABC()
			{
				static string russianABC =
					L"�����Ũ����������������������������������������������������������";
				return russianABC;
			}

			string& LatinABC()
			{
				static string latinABC = 
					L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
				return latinABC;
			}

			string& Digits()
			{
				static string digits = L"0123456789";
				return digits;
			}
		};
	}
}
