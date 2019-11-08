#ifndef RSA_MATH_PRIME_H
#define RSA_MATH_PRIME_H

#include "../math.h"

#define MILLER_RABIN_TRIALS_COUNT 6

using namespace NTL;

namespace RSA
{
namespace Math
{
namespace Prime
{
// n = 2^r * d + 1
bool compositenessWitness(const ZZ &a, const ZZ &n);
bool compositenessWitness(const ZZ &a, const ZZ &n, long r, const ZZ &d);
bool testMillerRabin(const ZZ &n);
} // namespace Prime
} // namespace Math
} // namespace RSA
#endif
