#include <gubg/prob/rng.hpp>
#include <chrono>

namespace gubg { namespace prob { 

    std::mt19937 &rng(bool seed_with_time)
    {
        static std::mt19937 rng_unseeded_;
        if (!seed_with_time)
            return rng_unseeded_;

        static std::mt19937 rng_seeded_;
        rng_seeded_.seed(rng_unseeded_()+std::chrono::high_resolution_clock::now().time_since_epoch().count());
        return rng_seeded_;
    }

} } 
