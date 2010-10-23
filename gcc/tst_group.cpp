#include "group.h"
#include "intmodn.h"
#include "permutation.h"
#include "std_ex.h"
#include "group_lattice.h"

#include <vector>
#include <iostream>

int main()
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

	std_ex::print_vector(normalizer_el);

	return 0;	
};

