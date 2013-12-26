#ifndef _COMMAND_CREATOR_H
#define _COMMAND_CREATOR_H

#include "command.h"
#include "getelem_command.h"
#include "getcenter_command.h"
#include "getcgraph_command.h"
#include "getrel_command.h"
#include "linalg_parser.h"
#include "poly_parser.h"
#include "getmatexpr_command.h"
#include "getnorm_command.h"
#include "getdeterminant_command.h"
#include "getinverse_command.h"
#include "getrref_command.h"
#include "getlinsyssol_command.h"
#include "getpolyzeros_command.h"
#include "getpolyplot_command.h"
#include "getfuncplot_command.h"
#include "getfuncdiff_command.h"

#include <boost/shared_ptr.hpp>

namespace engine
{

/*!
  implements the command creation using a variant of Factory method
*/
class cCommandCreator
{
public:
	static cCommand *GetCommand(COMMAND_TYPE command, const std::string& param)
	{
		cCommand *pcommand;
		if(command <= GET_RELATIONS)	//is group command
		{
			cParamGrpGenParser GenParamParser(param);
			GenParamParser.ParseParams();
			if(GET_ELEMENTS == command)
				pcommand = new cGetElemCommand(GenParamParser.GetGroupType(), GenParamParser.GetGenerators());
			else if(GET_CENTER == command)
				pcommand = new cGetCenterCommand(GenParamParser.GetGroupType(), GenParamParser.GetGenerators());
			else if(GET_CGRAPH == command)
				pcommand = new cGetCGraphCommand(GenParamParser.GetGroupType(), GenParamParser.GetGenerators());
			else if(GET_RELATIONS)
				pcommand = new cGetRelCommand(GenParamParser.GetGroupType(), GenParamParser.GetGenerators());
		}
		else if(command <= GET_MAT_EXPR)
		{
			cLinAlgParser LinAlgParamParser(param);
			LinAlgParamParser.ParseParams();
			if(GET_MAT_EXPR == command)
				pcommand = new cGetMatExprCommand(LinAlgParamParser.GetLinExpression());
			else if(GET_NORM == command)
				pcommand = new cGetNormCommand(LinAlgParamParser.GetLinExpression());
			else if(GET_MAT_DETERMINANT == command)
				pcommand = new cGetDeterminantCommand(LinAlgParamParser.GetLinExpression());
			else if(GET_MAT_INVERSE == command)
				pcommand = new cGetInverseCommand(LinAlgParamParser.GetLinExpression());
			else if(GET_MAT_RREF == command)
				pcommand = new cGetRREFCommand(LinAlgParamParser.GetLinExpression());
			else if(SOLVE_LINEQ_SYS == command || APPROX_LINEQ_SYS == command || SOLVEG_LINEQ_SYS == command)
				pcommand = new cGetLinSysSolCommand(LinAlgParamParser.GetLinExpression(), command);
		}
		else if(command <= GET_POLY_PLOT)
		{
			cPolyParser PolyParamParser(param);
			PolyParamParser.ParseParams();
			if(GET_POLY_ZEROS == command)
				pcommand = new cGetPolyZerosCommand(PolyParamParser.GetPolynomial());
//			else if(GET_POLY_DISCRIMINANT == command)
//				pcommand = new cGetPolyDiscriminantCommand(PolyParamParser.GetPolynomial());
			else if(GET_POLY_PLOT == command)
				pcommand = new cGetPolyPlotCommand(PolyParamParser.GetPolynomial());
		}
		else if(command <= GET_FNC_DIFF)
		{
			cFuncExprParser fnc_parser(param);
			fnc_parser.ParseParams();

			if(GET_FNC_PLOT == command)
				pcommand = new cGetFuncPlotCommand(fnc_parser.GetFuncExpr());
			else if(GET_FNC_DIFF == command)
				pcommand = new cGetFuncDiffCommand(fnc_parser.GetFuncExpr());
		}
		else
			throw std::invalid_argument(CONTEXT_STR + "invalid command received :" + param);

		return pcommand;
	}
};

}

#endif

