#pragma once
#include <map>
#include <vector>
#include "Blackboard.h"
#include "Job.h"

#include "../Logger/Logger.h"

class Strategy
{
protected:
	int currentJobIndex;
	int priority;
	std::map<int, std::vector<std::shared_ptr<Job>>> steps;

public :
	int GetPriority() { return priority; }

	virtual void computeStrategyPriority()
	{
		for (size_t i = 0; i < steps[currentJobIndex].size(); i++)
		{
			steps[currentJobIndex][i]->priority = priority;
		}
	}

	void assignMaxAnt(int maxAnt)
	{
		for (size_t i = 0; i < steps[currentJobIndex].size(); i++)
			steps[currentJobIndex][i]->maxAssignedAnts = ceil(maxAnt / steps[currentJobIndex].size());
	}

	void setJobsToBlackboard()
	{
		for (size_t i = 0; i < steps[currentJobIndex].size(); i++)
		{
			Blackboard::addJob(*steps[currentJobIndex][i]);
		}
	}

	Strategy(std::map<int, std::vector<std::shared_ptr<Job>>> steps) : steps{steps}
	{
		currentJobIndex = 0;
		priority = 0;
	}

	~Strategy()
	{
	}
};