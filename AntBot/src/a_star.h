#pragma once
#include <vector>
#include "a_star_node.h"

static class AStar
{
public:
	static std::vector<Location> getPathInGrid(std::vector<std::vector<AStarNode>> grid, AStarNode& r_start, AStarNode& r_target);
private:
	static int getNodeDistanceSq(const Location& r_location1, const Location& r_location2, const int gridRows, const int gridCols);
};

