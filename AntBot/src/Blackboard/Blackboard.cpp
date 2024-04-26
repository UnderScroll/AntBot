#include "Blackboard.h"

#include <algorithm>

#include "../a_star.h"

#include "../Logger/Logger.h"

//Initialize singleton static instance
Blackboard Blackboard::s_instance;

constexpr std::array<std::array<char, 120>, 48> transposeMap(const std::array<std::array<char, 48>, 120>& map)
{
	std::array<std::array<char, 120>, 48> transposedMap = std::array<std::array<char, 120>, 48>();

	for (size_t col = 0; col < map.size(); col++)
		for (size_t row = 0; row < map[col].size(); row++)
			transposedMap[row][col] = map[col][row];

	return transposedMap;
}

Blackboard::Blackboard()
	: p_gameState(nullptr)
{
	regions = getRegions();

	//Init AStar nodes
	mapNodes = std::vector<std::vector<AStarNode>>(48);

	std::array<std::array<char, 120>, 48> map = transposeMap(loadRegion());

	for (size_t row = 0; row < map.size(); row++)
	{
		mapNodes[row] = std::vector<AStarNode>(120);
		for (size_t col = 0; col < map[row].size(); col++)
		{
			mapNodes[row][col] = AStarNode();
			mapNodes[row][col].isWalkable = map[row][col] != -1;
			mapNodes[row][col].Location = Location(row, col);
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
	LOG(Logger::Trace, "F0");
	for (std::shared_ptr<Job>& job : jobs)
	{
		//Job candidates
		LOG(Logger::Trace, "F1");
		std::vector<std::pair<size_t, unsigned int>> candidates(ants.size());
		LOG(Logger::Trace, "F2");
		for (size_t antIndex = 0, candidateIndex = 0; antIndex < ants.size(); antIndex++, candidateIndex++)
		{
			LOG(Logger::Trace, "F3");
			const unsigned int candidateFitness = ants[antIndex]->computeFitness(*job);
			LOG(Logger::Trace, "F4");
			candidates[candidateIndex] = std::make_pair(antIndex, candidateFitness);
		}

		//Sort candidates by fitness
		LOG(Logger::Trace, "F5");
		const auto isBetterFit = [](const std::pair<size_t, unsigned int>& current, const std::pair<size_t, unsigned int>& other) { return current.second > other.second; };
		LOG(Logger::Trace, "F6");
		std::sort(candidates.begin(), candidates.end(), isBetterFit);

		//Assign top candidates to job
		LOG(Logger::Trace, "F7");
		if (job->maxAssignedAnts == 0) continue;
		LOG(Logger::Trace, "F8");
		for (unsigned int i = 0; i < job->maxAssignedAnts; i++)
		{
			LOG(Logger::Trace, "F9");
			size_t candidateIndex = candidates[i].first - i; //Offsets index by removed amount
			LOG(Logger::Trace, "F10");
			job->assignedAnts.push_back(ants[candidateIndex]);
			LOG(Logger::Trace, "F11");
			ants.erase(ants.begin() + candidateIndex);
			LOG(Logger::Trace, "F12");
			if (ants.size() == 0)
			{
				LOG(Logger::Trace, "F12.5");
				return;
			}

			LOG(Logger::Trace, "F13");
		}
		LOG(Logger::Trace, "F13.2");
	}
	LOG(Logger::Trace, "F13.3");
}

void Blackboard::i_moveAllAnts() {
	//Assign Jobs to all ants
	LOG(Logger::Trace, "Starting moving action...");

	std::vector<Ant*> ants = std::vector<Ant*>(p_gameState->ants.size());
	std::ranges::transform(p_gameState->ants.begin(), p_gameState->ants.end(), ants.begin(), [](Ant& ant) { return &ant; });
	LOG(Logger::Trace, "F-1");
	try
	{
	i_assignJobsToAnts(ants);
	}
	catch (int b)
	{
		LOG(Logger::Trace, "Caught Error :" + std::to_string(b));
	}
	LOG(Logger::Trace, "F14");

	//Get next position of each assigned ants
	Ant::resetNextMaps(mapNodes);
	std::vector<std::vector<AStarNode>> nextNodeMap = Ant::get_nextNodeMap();

	for (std::shared_ptr<Job>& job : jobs)
	{
		for (Ant* ant : job->assignedAnts)
		{
			//Get path (if no path try to find a new one)
			std::vector<Location>& r_path = ant->getPath();
			Location targetLocation = job->task();
			if (r_path.size() == 0)
			{
				AStarNode& start = nextNodeMap[ant->position.row][ant->position.col];
				AStarNode& target = nextNodeMap[targetLocation.row][targetLocation.col];
				LOG(Logger::Trace, "Target Location : " + std::to_string(target.Location.row) + ", " + std::to_string(target.Location.row));
				std::vector<Location> newPath = AStar::GetPathInGrid(nextNodeMap, start, target);
				r_path = newPath;
			}

			//If still no path, try to not be one top of another ant
			if (r_path.size() == 0)
			{
				//try all possible new location until one is free
				Location self = ant->position;
				Location right = Location(ant->position.row, ant->position.col + 1);
				Location top = Location(ant->position.row + 1, ant->position.col);
				Location left = Location(ant->position.row, ant->position.col - 1);
				Location bottom = Location(ant->position.row - 1, ant->position.col);
				if (Ant::isNextLocationFree(self))
					ant->setNextLocation(self);
				else if (Ant::isNextLocationFree(right))
					ant->setNextLocation(right);
				if (Ant::isNextLocationFree(top))
					ant->setNextLocation(top);
				if (Ant::isNextLocationFree(left))
					ant->setNextLocation(left);
				if (Ant::isNextLocationFree(bottom))
					ant->setNextLocation(bottom);

				continue;
			}

			//Try to go to the next location on path
			if (Ant::isNextLocationFree(r_path[r_path.size() - 1]))
			{
				AStarNode& start = nextNodeMap[ant->position.row][ant->position.col];
				AStarNode& target = nextNodeMap[targetLocation.row][targetLocation.col];
				std::vector<Location> newPath = AStar::GetPathInGrid(nextNodeMap, start, target);
				r_path = newPath;
			}
			LOG(Logger::Trace, "Path:");
			for (Location& l : r_path)
			{
				LOG(Logger::Trace, "\tLocation: " + std::to_string(l.col) + ", " + std::to_string(l.row));
			}
			if (r_path.size() != 0)
			{
				LOG(Logger::Trace, "Try to go to : " + std::to_string(r_path[r_path.size() - 1].row) + ", " + std::to_string(r_path[r_path.size() - 1].col));
				ant->setNextLocation(r_path[r_path.size() - 1]);
				r_path.erase(r_path.end() - 1);
			}
		}
	}

	//Move ants
	for (std::shared_ptr<Job>& job : jobs)
		for (Ant* ant : job->assignedAnts)
		{
			int deltax = ant->position.col - ant->nextPosition.col;
			int deltay = ant->position.row - ant->nextPosition.row;
			LOG(Logger::Debug, "position: (" + std::to_string(ant->position.row) + ", " + std::to_string(ant->position.col) + ")");
			LOG(Logger::Debug, "nextPosition: (" + std::to_string(ant->nextPosition.row) + ", " + std::to_string(ant->nextPosition.col) + ")");
			if (deltax != 0)
				p_gameState->makeMove(ant->position, (deltax > 0) * 2 + 1);
			else if (deltay != 0)
				p_gameState->makeMove(ant->position, !(deltax > 0) * 2);
		}
}

std::ostream& operator<<(std::ostream& r_os, const Blackboard& blackboard)
{
	r_os << "Blackboard : {\nstate: {\n";
	/*
	if (&blackboard.getState() != nullptr)
		r_os << blackboard.getState();
	*/
	r_os << "},\nants: {\n[\n";
	for (Ant& ant : blackboard.getState().ants)
	{
		r_os << '\t' << ant << '\n';
	}
	r_os << "]\n}" << std::endl;
	r_os << "},\njobs: {\n[\n";
	for (std::shared_ptr<Job>& job : blackboard.getJobs())
	{
		r_os << '\t' << *job << '\n';
	}
	r_os << "]\n}\n}" << std::endl;
	return r_os;
}