#include "http_server.h"

#include "../../engine/logger.h"
#include "daemon.h"

#include <iostream>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>


#define CONFIG_XML "../../config.xml"

using namespace http_server;
using namespace engine;
using boost::property_tree::ptree;

int main()
{
	unsigned int port = 80;
	std::string web_pages_path;
	std::string presentations_path;
	std::string log_path;

	try
	{
		std::ifstream file;
		ptree pt;

		file.open(CONFIG_XML);
		read_xml(file, pt);

		port = pt.get<unsigned int>("symmetry_config.address.port");
		web_pages_path = pt.get<std::string>("symmetry_config.paths.web_pages");
		presentations_path = pt.get<std::string>("symmetry_config.paths.presentations");
		log_path = pt.get<std::string>("symmetry_config.paths.log");

	}
	catch(std::exception& e)
	{
		std::cout << std::string("failed to load configuration: ") + e.what();
		return -1;
	}

	//make this a daemon process
	make_daemon();

	//start logging thread
	cLogger::getInstance().setLogFile(log_path);
	cLogger::getInstance().runLogLoop();

	while(true)
	{
		try
		{
			cHttpServer _http_server(port, web_pages_path, presentations_path);
			_http_server.Start();
		}
		catch(std::exception& e)
		{
			cLogger::getInstance().print(e);
			continue;
		}
		return 0;
	}

};
