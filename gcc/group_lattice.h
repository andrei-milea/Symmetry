#ifndef GROUP_LATTICE
#define GROUP_LATTICE

#include <vector>

template <typename T>
class cGrpLattice
{
public:
	cGrpLattice(cGroup<T> &group)
	{
		if(group.isSoluble())
		{
			CyclicExtensionMethod(group);
		}
		else
		{
			//other method
		}
	};
	~cGrpLattice();
	{};


	vector< cSubgroup<T> >& GetLayer(std::size_t index)
	{
		return m_Lattice[index];
	};

	void CyclicExtensionMethod(cGroup<T> &group)
	{
		//add first layer to the lattice
		//get cyclic subgroups of prime power order
		std::vector<T> group_el = group.GetElementsDimino();
		std::vector<cSubgroup> layer0;
		std::for_each(group_el.begin(), group_el.end(), [&layer0, &group]
			(std::vector<cSubgroup>::iterator it)
			{
				cSubgroup< cGroup<T> > subgrp(group->GetCyclicGroup(*it));
				if(isPrime(subgrp.GetOrder(group.GetOrder())))
				{
					layer0.push_back(subgrp);
				}
			});
		
		std::size_t layer_index = 0;
		m_Lattice[layer_index] = layer0;

		//loop through the lattice layers
		//generate ith layer from (i-1)th layer
		for(std::vector< std::vector< cSubgroup<T> > >::iter = m_Lattice.begin();
				iter != m_Lattice.end(); iter++)
		{
			//loop through the subgroups in the (i-1)th layer
			for(std::vector< cSubgroup<T> >::iterator subgrp_iter = (*iter).begin()
					subgrp_iter != (*iter).end(); subgrp_iter++)
			{
				std::vector<T> subgroup_el = (*subgrp_iter).Elements();
				std::vector<T> normal_subgrp_el = group.GetNormalizerEl((*subgrp_iter));
				std::vector<T> avoid_old_elem = normal_subgrp_el - subgroup_el;
				//remove already generated subgroups
				if((iter+1) != m_Lattice.end())
				{
					std::for_each((*(iter+1)).begin(), (*(iter+1)).end(), [&avoid_old_elem]
					   (std::vector<T>::iterator iter2)
					   {
					   		if((*subgrp_iter).isSubgroup((*iter2)))
							subgroup_el -= (*iter2);
					   });
				}
				//generate new subgroup Ui = <Ui-1,g>
				//and add it to the layer
				while(!avoid_old_elem.empty())
				{
					T g = avoid_old_elem.begin();
					if(Contains_prime_pow_el(subgroup_el, g))
					{
						cSubgroup<T> newsubgrp();
						newsubgrp.AddCoset(subgroup_el, g);
						avoid_old_elem = avoid_old_elem - newsubgrp.GetElementsDimino;
					}
					else
					{
						avoid_old_elem.remove(g);
					}
				}
			}
		}
	};

private:
	bool Contains_prime_pow_el(const cSubgroup<T> grp, const T element)const
	{

	};

private:
	std::vector< std::vector< cSubgroup<T> > > m_Lattice;
};

#endif

