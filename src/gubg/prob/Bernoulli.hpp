#ifndef HEADER_gubg_prob_Bernoulli_hpp_ALREADY_INCLUDED
#define HEADER_gubg_prob_Bernoulli_hpp_ALREADY_INCLUDED

#include <gubg/prob/rng.hpp>
#include <random>

namespace gubg { namespace prob { 

    class Bernoulli
    {
    public:
        Bernoulli() {}
        Bernoulli(double prob1): prob1_(prob1) {}

        unsigned int draw() const
        {
            return uniform_(rng()) < prob1_ ? 0 : 1;
        }

    private:
        double prob1_ = 0.5;
        const std::uniform_real_distribution<double> uniform_{0.0, 1.0};
    };

} } 

#endif
