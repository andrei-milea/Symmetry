#include "group.h"
#include "intmodn.h"

#include <iostream>

int main()
{

	cSqMatGroup3 gr1;
	auto random_element = gr1.GetRandomIterator();
	std::cout<<*random_element<<"hahahaha\n";
	//gr1.PrintGroupTable();
	return 0;	
};

