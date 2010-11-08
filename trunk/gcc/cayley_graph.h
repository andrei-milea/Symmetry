#ifndef CAYLEY_GRAPH_H_
#define CAYLEY_GRAPH_H_

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <vector>
#include <algorithm>
#include <cassert>
#include "group.h"


//implementation of a Cayley Graph
//used to represent an abbreviated 
//multiplication table
//template must be instantiated with a group type
template <typename G>
class cCayleyGrf
{
public:
	typedef typename G::ElementType ElemType;
	typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, 
    	ElemType, ElemType> Graph;
	typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
	typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;

public:
	cCayleyGrf(std::vector<ElemType> &elements, std::vector<ElemType> &generators)
		:m_Elements(elements),
		m_Generators(generators),
		m_Graph(NULL)
	{};

	cCayleyGrf(G &group )
		:m_Graph(NULL)
	{
		m_Elements = group.GetElementsDimino();
		m_Generators = group.GetGeneratorsSet();
	};

	~cCayleyGrf()
	{
		if(NULL != m_Graph)
			delete m_Graph;
	};

	//copy constructor and assignment op
	cCayleyGrf(const cCayleyGrf &graph)
	{
		m_Elements = graph.GetElements();
		m_Generators = graph.GetGenerators();
		m_Graph = new Graph(graph.GetGraph());
	};

	cCayleyGrf &operator=(const cCayleyGrf &graph)
	{
		m_Elements = graph.GetElements();
		m_Generators = graph.GetGenerators();
		m_Graph = new Graph(graph.GetGraph());
	};

	void BuildGraph()
	{
		m_Graph = new Graph(m_Elements.size());

		//add edges
		for(std::size_t index_gen = 0; index_gen < m_Generators.size(); index_gen++)
		{
			for(std::size_t index_el = 0; index_el < m_Elements.size(); index_el++)
			{
				ElemType result = m_Elements[index_el].GetBinaryOp()(m_Elements[index_el],
						m_Generators[index_gen]);
				
				assert(m_Elements.end() != std::find(m_Elements.begin(),
						  m_Elements.end(), result));
				typename Graph::vertex_descriptor source, target;
				target = (*vertices(*m_Graph).first) + 
				 (std::find(m_Elements.begin(), m_Elements.end(), result) - m_Elements.begin());

				//set bundle vertices properties	
				source = (*vertices(*m_Graph).first) + index_el; 
				(*m_Graph)[source] = m_Elements[index_el];
				(*m_Graph)[target] = result;

				add_edge(source, target, *m_Graph);
			}
		}
	};


//	std::vector<T> GetRelations()
//	{
//		if(NULL == m_Graph)
//		{
//			BuildGraph();
//		}
//		else
//		{
//		}
//
//		//colour edges of the spanning tree`
//	};


	//output operator overloaded
	friend std::ostream& operator<<(std::ostream& out, const cCayleyGrf &graph)
	{
		//print graph
		out<<"GRAPH:\n";
		boost::print_graph(*graph.GetGraph());
		
//		//print edges
//		out<<"\nEDGES:\n";
//		boost::print_edges(*graph.GetGraph(), get(boost::vertex_bundle,
//					*graph.GetGraph()));

		//print vertices
		out<<"\nVERTICES:\n";
		boost::print_vertices((*graph.GetGraph()), get(boost::vertex_bundle,
					*graph.GetGraph()));

		return out;
	};

	//getters
	std::vector<ElemType>& GetElements()const
	{
		return m_Elements;
	};

	std::vector<ElemType>& GetGenerators()const
	{
		return m_Generators;
	};

	Graph* GetGraph()const
	{
		if(NULL != m_Graph)
			return m_Graph;
		else throw;
	};

private:
	std::vector<ElemType> m_Elements;
	std::vector<ElemType> m_Generators;
	Graph		   *m_Graph;		
};


#endif

