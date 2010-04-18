#ifndef _SLP_H
#define _SLP_H

#include <vector>
//"straightline program" class
//used in group representation<container>
template <typename T>
class cSLP
{
public:
	cSLP();
	~cSLP();
	void EvaluateSLP()const;


private:
	std::size_t m_Rank;
	std::vector<T> m_SLP;
};

#endif

