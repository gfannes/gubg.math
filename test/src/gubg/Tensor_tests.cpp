#include <gubg/Tensor.hpp>
#include <catch.hpp>
#include <iostream>

TEST_CASE("Tensor tests", "[ut][Tensor]")
{
    using T = gubg::Tensor<int>;
    T t;
    REQUIRE(t.dimensions().empty());
    REQUIRE(t.size() == 1);
    {
        t = T{{2,3}, {0,1,2,3}};
        REQUIRE(t.size() == 6);
        std::cout << t << std::endl;
    }
    {
        t = T{{2,2,3}, {0,1,2,3,4,5,6,7,8,9,10,11}};
        REQUIRE(t.size() == 12);
        std::cout << t << std::endl;
    }
}
