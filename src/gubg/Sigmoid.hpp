#ifndef HEADER_gubg_Sigmoid_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Sigmoid_hpp_ALREADY_INCLUDED

#include <cmath>

namespace gubg { 

    template <typename T>
        T sigmoid(T x)
        {
            return T(1)/(T(1)+std::exp(-x));
        }

    template <typename T>
        struct Sigmoid
        {
            T operator()(T x) const {return sigmoid(x);}
        };

} 

#endif
