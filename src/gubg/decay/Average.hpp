#ifndef HEADER_gubg_decay_Average_hpp_ALREADY_INCLUDED
#define HEADER_gubg_decay_Average_hpp_ALREADY_INCLUDED

#include "gubg/decay/Sum.hpp"

namespace gubg { namespace decay { 

    template <typename T>
    class Average
    {
    public:
        Average() = default;
        Average(T alpha): sum_(alpha) {}

        T alpha() const {return sum_.alpha();}

        bool setup(T alpha)
        {
            const auto ret = sum_.setup(alpha);
            one_minus_alpha_ = (T{1} - sum_.alpha());
            return ret;
        }

        T operator<<(T v)
        {
            return (sum_ << v)*one_minus_alpha_;
        }

        T operator()() const
        {
            return sum_()*one_minus_alpha_;
        }

    private:
        Sum<T> sum_;
        T one_minus_alpha_{T{1}-sum_.alpha()};
    };

} } 

#endif
