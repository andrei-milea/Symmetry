

#include "../permutation.h"



//include boost test framework
//#define BOOST_TEST_MODULE PermTest
#include "boost/test/included/unit_test.hpp"
#include "boost/random.hpp"

using namespace boost::unit_test;

//test perm 3 identity
void test_perm_unity()
{
	//test default constructor
	cPermElem perm1(3);
	cPermElem perm2(3);
	cPermElem perm3 = perm1 * perm2;
	BOOST_CHECK(perm3 == (perm1 * perm2));
}

void test_perm_multiplication()
{
    cPermElem perm1(3);
    cPermElem perm2(3,{1, 3, 2});
    cPermElem perm3(3,{3, 2, 1});
    //test commmutatitivity
    BOOST_CHECK(perm1 * perm2 == perm2 * perm1);
    BOOST_CHECK(perm2 * perm3 == perm3 * perm2);
    //test associativity
    BOOST_CHECK((perm1 * perm2) * perm3 == perm1 * (perm2 * perm3));
    //test actual operation-- hardcoded result
    BOOST_CHECK(perm1 * perm3 == cPermElem(3,{1, 3, 2}));
    BOOST_CHECK(perm1 * perm1 * perm1 == perm1);
    BOOST_CHECK(perm1 * perm2 * perm3 == perm2 * perm1 * perm3);
}


void test_perm_trivial()
{
    //test constructors
    std::vector<std::size_t> perm_array(3);
    perm_array[0] = 1;
    perm_array[1] = 2;
    perm_array[2] = 3;

    cPermElem perm1(3);
    cPermElem perm2(3,{1,3,2});
    cPermElem perm3(perm_array);
    perm_array[0] = 3;
    perm_array[1] = 1;
    perm_array[2] = 2;
    cPermElem perm4(perm_array);

    BOOST_CHECK(perm1 == perm3 && perm3 == perm1);
    BOOST_CHECK(perm4 == perm2);

    //test copy constructor and assignment operator
    cPermElem perm5 = perm1;
    cPermElem perm6(perm1);
    BOOST_CHECK(perm5 == perm6);
    BOOST_CHECK(perm5 == perm1);
    BOOST_CHECK(perm6 == perm1);
    
	//test get identity
    BOOST_CHECK(perm4.GetIdentity() == perm1);
}




test_suite* init_unit_test_suite( int argc, char* argv[] ) 
{
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_perm_unity ) );
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_perm_multiplication ) );
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_perm_trivial ) );

    return 0;
};

