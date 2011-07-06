#ifndef _SESSION_H
#define _SESSION_H

#include <string>
class cCommand;

class cSession
{
public:
	cSession();
	cSession(unsigned int ses_id);
	~cSession();

	const std::string RunCommand(cCommand &command);
	void TerminateCommand();
	unsigned int GetProgess();

private:
	int m_SessionId;
	int m_State;
};


#endif
