#include "pagebuilder.h"

cPageBuilder *cPageBuilder::s_Instance = NULL;

std::string& cPageBuilder::GetIndexPage(const unsigned int session_id)
{
	return m_Index_page.replace(ID_POS, ID_SIZE, boost::lexical_cast<std::string>(session_id));
};

const std::string cPageBuilder::GetWebglConstent(const std::string &webglcontent)const
{
	return webglcontent;
};

const std::string cPageBuilder::GetPage(const cResult &result, const unsigned int ses_id)
{
	//TODO
	return "";
};

const std::string cPageBuilder::GetLoadingPage(const unsigned int estimation, const unsigned int ses_id)
{
	//TODO
	return "";
};

const std::string cPageBuilder::GetPlainContent(const std::string& planecontent)const
{
	return planecontent;
};



