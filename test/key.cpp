#include <string>
#include "catch2/catch.hpp"
#include "RSA/private_key.h"

using namespace RSA;

TEST_CASE("RSA::PrivateKey::PrivateKey(int size = 0)", "[key]")
{
    for (int i = 128; i <= 4096; i *= 2)
    {
        SECTION("when size is " + std::to_string(i))
        {
            PrivateKey key(i);

            REQUIRE(key.e == DEFAULT_E);
            REQUIRE(key.dP == InvMod(key.e, key.p - 1));
            REQUIRE(key.dQ == InvMod(key.e, key.q - 1));
            REQUIRE(key.p > key.q);
            REQUIRE(key.n == key.p * key.q);
            REQUIRE(NumBits(key.n) == i);
            REQUIRE(key.qInv == InvMod(key.q, key.p));
        }
    }
    PrivateKey key(128);
    key.ExportToFile((char*) "conbocuoi.txt");
}

TEST_CASE(
    "long RSA::PublicKey::Encrypt(unsigned char *ciphertext, unsigned char const *const plaintext, long length)\n"
    "long RSA::PrivateKey::Decrypt(unsigned char * plaintext, unsigned char const * const ciphertext, long length)",
    "[key]")
{
    PrivateKey privateKey(1024);

    long length = 12, ciphertextLength, plaintextLength;
    unsigned char message[] = "Hello World!";
    unsigned char ciphertext[1024];
    unsigned char plaintext[1024];

    ciphertextLength = privateKey.publicKey().Encrypt(ciphertext, message, length);
    plaintextLength = privateKey.Decrypt(plaintext, ciphertext, ciphertextLength);

    REQUIRE(plaintextLength == length);

    for (int i = 0; i < length; i++)
    {
        REQUIRE(plaintext[i] == message[i]);
    }
}
