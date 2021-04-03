#include <gubg/fxp/Number.hpp>
#include <gubg/macro/capture.hpp>
#include <gubg/mss.hpp>
#include <catch.hpp>
#include <iostream>
#include <type_traits>
using namespace gubg;

namespace  { 
    
    enum class Case { SetGet, Add, MultSmall, MultLarge };
    const char *str(Case c)
    {
        switch (c)
        {
            case Case::SetGet: return "SetGet";
            case Case::Add: return "Add";
            case Case::MultSmall: return "MultSmall";
            case Case::MultLarge: return "MultLarge";
        }
    }

    template <int Exp>
    bool test(Case c, const double extent = 5)
    {
        MSS_BEGIN(bool);

        using N = fxp::Number<32, Exp>;
        MSS((std::is_same_v<typename N::Repr, std::int32_t>));

        N x_fxp;
        N z_fxp;
        MSS(x_fxp.repr() == 0);

        const double offset = -0.5;
        const N offset_fxp{offset};
        const double small = 0.5;
        const N small_fxp{small};
        const double large = 4.5;
        const N large_fxp{large};

        for (double x = -extent; x <= extent; x += 0.01)
        {
            x_fxp.set(x);
            double y;
            switch (c)
            {
                case Case::SetGet:
                    y = x;
                    z_fxp = x_fxp;
                    break;
                case Case::Add:
                    y = x+offset;
                    z_fxp = x_fxp+offset_fxp;
                    break;
                case Case::MultSmall:
                    y = x*small;
                    z_fxp = x_fxp*small_fxp;
                    break;
                case Case::MultLarge:
                    y = x*large;
                    z_fxp = x_fxp*large_fxp;
                    break;
            }
            const auto z = z_fxp.template get<double>();
            std::cout << "[" << str(c) << "]" << C(x)C(y)C(z) << std::endl;
        }

        MSS_END();
    }
} 

TEST_CASE("fxp::Number tests", "[ut][fxp][Number]")
{
    SECTION("SetGet")
    {
        REQUIRE(test<-2>(Case::SetGet));
        REQUIRE(test<0>(Case::SetGet));
        REQUIRE(test<2>(Case::SetGet));
    }
    SECTION("Add")
    {
        REQUIRE(test<-2>(Case::Add));
        REQUIRE(test<0>(Case::Add));
        REQUIRE(test<2>(Case::Add));
    }
    SECTION("MultSmall")
    {
        REQUIRE(test<-2>(Case::MultSmall));
        REQUIRE(test<0>(Case::MultSmall));
        REQUIRE(test<2>(Case::MultSmall));
    }
    SECTION("MultLarge")
    {
        REQUIRE(test<-2>(Case::MultLarge));
        REQUIRE(test<0>(Case::MultLarge));
        REQUIRE(test<2>(Case::MultLarge));
    }
}
