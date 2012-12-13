
#include "results_bucket.h"

#include <boost/scoped_ptr.hpp>
#include <boost/filesystem.hpp>
#include <cstdio>
#include <sstream>
#include <cmath>

#define MIN_DIRECTORY_SZ			256

namespace resultsDB
{

cResultsBucket::cResultsBucket(std::size_t code)
	:m_Code(code),
	m_End(0),
	m_HeaderEntry(nullptr),
	m_Entries(0)
{
	boost::iostreams::mapped_file_params params;
	std::stringstream converter;
	converter<<m_Code;
	params.path = DB_PATH + converter.str();
	params.length = FILE_SZ;
	params.mode = std::ios_base::in | std::ios_base::out;

	bool newfile = !boost::filesystem::exists(params.path);
	if(newfile)
		params.new_file_size = FILE_SZ; 
	m_MappedFile.open(params);
	if(!m_MappedFile.is_open())
		throw;

	if(newfile)	//clear file
	{
		memset(m_MappedFile.data(), 0, FILE_SZ);
		m_IndexBitsSz = (m_Code < MIN_DIRECTORY_SZ) ? 8 : std::log2(m_Code);
	}
	else
	{
		memcpy(&m_IndexBitsSz, m_MappedFile.data(), sizeof(unsigned short));
	}
	m_HeaderEntry = reinterpret_cast<bucket_header_entry*>(m_MappedFile.data() + sizeof(unsigned short));

	//count the number of entries
	while(m_Entries < MAX_ENTRIES && (m_HeaderEntry[m_Entries].hash != 0 && m_HeaderEntry[m_Entries].offset != 0))
		m_Entries++;

	//get the end of the file
	m_End = MAX_ENTRIES * sizeof(bucket_header_entry) + sizeof(unsigned short);
	if(m_Entries != 0)
		m_End = m_HeaderEntry[m_Entries - 1].offset + m_HeaderEntry[m_Entries - 1].length + 1;
};

cResultsBucket::~cResultsBucket()
{
	memcpy(m_MappedFile.data(),&m_IndexBitsSz, sizeof(unsigned short));
	m_MappedFile.close();
};

bool cResultsBucket::GetResult(const std::size_t hash, const std::string &params, std::string& result)const
{
	std::size_t idx = 0;
	while(idx < m_Entries)
	{
		if(hash == m_HeaderEntry[idx].hash)
		{
			if(0 == memcmp(params.data(), m_MappedFile.data() + m_HeaderEntry[idx].offset, params.size()))
			{
				//TODO - use a custom string class that avoids copy on construction
				result.assign(m_MappedFile.data() + m_HeaderEntry[idx].offset + params.size() + 1, m_HeaderEntry[idx].length - params.size());
				return true;
			}
		}
		idx++;
	}
	return false;
};

std::unique_ptr<cResultsBucket> cResultsBucket::SaveResult(const std::size_t hash, const std::string &params, const std::string& result)
{
	std::unique_ptr<cResultsBucket> newbucket = nullptr;
	if( (m_Entries + 1 >= MAX_ENTRIES) || (m_End + params.size() + result.size() + 1 > FILE_SZ) )
	{
		newbucket = Split();
	}
	else
	{
		//add entry
		bucket_header_entry new_entry = {hash, m_End, params.size() + result.size()};
		bucket_header_entry sentinel_entry = {0, 0, 0};
		memcpy(&m_HeaderEntry[m_Entries], &new_entry, sizeof(bucket_header_entry));
		m_Entries++;
		memcpy(&m_HeaderEntry[m_Entries], &sentinel_entry, sizeof(bucket_header_entry));

		//add entry data
		memcpy(m_MappedFile.data() + m_End, params.data(), params.size());
		m_End += params.size() + 1;
		memcpy(m_MappedFile.data() + m_End, result.data(), result.size());
		m_End += result.size() + 1;
	}
	return newbucket;
};


std::unique_ptr<cResultsBucket> cResultsBucket::Split()
{
	m_IndexBitsSz++;
	std::size_t code = GetFirstBits((1 << (m_IndexBitsSz -1)) | m_HeaderEntry[0].hash);
	std::unique_ptr<cResultsBucket> newbucket(new cResultsBucket(code));
	newbucket->m_IndexBitsSz = m_IndexBitsSz;

	//use this block to delete old_bucket in a natural way(by going out of scope)
	//before deleting the file from disk
	{
		cResultsBucket old_bucket(INT_MAX);
		old_bucket.m_IndexBitsSz = m_IndexBitsSz;
			
		for(std::size_t idx = 0; idx < m_Entries; idx++)	
		{
			std::string params(m_MappedFile.data() + m_HeaderEntry[idx].offset);
			std::string result(m_MappedFile.data() + m_HeaderEntry[idx].offset + params.size() + 1);
			if(true == GetIndexBit(m_HeaderEntry[idx].hash))
				newbucket->SaveResult(m_HeaderEntry[idx].hash, params, result);
			else
				old_bucket.SaveResult(m_HeaderEntry[idx].hash, params, result);
		}
		(*this) = old_bucket;
	}

	std::stringstream converter;
	converter << INT_MAX;
	std::string temp_file = DB_PATH + converter.str();
	boost::filesystem::path temp_path(temp_file);
	boost::filesystem::remove(temp_path);

	return newbucket;
};

cResultsBucket& cResultsBucket::operator=(const cResultsBucket& results_bucket)
{
	if(this != &results_bucket)
	{
		m_IndexBitsSz = results_bucket.m_IndexBitsSz;
		m_End = results_bucket.m_End;
		m_Entries = results_bucket.m_Entries;

		memset(m_MappedFile.data(), 0, FILE_SZ);
		memcpy(m_MappedFile.data(), results_bucket.m_MappedFile.data(), m_End);

		m_HeaderEntry = reinterpret_cast<bucket_header_entry*>(m_MappedFile.data() + sizeof(unsigned short));
	}
	return *this;
};



}////////////////end of namespace
