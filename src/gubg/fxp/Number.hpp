#ifndef HEADER_gubg_fxp_Number_hpp_ALREADY_INCLUDED
#define HEADER_gubg_fxp_Number_hpp_ALREADY_INCLUDED

#include <gubg/fxp/util.hpp>
#include <ostream>

namespace gubg { namespace fxp { 

    //number = repr*2^exp

    template <unsigned int Width, int Exp>
    class Number
    {
    public:
        using Self = Number<Width, Exp>;
        using Repr = typename util::Repr<Width>::Type;

        Number() {}
        template <typename T>
        Number(T v) {set(v);}

        Repr repr() const {return repr_;}

        template <typename Flt>
        Flt get() const {return to_flt_factor_*repr_;}

        template <typename Flt>
        void set(Flt flt) { repr_ = std::round(to_repr_factor_*flt); }

        Self operator+(const Self &rhs) const { return Self{repr_+rhs.repr_}; }
        Self operator-(const Self &rhs) const { return Self{repr_-rhs.repr_}; }
        Self operator*(const Self &rhs) const
        {
            if constexpr (Exp < 0)
            {
                constexpr Repr preshift_rounding = 1 << -(Exp+1);
                return Self{(repr_*rhs.repr_+preshift_rounding) >> -Exp};
            }
            if constexpr (Exp == 0)
                return Self{repr_*rhs.repr_};
            if constexpr (Exp > 0)
                return Self{(repr_*rhs.repr_) << Exp};
        }

        void stream(std::ostream &os) const
        {
            os << "[fxp::Number](width:" << Width << ")(exp:" << Exp << ")(repr:" << repr_ << ")";
        }

    private:
        static constexpr double to_flt_factor_ =  util::pow(2.0, Exp);
        static constexpr double to_repr_factor_ = util::pow(2.0, -Exp);

        Number(Repr repr): repr_(repr) {}

        Repr repr_ = 0;
    };

    template <unsigned int Width, int Exp>
    std::ostream &operator<<(std::ostream &os, const Number<Width, Exp> &nbr)
    {
        nbr.stream(os);
        return os;
    }

} } 

#endif
