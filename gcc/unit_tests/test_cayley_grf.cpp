
#include "../lib/std_ex.h"
#include "../lib/cayley_graph.h"
#define BOOST_TEST_MODULE "test_cayley_grf"

#include "boost/test/included/unit_test.hpp"

using namespace boost::unit_test;


BOOST_AUTO_TEST_CASE(test_cayley_grf)
{
	cGroupElem<cPermElem, Multiplication> elt2( {4,1,2,3});
	cGroupElem<cPermElem, Multiplication> elt5( {1,4,3,2});
	cGroup<cGroupElem<cPermElem, Multiplication>, cSymmetricRep> D8;
	D8.AddGenerator(elt2);
	D8.AddGenerator(elt5);

	cCayleyGrf<cGroup<cGroupElem<cPermElem, Multiplication>, cSymmetricRep> > graph(D8);
	graph.BuildGraph();
	BOOST_ASSERT(nullptr != graph.GetGraph());
	//std::cout<<graph;
}


