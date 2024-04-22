#pragma once
#include <map>
#include <vector>
#include "Job.h"

class Strategy
{
protected:
	int currentJobIndex;
	int priority;
	std::map<int, std::vector<Job>> steps;

public :
	int GetPriority() { return priority; }

	virtual void ComputeStrategyPriority()
	{
		for (size_t i = 0; i < steps[currentJobIndex].size(); i++)
		{
			steps[currentJobIndex][i].priority = priority;
		}
	};

	Strategy(std::map<int, std::vector<Job>> steps) : steps{steps}
	{
		currentJobIndex = 0;
		priority = 0;
	}

	~Strategy()
	{
		//TODO
	}
};