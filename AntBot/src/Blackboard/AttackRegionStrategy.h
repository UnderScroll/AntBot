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
		LOG(Logger::Trace, "getAllregions");
		std::vector regionToCheck = Blackboard::getAllRegions()[regionIndex];
		int enemiesInRegion = 0;
		int knownTiles = 0;

		LOG(Logger::Trace, "start first loop");
		LOG(Logger::Trace, "Grid size : Row : " + std::to_string(Blackboard::getState().grid.size()));
		LOG(Logger::Trace, "Grid size : Col : " + std::to_string(Blackboard::getState().grid[0].size()));
		//Computing the amount of unseeable tiles and enemies in the region
		for (int i = 0; i < regionToCheck.size(); i++)
		{
			Location locationToCheck = regionToCheck[i];

			LOG(Logger::Trace, "Row : " + std::to_string(locationToCheck.row) + "Col: " + std::to_string(locationToCheck.col));

			if (!Blackboard::getState().grid[locationToCheck.row][locationToCheck.col].isVisible)
			{
				LOG(Logger::Trace, "Skipping invisible tile");
				continue;
			}

			else
			{
				knownTiles++;
				LOG(Logger::Trace, "Checking for enemy");

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

		LOG(Logger::Trace, "calculating priority");
		if (enemiesInRegion != 0)
			priority = (Blackboard::getState().myAnts.size() / enemiesInRegion) * knownTiles * priorityMultiplier;
		else
			priority = Blackboard::getState().myAnts.size() * knownTiles * priorityMultiplier;

		Strategy::computeStrategyPriority();
	};

	AttackRegionStrategy(std::map<int, std::vector<std::shared_ptr<Job>>> steps, int regionIndex) : Strategy(steps), regionIndex{ regionIndex } {};
};