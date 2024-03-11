#pragma once
#include <map>
#include <vector>
#include "Job.h"

class Strategy
{
private:
	int currentJobIndex;
	std::map<int, std::vector<Job>> steps;

public :
	virtual void ComputeStrategyPriority();
};