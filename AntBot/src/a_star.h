#pragma once
#include <vector>
#include "a_star_node.h"

static class AStar
{
public:
	static std::vector<Location> GetPathInGrid(std::vector<std::vector<AStarNode>> grid, AStarNode* start, AStarNode* target);
private:
	static int GetNodeDistance(Location location1, Location location2, int gridRows, int gridCols);
};

