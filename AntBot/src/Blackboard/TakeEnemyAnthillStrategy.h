#pragma once
#include "Strategy.h"

class TakeEnemyAnthillStrategy : public Strategy {
private:
	//-1 is unknown region
	int regionIndex = -1;
	int targetAnthill = 0;
	int priorityMultiplier = 10;

public:
	void computeStrategyPriority()override
	{
		//if we don't know the region of the anthill
		if (regionIndex == -1)
		{
			priority = -1;
			return;
		}

		std::vector<Location> r_regionToCheck = Blackboard::getAllRegions()[regionIndex];
		int enemiesInRegion = 0;
		int knownTiles = 0;

		//Computing the amount of seeable tiles and enemies in the region
		for (size_t i = 0; i < r_regionToCheck.size(); i++)
		{
			Location& r_locationToCheck = r_regionToCheck[i];

			if (!Blackboard::getState().grid[r_locationToCheck.row][r_locationToCheck.col].isVisible)
				continue;

			knownTiles++;

			for (size_t j = 0; j < Blackboard::getState().enemyAnts.size(); j++)
			{
				Location& r_enemyPosition = Blackboard::getState().enemyAnts[i];

				if (r_enemyPosition.col == r_locationToCheck.col && r_enemyPosition.row == r_locationToCheck.row)
					enemiesInRegion++;
			}
		}

		if (enemiesInRegion > 0)
			priority = (1 / enemiesInRegion) * priorityMultiplier;
		else
			priority = priorityMultiplier;

		Strategy::computeStrategyPriority();
	};

	void OnAnthillDiscovered(int discoveredRedionIndex)
	{
		regionIndex = discoveredRedionIndex;
	}

	TakeEnemyAnthillStrategy(std::map<int, std::vector<std::shared_ptr<Job>>> steps, int targetAnthill) : Strategy(steps), targetAnthill{ targetAnthill } {};
};