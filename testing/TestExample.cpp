// Compile with g++ -otest -lboost_unit_test_framework TestExample.cpp
//#include "Hint.cpp"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestExample
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( test1 )
{

    BOOST_CHECK( 2==2 );
}

//EOF
