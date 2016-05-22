#ifndef HEADER_gubg_Tanh_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Tanh_hpp_ALREADY_INCLUDED

#include <cmath>

namespace gubg { 

    template <typename T>
        struct Tanh
        {
            using Input = T;
            using Output = T;

            T operator()(T x) const {return std::tanh(x);}
            T derivative(T x) const {const auto v = operator()(x); return T{1} - v*v;}
        };

} 

#endif
