#ifndef _SESSION_H
#define _SESSION_H

#include <string>
#include "command_queue.h"
#include "thread_pool.h"

class cCommand;


//active object variant design pattern
class cSession
{
public:
	cSession();
	cSession(unsigned int ses_id);
	~cSession();

	//returns the estimative time for the next request
	const std::string RunCommand(cCommand *command);
	void TerminateCommand();
	unsigned int GetProgess();

private:
	static cThreadPool sThreadPool;
	int m_SessionId;
	int m_State;
};



#endif
