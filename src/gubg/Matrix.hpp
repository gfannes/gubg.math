#ifndef HEADER_gubg_Matrix_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Matrix_hpp_ALREADY_INCLUDED

#include "gubg/Range.hpp"
#include "gubg/mss.hpp"
#include <vector>
#include <algorithm>

namespace gubg { 

    template <typename T>
        class Matrix
        {
            public:
                Matrix() = default;
                Matrix(size_t nr_rows, size_t nr_cols): nr_rows_(nr_rows), nr_cols_(nr_cols)
            {
                allocate_();
            }

                size_t nr_rows() const {return nr_rows_;}
                size_t nr_cols() const {return nr_cols_;}

                template <typename TT, typename Left, typename Right>
                    bool multiply(TT &v, const Left &left, const Right &right) const
                    {
                        MSS_BEGIN(bool);
                        MSS(left.size() == nr_rows_);
                        MSS(right.size() == nr_cols_);
                        v = 0;
                        auto left_it = left.begin();
                        for (auto it = elements_.begin(); it != elements_.end(); it += nr_cols_)
                            v += (*left_it)*(std::inner_product(RANGE(right), it, TT(0)));
                        MSS_END();
                    }

            private:
                void allocate_()
                {
                    elements_.resize(nr_rows_*nr_cols_);
                }

                size_t nr_rows_ = 0;
                size_t nr_cols_ = 0;

                using Elements = std::vector<T>;
                Elements elements_;
        };

} 

#endif
