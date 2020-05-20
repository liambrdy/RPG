#include <catch2/catch.hpp>

#include "../src/Config.cpp"

TEST_CASE("Config File", "[config]")
{
    auto data = Config::LoadConfigFile("config");

    REQUIRE(data.windowDimensions.first > 0);
    REQUIRE(data.windowDimensions.second > 0);

    REQUIRE(data.FPS > 0);
}