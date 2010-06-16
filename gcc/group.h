#ifndef _GROUP_H
#define _GROUP_H

#define INFINITE_ORDER  0

#include "slp_rep.h"
#include "gen_rep.h"
#include "group_elem.h"

//group class
template < typename T, template <typename> class group_rep = cGenRep >
class cGroup : public group_rep<T>
{
public:
	typedef T ElementType;
	typedef cGroup<T, group_rep> SelfType;
	typedef group_rep<T> RepType;

public:
    cGroup()
		:group_rep<T>()
    {};

    ~cGroup()   {};
};



//************concrete groups table**************//
//squared matrix additive group
typedef cGroup< cGroupElem< cSqMatrixElement<int, 3>, Addition, 20> > cSqMatGroup3;	
//general liniar group
typedef cGroup< cGroupElem< cSqMatrixElement<int, 3>, Multiplication, 20> > cGLgroup3;	

#endif
