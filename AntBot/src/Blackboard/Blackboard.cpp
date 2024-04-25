#include "Blackboard.h"

#include <algorithm>

#include "../a_star.h"

#include "../Logger/Logger.h"

//Initialize singleton static instance
Blackboard Blackboard::s_instance;

Blackboard::Blackboard()
	: p_gameState(nullptr)
{
	regions = getRegions();

	//Init AStar nodes
	mapNodes = std::vector<std::vector<AStarNode>>(120);

	std::array<std::array<char, 48>, 120> map = loadRegion();
	for (size_t x = 0; x < map.size(); x++)
	{
		mapNodes[x] = std::vector<AStarNode>(48);
		for (size_t y = 0; y < map[x].size(); y++)
		{
			mapNodes[x][y] = AStarNode();
			mapNodes[x][y].isWalkable = map[x][y] == -1;
			mapNodes[x][y].Location = Location(x, y);
		}
	}
};

void Blackboard::i_updateState(State& r_state) {
	p_gameState = &r_state;
}

void Blackboard::i_addJob(std::shared_ptr<Job> job)
{
	auto isHigherPriority = [job](std::shared_ptr<Job>& r_other) { return job->priority >= r_other->priority; };
	auto itFirstHigherPriority = std::ranges::find_if(jobs, isHigherPriority);

	jobs.insert(itFirstHigherPriority, job);
}

bool Blackboard::i_removeJob(const std::shared_ptr<Job>& r_job)
{
	auto isJob = [r_job](std::shared_ptr<Job>& other) { return other->id == r_job->id; };
	auto itJob = std::ranges::find_if(jobs, isJob);

	if (itJob == jobs.end()) [[unlikely]]
		return false;

		jobs.erase(itJob);
		return true;
}

bool Blackboard::i_updateJobPriority(std::shared_ptr<Job>& r_job, int priority)
{
	if (!i_removeJob(r_job)) [[unlikely]]
		return false;

		r_job->priority = priority;

		i_addJob(r_job);

		return true;
}

void Blackboard::i_assignJobsToAnts(std::vector<Ant*> ants)
{
	LOG(Logger::Trace, "i_assignJobsToAnts");

	for (std::shared_ptr<Job>& job : jobs)
	{
		//Job candidates
		LOG(Logger::Trace, "F0");
		std::vector<std::pair<size_t, unsigned int>> candidates(ants.size());
		for (size_t antIndex = 0, candidateIndex = 0; antIndex < ants.size(); antIndex++, candidateIndex++)
		{
			const unsigned int candidateFitness = ants[antIndex]->computeFitness(*job);
			candidates[candidateIndex] = std::make_pair(antIndex, candidateFitness);
		}

		//Sort candidates by fitness
		LOG(Logger::Trace, "F1");
		const auto isBetterFit = [](const std::pair<size_t, unsigned int>& current, const std::pair<size_t, unsigned int>& other) { return current.second > other.second; };
		std::sort(candidates.begin(), candidates.end(), isBetterFit);

		//Assign top candidates to job
		if (job->maxAssignedAnts == 0) continue;
		for (unsigned int i = 0; i < job->maxAssignedAnts; i++)
		{
			LOG(Logger::Trace, &candidates[i]);
			LOG(Logger::Trace, "F3");
			size_t candidateIndex = candidates[i].first - i; //Offsets index by removed amount
			LOG(Logger::Trace, "F4");
			job->assignedAnts.push_back(ants[candidateIndex]);
			LOG(Logger::Trace, "F5");
			ants.erase(ants.begin() + candidateIndex);
			LOG(Logger::Trace, "F6");
			if (ants.size() == 0)
				return;
		}
	}
}

void Blackboard::i_moveAllAnts() {
	//Assign Jobs to all ants
	LOG(Logger::Trace, "Starting moving action...");

	std::vector<Ant*> ants = std::vector<Ant*>(p_gameState->ants.size());
	std::ranges::transform(p_gameState->ants.begin(), p_gameState->ants.end(), ants.begin(), [](Ant& ant) { return &ant; });
	i_assignJobsToAnts(ants);

	LOG(Logger::Trace, "F1");

	//Get next position of each assigned ants
	Ant::resetNextMaps(mapNodes);
	std::vector<std::vector<AStarNode>> nextNodeMap = Ant::get_nextNodeMap();

	LOG(Logger::Trace, "F2");

	for (std::shared_ptr<Job>& job : jobs)
	{
		for (Ant* ant : job->assignedAnts)
		{

			LOG(Logger::Trace, "F3");
			//Get path (if no path try to find a new one)
			std::vector<Location>& path = ant->getPath();
			Location targetLocation = job->task();
			if (path.size() == 0)
			{
				AStarNode& start = nextNodeMap[ant->position.col][ant->position.row];
				AStarNode& target = nextNodeMap[targetLocation.col][targetLocation.row];
				LOG(Logger::Trace, "Target col : " + std::to_string(target.Location.col) + "Target row : " + std::to_string(target.Location.row));
				std::vector<Location> newPath = AStar::GetPathInGrid(nextNodeMap, start, target);
				path = newPath;
			}

			LOG(Logger::Trace, "F4");
			//If still no path, stay idle
			if (path.size() == 0)
			{
				//try all possible new location until one is free
				if (!ant->setNextLocation(ant->position))
					if (!ant->setNextLocation(Location(ant->position.row + 1, ant->position.col)))
						if (!ant->setNextLocation(Location(ant->position.row, ant->position.col + 1)))
							if (!ant->setNextLocation(Location(ant->position.row - 1, ant->position.col)))
								ant->setNextLocation(Location(ant->position.row, ant->position.col - 1));

				break;
			}

			LOG(Logger::Trace, "F5");
			//Try to go to the next location on path
			if (!ant->setNextLocation(path[0]))
			{
				AStarNode& start = nextNodeMap[ant->position.col][ant->position.row];
				AStarNode& target = nextNodeMap[targetLocation.col][targetLocation.row];
				std::vector<Location> newPath = AStar::GetPathInGrid(nextNodeMap, start, target);
				path = newPath;
			}

			LOG(Logger::Trace, "F6");
			if (path.size() != 0)
			{
				ant->setNextLocation(path[0]);
				path.erase(path.begin());
			}
		}
	}

	//Move ants
	for (std::shared_ptr<Job>& job : jobs)
		for (Ant* ant : job->assignedAnts)
		{
			int deltax = ant->position.col - ant->nextPosition.col;
			int deltay = ant->position.row - ant->nextPosition.row;
			if (deltax != 0)
				p_gameState->makeMove(ant->position, (deltax > 0) * 2 + 1);
			else if (deltay != 0)
				p_gameState->makeMove(ant->position, !(deltax > 0) * 2);
		}
}

std::ostream& operator<<(std::ostream& r_os, const Blackboard& blackboard)
{
	r_os << "Blackboard : {\nstate: {\n";
	if (&blackboard.getState() != nullptr)
		r_os << blackboard.getState();
	r_os << "},\njobs: {\n[\n";
	for (std::shared_ptr<Job>& job : blackboard.getJobs())
	{
		r_os << '\t' << *job << '\n';
	}
	r_os << "]\n}\n}" << std::endl;
	return r_os;
}