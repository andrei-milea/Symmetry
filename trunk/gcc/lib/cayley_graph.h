#ifndef CAYLEY_GRAPH_H_
#define CAYLEY_GRAPH_H_

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <vector>
#include <algorithm>
#include <cassert>
#include <utility>
#include <string>
#include "group.h"


//implementation of a Cayley Graph
//used to represent an abbreviated 
//multiplication table
//template must be instantiated with a group type
template <typename G>
class cCayleyGrf
{
public:
	typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, 
    		ElemType, std::pair<ElemType,bool> > Graph;
	typedef typename G::ElementType ElemType;
	typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
	typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;
	typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;

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
		return *this;
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

	//extract the set of defining relations
	void BuildDefRelations()
	{
		assert(NULL == m_Graph);

		//colour edges of the spanning tree
		cColourEdgesVis colour_visitor;
		boost::depth_first_search((*m_Graph), boost::visitor(colour_visitor));
		for(std::vector<Edge>::iterator edges_it = colour_visitor.GetUncolouredEdges().begin();
				edges_it != colour_visitor.GetUncolouredEdges().end(); edges_it++)
		{
			if(false == m_Graph[*edges_it].second) //if edge is not coloured
			{
				Add_DefRelation(m_Graph[*edge_it]);
				m_Graph[*edge_it].second = true;	//colour edge
				for(std::vector<cRelation>::iterator relation_it = m_DefRelations.begin();
						relation_it != m_DefRelations.end(); relation_it++)
				{
					for(VertexIterator vertex_it = boost::vertices(*m_Graph).begin();
							vertex_it != boost::vertices(*m_Graph).end(); vertex_it++)
					{
						//trace relation around vertex

					}

				}
			}
		}
	};


	//output operator overloaded
	friend std::ostream& operator<<(std::ostream& out, const cCayleyGrf &graph)
	{
		//print graph
		out<<"GRAPH:\n";
		boost::print_graph(*graph.GetGraph());
		
		//print edges
		out<<"\nEDGES:\n";
		boost::print_edges(*graph.GetGraph(), get(boost::vertex_bundle,
					*graph.GetGraph()));

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

	const std::vector<cRelation>& GetDefRelations()const
	{
		return m_DefRelations;
	};

	Graph* GetGraph()const
	{
		if(NULL != m_Graph)
			return m_Graph;
		else throw;
	};

private:
	void Add_DefRelation(const Edge &edge)
	{

	};
	//inner class that colours the edges in the spanning tree used in
	//the colouring algorithm  to obtain a set of defining relations
	//inherits from boost::default_dfs_visitor
	class cColourEdgesVis : boost::default_dfs_visitor
	{
	public:
		cColourEdgesVis()		{};
		~cColourEdgesVis()		{};

		template <typename EDGE, typename GRF>
		void tree_edge(EDGE edge, const GRF& graph)
		{
			//found edge in the spaning tree -> colour edge
			edge.second = true;
		};

		void non_tree_edge(EDGE edge, const GRF& graph)
		{
			//found edge not in the spaning tree
			//add it to the list of uncoloured edges 
			m_UncolouredEdges.push_back(edge);
		};

		std::vector<EDGES> &GetUncolouredEdges()
		{
			return m_UncolouredEdges;
		};

	private:
		std::vector<EDGE> m_UncolouredEdges;
	};


private:
	std::vector<ElemType> m_Elements;
	std::vector<ElemType> m_Generators;
	Graph				  *m_Graph;		
	std::vector<cRelation> m_DefRelations;
};

template <typename T>
class cRelation
{
public:
	cRelation()
	{};
	~cRelation()
	{};


	void AddElement(T element, int power)
	{
		m_Elements.push_back(std::pair<T, int>(element, power));
	};

	void Simplify()
	{
		for(std::size_t index = 0; index < m_Elements.size(); index++)
		{
			if(m_Elements[index].first == m_Elements[index+1].first)
			{
				m_Elements[index].second += m_Elements[index+1].second;
				m_Elements.erase(m_Elements.begin() + (index+1));
			}
		}

	};

private:
	std::vector<std::pair<T,int> > m_Elements;
};


#endif

