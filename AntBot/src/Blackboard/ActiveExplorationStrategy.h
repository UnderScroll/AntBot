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
		//TODO : if we are late into the game, and that there are many anthills that we don't know
	};
	ActiveExplorationStrategy(std::map<int, std::vector<Job>> steps, int targetPlayerAnthill) : Strategy(steps), targetPlayerAnthill{ targetPlayerAnthill } {};
};