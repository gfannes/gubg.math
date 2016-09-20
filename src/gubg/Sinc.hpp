#ifndef HEADER_gubg_Sinc_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Sinc_hpp_ALREADY_INCLUDED

#include <cmath>

namespace gubg { 

    inline double sinc(double x)
    {
        return (x == 0.0 ? 1.0 : std::sin(x)/x);
    }
} 

#endif
