#ifndef HEADER_gubg_tensor_each_hpp_ALREADY_INCLUDED
#define HEADER_gubg_tensor_each_hpp_ALREADY_INCLUDED

#include <gubg/tensor/types.hpp>

namespace gubg { namespace tensor { 

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

} } 

#endif
