#include <gubg/prob/rng.hpp>

namespace gubg { namespace prob { 

    std::mt19937 &rng()
    {
        static std::mt19937 rng_;
        return rng_;
    }

} } 
