#include <string>
#include "catch2/catch.hpp"
#include "RSA/math/prime.h"

using namespace RSA::Math::Prime;

TEST_CASE("bool compositenessWitness(const ZZ &a, const ZZ &n)", "[math]")
{
    REQUIRE(compositenessWitness(ZZ(0), ZZ(3)) == false);
    REQUIRE(compositenessWitness(ZZ(0), ZZ(5)) == false);
    REQUIRE(compositenessWitness(ZZ(0), ZZ(7)) == false);
    REQUIRE(compositenessWitness(ZZ(137), ZZ(221)) == true);
    REQUIRE(compositenessWitness(ZZ(174), ZZ(221)) == false);

    PrimeSeq s;
    s.next();

    for (int i = 0; i < 250; i++)
    {
        ZZ n(s.next());

        SECTION("when n is " + std::to_string(conv<long>(n)))
        {
            for (ZZ j(2); j < n - 1; j++)
            {

                REQUIRE(compositenessWitness(j, n) == false);
            }
        }
    }
}

TEST_CASE("bool testMillerRabin(const ZZ &n)", "[math]")
{
    REQUIRE(testMillerRabin(ZZ(0)) == false);
    REQUIRE(testMillerRabin(ZZ(1)) == false);

    PrimeSeq s;
    s.next();

    for (int i = 0; i < 250; i++)
    {
        ZZ n(s.next());

        SECTION("when n is " + std::to_string(conv<long>(n)))
        {
            REQUIRE(testMillerRabin(n) == true);
        }
    }
}
