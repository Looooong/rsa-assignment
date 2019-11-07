#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "RSA/math.h"

TEST_CASE("NTL works")
{
    REQUIRE(conv<ZZ>("123456789") + conv<ZZ>("987654321") == conv<ZZ>("1111111110"));
    REQUIRE(conv<ZZ>("987654321") % conv<ZZ>("123456789") == conv<ZZ>(9));
}
