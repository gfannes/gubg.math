#include <gubg/Tensor.hpp>
#include <catch.hpp>
#include <iostream>

TEST_CASE("Tensor tests", "[ut][Tensor]")
{
    const auto do_log = true;

    using T = gubg::Tensor<int>;
    T t;

    SECTION("fresh")
    {
        REQUIRE(t.dimensions().empty());
        REQUIRE(t.size() == 1);
    }
    SECTION("ctor")
    {
        {
            t = T{{2,3}};
            REQUIRE(t.size() == 6);
            if (do_log)
                std::cout << t << std::endl;
        }
        {
            t = T{{2,3}, {0,1,2,3}};
            REQUIRE(t.size() == 6);
            if (do_log)
                std::cout << t << std::endl;
        }
        {
            t = T{{2,2,3}, {0,1,2,3,4,5,6,7,8,9,10,11}};
            REQUIRE(t.size() == 12);
            if (do_log)
                std::cout << t << std::endl;
        }
    }
    SECTION("zeros()")
    {
        t = T::zeros({2,3});
        REQUIRE(t.size() == 6);
        if (do_log)
            std::cout << t << std::endl;
        REQUIRE(t == T({2,3}));
    }
    SECTION("ones()")
    {
        t = T::ones({2,3});
        REQUIRE(t.size() == 6);
        if (do_log)
            std::cout << t << std::endl;
        REQUIRE(t == T({2,3}, {1,1,1, 1,1,1,}));
    }
    SECTION("eye()")
    {
        t = T::eye(3);
        REQUIRE(t.size() == 9);
        if (do_log)
            std::cout << t << std::endl;
        REQUIRE(t == T({3,3}, {1,0,0, 0,1,0, 0,0,1}));
    }
    SECTION("operator[]")
    {
        {
            t = T::zeros({6});
            t[{2}] = 1;
            if (do_log)
                std::cout << t << std::endl;
            REQUIRE(t == T({6}, {0,0,1,0,0,0}));
        }
        {
            t = T::zeros({2,3});
            t[{1,2}] = 1;
            if (do_log)
                std::cout << t << std::endl;
            REQUIRE(t == T({2,3}, {0,0,0, 0,0,1}));
        }
    }
    SECTION("broadcast()")
    {
        t = T::eye({2});
        t.broadcast([](int v){return 2*v;});
        if (do_log)
            std::cout << t << std::endl;
        REQUIRE(t == T({2,2}, {2,0, 0,2}));
    }
}
