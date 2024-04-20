#pragma once
#include "Strategy.h"

class AttackRegionStrategy : public Strategy
{
private :
	int regionIndex;
public :
	void ComputeStrategyPriority()override
	{
		//TODO If we have enough ants, ideally close by, and the region is next to a region we already occupy
	};

	AttackRegionStrategy(std::map<int, std::vector<Job>> steps, int regionIndex) : Strategy(steps), regionIndex{ regionIndex } {};
};