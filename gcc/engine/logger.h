#ifndef _LOGGER_H
#define _LOGGER_H

#include <fstream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>

#include <boost/lexical_cast.hpp>
#include <boost/variant.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/current_function.hpp>

namespace engine
{

#define CONTEXT_STR std::string(BOOST_CURRENT_FUNCTION + std::string(" :: thread id:: ") + boost::lexical_cast<std::string>(std::this_thread::get_id()) + " ")

#define LOG_SEV_ERROR		1
#define LOG_SEV_WARNING		2
#define LOG_SEV_INFO		3


typedef boost::variant<int, std::string, std::exception, double> SupportedTypes;

/*
   logger class -- uses a synchronized queue and runs in its own thread
   the log file must be set and the logging thread must be start before logging messages
*/
class cLogger
{
public:
	static cLogger& getInstance();

	void setLogFile(const std::string& logfile)
	{
		m_LogFile = logfile;
	}

	const std::string &GetLogFile()const
	{
		return m_LogFile;
	}

	void print(SupportedTypes type_variant, int severity = LOG_SEV_ERROR);

	void runLogLoop();

private:
	std::string GetCurrentDate()const
	{
		boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
		return boost::posix_time::to_simple_string(now);
	}

	cLogger()
		:m_Thread(nullptr)
	{}

	void pushLogMessage(const std::string&&);
	std::string popLogMessage();

private:
	std::queue<std::string> m_LogQueue;
	std::string m_LogFile;
	std::mutex m_Mutex;
	std::condition_variable m_CondVar;
	std::thread *m_Thread;
};

}

#endif

