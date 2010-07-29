#include "../group_elem.h"


#include "boost/test/included/unit_test.hpp"

using namespace boost::unit_test;


void test_trivial()
{
}

void test_order_power()
{
}


void test_properties()
{
}



test_suite* init_unit_test_suite( int argc, char* argv[] ) 
{
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_trivial ) );
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_order_power ) );
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_properties ) );

    return 0;
};
