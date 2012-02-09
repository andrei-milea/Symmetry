
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
	GROUP_TYPE type = GetGroupType();
	if(SYMMETRIC_GROUP == type)
	{
		SymmGrp symmetric_group;
		for(unsigned int i = 0; i < m_Generators.size(); i++)
		{
			SymmGrpElem generator = boost::any_cast<SymmGrpElem>(m_Generators[i]);
			symmetric_group.AddGenerator(generator);
		}
		std::vector<SymmGrpElem> group_elements = symmetric_group.GetElementsDimino();
		std::vector<SymmGrpElem> center_elements = symmetric_group.GetCenterEl(group_elements);
		m_Result->SetResult(center_elements);
	}
	else if(CYCLIC_GROUP == type)
	{
		SymmGrp symmetric_group;
		SymmGrpElem generator = boost::any_cast<SymmGrpElem>(m_Generators[0]);
		std::vector<SymmGrpElem> group_elements = symmetric_group.GetCyclicSubgroupEl(generator.GetSize());
		std::vector<SymmGrpElem> center_elements = symmetric_group.GetCenterEl(group_elements);
		m_Result->SetResult(center_elements);
	}
	else if(DIHEDRAL_GROUP == type)
	{
		SymmGrp symmetric_group;
		SymmGrpElem generator = boost::any_cast<SymmGrpElem>(m_Generators[0]);
		std::vector<SymmGrpElem> group_elements = symmetric_group.GetDihedralSubgroupEl(generator.GetSize());
		std::vector<SymmGrpElem> center_elements = symmetric_group.GetCenterEl(group_elements);
		m_Result->SetResult(center_elements);
	}
};

unsigned int cGetCenterCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return estimator.Estimate(*this);
};

}


