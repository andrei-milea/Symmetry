
#include "session.h"
#include "group_factory.h"
#include "command.h"


cThreadPool cSession::sThreadPool(20);

cSession::cSession()
	:m_SessionId(0),
	m_State(0)
{};

cSession::cSession(unsigned int ses_id)
	:m_SessionId(ses_id),
	m_State(STATE_FREE),
	m_Result(this)
{};

cSession::~cSession()
{};


cResult *cSession::GetResult()
{
	return &m_Result;
};

int cSession::GetState()const
{
	return m_State;
};

void cSession::SetState(int state)
{
	m_State = state;
};

void cSession::ScheduleCommand(cCommand *command)
{
	if(!cSession::sThreadPool.isStarted())
		cSession::sThreadPool.StartPool();
	m_Result.SetCommand(command);
	cSession::sThreadPool.AddToCommandQueue(command);
	m_State = STATE_COMMAND_PENDING;
};

void cSession::RunCommand(cCommand *command)
{
	command->Execute();
};



