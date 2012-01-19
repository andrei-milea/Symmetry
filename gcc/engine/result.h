#ifndef _RESULT_H
#define _RESULT_H

#include <string>
#include <boost/any.hpp>

namespace engine
{

class cCommand;
class cSession;

class cResult
{
public:
	cResult(cSession *session = NULL, cCommand *command = NULL);
	~cResult();

	void SetResult(const boost::any &result);
	void SetCommand(cCommand *command);

	const boost::any& GetResult()const;
	const cCommand *GetCommand()const;

private:
	cSession 	*m_Session;
	cCommand 	*m_Command;
	boost::any	m_Result;

};

}

#endif


