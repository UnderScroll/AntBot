#pragma once
#include <ostream>
#include <array>
#include <vector>

#include "../Location.h"
#include "../a_star_node.h"

class Job;

class Ant
{
private:
	static unsigned int s_idIndex;
	static std::array<std::array<Ant*, 48>, 120> s_nextPositionMap;
	static std::vector<std::vector<AStarNode>> s_nextNodeMap;

	std::vector<Location> path;
public:
	Ant();

	Location position;
	Location nextPosition;
	unsigned int id;

	static void resetNextMaps(std::vector<std::vector<AStarNode>> nodeMap);
	static std::vector<std::vector<AStarNode>>& get_nextNodeMap();

	unsigned int computeFitness(const Job& job) const;
	bool setNextLocation(Location newLocation);
	std::vector<Location>& getPath();
};

std::ostream& operator<<(std::ostream& r_os, const Ant& r_ant);