#pragma once

#include <vector>
#include "Job.h"
#include "Blackboard.h"

class AttackEnemyAnthillJob : public Job {
public:
	AttackEnemyAnthillJob(const int priority = 0, const int maxAssignedAnts = 1, const int targetIndex = 0) : Job(priority, maxAssignedAnts, targetIndex)
	{

	}

	bool isJobComplete() override
	{
		//if we took the enemy hill
		Location targetHill = Blackboard::getState().enemyHills[targetIndex];

		for (size_t i = 0; i < Blackboard::getState().takenEnemyHills.size(); i++)
		{
			Location takenHill = Blackboard::getState().takenEnemyHills[i];
			if (targetHill.col == takenHill.col && targetHill.row == takenHill.row)
				return true;
		}

		return false;
	}

	Location task() override
	{
		//rush to enemy anthill
		return Blackboard::getState().enemyHills[targetIndex];
	}
};