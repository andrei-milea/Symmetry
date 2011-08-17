#include "pagebuilder.h"
#include "../../engine/result.h"
#include "../../engine/logger.h"
#include <cassert>

namespace http_server
{

using namespace engine;

cPageBuilder *cPageBuilder::s_Instance = NULL;

#define INDEX_PAGE	"../pages/index.html"
#define CSS_PAGE	"../pages/styles.css"
#define COMPANEL_JS	"../pages/command_panel.js"
#define WEBGL_JS	"../pages/webgl.js"

//macro for inserting HTML directly in C++
#define HTML(...) #__VA_ARGS__



cPageBuilder* cPageBuilder::GetInstance()
{
	if(NULL == s_Instance)
		s_Instance = new cPageBuilder;
	return s_Instance;
};

cPageBuilder::cPageBuilder()
{
	//cache index html file
	std::ifstream File;
	File.open(INDEX_PAGE, std::ios::binary);
	if(!File.is_open())
		throw std::runtime_error(CONTEXT_STR + "failed to open index file");
	m_IndexFileStr.assign((std::istreambuf_iterator<char>(File)), (std::istreambuf_iterator<char>()));
	//set id position
	m_IdPosition = m_IndexFileStr.find("000000");
	assert(m_IdPosition != std::string::npos);
	m_IdSize = std::numeric_limits<std::size_t>::digits10;
	File.close();

	//cache css file
	File.open(CSS_PAGE, std::ios::binary);
	if(!File.is_open())
		throw std::runtime_error(CONTEXT_STR + "failed to open resource css file");
	m_ResourceFileStr.assign((std::istreambuf_iterator<char>(File)), (std::istreambuf_iterator<char>()));
	File.close();

	//cache webgl js file
	File.open(WEBGL_JS, std::ios::binary);
	if(!File.is_open())
		throw std::runtime_error(CONTEXT_STR + "failed to open webgl js file");
	m_WebglJsFileStr.assign((std::istreambuf_iterator<char>(File)), (std::istreambuf_iterator<char>()));
	File.close();

	//cache command_panel js file
	File.open(COMPANEL_JS, std::ios::binary);
	if(!File.is_open())
		throw std::runtime_error(CONTEXT_STR + "failed to open command_panel js file");
	m_ComPanelJsFileStr.assign((std::istreambuf_iterator<char>(File)), (std::istreambuf_iterator<char>()));
	File.close();
}; 


const std::string& cPageBuilder::GetIndexPage(const unsigned int session_id)
{
	return m_IndexFileStr.replace(m_IdPosition, m_IdSize, boost::lexical_cast<std::string>(session_id));
};

const std::string& cPageBuilder::GetPageResource(const std::string& resource)const
{
	if(resource.find("styles") != std::string::npos)	
		return GetPageResourceCss();
	else if(resource.find("webgl") != std::string::npos)
		return GetWebGlJsPage();
	else 
	{
		assert(resource.find("command_panel") != std::string::npos);
		return GetCommandPanelJs();
	}
};

const std::string& cPageBuilder::GetPageResourceCss()const
{
	return m_ResourceFileStr;
};

const std::string& cPageBuilder::GetWebGlJsPage()const
{
	return m_WebglJsFileStr;
};

const std::string& cPageBuilder::GetCommandPanelJs()const
{
	return m_ComPanelJsFileStr;
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

