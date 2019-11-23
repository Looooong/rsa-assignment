#include <string>
#include "catch2/catch.hpp"
#include "RSA/math/prime.h"

using namespace RSA::Math::Prime;

TEST_CASE("const long RSA::Math::Prime::first100[]", "[math]")
{
    REQUIRE(sizeof(first100) / sizeof(*first100) == 100);

    for (int i = 0; i < 100; i++)
    {
        long n = first100[i];

        SECTION("when n is " + std::to_string(n))
        {
            for (int j = 2; j <= SqrRoot(n); j++)
            {
                REQUIRE(n % j != 0);
            }
        }
    }
}

TEST_CASE("bool compositenessWitness(const ZZ &a, const ZZ &n)", "[math]")
{
    REQUIRE(CompositenessWitness(ZZ(0), ZZ(3)) == false);
    REQUIRE(CompositenessWitness(ZZ(0), ZZ(5)) == false);
    REQUIRE(CompositenessWitness(ZZ(0), ZZ(7)) == false);
    REQUIRE(CompositenessWitness(ZZ(137), ZZ(221)) == true);
    REQUIRE(CompositenessWitness(ZZ(174), ZZ(221)) == false);

    PrimeSeq s;
    s.next();

    for (int i = 0; i < 250; i++)
    {
        ZZ n(s.next());

        SECTION("when n is " + std::to_string(conv<long>(n)))
        {
            for (ZZ j(2); j < n - 1; j++)
            {

                REQUIRE(CompositenessWitness(j, n) == false);
            }
        }
    }
}

TEST_CASE("ZZ RSA::Math::Prime::Generate(const ZZ &lowerBound, const ZZ &upperBound)", "[math]")
{
    ZZ lowerBound, upperBound, n;

    SECTION("generate prime number from 2^2013 to 2^1024")
    {
        lowerBound = ZZ(1) << 1023;
        upperBound = ZZ(1) << 1024;

        for (int i = 0; i < 10; i++)
        {
            n = Generate(lowerBound, upperBound);

            REQUIRE(n >= lowerBound);
            REQUIRE(n < upperBound);
            REQUIRE(NumBits(n) == 1024);
            REQUIRE(ProbPrime(n) == true);
            REQUIRE(Test(n) == true);
        }
    }

    SECTION("generate prime number from 2^2013.5 to 2^1024")
    {
        lowerBound = ZZ(3) << 1022;
        upperBound = ZZ(1) << 1024;

        for (int i = 0; i < 10; i++)
        {
            ZZ p = Generate(lowerBound, upperBound);
            ZZ q = Generate(lowerBound, upperBound);
            n = p * q;

            REQUIRE(NumBits(n) == 2048);
        }
    }
}

TEST_CASE("bool RSA::Math::Prime::Test(const ZZ &n)", "[math]")
{
    REQUIRE(Test(ZZ(0)) == false);
    REQUIRE(Test(ZZ(1)) == false);

    PrimeSeq s;
    s.next();

    for (int i = 0; i < 250; i++)
    {
        ZZ n(s.next());

        SECTION("when n is " + std::to_string(conv<long>(n)))
        {
            REQUIRE(Test(n) == true);
        }
    }
}

TEST_CASE("bool testMillerRabin(const ZZ &n)", "[math]")
{
    REQUIRE(TestMillerRabin(ZZ(0)) == false);
    REQUIRE(TestMillerRabin(ZZ(1)) == false);

    PrimeSeq s;
    s.next();

    for (int i = 0; i < 250; i++)
    {
        ZZ n(s.next());

        SECTION("when n is " + std::to_string(conv<long>(n)))
        {
            REQUIRE(TestMillerRabin(n) == true);
        }
    }
}
