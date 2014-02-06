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
#include <stack>

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
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS,
	        boost::no_property, std::pair<std::size_t, bool> > Graph;
	typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
	typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;
	typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
	typedef typename boost::graph_traits<Graph>::out_edge_iterator outEdge;
	typedef typename boost::graph_traits<Graph>::in_edge_iterator inEdge;

public:
	cCayleyGrf()
		:m_Graph(nullptr)
	{}

	cCayleyGrf(std::vector<ElemType> &elements, std::vector<ElemType> &generators)
		:m_Elements(elements),
		 m_Generators(generators),
		 m_Graph(nullptr)
	{}

	cCayleyGrf(G &group)
		:m_Graph(nullptr)
	{
		m_Elements = group.GetElementsDimino();
		m_Generators = group.GetGeneratorsSet();
	}

	~cCayleyGrf()
	{
		if(nullptr != m_Graph)
			delete m_Graph;
	}

	void initGraph(const std::vector<ElemType> &elements, const std::vector<ElemType> &generators)
	{
		m_Elements = elements;
		m_Generators = generators;
	}

	//copy constructor and assignment op
	cCayleyGrf(const cCayleyGrf &graph)
	{
		m_Elements = graph.m_Elements;
		m_Generators = graph.m_Generators;
		if(nullptr != graph.m_Graph)
			m_Graph = new Graph(*graph.GetGraph());
	}
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
	}

	/*!
	  builds the Cayle graph as and adjacency list: the nodes are the indexes
	  of the elements, the edges are the indexes of the generators
	  Complexity: O(n*m), where n is the number of generators and m
	  the number of elements
	*/
	void BuildGraph()
	{
		assert(nullptr == m_Graph);
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

				source = (*vertices(*m_Graph).first) + index_el;

				edge = add_edge(source, target, *m_Graph).first;
				(*m_Graph)[edge].first = index_gen;
				(*m_Graph)[edge].second = false;
			}
		}
	}

	/*!
	  extract the set of defining relations using Cannon's algorithm
	  with one stage see Butler - "Fundamental Algorithms for permutation groups"
	*/
	void BuildDefRelations()
	{
		assert(nullptr != m_Graph);


		std::vector<Edge> UncolouredEdges;
		std::vector<std::size_t> SpanningTree;
		SpanningTree.resize(boost::num_vertices(*m_Graph));
		//colour edges of the spanning tree
		cColourEdgesVis<Edge, Graph > colour_visitor(UncolouredEdges, SpanningTree);
		boost::depth_first_search((*m_Graph), boost::visitor(colour_visitor));

		//while there are uncoloured edges
		for(auto edges_it = UncolouredEdges.begin(); edges_it != UncolouredEdges.end(); edges_it++)
		{
			if(false == (*m_Graph)[*edges_it].second) //if edge is not coloured
			{
				Add_DefRelation(*edges_it, SpanningTree);
				(*m_Graph)[*edges_it].second = true;	//colour edge

				//determine all deductions
				TraceRelations();
			}
		}
	}

	//output operator overloaded
	friend std::ostream& operator<<(std::ostream& out, const cCayleyGrf &graph)
	{
		//print graph
		boost::print_graph(*graph.GetGraph());

		//print edges
		out<<"\nEDGES:\n";
		for(std::size_t index_gen = 0; index_gen < graph.m_Generators.size(); index_gen++)
		{
			out<<"edge "<<index_gen<< " :\n"<<graph.m_Generators[index_gen];
		}

		//print vertices
		out<<"\nVERTICES:\n";
		for(std::size_t index_el = 0; index_el < graph.m_Elements.size(); index_el++)
		{
			out<<"vertex "<<index_el<< " :\n"<<graph.m_Elements[index_el];
		}


		return out;
	}

	const std::vector<cGroupRelation>& GetDefRelations()const
	{
		return m_DefRelations;
	}

	/*!
	  returns the underlying graph representation (adjacency list)
	*/
	Graph* GetGraph()const
	{
		return m_Graph;
	}

private:
	/*!
	  add the defining relation corresponding to the given vertex
	  to the set of defining relations
	*/
	void Add_DefRelation(const Edge &edge, std::vector<std::size_t> &spanning_tree)
	{
		cGroupRelation new_relation;
		std::size_t src_index = boost::source(edge, *m_Graph);
		std::size_t tgt_index = boost::target(edge, *m_Graph);
		std::stack<Edge> edges_stack;
		while(0 != spanning_tree[src_index])
		{
			edges_stack.push(boost::edge(spanning_tree[src_index], src_index, *m_Graph).first);
			src_index = spanning_tree[src_index];
		}
		if(spanning_tree[src_index] != src_index)
			edges_stack.push(boost::edge(spanning_tree[src_index], src_index, *m_Graph).first);
		while(!edges_stack.empty())
		{
			new_relation.AddElement((*m_Graph)[edges_stack.top()].first, 1);
			edges_stack.pop();
		}
		new_relation.AddElement((*m_Graph)[edge].first, 1);
		while(0 != spanning_tree[tgt_index])
		{
			new_relation.AddElement((*m_Graph)[boost::edge(spanning_tree[tgt_index], tgt_index, *m_Graph).first].first, -1);
			tgt_index = spanning_tree[tgt_index];
		}
		if(tgt_index != spanning_tree[tgt_index])
			new_relation.AddElement((*m_Graph)[boost::edge(spanning_tree[tgt_index], tgt_index, *m_Graph).first].first, -1);
		m_DefRelations.push_back(new_relation);
	}

	/*!
	  trace the relations around all the nodes in the graph
	  and colour the appropriate edges (if loop contains exactly one uncoloured edge)
	*/
	void TraceRelations()
	{
		bool coloured = true;
		while(coloured)
		{
			coloured = false;
			for(auto rel_it = m_DefRelations.begin(); rel_it != m_DefRelations.end(); rel_it++)
			{
				std::pair<VertexIterator, VertexIterator> vertex_it = boost::vertices(*m_Graph);
				for( ; vertex_it.first != vertex_it.second; vertex_it.first++)
				{
					Vertex vert_follower = *vertex_it.first;
					unsigned int found_edges = 0;
					Edge found_edge;
					for(auto word_it = rel_it->begin(); word_it != rel_it->end(); word_it++)
					{
						if(1 == word_it->second)
						{
							outEdge found_it, out_it, out_it_end; 
							tie(out_it, out_it_end) = boost::out_edges(vert_follower, *m_Graph);
							for( ; out_it != out_it_end; out_it++)
							{
								if((*m_Graph)[*out_it].first == word_it->first)
									break;
							}
							if(out_it != out_it_end)
							{
								if(false == (*m_Graph)[*out_it].second)
								{
									found_edge = *out_it;
									found_edges++;
								}
								vert_follower = boost::target(*out_it, *m_Graph);
							}
						}
						else
						{
							assert(-1 == word_it->second);
							inEdge found_it, in_it, in_it_end; 
							tie(in_it, in_it_end) = boost::in_edges(vert_follower, *m_Graph);
							for( ; in_it != in_it_end; in_it++)
							{
								if((*m_Graph)[*in_it].first == word_it->first)
									break;
							}
							if(in_it != in_it_end)
							{
								if(false == (*m_Graph)[*in_it].second)
								{
									found_edge = *in_it;
									found_edges++;
								}
								vert_follower = boost::source(*in_it, *m_Graph);
							}
						}
					}
					if(1 == found_edges)		//colour edge
					{
						(*m_Graph)[found_edge].second = true;
						coloured = true;
					}
				}
			}
		}
	}

	//inner class that colours the edges in the spanning tree used in
	//the colouring algorithm  to obtain a set of defining relations
	//inherits from boost::default_dfs_visitor
	template <typename E, typename Grf>
	class cColourEdgesVis : public boost::default_dfs_visitor
	{
	public:
		cColourEdgesVis(std::vector<E> &uncol_edges, std::vector<std::size_t> &spanning_tree)
			:m_UncolouredEdges(uncol_edges),
			m_SpanningTree(spanning_tree)
		{
			//root is it's own predecesor
			m_SpanningTree.push_back(0);
		}
		~cColourEdgesVis()		{};

		void tree_edge(E edge, const Grf& graph)
		{
			//found edge in the spaning tree -> colour edge
			(*const_cast<Grf*>(&graph))[edge].second = true;
			m_SpanningTree[boost::target(edge, graph)] = boost::source(edge, graph);
		}

		void back_edge(E edge, const Grf& graph)
		{
			//found edge not in the spaning tree
			//add it to the list of uncoloured edges
			m_UncolouredEdges.push_back(edge);
		}

		void forward_or_cross_edge(E edge, const Grf& graph)
		{
			//found edge not in the spaning tree
			//add it to the list of uncoloured edges
			m_UncolouredEdges.push_back(edge);
		}

	private:
		std::vector<E> &m_UncolouredEdges;
		std::vector<std::size_t> &m_SpanningTree;
	};


private:
	std::vector<ElemType> m_Elements;
	std::vector<ElemType> m_Generators;
	Graph				  *m_Graph;
	std::vector<cGroupRelation> m_DefRelations;
};

#endif

