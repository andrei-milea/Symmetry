#include "logger.h"

namespace engine
{

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
	}

	cVariantVisitor(const cVariantVisitor& var_vis)
		:boost::static_visitor<>(var_vis)
	{
		m_pStr = new std::string(*var_vis.m_pStr);
	}

	~cVariantVisitor()
	{}

	void operator()(const int &integer)
	{
		(*m_pStr) += boost::lexical_cast<std::string>(integer);
	}

	void operator()(const double &real_num)
	{

		(*m_pStr) += boost::lexical_cast<std::string>(real_num);
	}

	void operator()(const std::exception &exception)
	{
		(*m_pStr) += exception.what();
	}

	void operator()(const std::string &message)
	{
		(*m_pStr) += message;
	}

private:
	std::string *m_pStr;
};


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

cLogger& cLogger::getInstance()
{
	static cLogger instance;
	return instance;
}

void cLogger::runLogLoop()
{
	m_Thread = new std::thread([this]()
		{
			std::ofstream file(m_LogFile, std::ios_base::out | std::ios_base::app);
			while(true)
				file << popLogMessage();
			file.close();
		});
}


void cLogger::pushLogMessage(const std::string&& message)
{
	std::unique_lock<std::mutex> mlock(m_Mutex);
	m_LogQueue.push(std::move(message));
	mlock.unlock();
	m_CondVar.notify_one();	
}

std::string cLogger::popLogMessage()
{
	std::unique_lock<std::mutex> mlock(m_Mutex);
	while(m_LogQueue.empty())
		m_CondVar.wait(mlock);
	std::string message = m_LogQueue.front();
	m_LogQueue.pop();
	return message;
}

void cLogger::print(SupportedTypes type_variant, int severity)
{
	std::string severity_str;
	//init severirity types
	if(LOG_SEV_INFO == severity)
	{
		severity_str = "INFO";
	}
	else
	{
		severity_str = (LOG_SEV_ERROR == severity) ? "ERROR" : "WARNING";
	}
	std::string message;
	cVariantVisitor variant_visitor(&message);
	boost::apply_visitor(variant_visitor, type_variant);
	std::string final_message = severity_str + " : " + GetCurrentDate() + " -- " + message + "\n";
	pushLogMessage(std::move(final_message));
}

}

