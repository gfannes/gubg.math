#include "catch.hpp"
#include "gubg/decay/Average.hpp"
using namespace gubg::decay;

TEST_CASE("gubg::decay::Average tests", "[ut][gubg][decay]")
{
    using T = double;
    const T eps = 0.00001;

    SECTION("default ctor")
    {
        Average<T> avg;
        SECTION("alpha == 0")
        {
            REQUIRE(avg.alpha() == 0);
            REQUIRE(avg() == 0);
            REQUIRE(1 == (avg << 1));
            REQUIRE(2 == (avg << 2));
        }
        SECTION("alpha == 0.5")
        {
            REQUIRE(avg.setup(0.5));
            REQUIRE(avg.alpha() == 0.5);
            REQUIRE(0.5 == (avg << 1));
            REQUIRE(1.25 == (avg << 2));
        }
        SECTION("negative alpha should fail")
        {
            REQUIRE(!avg.setup(-eps));
        }
        SECTION("alpha ge 1 should fail")
        {
            REQUIRE(!avg.setup(1+eps));
        }
    }
    SECTION("alpha == 0.5")
    {
        Average<T> avg(0.5);
        REQUIRE(avg.alpha() == 0.5);
        REQUIRE(avg() == 0);
        REQUIRE(0.5 == (avg << 1));
        REQUIRE(0.75 == (avg << 1));
        REQUIRE(0.75 == avg());
        REQUIRE(0.875 == (avg << 1));
        SECTION("setup should reset the avg")
        {
            REQUIRE(avg.setup(0.5));
            REQUIRE(0 == avg());
        }
    }
}
