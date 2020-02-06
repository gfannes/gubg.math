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

        unsigned int operator()(bool seed_with_time = false) const
        {
            std::uniform_int_distribution<unsigned int> uniform{0, count_-1};
            return uniform(rng(seed_with_time));
        }

        template <typename RNG>
        unsigned int operator()(RNG &rng) const
        {
            std::uniform_int_distribution<unsigned int> uniform{0, count_-1};
            return uniform(rng);
        }

    private:
        unsigned int count_ = 0;
    };

    template <typename T>
    T &select_uniform(std::vector<T> &vec, bool seed_with_time = false)
    {
        std::uniform_int_distribution<std::size_t> uniform(0, vec.size()-1);
        return vec[uniform(rng(seed_with_time))];
    }
    template <typename T>
    const T &select_uniform(const std::vector<T> &vec, bool seed_with_time = false)
    {
        std::uniform_int_distribution<std::size_t> uniform(0, vec.size()-1);
        return vec[uniform(rng(seed_with_time))];
    }

    template <typename T, typename RNG>
    T &select_uniform(std::vector<T> &vec, RNG &rng)
    {
        std::uniform_int_distribution<std::size_t> uniform(0, vec.size()-1);
        return vec[uniform(rng)];
    }
    template <typename T, typename RNG>
    const T &select_uniform(const std::vector<T> &vec, RNG &rng)
    {
        std::uniform_int_distribution<std::size_t> uniform(0, vec.size()-1);
        return vec[uniform(rng)];
    }

} } 

#endif
