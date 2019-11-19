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
ZZ ModInv(const ZZ &a, const ZZ &m);
void ModInv(ZZ &b, const ZZ &a, const ZZ &m);
// (g, x, y) = EGCD(a, b)
void EGCD(ZZ &g, ZZ &x, ZZ &y, const ZZ &a, const ZZ &b);
std::string zToString(const ZZ &z);
} // namespace Math
} // namespace RSA

#endif
