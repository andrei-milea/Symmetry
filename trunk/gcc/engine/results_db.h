#ifndef _RESULTS_DB_H
#define _RESULTS_DB_H

#include "command_creator.h"
#include "results_bucket.h"
#include "lrumap.h"

#include <vector>
#include <tuple>
#include <memory>

namespace resultsDB
{

/*!
 database (based on dynamic hashing) for holding the results 
 of previously received commands -- SINGLETON
*/
class cResultsDB
{
public:
	bool GetResult(engine::COMMAND_TYPE command, const std::string &params, std::string &result);
	void SaveResult(engine::COMMAND_TYPE command, const std::string &params, const std::string& result);
	void SaveDB()const;
	static cResultsDB* GetInstance();
	
private:
	/////////////////singleton
	cResultsDB();	
	cResultsDB(const cResultsDB&);
	cResultsDB& operator=(const cResultsDB&);
	//////////////////////////
	
	std::size_t Hash(engine::COMMAND_TYPE command, const std::string &params)const
	{
		boost::hash<std::string> str_hash;
		std::size_t index = str_hash(params);
		index = index >> 5;
		index = index << 5;
		return index | command;
	};

	std::size_t GetFirstBits(const std::size_t hash)const
	{
		assert(m_IndexBitsSz > 0);
		return hash & ((1 << m_IndexBitsSz) - 1);
	};

private:
	unsigned int m_DirectorySz;		//m_DirectorySz = 2^m_IndexBitsSz
	unsigned short m_IndexBitsSz;
	std::vector<std::string> m_Directory;
	cLruHashMap<std::string, std::unique_ptr<cResultsBucket> > m_LruHashMap;
	static cResultsDB *s_Instance;
};

}//////////////end of namespace

#endif

