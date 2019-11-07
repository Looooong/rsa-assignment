#include "catch2/catch.hpp"
#include "RSA/math.h"

using namespace RSA::Math;

TEST_CASE("ZZ ModExp(ZZ b, ZZ e, const ZZ &m)", "[math]")
{
    REQUIRE(ModExp(ZZ(2), ZZ(3), ZZ(5)) == 3);
    REQUIRE(ModExp(ZZ(2), ZZ(5), ZZ(13)) == 6);
    REQUIRE(ModExp(ZZ(5), ZZ(3), ZZ(13)) == 8);
    REQUIRE(ModExp(ZZ(4), ZZ(13), ZZ(497)) == 445);
    REQUIRE(ModExp(ZZ(123), ZZ(456), ZZ(789)) == 699);
    REQUIRE(ModExp(ZZ(987), ZZ(654), ZZ(321)) == 57);
}
