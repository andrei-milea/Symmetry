#include "pagebuilder.h"
#include "../../engine/logger.h"
#include "../../engine/groupgen_command.h"
#include "../../engine/getcgraph_command.h"
#include "../../engine/getrel_command.h"
#include "../../engine/getmatexpr_command.h"
#include "../../engine/getnorm_command.h"
#include "../../engine/getdeterminant_command.h"
#include "../../engine/getinverse_command.h"
#include "../../engine/getrref_command.h"
#include "../../engine/getlinsyssol_command.h"
#include "../../engine/getpolyzeros_command.h"
#include "../../engine/getpolyplot_command.h"
#include "../../engine/getfuncplot_command.h"
#include "../../engine/getfuncdiff_command.h"
#include "../../engine/pres_command.h"
#include <cassert>
#include "../../lib/std_ex.h"
#include <sstream>
#include <iostream>

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>



namespace http_server
{

namespace fs = boost::filesystem;

using namespace engine;

cPageBuilder *cPageBuilder::s_Instance = nullptr;
std::string cPageBuilder::s_ResError = "Resource not available";
std::string cPageBuilder::s_WebPagesPath = "";
std::string cPageBuilder::s_PresentationsPath = "";


//macro for inserting HTML directly in C++
#define HTML(...) #__VA_ARGS__



cPageBuilder* cPageBuilder::GetInstance()
{
	if(NULL == s_Instance)
		s_Instance = new cPageBuilder;
	return s_Instance;
}


void cPageBuilder::SetPaths(const std::string& web_pages_path, const std::string& presentations_path)
{
	cPageBuilder::s_WebPagesPath = web_pages_path;
	cPageBuilder::s_PresentationsPath = presentations_path;
}

cPageBuilder::cPageBuilder()
{
	LoadWebPages(cPageBuilder::s_WebPagesPath);
}

void cPageBuilder::LoadWebPages(const std::string &path)
{
	fs::path dir_path(path);
	if(!fs::exists(dir_path))
		throw std::runtime_error(CONTEXT_STR + "invalid resources directory");
		
	fs::directory_iterator end_iter;

	for(fs::directory_iterator dir_iter(dir_path); dir_iter != end_iter; ++dir_iter)
	{
		if(fs::is_directory(dir_iter->status()))
		{
			LoadWebPages(dir_iter->path().string());
		}
		else if(fs::is_regular_file(dir_iter->status()))
		{
			std::ifstream file;
			file.open(dir_iter->path().string(), std::ios::binary);
			std::string dir_path = dir_iter->path().string();
			std::string file_path = "/" + dir_path.substr(dir_path.find("pages/") + 6);
			m_Resources[file_path].assign((std::istreambuf_iterator<char>(file)),
				   	std::istreambuf_iterator<char>());
		}
	}
}


const std::string& cPageBuilder::GetIndexPage(const std::size_t session_id)
{
	auto map_iter = m_Resources.find("/index.html");
	if(map_iter == m_Resources.end())
		return cPageBuilder::s_ResError;

	static size_t IdPosition = map_iter->second.find("00");
	static size_t IdSize = 2;
	assert(IdPosition != std::string::npos);

	std::size_t old_size = IdSize;
	IdSize = std_ex::numDigits<std::size_t>(session_id);

	return map_iter->second.replace(IdPosition, old_size, boost::lexical_cast<std::string>(session_id));
}

const std::string& cPageBuilder::GetPresPage(const std::size_t session_id)
{
	auto map_iter = m_Resources.find("/pres.html");
	if(map_iter == m_Resources.end())
		return cPageBuilder::s_ResError;

	static size_t IdPosition = map_iter->second.find("00");
	static size_t IdSize = 2;
	assert(IdPosition != std::string::npos);

	std::size_t old_size = IdSize;
	IdSize = std_ex::numDigits<std::size_t>(session_id);

	return map_iter->second.replace(IdPosition, old_size, boost::lexical_cast<std::string>(session_id));
}

const std::string& cPageBuilder::GetPageResource(const std::string& resource)const
{
	static std::string error = "Resource not found";
	auto map_iter = m_Resources.find(resource);
	if(map_iter != m_Resources.end())
		return map_iter->second;
	else
		return cPageBuilder::s_ResError;
}

const std::string cPageBuilder::GetLoadingPage(const std::size_t estimation, const std::size_t ses_id)const
{
	//TODO
	return "";
}

const std::string& cPageBuilder::GetPlainContent(const std::string& planecontent)const
{
	return planecontent;
}


}//namespace http_server

