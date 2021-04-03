#ifndef HEADER_gubg_fxp_Number_hpp_ALREADY_INCLUDED
#define HEADER_gubg_fxp_Number_hpp_ALREADY_INCLUDED

#include <gubg/fxp/util.hpp>
#include <ostream>

namespace gubg { namespace fxp { 

    template <unsigned int Width, int Exp>
    class Number
    {
    public:
        using Repr = typename util::Repr<Width>::Type;

        Number() {}
        template <typename T>
        Number(T v) {set(v);}

        Repr repr() const {return repr_;}

        template <typename Flt>
        Flt get() const {return to_flt_factor_*repr_;}

        template <typename Flt>
        void set(Flt flt) { repr_ = std::round(to_repr_factor_*flt); }

        void stream(std::ostream &os) const
        {
            os << "[fxp::Number](width:" << Width << ")(exp:" << Exp << ")(repr:" << repr_ << ")";
        }

    private:
        static constexpr double to_flt_factor_ =  util::pow(2.0, Exp);
        static constexpr double to_repr_factor_ = util::pow(2.0, -Exp);

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
