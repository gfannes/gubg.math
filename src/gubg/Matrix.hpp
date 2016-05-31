#ifndef HEADER_gubg_Matrix_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Matrix_hpp_ALREADY_INCLUDED

#include "gubg/Range.hpp"
#include "gubg/mss.hpp"
#include <vector>
#include <algorithm>
#include <ostream>

namespace gubg { 

    template <typename T>
        class Matrix
        {
            public:
                using Self = Matrix<T>;

                Matrix() = default;
                Matrix(size_t nr_rows, size_t nr_cols): nr_rows_(nr_rows), nr_cols_(nr_cols)
            {
                allocate_();
            }

                void resize(size_t nr_rows, size_t nr_cols)
                {
                    nr_rows_ = nr_rows;
                    nr_cols_ = nr_cols;
                    allocate_();
                }

                Self &operator=(const Self &rhs)
                {
                    nr_rows_ = rhs.nr_rows();
                    nr_cols_ = rhs.nr_cols();
                    elements_ = rhs.elements_;
                }

                bool add(const Self &rhs, T scalar)
                {
                    MSS_BEGIN(bool);
                    MSS(nr_rows() == rhs.nr_rows());
                    MSS(nr_cols() == rhs.nr_cols());
                    for (size_t i = 0; i < elements_.size(); ++i)
                        elements_[i] += scalar*rhs.elements_[i];
                    MSS_END();
                }

                Self &scale(T scalar)
                {
                    for (auto &v: elements_)
                        v += scalar;
                    return *this;
                }

                bool inproduct(T &v, const Self &rhs)
                {
                    MSS_BEGIN(bool);
                    MSS(nr_rows() == rhs.nr_rows());
                    MSS(nr_cols() == rhs.nr_cols());
                    v = 0;
                    v = std::inner_product(RANGE(elements_), rhs.elements_.begin(), v);
                    MSS_END();
                }

                size_t nr_rows() const {return nr_rows_;}
                size_t nr_cols() const {return nr_cols_;}

                void fill(T v) {std::fill(RANGE(elements_), v);}

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

                void stream(std::ostream &os) const
                {
                    auto el = elements_.begin();
                    for (size_t r = 0; r < nr_rows_; ++r)
                    {
                        for (size_t c = 0; c < nr_cols_; ++c, ++el)
                            os << (c == 0 ? "" : ", ") << *el;
                        os << std::endl;
                    }
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

    template <typename T>
        std::ostream &operator<<(std::ostream &os, const Matrix<T> &m)
        {
            m.stream(os);
            return os;
        }

} 

#endif
