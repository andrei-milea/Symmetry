#ifndef _RESULT_H
#define _RESULT_H

#include <string>
#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>

//#include "command.h"

namespace engine
{

class cSession;
class cCommand;

/*!
  used to retrieve the result after a given command is executed
  helps in the communication between the http_server and the engine
*/
class cResult
{
public:
	cResult(cSession *session = nullptr);
	~cResult();

	void SetResult(const boost::any &result);
	void SetCommand(boost::shared_ptr<cCommand>& command);

	const boost::any& GetResult()const;
	const boost::shared_ptr<cCommand>& GetCommand()const;

private:
	cSession 	*m_Session;
	boost::shared_ptr<cCommand> m_Command;
	boost::any	m_Result;

};

}

#endif


