#ifndef _RESULTS_BUCKET_H
#define _RESULTS_BUCKET_H

#include <boost/iostreams/device/mapped_file.hpp>
#include <string>


namespace resultsDB
{

#define DBIDX_FILENAME			"db.idx"
#define DB_PATH 				"resultsdb/"
#define FILE_SZ			 		1024
#define MAX_ENTRIES				20

/*!
 bucket for implementing the database(extendible hashing)
 that holds the result of presiously received commands
*/
class cResultsBucket
{
public:
	/*!
	 opens the memory mapped file with the specified name
	 if the newfile argument==true creates a new memory mapped file
	*/
	explicit cResultsBucket(std::string filename, unsigned short indexbits, bool newfile = false);
	~cResultsBucket();

	bool GetResult(const std::size_t hash, const std::string &params, std::string& result)const;

	unsigned short GetIndexBitsSz()const
	{
		return m_IndexBitsSz;
	};

	const std::string& GetFileName()const
	{
		return m_FileName;
	};

	/*!
 	 appends the result in the memory mapped file 
	 and returns a pointer to a new bucket if a split is needed
	 the new bucket contains the entries that have the next bit 1
	*/
	std::unique_ptr<cResultsBucket> SaveResult(const std::size_t hash, const std::string &params, const std::string& result);

private:	//too large to copy	
	cResultsBucket(const cResultsBucket&);

	//!!!!only used internally - keeps the same filename and copy only the contents
	cResultsBucket& operator=(const cResultsBucket&);	 

	std::unique_ptr<cResultsBucket> Split();
	bool GetIndexBit(const std::size_t hash)const
	{
		assert(m_IndexBitsSz > 0);
		return hash & (1 << (m_IndexBitsSz-1));
	};

	std::size_t GetFirstBits(const std::size_t hash)const
	{
		assert(m_IndexBitsSz > 0);
		return hash % (1 << m_IndexBitsSz);
	};

private:
	std::string m_FileName;
	boost::iostreams::mapped_file m_MappedFile;
	unsigned short m_IndexBitsSz;
	std::size_t m_End;

	struct bucket_header_entry
	{
		std::size_t hash;
		std::size_t offset;
		std::size_t length;
	};
	struct bucket_header_entry *m_HeaderEntry;
	std::size_t m_Entries;
};

}////////////////////end of namespace

#endif


