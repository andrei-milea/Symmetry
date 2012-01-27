#ifndef CAYLEY_GRAPH_H_
#define CAYLEY_GRAPH_H_

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/optional.hpp>
#include <vector>
#include <algorithm>
#include <cassert>
#include <utility>
#include <string>

#include "group.h"
#include "group_relation.h"


/*!
  implementation of a Cayley Graph(used to represent an abbreviated multiplication table)
  template must be instantiated with a group type
  uses Boost Graph Library for graph representation as an adjacency list
*/
template <typename G>
class cCayleyGrf
{
public:
	typedef typename G::ElementType ElemType;
	typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS,
	        ElemType, std::pair<ElemType,bool> > Graph;
	typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
	typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;
	typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;

public:
	cCayleyGrf(std::vector<ElemType> &elements, std::vector<ElemType> &generators)
		:m_Elements(elements),
		 m_Generators(generators),
		 m_Graph(nullptr)
	{};

	cCayleyGrf(G &group )
		:m_Graph(nullptr)
	{
		m_Elements = group.GetElementsDimino();
		m_Generators = group.GetGeneratorsSet();
	};

	~cCayleyGrf()
	{
		if(nullptr != m_Graph)
			delete m_Graph;
	};

	//copy constructor and assignment op
	cCayleyGrf(const cCayleyGrf &graph)
	{
		m_Elements = graph.m_Elements;
		m_Generators = graph.m_Generators;
		if(nullptr != graph.m_Graph)
			m_Graph = new Graph(*graph.GetGraph());
	};
	cCayleyGrf &operator=(const cCayleyGrf &graph)
	{
		if(this != &graph)
		{
			m_Elements = graph.m_Elements;
			m_Generators = graph.m_Generators;
			if(nullptr != graph.m_Graph)
				m_Graph = new Graph(*graph.GetGraph());
			return *this;
		}
	};

	/*!
	  builds the Cayle graph as and adjacency list: the nodes are the indexes
	  of the elements, the edges are the indexes of the generators
	  Complexity: O(n*m), where n is the number of generators and m
	  the number of elements
	*/
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
				Vertex source, target;
				Edge edge;

				target = (*vertices(*m_Graph).first) +
				         (std::find(m_Elements.begin(), m_Elements.end(), result) - m_Elements.begin());

				//set bundle vertices properties
				source = (*vertices(*m_Graph).first) + index_el;
				(*m_Graph)[source] = m_Elements[index_el];
				(*m_Graph)[target] = result;

				edge = add_edge(source, target, *m_Graph).first;
				(*m_Graph)[edge].first = m_Generators[index_gen];
				(*m_Graph)[edge].second = false;
			}
		}
	};

	/*!
	  extract the set of defining relations using Cannon's algorithm
	  with one stage see Butler - "Fundamental Algorithms for permutation groups"
	*/
	void BuildDefRelations()
	{
		assert(nullptr == m_Graph);

		//colour edges of the spanning tree
		cColourEdgesVis<Edge, Graph> colour_visitor;
		boost::depth_first_search((*m_Graph), boost::visitor(colour_visitor));

		//while there are uncoloured edges
		for(auto edges_it = colour_visitor.GetUncolouredEdges().begin();
		        edges_it != colour_visitor.GetUncolouredEdges().end(); edges_it++)
		{
			if(false == m_Graph[*edges_it].second) //if edge is not coloured
			{
				Add_DefRelation(*edges_it);
				m_Graph[*edges_it].second = true;	//colour edge

				//determine all deductions
				bool new_edges_coloured = true;
				while(new_edges_coloured)
				{
					for(auto relation_it = m_DefRelations.begin();
					        relation_it != m_DefRelations.end(); relation_it++)
					{
						for(VertexIterator vertex_it = boost::vertices(*m_Graph).begin();
						        vertex_it != boost::vertices(*m_Graph).end(); vertex_it++)
						{
							//trace relation around vertex
							//TODO

						}
					}
				}
			}
		}
	};


	//output operator overloaded
	friend std::ostream& operator<<(std::ostream& out, const cCayleyGrf &graph)
	{
		//print graph
		boost::print_graph(*graph.GetGraph());

//		//print edges
//		out<<"\nEDGES:\n";
//		boost::print_edges(*graph.GetGraph(), get(boost::vertex_bundle,
//					*graph.GetGraph()));
//
//		//print vertices
//		out<<"\nVERTICES:\n";
//		boost::print_vertices((*graph.GetGraph()), get(boost::vertex_bundle,
//					*graph.GetGraph()));
//
		return out;
	};

	const std::vector< cGroupRelation<ElemType> >& GetDefRelations()const
	{
		return m_DefRelations;
	};

	/*!
	  returns the underlying graph representation (adjacency list)
	*/
	Graph* GetGraph()const
	{
		return m_Graph;
	};

private:
	/*!
	  add the defining relation corresponding to the given vertex
	  to the set of defining relations
	  TODO -- finish this method
	*/
	void Add_DefRelation(const Edge &edge)
	{
		cGroupRelation<ElemType> new_relation;
		new_relation.AddElement();
	};
	//inner class that colours the edges in the spanning tree used in
	//the colouring algorithm  to obtain a set of defining relations
	//inherits from boost::default_dfs_visitor

	template <typename E, typename Grf>
	class cColourEdgesVis : boost::default_dfs_visitor
	{
	public:
		cColourEdgesVis()		{};
		~cColourEdgesVis()		{};

		void tree_edge(E edge, const Grf& graph)
		{
			//found edge in the spaning tree -> colour edge
			edge.second = true;
		};

		void non_tree_edge(E edge, const Grf& graph)
		{
			//found edge not in the spaning tree
			//add it to the list of uncoloured edges
			m_UncolouredEdges.push_back(edge);
		};

		/*!
		  returns the edges that are not contained in the spanning tree
		  (that are not coloured)
		*/
		std::vector<E&> &GetUncolouredEdges()
		{
			return m_UncolouredEdges;
		};

	private:
		std::vector<E&> m_UncolouredEdges;
	};


private:
	std::vector<ElemType> m_Elements;
	std::vector<ElemType> m_Generators;
	Graph				  *m_Graph;
	std::vector<cGroupRelation<ElemType> > m_DefRelations;
};

#endif

