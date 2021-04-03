#include <gubg/fxp/Number.hpp>
#include <gubg/macro/capture.hpp>
#include <catch.hpp>
#include <iostream>
using namespace gubg;

TEST_CASE("fxp::Number tests", "[ut][fxp][Number]")
{
    using N = fxp::Number<32, -2>;

    SECTION("default ctor")
    {
        N n;
        std::cout << n << std::endl;
    }
    SECTION("ctor from float")
    {
        N n{3.0f};
        std::cout << n << std::endl;
    }
    SECTION("set()/get()")
    {
        N n;
        const double extent = 0.6;
        for (double x = -extent; x <= extent; x += 0.01)
        {
            n.set(x);
            auto y = n.get<double>();
            std::cout << "[N]" << C(x)C(y) << std::endl;
        }
    }
}
