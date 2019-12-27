#ifndef HEADER_gubg_prob_Uniform_hpp_ALREADY_INCLUDED
#define HEADER_gubg_prob_Uniform_hpp_ALREADY_INCLUDED

#include <gubg/prob/rng.hpp>
#include <random>

namespace gubg { namespace prob { 

    class Uniform
    {
    public:
        Uniform() {}
        Uniform(unsigned int count): count_(count) {}

        void set_count(unsigned int count) {count_ = count;}

        unsigned int operator()() const
        {
            std::uniform_int_distribution<unsigned int> uniform{0, count_-1};
            return uniform(rng());
        }

    private:
        unsigned int count_ = 0;
    };

    template <typename T>
    T &select_uniform(std::vector<T> &vec)
    {
        std::uniform_int_distribution<unsigned int> uniform{0, vec.size()-1};
        return vec[uniform(rng())];
    }

} } 

#endif
