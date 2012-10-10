#ifndef _SESSION_H
#define _SESSION_H

#include <string>
#include "command_queue.h"
#include "thread_pool.h"

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
	cSession(std::size_t ses_id);
	~cSession();

	/*!
	  runs a command and returns the result as soon as it finishes
	*/
	void RunCommand(boost::shared_ptr<cCommand>& command);

	/*!
	  puts a command in the wait queue to be processed by the thread pool
	*/
	void ScheduleCommand(boost::shared_ptr<cCommand>& command);

	/*!
	  cancels a command received previously
	*/
	void TerminateCommand();

	boost::shared_ptr<cCommand> GetPendingCommand()
	{	return m_PendingCommand;	};

	int GetState()const;

	void SetState(int state);

private:
	static cThreadPool sThreadPool;
	std::size_t m_SessionId;
	volatile int m_State;
	boost::shared_ptr<cCommand> m_PendingCommand;
};

}

#endif
