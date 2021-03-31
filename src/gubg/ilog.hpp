#ifndef HEADER_gubg_ilog_hpp_ALREADY_INCLUDED
#define HEADER_gubg_ilog_hpp_ALREADY_INCLUDED

namespace gubg { 

    //Returns the number of bits required to write v in fixed-width
    //Note: 0 can be written with 0 bits
    template <typename T>
    unsigned int ilog2(T v)
    {
        unsigned int pop_cnt = 0u;
        for (; !!v; ++pop_cnt)
            v >>= 1;
        return pop_cnt;
    }

} 

#endif
