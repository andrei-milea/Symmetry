#ifndef _SLP_REP_H
#define _SLP_REP_H

#include <vector>
//"straightline program" representation class
template <typename T>
class cSLPRep
{
public:
	cSLPRep();

	~cSLPRep();

private:
	void EvaluateSLP()const;

private:
	std::size_t m_Rank;
	std::vector<T> m_SLP;
};

#endif

