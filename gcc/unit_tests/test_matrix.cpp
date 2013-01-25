
#include "../lib/matrix.h"

#define BOOST_TEST_MODULE "test_matrix"

#include "boost/test/included/unit_test.hpp"

using namespace boost::unit_test;


BOOST_AUTO_TEST_CASE(test_rref)
{
	//basic test
	bnu::matrix<double> mat(3, 4);
	bnu::matrix<double> mat_rref(3, 4);

	const double MATRIX_INIT[3][4] = {	{1, 2, -1, -4}, 
									{2, 3, -1, -11},
									{-2, 0, -3, 22}	};	

	const double MATRIX_INIT_RESULT[3][4] = {	{1, 0, 0, -8}, 
												{0, 1, 0, 1},
												{0, 0, 1, -2}	};	
	
	for(std::size_t row_idx = 0; row_idx < mat.size1(); row_idx++)
		for(std::size_t col_idx = 0; col_idx < mat.size2(); col_idx++)
			mat(row_idx, col_idx) = MATRIX_INIT[row_idx][col_idx];

	for(std::size_t row_idx = 0; row_idx < mat.size1(); row_idx++)
		for(std::size_t col_idx = 0; col_idx < mat.size2(); col_idx++)
			mat_rref(row_idx, col_idx) = MATRIX_INIT_RESULT[row_idx][col_idx];

	rref(mat);
	BOOST_ASSERT(bnu::norm_1(mat - mat_rref) == 0.0);
}

//int main()
//{
//	//basic test
//	bnu::matrix<double> mat(3, 4);
//	bnu::matrix<double> mat_rref(3, 4);
//
//	const double MATRIX_INIT[3][4] = {	{1, 2, -1, -4}, 
//									{2, 3, -1, -11},
//									{-2, 0, -3, 22}	};	
//
//	const double MATRIX_INIT_RESULT[3][4] = {	{1, 0, 0, -8}, 
//												{0, 1, 0, 1},
//												{0, 0, 1, -2}	};	
//	
//	for(std::size_t row_idx = 0; row_idx < mat.size1(); row_idx++)
//		for(std::size_t col_idx = 0; col_idx < mat.size2(); col_idx++)
//			mat(row_idx, col_idx) = MATRIX_INIT[row_idx][col_idx];
//
//	for(std::size_t row_idx = 0; row_idx < mat.size1(); row_idx++)
//		for(std::size_t col_idx = 0; col_idx < mat.size2(); col_idx++)
//			mat_rref(row_idx, col_idx) = MATRIX_INIT_RESULT[row_idx][col_idx];
//
//	rref(mat);
//	return 1;
//};

