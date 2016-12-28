#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <cstdint>
#include "QLab/utilities/int_adapter.hpp"

namespace utf = boost::unit_test;

using QLab::IntAdapter;
using QLab::SpecialValues;

using UIntAdapted = IntAdapter<unsigned>;
using IntAdapted = IntAdapter<int>;

struct IntAdapterTestFix {
     IntAdapterTestFix () {} ;

     IntAdapted nan     = IntAdapted::not_a_num();
     IntAdapted inf     = IntAdapted::pos_inf();
     IntAdapted _inf    = IntAdapted::neg_inf();
     IntAdapted max_v   = IntAdapted::max();
     IntAdapted min_v   = IntAdapted::min();

     UIntAdapted unan   = UIntAdapted::not_a_num();
     UIntAdapted uinf   = UIntAdapted::pos_inf();
     UIntAdapted u_inf  = UIntAdapted::neg_inf();
     UIntAdapted umax_v = UIntAdapted::max();
     UIntAdapted umin_v = UIntAdapted::min();
};

BOOST_AUTO_TEST_SUITE(test_utilities)

BOOST_FIXTURE_TEST_SUITE(test_IntAdapter, IntAdapterTestFix)

BOOST_AUTO_TEST_CASE(test_comparison)
{
    BOOST_TEST((nan != 0));
    BOOST_TEST((inf > max_v));
    BOOST_TEST((_inf < min_v));

    BOOST_TEST((unan != 0));
    BOOST_TEST((uinf > umax_v));
    BOOST_TEST((u_inf < umin_v));
    BOOST_TEST((umin_v == 1));

    BOOST_TEST((nan == unan));
    BOOST_TEST((inf == uinf));
    BOOST_TEST((_inf == u_inf));
}

BOOST_AUTO_TEST_CASE(test_arith)
{
    // operator+
    BOOST_TEST((nan + 1 == nan));
    BOOST_TEST((nan + inf == nan));
    BOOST_TEST((nan + _inf == nan));
    BOOST_TEST((inf + _inf == nan));

    BOOST_TEST((unan + 1 == unan));
    BOOST_TEST((unan + uinf == unan));
    BOOST_TEST((unan + u_inf == unan));
    BOOST_TEST((uinf + u_inf == unan));

    // operator-
    BOOST_TEST((nan - 1 == nan));
    BOOST_TEST((nan - inf == nan));
    BOOST_TEST((nan - _inf == nan));
    BOOST_TEST((inf - inf == nan));
    BOOST_TEST((_inf - _inf == nan));
    BOOST_TEST((1 - inf == _inf));
    BOOST_TEST((1 - _inf == inf));

    BOOST_TEST((unan - 1 == unan));
    BOOST_TEST((unan - uinf == unan));
    BOOST_TEST((unan - u_inf == unan));
    BOOST_TEST((uinf - uinf == unan));
    BOOST_TEST((u_inf - u_inf == unan));
    BOOST_TEST((1 - uinf == u_inf));
    BOOST_TEST((1 - u_inf == uinf));

    // operator*
    BOOST_TEST((nan * 1 == nan));
    BOOST_TEST((nan * inf == nan));
    BOOST_TEST((nan * _inf == nan));
    BOOST_TEST((inf * 0 == nan));
    BOOST_TEST((_inf * 0 == nan));
    BOOST_TEST((inf * inf == inf));
    BOOST_TEST((_inf * _inf == inf));
    BOOST_TEST((1 * inf == inf));
    BOOST_TEST((-1 * _inf == inf));
    BOOST_TEST((inf * _inf == _inf));
    BOOST_TEST((1 * _inf == _inf));
    BOOST_TEST((-1 * inf == _inf));

    BOOST_TEST((unan * 1 == unan));
    BOOST_TEST((unan * uinf == unan));
    BOOST_TEST((unan * u_inf == unan));
    BOOST_TEST((uinf * 0 == unan));
    BOOST_TEST((u_inf * 0 == unan));
    BOOST_TEST((uinf * uinf == uinf));
    BOOST_TEST((u_inf * u_inf == uinf));
    BOOST_TEST((1 * uinf == uinf));
    BOOST_TEST((-1 * u_inf == uinf));
    BOOST_TEST((uinf * u_inf == u_inf));
    BOOST_TEST((1 * u_inf == u_inf));
    BOOST_TEST((-1 * uinf == u_inf));

    BOOST_TEST((nan * unan == nan));
    BOOST_TEST((uinf * UIntAdapted(1) == inf));

    // operator/
    // operator/(Int, IntAdapter) is not supported
    BOOST_TEST((nan / 1 == nan));
    BOOST_TEST((nan / inf == nan));
    BOOST_TEST((nan / _inf == nan));
    BOOST_TEST((inf / inf == nan));
    BOOST_TEST((_inf / _inf == nan));
    BOOST_TEST((inf / _inf == nan));
    BOOST_TEST((_inf / inf == nan));
    BOOST_TEST((inf / 1 == inf));
    BOOST_TEST((_inf / -1 == inf));
    BOOST_TEST((_inf / 1 == _inf));
    BOOST_TEST((inf / -1 == _inf));

    BOOST_TEST((unan / 1 == unan));
    BOOST_TEST((unan / uinf == unan));
    BOOST_TEST((unan / u_inf == unan));
    BOOST_TEST((uinf / uinf == unan));
    BOOST_TEST((u_inf / u_inf == unan));
    BOOST_TEST((uinf / u_inf == unan));
    BOOST_TEST((u_inf / uinf == unan));
    BOOST_TEST((uinf / 1 == uinf));
    BOOST_TEST((u_inf / -1 == uinf));
    BOOST_TEST((u_inf / 1 == u_inf));
    BOOST_TEST((uinf / -1 == u_inf));
}

BOOST_AUTO_TEST_SUITE_END() // test suite test_IntAdapter

BOOST_AUTO_TEST_SUITE_END() // test suite test_utilities
