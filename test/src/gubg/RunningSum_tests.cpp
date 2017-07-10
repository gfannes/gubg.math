#include "catch.hpp"
#include "gubg/RunningSum.hpp"
#include <vector>
using namespace std;

TEST_CASE("gubg::RunningSum tests", "[ut][gubg][decay]")
{
    using T = double;

    struct Scn
    {
        size_t size = 3;
        vector<T> data;
    } scn;
    struct Should
    {
        bool valid = true;
        vector<T> sum;
    } should;

    SECTION("default")
    {
        SECTION("no data")
        {
        }
        SECTION("data")
        {
            scn.data = {1,2,3,4,5,6};
            should.sum = {1,3,6,9,12,15};
        }
    }
    SECTION("size == 0")
    {
        scn.size = 0;
        should.valid = false;
        SECTION("no data")
        {
        }
        SECTION("data")
        {
            scn.data = {1,2,3,4,5,6};
            should.sum = {0,0,0,0,0,0};
        }
    }
    SECTION("size == 1")
    {
        scn.size = 1;
        should.valid = true;
        SECTION("no data")
        {
        }
        SECTION("data")
        {
            scn.data = {1,2,3,4,5,6};
            should.sum = {1,2,3,4,5,6};
        }
    }

    gubg::RunningSum<T> rs;

    rs.setup(scn.size);
    REQUIRE(rs.valid() == should.valid);

    REQUIRE(rs() == 0);
    REQUIRE(scn.data.size() == should.sum.size());
    auto wanted = should.sum.begin();
    for (auto v: scn.data)
    {
        const auto sum = (rs << v);
        REQUIRE(rs() == sum);
        REQUIRE(sum == *wanted);
        ++wanted;
    }
}
