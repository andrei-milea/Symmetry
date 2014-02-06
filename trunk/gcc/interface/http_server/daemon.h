#ifndef _DAEMON_H
#define _DAEMON_H

#include "../../engine/logger.h"

#include <unistd.h>

namespace http_server
{


void make_daemon()
{	
	using namespace engine;

	if (pid_t pid = fork())
	{
		if (pid > 0)
		{
			//exit the parent process
			exit(0);
		}
		else
		{
			std::cout << "failed to make the process a daemon, fork failed";
			return;
		}
	}

	//make the process a new session leader, this detaches it from the terminal.
	setsid();

	//make root working directory
	chdir("/");

	//remove restrictions
	umask(0);

	//decouple the daemon from the terminal that started it by closing the standard streams
	close(0);
	close(1);
	close(2);

	//remove standard input.
	if (open("/dev/null", O_RDONLY) < 0)
	{
		std::cout << "failed to open /dev/null";
	}
}

}//namespace http_server

#endif


