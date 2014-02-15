#ifndef _SESSION_H
#define _SESSION_H

#include <string>
#include "command_queue.h"
#include "thread_pool.h"
#include <memory>

namespace engine
{

class cCommand;

/*!
 the session can be in one of these 3 states
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
	void RunCommand(std::shared_ptr<cCommand>& command);

	/*!
	  puts a command in the wait queue to be processed by the thread pool
	*/
	void ScheduleCommand(std::shared_ptr<cCommand>& command);

	std::shared_ptr<cCommand>& GetPendingCommand()
	{
		assert(m_State == STATE_RESULT_PENDING);
		return m_PendingCommand;
	}

	/*!
	  cancels a command received previously
	*/
	void TerminateCommand();

	int GetState()const
	{
		return m_State;
	}

	void SetPendingCommand(std::shared_ptr<cCommand> command)
	{
		m_PendingCommand = std::move(command);
		m_State = STATE_RESULT_PENDING;
	}

private:
	static cThreadPool sThreadPool;
	std::size_t m_SessionId;
	volatile int m_State;
	std::shared_ptr<cCommand> m_PendingCommand;
};

}

#endif
