/*
 CSP_CCOM.h : ��������� CSP �� ���� ������-���������� Crypto-COM.

 $Name: work1 $
 $Revision: 1.1.2.8 $
 $Date: 2009/05/18 13:20:20 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

// CCOM
//
#ifdef WIN64
//#	include <tools/CCOM/ccom_3_2_9.h>
#	include "../tools/CCOM/x64/ccevp.h"
#	error 64!
#else // WIN32
//#	include <tools/CCOM/ccom.h>
#	include "../tools/CCOM/x86/ccevp.h"
#	pragma comment(lib, "ccom33.lib" )
#endif
//
#include "../tools/CCOM/ccom_extra.h"

// CryptoPro
//
#include "../tools/CryptoPro/include/WinCryptEx.h" 

// 
//
#include "../low-level/SmartUtil.h"
#include "../low-level/SmartEToken.h"
#include "../low-level/SmartWriter.h"
#include "../alg/Alg_1_8_2.h"
#include "SlotCSP.h"
#include "SlotAsn.h"

// #include <dialogs/SlotPswDialog.h>

#define _CLOSE_PSE_AFTER_GEN (1)

namespace  {



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ������ CCOMException, CCOMLib, OPAQUE_PRIV_KEY 

//class CComException___ : public Exception
//{
//public: 
//	CComException() : Exception(string(FormatStr(_T("������ CCOM: %d"), int(ERR_get_last_error()) )))
//	{
//		TRACE_LOG(this->ToString()); 
//		TRACE_LOG(ERR_get_errors());
//	}
//
//	CComException(int r) : Exception(string(FormatStr(_T("������ CCOM: %d"), r )))
//	{
//		TRACE_LOG(this->ToString()); 
//		TRACE_LOG(ERR_get_errors());
//	}
//};

#define CComException() MethodError(FormatStr(L"������ CCOM: %d, ", (int)CCOM_GetLastError() ) + _W(CCOM_ErrorGetString())); 
#define CComExceptionI(I) MethodError(FormatStr(L"������ CCOM: %d, ", (int)I ) + _W(CCOM_ErrorGetString())); 



class CCOMLib
{
	inline static Blob& r_xO() 
	{
		static Blob r_x;
		return r_x;
	}

	inline static Blob& r_bufO() 
	{
		static Blob r_buf; 
		return r_buf;
	}

	inline static Blob& r_saveO() 
	{
		static Blob r_save;
		return r_save;
	}

	class CADB
	{
		TextMap m_ContainersToRemove;
		
	public:
		void AddContainerToRemove(const CString& PSEPath) 
		{
			m_ContainersToRemove[PSEPath] = PSEPath;
		}

		CADB()
		{
			PKCS11_Manager::Lock lock; 
			//
			///TRACE_LOG(_T("CADB(): 0"));
			static BYTE x[1024];
			static char buf[1024];
			// int save = 0;
			//
			r_xO().Allocate(256);
			r_bufO().Allocate(256);
			r_saveO().Allocate(256);
			//
			//void* x = r_xO().GetBuffer();
			//char* buf = (char*)r_bufO().GetBuffer();
			//int* save = (int*)r_saveO().GetBuffer();
			//
			//int r0 = PSE_pseudo_rand_init(x,buf,&save,&getch_cb,0); 
			///TRACE_LOG(_T("CADB(): 1"));
			//
			// CADB_init();
			CCOM_Init();
			//
			///TRACE_LOG(_T("CADB(): 1+"));
			//long e1 = ERR_get_last_error();
			//if (e1 != 0) throw CComException(e1);
			//
			///TRACE_LOG(_T("CADB(): 2"));
			//
			// --> PSE context 
			//
			//int r0 = PSE_pseudo_rand_init(0,0,0,&getch_cb,0);
			//if (r0 == 0)
			//{
			//	long e1 = ERR_get_last_error();
			//	if (e1 != 0) throw CComExceptionI(e1);
			//}
			// int inited = PSE_rand_inited();
			// int randtype = PSE_get_rand_type();
			//
			///TRACE_LOG(_T("CADB(): +"));
		}

		~CADB()
		{
			// TODO !!!
			// CADB_close();
			RemoveContainers();
		}

		void RemoveContainers()
		{
			// TODO: �������! 
			//
			//foreach (DictionaryEntry entry in m_ContainersToRemove)
			//{
			//	string path = (string)entry.Value;
			//	//
			//	if (path != null && path != "")
			//	{
			//		string[] files = Directory.GetFiles(path,"*.*");
			//		for (int k = 0; k < files.Length; ++k)
			//		{
			//			string path_1 = files[k];
			//			if ((File.GetAttributes(path_1) & FileAttributes.Directory) == 0)
			//				File.Delete(path_1);
			//		}
			//		Directory.Delete(path,true);
			//	}
			//}
		}
	};

protected:
	inline static SharedPtr<CADB>& spCadbO() 
	{
		static SharedPtr<CADB> spCadb;
		return spCadb;
	}

public:
	static void Init()
	{
		if (! spCadbO().IsEmpty()) return;
		//
		spCadbO() = new CADB();
	}
		
	static void AddContainerToRemove(const CString& PSEPath)
	{
		Init();
		spCadbO()->AddContainerToRemove(PSEPath);
	}

	static int WINAPI getch_cb(int c,int step,int from,
#		ifdef WIN64
		void*
#		else
		//char* 
		void*
#		endif
		//userdata
		)
	{
		/////TRACE_LOG(_T("getch_cb"));
		//char cc[64];
		//cc[0] = (char)c;
		//cc[1] = '\n';
		//if (cc[0] == '\n') return -1;
		//return (int)(char)cc[0];
		//
		unsigned char cc[64];
		//
		static int _s = 0;
		if (!_s) srand((unsigned int)time(0));
		//
		int x = (int)(7 + 3*(rand() % 3)); 
		Sleep(x); 
		//
		return c; 
		//
		fprintf(stdout, "Step=%2i Press '%c': ", step, c); 
		//
		//if (debug)
		//{
		//	fprintf(stdout, "%c\n", c); 
		//	return c;	/* debug only */
		//}
		fgets((char *)cc, sizeof(cc), stdin);
		if(strcmp((char *)cc, "\n") == 0) return -1;
		return *cc;
	}



public:
	inline static void LoginEToken() 
	{
		try
		{
			// PKCS11_Manager::Lock lock; 
			//
			CCOMLib::Init();
			//
			// PKCS11_eToken& eToken = PKCS11_Manager::Acquire().ContextEToken(); 
			//
			// TODO !!!
			// ETOKEN_set_passwd_callback(EToken::etoken_passwd_cb);
			//
			//{
			//	t.pseCtx = PSE_CTX_new(); 
			//	//
			//	if (PSE_CTX_set_etoken(
			//		t.pseCtx, 
			//		userPassA.GetBuffer(), 
			//		userPassA.GetLength(), 
			//		0L
			//		) == 0)
			//	{
			//		int r1 = ERR_get_last_error();
			//		throw MethodError(FormatStr(L"������ CCOM: %d", (int)r1 ));
			//	}
			//	else
			//	{
			//		// TRACE_LOG(_T("����������� � eToken ������ �������!"));
			//	}
			//}
		}
		_Catch();
	}
};



//struct OPAQUE_PRIV_KEY
//{
//	Blob Data;
//
//	CCOM_SECRET_KEY_CTX *_ctx;
//
//	OPAQUE_PRIV_KEY(CCOM_SECRET_KEY_CTX *ctx) : _ctx(ctx) 
//	{
//	}
//
//	OPAQUE_PRIV_KEY(CCOM_SECRET_KEY_CTX *ctx, Blob data) : Data(data), _ctx(ctx) 
//	{
//	}
//
//	//OPAQUE_PRIV_KEY(Blob privData,Blob macData)
//	//{
//	//	Data.Allocate(GOST_PRIV_MAXLEN+GOSTE_MAC_LENGTH);
//	//	for (int j = 0; j < GOST_PRIV_MAXLEN; ++j) Data[j] = privData[j];
//	//	for (int j = 0; j < GOSTE_MAC_LENGTH; ++j) Data[GOST_PRIV_MAXLEN+j] = macData[j];
//	//}
//
//	OPAQUE_PRIV_KEY(const OPAQUE_PRIV_KEY& other) : Data(other.Data)
//	{
//	}
//
//	// unsigned char priv	[GOST_PRIV_MAXLEN];
//	Blob priv()
//	{
//		int len = CCOM_SecretKeyGetLength(_ctx); 
//		//
//		Blob out_priv;
//		out_priv.Allocate(len);
//		CopyMemory(out_priv.GetBuffer(),Data.GetBuffer(),len);
//		return out_priv;
//	}
//
//	// unsigned char mac	[GOSTE_MAC_LENGTH];
//	//Blob mac()
//	//{
//	//	Blob out_mac;
//	//	out_mac.Allocate(GOSTE_MAC_LENGTH);
//	//	for (int j = 0; j < GOSTE_MAC_LENGTH; ++j) 
//	//		out_mac[j] = Data[GOST_PRIV_MAXLEN+j];
//	//	return out_mac;
//	//}
//
//	int SizeOf()
//	{
//		int len = CCOM_SecretKeyGetLength(_ctx); 
//		//
//		return len;
//	}
//};







// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ������ CCOM_KeyObject, CCOM_Key

class CCOM_KeyObject : public KeyObject 
{
protected:
	CString m_containerName;

	mutable int m_pubKeyParameters;

	mutable int m_SBox;

	bool m_standalone;

	// ----
	// ContainerPath - ���� � ��������� �������� (��� ��������� ���� � ��������� ��������)

	CString m_keyContainerPath;

	bool UseTempContainerPath;

	mutable CString m_Password;

	CString m_PIN;

	// ----
	// �������� ��������� ���������� 

	// PSE_CTX* pseCtx;
	CCOM_PSE_CTX* pse;
	CCOM_KEY_PAIR_CTX *keypair;
	CCOM_PRIVATE_KEY_CTX *priv;
	CCOM_PUBLIC_KEY_CTX *pub;

	// ----
	// ����� 

	//mutable Blob KPrivData1; 
	
	//mutable Blob KMacData; 

	//mutable Blob xPtr; // ccom.lib ����� void*, � �� const void* 

	mutable Blob pk;

	int yLen;

	mutable Blob y;

	// OPAQUE_PRIV_KEY m_PrivateKey;

 //   OPAQUE_PRIV_KEY GetPrivateKey()
	//{
	//	return OPAQUE_PRIV_KEY(_keyCtx, xPtr);
	//}

	// ----
	// Xml

	XmlElement KeyInfo_E;

	// ----
	// ������

	void Clear()
	{
		m_standalone = false;
		//yLen = ECGOST_PUB_MAXLEN; // TODO !!! 
		m_pubKeyParameters = -1;
		m_SBox = -1;
		pse = 0; 
		keypair = 0;
		priv = 0;
		pub = 0;
		//
		eTokenID = L"";
		key_i = -1; 
	}

	virtual void Dispose()
	{
		FreePSE();
		//
		if (m_standalone)
		{
			if (m_keyContainerPath.GetLength() > 0)
				CCOMLib::AddContainerToRemove(m_keyContainerPath); 
		}
		//
		Clear();
	}

	void FreePSE()
	{
		if (pse) 
		{
			if(pse) CCOM_PSEFree(pse);
			if(keypair) CCOM_KeyPairFree(keypair);
			if(priv) CCOM_PrivateKeyFree(priv);
			if(pub) CCOM_PublicKeyFree(pub);
			//
			pse = 0;
			keypair = 0;
			priv = 0;
			pub = 0;
		}
	}

public:
	CCOM_KeyObject()
	{
		Clear();
	}

	virtual ~CCOM_KeyObject()
	{
		Dispose();
	}

	inline int GetCryptoSystemId() const 
	{
		return CryptoSystemIdCCOM;
	}

	void CreateIn(const CString& keyContainerPath)
	{
		try
		{
			CreateIn(_T(""), _T(""), _T("")); 
		}
		_Catch()
	}

	Blob GetCryptoProPublicKey() const // �������� ���� � ����� CryptoPro, ���� �������� ���� RSA 
	{
		try
		{
/*
			int j;
			//
			Blob PK = GetPublicKey();
			int len = PK.GetSize()-1; // == 64 
			Blob cpPubKey;
			cpPubKey.Allocate(len+2);
			//
			for (j = 0; j < 32; ++j) 
			{
				cpPubKey[63-j] = PK[1+31-j];
			}
			for (j = 0; j < 32; ++j) 
			{
				cpPubKey[63-(32+j)] = PK[1+32+31-j]; 
			}
			cpPubKey[len+1] = 0x04;
			cpPubKey[len] = (BYTE)len;
*/
			//
			Blob pk = GetPublicKey();
			//
			/*
			int len = pk.Length()-1; // == 64
			Blob cpPubKey; cpPubKey.Allocate(len+2); 
			//
			for (int j = 0; j < 32; ++j) 
			{
				cpPubKey[63-j] = pk[1+31-j];
			}
			for (int j = 0; j < 32; ++j) 
			{
				cpPubKey[63-(32+j)] = pk[1+32+31-j]; 
			}
			cpPubKey[len+1] = 0x04;
			cpPubKey[len] = (byte)len; 
			*/
			//
			return pk;
		}
		_Catch()
	}



	Blob GetPublicKey_OLD() const
	{
		return y;
	}

	Blob GetCryptoProPublicKey_OLD() const // �������� ���� � ����� CryptoPro, ���� �������� ���� RSA 
	{
		try
		{
			int j;
			//
			Blob PK = GetPublicKey();
			int len = PK.GetSize()-1; // == 64 
			Blob cpPubKey;
			cpPubKey.Allocate(len+2);
			//
			for (j = 0; j < 32; ++j) 
			{
				cpPubKey[63-j] = PK[1+31-j];
			}
			for (j = 0; j < 32; ++j) 
			{
				cpPubKey[63-(32+j)] = PK[1+32+31-j]; 
			}
			cpPubKey[len+1] = 0x04;
			cpPubKey[len] = (BYTE)len;
			//
			return cpPubKey;
		}
		_Catch()
	}




    inline Blob CryptoProPublicKeyToY(const Blob& cpPubKey)
    {
        Blob pk; pk.Allocate(cpPubKey.Length()-2 // == len
            +1);   
		//
        int j;
		for (j = 0; j < 32; ++j) 
		{
			pk[1+31-j] = cpPubKey[63-j];
		}
		for (j = 0; j < 32; ++j) 
		{
			pk[1+32+31-j] = cpPubKey[63-(32+j)];
		}
        pk[0] = 0x04;
        return pk;
    }

	inline void EnterETokenContext() const 
	{
		try
		{
			if (eTokenID.GetLength() == 0) return; // no action 
			//
			EToken& eToken = EToken::OpenEToken(eTokenID); 
			// 
			eToken.Login(); 
			eToken.EnterContext(); 
			CCOMLib::LoginEToken(); 
			//
			//PKCS11_Manager& M = PKCS11_Manager::Acquire(); 
			////
			//M.EnterContext(eTokenID); 
			////M.LoginEToken(eTokenSlotId); 
			////AsnObject o1 = 
			//	eToken.ReadMetaObject(OID__META); 
		}
		_Catch()
	}

	//unsigned char Reverse(unsigned char x) const 
	//{
	//	unsigned char y = 0;
	//	for (int j = 0; j < 8; j++)
	//	{
	//		y = y << 1;
	//		if (x & 0x01) y = y | 0x01;
	//		x = x >> 1;
	//	}
	//	return y;
	//}

    inline static Blob Reverse(const Blob& b)
    {
        Blob x; x.Allocate(b.Length());
        for (int j = 0; j < b.Length(); j++) x[j] = b[b.Length() - 1 - j];
        return x;
    }

	inline static int Read_(const Blob& data, Blob& data2, int len, int* pos) 
	{
		int size = (*pos + len <= data.Length()) ? len : data.Length() - *pos; 
		memcpy(data2.GetBuffer(), ((const BYTE*)data) + *pos, size); 
		pos += size; 
		return size; 
	}

    inline static Blob RussianDigest(int alg1, const Blob& data)
    {
        int size = (int)data.Length();
        if (size <= 0)
            throw new Exception(L"Cannot determine data stream size");
        //
        // ----
        // Digest
        //
        CCOM_DIGEST_CTX* digestCtx = CCOM_DigestNew(alg1);
        if (!digestCtx)
            throw MethodError(L"Failure in creating a digest (alg = {0})"); // alg1; 
        //
        //long digestLen2 = Lib33.CCOMDigestGetBlockLength(digestCtx);
        //throw new Exception(string.Format("digest lehgth = {0}", digestLen2));
        //
        //long sbox = Lib33.CCOMDigestCtrl(digestCtx,
        //    Lib33.CCOM_DIGEST_GET_GOSTR3411_94_SBOX, 0, IntPtr.Zero); // 22 -- ��������� 
        //throw new Exception(string.Format("sbox = {0}", sbox));
        //
        //if (sbox != SBox)
        //    throw new Exception(string.Format("Non-matching sbox: {0} != {1}", sbox, SBox));
        //
        if (!CCOM_DigestInit(digestCtx))
            throw MethodError(L"Failure in digest init");
        //
		int pos = 0; 
		//
        int digestBlockLen = CCOM_DigestGetBlockLength(digestCtx);
        int p1 = 0;
        while (p1 < size)
        {
            int inl = (p1 + digestBlockLen <= size) ? digestBlockLen : size - p1;
            //
			/*
            Blob dataChunk; dataChunk.Allocate(inl); 
            Blob data2; data2.Allocate(inl); 
            int read2 = Read_(data, data2, inl, pos);
            if (read2 != inl)
                throw new Exception(L"Wrong read size: {0} != {1}"); // , read2, inl;
            //
			if (!CCOM_DigestUpdate(digestCtx, data2.GetBuffer(), inl))
                throw MethodError(L"Failure in digest update");
				*/
            //
			if (!CCOM_DigestUpdate(digestCtx, (char*)const_cast<BYTE*>(((const BYTE*)data) + p1), inl))
                throw MethodError(L"Failure in digest update");
            //
            p1 += digestBlockLen;
        }
        //
        int digestLen = CCOM_DigestGetDigestLength(digestCtx);
        //
        Blob digest; digest.Allocate(digestLen); 
        //
        int outl;
        if (!CCOM_DigestFinal(digestCtx, (char*)const_cast<BYTE*>( (const BYTE*)digest ), &outl))
            throw MethodError(L"Failure in digest finalization");
        //
        return digest;
    }

    inline static Blob ReverseDigestForCryptoPro(const Blob& inDigest)
    {
        int digestLen = inDigest.Length();
        Blob digest; digest.Allocate(digestLen);
        //
        // ��������������
        //
        for (int j = 0; j < digestLen / 2; j++)
        {
            byte x1 = inDigest[j]; 
            digest[j] = inDigest[digestLen - 1 - j]; 
            digest[digestLen - 1 - j] = x1;
        }
        //
        return digest; 
    }

    inline static Blob RotateSigBytesForCryptoPro(const Blob& sig0)
    {
        const int siglen = 64;
        Blob sig; sig.Allocate(siglen);
        int _32 = siglen/2;
        for (int j1 = 0; j1 < _32; j1++) sig[j1] = sig0[32 + j1];
        for (int j1 = 0; j1 < _32; j1++) sig[32+j1] = sig0[j1];
        return sig;
    }

	Blob CreateRawSignature(Blob dataToSign, short flags = 0, Blob digest0 = Blob()) const 
	{
		try
		{
			CCOM_PSE_CTX* pse = CCOM_PSENew();
			if (!pse)
			{
				throw MethodError(L"������ ������ ��������� ���������� (0)");
			}
			//
			CStringA pathA(m_keyContainerPath);
			CStringA pA(m_Password);
			CStringA privPathA(_A(m_keyContainerPath) + "\\k.bin"); 
			CStringA pubPathA(_A(m_keyContainerPath) + "\\p.bin");
			//
			if(!CCOM_PSESetPath(pse, pathA.GetBuffer())) 
			{
				throw CComException();
			}
			if(!CCOM_PSESetPassword(pse, pA.GetBuffer(), pA.GetLength()))   
			{
				throw CComException();
			}
			if(!CCOM_PSERead(pse)) 
			{
				throw CComException();
			}
			CCOM_PRIVATE_KEY_CTX* priv = CCOM_PrivateKeyNew();
			if(!priv) 
			{
				throw CComException();
			}
			if(!CCOM_PrivateKeySetPSE(priv, pse)) 
			{
				throw CComException();
			}
			//if(!CCOM_PrivateKeySetPath(priv, privPathA.GetBuffer())) 
			//{
			//	throw CComException();
			//}
			if(!CCOM_PrivateKeySetPassword(priv, pA.GetBuffer(), pA.GetLength())) 
			{
				throw CComException();
			}
			::::File f4;
			f4.OpenToRead(_S(privPathA));
			Blob sKey = f4.ReadAll();
			f4.Close();
			//
            if (!CCOM_PrivateKeySetEncoded(priv, (char*)sKey.GetBuffer(), sKey.Length())) 
			{
				throw CComException();
                //throw MethodError(L"Failure in parsing private key");   
			}
			//
			if(!CCOM_PrivateKeyRead(priv)) 
			{
				throw CComException();
			}
			//
			// ----
			// Digest
			//
            int alg1 = CCOM_DIGEST_GOSTR3411_94_CP;  
            //
            Blob digest = (flags & 1)? digest0 : ReverseDigestForCryptoPro(RussianDigest(alg1, dataToSign));
			//
			// ----
			// Signature 
			//
			CCOM_SIGN_CTX* sign_ctx = CCOM_SignNew(priv);
			if(!sign_ctx) throw CComException();
			if(!CCOM_SignInit(sign_ctx)) throw CComException();
            //
			int siglen = 256;
			Blob sign;
			sign.Expand(siglen);
			//
            if (!CCOM_SignDigest(sign_ctx, (char*)digest.GetBuffer(), digest.Length(), (char*)sign.GetBuffer(), &siglen))
                throw MethodError(L"Failure in signing digest");
			//
			sign.SetSize(siglen); 
            //
            Blob sig = RotateSigBytesForCryptoPro(sign);
            //
            return Reverse(sig); 
		}
		_Catch()
	}

	Blob Encipher(Blob data) const
	{
		try
		{
			return Blob();
			//
			// TODO !!!
	//		void* ctx = GOSTE_new();
	//		if (! ctx) 
	//		{
	//			throw CComException();
	//		}
	//		// ������������ ������
	//		// �������������
	//		//if (! GOSTE_init(ctx, GOSTE_MODE_ECB, GOSTE_ENCRYPT, xPtr.GetBuffer(), NULL, DefaultSBox))
	//		if (! GOSTE_init(ctx, GOSTE_MODE_ECB, GOSTE_ENCRYPT, y.GetBuffer(), NULL, DefaultSBox))
	//		{
	//			throw CComException();
	//		}
	//		// ������������
	//		Blob obuf;
	//		obuf.Allocate(data.Length());
	//		if (GOSTE_update(ctx, data.GetBuffer(), obuf.GetBuffer(), data.Length()) != data.Length())
	//		{
	//			throw CComException();
	//		}
	//		return obuf;
		}
		_Catch()
	}

	Blob Decipher(Blob ciphered) const
	{
		try
		{
			return Blob();
			//
			// TODO !!! 
	//		void* ctx = GOSTE_new();
	//		if (! ctx) 
	//		{
	//			throw CComException();
	//		}
	//		// ������������� ������
	//		// �������������
	//		if (! GOSTE_init(ctx, GOSTE_MODE_ECB, GOSTE_DECRYPT, xPtr.GetBuffer(), NULL, DefaultSBox)) 
	//		{
	//			throw CComException();
	//		}
	//		// �������������
	//		Blob data;
	//		data.Allocate(ciphered.Length());
	//		if (GOSTE_update(ctx, ciphered.GetBuffer(), data.GetBuffer(), ciphered.Length())
	//			!= ciphered.Length())
	//		{
	//			throw CComException();
	//		}
	//		return data;
		}
		_Catch()
	}

	Blob GetPKH() const 
	{
		try
		{
			Blob pk = GetCryptoProPublicKey();
			string pkHashStr = Algorithms::Alg_1_8_2().Encode(pk);
			return Util::FromBase64String(pkHashStr);
		}
		_Catch()
	}

	bool VerifyRawSignatureByKey(Blob dataToSign) const 
	{
		try
		{
			throw MethodError(E_NOTIMPL); 
		}
		_Catch() 
	}

	//void SetXmlInfo(XmlElement value) 
	//{
	//	try
	//	{
	//		// ��������� ���� �� XML-�����
	//		//
	//		string keyContPath = KeyObject::GetTempContainerPath();
	//		//
	//		KeyInfo_E = (XmlElement)value; // .Clone();
	//		//
	//		PubKeyParameters = 12; // TODO: Convert.ToInt32(KeyInfo_E.GetAttribute("PubKeyParameters"),10);
	//		SBox = 22; // TODO: Convert.ToInt32(KeyInfo_E.GetAttribute("SBox"),10);
	//		//
	//		// Public Key 
	//		//
	//		XmlElement PK_E = (XmlElement)KeyInfo_E.SelectSingleNode("PublicKey");
	//		string yData64 = PK_E.InnerText();
	//		byte[] yData = Slot::Util::FromBase64String(yData64);
	//		PublicKey = yData;
	//		////Runtime.Echo("PublicKey: "+Util.BlobToHex(PublicKey));
	//		////Runtime.Echo("PubKeyHash: "+Convert.ToBase64String(PubKeyHash)+" : "+Util.BlobToHex(PubKeyHash));
	//		// TRACE_LOG2("PubKeyHash: "+Convert.ToBase64String(PubKeyHash)+" : "+Util.BlobToHex(PubKeyHash));
	//		//
	//		// Private Key 
	//		//
	//		XmlElement KPriv_E = (XmlElement)KeyInfo_E.SelectSingleNode("PrivateKey/EncryptedKey");
	//		string KPrivData64 = KPriv_E.InnerText();
	//		byte[] KPrivData = Slot::Util::FromBase64String(KPrivData64);
	//		XmlElement KMac_E = (XmlElement)KeyInfo_E.SelectSingleNode("PrivateKey/Mac");
	//		string KMacData64 = KMac_E.InnerText();
	//		byte[] KMacData = Slot::Util::FromBase64String(KMacData64);
	//		xPtr = CADBLib::OPAQUE_PRIV_KEY(KPrivData,KMacData).Data;
	//		//
	//		// Password
	//		//
	//		XmlElement PSE_E = (XmlElement)KeyInfo_E.SelectSingleNode("PSE");
	//		if (PSE_E.HasAttribute("Password")) m_Password = PSE_E.GetAttribute("Password");
	//		else m_Password = null;
	//		//
	//		// Files
	//		//
	//		XmlNodeList L = KeyInfo_E.SelectNodes("PSE/File");
	//		for (int file_i = 0; file_i < L.Count; ++file_i)
	//		{
	//			XmlElement File_E = (XmlElement)L[file_i];
	//			//
	//			string file = File_E.GetAttribute("Name");
	//			string data64 = File_E.InnerText();
	//			byte[] data = Slot::Util::FromBase64String(data64);
	//			//
	//			string path = keyContPath+"\\"+file;
	//			Slot::File f;
	//			f.Open(path);
	//			f.Replace((char*)data.GetBuffer(),data.Length());
	//			f.Close();
	//		}
	//		//
	//		// ������������� ���� � PSE � ������ �������� 
	//		//
	//		ContainerPath = keyContPath;
	//	}
	//	_Catch()
	//}

	void SetPath(const CString& path) 
	{
		m_keyContainerPath = path;
	}

	string m_CN; 
	string m_Org; 

	inline void SetCommonName(const string& cn) 
	{
		m_CN = cn; 
	}

	inline void SetOrgName(const string& org)
	{
		m_Org = org; 
	}

	inline string GetKeyLabel() const 
	{
		string label = m_CN; 
		if (m_Org.GetLength() > 0) label = label + L" [" + m_Org + L"]"; 
		return label; 
	}

	string GetXmlInfoText() const 
	{
		try
		{
			XmlElement Info_E = GetXmlInfo();
			return Info_E.OuterXml();
		}
		_Catch()
	}

	XmlElement GetXmlInfo() const
	{
		return XmlElement(KeyInfo_E);
	}



	void DeriveKeyWithPass(const string& pwd_, 
			HCRYPTPROV& hCryptProv, 
			HCRYPTKEY& hKey 
		) const 
	{
		try
		{
			// OUTPUT 
			//------------------------------
			//HCRYPTPROV hCryptProv;
			//HCRYPTKEY hKey;
			//------------------------------
			//
			HCRYPTHASH hHash;
			//CHAR szPassword[PASSWORD_LENGTH] = "";
			DWORD dwLength;
			//
			string pwd = L".#{e12" + pwd_.Right(5) + pwd_ + pwd_.Left(3) + L"18a133}//"; 
			//
			const char* szPassword_ = (const char*)pwd.GetString(); 
			dwLength = pwd.GetLength() * sizeof(wchar_t); 
			//
			if(!CryptAcquireContext(
			   &hCryptProv,
			   _T("CABINETK"),
			   NULL,
			   PROV_RSA_FULL,
			   0))
			{
				DWORD dwErr = GetLastError(); 
				//
				if (dwErr == NTE_BAD_KEYSET)
				{
					if(!CryptAcquireContext(
					   &hCryptProv,
					   _T("CABINETK"),
					   NULL,
					   PROV_RSA_FULL,
					   CRYPT_NEWKEYSET))
					{
						dwErr = GetLastError(); 
					}
					else
					{
						dwErr = 0; 
					}
				}
				//
				if (dwErr != 0)
				{
					HRESULT rc = HRESULT_FROM_WIN32(dwErr);
					throw MethodError(rc); 
				}
			}
			//
			if(!CryptCreateHash(
			   hCryptProv,
			   CALG_MD5,
			   0,
			   0,
			   &hHash))
			{
				HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
				throw MethodError(rc); 
			}
			//
			if(!CryptHashData(
			   hHash,
			   (BYTE *)szPassword_,
			   dwLength,
			   0))
			{
				HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
				throw MethodError(rc); 
			}
			//
			if(!CryptDeriveKey(
			   hCryptProv,
			   CALG_RC2,
			   hHash,
			   CRYPT_EXPORTABLE, // 40 << 16, // CRYPT_EXPORTABLE,
			   &hKey))
			{
				HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
				throw MethodError(rc); 
			}
			//
			//----------------------------------------------------------------
			// Clean up 
			//
			if(hHash)
			{
			   if(!(CryptDestroyHash(hHash)))
			   {
					HRESULT rc = HRESULT_FROM_WIN32(GetLastError());
					throw MethodError(rc); 
			   }
			}
		}
		_Catch() 
	} 

	inline static void CleanUpHKey(
		HCRYPTPROV& hCryptProv, 
		HCRYPTKEY& hKey 
		) 
	{
		try
		{
			// Cleanup key and cryptprov handles 
			//
			if(hKey)
			{
				if(!(CryptDestroyKey(hKey)))
				{
					HRESULT rc = HRESULT_FROM_WIN32(GetLastError()); 
					throw MethodError(rc); 
				}
			}
			if(hCryptProv)
			{
			   if(!(CryptReleaseContext(hCryptProv, 0)))
			   {
				   throw MethodError(L"Error during CryptReleaseContext");  
			   }
			}
		}
		_Catch()
	}

#	ifndef ENCRYPT_BLOCK_SIZE
#	define ENCRYPT_BLOCK_SIZE 8
#	endif

	Blob MultiEncryptWithPass(Blob data, const string& pwd, int method, bool methodInData=true)
	{
		try
		{
			int prefixLen = 4;
			if (methodInData)
			{
			}
			else
			{
				prefixLen = 0; 
			}
			//
			if (method == _KEY_ENCRYPT_METHOD_DUMMY) 
			{
				if (data.Length() == 0) throw MethodError(L"������� ������ (MultiEncrypt, method: 1)"); 
				//
				if (pwd.GetLength() == 0) throw MethodError(L"������ ���� (MultiEncrypt, method: 1)"); 
				//
				Blob bPwd;
				bPwd.Allocate(pwd.GetLength() * sizeof(wchar_t)); 
				CopyMemory(bPwd.GetBuffer(), (const BYTE*)pwd.GetString(), bPwd.Length()); 
				//
				Blob encData;
				encData.Allocate(prefixLen + data.Length() + bPwd.Length()); 
				ZeroMemory(encData.GetBuffer(), encData.Length()); 
				if (methodInData) encData[3] = (BYTE)method; 
				CopyMemory(encData.GetBuffer() + prefixLen, data.GetBuffer(), data.Length()); 
				CopyMemory(encData.GetBuffer() + prefixLen + data.Length(), bPwd.GetBuffer(), bPwd.Length()); 
				return encData; 
			}
			else if (method == _KEY_ENCRYPT_METHOD_ENC_RSA)
			{
				HCRYPTPROV hCryptProv; 
				HCRYPTKEY hKey; 
				//
				DeriveKeyWithPass(pwd, hCryptProv, hKey); 
				//
				DWORD dwCount = data.Length(); 
				Blob encrypted;
				int size = ENCRYPT_BLOCK_SIZE; 
				while (size < data.Length()) size += ENCRYPT_BLOCK_SIZE; 
				size = size + 4*ENCRYPT_BLOCK_SIZE; 
				encrypted.Allocate(size); 
				ZeroMemory(encrypted.GetBuffer(), size); 
				CopyMemory(encrypted.GetBuffer(), data.GetBuffer(), data.Length()); 
				//
				if(!CryptEncrypt(
					hKey, 
					0, 
					TRUE, 
					0, 
					encrypted.GetBuffer(), 
					&dwCount, 
					size))
				{
					HRESULT rc = HRESULT_FROM_WIN32(GetLastError()); 
					throw MethodError(rc); 
				}
				//
				CleanUpHKey(hCryptProv, hKey); 
				//
				Blob result;
				result.Allocate(prefixLen + dwCount); 
				ZeroMemory(result.GetBuffer(), result.Length()); 
				CopyMemory(result.GetBuffer() + prefixLen, encrypted.GetBuffer(), dwCount); 
				if (methodInData)
				{
					result[3] = (BYTE)method; 
				}
				return result; 
			}
			else
			{
				throw MethodError(FormatStr(L"Unknown encrypt method: %d", (int)method )); 
			}
		}
		_Catch() 
	}

	Blob EncryptWithPass(Blob data, const string& pwd)  
	{
		try
		{
#			ifdef _KEY_ENCRYPT_METHOD
			{
				return MultiEncryptWithPass(data, pwd, _KEY_ENCRYPT_METHOD); 
			}
#			else
			{
				return MultiEncryptWithPass(data, pwd, _KEY_ENCRYPT_METHOD_ENC_RSA, false); 
			}
#			endif
		}
		_Catch() 
	}

	Blob MultiDecryptWithPass(Blob data, const string& pwd, int method_=-1, bool methodInData=true) const 
	{
		try
		{
			bool throwOnError = true; 
			//
			BYTE method = (BYTE)method_; 
			int prefixLen = 4; 
			//
			if (methodInData)
			{
				if (!(data[0] == 0 && data[1] == 0 && data[2] == 0)) 
					throw MethodError(L"�������� ������ ������ ��� �����������"); 
				//
				method = data[3]; 
				//
				prefixLen = 4; 
				//
				if (method_ > 0 && (method_ != method)) throw MethodError(L"��������� ���� �����"); 
			}
			else
			{
				prefixLen = 0; 
			}
			//
			if (method == _KEY_ENCRYPT_METHOD_DUMMY)
			{
				string pwdNonMatch = L"��������� ������ (MultiDecrypt, method: 1)"; 
				//
				if (pwd.GetLength() <= 0) throw MethodError(pwdNonMatch + L" (empty)"); 
				//
				Blob bPwd;
				bPwd.Allocate(pwd.GetLength() * sizeof(wchar_t)); 
				CopyMemory(bPwd.GetBuffer(), (const BYTE*)pwd.GetString(), bPwd.Length()); 
				//
				int L = data.Length() - prefixLen - bPwd.Length(); 
				if (L < 0) throw MethodError(pwdNonMatch); 
				//
				Blob decrypted;
				decrypted.Allocate(L);
				CopyMemory(decrypted.GetBuffer(), data.GetBuffer() + prefixLen, L); 
				//
				for (int j = 0; j < bPwd.Length(); j++) 
				{
					BYTE s1 = data.GetBuffer()[prefixLen + L + j];
					BYTE s2 = bPwd.GetBuffer()[j];
					//
					if (s1 != s2) throw MethodError(pwdNonMatch + L" (b)"); 
				}
				//
				return decrypted; 
			}
			else if (method == _KEY_ENCRYPT_METHOD_ENC_RSA)
			{
				HCRYPTPROV hCryptProv; 
				HCRYPTKEY hKey; 
				//
				DeriveKeyWithPass(pwd, hCryptProv, hKey); 
				//
#				ifdef _DEBUG
				{
					string msg = FormatStr(L"hCryptProv=%d, hKey=%d", 
						(int)hCryptProv, (int)hKey 
						);
					//OutputDebugStringW(msg + L"\n"); 
				}
#				endif
				//
				DWORD size = data.Length() + 128; 
				Blob decrypted;
				decrypted.Allocate(size); 
				ZeroMemory(decrypted.GetBuffer(), decrypted.Length()); 
				CopyMemory(decrypted.GetBuffer(), data.GetBuffer(), data.Length()); 
				//
				DWORD dwCount = data.Length() - prefixLen; // + 128; 
				//
				//DWORD dwEffectiveKeyLen = 40; 
				//if ( ! CryptSetKeyParam(hKey, KP_EFFECTIVE_KEYLEN, (BYTE *)&dwEffectiveKeyLen, 0) ) 
				//{
				//	DWORD dwErr = GetLastError();
				//	HRESULT rc = HRESULT_FROM_WIN32(rc);
				//	throw MethodError(rc);
				//}
				//
				if(!CryptDecrypt(
					hKey, 
					0, 
					TRUE, 
					0, 
					decrypted.GetBuffer() + prefixLen, 
					&dwCount))
				{
					DWORD dwErr = GetLastError(); 
					HRESULT rc = HRESULT_FROM_WIN32(dwErr);
					//
#					ifdef _DEBUG
					{
						string msg = FormatStr(L"Problem in CryptDecrypt: %d", dwErr ); 
						//OutputDebugStringW(msg + L"\n"); 
					}
#					endif
					//
					if ((dwErr & 0xffff) == 5)
					{
						m_Password = L"require"; 
						//
						if (throwOnError)
						{
							try
							{
								RemoveSavedPasswordByPkh(); 
							}
							catch(...)
							{
#								ifdef _DEBUG
								throw;
#								endif
							}
							//
							throw MethodError(L"������ �������� ������ �� ����"); 
						}
						else
						{
							return Blob(); 
						}
					}
					//
					if (throwOnError)
					{
						throw MethodError(rc); 
					}
					else
					{
						return Blob(); 
					}
				}
				//
#				ifdef _DEBUG
				{
					string msg = FormatStr(L"dwCount=%d", (int)dwCount ); 
					//OutputDebugStringW(msg + L"\n"); 
				}
#				endif
				//
				CleanUpHKey(hCryptProv, hKey); 
				//
				Blob result;
				result.Allocate(dwCount); 
				CopyMemory(result.GetBuffer(), decrypted.GetBuffer() + prefixLen, dwCount); 
				return result; 
			}
			else
			{
				throw MethodError(FormatStr(L"Unknown decrypt method: %d", (int)method )); 
			}
		}
		_Catch() 
	}

	Blob DecryptWithPass(Blob data, const string& pwd, bool throwOnError) const 
	{
		try
		{
			if (data.Length() <= 0x20) return data; // we encrypt only keys here, and original key size == 0x20 
			//
			if (
				((BYTE)data[0]) == 0 && 
				((BYTE)data[1]) == 0 && 
				((BYTE)data[2]) == 0 
				)
			{
				return MultiDecryptWithPass(data, pwd); 
			}
			//
			return MultiDecryptWithPass(data, pwd, _KEY_ENCRYPT_METHOD_ENC_RSA, false); 
		}
		_Catch() 
	}

	inline static CString GetRegRoot() 
	{
		try
		{
			CString s = _S("SOFTWARE\\") + _S(__REGISTRY_NAME) + _T("\\") + _S(_CABINET_NAME); 
			return s;
		}
		_Catch()
	}

	inline string GetOption(const string& name, HKEY root1=HKEY_LOCAL_MACHINE) const 
	{
		try
		{
			string o_Registry;
			//
			// Registry
			//
			try
			{
				CString regPath = GetRegRoot() + _T("\\Settings"); 
				//
				HRESULT rc = S_OK;
				o_Registry = Machine::GetRegStringValue(root1,regPath,_S(name),false,&rc); 
			}
			catch(...)
			{
				o_Registry = L"";
			}
			//
			return o_Registry; 
		}
		_Catch()
	}

	inline void SetOption(const string& name, const string& v, HKEY root1=HKEY_LOCAL_MACHINE) const 
	{
		try
		{
			// Registry
			//
			try
			{
				Machine::MountCabinetSettingsKey(root1); 
				//
				CString regPath = GetRegRoot() + _T("\\Settings"); 
				//
				HRESULT rc = S_OK;
				Machine::SetRegStringValue(root1,regPath,_S(name),_S(v),false,&rc); 
			}
			catch(...)
			{
			}
		}
		_Catch()
	}

#	ifndef _DEFAULT_PWD_RETR
#	define _DEFAULT_PWD_RETR 5 
#	endif

	inline int GetPwdRetr() const 
	{
		try
		{
			try
			{
				string rStr = GetOption(L"passwd-r"); 
				if (rStr.GetLength() == 0) return _DEFAULT_PWD_RETR; 
				//
				int r = _wtoi(rStr); 
				return r; 
			}
			catch(...)
			{
				return _DEFAULT_PWD_RETR; 
			}
		}
		_Catch()
	}

#ifndef _OPT_KEY_CNT_PWD
#define _OPT_KEY_CNT_PWD (L"key-cnt-pwd")
#endif

	inline string GetPasswordByPkh()
	{
		try
		{
			Blob client_pkh = GetPKH(); 
			string client_pkh64 = __ToBase64(client_pkh); 
			//
			string option_machine = GetOption(_OPT_KEY_CNT_PWD, HKEY_LOCAL_MACHINE); 
			string option_user = GetOption(_OPT_KEY_CNT_PWD, HKEY_CURRENT_USER); 
			//
			string option = option_machine; 
			if (option_user.GetLength() > 0)
			{
				if (option.GetLength() > 0) option = option + L", "; 
				option = option + option_user; 
			}
			//
			string delim = L","; 
			//
			while (option.GetLength() > 0)
			{
				int p1 = option.Find(delim); 
				//
				string item; 
				if (p1 != -1) 
				{
					item = option.Left(p1); 
					option = option.Right(option.GetLength()-p1-1);  
				}
				else 
				{
					item = option; 
					option = L""; 
				}
				//
				int j = item.Find(L":"); 
				if (j != -1)
				{
					string pkh64_ = item.Left(j); pkh64_.Trim(); 
					string pwd = item.Right(item.GetLength()-j-1); pwd.Trim(); 
					// 
					string pkh64 = __ToBase64(FromBase64String(pkh64_)); 
					//
					if (pkh64 == client_pkh64) return pwd; 
				}
				//
				p1 = option.Find(delim); 
			}
			//
			return L""; 
		}
		_Catch() 
	}

	inline void SetPasswordByPkh(const string& pwd_s) const 
	{
		try
		{
			Blob client_pkh = GetPKH(); 
			string client_pkh64 = __ToBase64(client_pkh); 
			//
			string option = GetOption(_OPT_KEY_CNT_PWD, HKEY_CURRENT_USER); 
			//
			bool f = false;
			//
			string delim = L","; 
			//
			string o2 = L"";
			//
			while (option.GetLength() > 0) 
			{
				int p1 = option.Find(delim); 
				//
				string item; 
				if (p1 != -1) 
				{
					item = option.Left(p1); 
					option = option.Right(option.GetLength()-p1-1);  
				}
				else 
				{
					item = option; 
					option = L""; 
				}
				//
				int j = item.Find(L":"); 
				if (j != -1)
				{
					string pkh64_ = item.Left(j); pkh64_.Trim(); 
					string pwd = item.Right(item.GetLength()-j-1); pwd.Trim(); 
					// 
					string pkh64 = __ToBase64(FromBase64String(pkh64_)); 
					//
					if (pkh64 == client_pkh64) 
					{
						f = true; 
					}
					else
					{
						if (o2.GetLength() > 0) o2 = o2 + L", "; 
						//
						o2 = o2 + pkh64 + L":" + pwd; 
					}
				}
				//
				p1 = option.Find(delim); 
			}
			//
			if (o2.GetLength() > 0) o2 = o2 + L", "; 
			//
			o2 = o2 + client_pkh64 + L":" + pwd_s; 
			//
			SetOption(_OPT_KEY_CNT_PWD, o2, HKEY_CURRENT_USER); 
		}
		_Catch() 
	}

	inline void RemoveSavedPasswordByPkh() const 
	{
		try
		{
			Blob client_pkh = GetPKH(); 
			string client_pkh64 = __ToBase64(client_pkh); 
			//
			string option = GetOption(_OPT_KEY_CNT_PWD, HKEY_CURRENT_USER); 
			//
			//bool f = false;
			//
			string delim = L","; 
			//
			string o2 = L"";
			//
			while (option.GetLength() > 0) 
			{
				int p1 = option.Find(delim); 
				//
				string item; 
				if (p1 != -1) 
				{
					item = option.Left(p1); 
					option = option.Right(option.GetLength()-p1-1);  
				}
				else 
				{
					item = option; 
					option = L""; 
				}
				//
				int j = item.Find(L":"); 
				if (j != -1)
				{
					string pkh64_ = item.Left(j); pkh64_.Trim(); 
					string pwd = item.Right(item.GetLength()-j-1); pwd.Trim(); 
					// 
					string pkh64 = __ToBase64(FromBase64String(pkh64_)); 
					//
					if (pkh64 == client_pkh64) 
					{
					}
					else
					{
						if (o2.GetLength() > 0) o2 = o2 + L", "; 
						//
						o2 = o2 + pkh64 + L":" + pwd; 
					}
				}
				//
				p1 = option.Find(delim); 
			}
			//
			SetOption(_OPT_KEY_CNT_PWD, o2, HKEY_CURRENT_USER); 
		}
		_Catch() 
	}

	inline void AnswerToCanceledPass() const 
	{
		throw MethodError(L"���� ������ �������"); 
	}

	inline string FindContainerPassword(int j) const 
	{
		try
		{
			bool rememberAnswer = false; 
			//
			string r = L""; // (!) PasswordDialog::GetKeyContainerPassword(GetKeyLabel(), j, &rememberAnswer); 
			//
			if (r == L"__CANCELED__") return r; 
			//
			if (rememberAnswer)
			{
				try
				{
					SetPasswordByPkh(r); 
				}
				catch(...)
				{
#					ifdef _DEBUG
					{
						throw;
					}
#					endif
				}
			}
			//
			return r; 
		}
		_Catch() 
	}

	inline void SetPrvKey(bool require=false) const 
	{
		try
		{
			// TODO !!!
//			if (xPtr.Length() > 0) return; 
//			//
//			Blob KPrivData; 
//			//
//			int pwdRetr = GetPwdRetr(); 
//			//
//			bool done = false; 
//			int j = 0; 
//			while (!done)
//			{
//				if (m_Password == L"require") 
//				{
//					string r = FindContainerPassword(j); 
//					//
//					if (r == L"__CANCELED__") 
//					{
//						AnswerToCanceledPass();
//						return; 
//					}
//					//
//					m_Password = r; 
//					//
//					if (m_Password.GetLength() == 0) 
//					{
//						m_Password = L"require"; 
//						//
//						if (require)
//						{
//							throw MethodError(L"�� ������ ������ �� ����"); 
//						}
//						//
//						return; 
//					}
//				}
//				//
//				// Private Key 
//				//
//#				ifdef _DEBUG
//				{
//					//OutputDebugStringW(L"!{SetPrivKey"); 
//				}
//#				endif 
//				KPrivData = DecryptWithPass(KPrivData1, _W(m_Password), j >= pwdRetr); 
//#				ifdef _DEBUG
//				{
//					string msg1 = _W(FormatStr(L"KPrivData(%d)", (int)KPrivData.Length() )) + 
//						L" / " + _W(m_Password) + L" ";
//					string msg2 = _W(FormatStr(L"\nKPrivData1(%d)", (int)KPrivData1.Length() )); 
//					//OutputDebugStringW(msg2 + L" !}\n"); 
//				}
//#				endif 
//				//
//				if (KPrivData.Length() > 0) done = true; 
//				//
//				++j;
//				if (j > pwdRetr)
//				{
//					throw new MethodError(L"�� ������ ������ �� ���� (R)"); 
//				}
//			}
//			//
//			// TODO !!!
//			//OPAQUE_PRIV_KEY privKey(KPrivData,KMacData);
//			//xPtr = privKey.Data;
		}
		_Catch() 
	}

	void SetXmlInfo(XmlElement value, bool setPrivKeyAfter=false) 
	{
		try
		{
			Clear();
			//
			PKCS11_Manager::Lock lock;
			//
			// ��������� ���� �� XML-�����
			//
			if (m_keyContainerPath.GetLength() == 0)
			{
				string m_keyContainerPath = GetTempContainerPath();
			}
			string keyContPath = string(m_keyContainerPath);
			//
			KeyInfo_E = (XmlElement)value; // .Clone();
			//
			string paramAttr = KeyInfo_E.GetAttribute(L"PubKeyParameters");
			if (paramAttr.GetLength() <= 2)
			{
				SetPubKeyParameters(_wtoi(KeyInfo_E.GetAttribute(L"PubKeyParameters")));
			}
			else SetPubKeyParameters(12);
			//
			string sBoxAttr = KeyInfo_E.GetAttribute(L"SBox");
			if (sBoxAttr.GetLength() <= 2)
			{
				SetSBox(_wtoi(KeyInfo_E.GetAttribute(L"SBox")));
			}
			else SetSBox(22); 
			//
			// Public Key 
			//
			XmlElement PK_E = (XmlElement)KeyInfo_E.SelectSingleNode(L"PublicKey");
			string yData64 = PK_E.InnerText();
			Blob yData = Util::FromBase64String(yData64);
			SetPublicKey(yData);
#			ifdef _DEBUG
			{
				Blob _pk = GetPublicKey();
				TRACE_LOG(_T("PublicKey: ")+Util::BlobToHex(_pk)); 
			}
#			endif
			//Runtime.Echo("PubKeyHash: "+Convert.ToBase64String(PubKeyHash)+" : "+Util.BlobToHex(PubKeyHash));
			//
			XmlElement PSE_E = (XmlElement)KeyInfo_E.SelectSingleNode(L"PSE"); 
			//
			// Password 
			//
			string p0; 
			if (PSE_E.HasAttribute(L"Password")) p0 = PSE_E.GetAttribute(L"Password");
			else p0 = L""; 
			// 
			if (p0 == L"require")
			{
				if (m_Password.GetLength() == 0) 
				{
					string pswByPkh = GetPasswordByPkh(); 
					if (pswByPkh.GetLength() > 0) m_Password = pswByPkh; 
				}
			}
			else 
			{
				m_Password = p0; 
			}
			//
			XmlElement KPriv_E = (XmlElement)KeyInfo_E.SelectSingleNode(L"PrivateKey/EncryptedKey");
			string KPrivData64 = KPriv_E.InnerText();
			pk = Util::FromBase64String(KPrivData64);
			//
			//XmlElement KMac_E = (XmlElement)KeyInfo_E.SelectSingleNode(L"PrivateKey/Mac");
			//string KMacData64 = KMac_E.InnerText();
			//KMacData = Util::FromBase64String(KMacData64); 
			//
			if (!setPrivKeyAfter)
			{
				SetPrvKey(); 
			}
			//
			// Files
			//
			XmlNodeList L = KeyInfo_E.SelectNodes(L"PSE/File");
			for (int file_i = 0; file_i < L.Count(); ++file_i)
			{
				XmlElement File_E = (XmlElement)L[file_i];
				//
				string file = File_E.GetAttribute(L"Name");
				string data64 = File_E.InnerText(); 
				Blob data = Util::FromBase64String(data64); 
				//
				string path = keyContPath + L"\\" + file;
				//FileStream writer = File.Open(path,FileMode.Create,FileAccess.Write);
				//writer.Write(data,0,(int)data.Length());
				//writer.Close();
				//
				// TODO: ???
				//
				//////File f;
				//////f.Open(CString(path));
				//////f.Replace((char*)data.GetBuffer(),data.Length());
				//////f.Close();
			}
			//
			// ������������� ���� � PSE � ������ ��������� 
			//
			SetContainerPath(CString(keyContPath)); 
		}
		_Catch()
	}

	string eTokenID;
	int key_i; 
	int key_mode; 

	//void Load_eTokenKey() 
	//{
	//	try
	//	{
	//		LoadETokenKey_2(); 
	//	}
	//	_Catch() 
	//}

	void LoadETokenKey(const string& eTokenID, int key_i_)
	{
		try
		{
			LoadETokenKey_2(eTokenID, key_i_); 
		}
		_Catch()
	}

	//void LoadETokenKey(int eTokenSlotId_, int key_i_, int key_mode_)
	//{
	//	try
	//	{
	//		key_mode = key_mode_;
	//		//
	//		if (key_mode == 1)
	//		{
	//			LoadETokenKey_1(eTokenSlotId_, key_i_); 
	//		}
	//		else if (key_mode == 2)
	//		{
	//			LoadETokenKey_2(eTokenSlotId_, key_i_); 
	//		}
	//		else 
	//		{
	//			string errMsg = FormatStr(L"��������� �������� KeyMode=%d", (int)key_mode_ ); 
	//			throw MethodError(errMsg); 
	//		}
	//	}
	//	_Catch() 
	//}

	void LoadETokenKey_2(const string& eTokenID_, int key_i_)
	{
		try
		{
			//AsnObject privateMetaO = eToken.ReadMetaObject(OID__META); 
			//AsnObject keyO = eToken.FindKeyObject(key_i); 
			////
			////AsnObject MetaO = PKCS11_Manager::Acquire()
			////	.MetaObject_E_2(eTokenSlotId_, _PRIVATE_META); 
			//////
			////AsnObject& keyO = PKCS11_Manager::Acquire().FindKeyObject(MetaO, key_i_); 
			//////
			//AsnObject& keyDataO = keyO[1]; 
			//
			eTokenID = eTokenID_; 
			key_i = key_i_; 
			//
			EToken& eToken = EToken::OpenEToken(eTokenID); 
			XmlElement key_E = eToken.GetPrivateKey(key_i); 
			XmlElement keyEnv_E = key_E.SelectSingleNode(
				_W(L"asn:object[@oid='") + OID_KEY_ENV + L"']"); 
			//
			AsnObject keyDataO = PKCS11_Manager_().XmlElementToAsnDict(keyEnv_E); 
			//
			Blob keyDataEnv = keyDataO.ToBlob(); 
			//
			// ----
			// Activating 
			//
			ParseAndActivateETokenKey(keyDataEnv); 
		}
		_Catch() 
	}

	void LoadETokenKey_1(int eTokenSlotId_, int key_i_)
	{
		try
		{
			//%//
			//const int buflen = 16 * 1024; 
			////
			//eTokenSlotId = eTokenSlotId_;
			//key_i = key_i_; 
			////
			//PKCS11_Manager::Lock lock; 
			////
			//string keyContainerPath = PKCS11_Manager_()
			//	.EToken_GetKeyContainerPath_U(eTokenSlotId, key_i); 
			////
			//CStringA keyContainerPathA = PKCS11_Manager::ETokenPath(
			//	eTokenSlotId, keyContainerPath); 
			////
			//// ----
			//// Key file 
			////
			//string keyPath = PKCS11_Manager_()
			//	.EToken_GetKeyPath(eTokenSlotId, key_i); 
			//CStringA keyPathA = PKCS11_Manager::ETokenPath(eTokenSlotId, keyPath); 
			////
			//Blob keyDataEnv;
			//keyDataEnv.Expand(buflen);
			//int r1 = CADB_read_file(keyPathA.GetBuffer(), (char*)keyDataEnv.GetBuffer(), buflen); 
			//if (r1 <= -1)
			//{
			//	int e = ERR_get_last_error();
			//	string errMsg = FormatStr(L"������ CCOM: %d", (int)e );
			//	throw MethodError(errMsg); 
			//}
			//keyDataEnv.SetSize(r1); 
			////
			//// ----
			//// Activating 
			////
			//ParseAndActivateETokenKey(keyDataEnv); 
		}
		_Catch()
	}

	void ParseAndActivateETokenKey(Blob keyDataEnv) 
	{
		try
		{
			// ----
			// Properties of the key 
			//
			AsnObject keyDataEnvO(keyDataEnv); 
			AsnObject& keyData = keyDataEnvO[1]; 
			AsnObject& keyAttrs = keyData[0];
			AsnObject& keyValues = keyData[1];
			//
			string keyTime_s = ((AsnObject&)keyAttrs[0]).m_text; 
			int pkParameters = ((AsnObject&)keyAttrs[1]).m_Integer; 
			int sBox = ((AsnObject&)keyAttrs[2]).m_Integer; 
			AsnObject& oPKH = keyAttrs[3];
			Blob pkh = oPKH.Data();
			string pkh64 = __ToBase64(pkh); 
			string pass = ((AsnObject&)keyAttrs[4]).m_text; 
			//
			AsnObject& oEK = keyValues[0];
			Blob EK = oEK.Data();
			//
			AsnObject& oMac = keyValues[1];
			Blob Mac = oMac.Data();
			//
			AsnObject& oPK = keyValues[2];
			Blob PK = oPK.Data(); 
			//
			//%%//pass = PKCS11_Manager_().GetETokenPassword(eTokenSlotId, key_i, 1); 
			SetProperties(pkParameters, sBox, PK, EK, Mac, pass); 
			//
			// ----
			// Activating container 
			//
			EToken& eToken = EToken::OpenEToken(eTokenID); 
			string keyContainerPath = EToken::EToken_GetKeyContainerPath_U(key_i); 
			//
			CStringA keyContainerPathA = eToken.ETokenPath(keyContainerPath); 
			//
			SetContainerPath(_S(keyContainerPathA)); 
		}
		_Catch() 
	}

	void SetProperties(
		int pkParameters, 
		int sBox, 
		Blob yData, 
		Blob KPrivData, 
		Blob KMacData, 
		const string& passw=L"require" 
		)
	{
		try
		{
			SetPubKeyParameters(pkParameters); 
			SetSBox(sBox);
			//
			// Public Key 
			//
			SetPublicKey(yData);
#			ifdef _DEBUG
			{
				Blob _pk = GetPublicKey();
				TRACE_LOG(_T("PublicKey: ")+Util::BlobToHex(_pk));
			}
#			endif
			//
			// Private Key 
			//
			// TODO !!!
			//OPAQUE_PRIV_KEY privKey(KPrivData,KMacData); 
			//xPtr = privKey.Data;
			//
			// Password
			//
			m_Password = passw;
			//
			//if (m_Password == L"require") 
			//{
			//	m_Password = PasswordDialog::GetKeyContainerPassword(); 
			//}
		}
		_Catch()
	}

	void SetFile(const string& name, Blob data) 
	{
		try
		{
		}
		_Catch() 
	}

public:
	int GetPubKeyParameters() const 
	{
		if (m_pubKeyParameters == -1) 
			m_pubKeyParameters = ECGOST_PARAMS_CP_A;
		//
		if (m_pubKeyParameters == -1) 
			throw MethodError(L"��������� ��������� ����� �� �������");
		//
		return m_pubKeyParameters;
	}
	
	void SetPubKeyParameters(int value)
	{
		if (m_pubKeyParameters != -1) 
			throw MethodError(L"��������� ��������� ����� ��� �����������");
		//
		m_pubKeyParameters = value;
	}

	static const int DefaultSBox = GOSTH_SBOX_CP;

	int GetSBox() const 
	{
		if (m_SBox == -1) 
			m_SBox = DefaultSBox;
		//
		if (m_SBox == -1) 
			throw MethodError(L"��������� ��������� ����� �� �������"); 
		//
		return m_SBox;
	}

	void SetSBox(int value)
	{
		if (m_SBox != -1) 
			throw MethodError(L"��������� ��������� ����� ��� �����������"); 
		//
		m_SBox = value;
	}

	bool IsStandalone()
	{
		return m_standalone;
	}

	CString GetContainerPath()
	{
		if (m_keyContainerPath.GetLength() == 0) 
			throw MethodError(L"���� � ��������� �������� �� �����");
		//
		return m_keyContainerPath;
	}

	void SetContainerPath(const CString& value)
	{
		try
		{
			EnterETokenContext(); 
			//
			//if (m_keyContainerPath.GetLength() > 0) 
			//	throw MethodError(L"���� ��� ���������� � �� ����� ���� �������");
			//
			// ��������� �������� 
			//
			m_keyContainerPath = value;
			//
			CStringA pathA(m_keyContainerPath);
			CStringA pA(m_Password);
			//
			// ��������� ���� 
			//
			CCOMLib::Init(); 
			//
			pse = CCOM_PSENew();
			if (!pse)
			{
				throw MethodError(L"������ ������ ��������� ���������� (0)");
			}
			//
			if(!CCOM_PSESetRandCallback(pse, CCOMLib::getch_cb, NULL)) 
			{
				throw CComException();
			}
			if(!CCOM_PSESetPath(pse, pathA.GetBuffer())) 
			{
				throw CComException();
			}
			if(!CCOM_PSESetPassword(pse, pA.GetBuffer(), pA.GetLength())) 
			{
				throw CComException();
			}
			if(!CCOM_PSERead(pse)) 
			{
				throw CComException();
			}
			//
	//		pseCtx = PSE_CTX_new();
	//		//
	//		CStringA pathA(m_keyContainerPath);
	//		int r1 = PSE_CTX_set_path(pseCtx,pathA.GetBuffer(),pathA.GetLength());
	//		if (r1 == 0) throw CComException();
	//		//
	//		//if (m_Password.GetLength() > 0)
	//		//{
	//		//	CStringA passwordA(m_Password); 
	//		//	//
	//		//	int r2 = PSE_CTX_set_passwd(pseCtx, passwordA.GetBuffer(), passwordA.GetLength());
	//		//	if (r2 == 0) throw CComException();
	//		//}			
	//		int r3 = PSE_CTX_read(pseCtx);
	//		if (r3 == 0) throw CComException(); 
	//		//
	//		PKCS11_Manager_().ReleaseContext(); 
		}
		_Catch() 
	}

	CString GetPassword()
	{
		return m_Password;
	}

	void SetPassword(const CString& value) 
	{
		try
		{
			m_Password = value; 
			//
			if (m_Password.GetLength() > 0) 
			{
				SetPrvKey(); 
			}
		}
		_Catch() 
	}

	CString GetPIN()
	{
		return m_PIN;
	}

	void SetPIN(const CString& value)
	{
		m_PIN = value;
	}

	Blob GetPublicKey() const
	{
		return y;
	}

	void SetPublicKey(Blob value)
	{
		y.Allocate(value.GetSize());
		for (int j = 0; j < value.GetSize(); ++j) y[j] = value[j];
		//
		//// m_RequestIsSigned = false;
	}



	// ===================================================================================
	// ��������� ������ ����� � ��������� ����������

	void CreateIn(const CString& keyContainerPath
		, const CString& containerPW
		, const CString& pin=_T("") 
		) 
	{
		try
		{
			m_keyContainerPath = keyContainerPath; 
			m_Password = containerPW; 
			//
			// InitKeyTime();
			//
			// ----
			// ������ ��������� � ���� 
			//
			GeneratePSE(containerPW);
			//
			CStringA pathA(m_keyContainerPath);
			CStringA privPathA(_A(m_keyContainerPath) + "\\k.bin"); 
			CStringA pubPathA(_A(m_keyContainerPath) + "\\p.bin");
			CStringA pA(containerPW); 
			//
			//if (_CLOSE_PSE_AFTER_GEN)
			//{
			//	if(!CCOM_PSESetPath(pse, pathA.GetBuffer())) 
			//	{
			//		throw CComException();
			//	}
			//	if(!CCOM_PSESetPassword(pse, pA.GetBuffer(), pA.GetLength())) 
			//	{
			//		throw CComException();
			//	}
			//	if(!CCOM_PSERead(pse)) 
			//	{
			//		throw CComException(); 
			//	}
			//}
			//
			// fprintf(stdout, "Key pair generation...\n"); 
			//
			int alg = CCOM_GOSTR3410_2001;
			int params = ECGOST_PARAMS_CP_XA; // ECGOST_PARAMS_CP_XA; 
			//
			pse = CCOM_PSENew();
			if (!pse)
			{
				throw MethodError(L"������ �������� ����� (0)");
			}
			if(!CCOM_PSESetPath(pse, pathA.GetBuffer())) 
			{
				throw CComException();
			}
			if(!CCOM_PSESetPassword(pse, pA.GetBuffer(), pA.GetLength())) 
			{
				throw CComException();
			}
			if(!CCOM_PSERead(pse)) 
			{
				throw CComException(); 
			}
			//
			keypair = CCOM_KeyPairNew();
			if(!keypair) 
			{
				throw CComException();
			}
			if(!CCOM_KeyPairSetPSE(keypair, pse)) 
			{
				throw CComException();
			}
			if(!CCOM_KeyPairGenerate(keypair, alg, params)) 
			{
				throw CComException();
			}
		
			// fprintf(stdout, "Private key writing: %s\n", privpath); 
			//
			priv = CCOM_KeyPairGetPrivateKey(keypair);
			if(!priv) 
			{
				throw CComException();
			}
			if(!CCOM_PrivateKeySetPSE(priv, pse)) 
			{
				throw CComException();
			}
			if(!CCOM_PrivateKeySetPath(priv, privPathA.GetBuffer())) 
			{
				throw CComException();
			}
			if(!CCOM_PrivateKeySetPassword(priv, pA.GetBuffer(), pA.GetLength())) 
			{
				throw CComException();
			}
			if(!CCOM_PrivateKeyWrite(priv)) 
			{
				throw CComException();
			}

			// fprintf(stdout, "Public key writing: %s\n", pubpath); 
			//
			pub = CCOM_KeyPairGetPublicKey(keypair);
			if(!pub) 
			{
				throw CComException();
			}
			if(!CCOM_PublicKeySetPath(pub, pubPathA.GetBuffer())) 
			{
				throw CComException();
			}
			if(!CCOM_PublicKeyWrite(pub)) 
			{
				throw CComException();
			}
			//
			int yLen = Machine::GetFileSize(_S(pubPathA)); 
			//
			// a - ASN, r - raw, b - bits reversed, ... 
			//
			::::File f;
			f.Open(_S(pubPathA)); 
			Blob y0 = f.ReadAll();
			f.Close();
			//
			AsnObject y0_o(y0);
			OutputDebugStringW(y0_o.Dump());
			AsnObject& y0_1 = y0_o[1];
			Blob y1 = y0_1.Data();
			int n1 = y1.GetSize();
			Blob y2; 
			y2.Allocate(64+2);
			for (int j = 0; j < 64; j++) y2[j] = y1[63-j]; 
			y2[64] = y1[64]; y2[65] = y1[65]; 
			Blob y3; 
			y3.Allocate(64+2);
			for (int j = 0; j < 32; j++) y3[32+j] = y1[j]; 
			for (int j = 0; j < 32; j++) y3[j] = y1[31+j]; 
			//for (int j = 0; j < 32; ++j) 
			//{
			//	BYTE y1 = y3[j]; y3[j] = y3[63-j]; y3[63-j] = y1;
			//}
			y3[64] = y1[64]; y3[65] = y1[65]; 
			//
			//for (int j = 0; j < 32; j++)
			//{
			//	BYTE s1 = y1[j]; y1[j] = y1[32+j]; y1[32+j] = s1;
			//}
			//for (int j = 0; j < 32; j++)
			//{
			//	BYTE s1 = y1[j]; y1[j] = y1[63-j]; y1[63-j] = s1;
			//}
			//for (int j = 0; j < 16; j++)
			//{
			//	BYTE s1 = y1[j]; y1[j] = y1[31-j]; y1[31-j] = s1;
			//	     s1 = y1[32+j]; y1[32+j] = y1[63-j]; y1[63-j] = s1;
			//}
			y = y0;
			//
			char buf[265];
			int bufLen = sizeof(buf); 
			if(!CCOM_PublicKeyGetEncoded(pub, buf, &bufLen, CCOM_PUBLIC_KEY_RAW)) // CCOM_PUBLIC_KEY_SPKI 
			{
				throw CComException(); 
			}
			int len = 64; 
			Blob cpPubKey;
			cpPubKey.Allocate(len+2);
			//
			for (int j = 0; j < 32; ++j) 
			{
				cpPubKey[63-j] = buf[1+31-j];
			}
			for (int j = 0; j < 32; ++j) 
			{
				cpPubKey[63-(32+j)] = buf[1+32+31-j]; 
			}
			cpPubKey[len+1] = 0x04;
			cpPubKey[len] = (BYTE)len;
			//
			//y = cpPubKey;

			//
			//::::File f2;
			//f2.Open(privPathA); 
			//pk = f2.ReadAll();
			//f2.Close();
			//
			PSEToXml();



			//
			//
			//
		//priv = CCOM_PrivateKeyNew();
		//if(!priv) throw CComException();
		//if(!CCOM_PrivateKeySetPSE(priv, pse)) throw CComException();

		//if(!CCOM_PrivateKeySetPath(priv, privpath)) throw CComException();
		//if(!CCOM_PrivateKeyReadRaw(priv, alg, params)) throw CComException();

		//if(!CCOM_PrivateKeySetPath(priv, newprivpath)) throw CComException();
		//if(!CCOM_PrivateKeySetPassword(priv, newprivpasswd, newprivpasswd ? (int)strlen(newprivpasswd) : 0)) goto err;
		//if(!CCOM_PrivateKeyWrite(priv)) goto err;
			//
			//
			//
	//////		void* pse = PSE_CTX_get_pse(pseCtx);
	//////		//
	//////		xPtr.Allocate(OPAQUE_PRIV_KEY::SizeOf());
	//////		yLen = ECGOST_PUB_MAXLEN;
	//////		y.Allocate(yLen);
	//////		// ~~~ yPtr.Allocate(ECGOST_PUB_MAXLEN);
	//////		//
	//////		// % 
	//////		BYTE y_[100];
	//////		// % 
	//////		ZeroMemory(&y_,100);		
	//////		//
	//////		// % ::OPAQUE_PRIV_KEY pk;
	//////		// % ZeroMemory(&pk,sizeof(pk));
	//////		//
	//////		///TRACE_LOG(_T("CreateIn: 2"));
	//////		if (ECGOST_generate_key(pse,GetPubKeyParameters(),
	//////			(::OPAQUE_PRIV_KEY*)xPtr.GetBuffer()
	//////			// % &pk
	//////			,y.GetBuffer()
	//////			// % ,y_
	//////			,&yLen,0) == 0) 
	//////		{
	//////			throw CComException();
	//////		}
	//////		//
	//////		/// AsnObject signedRequest = GetSignedRequest();
	//////		//
	//////		PSEToXml();
			//
			// ���������� ��������� ���������� � ����� � ���� ������������ ������� 
			//
			//if (m_standalone || true)
			//{
			//	CStringA path1 = CStringA(m_keyContainerPath) + "d001";
			//	///int r01 = 
			//		CADB_file_exists(path1.GetBuffer());
			//	///TRACE_LOG1(_T("r01=%d"), r01);
			//	//
			//	// ����
			//	//
			//	///Blob keyDataEnv = GetKeyData(); /// !!!
			//}
		}
		_Catch()
	}



	void GeneratePSE(const CString& containerPW)
	{
		try
		{
			CCOMLib::Init();
			//
			pse = CCOM_PSENew();
			if(!pse) 
			{
				throw MethodError(L"������ �������� ��������� ���������� (0)");
			}
			//
			CStringA pathA(m_keyContainerPath);
			CStringA pA(containerPW);
			//
			if(!CCOM_PSESetRandCallback(pse, &CCOMLib::getch_cb, NULL)) 
			{
				throw CComException();
			}
			if(!CCOM_PSEGenerate(pse)) 
			{
				throw CComException();
			}
			if(!CCOM_PSESetPath(pse, pathA.GetBuffer())) 
			{
				throw CComException();
			}
			if(!CCOM_PSESetPassword(pse, pA.GetBuffer(), pA.GetLength())) 
			{
				throw CComException();
			}
			if(!CCOM_PSEWrite(pse)) 
			{
				throw CComException();
			}
			if(pse) CCOM_PSEFree(pse);
			//
//			pseCtx = PSE_CTX_new();
//			//
//			if (! pseCtx) 
//			{
//				throw MethodError(L"������ �������� ��������� ����������");
//			}
//			//
//			// ��������� ������� ��������� ������ ��� ������������� ���
//			//	if (Lib.PSE_CTX_set_rand_callback(pseCtx,new Lib.RAND_CALLBACK(Lib.getch_cb)) != 0) 
//			//		throw new CComException();
//			//
//			if (containerPW == _T("require")) 
//			{
//				bool rememberAnswer = false; 
//				string r = PasswordDialog::GetKeyContainerPassword(L"", 0, &rememberAnswer); 
//				//
//				if (r == L"__CANCELED__") 
//				{
//					throw MethodError(L"�� ������ ������ �� ���� (G)"); 
//				}
//				//
//				if (rememberAnswer)
//				{
//					try
//					{
//						SetPasswordByPkh(r); 
//					}
//					catch(...)
//					{
//#						ifdef _DEBUG
//						{
//							throw;
//						}
//#						endif
//					}
//				}
//				//
//				m_Password = r; 
//			}
//			else
//			{
//				m_Password = containerPW; 
//			}
//			//
//			// ��������� ������
//			if (m_Password.GetLength() > 0)
//			{
//				CStringA passwordA(m_Password);
//				if (PSE_CTX_set_passwd(pseCtx,passwordA.GetBuffer(),passwordA.GetLength()) == 0)
//					throw CComException();
//			}
//			//
//			// ��������� �������� ����
//			// m_keyContainerPath = _T("etoken:/KEYA/"); // TODO: eToken
//			CStringA keyContainerPathA(m_keyContainerPath);
//			if (PSE_CTX_set_path(pseCtx,keyContainerPathA.GetBuffer(),keyContainerPathA.GetLength()) == 0)
//				throw CComException();
//			//if (PSE_CTX_set_path(pseCtx,keyContainerPathA.GetBuffer(),keyContainerPathA.GetLength()) == 0)
//			//	throw CComException();
//			//
//			//// ��������� ������ eToken
//			//if (StartsWith(m_keyContainerPath,_T("etoken:/")))
//			//{
//			//	CStringA pinA = "1234567890"; // (GetPIN());
//			//	//
//			//	if (PSE_CTX_set_etoken(
//			//		pseCtx, 
//			//		pinA.GetBuffer(), 
//			//		pinA.GetLength(), 
//			//		0L
//			//		) == 0)
//			//	{
//			//		throw CComException();
//			//	}
//			//	else
//			//	{
//			//		TRACE_LOG(_T("����������� � eToken ������ �������!"));
//			//	}
//			//}
//			//
//			// ���������
//			if (PSE_CTX_generate(pseCtx) == 0) 
//				throw CComException();
//				//throw MethodError(_T("������ �������� ��������� ����������"));
//			//
//			// ����������
//			if (PSE_CTX_write(pseCtx) == 0) 
//			{
//				//int r1 = ERR_get_last_error();
//				throw CComException();
//				//throw MethodError(_T("������ �������� ��������� ����������"));
//			}
//			else
//			{
//				TRACE_LOG(_T("������ ���������� ") + m_keyContainerPath + _T(" ������ �������!"));
//			}
		}
		_Catch()
	}

	AsnObject GetKeyDataObject()
	{
		try
		{
			AsnObject a1(0);
			return a1; 
			//
	//		COleDateTime t = GetKeyTime();
	//		string keyTime_s = string(
	//			FormatTime_ymd_HMD(_S("%04d-%02d-%02d"),_S("T%02d:%02d:%02dZ"),t)
	//			);
	//		//SYSTEMTIME st;
	//		//t.GetAsSystemTime(st);
	//		///int N = sizeof(SYSTEMTIME);
	//		//
	//		Blob pk = GetCryptoProPublicKey();
	//		Algorithms::Alg_1_8_2 alg_8_2;
	//		string pkHashStr = alg_8_2.Encode(pk);
	//		Blob PKH = Util::FromBase64String(pkHashStr); 
	//		//
	//		Blob EK = GetPrivateKey().priv();
	//		Blob Mac = GetPrivateKey().mac();
	//		//
	//		// ���������� ������ �������� ����
	//		//
	//		AsnObject keyDataEnv = AsnObject::NewSequence();
	//		keyDataEnv.Add(AsnObject(OID(L"1.2.643.6.2.1.5.4"))); 
	//		//
	//		AsnObject keyData = AsnObject::NewSequence();
	//		//
	//		AsnObject keyAttrs = AsnObject::NewSequence();
	//		keyAttrs.Add(AsnObject(string(keyTime_s)));
	//		keyAttrs.Add(AsnObject((int)GetPubKeyParameters())); 
	//		keyAttrs.Add(AsnObject((int)GetSBox()));
	//		keyAttrs.Add(AsnObject::NewOctetString());
	//		keyAttrs.Add(AsnObject(string(m_Password)));
	//		//
	//		AsnObject& oPKH = keyAttrs[3];
	//		oPKH.Data().Allocate(PKH.Length());
	//		CopyMemory(oPKH.Data().GetBuffer(),PKH.GetBuffer(),PKH.Length()); 
	//		//
	//		AsnObject keyValues = AsnObject::NewSequence();
	//		keyValues.Add(AsnObject::NewOctetString());
	//		keyValues.Add(AsnObject::NewOctetString());
	//		keyValues.Add(AsnObject::NewOctetString());
	//		//
	//		AsnObject& oEK = keyValues[0];
	//		oEK.Data().Allocate(EK.Length());
	//		CopyMemory(oEK.Data().GetBuffer(),EK.GetBuffer(),EK.Length());
	//		//
	//		AsnObject& oMac = keyValues[1];
	//		oMac.Data().Allocate(Mac.Length());
	//		CopyMemory(oMac.Data().GetBuffer(),Mac.GetBuffer(),Mac.Length());
	//		//
	//		AsnObject& oPK = keyValues[2];
	//		oPK.Data().Allocate(y.Length());
	//		CopyMemory(oPK.Data().GetBuffer(),y.GetBuffer(),y.Length());
	//		//
	//		keyData.Add(keyAttrs);
	//		keyData.Add(keyValues);
	//		//
	//		keyDataEnv.Add(keyData);
	//		//
	//		////OutputDebugStringW(L"\nkeyDataEnv:\n" + _W(keyDataEnv.Dump()) + L"\n"); 
	//		keyDataEnv.Update(); 
	//		//
	//		////OutputDebugStringW(L"\nkeyDataEnv:\n" + _W(keyDataEnv.Dump()) + L"\n"); 
	//		return keyDataEnv;
		}
		_Catch()
	}

	void SaveKeyToEToken() 
	{
		try
		{
			SaveKeyToEToken_2(); 
			//
			//if (key_mode == 1)
			//{
			//	SaveKeyToEToken_1(); 
			//}
			//else if (key_mode == 2)
			//{
			//	SaveKeyToEToken_2(); 
			//}
			//else 
			//{
			//	string errMsg = FormatStr(L"��������� �������� KeyMode=%d", (int)key_mode ); 
			//	throw MethodError(errMsg); 
			//}
		}
		_Catch() 
	}

	//void SaveKeyToEToken_1() 
	//{
	//	try
	//	{
	//		CString path = m_keyContainerPath + _T("/fa01");
	//		CStringA pathA(path); 
	//		//
	//		Blob b = GetKeyDataObject().Encoded(); 
	//		//
	//		int r1 = CADB_write_file(pathA.GetBuffer(), (char*)b.GetBuffer(), b.Length()); 
	//		if (r1 <= 0)
	//		{
	//			int e1 = ERR_get_last_error();
	//			string errMsg = FormatStr(L"������ CCOM: %d", (int)e1 );
	//			throw MethodError(errMsg); 
	//		}
	//	}
	//	_Catch() 
	//}

	void SaveKeyToEToken_2() 
	{
		try
		{
			EToken& eToken = EToken::OpenEToken(eTokenID); 
			//
			// int key_i = eToken.GetKeyIndex(GetPKH());	// ��� ������ �� �����, ��� ��� key_i 
			//												// �������� �� ����� ��������� 
			//
			Blob pkh = GetPKH(); 
			string pkh64 = __ToBase64(pkh); 
			//
			XmlElement key_E = eToken.GetFreeKey(key_i); 
			eToken.WriteTextObjectInS(key_E, 2, pkh64); 
			//
			XmlElement privateKey_E = eToken.GetPrivateKey(key_i); 
			XmlDocument doc = privateKey_E.OwnerDocument(); 
			//
			//OutputDebugStringW(privateKey_E.OuterXml()); 
			//
			AsnObject o1 = GetKeyDataObject(); 
			XmlElement new_prvKey_E = PKCS11_Manager_().AsnObjToXmlElement(o1, doc); 
			//
			XmlNodeList L1 = privateKey_E.SelectNodes(L"*"); 
			XmlNode prvKey_E = L1[1]; 
			privateKey_E.ReplaceChild(new_prvKey_E, prvKey_E); 
			//
			////OutputDebugStringW(privateKey_E.OuterXml()); 
			//keyO[1] = o1; 



			//PKCS11_Manager::Lock lock; 
			//PKCS11_Manager& M = PKCS11_Manager::Acquire(); 
			////
			//// Blob b = GetKeyDataObject().Encoded(); 
			//// 
			//AsnObject MetaO = M.MetaObject_E_2(eTokenSlotId, _PRIVATE_META); 
			////
			//AsnObject& keyO = M.FindKeyObject(MetaO, key_i); 
			////
			//keyO = GetKeyDataObject(); 
			//AsnObject o1 = GetKeyDataObject(); 
			//keyO[1] = o1; 
			////
			//OutputDebugStringW(keyO.Dump()); 
			//M.SaveMeta_M(eTokenSlotId, key_mode, _PRIVATE_META, MetaO); 
		}
		_Catch() 
	}

	void PSEToXml()
	{
		try
		{
			Blob pk = GetCryptoProPublicKey();
			Algorithms::Alg_1_8_2 alg_8_2;
			string pkHashStr = alg_8_2.Encode(pk);
			//
			COleDateTime t = GetKeyTime();
			string keyTime_s = string(
				FormatTime_ymd_HMD(_S("%04d-%02d-%02d"),_S("T%02d:%02d:%02dZ"),t)
				);
			//
			// TODO !!!
			Blob K1 = pk; 
			Blob K; 
			K = K1;
#			ifdef _KEY_FOR_CABINET_SERVER
			{
				//K = K1; 
			}
#			else
			{
				//K = EncryptWithPass(K1, _W(m_Password)); 
			}
#			endif
			///Blob K2 = DecryptWithPass(K, _W(m_Password)); 
			//
			string pwdAttr = m_Password.GetLength() > 0 ? L"require" : L""; 
			//
			string xml1 = string(L"<?xml version=\"1.0\" ?>") +
				L"<KeyInfo" +
				L" KeyTime=\"" + keyTime_s + L"\"" +
				L" PubKeyParameters=\"" + FormatStr(L"%d", (int)GetPubKeyParameters() ) + L"\"" + 
				L" SBox=\"" + FormatStr(L"%d", (int)GetSBox() ) + L"\"" +
				L" PubKeyHash=\"" + pkHashStr + L"\"" + 
				L">" + 
				L"<PrivateKey>" +
				L"<EncryptedKey>" + Util::ToBase64String(K) + L"</EncryptedKey>" +
				// TODO !!! 
				// L"<Mac>" + Util::ToBase64String(GetPrivateKey().mac()) + L"</Mac>" +
				L"</PrivateKey>" + 
				L"<PublicKey>" + Util::ToBase64String(y) + L"</PublicKey>" +
				L"<PSE Password=\"" + pwdAttr + L"\">" +
				L"</PSE>" +
				L"</KeyInfo>";
			//
			XmlDocument keyDoc;
			keyDoc.LoadXml(xml1); 
			//
			KeyInfo_E = keyDoc.DocumentElement();
			//
			CString prefix = _T("etoken"); 
			if (!(m_keyContainerPath.Left(prefix.GetLength()) == prefix)) 
			{
				XmlElement PSE_E = (XmlElement)KeyInfo_E.SelectSingleNode(L"//PSE"); 
				//
				CString dirAll = m_keyContainerPath + _T("\\*");
				WIN32_FIND_DATA _f_data;
				HANDLE _f = FindFirstFile(dirAll,&_f_data);
				bool done = false;
				while ((_f != INVALID_HANDLE_VALUE) & (! done))
				{
					CString file(_f_data.cFileName);
					//
					if (file.Left(1) != L".")
					{
						string path = string(m_keyContainerPath + _T("\\") + file); 
						string fileName(file);
						//
						File f;
						f.Open(CString(path));
						Blob fileData = f.ReadAll();
						f.Close();
						//
						XmlElement File_E = KeyInfo_E.OwnerDocument().CreateElement(L"",L"File",L"");
						File_E.SetAttribute(L"Name",fileName);
						File_E.InnerText() = __ToBase64String(fileData);
						PSE_E.AppendChild(File_E);
					}
					//
					if (! FindNextFile(_f,&_f_data)) done = true;
				}
				//if (_f != INVALID_HANDLE_VALUE) CloseHandle(_f); 
			}
		}
		_Catch() 
	}
};

class CCOM_Key : public SharedPtr<CCOM_KeyObject> 
{
public:
	CCOM_Key() : SharedPtr<CCOM_KeyObject>(new CCOM_KeyObject()) 
	{
	}

	operator Key()
	{
		return SharedPtr<KeyObject>(*this);
	}
};







// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ������ CCOM_CertificateObject, CCOM_Certificate 

class CCOM_CertificateObject : public CertificateObject 
{
public:
	HRESULT STDMETHODCALLTYPE QueryInterface(
		const IID & riid,  
		void **ppvObj       
		)
	{
		return E_NOTIMPL; 
	}

	ULONG STDMETHODCALLTYPE AddRef()
	{
		return 2; 
	}

	ULONG STDMETHODCALLTYPE Release()
	{
		return 2; 
	}


protected:
	void Clear()
	{
	}

	void Dispose()
	{
	}

public:
	CCOM_CertificateObject() 
	{
		Clear();
	}

	virtual ~CCOM_CertificateObject()
	{
		Dispose();
	}

	virtual void Import(const CString& path) 
	{
		File f;
		f.Open(path);
		Blob certData = f.ReadAll();
		f.Close();
		//
		Import(certData);
	}

	Blob m_certificateData;

	virtual void Import(Blob CertData) 
	{
		try
		{
			if (CertData.Length() <= 500) 
			{
				throw MethodError(L"������ ������ ����������� (1)"); 
			}
			//
			m_certificateData.Allocate(CertData.Length());
			CopyMemory(m_certificateData.GetBuffer(),CertData.GetBuffer(),CertData.Length());
			//
			AsnObject certO(m_certificateData);
			//
			if (! certO.IsCertificate())
			{
				string msg = FormatStr(L"���� �� �������� ������������ (������ �����: %d)",
					(int)CertData.Length()
					);
				throw MethodError(msg);
			}
			//
			Algorithms::Alg_1_8_2 a2;
			m_PKH = FromBase64String(
				a2.Encode((Blob)certO.CP_GOST2001PublicKeyBits)
				);
			//
			ParseCertData(); 
		}
		_Catch()
	}




	// ===========================================================================================
	// ��������� CertificateObject 

	// ===========================================================================================
	// ISigner 

	virtual Blob GetCertData() 
	{
		try
		{
			return m_certificateData;
		}
		_Catch() 
	}

	virtual string CreateCMSSignature64(Blob data) 
	{
		try
		{
			return CreateCMSSignature64(data,L"");
		}
		_Catch() 
	}

	string CreateCMSSignature64(Blob dataToSign,string // hashOid
		, bool includeCert=true 
		)
	{
		try
		{
			int j = 0;
			//
			m_PKH = m_spKey->GetPKH();
			//
			AsnObject cert_O = AsnObject::NewSequence(); 
			try
			{
				cert_O = AsnObject(m_certificateData); 
			}
			catch(::::Exception e)
			{
#				ifdef _DEBUG
				{
					TRACE_LOG(_T("!!!\n������ ��� ������� ����������� (CMS64)\n!!!")); 
					TRACE_LOG1(_T("Length: %d"), (int)m_certificateData.Length() );
					File f;
					f.Open(_T("D:\\___error-cer.cer")); 
					f.Replace((const char*)m_certificateData.GetBuffer(), m_certificateData.Length()); 
					f.Close();
				}
#				endif
				throw e.AddIfNewSource_(L"������ ��� ������� ����������� (CMS64)");
			}
			catch(...)
			{
				throw MethodError(L"������ ��� ������� ����������� (CMS64)");
			}
			//
			//
			//
			AsnObject m = AsnObject::NewSequence();
			AsnObject* p_m3 = 0;
			try
			{
				m	.Add(AsnObject(OID(L"1.2.840.113549.1.7.2")))
					.Add(AsnObject(true,AsnObject::CONTEXT_SPECIFIC,0));
				//m.SetIndefiniteLength(true);
				AsnObject& m__1 = m[1];
				//m__1.SetIndefiniteLength(true);
				m__1.Add(AsnObject::NewSequence());
				AsnObject& m2 = m__1[0];
				//m2.SetIndefiniteLength(true);
				m2	.Add(AsnObject(1))
					.Add(AsnObject::NewSet())
					.Add(AsnObject::NewSequence())
					//.Add(AsnObject::NewSequence()) // 
					///.Add(AsnObject(true,AsnObject::CONTEXT_SPECIFIC,0)) /// ADD CERT 
					.Add(AsnObject::NewSet());
				//
				AsnObject& m2__1 = m2[1];
				m2__1.Add(
					AsnObject::NewSequence()
						.Add(AsnObject(OID(L"1.2.643.2.2.9")))
						.Add(AsnObject(false,AsnObject::UNIVERSAL,AsnObject::_NULL_)) 
				);
				//
				AsnObject& m2__2 = m2[2];
				//m2__2.SetIndefiniteLength(true);
				m2__2.Add(AsnObject(OID(L"1.2.840.113549.1.7.1"))); 
				//
				AsnObject& m2__3 = m2[3]; /// ADD CERT 
				m2__3.Add(AsnObject::NewSequence());
				AsnObject& m3 = m2__3[0];
				p_m3 = &m3;
				//
				m3	.Add(AsnObject(1))
					.Add(AsnObject::NewSequence())
					.Add(AsnObject::NewSequence())
					//.Add(sInfo_O) 
					.Add(AsnObject::NewSequence())
					;
				//
				AsnObject& m3__1 = m3[1];
				AsnObject& m3__2 = m3[2];
				AsnObject& m3__3 = m3[3]; // sInfo_O => 4 
				//
				AsnObject& cert_O__0 = cert_O[0];
				for (int q = 0; q <= 3 && q <= cert_O__0.ChildCount(); ++q)
				{
					AsnObject& cert_O__0__q = cert_O__0[q];
					if (cert_O__0__q.Tag() == AsnObject::SEQUENCE)
						if (cert_O__0__q.ChildCount() > 0)
							if (((AsnObject&)cert_O__0__q[0]).Tag() == AsnObject::SET)
								m3__1.Add(cert_O__0__q);
				}
				m3__1.Add((AsnObject&)cert_O__0[1]);
				//
				m3__2.Add(AsnObject(OID(L"1.2.643.2.2.9")))
					.Add(AsnObject(false,AsnObject::UNIVERSAL,AsnObject::_NULL_));
				//
				m3__3.Add(AsnObject(OID(L"1.2.643.2.2.19")))
					.Add(AsnObject(false,AsnObject::UNIVERSAL,AsnObject::_NULL_));
				//
				m3.Add(AsnObject(false,AsnObject::UNIVERSAL,AsnObject::OCTET_STRING)); 
			}
			catch(::::Exception e)
			{
				throw e.AddIfNewSource_(L"������ ��� ������������ CMS-������� (CMS64)");
			}
			catch(...)
			{
				throw MethodError(L"������ ��� ������������ CMS-������� (CMS64)");
			}
			//
			// �����������
			//
			AsnObject& m3__4 = (*p_m3)[4]; // sInfo_O ? 
			//
			Blob rawSignature = m_spKey->CreateRawSignature(dataToSign, 0, Blob());
			//
			m3__4.Data().Allocate(rawSignature.Length());
			for (j = 0; j < rawSignature.Length(); ++j) 
				m3__4.Data()[j] = rawSignature[rawSignature.Length()-1-j]; 
			//
			return Util::ToBase64String(m.Encoded());
		}
		_Catch()
	}

	string CreateCMSSignature64___(Blob dataToSign,string // hashOid
		, bool includeCert=true 
		)
	{
#ifdef _DEBUG
		//{
		//	//// return CreateCMSSignature64_FCSM(dataToSign,true); 
		//	//
		//	File f1;
		//	f1.Open(_T("D:\\_source\\eek\\u1.xttd.sig"));
		//	Blob sig = f1.ReadAll();
		//	f1.Close();
		//	//
		//	Blob cert;
		//	cert.Allocate(924-57);
		//	CopyMemory(cert.GetBuffer(), sig.GetBuffer()+57, cert.Length()); 
		//	//
		//	File f2;
		//	f2.OpenToWrite(_T("D:\\_source\\eek\\u1.xttd.cer"));
		//	f2.Replace((const char*)cert.GetBuffer(), cert.Length());
		//	f2.Close();
		//}
#endif
		//
		try
		{
			int j = 0;
			//
			// TODO: PKH !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//
			m_PKH = m_spKey->GetPKH();
			//
			AsnObject cert_O(m_certificateData);
			////Runtime.Echo(cert_O.Dump);
			//
			AsnObject sInfo_O(true,AsnObject::CONTEXT_SPECIFIC,0); 
			{
				AsnObject sInfo_1 = AsnObject::NewSequence();
				AsnObject sInfo_2 = AsnObject::NewSequence();
				AsnObject sInfo_3 = AsnObject::NewSequence();
				AsnObject sInfo_4 = AsnObject::NewSequence();
				//
				{
					AsnObject s = AsnObject::NewSet();
					s.Add(AsnObject(OID(L"1.2.840.113549.1.7.1"))); 
					//
					sInfo_1.Add(AsnObject(OID(L"1.2.840.113549.1.9.3")))
						.Add(s); 
				}
				//
				{
					AsnObject t = AsnObject(false,AsnObject::UNIVERSAL,AsnObject::UTCTime);
					t.m_Time = COleDateTime::GetCurrentTime(); 
					//
					AsnObject s = AsnObject::NewSet();
					s.Add(t); 
					//
					sInfo_2.Add(AsnObject(OID(L"1.2.840.113549.1.9.5")))
						.Add(s); 
				}
				//
				{
					AsnObject comment(false,AsnObject::UNIVERSAL,AsnObject::BMPString);
					comment.m_text = L"Comment"; 
					//
					AsnObject q = AsnObject::NewSequence();
					q.Add(comment); 
					//
					AsnObject s = AsnObject::NewSet();
					s.Add(q); 
					//
					sInfo_3.Add(AsnObject(OID(L"1.3.6.1.4.1.311.2.1.120")))
						.Add(s); 
				}
				//
				{
					AsnObject s = AsnObject::NewSet();
					//
					sInfo_4.Add(AsnObject(OID(L"1.2.840.113549.1.9.4")))
						.Add(s); 
				}
				//
				sInfo_O.Add(sInfo_1);
				sInfo_O.Add(sInfo_2);
				sInfo_O.Add(sInfo_3);
				//sInfo_O.Add(sInfo_4);
			}
			//
			//
			//
			AsnObject m = AsnObject::NewSequence();
			m	.Add(AsnObject(OID(L"1.2.840.113549.1.7.2")))
				.Add(AsnObject(true,AsnObject::CONTEXT_SPECIFIC,0));
			//m.SetIndefiniteLength(true);
			AsnObject& m__1 = m[1];
			//m__1.SetIndefiniteLength(true);
			m__1.Add(AsnObject::NewSequence());
			AsnObject& m2 = m__1[0];
			//m2.SetIndefiniteLength(true);
			m2	.Add(AsnObject(1))
				.Add(AsnObject::NewSet())
				.Add(AsnObject::NewSequence())
				//.Add(AsnObject::NewSequence()) // 
				///.Add(AsnObject(true,AsnObject::CONTEXT_SPECIFIC,0)) /// ADD CERT 
				.Add(AsnObject::NewSet());
			//
			AsnObject& m2__1 = m2[1];
			m2__1.Add(
				AsnObject::NewSequence()
					.Add(AsnObject(OID(L"1.2.643.2.2.9")))
					.Add(AsnObject(false,AsnObject::UNIVERSAL,AsnObject::_NULL_)) 
			);
			//
			AsnObject& m2__2 = m2[2];
			//m2__2.SetIndefiniteLength(true);
			m2__2.Add(AsnObject(OID(L"1.2.840.113549.1.7.1"))); 
			//
			///AsnObject& m2__cert = m2[3]; /// ADD CERT 
			///m2__cert.Add((AsnObject&)cert_O); 
			//
			//AsnObject& m2__cert = m2[3];
			//AsnObject certO(GetCertData()); 
			//m2__cert.Add(certO); 
			//
			AsnObject& m2__3 = m2[3]; /// ADD CERT 
			m2__3.Add(AsnObject::NewSequence());
			AsnObject& m3 = m2__3[0];
			//
			m3	.Add(AsnObject(1))
				.Add(AsnObject::NewSequence())
				.Add(AsnObject::NewSequence())
				//.Add(sInfo_O) 
				.Add(AsnObject::NewSequence())
				;
			//
			AsnObject& m3__1 = m3[1];
			AsnObject& m3__2 = m3[2];
			AsnObject& m3__3 = m3[3]; // sInfo_O => 4 
			//
			AsnObject& cert_O__0 = cert_O[0];
			for (int q = 0; q <= 3 && q <= cert_O__0.ChildCount(); ++q)
			{
				AsnObject& cert_O__0__q = cert_O__0[q];
				if (cert_O__0__q.Tag() == AsnObject::SEQUENCE)
					if (cert_O__0__q.ChildCount() > 0)
						if (((AsnObject&)cert_O__0__q[0]).Tag() == AsnObject::SET)
							m3__1.Add(cert_O__0__q);
			}
			m3__1.Add((AsnObject&)cert_O__0[1]);
			//
			m3__2.Add(AsnObject(OID(L"1.2.643.2.2.9")))
				.Add(AsnObject(false,AsnObject::UNIVERSAL,AsnObject::_NULL_));
			//
			m3__3.Add(AsnObject(OID(L"1.2.643.2.2.19")))
				.Add(AsnObject(false,AsnObject::UNIVERSAL,AsnObject::_NULL_));
			//
			m3.Add(AsnObject(false,AsnObject::UNIVERSAL,AsnObject::OCTET_STRING));
			AsnObject& m3__4 = m3[4]; // sInfo_O ? 
			//
			// �����������
			//
			Blob rawSignature = m_spKey->CreateRawSignature(dataToSign, 0, Blob());
#			ifdef _DEBUG
			//{
			//	if (KeyObject::MakeWrong())
			//	{
			//		rawSignature[0] = 3; // !!! 
			//	}
			//}
#			endif
			///TRACE_LOG1(_T("Raw Signature: %s"), Util::BlobToHex(rawSignature).GetString() );
			//
			m3__4.Data().Allocate(rawSignature.Length());
			for (j = 0; j < rawSignature.Length(); ++j) 
				m3__4.Data()[j] = rawSignature[rawSignature.Length()-1-j];
			//
			//m.SetIndefiniteLength(true);
			//m__1.SetIndefiniteLength(true);
			//
			////TRACE_LOG1(_T("CMS Signature:\n%s"), CString(m.Dump()).GetString() ); 
			//
			//string path2 = @"z:\MMBANK\_sig.der";
			//FileStream writer = File.Open(path2,FileMode.Create,FileAccess.Write);				
			//byte[] data2 = m.Encoded;
			//writer.Write(data2,0,(int)data2.Length);
			//writer.Close();
			//
			// Signature OctetString data: 
			// m[1][0][3][0][4]
			//
			// ----
			// ��������� ������� ��� ������������ 
			//
#			ifdef _DEBUG
			{
				//OutputDebugStringW(m.Dump() + L"\n"); 
				////
				//File f_cert;
				//f_cert.OpenToWrite(_T("d:\\test_data.cer"));
				//f_cert.Replace((const char*)m_certificateData.GetBuffer(), m_certificateData.Length()); 
				//f_cert.Close();
				////
				//AsnObject _C(m_certificateData);
				//OutputDebugStringW(_C.Dump() + L"\n"); 
				//Blob data_C = _C.Encoded(); 
				////
				//File f_data;
				//f_data.OpenToWrite(_T("d:\\test_data.bin"));
				//f_data.Replace((const char*)dataToSign.GetBuffer(), dataToSign.Length()); 
				//f_data.Close();
				////
				//Blob sig = m.Encoded(); 
				////
				//File f_sig;
				//f_sig.OpenToWrite(_T("d:\\test_data.bin.SIG"));
				//f_sig.Replace((const char*)sig.GetBuffer(), sig.Length()); 
				//f_sig.Close();
			}
#			endif
			//
			return Util::ToBase64String(m.Encoded());
		}
		_Catch()
	}

	string GetPolicy()
	{
		try
		{
			AsnObject cert_O(m_certificateData);
			//
			AsnObject::OidSet Policies = cert_O.CertificatePolicies(); 
			//
			string policy;
			//
			policy = L"1.2.643.6.2.1.7.1";
			if (Policies[policy]) return policy;
			//
			policy = L"1.2.643.6.2.1.7.2";
			if (Policies[policy]) return policy;
			//
			return policy;
		}
		_Catch()
	}

	string CreateCMSSignature64_FCSM(Blob dataToSign, Blob originalSig, bool includeCert=true)
	{
		try
		{
			int j = 0;
			//
			// TODO: PKH !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//
			m_PKH = m_spKey->GetPKH();
			//
			AsnObject cert_O(m_certificateData);
			////Runtime.Echo(cert_O.Dump);
			//
			//AsnObject sInfo_O(true,AsnObject::CONTEXT_SPECIFIC,0); 
			//{
			//	AsnObject sInfo_1 = AsnObject::NewSequence();
			//	AsnObject sInfo_2 = AsnObject::NewSequence();
			//	AsnObject sInfo_3 = AsnObject::NewSequence();
			//	AsnObject sInfo_4 = AsnObject::NewSequence();
			//	//
			//	{
			//		AsnObject s = AsnObject::NewSet();
			//		s.Add(AsnObject(OID(L"1.2.840.113549.1.7.1"))); 
			//		//
			//		sInfo_1.Add(AsnObject(OID(L"1.2.840.113549.1.9.3")))
			//			.Add(s); 
			//	}
			//	//
			//	{
			//		AsnObject t = AsnObject(false,AsnObject::UNIVERSAL,AsnObject::UTCTime);
			//		t.m_Time = COleDateTime::GetCurrentTime(); 
			//		//
			//		AsnObject s = AsnObject::NewSet();
			//		s.Add(t); 
			//		//
			//		sInfo_2.Add(AsnObject(OID(L"1.2.840.113549.1.9.5")))
			//			.Add(s); 
			//	}
			//	//
			//	{
			//		AsnObject comment(false,AsnObject::UNIVERSAL,AsnObject::BMPString);
			//		comment.m_text = L"Comment"; 
			//		//
			//		AsnObject q = AsnObject::NewSequence();
			//		q.Add(comment); 
			//		//
			//		AsnObject s = AsnObject::NewSet();
			//		s.Add(q); 
			//		//
			//		sInfo_3.Add(AsnObject(OID(L"1.3.6.1.4.1.311.2.1.120")))
			//			.Add(s); 
			//	}
			//	//
			//	{
			//		AsnObject s = AsnObject::NewSet();
			//		//
			//		sInfo_4.Add(AsnObject(OID(L"1.2.840.113549.1.9.4")))
			//			.Add(s); 
			//	}
			//	//
			//	sInfo_O.Add(sInfo_1);
			//	sInfo_O.Add(sInfo_2);
			//	sInfo_O.Add(sInfo_3);
			//	sInfo_O.Add(sInfo_4);
			//}
			//
			//
			//
			AsnObject m = AsnObject::NewSequence();
			//
			AsnObject* p_m3 = 0;
			//
			bool nextSig = originalSig.Length() > 0; 
			bool firstSig = !nextSig;
			//
			bool addNextCertInfo = false; 
			//
			if (firstSig)
			{
				m	.Add(AsnObject(OID(L"1.2.840.113549.1.7.2")))
					.Add(AsnObject(true,AsnObject::CONTEXT_SPECIFIC,0));
				m.SetIndefiniteLength(true);
				AsnObject& m__1 = m[1];
				m__1.SetIndefiniteLength(true);
				m__1.Add(AsnObject::NewSequence());
				AsnObject& m2 = m__1[0];
				m2.SetIndefiniteLength(true);
				m2	.Add(AsnObject(1))
					.Add(AsnObject::NewSet())
					.Add(AsnObject::NewSequence())
					//.Add(AsnObject::NewSequence()) // 
					.Add(AsnObject(true,AsnObject::CONTEXT_SPECIFIC,0)) /// ADD CERT 
					.Add(AsnObject::NewSet());
				//
				AsnObject& m2__1 = m2[1];
				m2__1.Add(
					AsnObject::NewSequence()
						.Add(AsnObject(OID(L"1.2.643.2.2.9")))
						.Add(AsnObject(false,AsnObject::UNIVERSAL,AsnObject::_NULL_)) 
				);
				//
				AsnObject& m2__2 = m2[2];
				m2__2.SetIndefiniteLength(true);
				m2__2.Add(AsnObject(OID(L"1.2.840.113549.1.7.1"))); 
				//
				AsnObject& m2__cert = m2[3]; /// ADD CERT 
				m2__cert.Add((AsnObject&)cert_O); 
				//
				//AsnObject& m2__cert = m2[3];
				//AsnObject certO(GetCertData()); 
				//m2__cert.Add(certO); 
				//
				AsnObject& m2__3 = m2[4]; /// ADD CERT 
				m2__3.Add(AsnObject::NewSequence());
				AsnObject& m3 = m2__3[0];
				p_m3 = &m3;
			}
			else
			{
				m = AsnObject(originalSig); 
				AsnObject& m__1 = m[1];
				AsnObject& m2 = m__1[0];
				//
				AsnObject& m2__cert = m2[3]; /// ADD CERT 
				m2__cert.Add((AsnObject&)cert_O); 
				//
				AsnObject& m2__3 = m2[4]; /// ADD CERT (check !!!) 
				m2__3.Add(AsnObject::NewSequence());
				int signatureIndex = m2__3.ChildCount()-1; 
				AsnObject& m3 = m2__3[signatureIndex];
				p_m3 = &m3;
				//
				addNextCertInfo = true; 
			}
			//
			// ----
			// Creating the signature object 
			//
			AsnObject& m3 = *(p_m3); 
			//
			m3	.Add(AsnObject(1))
				.Add(AsnObject::NewSequence())
				.Add(AsnObject::NewSequence())
				//.Add(sInfo_O) 
				.Add(AsnObject::NewSequence())
				;
			//
			AsnObject& m3__1 = m3[1];
			AsnObject& m3__2 = m3[2];
			AsnObject& m3__3 = m3[3]; // sInfo_O => 4 
			//
			AsnObject& cert_O__0 = cert_O[0];
			for (int q = 0; q <= 3 && q <= cert_O__0.ChildCount(); ++q)
			{
				AsnObject& cert_O__0__q = cert_O__0[q];
				if (cert_O__0__q.Tag() == AsnObject::SEQUENCE)
					if (cert_O__0__q.ChildCount() > 0)
						if (((AsnObject&)cert_O__0__q[0]).Tag() == AsnObject::SET)
							m3__1.Add(cert_O__0__q);
			}
			m3__1.Add((AsnObject&)cert_O__0[1]);
			//
			m3__2.Add(AsnObject(OID(L"1.2.643.2.2.9")))
				.Add(AsnObject(false,AsnObject::UNIVERSAL,AsnObject::_NULL_));
			//
			m3__3.Add(AsnObject(OID(L"1.2.643.2.2.19")))
				.Add(AsnObject(false,AsnObject::UNIVERSAL,AsnObject::_NULL_));
			//
			m3.Add(AsnObject(false,AsnObject::UNIVERSAL,AsnObject::OCTET_STRING));
			AsnObject& m3__4 = m3[4]; // sInfo_O ? 
			//
			// �����������
			//
			Blob rawSignature = m_spKey->CreateRawSignature(dataToSign, 0, Blob());
#			ifdef _DEBUG
			//{
			//	if (KeyObject::MakeWrong())
			//	{
			//		rawSignature[0] = 3; // !!! 
			//	}
			//}
#			endif
			///TRACE_LOG1(_T("Raw Signature: %s"), Util::BlobToHex(rawSignature).GetString() );
			//
			m3__4.Data().Allocate(rawSignature.Length());
			for (j = 0; j < rawSignature.Length(); ++j) 
				m3__4.Data()[j] = rawSignature[rawSignature.Length()-1-j]; 
			//
			//m.SetIndefiniteLength(true);
			//m__1.SetIndefiniteLength(true);
			//
			////TRACE_LOG1(_T("CMS Signature:\n%s"), CString(m.Dump()).GetString() ); 
			//
			//string path2 = @"z:\MMBANK\_sig.der";
			//FileStream writer = File.Open(path2,FileMode.Create,FileAccess.Write);				
			//byte[] data2 = m.Encoded;
			//writer.Write(data2,0,(int)data2.Length);
			//writer.Close();
			//
			// Signature OctetString data: 
			// m[1][0][3][0][4]
			//
			string m3Dump = m3.Dump();
			////OutputDebugStringW(L"----\nm3:\m" + m3Dump + L"\n\n"); 
			//
			bool fKD = AsnObject::fKeepDeep();
			AsnObject::fKeepDeep() = true;
			Blob sig = m.ToBlob(); 
			AsnObject::fKeepDeep() = fKD; 
			//
			// ----
			// ��������� ������� ��� ������������ 
			//
#			ifdef _DEBUG
			{
				//OutputDebugStringW(m.Dump() + L"\n"); 
				////
				//File f_cert;
				//f_cert.OpenToWrite(_T("d:\\test_data.cer"));
				//f_cert.Replace((const char*)m_certificateData.GetBuffer(), m_certificateData.Length());  
				//f_cert.Close();
				////
				//AsnObject _C(m_certificateData);
				//OutputDebugStringW(_C.Dump() + L"\n"); 
				////Blob data_C = _C.Encoded(); 
				////
				//File f_data;
				//f_data.OpenToWrite(_T("d:\\test_data.bin"));
				//f_data.Replace((const char*)dataToSign.GetBuffer(), dataToSign.Length()); 
				//f_data.Close();
				////
				//try
				//{
				//}
				//catch(::Exception e)
				//{
				//	TRACE_LOG(e.ToString()); 
				//	throw;
				//}
				////
				//File f_sig;
				//f_sig.OpenToWrite(_T("d:\\test_data.bin.SIG"));
				//f_sig.Replace((const char*)sig.GetBuffer(), sig.Length()); 
				//f_sig.Close();
			}
#			endif
			//
			return Util::ToBase64String(sig);
		}
		_Catch()
	}































	ALG_ID GetAlgId()
	{
		//DWORD size1 = 0;
		//BYTE* b1 = 0;
		//CryptGetKeyParam(m_hKey,KP_ALGID,0,&size1,0);
		//b1 = new BYTE[size1];
		//CryptGetKeyParam(m_hKey,KP_ALGID,b1,&size1,0);
		////
		//ALG_ID& algId = *((ALG_ID*)b1);
		//
		// TODO: ������ �������� ��� CCOM?
		//
		return 0;
	}



	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// ��������� ISlotSigner 

	Blob m_DataToSign;

	STDMETHOD(Start)()
	{
		try
		{
			if (! m_DataToSign.IsEmpty()) m_DataToSign.Free(); 
			//
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(AddBlobk)(
		BYTE* data,
		int size)
	{
		try
		{
			if (! m_DataToSign.IsEmpty()) m_DataToSign.Free(); 
			//
			m_DataToSign.Allocate(size);
			CopyMemory(m_DataToSign.GetBuffer(),data,size);
			//
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(GetSignature)(
		BYTE** ppSignature,
		int* pSignatureSize)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetSignature64)(BSTR* out_signature)
	{
		try
		{
			string s64 = CreateCMSSignature64(m_DataToSign); 
			//
			CComBSTR bstr_s64(s64); 
			if (out_signature) *out_signature = bstr_s64.Detach(); 
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(GetSignature64_FCSM)(BSTR in_signature, BSTR* out_signature)
	{
		try
		{
			CComBSTR bstrInSig(in_signature); 
			string originalSig64(bstrInSig); 
			originalSig64.Trim(); 
			Blob originalSig;
			if (originalSig64.GetLength() > 0) originalSig = FromBase64String(originalSig64); 
			//
			string s64 = CreateCMSSignature64_FCSM(m_DataToSign, originalSig); 
			//
			CComBSTR bstr_s64(s64); 
			if (out_signature) *out_signature = bstr_s64.Detach(); 
			return S_OK;
		}
		_ComCatch()
	}












};

class CCOM_Certificate : public SharedPtr<CCOM_CertificateObject>
{
public:
	CCOM_Certificate() : SharedPtr<CCOM_CertificateObject>(new CCOM_CertificateObject())
	{
	}

	template<class A1>
	CCOM_Certificate(A1 a1) : SharedPtr<CCOM_CertificateObject>(new CCOM_CertificateObject(a1))
	{
	}
};



class CCOM_CSP : public CSP
{
public:
	Certificate FindPersonalCertificate(const CString& CommonNamePattern) 
	{
		return Certificate(); 
	}
};












// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ���������� �������      

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� CCOM_CSP 


} // namespace  
