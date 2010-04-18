#include "sqmatrix.h"


#include <iostream>

int main()
{
	cSqMatrixElement< int, 5, Addition> mat1;
	cSqMatrixElement< int, 5, Addition> mat2;

	mat1 = mat2;


	return 0;
};
