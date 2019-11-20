#ifndef RSA_UTILS_H
#define RSA_UTILS_H

#include <string>
#include "NTL/ZZ.h"

using namespace NTL;

namespace RSA
{
namespace Utils
{
ZZ HexToZZ(std::string s);
void HexToZZ(ZZ &z, std::string s);
std::string ZZtoHex(const ZZ &z);
}
} // namespace RSA

#endif
