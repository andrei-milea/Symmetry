
#include "../lib/std_ex.h"

//allow to test private methods
#define private public
#define protected public

#include "../lib/group.h"

#define BOOST_TEST_MODULE "test_symmetric"
#include "boost/test/included/unit_test.hpp"

using namespace boost::unit_test;

//BOOST_TEST_MESSAGE( "cyc_grp:" << cyc_grp[0]<<"\n" << cyc_grp[1]<<"\n");

BOOST_AUTO_TEST_CASE(test_trivial)
{

	//test constructors

	//build the group
	cPermElem s1(3, {1,2});
	cPermElem s2(3, {2,3});
	cGroupElem< cPermElem, Multiplication> elem1(s1);
	cGroupElem< cPermElem, Multiplication> elem2(s2);
	std::vector< cGroupElem<cPermElem, Multiplication> >  generators;
	generators.push_back(elem1);
	generators.push_back(elem2);
	S3 g1(generators);

	S3 g2;
	g2.SetGeneratorsSet(generators);

	BOOST_CHECK(g1 == g2);


	//test copy and assignment
	S3 g3(g2);
	S3 g4 = g1;

	BOOST_CHECK(g3 == g4);
	BOOST_CHECK(g4 == g2);

}

BOOST_AUTO_TEST_CASE(test_private)
{
	/*****************************************
	 * tests for S3
	*****************************************/

/////////test get_cyclic_group//////////

	cPermElem s1(3, {1,2});
	cPermElem s2(3, {2,3});
	cGroupElem< cPermElem, Multiplication> elem1(s1);
	cGroupElem< cPermElem, Multiplication> elem2(s2);
	std::vector< cGroupElem<cPermElem, Multiplication> >  generators;
	generators.push_back(elem1);
	generators.push_back(elem2);
	S3 g1(generators);
	std::vector< cGroupElem<cPermElem, Multiplication> > cyc_grp;

	//test for identity
	cyc_grp.push_back(g1.GetIdentity());
	BOOST_CHECK(cyc_grp == g1.GetCyclicSubgroup(g1.GetIdentity()));

	//test for elem1
	cyc_grp.clear();
	cyc_grp.push_back(g1.GetIdentity());
	cyc_grp.push_back(elem1);

	BOOST_CHECK(cyc_grp == g1.GetCyclicSubgroup(elem1));

	//test for elem2
	cyc_grp.clear();
	cyc_grp.push_back(g1.GetIdentity());
	cyc_grp.push_back(elem2);
	BOOST_CHECK(cyc_grp == g1.GetCyclicSubgroup(elem2));

	//test for elem3
	cPermElem s3(3, {1,3,2});
	cPermElem s4(3, {1,2,3});
	cGroupElem< cPermElem, Multiplication> elem3(s3);
	cGroupElem< cPermElem, Multiplication> elem4(s4);
	cyc_grp.clear();
	cyc_grp.push_back(g1.GetIdentity());
	cyc_grp.push_back(elem3);
	cyc_grp.push_back(elem4);
	BOOST_CHECK(cyc_grp == g1.GetCyclicSubgroup(elem3));

	//test for elem4
	cyc_grp.clear();
	cyc_grp.push_back(g1.GetIdentity());
	cyc_grp.push_back(elem4);
	cyc_grp.push_back(elem3);
	BOOST_CHECK(cyc_grp == g1.GetCyclicSubgroup(elem4));

///////////////////////////////////////


	/*****************************************
	 * tests for D8
	*****************************************/

	//test get cyclic subgroup
	cGroupElem<cPermElem, Multiplication> elt1(4);
	cGroupElem<cPermElem, Multiplication> elt2( {4,1,2,3});
	cGroupElem<cPermElem, Multiplication> elt3( {3,4,1,2});
	cGroupElem<cPermElem, Multiplication> elt4( {2,3,4,1});

	std::vector<cGroupElem<cPermElem, Multiplication> > cyc_grp__;
	cyc_grp__.push_back(elt1);
	cyc_grp__.push_back(elt2);
	cyc_grp__.push_back(elt3);
	cyc_grp__.push_back(elt4);

	cGroup<cGroupElem<cPermElem, Multiplication>, cSymmetricRep >  cyc_grp_;
	cyc_grp_.AddGenerator(elt1);
	BOOST_CHECK(std_ex::set_equality(cyc_grp_.GetCyclicSubgroup(elt2), cyc_grp__));

///////////////////////////////////////
}


BOOST_AUTO_TEST_CASE(test_elements)
{

	/*****************************************
	 * tests for S3
	*****************************************/

	//test get elements naive
	cPermElem s1(3, {1,2});
	cPermElem s2(3, {2,3});
	cGroupElem< cPermElem, Multiplication> elem1(s1);
	cGroupElem< cPermElem, Multiplication> elem2(s2);
	std::vector< cGroupElem<cPermElem, Multiplication> >  generators;
	generators.push_back(elem1);
	generators.push_back(elem2);
	S3 g1(generators);
	std::vector< cGroupElem<cPermElem, Multiplication> > elements = g1.GetElementsNaive();

	//test get elements dimino
	std::vector< cGroupElem<cPermElem, Multiplication> > elementsD = g1.GetElementsDimino();
	BOOST_ASSERT(std_ex::set_equality(elements, elementsD));

	cPermElem s3(3, {1,2});
	cPermElem s4(3, {1,2,3});
	cGroupElem< cPermElem, Multiplication> elem3(s3);
	cGroupElem< cPermElem, Multiplication> elem4(s4);
	std::vector< cGroupElem<cPermElem, Multiplication> >  generators1;
	generators1.push_back(elem3);
	generators1.push_back(elem4);
	S3 g2(generators1);
	std::vector< cGroupElem<cPermElem, Multiplication> > elements1 = g2.GetElementsNaive();
	std::vector< cGroupElem<cPermElem, Multiplication> > elements1D = g2.GetElementsDimino();

	BOOST_ASSERT(std_ex::set_equality(elements, elements1));
	BOOST_ASSERT(std_ex::set_equality(elements, elements1D));

	cPermElem s5(3, {1,2,3});
	cGroupElem< cPermElem, Multiplication> elem5(s5);
	generators.clear();
	generators.push_back(elem5);
	S3 g5(generators);
	std::vector< cGroupElem<cPermElem, Multiplication> > elements5 = g5.GetElementsDimino();
	std::vector< cGroupElem<cPermElem, Multiplication> > elements5_check;
	elements5_check.push_back(g1.GetIdentity());
	elements5_check.push_back(elem5);
	cPermElem s6(3, {1,3,2});
	cGroupElem< cPermElem, Multiplication> elem6(s6);
	elements5_check.push_back(elem6);

	BOOST_ASSERT(std_ex::set_equality(elements5, elements5_check));


	/*****************************************
	 * tests for D8
	*****************************************/

	cGroupElem<cPermElem, Multiplication> elt2( {4,1,2,3});
	cGroupElem<cPermElem, Multiplication> elt5( {1,4,3,2});
	cGroup<cGroupElem<cPermElem, Multiplication>, cSymmetricRep> D8;
	D8.AddGenerator(elt2);

	BOOST_CHECK(std_ex::set_equality(D8.GetElementsDimino(), D8.GetElementsNaive()));

	D8.AddGenerator(elt5);

	BOOST_CHECK(std_ex::set_equality(D8.GetElementsDimino(), D8.GetElementsNaive()));
}

BOOST_AUTO_TEST_CASE(test_getorbit)
{
	/*****************************************
	 * tests o S3
	*****************************************/

	cPermElem s3(3, {1,2});
	cPermElem s4(3, {1,2,3});
	cGroupElem< cPermElem, Multiplication> elem3(s3);
	cGroupElem< cPermElem, Multiplication> elem4(s4);
	std::vector< cGroupElem<cPermElem, Multiplication> >  generators1;
	generators1.push_back(elem3);
	generators1.push_back(elem4);
	S3 g2(generators1);
	std::vector<std::size_t> orbit1 = g2.GetOrbit(1);
	std::vector<std::size_t> orbit2 = g2.GetOrbit(2);
	BOOST_CHECK(std_ex::set_equality(orbit1, orbit2));

	/*****************************************
	 * tests on D8
	*****************************************/

	cGroupElem<cPermElem, Multiplication> elt2( {4,1,2,3});
	cGroupElem<cPermElem, Multiplication> elt5( {1,4,3,2});
	cGroup<cGroupElem<cPermElem, Multiplication>, cSymmetricRep> D8;
	D8.AddGenerator(elt2);
	D8.AddGenerator(elt5);

	std::vector<std::size_t> orbit = {1,2,3,4};

	BOOST_CHECK(std_ex::set_equality(orbit, D8.GetOrbit(1)));

	BOOST_CHECK(std_ex::set_equality(orbit, D8.GetOrbit(2)));

};

