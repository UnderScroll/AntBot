#pragma once
#include <vector>
#include <ostream>

#include "../Location.h" 

#include "../Ant/Ant.h"

class Job
{
protected:
	static unsigned int s_idIndex;
	//Target index is either the region index or anthill index, depending on the type of job
	int targetIndex;
public:
	Job(const int priority = 0, const int maxAssignedAnts = 1, const int targetIndex = 0);
	virtual bool isJobComplete() { return true; };
	unsigned int id;
	int priority; //Higher is higher priority
	size_t maxAssignedAnts;
	Location taskVariable; // A task is exclusively a location to go to as it's the only thing an ant can do
	virtual Location task() { return Location(); } // A task is exclusively a location to go to as it's the only thing an ant can do
	
	std::vector<Ant*> assignedAnts;
};

std::ostream& operator<<(std::ostream& r_os, const Job& r_job);