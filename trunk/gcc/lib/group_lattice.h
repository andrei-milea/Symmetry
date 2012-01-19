#ifndef GROUP_LATTICE
#define GROUP_LATTICE

#include <vector>
#include <map>
#include <boost/math/special_functions/prime.hpp>
#include <iostream>
#include <cassert>
#include "std_ex.h"
#include "subgroup.h"

/*!
  this class is under construction (not working yet)
*/
template <typename G>
class cGrpLattice
{
public:

	typedef typename G::ElementType T;
	typedef typename std::vector< cSubgroup<G> >::iterator SubGrp_Iterator;
	typedef cGrpLattice<G> SelfType;
	typedef typename std::vector<T> ElemVec;

	cGrpLattice(G &group)
		:m_Group(group)
	{};
	~cGrpLattice()
	{};


	friend std::ostream& operator<<(std::ostream& out, SelfType& lattice)
	{
		out<<"LATTICE:\n";
		for(int index = lattice.m_Lattice.size() - 1; index >= 0; index--)
		{
			std::vector< cSubgroup<G> > layer = lattice.GetLayer(index);
			out<<"Layer "<<index<<" : \n";
			for(SubGrp_Iterator iter = layer.begin(); iter != layer.end(); iter++)
			{
				out<<*iter<<"\n";
			}
		}
		return out;
	};


	std::vector< cSubgroup<G> >& GetLayer(const std::size_t index)
	{
		assert(m_Lattice.size() > index);
		return m_Lattice[index];
	};


	void CyclicExtensionMethod()
	{
		BuildCycSubgrpPPOrder();

		AddFirstLayer();

		//cyclic subgroups of prime power order
		AddSecondLayer();

		bool need_new_layer = false;
		//main loop -- iterate through every layer
		for(std::size_t index = 1; index < m_Non_Triv_Layers; index++)
		{
			//add cyclic subgroups of order p^index
			if(m_CycSubgrpsGen[index+1].empty())
			{
				need_new_layer = true;
			}
			else
			{
				AddNewLayer();
				for(typename ElemVec::iterator it = m_CycSubgrpsGen[index+1].begin();
				        it != m_CycSubgrpsGen[index+1].end(); it++)
				{
					cSubgroup<G> subgrp;
					subgrp.AddGenerator(*it);
					GetLayer(index+1).push_back(subgrp);
				}
			}
			//for each subgroup in the layer
			for(SubGrp_Iterator subgrp_iter = GetLayer(index).begin();
			        subgrp_iter != GetLayer(index).end(); subgrp_iter++)
			{
				//compute generators of possible subgroups
				//possible_gen = (cyc_gen ^ (N(U) - U) ) - subgrps in the ith layer
				ElemVec norm_elem = m_Group.GetNormalizerEl(*subgrp_iter);
				//std_ex::print_vector(norm_elem);

				std_ex::set_difference(norm_elem, (*subgrp_iter).GetElementsDimino());


				//std_ex::print_vector(norm_elem);

				ElemVec possible_gen = std_ex::set_intersection(m_CycSubgrpsGen[1],
				                       norm_elem);

				//remove subgroups already in the ith layer
				if(index+1 < m_Lattice.size())
				{
					for(SubGrp_Iterator subgrp1_iter = GetLayer(index+1).begin();
					        subgrp1_iter != GetLayer(index+1).end(); subgrp1_iter++)
					{
						std_ex::set_difference(possible_gen,
						                       (*subgrp1_iter).GetGeneratorsSet());
					}
				}

				//construct new subgroups and add them to the ith layer
				while(!possible_gen.empty())
				{
					T generator = *possible_gen.begin();
					if(Has_prime_pow_el(*subgrp_iter, generator))
					{
						cSubgroup<G> subgrp = (*subgrp_iter);
						subgrp.AddGenerator(generator);
						if(need_new_layer)
						{
							AddNewLayer();
							need_new_layer = false;
						}
						GetLayer(index+1).push_back(subgrp);
						std_ex::set_difference(possible_gen,subgrp.GetElementsDimino());
					}
					else
					{
						possible_gen.erase(possible_gen.begin());
					}
				}
			}
		}
		AddLastLayer();
	};

private:

	//add a new empty layer
	void AddNewLayer()
	{
		std::vector< cSubgroup<G> > new_layer;
		m_Lattice.push_back(new_layer);
	};

	//add first layer containing the subgroup
	//generated by the identity
	void AddFirstLayer()
	{
		ElemVec trivial_subgrp_gen;
		trivial_subgrp_gen.push_back(m_Group.GetIdentity());
		cSubgroup<G> trivial_subgrp(trivial_subgrp_gen);
		std::vector< cSubgroup<G> > layer0;
		layer0.push_back(trivial_subgrp);
		m_Lattice.push_back(layer0);
	};

	//add second layer consisting of cyclic? subgroups
	//of prime power order
	void AddSecondLayer()
	{
		AddNewLayer();

		for(typename ElemVec::iterator iter = m_CycSubgrpsGen[1].begin();
		        iter != m_CycSubgrpsGen[1].end(); iter++)
		{
			cSubgroup<G> newsubgroup;
			newsubgroup.AddGenerator(*iter);
			assert(isPrime(newsubgroup.GetCyclicSubgroup(*iter).size()));
			m_Lattice[1].push_back(newsubgroup);
		}
	};

	//add last layer containing the group G itself
	void AddLastLayer()
	{
		AddNewLayer();
		cSubgroup<G> group_itself(m_Group);
		m_Lattice[m_Lattice.size()-1].push_back(group_itself);
	};

	//build cyclic subgroups of prime power order
	//also computes the number of non-trivial layers
	void BuildCycSubgrpPPOrder()
	{
		ElemVec group_elements = m_Group.GetElementsDimino();

		//set the number of non-trivial layers
		//factor the group order -- TODO : improve algorithm
		//trial division -- bad complexity
		std::size_t group_order = group_elements.size();
		std::size_t index1 = 0;
		std::size_t non_triv_layers = 0;
		while(group_order > 1)
		{
			std::size_t prime = boost::math::prime(index1);
			while(group_order % prime == 0)
			{
				group_order = group_order / prime;
				non_triv_layers++;
			}
			index1++;
		}
		m_Non_Triv_Layers = non_triv_layers - 1;


		while(!group_elements.empty())
		{
			ElemVec cyc_subgrp_elem = m_Group.GetCyclicSubgroup(*group_elements.begin());
			std::size_t cyc_subgrp_size = cyc_subgrp_elem.size();
			if(isPrime(cyc_subgrp_size))
			{
				m_CycSubgrpsGen[1].push_back(*group_elements.begin());
			}
			else
			{
				std::size_t index = 0;
				std::size_t power = 0;
				while(cyc_subgrp_size > 1)
				{
					std::size_t prime = boost::math::prime(index);
					while(cyc_subgrp_size % prime == 0)
					{
						cyc_subgrp_size = cyc_subgrp_size / prime;
						power++;
					}
					index++;
				}
				m_CycSubgrpsGen[power].push_back(*group_elements.begin());
			}
			//TODO
			std_ex::set_difference(group_elements, cyc_subgrp_elem);
		}

	};

	//check if a subgroup contains the element at prime power order
	bool Has_prime_pow_el(const cSubgroup<G> grp, const T element)const
	{
		std::size_t prime_index = 0;
		std::size_t elem_order = element.GetOrder();
		std::size_t prime = boost::math::prime(prime_index);
		while(prime <= elem_order)
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
		if(number == 2) return true;
		if(number == 1 || (number%2 == 0)) return false;
		for(int i=3; i*i<=number; i+=2)
		{
			if(number%i == 0)
				return false;
		}
		return true;
	}

private:
	G												m_Group;
	std::map<int, ElemVec>							m_CycSubgrpsGen;
	std::vector< std::vector< cSubgroup<G> > > 		m_Lattice;
	std::size_t 									m_Non_Triv_Layers;
};

#endif

