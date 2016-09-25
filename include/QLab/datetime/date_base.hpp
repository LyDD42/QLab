#ifndef QLAB_DATETIME_DATE_BASE_HPP_AYUFJRUI
#define QLAB_DATETIME_DATE_BASE_HPP_AYUFJRUI


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

    DateBaseT(const DateBaseT<DateT, CalenderT, DurationT>&) = default;
    DateBaseT& operator=(const DateBaseT<DateT, CalenderT, DurationT>&) = default;
    DateBaseT(DateBaseT<DateT, CalenderT, DurationT>&&) = default;
    DateBaseT& operator=(DateBaseT<DateT, CalenderT, DurationT>&&) = default;
    ~DateBaseT() = default;


private:
    DateIntT days_;
};


} // namespace QLab


#endif // end of include guard: QLAB_DATETIME_DATE_BASE_HPP_AYUFJRUI
