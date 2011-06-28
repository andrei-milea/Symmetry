#ifndef _COMMAND_H
#define _COMMAND_H

#include <string>

#define PROGRESS_START 1 
#define PROGRESS_END 1000

class cCommand
{
public:
	virtual ~cCommand()
	{
	};

	virtual void Execute()=0;

protected://methods
	cCommand()
	:m_Progress(0)
	{};
	
protected://members
	std::string m_Params;
	int m_Progress;
};


//getsubgroup
class cSelectCommand : public cCommand
{
public:
	cSelectCommand(std::string &params);
	~cSelectCommand();

	void Execute();

};

//get elements
class cCreateCommand : public cCommand
{
public:
	cCreateCommand(std::string &params);
	~cCreateCommand();

	void Execute();

};


#endif


