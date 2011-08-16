#include "pagebuilder.h"
#include "../../engine/result.h"
#include "../../engine/logger.h"

namespace http_server
{

using namespace engine;


cPageBuilder *cPageBuilder::s_Instance = NULL;


cPageBuilder* cPageBuilder::GetInstance()
{
	if(NULL == s_Instance)
		s_Instance = new cPageBuilder;
	return s_Instance;
};

cPageBuilder::cPageBuilder()
{
	//open index html file
	std::ifstream IndexFile;
	IndexFile.open(INDEX_PAGE);
	if(!IndexFile.is_open())
		throw std::runtime_error(CONTEXT_STR + "failed to open index file");
	std::stringstream IndexFileStream(m_IndexFileStr);
	IndexFileStream << IndexFile.rdbuf();

	//set id position
	m_IdPosition = m_IndexFileStr.find("0000000");

	m_IdSize = std::numeric_limits<std::size_t>::digits10;
	IndexFile.close();
}; 


const std::string& cPageBuilder::GetIndexPage(const unsigned int session_id)
{
	return m_IndexFileStr.replace(m_IdPosition, m_IdSize, boost::lexical_cast<std::string>(session_id));
};

const std::string cPageBuilder::GetWebglConstent(const std::string &webglcontent)const
{
	return "";
};

const std::string cPageBuilder::GetPage(const cResult &result, const unsigned int ses_id)const
{
	//TODO
	return "";
};

const std::string cPageBuilder::GetLoadingPage(const unsigned int estimation, const unsigned int ses_id)const
{
	//TODO
	return "";
};

const std::string cPageBuilder::GetPlainContent(const std::string& planecontent)const
{
	return planecontent;
};


}

