#include "catch2/catch.hpp"
#include "RSA/math.h"

using namespace RSA::Math;

TEST_CASE("long RSA::Math::FactorPower2(ZZ &n)", "[math]")
{
    ZZ n(0x123456789000);
    long r = FactorPower2(n);

    REQUIRE(n == 0x123456789);
    REQUIRE(r == 12);
}

TEST_CASE("ZZ RSA::Math::ModExp(ZZ b, ZZ e, const ZZ &m)", "[math]")
{
    REQUIRE(ModExp(ZZ(2), ZZ(3), ZZ(5)) == 3);
    REQUIRE(ModExp(ZZ(2), ZZ(5), ZZ(13)) == 6);
    REQUIRE(ModExp(ZZ(5), ZZ(3), ZZ(13)) == 8);
    REQUIRE(ModExp(ZZ(4), ZZ(13), ZZ(497)) == 445);
    REQUIRE(ModExp(ZZ(123), ZZ(456), ZZ(789)) == 699);
    REQUIRE(ModExp(ZZ(987), ZZ(654), ZZ(321)) == 57);
}

TEST_CASE("ZZ RSA::Math::ModInv(const ZZ &a, const ZZ &m)")
{
    REQUIRE(ModInv(ZZ(3), ZZ(7)) == 5);
    REQUIRE(ModInv(ZZ(3), ZZ(10)) == 7);
    REQUIRE(ModInv(ZZ(123), ZZ(1234)) == 923);
}
