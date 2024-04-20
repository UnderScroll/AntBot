#include "Blackboard.h"

#include <algorithm>

#include "../a_star.h"

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

void Blackboard::i_addJob(Job job)
{
	auto isHigherPriority = [job](Job& r_other) { return job.priority >= r_other.priority; };
	auto itFirstHigherPriority = std::ranges::find_if(jobs, isHigherPriority);

	jobs.insert(itFirstHigherPriority, job);
}

bool Blackboard::i_removeJob(const Job& r_job)
{
	auto isJob = [r_job](Job& other) { return other.id == r_job.id; };
	auto itJob = std::find_if(jobs.begin(), jobs.end(), isJob);

	if (itJob == jobs.end()) [[unlikely]]
		return false;

		jobs.erase(itJob);
		return true;
}

bool Blackboard::i_updateJobPriority(Job& r_job, int priority)
{
	if (!i_removeJob(r_job)) [[unlikely]]
		return false;

		r_job.priority = priority;

		i_addJob(r_job);

		return true;
}

void Blackboard::i_assignJobsToAnts(std::vector<Ant*> ants)
{
	for (Job& job : jobs)
	{
		//Job candidates
		std::vector<std::pair<size_t, unsigned int>> candidates(ants.size());
		for (size_t antIndex = 0, candidateIndex = 0; antIndex < ants.size(); antIndex++, candidateIndex++)
		{
			const unsigned int candidateFitness = ants[antIndex]->computeFitness(job);
			candidates[candidateIndex] = std::make_pair(antIndex, candidateFitness);
		}

		//Sort candidates by fitness
		const auto isBetterFit = [](const std::pair<size_t, unsigned int>& current, const std::pair<size_t, unsigned int>& other) { return current.second > other.second; };
		std::sort(candidates.begin(), candidates.end(), isBetterFit);

		//Assign top candidates to job
		for (unsigned int i = 0; i < job.maxAssignedAnts; i++)
		{
			const size_t candidateIndex = candidates[i].first - i; //Offsets index by removed amount
			job.assignedAnts.push_back(ants[candidateIndex]);
			ants.erase(ants.begin() + candidateIndex);
			if (ants.size() == 0)
				return;
		}
	}
}

void Blackboard::i_moveAllAnts() {
	Ant::resetNextMaps(mapNodes);
	std::vector<std::vector<AStarNode>> nextNodeMap = Ant::get_nextNodeMap();

	for (Job& job : jobs)
	{
		for (Ant* ant : job.assignedAnts) 
		{
			//Get path (if no path try to find a new one)
			std::vector<Location>& path = ant->getPath();
			if (path.size() == 0)
			{
				AStarNode& start = nextNodeMap[ant->position.col][ant->position.row];
				AStarNode& target = nextNodeMap[job.task.col][job.task.row];
				std::vector<Location> newPath = AStar::GetPathInGrid(nextNodeMap, start, target);
				path = newPath;
			}

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
			
			//Try to go to the next location on path
			if (!ant->setNextLocation(path[0]))
			{
				AStarNode& start = nextNodeMap[ant->position.col][ant->position.row];
				AStarNode& target = nextNodeMap[job.task.col][job.task.row];
				std::vector<Location> newPath = AStar::GetPathInGrid(nextNodeMap, start, target);
				path = newPath;
			}

			if (path.size() != 0) 
			{
				ant->setNextLocation(path[0]);
				path.erase(path.begin());
			}
		}
	}

	//Move ants
	for (Job& job : jobs)
		for (Ant* ant : job.assignedAnts)
		{
			int deltax = ant->position.col - ant->nextPosition.col;
			int deltay = ant->position.row - ant->nextPosition.row;
			if (deltax != 0)
				p_gameState->makeMove(ant->position, deltax > 0 ? 'W' : 'E');
			else if (deltay != 0)
				p_gameState->makeMove(ant->position, deltax > 0 ? 'N' : 'S');
		}
}

std::ostream& operator<<(std::ostream& r_os, const Blackboard& blackboard)
{
	r_os << "Blackboard : {\nstate: {\n";
	if (&blackboard.getState() != nullptr)
		r_os << blackboard.getState();
	r_os << "},\njobs: {\n[\n";
	for (Job& job : blackboard.getJobs())
	{
		r_os << '\t' << job << '\n';
	}
	r_os << "]\n}\n}" << std::endl;
	return r_os;
}