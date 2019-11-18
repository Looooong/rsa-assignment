#ifndef RSA_PUBLIC_KEY_H
#define RSA_PUBLIC_KEY_H

#include "NTL/ZZ.h"

using namespace NTL;

namespace RSA
{
class PublicKey
{
public:
    ZZ e;
    ZZ n;

    PublicKey(const ZZ &n, const ZZ &e);
    long Encrypt(unsigned char *ciphertext, unsigned char const *const plaintext, long length);
};
} // namespace RSA

#endif
