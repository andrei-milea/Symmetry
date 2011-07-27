#include "http_server.h"

#include <iostream>

int main()
{

    try
    {
        boost::asio::io_service io_service;
        cHttpServer http_server(io_service);
        io_service.run();
    }
    catch(std::exception& e)
    {
		cLogger log(LOG_SEV_ERROR);
        log<< e.what();
    }

};
