#ifndef QLAB_DATE_TIME_DATE_HPP_
#define QLAB_DATE_TIME_DATE_HPP_


namespace QLab {


template <class DateT_, class CalenderT_, class DurationT_>
class DateBaseT {
public:
	using DateT		= DateT_;
	using CalenderT	= CalenderT_;
	using DurationT = DurationT_;
    using YMDT      = typename CalenderT::YMDT;
    using DateIntT  = typename CalenderT::DateIntT;
    using YearT     = typename CalenderT::YearT;
    using MonthT    = typename CalenderT::MonthT;
    using DayT      = typename CalenderT::DayT;
    
    DateBaseT(YearT year, MonthT month, DayT day)
        : days_(CalenderT::day_number(YMDT(year, month, day)))
    {}
    DateBaseT(YMDT ymd)
        : days_(CalenderT::day_number(ymd))
    {}

private:
    DateIntT days_;
};


} // namespace QLab


#endif
