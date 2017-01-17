#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "QLab/math/array.hpp"

namespace utf = boost::unit_test;

using QLab::Array;

BOOST_AUTO_TEST_SUITE(test_math)

BOOST_AUTO_TEST_SUITE(test_array)

BOOST_AUTO_TEST_CASE(test)
{
    BOOST_TEST((Array<double, 1>::dim == 1));
}

BOOST_AUTO_TEST_CASE(test_constructor)
{
    Array<double, 1> array1{};
    BOOST_TEST(array2.size() == 0);
    Array<double, 2> array2{{2, 2}, 1.0};
    BOOST_TEST(array2.size() == 4);
    Array<double, 2> array3(array2);
}

BOOST_AUTO_TEST_SUITE_END() // test suite test_array

BOOST_AUTO_TEST_SUITE_END() // test suite test_math
