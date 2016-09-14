#ifndef QLAB_DATE_TIME_CALENDER_HPP_
#define QLAB_DATE_TIME_CALENDER_HPP_


namespace QLab {


template <class YMDT_, class DateIntT_>
class GregorianCalenderBase{
public:
	using YMDT		= YMDT_;
	using YearT		= typename YMDT::YerT;
	using MonthT	= typename YMDT::MonthT;
	using DayT		= typename YMDT::DayT;
	using DateIntT  = DateIntT_;

	static YMDT from_day_num (const DateIntT);
	static DateIntT_ day_num (const YMDT_&);
};


//! Change a day number into a year-month-day
template<typename YMDT_, typename DateIntT_>
YMDT GregorianCalenderBase<YMDT_, DateIntT_>::from_day_number(DateIntT dayNumber)
{
    DateIntT a = dayNumber + 32044;
    DateIntT b = (4*a + 3)/146097;
    DateIntT c = a-((146097*b)/4);
    DateIntT d = (4*c + 3)/1461;
    DateIntT e = c - (1461*d)/4;
    DateIntT m = (5*e + 2)/153;
    uint32_t day   = static_cast<uint32_t>(e - ((153*m + 2)/5) + 1);
    uint32_t month = static_cast<uint32_t>(m + 3 - 12 * (m/10));
    YearT year     = static_cast<uint32_t>(100*b + d - 4800 + (m/10));
    return YMDT(static_cast<uint32_t>(year), month, day);
}


template<typename YMDT_, typename DateIntT_>
DateIntT GregorianCalenderBase<YMDT_, DateIntT_>::day_number(const YMDT& ymd){
   uint32_t a = static_cast<uint32_t>((14-ymd.month)/12);
   uint32_t y = static_cast<uint32_t>(ymd.year + 4800 - a);
   uint32_t m = static_cast<uint32_t>(ymd.month + 12*a - 3);                                                                                                                                    
   uint32_t d = ymd.day + ((153*m + 2)/5) + 365*y + (y/4) - (y/100) + (y/400) - 32045;
   return static_cast<DateIntT>(d);
}


} // namespace QLab



#endif
