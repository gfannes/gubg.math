#ifndef HEADER_gubg_prob_Bernoulli_hpp_ALREADY_INCLUDED
#define HEADER_gubg_prob_Bernoulli_hpp_ALREADY_INCLUDED

#include <gubg/prob/rng.hpp>
#include <random>

namespace gubg { namespace prob { 

    class Bernoulli
    {
    public:
        Bernoulli() {}
        Bernoulli(double prob_true): prob_true_(prob_true) {}

        void set_prob(double prob_true) {prob_true_ = prob_true;}

        bool operator()() const { return uniform_(rng()) <= prob_true_; }

    private:
        double prob_true_ = 0.5;
        mutable std::uniform_real_distribution<double> uniform_{0.0, 1.0};
    };

    template <typename T>
    T &choose(T &a, T &b, double prob_a, bool seed_with_time = false)
    {
        std::uniform_real_distribution<double> uniform{0.0, 1.0};
        return uniform(rng(seed_with_time)) <= prob_a ? a : b;
    }

    template <typename T, typename RNG>
    T &choose(T &a, T &b, double prob_a, RNG &rng)
    {
        std::uniform_real_distribution<double> uniform{0.0, 1.0};
        return uniform(rng) <= prob_a ? a : b;
    }

} } 

#endif
