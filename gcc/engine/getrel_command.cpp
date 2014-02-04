#include "getrel_command.h"
#include "command.h"
#include "group_factory.h"

#include <sstream>

namespace engine
{

cGetRelCommand::cGetRelCommand(GROUP_TYPE group_type, const std::vector<boost::any> &generators)
	:cGroupGenCommand(group_type, generators)
{
}

cGetRelCommand::~cGetRelCommand()
{
}

void cGetRelCommand::Execute()
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
		cCayleyGrf<SymmGrp> graph(symmetric_group);
		graph.BuildGraph();
		graph.BuildDefRelations();
		m_Result = graph.GetDefRelations();
		for(auto it = m_Result.begin(); it != m_Result.end(); it++)
			it->Simplify();
	}
}


std::string cGetRelCommand::GetResultStr()const
{
	std::string result_str;
	std::stringstream ss;
	if(SYMMETRIC_GROUP != m_GrpType && CYCLIC_GROUP != m_GrpType && DIHEDRAL_GROUP != m_GrpType)
		throw std::runtime_error(CONTEXT_STR + "invalid group type");

	result_str = "<br/>Defining Relations:</br></br>";
	std::string str;

	ss.str("");
	std::size_t index = 1;
	for(auto rel_iter = m_Result.begin(); rel_iter != m_Result.end(); rel_iter++)
	{
		ss << index << ". $" << *rel_iter << "$<br/>";
		index++;
	}	
	result_str += ss.str();
	return result_str;
}

unsigned int cGetRelCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return estimator.Estimate(*this);
}

}
