#pragma once
#include "Strategy.h"

#include "../Logger/Logger.h"

class ActiveExplorationStrategy : public Strategy 
{
private :
	int targetPlayerAnthill; 
	float turnInterestMultiplier = .1f;
public:
	void computeStrategyPriority() override
	{
		//If we know the anthill position, this is void of interest
		if (Blackboard::getState().enemyHills.size() >= targetPlayerAnthill - 1)
			priority = -1;
		//If we don't, it gets more interesting as the game progresses
		else 
			priority = ceil(Blackboard::getState().turn * turnInterestMultiplier);

		Strategy::computeStrategyPriority();
	};
	ActiveExplorationStrategy(std::map<int, std::vector<std::shared_ptr<Job>>> steps, int targetPlayerAnthill) : Strategy(steps), targetPlayerAnthill{ targetPlayerAnthill } {};
};