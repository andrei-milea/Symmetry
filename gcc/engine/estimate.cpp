#include "estimate.h"

#include "groupgen_command.h"

namespace engine
{

cEstimator::cEstimator()
{};

cEstimator::~cEstimator()
{};

std::size_t cEstimator::Estimate(const cGetElemCommand& getelem_command)const
{
	return 0;
};

std::size_t cEstimator::Estimate(const cGetSubgrpCommand& getsubgrp_command)const
{
	return 0;
};

}

