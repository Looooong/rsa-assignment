#include "prime.h"

namespace RSA
{
namespace Math
{
namespace Prime
{
bool compositenessWitness(const ZZ &a, const ZZ &n)
{
    if (a == 0)
        return false;

    ZZ d = n - 1;
    long r = FactorPower2(d);

    return compositenessWitness(a, n, r, d);
}

bool compositenessWitness(const ZZ &a, const ZZ &n, long r, const ZZ &d)
{
    if (a == 0)
        return false;

    ZZ x;
    ZZ nMinus1 = n - 1;

    ModExp(x, a, d, n);

    if (x == 1 || x == nMinus1)
        return false;

    for (; r > 1; r--)
    {
        x = (x * x) % n;

        if (x == nMinus1)
            return false;
    }

    return true;
}

bool testMillerRabin(const ZZ &n)
{
    if (n <= 1)
        return false;

    ZZ nMinus1 = n - 1;
    ZZ d = nMinus1;
    long r = FactorPower2(d);

    if (compositenessWitness(ZZ(2), n, r, d))
        return false;

    ZZ a;

    for (int i = 0; i < MILLER_RABIN_TRIALS_COUNT; i++)
    {
        RandomBnd(a, nMinus1);

        if (compositenessWitness(a, n, r, d))
            return false;
    }

    return true;
}
} // namespace Prime
} // namespace Math
} // namespace RSA
