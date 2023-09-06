using System;
using .Algorithms;

namespace 
{
    class XmlDSigSigner33 : ISigner
    {
        private readonly string _mPkh64;

        private readonly string _mPsePwd;

        private readonly string _mPrivPwd;

        private readonly byte[] _mCertificate;

        private Certificate _mCertObject;

        public XmlDSigSigner33(string pkh64, 
            string psePwd, string privPwd, 
            byte[] certificate
            )
        {
            _mPkh64 = pkh64;
            _mPsePwd = psePwd;
            _mPrivPwd = privPwd;
            _mCertificate = certificate;
            //
            _mCertObject = new Certificate(certificate);
        }

        public byte[] GetCertData()
        {
            return _mCertificate;
        }

        public string GetCertParameter(string name)
        {
            return _mCertObject.GetCertParameter(name);
        }

        public string CreateCMSSignature64(byte[] data)
        {
            byte[] signatureCMS =
                XmlDSigHelper33.SignBinaryCMS(_mPkh64, new EnvelopingStream(data), 
                DateTime.Now, 
                _mPsePwd, _mPrivPwd);
            //
            return Convert.ToBase64String(signatureCMS);
        }

        public string CreateCMSSignature64(byte[] data, string hashOid)
        {
            byte[] signatureCMS =
                XmlDSigHelper33.SignBinaryCMS(_mPkh64, new EnvelopingStream(data), 
                DateTime.Now, 
                _mPsePwd, _mPrivPwd);
            //
            return Convert.ToBase64String(signatureCMS);
        }
    }
}
