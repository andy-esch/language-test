// Compile with g++ -otest -lboost_unit_test_framework TestExample.cpp -L/opt/local/lib -I/opt/local/include
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hint test
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE( test1 )
{
    BOOST_CHECK( 2==2 );
}

BOOST_AUTO_TEST_CASE( test2 )
{
    BOOST_CHECK( 3==1 );
}

//EOF
