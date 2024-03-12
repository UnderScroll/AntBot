#pragma once
#include "Strategy.h"

class ActiveExplorationStrategy : Strategy 
{
private :
	int targetPlayerAnthill;
public:
	void ComputeStrategyPriority() override;
	void SetTargetPlayerAnthill(int playerID);
	ActiveExplorationStrategy(std::map<int, std::vector<Job>> steps, int targetPlayerAnthill) : Strategy(steps), targetPlayerAnthill{targetPlayerAnthill}
	{
	};
};