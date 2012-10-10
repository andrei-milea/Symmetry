#ifndef _GETCGRAPH_COMMAND_H
#define _GETCGRAPH_COMMAND_H

#include "groupgen_command.h"

namespace engine
{

class cEstimator;

/*!
  command that obtains Cayley graph of the group
*/
class cGetCGraphCommand : public cGroupGenCommand
{
public:
	cGetCGraphCommand(GROUP_TYPE group_type, const std::vector<boost::any> &generators);
	virtual ~cGetCGraphCommand();

	void Execute();
	unsigned int EstimateRunTime(const cEstimator &estimator)const;
	const cCayleyGrf<SymmGrp> &GetResult()const
	{	return m_Result;	};
private:
	cCayleyGrf<SymmGrp> m_Result;
};

}

#endif

