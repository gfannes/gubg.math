#ifndef HEADER_gubg_V2_hpp_ALREADY_INCLUDED
#define HEADER_gubg_V2_hpp_ALREADY_INCLUDED

#include "gubg/math/constants.hpp"
#include <cmath>

namespace gubg { 

    struct V2
    {
        double x = 0.0;
        double y = 0.0;
        
        V2() {}
        V2(double x, double y): x(x), y(y) {}

        V2 &operator+=(const V2 &v)
        {
            x += v.x;
            y += v.y;
            return *this;
        }

        static V2 from_frac(double frac, double radius = 1.0)
        {
            const auto angle = frac*gubg::math::tau;
            return V2(std::cos(angle)*radius, std::sin(angle)*radius);
        }
        static V2 ortho(const V2 &v, bool left)
        {
            return left ? V2(v.y, v.x) : V2(-v.y, v.x);
        }
    };

} 

#endif
