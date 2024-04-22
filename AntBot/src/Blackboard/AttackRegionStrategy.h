#pragma once
#include "Strategy.h"

class AttackRegionStrategy : public Strategy
{
private :
	int regionIndex;
	int priorityMultiplier = .01;
public :
	void computeStrategyPriority()override
	{
		std::vector regionToCheck = Blackboard::getAllRegions()[regionIndex];
		int enemiesInRegion = 0;
		int knownTiles = 0;

		//Computing the amount of unseeable tiles and enemies in the region
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
			priority = (Blackboard::getState().myAnts.size() / enemiesInRegion) * knownTiles * priorityMultiplier;

			Strategy::computeStrategyPriority();
	};

	AttackRegionStrategy(std::map<int, std::vector<Job>> steps, int regionIndex) : Strategy(steps), regionIndex{ regionIndex } {};
};