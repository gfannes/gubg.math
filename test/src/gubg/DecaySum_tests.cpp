#include "catch.hpp"
#include "gubg/DecaySum.hpp"
#include <vector>
using namespace std;

TEST_CASE("gubg::DecaySum tests", "[ut][gubg][decay]")
{
    using T = double;
    const T eps = 0.00001;

    struct Scn
    {
        size_t size = 3;
        T alpha = 0.5;
        vector<T> data;
    } scn;
    struct Should
    {
        bool setup_ok = true;
        vector<T> sum;
    } should;

    SECTION("default") { }
    SECTION("setup fail")
    {
        should.setup_ok = false;
        SECTION("size == 0") { scn.size = 0; }
        SECTION("alpha < 0") { scn.alpha = -eps; }
        SECTION("alpha > 1") { scn.alpha = 1+eps; }
    }
    SECTION("data")
    {
        SECTION("1 1 1 1 1")
        {
            scn.data = {1,2,3,4,5,6};
            should.sum = {1,2.5,4.25,6,7.75,9.5};
        }
    }

    gubg::DecaySum<T> ds;

    REQUIRE(should.setup_ok == ds.setup(scn.size, scn.alpha));

    if (ds.valid())
    {
        REQUIRE(ds.sum() == 0);
        REQUIRE(scn.data.size() == should.sum.size());
        auto wanted = should.sum.begin();
        for (auto v: scn.data)
        {
            const auto sum = (ds << v);
            REQUIRE(ds.sum() == sum);
            REQUIRE(sum == *wanted);
            ++wanted;
        }
    }

}
