#include "group.h"
#include "intmodn.h"
#include "permutation.h"

#include <iostream>

int main()
{

	cPermElem<3> perm1({1,2,3});
	cPermElem<3> perm2({1,2,3});
	perm1 = perm1 * perm2;
	std::cout<<perm1;
	std::cout<<perm2;
	return 0;	
};

