#ifndef QLAB_DATETIME_YEAR_MONTH_DAY_HPP_EGK7MHUI
#define QLAB_DATETIME_YEAR_MONTH_DAY_HPP_EGK7MHUI


namespace QLab {


template <class Year, class Month, class Day>
struct YMDBase{
public:
	using year_type		= Year;
	using month_type	= Month;
	using day_type		= Day;

	constexpr YMDBase (year_type year, month_type month, day_type day):
		year(year),
		month(month),
		day(day)
	{}

	year_type	year;
	month_type	month;
	day_type	day;
};


} // namespace QLab


#endif // end of include guard: QLAB_DATETIME_YEAR_MONTH_DAY_HPP_EGK7MHUI
