#include "../group.h"
#include "../std_ex.h"

#include "boost/test/included/unit_test.hpp"

using namespace boost::unit_test;

void test_s3_centralizer_el()
{
	cPermElem s1(3,{1,2});
	cPermElem s2(3,{2,3});
	cPermElem s3(3,{1,2,3});
	cPermElem s4(3,{1});
	cPermElem s5(3,{1,3,2});
	cGroupElem< cPermElem, Multiplication> elem1(s1);
	cGroupElem< cPermElem, Multiplication> elem2(s2);
	cGroupElem< cPermElem, Multiplication> elem3(s3);
	cGroupElem< cPermElem, Multiplication> elem4(s4);
	cGroupElem< cPermElem, Multiplication> elem5(s5);
	std::vector< cGroupElem<cPermElem, Multiplication> >  generators;
	std::vector< cGroupElem<cPermElem, Multiplication> >  res;
	generators.push_back(elem1);
	generators.push_back(elem2);
	S3 g1(generators);
	std::vector< cGroupElem< cPermElem, Multiplication> > centralizer_el;
   	centralizer_el = g1.GetCentralizerEl(elem3);
	res.push_back(elem4);
	res.push_back(elem3);
	res.push_back(elem5);
	BOOST_CHECK(std_ex::set_equality(centralizer_el, res));
};

void test_s3_center_el()
{
	cPermElem s1(3,{1,2});
	cPermElem s2(3,{2,3});
	cGroupElem< cPermElem, Multiplication> elem1(s1);
	cGroupElem< cPermElem, Multiplication> elem2(s2);
	std::vector< cGroupElem<cPermElem, Multiplication> >  generators;
	generators.push_back(elem1);
	generators.push_back(elem2);
	S3 g1(generators);

	std::vector< cGroupElem< cPermElem, Multiplication> > center_el;
	center_el = g1.GetCenterEl();
	std::vector< cGroupElem<cPermElem, Multiplication> >  center_el1;
	center_el1.push_back(g1.GetIdentity());
	BOOST_CHECK(std_ex::set_equality(center_el, center_el1));
};

void test_s3_normalizer_el()
{

	cPermElem s1(3,{1,2});
	cPermElem s2(3,{2,3});
	cGroupElem< cPermElem, Multiplication> elem1(s1);
	cGroupElem< cPermElem, Multiplication> elem2(s2);
	std::vector< cGroupElem<cPermElem, Multiplication> >  generators;
	generators.push_back(elem1);
	generators.push_back(elem2);
	S3 g1(generators);

	std::vector< cGroupElem< cPermElem, Multiplication> > normalizer_el;

	cPermElem a1(3,{1,2,3});
	cPermElem a2(3,{1,3,2});
	cGroupElem< cPermElem, Multiplication> elem_a1(a1);
	cGroupElem< cPermElem, Multiplication> elem_a2(a2);
	std::vector< cGroupElem< cPermElem, Multiplication> > a3_el;

	a3_el.push_back(g1.GetIdentity());
	a3_el.push_back(elem_a1);
	a3_el.push_back(elem_a2);
	S3 a3(a3_el);
	cSubgroup<S3> A3(a3_el);
	normalizer_el = g1.GetNormalizerEl(A3);

	BOOST_CHECK(std_ex::set_equality(normalizer_el, g1.GetElementsDimino()));

	std::vector< cGroupElem< cPermElem, Multiplication> > iden_el;
	iden_el.push_back(g1.GetIdentity());
	cSubgroup<S3> iden(iden_el);
	S3 g2(g1.GetNormalizer(iden));
	BOOST_CHECK(std_ex::set_equality(g1.GetElementsDimino(), g2.GetElementsDimino()));
};


test_suite* init_unit_test_suite( int argc, char* argv[] ) 
{
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_s3_centralizer_el ) );
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_s3_center_el ) );
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_s3_normalizer_el ) );
	return 0;
}; 

