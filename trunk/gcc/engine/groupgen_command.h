#ifndef _GROUPGEN_COMMAND
#define _GROUPGEN_COMMAND

#include "command.h"
#include "group_gen_parser.h"

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

	virtual GROUP_TYPE GetGroupType()
	{	return m_GrpType;	}

	const std::vector<SymmGrpElem> &GetResult()const
	{	return m_Result;	};

protected:
	GROUP_TYPE m_GrpType;
	std::vector<boost::any>  m_Generators;
	std::vector<SymmGrpElem> m_Result;
};

}
#endif

