#include <cstdio>
#include <string>
#include "catch2/catch.hpp"
#include "RSA/math.h"
#include "RSA/private_key.h"

using namespace RSA;

TEST_CASE("RSA::PrivateKey::PrivateKey(int size = 0)", "[key]")
{
    for (int i = 128; i <= 4096; i *= 2)
    {
        SECTION("when size is " + std::to_string(i))
        {
            PrivateKey key(i);

            REQUIRE(Math::ModExp(Math::ModExp(ZZ(127), key.e, key.n), key.d, key.n) == 127);
            REQUIRE(key.e == DEFAULT_E);
            REQUIRE(key.dP == InvMod(key.e, key.p - 1));
            REQUIRE(key.dQ == InvMod(key.e, key.q - 1));
            REQUIRE(key.p > key.q);
            REQUIRE(key.n == key.p * key.q);
            REQUIRE(NumBits(key.n) == i);
            REQUIRE(key.qInv == InvMod(key.q, key.p));
        }
    }
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

TEST_CASE(
    "void RSA::PrivateKey::Read(std::string path)"
    "void RSA::PrivateKey::Write(std::string path)",
    "[key]")
{
    PrivateKey key(1024);
    key.Write("key.json");

    PrivateKey other_key;
    other_key.Read("key.json");

    REQUIRE(key.d == other_key.d);
    REQUIRE(key.e == other_key.e);
    REQUIRE(key.dP == other_key.dP);
    REQUIRE(key.dQ == other_key.dQ);
    REQUIRE(key.n == other_key.n);
    REQUIRE(key.p == other_key.p);
    REQUIRE(key.q == other_key.q);
    REQUIRE(key.qInv == other_key.qInv);

    remove("key.json");
}

TEST_CASE(
    "void RSA::PublicKey::Read(std::string path)"
    "void RSA::PublicKey::Write(std::string path)",
    "[key]")
{
    PublicKey key = PrivateKey(1024).publicKey();
    key.Write("key.json");

    PublicKey other_key;
    other_key.Read("key.json");

    REQUIRE(key.e == other_key.e);
    REQUIRE(key.n == other_key.n);

    remove("key.json");
}
