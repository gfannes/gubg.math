#ifndef HEADER_gubg_Sigmoid_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Sigmoid_hpp_ALREADY_INCLUDED

#include <cmath>

namespace gubg { 

    template <typename T>
        T sigmoid(T x)
        {
            return T{1}/(T{1}+std::exp(-x));
        }

    template <typename T>
        struct Sigmoid
        {
            using Input = T;
            using Output = T;

            T operator()(T x) const {return sigmoid(x);}
            T derivative(T x) const {const auto v = operator()(x); return v*(T{1}-v);}
        };

} 

#endif
