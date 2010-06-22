#include "group.h"
#include "intmodn.h"
#include "permutation.h"

#include <iostream>
#include <boost/test/minimal.hpp>

//int main()
int test_main( int, char *[] )
{

	BOOST_CHECK( 3 == 4 );
	cPermElem<3> perm1({1,2,3});
	cPermElem<3> perm2({1,2,3});
	perm1 = perm1 * perm2;
	std::cout<<perm1;
	return 0;	
};

