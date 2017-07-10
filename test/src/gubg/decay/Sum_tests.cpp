#include "catch.hpp"
#include "gubg/decay/Sum.hpp"
using namespace gubg::decay;

TEST_CASE("gubg::decay::Sum tests", "[ut][gubg][decay]")
{
    using T = double;
    const T eps = 0.00001;

    SECTION("default ctor")
    {
        Sum<T> sum;
        SECTION("alpha == 0")
        {
            REQUIRE(sum.alpha() == 0);
            REQUIRE(sum() == 0);
            REQUIRE(1 == (sum << 1));
            REQUIRE(2 == (sum << 2));
        }
        SECTION("alpha == 0.5")
        {
            REQUIRE(sum.setup(0.5));
            REQUIRE(sum.alpha() == 0.5);
            REQUIRE(1 == (sum << 1));
            REQUIRE(2.5 == (sum << 2));
        }
        SECTION("negative alpha should fail")
        {
            REQUIRE(!sum.setup(-eps));
        }
        SECTION("alpha ge 1 should fail")
        {
            REQUIRE(!sum.setup(1));
        }
    }
    SECTION("alpha == 0.5")
    {
        Sum<T> sum(0.5);
        REQUIRE(sum.alpha() == 0.5);
        REQUIRE(sum() == 0);
        REQUIRE(1 == (sum << 1));
        REQUIRE(2.5 == (sum << 2));
        REQUIRE(2.5 == sum());
        SECTION("setup should reset the sum")
        {
            REQUIRE(sum.setup(0.5));
            REQUIRE(0 == sum());
        }
    }
}
