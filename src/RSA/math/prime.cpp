#include "prime.h"

namespace RSA
{
namespace Math
{
namespace Prime
{
bool CompositenessWitness(const ZZ &a, const ZZ &n)
{
    if (a == 0)
        return false;

    ZZ d = n - 1;
    long r = FactorPower2(d);

    return CompositenessWitness(a, n, r, d);
}

bool CompositenessWitness(const ZZ &a, const ZZ &n, long r, const ZZ &d)
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

ZZ Generate(const ZZ &lowerBound, const ZZ &upperBound)
{
    ZZ n;
    Generate(n, lowerBound, upperBound);
    return n;
}

void Generate(ZZ &n, const ZZ &lowerBound, const ZZ &upperBound)
{
    ZZ bound = upperBound - lowerBound;

    do
    {
        n = lowerBound + RandomBnd(bound);
        n |= 1;
    } while (!Test(n));
};

bool Test(const ZZ &n)
{
    if (n <= 1)
        return false;

    for (int i = 0; i < 100; i++)
    {
        if (n <= first100[i])
            return true;

        if (n % first100[i] == 0)
            return false;
    }

    return TestMillerRabin(n);
};

bool TestMillerRabin(const ZZ &n)
{
    if (n <= 1)
        return false;

    ZZ nMinus1 = n - 1;
    ZZ d = nMinus1;
    long r = FactorPower2(d);

    if (CompositenessWitness(ZZ(2), n, r, d))
        return false;

    ZZ a;

    for (int i = 0; i < MILLER_RABIN_TRIALS_COUNT; i++)
    {
        RandomBnd(a, nMinus1);

        if (CompositenessWitness(a, n, r, d))
            return false;
    }

    return true;
}
} // namespace Prime
} // namespace Math
} // namespace RSA
