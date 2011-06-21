

#include "command.h"


cCreateCommand::cCreateCommand(std::string &params)
{
	m_Params = params;
};

cCreateCommand::Execute()
{
	m_Progress = PROGRESS_START;



	m_Progress = PROGRESS_END;
};


