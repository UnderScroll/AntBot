#pragma once
#include "Strategy.h"

class OccupyRegionStrategy : public Strategy 
{
private:
	int regionIndex;

public:
	void ComputeStrategyPriority()override
	{
		//TODO : if the region has few to no enemy in it, assign one ant to take its food
	};
	OccupyRegionStrategy(std::map<int, std::vector<Job>> steps, int regionIndex) : Strategy(steps), regionIndex{ regionIndex } {};
};