#pragma once

#include <vector>
#include "Job.h"
#include "Blackboard.h"

class AttackZoneJob : public Job {
private :
	std::vector<Location> getLocationsWithEnemiesInRegion()
	{
		std::vector<Location> locationWithEnemiesInRegion = std::vector<Location>();

		for (size_t i = 0; i < Blackboard::getState().enemyAnts.size(); i++)
		{
			for (size_t j = 0; j < Blackboard::getAllRegions()[targetIndex].size(); j++)
			{
				Location enemyAntLocation = Blackboard::getState().enemyAnts[i];
				Location currentLocation = Blackboard::getAllRegions()[targetIndex][j];
				
				if (enemyAntLocation.col == currentLocation.col && enemyAntLocation.row == currentLocation.row)
					locationWithEnemiesInRegion.push_back(currentLocation);
			}
		}

		return Blackboard::getState().enemyAnts;
	}

	Location getLocationInZoneWithEnemies()
	{
		Location zoneWithEnemies; 

		std::vector<Location> locationsWithEnemiesInRegion = getLocationsWithEnemiesInRegion();

		std::vector<Location> enemies = Blackboard::getState().enemyAnts;

		//TODO : optimize
		for (size_t i = 0; i < locationsWithEnemiesInRegion.size(); i++)
			for (size_t j = 0; j < enemies.size(); j++)
				if (enemies[j].col == locationsWithEnemiesInRegion[i].col && enemies[j].row == locationsWithEnemiesInRegion[i].row)
					return locationsWithEnemiesInRegion[i];

		//No enemy was found : picking a random position in the region
		srand(time(NULL));
		int randomIndex = rand() % locationsWithEnemiesInRegion.size();
		return locationsWithEnemiesInRegion[randomIndex];
	}
public:
	AttackZoneJob(const int priority = 0, const int maxAssignedAnts = 1, const int targetIndex = 0) : Job(priority, maxAssignedAnts, targetIndex)
	{

	}

	bool isJobComplete() override
	{
		//check if enemies are in the region
		return getLocationsWithEnemiesInRegion().size() == 0;
	}

	Location task() override
	{
		//Return a postion where there is an ant in the chosen region
		//If none is found, return a random position in the region, 
		// but this REALLY shouldn't happen, since this would mean the job is useless

		Location locationsWithEnemies = getLocationInZoneWithEnemies();

		return locationsWithEnemies;
	}
};