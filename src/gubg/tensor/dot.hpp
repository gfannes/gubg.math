#ifndef HEADER_gubg_tensor_dot_hpp_ALREADY_INCLUDED
#define HEADER_gubg_tensor_dot_hpp_ALREADY_INCLUDED

#include <gubg/tensor/Tensor.hpp>
#include <stdexcept>

namespace gubg { namespace tensor { 

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
        throw std::out_of_range("Not implemented yet");
    }

} } 

#endif
