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
         std::cerr << e.what() << std::endl;
    }

};
