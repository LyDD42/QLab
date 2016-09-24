// BOOST TEST
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "QLab/datetime/greg_calendar_base.hpp"
#include "QLab/datetime/greg_ymd.hpp"

struct F{
    F() : greg_clendar{} {}
    ~F(){}
    QLab::GregorianCalendarBase<QLab::GregYMD, int> greg_clendar;
};

BOOST_FIXTURE_TEST_SUITE(test_GregorianCalendarBase, F)

BOOST_AUTO_TEST_CASE(test_from_day_number){
    auto ymd1 = greg_clendar.from_day_number(2451545);
    BOOST_TEST(((ymd1.year == 2000) && (ymd1.month==1) && (ymd1.day == 1)), "2000-01-01 is day 2451545");
    auto ymd2 = greg_clendar.from_day_number(2451911);
    BOOST_TEST(((ymd2.year == 2001) && (ymd2.month==1) && (ymd2.day == 1)), "2001-01-01 is day 2451911");
}

BOOST_AUTO_TEST_SUITE_END()
