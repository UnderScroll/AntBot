#include "Ant.h"

#include "../Blackboard/Job.h"

unsigned int Ant::s_idIndex = 0;

Ant::Ant()
{
	id = Ant::s_idIndex++;
}

unsigned int Ant::computeFitness(const Job& job) const
{
	const int distSqr = (position.col - job.taskVariable.col) * (position.col - job.taskVariable.col) +
		(position.row - job.taskVariable.row) * (position.row - job.taskVariable.row);

	return INT_MAX - distSqr;
}

std::ostream& operator<<(std::ostream& r_os, const Ant& r_ant)
{
	return r_os << "Ant(" << r_ant.id << ")";
}