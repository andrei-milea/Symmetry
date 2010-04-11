#ifndef _GROUP_H
#define _GROUP_H

#define INFINITE_ORDER  0

#include <set>
#include "subgroup.h"
#include "binary_op.h"
#include "element.h"
#include "sqmatrix.h"

template <typename T, typename OpPolicy = Addition>
class cGroup
{
public:
    cGroup(size_t size)
		:m_Order(size)
    {};

    cGroup()
		:m_Order(INFINITE_ORDER)
	{};

    virtual ~cGroup()   {};
	void GenerateGroupTable();

    cSubGroup<T>& GetKernel();
    cSubGroup<T>& GetImage();
	
private:
	std::set< cElement<T,OpPolicy> > m_Set;
	size_t m_Order;
};

//typedef cSqMatrix<int,5,Addition> cSqMatrixAdd5;
//typedef cGroup<cSqMatrixAdd5, Addition> GenLinGroup5;
typedef cGroup<int, Addition> Z;


#endif
