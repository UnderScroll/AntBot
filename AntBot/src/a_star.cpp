#include <string>
#include "a_star.h"
#include "Logger/Logger.h"

std::vector<Location> AStar::getPathInGrid(std::vector<std::vector<AStarNode>> grid, AStarNode& r_start, AStarNode& r_target)
{
	// Create lists for open and closed nodes
	std::vector<AStarNode*> openList = std::vector<AStarNode*>();
	std::vector<AStarNode*> closedList = std::vector<AStarNode*>();

	// Add the start node to the open list
	openList.push_back(&r_start);

	// Set the initial distance and score values for the start node
	r_start.distanceToStart = 0;
	r_start.distanceToEnd = getNodeDistanceSq(r_start.location, r_target.location, grid.size(), grid[0].size());
	r_start.setScore();

	// Define the x and y coordinate changes for the neighbors
	int dx[] = { 0, 0, -1, 1 };  // x-coordinate changes for neighbors
	int dy[] = { -1, 1, 0, 0 };  // y-coordinate changes for neighbors

	// Main loop until the open list is empty
	while (openList.size() > 0)
	{
		// Find the node with the lowest cost in the open list
		int index = 0;
		int lowestCost = openList[0]->nodeCost;

		for (size_t i = 1; i < openList.size(); i++)
		{
			if (openList[i]->nodeCost < lowestCost)
			{
				lowestCost = openList[i]->nodeCost;
				index = i;
			}
		}

		// Get the current node and remove it from the open list
		AStarNode& r_currentNode = *openList[index];
		openList.erase(openList.begin() + index);

		// Add the current node to the closed list
		closedList.push_back(&r_currentNode);

		// Check if the current node is the target node
		if (r_currentNode.location.col == r_target.location.col && r_currentNode.location.row == r_target.location.row)
			break;

		// Explore the neighbors of the current node
		for (int i = 0; i < 4; ++i)
		{
			// Calculate the coordinates of the neighbor, considering grid wrapping
			int newX = (r_currentNode.location.col + dx[i] + grid[0].size()) % grid[0].size();
			int newY = (r_currentNode.location.row + dy[i] + grid.size()) % grid.size();

			// Check if the neighbor is within the grid bounds and is walkable
			if (grid.size() <= newY || grid[0].size() <= newX) [[unlikely]]
				continue;

				if (!grid[newY][newX].isWalkable)
					continue;

				// Check if the neighbor is in the closed list
				bool isInClosedList = false;
				for (size_t i = 0; i < closedList.size(); i++)
				{
					if (*closedList[i] == grid[newY][newX])
					{
						isInClosedList = true;
						break;
					}
				}

				// Update the neighbor's distance and parent if it has a shorter path
				if (r_currentNode.distanceToStart + 1 < grid[newY][newX].distanceToStart)
				{
					if (!isInClosedList)
					{
						openList.push_back(&grid[newY][newX]);
					}

					grid[newY][newX].distanceToStart = r_currentNode.distanceToStart + 1;
					grid[newY][newX].p_parentNode = &r_currentNode;
					grid[newY][newX].distanceToEnd = getNodeDistanceSq(r_target.location, grid[newY][newX].location, grid.size(), grid[0].size());
					grid[newY][newX].setScore();
				}
		}
	}

	// Reconstruct the path by backtracking from the target node to the start node
	std::vector<Location> path = std::vector<Location>();
	AStarNode& r_currentNode = grid[r_target.location.row][r_target.location.col];

	while (r_currentNode != r_start && r_currentNode.p_parentNode != nullptr)
	{
		path.push_back(r_currentNode.location);
		r_currentNode = *r_currentNode.p_parentNode;
	}

	// Return the path from the start node to the target node
	return path;
}

int AStar::getNodeDistanceSq(const Location& r_location1, const Location& r_location2, const int gridRows, const int gridCols)
{
	int dx = std::abs(r_location1.col - r_location2.col);
	int dy = std::abs(r_location1.row - r_location2.row);

	if (dx > gridCols / 2)
		dx = gridCols - dx;

	if (dy > gridRows / 2)
		dy = gridRows - dy;

	return dx * dx + dy * dy;
}
