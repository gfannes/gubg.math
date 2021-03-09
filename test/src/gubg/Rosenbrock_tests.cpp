#include <gubg/Rosenbrock.hpp>
#include <catch.hpp>
#include <array>
#include <fstream>

TEST_CASE("Rosenbrock tests", "[ut][Rosenbrock]")
{
    gubg::Rosenbrock<double> rb;
    std::array<double, 2> pos, grad;

    std::ofstream value_fo{"rosenbrock_value.gnuplot"};
    std::ofstream gradient_fo{"rosenbrock_gradient.gnuplot"};

    value_fo << "$data << EOD" << std::endl;
    gradient_fo << "$data << EOD" << std::endl;
    const double d = 0.1;
    const double min = -2, max = 3;
    const unsigned int step_cnt = (max-min)/d;
    auto &x = pos[0];
    auto &y = pos[1];
    for (x = min; x <= max; x += d)
    {
        for (y = min; y <= max; y += d)
        {
            const auto z = rb(x, y);
            value_fo << x << '\t' << y << '\t' << z << std::endl;
            REQUIRE(rb.value(pos) == Approx(z));

            REQUIRE(rb.gradient(grad, pos));
            const double factor = 1.0/5000;
            gradient_fo << x << '\t' << y << '\t' << factor*grad[0] << '\t' << factor*grad[1] << std::endl;
        }
    }
    value_fo << "EOD" << std::endl;
    gradient_fo << "EOD" << std::endl;

    value_fo << "set dgrid3d " << step_cnt << "," << step_cnt << " qnorm 2" << std::endl;
    /* value_fo << "splot $data using 1:2:3 with lines" << std::endl; */
    /* value_fo << "set pm3d interpolate 0,0" << std::endl; */
    value_fo << "set cntrparam levels incr 0,10,100" << std::endl;
    value_fo << "set contour base" << std::endl;
    value_fo << "splot $data using 1:2:3 with lines" << std::endl;
    value_fo << "pause(-1)" << std::endl;

    gradient_fo << "plot $data with vec" << std::endl;
    gradient_fo << "pause(-1)" << std::endl;
}
