#include "group.h"
#include "intmodn.h"
#include "permutation.h"
#include "std_ex.h"
#include "group_lattice.h"
#include "cayley_graph.h"

#include <vector>
#include <iostream>

int main()
{

//	cPermElem s1(3,{1,2});
//	cPermElem s2(3,{2,3});
//	cGroupElem< cPermElem, Multiplication> elem1(s1);
//	cGroupElem< cPermElem, Multiplication> elem2(s2);
//	std::vector< cGroupElem<cPermElem, Multiplication> >  generators;
//	generators.push_back(elem1);
//	generators.push_back(elem2);
//	S3 g1(generators);
//
//	cGrpLattice<S3> s3_lattice(g1);
//	s3_lattice.CyclicExtensionMethod();
//	std::cout<<s3_lattice;


//	cGroupElem<cPermElem, Multiplication> elt2({4,1,2,3});
//	cGroupElem<cPermElem, Multiplication> elt5({1,4,3,2});
//	cGroup<cGroupElem<cPermElem, Multiplication>, cSymmetricRep> D8;
//	D8.AddGenerator(elt2);
//	D8.AddGenerator(elt5);
//
//	cGrpLattice<cGroup<cGroupElem<cPermElem,Multiplication>, cSymmetricRep> > D8_lat(D8);
//	D8_lat.CyclicExtensionMethod();
//	std::cout<<D8_lat;

	cGroupElem<cPermElem, Multiplication> elt2({4,1,2,3});
	cGroupElem<cPermElem, Multiplication> elt5({1,4,3,2});
	cGroup<cGroupElem<cPermElem, Multiplication>, cSymmetricRep> D8;
	D8.AddGenerator(elt2);
	D8.AddGenerator(elt5);

	cCayleyGrf<cGroup<cGroupElem<cPermElem, Multiplication>, cSymmetricRep> > graph(D8);
	graph.BuildGraph();

	return 0;	
};

