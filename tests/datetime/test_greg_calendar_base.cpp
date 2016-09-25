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

BOOST_AUTO_TEST_CASE(test_from_day_number) {
    auto ymd1 = greg_clendar.from_day_number(2451545);
    BOOST_TEST(((ymd1.year == 2000) && (ymd1.month==1) && (ymd1.day == 1)), "2000-01-01 is day 2451545");
    auto ymd2 = greg_clendar.from_day_number(2451911);
    BOOST_TEST(((ymd2.year == 2001) && (ymd2.month==1) && (ymd2.day == 1)), "2001-01-01 is day 2451911");
}

BOOST_AUTO_TEST_CASE(test_day_number) {
    auto day_number1 = greg_clendar.day_number(QLab::GregYMD(2000, 1, 1));
    BOOST_TEST(day_number1==2451545, "2000-01-01 is day 2451545");
    auto day_number2 = greg_clendar.day_number(QLab::GregYMD(2001, 1, 1));
    BOOST_TEST(day_number2==2451911, "2001-01-01 is day 2451911");
}

BOOST_AUTO_TEST_CASE(test_epoch) {
    auto ymd = greg_clendar.epoch();
    BOOST_TEST(((ymd.year == 1400) && (ymd.month==1) && (ymd.day == 1)), "1400-01-01 is the first day");
}

BOOST_AUTO_TEST_CASE(test_is_leap_year) {
    BOOST_TEST(greg_clendar.is_leap_year(1404), "1404 is a leap year");
    BOOST_TEST(greg_clendar.is_leap_year(2000), "2000 is a leap year");
    BOOST_TEST(greg_clendar.is_leap_year(2004), "2004 is a leap year");
    BOOST_TEST(greg_clendar.is_leap_year(2400), "2400 is a leap year");
    BOOST_TEST(greg_clendar.is_leap_year(4000), "4000 is a leap year");
    BOOST_TEST(!greg_clendar.is_leap_year(1400), "1400 is not a leap year");
    BOOST_TEST(!greg_clendar.is_leap_year(1900), "1900 is not a leap year");
    BOOST_TEST(!greg_clendar.is_leap_year(2100), "2100 is not a leap year");
    BOOST_TEST(!greg_clendar.is_leap_year(1999), "1999 is not a leap year");
    BOOST_TEST(!greg_clendar.is_leap_year(5000), "5000 is not a leap year");
}

BOOST_AUTO_TEST_CASE(test_week_number) {
    BOOST_TEST(greg_clendar.week_number(QLab::GregYMD(1400, 1, 1)) == 1, "1400-01-01 is week 1");
    BOOST_TEST(greg_clendar.week_number(QLab::GregYMD(9999, 12, 31)) == 52, "9999-12-31 is week 52");
    BOOST_TEST(greg_clendar.week_number(QLab::GregYMD(2004, 10, 18)) == 43, "2004-10-18 is week 43");
    BOOST_TEST(greg_clendar.week_number(QLab::GregYMD(2003, 12, 29)) == 1, "2003-12-29 is week 1");
    BOOST_TEST(greg_clendar.week_number(QLab::GregYMD(1993, 1, 1)) == 53, "1993-01-01 is week 53");
    BOOST_TEST(greg_clendar.week_number(QLab::GregYMD(1993, 1, 2)) == 53, "1993-01-02 is week 53");
    BOOST_TEST(greg_clendar.week_number(QLab::GregYMD(1993, 1, 3)) == 53, "1993-01-03 is week 53");
    BOOST_TEST(greg_clendar.week_number(QLab::GregYMD(1993, 1, 4)) == 1, "1993-01-04 is week 1");
}

BOOST_AUTO_TEST_SUITE_END()
