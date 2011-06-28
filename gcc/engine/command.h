#ifndef _COMMAND_H
#define _COMMAND_H

#include <string>
#include "estimate.h"

#define PROGRESS_START 1 
#define PROGRESS_END 1000


enum GROUP_TYPE
{
	SYMMETRIC_GROUP
};

class cCommand
{
public:
	virtual ~cCommand()
	{
	};

	virtual void Execute()=0;
	virtual unsigned int EstimateRunTime(const cEstimator &estimator)const=0;

protected://methods
	cCommand()
	:m_Progress(0)
	{};
	virtual void ParseParams()=0;

protected://members
	std::string m_Params;
	int m_Progress;
};


class cGetElemCommand : public cCommand
{
public:
	cGetElemCommand(std::string &params);
	~cGetElemCommand();

	void Execute();
	unsigned int EstimateRunTime(const cEstimator &estimator);

protected:
	virtual void ParseParams();

};

class cGetSubgrpCommand : public cCommand
{
public:
	cGetSubgrpCommand(std::string &params);
	~cGetSubgrpCommand();

	void Execute();
	unsigned int EstimateRunTime(const cEstimator &estimator);

protected:
	void ParseParams();
	BuildGroupElem(const std::string& elem)



private:
	std::vector<string> m_Generators;
	GROUP_TYPE m_GroupType;
};


#endif


