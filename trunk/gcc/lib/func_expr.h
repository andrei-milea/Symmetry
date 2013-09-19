#ifndef _FUNC_EXPR_H
#define _FUNC_EXPR_H

#include "logarithm.h"
#include "exponential.h"
#include "abs_val.h"
#include "trig_funcs.h"
#include "univar_polynomial.h"
#include "univar_func.h"
#include "binary_op.h"

#include <boost/variant.hpp>
#include <boost/variant/recursive_wrapper.hpp>
#include <string>
#include <ostream>

class cVariable
{
public:
	cVariable(const std::string& str)
		:m_Str(str)
	{}
	
	const std::string getStr()const
	{
		return m_Str;
	}

	bool operator==(const cVariable& var)const
	{
		return m_Str == var.m_Str;
	}

private:
	std::string m_Str;
};

inline std::ostream& operator<<(std::ostream& out, const cVariable& var)
{
	out << var.getStr();
	return out;
}

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
					cExponential<double>,
					cLogarithm<double>,
					cAbsVal<double>,
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
					Power,
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
	
	bool operator==(const cFuncExpr& fnc_expr)const;

	~cFuncExpr();

	/*!
	 * siplifies the expression by partially evaluating subexpressions
	*/
	void simplify();

	/*!
	 * siplifies the expression by matching trigonometric identities
	*/
	void trig_simplify();

	/*!
	 * expand multiplications and powers removing paranthesis
	*/
	void expand();

	/*!
	 * try to factor expression
	*/
	void factor();

	cFuncExpr derivative()const;

	cFuncExpr primitive()const;

	/*!
	 * substitute var1 with var2 in expression
	 * throws exception if var1 is not found in expression
	*/
	void substitute(const cVariable& var1, const cVariable& var2);

	/*!
	 * evaluates the expression by substituting the variable with the given value
	 * an exception is thrown if the substitution fails
	*/
	template <typename T>
	expr_type eval(const cVariable &var, T& arg)const;

	/*!
	 * prints func expr as tree structure --for debugging purposes
	*/
	void printTree(const expr_type* root = nullptr)const;
	void printOp()const;

private:
	cFuncExpr derivative_impl()const;
	int precedence(const operation_type& op)const;

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

