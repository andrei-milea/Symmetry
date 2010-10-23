#include "../group.h"
#include "../std_ex.h"
#include "../group_lattice.h"

#include "boost/test/included/unit_test.hpp"

using namespace boost::unit_test;


void test_s3_lattice()
{
	cPermElem<3> s1({1,2});
	cPermElem<3> s2({2,3});
	cGroupElem< cPermElem<3>, Multiplication> elem1(s1);
	cGroupElem< cPermElem<3>, Multiplication> elem2(s2);
	std::vector< cGroupElem<cPermElem<3>, Multiplication> >  generators;
	generators.push_back(elem1);
	generators.push_back(elem2);
	S3 g1(generators);

	cGrpLattice<S3> s3_lattice(g1);


};

test_suite* init_unit_test_suite( int argc, char* argv[] ) 
{
    framework::master_test_suite().add( BOOST_TEST_CASE( &test_s3_lattice ) );
	return 0;
}; 


