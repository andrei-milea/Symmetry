#ifndef CAYLEY_GRAPH_H_
#define CAYLEY_GRAPH_H_

#include <vector>
#include "group.h"


//implementation of a Cayley Graph
//used to represent an abbreviated 
//multiplication table
template <typename T, typename R>
class cCayleyGrf
{
typedef property<edge_index_t, T> edge_property;
typedef boost::adjacency_matrix<boost::undirectedS, no_property
    edge_property> Graph;
typedef typename graph_traits<Graph>::vertex_descriptor Vertex;


public:
	cCayleyGrf(std::vector<T> elements, std::vector<T> generators)
		:m_Elements(elements),
		m_Generators(generators),
		m_Graph(NULL)
	{};
	cCayleyGrf(cGroup<T, R> &group )
	{
		m_Elements = group.GetElementsDimino();
		m_Generators = group.GetGeneratorsSet();
	}
	~cCayleyGrf()
	{};


	void BuildGraph()
	{
		m_Graph = new Graph(m_Elements.size());
		std::size_t edge_id;
		for(std::vector<T>::iterator it_el = m_Elements.begin(); it_el!= m_Elements.end();
			   	it_el++)
		{
			for(std::vector<T>::iterator it_gen = m_Generators.begin();
			  it_gen != m_Generators.end(), it_gen++)
			{
				edge_property eprop(edge_id, *it_gen);
				add_edge(*it_el, T::BinOp((*it_el), (*it_gen)), eprop, m_Graph);
			}
		}
	};


	std::vector<T> GetRelations()
	{
		if(0 == m_Graph.size())
		{
			BuildGraph();
		}

		//build spanning tree


		//colour edges of the spanning tree`


	}



	GetGraph()const;
private:
	std::vector<T> m_Elements;
	std::vector<T> m_Generators;
	Graph		   *m_Graph;		
};


#endif

