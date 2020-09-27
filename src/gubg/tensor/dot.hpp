#ifndef HEADER_gubg_tensor_dot_hpp_ALREADY_INCLUDED
#define HEADER_gubg_tensor_dot_hpp_ALREADY_INCLUDED

#include <gubg/tensor/Tensor.hpp>
#include <stdexcept>
#include <iostream>

namespace gubg { namespace tensor { 

    //Computes inproduct on last dimension of lhs and first dimension of rhs
    template <typename Dst, typename Lhs, typename Rhs>
    void dot(Tensor<Dst> &dst, const Tensor<Lhs> &lhs, const Tensor<Rhs> &rhs)
    {
        const auto &lhs_dims = lhs.dimensions();
        const auto &rhs_dims = rhs.dimensions();
        if (lhs_dims.empty() && rhs_dims.empty())
        {
            dst.resize({});
            dst[{}] = lhs[{}]*rhs[{}];
            return;
        }
        if (lhs_dims.empty() || rhs_dims.empty())
            throw std::out_of_range("Only one argument has no dimensions");
        if (lhs_dims.back() != rhs_dims.front())
            throw std::out_of_range("Last and first dimension should match for gubg::tensor::dot()");

        const auto lhs_dimssize_remain = lhs_dims.size()-1u;
        const auto rhs_dimssize_remain = rhs_dims.size()-1u;
        Dimensions new_dims(lhs_dimssize_remain + rhs_dimssize_remain);
        auto dst_dim = new_dims.begin();
        std::copy(lhs_dims.begin(), lhs_dims.begin()+lhs_dimssize_remain, dst_dim);
        dst_dim += lhs_dimssize_remain;
        std::copy(rhs_dims.begin()+1u, rhs_dims.end(), dst_dim);
        dst_dim += rhs_dimssize_remain;
        dst.resize(new_dims);
        dst.fill();

        const auto inprod_size = lhs_dims.back();

        const std::size_t lhs_size = lhs.size();
        const std::size_t lhs_size_remain = lhs.size()/inprod_size;
        const auto *lhs_ptr = lhs.data();

        const std::size_t rhs_size = rhs.size();
        const std::size_t rhs_size_remain = rhs.size()/inprod_size;

        auto *dst_ptr = dst.data();
        for (auto lhs_i = 0u; lhs_i < lhs_size_remain; ++lhs_i, dst_ptr += rhs_size_remain)
        {
            auto *rhs_ptr = rhs.data();
            for (auto inprod_i = 0u; inprod_i < inprod_size; ++inprod_i, ++lhs_ptr, rhs_ptr += rhs_size_remain)
            {
                const auto lhs_factor = *lhs_ptr;
                for (auto rhs_remain_i = 0u; rhs_remain_i < rhs_size_remain; ++rhs_remain_i)
                {
                    dst_ptr[rhs_remain_i] += lhs_factor*rhs_ptr[rhs_remain_i];
                }
            }
        }
    }

} } 

#endif
