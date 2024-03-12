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

bool Blackboard::i_assignJobToAnt(Job& r_job, const Ant& ant)
{
	return r_job.assignAnt(ant);
}

bool Blackboard::i_unassignJobToAnt(Job& r_job, const Ant& ant)
{
	return r_job.unassignAnt(ant);
}

std::ostream& operator<<(std::ostream& r_os, const Blackboard& blackboard) 
{
	r_os << "Blackboard : {\nstate: {\n";
	if (&blackboard.getState() != nullptr)
		r_os << blackboard.getState();
	r_os << "},\njobs: {\n[\n";
	for (Job& job : blackboard.getJobs()) 
	{
		r_os << '\t' << "(" << job.id << ") " << job.priority << '\n';
	}
	r_os << "]\n}\n}" << std::endl;
	return r_os;
}