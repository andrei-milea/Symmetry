#include "logger.h"

namespace engine
{

boost::mutex cLogger::s_Mutex;

/*!
  class implementing the strategy pattern in order 
  interpret different types of objects as errors
*/
class cVariantVisitor : public boost::static_visitor<>
{
public:
	cVariantVisitor(std::string *str)
		:m_pStr(str)
	{
	};

	~cVariantVisitor()
	{};

	void operator()(const int &integer)
	{
		(*m_pStr) += boost::lexical_cast<std::string>(integer);
	};

	void operator()(const double &real_num)
	{

		(*m_pStr) += boost::lexical_cast<std::string>(real_num);
	};

	void operator()(const std::exception &exception)
	{
		(*m_pStr) += exception.what();
	};

	void operator()(const std::string &message)
	{
		(*m_pStr) += message;
	};

private:
	std::string *m_pStr;
};



cLogger::cLogger(int severity = LOG_SEV_ERROR)
{
	//init severirity types
	if(LOG_SEV_INFO == severity)
	{
		m_Severity = "INFO";
	}
	else
	{
		m_Severity = (LOG_SEV_ERROR == severity) ? "ERROR" : "WARNING";
	}
};


cLogger::~cLogger()
{};

const std::string& cLogger::GetSeverity()const
{
	return m_Severity;
};

cLogger& cLogger::operator<<(SupportedTypes type_variant)
{
	std::string message;
	std::string final_message;
	cVariantVisitor variant_visitor(&message);
	boost::apply_visitor(variant_visitor, type_variant);
	final_message += m_Severity + " : " + GetCurrentDate() + " -- " + message + "\n";

	//write to disk
	boost::mutex::scoped_lock lock(cLogger::s_Mutex);
	std::ofstream file(GLOBAL_LOG_FILE, std::ios_base::out | std::ios_base::app);
	file<<final_message;
	file.close();
	return *this;
};

std::string cLogger::GetCurrentDate()const
{
	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
	return boost::posix_time::to_simple_string(now);
};



}

