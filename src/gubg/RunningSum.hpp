#ifndef HEADER_gubg_RunningSum_hpp_ALREADY_INCLUDED
#define HEADER_gubg_RunningSum_hpp_ALREADY_INCLUDED

#include <vector>
#include <algorithm>

namespace gubg { 

    template <typename T>
    class RunningSum
    {
    public:
        RunningSum() = default;
        RunningSum(size_t size): elements_(size, T{}) { }

        bool valid() const {return !elements_.empty();}

        void setup(size_t size)
        {
            sum_ = T{};
            partial_sum_ = T{};
            ix_ = 0;
            elements_.resize(size);
            std::fill(elements_.begin(), elements_.end(), T{});
        }

        T operator<<(T v)
        {
            if (valid())
            {
                partial_sum_ += v;
                sum_ += v;
                std::swap(v, elements_[ix_]);
                ++ix_;
                if (ix_ == elements_.size())
                {
                    ix_ = 0;
                    sum_ = partial_sum_;
                    partial_sum_ = T{};
                }
                else
                {
                    sum_ -= v;
                }
            }
            return sum_;
        }

        T operator()() const { return sum_; }

    private:
        T sum_{};
        T partial_sum_{};
        size_t ix_ = 0;
        std::vector<T> elements_;
    };

} 

#endif
