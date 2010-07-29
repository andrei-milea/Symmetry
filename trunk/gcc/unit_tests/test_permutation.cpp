

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
	cPermElem<3> perm1;
	cPermElem<3> perm2;
	cPermElem<3> perm3 = perm1 * perm2;
	BOOST_CHECK(perm3 == (perm1 * perm2));
}

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
    BOOST_CHECK(perm1 * perm1 * perm1 == perm1);
    BOOST_CHECK(perm1 * perm2 * perm3 == perm2 * perm1 * perm3);
}


void test_perm_trivial()
{
    //test constructors
    std::array<std::size_t, 4> perm_array;
    perm_array[0] = 0;
    perm_array[1] = 1;
    perm_array[2] = 2;
    perm_array[3] = 3;

    cPermElem<3> perm1;
    cPermElem<3> perm2({1,3,2});
    cPermElem<3> perm3(perm_array);
    perm_array[1] = 3;
    perm_array[2] = 1;
    perm_array[3] = 2;
    cPermElem<3> perm4(perm_array);

    BOOST_CHECK(perm1 == perm3 && perm3 == perm1);
    BOOST_CHECK(perm4 == perm2);

    //test copy constructor and assignment operator
    cPermElem<3> perm5 = perm1;
    cPermElem<3> perm6(perm1);
    BOOST_CHECK(perm5 == perm6 && perm5 == perm1 && perm6 == perm1);
    cPermElem<3> perm7 = perm2;
    cPermElem<3> perm8(perm2);
    BOOST_CHECK(perm7 == perm8);
	BOOST_CHECK(perm7 == perm2);
	BOOST_CHECK(perm8 == perm2);

    //test getter / setter
    BOOST_CHECK(perm4.GetPermutationArray() == perm_array);
    perm5.SetPermutationArray(perm_array);
    BOOST_CHECK(perm5 == perm4);

    //test get identity
    BOOST_CHECK(cPermElem<3>::GetIdentity() == perm1);
}

test_suite* init_unit_test_suite( int argc, char* argv[] ) 
{
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_perm_unity ) );
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_perm_multiplication ) );
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_perm_trivial ) );

    return 0;
};

