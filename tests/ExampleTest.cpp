#include "lavaTests.h"
//#include <lava/lava.h>

double sqr(double x) { return x*x; }

BOOST_AUTO_TEST_CASE(FailTest)
{
    BOOST_CHECK_EQUAL(9, sqr(3));
}

BOOST_AUTO_TEST_CASE(PassTest)
{
    BOOST_CHECK_EQUAL(4, sqr(2));
}