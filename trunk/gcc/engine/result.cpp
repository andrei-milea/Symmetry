
#include "result.h"
#include "session.h"


cResult::cResult(cSession *session, cCommand *command)
	:m_Session(session),
	m_Command(command)
{};

cResult::~cResult()
{};

void cResult::SetCommand(cCommand *command)
{
	m_Command = command;
};

void cResult::SetResult(const boost::any &result)
{
	m_Result = result;
};

const boost::any& cResult::GetResult()const
{
	return m_Result;
};

const cCommand* cResult::GetCommand()const
{
	return m_Command;
};




