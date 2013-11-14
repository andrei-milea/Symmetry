
#include "getcenter_command.h"
#include "command.h"
#include "group_factory.h"

namespace engine
{

cGetCenterCommand::cGetCenterCommand(GROUP_TYPE group_type, const std::vector<boost::any> &generators)
	:cGroupGenCommand(group_type, generators)
{
}

cGetCenterCommand::~cGetCenterCommand()
{
}

void cGetCenterCommand::Execute()
{
	if(SYMMETRIC_GROUP == m_GrpType)
	{
		SymmGrp symmetric_group;
		for(unsigned int i = 0; i < m_Generators.size(); i++)
		{
			SymmGrpElem generator = boost::any_cast<SymmGrpElem>(m_Generators[i]);
			symmetric_group.AddGenerator(generator);
		}
		std::vector<SymmGrpElem> group_elements = symmetric_group.GetElementsDimino();
		m_Result = symmetric_group.GetCenterEl(group_elements);
	}
	else if(CYCLIC_GROUP == m_GrpType)
	{
		SymmGrp symmetric_group;
		SymmGrpElem generator = boost::any_cast<SymmGrpElem>(m_Generators[0]);
		std::vector<SymmGrpElem> group_elements = symmetric_group.GetCyclicSubgroupEl(generator.GetSize());
		m_Result = symmetric_group.GetCenterEl(group_elements);
	}
	else if(DIHEDRAL_GROUP == m_GrpType)
	{
		SymmGrp symmetric_group;
		SymmGrpElem generator = boost::any_cast<SymmGrpElem>(m_Generators[0]);
		std::vector<SymmGrpElem> group_elements = symmetric_group.GetDihedralSubgroupEl(generator.GetSize());
		m_Result = symmetric_group.GetCenterEl(group_elements);
	}
}

unsigned int cGetCenterCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return estimator.Estimate(*this);
}

}


