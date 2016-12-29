#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "QLab/math/array.hpp"

namespace utf = boost::unit_test;

using QLab::Array;

BOOST_AUTO_TEST_SUITE(test_math)

BOOST_AUTO_TEST_SUITE(test_array)

BOOST_AUTO_TEST_CASE(test)
{
    Array<int, 1>();
    BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE_END() // test suite test_array

BOOST_AUTO_TEST_SUITE_END() // test suite test_math
