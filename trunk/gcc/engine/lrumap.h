#ifndef _LRUMAP_H
#define _LRUMAP_H

#include<boost/unordered_map.hpp>
#include <list>
#include <utility>


namespace resultsDB
{

/*!
 hashtable that implements a LRU strategy
 insert overwrites the oldest entry
*/
template <typename KEY, typename MAPPED>
class cLruHashMap
{
	typedef typename boost::unordered_map<KEY, typename std::list<std::pair<KEY, MAPPED> >::iterator >::const_iterator const_iter;

public:
	cLruHashMap(std::size_t size)
		:m_Size(size),
		m_Entries(0)
	{
		m_HashTable.max_load_factor(0.75);
		m_HashTable.rehash(m_Size);
	};

	~cLruHashMap()
	{
	};

	void resize(std::size_t size)
	{
		m_Size = size;	
		m_HashTable.rehash(m_Size);
	}

	void insert(KEY key, MAPPED& item)
	{
		m_ItemsList.push_front(std::make_pair(key, std::move(item)));
		m_HashTable[key] = m_ItemsList.begin();
		m_Entries++;
		if(m_Entries + 1 > m_Size)
		{
			//remove the oldest entry
			m_ItemsList.pop_back();
			m_HashTable.erase(m_ItemsList.back().first);
		}
	};

	const MAPPED &get(KEY key)const
	{
		typename std::list<std::pair<KEY, MAPPED> >::iterator item_iter = m_HashTable.at(key);
		//move item to the front of the list
		m_ItemsList.splice(m_ItemsList.begin(), m_ItemsList, item_iter);

		return item_iter->second;
	};

	std::size_t size()const
	{
		return m_Size;
	}

	const_iter find(KEY key)const
	{
		return m_HashTable.find(key);
	};
	
	const_iter end()const
	{
		return m_HashTable.end();
	};

private:
	std::size_t m_Size;
	std::size_t m_Entries;
	boost::unordered_map<KEY, typename std::list<std::pair<KEY, MAPPED> >::iterator> m_HashTable;
	mutable std::list<std::pair<KEY, MAPPED> > m_ItemsList;
};

}/////////////////end of namespace

#endif

