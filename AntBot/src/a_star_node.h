#pragma once
#include "Square.h"
#include "Location.h"

struct AStarNode {
	bool isWalkable;
	Location location;
	AStarNode* p_parentNode;
	int distanceToStart = INT_MAX;
	int distanceToEnd = INT_MAX;
	int nodeCost = INT_MAX;

	void setScore() 
	{
		nodeCost = distanceToStart + distanceToEnd;
	}

	bool operator==(const AStarNode& other) const {
		return location.col == other.location.col && location.row == other.location.row;
	}

	bool operator!=(const AStarNode& other) const {
		return location.col != other.location.col || location.row != other.location.row;
	}
};