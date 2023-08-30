/*
 CSP.h : ��������� ������������� (������-����������, CSP � ������� ������).

 $Name: work1 $
 $Revision: 1.1.2.6 $
 $Date: 2008/11/01 15:36:30 $
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
#else // WIN32
//#	include <tools/CCOM/ccom.h>
#	include "../tools/CCOM/x86/ccevp.h"
#endif

// 
//
#include "../low-level/SmartErrorHandling.h"
#include "../low-level/SmartCryptography.h"
#include "../low-level/SmartXml.h"
//
#include "SlotUtil.h"
#include "SlotAsn.h"
///#include <SlotEToken.h>
//
#include "../ax/interfaces/ISlotSigner.h"


#ifndef UNKNOWN_SLOT
#define UNKNOWN_SLOT -2
#endif


namespace  {



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� CSPCtx

class CSPCtx : public ErrorHandling<CSPCtx>
{
public:
	// ==============================================================================================
	// ���������� �� ��������� ��������� 
	// ----------------------

	// �������� ���������� ���������
	static CString GetEventSourceName() { return _T("CSP"); }

	// ����������, ������������ ��������� ���������
	static CString GetFacilityName() { return _T("Slot"); }

	// ���������� ��� ������
	static HRESULT GetErrorCode() { return E_FAIL; }

	// ���������� ��� ��������������
	static HRESULT GetWarningCode() { return E_FAIL; }

	// ��������������� CSP
	static HCRYPTPROV GetAuxCSP()
	{
		static HCRYPTPROV s_AuxCSP;
		//
		AuxCrypto A;
		if (! s_AuxCSP) s_AuxCSP = A.GetAuxCSP();
		//
		return s_AuxCSP;
	}
};






// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ������ KeyObject, Key

// ���� ������

class CertRequestObject;
typedef SharedPtr<CertRequestObject> CertRequest;

#define CryptoSystemIdWindowsCSP	1
#define CryptoSystemIdCCOM			2

class KeyObject 
{
protected:
	typedef SimpleErrorHandling<CSPCtx> Policies;

	void Dispose()
	{
	}

public:
	virtual ~KeyObject()
	{
		Dispose();
	}

#	ifdef _DEBUG
	inline static int& MakeWrong()
	{
		static int w = 0;
		return w;
	}
#	endif

	virtual int GetCryptoSystemId() const =0;

	virtual void SetPath(const CString& path) =0;

	virtual void CreateIn(const CString& path,const CString& containerPW,const CString& pin=_T("")) =0;

	virtual Blob GetCryptoProPublicKey() const =0; // �������� ���� � ����� CryptoPro, ���� �������� ���� RSA

	virtual Blob CreateRawSignature(Blob dataToSign, short flags, Blob digest0) const =0;

	virtual bool VerifyRawSignatureByKey(Blob dataToSign) const =0;

	virtual Blob Encipher(Blob data) const =0;

	virtual Blob Decipher(Blob ciphered) const =0;

	virtual Blob GetPKH() const =0;

	virtual void SetXmlInfo(XmlElement keyInfo, bool setPrivKeyAfter) =0;

	virtual string GetXmlInfoText() const =0;

	// ����� ������

	COleDateTime m_KeyTime;

	COleDateTime GetKeyTime()
	{
		return m_KeyTime;
	}

	void InitKeyTime()
	{
		m_KeyTime = COleDateTime::GetCurrentTime();
	}

	static string& _TempPath()
	{
		static string s_TempPath;
		return s_TempPath;
	}

	static string GetTempPath()
	{
		if (_TempPath().GetLength() == 0) 
			throw MethodError(L"���� ��� ���������� ���������� �������� ��������� �� �����");
		//
		return _TempPath();
	}

	static void SetTempPath(string value)
	{
		try
		{
			//if (_TempPath().GetLength() != 0) 
			//	throw MethodError(L���� ��� ���������� � �� ����� ���� �������");
			//
			// ������������� ���� 
			//
			_TempPath() = value;
			//
			try
			{
				if (! Util::DirectoryExists(CString(_TempPath())))
				{
					CreateDirectory(CString(_TempPath()),0);
				}
			}
			catch(...)
			{
				_TempPath() = L"";
				throw;
			}
		}
		_Catch()
	}

	static string GetTempContainerPath()
	{
		try
		{
			string tempPath = GetTempPath();
			//
			if (! Util::DirectoryExists(CString(tempPath))) 
				throw MethodError(L"������ ��������� ���� ��� ���������� �������� �����������");
			//
			string tempContainerPath = tempPath + L"\\" + NewGuidStr();
			CreateDirectory(CString(tempContainerPath),0);
			//
			return tempContainerPath;
		}
		_Catch()
	}

	static string NewGuidStr()
	{
		try
		{
			UUID guid = GUID_NULL; 
			//HRESULT hr =	
				::UuidCreate(&guid); 
			//
			unsigned char* GUIDA;
			UuidToStringA(&guid,&GUIDA);
			string GUIDs((TCHAR*)GUIDA);
			RpcStringFreeA(&GUIDA);
			return GUIDs;
		}
		_Catch()
	}
};

typedef SharedPtr<KeyObject> Key;






// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ������ CertRequestObject, CertRequest 

// ���������: ASN-������ ������� ������������� ������������ �������, �� � ������ ������� �� �������.

class CertRequestObject 
{
protected:
	typedef SimpleErrorHandling<CSPCtx> Policies;

	Key m_spKey;

	Blob m_PKH; 

	AsnObject m_Request;

	XmlElement m_CertRequestInfo;

	bool m_RequestIsSigned;

	void Clear()
	{
		m_RequestIsSigned = false;
	}

	void Dispose()
	{
	}

public:
	CertRequestObject()
		: m_Request(true,AsnObject::UNIVERSAL,AsnObject::_NULL_) 
	{
		Clear();
	}

	virtual ~CertRequestObject()
	{
		Dispose();
	}

	virtual void SetKey(Key key) 
	{ 
		try
		{
			//m_spKey = key; 
			////
			//m_Request.CP_GOST2001PublicKeyBits = m_spKey->GetCryptoProPublicKey();
			//return;



			m_spKey = key; 
			//
			Blob yData = m_spKey->GetCryptoProPublicKey();
			AsnObject yObj(yData); 
			//
			//m_Request.CP_GOST2001PublicKeyBits = m_spKey->GetCryptoProPublicKey();
			//
			AsnObject& o_0 = m_Request[0];
			//AsnObject& o_0_2 = o_0[2];
			o_0[2] = yObj;
			//
			//OutputDebugStringW(m_Request.Dump()); 
		}
		_Catch() 
	}

	//// virtual void Sign() =0;

	virtual AsnObject GetASN() { return m_Request; } 

	virtual Blob GetPKH() { return m_PKH; } 

	virtual XmlElement GetXmlInfo() { return m_CertRequestInfo; } 

	TextMap m_parameters;

	inline TextMap& Parameters() { return m_parameters; } 

	void LoadParameters(TextMap& paramSrc)
	{
		try
		{
			for (TextMap::Iterator i(paramSrc); i; ++i)
			{
				CString name = i.Id();
				CString value = i;
				m_parameters[name] = value;
			}
		}
		_Catch()
	}

	virtual void Create() 
	{
		try
		{
			Clear();
			//
			// ������ ������ �� ��������� ����������� � ����� ASN-�������. 
			//
		}
		_Catch()
	}

	AsnObject& GetRequest()
	{
		try
		{
			if (m_Request.m_Tag == AsnObject::_NULL_)
			{
				LoadRequestTemplate();
			}
			return m_Request;
		}
		_Catch()
	}

	void LoadRequestTemplate()
	{
		try
		{
			Blob requestTemplateBlob = AsnObject::PersonalRequestTemplate();
			Blob requestTemplate;
			requestTemplate.Allocate(requestTemplateBlob.GetSize());
			CopyMemory(requestTemplate.GetBuffer(),requestTemplateBlob.GetBuffer()
				,requestTemplateBlob.GetSize());
			m_Request = AsnObject(requestTemplate);
			//
#			ifdef _DEBUG
			{
				//OutputDebugString(_S(m_Request.Dump()));
			}
#			endif
			//
			m_RequestIsSigned = false;
		}
		_Catch()
	}

	//AsnObject GetSignedRequest()
	//{
	//	AsnObject request = GetRequest();
	//	//
	//	if (! m_RequestIsSigned)
	//	{
	//		TRACE_LOG(request.Dump());
	//		Blob eRequest = ((AsnObject&)m_Request[0]).Encoded();
	//		m_dataToSign.Allocate(eRequest.Length());
	//		CopyMemory(m_dataToSign.GetBuffer(),eRequest.GetBuffer(),eRequest.Length());
	//		SignRequest();
	//	}
	//	//
	//	return m_Request;
	//}

	//public XmlElement RequestInfo
	//{
	//	get
	//	{
	//		byte[] pk = CryptoProPublicKey;
	//		string pkHashStr = new Alg_1_8_2().Encode(y);
	//		//
	//		XmlDocument requestDoc = new XmlDocument();
	//		requestDoc.LoadXml(@"<?xml version=""1.0"" ?>" +
	//			"<RequestInfo" +
	//			" PubKeyHash=\"" + pkHashStr + "\"" + 
	//			">" + 
	//			"</RequestInfo>"); 
	//		//
	//		XmlElement RequestInfo_E = requestDoc.DocumentElement;
	//		//
	//		RequestInfo_E.AppendChild(
	//			requestDoc.CreateTextNode(Convert.ToBase64String(SignedRequest.Encoded))
	//			);
	//		//
	//		return RequestInfo_E;
	//	}
	//}

	Blob GetRequestData()
	{
		try
		{
#ifdef _DEBUG
			{
				//string line2 = L"*********************************************\n";
				//OutputDebugStringW(line2 + m_Request.Dump() + L"\n" + line2); 
			}
#endif
			//
			//m_Request.DropEncoded();
			//m_Request.Update();
			Blob requestData = m_Request.Encoded();
			//
#ifdef _DEBUG
			{
				//AsnObject r(requestData); 
				//string line2 = L"*********************************************\n";
				//OutputDebugStringW(line2 + r.Dump() + L"\n" + line2); 
			}
#endif
			//
			return requestData; 
		}
		_Catch()
	}

	void SaveRequestDER(string rpath,string rpath64=L"")
	{
		return; 
		// 
#		ifdef _DEBUG
		TRACE_LOG(m_Request.Dump());
#		endif
		m_Request.DropEncoded();
		m_Request.Update();
		Blob requestData = m_Request.Encoded();
		//
		File f;
		f.OpenToWrite(CString(rpath));
		f.Replace((char*)requestData.GetBuffer(),(int)requestData.Length());
		f.Close();
		//
		if (rpath64.GetLength() > 0)
		{
			string request64 = Util::ToBase64String(requestData);
			//
			File f10;
			f10.OpenToWrite(CString(rpath64));
			f10.Replace(_S(request64));
			f10.Close();
		}
	}

//	void SaveRequestDERToEToken(string rpath)
//	{
//#		ifdef _DEBUG
//		//TRACE_LOG(m_Request.Dump());
//#		endif
//		m_Request.Update();
//		Blob requestData = m_Request.Encoded();
//		//
//		CStringA rpathA;
//		CADB_write_file(rpathA.GetBuffer(),
//			(char*)requestData.GetBuffer(),requestData.Length());
//	}

	inline void SaveRequestDERToTemp()
	{
		string rpath; 
		//
		if (m_SavePath.GetLength() > 0)
		{
			rpath = m_SavePath;
		}
		else
		{
			rpath = KeyObject::GetTempPath() + L"\\" + Util::BlobToHexW(GetPKH())+L".der";
		}
		SaveRequestDER(rpath);
		//
		m_SavePath = rpath; 
	}

	string m_SavePath;

	inline string GetSavePath() 
	{
		return m_SavePath;
	}

	void SetSavePath(string value)
	{
		try
		{
			if (m_SavePath.GetLength() == 0)
			{
				// throw MethodError(_T("���� ��� ����������")); // �����? 
			}
			//
			m_SavePath = value;
			//
			// �������������� ��������: 
			// 
			// ... 
		}
		_Catch()
	}

	AsnObject SignRequest(const string& rpath)
	{
		try
		{
			if (m_RequestIsSigned) return m_Request; 
			//
			if (m_Request.m_Tag == AsnObject::_NULL_) 
			{
				LoadRequestTemplate();
			}
			//
			// �����������: 
			//
			int j;
			//
			m_Request.DropEncoded(); 
			m_Request.Update(); 
			//
			AsnObject& r0 = m_Request[0];
			AsnObject& r02 = r0[2];
			AsnObject& r020 = r02[0];
			AsnObject& r0201 = r020[1];
			AsnObject& r02010 = r0201[0];
			//r02010 = AsnObject(OID((string)L"1.2.643.2.2.36.0"));
			//
			// Blob R00 = m_Request.ToBlob();
			Blob eRequest = ((AsnObject&)m_Request[0]).ToBlob();
			int L = eRequest.Length(); 
			unsigned char k1 = eRequest[L-1];
			unsigned char k2 = eRequest[L-2];
			//
			File f1;
			f1.OpenToWrite(CString(rpath+_T(".1.der")));
			Blob requestData = m_Request.Encoded(); 
			f1.Replace((char*)eRequest.GetBuffer(),(int)eRequest.Length());
			f1.Close();
			//
#			ifdef _DEBUG
			{
				OutputDebugStringW(L"\nR to sign:\n" + _W(AsnObject(eRequest).Dump()) + L"\n"); 
			}
#			endif
			//
			Blob sign__1 = m_spKey->CreateRawSignature(eRequest, 0, Blob());
			//
			AsnObject& r2 = m_Request[2];
			Blob& r2data = r2.Data();
			r2data.Allocate(sign__1.Length());
			for (j = 0; j < sign__1.Length(); ++j) r2data.GetBuffer()[j] = sign__1[j];
			//
#			ifdef _DEBUG
			{
				TRACE_LOG(r2.Dump());
			}
#			endif
			//
			AsnObject& r1 = m_Request[1];
			((AsnObject&)r1[0]) = AsnObject(OID((string)L"1.2.643.2.2.3"));   
			//
			OutputDebugStringW(m_Request.Dump() + L"\n");
			//
			File f;
			f.OpenToWrite(CString(rpath));
			m_Request.DropEncoded(); 
			m_Request.Update(); 
			Blob requestData2 = m_Request.Encoded(); 
			f.Replace((char*)requestData2.GetBuffer(),(int)requestData2.Length());   
			f.Close();
			//
			return m_Request;
		}
		_Catch()
	}
};

typedef SharedPtr<CertRequestObject> CertRequest;

//class CertRequest : public SharedPtr<CertRequestObject>
//{
//public:
//	CertRequest() : SharedPtr<CertRequestObject>(new CertRequestObject())  
//	{
//	}
//};






// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ������ CertificateObject, Certificate

class CertificateObject : public ISlotSigner
{
protected:
	typedef SimpleErrorHandling<CSPCtx> Policies;

public:
	string CommonName;

	Blob SerialNumber;

	Blob SKI;

	string SignatureAlgorithm;

	int m_Validity; 

	COleDateTime m_notBefore;

	COleDateTime m_notAfter;

	SharedArray<CString> EnhKeyUsage;

	int m_slotId; // �������� ��� ������ ����������� � SlotId, ��������������� � ������������

	Key m_spKey;

	Blob m_PKH; 

protected:
	XmlElement m_CertInfo;

	SharedArray<CString> m_policies;

	PCCERT_CONTEXT m_cert;

	Map<CString,CString> m_attributes;

	Map<CString,CString> m_issuer;

	void Clear()
	{
		m_slotId = UNKNOWN_SLOT;
		//
		m_notBefore = COleDateTime();
		m_notAfter = COleDateTime();
		m_Validity = -5;
		//
		m_cert = 0;
	}

	void Dispose()
	{
	}

public:
	virtual ~CertificateObject()
	{
		Dispose();
	}

	CertificateObject() 
	{
	}

	virtual void SetKey(Key key) 
	{ 
		m_spKey = key; 
		//
		m_PKH = m_spKey->GetPKH();
	}

	virtual void Import(const CString& path) =0; 

	virtual void Import(Blob CertData) =0;

	virtual Blob GetPKH() const 
	{ 
		return m_PKH; 
	} 

	inline void ParseCertData() 
	{
		try
		{
			Blob certData = GetCertData(); 
			//
			PCCERT_CONTEXT pCertContext = CertCreateCertificateContext(X509_ASN_ENCODING,
				certData.GetBuffer(),
				certData.Length()
				);
			//
			if (pCertContext) 
			{
				// bool use = true; 
				//
				SYSTEMTIME st;
				FILETIME lft;   
				// 
				FileTimeToLocalFileTime((const FILETIME *)&
					pCertContext->pCertInfo->NotBefore, &lft);
				FileTimeToSystemTime(( const FILETIME *)&
					pCertContext->pCertInfo->NotBefore, &st);
				//
				m_notBefore = COleDateTime(st);
				// 
				FileTimeToLocalFileTime((const FILETIME *)&
					pCertContext->pCertInfo->NotAfter, &lft);
				FileTimeToSystemTime(( const FILETIME *)&
					pCertContext->pCertInfo->NotAfter, &st);
				//
				m_notAfter = COleDateTime(st);
				//
				m_Validity = CertVerifyTimeValidity(NULL, pCertContext->pCertInfo); 
			}
		}
		_Catch() 
	}

	virtual Blob GetCertData() =0;

	XmlElement GetXmlInfo(bool woBin) 
	{ 
		try
		{
			string
			t = L"<?xml version=\"1.0\" ?>\n"
				L"<CertificateInfo>\n"
				L"</CertificateInfo>"
				;
			//
			XmlDocument CertInfoDoc;
			CertInfoDoc.LoadXml(t);
			//
			XmlElement CertInfo_E = CertInfoDoc.DocumentElement(); 
			//
			CertInfo_E.SetAttribute(L"PubKeyHash",Util::ToBase64String(m_PKH)); 
			//
			if (!woBin) 
			{
				CertInfo_E.InnerText() = Util::ToBase64String(GetCertData()) + L"="; 
			}
			//
			return CertInfo_E; 
		}
		_Catch()
	} 

	void SetXmlInfo(XmlElement value, bool setPrivKeyAfter=false) 
	{
		// TODO: �������! 
	}

	// ===========================================================================================
	// ������ ������� � ������ �����������
	// ----------------------

	virtual TextMap& AllAttributes() { return m_attributes; } 

	virtual CString& IssuerCN()
	{
		static CString issuerCN;
		return issuerCN;
	}

	virtual CString& IssuerO()
	{
		static CString issuerO;
		return issuerO;
	}

	virtual string GetPolicy() =0;
};

typedef SharedPtr<CertificateObject> Certificate;

















// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ������ CSPObject, CSP

class CSPObject
{
protected:
	typedef SimpleErrorHandling<CSPCtx> Policies;

public:
	virtual Certificate FindPersonalCertificate(const CString& CommonNamePattern) =0;

	//virtual Certificate ChooseCertificate(HWND wnd,const CString& title,const CString& description) =0;

	//virtual Certificate LoadCertificate(const CString& certPath) =0;

	//virtual Certificate LoadCertificateData(Blob certPath) =0;

	//virtual Certificate LoadCertificateData64(const CString& certPath) =0;
};

typedef SharedPtr<CSPObject> CSP;



} // namespace  



