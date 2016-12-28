#ifndef QLAB_DATETIME_DATE_BASE_HPP_AYUFJRUI
#define QLAB_DATETIME_DATE_BASE_HPP_AYUFJRUI


namespace QLab {


template <class Date_, class Calendar_, class Duration_>
class DateBase {
public:
	using date_type		= Date_;
	using calendar_type	= Calendar_;
	using duration_type = Duration_;
    using ymd_type      = typename calendar_type::ymd_type;
    using date_int_type = typename calendar_type::date_int_type;
    using year_type     = typename calendar_type::year_type;
    using month_type    = typename calendar_type::month_type;
    using day_type      = typename calendar_type::day_type;
    
    DateBase(year_type year, month_type month, day_type day)
        : days_(calendar_type::day_number(ymd_type(year, month, day)))
    {}
    DateBase(ymd_type ymd)
        : days_(calendar_type::day_number(ymd))
    {}

    constexpr DateBase(const DateBase<date_type, calendar_type, duration_type>&) = default;
    constexpr DateBase& operator=(const DateBase<date_type, calendar_type, duration_type>&) = default;
    constexpr DateBase(DateBase<date_type, calendar_type, duration_type>&&) = default;
    constexpr DateBase& operator=(DateBase<date_type, calendar_type, duration_type>&&) = default;
    ~DateBase() = default;


private:
    date_int_type days_;
};


} // namespace QLab


#endif // end of include guard: QLAB_DATETIME_DATE_BASE_HPP_AYUFJRUI
