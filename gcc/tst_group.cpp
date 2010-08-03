#include "group.h"
#include "intmodn.h"
#include "permutation.h"

#include <iostream>

int main()
{
	cPermElem<3> s1;
	cPermElem<3> s2({2,3});
	cPermElem<3> s3({1,2});
	cGroupElem< cPermElem<3>, Multiplication> elem1(s1);
	cGroupElem< cPermElem<3>, Multiplication> elem2(s2);
	cGroupElem< cPermElem<3>, Multiplication> elem3(s3);
	std::cout<<elem1.GetOrder()<<"\n"<<elem2.GetOrder()<<"\n"<<elem3.GetOrder()<<"\n";
	std::cout<<"aaa: " <<elem2.GetOrder(cGroupElem< cPermElem<3>, Multiplication>::GroupSize)<<"\n";
	std::cout<<elem2.GetNthPower(2);
	//S4 sim4({perm1, perm2, perm3, perm4});
	return 0;	
};

