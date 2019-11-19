#ifndef RSA_PRIVATE_KEY_H
#define RSA_PRIVATE_KEY_H

#include "NTL/ZZ.h"
#include "public_key.h"

#define DEFAULT_E 65537

using namespace NTL;

namespace RSA
{
class PrivateKey
{
public:
    PrivateKey(int size = 0);

    ZZ e;
    ZZ d;
    ZZ dP;
    ZZ dQ;
    ZZ n;
    ZZ p;
    ZZ q;
    ZZ qInv;

    PublicKey publicKey();
    long Decrypt(unsigned char * plaintext, unsigned char const * const ciphertext, long length);
    void ExportToFile(char* file);
    void ImportFromFile(char* file);
};
} // namespace RSA

#endif
