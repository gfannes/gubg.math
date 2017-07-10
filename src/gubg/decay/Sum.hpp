#ifndef HEADER_gubg_decay_Sum_hpp_ALREADY_INCLUDED
#define HEADER_gubg_decay_Sum_hpp_ALREADY_INCLUDED

namespace gubg { namespace decay { 

    template <typename T>
    class Sum
    {
    public:
        Sum() = default;
        Sum(T alpha)
        {
            setup(alpha);
        }
        
        T alpha() const {return alpha_;}

        bool setup(T alpha)
        {
            sum_ = T{};

            if (alpha < 0 || alpha >= 1)
            {
                alpha_ = T{};
                return false;
            }

            alpha_ = alpha;
            return true;
        }

        T operator<<(T v)
        {
            sum_ *= alpha_;
            sum_ += v;
            return sum_;
        }

        T operator()() const
        {
            return sum_;
        }

    private:
        T alpha_{};
        T sum_{};
    };

} } 

#endif
