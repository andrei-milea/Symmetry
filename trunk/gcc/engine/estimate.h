#ifndef _ESTIMATE_H
#define _ESTIMATE_H

//estimate time in minutes
class cEstimator
{
public:
	cEstimator()
	{};
	virtual ~cEstimator()
	{};

	virtual unsigned int EstimateCreate(const cGetElemCommand& getelem_command);
	virtual unsigned int EstimateSelect(const cGetSubgrpCommand& getsubgrp_command);
};

#endif

