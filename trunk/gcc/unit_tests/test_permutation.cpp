

#include "../permutation.h"


//include boost test framework
//#define BOOST_TEST_MODULE PermTest
#include "boost/test/included/unit_test.hpp"

using namespace boost::unit_test;

//test perm 3 unity
void test_perm_unity()
{
	//test default constructor
	cPermElem<3> perm1;
	cPermElem<3> perm2;
	cPermElem<3> perm3 = perm1 * perm2;
	BOOST_CHECK(perm3 == (perm1 * perm2));
}

//test multiplication
void test_perm_multiplication()
{
	cPermElem<3> perm1;
	cPermElem<3> perm2({1, 3, 2});
	cPermElem<3> perm3({3, 2, 1});
	//test commmutatitivity
	BOOST_CHECK(perm1 * perm2 == perm2 * perm1);
	BOOST_CHECK(perm2 * perm3 == perm3 * perm2);
	//test associativity
	BOOST_CHECK((perm1 * perm2) * perm3 == perm1 * (perm2 * perm3));
	//test actual operation-- hardcoded result
	BOOST_CHECK(perm1 * perm3 == cPermElem<3>({1, 3, 2}));
	
}

//test trivial class operations : constructors, copy and assign
void test_perm_trivial()
{
	cPermElem<3> perm1;
	cPermElem<3> perm2({1,3,2});

}

test_suite* init_unit_test_suite( int argc, char* argv[] ) 
{
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_perm_unity ) );
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_perm_multiplication ) );
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_perm_trivial ) );

    return 0;
};

