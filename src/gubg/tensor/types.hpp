#ifndef HEADER_gubg_tensor_types_hpp_ALREADY_INCLUDED
#define HEADER_gubg_tensor_types_hpp_ALREADY_INCLUDED

#include <vector>
#include <cstdint>

namespace gubg { namespace tensor { 

    using Dimensions = std::vector<std::size_t>;
    using Strides = std::vector<std::size_t>;
    using Index = std::vector<std::size_t>;

} } 

#endif
