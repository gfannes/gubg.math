#include <gubg/tensor/Tensor.hpp>
#include <gubg/tensor/dot.hpp>
#include <catch.hpp>
#include <iostream>
using namespace gubg;

TEST_CASE("Tensor tests", "[ut][tensor][Tensor]")
{
    const auto do_log = true;

    using T = tensor::Tensor<int>;
    T t;

    SECTION("fresh")
    {
        REQUIRE(t.dimensions().empty());
        REQUIRE(t.size() == 1);
    }
    SECTION("ctor")
    {
        SECTION("from initializer_list")
        {
            SECTION("no data")
            {
                t = T{{2,3}};
                REQUIRE(t.size() == 6);
                if (do_log)
                    std::cout << t << std::endl;
            }
            SECTION("correct amount of data")
            {
                t = T{{2,2,3}, {0,1,2,3,4,5,6,7,8,9,10,11}};
                REQUIRE(t.size() == 12);
                if (do_log)
                    std::cout << t << std::endl;
            }
            SECTION("not enough data")
            {
                t = T{{2,3}, {0,1,2,3}};
                REQUIRE(t.size() == 6);
                if (do_log)
                    std::cout << t << std::endl;
            }
        }
        SECTION("from Dimensions")
        {
            SECTION("no data")
            {
                tensor::Dimensions dims = {2,3};
                t = T{dims};
                REQUIRE(t.size() == 6);
                if (do_log)
                    std::cout << t << std::endl;
            }
        }
    }
    SECTION("zeros() small")
    {
        t = T::zeros({2,3});
        REQUIRE(t.size() == 6);
        if (do_log)
            std::cout << t << std::endl;
        REQUIRE(t == T({2,3}));
    }
    SECTION("zeros() large")
    {
        std::size_t n = 10000;
        t = T::zeros({n,n});
        REQUIRE(t.size() == n*n);
        REQUIRE(t == T({n,n}));
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
        t = T::eye(2);
        t.broadcast([](int v){return 2*v;});
        if (do_log)
            std::cout << t << std::endl;
        REQUIRE(t == T({2,2}, {2,0, 0,2}));
    }
    SECTION("operator+=()")
    {
        t = T::eye(2);
        REQUIRE_NOTHROW(t += T::ones({2,2}));
        REQUIRE_THROWS_AS(t += T::ones({2,3}), std::length_error);
        if (do_log)
            std::cout << t << std::endl;
        REQUIRE(t == T({2,2}, {2,1, 1,2}));
    }
    SECTION("operator-=()")
    {
        t = T::eye(2);
        REQUIRE_NOTHROW(t -= T::ones({2,2}));
        REQUIRE_THROWS_AS(t -= T::ones({2,3}), std::length_error);
        if (do_log)
            std::cout << t << std::endl;
        REQUIRE(t == T({2,2}, {0,-1, -1,0}));
    }
    SECTION("resize()")
    {
        t = T({2,3});
        REQUIRE_NOTHROW(t.reshape({3,2}));
        REQUIRE_THROWS_AS(t.reshape({2,2}), std::out_of_range);
    }
    SECTION("resize()")
    {
        t = T({2,3});
        t.resize({3,2});
        REQUIRE(t.size() == 6);
        t.resize({2,2});
        REQUIRE(t.size() == 4);
    }
    SECTION("dot()")
    {
        SECTION("{} x {}")
        {
            T a({}, {2});
            T b({}, {3});
            T c;
            tensor::dot(c, a, b);
            if (do_log)
                std::cout << c << std::endl;
            REQUIRE(c[{}] == 6);
        }
        SECTION("{} x {1}")
        {
            T a({}, {2});
            T b({1}, {3});
            T c;
            REQUIRE_THROWS_AS(tensor::dot(c, a, b), std::out_of_range);
        }
        SECTION("{3,2} x {4,2}")
        {
            T a({3,2}, {0,1,2,3});
            T b({4,2}, {4,5,6,7,8,9,10,11});
            T c;
            REQUIRE_THROWS_AS(tensor::dot(c, a, b), std::out_of_range);
        }
#if 0
        SECTION("{3,2} x {2,4}")
        {
            T a({3,2}, {0,1,2,3});
            T b({2,4}, {4,5,6,7,8,9,10,11});
            T c;
            tensor::dot(c, a, b);
        }
#endif
    }
}
