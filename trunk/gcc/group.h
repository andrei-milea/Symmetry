#ifndef _GROUP_H
#define _GROUP_H

#define INFINITE_ORDER  0

#include "slp_rep.h"
#include "gen_rep.h"
#include "group_elem.h"
#include "symmetric_rep.h"

//group class
template < typename T, template <typename> class group_rep = cGenRep >
class cGroup : public group_rep<T>
{
public:
	typedef typename T ElementType;
	typedef cGroup<T, group_rep> SelfType;
	typedef group_rep<T> RepType;

public:
    cGroup()
		:group_rep<T>()
    {};

    ~cGroup()   {};


	cSubGroup<SelfType> GetCentralizer(ElementType &element)const
	{
		typedef typename std::vector<ElementType> GrpVec;
		GrpVec subgrp_el;
		subgrp_el.push_back(ElementType::GetIdentity());
		GrpVec grp_el = this->GetElementsDimino();
		GrpVec rem_el = grp_el;
		std::remove(rem_el.begin(), rem_e.end(), ElementType::GetIdentity());
		while(!rem_el.empty())
		{
			std::for_each(grp_el.begin(), grp_el.end(), 
					[&rem_el, &subgrp_el] (GrpVec::iterator it1)
			{
				if(rem_el.begin()->IsCentralizer(*it))
				{
					subgrp_el.push_back(rem_el.begin());
					rem_el.erase(rem_el.begin());
				}
				else
				{
					rem_el.erase(it);
				}
			})
		}
		return cSubGroup<SelfType>(subgrp_el);
	};

	cSubGroup<SelfType> GetCenter()const
	{

	};
};



//************concrete groups table**************//
//squared matrix additive group
typedef cGroup< cGroupElem< cSqMatrixElement<int, 3>, Addition, 20> > cSqMatGroup3;	
//general liniar group
typedef cGroup< cGroupElem< cSqMatrixElement<cIntModNElem<20>, 3>, Multiplication, 20> > cGLgroup3;	
typedef cGroup< cGroupElem< cPermElem<3>, Multiplication >, cSymmetricRep > S3;
typedef cGroup< cGroupElem< cPermElem<4>, Multiplication >, cSymmetricRep > S4;

#endif
