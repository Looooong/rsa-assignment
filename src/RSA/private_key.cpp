#include "private_key.h"
#include "math.h"
#include "math/prime.h"
#include "base64.h"
#include <tinyxml.h>
#include <fstream>
#include <string>
namespace RSA
{
PrivateKey::PrivateKey(int size) : e(DEFAULT_E)
{
    if (size <= 0)
        return;

    int pSize = size / 2 + 1;
    int qSize = size / 2 - 1 + size % 2;
    ZZ lowerBound, upperBound;

    lowerBound = ZZ(3) << (pSize - 2);
    upperBound = ZZ(1) << pSize;

    Math::Prime::Generate(p, lowerBound, upperBound);

    lowerBound = ZZ(3) << (qSize - 2);
    upperBound = ZZ(1) << qSize;

    Math::Prime::Generate(q, lowerBound, upperBound);

    n = p * q;

    ZZ phi = (p - 1) * (q - 1);
    
    Math::ModInv(d, e, phi);
    Math::ModInv(dP, e, p - 1);
    Math::ModInv(dQ, e, q - 1);
    Math::ModInv(qInv, q, p);
}

PublicKey PrivateKey::publicKey()
{
    return PublicKey(n, e);
}

long PrivateKey::Decrypt(unsigned char *plaintext, unsigned char const *const ciphertext, long length)
{
    ZZ c, h, m, m1, m2;

    ZZFromBytes(c, ciphertext, length);
    Math::ModExp(m1, c, dP, p);
    Math::ModExp(m2, c, dQ, q);
    h = qInv * (m1 - m2) % p;
    m = m2 + h * q;
    length = NumBits(m) / 8;
    BytesFromZZ(plaintext, m, length);

    return length;
}

void PrivateKey::ExportToFile(char* filename)
{
    TiXmlDocument *pDoc =new TiXmlDocument("RSA Private Key");
    TiXmlElement *RSAPrivateKey = new TiXmlElement("RSAPrivateKey");
    pDoc->LinkEndChild(RSAPrivateKey);
    TiXmlElement *modulus = new TiXmlElement("modulus");
    modulus->LinkEndChild(new TiXmlText(Math::zToString(n)));
    RSAPrivateKey->LinkEndChild(modulus);
    TiXmlElement *publicExponent = new TiXmlElement("publicExponent");
    publicExponent->LinkEndChild(new TiXmlText(Math::zToString(e)));
    RSAPrivateKey->LinkEndChild(publicExponent);
    TiXmlElement *privateExponent = new TiXmlElement("privateExponent");
    privateExponent->LinkEndChild(new TiXmlText(Math::zToString(d)));
    RSAPrivateKey->LinkEndChild(privateExponent);
    TiXmlElement *prime1 = new TiXmlElement("prime1");
    prime1->LinkEndChild(new TiXmlText(Math::zToString(p)));
    RSAPrivateKey->LinkEndChild(prime1);
    TiXmlElement *prime2 = new TiXmlElement("prime2");
    prime2->LinkEndChild(new TiXmlText(Math::zToString(q)));
    RSAPrivateKey->LinkEndChild(prime2);
    TiXmlElement *exponent1 = new TiXmlElement("exponent1");
    exponent1->LinkEndChild(new TiXmlText(Math::zToString(dP)));
    RSAPrivateKey->LinkEndChild(exponent1);
    TiXmlElement *exponent2 = new TiXmlElement("exponent2");
    exponent2->LinkEndChild(new TiXmlText(Math::zToString(dQ)));
    RSAPrivateKey->LinkEndChild(exponent2);
    TiXmlElement *coefficient = new TiXmlElement("coefficient");
    coefficient->LinkEndChild(new TiXmlText(Math::zToString(qInv)));
    RSAPrivateKey->LinkEndChild(coefficient);
    
    TiXmlPrinter printer;
    pDoc->Accept(&printer);   
    const char* str = printer.CStr();
    std::ofstream outfile;
    outfile.open(filename, std::fstream::out);
    // outfile << BASE64::base64_encode(reinterpret_cast<const unsigned char*>(str), std::strlen(str));
    outfile << str;
    outfile.close();
}

} // namespace RSA
