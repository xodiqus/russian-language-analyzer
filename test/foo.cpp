
#include "foo.hpp"

#include "module.hpp"

BOOST_AUTO_TEST_SUITE(test_foo);

BOOST_AUTO_TEST_CASE(f_1)
{
    BOOST_CHECK_EQUAL(int(f(1)), 0);
} 

BOOST_AUTO_TEST_SUITE_END();