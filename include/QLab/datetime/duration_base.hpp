#ifndef QLAB_DATETIME_DURATION_BASE_HPP_8X91EU3Y
#define QLAB_DATETIME_DURATION_BASE_HPP_8X91EU3Y

#include <ratio>
#include "QLab/utilities/traits.hpp"

namespace QLab {


template <typename Rep, typename Tick = std::ratio<1, 1>>
class DurationBase {
public:
    using impl_type  = Rep;
    //TODO: add support for built-in numeric types
    using value_type = typename impl_type::value_type;
    using tick_type = Tick;

    static constexpr DurationBase min();
    static constexpr DurationBase max();

    constexpr DurationBase()           = default;
    DurationBase(const DurationBase &) = default;
    DurationBase& operator             = (const DurationBase &) = default;
    // TODO: 1. what if Rep is not Literal
    //       2. 
    //DurationBase(DurationBase &&)      = default;
    //DurationBase& operator             = (DurationBase &&) = default;
    //! Rep2 should be implicitly convertible to rep_type
    template <typename Rep2>
    constexpr explicit DurationBase(const DurationBase<Rep2, tick_type> & other) : ticks_(other.ticks_) {} ;

    //! Rep
    template <typename Rep2, typename Tick2>
    constexpr explicit DurationBase(const DurationBase<Rep2, Tick2> &);

    //! return the count of ticks
    constexpr value_type count() const;

private:
    impl_type ticks_;
};

template<typename Rep, typename Tick>
template<typename Rep2, typename Tick2>
constexpr DurationBase<Rep, Tick>::DurationBase(const DurationBase<Rep2, Tick2> & other)
{

}


} // namespace QLab  


#endif // end of include guard: QLAB_DATETIME_DURATION_BASE_HPP_8X91EU3Y
