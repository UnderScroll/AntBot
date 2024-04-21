#include "Ant.h"

#include "../Blackboard/Job.h"

unsigned int Ant::s_idIndex = 0;
std::array<std::array<Ant*, 48>, 120> Ant::s_nextPositionMap{ nullptr };
std::vector<std::vector<AStarNode>> Ant::s_nextNodeMap{};

Ant::Ant()
{
	id = Ant::s_idIndex++;
	path = std::vector<Location>();
}

unsigned int Ant::computeFitness(const Job& job) const
{
	const int distSqr = (position.col - job.taskVariable.col) * (position.col - job.taskVariable.col) +
		(position.row - job.taskVariable.row) * (position.row - job.taskVariable.row);

	return INT_MAX - distSqr;
}

bool Ant::setNextLocation(Location newLocation)
{
	if (s_nextPositionMap[newLocation.row][newLocation.col] != nullptr)
	{
		nextPosition = position;
		return false;
	}


	s_nextPositionMap[newLocation.col][newLocation.row] = this;
	s_nextNodeMap[newLocation.col][newLocation.row].isWalkable = false;
	nextPosition = newLocation;
	return true;
}

void Ant::resetNextMaps(std::vector<std::vector<AStarNode>> nodeMap)
{
	Ant::s_nextNodeMap = nodeMap;
	Ant::s_nextPositionMap = std::array<std::array<Ant*, 48>, 120>(nullptr);
}

std::vector<Location>& Ant::getPath() {
	return path;
}

std::vector<std::vector<AStarNode>>& Ant::get_nextNodeMap()
{
	return s_nextNodeMap;
}

std::ostream& operator<<(std::ostream& r_os, const Ant& r_ant)
{
	return r_os << "Ant(" << r_ant.id << ")";
}