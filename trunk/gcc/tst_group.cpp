#include "group.h"
#include "intmodn.h"
#include "permutation.h"
#include "std_ex.h"


#include <iostream>

int main()
{

	cPermElem<3> s3({1,2});
	cPermElem<3> s4({1,2,3});
	cGroupElem< cPermElem<3>, Multiplication> elem3(s3);
	cGroupElem< cPermElem<3>, Multiplication> elem4(s4);
	std::vector< cGroupElem<cPermElem<3>, Multiplication> >  generators1;
	generators1.push_back(elem3);
	generators1.push_back(elem4);
	S3 g2(generators1);
	std::vector< cGroupElem<cPermElem<3>, Multiplication> >el = g2.GetElementsDimino();
	std_ex::cout<<el;

	std::vector<std::size_t> orbit1 = g2.GetOrbit(1);
	std::vector<std::size_t> orbit2 = g2.GetOrbit(2);
	std_ex::cout<<orbit1;
	std_ex::cout<<orbit2;

//	std::cout<<"ELEMENTS:\n";
//	for(std::size_t i = 0; i < elements1.size(); i++)
//	{
//		std::cout<< "element:\n" <<elements1[i]<<"\n";
//	}
	
//	std::cout<<"ELEMENTSD:\n";
//	for(std::size_t i = 0; i < elementsD.size(); i++)
//	{
//		std::cout<< "element:\n" <<elementsD[i]<<"\n";
//	}

	return 0;	
};

