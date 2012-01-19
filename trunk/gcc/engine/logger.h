#ifndef _LOGGER_H
#define _LOGGER_H

#include <fstream>
#include <string>
#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/variant.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/thread.hpp>
#include <boost/current_function.hpp>

namespace engine
{

#define CONTEXT_STR std::string(BOOST_CURRENT_FUNCTION + std::string(" :: thread id:: ") + boost::lexical_cast<std::string>(boost::this_thread::get_id()) + " ")

#define GLOBAL_LOG_FILE "log.txt"
#define BUFFER_MAX_SIZE 1024

#define LOG_SEV_ERROR		1
#define LOG_SEV_WARNING		2
#define LOG_SEV_INFO		3


typedef boost::variant<int, std::string, std::exception, double> SupportedTypes;

//logger class -- implements the patterns STRATEGY
//and MONITOR OBJECT for synchronization
//buffer size used as an aproximation
class cLogger
{
public:
	cLogger(int severity, std::size_t buffersize = BUFFER_MAX_SIZE);
	~cLogger();

	const std::string &GetSeverity()const;
	std::size_t GetBufferSize()const;
	void SetBufferSize(std::size_t buffersize);

	cLogger& operator<<(SupportedTypes type_variant);

	static bool WriteToDisk(std::string &buffer);
private:
	std::string GetCurrentDate()const;

private:
	std::string m_Buffer;
	std::size_t m_BufferSize;
	static boost::mutex s_Mutex;
	std::string m_Severity;

};

}

#endif

