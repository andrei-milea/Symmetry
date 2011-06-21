#ifndef _SESSION_H
#define _SESSION_H

#include "group_factory.h"
#include "command.h"



class cSession
{
public:
	cSession()
	{
	};
	~cSession()
	{
	};

	RunCommand(cCommand &command);
	TerminateCommand();
	GetProgess();

private:
	int m_SessionId;
	int m_State;
};


#endif
