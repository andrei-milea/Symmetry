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

cPageBuilder *cPageBuilder::s_Instance = NULL;
std::string cPageBuilder::s_ResError = "Resource not available";
std::string cPageBuilder::s_WebPagesPath = "../pages";
std::string cPageBuilder::s_PresentationsPath = "../presentations";

#define INDEX_PAGE	"/index.html"

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
	:m_IdPosition(0),
	m_IdSize(2)
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
			m_Resources[file_path].assign(std::istreambuf_iterator<char>(file),
				   	std::istreambuf_iterator<char>());
			if(INDEX_PAGE == file_path)
			{
				m_IdPosition = m_Resources[file_path].find("00");
				assert(m_IdPosition != std::string::npos);
			}
		}
	}
}


const std::string& cPageBuilder::GetIndexPage(const std::size_t session_id)
{
	std::size_t old_size = m_IdSize;
	m_IdSize = std_ex::numDigits<std::size_t>(session_id);
	auto map_iter = m_Resources.find(INDEX_PAGE);
	if(map_iter != m_Resources.end())
		return map_iter->second.replace(m_IdPosition, old_size, boost::lexical_cast<std::string>(session_id));
	else
		return cPageBuilder::s_ResError;
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

const std::string &cPageBuilder::GetPage(boost::shared_ptr<cCommand> pCommand, const std::size_t ses_id)const
{
	m_ResultStr.clear();
	std::stringstream ss;
	ss.precision(std::numeric_limits<double>::digits10);

	//TODO --  change this
	boost::shared_ptr<cGetCGraphCommand> command_cgraph = boost::dynamic_pointer_cast<cGetCGraphCommand>(pCommand);
	boost::shared_ptr<cGroupGenCommand> command_groupgen = boost::dynamic_pointer_cast<cGroupGenCommand>(pCommand);
	boost::shared_ptr<cGetRelCommand> command_rel = boost::dynamic_pointer_cast<cGetRelCommand>(pCommand);
	boost::shared_ptr<cGetMatExprCommand> command_matexpr = boost::dynamic_pointer_cast<cGetMatExprCommand>(pCommand);
	boost::shared_ptr<cGetNormCommand> command_norm = boost::dynamic_pointer_cast<cGetNormCommand>(pCommand);
	boost::shared_ptr<cGetDeterminantCommand> command_determinant = boost::dynamic_pointer_cast<cGetDeterminantCommand>(pCommand);
	boost::shared_ptr<cGetInverseCommand> command_inverse = boost::dynamic_pointer_cast<cGetInverseCommand>(pCommand);
	boost::shared_ptr<cGetRREFCommand> command_rref = boost::dynamic_pointer_cast<cGetRREFCommand>(pCommand);
	boost::shared_ptr<cGetLinSysSolCommand> command_lineq = boost::dynamic_pointer_cast<cGetLinSysSolCommand>(pCommand);
	boost::shared_ptr<cGetPolyZerosCommand> command_polyzeros = boost::dynamic_pointer_cast<cGetPolyZerosCommand>(pCommand);
	boost::shared_ptr<cGetPolyPlotCommand> command_polyplot = boost::dynamic_pointer_cast<cGetPolyPlotCommand>(pCommand);

	if(command_rref || command_lineq)
	{
		boost::numeric::ublas::matrix<double> mat;
		mat = (command_rref ? command_rref->GetResult() : command_lineq->GetResult());
		m_ResultStr = "$\\begin{bmatrix} ";
		for(std::size_t rows_idx = 0; rows_idx < mat.size1(); rows_idx++)
		{
			for(std::size_t cols_idx = 0; cols_idx < mat.size2(); cols_idx++)
			{
				ss.str("");
				ss << mat(rows_idx, cols_idx);
				m_ResultStr += ss.str(); 

				if(cols_idx < mat.size2() - 1)
					m_ResultStr += " & ";
			}

			if(rows_idx < mat.size1() - 1)
				m_ResultStr += " \\\\ ";
		}
		m_ResultStr += " \\end{bmatrix}$";
	}
	else if(command_polyzeros)
	{
		if(command_polyzeros->GetResult().size() == 0)
		{
			m_ResultStr = "no real solution exists";
		}
		else
		{
			m_ResultStr = "roots: $";
			for(auto root : command_polyzeros->GetResult())
			{
				ss.str("");
				ss << root;
				m_ResultStr += ss.str() + "; ";
			}
			m_ResultStr += "$";
		}
	}
	else if(command_polyplot)
	{
		m_ResultStr = "plot: ";
		for(auto points : command_polyplot->GetResult())
		{
			ss.str("");
			ss << std::fixed << std::setprecision(2) << points.first << "," << points.second;
			m_ResultStr += ss.str() + ";";
		}
	}
	else if(command_norm || command_determinant)
	{
		ss.str("");
		if(command_norm)
		{
			ss << command_norm->GetResult();
			m_ResultStr = "$ " + ss.str() + " $";
		}
		else if(command_determinant)
		{
			ss << command_determinant->GetResult();
			m_ResultStr = "$ " + ss.str() + " ; ";
			ss.str("");
			ss << command_determinant->GetTrace();
			m_ResultStr += ss.str() + " $";
		}
	}
	else if(command_matexpr || command_inverse)
	{
		ss.str("");
		m_ResultStr = "$\\begin{bmatrix} ";
		boost::numeric::ublas::matrix<double> mat;
		if(command_matexpr)
			mat = command_matexpr->GetResult();
		else if(command_inverse)
			mat = command_inverse->GetResult();
		for(std::size_t rows_idx = 0; rows_idx < mat.size1(); rows_idx++)
		{
			for(std::size_t cols_idx = 0; cols_idx < mat.size2(); cols_idx++)
			{
				ss.str("");
				ss << mat(rows_idx, cols_idx);
				m_ResultStr += ss.str(); 

				if(cols_idx < mat.size2() - 1)
					m_ResultStr += " & ";
			}

			if(rows_idx < mat.size1() - 1)
				m_ResultStr += " \\\\ ";
		}
		m_ResultStr += " \\end{bmatrix}$";
	}
	else if(command_cgraph)
	{
		GROUP_TYPE group_type = command_cgraph->GetGroupType();
		if(SYMMETRIC_GROUP != group_type && CYCLIC_GROUP != group_type && DIHEDRAL_GROUP != group_type)
			throw std::runtime_error(CONTEXT_STR + "invalid group type");

		m_ResultStr = "</br>Cayley Graph representation as adjacency list:</br>";
		std::stringstream redirectstream;
		std::streambuf* oldbuf = std::cout.rdbuf(redirectstream.rdbuf());
		std::string str;
		std::cout<<command_cgraph->GetResult();
		while(std::getline(redirectstream, str))
		{
			ss << str << "</br>";
		}
		//put back the old stream buffer
		std::cout.rdbuf(oldbuf);

		m_ResultStr += ss.str();
	}
	else if(command_rel)
	{
		GROUP_TYPE group_type = command_rel->GetGroupType();
		if(SYMMETRIC_GROUP != group_type && CYCLIC_GROUP != group_type && DIHEDRAL_GROUP != group_type)
			throw std::runtime_error(CONTEXT_STR + "invalid group type");

		m_ResultStr = "</br>Defining Relations:</br></br>";
		std::string str;
		const std::vector<cGroupRelation> &relations = command_rel->GetResult();

		ss.str("");
		std::size_t index = 1;
		for(auto rel_iter = relations.begin(); rel_iter != relations.end(); rel_iter++)
		{
			ss << index << ". $" << *rel_iter << "$</br>";
			index++;
		}	
		m_ResultStr += ss.str();
	}
	else if(command_groupgen)
	{
		GROUP_TYPE group_type = command_groupgen->GetGroupType();
		if(SYMMETRIC_GROUP != group_type && CYCLIC_GROUP != group_type && DIHEDRAL_GROUP != group_type)
			throw std::runtime_error(CONTEXT_STR + "invalid group type");

		m_ResultStr = "</br>Elements: </br></br><ul id='list-elem'>";
		std::string perm_str;
		const std::vector<SymmGrpElem> &elements = command_groupgen->GetResult();
		for(std::size_t index = 0; index < elements.size(); index++)
		{
			ss.str("");
			ss << elements[index];
			perm_str = ss.str();
			perm_str.replace(perm_str.find("\n"), 1, "</br>");
			m_ResultStr += "<li>" + perm_str + "</li>";
		}
		m_ResultStr += "</ul></br></br>";
	}
	return m_ResultStr;
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

