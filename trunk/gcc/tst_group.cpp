#include "group.h"
#include "intmodn.h"
#include "permutation.h"
#include "std_ex.h"
#include "group_lattice.h"

#include <vector>
#include <iostream>

int main()
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

	std_ex::print_vector(elementsD);
//	cGrpLattice<S3> s3_lattice(g1);
//	s3_lattice.CyclicExtensionMethod();
//	std::cout<<s3_lattice;

	return 0;	

};

