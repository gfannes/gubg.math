#ifndef HEADER_gubg_Tensor_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Tensor_hpp_ALREADY_INCLUDED

#include <gubg/tensor/types.hpp>
#include <gubg/tensor/each.hpp>
#include <gubg/tensor/str.hpp>

#include <ostream>
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <sstream>

#include <iostream>

namespace gubg { 

    template <typename T>
    class Tensor
    {
    public:
        using Dimensions = tensor::Dimensions;
        using Index = tensor::Index;
        using Data = std::vector<T>;
        using Self = Tensor<T>;

        Tensor();
        Tensor(const Dimensions  & dimensions);
        Tensor(const Dimensions  & dimensions, Data data);

        static Self zeros(const Dimensions & dimensions);
        static Self ones(const Dimensions & dimensions);
        static Self eye(std::size_t dimension);

        //operator[](std::size_t ix) is not provided since it leads to errors with matrix[1,2] being interpreted to matrix[2]
        //due to the comma operator iso the expected matrix[{1,2}]
        //T &operator[](std::size_t ix);
        T &operator[](const Index & ixs);
        const T &operator[](const Index & ixs) const;

        template <typename Rhs>
        bool operator==(const Rhs &rhs) const;
        template <typename Rhs>
        bool operator!=(const Rhs &rhs) const {return !operator==(rhs);}

        template <typename Rhs>
        Self &operator+=(const Rhs &rhs);
        template <typename Rhs>
        Self &operator-=(const Rhs &rhs);

        const std::size_t size() const {return size_;}
        const Dimensions & dimensions() const {return dimensions_;}

        Self &reshape(const Dimensions & dimensions);
        Self &resize(const Dimensions & dimensions);

        template <typename Ftor>
        void broadcast(Ftor &&ftor);

        void stream(std::ostream &os) const;

    private:
        static std::size_t data_size_(const Dimensions & dimensions);
        void process_new_dimensions_();

        Dimensions dimensions_;

        tensor::Strides strides_;
        std::size_t size_;
        Data data_;
    };


    //Public method implementation
    //
    //Constructors
    template <typename T>
    Tensor<T>::Tensor()
    {
        process_new_dimensions_();
        data_.resize(size_);
    }
    template <typename T>
    Tensor<T>::Tensor(const Dimensions & dimensions)
    : dimensions_(dimensions)
    {
        process_new_dimensions_();
        data_.resize(size_);
    }
    template <typename T>
    Tensor<T>::Tensor(const Dimensions & dimensions, Data data)
    : dimensions_(dimensions)
    {
        process_new_dimensions_();
        if (data.size() == size_)
            data_.swap(data);
        else
        {
            data_.resize(size_);
            const auto *src = &data[0];
            auto *dst = &data_[0];
            const auto nr_to_copy = std::min(size_, data.size());
            std::copy(src, src+nr_to_copy, dst);
        }
    }

    template <typename T>
    typename Tensor<T>::Self Tensor<T>::zeros(const Dimensions & dimensions)
    {
        return Self{dimensions};
    }
    template <typename T>
    typename Tensor<T>::Self Tensor<T>::ones(const Dimensions & dimensions)
    {
        Self t{dimensions};
        std::fill(t.data_.begin(), t.data_.end(), 1);
        return t;
    }
    template <typename T>
    typename Tensor<T>::Self Tensor<T>::eye(std::size_t dimension)
    {
        Self t{{dimension, dimension}};
        for (auto ix = 0u; ix < dimension; ++ix)
            t[{ix,ix}] = 1;
        return t;
    }

    template <typename T>
    T &Tensor<T>::operator[](const Index & ixs)
    {
        const auto nr_dims = dimensions_.size();
        assert(ixs.size() == nr_dims);
        std::size_t my_ix = 0;
        auto stride_it = strides_.begin();
        for (auto ix: ixs)
        {
            my_ix += *stride_it*ix;
            ++stride_it;
        }
        return data_[my_ix];
    }
    template <typename T>
    const T &Tensor<T>::operator[](const Index & ixs) const
    {
        const auto nr_dims = dimensions_.size();
        assert(ixs.size() == nr_dims);
        std::size_t my_ix = 0;
        auto stride_it = strides_.begin();
        for (auto ix: ixs)
        {
            my_ix += *stride_it*ix;
            ++stride_it;
        }
        return data_[my_ix];
    }

    template <typename T>
    template <typename Rhs>
    bool Tensor<T>::operator==(const Rhs &rhs) const
    {
        if (dimensions_ != rhs.dimensions_)
            return false;
        assert(size_ == rhs.size_);
        bool same_data = true;
        for (auto ix = 0u; ix < size_; ++ix)
            same_data = same_data && (data_[ix] == rhs.data_[ix]);
        return same_data;
    }

    template <typename T>
    template <typename Rhs>
    typename Tensor<T>::Self &Tensor<T>::operator+=(const Rhs &rhs)
    {
        if (dimensions_ != rhs.dimensions_)
        {
            std::ostringstream oss;
            oss << "Cannot operator+=(), sizes do not match: lhs: " << tensor::dim_str(dimensions_) << ", rhs: " << tensor::dim_str(rhs.dimensions_);
            throw std::length_error(oss.str());
        }
        for (auto ix = 0u; ix < size_; ++ix)
            data_[ix] += rhs.data_[ix];
        return *this;
    }
    template <typename T>
    template <typename Rhs>
    typename Tensor<T>::Self &Tensor<T>::operator-=(const Rhs &rhs)
    {
        if (dimensions_ != rhs.dimensions_)
        {
            std::ostringstream oss;
            oss << "Cannot operator-=(), sizes do not match: lhs: " << tensor::dim_str(dimensions_) << ", rhs: " << tensor::dim_str(rhs.dimensions_);
            throw std::length_error(oss.str());
        }
        for (auto ix = 0u; ix < size_; ++ix)
            data_[ix] -= rhs.data_[ix];
        return *this;
    }

    template <typename T>
    typename Tensor<T>::Self &Tensor<T>::reshape(const Dimensions & dimensions)
    {
        Dimensions new_dimensions = dimensions;
        const auto size = data_size_(new_dimensions);
        if (size != size_)
        {
            std::ostringstream oss;
            oss << "Cannot reshape Tensor, total size does not match: old size: " << size_ << " new size: " << size;
            throw std::out_of_range(oss.str());
        }
        dimensions_.swap(new_dimensions);
        process_new_dimensions_();
        return *this;
    }
    template <typename T>
    typename Tensor<T>::Self &Tensor<T>::resize(const Dimensions & dimensions)
    {
        dimensions_ = dimensions;
        process_new_dimensions_();
        return *this;
    }

    template <typename T>
    template <typename Ftor>
    void Tensor<T>::broadcast(Ftor &&ftor)
    {
        for (auto &v: data_)
            v = ftor(v);
    }

    template <typename T>
    void Tensor<T>::stream(std::ostream &os) const
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

    //Private method implementation
    template <typename T>
    std::size_t Tensor<T>::data_size_(const Dimensions & dimensions)
    {
        std::size_t size = 1;
        for (auto dimsize: dimensions)
            size *= dimsize;
        return size;
    }
    template <typename T>
    void Tensor<T>::process_new_dimensions_()
    {
        size_ = data_size_(dimensions_);

        {
            std::size_t stride = 1;
            strides_.resize(dimensions_.size());
            for (auto ix = dimensions_.size(); ix > 0;)
            {
                --ix;
                strides_[ix] = stride;
                stride *= dimensions_[ix];
            }
        }
    }

    //Free function implementation
    template <typename T>
    inline std::ostream &operator<<(std::ostream &os, const Tensor<T> &t)
    {
        t.stream(os);
        return os;
    }

} 

#endif
