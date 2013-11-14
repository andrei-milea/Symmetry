#ifndef _COMMAND_H
#define _COMMAND_H

#include <string>
#include "estimate.h"


/*!
 base class for commands (Command design pattern)
*/
namespace engine
{

enum COMMAND_TYPE
{
    NULL_COMMAND = 0,
    GET_ELEMENTS,
    GET_CENTER,
    GET_CGRAPH,
	GET_RELATIONS,
	SOLVE_LINEQ_SYS,
	APPROX_LINEQ_SYS,
	SOLVEG_LINEQ_SYS,
	GET_NORM,
	GET_MAT_INVERSE,
	GET_MAT_DETERMINANT,
	GET_MAT_EIGENVALUES,
	GET_MAT_RREF,
	GET_MAT_EXPR,
	GET_POLY_ZEROS,
	GET_POLY_DISCRIMINANT,
	GET_POLY_PLOT
};

class cCommand
{
public:
	virtual ~cCommand()
	{
	};

	virtual void Execute()=0;

	/*!
	  uses the visitor based on cEstimator to return a rough estimation
	  of the running time of a given command
	*/
	virtual unsigned int EstimateRunTime(const cEstimator &estimator)const=0;
};

}

#endif


