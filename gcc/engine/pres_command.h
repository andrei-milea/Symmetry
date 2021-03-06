#ifndef _PRES_COMMAND_H
#define _PRES_COMMAND_H

#include "command.h"

#include <string>

namespace engine
{

class cPresCommand : public cCommand
{
public:
	cPresCommand(const std::string &param);

	~cPresCommand(){}
	
	void Execute();

	unsigned int EstimateRunTime(const cEstimator &estimator)const;

	std::string GetResultStr()const
	{
		return m_Result;
	}

private:
	void Dir();
	void Save();
	void Load();
	void Download();
	void createSlidesImgs();



private:
	std::string m_Result;
	std::string m_PresName;
	std::string m_PresCommand;
	std::string m_Html;
};

}


#endif

