#include "group.h"

void test_s3_trivial()
{
	//build the group
	//use this construction to avoid g++ bug with 
	//initializer list
	cPermElem<3> s1({1,2});
	cPermElem<3> s2({2,3});
	cGroupElem< cPermElem<3>, Multiplication> elem1(s1);
	cGroupElem< cPermElem<3>, Multiplication> elem2(s2);
	std::vector< cGroupElem<cPermElem<3>, Multiplication> >  generators;
	generators.push_back(elem1);
	generators.push_back(elem2);
	S3 g1(generators);

}

void test_s3_order_power()
{
}


void test_s3_properties()
{
}



test_suite* init_unit_test_suite( int argc, char* argv[] ) 
{
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_s3_trivial ) );
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_s3_order_power ) );
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_s3_properties ) );

    return 0;
};


