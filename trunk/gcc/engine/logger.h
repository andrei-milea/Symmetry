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

#define GLOBAL_LOG_FILE "/var/log/symmetry_log.txt"

#define LOG_SEV_ERROR		1
#define LOG_SEV_WARNING		2
#define LOG_SEV_INFO		3


typedef boost::variant<int, std::string, std::exception, double> SupportedTypes;

/*
   TODO -- make it a singleton
   logger class -- implements the pattern MONITOR OBJECT for synchronization
   writes log to GLOBAL_LOG_FILE
*/
class cLogger
{
public:
	cLogger(int severity);
	~cLogger();

	const std::string &GetSeverity()const;

	cLogger& operator<<(SupportedTypes type_variant);

private:
	std::string GetCurrentDate()const;

private:
	static boost::mutex s_Mutex;
	std::string m_Severity;

};

}

#endif

