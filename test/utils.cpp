#include "catch2/catch.hpp"
#include "RSA/utils.h"

using namespace RSA::Utils;

TEST_CASE("ZZ RSA::Utils::HexToZZ(std::string s)", "[utils]")
{
    REQUIRE(HexToZZ("075bcd15") == 123456789);
    REQUIRE(HexToZZ("3ade68b1") == 987654321);
}

TEST_CASE("std::string RSA::Utils::ZZtoHex(const ZZ &z)", "[utils]")
{
    REQUIRE(ZZtoHex(ZZ(123456789)) == "075bcd15");
    REQUIRE(ZZtoHex(ZZ(987654321)) == "3ade68b1");
}
