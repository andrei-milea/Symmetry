#ifndef _GROUP_RELATION_H
#define _GROUP_RELATION_H

#include <vector>
#include <utility>
#include <iostream>

/*!
 group relation -> word corresponding to the identity element
 also corresponds a loop in the Cayley graph
*/
class cGroupRelation
{
public:
	cGroupRelation()
	{}
	~cGroupRelation()
	{}

	/*!
	  the element corresponds to the index of a generator of the group
	  in the generators set used to obtain the Cayley graph
	*/
	void AddElement(std::size_t element, int power)
	{
		m_Elements.push_back(std::pair<std::size_t, int>(element, power));
	}

	void Simplify()
	{
		for(std::size_t index = 0; index < m_Elements.size(); index++)
		{
			if(m_Elements.size() < 2)
				return;
			if(m_Elements[index].first == m_Elements[index+1].first)
			{
				m_Elements[index].second += m_Elements[index+1].second;
				m_Elements.erase(m_Elements.begin() + (index+1));
				index--;
			}
		}
	}

	std::vector<std::pair<std::size_t,int> >::iterator begin()
	{
		return m_Elements.begin();
	}

	std::vector<std::pair<std::size_t,int> >::iterator end()
	{
		return m_Elements.end();
	}

	friend std::ostream& operator<<(std::ostream& out, const cGroupRelation& relation)
	{
		//out<<"-> ";
		for(auto elem_iter = relation.m_Elements.begin(); elem_iter != relation.m_Elements.end(); elem_iter++)
		{
			if(elem_iter != relation.m_Elements.begin())
				out<<" \\cdot ";
			out<<"g_"<<elem_iter->first<<" ^ "<<elem_iter->second;

		}
		out<<"\n";
		return out;
	}


private:
	std::vector<std::pair<std::size_t,int> > m_Elements;
};

#endif

