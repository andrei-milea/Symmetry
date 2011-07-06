#ifndef _ESTIMATE_H
#define _ESTIMATE_H

class cGetElemCommand;
class cGetSubgrpCommand;

#include <string>

//estimate time in minutes
class cEstimator
{
public:
	cEstimator();
	virtual ~cEstimator();

	virtual std::size_t Estimate(const cGetElemCommand& getelem_command)const;
	virtual std::size_t Estimate(const cGetSubgrpCommand& getsubgrp_command)const;
};

#endif

