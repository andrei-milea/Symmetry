#include "group.h"
#include "intmodn.h"
#include "permutation.h"

#include <iostream>

int main()
{

	cSqMatGroup3 gr1;
	auto random_element = gr1.GetRandomIterator();
	std::cout<<*random_element<<"hahahaha\n";
	return 0;	
};

