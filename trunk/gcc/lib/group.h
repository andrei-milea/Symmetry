#ifndef _GROUP_H
#define _GROUP_H

#define INFINITE_ORDER  0

#include "slp_rep.h"
#include "gen_rep.h"
#include "group_elem.h"
#include "symmetric_rep.h"
#include "subgroup.h"
#include "std_ex.h"

/*!
  this class represents a group given by a set of generators
  it uses an internal representation given by the group_rep
  template parameter and the type element T
*/
template < typename T, template <typename> class group_rep = cGenRep >
class cGroup : public group_rep<T>
{
public:
	typedef T ElementType;
	typedef cGroup<T, group_rep> SelfType;
	typedef group_rep<T> RepType;
	typedef typename std::vector<ElementType> GrpVec;

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

	/*!
	  TODO implement this ?
	  returns true if the group is soluble
	*/
	bool isSoluble()const
	{
		return true;
	};

	/*!
	  returns the centralizer subgroup of the group using the given subgroup
	*/
	cSubgroup<SelfType> GetCentralizer(const cSubgroup<SelfType> &_subgrp)const
	{
		cSubgroup<SelfType> subgroup(GetCentralizerEl(_subgrp));
		subgroup.isNormal(true);
		return subgroup;
	};

	/*!
	  returns the center subgroup of the group Z(G), the elements that comute with all the 
	  elements of the group
	*/
	cSubgroup<SelfType> GetCenter()const
	{
		cSubgroup<SelfType> subgroup(GetCenterEl());
		subgroup.isNormal(true);
		return subgroup;
	};
	
	/*!
	  returns the normalizer subgroup, given a subgroup
	*/
	cSubgroup<SelfType> GetNormalizer(const cSubgroup<SelfType> &_subgrp)const
	{
		cSubgroup<SelfType> subgroup(GetNormalizerEl(_subgrp));
		subgroup.isNormal(true);
		return subgroup;
	};

	/*!
	  returns the centralizer subgroup of a given element
	*/
	std::vector<ElementType> GetCentralizerEl(ElementType &element)const
	{
		typedef typename std::vector<ElementType>::iterator Elem_Iter ;
		GrpVec grp_el = this->GetElementsDimino();
		GrpVec centralizer;
		for(Elem_Iter iter = grp_el.begin(); iter != grp_el.end(); iter++)
		{
			if(iter->CommutesWith(element))
				centralizer.push_back(*iter);
		}
		return centralizer;
	};

	/*!
	  returns the centralizer subgroup of the group as a list of elements
	*/
	std::vector<ElementType> GetCenterEl()const
	{
		GrpVec subgrp_el;
		subgrp_el.push_back(RepType::GetIdentity());
		GrpVec grp_el = this->GetElementsDimino();
		GrpVec rem_el = grp_el;
		std::remove(rem_el.begin(), rem_el.end(), RepType::GetIdentity());
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

	/*!
	  TODO -- check for bugs
	  returns the normalizer subgroup of the given subgroup as a list of elements
	*/
	std::vector<ElementType> GetNormalizerEl(const cSubgroup<SelfType> &_subgrp)const
	{
		GrpVec normalizer_el;
		normalizer_el.push_back(RepType::GetIdentity());

		GrpVec grp_el = this->GetElementsDimino();
		GrpVec rem_el = grp_el;

		const GrpVec _subgrp_el = _subgrp.GetElementsDimino();

		//remove identity
		rem_el = GrpVec(rem_el.begin(),
				std::remove(rem_el.begin(), rem_el.end(), RepType::GetIdentity()));

		while(!rem_el.empty())
		{
			if(rem_el.begin()->IsNormalizer(_subgrp_el))
			{
				normalizer_el.push_back(*rem_el.begin());
				SelfType H(normalizer_el);
				std_ex::set_difference(rem_el, H.GetElementsNaive());
			}
			else
			{
				rem_el.erase(rem_el.begin());
			}
		}
		return normalizer_el;
	};
};

typedef cGroup<SymmGrpElem, cSymmetricRep> SymmGrp;
typedef std::vector< cGroupElem<cPermElem, Multiplication> >  SymmGrpGenerators;

//************concrete groups table**************//
typedef cGroup< cGroupElem< cPermElem, Multiplication >, cSymmetricRep > S3;

#endif
