#include "ActiveExplorationStrategy.h"
#include "BlackBoard.h"

void ActiveExplorationStrategy::SetTargetPlayerAnthill(int id) 
{
	targetPlayerAnthill = id;
}

void ActiveExplorationStrategy::ComputeStrategyPriority() 
{
	//TODO IF WE DON'T KNOW THE ANTHILL AND WE ARE LATE INTO THE GAME
}