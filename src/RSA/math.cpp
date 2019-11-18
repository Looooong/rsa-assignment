#include "math.h"

using namespace NTL;

namespace RSA
{
namespace Math
{
long FactorPower2(ZZ &n)
{
    long r;
    for (r = 0; (n & 1) == 0; r++, n >>= 1)
        ;
    return r;
}

ZZ ModExp(ZZ b, ZZ e, const ZZ &m)
{
    ZZ r;
    ModExp(r, b, e, m);
    return r;
}

void ModExp(ZZ &r, ZZ b, ZZ e, const ZZ &m)
{
    if (m == 1)
    {
        r = 0;
        return;
    }

    for (r = 1, b %= m; e > 0; e >>= 1)
    {
        if ((e & 1) == 1)
            r = (r * b) % m;

        b = (b * b) % m;
    }
}

ZZ ModInv(const ZZ &a, const ZZ &m) {
    ZZ b;
    ModInv(b, a, m);
    return b;
}

void ModInv(ZZ &b, const ZZ &a, const ZZ &m) {
    InvMod(b, a, m);
}
} // namespace Math
} // namespace RSA
