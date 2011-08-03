
#include "result.h"
#include "session.h"


cResult::cResult(cSession *session, cCommand *command)
	:m_Session(session),
	m_Command(command)
{};

cResult::~cResult()
{};

void cResult::SetResultStr(const std::string& result)
{
	m_Result_str = result;
	m_Session->SetState(STATE_RESULT_PENDING);
};

void cResult::SetCommand(cCommand *command)
{
	m_Command = command;
};

const std::string& cResult::GetResultStr()const
{
	return m_Result_str;
};

const cCommand* cResult::GetCommand()const
{
	return m_Command;
};




