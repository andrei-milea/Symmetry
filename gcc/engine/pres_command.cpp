
#include "pres_command.h"
#include "logger.h"

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>



//TODO -- get the path from pagebuilder
#define PRES_PATH "/root/projects/symmetry/absalg/gcc/interface/presentations"

namespace engine
{

namespace fs = boost::filesystem;

cPresCommand::cPresCommand(const std::string &param)
{
	std::size_t idx1 = param.find(":");
	std::size_t idx2 = param.find("<");
	if(std::string::npos == idx1 || 0 == idx1 || std::string::npos == idx2 || 0 == idx2)
		throw std::runtime_error(CONTEXT_STR + "invalid presentation param");
 
	m_PresCommand = param.substr(0, idx1);
	m_PresName = param.substr(idx1 + 1, idx2 - idx1 - 1);
	m_Html = param.substr(idx2);
}


void cPresCommand::Execute()
{
	if(m_PresCommand == "save")
	{
		bool overwrite = false;
		fs::path pres_path(std::string(PRES_PATH) + "/" + m_PresName);
		if(fs::exists(pres_path))
			overwrite = true;

		std::ofstream file;
		file.open(pres_path.string(), std::ios::binary);
		if(file.is_open())
		{
			file << m_Html;
			file.close();
		}
		else
		{
			throw std::runtime_error(CONTEXT_STR + "failed to save presentation");
		}

		if(overwrite)
			m_Result = "Presentation " + m_PresName + " was successfuly overwritten.";
		else
			m_Result = "Presentation " + m_PresName + " was successfuly saved.";
	}
	else
	{
	}
}

unsigned int cPresCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return 1;
}


}

