
#include "pres_command.h"
#include "logger.h"

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

#include "boost/date_time/posix_time/posix_time.hpp"
#include "html_processing/html_processing_inc.h"



//TODO -- get the path from pagebuilder
#define PRES_PATH "/root/projects/symmetry/absalg/gcc/interface/presentations"
#define PAGES_PATH "/root/projects/symmetry/absalg/gcc/interface/pages"
const std::string library_path = "/root/projects/symmetry/absalg/gcc/engine/html_processing/libhtml_processing.so";

namespace engine
{

namespace fs = boost::filesystem;
using namespace boost::posix_time;

cPresCommand::cPresCommand(const std::string &param)
{
	std::size_t idx1 = param.find(":");
	if(std::string::npos == idx1)
	{
		m_PresCommand = param;
		if(m_PresCommand != "dir")
			throw std::runtime_error(CONTEXT_STR + "invalid presentation param");
	}
	else
	{
		m_PresCommand = param.substr(0, idx1);
		if(m_PresCommand == "save" || m_PresCommand == "download" || m_PresCommand == "slides")
		{
			std::size_t idx2 = param.find("<");
			if(std::string::npos == idx2)
				throw std::runtime_error(CONTEXT_STR + "invalid presentation param");
			m_PresName = param.substr(idx1 + 1, idx2 - idx1 - 1);
			m_Html = param.substr(idx2);
		}
		else
		{
			assert(m_PresCommand == "load");
			m_PresName = param.substr(idx1 + 1);
		}
	}
}


void cPresCommand::Execute()
{
	if(m_PresCommand == "slides")
	{
		createSlidesImgs();
	}
	else if(m_PresCommand == "save")
	{
		Save();
	}
	else if(m_PresCommand == "dir")
	{
		Dir();
	}
	else if(m_PresCommand == "load")
	{
		Load();
	}
	else if(m_PresCommand == "download")
	{
		Download();
	}
	else
		assert(false);
}


void cPresCommand::Save()
{
	//encode html
	m_Html = cHtmlProcApp::GetInstance()->html_encode(m_Html);

	bool overwrite = false;
	fs::path pres_path(std::string(PRES_PATH) + "/" + m_PresName);
	if(fs::exists(pres_path))
		overwrite = true;
	else
		fs::create_directory(pres_path);

	std::ofstream file;
	file.open(pres_path.string() + "/" + m_PresName + ".html", std::ios::binary);
	if(!file.is_open())
		throw std::runtime_error(CONTEXT_STR + "failed to save presentation");

	file << m_Html;
	file.close();

	if(overwrite)
		m_Result = "Presentation " + m_PresName + " was successfuly overwritten.";
	else
		m_Result = "Presentation " + m_PresName + " was successfuly saved.";
}



void cPresCommand::createSlidesImgs()
{
	m_Html = cHtmlProcApp::GetInstance()->html_encode(m_Html);
	std::ifstream file;
	file.open(std::string(PAGES_PATH) + "/pres_template.html", std::ios::binary);
	std::string pres_page_html((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	auto content_it = pres_page_html.find("CONTENT");
	pres_page_html.replace(content_it, 7, m_Html);
	auto imgs = cHtmlProcApp::GetInstance()->html_to_imgs(pres_page_html, std::string(PAGES_PATH));

	if(0 == imgs.size())
		throw std::runtime_error(CONTEXT_STR + "failed to create slides");

	for(auto it : imgs)
		m_Result += "slide:" + it;
}


void cPresCommand::Dir()
{
	m_Result = "<div class='pres_list'><h1>Available Presentations:</h1><br/><br/><ul>";
	fs::path dir_path(PRES_PATH);
	if(!fs::exists(dir_path))
		throw std::runtime_error(CONTEXT_STR + "invalid presentations directory");
		
	fs::directory_iterator end_iter;

	std::ifstream template_file;
	template_file.open(std::string(PAGES_PATH) + "/pres_template.html", std::ios::binary);
	if(!template_file.is_open())
		throw std::runtime_error(CONTEXT_STR + "invalid presentation template file");
	std::string pres_page_html((std::istreambuf_iterator<char>(template_file)), std::istreambuf_iterator<char>());

	for(fs::directory_iterator dir_iter(dir_path); dir_iter != end_iter; ++dir_iter)
	{
		if(fs::is_directory(dir_iter->status()))
		{
			
			fs::path pres_path(dir_iter->path());
			if(!fs::exists(pres_path))
				throw std::runtime_error(CONTEXT_STR + "invalid presentation directory");
				
			for(fs::directory_iterator pres_iter(pres_path); pres_iter != end_iter; ++pres_iter)
			{
				if(fs::is_regular_file(pres_iter->status()))
				{
					std::ifstream file;
					file.open(pres_iter->path().string(), std::ios::binary);
					if(!file.is_open())
						throw std::runtime_error(CONTEXT_STR + "invalid presentation file" + pres_iter->path().string());
					std::string pres_content((std::istreambuf_iterator<char>(file)),
							std::istreambuf_iterator<char>());
					std::string page_html = pres_page_html;
					auto content_it = page_html.find("CONTENT");
					page_html.replace(content_it, 7, pres_content);
					std::string image_data = cHtmlProcApp::GetInstance()->html_to_img(page_html, std::string(PAGES_PATH));
					m_Result += "<li id='" + pres_iter->path().filename().stem().string()
						+"' onclick=\"ToolBox.submitPresCommand('load', this)\"><img src='data:image/png;base64,"
					   	+ image_data + "' /><span>Name: <b>" + pres_iter->path().filename().stem().string() 
						+ "</b><br/>Author: <b> Andrei </b>" //TODO -- add author
						+ "<br/> Created: " + to_simple_string(from_time_t(fs::last_write_time(pres_iter->path())).date()) 
						+ "</span></li><hr width='100%'>";
				}
				else
					assert(false);
			}
		}
	}

	m_Result += "</ul></div>";
}

void cPresCommand::Load()
{
	fs::path pres_path(std::string(PRES_PATH) + "/" + m_PresName + "/" + m_PresName + ".html");
	if(!fs::exists(pres_path))
		throw std::runtime_error(CONTEXT_STR + "presentation file does not exists");
	std::ifstream file;
	file.open(pres_path.string(), std::ios::binary);
	if(!file.is_open())
		throw std::runtime_error(CONTEXT_STR + "failed to open presentation file");

	std::string pres_page_html((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	m_Result = pres_page_html;

	if(0 == m_Result.size())
		throw std::runtime_error(CONTEXT_STR + "failed to load presentation");
}

void cPresCommand::Download()
{
	m_Html = cHtmlProcApp::GetInstance()->html_encode(m_Html);
	
	std::ifstream template_file;
	template_file.open(std::string(PAGES_PATH) + "/pres_template.html", std::ios::binary);
	if(!template_file.is_open())
		throw std::runtime_error(CONTEXT_STR + "invalid presentation template file");
	std::string pres_page_html((std::istreambuf_iterator<char>(template_file)), std::istreambuf_iterator<char>());

	auto content_it = pres_page_html.find("CONTENT");
	pres_page_html.replace(content_it, 7, m_Html);
	m_Result = cHtmlProcApp::GetInstance()->html_to_pdf(pres_page_html, std::string(PAGES_PATH));
	
	if(0 == m_Result.size())
		throw std::runtime_error(CONTEXT_STR + "failed to create PDF");
}

unsigned int cPresCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return 1;
}


}

