
#include "getcenter_command.h"
#include "command.h"
#include "group_factory.h"

namespace engine
{

cGetCenterCommand::cGetCenterCommand(const std::string &params, cResult* result)
	:cGroupGenCommand(params, result)
{
};

cGetCenterCommand::~cGetCenterCommand()
{
};

void cGetCenterCommand::Execute()
{
	if(SYMMETRIC_GROUP == GetGroupType())
	{
		SymmGrp symmetric_group;
		for(unsigned int i = 0; i < m_Generators.size(); i++)
		{
			SymmGrpElem generator = boost::any_cast<SymmGrpElem>(m_Generators[i]);
			symmetric_group.AddGenerator(generator);
		}

		std::vector<SymmGrpElem> center_elements = symmetric_group.GetCenterEl();
		m_Result->SetResult(center_elements);
	}
};

unsigned int cGetCenterCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return estimator.Estimate(*this);
};

}


