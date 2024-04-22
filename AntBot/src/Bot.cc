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

	LOG(Logger::Trace, "Bot initialized")
		//continues making moves while the game is not over
		while (cin >> state)
		{
			LOG(Logger::Trace, Blackboard::getInstance());

			LOG(Logger::Trace, "Started turn");

			LOG(Logger::Trace, "Updating state");
			Blackboard::updateState(state);

			LOG(Logger::Trace, "Updating vision");
			state.updateVisionInformation();

			LOG(Logger::Trace, "Updating jobs");
			updateJobs();

			LOG(Logger::Trace, "Moving ants");
			makeMoves();

			endTurn();
			LOG(Logger::Trace, "Turn ended");
		}
};

void Bot::setupStrategies()
{
	LOG(Logger::Trace, "Setting up strategies")

		LOG(Logger::Trace, "Add enemy anthill jobs")
		LOG(Logger::Trace, Blackboard::getInstance().getState().noPlayers)

		//Add the enemy anthill related jobs
		for (size_t antHillIndex = 0; antHillIndex < Blackboard::getInstance().getState().noPlayers - 1; antHillIndex++)
		{
			LOG(Logger::Trace, "Add enemy anthill jobs - index : " + std::to_string(antHillIndex))
				addExploreAnthillStrategy(antHillIndex);
			addAttackAnthillStrategy(antHillIndex);
		}

	LOG(Logger::Info, "Add regions jobs")
		//Add the regions related jobs
		for (size_t regionIndex = 0; regionIndex < Blackboard::getInstance().getAllRegions().size(); regionIndex++)
		{
			addAttackRegionStrategy(regionIndex);
			addOccupyRegionStrategy(regionIndex);
		}

	LOG(Logger::Info, "Strategies set up")
}

void Bot::addAttackRegionStrategy(const size_t& regionIndex)
{
	std::vector<Job> stepJobs{ AttackZoneJob(0, 3, regionIndex) };

	std::map<int, std::vector<Job>> jobsMap = std::map<int, std::vector<Job>>();
	jobsMap.insert(std::make_pair(0, stepJobs));

	AttackRegionStrategy strategy = AttackRegionStrategy(jobsMap, regionIndex);
	strategies.push_back(strategy);
}

void Bot::addOccupyRegionStrategy(const size_t& regionIndex)
{
	std::vector<Job> stepJobs{ ExploreZoneJob(0, 3, regionIndex) };

	std::map<int, std::vector<Job>> jobsMap = std::map<int, std::vector<Job>>();
	jobsMap.insert(std::make_pair(0, stepJobs));

	OccupyRegionStrategy strategy = OccupyRegionStrategy(jobsMap, regionIndex);
	strategies.push_back(strategy);
}

void Bot::addExploreAnthillStrategy(const size_t& antHillIndex)
{
	std::vector<Job> explorationStepJobs{ DiscoverAnthillPositionJob(0, 3, antHillIndex) };

	std::map<int, std::vector<Job>> explorationJobsMap = std::map<int, std::vector<Job>>();
	explorationJobsMap.insert(std::make_pair(0, explorationStepJobs));

	ActiveExplorationStrategy explorationStrategy = ActiveExplorationStrategy(explorationJobsMap, antHillIndex);
	strategies.push_back(explorationStrategy);
}

void Bot::addAttackAnthillStrategy(const size_t& antHillIndex)
{
	std::vector<Job> stepJobs{ AttackEnemyAnthillJob(0, 3, antHillIndex) };

	std::map<int, std::vector<Job>> attackJobsMap = std::map<int, std::vector<Job>>();
	attackJobsMap.insert(std::make_pair(0, stepJobs));

	TakeEnemyAnthillStrategy attackStrategy = TakeEnemyAnthillStrategy(attackJobsMap, antHillIndex);
	strategies.push_back(attackStrategy);
}

void Bot::updateJobs()
{
	int totalPriority = 0;
	//We compute the strategy per priority
	for (size_t i = 0; i < strategies.size(); i++)
	{
		strategies[i].computeStrategyPriority();
		totalPriority += strategies[i].GetPriority();
		LOG(Logger::Trace, "Strategy priority : " + std::to_string(strategies[i].GetPriority()))
	}

	//Clean the blackboard job
	Blackboard::getJobs() = std::vector<Job>();
	LOG(Logger::Trace, "Jobs cleaned ");

	//We assign a number of ants per priority and add jobs to BlackBoard
	for (size_t i = 0; i < strategies.size(); i++)
	{
	LOG(Logger::Trace, "Assing ant to job : " + std::to_string(i));
		strategies[i].assignMaxAnt(ceil(strategies[i].GetPriority() / totalPriority) * Blackboard::getState().myAnts.size());
	LOG(Logger::Trace, "Setting job to BB: " + std::to_string(i));
		strategies[i].setJobsToBlackboard();
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
