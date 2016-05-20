#ifndef HEADER_gubg_Tanh_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Tanh_hpp_ALREADY_INCLUDED

#include <cmath>

namespace gubg { 

    template <typename T>
        struct Tanh
        {
            T operator()(T x) const {return std::tanh(x);}
        };

} 

#endif
