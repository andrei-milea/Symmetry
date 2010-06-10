#ifndef _GROUP_H
#define _GROUP_H

#define INFINITE_ORDER  0

#include "slp_rep.h"
#include "gen_rep.h"
#include "sqmatrix.h"

//group class
template < typename T, template <typename> class group_rep = cGenRep >
class cGroup : public group_rep<T>
{
	typedef T ElementType;
	typedef cGroup<T, group_rep> SelfType;
	typedef group_rep<T> RepType;

public:
    cGroup(std::size_t size)
		:group_rep<T>(size)
    {};

    cGroup()
		:group_rep<T>(INFINITE_ORDER)
	{};

    ~cGroup()   {};

	void PrintGroupTable();

	std::size_t GetOrder()const
	{
		return group_rep<T>::GetOrder();
	};
};



//************concrete groups table**************//
//squared matrix additive group
typedef cGroup< cSqMatrixElement<int, 3, Addition> > cSqMatGroup3;	
//general liniar group
typedef cGroup< cSqMatrixElement<int, 3, Multiplication> > cGLGroup3;

#endif
