#include "../group.h"
#include "../std_ex.h"

#include "boost/test/included/unit_test.hpp"

using namespace boost::unit_test;

void test_s3_centralizer_el()
{
	cPermElem<3> s1({1,2});
	cPermElem<3> s2({2,3});
	cPermElem<3> s3({1,2,3});
	cPermElem<3> s4({1});
	cPermElem<3> s5({1,3,2});
	cGroupElem< cPermElem<3>, Multiplication> elem1(s1);
	cGroupElem< cPermElem<3>, Multiplication> elem2(s2);
	cGroupElem< cPermElem<3>, Multiplication> elem3(s3);
	cGroupElem< cPermElem<3>, Multiplication> elem4(s4);
	cGroupElem< cPermElem<3>, Multiplication> elem5(s5);
	std::vector< cGroupElem<cPermElem<3>, Multiplication> >  generators;
	std::vector< cGroupElem<cPermElem<3>, Multiplication> >  res;
	generators.push_back(elem1);
	generators.push_back(elem2);
	S3 g1(generators);
	std::vector< cGroupElem< cPermElem<3>, Multiplication> > centralizer_el;
   	centralizer_el = g1.GetCentralizerEl(elem3);
	res.push_back(elem4);
	res.push_back(elem3);
	res.push_back(elem5);
	BOOST_CHECK(std_ex::set_equality(centralizer_el, res));
};

void test_s3_center_el()
{
	cPermElem<3> s1({1,2});
	cPermElem<3> s2({2,3});
	cGroupElem< cPermElem<3>, Multiplication> elem1(s1);
	cGroupElem< cPermElem<3>, Multiplication> elem2(s2);
	std::vector< cGroupElem<cPermElem<3>, Multiplication> >  generators;
	generators.push_back(elem1);
	generators.push_back(elem2);
	S3 g1(generators);

	std::vector< cGroupElem< cPermElem<3>, Multiplication> > center_el;
	center_el = g1.GetCenterEl();
	std::vector< cGroupElem<cPermElem<3>, Multiplication> >  center_el1;
	center_el1.push_back(g1.GetIdentity());
	BOOST_CHECK(std_ex::set_equality(center_el, center_el1));
};

void test_s3_normalizer_el()
{

	cPermElem<3> s1({1,2});
	cPermElem<3> s2({2,3});
	cGroupElem< cPermElem<3>, Multiplication> elem1(s1);
	cGroupElem< cPermElem<3>, Multiplication> elem2(s2);
	std::vector< cGroupElem<cPermElem<3>, Multiplication> >  generators;
	generators.push_back(elem1);
	generators.push_back(elem2);
	S3 g1(generators);

	std::vector< cGroupElem< cPermElem<3>, Multiplication> > normalizer_el;

	cPermElem<3> a1({1,2,3});
	cPermElem<3> a2({1,3,2});
	cGroupElem< cPermElem<3>, Multiplication> elem_a1(a1);
	cGroupElem< cPermElem<3>, Multiplication> elem_a2(a2);
	std::vector< cGroupElem< cPermElem<3>, Multiplication> > a3_el;

	a3_el.push_back(g1.GetIdentity());
	a3_el.push_back(elem_a1);
	a3_el.push_back(elem_a2);
	S3 a3(a3_el);
	cSubgroup<S3> A3(a3_el);
	normalizer_el = g1.GetNormalizerEl(A3);

	//?????? -- not sure
	generators.clear();
	generators.push_back(g1.GetIdentity());
	BOOST_CHECK(std_ex::set_equality(normalizer_el, generators));
};


test_suite* init_unit_test_suite( int argc, char* argv[] ) 
{
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_s3_centralizer_el ) );
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_s3_center_el ) );
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_s3_normalizer_el ) );
	return 0;
}; 

