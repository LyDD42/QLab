// BOOST TEST
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "QLab/utilities/constrained_value.hpp"
#include <stdexcept>

using IntBiggerThan10 = QLab::ConstrainedValue<QLab::LowerBounded<int, 10>>;
using IntSmallerThan10 = QLab::ConstrainedValue<QLab::UpperBounded<int, 10>>;

BOOST_AUTO_TEST_SUITE(test_ConstrainedValue)
BOOST_AUTO_TEST_CASE(test_LowerBounded){
    BOOST_CHECK_THROW(IntBiggerThan10(0), std::out_of_range);
    BOOST_TEST(IntBiggerThan10(10)==10);
}

BOOST_AUTO_TEST_CASE(test_UpperBounded){
    BOOST_CHECK_THROW(IntSmallerThan10(11), std::out_of_range);
    BOOST_TEST(IntSmallerThan10(10)==10);
}

BOOST_AUTO_TEST_SUITE_END()
