
#include "results_db.h"

#include <boost/functional/hash.hpp>

#define MAX_CACHE_SZ	10

namespace resultsDB
{

cResultsDB* cResultsDB::s_Instance = nullptr;

cResultsDB::cResultsDB()
	:m_DirectorySz(2),
	m_IndexBitsSz(1),
	m_LruHashMap(MAX_CACHE_SZ)
{
	std::ifstream idx_file;
	std::string file_path = std::string(DB_PATH) + DBIDX_FILENAME;
	idx_file.open(file_path, std::ifstream::in | std::ifstream::out);
	if(!idx_file.is_open())
		throw;

	//read directory from idx file
	std::string bucket_name;
	while(getline(idx_file, bucket_name))
	{
		m_Directory.push_back(bucket_name);
	}
	if(!idx_file.eof())
		throw;

	if(m_Directory.empty())
	{
		std::string bucket0 = "0";
		std::string bucket1 = "1";
		std::unique_ptr<cResultsBucket> results_bucket0(new cResultsBucket(bucket0, m_IndexBitsSz, true));
		m_LruHashMap.insert(bucket0, results_bucket0);
		std::unique_ptr<cResultsBucket> results_bucket1(new cResultsBucket(bucket1, m_IndexBitsSz, true));
		m_LruHashMap.insert(bucket1, results_bucket1);
	}
};

void cResultsDB::SaveDB()const
{
	std::ofstream idx_file;
	idx_file.open(std::string(DB_PATH) + DBIDX_FILENAME, std::ifstream::out);
	if(!idx_file.is_open())
		throw;
	//write directory to idx file
	for(auto it = m_Directory.begin(); it != m_Directory.end(); it++)
	{
		idx_file<<*it<<"\n";
	}
};
	
cResultsDB* cResultsDB::GetInstance()
{
	if(nullptr == s_Instance)
		s_Instance = new cResultsDB;
	return s_Instance;
};

bool cResultsDB::GetResult(engine::COMMAND_TYPE command, const std::string &params, std::string &result)
{
	std::size_t index = GetFirstBits(Hash(command, params));
	std::string bucket_filename = m_Directory.at(index);
	auto bucket_iter = m_LruHashMap.find(bucket_filename);
	if(bucket_iter == m_LruHashMap.end())
	{
		//load the bucket from the disk
		std::unique_ptr<cResultsBucket> results_bucket (new cResultsBucket(bucket_filename, m_IndexBitsSz));
		m_LruHashMap.insert(bucket_filename, results_bucket);
		return results_bucket->GetResult(command, params, result);
	} 
	return (*bucket_iter).second->second->GetResult(command, params, result);
};

void cResultsDB::SaveResult(engine::COMMAND_TYPE command, const std::string &params, const std::string& result)
{
	const std::size_t hash = Hash(command, params);
	std::size_t index = GetFirstBits(hash);
	std::string bucket_filename;
	std::unique_ptr<cResultsBucket> results_bucket;
	bucket_filename = m_Directory.at(index);
	auto bucket_it = m_LruHashMap.find(bucket_filename);
	std::unique_ptr<cResultsBucket> newbucket;
	if(bucket_it == m_LruHashMap.end())
	{
		//load the bucket from the disk
		std::unique_ptr<cResultsBucket> results_bucket(new cResultsBucket(bucket_filename, m_IndexBitsSz));
		m_LruHashMap.insert(bucket_filename, results_bucket);
		newbucket = std::unique_ptr<cResultsBucket>(results_bucket->SaveResult(hash, params, result));
	}
	else
	{
		newbucket = std::unique_ptr<cResultsBucket>((*bucket_it).second->second->SaveResult(hash, params, result));
	}
	if(newbucket != nullptr)
	{
		m_LruHashMap.insert(newbucket->GetFileName(), newbucket);
		if(newbucket->GetIndexBitsSz() == m_IndexBitsSz)
		{
			m_Directory[(index | (1 << m_IndexBitsSz))] = newbucket->GetFileName();
		}
		else if(newbucket->GetIndexBitsSz() > m_IndexBitsSz)
		{
			//need to double the size of the hash table	
			m_IndexBitsSz++;
			std::size_t old_size = m_Directory.size();
			m_Directory.resize(2* old_size);
			m_Directory[(index | (1 << m_IndexBitsSz))] = newbucket->GetFileName();
			//link the new entries in the directory to the existing buckets
			std::size_t old_idx = 0;
			for(std::size_t idx = old_size; idx < m_Directory.size(); idx++)
			{
				if(idx != (index | (1 << m_IndexBitsSz)))
				{
					if(old_idx != index )	
					{
						m_Directory[idx] = m_Directory[old_idx];
						old_idx++;

					}
					else
					{
						old_idx++;
						m_Directory[idx] = m_Directory[old_idx];
						old_idx++;
					}
				}
			}
		}
		else
		{
			//we never decrease the size(delete items) so this should never happen
			assert(false);
		}
	}
};



}/////////////////////end of namespace

