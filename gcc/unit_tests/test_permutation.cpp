

#include "../lib/permutation.h"



#include "boost/random.hpp"

#define BOOST_TEST_MODULE "test_permutation"
#include "boost/test/included/unit_test.hpp"

using namespace boost::unit_test;

//test perm 3 identity
BOOST_AUTO_TEST_CASE(test_perm_unity)
{
	//test default constructor
	cPermElem perm1(3);
	cPermElem perm2(3);
	cPermElem perm3 = perm1 * perm2;
	BOOST_CHECK(perm3 == (perm1 * perm2));
}

BOOST_AUTO_TEST_CASE(test_perm_multiplication)
{
	cPermElem perm1(3);
	cPermElem perm2(3, {1, 3, 2});
	cPermElem perm3(3, {3, 2, 1});
	//test commmutatitivity
	BOOST_CHECK(perm1 * perm2 == perm2 * perm1);
	BOOST_CHECK(perm2 * perm3 == perm3 * perm2);
	//test associativity
	BOOST_CHECK((perm1 * perm2) * perm3 == perm1 * (perm2 * perm3));
	//test actual operation-- hardcoded result
	BOOST_CHECK(perm1 * perm3 == cPermElem(3, {1, 3, 2}));
	BOOST_CHECK(perm1 * perm1 * perm1 == perm1);
	BOOST_CHECK(perm1 * perm2 * perm3 == perm2 * perm1 * perm3);


	//test multiplication for elements of S4(D8)
	cPermElem elt1(4);
	cPermElem elt2(4, {1,4,3,2});
	cPermElem elt3(4, {1,3});
	elt3 = elt3 * cPermElem(4, {2,4});
	cPermElem elt4(4, {1,2,3,4});
	cPermElem elt5( {1,4,3,2});
	cPermElem elt6( {2,1,4,3});
	BOOST_CHECK(elt3 == elt2 * elt2);
	BOOST_CHECK(elt4 == elt2 * elt2 * elt2);
	BOOST_CHECK(elt2 * elt5 == elt6);
}


BOOST_AUTO_TEST_CASE(test_perm_trivial)
{
	//test constructors
	std::vector<std::size_t> perm_array(3);
	perm_array[0] = 1;
	perm_array[1] = 2;
	perm_array[2] = 3;

	cPermElem perm1(3);
	cPermElem perm2(3, {1,3,2});
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
	BOOST_CHECK(perm4.GetIdentity(1) == perm1);
}

BOOST_AUTO_TEST_CASE(test_perm_inversions)
{
	cPermElem perm1( {2, 3, 8, 6, 1});
	BOOST_CHECK(perm1.GetInversions() == 5);
}


