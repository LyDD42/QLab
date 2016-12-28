#ifndef QLAB_DATETIME_YEAR_MONTH_DAY_HPP_EGK7MHUI
#define QLAB_DATETIME_YEAR_MONTH_DAY_HPP_EGK7MHUI


namespace QLab {


template <class YearT_, class MonthT_, class DayT_>
struct YMDBase{
public:
	using YearT		= YearT_;
	using MonthT	= MonthT_;
	using DayT		= DayT_;

	constexpr YMDBase (YearT year, MonthT month, DayT day):
		year(year),
		month(month),
		day(day)
	{}

	YearT	year;
	MonthT	month;
	DayT	day;
};


} // namespace QLab


#endif // end of include guard: QLAB_DATETIME_YEAR_MONTH_DAY_HPP_EGK7MHUI
