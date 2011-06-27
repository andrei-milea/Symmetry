#ifndef _SESSION_H
#define _SESSION_H

#include "group_factory.h"
#include "command.h"



class cSession
{
public:
	cSession();
	~cSession();

	const string RunCommand(cCommand &command);
	void TerminateCommand();
	unsigned int GetProgess();

private:
	int m_SessionId;
	int m_State;
};


#endif
