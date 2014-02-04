#ifndef _GROUPGEN_COMMAND_H
#define _GROUPGEN_COMMAND_H

#include "command.h"
#include "group_gen_parser.h"

#include <sstream>

namespace engine
{

/*!
  holds data common to group commands
*/
class cGroupGenCommand : public cCommand
{
public:
	cGroupGenCommand(GROUP_TYPE group_type, const std::vector<boost::any> &generators)
		:m_GrpType(group_type),
		m_Generators(generators)
	{};

	virtual ~cGroupGenCommand()
	{
	};

	const GROUP_TYPE GetGroupType()const
	{	return m_GrpType;	}

	std::string GetResultStr()const
	{
		std::stringstream ss;
		std::string result_str;
		if(SYMMETRIC_GROUP != m_GrpType && CYCLIC_GROUP != m_GrpType && DIHEDRAL_GROUP != m_GrpType)
			throw std::runtime_error(CONTEXT_STR + "invalid group type");

		result_str = "<br/>Elements: <br/><br/><ul id='list-elem'>";
		std::string perm_str;
		for(std::size_t index = 0; index < m_Result.size(); index++)
		{
			ss.str("");
			ss << m_Result[index];
			perm_str = ss.str();
			perm_str.replace(perm_str.find("\n"), 1, "<br/>");
			result_str += "<li>" + perm_str + "</li>";
		}
		result_str += "</ul><br/><br/>";
		return result_str;
	}

	const std::vector<boost::any>& GetGenerators()const
	{	return m_Generators;	};

protected:
	GROUP_TYPE m_GrpType;
	std::vector<boost::any>  m_Generators;
	std::vector<SymmGrpElem> m_Result;
};

}
#endif

