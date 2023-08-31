/*
 SmartGOSTR.h : GOST R Algorithms.

 $Name: work1 $
 $Revision: 1.1.2.3 $
 $Date: 2008/10/16 07:09:28 $

 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif


#include <low-level/SmartException.h>
#include <low-level/SmartPtr.h>
#include <low-level/SmartMap.h>
#include <SlotAsn.h>
#include <ax/coclasses/AX_SlotMemoryReader.h>


namespace 
{
	class GOSTR
	{
	public:
		inline static CRITICAL_SECTION& CriticalSection() 
		{
			static bool crits_f = false;
			static CRITICAL_SECTION crits; 
			if (! crits_f)
			{
				InitializeCriticalSection(&crits); 
				crits_f = true;
			}
			return crits; 
		}

		class Lock
		{
		public:
			Lock()
			{
				EnterCriticalSection(&CriticalSection());
			}

			~Lock()
			{
				LeaveCriticalSection(&CriticalSection());
			}
		};

	public:
		// ---- 
		// Algorithms 

		// ----
		// Common functions 

		typedef unsigned __int32 UInt32;

		typedef unsigned __int64 UInt64;

		class I256 : public SharedArray<UInt64> // Length == 4 + 1 == 5 
		{
		public:
			I256()
			{
				Allocate(5); 
				(*this)[4] = 0; 
			}

			I256(const I256& other)
			{
				Allocate(5); 
				operator =(other);
			}

			inline Blob operator =(Blob data)
			{
				BYTE* p = data.GetBuffer();
				int n = data.Length();
				int pos = 0;
				//
				for (int k = 0; k < 4; k++)
				{
					UInt64 W = 0;
					//
					for (int s = 0; s < 64; s += 8)
					{
						UInt64 u = (pos < n) ? (UInt64)(*p) : 0;
						W = W | (u << s);
						//
						if (pos < n) { ++p; ++pos; }
					}
					(*this)[k] = W;
				}
				//
				(*this)[4] = 0; 
				//
				return data;
			}

			I256(Blob data)
			{
				Allocate(5); 
				operator =(data);
			}

			inline void SetToPositiveInteger(UInt64 x)
			{
				(*this)[0] = x;
				(*this)[1] = 0;
				(*this)[2] = 0;
				(*this)[3] = 0;
				(*this)[4] = 0;
			}

			inline void SetToInteger(__int64 x)
			{
				if (x > 0)
				{
					SetToPositiveInteger(x); 
				}
				else
				{
					(*this) = I256(-x).Minus(); 
				}
			}

			I256(UInt64 x) // x > 0 
			{
				Allocate(5); 
				//
				SetToPositiveInteger(x); 
			}

			I256(AsnObject o)
			{
				Allocate(4); 
				Blob data = o.Data();
				if (data.Length() == 0)
				{
					SetToPositiveInteger(o.m_Integer); 
				}
				else
				{
					(*this) = data; 
				}
			}

			inline void Zero()
			{
				SetToPositiveInteger(0); 
			}

			inline const I256& operator =(const I256& other)
			{
				(*this)[0] = other[0]; 
				(*this)[1] = other[1]; 
				(*this)[2] = other[2]; 
				(*this)[3] = other[3]; 
				(*this)[4] = other[4]; 
				//
				return other; 
			}

			inline I256 operator ^(const I256& y) 
			{
				const I256& x = *this; 
				//
				I256 z;
				z[0] = x[0] ^ y[0];
				z[1] = x[1] ^ y[1];
				z[2] = x[2] ^ y[2];
				z[3] = x[3] ^ y[3];
				z[4] = x[4] ^ y[4];
				return z;
			}

			inline I256 operator +(const I256& y) 
			{
				const I256& x = *this; 
				//
				I256 sum;
				//
				UInt64 m = 0;
				for (int j = 0; j < 5; j++)
				{
					UInt64 s = x[j] + y[j]; 
					if (s >= 256)
					{
						m = 1;
						s -= 256; 
					}
					else m = 0;
					//
					sum[j] = s;
				}
				return sum;
			}

			inline I256 Minus() const 
			{
				I256 minus;
				//
				minus[0] = (*this)[0] ^ 0xffffffffffffffffL; 
				minus[1] = (*this)[1] ^ 0xffffffffffffffffL; 
				minus[2] = (*this)[2] ^ 0xffffffffffffffffL; 
				minus[3] = (*this)[3] ^ 0xffffffffffffffffL; 
				minus[4] = (*this)[4] ^ 0xffffffffffffffffL; 
				//
				minus += I256((UInt64)1); 
				//
				return minus; 
			}

			inline I256 A() const // uses only 4 elements 
			{
				const I256& Y = *this; 
				//
				I256 r;
				r[0] = Y[1];
				r[1] = Y[2];
				r[2] = Y[3];
				r[3] = Y[0] ^ Y[1];
				r[4] = 0; 
				return r;
			}

			inline static int phi(int x) // x == 0..31, uses only 4 elements 
			{
#				ifdef _DEBUG
				{
					if (x < 0) throw MethodError(L"x < 0"); 
					if (x >= 32) throw MethodError(L"x >= 32"); 
				}
#				endif
				//
				int k = x >> 2; 
				int i = x << 3; 
				//
				int v = (i | k) & 0x1F; 
				return v;
			}

			inline UInt64 Part32(int i) const // uses only 4 elements 
			{
#				ifdef _DEBUG
				{
					if (i < 0) throw MethodError(L"i < 0"); 
					if (i >= 32) throw MethodError(L"i >= 32"); 
				}
#				endif
				//
				int k = i & 0x07; // ������ ������ ����� 
				i = i >> 3; // ����� ����� UInt64
				UInt64 v = (*this)[i]; 
				while (k > 0)
				{
					v = v >> 8; // ���� ����! 
					k--;
				}
				v = v & 0xff; 
				return v;
			}

			inline I256 P() const // uses only 4 elements 
			{
				I256 r;
				//
				int i = 0; // index in Y 
				int k = 0; // position inside Y[i] 
				UInt64 v = 0;
				for (int j = 0; j < 32; j++)
				{
					int q = phi(j); 
					UInt64 u = Part32(q); 
					v = v | (u << (8*k)); 
					//
					k++;
					if (k == 8)
					{
						r[i] = v; 
						v = 0; 
						//
						k = 0;
						i++;
					}
				}
				//
				return r; 
			}

			inline I256 GetCopy() const 
			{
				I256 Y;
				Y[0] = (*this)[0];
				Y[1] = (*this)[1];
				Y[2] = (*this)[2];
				Y[3] = (*this)[3];
				Y[4] = (*this)[4];
				return Y;
			}

			inline I256 psi() const // uses only 4 elements 
			{
				I256 r = *this; 
				//
				UInt64 a = (*this)[0];
				UInt64 s = a & 0xffff;
				a = a >> 16;
				s = s ^ (a & 0xffff);
				a = a >> 16;
				s = s ^ (a & 0xffff);
				a = a >> 16;
				s = s ^ a;
				//
				UInt64 b = (*this)[3];
				s = s ^ (b & 0xffff);
				b = b >> 48;
				s = s ^ b;
				//
				for (int j = 0; j <= 2; j++)
				{
					r[j] = (r[j] >> 16) | (r[j+1] << 48);
				}
				r[3] = (r[3] >> 16) | (s << 48); 
				//
				return r; 
			}

			inline I256 BitwiseAnd(UInt64 rhs) 
			{
				I256 result; 
				//
				result[0] = ((*this)[0] & rhs); 
				result[1] = ((*this)[1] ); 
				result[2] = ((*this)[2] ); 
				result[3] = ((*this)[3] ); 
				result[4] = ((*this)[4] ); 
				//
				return result; 
			}

			inline I256 BitwiseAnd(const I256& rhs) 
			{
				I256 result; 
				//
				result[0] = ((*this)[0]) & (rhs[0]); 
				result[1] = ((*this)[1]) & (rhs[1]); 
				result[2] = ((*this)[2]) & (rhs[2]); 
				result[3] = ((*this)[3]) & (rhs[3]); 
				result[4] = ((*this)[4]) & (rhs[4]); 
				//
				return result; 
			}

			inline I256 operator >>(UInt64 a) // a ��������� (!) 
			{
				I256 result; 
				//
				UInt64 i_a = 64 - a; 
				//
				//UInt64 m = 0;
				//for (int j = 0; j < a); ++j) m = (m << 1) | 0x1;
				//
				UInt64 v0 = (*this)[0]; 
				UInt64 v1 = (*this)[1]; 
				UInt64 v2 = (*this)[2]; 
				UInt64 v3 = (*this)[3]; 
				UInt64 v4 = (*this)[4]; 
				//
				result[4] = v4 >> a; 
				result[3] = (v4 << i_a) | (v3 >> a); 
				result[2] = (v3 << i_a) | (v2 >> a); 
				result[1] = (v2 << i_a) | (v1 >> a); 
				result[0] = (v1 << i_a) | (v0 >> a); 
				//
				return result; 
			}
			
			inline static UInt64 MinusUI64(UInt64 r0, UInt64 q, int& z) 
			{
				UInt64 r = r0 + z; 
				//
				if (r >= q)
				{
					z = 0; 
					return r - q; 
				}
				else
				{
					r = (0xffffffffffffffffL ^ q) + 1 + r; 
					z = 1;
					return r; 
				}
			}

			inline int CompareTo(const I256& y) const // only for positive arguments (!) 
			{
				const I256& x = *this; 
				//
				int r = 0;
				//
				UInt64 xSign = x[4] & 0x8000000000000000L;
				UInt64 ySign = y[4] & 0x8000000000000000L;
				//
				if (xSign == 0 && ySign != 0) r = 1; 
				if (xSign != 0 && ySign == 0) r = -1; 
				else
				{
					for (int j = 4; j >= 0 && (r == 0); j--)
					{
						if (x[j] > y[j]) 
						{
							r = 1;
						}
						else if (x[j] < y[j]) 
						{
							r = -1; 
						}
						else
						{
							// to the next step 
						}
					}
					//
					if (xSign != 0) r = -r; 
				}
				return r; 
			}

			inline I256 Mod(const I256& q) const // q > 0 (!) 
			{
				I256 r = *this; 
				//
				I256 minus_q = q.Minus(); 
				//
				// r.Echo(L"r="); 
				//
				bool done = false;
				while (! done)
				{
					int larger = r.CompareTo(q); 
					//
					if (larger != -1)
					{
						r = r + minus_q; 
						//int z = 0;
						//r[0] = MinusUI64(r[0], q[0], z); 
						//r[1] = MinusUI64(r[1], q[1], z); 
						//r[2] = MinusUI64(r[2], q[2], z); 
						//r[3] = MinusUI64(r[3], q[3], z); 
						//r[4] = MinusUI64(r[3], q[3], z); 
					}
					else 
					{
						done = true;
					}
				}
				//
				return r;
			}

			inline static I256 Sum_Mod(I256 x, I256 y, I256 p) 
			{
				I256 sum;
				//
				UInt64 m = 0;
				for (int j = 0; j < 3; j++)
				{
					UInt64 s = x[j] + y[j]; 
					if (s >= 256)
					{
						m = 1;
						s -= 256; 
					}
					else m = 0;
					//
					sum[j] = s;
				}
				//
				I256 result = sum.Mod(p); // sum.Mod(p, m) ?
			}

			//inline I256 Divide(const I256& y, I256& r) const 
			//{
			//	I256 x = *this; 
			//	I256 q(0L);
			//	//
			//	bool done = false; 
			//	if (!done)
			//	{
			//		int s = x.Compare(y);
			//		if (s == -1)
			//		{
			//			r = x;
			//			return q; 
			//		}
			//		else
			//		{
			//			x = x - y; 
			//		}
			//	}

			//	UInt64 _65 = _65_;
			//	//
			//	bool done = false;
			//	while (! done)
			//	{
			//		bool larger = false;
			//		if (_65 > 0)
			//		{
			//			larger = true;
			//		}
			//		else
			//		{
			//			for (int j = 3; j >= 0 && !larger; j--)
			//			{
			//				if (r[j] > q[j]) larger = true;
			//				else 
			//				{
			//					if (r[j] < q[j]) j = -1; 
			//				}
			//			}
			//		}
			//		//
			//		if (larger)
			//		{
			//			int z = 0;
			//			r[0] = MinusUI64(r[0], q[0], z); 
			//			r[1] = MinusUI64(r[1], q[1], z); 
			//			r[2] = MinusUI64(r[2], q[2], z); 
			//			r[3] = MinusUI64(r[3], q[3], z); 
			//			if (z < 0) _65 -= z;
			//		}
			//		else 
			//		{
			//			done = true;
			//		}
			//	}
			//	//
			//	return r;
			//}

			inline I256& operator ++() 
			{
				UInt64 z = 0; 
				for (int j = 0; j < 4; j++)
				{
					UInt64& x = (*this)[j];
					if (j == 0)
					{
						if (x == 0xffffffffffffffff)
						{
							x = 0;
							z = 1; 
						}
						else
						{
							++x;
							z = 0;
						}
					}
					else
					{
						if (z == 0)
						{
						}
						else // z == 1 
						{
							if (x == 0xffffffffffffffff)
							{
								x = 0;
								z = 1; 
							}
							else
							{
								++x;
								z = 0;
							}
						}
					}
				}
			}

			inline static void Euclid(I256 x_, I256 y_)
			{
				I256 x = x_;
				I256 y = y_;
				//
				bool done = false;
				while (!done)
				{
					int r = x.CompareTo(y); 
					if (r == 1)
					{
						x = x.Mod(y); 
					}
					else if (r == -1)
					{
						y = y.Mod(x); 
					}
					else // if (r == 0)
					{
						done = true;
					}
				}
			}

			inline bool IfZero() const 
			{
				return 
					((UInt64)(*this)[0]) == 0 &&
					((UInt64)(*this)[1]) == 0 &&
					((UInt64)(*this)[2]) == 0 &&
					((UInt64)(*this)[3]) == 0 &&
					((UInt64)(*this)[4]) == 0; // (!) 
			}

			inline void Echo(const string& prefix=L"I256: ") const 
			{
#				ifdef _DEBUG
				{
					string msg = prefix; 
					msg += L"0x";
					for (int i = 3; i >= 0; i--)
					{
						if (i != 3) msg += L""; 
						UInt64 a = (*this)[i]; 
						msg += FormatStr(L".%08x", (a >> 32) ) + FormatStr(L"%08x", (a & 0xffffffff) ); 
					}
					msg += L"\n"; 
					//
					//OutputDebugStringW(msg);
				}
#				endif
			}
		};

		class Key256 : private I256
		{
		public:
			Key256(const I256& other)
			{
				I256::operator =(other);
			}

			Key256(const Key256& other)
			{
				I256::operator =(other);
			}

			const I256& operator =(const I256& other)
			{
				I256::operator =(other);
				return other; 
			}

			UInt32 Part(int j) 
			{
				int i = j >> 1;
				UInt64 a = (*this)[i];
				if (j & 1) a = a >> 32;
				return (UInt32)(a & 0xffffffff); 
			}
		};

		class Message
		{
			inline void Clear() 
			{
				Position = 0; 
			}

		public:
			int Type;

			Blob m;

			Message(Blob m_)
			{
				Type = 1;
				m = m_;
				Clear();
			}

			const Message& operator =(const Message& other)
			{
				Type = other.Type;
				Position = other.Position;
				m = other.m;
				//
				return other; 
			}

			Message(const Message& other)
			{
				operator =(other);
			}

			inline UInt64 Length()
			{
				if (Type == 1) return m.Length(); 
				//
				return 0; 
			}

			inline UInt64 BitLength()
			{
				return 8 * Length(); 
			}

			// Reading 

			UInt64 Position;

			inline void Seek(UInt64 pos) 
			{
				if (Type == 1)
				{
					if (pos < 0) throw MethodError(L"pos < 0");
					if (pos > m.Length()) throw MethodError(L"pos > m.Length");
					//
					Position = pos; 
				}
			}

			inline bool OnEnd() 
			{
				if (Type == 1)
				{
					if (Position >= m.Length()) return true; 
					//
					return false;
				}
				return true; 
			}

			inline UInt64 ReadUInt64()
			{
				if (Type == 1)
				{
					BYTE* p = m.GetBuffer(); 
					UInt64 j = Position;
					UInt64 a = 0;
					for (int s = 0; s < 8; s++)
					{
						a = a << 8;
						a = a | p[j];
						j++;
					}
					Position = j;
					return a; 
				}
				return 0;
			}

			inline I256 ReadI256()
			{
				if (Type == 1)
				{
					I256 Y;
					//
					Y[3] = ReadUInt64();
					Y[2] = ReadUInt64();
					Y[1] = ReadUInt64();
					Y[0] = ReadUInt64();
					//
					return Y;
				}
				return I256();
			}
		};



		inline Blob Part(Blob a, int pos, int len) 
		{
			try
			{
				if (len <= 0) throw MethodError(L"len <= 0"); 
				//
				Blob r;
				r.Allocate(len); 
				//
				CopyMemory(r.GetBuffer(), a.GetBuffer() + pos, len); 
				//
				return r;
			}
			_Catch()
		}

		inline void Set(Blob r, int destPos, Blob source, int fromPos, int len)
		{
			try
			{
				CopyMemory(r.GetBuffer() + destPos, source.GetBuffer() + fromPos, len); 
			}
			_Catch()
		}

		inline void Set(Blob r, int destPos, Blob source)
		{
			try
			{
				int fromPos = 0; 
				int len = source.Length(); 
				//
				Set(r, destPos, source, fromPos, len);
			}
			_Catch()
		}

		inline Blob Xor(Blob a, Blob b)
		{
			try
			{
				int n = a.Length(); 
				if (n == 0) throw MethodError(L"a.Length == 0"); 
				//
				Blob r;
				r.Allocate(n); 
				BYTE* a_ = a.GetBuffer(); 
				BYTE* b_ = b.GetBuffer(); 
				BYTE* r_ = r.GetBuffer(); 
				//
				for (int j = 0; j < n; j++)
				{
					r_[j] = a_[j] ^ b_[j]; 
				}
				//
				return r; 
			}
			_Catch()
		}

		inline Blob Sum(Blob a, Blob b)
		{
			try
			{
				int n = a.Length(); 
				if (n == 0) throw MethodError(L"a.Length == 0"); 
				//
				Blob r;
				r.Allocate(n); 
				BYTE* a_ = a.GetBuffer(); 
				BYTE* b_ = b.GetBuffer(); 
				BYTE* r_ = r.GetBuffer(); 
				//
				int m = 0;
				for (int j = 0; j < n; j++)
				{
					int x = a_[j] + b_[j] + m; 
					if (x >= 256) 
					{
						m = 1;
						x = x - 256;
					}
					else
					{
						m = 0;
					}
					r_[j] = (BYTE)x; 
				}
				//
				return r; 
			}
			_Catch()
		}

#		ifndef Check_Len
#		define Check_Len(source, len, mustBe) \
			if (len != mustBe) \
				{ \
					string errMsg = FormatStr(_W(source) + L": ��������� ����� Y: %d, ������ ����: %d", (int)len, (int)mustBe ); \
					throw MethodError(errMsg); \
				} 
#		endif

#		ifndef Check_256
#		define Check_256(source, len) Check_Len(source)
#		endif



		// ---------------------------------------------------------------------------------------
		// GOST R 24.11-94

		inline I256 R3411_94__f(I256 H, I256 m, SharedArray<Blob>& SBox=R3411_94__Test_SBox()) 
		{
			try
			{
				// Key generation 
				//
				SharedArray<I256> K;  
				K.Allocate(5);
				//I256& K1 = K[1];
				//I256& K2 = K[2];
				//I256& K3 = K[3];
				//I256& K4 = K[4];
				//
				I256 U = H; // U.Echo(L"U = "); 
				I256 V = m; // V.Echo(L"V = "); 
				I256 W = U ^ V; // W.Echo(L"W = "); 
				K[1] = W.P(); // K[1].Echo(L"K1 = "); 
				//
				for (int j = 2; j <= 4; j++)
				{
					U = U.A() ^ R3411_94__C(j);
					V = V.A();
					V = V.A();
					W = U ^ V; 
					K[j] = W.P(); // K[j].Echo(L"K" + FormatStr(L"%d", j) + L" = "); 
				}
				//
				// Ciphering 
				//
				I256 S;
				for (int j = 0; j < 4; j++)
				{
					UInt64 N = H[j]; 
					R28147_89__Cipher_Simple(K[j+1], SBox, &N, 1); 
					S[j] = N; // S.Echo(L"S(j) = "); 
				}
				// S.Echo(L"S = "); 
				//
				// Mixing 
				//
				for (int j = 1; j <= 12; j++)
				{
					S = S.psi(); 
				}
				S = H ^ (m ^ S).psi(); 
				for (int j = 1; j <= 61; j++)
				{
					S = S.psi(); 
				}
				// S.Echo(L"H2 = "); 
				//
				return S;
			}
			_Catch()
		}

		inline I256 R3411_94__Hash(
			// input data 
			Message m, 
			// parameters 
			SharedArray<Blob>& SBox=R3411_94__Test_SBox() 
			) 
		{
			try
			{
				I256 H;
				H.Zero();
				//
				I256 S;
				S.Zero();
				//
				while (! m.OnEnd())
				{
					I256 a = m.ReadI256(); 
					//
					H = R3411_94__f(H, a, SBox); 
					S = S ^ a;
				}
				//
				I256 L;
				L.Zero();
				L[0] = m.BitLength();
				H = R3411_94__f(H, L, SBox); 
				//
				H = R3411_94__f(H, S, SBox); 
				// H.Echo(L"H="); 
				//
				return H; 
			}
			_Catch()
		}

		inline I256 R3411_94__Test() 
		{
			try
			{
				BYTE a[] = {
					0x73, 0x65, 0x74, 0x79, 0x62, 0x20, 0x32, 0x33, 
					0x3D, 0x68, 0x74, 0x67, 0x6E, 0x65, 0x6C, 0x20, 
					0x2C, 0x65, 0x67, 0x61, 0x73, 0x73, 0x65, 0x6D, 
					0x20, 0x73, 0x69, 0x20, 0x73, 0x69, 0x68, 0x54 
				};
				//
				Blob b;
				b.Allocate(sizeof(a));
				CopyMemory(b.GetBuffer(), a, sizeof(a)); 
				Message m(b); 
				//
				// Hashing 
				//
				I256 H = R3411_94__Hash(m); 
				return H; 
			}
			_Catch() 
		}



		// ----
		// Constants 

		inline I256 R3411_94__C(int j)
		{
			try
			{
				static I256 C2;
				static I256 C3;
				static I256 C4;
				//
				static bool inited = false;
				//
				if (! inited)
				{
					C2.Zero();
					C3.Zero();
					C4.Zero();
					//
					C3[0] = 0xff00ff00ff00ff00L;
					C3[1] = 0x00ff00ff00ff00ffL;
					C3[2] = 0xff0000ff00ffff00L;
					C3[3] = 0xff00ffff000000ffL;
					//
					inited = true; 
				}
				//
				if (j < 2 || j > 4) 
				{
					string errMsg = FormatStr(L"R3411_94__C: ��������� ������ ���������: %d", (int)j ); 
					throw MethodError(errMsg);
				}
				//
				switch (j)
				{
				case 2:
					return C2;
				case 3:
					return C3;
				default:
					return C4;
				}
			}
			_Catch()
		}

		inline static SharedArray<Blob>& R3411_94__Test_SBox()
		{
			try
			{
				static SharedArray<Blob> mSBox;
				//
				const BYTE a[] = {
					0x04, 0x0A, 0x09, 0x02, 0x0D, 0x08, 0x00, 0x0E, 0x06, 0x0B, 0x01, 0x0C, 
					0x07, 0x0F, 0x05, 0x03,
					//
					0x0E, 0x0B, 0x04, 0x0C, 0x06, 0x0D, 0x0F, 0x0A, 0x02, 0x03, 0x08, 0x01, 
					0x00, 0x07, 0x05, 0x09, 
					//
					0x05, 0x08, 0x01, 0x0D, 0x0A, 0x03, 0x04, 0x02, 0x0E, 0x0F, 0x0C, 0x07, 
					0x06, 0x00, 0x09, 0x0B, 
					//
					0x07, 0x0D, 0x0A, 0x01, 0x00, 0x08, 0x09, 0x0F, 0x0E, 0x04, 0x06, 0x0C, 
					0x0B, 0x02, 0x05, 0x03, 
					//
					0x06, 0x0C, 0x07, 0x01, 0x05, 0x0F, 0x0D, 0x08, 0x04, 0x0A, 0x09, 0x0E, 
					0x00, 0x03, 0x0B, 0x02, 
					//
					0x04, 0x0B, 0x0A, 0x00, 0x07, 0x02, 0x01, 0x0D, 0x03, 0x06, 0x08, 0x05, 
					0x09, 0x0C, 0x0F, 0x0E, 
					//
					0x0D, 0x0B, 0x04, 0x01, 0x03, 0x0F, 0x05, 0x09, 0x00, 0x0A, 0x0E, 0x07, 
					0x06, 0x08, 0x02, 0x0C, 
					//
					0x01, 0x0F, 0x0D, 0x00, 0x05, 0x07, 0x0A, 0x04, 0x09, 0x02, 0x03, 0x0E, 
					0x06, 0x0B, 0x08, 0x0C 
				};
				//
				if (mSBox.Length() == 0) 
				{
					mSBox.Allocate(8); 
					for (int j = 0; j < 8; j++) 
					{
						mSBox[j].Allocate(16); 
						CopyMemory(mSBox[j].GetBuffer(), ((BYTE*)a) + 16 * j, 16); 
					}
				}
				//
				return mSBox; 
			}
			_Catch()
		}



		// ----
		// GOST R 28147-89 

		inline SharedArray<Blob>& R28147_89__C12()
		{
			try
			{
				static SharedArray<Blob> C12;
				//
				if (C12.Length() == 0)
				{
					C12.Allocate(2); 
					//
					Blob& C1 = C12[0];
					Blob& C2 = C12[1];
					//
					C1.Allocate(4);
					C2.Allocate(4);
					//
					C1[0] = 0x04;
					C1[1] = 0x01;
					C1[2] = 0x01;
					C1[3] = 0x01;
					//
					C2[0] = 0x01;
					C2[1] = 0x01;
					C2[2] = 0x01;
					C2[3] = 0x01;
				}
				//
				return C12;
			}
			_Catch()
		}

		inline Blob& GostR3411_94_ParamSetParameters()
		{
			try
			{
				static string s = 
					L"MIHiMG8GByqFAwICHgAwZARATldk0auNy7+UGnpNLNEQENagVzWNOPL3D0nRWuov"
					L"jZRi7kMJs/SmohjGmOPBfOV+cGsJZvcCPItVlb8oObMuzAQgAAAAAAAAAAAAAAAA"
					L"AAAAAAAAAAAAAAAAAAAAAAAAAAAwbwYHKoUDAgIeATBkBECldHfRT/pm41THQkpg"
					L"7LQZgpCddR1PyQs7Ei9UeQigr9E+GjjHsYHG5lYFhwMl6/6cbfhtLqveILqJPJL4"
					L"01O8BCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
					;
				static Blob b;
				//
				Lock lock;
				//
				if (b.Length() == 0)
				{
					b = FromBase64String(s); 
				}
				//
				return b;
			}
			_Catch()
		}

		inline Blob GostR3411_94_CryptoProSBox(SharedArray<Blob>)
		{
			try
			{
			}
			_Catch()
		}

		inline Blob& GostR3410_2001_ParamSetParameters()
		{
			try
			{
				static string s = 
					L"MIID5jCBnAYHKoUDAgIjADCBkAIBBwIgX7/0mKqTjOc5uOAi+6/vQFY/bmo0cvwq" 
					L"UUwM6driO34CIQCAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEMQIhAIAA"
					L"AAAAAAAAAAAAAAAAAAFQ/ooYkpdhVMWc/Bk6zPWzAgECAiAI4qig5lFH1L1jFgMO"
					L"FtGchcl/CpyiZxIrlqu86n6PyDCBnwYHKoUDAgIjATCBkwIhAP//////////////"
					L"//////////////////////////2UAgIApgIhAP//////////////////////////"
					L"//////////////2XAiEA/////////////////////2xhEHCZWtEARYQbCbdhuJMC"
					L"AQECIQCNkeRx4Jic2iffUFpFPyt2NSlPLd8j47EirMmcnp8eFDCBvAYHKoUDAgIj"
					L"AjCBsAIhAIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAyWAiA+GvQZomml"
					L"+Gan08JcPfgK6Xklk3P/KxgvSdTOfhu8iwIhAIAAAAAAAAAAAAAAAAAAAAAAAAAA"
					L"AAAAAAAAAAAAAAyZAiEAgAAAAAAAAAAAAAAAAAAAAV9wDP/xpiTl5JcWG8yKGY8C"
					L"AQECID+oEkNZ+WaAuD0cPrLAcOXFRcmFjQPs+3RL+NcXcX78MIGfBgcqhQMCAiMD"
					L"MIGTAiEAm59gX1qFgQerHshea0HIqs+EboZ4kFHTeZj3uQItdZgCAwCAWgIhAJuf"
					L"YF9ahYEHqx7IXmtByKrPhG6GeJBR03mY97kCLXWbAiEAm59gX1qFgQerHshea0HI"
					L"qlgso1Ee3ft08C86ZZiYC7kCAQACIEHs5VdDcRqMPL83g80IwO5NTcRA1GQajzZu"
					L"VQ39s7tnMIGfBgcqhQMCAiQAMIGTAiEA////////////////////////////////"
					L"/////////ZQCAgCmAiEA/////////////////////////////////////////ZcC"
					L"IQD/////////////////////bGEQcJla0QBFhBsJt2G4kwIBAQIhAI2R5HHgmJza"
					L"J99QWkU/K3Y1KU8t3yPjsSKsyZyenx4UMIGfBgcqhQMCAiQBMIGTAiEAm59gX1qF"
					L"gQerHshea0HIqs+EboZ4kFHTeZj3uQItdZgCAwCAWgIhAJufYF9ahYEHqx7IXmtB"
					L"yKrPhG6GeJBR03mY97kCLXWbAiEAm59gX1qFgQerHshea0HIqlgso1Ee3ft08C86"
					L"ZZiYC7kCAQACIEHs5VdDcRqMPL83g80IwO5NTcRA1GQajzZuVQ39s7tn"
					;
				static Blob b;
				//
				Lock lock; 
				//
				if (b.Length() == 0)
				{
					b = FromBase64String(s); 
				}
				//
				return b;
			}
			_Catch()
		}

		inline UInt32 R28147_89__SBoxReplace(int i, int j, 
			SharedArray<Blob> mSBox) 
		{
			try
			{
				Blob& P = mSBox[i]; 
				return (UInt32)P[j]; 
			}
			_Catch()
		}

		inline UInt32 R28147_89__ApplySBox(UInt32 S, SharedArray<Blob> mSBox) 
		{
			try
			{
				UInt32 S2 = 0;
				for (int i = 0; i < 8; i++)
				{
					int j = S & 0x0f; 
					UInt32 x = R28147_89__SBoxReplace(i, j, mSBox); 
					S2 = S2 | (x << (4*i)); 
					S = S >> 4; 
				}
				return S2;
			}
			_Catch()
		}

		inline UInt32 R28147_89__Shift(UInt32 S, int a) 
		{
			try
			{
				UInt32 S2 = (S << a) | (S >> (32-a)); 
				return S2;
			}
			_Catch()
		}

		inline UInt64 R28147_89__Step(
			UInt32 X, SharedArray<Blob> mSBox, UInt64 N) 
		{
			try
			{
				UInt32 N1 = (UInt32)(N & 0xffffffffL); 
				UInt32 N2 = (UInt32)(N >> 32); 
				//
				UInt32 S = N1 + X; 
				//
				S = R28147_89__ApplySBox(S, mSBox); 
				//
				S = R28147_89__Shift(S, 11); 
				//
				S = S ^ N2; 
				//
				UInt64 _N_ = (N << 32) | S; 
				return _N_; 
			}
			_Catch()
		}

		inline unsigned __int64 R28147_89__Cycle(
			Key256 K, SharedArray<Blob> mSBox, unsigned __int64 N_) 
		{
			try
			{
				unsigned __int64 N = N_;
				//
				SharedArray<UInt32> keys;
				keys.Allocate(8);
				UInt32* keys_p = keys.GetBuffer(); 
				//
				for (int j = 0; j <= 7; j++)
				{
					UInt32 K_j = K.Part(j); 
					keys_p[j] = K_j; 
				}
				//
				for (int k = 1; k <= 3; k++)
				{
					for (int j = 0; j <= 7; j++)
					{
						N = R28147_89__Step(keys_p[j], mSBox, N); 
					}
				}
				//
				for (int j = 7; j >= 0; j--)
				{
					N = R28147_89__Step(keys_p[j], mSBox, N); 
				}
				//
				UInt64 result_N = (N >> 32) | (N << 32); 
				//
				return result_N; 
			}
			_Catch()
		}

		inline void R28147_89__Cipher_Simple(
			I256 K, SharedArray<Blob> mSBox, unsigned __int64* T, int n) 
		{
			try
			{
				if (n <= 0) return; // no data 
				//
				unsigned __int64 *pN = T; 
				//
				for (int pos = 0; pos < n; pos++)
				{
					unsigned __int64 N = *pN;
					//
					N = R28147_89__Cycle(K, mSBox, N); 
					//
					*pN = N;
					//
					pN++;
				}
			}
			_Catch()
		}

		inline void R28147_89__A()
		{
			try
			{
			}
			_Catch()
		}



		// ---------------------------------------------------------------------------------------
		// ���� � 34.10-2001 

		class EllipticCurve
		{
		public:
			I256 a;
			I256 b;
			I256 p;
			I256 q;
			I256 x;
			I256 y;

			EllipticCurve(AsnObject& paramO)
			{
				Parse(paramO); 
			}

			inline void Parse(AsnObject& paramO)
			{
				try
				{
					//OutputDebugStringW(paramO.Dump());
					//
					AsnObject& s1 = paramO[1];
					//OutputDebugStringW(s1.Dump());
					//
					AsnObject& aO = s1[0];
					a = I256(aO); 
					//
					AsnObject& bO = s1[1];
					b = I256(bO); 
					//
					AsnObject& pO = s1[2];
					p = I256(pO); 
					//
					AsnObject& qO = s1[3];
					q = I256(qO); 
					//
					AsnObject& xO = s1[4];
					x = I256(xO); 
					//
					AsnObject& yO = s1[5];
					y = I256(yO); 
				}
				_Catch()
			}

			inline void Echo() const 
			{
				try
				{
					a.Echo(L"a="); 
					b.Echo(L"b="); 
					p.Echo(L"p="); 
					q.Echo(L"q="); 
					x.Echo(L"x="); 
					y.Echo(L"y="); 
				}
				_Catch() 
			}
		};

		typedef SharedPtr<EllipticCurve> EC;

		class EllipticPoint
		{
		public:
			EC curve;

			I256 x;
			I256 y;

			EllipticPoint(EC curve_, I256 x_=I256(0L), I256 y_=I256(0L))
			{
				curve = curve_;
				x = x_;
				y = y_; 
			}

			inline const EllipticPoint& operator =(const EllipticPoint& other) 
			{
				curve = other.curve;
				x = other.x;
				y = other.y;
				//
				M = other.M;
				//
				return other; 
			}

			EllipticPoint(const EllipticPoint& other)
			{
				operator =(other); 
			}

			EllipticPoint()
			{
			}

			EllipticPoint(EC curve_)
			{
				curve = curve_;
			}

			inline static EllipticPoint Zero(EC curve) 
			{
				return EllipticPoint(curve,0,0);
			}

			inline static EllipticPoint P0(EC curve) 
			{
				EllipticPoint a(curve, curve->x, curve->y); 
				return a; 
			}

#ifdef _DEBUG
			inline EllipticPoint Multiple(I256 k_) 
			{
				PrepareDiadic(); 
				//
				EllipticPoint S = EllipticPoint::Zero(curve);
				//
				I256 k = k_;
				//
				for (int j = 0; j < 64; j++)
				{
					if (k.BitwiseAnd(0x1)) S = S + M[j]; 
					//
					k >> 1; 
				}
				//
				return S; 
			}

			inline void PrepareDiadic()
			{
				if (M.Length() > 0) return; 
				//
				M.Allocate(64);
				M[0] = *this; 
				for (int k = 1; k < 64; k++)
				{
					EllipticPoint& P = M[k-1];
					M[k] = P + P;
				}
			}
#endif

			SharedArray<EllipticPoint> M;

#ifdef _DEBUG
			inline EllipticPoint operator +(const EllipticPoint& Q2) 
			{
				const EllipticPoint Q1 = *this;
				//
				//const I256& x1 = Q1.x;
				//const I256& y1 = Q1.y;
				//const I256& x2 = Q2.x;
				//const I256& y2 = Q2.y;
				////
				//I256 i_x1 = x1.Minus();
				//I256 i_x2 = x2.Minus();
				//I256 i_y1 = y1.Minus(); 
				////
				//I256 la = (y2 + i_y1).Multiply((x2 + x2_i).Inverse());
				////
				//I256 x3 = la.Multiple(la) + i_x1 + i_x2; 
				//I256 i_x3 = x3.Minus(); 
				////
				//I256 y3 = la.Multiple(x1 + i_x3) + i_y1;
				//
				I256 x3;
				I256 y3; 
				//
				EllipticPoint sum(curve, x3, y3); 
				return sum;
			}
		};
#endif

		inline static OID& idGostR34102001TestParamSet() 
		{
			static OID oid(L"1.2.643.2.2.35.0");
			return oid;
		}

		inline static OID& idGostR34102001CryptoProAParamSet() 
		{
			static OID oid(L"1.2.643.2.2.35.1");
			return oid;
		}

		inline static OID& idGostR34102001CryptoProBParamSet() 
		{
			static OID oid(L"1.2.643.2.2.35.2");
			return oid;
		}

		inline static OID& idGostR34102001CryptoProCParamSet() 
		{
			static OID oid(L"1.2.643.2.2.35.3");
			return oid;
		}

		inline static OID& idGostR34102001CryptoProXchAParamSet() 
		{
			static OID oid(L"1.2.643.2.2.36.0");
			return oid;
		}

		inline static OID& idGostR34102001CryptoProXchBParamSet() 
		{
			static OID oid(L"1.2.643.2.2.36.1");
			return oid;
		}

		inline AsnObject& R3410_2001__ParameterSet()
		{
			try
			{
				static AsnObject P(true,AsnObject::UNIVERSAL,AsnObject::_NULL_);
				//
				Lock lock; 
				//
				if (P.Tag() == AsnObject::_NULL_)
				{
					P = GostR3410_2001_ParamSetParameters(); 
					//OutputDebugStringW(P.Dump());
				}
				//
				return P;
			}
			_Catch()
		}

		inline AsnObject& R3410_2001__Parameters(OID oid)
		{
			try
			{
				AsnObject& o = R3410_2001__ParameterSet().Children.operator [](oid);
				//OutputDebugStringW(o.Dump());
				return o; 
			}
			_Catch()
		}

		inline AsnObject& R3410_2001__TestParameters()
		{
			return R3410_2001__Parameters(idGostR34102001TestParamSet()); 
		}

		inline AsnObject& R3410_2001__CryptoProAParameters()
		{
			return R3410_2001__Parameters(idGostR34102001CryptoProAParamSet()); 
		}

		inline AsnObject& R3410_2001__CryptoProXchAParameters()
		{
			return R3410_2001__Parameters(idGostR34102001CryptoProXchAParamSet()); 
		}

		// ----
		// �������� ������� 
		
		inline static void RandomPause(UInt64 r0)
		{
			SYSTEMTIME st;
			GetSystemTime(&st);
			//
			UInt64 tau = 
				0x8000007 * st.wYear + 
				0x800005 * st.wMonth + 
				0x8000B * st.wDayOfWeek + 
				0x8001 * st.wMinute + 
				0x803 * st.wSecond + 
				3 * st.wMilliseconds;
			//
			UInt64 a = 17*((tau + RandomInt32() + r0) & 0xfff);
			UInt64 m = ((a >> 13) ^ a);
			UInt64 sleep_t = ((m >> 5) & 0x7) + 1;
			UInt64 J = (m >> 9) & 0x1f;
			m = m & 0xf;
			//
			UInt64 S = 0;
			for (int j = 0; j < m; j++)
			{
				Sleep((DWORD)sleep_t);
				//
				for (int u = 0; u < J; u++)
				{
					S += RandomInt32(); 
				}
			}
		}

		inline static UInt64 RandomUI64() 
		{
			UInt64 r0 = RandomInt32();
			//
			RandomPause(r0);
			//
			UInt64 r1 = RandomInt32();
			UInt64 r2 = RandomInt32();
			//
			return r0 ^ (r1 << 13) ^ (r2 << 33);
		}

		inline static I256 RandomI256(I256 q) 
		{
			I256 k;
			bool done = false;
			while (! done)
			{
				k[0] = RandomUI64();
				k[1] = RandomUI64();
				k[2] = RandomUI64();
				k[3] = RandomUI64();
				//
				if (k[3] < q[3]) done = true;
			}
			return k; 
		}

		inline SharedArray<I256> R3410_2001_SignHash(I256 h, EC curve) 
		{
			try
			{
				SharedArray<I256> result; 
				//
				I256& a = curve->a;  
				I256& b = curve->b; 
				I256& p = curve->p; 
				I256& q = curve->q; 
				//
				I256 e_ = h.Mod(q);  
				if (e_.IfZero()) e_ = I256((UInt64)1); 
				e_.Echo(L"e=");
				//
				I256 k = RandomI256(q); 
				k.Echo(L"k=");
				//
#				ifdef _DEBUG
				{
					k[0] = 0x4FED924594DCEAB3L;
					k[1] = 0x6DE33814E95B7FE6L;
					k[2] = 0x2823C8CF6FCC7B95L;
					k[3] = 0x77105C9B20BCD312L;
					//
					EllipticPoint P = EllipticPoint::P0(curve);
					EllipticPoint kP = P.Multiple(k); 
					kP.x.Echo(L"kP.x=");
					kP.y.Echo(L"kP.y=");
				}
#				endif
				//
				return result; 
			}
			_Catch()
		}

		inline void R3410_2001__Test()  
		{
			try
			{
				Lock lock;
				//
				EC curve = new EllipticCurve(R3410_2001__TestParameters()); 
				curve->Echo(); 
				//
				// I256 h = R3411_94__Test(); 
				//
				I256 h;
				h[0] = 0x67ECE6672B043EE5L;
				h[1] = 0xCE52032AB1022E8EL;
				h[2] = 0x88C09C25E0EEC61FL;
				h[3] = 0x2DFBC1B372D89A11L;
				//
				// �������� ����� 
				//
				I256 d;
				d[0] = 0x1D19CE9891EC3B28L;
				d[1] = 0x1B60961F49397EEEL;
				d[2] = 0x10ED359DD39A72C1L;
				d[3] = 0x7A929ADE789BB9BEL;
				//
				I256 xq;
				xq[0] = 0x6689DBD8E56FD80BL;
				xq[1] = 0x8585BA1D4E9B788FL;
				xq[2] = 0xD8595BEC458B50C5L;
				xq[3] = 0x7F2B49E270DB6D90L;
				//
				I256 yq;
				yq[0] = 0xDFFB101A87FF77DAL;
				yq[1] = 0xAF64D1C593D26627L;
				yq[2] = 0x85C8413A977B3CBBL;
				yq[3] = 0x26F1B489D6701DD1L;
				//
				// �������� ������� 
				//
				R3410_2001_SignHash(h, curve); 
			}
			_Catch() 
		}
	};

} // namespace 
