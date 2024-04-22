#include <iostream>
#include "Bot.h"
#define LOG_STREAM std::cerr
#define LOGGER_VERBOSE
#include "Logger/Logger.h"
#include "BlackBoard/BlackBoard.h"
#include "BlackBoard/TakeEnemyAnthillStrategy.h"
#include "BlackBoard/AttackRegionStrategy.h"
#include "BlackBoard/OccupyRegionStrategy.h"
#include "BlackBoard/ActiveExplorationStrategy.h"
#include "Blackboard/ExploreZoneJob.h"
#include "Blackboard/AttackZoneJob.h"
#include "Blackboard/DiscoverAnthillPositionJob.h"
#include "Blackboard/AttackEnemyAnthillJob.h"

using namespace std;

static ofstream fileStream;

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

	setupStrategies();

	//continues making moves while the game is not over
	while (cin >> state)
	{
		state.updateVisionInformation();
		updateJobs();
		makeMoves();
		endTurn();
	}
};

void Bot::setupStrategies()
{
	//Add the enemy anthill related jobs
	for (size_t antHillIndex = 0; antHillIndex < Blackboard::getInstance().getState().noPlayers - 1; antHillIndex++)
	{
		addExploreAnthillStrategy(antHillIndex);
		addAttackAnthillStrategy(antHillIndex);
	}

	//Add the regions related jobs
	for (size_t regionIndex = 0; regionIndex < Blackboard::getInstance().getAllRegions().size(); regionIndex++)
	{
		addAttackRegionStrategy(regionIndex);
		addOccupyRegionStrategy(regionIndex);
	}
	fileStream.open("log.txt");
#define LOG_STREAM fileStream
	for (size_t i = 0; i < strategies.size(); i++)
	{
		LOG(Logger::Debug, typeid(strategies[i]).name());
		std::cerr.flush();
	}
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
	}

	//We assign a number of ants per priority
	for (size_t i = 0; i < strategies.size(); i++)
	{
		strategies[i].assignMaxAnt(ceil(strategies[i].GetPriority() / totalPriority) * Blackboard::getState().myAnts.size());
	}
}

//makes the bots moves for the turn
void Bot::makeMoves()
{
	state.bug << "turn " << state.turn << ":" << endl;
	state.bug << state << endl;

	//picks out moves for each ant
	for (int ant = 0; ant < (int)state.myAnts.size(); ant++)
	{
		for (int d = 0; d < TDIRECTIONS; d++)
		{
			Location loc = state.getLocation(state.myAnts[ant], d);

			if (!state.grid[loc.row][loc.col].isWater)
			{
				state.makeMove(state.myAnts[ant], d);
				break;
			}
		}
	}

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
