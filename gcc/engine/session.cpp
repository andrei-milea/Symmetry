
#include "session.h"
#include "group_factory.h"
#include "command.h"

namespace engine
{

cThreadPool cSession::sThreadPool(20);

cSession::cSession()
	:m_SessionId(0),
	 m_State(STATE_FREE),
	 m_PendingCommand(nullptr)
{}

cSession::cSession(std::size_t ses_id)
	:m_SessionId(ses_id),
	 m_State(STATE_FREE),
	 m_PendingCommand(nullptr)
{}

cSession::~cSession()
{}

void cSession::ScheduleCommand(std::shared_ptr<cCommand>& command)
{
	assert(m_State == STATE_FREE);
	if(!cSession::sThreadPool.isStarted())
		cSession::sThreadPool.StartPool();
	cSession::sThreadPool.AddToCommandQueue(command, this);
	m_State = STATE_COMMAND_PENDING;
}

void cSession::RunCommand(std::shared_ptr<cCommand>& command)
{
	command->Execute();
}

}


