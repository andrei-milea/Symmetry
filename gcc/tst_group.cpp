#include "group.h"
#include "intmodn.h"
#include "permutation.h"

#include <iostream>

int main()
{

//	cPermElem<3> s1;
//	cPermElem<3> s2({2,3});
//	cPermElem<3> s3({1,2});
//	cPermElem<3> s4({3,2});
//	cGroupElem< cPermElem<3>, Multiplication> elem1(s1);
//	cGroupElem< cPermElem<3>, Multiplication> elem2(s2);
//	cGroupElem< cPermElem<3>, Multiplication> elem3(s3);
//	cGroupElem< cPermElem<3>, Multiplication> elem4(s4);
//	//std::cout<<elem2.GetInverse();
//	//test is normalizer
//	std::vector<cGroupElem< cPermElem<3>, Multiplication> > elements;
//	elements.push_back(elem1);
//	elements.push_back(elem2);
//	elements.push_back(elem3);
//	elem1.IsNormalizer(elements);

	//test get elements naive
	cPermElem<3> s1({1,2});
	cPermElem<3> s2({2,3});
	cGroupElem< cPermElem<3>, Multiplication> elem1(s1);
	cGroupElem< cPermElem<3>, Multiplication> elem2(s2);
	std::vector< cGroupElem<cPermElem<3>, Multiplication> >  generators;
	generators.push_back(elem1);
	generators.push_back(elem2);
	S3 g1(generators);

	std::vector< cGroupElem<cPermElem<3>, Multiplication> > elements = g1.GetElementstNaive();
	std::vector< cGroupElem<cPermElem<3>, Multiplication> > elementsD = g1.GetElementsDimino();

	std::cout<<"ELEMENTS:\n";
	for(std::size_t i = 0; i < elements.size(); i++)
	{
		std::cout<< "element:\n" <<elements[i]<<"\n";
	}
	
	std::cout<<"ELEMENTSD:\n";
	for(std::size_t i = 0; i < elementsD.size(); i++)
	{
		std::cout<< "element:\n" <<elementsD[i]<<"\n";
	}

	return 0;	
};

