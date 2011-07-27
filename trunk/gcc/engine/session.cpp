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
	m_State(0)
{};

cSession::~cSession()
{};

const std::string cSession::RunCommand(cCommand *command)
{
	if(!cSession::sThreadPool.isStarted())
		cSession::sThreadPool.StartPool();
	cSession::sThreadPool.AddToCommandQueue(command);
	return "";
};



