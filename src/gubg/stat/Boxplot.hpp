#ifndef HEADER_gubg_stat_Boxplot_hpp_ALREADY_INCLUDED
#define HEADER_gubg_stat_Boxplot_hpp_ALREADY_INCLUDED

#include <gubg/Range.hpp>
#include <gubg/mss.hpp>
#include <vector>
#include <ostream>

namespace gubg { namespace stat { 

    class Boxplot
    {
    private:
        using T = double;

    public:
        void reset()
        {
            data_.clear();
        }

        Boxplot &operator<<(double v)
        {
            data_.push_back(v);
            return *this;
        }

        bool calculate()
        {
            MSS_BEGIN(bool);

            const auto size = data_.size();
            MSS(size > 0);
            std::sort(RANGE(data_));

            const size_t q1ix = 0.25*size;
            q1_ = data_[q1ix];

            const size_t q2ix = 0.50*size;
            median_ = data_[q2ix];

            const size_t q3ix = 0.75*size;
            q3_ = data_[q3ix];

            const auto iqr = q3_-q1_;

            min_ = q1_-1.5*iqr;
            outliers_min_.clear();
            for (auto ix = 0u; ix < q1ix; ++ix)
            {
                if (data_[ix] >= min_)
                {
                    min_ = data_[ix];
                    break;
                }
                outliers_min_.push_back(data_[ix]);
            }

            max_ = q3_+1.5*iqr;
            outliers_max_.clear();
            for (auto ix = size-1; ix > q2ix; --ix)
            {
                if (data_[ix] <= max_)
                {
                    max_ = data_[ix];
                    break;
                }
                outliers_max_.push_back(data_[ix]);
            }

            MSS_END();
        }

        void stream(std::ostream &os) const
        {
            os << "[boxplot]{" << std::endl;
            os << "  [box](q1:" << q1_ << ")(median:" << median_ << ")(q3:" << q3_ << ")" << std::endl;
            os << "  [whiskers](min:" << min_ << ")(max:" << max_ << ")" << std::endl;
            if (!outliers_min_.empty() || !outliers_max_.empty())
            {
                os << "  [outliers]";
                for (auto v: outliers_min_)
                    os << "(min:" << v << ")";
                for (auto v: outliers_max_)
                    os << "(max:" << v << ")";
                os << std::endl;
            }
            os << "}" << std::endl;
        }

    private:
        std::vector<T> data_;

        std::vector<T> outliers_min_;
        T min_;
        T q1_;
        T median_;
        T q3_;
        T max_;
        std::vector<T> outliers_max_;
    };

    std::ostream &operator<<(std::ostream &os, const Boxplot &bp)
    {
        bp.stream(os);
        return os;
    }

} } 

#endif
