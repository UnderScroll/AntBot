#pragma once
#include <vector>
#include <ostream>

#include "../Location.h"

#include "../Ant/Ant.h"

class Job
{
private:
	static unsigned int s_idIndex;
public:
	Job(const int priority = 0, const int maxAssignedAnts = 1);

	unsigned int id;
	int priority; //Higher is higher priority
	size_t maxAssignedAnts;
	Location task; // A task is exclusively a location to go to as it's the only thing an ant can do
	
	std::vector<Ant*> assignedAnts;
};

std::ostream& operator<<(std::ostream& r_os, const Job& r_job);