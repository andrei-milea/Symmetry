#include "../lib/group.h"
#include "../lib/std_ex.h"


#include "boost/test/included/unit_test.hpp"

//allow to test private/protected methods
#define private public
#define protected public

#include "../lib/group_lattice.h"


using namespace boost::unit_test;

void test_s3_lattice_has_prime_power_el()
{
	
	cPermElem s1(3,{1,2,3});
	cPermElem s2(3,{1,3,2});
	cGroupElem< cPermElem, Multiplication> elem1(s1);
	cGroupElem< cPermElem, Multiplication> elem2(s2);
	std::vector< cGroupElem<cPermElem, Multiplication> >  generators;
	generators.push_back(elem1.GetIdentity());
	generators.push_back(elem1);
	generators.push_back(elem2);

	S3 g1(generators);
	cGrpLattice<S3> s3_lattice(g1);
	cSubgroup<S3> a3(generators);

	BOOST_CHECK(true == s3_lattice.Has_prime_pow_el(a3, elem1));

};

void test_s3_lattice()
{

	cPermElem s1(3,{1,2});
	cPermElem s2(3,{2,3});
	cGroupElem< cPermElem, Multiplication> elem1(s1);
	cGroupElem< cPermElem, Multiplication> elem2(s2);
	std::vector< cGroupElem<cPermElem, Multiplication> >  generators;
	generators.push_back(elem1);
	generators.push_back(elem2);
	S3 g1(generators);

	cGrpLattice<S3> s3_lattice(g1);
	s3_lattice.CyclicExtensionMethod();


};

test_suite* init_unit_test_suite( int argc, char* argv[] ) 
{
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_s3_lattice_has_prime_power_el) );
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_s3_lattice ) );
	return 0;
}; 


