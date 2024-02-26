#include "Blackboard.h"

#include <algorithm>

//Initialize singleton static instance
Blackboard Blackboard::s_instance;

void Blackboard::i_updateState(State& state) {
	p_gameState = &state;
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
	if (!i_removeJob(r_job))
		return false;

	r_job.priority = priority;

	i_addJob(r_job);
}

bool Blackboard::i_assignJobToAnt(Job& r_job, const Ant& ant)
{
	return r_job.assignAnt(ant);
}

bool Blackboard::i_unassignJobToAnt(Job& r_job, const Ant& ant)
{
	return r_job.unassignAnt(ant);
}

std::ostream& operator<<(std::ostream& os, const Blackboard& blackboard) 
{
	os << "Blackboard : {\nstate: {\n";
	if (&blackboard.getState() != nullptr)
		os << blackboard.getState();
	os << "},\njobs: {\n[\n";
	for (Job& job : blackboard.getJobs()) 
	{
		os << '\t' << "(" << job.id << ") " << job.priority << '\n';
	}
	os << "]\n}\n}" << std::endl;
	return os;
}