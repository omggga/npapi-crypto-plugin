
#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

// CCOM
//
#ifdef WIN64
#	include "tools/CCOM/x86_64/ccevp.h"
#	include "tools/CCOM/x86_64/errn.h"
#	pragma(comment, "tools/CCOM/x86_64/ccom33.lib")
#else // WIN32
//#	error "We are x64 !!!"
#	include "tools/CCOM/x86/ccevp.h"
#	include "tools/CCOM/x86/errn.h"
#	pragma comment(lib, "tools/CCOM/x86/ccom33.lib")
#endif
//
//#include <tools/CCOM/ccom_extra.h>
//#include <tools/eToken/pkcs11.h>
//#include <tools/eToken/eTSAPI.h>

// 
//
#include "_cpp/EnvelopingStream.h"
#include "_cpp/SlotUtil.h"
#include "_cpp/SlotAsn.h"
#include "low-level/SmartXml.h"

namespace 
{
    class XmlDSigHelper33
    {
	public:
        //========================================================================================
        // Глобальный путь к PSE

        inline static string RootPSEPath()
        {
                if (_rootPSEPath().GetLength() == 0) 
					MethodError(L"RootPSEPath is not set");
				//
                return _rootPSEPath();
        }

        inline static string set_RootPSEPath(const string& value)
		{
                ///lock (Lock)
                //{
                    if (_rootPSEPath().GetLength() != 0)
                    {
                        //throw new Exception("RootPSEPath is already set");
                    }
                    else
                    {
                        Lib33.CCOM_Init();
                    }
                    //
                    _rootPSEPath() = value;
                    if (_rootPSEPath()[_rootPSEPath().GetLength() - 1] != L'\\') 
						_rootPSEPath() += L"\\";
                //}
        }

        inline static string& _rootPSEPath()
		{
			static string s_rootPSEPath;
			return s_rootPSEPath; 
		}


        //========================================================================================
        // Lock 

        ///private const string Lock = "";

        //========================================================================================
        // Константы

        const int SBox = Lib33.GOSTH_SBOX_CP;
        const int PKParameters = Lib33.CCOM_GOSTR3410_2001_PARAMS_CP_XA;
        const int KeyAlg = Lib33.CCOM_GOSTR3410_2001;

        const char PrivateKeyFileName[] = "k.bin";
        const char PublicKeyFileName[] = "p.bin";

        const char ClientReqFileName[] = "client-request.der";
        const char ClientCertFileName[] = "client.cer";

        const int KeyIdHexSize = 5;

        //========================================================================================
        // Папки PSE

        //static Hashtable PSETable
        //{
        //    get
        //    {
        //        lock (Lock)
        //        {
        //            if (_pseTable == null)
        //            {
        //                _pseTable = new Hashtable();
        //            }
        //        }
        //        return _pseTable;
        //    }
        //}

        //private static Hashtable _pseTable;

        inline static string NormalizeBase64Id(const string& id64)
        {
			return __ToBase64(FromBase64String(id64));
        }

   //     bool PSEExists(string pkh64)
   //     {
   //         if (pkh64 == null) 
			//	MethodError(L"NullReferenceException: pkh64");
			////
   //         string pkh64N = NormalizeBase64Id(pkh64);
   //         return PSETable.ContainsKey(pkh64N);
   //     }


        //========================================================================================
        // Экспорт/импорт ключей (включая PSE) 

        //public static SHA1 SHA1Alg
        //{
        //    get
        //    {
        //        lock (Lock)
        //        {
        //            if (_sha1 == null)
        //            {
        //                _sha1 = new SHA1Managed();
        //            }
        //        }
        //        return _sha1;
        //    }
        //}

        inline static string DumpASN(byte[] objAsn)
        {
            AsnObject o;
            try
            {
                o = new AsnObject(objAsn);
                return o.Dump;
            }
            catch (Exception e)
            {
                string msg = "This is not an ASN.1 objest!\n" + e;
                throw new Exception(msg);
            }
        }

        public static string DumpASN(Stream objAsn)
        {
            return DumpASN(ReadAllFromStream(objAsn));
        }

        //private static SHA1 _sha1;

        public static byte[] GetPublicKeyHash(byte[] pub)
        {
            SHA1 sha1 = new SHA1Managed();
            byte[] r1 = sha1.ComputeHash(pub);
            return r1;
        }

        public static string GetPublicKeyHash64(byte[] pub)
        {
            return Convert.ToBase64String(GetPublicKeyHash(pub));
        }

        private static byte[] GetPublicKeyHash(byte[] pub, int len)
        {
            SHA1 sha1 = new SHA1Managed();
            byte[] r1 = sha1.ComputeHash(pub, 0, len);
            return r1;
        }

        public static string GetPublicKeyHash64(byte[] pub, int len)
        {
            return Convert.ToBase64String(GetPublicKeyHash(pub, len));
        }

        public static byte[] GetReducedHash(byte[] hash, int sizeInBytes)
        {
            int m = hash.Length/sizeInBytes;
            byte[] hex = new byte[sizeInBytes];
            for (int k = 0; k < sizeInBytes; k++)
            {
                int s = 0;
                for (int j = 0; j < m; j++) s += hash[k + j * sizeInBytes];
                //
                int rem;
                Math.DivRem(s, 256, out rem);
                hex[k] = (byte)rem;
            }
            return hex;
        }

        public static byte[] GetPublicKeyHashHex(byte[] pub, int sizeInBytes)
        {
            byte[] hash = GetPublicKeyHash(pub, pub.Length);
            return GetReducedHash(hash, sizeInBytes);
        }

        public static string GetPublicKeyHashHexStr(byte[] pub, int sizeInBytes)
        {
            return GetPublicKeyHashHexStr(pub, pub.Length, sizeInBytes);
        }

        public static string GetPublicKeyHashHexStr(byte[] pub, int pubLen, int sizeInBytes)
        {
            byte[] hash = GetPublicKeyHash(pub, pubLen);
            byte[] hex = GetReducedHash(hash, sizeInBytes);
            return GetHexStr(hex);
        }

        public static string GetHexStr(byte[] hex)
        {
            string str = "";
            for (int k = 0; k < hex.Length; k++) str += String.Format("{0:x2}", hex[k]);
            return str;
        }

        private static IEnumerable<string> PSEFilesX
        {
            get
            {
                lock (Lock)
                {
                    if (_pseFilesX == null)
                    {
                        _pseFilesX = new List<string>();
                        _pseFilesX.Add("kek.opq");
                        _pseFilesX.Add("masks.db3");
                        _pseFilesX.Add("mk.db3");
                        _pseFilesX.Add("rand.opq");
                        _pseFilesX.Add(PrivateKeyFileName);
                        _pseFilesX.Add(PublicKeyFileName);
                        //{
                        //    "kek.opq", "masks.db3", "mk.db3", "rand.opq", 
                        //    //
                        //    PrivateKeyFileName, PublicKeyFileName
                        //};
                    }
                }
                return _pseFilesX;
            }
        }

        private static List<string> _pseFilesX;

        private static IEnumerable<string> PSEFilesXA
        {
            get
            {
                lock (Lock)
                {
                    if (_pseFilesXa == null)
                    {
                        _pseFilesXa = new List<string>(PSEFilesX);
                        //
                        _pseFilesXa.Add(ClientReqFileName);
                        _pseFilesXa.Add(ClientCertFileName);
                    }
                }
                return _pseFilesXa;
            }
        }

        private static List<string> _pseFilesXa;

        public static XmlDocument ExportPSEByPkh(string pkh64,
            string psePwd, string privPwd
            )
        {
            string path = GetKeyPathByPkh(pkh64);
            return ExportPSEFromLocation(path, psePwd, privPwd);
        }

        public static XmlDocument ExportPSEFromLocation(string path,
            string psePwd, string privPwd
            )
        {
            if (path == null) throw new NullReferenceException("path");
            if (path.Length <= 2) throw new Exception("path is malformed");
            if (path[path.Length - 1] != '\\') path += "\\";
            //
            // XML
            //
            XmlDocument doc = new XmlDocument();
            doc.LoadXml("<KeyInfo><PrivateKey/><PublicKey/><PSE/></KeyInfo>");
            XmlElement keyInfo = (XmlElement)doc.SelectSingleNode("/*");
            XmlElement privateKeyInfo = (XmlElement)doc.SelectSingleNode("/*/PrivateKey");
            XmlElement publicKeyInfo = (XmlElement)doc.SelectSingleNode("/*/PublicKey");
            XmlElement pseInfo = (XmlElement)doc.SelectSingleNode("/*/PSE");
            //
            if (keyInfo == null) throw new NullReferenceException("KeyInfo");
            if (privateKeyInfo == null) throw new NullReferenceException("KeyInfo/PrivateKey");
            if (publicKeyInfo == null) throw new NullReferenceException("KeyInfo/PublicKey");
            if (pseInfo == null) throw new NullReferenceException("KeyInfo/PSE");
            //
            // Читаем
            //
            foreach (string pseFile in PSEFilesXA)
            {
                byte[] b1 = new byte[4096];
                if (File.Exists(path + pseFile))
                {
                    Stream f1 = File.OpenRead(path + pseFile);
                    int len1 = f1.Read(b1, 0, b1.Length);
                    string data1 = Convert.ToBase64String(b1, 0, len1);
                    //
                    XmlElement fileE = doc.CreateElement("File");
                    fileE.SetAttribute("Name", pseFile);
                    fileE.InnerText = data1;
                    pseInfo.AppendChild(fileE);
                    //
                    if (pseFile == PrivateKeyFileName)
                    {
                        privateKeyInfo.InnerText = data1;
                        //
                        DateTime kTime = File.GetCreationTimeUtc(path + pseFile);
                        string kTimeS = kTime.ToString("yyyy-MM-ddTHH:mm:ssZ");
                        keyInfo.SetAttribute("KeyTime", kTimeS);
                    }
                    //
                    if (pseFile == PublicKeyFileName)
                    {
                        publicKeyInfo.InnerText = data1;
                        keyInfo.SetAttribute("PubKeyHash", GetPublicKeyHash64(b1, len1));
                    }
                }
            }
            //
            pseInfo.SetAttribute("Password", psePwd);
            //
            privateKeyInfo.SetAttribute("Password", privPwd);
            //
            keyInfo.SetAttribute("SBox", SBox.ToString(CultureInfo.InvariantCulture));
            keyInfo.SetAttribute("PubKeyParameters", PKParameters.ToString(CultureInfo.InvariantCulture));
            //
            return doc;
        }


        //========================================================================================
        // Экспорт/импорт сведений о владельце сертификата (CertificateInfo, DER request) 

        public static XmlElement ImportCer(string path)
        {
            Stream s = File.OpenRead(path);
            return ImportCer(s);
        }

        private const int CertSizeMax = 32*1024;

        public static XmlElement ImportCer(Stream cStream)
        {
            byte[] buf = new byte[CertSizeMax];
            int len = cStream.Read(buf, 0, buf.Length);
            return ImportCer(buf, 0, len);
        }

        public static XmlElement ImportCer(byte[] cer, int offset, int len) 
        {
            if (offset != 0) throw new NotSupportedException();
            //
            Certificate certificate = new Certificate(cer, len);
            return certificate.ExpandedInfo;
        }

        public static XmlElement ImportCer(byte[] cer)
        {
            return ImportCer(cer, 0, cer.Length);
        }

        public static byte[] GetPublicKeyOfRequest(Stream reqStream)
        {
            byte[] request = ReadAllFromStream(reqStream);
            return GetPublicKeyOfRequest(request);
        }

        public static byte[] GetPublicKeyOfRequest(byte[] request)
        {
            AsnObject reqO = new AsnObject(request);
            byte[] pubKey = reqO[0][2].Encoded;
            return pubKey;
        }

        public static byte[] GetPublicKeyOfCert(Stream certStream)
        {
            byte[] certificate = ReadAllFromStream(certStream);
            return GetPublicKeyOfCert(certificate);
        }

        public static byte[] GetPublicKeyOfCert(byte[] certificate)
        {
            AsnObject certO = new AsnObject(certificate);
            //string certS = certO.Dump;
            AsnObject o0 = certO[0];
            AsnObject o06 = o0[6];
            byte[] pubKey = o06.Encoded;
            return pubKey;
        }

        public static DateTime GetNotAfterOfCert(Stream certStream)
        {
            byte[] certificate = ReadAllFromStream(certStream);
            return GetNotAfterOfCert(certificate);
        }

        public static DateTime GetNotAfterOfCert(byte[] certData)
        {
            Certificate certificate = new Certificate(certData);
            return certificate.NotAfter;
        }

        public static string GetSubjectParamOfRequest(byte[] request, OID oid)
        {
            AsnObject reqO = new AsnObject(request);
            AsnObject subject = reqO[0][1];
            for (int i = 0; i < subject.ChildCount; i++)
            {
                AsnObject pair = subject[i];
                if (pair.Tag == 17) pair = pair[0];
                //
                if (pair[0].Oid == oid)
                {
                    return pair[1].Text;
                }
            }
            throw new Exception(string.Format("Parameter '{0}' not found in the request", oid));
        }

        public static string GetCommonNameOfRequest(byte[] request)
        {
            return GetSubjectParamOfRequest(request, new OID(X500.sCommonNameOid));
        }


        //========================================================================================
        // Сведения о ключах

        public static XmlDocument GetKeyInfo(int verboseLevel)
        {
            List<string> keyDirList = GetKeyDirs();
            //
            XmlDocument doc = new XmlDocument();
            doc.LoadXml("<Keys />");
            XmlElement keysInfo = doc.DocumentElement;
            if (keysInfo == null) throw new NullReferenceException("<Keys />");
            //
            string report = "";
            //
            foreach (string dir in keyDirList)
            {
                string path = dir;
                //
                try
                {
                    XmlDocument keyInfoDoc = new XmlDocument();
                    string p2 = path + @"\key-info.xml";
                    keyInfoDoc.Load(p2);
                    XmlElement k1 = keyInfoDoc.DocumentElement;
                    if (k1 == null) throw new NullReferenceException("k1");
                    //
                    if (verboseLevel == 0)
                    {
                        string pkh64 = NormalizeBase64Id(k1.GetAttribute("PubKeyHash"));
                        string kTimeStr = k1.GetAttribute("KeyTime");
                        //
                        XmlElement k2 = doc.CreateElement("KeyInfo");
                        k2.SetAttribute("PubKeyHash", pkh64);
                        k2.SetAttribute("KeyTime", kTimeStr);
                        //
                        keysInfo.AppendChild(k2);
                    }
                    else if (verboseLevel == 8)
                    {
                        XmlNode k2 = doc.ImportNode(k1, true);
                        //
                        string pkh64 = NormalizeBase64Id(k1.GetAttribute("PubKeyHash"));
                        ((XmlElement)k2).SetAttribute("PubKeyHash", pkh64);
                        //
                        keysInfo.AppendChild(k2);
                    }
                }
                catch (Exception e)
                {
                    report += "----\nEsception:\n" + e;
                }
            }
            if (report.Length > 0)
            {
                XmlElement reportE = doc.CreateElement("Report");
                XmlElement errorsE = doc.CreateElement("Errors");
                keysInfo.AppendChild(reportE);
                reportE.AppendChild(errorsE);
                //
                errorsE.InnerText = report;
            }
            return doc;
        }

        static List<string> GetKeyDirs()
        {
            string[] filePaths = Directory.GetDirectories(RootPSEPath, "keys_*", 
                SearchOption.TopDirectoryOnly);
            //
            return new List<string>(filePaths);
        }


        //========================================================================================
        // Пароли PSE

        public static string PSEPwd
        {
            get
            {
                if (_psePwd == null) throw new Exception("PSEPwd is not set");
                return _psePwd;
            }
            set
            {
                if (_psePwd != null) throw new Exception("PSEPwd is already set");
                _psePwd = value;
            }
        }

        private static string _psePwd;


        // Пароли ключа

        public static string PrivPwd
        {
            get
            {
                if (_privPwd == null) throw new Exception("PrivPwd is not set");
                return _privPwd;
            }
            set
            {
                if (_privPwd != null) throw new Exception("PrivPwd is already set");
                _privPwd = value;
            }
        }

        private static string _privPwd;

        
        //========================================================================================
        // Информация об индивидуальных: ключе, запросе, сертификате 

        public static byte[] GetClientRequestDER(string pkh64)
        {
            return GetPSEFileBin(pkh64, ClientReqFileName);
        }

        public static byte[] GetClientCertificate(string pkh64)
        {
            return GetPSEFileBin(pkh64, ClientCertFileName);
        }

        public static byte[] GetPublicKey(string pkh64)
        {
            return GetPSEFileBin(pkh64, PublicKeyFileName);
        }

        public static byte[] GetPSEFileBin(string pkh64, string name)
        {
            string path = GetKeyPathByPkh(pkh64);
            //
            string path1 = path + @"\" + name;
            //
            byte[] data = File.ReadAllBytes(path1);
            return data;
        }

        public static string GetKeyPathByPkh(string pkh64)
        {
            byte[] pkh = Convert.FromBase64String(pkh64);
            //
            string id = "keys_" + GetHexStr(GetReducedHash(pkh, KeyIdHexSize));
            string path = RootPSEPath + id + "\\";
            //
            return path;
        }

        public static int WriteFile(string path, Stream dataStream)
        {
            Stream w = File.OpenWrite(path);
            byte[] data = ReadAllFromStream(dataStream); 
            w.Write(data, 0, data.Length);
            w.Close();
            //
            return data.Length;
        }

        public static int WriteFileToPSERoot(string path, Stream dataStream)
        {
            return WriteFile(RootPSEPath + path, dataStream);
        }

        public static int InstallCertificate(Stream certStream)
        {
            string pkh64 = GetPublicKeyHash64(GetPublicKeyOfCert(certStream));
            //throw new Exception(pkh64);
            string path = GetKeyPathByPkh(pkh64);
            return WriteFile(path + ClientCertFileName, certStream);
        }

        public static int InstallCertificate(string pkh64, byte[] certinifate) 
        {
            string path = GetKeyPathByPkh(pkh64);
            return WriteFileToPSERoot(path + ClientCertFileName, new EnvelopingStream(certinifate)); 
        }

        public static int TestContainer(string pkh64, out string report)
        {
            throw new NotImplementedException();
        }


        //========================================================================================
        // Обработка запросов 

        public static Stream CreateRequestByTpl(string pkh64, Stream reqTplStream,
            string psePwd, string privPwd)
        {
            byte[] pub = GetPublicKey(pkh64);
            AsnObject pubO = new AsnObject(pub);
            //
            // Создаём Request
            //
            byte[] reqTpl = ReadAllFromStream(reqTplStream);
            AsnObject request = new AsnObject(reqTpl);
            //
            request[0][2] = pubO;
            //
            byte[] reqTplToSign = request[0].Encoded;
            byte[] sig = SignBinary(pkh64, new EnvelopingStream(reqTplToSign), psePwd, privPwd);
            request[2].Data = Reverse(sig);
            //byte[] d2 = request[2].Data;
            //
            byte[] req = request.Encoded;
            return new EnvelopingStream(req);
        }

        public static Stream RequestTplFromCertificate(Stream certStream)
        {
            AsnObject certO = new AsnObject(ReadAllFromStream(certStream));
            //
            AsnObject r040 = AsnObject.NewSequence;
            r040.Add(new AsnObject(new OID("1.3.6.1.4.1.311.2.1.14")));
            AsnObject r040X1 = AsnObject.NewSet;
            r040X1.Add(certO[0].Tagged(3)[0]);
            r040.Add(r040X1);
            //
            AsnObject r04 = new AsnObject(true, AsnObject.CONTEXT_SPECIFIC, 0);
            r04.Add(r040);
            //
            AsnObject r0 = AsnObject.NewSequence;
            byte[] b1 = new byte[3];
            b1[0] = 0x2;
            b1[1] = 0x1;
            b1[2] = 0x0;
            AsnObject i0 = new AsnObject(b1); // new AsnObject(false, AsnObject.UNIVERSAL, AsnObject.INTEGER);
            //byte[] d0 = i0.Encoded;
            r0.Add(i0);
            r0.Add(certO[0][5]); // Subject
            r0.Add(certO[0][6]); // Public key
            r0.Add(r04);
            //
            AsnObject reqO = AsnObject.NewSequence;
            reqO.Add(r0);
            reqO.Add(certO[1]);
            reqO.Add(certO[2]);
            //
            byte[] reqData = reqO.Encoded;
            return new EnvelopingStream(reqData);
        }

        private static void SetValueByOid(AsnObject o, OID oid, string value, int tag)
        {
            AsnObject s1V = new AsnObject(value, tag);
            //
            bool ready = false;
            for (int i = 0; i < o.ChildCount; i++)
            {
                if (o[i][0].Oid == oid)
                {
                    o[i][1] = s1V;
                    ready = true;
                }
            }
            if (!ready)
            {
                AsnObject pair = AsnObject.NewSequence;
                pair.Add(new AsnObject(oid));
                pair.Add(s1V);
                //
                o.Add(pair);
            }
        }

        private static void SetValueByOid(AsnObject o, OID oid, AsnObject v)
        {
            bool ready = false;
            for (int i = 0; i < o.ChildCount; i++)
            {
                if (o[i][0].Oid == oid)
                {
                    o[i][1] = v;
                    ready = true;
                }
            }
            if (!ready)
            {
                AsnObject pair = AsnObject.NewSequence;
                pair.Add(new AsnObject(oid));
                pair.Add(v);
                //
                o.Add(pair);
            }
        }

        private static void SetSubjectValueByOid(AsnObject o, OID oid, AsnObject v)
        {
            bool ready = false;
            for (int i = 0; i < o.ChildCount; i++)
            {
                AsnObject pair = o[i];
                if (pair.Tag == 17) pair = pair[0];
                //
                if (pair[0].Oid == oid)
                {
                    pair[1] = v;
                    ready = true;
                }
            }
            if (!ready)
            {
                AsnObject pair = AsnObject.NewSequence;
                pair.Add(new AsnObject(oid));
                pair.Add(v);
                //
                AsnObject set1 = AsnObject.NewSet;
                set1.Add(pair);
                //
                o.Add(set1);
            }
        }

        public static Stream JoinRequestsTpl(Stream req0TplStream, Stream req1InfoStream)
        {
            AsnObject reqO = new AsnObject(ReadAllFromStream(req0TplStream)); 
            AsnObject info1 = new AsnObject(ReadAllFromStream(req1InfoStream)); 
            //
            AsnObject subj0 = reqO[0][1];
            AsnObject subj1 = info1[0][1];
            //
            for (int i = 0; i < subj1.ChildCount; i++)
            {
                AsnObject pair1 = subj1[i];
                if (pair1.Tag == 17) pair1 = pair1[0];
                //
                OID oid = pair1[0].Oid;
                //int tag = pair1[1].Tag;
                SetSubjectValueByOid(subj0, oid, pair1[1]);
                //
                //switch (tag)
                //{
                //    case AsnObject.BMPString:
                //    case AsnObject.IA5String:
                //    case AsnObject.PrintableString:
                //    case AsnObject.NumericString:
                //        SetSubjectValueByOid(subj0, oid, pair1[1]);
                //        break;
                //    case AsnObject.OCTET_STRING:
                //        throw new NotSupportedException();
                //    default:
                //        throw new NotSupportedException();
                //}
            }
            //
            AsnObject ext0 = reqO[0].Tagged(0)[0][1][0];
            AsnObject ext1 = info1[0].Tagged(0)[0][1][0];
            //
            Hashtable h1 = new Hashtable();
            h1["2.5.29.7"] = 1;
            h1["2.5.29.17"] = 1;
            //
            for (int i = 0; i < ext1.ChildCount; i++)
            {
                AsnObject pair1 = ext1[i];
                OID oid = pair1[0].Oid;
                if (h1.ContainsKey(oid.ToString()))
                    SetValueByOid(ext0, oid, pair1[1]);
            }
            //
            byte[] request = reqO.Encoded;
            return new EnvelopingStream(request);
        }

        public static int SaveRequest(string pkh64, Stream request)
        {
            string path = GetKeyPathByPkh(pkh64);
            return WriteFile(path + ClientReqFileName, request);
        }



        // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        // Крипто-процедуры

        //========================================================================================
        // Генерация PSE и ключей 

        private static readonly Random R1 = new Random();

        private static int GetchCb(int c, int step, int from, IntPtr userdata)
        {
            int p1 = 28 + R1.Next(33);
            //
            if ((p1 % 3) == 1) p1 -= 7;
// ReSharper disable RedundantAssignment
            if ((p1 % 3) == 2) p1 += 7;
// ReSharper restore RedundantAssignment
            //
            //Thread.Sleep(p1);
            //
            return c;	
        }

        private const string ConsoleEncodingName = "windows-1251";

        private static Encoding ConsoleEncoding
        {
            get
            {
                lock (Lock)
                {
                    if (_consoleEncoding == null)
                    {
                        _consoleEncoding = Encoding.GetEncoding(ConsoleEncodingName);
                    }
                }
                return _consoleEncoding;
            }
        }

        private static Encoding _consoleEncoding;

        public static string GenerateNewKeys(string psePwd, string privPwd)
        {
            bool usePSEPwd = (psePwd.Length > 0);
            bool usePrivPwd = (privPwd.Length > 0);
            //
            if (usePSEPwd)
            {
                if (psePwd.Length <= 3) throw new Exception("PSE password is too short");
            }
            //
            if (usePrivPwd)
            {
                if (privPwd.Length <= 3) throw new Exception("Key password is too short");
            }
            //
            // ----
            // Temporary PSE path 
            //
            string pseTemp = RootPSEPath + "\\Temp\\";
            if (!Directory.Exists(pseTemp)) Directory.CreateDirectory(pseTemp);
            //
            string pseTemlId = "temppse" + (1 + R1.Next(9997));
            string pseTempPath = pseTemp + "\\" + pseTemlId + "\\";
            //string pseTempPath = RootPSEPath + "K\\"; //   pseTemlId + "\\";
            //
            if (Directory.Exists(pseTempPath))
                throw new Exception("Temp dirrectory '" + pseTempPath + "' is occasionally non-empty");
            //
            Directory.CreateDirectory(pseTempPath);
            //
            // ----
            // PSE
            //
            Lib33.CCOM_PSE_CTX pse = Lib33.CCOMPSENew();
            if (pse.Ptr == IntPtr.Zero) 
                throw new Exception("Failure in creating PSE");
            //
            if (Lib33.CCOMPSESetRandCallback(pse, GetchCb, IntPtr.Zero) == 0)
                throw new Exception("Failure in setting random callback");
            //
            if (Lib33.CCOMPSEGenerate(pse) == 0) 
                throw new Exception("Failure in PSE generation");
            //
            if (Lib33.CCOMPSESetPath(pse, pseTempPath) == 0)
                throw new Exception("Failure in setting PSE path");
            //
            if (usePSEPwd)
            {
                //if (Lib33.CCOMPSESetPassword(pse, psePwd) == 0)
                //    throw new Exception("Failure in setting PSE password");
            }
            else
            {
                if (Lib33.CCOMPSESetPassword(pse, IntPtr.Zero, 0) == 0)
                    throw new Exception("Failure in setting PSE password");
            }
            //
            if (Lib33.CCOMPSEWrite(pse) == 0)
            {
                //long err0 = Lib33.CCOM_GetLastError();
                IntPtr err1 = Lib33.CCOM_ErrorGetString();
                throw new Exception("Failure in writing PSE:\n" + err1);
            }
            //
            Lib33.CCOMPSEFree(pse);
            //
            // ----
            // Keys
            //
            Lib33.CCOM_PSE_CTX pse2 = Lib33.CCOMPSENew();
            if (pse2.Ptr == IntPtr.Zero) 
                throw new Exception("Failure in creating PSE");
            //
            if (Lib33.CCOMPSESetPath(pse2, pseTempPath) == 0)
                throw new Exception("Failure in setting PSE path");
            //
            if (usePSEPwd)
            {
                //if (Lib33.CCOMPSESetPassword(pse2, psePwd) == 0)
                //    throw new Exception("Failure in setting PSE password");
            }
            else
            {
                if (Lib33.CCOMPSESetPassword(pse2, IntPtr.Zero, 0) == 0)
                    throw new Exception("Failure in setting PSE password");
            }
            //
		    if(Lib33.CCOMPSERead(pse2) == 0) 
                throw new Exception("Failure in reading PSE");
            //
            // key pair
            //
            Lib33.CCOM_KEY_PAIR_CTX keyPair = Lib33.CCOMKeyPairNew();
            if (keyPair.Ptr == IntPtr.Zero) 
                throw new Exception("Failure in creating PSE");
            //
		    if(Lib33.CCOMKeyPairSetPSE(keyPair, pse2) == 0) 
                throw new Exception("Failure in setting PSE for key pair");
            //
		    if(Lib33.CCOMKeyPairGenerate(keyPair, KeyAlg, PKParameters) == 0)
                throw new Exception("Failure in key pair generation");
            //
            // private
            //
            Lib33.CCOM_PRIVATE_KEY_CTX priv = Lib33.CCOMKeyPairGetPrivateKey(keyPair);
		    if(priv.Ptr == IntPtr.Zero)
                throw new Exception("Failure in getting private key (from key pair)");
            //
		    if(Lib33.CCOMPrivateKeySetPSE(priv, pse2) == 0)
                throw new Exception("Failure in connecting private key and PSE");
            //
            string privPath = pseTempPath + PrivateKeyFileName;
            if(Lib33.CCOMPrivateKeySetPath(priv, privPath) == 0) 
                throw new Exception("Failure in setting private key path");
            //
            if (usePrivPwd)
            {
                //if(Lib33.CCOMPrivateKeySetPassword(priv, privPwd, privPwd.Length) == 0)
                //    throw new Exception("Failure in setting private key password");
            }
            else
            {
                if (Lib33.CCOMPrivateKeySetPassword(priv, IntPtr.Zero, 0) == 0)
                    throw new Exception("Failure in setting private key password");
            }
            //
		    if(Lib33.CCOMPrivateKeyWrite(priv) == 0)
                throw new Exception("Failure in writing private key");
            //
            //Lib33.CCOM_PRIVATE_KEY_CTX priv2 = Lib33.CCOMPrivateKeyNew();
            //if (priv2.Ptr == IntPtr.Zero)
            //    throw new Exception("Failure in getting private key (from key pair)");
            ////
            //if (Lib33.CCOMPrivateKeySetPSE(priv2, pse2) == 0)
            //    throw new Exception("Failure in connecting private key and PSE");
            ////
            //if (Lib33.CCOMPrivateKeySetPath(priv2, privPath) == 0)
            //    throw new Exception("Failure in setting private key path");
            ////
            //if (Lib33.CCOMPrivateKeyRead(priv2) == 0)
            //    throw new Exception("Failure in reading private key");
            //
            // public
            //
            Lib33.CCOM_PUBLIC_KEY_CTX pub = Lib33.CCOMKeyPairGetPublicKey(keyPair);
            if (pub.Ptr == IntPtr.Zero)
                throw new Exception("Failure in getting public key (from key pair)");
            //
            string pubPath = pseTempPath + PublicKeyFileName;
            if (Lib33.CCOMPublicKeySetPath(pub, pubPath) == 0)
                throw new Exception("Failure in setting public key path");
            //
            if (Lib33.CCOMPublicKeyWrite(pub) == 0)
                throw new Exception("Failure in setting writing public key");
            //
            Lib33.CCOMPSEFree(pse2);
		    Lib33.CCOMKeyPairFree(keyPair);
		    Lib33.CCOMPrivateKeyFree(priv);
		    Lib33.CCOMPublicKeyFree(pub);
            //
            // ----
            // Папка с ключами
            //
            Stream f2 = File.OpenRead(pubPath);
            byte[] pubBlob = new byte[1024];
            int pubLen = f2.Read(pubBlob, 0, pubBlob.Length);
            f2.Close();
            //
            string pkh64 = GetPublicKeyHash64(pubBlob, pubLen);
            //
            //string id = "keys_" + GetPublicKeyHashHexStr(pubBlob, KeyIdHexSize);
            //string path = RootPSEPath + "\\" + id + "\\";
            //
            string path = GetKeyPathByPkh(pkh64);
            //
            if (Directory.Exists(path))
                throw new Exception("Key dirrectory '" + path + "' is occasionally non-empty");
            Directory.CreateDirectory(path);
            //
            // копируем
            //
            foreach (string pseFile in PSEFilesX)
            {
                string path1 = pseTempPath + pseFile;
                string path2 = path + pseFile;
                //
                if (File.Exists(path1))
                {
                    File.Copy(path1, path2);
                    if (!File.Exists(path2))
                        throw new Exception(string.Format("File '{0}' was not copied", path1));
                }
                //
                File.Delete(path1);
            }
            Directory.Delete(pseTempPath);
            //
            // ----
            // Отчёт
            //
            DateTime kTime = File.GetCreationTimeUtc(path + PrivateKeyFileName);
            string kTimeS = kTime.ToString("yyyy-MM-ddTHH:mm:ssZ");
            //
            XmlDocument keyInfo = ExportPSEFromLocation(path, psePwd, privPwd);
            keyInfo.Save(path + "key-info.xml");
            //
            string report = string.Format(@" keys
----------
Time: {0}
PKH: {1}
", kTimeS, pkh64);
            Stream f3 = File.OpenWrite(path + "report.log");
            byte[] reportB = ConsoleEncoding.GetBytes(report);
            f3.Write(reportB, 0, reportB.Length);
            f3.Close();
            //
            return pkh64;
        }


        public static string GenerateNewKeysGDP()
        {
            //string psePwd = "*K__" + R1.Next(1000) + "_" + R1.Next(1000) + "_" + R1.Next(1000) + "!";
            //string privPwd = "*K__" + R1.Next(1000) + "_" + R1.Next(1000) + "_" + R1.Next(1000) + "!";
            //
            //return GenerateNewKeys(psePwd, privPwd);
            //
            return GenerateNewKeys("", ""); 
        }




        // Вспомогательные функции

        public static Stream ConvertFromBase64(string data64)
        {
            return new EnvelopingStream(Convert.FromBase64String(data64));
        }

        public static string ConvertToBase64(Stream dataStream)
        {
            byte[] data = ReadAllFromStream(dataStream);
            return Convert.ToBase64String(data);
        }


        // Хеширование бинарного фрагмента

        public const int BasicChunk = 4096;

        public static byte[] SHA1Digest(Stream dataStream)
        {
            SHA1 shaM = new SHA1Managed();
            byte[] hash = shaM.ComputeHash(dataStream);
            return hash;
        }

        public static byte[] RussianDigest(int alg1, Stream dataStream)
        {
            int size = (int)dataStream.Length;
            if (size <= 0)
                throw new Exception("Cannot determine data stream size");
            //
            // ----
            // Digest
            //
            Lib33.CCOM_DIGEST_CTX digestCtx = Lib33.CCOMDigestNew(alg1);
            if (digestCtx.Ptr == IntPtr.Zero)
                throw new Exception(string.Format("Failure in creating a digest (alg = {0})", alg1));
            //
            //long digestLen2 = Lib33.CCOMDigestGetBlockLength(digestCtx);
            //throw new Exception(string.Format("digest lehgth = {0}", digestLen2));
            //
            //long sbox = Lib33.CCOMDigestCtrl(digestCtx,
            //    Lib33.CCOM_DIGEST_GET_GOSTR3411_94_SBOX, 0, IntPtr.Zero); // 22 -- правильно 
            //throw new Exception(string.Format("sbox = {0}", sbox));
            //
            //if (sbox != SBox)
            //    throw new Exception(string.Format("Non-matching sbox: {0} != {1}", sbox, SBox));
            //
            if (Lib33.CCOMDigestInit(digestCtx) == 0)
                throw new Exception("Failure in digest init");
            //
            int digestBlockLen = Lib33.CCOMDigestGetBlockLength(digestCtx);
            int p1 = 0;
            while (p1 < size)
            {
                int inl = (p1 + digestBlockLen <= size) ? digestBlockLen : size - p1;
                //
                IntPtr dataChunk = Marshal.AllocCoTaskMem(inl);
                byte[] data2 = new byte[inl];
                int read2 = dataStream.Read(data2, 0, inl);
                if (read2 != inl)
                    throw new Exception(string.Format("Wrong read size: {0} != {1}", read2, inl));
                //
                Marshal.Copy(data2, 0, dataChunk, inl);
                //
                if (Lib33.CCOMDigestUpdate(digestCtx, dataChunk, inl) == 0)
                    throw new Exception("Failure in digest update");
                //
                p1 += digestBlockLen;
            }
            //
            int digestLen = Lib33.CCOMDigestGetDigestLength(digestCtx);
            //
            byte[] digest = new byte[digestLen];
            //
            IntPtr digestPtr = Marshal.AllocCoTaskMem(digestLen);
            //
            int outl;
            if (Lib33.CCOMDigestFinal(digestCtx, digestPtr, out outl) == 0)
                throw new Exception("Failure in digest finalization");
            //
            Marshal.Copy(digestPtr, digest, 0, digestLen);
            //
            return digest;
        }

        public static byte[] Reverse(byte[] b)
        {
            byte[] x = new byte[b.Length];
            for (int j = 0; j < b.Length; j++) x[j] = b[b.Length - 1 - j];
            return x;
        }

        public static byte[] ReverseDigestForCryptoPro(byte[] inDigest)
        {
            int digestLen = inDigest.Length;
            byte[] digest = new byte[digestLen];
            //
            // переворачиваем
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

        public static byte[] RotateSigBytesForCryptoPro(byte[] sig0)
        {
            const int siglen = 64;
            byte[] sig = new byte[siglen];
            int _32 = siglen/2;
            for (int j1 = 0; j1 < _32; j1++) sig[j1] = sig0[32 + j1];
            for (int j1 = 0; j1 < _32; j1++) sig[32+j1] = sig0[j1];
            return sig;
        }


        // Подпись бинарного фрагмента

        public static byte[] SignBinary(string pkh64, Stream dataStream, //byte[] data,
            string psePwd, string privPwd
            )
        {
            DateTime t0 = DateTime.Now;
            return SignWithGivenTime(pkh64, dataStream, t0, psePwd, privPwd);
        }

        public static byte[] SignWithGivenTime(string pkh64, Stream dataStream, //byte[] data, 
            DateTime t,
            string psePwd, string privPwd,
			int flags = 0, 

            )
        {
            bool usePSEPwd = (psePwd.Length > 0);
            bool usePrivPwd = (privPwd.Length > 0);
            //
            // ----
            // PSE
            //
            string path = GetKeyPathByPkh(pkh64);
            //string path = RootPSEPath + "K\\";
            //
            Lib33.CCOM_PSE_CTX pse2 = Lib33.CCOMPSENew();
            if (pse2.Ptr == IntPtr.Zero)
                throw new Exception("Failure in creating PSE");
            //
            if (Lib33.CCOMPSESetRandCallback(pse2, GetchCb, IntPtr.Zero) == 0)
                throw new Exception("Failure in setting random callback");
            //
            if (Lib33.CCOMPSESetPath(pse2, path) == 0)
                throw new Exception("Failure in setting PSE path");
            //
            if (usePSEPwd)
            {
                //if (Lib33.CCOMPSESetPassword(pse2, psePwd) == 0)
                //    throw new Exception("Failure in setting PSE password");
            }
            else
            {
                if (Lib33.CCOMPSESetPassword(pse2, IntPtr.Zero, 0) == 0)
                    throw new Exception("Failure in setting PSE password");
            }
            //
            if (Lib33.CCOMPSERead(pse2) == 0)
                throw new Exception("Failure in reading PSE, path: " + path);
            //
            // ----
            // Key
            //
            Lib33.CCOM_PRIVATE_KEY_CTX priv = Lib33.CCOMPrivateKeyNew();
            if (priv.Ptr == IntPtr.Zero)
                throw new Exception("Failure in creating a private key");
            //
            if (Lib33.CCOMPrivateKeySetPSE(priv, pse2) == 0)
                throw new Exception("Failure in connecting private key and PSE");
            //
            string privPath = path + PrivateKeyFileName;
            //
            //if (Lib33.CCOMPrivateKeySetPath(priv, privPath) == 0)
            //    throw new Exception("Failure in setting private key path");
            //
            if (usePrivPwd)
            {
                //if (Lib33.CCOMPrivateKeySetPassword(priv, privPwd, privPwd.Length) == 0)
                //    throw new Exception("Failure in setting private key password");
            }
            else
            {
                if (Lib33.CCOMPrivateKeySetPassword(priv, IntPtr.Zero, 0) == 0)
                    throw new Exception("Failure in setting private key password");
            }
            //
            byte[] privBlob = File.ReadAllBytes(privPath);
            IntPtr privPtr = Marshal.AllocCoTaskMem(privBlob.Length);
            Marshal.Copy(privBlob, 0, privPtr, privBlob.Length);
            //
            if (Lib33.CCOMPrivateKeySetEncoded(priv, privPtr, privBlob.Length) == 0)
                throw new Exception("Failure in parsing private key");
            ////
            if (Lib33.CCOMPrivateKeyRead(priv) == 0)
            {
                long err1 = Lib33.CCOM_GetLastError();
            //    IntPtr err1sPtr = Lib33.CCOM_ErrorGetString();
            //    string err1s = Marshal.PtrToStringAnsi(err1sPtr);
                throw new Exception(string.Format("Failure in reading private key (error {0})", err1));
            }
            //
            // ----
            // Digest
            //
            int alg1 = Lib33.CCOM_DIGEST_GOSTR3411_94_CP;
            //
            byte[] digest = ReverseDigestForCryptoPro(RussianDigest(alg1, dataStream));
            //
            // ----
            // Signature
            //
            Lib33.CCOM_SIGN_CTX signCtx = Lib33.CCOMSignNew(priv);
            if (signCtx.Ptr == IntPtr.Zero)
            {
                //long err1 = Lib33.CCOM_GetLastError();
                //IntPtr err1sPtr = Lib33.CCOM_ErrorGetString();
                //string err1s = Marshal.PtrToStringAnsi(err1sPtr);
                throw new Exception("Failure in creating sign context");
            }
            //
            //-------------------------------------------------------------------
            // Not needed for DIGEST !
            //
            //if(Lib33.CCOMSignInit(signCtx) == 0)
            //    throw new Exception("Failure in sign initialization");
            //-------------------------------------------------------------------
            //
            IntPtr digestPtr = Marshal.AllocCoTaskMem(digest.Length);
            Marshal.Copy(digest, 0, digestPtr, digest.Length);
            //
            IntPtr sigPtr = Marshal.AllocCoTaskMem(256);
            int siglen = 256;
            //
            if (Lib33.CCOMSignDigest(signCtx, digestPtr, digest.Length, sigPtr, ref siglen) == 0)
                throw new Exception("Failure in signing digest");
            //
            byte[] sig0 = new byte[siglen];
            Marshal.Copy(sigPtr, sig0, 0, siglen);
            //
            byte[] sig = RotateSigBytesForCryptoPro(sig0);
            //
            return sig;
        }

        public static byte[] SignBinaryCMS(string pkh64, Stream dataToSign, DateTime t, 
            string psePwd, string privPwd 
            )
        {
            string path = GetKeyPathByPkh(pkh64);
            //throw new Exception(pkh64 + " : " + path);
            //
            byte[] certificate = ReadAllFromStream(File.OpenRead(
                                                       path + ClientCertFileName
                                                       ));
            AsnObject certO = new AsnObject(certificate);
            //
            AsnObject m = AsnObject.NewSequence
                .Add(new AsnObject(new OID("1.2.840.113549.1.7.2")))
                .Add(new AsnObject(true, AsnObject.CONTEXT_SPECIFIC, 0));
            AsnObject m2 = (m[1].Add(AsnObject.NewSequence))[0];
            m2.Add(new AsnObject(1))
                .Add(AsnObject.NewSet)
                .Add(AsnObject.NewSequence)
                .Add(AsnObject.NewSet);
            //
            m2[1].Add(AsnObject.NewSequence.Add(new AsnObject(new OID("1.2.643.2.2.9"))));
            //
            m2[2].Add(new AsnObject(new OID("1.2.840.113549.1.7.1")));
            //
            m2[3].Add(AsnObject.NewSequence);
            AsnObject m3 = m2[3][0];
            //
            m3.Add(new AsnObject(1))
                .Add(AsnObject.NewSequence)
                .Add(AsnObject.NewSequence)
                .Add(AsnObject.NewSequence);
            //
            for (int q = 0; q <= 3 && q <= certO[0].ChildCount; ++q)
            {
                if (certO[0][q].Tag == AsnObject.SEQUENCE)
                    if (certO[0][q].ChildCount > 0)
                        if (certO[0][q][0].Tag == AsnObject.SET)
                            m3[1].Add(certO[0][q]);
            }
            m3[1].Add(certO[0][1]);
            //
            m3[2].Add(new AsnObject(new OID("1.2.643.2.2.9")))
                .Add(new AsnObject(false, AsnObject.UNIVERSAL, AsnObject.NULL));
            //
            m3[3].Add(new AsnObject(new OID("1.2.643.2.2.19")))
                .Add(new AsnObject(false, AsnObject.UNIVERSAL, AsnObject.NULL));
            //
            m3.Add(new AsnObject(false, AsnObject.UNIVERSAL, AsnObject.OCTET_STRING));
            //
            // Подписываем
            //
            byte[] sign = SignBinary(pkh64, dataToSign, psePwd, privPwd);
            //
            m3[4].Data = sign; 
            //
            //m.IndefiniteLength = true;
            //m[1].IndefiniteLength = true;
            //m[1][0][2].IndefiniteLength = true;
            ////
            //				Runtime.Echo(m.Dump);
            //				//
            //				string path2 = @"z:\MMBANK\_sig.der";
            //				FileStream writer = File.Open(path2,FileMode.Create,FileAccess.Write);				
            //				byte[] data2 = m.Encoded;
            //				writer.Write(data2,0,(int)data2.Length);
            //				writer.Close();
            //
            return m.Encoded;
        }

        //static void f(XmlElement E)
        //{
        //    Alg_1_8_8 a = new Alg_1_8_8();
        //    a.CreateSignature(ISigner signer,ref XmlElement E,bool enveloped,string hashOid)
        //}



        // Проверка подписи 

        public static int VerifySignature(string pkh64, Stream dataStream, byte[] sig)
        {
            byte[] pubKey = File.ReadAllBytes(GetKeyPathByPkh(pkh64) + PublicKeyFileName);
            //
            return VerifySignature(pubKey, dataStream, sig);
        }

        public static int VerifySignature(byte[] pubKey, Stream dataStream, byte[] sig)
        {
            // ----
            // Signature blob
            //
            const int siglen = 64;
            byte[] sig2 = RotateSigBytesForCryptoPro(sig); 
            //
            // ----
            // Public key 
            //
            Lib33.CCOM_PUBLIC_KEY_CTX publicKeyCtx = Lib33.CCOMPublicKeyNew(); 
            if (publicKeyCtx.Ptr == IntPtr.Zero)
                throw new Exception("Failure in creating pub key context");
            //
            IntPtr pubKeyPtr = Marshal.AllocCoTaskMem(pubKey.Length);
            Marshal.Copy(pubKey, 0, pubKeyPtr, pubKey.Length);
            //
            if (Lib33.CCOMPublicKeySetEncoded(publicKeyCtx, pubKeyPtr, pubKey.Length) == 0)
                throw new Exception("Failure in parsing pub key");
            //
            if (Lib33.CCOMPublicKeyRead(publicKeyCtx) == 0)
                throw new Exception("Failure in reading pub key");
            //
            // ----
            // Digest
            //
            int alg1 = Lib33.CCOM_DIGEST_GOSTR3411_94_CP;
            //
            byte[] digest = ReverseDigestForCryptoPro(RussianDigest(alg1, dataStream));
            //
            // ----
            // Signature
            //
            Lib33.CCOM_SIGN_CTX signCtx = Lib33.CCOMSignNew(publicKeyCtx);
            if (signCtx.Ptr == IntPtr.Zero)
                throw new Exception("Failure in creating sign context (from public key)");
            //
            IntPtr digestPtr = Marshal.AllocCoTaskMem(digest.Length);
            Marshal.Copy(digest, 0, digestPtr, digest.Length);
            //
            IntPtr sigPtr = Marshal.AllocCoTaskMem(siglen);
            Marshal.Copy(sig2, 0, sigPtr, siglen);
            //
            if (Lib33.CCOMVerifyDigest(signCtx, digestPtr, digest.Length, sigPtr, siglen) == 0)
            {
                return 0; // signature is wrong; 
            }
            return 1; // signature is Ok 
        }

        public static int VerifyRequest(byte[] request)
        {
            AsnObject requestO = new AsnObject(request);
            byte[] data = requestO[0].Encoded;
            //
            byte[] pubKey = requestO[0][2].Encoded;
            //
            byte[] sig = requestO[2].Encoded;
            //
            int r = VerifySignature(pubKey, new EnvelopingStream(data), sig);
            return r;
        }





        //========================================================================================
        // Утилиты 

        inline static byte[] ReadAllFromStream(EnveloppingStream s)
        {
            Blob buf;
			buf.Allocate(1024);
            //
            s.Position = 0;
            //
            MemoryStream ms1 = new MemoryStream();
            int len = s.Read(buf, 0, buf.Length);
            while (len > 0)
            {
                ms1.Write(buf, 0, len);
                //
                len = s.Read(buf, 0, buf.Length);
            }
            //
            long l = ms1.Length;
            byte[] result = new byte[l];
            ms1.Position = 0;
            ms1.Read(result, 0, (int)l);
            //
            return result;
        }
        
    }
}
