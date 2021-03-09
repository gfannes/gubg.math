#ifndef HEADER_gubg_Rosenbrock_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Rosenbrock_hpp_ALREADY_INCLUDED

#include <gubg/mss.hpp>

namespace gubg { 

    template <typename T>
    class Rosenbrock
    {
    public:
        Rosenbrock(T a = 1, T b = 100): a_(a), b_(b) {}

        T operator()(T x, T y) const
        {
            const T amx = (a_ - x);
            const T ymxx = (y - x*x);
            return amx*amx + b_*ymxx*ymxx;
        }

        template <typename Position>
        T value(const Position &position) {return operator()(position[0], position[1]);}

        template <typename Gradient, typename Position>
        bool gradient(Gradient &gradient, const Position &position)
        {
            MSS_BEGIN(bool);

            MSS(gradient.size() == 2);
            MSS(position.size() == 2);

            const auto x = position[0];
            const auto y = position[1];

            const auto ymxx = (y-x*x);

            gradient[0] = 2*(x-a_) - 4*b_*ymxx*x;
            gradient[1] = 2*b_*ymxx;

            MSS_END();
        }

    private:
        const T a_;
        const T b_;
    };

} 

#endif
