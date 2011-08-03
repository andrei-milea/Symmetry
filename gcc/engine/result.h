#ifndef _RESULT_H
#define _RESULT_H

#include <string>

class cCommand;
class cSession;

class cResult
{
public:
	cResult(cSession *session = NULL, cCommand *command = NULL);
	~cResult();

	void SetResultStr(const std::string& result);
	void SetCommand(cCommand *command);
	const std::string& GetResultStr()const;
	const cCommand *GetCommand()const;

private:
	cSession 	*m_Session;
	cCommand 	*m_Command;
	std::string m_Result_str;
};


#endif


