#include "logger.h"

boost::mutex cLogger::s_Mutex;

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



cLogger::cLogger(int severity = LOG_SEV_ERROR, std::size_t buffersize)
	:m_BufferSize(buffersize)
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
{
	if(m_Buffer.size() >= 0)
		cLogger::WriteToDisk(m_Buffer);
};

const std::string& cLogger::GetSeverity()const
{
	return m_Severity;
};
	
std::size_t cLogger::GetBufferSize()const
{
	return m_BufferSize;
};

void cLogger::SetBufferSize(std::size_t buffersize)
{
	m_BufferSize = buffersize;
};

cLogger& cLogger::operator<<(SupportedTypes type_variant)
{
	if(m_Buffer.size() >= m_BufferSize)
		cLogger::WriteToDisk(m_Buffer);

	std::string message;
	cVariantVisitor variant_visitor(&message);
	boost::apply_visitor(variant_visitor, type_variant);
	m_Buffer += m_Severity + " : " + GetCurrentDate() + " -- " + message + "\n";
	return *this;
};

std::string cLogger::GetCurrentDate()const
{
	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
	return boost::posix_time::to_simple_string(now);
};

bool cLogger::WriteToDisk(std::string &buff)
{
	boost::mutex::scoped_lock lock(cLogger::s_Mutex);
	try
	{
		std::ofstream file(GLOBAL_LOG_FILE, std::ios_base::out | std::ios_base::app);
		file<<buff;
		file.close();
	}
	catch(...)
	{
		return false;
	}
	buff.clear();
	return true;
};



