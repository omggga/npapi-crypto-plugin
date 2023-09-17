using System.IO;
using .ASN;
using .Algorithms;

namespace
{
    public class XmlDSigVerificator33 : IVerificator
    {
        public bool VerifySignature(byte[] signatureCMS, byte[] data, byte[] certificate)
        {
            var asnObject = new AsnObject(signatureCMS);
            byte[] signature = asnObject[1][0][3][0][4].Data;

            byte[] publicKey = XmlDSigHelper33.GetPublicKeyOfCert(certificate);

            using (Stream dataStream = new EnvelopingStream(data))
            {
                return XmlDSigHelper33.VerifySignature(publicKey, dataStream, signature) > 0;
            }
        }
    }
}
