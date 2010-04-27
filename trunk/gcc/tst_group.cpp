#include "group.h"

#include <iostream>

int main()
{
	//tst squared matrix
	cSqMatrixElement<int, 3, Addition> mat1;
	mat1(0,0) = 1;
	mat1(0,1) = 2;
	mat1(2,1) = 3;
	std::cout << mat1 <<"\n";
	AdMatG gr(5);

	return 0;	


};

