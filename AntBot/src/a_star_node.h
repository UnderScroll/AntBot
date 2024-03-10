#pragma once
#include "Square.h"
#include "Location.h"

struct AStarNode {
	bool isWalkable;
	Location Location;
	AStarNode* ParentNode;
	int distanceToStart = INT_MAX;
	int distanceToEnd = INT_MAX;
	int nodeCost = INT_MAX;

	void SetScore() 
	{
		nodeCost = distanceToStart + distanceToEnd;
	}

	bool operator==(const AStarNode& other) const {
		return Location.col == other.Location.col && Location.row == other.Location.row;
	}

	bool operator!=(const AStarNode& other) const {
		return Location.col != other.Location.col || Location.row != other.Location.row;
	}
};