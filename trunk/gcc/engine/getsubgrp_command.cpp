
#include "getsubgrp_command.h"
#include "command.h"
#include "group_factory.h"

cGetSubgrpCommand::cGetSubgrpCommand(const std::string &params, cResult* result)
	:cGroupGenCommand(params, result)
{
};

cGetSubgrpCommand::~cGetSubgrpCommand()
{
};

void cGetSubgrpCommand::Execute()
{

	ParseParams();

//	if(SYMMETRIC_GROUP == m_GroupType)
//		SymmGrp symmetryc_group = cGroupFactory::GetInstance()->GetSymmGrp();
//
//	while(m_Generators::iterator it = m_Generators.begin(); it != m_Generators.end(); it++)
//		symmetryc_group->AddGenerator()


};

unsigned int cGetSubgrpCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return estimator.Estimate(*this);
};



