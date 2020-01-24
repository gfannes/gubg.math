#ifndef HEADER_gubg_prob_rng_hpp_ALREADY_INCLUDED
#define HEADER_gubg_prob_rng_hpp_ALREADY_INCLUDED

#include <random>

namespace gubg { namespace prob { 

    std::mt19937 &rng(bool seed_with_time = false);

} } 

#endif
