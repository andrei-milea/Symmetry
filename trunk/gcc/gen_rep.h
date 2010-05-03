#ifndef GEN_REP_H_
#define GEN_REP_H_

#include <set>

//general group representation class
template <typename T>
class cGenRep
{
public:
	cGenRep(std::size_t size)
		:m_GroupOrder(size)
	{
		m_Set = new std::set<T>(size);
	};

	cGenRep(std::set<T> &set)
		:m_GroupOrder(set.size())
	{
		m_Set = set;
	};

	~cGenRep()	{};

	std::set<T>& GetGroupSet()const
	{
		return m_Set;
	};


	

private:
	std::set<T> m_Set;
	std::size_t m_GroupOrder;
};


#endif

