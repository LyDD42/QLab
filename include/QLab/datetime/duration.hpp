#ifndef DURATION_HPP_SU4L7HET
#define DURATION_HPP_SU4L7HET

#include <ratio>


namespace QLab {


namespace datetime {


template <typename RepT_, typename UnitT_ = std::ratio<1> >
class DurationBase{
public:
    using RepT  = RepT_;
    using UnitT = UnitT_;

    constexpr DurationBase() : ticks_(0) {};
    constexpr DurationBase( const DurationBase<RepT, UnitT>& other ) : ticks_(other.ticks_) {};

    template <typename UnitT2>
    constexpr DurationBase( const DurationBase<RepT, UnitT2>& );

private:
    RepT ticks_;
};


template <typename RepT_, typename UnitT_>
template <typename UnitT2>
constexpr DurationBase<RepT_, UnitT_>::DurationBase( const DurationBase<RepT_, UnitT2>& )
{
     
}


} // namespace datetime   


} // namespace QLab  

#endif // end of include guard: DURATION_HPP_SU4L7HET
