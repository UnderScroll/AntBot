#pragma once
#include "Strategy.h"

class TakeEnemyAnthillStrategy : public Strategy {
private:
	//-1 is unknown region
	int regionIndex = -1;
	int targetAnthill = 0;

public:
	void ComputeStrategyPriority()override
	{
		//TODO If we have enough ants, ideally close by, && if we know where the anthill is
	};

	void OnAnthillDiscovered(int discoveredRedionIndex) 
	{
		regionIndex = discoveredRedionIndex;
	}

	TakeEnemyAnthillStrategy(std::map<int, std::vector<Job>> steps, int targetAnthill) : Strategy(steps), targetAnthill{ targetAnthill } {};
};