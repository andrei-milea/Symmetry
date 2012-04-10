#ifndef _ESTIMATE_H
#define _ESTIMATE_H

#include <string>

namespace engine
{

class cGetElemCommand;
class cGetCenterCommand;
class cGetCGraphCommand;
class cGetRelCommand;

/*!
 base class for command estimators
 should be used as a visitor in the command class(Estimate(cEstimator&))
*/
class cEstimator
{
public:
	cEstimator();
	virtual ~cEstimator();

	virtual std::size_t Estimate(const cGetElemCommand& getelem_command)const;
	virtual std::size_t Estimate(const cGetCenterCommand& getcenter_command)const;
	virtual std::size_t Estimate(const cGetCGraphCommand& getcgraph_command)const;
	virtual std::size_t Estimate(const cGetRelCommand& getrel_command)const;
};

}

#endif

