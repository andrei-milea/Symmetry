#ifndef GROUP_LATTICE
#define GROUP_LATTICE

#include <vector>
#include <boost/math/special_functions/prime.hpp>

template <typename G>
class cGrpLattice
{
public:

	typedef typename G::ElementType T;
	typedef typename std::vector< cSubgroup<G> >::iterator SubGrp_Iterator;

	cGrpLattice(G &group)
		:m_Group(group)
	{};
	~cGrpLattice()
	{};


	std::vector< cSubgroup<G> >& GetLayer(std::size_t index)
	{
		return m_Lattice[index];
	};


	void CyclicExtensionMethod(G &group)
	{
		BuildCycSubgrpPPOrder();

		AddFirstLayer();

		//main loop -- iterate through every layer
		for(std::size_t index = 0; index < m_Lattice.size(); index++)	
		{
			//for each subgroup in the layer
			for(SubGrp_Iterator subgrp_iter = GetLayer(index).begin();
					subgrp_iter != GetLayer(index).end(); subgrp_iter++)
			{
				//compute generators of possible subgroups
				//possible_gen = (cyc_gen ^ (N(U) - U) ) - subgrps in the ith layer
				std::vector<T> norm_elem = m_Group.GetNormalizerEl(*subgrp_iter);
				std_ex::set_difference(norm_elem, (*subgrp_iter).GetElementsDimino());
				std::vector<T> possible_gen = std_ex::set_difference(m_CycSubgrpsGen, 
						norm_elem);
				//remove subgroups already in the ith layer
				for(SubGrp_Iterator subgrp1_iter = GetLayer(index+1).begin();
						subgrp1_iter != GetLayer(index+1).end(); subgrp1_iter++) 
				{
					std_ex::set_difference(possible_gen, (*subgrp1_iter).GetGeneratorsSet());
				}

				//construct new subgroups and add them to the ith layer
				for(typename std::vector<T>::iterator elem_iter = possible_gen.begin();
						elem_iter != possible_gen.end(); elem_iter++)
				{
					if(Has_prime_pow_el(*subgrp_iter, *elem_iter))
					{
						(*subgrp_iter).AddGenerator(*elem_iter);
						GetLayer(index).push_back(*subgrp_iter);
						std_ex::set_difference(possible_gen, (*subgrp_iter).GetGeneratorsSet());
					}
					else
					{
						possible_gen.remove(*elem_iter);
					}
				}
			}
		}
		AddLastLayer();
	};


private:

	//add first layer containing the subgroup
	//generated by the identity
	void AddFirstLayer()
	{
		std::vector<T> trivial_subgrp_gen;
		trivial_subgrp_gen.push_back(G::GetIdentity());
		cSubgroup<G> trivial_subgrp(trivial_subgrp_gen);
		std::vector< cSubgroup<G> > layer0;
		layer0.push_back(trivial_subgrp);
		m_Lattice.push_back(layer0);
	};

	//add last layer containing the group G itself
	void AddLastLayer()
	{
		cSubgroup<G> group_itself(m_Group);
		std::vector< cSubgroup<G> > last_layer;
		m_Lattice.push_back(last_layer);
	};

	//build cyclic subgroups of prime power order
	void BuildCycSubgrpPPOrder()
	{
		std::vector<T> group_elements = m_Group.GetElementsDimino();
		for(typename std::vector<T>::iterator iter = group_elements.begin();
				iter != group_elements.end(); iter++)
		{
			std::vector<T> cyc_subgrp_elem = m_Group.GetCyclicSubgroup(*iter);
			if(isPrime(cyc_subgrp_elem.size()))
			{
				m_CycSubgrpsGen.push_back(*iter);
			}
		}
	};

	//check if a subgroup the element at prime power order
	bool Has_prime_pow_el(const cSubgroup<T> grp, const T element)const
	{
		std::size_t prime_index = 0;
		std::size_t elem_order = element.GetOrder();
		std::size_t prime = boost::math::prime(prime_index);
		while(prime < elem_order)
		{
			if(grp.Contains(element.GetNthPower(prime)))
				return true;
			prime_index++;
			prime = boost::math::prime(prime_index);
		}
		return false;
	};

	//TODO -- improve naive primality testing
	bool isPrime(int number) 
	{
	   if(number == 1 || (number%2 == 0)) return false;
	   if(number == 2) return true;
	   for(int i=3; i*i<=number; i+=2) 
	   {
		  if(number%i == 0)
			 return false;
	   }
	   return true;
	}

private:
	G												m_Group;
	std::vector<T> 									m_CycSubgrpsGen;
	std::vector< std::vector< cSubgroup<T> > > 		m_Lattice;
};

#endif

