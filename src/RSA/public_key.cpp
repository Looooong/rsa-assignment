#include "math.h"
#include "public_key.h"

namespace RSA
{
PublicKey::PublicKey(const ZZ &n, const ZZ &e) : n(n), e(e){};

long PublicKey::Encrypt(unsigned char *ciphertext, unsigned char const *const plaintext, long length)
{
    ZZ c, m;

    ZZFromBytes(m, plaintext, length);
    m |= ZZ(1) << (8 * length);
    Math::ModExp(c, m, e, n);
    length = NumBytes(c);
    BytesFromZZ(ciphertext, c, length);

    return length;
}
} // namespace RSA
