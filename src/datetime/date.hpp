#ifndef QLAB_DATE_TIME_DATE_HPP_
#define QLAB_DATE_TIME_DATE_HPP_


namespace QLab {


template <class date_type_, class calender_type_, class duration_type_>
class base_date_type {
public:
	using date_type		= date_type_;
	using calender_type	= calender_type_;
	using duration_type = duration_type_;

private:
protected:
};


} // namespace QLab


#endif
