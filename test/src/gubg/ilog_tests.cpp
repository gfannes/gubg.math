#include <gubg/ilog.hpp>
#include <catch.hpp>

TEST_CASE("ilog2 tests", "[ut][ilog][ilog2]")
{
    REQUIRE(gubg::ilog2(0b0000u) == 0u);
    REQUIRE(gubg::ilog2(0b0001u) == 1u);
    REQUIRE(gubg::ilog2(0b0010u) == 2u);
    REQUIRE(gubg::ilog2(0b0011u) == 2u);
    REQUIRE(gubg::ilog2(0b0100u) == 3u);
    REQUIRE(gubg::ilog2(0b0101u) == 3u);
    REQUIRE(gubg::ilog2(0b0110u) == 3u);
    REQUIRE(gubg::ilog2(0b0111u) == 3u);
    REQUIRE(gubg::ilog2(0b1000u) == 4u);
}
