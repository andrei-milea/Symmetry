
#include "getelem_command.h"
#include "group_factory.h"
#include "estimate.h"
#include "serializer.h"

namespace engine
{

cGetElemCommand::cGetElemCommand(GROUP_TYPE group_type, const std::vector<boost::any> &generators)
	:cGroupGenCommand(group_type, generators)
{
}

cGetElemCommand::~cGetElemCommand()
{
}

void cGetElemCommand::Execute()
{
	if( SYMMETRIC_GROUP == m_GrpType )
	{
		SymmGrp symmetric_group;
		for(unsigned int i = 0; i < m_Generators.size(); i++)
		{
			SymmGrpElem generator = boost::any_cast<SymmGrpElem>(m_Generators[i]);
			symmetric_group.AddGenerator(generator);
		}

		 m_Result = symmetric_group.GetElementsDimino();
	}
	else if(CYCLIC_GROUP == m_GrpType)
	{
		SymmGrp symmetric_group;
		SymmGrpElem generator = boost::any_cast<SymmGrpElem>(m_Generators[0]);
		m_Result = symmetric_group.GetCyclicSubgroupEl(generator.GetSize());
	}
	else if(DIHEDRAL_GROUP == m_GrpType)
	{
		SymmGrp symmetric_group;
		SymmGrpElem generator = boost::any_cast<SymmGrpElem>(m_Generators[0]);
		m_Result = symmetric_group.GetDihedralSubgroupEl(generator.GetSize());
	}
}

unsigned int cGetElemCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return estimator.Estimate(*this);
}

}


