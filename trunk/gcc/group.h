#ifndef _GROUP_H
#define _GROUP_H

#define INFINITE_ORDER  0

#include "slp_rep.h"
#include "gen_rep.h"
#include "group_elem.h"
#include "symmetric_rep.h"
#include "subgroup.h"

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
	cGroup(std::vector<ElementType> &gr_vec)
		:group_rep<ElementType> (gr_vec)
	{};
	//TODO -- add constructor inheritance in the next gcc release
	//broken compiler ???
	cGroup (std::initializer_list<T> ini_list)
		:group_rep<T>(ini_list)
	{};

    ~cGroup()   {};

	bool isSoluble()const
	{
		return true;
	};

	cSubgroup<SelfType> GetCentralizerEl(const cSubgroup<SelfType> &_subgrp)const
	{
		cSubgroup<SelfType> subgroup(GetCentralizerEl(_subgrp));
		subgroup.isNormal(true);
		return subgroup;
	};

	cSubgroup<SelfType> GetCenter()const
	{
		cSubgroup<SelfType> subgroup(GetCenterEl());
		subgroup.isNormal(true);
		return subgroup;
	};
	
	cSubgroup<SelfType> GetNormalizer(const cSubgroup<SelfType> &_subgrp)const
	{
		cSubgroup<SelfType> subgroup(GetNormalizerEl(_subgrp));
		subgroup.isNormal(true);
		return subgroup;
	};


	std::vector<ElementType> GetCentralizerEl(ElementType &element)const
	{
		typedef typename std::vector<ElementType> GrpVec;
		GrpVec subgrp_el;
		subgrp_el.push_back(ElementType::GetIdentity());
		GrpVec grp_el = this->GetElementsDimino();
		GrpVec rem_el = grp_el;
		std::remove(rem_el.begin(), rem_el.end(), ElementType::GetIdentity());
		while(!rem_el.empty())
		{
			std::for_each(grp_el.begin(), grp_el.end(), 
					[&rem_el, &subgrp_el] (typename GrpVec::iterator it1)
			{
				if(rem_el.begin()->IsCentralizer(*it1))
				{
					subgrp_el.push_back(rem_el.begin());
					rem_el.erase(rem_el.begin());
				}
				else
				{
					rem_el.erase(it1);
				}
			});
		}
		return subgrp_el;
	};

	std::vector<ElementType> GetCenterEl()const
	{
		typedef typename std::vector<ElementType> GrpVec;
		GrpVec subgrp_el;
		subgrp_el.push_back(ElementType::GetIdentity());
		GrpVec grp_el = this->GetElementsDimino();
		GrpVec rem_el = grp_el;
		std::remove(rem_el.begin(), rem_el.end(), ElementType::GetIdentity());
		while(!rem_el.empty())
		{
			bool commutes = true;
			for(typename GrpVec::iterator it = grp_el.begin(); it != grp_el.end(); it++)
			{
				if(!rem_el.begin()->CommutesWith(*it))
				{
					commutes = false;
					break;
				}
			}
			if(commutes)
			{
				subgrp_el.push_back(*rem_el.begin());
			}
			rem_el.erase(rem_el.begin());
		}
		return subgrp_el;	
	};

	std::vector<ElementType> GetNormalizerEl(const cSubgroup<SelfType> &_subgrp)const
	{
		typedef typename std::vector<ElementType> GrpVec;
		GrpVec subgrp_el;
		subgrp_el.push_back(ElementType::GetIdentity());
		GrpVec grp_el = this->GetElementsDimino();
		GrpVec rem_el = grp_el;
		const GrpVec _subgrp_el = _subgrp.GetElementsDimino();
		std::remove(rem_el.begin(), rem_el.end(), ElementType::GetIdentity());
		while(!rem_el.empty())
		{
			bool normalizes = true;
			for(typename GrpVec::iterator it = grp_el.begin(); it != grp_el.end(); it++)
			{
				if(!rem_el.begin()->IsNormalizer(_subgrp_el));
				{
					normalizes = false;
					break;
				}
			}
			if(normalizes)
			{
				subgrp_el.push_back(*rem_el.begin());
			}
			rem_el.erase(rem_el.begin());
		}
		return subgrp_el;
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
