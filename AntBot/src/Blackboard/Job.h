#pragma once
#include "../Ant/Ant.h"

class Job
{
public:
	int priority; //Higher is higher priority
	int id; //TODO: generate an ID at construction
	bool assignAnt(const Ant& ant) {/*TODO*/ return true; };
	bool unassignAnt(const Ant& ant) {/*TODO*/ return true; };
};

