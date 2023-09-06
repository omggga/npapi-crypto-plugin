using System.IO;
using .ASN;
using .Algorithms;

namespace 
{
    class XmlDSigVerificator33 : IVerificator
    {
        public bool VerifySignature(byte[] signatureCMS, byte[] data, byte[] certificate)
        {
            AsnObject m = new AsnObject(signatureCMS);
            byte[] signature = m[1][0][3][0][4].Data;
            //
            byte[] pubKey = XmlDSigHelper33.GetPublicKeyOfCert(certificate);
            //
            Stream dataStream = new EnvelopingStream(data);
            return XmlDSigHelper33.VerifySignature(pubKey, dataStream, signature) > 0;
        }
    }
}
