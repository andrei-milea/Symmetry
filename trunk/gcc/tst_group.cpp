#include "group.h"
#include "intmodn.h"
#include "permutation.h"
#include "std_ex.h"
#include "group_lattice.h"

#include <vector>
#include <iostream>

int main()
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
	std::cout<<"sizeof"<<sizeof(elem_a1);

//	cGroupElem< cPermElem, Multiplication> elem_a2(a2);
//	std::vector< cGroupElem< cPermElem, Multiplication> > a3_el;
//
//	a3_el.push_back(g1.GetIdentity());
//	a3_el.push_back(elem_a1);
//	a3_el.push_back(elem_a2);
//	S3 a3(a3_el);
//	cSubgroup<S3> A3(a3_el);
//	normalizer_el = g1.GetNormalizerEl(A3);
//
//	std_ex::print_vector(normalizer_el);

//	//?????? -- not sure
//	generators.clear();
//	generators.push_back(g1.GetIdentity());
//	if(!std_ex::set_equality(normalizer_el, generators));
//	std::cout<<"error\n";

//	std::vector< cGroupElem< cPermElem, Multiplication> > iden_el;
//	iden_el.push_back(g1.GetIdentity());
//	cSubgroup<S3> iden(iden_el);
//	S3 g2(g1.GetNormalizer(iden));
//	BOOST_CHECK(std_ex::set_equality(g1.GetElementsDimino(), g2.GetElementsDimino()));

	return 0;	
};

