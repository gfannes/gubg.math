#ifndef HEADER_gubg_tensor_str_hpp_ALREADY_INCLUDED
#define HEADER_gubg_tensor_str_hpp_ALREADY_INCLUDED

#include <gubg/tensor/types.hpp>
#include <sstream>

namespace gubg { namespace tensor { 

    inline std::string dim_str(const Dimensions &dims)
    {
        std::ostringstream oss;
        oss << "[Dimensions]";
        for (auto dim: dims)
            oss << "(" << dim << ")";
        return oss.str();
    }

} } 

#endif
