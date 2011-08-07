#include "http_server.h"

#include <iostream>
#include "../../engine/logger.h"

using namespace http_server;

int main()
{

    try
    {
        cHttpServer _http_server(80);
		_http_server.Start();
    }
    catch(std::exception& e)
    {
		cLogger log(LOG_SEV_ERROR);
        log<< e.what();
    }

};
