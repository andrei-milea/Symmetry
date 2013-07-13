#ifndef _FUNC_EXPR_H
#define _FUNC_EXPR_H

#include "binary_op.h"
#include "variable.h"
#include "trig_funcs.h"
#include "univar_polynomial.h"
#include "univar_func.h"

#include <boost/variant.hpp>
#include <boost/variant/recursive_wrapper.hpp>

struct cEmptyExpr
{
	bool operator==(const cEmptyExpr &expr)const
	{
		return true;
	}
};

//suppported functions
typedef boost::variant<cSine<double>,
					cCosine<double>,
					cTangent<double>,
					cAsine<double>,
					cAcosine<double>,
					cAtangent<double>,
					cUnivarPolynomial<double>,
					boost::recursive_wrapper<cFuncExpr>,
					cVariable,
					cEmptyExpr,
					double > expr_type;

//suppported operations
typedef boost::variant< Addition,
					Multiplication,
					Division,
					Subtraction,
					Composition,
					NoOp > operation_type;


/*!
 * holds a compound function expression (i.e. (sin(x) + e^x)*cos(x))
 * implements the 'symbolic' functionality
*/
class cFuncExpr
{
public:
	cFuncExpr();

	cFuncExpr(expr_type univar_func);

	cFuncExpr(operation_type operation, expr_type univar_func1, expr_type univar_func2);

	cFuncExpr(const cFuncExpr &func_expr);

	cFuncExpr &operator=(const cFuncExpr& func_expr);

	~cFuncExpr();

	void simplify();

	void print();

	cFuncExpr derivative()const;

	cFuncExpr primitive()const;

	bool operator==(const cFuncExpr& fnc_expr)const;

	template <typename T>
	T operator()(T arg)const;

private:
	cFuncExpr derivative_impl()const;

private:
	operation_type m_Operation;
	expr_type  m_LHSExpr;
	expr_type m_RHSExpr;

friend class cExprDiffVisitor;
friend class cDiffVisitor;
friend class cSimplifyVisitor;
friend std::ostream& operator<<(std::ostream& out, const cFuncExpr& func_expr);
};


std::ostream& operator<<(std::ostream& out, const cFuncExpr& func_expr);

#endif

