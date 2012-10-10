#ifndef _GETREL_COMMAND_H
#define _GETREL_COMMAND_H

#include "groupgen_command.h"

namespace engine
{

class cEstimator;

/*!
  command that obtains Cayley graph of the group
*/
class cGetRelCommand : public cGroupGenCommand
{
public:
	cGetRelCommand(GROUP_TYPE group_type, const std::vector<boost::any> &generators);
	virtual ~cGetRelCommand();

	void Execute();
	unsigned int EstimateRunTime(const cEstimator &estimator)const;

	const std::vector<cGroupRelation> &GetResult()const
	{	return m_Result;	};

private:
	std::vector<cGroupRelation> m_Result;
};

}

#endif

