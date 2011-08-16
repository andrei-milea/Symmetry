#include "http_server.h"

#include <iostream>
#include "../../engine/logger.h"

using namespace http_server;
using namespace engine;

int main()
{

	while(true)
	{
		cHttpServer _http_server(80);
		try
		{
			_http_server.Start();
		}
		catch(std::exception& e)
		{
			cLogger log(LOG_SEV_ERROR);
			log<< e.what();
			_http_server.Stop();
			continue;
		}

		_http_server.Stop();
		return 0;
	}

};
