
#include "session.h"
#include "group_factory.h"
#include "command.h"

namespace engine
{

cThreadPool cSession::sThreadPool(20);

cSession::cSession()
	:m_SessionId(0),
	 m_State(0)
{}

cSession::cSession(std::size_t ses_id)
	:m_SessionId(ses_id),
	 m_State(STATE_FREE)
{}

cSession::~cSession()
{}

int cSession::GetState()const
{
	return m_State;
}

void cSession::SetState(int state)
{
	m_State = state;
}

void cSession::ScheduleCommand(boost::shared_ptr<cCommand>& command)
{
	if(!cSession::sThreadPool.isStarted())
		cSession::sThreadPool.StartPool();
	m_PendingCommand = command;
	cSession::sThreadPool.AddToCommandQueue(m_PendingCommand);
	m_State = STATE_COMMAND_PENDING;
}

void cSession::RunCommand(boost::shared_ptr<cCommand>& command)
{
	command->Execute();
}

}


