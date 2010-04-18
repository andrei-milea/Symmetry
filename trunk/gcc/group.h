#ifndef _GROUP_H
#define _GROUP_H

#define INFINITE_ORDER  0

#include "group_set.h"
#include "binary_op.h"
#include "sqmatrix.h"

template <typename T,
typename OpPolicy,
template <class> class CONT>
class cGroup
{
	typedef cGroup<T,OpPolicy,CONT> GroupType;
public:
    cGroup(std::size_t size)
		:m_Order(size)
    {};

    cGroup()
		:m_Order(INFINITE_ORDER)
	{};

    virtual ~cGroup()   {};
	void GenerateGroupTable();


	std::size_t GetOrder()const
	{
		return m_Order;
	};
	
private:
	CONT<T> m_Set;
	std::size_t m_Order;
};



typedef cGroup < cSqMatrixElement<int,5,Addition>, Addition, cSet> AdMatG;

#endif
