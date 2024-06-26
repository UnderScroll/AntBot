#pragma once

#include <vector>
#include <algorithm>

#include "Job.h"
#include ".//Logger/Logger.h"

class ExploreZoneJob : public Job {
public:
	ExploreZoneJob(const int priority = 0, const int maxAssignedAnts = 1, const int targetIndex = 0) : Job(priority, maxAssignedAnts, targetIndex)
	{

	}

	bool isJobComplete() override
	{
		//This is a "passive" job, we always want to have a few ants here and theere in every region to gather food
		return false;
	}

	Location task() override
	{
		//Return a position with food in the zone if there is one, or a random position in the region we are trying to explore
		std::vector<Location>& r_locationsInRegion = Blackboard::getAllRegions()[targetIndex];

		std::vector<Location> foods = Blackboard::getState().food;

		//TODO : optimize
		for (size_t i = 0; i < r_locationsInRegion.size(); i++)
		{
			for (size_t j = 0; j < foods.size(); j++)
			{
				if (foods[j].col == r_locationsInRegion[i].col && foods[j].row == r_locationsInRegion[i].row)
				{
					return r_locationsInRegion[i];
				}
			}
		}

		//No food was found : picking a random position in the region
		srand(time(NULL));
		int randomIndex = rand() % r_locationsInRegion.size();

		return r_locationsInRegion[randomIndex];
	}
};