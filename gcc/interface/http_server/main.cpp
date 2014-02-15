#include "http_server.h"

#include "../../engine/logger.h"
#include "daemon.h"

#include <iostream>
#include <chrono>
#include <thread>
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
	catch(const std::exception& e)
	{
		std::cout << std::string("failed to load configuration: ") + e.what();
		return -1;
	}

	//make this a daemon process
	make_daemon();

	//start logging thread
	try
	{
		cLogger::getInstance().setLogFile(log_path);
		cLogger::getInstance().runLogLoop();
	}
	catch(const std::exception& e)
	{
		std::cout << std::string("failed to start logging") + e.what();
		return -1;
	}

	//run server
	unsigned short tries = 0;
	unsigned short max_fails = 5;
	while(tries < max_fails)
	{
		try
		{
			tries++;
			cHttpServer _http_server(port, web_pages_path, presentations_path);
			_http_server.Start();
		}
		catch(const std::exception& e)
		{
			cLogger::getInstance().print(e);
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			continue;
		}
	}
	return -1;
};

