#include "utils.h"

namespace RSA
{
namespace Utils
{
unsigned char HexToUChar(char c)
{
    switch (c)
    {
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    case 'a':
        return 10;
    case 'b':
        return 11;
    case 'c':
        return 12;
    case 'd':
        return 13;
    case 'e':
        return 14;
    case 'f':
        return 15;
    }
}

ZZ HexToZZ(std::string s)
{
    ZZ z;
    HexToZZ(z, s);
    return z;
}

void HexToZZ(ZZ &z, std::string s)
{
    z = 0;
    int n = (s.length() + 1) / 2;
    unsigned char *b = new unsigned char[n];

    for (int i = 0; i < n; i++)
    {
        b[i] = HexToUChar(s.back());
        s.pop_back();
        b[i] |= HexToUChar(s.back()) << 4;
        s.pop_back();
    }

    ZZFromBytes(z, b, n);
    delete b;
}

std::string ZZtoHex(const ZZ &z)
{
    if (z == 0)
        return "00";

    static char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    std::string s;
    int n = NumBytes(z);
    unsigned char *b = new unsigned char[n];
    BytesFromZZ(b, z, n);

    for (int i = n - 1; i >= 0; i--)
    {
        s.push_back(hex[b[i] >> 4]);
        s.push_back(hex[b[i] & 0xF]);
    }

    delete b;

    return s;
}
} // namespace Utils
} // namespace RSA
