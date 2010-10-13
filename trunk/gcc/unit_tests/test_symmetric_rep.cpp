
#include "../group.h"
#include "boost/test/included/unit_test.hpp"
#include "../std_ex.h"

using namespace boost::unit_test;


	//BOOST_TEST_MESSAGE( "cyc_grp:" << cyc_grp[0]<<"\n" << cyc_grp[1]<<"\n");
	
void test_s3_trivial()
{

	//test constructors
	
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

	S3 g2;
	g2.SetGeneratorsSet(generators);

	BOOST_CHECK(g1 == g2);


	//test copy and assignment
	S3 g3(g2);
	S3 g4 = g1;

	BOOST_CHECK(g3 == g4);
	BOOST_CHECK(g4 == g2);

}

void test_s3_private()
{
	//REMEMBER: make methods public first
	
/////////test get_cyclic_group//////////
	
	cPermElem<3> s1({1,2});
	cPermElem<3> s2({2,3});
	cGroupElem< cPermElem<3>, Multiplication> elem1(s1);
	cGroupElem< cPermElem<3>, Multiplication> elem2(s2);
	std::vector< cGroupElem<cPermElem<3>, Multiplication> >  generators;
	generators.push_back(elem1);
	generators.push_back(elem2);
	S3 g1(generators);
	std::vector< cGroupElem<cPermElem<3>, Multiplication> > cyc_grp;

	//test for identity
	cyc_grp.push_back(g1.GetIdentity());
	BOOST_CHECK(cyc_grp == g1.GetCyclicGroup(g1.GetIdentity()));

	//test for elem1
	cyc_grp.clear();
	cyc_grp.push_back(g1.GetIdentity());
	cyc_grp.push_back(elem1);

	BOOST_CHECK(cyc_grp == g1.GetCyclicGroup(elem1));

	//test for elem2
	cyc_grp.clear();
	cyc_grp.push_back(g1.GetIdentity());
	cyc_grp.push_back(elem2);
	BOOST_CHECK(cyc_grp == g1.GetCyclicGroup(elem2));

	//test for elem3
	cPermElem<3> s3({1,3,2});
	cPermElem<3> s4({1,2,3});
	cGroupElem< cPermElem<3>, Multiplication> elem3(s3);
	cGroupElem< cPermElem<3>, Multiplication> elem4(s4);
	cyc_grp.clear();
	cyc_grp.push_back(g1.GetIdentity());
	cyc_grp.push_back(elem3);
	cyc_grp.push_back(elem4);
	BOOST_CHECK(cyc_grp == g1.GetCyclicGroup(elem3));

	//test for elem4
	cyc_grp.clear();
	cyc_grp.push_back(g1.GetIdentity());
	cyc_grp.push_back(elem4);
	cyc_grp.push_back(elem3);
	BOOST_CHECK(cyc_grp == g1.GetCyclicGroup(elem4));

///////////////////////////////////////

/////////////test add_coset//////////////
	g1.AddCoset(cyc_grp, elem2);
	std::vector< cGroupElem<cPermElem<3>, Multiplication> > tst_vec;
	tst_vec.push_back(g1.GetIdentity());
	tst_vec.push_back(elem4);
	tst_vec.push_back(elem3);
	tst_vec.push_back(elem2);
	tst_vec.push_back(elem2 * elem4);
	tst_vec.push_back(elem2 * elem3);
	BOOST_CHECK(cyc_grp == tst_vec);


///////////////////////////////////////

}


void test_s3_elements()
{

	//test get elements naive
	cPermElem<3> s1({1,2});
	cPermElem<3> s2({2,3});
	cGroupElem< cPermElem<3>, Multiplication> elem1(s1);
	cGroupElem< cPermElem<3>, Multiplication> elem2(s2);
	std::vector< cGroupElem<cPermElem<3>, Multiplication> >  generators;
	generators.push_back(elem1);
	generators.push_back(elem2);
	S3 g1(generators);
	std::vector< cGroupElem<cPermElem<3>, Multiplication> > elements = g1.GetElementsNaive();

	//test get elements dimino
	std::vector< cGroupElem<cPermElem<3>, Multiplication> > elementsD = g1.GetElementsDimino();
	BOOST_ASSERT(std_ex::set_equality(elements, elementsD));

	cPermElem<3> s3({1,2});
	cPermElem<3> s4({1,2,3});
	cGroupElem< cPermElem<3>, Multiplication> elem3(s3);
	cGroupElem< cPermElem<3>, Multiplication> elem4(s4);
	std::vector< cGroupElem<cPermElem<3>, Multiplication> >  generators1;
	generators1.push_back(elem3);
	generators1.push_back(elem4);
	S3 g2(generators1);
	std::vector< cGroupElem<cPermElem<3>, Multiplication> > elements1 = g2.GetElementsNaive();
	std::vector< cGroupElem<cPermElem<3>, Multiplication> > elements1D = g2.GetElementsDimino();

	BOOST_ASSERT(std_ex::set_equality(elements, elements1));
	BOOST_ASSERT(std_ex::set_equality(elements, elements1D));
}

void test_s3_getorbit()
{
	cPermElem<3> s3({1,2});
	cPermElem<3> s4({1,2,3});
	cGroupElem< cPermElem<3>, Multiplication> elem3(s3);
	cGroupElem< cPermElem<3>, Multiplication> elem4(s4);
	std::vector< cGroupElem<cPermElem<3>, Multiplication> >  generators1;
	generators1.push_back(elem3);
	generators1.push_back(elem4);
	S3 g2(generators1);
	std::vector<std::size_t> orbit1 = g2.GetOrbit(1);
	std::vector<std::size_t> orbit2 = g2.GetOrbit(2);
	std_ex::cout<<orbit1;
	std_ex::cout<<orbit2;
};


test_suite* init_unit_test_suite( int argc, char* argv[] ) 
{
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_s3_trivial ) );
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_s3_private ) );
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_s3_elements ) );
	return 0;
}; 
