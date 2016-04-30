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
                        for (auto el = elements_.begin(); el != elements_.end(); el += nr_cols_, ++left_it)
                            v += (*left_it)*(std::inner_product(RANGE(right), el, TT(0)));
                        MSS_END();
                    }

                template <typename Vector, typename Right>
                    bool multiply(Vector &vec, const Right &right) const
                    {
                        MSS_BEGIN(bool);
                        MSS(right.size() == nr_cols_);
                        MSS(vec.size() == nr_rows_);
                        auto vec_it = vec.begin();
                        using V = typename Vector::value_type;
                        for (auto el = elements_.begin(); el != elements_.end(); el += nr_cols_, ++vec_it)
                            *vec_it = std::inner_product(RANGE(right), el, V(0));
                        MSS_END();
                    }

                template <typename Vector, typename Left>
                    bool multiply_trans(Vector &vec, const Left &left) const
                    {
                        MSS_BEGIN(bool);
                        MSS(left.size() == nr_rows_);
                        MSS(vec.size() == nr_cols_);
                        using V = typename Vector::value_type;
                        std::fill(RANGE(vec), V(0));
                        for (auto el = elements_.begin(); el != elements_.end();)
                        {
                            auto dst = vec.begin();
                            for (auto left_it = left.begin(); left_it != left.end(); ++left_it, ++dst, ++el)
                                *dst += (*left_it)*(*el);
                        }
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
                //(elements_[row*nr_cols_], ... , elements_[(row+1)*nr_cols_-1]) is row row
                Elements elements_;
        };

} 

#endif
