
#pragma once

#include <map> 
#include <vector> 
#include <string> 
//#include "cades.h"
#include "Windows.h"
#   include <wincrypt.h>
#   include <prsht.h>
#include "CryptoPro/WinCryptEx.h"
//#include "JSAPIAuto.h"
//#include <wincsp.h>

// #pragma comment(lib, "cades.lib")

namespace  {

	class PKITools 
	{
	public:
		inline static std::map<std::string,std::string>& Passwords()  
		{		
			static std::map<std::string,std::string> P; 
			return P; 
		}

		inline static SharedArray<CString> GetKeyDrives()
		{			
			try
			{
				SharedArray<CString> drives = Machine::ListDrives(DRIVE_REMOVABLE);    
				//
				//*
				string K = Machine::GetRegStringValue(
					HKEY_CURRENT_USER,
					_S("Software\\\\Cabinet\\Settings"),
					_S("special-102"), false
					);
				//
				if (K.GetLength() > 0)
				{
					drives.Add(_S(K)); 
				}
				//*/
				//
				// drives.Add(L"k");
				//
				HCRYPTPROV hProv = NULL;
				if (CryptAcquireContext(&hProv, 0, NULL, PROV_GOST_2001_DH,
					CRYPT_VERIFYCONTEXT))
				{
					drives.Add(L"_CryptoPro");
				}
				hProv = NULL;
				if (CryptAcquireContext(&hProv, 0, NULL, PROV_GOST_2012_256,
					CRYPT_VERIFYCONTEXT))
				{
					drives.Add(L"_CryptoPro2012_256");
				}
				hProv = NULL;
				if (CryptAcquireContext(&hProv, 0, NULL, PROV_GOST_2012_512,
					CRYPT_VERIFYCONTEXT))
				{
					drives.Add(L"_CryptoPro2012_512");
				}
				//
				return drives; 
			}
			_Catch() 
		}

		inline static SharedArray<CString> GetKeysCryptoPro(
			  SharedArray<string>* paths = NULL
			, SharedArray<string>* roots = NULL
			, SharedArray<string>* names = NULL
			)
		{
			try
			{
				SharedArray<CString> keys;
				//
				SharedArray<CString> keyContainers;
				try
				{
					keyContainers = Machine::ListRegKeys(
						HKEY_CURRENT_USER,
						_S("Software\\\\Cabinet\\LK\\Containers")
						);
				}
				catch (...)
				{
					return keys;
				}
				//
				for (int k = 0; k < keyContainers.GetSize(); k++)
				{
					CString containerName = keyContainers[k];
					//
					try
					{
						CString pkhStr = Machine::GetRegStringValue(
							HKEY_CURRENT_USER,
							_S("Software\\\\Cabinet\\LK\\Containers\\") + containerName,
							_S("pkh"), false
							);
						CString driveLetter = Machine::GetRegStringValue(
							HKEY_CURRENT_USER,
							_S("Software\\\\Cabinet\\LK\\Containers\\") + containerName,
							_S("drive"), false
							);
						//
						if (pkhStr.GetLength() > 0)
						{
							CString pkh1Str = _S(__ToBase64(FromBase64String(pkhStr)));
							//
							keys.Add(string(pkh1Str));
							if (paths)
							{
								(*paths).Add(containerName);
							}
							if (roots)
							{
								(*roots).Add(driveLetter);
							}
						}
					}
					catch (...)
					{
					}
				}
				//
				return keys;

















				if (paths) *paths = SharedArray<string>();
				//
				{
					DWORD       dwType;
					DWORD       cbName;
					DWORD       dwIndex = 0;
					BYTE        *ptr = NULL;
					ALG_ID      aiAlgid;
					DWORD       dwBits;
					DWORD       dwNameLen;
					CHAR        szName[1024]; // ������������ �����������
					BYTE        pbData[1024]; // ������������ �����������
					DWORD       cbData = 1024;
					DWORD       dwIncrement = sizeof(DWORD);
					DWORD       dwFlags = CRYPT_FIRST;
					CHAR        *pszAlgType = NULL;
					BOOL        fMore = TRUE;
					DWORD       cbProvName;

					HCRYPTPROV  hProv = 0;         // ���������� CSP
					LPTSTR      pszName = NULL;
					LPTSTR      pbProvName = NULL;
					
					pbProvName = (LPTSTR)malloc(cbProvName);
					if (!pbProvName)
						throw MethodError(L"Error during memory allocation for provider name.");

					memset(pbProvName, 0, cbProvName);

					// ��������� ����� ���������� �� ���������.
					//////if (CryptGetDefaultProvider(
					//////	PROV_GOST_2012_256,
					//////	NULL,
					//////	CRYPT_MACHINE_DEFAULT,
					//////	pbProvName,
					//////	&cbProvName))
					//////{
					//////	keys.Add(L"1234");
					//////}
				}
				//
				return keys;
			}
			_Catch()
		}

		/*
		window._plugin['commonKeyInfo'].then(function(res) {
			console.log(res);
		});
		*/

		inline static SharedArray<CString> GetKeys(const string& _drive
			, SharedArray<string>* paths=NULL
			, SharedArray<string>* roots=NULL
			, SharedArray<string>* names=NULL
			) 
		{
			try
			{
				if (_drive.Left(_W("_CryptoPro").GetLength()) == L"_CryptoPro")
					return GetKeysCryptoPro(paths, roots, names);
				//
				SharedArray<CString> keys; 
				//
				if (paths) *paths = SharedArray<string>();
				//
				CString drive(_drive); 
				CString driveRoot = drive + _T(":\\");
				CString Root = driveRoot + _T("");
				//
				if (Machine::DirectoryExists(Root))
				{
					CString certDir = Root + _T("\\Certificates"); 
					//
					if (Machine::DirectoryExists(certDir))
					{
						SharedArray<CString> keyDirs = Machine::ListFiles(certDir);   
						//
						for (int k = 0; k < keyDirs.Length(); ++k)
						{
							CString keyDir = keyDirs[k];
							////TRACE_LOG(keyDir);
							//
							int file_p = -1;
							int p1 = keyDir.Find(_T("\\"));
							while (p1 != -1)
							{
								file_p = p1;
								p1 = keyDir.Find(_T("\\"),p1+1);
							}
							CString keyName;
							if (file_p != -1)
								keyName = keyDir.Right(keyDir.GetLength()-file_p-1);
							else
								keyName = keyDir;
							//
							string path = keyDir;
							//
							// ----
							// ��������� ���������� � �����
							//
							string pkh64;
							//
							try
							{
								SharedArray<CString> pkXmlPaths = Machine::ListFiles(path, _T("*-k.xml"));
								if (pkXmlPaths.Length() > 0)
								{
									CString pkXmlPath = pkXmlPaths[0];
									//
									XmlDocument pkInfo;
									pkInfo.Load(string(pkXmlPath));
									XmlElement pkInfo_E = pkInfo.DocumentElement();
									//
									pkh64 = pkInfo_E.GetAttribute(L"PubKeyHash");
									keys.Add(pkh64);
									if (paths) (*paths).Add(path);
									if (roots) (*roots).Add(certDir);
									if (names) (*names).Add(keyName);
									//
									//if (pkh64.Right(1) == L"=") pkh64 = pkh64.Left(pkh64.GetLength()-1); 
									//keyInfo.SetAttribute(L"PubKeyHash",pkh64);
									////
									////t0 = COleDateTime(...);
									////string datetime_s = string(t0.Format(_T("%Y-%m-%dT%H:%M:%SZ")));
									//string datetime_s = pkInfo.DocumentElement().GetAttribute(L"KeyTime"); 
									////
									//// ----
									//// ��������� KeyInfo
									////
									//keyInfo.SetAttribute(L"KeyTime",datetime_s);
									////
									////if (lookupPkh64.Length() > 0)
									////{
									////	string activePkh64 = __ToBase64String(lookupPkh);
									////	if (
									////		(activePkh64 == pkh64) || 
									////		(_W(activePkh64+L"=") == pkh64) || 
									////		(activePkh64 == _W(pkh64+L"="))
									////		)
									////	{
									////		CComBSTR bstrOn(L"true");  
									////		keyInfo.SetAttribute(L"IsActive",CComVariant(bstrOn)); 
									////	}
									////}
								}
							}
							catch (...)
							{
							}
							//
							// ----
							// ��������� ����������
							//
		//					SharedArray<CString> certPaths = Machine::ListFiles(path,_T("*.cer"));
		//					bool certFound = false;
		//					for (int i = 0; i < certPaths.Length() && (! certFound); ++i)
		//					{
		//						CString certPath = certPaths[i];
		//						//
		//						Blob certData;
		//						::::File f;
		//						f.Open(certPath);
		//						certData = f.ReadAll();
		//						f.Close();
		//						//
		//						// CCOM:
		//						//
		//						CCOM_Certificate cert;
		//						try
		//						{
		//							cert->Import(certData);
		//							//
		//							string certPkh64 = __ToBase64String(cert->GetPKH());
		//							if (
		//								((certPkh64 == pkh64) || (certPkh64+L"=" == pkh64) || (certPkh64 == pkh64+L"="))
		//								|| (pkh64.GetLength() == 0)
		//								)
		//							{
		//								XmlElement CertInfo_E = cert->GetXmlInfo(woBin); 
		//								CertInfo_E.SetAttribute(L"PubKeyHashUrlEnc",
		//									UrlEncode(Base64Text_4Url(certPkh64))
		//									);
		//								keyInfo.AppendChild(CertInfo_E); 
		//								//
		//								certFound = true;
		//								//
		//								// ---- 
		//								// ��������� ����������� 
		//								//
		//								PrepareCertAttributesForXml(CertInfo_E, certData, cert); 
		//							}
		//						}
		//						catch(Exception& e)
		//						{
		//							TRACE_LOG(e.ToString());
		//						}
		//						catch(...)
		//						{
		//							TRACE_LOG(_T("����������� ������!"));
		//						}
		//					}
		//					//
		//					// ��������� ������
		//					//
		//					AsnObject request = AsnObject::NewSequence();
		//					AsnObject requestXO = AsnObject::NewSequence();
		//					//
		//					SharedArray<CString> reqPaths = Machine::ListFiles(path,_T("*-request.der")); 
		//					bool reqFound = false;
		//					for (int i = 0; i < reqPaths.Length() && (! reqFound); ++i)
		//					{
		//						CString reqPath = reqPaths[i];
		//						//
		//						Blob reqData;
		//						::::File f;
		//						f.Open(reqPath);
		//						reqData = f.ReadAll();
		//						f.Close();
		//						//
		//						try
		//						{
		//							request = AsnObject(reqData);
		//#ifdef _DEBUG
		//							{
		//								//OutputDebugStringW(request.Dump() + L"\n"); 
		//							}
		//#endif
		//							//
		//							CString reqXOPath = reqPath;
		//							reqXOPath.Replace(_T("-request.der"),_T("-x.der")); 
		//							//
		//							if (Machine::FileExists(reqXOPath))
		//							{
		//								Blob reqXOData;
		//								::::File fXO;
		//								fXO.Open(reqXOPath);
		//								reqXOData = fXO.ReadAll();
		//								fXO.Close();
		//								//
		//								requestXO = AsnObject(reqXOData);
		//							}
		//							//
		//							reqFound = true;
		//						}
		//						catch(Exception& e)
		//						{
		//							TRACE_LOG(e.ToString());
		//						}
		//						catch(...)
		//						{
		//							TRACE_LOG(_T("����������� ������!")); 
		//						}
		//					}
		//					//
		//					if (reqFound)
		//					{
		//						XmlDocument requestInfo = PKI::GetRequestInfo(request,requestXO);
		//						XmlElement ri = requestInfo.DocumentElement();
		//						keyInfo.AppendChild(ri);
		//						if (! ri.IsEmpty())
		//						{
		//							pkh64 = ((XmlElement)ri.SelectSingleNode(L"CertificateInfo"))
		//								.GetAttribute(L"PubKeyHash");
		//							//
		//							keyInfo.SetAttribute(L"PubKeyHash",pkh64);
		//						}
		//					}
		//					//
		//					if (keyInfo.HasAttribute(L"PubKeyHash")) // ������ ���� 
		//					{ 
		//						bool use = true;
		//						//
		//						if (use)
		//						{
		//							CommonKeyInfo_E.AppendChild(keyInfo);
		//						}
		//					}
						}
					}
				}
				return keys;
			}
			_Catch() 
		}

		inline static HCRYPTPROV GetCryptoProProvider2001()
		{
			try
			{
				HCRYPTPROV hProv;
				//
				if (!CryptAcquireContext(&hProv, 0, NULL, PROV_GOST_2001_DH,
					CRYPT_VERIFYCONTEXT)) 
				{
					throw MethodError(L"���������� ���������� ��������� ��������� (2001)");
				}
				//
				return hProv;
			}
			_Catch()
		}

		inline static HCRYPTPROV GetCryptoProProvider2012_256()
		{
			try
			{
				HCRYPTPROV hProv;
				//
				if (!CryptAcquireContext(&hProv, 0, NULL, PROV_GOST_2012_256,
					CRYPT_VERIFYCONTEXT))
				{
					throw MethodError(L"���������� ���������� ��������� ��������� (2012:256)");
				}
				//
				return hProv;
			}
			_Catch()
		}

		inline static HCRYPTPROV GetCryptoProProvider2012_512()
		{
			try
			{
				HCRYPTPROV hProv;
				//
				if (!CryptAcquireContext(&hProv, 0, NULL, PROV_GOST_2012_512,
					CRYPT_VERIFYCONTEXT))
				{
					throw MethodError(L"���������� ���������� ��������� ��������� (2012:512)");
				}
				//
				return hProv;
			}
			_Catch()
		}

		inline static SharedArray<string> GetKeyContainers2001(const string& search)
		{
			try
			{
				SharedArray<CString> containerNames;
				//
				HCRYPTPROV hProv = GetCryptoProProvider2001();
				//
				BYTE cntBuf[1024];
				DWORD cntLen = sizeof(cntBuf);
				DWORD dwFlags = CRYPT_FIRST;  //required initalization
				while (CryptGetProvParam(hProv, 
					PP_ENUMCONTAINERS, cntBuf, &cntLen, dwFlags))
				{
					dwFlags = 0;      //required to continue entire enumeration
					containerNames.Add(string(cntBuf));
				}				
				//
				return containerNames;
			}
			_Catch()
		}

		inline static SharedArray<string> GetKeyContainers2012_256(const string& search)
		{
			try
			{
				SharedArray<CString> containerNames;
				//
				HCRYPTPROV hProv = GetCryptoProProvider2012_256();
				//
				BYTE cntBuf[1024];
				DWORD cntLen = sizeof(cntBuf);
				DWORD dwFlags = CRYPT_FIRST;  //required initalization
				while (CryptGetProvParam(hProv,
					PP_ENUMCONTAINERS, cntBuf, &cntLen, dwFlags))
				{
					dwFlags = 0;      //required to continue entire enumeration
					containerNames.Add(string(cntBuf));
				}
				//
				return containerNames;
			}
			_Catch()
		}

		inline static SharedArray<string> GetKeyContainers2012_512(const string& search)
		{
			try
			{
				SharedArray<CString> containerNames;
				//
				HCRYPTPROV hProv = GetCryptoProProvider2012_512();
				//
				BYTE cntBuf[1024];
				DWORD cntLen = sizeof(cntBuf);
				DWORD dwFlags = CRYPT_FIRST;  //required initalization
				while (CryptGetProvParam(hProv,
					PP_ENUMCONTAINERS, cntBuf, &cntLen, dwFlags))
				{
					dwFlags = 0;      //required to continue entire enumeration
					containerNames.Add(string(cntBuf));
				}
				//
				return containerNames;
			}
			_Catch()
		}

		inline static void CreateRegistryRoot()
		{
			try
			{
				Machine::AddRegKey(HKEY_CURRENT_USER, _S(L"Software\\"));
				Machine::AddRegKey(HKEY_CURRENT_USER, _S(L"Software\\\\Cabinet"));
				Machine::AddRegKey(HKEY_CURRENT_USER, _S(L"Software\\\\Cabinet\\LK"));
			}
			_Catch()
		}

		inline static Blob requestPKH(AsnObject& requestO)
		{
			// Blob pk = requestO.CP_GOST2001PublicKeyBits;
			//
			AsnObject& rO_0 = requestO[0];
			AsnObject& rO_0_2 = rO_0[2];
			Blob pk = rO_0_2.Encoded();
			//
			Algorithms::Alg_1_8_2 a2;
			Blob m_PKH = FromBase64String(
				a2.Encode(pk)
				);
			//
			return m_PKH;
		}

		inline static void RegisterContainer(
			const string& containerName,
			const string& drive, 
			const COleDateTime& keyTime,
			Blob& requestData,
			AsnObject& requestO)
		{
			try
			{
				CreateRegistryRoot();
				//
				Machine::AddRegKey(HKEY_CURRENT_USER, 
					_S("Software\\\\Cabinet\\LK\\Containers"));
				Machine::AddRegKey(HKEY_CURRENT_USER,
					_S("Software\\\\Cabinet\\LK\\Containers\\") + _S(containerName));
				//
				Blob m_PKH = requestPKH(requestO);
				//
				Machine::SetRegStringValue(HKEY_CURRENT_USER,
					_S("Software\\\\Cabinet\\LK\\Containers\\") + _S(containerName),
					_S("pkh"),
					_S(__ToBase64(m_PKH))
					);				
				Machine::SetRegStringValue(HKEY_CURRENT_USER,
					_S("Software\\\\Cabinet\\LK\\Containers\\") + _S(containerName),
					_S("drive"),
					_S(drive)
					);					//
				//AsnObject requestO2 = requestO;
				//Blob requestData = requestO.Encoded();
				//
				Machine::SetRegBinaryValue(HKEY_CURRENT_USER,
					_S("Software\\\\Cabinet\\LK\\Containers\\") + _S(containerName),
					_S("0"),
					requestData
					);
				//
				COleDateTime t = keyTime;
				string keyTime_s = string(
					FormatTime_ymd_HMD(_S("%04d-%02d-%02d"),_S("T%02d:%02d:%02dZ"),t)
					);
				//
				Machine::SetRegStringValue(HKEY_CURRENT_USER,
					_S("Software\\\\Cabinet\\LK\\Containers\\") + _S(containerName),
					_S("key-time"),
					_S(keyTime_s)
					);
			}
			_Catch()
		}

		inline static void parseCert(const Blob& certData,
			string& surName,
			string& givenNames,
			string& commonName, // no CN 
			string& eMail,
			string& localityName,
			string& stateOrProvinceName,
			string& streetAddress,
			string& orgShortName,
			string& orgUnitName,
			string& title,
			string& serialNumber,
			string& notBefore, 
			string& notAfter,
			string& INN,
			string& OGRN,
			string& SNILS
			)
		{
			CCOM_CertificateObject cert;
			cert.Import(certData);
			commonName = cert.CommonName;
			//
			AsnObject certO(certData);
			AsnObject& o_0 = (AsnObject&)certO[0];
			AsnObject& o_0_1 = (AsnObject&)o_0[1];
			AsnObject& o_0_5 = (AsnObject&)o_0[5];
			for (int i = 0; i < o_0_5.ChildCount(); i++)
			{
				AsnObject& element = o_0_5[i];
				if (element.ChildCount() >= 2)
				{
					AsnObject& a = (AsnObject&)element[0];
					AsnObject& b = (AsnObject&)element[1];
					//if (a.Tag() == AsnObject::OBJECT_IDENTIFIER)   
					{
						if (a.Oid() == OID(L"2.5.4.3"))
						{
							// commonName = b.m_text; 
						}
						else if (a.Oid() == OID(L"2.5.4.10"))
						{
							orgShortName = b.m_text;
						}
						else if (a.Oid() == OID(L"2.5.4.11"))
						{
							orgUnitName = b.m_text;
						}
						else if (a.Oid() == OID(L"2.5.4.12"))
						{
							title = b.m_text;
						}
						else if (a.Oid() == OID(L"2.5.4.4"))
						{
							surName = b.m_text;
						}
						else if (a.Oid() == OID(L"2.5.4.42"))
						{
							givenNames = b.m_text;
						}
						else if (a.Oid() == OID(L"1.2.840.113549.1.9.1"))
						{
							eMail = b.m_text;
						}
						else if (a.Oid() == OID(L"2.5.4.7"))
						{
							localityName = b.m_text;
						}
						else if (a.Oid() == OID(L"2.5.4.8"))
						{
							stateOrProvinceName = b.m_text;
						}
						else if (a.Oid() == OID(L"2.5.4.9"))
						{
							streetAddress = b.m_text;
						}
						else if (a.Oid() == OID(L"1.2.643.3.131.1.1"))
						{
							INN = b.m_text;
						}
						else if (a.Oid() == OID(L"1.2.643.100.1"))
						{
							OGRN = b.m_text;
						}
						else if (a.Oid() == OID(L"1.2.643.100.3"))
						{
							SNILS = b.m_text;
						}
					}
				}
				else if (element.ChildCount() == 1)
				{
					AsnObject& set1 = element[0];
					AsnObject& a = (AsnObject&)set1[0];
					AsnObject& b = (AsnObject&)set1[1];
					if (set1.ChildCount() >= 2)
						//if (a.Tag() == AsnObject::OBJECT_IDENTIFIER)
					{
						if (a.Oid() == OID(L"2.5.4.3"))
						{
							// commonName = b.m_text; 
						}
						else if (a.Oid() == OID(L"2.5.4.4"))
						{
							surName = b.m_text;
						}
						else if (a.Oid() == OID(L"2.5.4.42"))
						{
							givenNames = b.m_text;
						}
						else if (a.Oid() == OID(L"2.5.4.10"))
						{
							orgShortName = b.m_text;
						}
						else if (a.Oid() == OID(L"2.5.4.11"))
						{
							orgUnitName = b.m_text;
						}
						else if (a.Oid() == OID(L"2.5.4.12"))
						{
							title = b.m_text;
						}
						else if (a.Oid() == OID(L"1.2.840.113549.1.9.1"))
						{
							eMail = b.m_text;
						}
						else if (a.Oid() == OID(L"2.5.4.7"))
						{
							localityName = b.m_text;
						}
						else if (a.Oid() == OID(L"2.5.4.8"))
						{
							stateOrProvinceName = b.m_text;
						}
						else if (a.Oid() == OID(L"2.5.4.9"))
						{
							streetAddress = b.m_text;
						}
						else if (a.Oid() == OID(L"1.2.643.3.131.1.1"))
						{
							INN = b.m_text;
						}
						else if (a.Oid() == OID(L"1.2.643.100.1"))
						{
							OGRN = b.m_text;
						}
						else if (a.Oid() == OID(L"1.2.643.100.3"))
						{
							SNILS = b.m_text;
						}
					}
				}
			}
			serialNumber = Util::BlobToHex(o_0_1.m_Data);
			//
			commonName = surName;
			if (givenNames.GetLength() > 0)
				commonName = commonName + L" " + givenNames;
			//
			AsnObject& o_0_4 = (AsnObject&)o_0[4];
			AsnObject& o_t0 = o_0_4[0];
			AsnObject& o_t1 = o_0_4[1];
			notBefore = o_t0.m_Time.Format(L"%d.%m.%Y");
			notAfter = o_t1.m_Time.Format(L"%d.%m.%Y");
		}

		inline static string GetKeysJSONListCnt(const string& driveLetter, const string& compareToPkh=L"")   
		{
			try
			{
				//return L"{\"" + driveLetter + "\": \"1\"}";
				if (driveLetter.Left(_W("_CryptoPro").GetLength()) == L"_CryptoPro")
				{
					// return GetKeysJSONListCnt_CryptoPro(driveLetter, compareToPkh);
				}
				//
				SharedArray<string> paths;
				SharedArray<string> pkhs = GetKeys(driveLetter, &paths);   
				//
				//if (compareToPkh.GetLength() > 0)
				//{
				//	pkhs.Add(compareToPkh); 
				//}
				//else
				//{
				//	pkhs = GetKeys(driveLetter, &paths);   
				//}
				//
				string cnt = L"";
				//
				int index = 0;
				for (int k = 0; k < pkhs.Length(); k++) 
				{
					string pkh = pkhs[k]; 
					bool use = true; 
					if (compareToPkh.GetLength() > 0) 
					{
						if (!(pkh == compareToPkh)) use = false;   
					}
					//
					if (pkh == "1234")
					{ 
						string s = L"{\"pkh\": \"" + pkh + "\"}";
					}
					else if (use)
					try
					{
						int certInstalled = 0;
						string f2015 = L"1"; 
						//
						string surName = L"";
						string givenNames = L"";
						string commonName = L""; // no CN 
						string eMail = L""; 
						string localityName = L""; 
						string stateOrProvinceName = L""; 
						string streetAddress = L"";
						string orgShortName = L"";
						string orgUnitName = L"";
						string title = L"";
						string serialNumber = L""; 
						string notBefore, notAfter; 
						string INN = L""; 
						string OGRN = L""; 
						string SNILS = L"";
						// 
						string algS = L"";
						string keyS = L"";
						string time_s = L""; 
						//
						Blob certData;
						Blob reqData;
						Map<string,string> extra; 
						//
						bool f0 = false;
						//
						if (driveLetter.Left(_W("_CryptoPro").GetLength()) == L"_CryptoPro")
						{
							try
							{
								auto m = SearchKey(pkh);
								if (string(m[0]) != driveLetter && driveLetter != L"")
									continue;
								//
								if (m.Length() >= 7)
								{
									string s0 = m[6];
									if (s0 != "")
										reqData = FromBase64String(s0);
									//
									if (m.Length() >= 8)
									{
										string s1 = m[7];
										if (s1 != "")
										{
											certData = FromBase64String(s1);
											certInstalled = 1;
										}
									}
								}
								time_s = m[8];
							}
							catch (...)
							{
							}
						}
						else
						{
							{
								SharedArray<CString> keyPaths = Machine::ListFiles(paths[k], _T("*-k.xml"));
								string keyPath = keyPaths[0];
								// 
								XmlDocument pkInfo;
								pkInfo.Load(string(keyPath));
								XmlElement pkInfo_E = pkInfo.DocumentElement();
								//
								time_s = pkInfo_E.GetAttribute(L"KeyTime");
								//time_s = time_s.Left(10); 
							}
							//
							string certPath = paths[k] + L"\\client.cer";
							if (Machine::FileExists(_S(certPath)))
							{
								certInstalled = 1;
								//
								File f;
								f.OpenToRead(_S(certPath));
								certData = f.ReadAll();
								f.Close();
							}
						}
						//
						if (certData.Length() > 0)
						{
							//
							// AsnObject certO(certData);
							try
							{
								parseCert(certData,
									surName,
									givenNames,
									commonName, // no CN 
									eMail,
									localityName,
									stateOrProvinceName,
									streetAddress,
									orgShortName,
									orgUnitName,
									title,
									serialNumber,
									notBefore,
									notAfter,
									INN,
									OGRN,
									SNILS);
							}
							catch(...)
							{
								f0 = true;
							}
						}
						else 
						{
							f0 = true;
						}
						//
						if (f0) // always overwrite! 
						{
							if (driveLetter.Left(_W("_CryptoPro").GetLength()) == L"_CryptoPro")
							{
								// reqData is already read!
							}
							else
							{
								SharedArray<CString> reqPaths = Machine::ListFiles(paths[k], _T("*-request.der"));
								if (reqPaths.Length() > 0)
								{
									string reqPath = reqPaths[0];
									//
									File f;
									f.OpenToRead(_S(reqPath));
									reqData = f.ReadAll();
									f.Close();
								}
							}
							//
							if (reqData.Length() > 0)
							{
								//
								//AsnObject reqO(reqData); 
								//string s = reqO.Dump();
								//File f2;
								//f2.OpenToWrite(_S("k:\\\\req.txt"));
								//f2.Write(_S(s));
								//f2.Close(); 
								//
								AsnObject reqO(reqData); 
								OutputDebugStringW(reqO.Dump());
								//
								AsnObject& o_0 = (AsnObject&)reqO[0];
								AsnObject& o_0_1 = (AsnObject&)o_0[1]; 
								AsnObject& o_0_2 = (AsnObject&)o_0[2]; 
								//
								if (o_0.ChildCount() >= 4 && false) {
									AsnObject& o_0_3 = (AsnObject&)o_0[3]; 
									AsnObject& o_0_3_0 = (AsnObject&)o_0_3[0]; 
									if (o_0_3_0.ChildCount() >= 2) {
										AsnObject& o_0_3_0_1 = (AsnObject&)o_0_3_0[1]; 
										AsnObject& o_0_3_0_1_0 = (AsnObject&)o_0_3_0_1[0]; 
										//
										for (int k = 0; k < o_0_3_0_1_0.ChildCount(); k++)
										{
											AsnObject& pair = (AsnObject&)o_0_3_0_1_0[k]; 
											if (
												(((AsnObject&)pair[0]).Oid() == OID(L"2.5.29.7")) ||
												(((AsnObject&)pair[0]).Oid() == OID(L"2.5.29.17"))
												)
											{
												AsnObject& b = ((AsnObject&)pair[1]).Deep;
												AsnObject& b_0 = (AsnObject&)b[0]; 
												AsnObject& b_0_0 = (AsnObject&)b_0[0]; 
												if (b_0_0.ChildCount() > 2) f2015 = "0";
												for (int j = 0; j < b_0_0.ChildCount(); j++)
												{
													AsnObject& set1 = b_0_0[j];
													AsnObject& pair = set1[0];
													string oid1 = ((AsnObject&)pair[0]).Oid(); 
													string val1 = ((AsnObject&)pair[1]).m_text; 
													extra[oid1] = val1; 
												}
											}
										}
									}}
								//
								//AsnObject& o_0_2_1 = (AsnObject&)o_0_2[1]; 
								//{
								//	string alg1 = ((AsnObject&)o_0_2[0]).Oid();
								//	string alg2 = ((AsnObject&)o_0_2_1[0]).Oid();
								//	string alg3 = ((AsnObject&)o_0_2_1[1]).Oid();
								//	string algS = alg1 + L", " + alg2 + L", " + alg3; 
								//}
								// 
								OutputDebugStringW(L"\n\n\n----");
								OutputDebugStringW(o_0_1.Dump());
								int n = o_0_1.ChildCount();
								for (int i = 0; i < n; i++)
								{
									AsnObject& element = o_0_1[i];
									if (element.ChildCount() >= 2)
									{
										AsnObject& a = (AsnObject&)element[0];
										AsnObject& b = (AsnObject&)element[1];
										//if (a.Tag() == AsnObject::OBJECT_IDENTIFIER)
										{
											if (a.Oid() == OID(L"2.5.4.3"))
											{
												commonName = b.m_text; 
											}
											else if (a.Oid() == OID(L"2.5.4.10"))
											{
												orgShortName = b.m_text; 
											}
											else if (a.Oid() == OID(L"2.5.4.11"))
											{
												orgUnitName = b.m_text;
											}
											else if (a.Oid() == OID(L"2.5.4.4"))
											{
												surName = b.m_text;
											}
											else if (a.Oid() == OID(L"2.5.4.42"))
											{
												givenNames = b.m_text;
											}
											else if (a.Oid() == OID(L"2.5.4.12"))
											{
												title = b.m_text;
											}
											else if (a.Oid() == OID(L"1.2.840.113549.1.9.1"))
											{
												eMail = b.m_text; 
											}
											else if (a.Oid() == OID(L"2.5.4.7"))
											{
												localityName = b.m_text; 
											}
											else if (a.Oid() == OID(L"2.5.4.8"))
											{
												stateOrProvinceName = b.m_text; 
											}
											else if (a.Oid() == OID(L"2.5.4.9"))
											{
												streetAddress = b.m_text;
											}
											else if (a.Oid() == OID(L"1.2.643.3.131.1.1"))
											{
												INN = b.m_text; 
											}
											else if (a.Oid() == OID(L"1.2.643.100.1"))
											{
												OGRN = b.m_text; 
											}
											else if (a.Oid() == OID(L"1.2.643.100.3"))
											{
												SNILS = b.m_text;
											}
										}
									}
									else if (element.ChildCount() == 1)
									{
										AsnObject& set1 = element[0]; 
										AsnObject& a = (AsnObject&)set1[0];
										AsnObject& b = (AsnObject&)set1[1];
										if (set1.ChildCount() >= 2) 
										//if (a.Tag() == AsnObject::OBJECT_IDENTIFIER)
										{
											if (a.Oid() == OID(L"2.5.4.3"))
											{
												commonName = b.m_text; 
											}
											else if (a.Oid() == OID(L"2.5.4.10"))
											{
												orgShortName = b.m_text; 
											}
											else if (a.Oid() == OID(L"2.5.4.11"))
											{
												orgUnitName = b.m_text;
											}
											else if (a.Oid() == OID(L"2.5.4.4"))
											{
												surName = b.m_text;
											}
											else if (a.Oid() == OID(L"2.5.4.42"))
											{
												givenNames = b.m_text;
											}
											else if (a.Oid() == OID(L"2.5.4.12"))
											{
												title = b.m_text;
											}
											else if (a.Oid() == OID(L"1.2.840.113549.1.9.1"))
											{
												eMail = b.m_text; 
											}
											else if (a.Oid() == OID(L"2.5.4.7"))
											{
												localityName = b.m_text; 
											}
											else if (a.Oid() == OID(L"2.5.4.8"))
											{
												stateOrProvinceName = b.m_text; 
											}
											else if (a.Oid() == OID(L"2.5.4.9"))
											{
												streetAddress = b.m_text;
											}
											else if (a.Oid() == OID(L"1.2.643.3.131.1.1"))
											{
												INN = b.m_text; 
											}
											else if (a.Oid() == OID(L"1.2.643.100.1"))
											{
												OGRN = b.m_text; 
											}
											else if (a.Oid() == OID(L"1.2.643.100.3"))
											{
												SNILS = b.m_text;
											}
										}
									}
								}
							}
							//
							try
							{
								if (driveLetter.Left(_W("_CryptoPro").GetLength()) != L"_CryptoPro")
								{
									auto reqPaths = Machine::ListFiles(paths[k], _T("*-x.der"));
									if (reqPaths.Length() > 0)
									{
										string reqPath = reqPaths[0];
										//
										File f;
										f.OpenToRead(_S(reqPath));
										Blob reqData = f.ReadAll();
										f.Close();
										//
										AsnObject reqO(reqData);
										AsnObject& o_1 = (AsnObject&)reqO[1];
										//
										//
										for (int k = 0; k < o_1.ChildCount(); k++)
										{
											AsnObject& pair = ((AsnObject&)o_1[k])[0];
											string oid1 = ((AsnObject&)pair[0]).Oid();
											string val1 = ((AsnObject&)pair[1]).m_text;
											extra[oid1] = val1;
										}
									}
								}
							}
							catch (...)
							{
							}
						}
						
						
						
						//
						if (surName.GetLength() > 0)
						{
							commonName = surName;
							if (givenNames.GetLength() > 0)
								commonName = commonName + L" " + givenNames; 
						}
						//
						string m1 = L"";
						for (Map<string,string>::Iterator i(extra); i; ++i)
						{
							string name = i.Id();
							string value = i;
							value = escapeJSON(std::wstring((const wchar_t*)value)).c_str(); 
							//
							m1 += string(L", \"") + name + "\": \"" + value + L"\""; 
						}
						//
						//
						//
						char certInstalledS[64];
						sprintf(certInstalledS,"%d",certInstalled); 
						//
						string s = L"{\"pkh\": \"" + pkh + 
							"\", \"driveLetter\": \"" + driveLetter + 
							"\", \"keyTime\": \"" + time_s + 
							"\", \"certInstalled\": \"" + certInstalledS + 
							"\", \"f2015\": \"" + f2015 + 
							"\", \"serialNumber\": \"" + serialNumber + 
							"\", \"commonName\": \"" + escapeJSONf(commonName) +
							"\", \"surName\": \"" + surName +
							"\", \"givenName\": \"" + givenNames +
							"\", \"notBefore\": \"" + notBefore +
							"\", \"notAfter\": \"" + notAfter + 
							"\", \"localityName\": \"" + localityName + 
							"\", \"streetAddress\": \"" + escapeJSONf(streetAddress) +
							"\", \"stateOrProvinceName\": \"" + stateOrProvinceName +
							"\", \"eMail\": \"" + eMail + 
							"\", \"orgShortName\": \"" + escapeJSONf(orgShortName) +
							"\", \"orgUnit\": \"" + escapeJSONf(orgUnitName) +
							"\", \"title\": \"" + escapeJSONf(title) +
							"\", \"INN\": \"" + INN +
							"\", \"OGRN\": \"" + OGRN + 
							"\", \"SNILS\": \"" + SNILS +
							"\"" + m1 + "}"
							; 
						if (commonName.GetLength() > 0)
						{
							if (index > 0) cnt += ", ";
							cnt += s;
						}
						//
						index++; 
					}
					catch(...)
					{
						// just skipping a bad key 
					}
				}
				//
				return cnt; 
			}
			_Catch() 
		}

		inline static SharedArray<string> ListCertsCryptoPro()
		{
			try
			{
				SharedArray<string> certIds;
				//			
				HCERTSTORE       hCertStore;
				PCCERT_CONTEXT   pCertContext = NULL;
				char pszNameString[256];
				char pszStoreName[256];
				void*            pvData;
				DWORD            cbData;
				DWORD            dwPropId = 0;

				return certIds;
			}
			_Catch()
		}

		//inline static string GetKeysJSONListCnt_CryptoPro(const string& driveLetter, 
		//	const string& compareToPkh = L"")
		//{
		//	try
		//	{


		//		//return L"{\"test\": \"5\"}";
		//		//auto certIds = ListCertsCryptoPro();
		//		//for (int i = 0, index = 0; i < certIds.GetSize(); i++) {}

		//		HCERTSTORE       hCertStore;
		//		PCCERT_CONTEXT   pCertContext = NULL;
		//		wchar_t pszNameString[256];
		//		wchar_t pszStoreName[256];
		//		void*            pvData;
		//		DWORD            cbData;
		//		DWORD            dwPropId = 0;

		//		//LPTSTR      pszProvName = NULL;
		//		wchar_t pbProvName[1024];
		//		DWORD cbProvName = 1000;

		//		string cnt = L"";
		//		int index = 0;

		//		memset(pbProvName, 0, 1000);

		//		// ��������� ����� ���������� �� ���������.
		//		if (CryptGetDefaultProvider(
		//			PROV_GOST_2001_DH, // PROV_GOST_2012_256
		//			NULL,
		//			CRYPT_MACHINE_DEFAULT,
		//			pbProvName,
		//			&cbProvName))
		//		{
		//		}
		//		else
		//		{
		//			//throw MethodError("The store was not opened.");
		//			return L"{\"error\": \"cannot load provider\"}";
		//		}

		//		if (hCertStore = CertOpenSystemStore(
		//			NULL,
		//			L"MY"))
		//		{
		//			//fprintf(stderr, "The %s store has been opened. \n",
		//			//	pszStoreName);
		//		}
		//		else
		//		{
		//			//throw MethodError("The store was not opened.");
		//			return L"{\"error\": \"cannot open store\"}";
		//		}

		//		// pCertContext = NULL;

		//		while (pCertContext = CertEnumCertificatesInStore(
		//			hCertStore,
		//			pCertContext))
		//		{
		//			if (CertGetNameString(
		//				pCertContext,
		//				CERT_NAME_SIMPLE_DISPLAY_TYPE,
		//				0,
		//				NULL,
		//				pszNameString,
		//				128))
		//			{
		//				//printf("\nCertificate for %s \n", pszNameString);
		//			}
		//			else
		//			{
		//				//fprintf(stderr, "CertGetName failed. \n");
		//				continue;
		//			}

		//			string certId; // = certIds[i];

		//			string pkh = certId, m1, certInstalledS = L"1";

		//			string f2015 = L"1";
		//			//
		//			string surName = L"";
		//			string givenNames = L"";
		//			string commonName = L""; // no CN 
		//			string eMail = L"";
		//			string localityName = L"";
		//			string stateOrProvinceName = L"";
		//			string streetAddress = L"";
		//			string orgShortName = L"";
		//			string orgUnitName = L"";
		//			string title = L"";
		//			string serialNumber = L"";
		//			string notBefore, notAfter;
		//			string INN = L"";
		//			string OGRN = L"";
		//			string SNILS = L"";
		//			// 
		//			string algS = L"";
		//			string keyS = L"";
		//			string time_s = L"";

		//			try
		//			{
		//				commonName = string(pszNameString);

		//				Blob certData;
		//				certData.Allocate(pCertContext->cbCertEncoded);
		//				CopyMemory(certData.GetBuffer(),
		//					pCertContext->pbCertEncoded, pCertContext->cbCertEncoded);

		//				parseCert(certData,
		//					surName,
		//					givenNames,
		//					commonName, // no CN 
		//					eMail,
		//					localityName,
		//					stateOrProvinceName,
		//					streetAddress,
		//					orgShortName,
		//					orgUnitName,
		//					title,
		//					serialNumber,
		//					notBefore,
		//					notAfter,
		//					INN,
		//					OGRN,
		//					SNILS);

		//				/*
		//				while (dwPropId = CertEnumCertificateContextProperties(
		//					pCertContext, // The context whose properties are to be listed.
		//					dwPropId))    // Number of the last property found.  
		//								  // This must be zero to find the first 
		//								  // property identifier.
		//				{
		//					//-------------------------------------------------------------------
		//					// When the loop is executed, a property identifier has been found.
		//					// Print the property number.

		//					printf("Property # %d found->", dwPropId);

		//					//-------------------------------------------------------------------
		//					// Indicate the kind of property found.

		//					switch (dwPropId)
		//					{
		//					case CERT_FRIENDLY_NAME_PROP_ID:
		//					{
		//						printf("Display name: ");
		//						break;
		//					}
		//					//case CERT_SIGNATURE_HASH_PROP_ID:
		//					//{
		//					//	printf("Signature hash identifier ");
		//					//	break;
		//					//}
		//					//case CERT_KEY_PROV_HANDLE_PROP_ID:
		//					//{
		//					//	printf("KEY PROVE HANDLE");
		//					//	break;
		//					//}
		//					//case CERT_KEY_PROV_INFO_PROP_ID:
		//					//{
		//					//	printf("KEY PROV INFO PROP ID ");
		//					//	break;
		//					//}
		//					DWORD cbData;
		//					char* pbData;
		//					case CERT_SHA1_HASH_PROP_ID:
		//					{
		//						// printf("SHA1 HASH identifier");
		//						if (CertGetCertificateContextProperty(
		//							pCertContext,
		//							dwPropId,
		//							NULL,
		//							&cbData))
		//						{
		//							pbData = new char[cbData + 1];
		//							if (CertGetCertificateContextProperty(
		//								pCertContext,
		//								dwPropId,
		//								pbData,
		//								&cbData))
		//							{
		//								pbData[cbData] = 0;
		//								Blob a;
		//								a.Allocate(cbData);
		//								CopyMemory(a.GetBuffer(), pbData, cbData);
		//								pkh = __ToBase64(a);
		//							}
		//						}
		//					}
		//					}
		//				}
		//				*/

		//				string s = L"{\"pkh\": \"" + pkh +
		//					"\", \"driveLetter\": \"" + driveLetter +
		//					"\", \"keyTime\": \"" + time_s +
		//					"\", \"certInstalled\": \"" + certInstalledS +
		//					"\", \"f2015\": \"" + f2015 +
		//					"\", \"serialNumber\": \"" + serialNumber +
		//					"\", \"commonName\": \"" + escapeJSONf(commonName) +
		//					"\", \"surName\": \"" + surName +
		//					"\", \"givenName\": \"" + givenNames +
		//					"\", \"notBefore\": \"" + notBefore +
		//					"\", \"notAfter\": \"" + notAfter +
		//					"\", \"localityName\": \"" + localityName +
		//					"\", \"streetAddress\": \"" + escapeJSONf(streetAddress) +
		//					"\", \"stateOrProvinceName\": \"" + stateOrProvinceName +
		//					"\", \"eMail\": \"" + eMail +
		//					"\", \"orgShortName\": \"" + escapeJSONf(orgShortName) +
		//					"\", \"orgUnit\": \"" + escapeJSONf(orgUnitName) +
		//					"\", \"title\": \"" + escapeJSONf(title) +
		//					"\", \"INN\": \"" + INN +
		//					"\", \"OGRN\": \"" + OGRN +
		//					"\", \"SNILS\": \"" + SNILS +
		//					"\"" + m1 + "}"
		//					;
		//				if (index > 0) cnt += ", ";
		//				cnt += s;
		//				index++;
		//			}
		//			catch (...)
		//			{
		//				// just skipping a bad key 
		//			}
		//		}
		//		//
		//		return cnt;
		//	}
		//	_Catch()
		//}

		inline static string GetCommonKeyInfoJSON(const string& compareToPkh=L"") 
		{
			try
			{
				SharedArray<string> drives = GetKeyDrives(); // Machine::ListDrives(DRIVE_REMOVABLE);  
				// drives.Add(L"k"); 
				//
				string s = L"[";
				//
				for (int i = 0, index = 0; i < drives.GetSize(); i++)
				{
					string driveLetter = drives[i]; 
					string cnt = GetKeysJSONListCnt(driveLetter, compareToPkh); 
					if (cnt.Trim().GetLength() > 0)
					{
						if (index > 0) s += ", ";
						s += cnt;
						index++;
					}
				}
				//
				s += L"]";
				//
				return s;
			}
			_Catch() 
		}

		inline static SharedArray<string> SearchKey(const string& pkhToSearch, 
			const string& driveLetter = L"")
		{			
			try
			{
				string drive1, pkh1, path1, kpath1, root1, name1, keyTime;
				Blob reqData, certData;
				//
				SharedArray<string> paths;
				SharedArray<string> roots;
				SharedArray<string> names;
				//
				bool fExcludeCryptoPro = true;
				//
				if (driveLetter.Left(_W(L"_CryptoPro").GetLength()) != L"_CryptoPro")
				{
					SharedArray<CString> drives = GetKeyDrives();
					for (int i = 0; i < drives.GetSize(); i++)
					{
						string drive = drives[i];
						if (driveLetter != L"")
						{
							if (drive != driveLetter)
								continue;
						}
						//
						if (fExcludeCryptoPro)
						{
							if (drive.Left(_W(L"_CryptoPro").GetLength()) == L"_CryptoPro")
								continue;
						}
						//
						SharedArray<CString> keys = GetKeys(drive, &paths, &roots, &names);
						for (int k = 0; k < keys.GetSize(); k++)
						{
							string pkh = keys[k];
							if (pkhToSearch == pkh)
							{
								drive1 = drive;
								pkh1 = pkh;
								path1 = paths[k];
								root1 = roots[k];
								name1 = names[k];
								//
								SharedArray<CString> kPaths = Machine::ListFiles(path1, _T("*-k.xml"));
								//if (kPaths.Length() > 0) 
								kpath1 = _W(kPaths[0]);
							}
						}
					}
				}
				//
				if (pkh1.GetLength() == 0 && (driveLetter == L"_CryptoPro" || 
					driveLetter == L"_CryptoPro2012_256" || driveLetter == L"_CryptoPro2012_512")
					|| driveLetter == L"")
				{
					// Searching in CryptoPro
					//
					CString pkhSearchStr = _S(__ToBase64(FromBase64String(pkhToSearch)));
					//
					SharedArray<CString> keyContainers = Machine::ListRegKeys(
						HKEY_CURRENT_USER,
						_S("Software\\\\Cabinet\\LK\\Containers")
						);
					//
					for (int k = 0; k < keyContainers.GetSize(); k++)
					{
						CString containerName = keyContainers[k];
						//
						try
						{
							CString pkhStr = Machine::GetRegStringValue(
								HKEY_CURRENT_USER,
								_S("Software\\\\Cabinet\\LK\\Containers\\") + containerName,
								_S("pkh"), false
								);
							keyTime = _W(Machine::GetRegStringValue(
								HKEY_CURRENT_USER,
								_S("Software\\\\Cabinet\\LK\\Containers\\") + containerName,
								_S("key-time"), false
								));
							string drive2 = _W(Machine::GetRegStringValue(
								HKEY_CURRENT_USER,
								_S("Software\\\\Cabinet\\LK\\Containers\\") + containerName,
								_S("drive"), false
								));
							//
							if (pkhStr.GetLength() > 0 && keyTime.GetLength() > 0)
							{
								CString pkh1Str = _S(__ToBase64(FromBase64String(pkhStr)));
								//
								try
								{
									reqData = Machine::GetRegBinaryValue(
										HKEY_CURRENT_USER,
										_S("Software\\\\Cabinet\\LK\\Containers\\") + containerName,
										_S("0"), false
										);
									certData = Machine::GetRegBinaryValue(
										HKEY_CURRENT_USER,
										_S("Software\\\\Cabinet\\LK\\Containers\\") + containerName,
										_S("1"), false
										);
								}
								catch (...)
								{
								}
								//
								if (pkh1Str == pkhSearchStr)
								{
									drive1 = drive2;
									pkh1 = pkh1Str;
									path1 = L"";
									root1 = L"CryptoPro";
									name1 = containerName;
									break;
								}
							}
						}
						catch (...)
						{
						}
					}
				}
				//
				SharedArray<string> data; 
				data.Add(drive1);
				data.Add(pkh1);
				data.Add(path1);
				data.Add(kpath1); 
				data.Add(root1); 
				data.Add(name1); 
				if (reqData.Length() > 0)
				{
					data.Add(__ToBase64(reqData));
					if (certData.Length() > 0)
					{
						data.Add(__ToBase64(certData));
					}
					else
						data.Add(L"");
				}
				else
				{
					data.Add(L"");
					data.Add(L"");
				}
				data.Add(keyTime);
				return data; 
			}
			_Catch() 
		}

		inline static void InstallCertificate(const string& certificate64, 
			const string& pkh64)
		{			
			try
			{
				Blob pkh = FromBase64String(pkh64); 
				Blob certificate = FromBase64String(certificate64); 
				//
				SharedArray<string> data = SearchKey(pkh64);
				string driveLetter = data[0];
				//
				if (driveLetter.Left(string(L"_CryptoPro").GetLength()) != L"_CryptoPro")
				{
					SharedArray<string> m = SearchKey(pkh64);
					//
					if (m[2].GetLength() == 0)
					{
						throw MethodError(L"�������� ��������� �� ������");
					}
					//
					string path1 = m[2];
					//
					CString certPath = _S(path1) + _T("\\client.cer");
					//
					File f;
					f.OpenToWrite(certPath);
					f.Replace((char*)certificate.GetBuffer(), certificate.Length());
					f.Close();
				}
				else // Crypto Pro
				{
					SharedArray<string> m = SearchKey(pkh64);
					//
					string containerName = m[5];
					wchar_t containerNameB[1024];
					for (int j = 0; j < containerName.GetLength(); j++)
						containerNameB[j] = containerName[j];
					containerNameB[containerName.GetLength()] = 0;

					Machine::SetRegBinaryValue(HKEY_CURRENT_USER,
						_S("Software\\\\Cabinet\\LK\\Containers\\") + _S(containerName),
						_S("1"),
						certificate
						);
					//
					HCERTSTORE hCertStore;
					PCCERT_CONTEXT pCertContext;
					//
					if (hCertStore = CertOpenSystemStore(
						NULL,
						L"MY"))
					{
						PCCERT_CONTEXT pCertContext = CertCreateCertificateContext(
							X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
							certificate.GetBuffer(),
							certificate.GetSize());

						int providerType = 75; // 2012  !!!!!!!!

						CRYPT_KEY_PROV_INFO providerInfo;
						memset(&providerInfo, 0, sizeof(providerInfo));
						providerInfo.pwszContainerName = containerNameB;
						providerInfo.dwProvType = providerType;
						providerInfo.dwKeySpec = AT_KEYEXCHANGE;

						// ------------------------------------------------------------------ 
						// 4.) Associate the container with our certificate
						if (!CertSetCertificateContextProperty(pCertContext, CERT_KEY_PROV_INFO_PROP_ID, 0, &providerInfo))
						{
							throw MethodError(L"Installing certificate: error 1");
						}

						// ------------------------------------------------------------------ 
						// 5.) Get access to container
						HCRYPTPROV hCryptProv = NULL;
						if (!CryptAcquireContext(
							&hCryptProv,                 // handle to the CSP
							(const wchar_t*)containerName,                  // container name 
							NULL,                        // use the default provider
							providerType,                // provider type
							0)							 // flag values
							)
						{
							throw MethodError(L"Installing certificate: error 2");
						}

						// ------------------------------------------------------------------ 
						// 6.) Get key
						HCRYPTKEY hKey = NULL;
						if (!CryptGetUserKey(hCryptProv, AT_KEYEXCHANGE, &hKey))
						{
							throw MethodError(L"Installing certificate: error 3");
						}

						// ------------------------------------------------------------------ 
						// 7.) Map key and certificate.
						if (!CryptSetKeyParam(
							hKey,
							KP_CERTIFICATE,
							certificate.GetBuffer(),
							0))
						{
							throw MethodError(L"Installing certificate: error 4");
						}

						// ------------------------------------------------------------------ 
						// 8.) Add certificate to store.

						if (!CertAddCertificateContextToStore(hCertStore, pCertContext, CERT_STORE_ADD_ALWAYS, 0))
						{
							throw MethodError(L"Installing certificate: error 5");
						}



						// PCCERT_CONTEXT *ppStoreContext;

						//if (!CertAddCertificateContextToStore(
						//	hCertStore,
						//	pCertContext,
						//	0,
						//	NULL
						//	))
						//{

						//}
						//else
						//{
						//	throw MethodError(L"Cannot add certificate");
						//}
					}
					else
					{
						throw MethodError(L"Cannot open store");
					}

				}
			}
			_Catch() 
		}

		inline static string RemoveKey(const string& pkh64)
		{			
			try
			{
				Blob pkh = FromBase64String(pkh64); 
				// 
				SharedArray<string> m = SearchKey(pkh64); 
				//
				string path1 = m[2], root1 = m[4], name1 = m[5]; 
				string arcRoot = root1 + L"\\_archive"; 
				string arcPath = arcRoot + L"\\" + name1; 
				string arcContainer = arcPath + L"\\Container"; 
				//
				CreateDirectoryW(arcRoot, 0); 
				CreateDirectoryW(arcPath, 0); 
				CreateDirectoryW(arcContainer, 0); 
				//
				// Copying... 
				//
				SharedArray<CString> fileNames; 
				SharedArray<CString> a = Machine::ListFiles(path1,_T("*.*"),&fileNames); 
				for (int k = 0; k < a.Length(); k++) 
				{
					CString path = a[k];   
					CString fileName = fileNames[k]; 
					CopyFileW(path, arcPath + L"\\" + fileName, true); 
				}
				//
				SharedArray<CString> fileNames2; 
				a = Machine::ListFiles(path1 + _T("\\Container"),_T("*.*"),&fileNames2);
				for (int k = 0; k < a.Length(); k++) 
				{
					CString path = a[k];   
					CString fileName = fileNames2[k]; 
					CopyFileW(path, arcContainer + L"\\" + fileName, true); 
				}
				//
				a = Machine::ListFiles(arcPath,_T("*.xml"));
				if (a.Length() == 0) return L"{\"error\":\"no files in archive\"}"; 
				//
				RemoveKeyFromDisk(pkh64);   
				//
				return L"{\"msg\":\"" + arcPath + L"\"}"; 
			}
			_Catch() 
		}

		inline static void RemoveKeyFromDisk(const string& pkh64)
		{			
			try
			{
				Blob pkh = FromBase64String(pkh64); 
				// 
				SharedArray<string> m = SearchKey(pkh64); 
				//
				string path1 = m[2];
				//
				CString certPath = _S(path1) + _T("\\client.cer"); 
				//
				DeleteFileW(_W(certPath)); 
				//
				// Keys 
				//
				SharedArray<CString> pkXmlPaths = Machine::ListFiles(path1,_T("*-k.xml"));
				if (pkXmlPaths.Length() > 0) 
				{
					CString pkXmlPath = pkXmlPaths[0];
					if (pkXmlPath.GetLength() >= 5) DeleteFileW(_W(pkXmlPath));   
				}
				pkXmlPaths = Machine::ListFiles(path1,_T("*.der"));
				for (int k = 0; k < pkXmlPaths.Length(); k++) 
				{
					CString path = pkXmlPaths[k];   
					if (path.GetLength() >= 5) DeleteFileW(_W(path));   
				}
				SharedArray<CString> a = Machine::ListFiles(path1 + _T("\\Container"),_T("*.*"));
				for (int k = 0; k < a.Length(); k++) 
				{
					CString path = a[k];   
					if (path.GetLength() >= 5) DeleteFileW(_W(path));   
				}
				if (path1.GetLength() >= 6)
				{
					RemoveDirectoryW(path1 + _W("\\Container")); 
					RemoveDirectoryW(path1); 
				}
			}
			_Catch() 
		}

		inline static void RemoveCertificate(const string& pkh64)
		{			
			try
			{
				Blob pkh = FromBase64String(pkh64); 
				// 
				SharedArray<string> m = SearchKey(pkh64); 
				//
				string path1 = m[2];
				//
				CString certPath = _S(path1) + _T("\\client.cer"); 
				//
				DeleteFileW(_W(certPath));
			}
			_Catch() 
		}

		inline static string GetCertificate(const string& pkh64)
		{			
			try
			{
				SharedArray<string> m = SearchKey(pkh64);
				string driveLetter = m[0];
				string pkh_ = m[1];
				if (pkh_ == L"")
					return L"";
				//
				if (driveLetter.Left(_W(L"_CryptoPro").GetLength()) == L"_CryptoPro")
				{
					string s1 = m[7];
					if (s1 != L"")
						return s1;
					return L""; // GetCertificateInStoreMy(pkh64);
				}
				//
				Blob pkh = FromBase64String(pkh64); 
				// 
				// SharedArray<string> m = SearchKey(pkh64); 
				//
				string path1 = m[2];
				//
				CString certPath = _S(path1) + _T("\\client.cer"); 
				//
				File f;
				f.OpenToRead(certPath); 
				Blob certificate = f.ReadAll(); 
				f.Close();
				//
				string certificate64 = __ToBase64(certificate); 
				// 
				return certificate64; 
			}
			_Catch() 
		}

		//inline static string GetCertificateInStoreMy(const string& pkh64)
		//{
		//	try
		//	{
		//		Blob pkh = FromBase64String(pkh64);
		//		// 
		//		SharedArray<string> m = SearchKey(pkh64);
		//		//
		//		string containerName = m[5];
		//		//
		//		Blob certificate;
		//		//
		//		string certificate64 = __ToBase64(certificate);
		//		// 
		//		return certificate64;
		//	}
		//	_Catch()
		//}

		inline static string GetToken(const string& s, int p, int* newPos)
		{
			int p1 = s.Find(L"\"", p); 
			if (p1 == -1) { *newPos = -1; return L""; } 
			int p2 = s.Find(L"\"", p1+1); 
			if (p2 == -1) { *newPos = -1; return L""; } 
			//
			*newPos = p2+1;
			return s.Mid(p1+1, p2-p1-1); 
		}

		inline static SharedArray<string> ParseDN(const string& dNameMap)
		{
			try
			{
				int p00 = dNameMap.Find(L"{");
				int p01 = dNameMap.Find(L"}");
				if ((p00 == -1) || (p01 == -1)) 
				{
					throw MethodError(L"�������� ������"); 
				}
				//
				SharedArray<string> m;
				//
				string mapStr = dNameMap.Mid(p00+1, p01-p00-1);
				int p = 0; 
				p = mapStr.Find(L"\""); 
				while (p != -1)
				{
					int newPos = 0, newPos2 = 0;
					string key = GetToken(mapStr, p, &newPos); 
					if (newPos == -1) break; 
					string value = GetToken(mapStr, newPos, &newPos2); 
					if (newPos2 == -1) break; 
					//
					m.Add(key).Add(value); 
					//
					p = mapStr.Find(L"\"", newPos2); 
				}
				//
				return m; 
			}
			_Catch() 
		}

		inline static string GetDNElement(SharedArray<string>& m, const string& key) 
		{
			try
			{
				int n = m.Length() / 2;
				//
				for (int k = 0; k < n; k++)
				{
					string name = m[2*k]; 
					if (name == key)
					{
						return (string)(m[2*k+1]); 
					}
				}
				throw MethodError(string(L"������� ") + key + L" �� ������"); 
			}
			_Catch() 
		}

		inline static bool DNElementProvided(SharedArray<string>& m, const string& key) 
		{
			try
			{
				int n = m.Length() / 2;
				//
				for (int k = 0; k < n; k++)
				{
					string name = m[2*k]; 
					if (name == key)
					{
						return true; 
					}
				}
				return false; 
			}
			_Catch() 
		}







	inline static string escapeJSONf(const string& input)
	{
		return string(escapeJSON(input.GetString()).c_str());
	}

	inline static std::string escapeJSON(const std::string& input)
	{
		std::string output;
		output.reserve(input.length());

		for (std::string::size_type i = 0; i < input.length(); ++i)
		{
			switch (input[i]) {
				case '"':
					output += "\\\"";
					break;
				case '/':
					output += "\\/";
					break;
				case '\b':
					output += "\\b";
					break;
				case '\f':
					output += "\\f";
					break;
				case '\n':
					output += "\\n";
					break;
				case '\r':
					output += "\\r";
					break;
				case '\t':
					output += "\\t";
					break;
				case '\\':
					output += "\\\\";
					break;
				default:
				{
					char sym = input[i];
					if ((sym >= 'a' && sym <= 'z') || (sym >= 'A' && sym <= 'Z') || 
						(sym >= '0' && sym <= '9') ||
						sym == '-' || sym == '_' || true)
						output += sym;
					else
					{
					}
					break;
				}
			}

		}

		return output;
	}

	inline static std::string escapeJSONX(const std::string& input)
	{
		std::string output;
		output.reserve(input.length());

		for (std::string::size_type i = 0; i < input.length(); ++i)
		{
			switch (input[i]) {
				case '"':
					output += "\\\"";  
					break;
				case '/':
					output += "\\/";
					break;
				case '\b':
					output += "\\b";
					break;
				case '\f':
					output += "\\f";
					break;
				case '\n':
					//output += "\\n";
					break;
				case '\r':
					//output += "\\r";
					break;
				case '\t':
					output += "\\t";
					break;
				case '\\':
					output += "\\\\";
					break;
				default:
					output += input[i];   
					break;
			}

		}

		return output;
	}

	inline static std::wstring escapeJSON(const std::wstring& input)
	{
		std::string a = (const char*)_A(input.c_str()); 
		return std::wstring((const wchar_t*)_W(
			escapeJSON(a).c_str()   
			)); 
	}

	inline static std::wstring escapeJSONX(const std::wstring& input)
	{
		std::string a = (const char*)_A(input.c_str()); 
		return std::wstring((const wchar_t*)_W(
			escapeJSONX(a).c_str()   
			)); 
	}












	inline static string CreateSimpleSignature64(
		const string& pkh64, const string& pwd,
		const string& cn, const string& org, 
		Blob dataToSign) 
	{
		try
		{
			// string plk64 = __ToBase64(pkh); 
			SharedArray<string> a = SearchKey(pkh64); 
			//
			string driveLeter = a[0];
			string path1 = a[2]; 
			string kpath1 = a[3]; 
			//
			if (driveLeter.Left(_W(L"_CryptoPro").GetLength()) == L"_CryptoPro")
			{
				return CreateSimpleSignature64_CryptoPro(pkh64, pwd, cn, org, dataToSign);
			}
			// 
			CCOM_KeyObject key; 
			XmlDocument d; 
			d.Load(kpath1);
			key.SetPath(path1 + L"\\Container");
			key.SetCommonName(cn); 
			key.SetOrgName(org);
			key.SetPassword(pwd); 
			try
			{
				key.SetXmlInfo(d.DocumentElement());
			}
			catch(::::Exception& e)
			{
				throw MethodError(L"������ ������ �����, ���� �������� ������"); 
			}
			//
			string s; 
			//
			try
			{
				s = __ToBase64(key.CreateRawSignature(dataToSign, 0, Blob())); 
			}
			catch(::::Exception& e)
			{
				throw MethodError(L"������ ������������ ���"); 
			}
			s = _W(escapeJSONX(std::wstring((const wchar_t*)s)).c_str());   
			//
			return s; 
		}
		_Catch()
	}

	inline static string CreateSimpleSignature64_CryptoPro(
		const string& pkh64, const string& pwd,
		const string& cn, const string& org,
		Blob dataToSign)
	{
		try
		{
			SharedArray<string> a = SearchKey(pkh64);
			//
			string driveLeter = a[0];
			string path1 = a[2];
			string kpath1 = a[3];
			string containerName = a[5];
			//
			HCRYPTPROV hProv = 0;
			if (driveLeter == L"_CryptoPro")
			{
				if (!CryptAcquireContext(
					&hProv,
					containerName,
					NULL,
					PROV_GOST_2001_DH,
					0))
				{
					throw MethodError(L"������ �������� ����������: " + containerName);
				}
			}
			else if (driveLeter == L"_CryptoPro2012_256")
			{
				if (!CryptAcquireContext(
					&hProv,
					containerName,
					NULL,
					PROV_GOST_2012_256,
					0))
				{
					throw MethodError(L"������ �������� ����������: " + containerName);
				}
			}
			else if (driveLeter == L"_CryptoPro2012_512")
			{
				if (!CryptAcquireContext(
					&hProv,
					containerName,
					NULL,
					PROV_GOST_2012_256, // %!% // PROV_GOST_2012_512,
					0))
				{
					throw MethodError(L"������ �������� ����������: " + containerName);
				}
			}
			if (!hProv)
				throw MethodError(L"������ �������� ���������� (0): " + containerName);
			//
			HCRYPTKEY hKey = 0;
			HCRYPTHASH hHash = 0;
			if (!CryptGetUserKey(
				hProv,
				AT_KEYEXCHANGE,
				&hKey))
			{
				throw MethodError(L"������ �������� ����� �������: " + containerName);
			}
			//
			ALG_ID algId = CALG_GR3411;
			//
			if (driveLeter == L"_CryptoPro2012_256")
				algId = CALG_GR3411_2012_256;
			if (driveLeter == L"_CryptoPro2012_512")
				algId = CALG_GR3411_2012_256; // %!% // CALG_GR3411_2012_512;
			//
			if (!CryptCreateHash(
				hProv,
				algId,
				0,
				0,
				&hHash))
			{
				throw MethodError(L"������ ����������� (0)");
			}
			//
			// ��������� ��������� HP_OID.
			//
			DWORD cbHash = 1024;
			BYTE pbHash[1024];
			if (!CryptGetHashParam(hHash,
				HP_OID,
				NULL,
				&cbHash,
				0))
			{
				throw MethodError(L"������ ����������� (1)");
			}
			//
			// ����������� ��������� HP_OID � pbHash.
			if (!CryptGetHashParam(hHash,
				HP_OID,
				pbHash,
				&cbHash,
				0))
			{
				throw MethodError(L"������ ����������� (2)");
			}
			//
			//if (CryptSetHashParam(
			//	hHash,
			//	HP_OID,
			//	pbHash,
			//	0))
			//{
			//	throw MethodError(L"������ ����������� (1)");
			//}
			//
			// ���������� ������������������ ���� ������.
			//
			if (!CryptHashData(
				hHash,
				dataToSign.GetBuffer(),
				dataToSign.GetSize(),
				0))
			{
				throw MethodError(L"������ ����������� (3)");
			}
			//
			DWORD dwSigLen = 32 * 1024;
			BYTE pbSignature[32 * 1024];
			if (!CryptSignHash(
				hHash,
				AT_KEYEXCHANGE,
				NULL,
				0,
				NULL,
				&dwSigLen))
			{
				throw MethodError(L"������ ������� (1)");
			}
			//
			if (!CryptSignHash(
				hHash,
				AT_KEYEXCHANGE,
				NULL,
				0,
				pbSignature,
				&dwSigLen))
			{
				throw MethodError(L"������ ������� (2)");
			}
			//
			Blob sig;
			sig.Allocate(dwSigLen);
			CopyMemory(sig.GetBuffer(), pbSignature, dwSigLen);
			auto s = __ToBase64(sig);
			s = _W(escapeJSONX(std::wstring((const wchar_t*)s)).c_str());
			return s;
			//
			/*
			//--------------------------------------------------------------------
			// �������� �������� �������.
			//
			if (CryptVerifySignature(
				hHash,
				pbSignature,
				dwSigLen,
				hPubKey,
				NULL,
				0))
			{
				printf("The signature has been verified.\n");
			}
			else
			{
				printf("Signature not validated!\n");
			}





			//
			if (driveLeter == L"_CryptoPro")
			{
				return CreateSimpleSignature64_CryptoPro(pkh64, pwd, cn, org, dataToSign);
			}
			// 
			CCOM_KeyObject key;
			XmlDocument d;
			d.Load(kpath1);
			key.SetPath(path1 + L"\\Container");
			key.SetCommonName(cn);
			key.SetOrgName(org);
			key.SetPassword(pwd);
			try
			{
				key.SetXmlInfo(d.DocumentElement());
			}
			catch (::::Exception& e)
			{
				throw MethodError(L"������ ������ �����, ���� �������� ������");
			}
			//
			string s;
			//
			try
			{
				s = __ToBase64(key.CreateRawSignature(dataToSign, 0, Blob()));
			}
			catch (::::Exception& e)
			{
				throw MethodError(L"������ ������������ ���");
			}
			s = _W(escapeJSONX(std::wstring((const wchar_t*)s)).c_str());
			//
			return s;
			*/
		}
		_Catch()
	}

	inline static string CreateSimpleSignature64_CryptoPro_Digest(
		const string& pkh64, const string& pwd,
		const string& cn, const string& org,
		Blob digest)
	{
		try
		{
			SharedArray<string> a = SearchKey(pkh64);
			//
			string driveLeter = a[0];
			string path1 = a[2];
			string kpath1 = a[3];
			string containerName = a[5];
			//
			HCRYPTPROV hProv = 0;
			if (driveLeter == L"_CryptoPro")
			{
				if (!CryptAcquireContext(
					&hProv,
					containerName,
					NULL,
					PROV_GOST_2001_DH,
					0))
				{
					throw MethodError(L"������ �������� ����������: " + containerName);
				}
			}
			else if (driveLeter == L"_CryptoPro2012_256")
			{
				if (!CryptAcquireContext(
					&hProv,
					containerName,
					NULL,
					PROV_GOST_2012_256,
					0))
				{
					throw MethodError(L"������ �������� ����������: " + containerName);
				}
			}
			else if (driveLeter == L"_CryptoPro2012_512")
			{
				if (!CryptAcquireContext(
					&hProv,
					containerName,
					NULL,
					PROV_GOST_2012_256, // %!% // PROV_GOST_2012_512,
					0))
				{
					throw MethodError(L"������ �������� ����������: " + containerName);
				}
			}
			if (!hProv)
				throw MethodError(L"������ �������� ���������� (0): " + containerName);
			//
			HCRYPTKEY hKey = 0;
			HCRYPTHASH hHash = 0;
			if (!CryptGetUserKey(
				hProv,
				AT_KEYEXCHANGE,
				&hKey))
			{
				throw MethodError(L"������ �������� ����� �������: " + containerName);
			}
			//
			ALG_ID algId = CALG_GR3411;
			//if (!CryptAcquireContext(
			//	&hProv,
			//	containerName,
			//	NULL,
			//	PROV_GOST_2001_DH,
			//	0))
			//{
			//	throw MethodError(L"������ �������� ����������: " + containerName);
			//}
			//
			if (driveLeter == L"_CryptoPro2012_256")
				algId = CALG_GR3411_2012_256;
			if (driveLeter == L"_CryptoPro2012_512")
				algId = CALG_GR3411_2012_256; // %!% // CALG_GR3411_2012_512;
											  //
			//algId = CALG_GR3411; // TODO: %%% !!!
			if (!CryptCreateHash(
				hProv,
				algId,
				0,
				0,
				&hHash))
			{
				throw MethodError(L"������ ����������� (0)");
			}
			//
			// ��������� ��������� HP_OID.
			//
			DWORD cbHash = 1024;
			BYTE pbHash[1024];
			if (!CryptGetHashParam(hHash,
				HP_OID,
				NULL,
				&cbHash,
				0))
			{
				throw MethodError(L"������ ����������� (1)");
			}
			//
			// ����������� ��������� HP_OID � pbHash.
			if (!CryptGetHashParam(hHash,
				HP_OID,
				pbHash,
				&cbHash,
				0))
			{
				throw MethodError(L"������ ����������� (2)");
			}
			//
			BYTE sise1[64];
			DWORD size1n = 64;
			if (!CryptGetHashParam(hHash,
				HP_HASHSIZE,
				sise1,
				&size1n,
				0))
			{
				throw MethodError(L"������ ����������� (2)");
			}
			//
			DWORD dwSize = (DWORD)digest.Length();
			//if (CryptSetHashParam(
			//	hHash,
			//	HP_HASHSIZE,
			//	(const BYTE*)&dwSize,
			//	0))
			//{
			//	throw MethodError(L"������ ����������� (4s)");
			//}
			if (!CryptSetHashParam(
				hHash,
				HP_HASHVAL,
				digest.GetBuffer(),
				0))
			{
				throw MethodError(L"������ ����������� (4)");
			}
			//
			// ���������� ������������������ ���� ������.
			//
			//if (!CryptHashData(
			//	hHash,
			//	dataToSign.GetBuffer(),
			//	dataToSign.GetSize(),
			//	0))
			//{
			//	throw MethodError(L"������ ����������� (3)");
			//}
			//
			DWORD dwSigLen = 32 * 1024;
			BYTE pbSignature[32 * 1024];
			if (!CryptSignHash(
				hHash,
				AT_KEYEXCHANGE,
				NULL,
				0,
				NULL,
				&dwSigLen))
			{
				throw MethodError(L"������ ������� (1)");
			}
			//
			if (!CryptSignHash(
				hHash,
				AT_KEYEXCHANGE,
				NULL,
				0,
				pbSignature,
				&dwSigLen))
			{
				throw MethodError(L"������ ������� (2)");
			}
			//
			Blob sig;
			sig.Allocate(dwSigLen);
			CopyMemory(sig.GetBuffer(), pbSignature, dwSigLen);
			auto s = __ToBase64(sig);
			// s = _W(escapeJSONX(std::wstring((const wchar_t*)s)).c_str());
			return s;
			//
			/*
			//--------------------------------------------------------------------
			// �������� �������� �������.
			//
			if (CryptVerifySignature(
			hHash,
			pbSignature,
			dwSigLen,
			hPubKey,
			NULL,
			0))
			{
			printf("The signature has been verified.\n");
			}
			else
			{
			printf("Signature not validated!\n");
			}





			//
			if (driveLeter == L"_CryptoPro")
			{
			return CreateSimpleSignature64_CryptoPro(pkh64, pwd, cn, org, dataToSign);
			}
			//
			CCOM_KeyObject key;
			XmlDocument d;
			d.Load(kpath1);
			key.SetPath(path1 + L"\\Container");
			key.SetCommonName(cn);
			key.SetOrgName(org);
			key.SetPassword(pwd);
			try
			{
			key.SetXmlInfo(d.DocumentElement());
			}
			catch (::::Exception& e)
			{
			throw MethodError(L"������ ������ �����, ���� �������� ������");
			}
			//
			string s;
			//
			try
			{
			s = __ToBase64(key.CreateRawSignature(dataToSign, 0, Blob()));
			}
			catch (::::Exception& e)
			{
			throw MethodError(L"������ ������������ ���");
			}
			s = _W(escapeJSONX(std::wstring((const wchar_t*)s)).c_str());
			//
			return s;
			*/
		}
		_Catch()
	}




	inline static int findIn(const Blob& pattern, const Blob& b)
	{
		int stop = 0;
		if (pattern.Length() == 0) return -2;
		for (int i = 0; i < b.Length() - pattern.Length(); i++)
		{
			int j;
			for (j = 0; j < pattern.Length(); j++)
			{
				if (pattern[j] != b[i + j])
				{
					if (j > 3)
						stop = 1;
					break;
				}
			}
			//if (j > 98)
			//	return j; 
			if (j >= pattern.Length() - 8)
				return i;
		}
		return -1;
	}

	inline static string CreateCMSSignature64(
		const string& pkh64, const string& pwd
		// , const string& cn, const string& org
		, Blob dataToSign //, string // hashOid
		, bool includeCert = true
		, Blob digest0 = Blob()
		, int* p = 0
		, int* certSize = 0
		)
	{
		try
		{
			Blob m_certificateData;
			CCOM_KeyObject key;
			//
			if (dataToSign.Length() == 0 && digest0.Length() == 0)
			{
				dataToSign.Allocate(1);
				dataToSign[0] = '8';
			}
			//
			SharedArray<string> a = SearchKey(pkh64);
			//
			string driveLetter = a[0];
			//
			//if (driveLetter.Left(_W("_CryptoPro").GetLength()) == L"_CryptoPro")
			//{
			//	//if (digest0.Length() > 0)
			//	//{
			//	//	return CreateSimpleSignature64_CryptoPro_Digest(pkh64, 
			//	//		pwd, L"", L"", digest0);
			//	//}
			//	return CreateCMSSignature64_CADES_CryptoPro(pkh64, pwd,
			//		dataToSign, includeCert, digest0, p, certSize);
			//}
			//
			//if (true)
			//{
			//	HCRYPTPROV hProv;
			//	CryptAcquireContext(&hProv, NULL, NULL, PROV_GOST_2012_256, CRYPT_VERIFYCONTEXT);
			//	HCRYPTHASH hHash;
			//	CryptCreateHash(hProv, CALG_GR3411_2012_256, NULL, 0, &hHash);
			//	::::File f;
			//	f.OpenToRead(_S("D:\\HOME\\WSTA\\15.png"));
			//	Blob data = f.ReadAll();
			//	f.Close();
			//	if (!CryptHashData(hHash, data, data.Length(), 0))
			//	{
			//		throw MethodError(L"������ ����������� (3)");
			//	}
			//	DWORD size = 32;
			//	Blob hashBlob;
			//	hashBlob.Allocate(size);
			//	if (!CryptGetHashParam(hHash, HP_HASHVAL, hashBlob.GetBuffer(), &size, 0))
			//	{
			//		throw MethodError(L"������ ����������� (4)");
			//	}
			//	digest0 = hashBlob;
			//}
			//
			bool g2012 = false;
			if (driveLetter.Left(_W("_CryptoPro").GetLength()) == L"_CryptoPro")
			{
				g2012 = true;
				if (digest0.GetSize() == 0)
				{
					throw MethodError(L"CADES!");
					//return CreateCMSSignature64_CADES_CryptoPro(pkh64, pwd,
					//	dataToSign, includeCert, digest0, p, certSize);
				}
				//
				string s1 = a[7];
				if (s1 == L"")
					throw MethodError(L"��� �����������!");
				m_certificateData = FromBase64String(s1);
			}
			else
			{
				string path1 = a[2];
				string kpath1 = a[3];
				//
				string certPath = path1 + "\\client.cer";
				// 
				XmlDocument d;
				d.Load(kpath1);
				key.SetPath(path1 + L"\\Container");
				//key.SetCommonName(cn);
				//key.SetOrgName(org);
				key.SetPassword(pwd);
				try
				{
					key.SetXmlInfo(d.DocumentElement());
				}
				catch (::::Exception& e)
				{
					throw MethodError(L"������ ������ �����, ���� �������� ������");
				}
				//
				File f;
				f.OpenToRead(_S(certPath));
				m_certificateData = f.ReadAll();
				f.Close();
			}
			//
			if (certSize) *certSize = m_certificateData.Length();
			//
			int j = 0;
			//
			Blob pkh = FromBase64String(pkh64); 
			//
			AsnObject cert_O = AsnObject::NewSequence();
			try
			{
				cert_O = AsnObject(m_certificateData);
			}
			catch (::::Exception e)
			{
#				ifdef _DEBUG
				try
				{
					TRACE_LOG(_T("!!!\n������ ��� ������� ����������� (CMS64)\n!!!"));
					TRACE_LOG1(_T("Length: %d"), (int)m_certificateData.Length());
					//File f;
					//f.Open(_T("D:\\___error-cer.cer"));
					//f.Replace((const char*)m_certificateData.GetBuffer(), m_certificateData.Length());
					//f.Close();
				}
				catch (...)
				{
				}
#				endif
			throw e.AddIfNewSource_(L"������ ��� ������� ����������� (CMS64)");
			}
			catch (...)
			{
				throw MethodError(L"������ ��� ������� ����������� (CMS64)");
			}
			// throw MethodError(L"_1_");
			//
			//
			//
			AsnObject m = AsnObject::NewSequence();
			AsnObject* p_m3 = 0;
			try
			{
				m.Add(AsnObject(OID(L"1.2.840.113549.1.7.2")))
					.Add(AsnObject(true, AsnObject::CONTEXT_SPECIFIC, 0));
				//m.SetIndefiniteLength(true);
				AsnObject& m__1 = m[1];
				//m__1.SetIndefiniteLength(true);
				m__1.Add(AsnObject::NewSequence());
				AsnObject& m2 = m__1[0];
				//m2.SetIndefiniteLength(true);
				m2.Add(AsnObject(1))
					.Add(AsnObject::NewSet())
					.Add(AsnObject::NewSequence())
					//.Add(AsnObject::NewSequence()) // 
					.Add(AsnObject(true,AsnObject::CONTEXT_SPECIFIC,0)) /// ADD CERT 
					.Add(AsnObject::NewSet());
				//
				AsnObject& m2__1 = m2[1];
				m2__1.Add(
					AsnObject::NewSequence()
					.Add(AsnObject(OID(g2012? L"1.2.643.7.1.1.2.2" : L"1.2.643.2.2.9")))
					.Add(AsnObject(false, AsnObject::UNIVERSAL, AsnObject::_NULL_))
					);
				//
				AsnObject& m2__2 = m2[2];
				//m2__2.SetIndefiniteLength(true);
				m2__2.Add(AsnObject(OID(L"1.2.840.113549.1.7.1")));
				//
				AsnObject& m2_cert = m2[3];
				m2_cert.Add(cert_O);
				//
				AsnObject& m2__3 = m2[4]; /// ADD CERT 
				m2__3.Add(AsnObject::NewSequence()); 
				AsnObject& m3 = m2__3[0];
				p_m3 = &m3;
				//
				m3.Add(AsnObject(1))
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
				m3__2.Add(AsnObject(OID(g2012 ? L"1.2.643.7.1.1.2.2" : L"1.2.643.2.2.9")))
					.Add(AsnObject(false, AsnObject::UNIVERSAL, AsnObject::_NULL_));
				//
				m3__3.Add(AsnObject(OID(g2012 ? L"1.2.643.7.1.1.1.1" : L"1.2.643.2.2.19")))
					.Add(AsnObject(false, AsnObject::UNIVERSAL, AsnObject::_NULL_));
				//
				m3.Add(AsnObject(false, AsnObject::UNIVERSAL, AsnObject::OCTET_STRING));
			}
			catch (::::Exception e)
			{
				throw e.AddIfNewSource_(L"������ ��� ������������ CMS-������� (CMS64)");
			}
			catch (...)
			{
				throw MethodError(L"������ ��� ������������ CMS-������� (CMS64)");
			}
			//
			// �����������
			//
			AsnObject& m3__4 = (*p_m3)[4]; // sInfo_O ? 
										   //
		    // throw MethodError(L"_2_");
			int flags = 0;
			if (digest0.Length() > 0) flags = 1;
			//
			Blob rawSignature;
			if (driveLetter.Left(_W("_CryptoPro").GetLength()) == L"_CryptoPro")
			{
				rawSignature = FromBase64String(
					CreateSimpleSignature64_CryptoPro_Digest(pkh64, pwd, L"", L"", digest0));
			}
			else
			{
				rawSignature = key.CreateRawSignature(dataToSign, flags, digest0);
			}
			// throw MethodError(L"_3_");
			//
			m3__4.Data().Allocate(rawSignature.Length());
			for (j = 0; j < rawSignature.Length(); ++j)
				m3__4.Data()[j] = rawSignature[rawSignature.Length() - 1 - j];
			//
			Blob b = m.Encoded();
			if (p) 
				*p = findIn(m_certificateData, b);
			//File f2;
			//f2.OpenToWrite(_T("D:\\dev\\___sign2012.der")); 
			//f2.Replace((const char*)b.GetBuffer(), b.Length()); 
			//f2.Close(); 
			////
			//File f3;
			//f3.OpenToWrite(_T("C:\\temp\\___cert.cer"));
			//f3.Replace((const char*)m_certificateData.GetBuffer(), m_certificateData.Length());
			//f3.Close();
			//
			return Util::ToBase64String(b);
		}
		_Catch()
	}



	inline static string CreateCMSSignature64_obs_2001(
		const string& pkh64, const string& pwd
		// , const string& cn, const string& org
		, Blob dataToSign //, string // hashOid
		, bool includeCert = true
		, Blob digest0 = Blob()
		, int* p = 0
		, int* certSize = 0
		)
	{
		try
		{
			if (dataToSign.Length() == 0 && digest0.Length() == 0)
			{
				dataToSign.Allocate(1);
				dataToSign[0] = '8';
			}
			//
			SharedArray<string> a = SearchKey(pkh64);
			//
			string driveLetter = a[0];
			//
			//if (driveLetter.Left(_W("_CryptoPro").GetLength()) == L"_CryptoPro")
			//{
			//	//if (digest0.Length() > 0)
			//	//{
			//	//	return CreateSimpleSignature64_CryptoPro_Digest(pkh64, 
			//	//		pwd, L"", L"", digest0);
			//	//}
			//	return CreateCMSSignature64_CADES_CryptoPro(pkh64, pwd,
			//		dataToSign, includeCert, digest0, p, certSize);
			//}
			//
			string path1 = a[2];
			string kpath1 = a[3];
			//
			string certPath = path1 + "\\client.cer";
			// 
			CCOM_KeyObject key;
			XmlDocument d;
			d.Load(kpath1);
			key.SetPath(path1 + L"\\Container");
			//key.SetCommonName(cn);
			//key.SetOrgName(org);
			key.SetPassword(pwd);
			try
			{
				key.SetXmlInfo(d.DocumentElement());
			}
			catch (::::Exception& e)
			{
				throw MethodError(L"������ ������ �����, ���� �������� ������");
			}
			//
			File f;
			f.OpenToRead(_S(certPath));
			Blob m_certificateData = f.ReadAll();
			f.Close();
			//
			if (certSize) *certSize = m_certificateData.Length();
			//
			int j = 0;
			//
			Blob pkh = FromBase64String(pkh64);
			//
			AsnObject cert_O = AsnObject::NewSequence();
			try
			{
				cert_O = AsnObject(m_certificateData);
			}
			catch (::::Exception e)
			{
#				ifdef _DEBUG
				try
				{
					TRACE_LOG(_T("!!!\n������ ��� ������� ����������� (CMS64)\n!!!"));
					TRACE_LOG1(_T("Length: %d"), (int)m_certificateData.Length());
					//File f;
					//f.Open(_T("D:\\___error-cer.cer"));
					//f.Replace((const char*)m_certificateData.GetBuffer(), m_certificateData.Length());
					//f.Close();
				}
				catch (...)
				{
				}
#				endif
				throw e.AddIfNewSource_(L"������ ��� ������� ����������� (CMS64)");
			}
			catch (...)
			{
				throw MethodError(L"������ ��� ������� ����������� (CMS64)");
			}
			// throw MethodError(L"_1_");
			//
			//
			//
			AsnObject m = AsnObject::NewSequence();
			AsnObject* p_m3 = 0;
			try
			{
				m.Add(AsnObject(OID(L"1.2.840.113549.1.7.2")))
					.Add(AsnObject(true, AsnObject::CONTEXT_SPECIFIC, 0));
				//m.SetIndefiniteLength(true);
				AsnObject& m__1 = m[1];
				//m__1.SetIndefiniteLength(true);
				m__1.Add(AsnObject::NewSequence());
				AsnObject& m2 = m__1[0];
				//m2.SetIndefiniteLength(true);
				m2.Add(AsnObject(1))
					.Add(AsnObject::NewSet())
					.Add(AsnObject::NewSequence())
					//.Add(AsnObject::NewSequence()) // 
					.Add(AsnObject(true, AsnObject::CONTEXT_SPECIFIC, 0)) /// ADD CERT 
					.Add(AsnObject::NewSet());
				//
				AsnObject& m2__1 = m2[1];
				m2__1.Add(
					AsnObject::NewSequence()
					.Add(AsnObject(OID(L"1.2.643.2.2.9")))
					.Add(AsnObject(false, AsnObject::UNIVERSAL, AsnObject::_NULL_))
					);
				//
				AsnObject& m2__2 = m2[2];
				//m2__2.SetIndefiniteLength(true);
				m2__2.Add(AsnObject(OID(L"1.2.840.113549.1.7.1")));
				//
				AsnObject& m2_cert = m2[3];
				m2_cert.Add(cert_O);
				//
				AsnObject& m2__3 = m2[4]; /// ADD CERT 
				m2__3.Add(AsnObject::NewSequence());
				AsnObject& m3 = m2__3[0];
				p_m3 = &m3;
				//
				m3.Add(AsnObject(1))
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
					.Add(AsnObject(false, AsnObject::UNIVERSAL, AsnObject::_NULL_));
				//
				m3__3.Add(AsnObject(OID(L"1.2.643.2.2.19")))
					.Add(AsnObject(false, AsnObject::UNIVERSAL, AsnObject::_NULL_));
				//
				m3.Add(AsnObject(false, AsnObject::UNIVERSAL, AsnObject::OCTET_STRING));
			}
			catch (::::Exception e)
			{
				throw e.AddIfNewSource_(L"������ ��� ������������ CMS-������� (CMS64)");
			}
			catch (...)
			{
				throw MethodError(L"������ ��� ������������ CMS-������� (CMS64)");
			}
			//
			// �����������
			//
			AsnObject& m3__4 = (*p_m3)[4]; // sInfo_O ? 
										   //
										   // throw MethodError(L"_2_");
			int flags = 0;
			if (digest0.Length() > 0) flags = 1;
			//
			Blob rawSignature;
			if (driveLetter.Left(_W("_CryptoPro").GetLength()) == L"_CryptoPro")
			{
				rawSignature = FromBase64String(
					CreateSimpleSignature64_CryptoPro_Digest(pkh64, pwd, L"", L"", digest0));
			}
			else
			{
				rawSignature = key.CreateRawSignature(dataToSign, flags, digest0);
			}
			// throw MethodError(L"_3_");
			//
			m3__4.Data().Allocate(rawSignature.Length());
			for (j = 0; j < rawSignature.Length(); ++j)
				m3__4.Data()[j] = rawSignature[rawSignature.Length() - 1 - j];
			//
			Blob b = m.Encoded();
			if (p)
				*p = findIn(m_certificateData, b);
			//File f2;
			//f2.OpenToWrite(_T("C:\\temp\\___sign.der")); 
			//f2.Replace((const char*)b.GetBuffer(), b.Length()); 
			//f2.Close(); 
			////
			//File f3;
			//f3.OpenToWrite(_T("C:\\temp\\___cert.cer"));
			//f3.Replace((const char*)m_certificateData.GetBuffer(), m_certificateData.Length());
			//f3.Close();
			//
			return Util::ToBase64String(b);
		}
		_Catch()
	}


	//inline static string CreateCMSSignature64_CADES_CryptoPro(
	//	const string& pkh64, const string& pwd
	//	// , const string& cn, const string& org
	//	, Blob dataToSign //, string // hashOid
	//	, bool includeCert = true
	//	, Blob digest0 = Blob()
	//	, int* p = 0
	//	, int* certSize = 0
	//	)
	//{
	//	try
	//	{
	//		SharedArray<string> a = SearchKey(pkh64);
	//		//
	//		string driveLetter = a[0];
	//		string containerName = a[5];
	//		//
	//		if (driveLetter.Left(_W("_CryptoPro").GetLength()) != L"_CryptoPro")
	//		{
	//			throw MethodError(L"�������� ��� ����� (21)");
	//		}
	//		//
	//		HCRYPTPROV hProv = 0;
	//		if (driveLetter == L"_CryptoPro")
	//		{
	//			if (!CryptAcquireContext(
	//				&hProv,
	//				containerName,
	//				NULL,
	//				PROV_GOST_2001_DH,
	//				0))
	//			{
	//				throw MethodError(L"������ �������� ����������: " + containerName);
	//			}
	//		}
	//		else if (driveLetter == L"_CryptoPro2012_256")
	//		{
	//			if (!CryptAcquireContext(
	//				&hProv,
	//				containerName,
	//				NULL,
	//				PROV_GOST_2012_256,
	//				0))
	//			{
	//				throw MethodError(L"������ �������� ����������: " + containerName);
	//			}
	//		}
	//		else if (driveLetter == L"_CryptoPro2012_512")
	//		{
	//			if (!CryptAcquireContext(
	//				&hProv,
	//				containerName,
	//				NULL,
	//				PROV_GOST_2012_256, // %!% // PROV_GOST_2012_512,
	//				0))
	//			{
	//				throw MethodError(L"������ �������� ����������: " + containerName);
	//			}
	//		}
	//		if (!hProv)
	//			throw MethodError(L"������ �������� ���������� (0): " + containerName);
	//		//			
	//		//
	//		//
	//		HCERTSTORE hCertStore = CertOpenSystemStore(0, _TEXT("MY"));
	//		//
	//		// wchar_t* subject(pSubject);
	//		PCCERT_CONTEXT pCertContext(0);
	//		DWORD dwSize(0);
	//		CRYPT_KEY_PROV_INFO* pKeyInfo(0);
	//		//
	//		int mustFree;
	//		DWORD dwKeySpec = 0;
	//		// HCRYPTPROV hProv;

	//		for (;;)
	//		{
	//			//if (subject)
	//			//{
	//			//	// ���� ������ Subject Name, �� ���� ���������� �� ����, �������� ��� ��������
	//			//	pCertContext = CertFindCertificateInStore(hCertStore, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, 0, CERT_FIND_SUBJECT_STR, subject, pCertContext);
	//			//	if (pCertContext)
	//			//		return pCertContext;
	//			//}
	//			//else
	//			//{
	//				// ������� ��������� ���������, �������� ��� ��������
	//				pCertContext = CertFindCertificateInStore(hCertStore, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, 0, CERT_FIND_ANY, 0, pCertContext);
	//			//}

	//			if (pCertContext)
	//			{
	//				if (!CryptAcquireCertificatePrivateKey(pCertContext, 0, 0, &hProv, &dwKeySpec, &mustFree))
	//				{
	//					//if (mustFree)
	//					//	CryptReleaseContext(hProv, 0);
	//					continue;
	//				}

	//				// �������� ������ ������� �����������
	//				if (!(CertGetCertificateContextProperty(pCertContext, CERT_KEY_PROV_INFO_PROP_ID, 0, &dwSize)))
	//				{
	//					//cout << "Certificate property was not got" << endl;
	//					//return 0;
	//					continue;
	//				}

	//				if (pKeyInfo)
	//					free(pKeyInfo);

	//				// �������� ������
	//				pKeyInfo = (CRYPT_KEY_PROV_INFO*)malloc(dwSize);

	//				if (!pKeyInfo)
	//				{
	//					throw MethodError(L"Error occured during the time of memory allocating");
	//				}

	//				// �������� �������� �����������
	//				if (!(CertGetCertificateContextProperty(pCertContext, CERT_KEY_PROV_INFO_PROP_ID, pKeyInfo, &dwSize)))
	//				{
	//					free(pKeyInfo);
	//					//cout << "Certificate property was not got" << endl;
	//					//return 0;
	//					continue;
	//				}

	//				// ��������� ������������ ������ ����������� GOST R 34.10 - 2001
	//				//if (pKeyInfo->dwKeySpec == AT_KEYEXCHANGE && isGostType(pKeyInfo->dwProvType))
	//				//{
	//				//	if (mustFree)
	//				//		CryptReleaseContext(hProv, 0);
	//				//	free(pKeyInfo);
	//				//	return pCertContext;
	//				//}

	//				if (string(pKeyInfo->pwszContainerName) == containerName)
	//				{
	//					break;
	//				}

	//				//if (!CryptGetProvParam(
	//				//	hCryptProv,               // ���������� CSP
	//				//	PP_CONTAINER,             // ��������� ����� ��������� ����������
	//				//	NULL,                     // ��������� �� ��� ��������� ����������
	//				//	&dwUserNameLen,           // ����� �����
	//				//	0))
	//				//{
	//				//	// ������ ��������� ����� ��������� ����������
	//				//	throw MethodError(L"error occurred getting the key container name.");
	//				//}

	//				//// ����� ������������ auto_ptr:
	//				////std::auto_ptr<char> aptrUserName(new char[dwUserNameLen+1]);
	//				////szUserName = aptrUserName.get();
	//				//pszUserName = (char *)malloc((dwUserNameLen + 1));

	//				//if (!CryptGetProvParam(
	//				//	hCryptProv,               // ���������� CSP
	//				//	PP_CONTAINER,             // ��������� ����� ��������� ����������
	//				//	(LPBYTE)pszUserName,      // ��������� �� ��� ��������� ����������
	//				//	&dwUserNameLen,           // ����� �����
	//				//	0))
	//				//{
	//				//	// ������ ��������� ����� ��������� ����������
	//				//	free(pszUserName);
	//				//	throw MethodError(L"error occurred getting the key container name.");
	//				//}


	//			}
	//			else
	//			{
	//				break;
	//			}
	//		}
	//		if (!pCertContext)
	//		{
	//			throw MethodError(L"���������� �� ������ (1)"); 
	//		}
	//		if (!CryptAcquireCertificatePrivateKey(pCertContext, 0, 0, &hProv, &dwKeySpec, &mustFree))
	//		{
	//			throw MethodError(L"Sk");
	//			//cout << "CryptAcquireCertificatePrivateKey() failed" << "GetLastError() = " << GetLastError() << endl;
	//			//CertFreeCertificateContext(context);
	//			//return -1;
	//		}
	//		//
	//		//
	//		//
	//		CMSG_SIGNER_ENCODE_INFO signer = { sizeof(CMSG_SIGNER_ENCODE_INFO) };
	//		signer.pCertInfo = pCertContext->pCertInfo;
	//		signer.hCryptProv = hProv;
	//		signer.dwKeySpec = dwKeySpec;
	//		signer.HashAlgorithm.pszObjId = szOID_CP_GOST_R3411_12_256;

	//		CMSG_SIGNED_ENCODE_INFO info = { sizeof(CMSG_SIGNED_ENCODE_INFO) };
	//		info.cSigners = 1;
	//		info.rgSigners = &signer;
	//		info.cCertEncoded = 1;
	//		info.rgCertEncoded = new CERT_BLOB();
	//		info.rgCertEncoded[0].cbData = pCertContext->cbCertEncoded;
	//		info.rgCertEncoded[0].pbData = pCertContext->pbCertEncoded;

	//		CADES_ENCODE_INFO cadesInfo = { sizeof(cadesInfo) };
	//		cadesInfo.pSignedEncodeInfo = &info;

	//		HCRYPTMSG hMsg = CadesMsgOpenToEncode(
	//			X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, CMSG_DETACHED_FLAG, &cadesInfo, 0, 0);
	//		if (!hMsg)
	//		{
	//			throw MethodError(L"S1");
	//			//CryptReleaseContext(hProv, 0);
	//			//CertFreeCertificateContext(pCertContext);
	//			//std::cout << "CadesMsgOpenToEncode() failed" << std::endl;
	//			//return empty;
	//		}

	//		// std::vector<BYTE> data(10, 25);

	//		if (!CryptMsgUpdate(hMsg, dataToSign.GetBuffer(), (DWORD)dataToSign.GetSize(), TRUE))
	//		{
	//			throw MethodError(L"S2");
	//			//CryptReleaseContext(hProv, 0);
	//			//CertFreeCertificateContext(pCertContext);
	//			//CryptMsgClose(hMsg);
	//			//std::cout << "CryptMsgUpdate() failed" << std::endl;
	//			//return empty;
	//		}

	//		DWORD size = 0;
	//		if (!CryptMsgGetParam(hMsg, CMSG_CONTENT_PARAM, 0, 0, &size))
	//		{
	//			throw MethodError(L"S3");
	//			//CryptReleaseContext(hProv, 0);
	//			//CertFreeCertificateContext(pCertContext);
	//			//CryptMsgClose(hMsg);
	//			//std::cout << "CryptMsgGetParam() failed" << std::endl;
	//			//return empty;
	//		}

	//		Blob message;
	//		message.Allocate(size);
	//		if (!CryptMsgGetParam(hMsg, CMSG_CONTENT_PARAM, 0, message.GetBuffer(), &size))
	//		{
	//			throw MethodError(L"S4");
	//			//CryptReleaseContext(hProv, 0);
	//			//CertFreeCertificateContext(pCertContext);
	//			//CryptMsgClose(hMsg);
	//			//std::cout << "CryptMsgGetParam() failed" << std::endl;
	//			//return empty;
	//		}

	//		if (!CryptMsgClose(hMsg))
	//		{
	//			throw MethodError(L"S5");
	//			//CryptReleaseContext(hProv, 0);
	//			//CertFreeCertificateContext(pCertContext);
	//			//std::cout << "CryptMsgGetParam() failed" << std::endl;
	//			//return empty;
	//		}

	//		// CadesSignMessage
	//		hMsg = CryptMsgOpenToDecode(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
	//			CMSG_DETACHED_FLAG, 0, 0, 0, 0);
	//		if (!hMsg)
	//		{
	//			throw MethodError(L"S6");
	//			//CryptReleaseContext(hProv, 0);
	//			//CertFreeCertificateContext(pCertContext);
	//			//std::cout << "CryptMsgOpenToDecode() failed" << std::endl;
	//			//return empty;
	//		}

	//		if (!CryptMsgUpdate(hMsg, message.GetBuffer(), (DWORD)message.GetSize(), TRUE))
	//		{
	//			throw MethodError(L"S7");
	//			//CryptReleaseContext(hProv, 0);
	//			//CertFreeCertificateContext(pCertContext);
	//			//CryptMsgClose(hMsg);
	//			//std::cout << "CryptMsgUpdate() failed" << std::endl;
	//			//return empty;
	//		}

	//		//if (!CadesMsgEnhanceSignature(hMsg, 0, 0))
	//		//{
	//		//	throw MethodError(L"S8");
	//		//	//CryptReleaseContext(hProv, 0);
	//		//	//CertFreeCertificateContext(pCertContext);
	//		//	//CryptMsgClose(hMsg);
	//		//	//std::cout << "CadesMsgEnhanceSignature() failed" << std::endl;
	//		//	//return empty;
	//		//}

	//		size = 0;
	//		if (!CryptMsgGetParam(hMsg, CMSG_ENCODED_MESSAGE, 0, 0, &size))
	//		{
	//			throw MethodError(L"S9");
	//			//CryptReleaseContext(hProv, 0);
	//			//CertFreeCertificateContext(pCertContext);
	//			//CryptMsgClose(hMsg);
	//			//std::cout << "CryptMsgGetParam() failed" << std::endl;
	//			//return empty;
	//		}

	//		message.Reallocate(size);
	//		if (!CryptMsgGetParam(hMsg, CMSG_ENCODED_MESSAGE, 0, message.GetBuffer(), &size))
	//		{
	//			throw MethodError(L"S10");
	//			//CryptReleaseContext(hProv, 0);
	//			//CertFreeCertificateContext(pCertContext);
	//			//CryptMsgClose(hMsg);
	//			//std::cout << "CryptMsgGetParam() failed" << std::endl;
	//			//return empty;
	//		}

	//		if (!CryptMsgClose(hMsg))
	//		{
	//			throw MethodError(L"S10-2");
	//			//CryptReleaseContext(hProv, 0);
	//			//CertFreeCertificateContext(pCertContext);
	//			//std::cout << "CryptMsgClose() failed" << std::endl;
	//			//return empty;
	//		}

	//		CryptReleaseContext(hProv, 0);
	//		CertFreeCertificateContext(pCertContext);
	//		//
	//		string _k0 = a[0];
	//		string _k1 = a[1];
	//		string _k2 = a[2];
	//		string _k3 = a[3];
	//		string _k4 = a[4];
	//		string _k5 = a[5];
	//		string s0 = a[6];
	//		string s1 = a[7];
	//		string _k8 = a[8];
	//		Blob certificate = FromBase64String(s1);
	//		if (p)
	//			*p = findIn(certificate, message);
	//		//
	//		return __ToBase64(message); // message;
	//	}
	//	_Catch()
	//}



	// ====
	// Certificate request

#	define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)

	inline static CERT_NAME_INFO createRequestInfo(SharedArray<string>& attr)
	{
		int n = attr.Length() / 2;
		CERT_NAME_INFO info;
		info.cRDN = n;
		info.rgRDN = new CERT_RDN[n];
		for (int i = 0; i < n; i++)
		{
			info.rgRDN[i].cRDNAttr = 1;
			info.rgRDN[i].rgRDNAttr = new CERT_RDN_ATTR[1];
			info.rgRDN[i].rgRDNAttr[0].pszObjId = new char[64];
			CStringA oid(attr[2 * i]);
			CopyMemory(info.rgRDN[i].rgRDNAttr[0].pszObjId,
				(const char*)oid, oid.GetLength());
			info.rgRDN[i].rgRDNAttr[0].pszObjId[oid.GetLength()] = 0;
			info.rgRDN[i].rgRDNAttr[0].dwValueType = CERT_RDN_UNICODE_STRING;
			string v = attr[2 * i + 1];
			info.rgRDN[i].rgRDNAttr[0].Value.cbData = v.GetLength() * sizeof(wchar_t);
			info.rgRDN[i].rgRDNAttr[0].Value.pbData = 
				new BYTE[info.rgRDN[i].rgRDNAttr[0].Value.cbData];
			CopyMemory(info.rgRDN[i].rgRDNAttr[0].Value.pbData,
				v.GetString(), v.GetLength() * sizeof(wchar_t));
		}
		return info;
	}

	inline static void freeRequestInfo(CERT_NAME_INFO& info)
	{
		int n = info.cRDN;
		for (int i = 0; i < n; i++)
		{
			if (info.rgRDN[i].rgRDNAttr)
			{
				if (info.rgRDN[i].rgRDNAttr[0].pszObjId)
					delete[] info.rgRDN[i].rgRDNAttr[0].pszObjId;
				if (info.rgRDN[i].rgRDNAttr[0].Value.pbData)
					delete[] info.rgRDN[i].rgRDNAttr[0].Value.pbData;
				delete[] info.rgRDN[i].rgRDNAttr;
			}
		}
		if (info.rgRDN) delete[] info.rgRDN;
	}

	inline static std::string generateCSRLowLevel(Blob& _requestBlob,
		const string& commonName,
		const string& surName,
		const string& givenName,
		const string& title,
		const string& orgName,
		const string& orgUnitName,
		const string& locality,
		const string& streetAddress,
		const string& areaName,
		const string& INN, const string& OGRN, const string& SNILS
		)
	{
		try
		{
			string drive = L"_CryptoPro2012_512";

			const int n1 = 13;
			BYTE data1[n1 * 1024];
			SharedArray<string> attr;
			attr.Add(L"2.5.4.3").Add(commonName)
				.Add(L"2.5.4.4").Add(surName)
				.Add(L"2.5.4.42").Add(givenName)
				.Add(L"2.5.4.12").Add(title)
				.Add(L"2.5.4.10").Add(orgName)
				.Add(L"2.5.4.11").Add(orgUnitName)
				.Add(L"1.2.643.3.131.1.1").Add(INN)
				.Add(L"1.2.643.100.1").Add(OGRN)
				.Add(L"1.2.643.100.3").Add(SNILS)
				.Add(L"2.5.4.6").Add(L"RU")
				.Add(L"2.5.4.7").Add(locality)
				.Add(L"2.5.4.8").Add(areaName)
				.Add(L"2.5.4.9").Add(streetAddress)
				;

			COleDateTime keyTime = COleDateTime::GetCurrentTime();
			//*/
			CStringA keyTimeSuffix = //_S("15-01-12-18-28-36"); 
				FormatTime_ymd_HMD(
					_A("%02d-%02d-%02d"), _A("-%02d-%02d-%02d") // _T("%y-%m-%d-%H-%M-%S")) 
					, keyTime
					);
			//
			CStringA keyName = _A("-") + keyTimeSuffix;

			std::string containerName((const char*)keyName);
			//CERT_SUBJECT_NAME = containerName.c_str();

			/*
			wchar_t CNbuf[1024], SNbuf[1024], GNbuf[1024], Tbuf[1024];
			CopyMemory(CNbuf, (const wchar_t*)commonName, commonName.GetLength() * sizeof(wchar_t));
			CNbuf[commonName.GetLength()] = 0;
			CopyMemory(SNbuf, (const wchar_t*)surName, surName.GetLength() * sizeof(wchar_t));
			SNbuf[surName.GetLength()] = 0;
			CopyMemory(GNbuf, (const wchar_t*)givenName, givenName.GetLength() * sizeof(wchar_t));
			GNbuf[givenName.GetLength()] = 0;
			CopyMemory(Tbuf, (const wchar_t*)title, title.GetLength() * sizeof(wchar_t));
			GNbuf[title.GetLength()] = 0;

			CERT_RDN_ATTR rgNameAttr_CN[3];
			rgNameAttr_CN[0].dwValueType = CERT_RDN_UNICODE_STRING;
			rgNameAttr_CN[0].pszObjId = "2.5.4.3";
			rgNameAttr_CN[0].Value.pbData = (BYTE*)CNbuf;
			rgNameAttr_CN[0].Value.cbData = commonName.GetLength() * sizeof(wchar_t);
			rgNameAttr_CN[1].dwValueType = CERT_RDN_UNICODE_STRING;
			rgNameAttr_CN[1].pszObjId = "2.5.4.4";
			rgNameAttr_CN[1].Value.pbData = (BYTE*)SNbuf;
			rgNameAttr_CN[1].Value.cbData = surName.GetLength() * sizeof(wchar_t);
			rgNameAttr_CN[2].dwValueType = CERT_RDN_UNICODE_STRING;
			rgNameAttr_CN[2].pszObjId = "2.5.4.42";
			rgNameAttr_CN[2].Value.pbData = (BYTE*)GNbuf;
			rgNameAttr_CN[2].Value.cbData = givenName.GetLength() * sizeof(wchar_t);
			rgNameAttr_CN[3].dwValueType = CERT_RDN_UNICODE_STRING;
			rgNameAttr_CN[3].pszObjId = "2.5.4.12";
			rgNameAttr_CN[3].Value.pbData = (BYTE*)Tbuf;
			rgNameAttr_CN[3].Value.cbData = title.GetLength() * sizeof(wchar_t);
			//= {
			//	"2.5.4.3",                             
			//	CERT_RDN_UNICODE_STRING,             
			//	commonName.GetLength() * sizeof(wchar_t),
			//	(BYTE*)CNbuf,
			//	"2.5.4.4",
			//	CERT_RDN_UNICODE_STRING,
			//	surName.GetLength() * sizeof(wchar_t),
			//	(BYTE*)SNbuf
			//};

			CERT_RDN rgRDN[] = {
				4,                 // rgRDN[0].cRDNAttr
				&rgNameAttr_CN[0] };   // rgRDN[0].rgRDNAttr

								
			//CERT_NAME_INFO Name = {
			//	1,                  // Name.cRDN
			//	rgRDN };             // Name.rgRDN

									 //-------------------------------------------------------------------
									 // Declare and initialize all other variables and structures.

									 */

			/*
			BYTE* pCertReqInfo0 = NULL;
			DWORD cbCertReqInfo0 = 0;
			::::File f0;
			f0.OpenToRead(_S("D:\\dev\\test_512_gost2012_req.der"));
			Blob req0 = f0.ReadAll();
			f0.Close();

			if (!CryptDecodeObjectEx(
				MY_ENCODING_TYPE,     // Encoding type
				X509_CERT_REQUEST_TO_BE_SIGNED,            // Structure type
				req0.GetBuffer(),
				req0.GetSize(),                
				CRYPT_DECODE_NOCOPY_FLAG,
				NULL,                 
				NULL,
				&cbCertReqInfo0))      
			{
				throw MethodError(L"The first call to CryptEncodeObject failed. \nA public/private key pair may not exit in the container. \n");
			}
			pCertReqInfo0 = new BYTE[cbCertReqInfo0];
			if (!CryptDecodeObjectEx(
				MY_ENCODING_TYPE,     // Encoding type
				X509_CERT_REQUEST_TO_BE_SIGNED,            // Structure type
				req0.GetBuffer(),
				req0.GetSize(),
				CRYPT_DECODE_NOCOPY_FLAG,
				NULL,
				pCertReqInfo0,
				&cbCertReqInfo0))
			{
				throw MethodError(L"The first call to CryptEncodeObject failed. \nA public/private key pair may not exit in the container. \n");
			}
			CERT_REQUEST_INFO& CertReqInfo0 = *((CERT_REQUEST_INFO*)pCertReqInfo0);

			Blob b0;
			b0.Allocate(CertReqInfo0.rgAttribute->rgValue->cbData);
			CopyMemory(b0.GetBuffer(), CertReqInfo0.rgAttribute->rgValue->pbData, CertReqInfo0.rgAttribute->rgValue->cbData);
			string s0 = __ToBase64(b0);
			*/

			string s0 = L"MIIBZjAOBgNVHQ8BAf8EBAMCA9gwHQYDVR0lBBYwFAYIKwYBBQUHAwIGCCsGAQUFBwMEMBYGA1UdIAEB/wQMMAowCAYGKoUDZHEBMDIGBSqFA2RvBCkMJ9Ca0YDQuNC/0YLQvtCf0YDQviBDU1Ag0LLQtdGA0YHQuNGPIDQuMDCB6AYFKoUDZHAEgd4wgdsMKyLQmtGA0LjQv9GC0L7Qn9GA0L4gQ1NQIiAo0LLQtdGA0YHQuNGPIDMuNikMJ9Ch0KQvMTIxLTE4NTkg0L7RgiAxNyDQuNGO0L3RjyAyMDEyINCzLgxa0J/QkNCaICLQo9C00L7RgdGC0L7QstC10YDRj9GO0YnQuNC5INGG0LXQvdGC0YAgItCa0YDQuNC/0YLQvtCf0YDQviDQo9CmIiDQstC10YDRgdC40LggMS41DCfQodCkLzEyOC0xODIyINC+0YIgMDEg0LjRjtC90Y8gMjAxMiDQsy4=";
			Blob b0 = FromBase64String(s0);

			CRYPT_ATTRIBUTE a0;
			a0.pszObjId = "1.3.6.1.4.1.311.2.1.14";
			a0.cValue = 1;
			a0.rgValue = new CRYPT_ATTR_BLOB();
			a0.rgValue->cbData = b0.GetSize();
			a0.rgValue->pbData = b0.GetBuffer();

			CERT_NAME_INFO Name = createRequestInfo(attr);

			CERT_REQUEST_INFO  CertReqInfo;			
			CERT_NAME_BLOB  SubjNameBlob;
			DWORD  cbNameEncoded;
			BYTE*  pbNameEncoded;
			HCRYPTPROV  hCryptProv;
			DWORD  cbPublicKeyInfo;
			CERT_PUBLIC_KEY_INFO*  pbPublicKeyInfo;
			DWORD  cbEncodedCertReqSize;
			CRYPT_OBJID_BLOB  Parameters;
			CRYPT_ALGORITHM_IDENTIFIER  SigAlg;
			BYTE*  pbSignedEncodedCertReq;
			char*  pSignedEncodedCertReqBlob;

			//-------------------------------------------------------------------
			//    Begin processing.

			if (!CryptEncodeObject(
				MY_ENCODING_TYPE,     // Encoding type
				X509_NAME,            // Structure type
				&Name,                // Address of CERT_NAME_INFO structure
				NULL,                 // pbEncoded
				&cbNameEncoded))      // pbEncoded size
			{
				throw MethodError(L"The first call to CryptEncodeObject failed. \nA public/private key pair may not exit in the container. \n");
			}
			//-------------------------------------------------------------------
			//     Allocate memory for the encoded name.

			if (!(pbNameEncoded = (BYTE*)malloc(cbNameEncoded)))
				throw MethodError(L"The pbNamencoded malloc operation failed. \n");

			//-------------------------------------------------------------------
			//  Call CryptEncodeObject to do the actual encoding of the name.

			if (!CryptEncodeObject( 
				MY_ENCODING_TYPE,    // Encoding type
				X509_NAME,           // Structure type
				&Name,               // Address of CERT_NAME_INFO structure
				pbNameEncoded,       // pbEncoded
				&cbNameEncoded))     // pbEncoded size
			{
				free(pbNameEncoded);
				throw MethodError(L"The second call to CryptEncodeObject failed. \n");
			}
			//-------------------------------------------------------------------
			// Set the subject member of CertReqInfo to point to 
			// a CERT_NAME_INFO structure that 
			// has been initialized with the data from cbNameEncoded
			// and pbNameEncoded.

			SubjNameBlob.cbData = cbNameEncoded;
			SubjNameBlob.pbData = pbNameEncoded;
			CertReqInfo.Subject = SubjNameBlob;

			//-------------------------------------------------------------------
			// Generate custom information. This step is not
			// implemented in this code.

			CertReqInfo.cAttribute = 1;
			CertReqInfo.rgAttribute = &a0;
			CertReqInfo.dwVersion = CERT_REQUEST_V1;

			// DWORD n2 = CertReqInfo.cAttribute;

			//-------------------------------------------------------------------
			//    Call CryptExportPublicKeyInfo to return an initialized
			//    CERT_PUBLIC_KEY_INFO structure.
			//    First, get a cryptographic provider.
			/*
			if (CryptAcquireContext(
				&hCryptProv,        // Address for handle to be returned.
				NULL,               // Use the current user's logon name.
				NULL,               // Use the default provider.
				PROV_RSA_FULL,      // Need to both encrypt and sign.
				NULL))              // No flags needed.
			{
				printf("A cryptographic provider has been acquired. \n");
			}
			else
			{
				free(pbNameEncoded);
				throw MethodError(L"CryptAcquireContext failed. \n");
			}
			*/

			// ���������� � ������������� ����������. 
			LPSTR pszUserName;            // ����� ��� �������� �����  ��������� ����������.
			DWORD dwUserNameLen;          // ����� ������.
			//LPCSTR UserName;              // ����������� �� ������ ��� ������������ 
										  // ����� ����� ������������ ��� ���
										  // ��������� ���������� (����������� �� 100 ��������).

										  // ������ ����������. ��������� ����� ������������ ����������.
			//if (argc < 2)
			//	HandleError(" using: CreatingKeyContainer.exe <container_name>");

			// UserName = CERT_SUBJECT_NAME;

			//  ��� �������� ������ ��������� ���������� ������ ������� ���������
			//  ���������� �� NULL ����� � ��� ��������� ������ �������:
			//if (CryptAcquireContextA(
			//	&hCryptProv,               // ���������� CSP
			//	UserName,                  // ��� ���������� 
			//	NULL,                      // ������������� ���������� �� ���������
			//	PROV_GOST_2001_DH,         // ��� ����������
			//	0))                        // �������� ������
			//{
			//	printf("A cryptcontext with the %s key container has been acquired.\n", UserName);
			//}
			//else
			//{
				// �������� ������ ����������. 

			char containerNameBuf[1024]; 
			CopyMemory(containerNameBuf, containerName.c_str(),
				containerName.size());
			containerNameBuf[containerName.size()] = 0;
			if (!CryptAcquireContextA(
				&hCryptProv,
				containerNameBuf,
				NULL,
				// PROV_GOST_2001_DH,
				PROV_GOST_2012_256, // %!% // PROV_GOST_2012_512,
				CRYPT_NEWKEYSET))
			{
				throw MethodError(L"Could not create a new key container.\n");
			}


			// ����������������� �������� � �������� ����������� ��������. ���������
			// ����� ��������� ����������. 
			if (!CryptGetProvParam(
				hCryptProv,               // ���������� CSP
				PP_CONTAINER,             // ��������� ����� ��������� ����������
				NULL,                     // ��������� �� ��� ��������� ����������
				&dwUserNameLen,           // ����� �����
				0))
			{
				// ������ ��������� ����� ��������� ����������
				throw MethodError(L"error occurred getting the key container name.");
			}

			// ����� ������������ auto_ptr:
			//std::auto_ptr<char> aptrUserName(new char[dwUserNameLen+1]);
			//szUserName = aptrUserName.get();
			pszUserName = (char *)malloc((dwUserNameLen + 1));

			if (!CryptGetProvParam(
				hCryptProv,               // ���������� CSP
				PP_CONTAINER,             // ��������� ����� ��������� ����������
				(LPBYTE)pszUserName,      // ��������� �� ��� ��������� ����������
				&dwUserNameLen,           // ����� �����
				0))
			{
				// ������ ��������� ����� ��������� ����������
				free(pszUserName);
				throw MethodError(L"error occurred getting the key container name.");
			}

			printf("A crypto context has been acquired and \n");
			printf("The name on the key container is %s\n\n", pszUserName);
			free(pszUserName);

			// �������� � �������� ����������� ��������,
			// ������� ��������� ����������� ����� �������
			//
			HCRYPTKEY hKey = 0;
			//
			//if (CryptGetUserKey(
			//	hCryptProv,                     // ���������� CSP
			//	AT_SIGNATURE,                   // ������������ �����
			//	&hKey))                         // ���������� �����
			//{
			//	printf("A signature key is available.\n");
			//}
			//else
			//{
			//	printf("No signature key is available.\n");

			//	// ������ � ���, ��� ��������� �� �������� �����.
			//	if (!(GetLastError() == (DWORD)NTE_NO_KEY))
			//		throw MethodError(L"An error other than NTE_NO_KEY getting signature key.\n");

			//	// �������� ����������� �������� ����. 
			//	printf("The signature key does not exist.\n");
			//	printf("Creating a signature key pair...\n");

			//	if (!CryptGenKey(
			//		hCryptProv,
			//		AT_KEYEXCHANGE,
			//		0,
			//		&hKey))
			//	{
			//		throw MethodError(L"Error occurred creating a signature key.\n");
			//	}
			//	printf("Created a signature key pair.\n");

			//}

			if (!CryptGenKey(
				hCryptProv,
				AT_KEYEXCHANGE,
				CRYPT_EXPORTABLE,
				&hKey))
			{
				throw MethodError(L"Error occurred creating a signature key.\n");
			}

			// ��������� ����� ������: AT_KEYEXCHANGE
			if (CryptGetUserKey(
				hCryptProv,
				AT_KEYEXCHANGE,
				&hKey))
			{
				printf("An exchange key exists. \n");
			}
			else
			{
			}

			// ������ ��������� ����� � �������� BLOB.
			// ����������� ������� BLOB� ��������� ����� � ������������� ������.
			//
			DWORD cbKeyBlob = 0;
			BYTE *pbKeyBlob = NULL;          // ��������� �� �������� BLOB 
			FILE *Cert = NULL;               // ���� ��� �������� �����������
			BYTE *pbCertBlob = NULL; // ��������� BLOB �����������
									 //
			if (CryptExportKey(
				hKey,
				0,
				PUBLICKEYBLOB,
				0,
				NULL,
				&cbKeyBlob))
			{
				printf("Size of the BLOB for the public key determined. \n");
			}
			else
			{
				throw MethodError(L"Error computing BLOB length.");
			}

			pbKeyBlob = (BYTE*)malloc(cbKeyBlob);
			if (!pbKeyBlob)
			{
				throw MethodError(L"Out of memory. \n");
			}

			// ��������������� ��������� ����� � BLOB ��������� �����.
			if (!CryptExportKey(
				hKey,
				0,
				PUBLICKEYBLOB,
				0,
				pbKeyBlob,
				&cbKeyBlob))
			{
				throw MethodError(L"Error during CryptExportKey.");
			}






			//-------------------------------------------------------------------
			// Call CryptExportPublicKeyInfo to get the size of the returned
			// information.

			if (CryptExportPublicKeyInfo(
				hCryptProv,            // Provider handle
				AT_KEYEXCHANGE,          // Key spec
				MY_ENCODING_TYPE,      // Encoding type
				NULL,                  // pbPublicKeyInfo
				&cbPublicKeyInfo))     // Size of PublicKeyInfo
			{
				printf("The keyinfo structure is %d bytes. \n", cbPublicKeyInfo);
			}
			else
			{
				free(pbNameEncoded);
				throw MethodError(L"The first call to CryptExportPublickKeyInfo failed. \n"
					L"The probable cause is that \n"
					L"there is no key pair in the key container. \n");
			}
			//-------------------------------------------------------------------
			// Allocate the necessary memory.

			if (pbPublicKeyInfo =
				(CERT_PUBLIC_KEY_INFO*)malloc(cbPublicKeyInfo))
			{
				printf("Memory is allocated for the public key structure. \n");
			}
			else
			{
				free(pbNameEncoded);
				throw MethodError(L"Memory allocation failed. \n");
			}
			//-------------------------------------------------------------------
			// Call CryptExportPublicKeyInfo to get pbPublicKeyInfo.

			if (CryptExportPublicKeyInfo(
				hCryptProv,            // Provider handle
				AT_KEYEXCHANGE,          // Key spec
				MY_ENCODING_TYPE,      // Encoding type
				pbPublicKeyInfo,       // pbPublicKeyInfo
				&cbPublicKeyInfo))     // Size of PublicKeyInfo
			{
				printf("The key has been exported. \n");
			}
			else
			{
				free(pbNameEncoded);
				free(pbPublicKeyInfo);
				throw MethodError(L"The second call to CryptExportPublicKeyInfo failed. \n");
			}
			//-------------------------------------------------------------------
			// Set the SubjectPublicKeyInfo member of the 
			// CERT_REQUEST_INFO structure to point to the CERT_PUBLIC_KEY_INFO 
			// structure created.

			CertReqInfo.SubjectPublicKeyInfo = *pbPublicKeyInfo;

			memset(&Parameters, 0, sizeof(Parameters));
			//SigAlg.pszObjId = szOID_CP_GOST_R3411_R3410EL; 		// szOID_OIWSEC_sha1RSASign;
			SigAlg.pszObjId = szOID_CP_GOST_R3411_12_256_R3410; // %!% // szOID_CP_GOST_R3411_12_512; 		// szOID_OIWSEC_sha1RSASign;
			SigAlg.Parameters = Parameters;

			//-------------------------------------------------------------------
			// Call CryptSignAndEncodeCertificate to get the size of the
			// returned BLOB. The dwKeySpec argument should match the KeySpec
			// (AT_SIGNATURE or AT_KEYEXCHANGE) used to create the private
			// key. Here, AT_KEYEXCHANGE is assumed.

			if (CryptSignAndEncodeCertificate(
				hCryptProv,                      // Crypto provider
				AT_KEYEXCHANGE,                  // Key spec
				MY_ENCODING_TYPE,                // Encoding type
				X509_CERT_REQUEST_TO_BE_SIGNED,  // Structure type
				&CertReqInfo,                    // Structure information
				&SigAlg,                         // Signature algorithm
				NULL,                            // Not used
				NULL,                            // pbSignedEncodedCertReq
				&cbEncodedCertReqSize))          // Size of certificate 
												 // required
			{
				printf("The size of the encoded certificate is set. \n");
			}
			else
			{
				free(pbNameEncoded);
				free(pbPublicKeyInfo);
				throw MethodError(L"First call to CryptSignandEncode failed. \n");
			}
			//-------------------------------------------------------------------
			// Allocate memory for the encoded certificate request.

			if (pbSignedEncodedCertReq = (BYTE*)malloc(cbEncodedCertReqSize))
			{
				printf("Memory has been allocated.\n");
			}
			else
			{
				free(pbNameEncoded);
				free(pbPublicKeyInfo);
				throw MethodError(L"The malloc operation failed. \n");
			}
			//-------------------------------------------------------------------
			// Call CryptSignAndEncodeCertificate to get the 
			// returned BLOB.

			if (CryptSignAndEncodeCertificate(
				hCryptProv,                     // Crypto provider
				AT_KEYEXCHANGE,                 // Key spec
				MY_ENCODING_TYPE,               // Encoding type
				X509_CERT_REQUEST_TO_BE_SIGNED, // Struct type
				&CertReqInfo,                   // Struct info        
				&SigAlg,                        // Signature algorithm
				NULL,                           // Not used
				pbSignedEncodedCertReq,         // Pointer
				&cbEncodedCertReqSize))         // Length of the message
			{
				printf("The message is encoded and signed. \n");
			}
			else
			{
				free(pbNameEncoded);
				free(pbPublicKeyInfo);
				free(pbSignedEncodedCertReq);
				throw MethodError(L"The second call to CryptSignAndEncode failed. \n");
			}

			//-------------------------------------------------------------------
			// View the signed and encoded certificate request BLOB.

			//try
			//{
			//	File f;
			//	f.OpenToWrite(_T("d:\\dev\\____R1.der"));
			//	f.Replace((char*)pbSignedEncodedCertReq, cbEncodedCertReqSize);
			//	f.Close();
			//}
			//catch (...)
			//{
			//}

			Blob reqData;
			reqData.Allocate(cbEncodedCertReqSize);
			CopyMemory(reqData.GetBuffer(), pbSignedEncodedCertReq, cbEncodedCertReqSize);
			_requestBlob = reqData;

			AsnObject requestO(reqData);
			OutputDebugStringW(requestO.Dump());
			Blob pkh = requestO.CP_GOST2001PublicKeyBits;

			RegisterContainer(string(keyName), drive, keyTime, reqData, requestO);




			pSignedEncodedCertReqBlob =
				new char[(cbEncodedCertReqSize * 2) + 1];

			//-------------------------------------------------------------------
			// Call ByteToStr, one of the general purpose functions, to convert 
			// the byte BLOB to ASCII hexadecimal format. 

			//////ByteToStr(cbEncodedCertReqSize,
			//////	pbSignedEncodedCertReq,
			//////	pSignedEncodedCertReqBlob);

			//-------------------------------------------------------------------
			// Print the string.
			printf("The string created is: \n");
			printf("%s\n", pSignedEncodedCertReqBlob);

			//-------------------------------------------------------------------
			// Free memory.

			free(pbNameEncoded);
			free(pbPublicKeyInfo);
			free(pbSignedEncodedCertReq);
			CryptReleaseContext(hCryptProv, 0);

			printf("\nMemory freed. Program ran without error. \n");

			return containerName;
		}
		_Catch()
	} 
	
	inline static void testRequestGeneration()
	{
		string dNameMap = L"{\"1.2.643.3.131.1.1\": \"1111111111\","
			L"\"1.2.643.6.2.1.6.1.100.6\": \"����� ����� ��\","
			L"\"1.2.643.6.2.1.6.1.100.7\": \"66\","
			L"\"1.2.643.6.2.1.6.1.100.8\": \"\","
			L"\"1.2.643.6.2.1.6.1.100.9\": \"\","
			L"\"1.2.643.100.1\": \"1111111111111\","
			L"\"1.2.643.100.3\": \"10123456789\","
			L"\"C\": \"RU\","
			L"\"CLF\": \"������3\","
			L"\"CLI\": \"����3\","
			L"\"CLO\": \"������3\","
			L"\"CN\": \"������3 ����3 ������3\","
			L"\"E\": \"zolotov@.ru\","
			L"\"L\": \"������\","
			L"\"O\": \"�������� ��\","
			L"\"OU\": \"������������� IT\","
			L"\"S\": \"������\","
			L"\"T\": \"�����������\","
			L"\"password\": \"12345\""
			L"}";
		//
		SharedArray<string> m = ParseDN(dNameMap);
		std::string iv = "";
		//
		Blob reqData;
		newCertRequestCryptoPro(L"_CryptoPro2012_512", m, iv, reqData);
	}

	inline static AsnObject newCertRequestCryptoPro(
		const string& drive,
		SharedArray<string> m, const std::string& iv,
		Blob& _requestBlob
		)
	{
		try
		{
			if (drive != L"_CryptoPro2012_512")
				throw MethodError(L"���������������� ��� �����: " + drive);

			// SharedArray<CString> R;
			//AsnObject requestO = AsnObject::NewSequence();
			//return requestO;

			string INN = PKITools::GetDNElement(m, L"1.2.643.3.131.1.1"); // L"11111111";
			string OGRN = PKITools::GetDNElement(m, L"1.2.643.100.1"); // L"2222222222";
			string SNILS = PKITools::GetDNElement(m, L"1.2.643.100.3");
			//
			string commonName = PKITools::GetDNElement(m, L"O"); 
			//
			string Client_F = PKITools::GetDNElement(m, L"CLF");
			string Client_I = PKITools::GetDNElement(m, L"CLI");
			string Client_O = PKITools::GetDNElement(m, L"CLO");
			string givenNames = Client_I;
			if (Client_O.GetLength() > 0) givenNames += L" " + Client_O;
			//
			string title = PKITools::GetDNElement(m, L"T");;
			//
			string orgName = PKITools::GetDNElement(m, L"O");
			string orgUnit = PKITools::GetDNElement(m, L"OU");
			//
			string locality = PKITools::GetDNElement(m, L"L");
			string areaName = PKITools::GetDNElement(m, L"S");
			string streetAddress = L""; // ?????????????? // PKITools::GetDNElement(m, L"S");

			Blob requestBlob;
			auto containerName = generateCSRLowLevel(requestBlob,
				commonName,
				Client_F,
				givenNames,
				title,
				orgName, orgUnit,
				locality, streetAddress, areaName,
				INN, OGRN, SNILS);

			_requestBlob = requestBlob;
			AsnObject requestO(requestBlob);
			return requestO;
		}
		_Catch()
	}

	inline static std::string prepareString(const wchar_t* r)
	{
		Blob b = WideStringToUTF8(r);
		char* buf = new char[b.Length() + 1];
		memcpy(buf, (const BYTE*)b, b.Length());
		buf[b.Length()] = 0;
		return std::string(buf);
	}

	inline static std::string prepareString(const std::string& r)
	{
		return prepareString(_W(r.c_str()));
	}


	inline static void prepareRequest(AsnObject& requestO,
		string& algS,
		string& paramsS,
		string& pubS,
		string& reqStr,
		string& pkh64
		)
	{
		AsnObject& o_0 = (AsnObject&)requestO[0];
		AsnObject& o_0_1 = (AsnObject&)o_0[1];
		AsnObject& o_0_2 = (AsnObject&)o_0[2];
		AsnObject& o_0_2_0 = (AsnObject&)o_0_2[0];
		AsnObject& o_0_2_0_0 = (AsnObject&)o_0_2_0[0];
		AsnObject& o_0_2_0_1 = (AsnObject&)o_0_2_0[1];
		AsnObject& o_0_2_0_1_0 = (AsnObject&)o_0_2_0_1[0];
		AsnObject& o_0_2_0_1_1 = (AsnObject&)o_0_2_0_1[1];
		AsnObject& o_0_2_1 = (AsnObject&)o_0_2[1];
		{
			string alg1 = o_0_2_0_0.Oid();
			string alg2 = o_0_2_0_1_0.Oid();
			string alg3 = o_0_2_0_1_1.Oid();
			algS = alg1;
			paramsS = alg2 + L", " + alg3;
			pubS = __ToBase64(o_0_2_1.Data());
		}
		//
		// ----
		// ���������� ���������� � ��������� �������
		//
		Blob pkh = requestPKH(requestO);
		pkh64 = __ToBase64(pkh);
		//
		// ----
		// Return value 
		//
		// FB::VariantList result;
		//result.push_back(prepareString(reqStr));
		//result.push_back(prepareString(std::string(_A(pkh64))));
		//result.push_back(prepareString(algS));
		//result.push_back(prepareString(paramsS));
		//result.push_back(prepareString(pubS));
		////
		//return result;
	}













	};

} // namespace 
