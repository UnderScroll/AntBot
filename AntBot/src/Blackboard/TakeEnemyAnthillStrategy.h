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

		std::vector regionToCheck = Blackboard::getAllRegions()[regionIndex];
		int enemiesInRegion = 0;
		int knownTiles = 0;

		//Computing the amount of seeable tiles and enemies in the region
		for (size_t i = 0; i < regionToCheck.size(); i++)
		{
			Location locationToCheck = regionToCheck[i];

			if (!Blackboard::getState().grid[locationToCheck.row][locationToCheck.col].isVisible)
			{
				continue;
			}

			else
			{
				knownTiles++;

				for (size_t j = 0; j < Blackboard::getState().enemyAnts.size(); j++)
				{
					Location enemyPosition = Blackboard::getState().enemyAnts[i];

					if (enemyPosition.col == locationToCheck.col && enemyPosition.row == locationToCheck.row)
					{
						enemiesInRegion++;
					}
				}
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

	TakeEnemyAnthillStrategy(std::map<int, std::vector<Job>> steps, int targetAnthill) : Strategy(steps), targetAnthill{ targetAnthill } {};
};