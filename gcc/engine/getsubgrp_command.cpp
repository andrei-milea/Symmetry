
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
	if(SYMMETRIC_GROUP == GetGroupType())
	{
		SymmGrp symmetric_group;
		for(unsigned int i = 0; i < m_Generators.size(); i++)
		{
			SymmGrpElem generator = boost::any_cast<SymmGrpElem>(m_Generators[i]);
			symmetric_group.AddGenerator(generator);
		}

		std::vector<SymmGrpElem> group_elements = symmetric_group.GetElementsDimino();
		std::vector<SymmGrpElem> group_elements = symmetric_group.GetElementsDimino();
		m_Result->SetResult(group_elements);
	}
};

unsigned int cGetSubgrpCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return estimator.Estimate(*this);
};



