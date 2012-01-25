#ifndef _SESSION_H
#define _SESSION_H

#include <string>
#include "command_queue.h"
#include "thread_pool.h"
#include "result.h"

namespace engine
{

class cCommand;

/*!

*/
#define STATE_FREE 0
#define STATE_COMMAND_PENDING 1
#define STATE_RESULT_PENDING 2

/*!
 implements a session for a client connected to the http_server
 uses a thread pool to run received commands
 active object variant design pattern
*/
class cSession
{
public:
	cSession();
	cSession(unsigned int ses_id);
	~cSession();

	/*!
	  runs a command and returns the result as soon as it finishes
	*/
	void RunCommand(cCommand *command);

	/*!
	  puts a command in the wait queue to be processed by the thread pool
	*/
	void ScheduleCommand(cCommand *command);

	/*!
	  cancels a command received previously
	*/
	void TerminateCommand();

	/*!
	  return a given estimate of the progress
	*/
	unsigned int GetProgess();

	int GetState()const;

	void SetState(int state);

	/*!
	  returns the result of a command
	*/
	cResult *GetResult();

private:
	static cThreadPool sThreadPool;
	int m_SessionId;
	volatile int m_State;
	cResult m_Result;
};

}

#endif
