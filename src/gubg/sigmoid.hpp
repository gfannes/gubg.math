#ifndef HEADER_gubg_sigmoid_hpp_ALREADY_INCLUDED
#define HEADER_gubg_sigmoid_hpp_ALREADY_INCLUDED

#include <cmath>

namespace gubg { 

    template <typename T>
        T sigmoid(T x)
        {
            return T(1)/(T(1)+std::exp(-x));
        }

} 

#endif
