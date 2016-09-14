#ifndef DATE_TIME_GREG_YMD_HPP
#define DATE_TIME_GREG_YMD_HPP

#include "utilities/constrained_value.hpp"
#include "datetime/year_month_day.hpp"

namespace QLab
{


using GregYear  = LowerBounded<int32_t, 1400>;
using GregMonth = BiBounded<int8_t, 1, 12>;
using GregDay   = BiBounded<int8_t, 1, 31>;

using GregYMD   = 


} // namespace QLab  

#endif // end of include guard: DATE_TIME_GREG_YMD_HPP
