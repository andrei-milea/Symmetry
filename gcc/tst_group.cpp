#include "group.h"

#include <iostream>

int main()
{
	//test squared matrix
	typedef cSqMatrixElement<int, 3, Addition> sqmat3;
	sqmat3 mat1;
	mat1(0,0) = 1;
	mat1(0,1) = 2;
	mat1(2,1) = 3;


	sqmat3 mat2;
	for(unsigned int i = 0; i< mat2.size1(); i++)
	{
		for(unsigned int j = 0; j< mat2.size2(); j++)
		{
			mat2(i, j) = 2;
		}
	}
	mat2 += mat1;
	std::cout << mat1 << "\n";
	std::cout << "mat1+mat2" << mat2 << "\n";

	//test matrix group
	cSqMatGroup3 mat_group(4); 
	return 0;	


};

