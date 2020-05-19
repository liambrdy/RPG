#include <catch2/catch.hpp>

TEST_CASE("Number Test", "[numbers]")
{
    REQUIRE(1 != 2);
    REQUIRE(2 * 2 == 4);
}