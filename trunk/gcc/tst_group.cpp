#include "group.h"
#include "intmodn.h"
#include "permutation.h"

#include <iostream>

int main()
{
	cPermElem<3> s1;
	cPermElem<3> s2({2,3});
	cPermElem<3> s3({1,2});
	cPermElem<3> s4({3,2});
	cGroupElem< cPermElem<3>, Multiplication> elem1(s1);
	cGroupElem< cPermElem<3>, Multiplication> elem2(s2);
	cGroupElem< cPermElem<3>, Multiplication> elem3(s3);
	cGroupElem< cPermElem<3>, Multiplication> elem4(s4);
	//std::cout<<elem2.GetInverse();
	//test is normalizer
	std::vector<cGroupElem< cPermElem<3>, Multiplication> > elements;
	elements.push_back(elem1);
	elements.push_back(elem2);
	elements.push_back(elem3);
	elem1.IsNormalizer(elements);
	return 0;	
};

