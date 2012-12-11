
#include "lrumap.h"

namespace resultsDB
{

cLruHashMap::cLruHashMap(std::size_t size)
	:m_Size(size),
	m_Entries(0)
{
	m_HashTable.max_load_factor(0.75);
	m_HashTable.rehash(m_Size);
};


cLruHashMap::~cLruHashMap()
{

};

void cLruHashMap::insert(KEY key, MAPPED& item)
{
	m_ItemsList.push_front(make_pair<KEY, MAPPED>(key, item));
	m_HashTable[key] = m_ItemsList.begin();
	m_Entries++;
	if(m_Entries + 1 > m_Size)
	{
		//remove the oldest entry
		m_ItemsList.pop_back();
		m_HashTable.erase(m_ItemsList.back().first);
	}
};

MAPPED& cLruHashMap::get(KEY key)const
{
	std::list<std::pair<KEY, MAPPED> >::iterator item_iter = m_HashTable[key];
	//move item to the front of the list
	m_ItemsList.slice(m_ItemsList.begin(), m_ItemsList, item_iter);

	return (*item_iter);
};

inline std::size_t cLruHashMap::size()const
{
	return m_Size;
}

const_iter cLruHashMap::find(KEY key)const
{
	return m_HashTable.find(key);
};

const_iter end()const
{
	return m_HashTable.end();
};

void cLruHashMap::resize(std::size_t size)
{
	m_Size = size;	
	m_HashTable.rehash(m_Size);
};

}///////////////////end of namespace


