#include "pagebuilder.h"
#include "../../engine/result.h"
#include "../../engine/logger.h"
#include "../../engine/groupgen_command.h"
#include "../../engine/getcgraph_command.h"
#include <cassert>
#include "../../lib/std_ex.h"
#include <sstream>

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
	m_IdPosition = m_IndexFileStr.find("00");
	assert(m_IdPosition != std::string::npos);
	File.close();
	m_IdSize = 2;

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
	int old_size = m_IdSize;
	m_IdSize = std_ex::numDigits<std::size_t>(session_id);
	return m_IndexFileStr.replace(m_IdPosition, old_size, boost::lexical_cast<std::string>(session_id));
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
	std::string result_str;
	std::stringstream ss;

	const cGetCGraphCommand *command_cgraph = dynamic_cast<const cGetCGraphCommand*>(result.GetCommand());
	const cGroupGenCommand *command = dynamic_cast<const cGroupGenCommand*>(result.GetCommand());
	if(command_cgraph && (SYMMETRIC_GROUP == command_cgraph->GetGroupType()))
	{
		result_str = "</br>Cayley Graph representation as adjacency list:</br>";
		std::stringstream redirectstream;
		std::streambuf* oldbuf = std::cout.rdbuf(redirectstream.rdbuf());
		std::string str;
		std::cout<<boost::any_cast<cCayleyGrf<SymmGrp> >(result.GetResult());
		while(std::getline(redirectstream, str))
		{
			ss<<str<<"</br>";
		}
		//put back the old stream buffer
		std::cout.rdbuf(oldbuf);

		result_str += ss.str();
	}
	else if(command && (SYMMETRIC_GROUP == command->GetGroupType()))
	{
		result_str = "<ul id='list-elem'>";
		std::string perm_str;
		std::vector<SymmGrpElem> elements = boost::any_cast<std::vector<SymmGrpElem> >(result.GetResult());
		for(std::size_t index = 0; index < elements.size(); index++)
		{
			ss.str("");
			ss<<elements[index];
			perm_str = ss.str();
			perm_str.replace(perm_str.find("\n"), 1, "</br>");
			result_str += "<li>" + perm_str + "</li>";
		}
		result_str += "</ul>";
	}
	return result_str;
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

