
#include "getsubgrp_command.h"
#include "command.h"
#include "group_factory.h"

cGetSubgrpCommand::cGetSubgrpCommand(std::string &params)
	:cGroupGenCommand(params)
{
};

cGetSubgrpCommand::~cGetSubgrpCommand()
{
};

std::string cGetSubgrpCommand::Execute()
{
	m_Progress = PROGRESS_START;

	ParseParams();

//	if(SYMMETRIC_GROUP == m_GroupType)
//		SymmGrp symmetryc_group = cGroupFactory::GetInstance()->GetSymmGrp();
//
//	while(m_Generators::iterator it = m_Generators.begin(); it != m_Generators.end(); it++)
//		symmetryc_group->AddGenerator()


	m_Progress = PROGRESS_END;
	return "Ana are mere";
};

unsigned int cGetSubgrpCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return estimator.Estimate(*this);
};



