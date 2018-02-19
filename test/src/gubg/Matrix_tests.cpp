#include "catch.hpp"
#include "gubg/Matrix.hpp"
using namespace gubg;

TEST_CASE("Matrix tests", "[ut][matrix]")
{
    Matrix<float> matrix;

    SECTION("fresh should have no rows nor cols")
    {
        REQUIRE(0 == matrix.nr_rows());
        REQUIRE(0 == matrix.nr_cols());
    }
}
