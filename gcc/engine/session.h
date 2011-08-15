#ifndef _SESSION_H
#define _SESSION_H

#include <string>
#include "command_queue.h"
#include "thread_pool.h"
#include "result.h"

namespace engine
{

class cCommand;

#define STATE_FREE 0
#define STATE_COMMAND_PENDING 1 
#define STATE_RESULT_PENDING 2

//active object variant design pattern
class cSession
{
public:
	cSession();
	cSession(unsigned int ses_id);
	~cSession();

	//returns the estimative time for the next request
	void RunCommand(cCommand *command);
	void ScheduleCommand(cCommand *command);
	void TerminateCommand();
	unsigned int GetProgess();
	int GetState()const;
	void SetState(int state);
	cResult *GetResult();

private:
	static cThreadPool sThreadPool;
	int m_SessionId;
	volatile int m_State;
	cResult m_Result;
};

}

#endif
