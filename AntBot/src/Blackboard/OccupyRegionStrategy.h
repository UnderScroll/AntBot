#pragma once
#include "Strategy.h"

class OccupyRegionStrategy : public Strategy
{
private:
	int regionIndex;

public:
	void computeStrategyPriority() override
	{
		std::vector<Location>& r_regionToCheck = Blackboard::getAllRegions()[regionIndex];
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
				Location& r_enemyPosition = Blackboard::getState().enemyAnts[j];

				if (r_enemyPosition.col == r_locationToCheck.col && r_enemyPosition.row == r_locationToCheck.row)
					enemiesInRegion++;
			}
		}

		if (enemiesInRegion > 0)
			priority = knownTiles / enemiesInRegion;
		else
			priority = knownTiles;

		Strategy::computeStrategyPriority();

	};

	OccupyRegionStrategy(std::map<int, std::vector<std::shared_ptr<Job>>> steps, int regionIndex) : Strategy(steps), regionIndex{ regionIndex } {};
};