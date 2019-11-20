#include <fstream>
#include "nlohmann/json.hpp"
#include "math.h"
#include "math/prime.h"
#include "private_key.h"
#include "utils.h"

using json = nlohmann::json;

namespace RSA
{
PrivateKey::PrivateKey(int size) : e(DEFAULT_E)
{
    if (size <= 0)
        return;

    int pSize = size / 2 + 1;
    int qSize = size / 2 - 1 + size % 2;
    ZZ lowerBound, upperBound;

    lowerBound = ZZ(3) << (pSize - 2);
    upperBound = ZZ(1) << pSize;

    Math::Prime::Generate(p, lowerBound, upperBound);

    lowerBound = ZZ(3) << (qSize - 2);
    upperBound = ZZ(1) << qSize;

    Math::Prime::Generate(q, lowerBound, upperBound);

    n = p * q;

    Math::ModInv(d, e, (p - 1) * (q - 1));
    Math::ModInv(dP, e, p - 1);
    Math::ModInv(dQ, e, q - 1);
    Math::ModInv(qInv, q, p);
}

PublicKey PrivateKey::publicKey()
{
    return PublicKey(n, e);
}

long PrivateKey::Decrypt(unsigned char *plaintext, unsigned char const *const ciphertext, long length)
{
    ZZ c, h, m, m1, m2;

    ZZFromBytes(c, ciphertext, length);
    Math::ModExp(m1, c, dP, p);
    Math::ModExp(m2, c, dQ, q);
    h = qInv * (m1 - m2) % p;
    m = m2 + h * q;
    length = NumBits(m) / 8;
    BytesFromZZ(plaintext, m, length);

    return length;
}

void PrivateKey::Read(std::string path)
{
    std::ifstream file(path);

    json key;
    file >> key;

    Utils::HexToZZ(d, key["d"].get<std::string>());
    Utils::HexToZZ(e, key["e"].get<std::string>());
    Utils::HexToZZ(dP, key["dP"].get<std::string>());
    Utils::HexToZZ(dQ, key["dQ"].get<std::string>());
    Utils::HexToZZ(n, key["n"].get<std::string>());
    Utils::HexToZZ(p, key["p"].get<std::string>());
    Utils::HexToZZ(q, key["q"].get<std::string>());
    Utils::HexToZZ(qInv, key["qInv"].get<std::string>());

    file.close();
}

void PrivateKey::Write(std::string path)
{
    json key;
    key["d"] = Utils::ZZtoHex(d);
    key["e"] = Utils::ZZtoHex(e);
    key["dP"] = Utils::ZZtoHex(dP);
    key["dQ"] = Utils::ZZtoHex(dQ);
    key["n"] = Utils::ZZtoHex(n);
    key["p"] = Utils::ZZtoHex(p);
    key["q"] = Utils::ZZtoHex(q);
    key["qInv"] = Utils::ZZtoHex(qInv);

    std::ofstream file(path);
    file << key.dump(2) << std::endl;
    file.close();
}
} // namespace RSA
