#ifndef QLAB_DATE_TIME_CALENDER_HPP_
#define QLAB_DATE_TIME_CALENDER_HPP_

#include <cstdint>

namespace QLab {


template <class YMDT_, class DateIntT_>
class GregorianCalendarBase{
public:
    using YMDT      = YMDT_;
	using YearT		= typename YMDT::YearT;
	using MonthT	= typename YMDT::MonthT;
	using DayT		= typename YMDT::DayT;
	using DateIntT  = DateIntT_;

	static auto from_day_number(const DateIntT) -> YMDT;
	static auto day_number(const YMDT&) -> DateIntT;
    static auto epoch() -> YMDT;
    static auto is_leap_year(const YearT&) -> bool;
    static auto end_of_month(const YearT&, const MonthT&) -> uint8_t;
    static auto week_number(const YMDT&) -> uint8_t;
    static auto day_of_week(const YMDT&) -> uint8_t;

};


//! Change a day number into a year-month-day
template<typename YMDT_, typename DateIntT_>
auto GregorianCalendarBase<YMDT_, DateIntT_>::from_day_number(DateIntT dayNumber) -> YMDT {
    DateIntT a    = dayNumber + 32044;
    DateIntT b    = (4*a + 3)/146097;
    DateIntT c    = a-((146097*b)/4);
    DateIntT d    = (4*c + 3)/1461;
    DateIntT e    = c - (1461*d)/4;
    DateIntT m    = (5*e + 2)/153;
    uint8_t day   = static_cast<uint8_t>(e - ((153*m + 2)/5) + 1);
    uint8_t month = static_cast<uint8_t>(m + 3 - 12 * (m/10));
    YearT year    = static_cast<uint32_t>(100*b + d - 4800 + (m/10));
    return YMDT(static_cast<uint32_t>(year), month, day);
}

template<typename YMDT_, typename DateIntT_>
auto GregorianCalendarBase<YMDT_, DateIntT_>::day_number(const YMDT& ymd) -> DateIntT {
   uint32_t a = static_cast<uint32_t>((14-ymd.month)/12);
   uint32_t y = static_cast<uint32_t>(ymd.year + 4800 - a);
   uint32_t m = static_cast<uint32_t>(ymd.month + 12*a - 3);
   uint32_t d = ymd.day + ((153*m + 2)/5) + 365*y + (y/4) - (y/100) + (y/400) - 32045;
   return static_cast<DateIntT>(d);
}

template<typename YMDT_, typename DateIntT_>
auto GregorianCalendarBase<YMDT_, DateIntT_>::is_leap_year(const YearT& year) -> bool {
    return (!(year % 4))  && ((year % 100) || (!(year % 400)));
}

template<typename YMDT_, typename DateIntT_>
auto GregorianCalendarBase<YMDT_, DateIntT_>::epoch() -> YMDT {
    return YMDT(1400, 1, 1);
}

template<typename YMDT_, typename DateIntT_>
auto GregorianCalendarBase<YMDT_, DateIntT_>::end_of_month(const YearT& year, const MonthT& month) -> uint8_t {
    switch (month) {
    case 2:
      if (is_leap_year(year)) {
        return 29;
      } else {
        return 28;
      };
    case 4:
    case 6:
    case 9:
    case 11:
      return 30;
    default:
      return 31;
    };
}


template<typename YMDT_, typename DateIntT_>
auto GregorianCalendarBase<YMDT_,DateIntT_>::week_number(const YMDT& ymd) -> uint8_t {
  uint64_t julianbegin = day_number(YMDT(ymd.year,1,1));
  uint64_t juliantoday = day_number(ymd);
  uint64_t day = (julianbegin + 3) % 7;
  uint64_t week = (juliantoday + day - julianbegin + 4)/7;

  if ((week >= 1) && (week <= 52)) {
    return static_cast<uint8_t>(week);
  }

  if (week == 53) {
    if((day==6) ||(day == 5 && is_leap_year(ymd.year))) {
      return static_cast<uint8_t>(week); //under these circumstances week == 53.
    } else {
      return 1; //monday - wednesday is in week 1 of next year
    }
  }
  //if the week is not in current year recalculate using the previous year as the beginning year
  else if (week == 0) {
    julianbegin = day_number(YMDT(static_cast<uint32_t>(ymd.year-1),1,1));
    juliantoday = day_number(ymd);
    day = (julianbegin + 3) % 7;
    week = (juliantoday + day - julianbegin + 4)/7;
    return static_cast<uint8_t>(week);
  }

  return static_cast<uint8_t>(week);  //not reachable -- well except if day == 5 and is_leap_year != true
}

template<typename YMDT_, typename DateIntT_>
auto GregorianCalendarBase<YMDT_,DateIntT_>::day_of_week(const YMDT& ymd) -> uint8_t {
    uint32_t a = static_cast<uint32_t>((14-ymd.month)/12);
    uint32_t y = static_cast<uint32_t>(ymd.year - a);
    uint32_t m = static_cast<uint32_t>(ymd.month + 12*a - 2);
    uint8_t d  = static_cast<uint8_t>((ymd.day + y + (y/4) - (y/100) + (y/400) + (31*m)/12) % 7);
    return d;
}


} // namespace QLab


#endif
