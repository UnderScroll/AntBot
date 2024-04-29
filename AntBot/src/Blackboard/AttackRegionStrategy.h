#pragma once
#include "Strategy.h"
#include <string>
#include "../Logger/Logger.h"

class AttackRegionStrategy : public Strategy
{
private:
	int regionIndex;
	int priorityMultiplier = .01;
public:
	void computeStrategyPriority()override
	{
		std::vector<Location>& r_regionToCheck = Blackboard::getAllRegions()[regionIndex];
		int enemiesInRegion = 0;
		int knownTiles = 0;

		//Computing the amount of unseeable tiles and enemies in the region
		for (int i = 0; i < r_regionToCheck.size(); i++)
		{
			Location& r_locationToCheck = r_regionToCheck[i];

			if (!Blackboard::getState().grid[r_locationToCheck.row][r_locationToCheck.col].isVisible) continue;


			knownTiles++;

			for (size_t j = 0; j < Blackboard::getState().enemyAnts.size(); j++)
			{
				Location& r_enemyPosition = Blackboard::getState().enemyAnts[j];

				if (r_enemyPosition.col == r_locationToCheck.col && r_enemyPosition.row == r_locationToCheck.row)
					enemiesInRegion++;
			}
		}

		if (enemiesInRegion != 0)
			priority = (Blackboard::getState().myAnts.size() / enemiesInRegion) * knownTiles * priorityMultiplier;
		else
			priority = Blackboard::getState().myAnts.size() * knownTiles * priorityMultiplier;

		Strategy::computeStrategyPriority();
	};

	AttackRegionStrategy(std::map<int, std::vector<std::shared_ptr<Job>>> steps, int regionIndex) : Strategy(steps), regionIndex{ regionIndex } {};
};