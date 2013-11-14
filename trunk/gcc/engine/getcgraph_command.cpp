#include "getcgraph_command.h"
#include "command.h"
#include "group_factory.h"

namespace engine
{

cGetCGraphCommand::cGetCGraphCommand(GROUP_TYPE group_type, const std::vector<boost::any> &generators)
	:cGroupGenCommand(group_type, generators)
{
}

cGetCGraphCommand::~cGetCGraphCommand()
{
}

void cGetCGraphCommand::Execute()
{
	if(SYMMETRIC_GROUP == m_GrpType || CYCLIC_GROUP == m_GrpType || DIHEDRAL_GROUP == m_GrpType)
	{
		SymmGrp symmetric_group;
		for(std::size_t i = 0; i < m_Generators.size(); i++)
		{
			SymmGrpElem generator = boost::any_cast<SymmGrpElem>(m_Generators[i]);
			symmetric_group.AddGenerator(generator);
		}

		std::vector<SymmGrpElem> group_elements = symmetric_group.GetElementsDimino();
		m_Result.initGraph(group_elements, symmetric_group.GetGeneratorsSet());
		m_Result.BuildGraph();
	}
}

unsigned int cGetCGraphCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return estimator.Estimate(*this);
}

}
