
#include "command.h"
#include "group_factory.h"

cGetSubgrpCommand::cCreateCommand(std::string &params)
{
	m_Params = params;
	ParseParams();
};

void cGetSubgrpCommand::ParseParams()
{

};

cGetSubgrpCommand::Execute()
{
	m_Progress = PROGRESS_START;

	if(SYMMETRIC_GROUP == m_GroupType)
		SymmGrp symmetryc_group = cGroupFactory::GetInstance()->GetSymmGrp();

	while(m_Generators::iterator it = m_Generators.begin(); it != m_Generators.end(); it++)
		symmetryc_group->AddGenerator()


	m_Progress = PROGRESS_END;
};

unsigned int cGetSubgrpCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return estimator->EstimateCreate(*this);
};



