#ifndef RSA_MATH_H
#define RSA_MATH_H

#include <NTL/ZZ.h>

using namespace NTL;

namespace RSA
{
namespace Math
{
long FactorPower2(ZZ &n);
ZZ ModExp(ZZ b, ZZ e, const ZZ &m);
void ModExp(ZZ &r, ZZ b, ZZ e, const ZZ &m);
} // namespace Math
} // namespace RSA

#endif
