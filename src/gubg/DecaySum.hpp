#ifndef HEADER_gubg_DecaySum_hpp_ALREADY_INCLUDED
#define HEADER_gubg_DecaySum_hpp_ALREADY_INCLUDED

#include <vector>
#include <algorithm>
#include <iostream>

namespace gubg { 

    template <typename T>
    class DecaySum
    {
    public:
        DecaySum()
        {
            clear();
        }
        DecaySum(size_t size, T alpha)
        {
            setup(size, alpha);
        }
        bool valid() const {return !elements_.empty();}
        void clear()
        {
            elements_.clear();
            sum_ = T{};
        }
        bool setup(size_t size, T alpha)
        {
            if (size == 0 || alpha < 0 || alpha > 1)
            {
                clear();
                return false;
            }
            alpha_ = alpha;
            alpha_n_ = std::pow(alpha_, size);
            elements_.resize(size);
            std::fill(elements_.begin(), elements_.end(), T{});
            sum_ = T{};
            partial_sum_ = T{};
            ix_ = 0;
            return true;
        }
        T operator<<(T v)
        {
            using namespace std;
            cout << "[<<](ix:" << ix_ << ")(v:" << v << ")(ps:" << partial_sum_ << ")";
            if (valid())
            {
                partial_sum_ = alpha_*partial_sum_ + v;
                cout << "(nps:" << partial_sum_ << ")";
                sum_ = alpha_*sum_ + v;
                v *= alpha_n_;
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
            cout << endl;
            return sum_;
        }
        T sum() const { return sum_; }
    private:
        T alpha_;
        T alpha_n_;
        T sum_{};
        T partial_sum_;
        size_t ix_;
        std::vector<T> elements_;
    };

} 

#endif
