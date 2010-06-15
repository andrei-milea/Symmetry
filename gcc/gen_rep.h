#ifndef GEN_REP_H_
#define GEN_REP_H_

#include <tr1/unordered_set>
#include <algorithm>
#include <iostream>

namespace tr1 = std::tr1;

//general (naive) group representation class
//no public members -- used only from cGroup
template <typename T>
class cGenRep
{
protected:
	cGenRep(std::size_t size)
		:m_GroupOrder(size)
	{
		//m_Set = new std::set<T>(size);
	};

	cGenRep(tr1::unordered_set<T> &set)
		:m_GroupOrder(set.size())
	{
		m_Set = set;
	};

	~cGenRep()	{};

	tr1::unordered_set<T>& GetGroupSet()const
	{
		return m_Set;
	};

	void PrintGroupTable()const
	{
		std::for_each(m_Set.begin(), m_Set.end(), 
				[&m_Set] (typename tr1::unordered_set<T>::const_iterator it)
				{
					std::cout<< "Table for "<< (*it) << ": \n";	
					std::for_each(m_Set.begin(), m_Set.end(), 
						[&it](typename tr1::unordered_set<T>::const_iterator it1)
						{std::cout<< T::BinOpType::BinOp(*(it),*(it1)) << "\n"; });
				});
	};

	void PrintElementTable(typename tr1::unordered_set<T>::const_iterator &itt)const
	{
		std::cout<<	"Table for element " << itt <<":\n";
		std::for_each(m_Set.begin(), m_Set.end(),
			   	[&m_Set] (typename tr1::unordered_set<T>::const_iterator it1)
				{
					std::cout<< T::BinOpType::BinOp(*(it),*(it1));
				});
	};
	

private:
	tr1::unordered_set<T> m_Set;
	std::size_t m_GroupOrder;
};


#endif

