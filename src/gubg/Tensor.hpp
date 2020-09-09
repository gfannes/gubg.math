#ifndef HEADER_gubg_Tensor_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Tensor_hpp_ALREADY_INCLUDED

#include <vector>
#include <ostream>
#include <algorithm>
#include <cstdint>
#include <cassert>

namespace gubg { 

    namespace tensor { 
        using Dimensions = std::vector<std::size_t>;
        using Index = std::vector<std::size_t>;

        template <typename Ftor>
        void each_subindex(const Dimensions &dimensions, Index &index, std::size_t dim, std::size_t nr_dims, Ftor &&ftor)
        {
            if (dim == nr_dims)
            {
                ftor(index);
            }
            else
            {
                const auto nr = dimensions[dim];
                for (auto ix = 0u; ix < nr; ++ix)
                {
                    index[dim] = ix;
                    each_subindex(dimensions, index, dim+1, nr_dims, ftor);
                }
            }
        }
        template <typename Ftor>
        void each_index(const Dimensions &dimensions, std::size_t nr_dims, Ftor &&ftor)
        {
            Index index(nr_dims);
            each_subindex(dimensions, index, 0, nr_dims, ftor);
        }
    } 

    template <typename T>
    class Tensor
    {
    public:
        using Dimensions = tensor::Dimensions;

        Tensor()
        {
            recompute_size_();
            data_.resize(size_);
        }
        Tensor(std::initializer_list<std::size_t> dimensions, std::initializer_list<T> data): dimensions_(dimensions), data_(data)
        {
            recompute_size_();
            data_.resize(size_);
        }

        const std::size_t size() const {return size_;}
        const Dimensions &dimensions() const {return dimensions_;}

        void stream(std::ostream &os) const
        {
            const auto dimsize = dimensions_.size();
            const auto nr_dims = std::max<std::size_t>(dimsize,2) - 2;

            const T *ptr = data_.data();

            auto lambda = [&](const auto &index)
            {
                switch (dimsize)
                {
                    case 0://Scalar
                        {
                            os << "Scalar: " << ptr[0] << std::endl;
                            ++ptr;
                        }
                        break;
                    case 1://Vector
                        {
                            os << "Vector: [";
                            const auto nr = dimensions_.back();
                            for (auto ix = 0u; ix < nr; ++ix)
                                os << ptr[ix] << ", ";
                            ptr += nr;
                            os << "]" << std::endl;
                        }
                        break;
                    case 2://Matrix
                        {
                            os << "Matrix: [" << std::endl;
                            const auto nr_rows = dimensions_[dimsize-2];
                            const auto nr_cols = dimensions_[dimsize-1];
                            for (auto row = 0u; row < nr_rows; ++row, ptr += nr_cols)
                            {
                                os << "  [";
                                for (auto col = 0u; col < nr_cols; ++col)
                                    os << ptr[col] << ", ";
                                os << "]" << std::endl;
                            }
                            os << "]" << std::endl;
                        }
                        break;
                    default://Higher
                        {
                            os << "Tensor:" << std::endl;
                            os << "  Index: [";
                            for (auto ix = 0u; ix < nr_dims; ++ix)
                                os << index[ix] << ", ";
                            os << "]" << std::endl;
                            os << "  Submatrix: [" << std::endl;
                            const auto nr_rows = dimensions_[dimsize-2];
                            const auto nr_cols = dimensions_[dimsize-1];
                            for (auto row = 0u; row < nr_rows; ++row, ptr += nr_cols)
                            {
                                os << "  [";
                                for (auto col = 0u; col < nr_cols; ++col)
                                    os << ptr[col] << ", ";
                                os << "]" << std::endl;
                            }
                            os << "]" << std::endl;
                        }
                        break;
                }
            };
            tensor::each_index(dimensions_, nr_dims, lambda);
            assert(ptr == data_.data()+data_.size());
        }

    private:
        void recompute_size_()
        {
            size_ = 1;
            for (auto dimsize: dimensions_)
                size_ *= dimsize;
        }

        Dimensions dimensions_;
        std::size_t size_;
        std::vector<T> data_;
    };

    template <typename T>
    inline std::ostream &operator<<(std::ostream &os, const Tensor<T> &t)
    {
        t.stream(os);
        return os;
    }

} 

#endif
