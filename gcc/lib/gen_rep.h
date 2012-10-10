#ifndef _GEN_REP_H
#define _GEN_REP_H

#include <tr1/unordered_set>
#include <algorithm>
#include <iostream>
#include <boost/random.hpp>
#include <ctime>

namespace tr1 = std::tr1;

//general (naive) group representation class
//no public members -- used only from cGroup
template <typename T>
class cGenRep
{
public:
	typename tr1::unordered_set<T>::iterator IteratorType;

public:

	//constructors
	cGenRep()
		:m_GroupOrder(T::GroupOrder)
	{
		//m_Set = new std::set<T>(size);
	};

	cGenRep(tr1::unordered_set<T> &set)
		:m_GroupOrder(set.size())
	{
		m_Set = set;
	};

	~cGenRep()	{};

	typename tr1::unordered_set<T>::const_iterator GetRandomIterator()const
	{
		boost::mt19937 randGen(std::time(0));
		boost::uniform_int<std::size_t> random_index(0,m_GroupOrder);
		boost::variate_generator< boost::mt19937&, boost::uniform_int<std::size_t> >
		GetRand(randGen, random_index);
		return m_Set.begin();
	};

//	void PrintGroupTable()const
//	{
//		std::for_each(m_Set.begin(), m_Set.end(),
//		              [&m_Set] (typename tr1::unordered_set<T>::iterator it)
//		{
//			std::cout<< "Table for "<< (*it) << ": \n";
//			PrintElementTable(it);
//		});
//	};

//	void PrintElementTable(typename tr1::unordered_set<T>::iterator &itt)const
//	{
//		std::cout<<	"Table for element " << itt <<":\n";
//		std::for_each(m_Set.begin(), m_Set.end(),
//		              [&itt] (typename tr1::unordered_set<T>::iterator it1)
//		{
//			std::cout<< T::BinOpType::BinOp(*(itt),*(it1));
//		});
//	};


	//getter, setter
	tr1::unordered_set<T>& GetGroupSet()const
	{
		return m_Set;
	};
	void SetGroupSet(tr1::unordered_set<T> &set)
	{
		m_Set = set;
	};


private:
	tr1::unordered_set<T> m_Set;
	std::size_t m_GroupOrder;
};


#endif

