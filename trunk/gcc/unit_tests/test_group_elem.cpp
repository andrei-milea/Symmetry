#include "../lib/group.h"

#define BOOST_TEST_MODULE "test_group_el"
#include "boost/test/included/unit_test.hpp"

using namespace boost::unit_test;


BOOST_AUTO_TEST_CASE(test_trivial)
{
	//test perm element
	cPermElem s1(3);
	cPermElem s2(3, {2,3});
	cPermElem s3(3, {1,2});
	cGroupElem< cPermElem, Multiplication> elem1(s1);
	cGroupElem< cPermElem, Multiplication> elem2(s2);
	cGroupElem< cPermElem, Multiplication> elem3(s3);
	BOOST_CHECK(elem2 * elem2 == elem1);
	BOOST_CHECK(elem1 == elem3 * elem3);

	//test copy constructor and assignment operator
	cGroupElem< cPermElem, Multiplication> elem4(elem1);
	cGroupElem< cPermElem, Multiplication> elem5 = elem2;
	BOOST_CHECK(elem5 * elem5 == elem4);
}

BOOST_AUTO_TEST_CASE(test_order_power)
{
	/*****************************************
	 * tests for S3
	*****************************************/

	cPermElem s1(3);
	cPermElem s2(3, {2,3});
	cPermElem s3(3, {1,2});
	cPermElem s4(3, {3,2});
	cGroupElem< cPermElem, Multiplication> elem1(s1);
	cGroupElem< cPermElem, Multiplication> elem2(s2);
	cGroupElem< cPermElem, Multiplication> elem3(s3);
	cGroupElem< cPermElem, Multiplication> elem4(s4);

	//test perm elem power
	BOOST_CHECK(elem1.GetNthPower(2) == elem1);
	BOOST_CHECK(elem2.GetNthPower(2) == elem1);
	BOOST_CHECK(elem2.GetNthPower(3) == elem2);
	BOOST_CHECK(elem3.GetNthPower(3) == elem3);
	BOOST_CHECK(elem1.GetNthPower(4) == elem1);

	//test order
	BOOST_CHECK(elem2.GetOrder() == 2);
	BOOST_CHECK(elem2.GetOrder() == elem3.GetOrder());
	BOOST_CHECK(elem1.GetOrder() == 1);
	BOOST_CHECK(elem2.GetOrder(6)
	            == elem2.GetOrder());


	//test inverse
	BOOST_CHECK(elem1.GetInverse() == elem1);
	BOOST_CHECK(elem2.GetInverse() == elem4);

	/*****************************************
	 * tests for D8
	*****************************************/

	cGroupElem<cPermElem, Multiplication> elt1(4);
	cGroupElem<cPermElem, Multiplication> elt2( {4,1,2,3});
	cGroupElem<cPermElem, Multiplication> elt3( {3,4,1,2});
	cGroupElem<cPermElem, Multiplication> elt4( {2,3,4,1});

	//test getnthpower
	BOOST_CHECK(elt2.GetNthPower(2) == elt3);
	BOOST_CHECK(elt2.GetNthPower(3) == elt4);

	//test getorder
	BOOST_CHECK(elt2.GetOrder() == 4);
	BOOST_CHECK(elt3.GetOrder() == 2);
	BOOST_CHECK(elt2.GetOrder() == elt2.GetOrder(8));

	//test getinverse
	BOOST_CHECK(elt3.GetInverse() == elt3);

}


BOOST_AUTO_TEST_CASE(test_properties)
{
	/*****************************************
	 * tests for S3
	*****************************************/

	//test commutes with
	cPermElem s1(3);
	cPermElem s2(3, {2,3});
	cPermElem s3(3, {1,2});
	cGroupElem< cPermElem, Multiplication> elem1(s1);
	cGroupElem< cPermElem, Multiplication> elem2(s2);
	cGroupElem< cPermElem, Multiplication> elem3(s3);
	BOOST_CHECK(elem1.CommutesWith(elem1));
	BOOST_CHECK(elem1.CommutesWith(elem2));
	BOOST_CHECK(elem1.CommutesWith(elem3));
	BOOST_CHECK(!elem2.CommutesWith(elem3));
	BOOST_CHECK(!elem3.CommutesWith(elem2));

	//test is normalizer
	std::vector<cGroupElem< cPermElem, Multiplication> > elements;
	elements.push_back(elem1);
	elements.push_back(elem2);
	elements.push_back(elem3);
	BOOST_CHECK(elem1.IsNormalizer(elements));


	/*****************************************
	 * tests for D8
	*****************************************/

	cGroupElem<cPermElem, Multiplication> elt1(4);
	cGroupElem<cPermElem, Multiplication> elt2( {4,1,2,3});
	cGroupElem<cPermElem, Multiplication> elt3( {3,4,1,2});
	cGroupElem<cPermElem, Multiplication> elt4( {2,3,4,1});

	std::vector< cGroupElem<cPermElem, Multiplication> > elem;
	elem.push_back(elt1);
	elem.push_back(elt2);
	elem.push_back(elt3);

	//test commutes with
	BOOST_CHECK(elt1.CommutesWith(elt2));
	BOOST_CHECK(elt1.CommutesWith(elt3));
	BOOST_CHECK(elt1.CommutesWith(elt4));
	BOOST_CHECK(elt3.CommutesWith(elt3));
	BOOST_CHECK(elt2.CommutesWith(elt3));

	//test is normalizer
	BOOST_CHECK(elt1.IsNormalizer(elem));
	BOOST_CHECK(elt2.IsNormalizer(elem));
}


