#include "private_key.h"
#include "math.h"
#include "math/prime.h"

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

    Math::ModInv(dP, e, p - 1);
    Math::ModInv(dQ, e, q - 1);
    Math::ModInv(qInv, q, p);
}

PublicKey PrivateKey::publicKey()
{
    return PublicKey(n, e);
}

long PrivateKey::Descrypt(unsigned char *plaintext, unsigned char const *const ciphertext, long length)
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
} // namespace RSA
