#pragma once
#include <ostream>

#include "../Location.h"

class Job;

class Ant
{
private:
	static unsigned int s_idIndex;
public:
	Ant();

	Location position;
	unsigned int id;

	unsigned int computeFitness(const Job& job) const;
};

std::ostream& operator<<(std::ostream& r_os, const Ant& r_ant);