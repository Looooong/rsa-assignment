#include "math.h"

using namespace NTL;

namespace RSA
{
namespace Math
{
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
} // namespace Math
} // namespace RSA
