
#include "getelem_command.h"
#include "group_factory.h"
#include "estimate.h"


cGetElemCommand::cGetElemCommand(std::string &params)
	:cGroupGenCommand(params)
{
};

cGetElemCommand::~cGetElemCommand()
{
};

std::string cGetElemCommand::Execute()
{
	m_Progress = PROGRESS_START;
	ParseParams();	
	m_Progress = PROGRESS_END;

	return "Ana are mere";
};

unsigned int cGetElemCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return estimator.Estimate(*this);
};



