#include <iostream>

#include "Bot.h"
#include "BlackBoard/BlackBoard.h"
#include "BlackBoard/TakeEnemyAnthillStrategy.h"
#include "BlackBoard/AttackRegionStrategy.h"
#include "BlackBoard/OccupyRegionStrategy.h"
#include "BlackBoard/ActiveExplorationStrategy.h"
#include "Blackboard/ExploreZoneJob.h"
#include "Blackboard/AttackZoneJob.h"
#include "Blackboard/DiscoverAnthillPositionJob.h"
#include "Blackboard/AttackEnemyAnthillJob.h"

#include "Logger/Logger.h"

using namespace std;

//constructor
Bot::Bot()
{

};

//plays a single game of Ants.
void Bot::playGame()
{
	//reads the game parameters and sets up
	cin >> state;
	state.setup();
	endTurn();

	state.noPlayers = 6;

	Blackboard::updateState(state);
	setupStrategies();

	//continues making moves while the game is not over
	while (cin >> state)
	{

		state.updateVisionInformation();

		Blackboard::updateState(state);

		updateJobs();

		makeMoves();

		endTurn();
	}
};

void Bot::setupStrategies()
{
	//Add the enemy anthill related jobs
	for (size_t antHillIndex = 0; antHillIndex < Blackboard::getState().noPlayers - 1; antHillIndex++)
	{
		addExploreAnthillStrategy(antHillIndex);
		addAttackAnthillStrategy(antHillIndex);
	}

	//Add the regions related jobs
	for (size_t regionIndex = 0; regionIndex < Blackboard::getAllRegions().size(); regionIndex++)
	{
		addAttackRegionStrategy(regionIndex);
		addOccupyRegionStrategy(regionIndex);
	}

}

void Bot::addAttackRegionStrategy(const size_t& regionIndex)
{
	std::vector<std::shared_ptr<Job>> stepJobs{ std::make_shared<AttackZoneJob>(AttackZoneJob(0, 3, regionIndex)) };

	std::map<int, std::vector<std::shared_ptr<Job>>> jobsMap = std::map<int, std::vector<std::shared_ptr<Job>>>();
	jobsMap.insert(std::make_pair(0, stepJobs));

	AttackRegionStrategy strategy = AttackRegionStrategy(jobsMap, regionIndex);
	strategies.push_back(std::make_shared<AttackRegionStrategy>(strategy));
}

void Bot::addOccupyRegionStrategy(const size_t& regionIndex)
{
	std::vector<std::shared_ptr<Job>> stepJobs{ std::make_shared<ExploreZoneJob>(ExploreZoneJob(0, 3, regionIndex)) };

	std::map<int, std::vector<std::shared_ptr<Job>>> jobsMap = std::map<int, std::vector<std::shared_ptr<Job>>>();
	jobsMap.insert(std::make_pair(0, stepJobs));

	OccupyRegionStrategy strategy = OccupyRegionStrategy(jobsMap, regionIndex);
	strategies.push_back(std::make_shared<OccupyRegionStrategy>(strategy));
}

void Bot::addExploreAnthillStrategy(const size_t& antHillIndex)
{
	std::vector<std::shared_ptr<Job>> explorationStepJobs{ std::make_shared<DiscoverAnthillPositionJob>(DiscoverAnthillPositionJob(0, 3, antHillIndex)) };

	std::map<int, std::vector<std::shared_ptr<Job>>> explorationJobsMap = std::map<int, std::vector<std::shared_ptr<Job>>>();
	explorationJobsMap.insert(std::make_pair(0, explorationStepJobs));

	ActiveExplorationStrategy explorationStrategy = ActiveExplorationStrategy(explorationJobsMap, antHillIndex);
	strategies.push_back(std::make_shared<ActiveExplorationStrategy>(explorationStrategy));
}

void Bot::addAttackAnthillStrategy(const size_t& antHillIndex)
{
	std::vector<std::shared_ptr<Job>> stepJobs{ std::make_shared<AttackEnemyAnthillJob>(AttackEnemyAnthillJob(0, 3, antHillIndex)) };

	std::map<int, std::vector<std::shared_ptr<Job>>> attackJobsMap = std::map<int, std::vector<std::shared_ptr<Job>>>();
	attackJobsMap.insert(std::make_pair(0, stepJobs));

	TakeEnemyAnthillStrategy attackStrategy = TakeEnemyAnthillStrategy(attackJobsMap, antHillIndex);
	strategies.push_back(std::make_shared<TakeEnemyAnthillStrategy>(attackStrategy));
}

void Bot::updateJobs()
{
	int totalPriority = 0;
	//We compute the strategy per priority
	for (size_t i = 0; i < strategies.size(); i++)
	{
		strategies[i]->computeStrategyPriority();

		if (strategies[i]->GetPriority() > 0)
			totalPriority += strategies[i]->GetPriority();
	}

	//Clean the blackboard job
	std::vector<std::shared_ptr<Job>>& r_jobs = Blackboard::getJobs();
	for (std::shared_ptr<Job>& job : r_jobs)
		job->assignedAnts = std::vector<Ant*>();

	r_jobs = std::vector<std::shared_ptr<Job>>();

	//We assign a number of ants per priority and add jobs to BlackBoard
	if (totalPriority > 0)
		for (size_t i = 0; i < strategies.size(); i++)
		{
			strategies[i]->assignMaxAnt(ceil(strategies[i]->GetPriority() / (float)totalPriority * Blackboard::getState().myAnts.size()));
			strategies[i]->setJobsToBlackboard();
		}
}

//makes the bots moves for the turn
void Bot::makeMoves()
{

	state.bug << "turn " << state.turn << ":" << endl;
	state.bug << state << endl;

	//picks out moves for each ant
	Blackboard::moveAllAnts();

	state.bug << "time taken: " << state.timer.getTime() << "ms" << endl << endl;
};

//finishes the turn
void Bot::endTurn()
{
	if (state.turn > 0)
		state.reset();
	state.turn++;

	cout << "go" << endl;
};
