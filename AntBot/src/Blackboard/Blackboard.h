#pragma once

#include <vector>

#include "../State.h"
#include "../Ant/Ant.h"
#include "Job.h"

//Note : The Blackboard singleton is not threadsafe
class Blackboard
{
public:
	static Blackboard& getInstance() { return s_instance; };

	static void addJob(Job job) { getInstance().i_addJob(job); }
	static void removeJob(const Job& r_job) { getInstance().i_removeJob(r_job); }
	static void updateJobPriority(Job& r_job, int priority) { getInstance().i_updateJobPriority(r_job, priority); }

	static bool assignJobToAnt(Job& r_job, const Ant& ant) { return getInstance().i_assignJobToAnt(r_job, ant); };
	static bool unassignJobToAnt(Job& r_job, const Ant& ant) { return getInstance().i_unassignJobToAnt(r_job, ant); };

	static State& getState() { return *getInstance().p_gameState; }
	static std::vector<Job>& getJobs() { return getInstance().jobs; }
private:
	/*Singleton*/
	Blackboard(): p_gameState(nullptr) {}; //Removes constructor direct call

	Blackboard(Blackboard& r_other) = delete; //Not clonable
	void operator=(const Blackboard&) = delete; //Not assignable

	static Blackboard s_instance;
	/**/


	/*State*/
	State* p_gameState;
	void i_updateState(State& newState);

	//TODO get graph from state, update graph
	/**/


	/*Jobs*/
	std::vector<Job> jobs;
	
	//Adds a job to jobs, conserves priority order
	void i_addJob(Job job);

	//Remove a job from jobs, conserves priority order
	bool i_removeJob(const Job& r_job);

	//Updated the job r_job with the new updatedJob, conserves priority order
	bool i_updateJobPriority(Job& r_job, int priority);

	bool i_assignJobToAnt(Job& r_job, const Ant& ant);
	bool i_unassignJobToAnt(Job& r_job, const Ant& ant);
	/**/
};

std::ostream& operator<<(std::ostream& os, const Blackboard& blackboard);

