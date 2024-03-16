#pragma once
#include "Strategy.h"

class ActiveExplorationStrategy : public Strategy 
{
private :
	int targetPlayerAnthill; 
	bool isAntHillPositionKnow = false;
public:
	void ComputeStrategyPriority()override 
	{
	};
	ActiveExplorationStrategy(std::map<int, std::vector<Job>> steps, int targetPlayerAnthill) : Strategy(steps), targetPlayerAnthill{ targetPlayerAnthill } {};
};