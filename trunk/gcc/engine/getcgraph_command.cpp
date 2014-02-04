#include "getcgraph_command.h"
#include "command.h"
#include "group_factory.h"

#include <sstream>

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


std::string cGetCGraphCommand::GetResultStr()const
{
	std::string result_str;
	std::stringstream ss;

	if(SYMMETRIC_GROUP != m_GrpType && CYCLIC_GROUP != m_GrpType && DIHEDRAL_GROUP != m_GrpType)
		throw std::runtime_error(CONTEXT_STR + "invalid group type");

	result_str = "<br/>Cayley Graph representation as adjacency list:<br/>";
	std::stringstream redirectstream;
	std::streambuf* oldbuf = std::cout.rdbuf(redirectstream.rdbuf());
	std::string str;
	std::cout << m_Result;
	while(std::getline(redirectstream, str))
	{
		ss << str << "<br/>";
	}
	//put back the old stream buffer
	std::cout.rdbuf(oldbuf);

	result_str += ss.str();
	return result_str;
}

unsigned int cGetCGraphCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return estimator.Estimate(*this);
}

}
