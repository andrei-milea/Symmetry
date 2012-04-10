#include "getrel_command.h"
#include "command.h"
#include "group_factory.h"

namespace engine
{

cGetRelCommand::cGetRelCommand(const std::string &params, cResult& result)
	:cGroupGenCommand(params, result)
{
};

cGetRelCommand::~cGetRelCommand()
{
};

void cGetRelCommand::Execute()
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
		graph.BuildDefRelations();
		auto def_relations = graph.GetDefRelations();
		for(auto it = def_relations.begin(); it != def_relations.end(); it++)
			it->Simplify();
		m_Result.SetResult(def_relations);
	}
};

unsigned int cGetRelCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return estimator.Estimate(*this);
};

}
