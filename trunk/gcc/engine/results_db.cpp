
#include "results_db.h"

#include <boost/functional/hash.hpp>
#include <cmath>

#define MAX_CACHE_SZ				5	
#define MIN_DIRECTORY_SZ			256

namespace resultsDB
{

cResultsDB* cResultsDB::s_Instance = nullptr;

cResultsDB::cResultsDB()
	:m_DirectorySz(MIN_DIRECTORY_SZ),
	m_IndexBitsSz(8),
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
		m_Directory.resize(MIN_DIRECTORY_SZ);
		for(std::size_t idx = 0; idx < MIN_DIRECTORY_SZ; idx++)
		{
			std::stringstream converter;
			converter<<GetFirstBits(idx);
			std::unique_ptr<cResultsBucket> results_bucket(new cResultsBucket(converter.str(), m_IndexBitsSz, true));
			m_Directory.at(GetFirstBits(idx)) = converter.str();
		}
	}
	else
	{
		assert( 0 == (m_Directory.size() & (m_Directory.size() - 1)) );
		m_IndexBitsSz = std::log2(m_Directory.size());
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
	std::size_t hash = Hash(command, params);
	std::size_t index = GetFirstBits(hash);
	std::string bucket_filename = m_Directory.at(index);
	auto bucket_iter = m_LruHashMap.find(bucket_filename);
	if(bucket_iter == m_LruHashMap.end())
	{
		//load the bucket from the disk
		std::unique_ptr<cResultsBucket> results_bucket (new cResultsBucket(bucket_filename, m_IndexBitsSz));
		m_LruHashMap.insert(bucket_filename, results_bucket);
		return results_bucket->GetResult(hash, params, result);
	} 
	return (*bucket_iter).second->second->GetResult(hash, params, result);
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
		newbucket = std::unique_ptr<cResultsBucket>(results_bucket->SaveResult(hash, params, result));
		m_LruHashMap.insert(bucket_filename, results_bucket);
	}
	else
	{
		newbucket = std::unique_ptr<cResultsBucket>((*bucket_it).second->second->SaveResult(hash, params, result));
	}
	if(newbucket != nullptr)
	{
		if(newbucket->GetIndexBitsSz() <= m_IndexBitsSz)
		{
			assert(m_IndexBitsSz > 0);
			m_Directory.at(index | (1 << (m_IndexBitsSz - 1))) = newbucket->GetFileName();
		}
		else if(newbucket->GetIndexBitsSz() > m_IndexBitsSz)
		{
			//need to double the size of the hash table	
			m_IndexBitsSz++;
			assert(m_IndexBitsSz < 64);
			std::size_t old_size = m_Directory.size();
			m_Directory.resize(2* old_size);
			assert(m_IndexBitsSz > 0);
			//link the new entries in the directory to the existing buckets
			for(std::size_t idx = old_size; idx < m_Directory.size(); idx++)
			{
				m_Directory[idx] = m_Directory[idx - old_size];
			}
			//overwrite the new entry
			m_Directory.at(index | (1 << (m_IndexBitsSz - 1))) = newbucket->GetFileName();
		}
		m_LruHashMap.insert(newbucket->GetFileName(), newbucket);
		SaveResult(command, params, result);
	}
};



}/////////////////////end of namespace

