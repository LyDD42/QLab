#ifndef QLAB_DATE_TIME_YEAR_MONTH_DAY_HPP_
#define QLAB_DATE_TIME_YEAR_MONTH_DAY_HPP_

namespace QLab {


template <class YearT_, class MonthT_, class DayT_>
struct YMDBase{
public:
	using YearT		= YearT_;
	using MonthT	= MonthT_;
	using DayT		= DayT_;

	YMDBase (YearT year, MonthT month, DayT day):
		year(year),
		month(month),
		day(day)
	{}

	YearT	year;
	MonthT	month;
	DayT	day;
};


} // namespace QLab


#endif
