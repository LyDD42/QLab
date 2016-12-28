#ifndef DATE_TIME_GREG_YMD_HPP
#define DATE_TIME_GREG_YMD_HPP

#include "QLab/utilities/constrained_value.hpp"
#include "QLab/utilities/int_adapter.hpp"
#include "QLab/datetime/year_month_day.hpp"
#include "QLab/datetime/greg_calendar_base.hpp"

namespace QLab
{


using GregYear     = ConstrainedValue<LowerBounded<uint32_t, 1400>>;
using GregMonth    = ConstrainedValue<BiBounded<uint8_t, 1, 12>>;
using GregDay      = ConstrainedValue<BiBounded<uint8_t, 1, 31>>;

using GregYMD      = YMDBase<GregYear, GregMonth, GregDay>;

using GregDateRep  = IntAdapter<uint32_t>;

using GregCalendar = GregorianCalendarBase<GregYMD, GregDateRep::int_type>;


} // namespace QLab  

#endif // end of include guard: DATE_TIME_GREG_YMD_HPP
