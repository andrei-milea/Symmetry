#include "group.h"
#include "intmodn.h"
#include "permutation.h"

#include <iostream>

int main()
{
	cPermElem<3> perm;
	cPermElem<3> permt({1,3,2});
	//perm = perm * permt;
	//if(perm * permt == permt * perm)
		std::cout<<perm<<"\n"<<permt<<"\n";
	cPermElem<4> perm1({1,2});
	cPermElem<4> perm2({3,4});
	cPermElem<4> perm3({1,3,2,4});
	cPermElem<4> perm4({2,3,4});

	//S4 sim4({perm1, perm2, perm3, perm4});
	return 0;	
};
