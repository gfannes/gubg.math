#ifndef HEADER_gubg_fxp_util_hpp_ALREADY_INCLUDED
#define HEADER_gubg_fxp_util_hpp_ALREADY_INCLUDED

#include <cstdint>
#include <cmath>

namespace gubg { namespace fxp { 

    namespace util { 

        template <unsigned int Width> struct Repr { };
        template <>                   struct Repr<8>  {using Type = std::int8_t;};
        template <>                   struct Repr<16> {using Type = std::int16_t;};
        template <>                   struct Repr<32> {using Type = std::int32_t;};
        template <>                   struct Repr<64> {using Type = std::int64_t;};

        template <typename Flt>
        constexpr Flt pow(Flt base, int exp)
        {
            return std::pow(base, exp);
        }

    } 

} } 

#endif
