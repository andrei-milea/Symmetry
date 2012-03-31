#include "getcgraph_command.h"
#include "command.h"
#include "group_factory.h"

namespace engine
{

cGetCGraphCommand::cGetCGraphCommand(const std::string &params, cResult& result)
	:cGroupGenCommand(params, result)
{
};

cGetCGraphCommand::~cGetCGraphCommand()
{
};

void cGetCGraphCommand::Execute()
{
	GROUP_TYPE type = GetGroupType();
	if(SYMMETRIC_GROUP == type || CYCLIC_GROUP == type || DIHEDRAL_GROUP == type)
	{
		SymmGrp symmetric_group;
		for(unsigned int i = 0; i < m_Generators.size(); i++)
		{
			SymmGrpElem generator = boost::any_cast<SymmGrpElem>(m_Generators[i]);
			symmetric_group.AddGenerator(generator);
		}

		std::vector<SymmGrpElem> group_elements = symmetric_group.GetElementsDimino();
		cCayleyGrf<SymmGrp> graph(symmetric_group);
		graph.BuildGraph();
		m_Result.SetResult(graph);
	}
};

unsigned int cGetCGraphCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return estimator.Estimate(*this);
};

}
