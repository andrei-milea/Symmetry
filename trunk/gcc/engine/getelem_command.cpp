#include "command.h"


cGetElemCommand::cSelectCommand(std::string &params)
{
	m_Params = params;
};

cGetElemCommand::Execute()
{
	m_Progress = PROGRESS_START;



	m_Progress = PROGRESS_END;
};

unsigned int cGetElemCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return estimator->EstimateSelect(*this);
};


