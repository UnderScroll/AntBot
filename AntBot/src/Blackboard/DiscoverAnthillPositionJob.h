#pragma once

#include <vector>
#include "Job.h"
#include "Blackboard.h"

class DiscoverAnthillPositionJob : public Job {
public:
	DiscoverAnthillPositionJob(const int priority = 0, const int maxAssignedAnts = 1, const int targetIndex = 0) : Job(priority, maxAssignedAnts, targetIndex)
	{

	}

	bool isJobComplete() override
	{
		//if we discovered the enemy anthill
		return Blackboard::getState().enemyHills.size() > targetIndex;
	}

	Location task() override
	{
		//Go to a random position in a region
		// TODO BETTER STRATEGY (hardcoded positions ?)
		srand(time(NULL));
		std::vector<Location> regionToExplore = Blackboard::getAllRegions()[rand() % Blackboard::getAllRegions().size()];

		Location locationsWithEnemies = regionToExplore[rand() % regionToExplore.size()];
	return locationsWithEnemies;
	}
};