#ifndef QLAB_UTILITIES_IN_ADAPTER_HPP_HITP3UES
#define QLAB_UTILITIES_IN_ADAPTER_HPP_HITP3UES

#include <limits>
#include <type_traits>


namespace QLab {

namespace utilities {


enum class SpecialValues : int {
    not_a_num,
    neg_inf,
    pos_inf,
    min, max,
    not_special
};


//! Adapter to create integer types with +-infinity, and not a value
/*! This class is used internally in counted date/time representations.
 *  It adds the floating point like features of infinities and
 *  not a number. It also provides mathmatical operations with
 *  consideration to special values following these rules:
 *@code
 *  +infinity  -  infinity  == Not A Number (NAN)
 *   infinity  *  non-zero  == infinity
 *   infinity  *  zero      == NAN
 *  +infinity  * -integer   == -infinity
 *   infinity  /  infinity  == NAN
 *   infinity  *  infinity  == infinity 
 *@endcode 
 */
template <typename Int_>
class IntAdapter {
public:
    using Int = Int_;

    constexpr IntAdapter(const Int v) : value_(v) {}

    static constexpr bool has_infinity() noexcept
    {
        return true;
    }

    static constexpr IntAdapter  pos_inf()
    {
        return (::std::numeric_limits<Int>::max)();
    }
    static constexpr IntAdapter  neg_inf()
    {
        return (::std::numeric_limits<Int>::min)();
    }
    static constexpr IntAdapter  not_a_num()
    {
        return (::std::numeric_limits<Int>::max)()-1;
    }
    static constexpr IntAdapter max ()
    {
        return (::std::numeric_limits<Int>::max)()-2;
    }
    static constexpr IntAdapter min ()
    {
        return (::std::numeric_limits<Int>::min)()+1;
    }
    static constexpr IntAdapter from_special(SpecialValues sv)
    {
        if (sv == SpecialValues::not_a_num)
        { 
            return not_a_num();
        } else if (sv == SpecialValues::neg_inf) 
        {
            return neg_inf();
        } else if (sv == SpecialValues::pos_inf)
        {
            return pos_inf();
        } else if (sv == SpecialValues::max)
        {
            return max();
        } else if (sv == SpecialValues::min) 
        {
            return min();
        }
        return not_a_num();
    }
    //! Returns either special value type or is_not_special
    static constexpr SpecialValues to_special(Int v)
    {
        if (is_nan(v)) return SpecialValues::not_a_num;
        if (is_neg_inf(v)) return SpecialValues::neg_inf;
        if (is_pos_inf(v)) return SpecialValues::pos_inf;
        return SpecialValues::not_special;
    }
    static constexpr bool is_inf(Int v)
    {
        return (v == neg_inf().as_number() ||
                v == pos_inf().as_number());
    }
    static constexpr bool is_neg_inf(Int v)
    {
        return (v == neg_inf().as_number());
    }
    static constexpr bool is_pos_inf(Int v)
    {
        return (v == pos_inf().as_number());
    }
    static constexpr bool is_nan(Int v)
    {
        return (v == not_a_num().as_number());
    }
    //-3 leaves room for representations of infinity and not a date
    static constexpr Int maxcount()
    {
        return (::std::numeric_limits<Int>::max)()-3;
    }
    constexpr bool is_inf() const
    {
        return (value_ == neg_inf().as_number() ||
                value_ == pos_inf().as_number());
    }
    constexpr bool is_pos_inf() const
    {
        return(value_ == pos_inf().as_number());
    }
    constexpr bool is_neg_inf() const
    {
        return(value_ == neg_inf().as_number());
    }
    constexpr bool is_nan() const
    {
        return (value_ == not_a_num().as_number());
    }
    constexpr bool is_special() const
    {
        return(is_inf() || is_nan()); 
    }
    constexpr Int as_number() const
    {
        return value_;
    }
    //! Returns either special value type or is_not_special
    constexpr SpecialValues as_special() const
    {
        return IntAdapter::to_special(value_);
    }

    //creates nasty ambiguities
    //   operator Int() const
    //   {
    //     return value_;
    //   }
    
    constexpr IntAdapter operator+() const
    {
        return *this;
    }

    constexpr IntAdapter operator-() const
    {
        if (is_nan()) return not_a_num();
        if (is_neg_inf()) return pos_inf();
        if (is_pos_inf()) return neg_inf();
        return IntAdapter<Int>(static_cast<Int>(-value_));
    }

private:
    Int value_;
};


//! returns -1, 0, 1, or 2 if 'this' is <, ==, >, or 'nan comparison' rhs
template <typename Int1, typename Int2>
constexpr int compare( const IntAdapter<Int1> & lhs, const IntAdapter<Int2> & rhs)
{
    if ( lhs.is_nan() || rhs.is_nan() )
    {
        if ( lhs.is_nan() && rhs.is_nan() )
        {
            return 0;
        } else {
            return 2;
        }
    }
    if ( (lhs.is_neg_inf() && !rhs.is_neg_inf()) ||
            (rhs.is_pos_inf() && !lhs.is_pos_inf()))
    {
        return -1;
    }
    if ( (lhs.is_pos_inf() && !rhs.is_pos_inf()) ||
            (rhs.is_neg_inf() && !lhs.is_neg_inf()))
    {
        return 1;
    }
    if ( (lhs.is_pos_inf() && rhs.is_pos_inf()) ||
            (rhs.is_neg_inf() && lhs.is_neg_inf()))
    {
        return 0;
    }
    if ( lhs.as_number() < rhs.as_number() ) return -1;
    if ( lhs.as_number() > rhs.as_number() ) return 1;
    return 0;

}

template <typename Int1, typename Int2>
constexpr int compare( const IntAdapter<Int1> & lhs, const Int2 & rhs)
{
    if ( lhs.is_nan() ) return 2;
    if ( lhs.is_neg_inf() ) return -1;
    if ( lhs.is_pos_inf() ) return 1;
    if ( lhs.as_number() < rhs ) return -1;
    if ( lhs.as_number() > rhs ) return 1;
    return 0;
}

template <typename Int1, typename Int2>
constexpr int compare( const Int1 & lhs, const IntAdapter<Int2> & rhs)
{
    if ( rhs.is_nan() ) return 2;
    if ( rhs.is_neg_inf() ) return 1;
    if ( rhs.is_pos_inf() ) return -1;
    if ( rhs < rhs.as_number() ) return -1;
    if ( rhs > rhs.as_number() ) return 1;
    return 0;
}

template <typename Int1, typename Int2>
constexpr bool operator==( const Int1 & lhs, const Int2 & rhs)
{
    return (compare(lhs, rhs) == 0);
}

template <typename Int1, typename Int2>
constexpr bool operator!=( const Int1 & lhs, const Int2 & rhs)
{
    return (compare(lhs, rhs) != 0);
}

template <typename Int1, typename Int2>
constexpr bool operator<( const Int1 & lhs, const Int2 & rhs)
{
    return (compare(lhs, rhs) == -1);
}

template <typename Int1, typename Int2>
constexpr bool operator<=( const Int1 & lhs, const Int2 & rhs)
{
    return ((compare(lhs, rhs) == -1) || (compare(lhs, rhs)==0));
}

template <typename Int1, typename Int2>
constexpr bool operator>( const Int1 & lhs, const Int2 & rhs)
{
    return (compare(lhs, rhs) == 1);
}

template <typename Int1, typename Int2>
constexpr bool operator>=( const Int1 & lhs, const Int2 & rhs)
{
    return ((compare(lhs, rhs) == 1) || (compare(lhs, rhs)==0));
}

template <typename Int1, typename Int2>
constexpr auto operator+(const IntAdapter<Int1> & lhs, const IntAdapter<Int2> & rhs)
    -> IntAdapter<typename std::common_type<Int1, Int2>::type>
{
    using CommonInt = typename std::common_type<Int1, Int2>::type;
    if ( lhs.is_nan() || rhs.is_nan())
    {
        return IntAdapter<CommonInt>::not_a_num();
    }
    if ( (lhs.is_neg_inf() && !rhs.is_pos_inf()) ||
            (!lhs.is_pos_inf() && rhs.is_neg_inf()))
    {
        return IntAdapter<CommonInt>::neg_inf();
    }
    if ( (lhs.is_pos_inf() && !rhs.is_neg_inf()) ||
            (!lhs.is_neg_inf() && rhs.is_pos_inf()))
    {
        return IntAdapter<CommonInt>::pos_inf();
    }
    if ( (lhs.is_pos_inf() && rhs.is_neg_inf()) ||
            (lhs.is_neg_inf() && rhs.is_pos_inf()))
    {
        return IntAdapter<CommonInt>::not_a_num();
    }
    return IntAdapter<CommonInt>(static_cast<CommonInt>(lhs.as_number()) + static_cast<CommonInt>(rhs.as_number()));
    // not sure should simply lhs.as_number() + rhs.as_number() work
}

template <typename Int1, typename Int2>
constexpr auto operator+(const IntAdapter<Int1> & lhs, const Int2 & rhs)
    -> IntAdapter<typename std::common_type<Int1, Int2>::type>
{
    using CommonInt = typename std::common_type<Int1, Int2>::type;
    if ( lhs.is_nan() )
    {
        return IntAdapter<CommonInt>::not_a_num();
    }
    if ( lhs.is_neg_inf() ) {
        return IntAdapter<CommonInt>::neg_inf();
    }
    if ( lhs.is_pos_inf() ) {
        return IntAdapter<CommonInt>::pos_inf();
    }
    return IntAdapter<CommonInt>(static_cast<CommonInt>(lhs.as_number()) + static_cast<CommonInt>(rhs));
}

template <typename Int1, typename Int2>
constexpr auto operator+(const Int1 & lhs, const IntAdapter<Int2> & rhs)
    -> IntAdapter<typename std::common_type<Int1, Int2>::type>
{
    using CommonInt = typename std::common_type<Int1, Int2>::type;
    if ( rhs.is_nan() )
    {
        return IntAdapter<CommonInt>::not_a_num();
    }
    if ( rhs.is_neg_inf() ) {
        return IntAdapter<CommonInt>::neg_inf();
    }
    if ( rhs.is_pos_inf() ) {
        return IntAdapter<CommonInt>::pos_inf();
    }
    return IntAdapter<CommonInt>(static_cast<CommonInt>(lhs) + static_cast<CommonInt>(rhs.as_number()));
}

template <typename Int1, typename Int2>
constexpr auto operator-(const IntAdapter<Int1> & lhs, const IntAdapter<Int2> & rhs)
    -> IntAdapter<typename std::common_type<Int1, Int2>::type>
{
    using CommonInt = typename std::common_type<Int1, Int2>::type;
    if ( lhs.is_nan() || rhs.is_nan())
    {
        return IntAdapter<CommonInt>::not_a_num();
    }
    if ( (lhs.is_neg_inf() && !rhs.is_neg_inf()) ||
            (!lhs.is_pos_inf() && rhs.is_pos_inf()))
    {
        return IntAdapter<CommonInt>::neg_inf();
    }
    if ( (lhs.is_pos_inf() && !rhs.is_pos_inf()) ||
            (!lhs.is_neg_inf() && rhs.is_neg_inf()))
    {
        return IntAdapter<CommonInt>::pos_inf();
    }
    if ( (lhs.is_pos_inf() && rhs.is_pos_inf()) ||
            (lhs.is_neg_inf() && rhs.is_neg_inf()))
    {
        return IntAdapter<CommonInt>::not_a_num();
    }
    return IntAdapter<CommonInt>(static_cast<CommonInt>(lhs.as_number()) - static_cast<CommonInt>(rhs.as_number()));
    // not sure should simply lhs.as_number() - rhs.as_number() work
}

template <typename Int1, typename Int2>
constexpr auto operator-(const IntAdapter<Int1> & lhs, const Int2 & rhs)
    -> IntAdapter<typename std::common_type<Int1, Int2>::type>
{
    using CommonInt = typename std::common_type<Int1, Int2>::type;
    if ( lhs.is_nan() )
    {
        return IntAdapter<CommonInt>::not_a_num();
    }
    if ( lhs.is_neg_inf() ) {
        return IntAdapter<CommonInt>::neg_inf();
    }
    if ( lhs.is_pos_inf() ) {
        return IntAdapter<CommonInt>::pos_inf();
    }
    return IntAdapter<CommonInt>(static_cast<CommonInt>(lhs.as_number()) - static_cast<CommonInt>(rhs));
}

template <typename Int1, typename Int2>
constexpr auto operator-(const Int1 & lhs, const IntAdapter<Int2> & rhs)
    -> IntAdapter<typename std::common_type<Int1, Int2>::type>
{
    using CommonInt = typename std::common_type<Int1, Int2>::type;
    if ( rhs.is_nan() )
    {
        return IntAdapter<CommonInt>::not_a_num();
    }
    if ( rhs.is_neg_inf() ) {
        return IntAdapter<CommonInt>::pos_inf();
    }
    if ( rhs.is_pos_inf() ) {
        return IntAdapter<CommonInt>::neg_inf();
    }
    return IntAdapter<CommonInt>(static_cast<CommonInt>(lhs) - static_cast<CommonInt>(rhs.as_number()));
}


template <typename Int1, typename Int2>
constexpr auto mult_div_specials(const IntAdapter<Int1> & lhs, const IntAdapter<Int2> & rhs)
    -> IntAdapter<typename std::common_type<Int1, Int2>::type>
{
    using CommonInt = typename std::common_type<Int1, Int2>::type;
    if ( lhs.is_nan() || rhs.is_nan())
    {
        return IntAdapter<CommonInt>::not_a_num();
    }
    int min_value1 = std::numeric_limits<Int1>::is_signed ? 0 : 1;
    int min_value2 = std::numeric_limits<Int2>::is_signed ? 0 : 1;
    if ( (lhs < min_value1 && rhs < min_value2) ||
           (lhs > 0 && rhs > 0) )
    {
        return IntAdapter<CommonInt>::pos_inf();
    }
    if ( (lhs < min_value1 && rhs > 0) ||
           (lhs > 0 && rhs < min_value2) )
    {
        return IntAdapter<CommonInt>::neg_inf();
    }
    return IntAdapter<CommonInt>::not_a_num();
}

template <typename Int1, typename Int2>
constexpr auto mult_div_specials(const IntAdapter<Int1> & lhs, const Int2 & rhs)
    -> IntAdapter<typename std::common_type<Int1, Int2>::type>
{
    using CommonInt = typename std::common_type<Int1, Int2>::type;
    if ( lhs.is_nan() )
    {
        return IntAdapter<CommonInt>::not_a_num();
    }
    int min_value = std::numeric_limits<Int1>::is_signed ? 0 : 1;
    if ( (lhs < min_value && rhs < 0) ||
           (lhs > 0 && rhs > 0) )
    {
        return IntAdapter<CommonInt>::pos_inf();
    }
    if ( (lhs < min_value && rhs > 0) ||
           (lhs > 0 && rhs < 0) )
    {
        return IntAdapter<CommonInt>::neg_inf();
    }
    return IntAdapter<CommonInt>::not_a_num();
}

template <typename Int1, typename Int2>
constexpr auto operator*(const IntAdapter<Int1> & lhs, const IntAdapter<Int2> & rhs)
    -> IntAdapter<typename std::common_type<Int1, Int2>::type>
{
    using CommonInt = typename std::common_type<Int1, Int2>::type;
    if ( lhs.is_special() || rhs.is_special())
    {
        return mult_div_specials(lhs, rhs);
    }
    return IntAdapter<CommonInt>(static_cast<CommonInt>(lhs.as_number()) * static_cast<CommonInt>(rhs.as_number()));
    // not sure should simply lhs.as_number() * rhs.as_number() work
}

template <typename Int1, typename Int2>
constexpr auto operator*(const IntAdapter<Int1> & lhs, const Int2 & rhs)
    -> IntAdapter<typename std::common_type<Int1, Int2>::type>
{
    using CommonInt = typename std::common_type<Int1, Int2>::type;
    if (lhs.is_special()) {
        return mult_div_specials(lhs, rhs);
    }
    return IntAdapter<CommonInt>(static_cast<CommonInt>(lhs.as_number()) * static_cast<CommonInt>(rhs));
    // not sure should simply lhs.as_number() * rhs.as_number() work
}

template <typename Int1, typename Int2>
constexpr auto operator*(const Int1 & lhs, const IntAdapter<Int2> & rhs)
    -> IntAdapter<typename std::common_type<Int1, Int2>::type>
{
    using CommonInt = typename std::common_type<Int1, Int2>::type;
    if (rhs.is_special()) {
        return mult_div_specials(rhs, lhs);
    }
    return IntAdapter<CommonInt>(static_cast<CommonInt>(lhs) * static_cast<CommonInt>(rhs.as_number()));
    // not sure should simply lhs.as_number() * rhs.as_number() work
}

template <typename Int1, typename Int2>
constexpr auto operator/(const IntAdapter<Int1> & lhs, const IntAdapter<Int2> & rhs)
    -> IntAdapter<typename std::common_type<Int1, Int2>::type>
{
    using CommonInt = typename std::common_type<Int1, Int2>::type;
    if ( lhs.is_special() || rhs.is_special())
    {
        if ( lhs.is_inf() && rhs.is_inf() )
        {
            return IntAdapter<CommonInt>::not_a_num();
        }
        if ( rhs != 0 )
        {
            return mult_div_specials(lhs, rhs);
        }
        // else let it blow up
    }
    return IntAdapter<CommonInt>(static_cast<CommonInt>(lhs.as_number()) / static_cast<CommonInt>(rhs.as_number()));
    // not sure should simply lhs.as_number() * rhs.as_number() work
}

template <typename Int1, typename Int2>
constexpr auto operator/(const IntAdapter<Int1> & lhs, const Int2 & rhs)
    -> IntAdapter<typename std::common_type<Int1, Int2>::type>
{
    using CommonInt = typename std::common_type<Int1, Int2>::type;
    if ( lhs.is_special() && rhs != 0 )
    {
        return mult_div_specials(lhs, rhs);
        // else let it blow up
    }
    return IntAdapter<CommonInt>(static_cast<CommonInt>(lhs.as_number()) / static_cast<CommonInt>(rhs));
    // not sure should simply lhs.as_number() * rhs.as_number() work
}


} // namespace utilities  


} // namespace QLab  

#endif // end of include guard: QLAB_UTILITIES_IN_ADAPTER_HPP_HITP3UES
