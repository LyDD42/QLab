#ifndef QLAB_DATE_TIME_CALENDER_HPP_
#define QLAB_DATE_TIME_CALENDER_HPP_


namespace QLab {

template <class ymd_type_, class date_int_type_>
class calender_type_base{
public:
	using ymd_type		= ymd_type_;
	using year_type		= typename ymd_type::yer_type;
	using month_type	= typename ymd_type::month_type;
	using day_type		= typename ymd_type::day_type;
	using date_int_type = date_int_type_;

	static ymd_type from_day_num (date_int_type);
	static date_int_type day_num (ymd_type);

};


} // namespace QLab


#endif
