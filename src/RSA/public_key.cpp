#include "fstream"
#include "nlohmann/json.hpp"
#include "math.h"
#include "public_key.h"
#include "utils.h"

using json = nlohmann::json;

namespace RSA
{
PublicKey::PublicKey(){};
PublicKey::PublicKey(const ZZ &n, const ZZ &e) : n(n), e(e){};

long PublicKey::Encrypt(unsigned char *ciphertext, unsigned char const *const plaintext, long length)
{
    ZZ c, m;

    ZZFromBytes(m, plaintext, length);
    m |= ZZ(1) << (8 * length);
    Math::ModExp(c, m, e, n);
    length = NumBytes(c);
    BytesFromZZ(ciphertext, c, length);

    return length;
}

void PublicKey::Read(std::string path)
{
    std::ifstream file(path);

    json key;
    file >> key;

    Utils::HexToZZ(e, key["e"].get<std::string>());
    Utils::HexToZZ(n, key["n"].get<std::string>());

    file.close();
}

void PublicKey::Write(std::string path)
{
    json key;
    key["e"] = Utils::ZZtoHex(e);
    key["n"] = Utils::ZZtoHex(n);

    std::ofstream file(path);
    file << key.dump(2) << std::endl;
    file.close();
}
} // namespace RSA
