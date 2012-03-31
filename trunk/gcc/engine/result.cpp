
#include "result.h"
#include "session.h"

namespace engine
{

cResult::cResult()
{};

cResult::~cResult()
{
};


void cResult::SetCommand(boost::shared_ptr<cCommand>& command)
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

const boost::shared_ptr<cCommand>& cResult::GetCommand()const
{
	return m_Command;
};


}

