#ifndef _GROUP_RELATION_H
#define _GROUP_RELATION_H

#include <vector>
#include <utility>

template <typename T>
class cGroupRelation
{
public:
	cGroupRelation()
	{};
	~cGroupRelation()
	{};

	void AddElement(T &element, int power)
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

