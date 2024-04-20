#include "Blackboard.h"

#include <algorithm>

//Initialize singleton static instance
Blackboard Blackboard::s_instance;

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