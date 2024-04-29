#pragma once

#include <vector>

#include "../State.h"
#include "../Ant/Ant.h"
#include "../MapRegion.h"
#include "../a_star_node.h"
#include "Job.h"

//Note : The Blackboard singleton is not threadsafe
class Blackboard
{
public:
	static Blackboard& getInstance() { return s_instance; };

	static void updateState(State& r_newState) { getInstance().i_updateState(r_newState); }
	static void addJob(std::shared_ptr<Job> job) { getInstance().i_addJob(job); }
	static void removeJob(const std::shared_ptr<Job>& r_job) { getInstance().i_removeJob(r_job); }
	static void updateJobPriority(std::shared_ptr<Job>& r_job, int priority) { getInstance().i_updateJobPriority(r_job, priority); }
	static void assignJobsToAnts(std::vector<Ant*> ants) { getInstance().i_assignJobsToAnts(ants); }

	static State& getState() { return *getInstance().p_gameState; }
	static std::vector<std::shared_ptr<Job>>& getJobs() { return getInstance().jobs; }
	static std::array<std::vector<Location>, MAX_REGION_INDEX>& getAllRegions() { return getInstance().regions; }
	static void moveAllAnts() { getInstance().i_moveAllAnts(); }
private:
	/*Singleton*/
	Blackboard(); //Removes constructor direct call

	Blackboard(Blackboard& r_other) = delete; //Not clonable
	void operator=(const Blackboard&) = delete; //Not assignable

	static Blackboard s_instance;
	/**/

	/*State*/
	State* p_gameState;
	void i_updateState(State& r_newState);

	/*Region*/
	std::array<std::vector<Location>, MAX_REGION_INDEX> regions;

	/*Jobs*/
	std::vector<std::shared_ptr<Job>> jobs;
	
	//Adds a job to jobs, conserves priority order
	void i_addJob(std::shared_ptr<Job> job);

	//Remove a job from jobs, conserves priority order
	bool i_removeJob(const std::shared_ptr<Job>& r_job);

	//Updated the job r_job with the new priority, conserves priority order
	bool i_updateJobPriority(std::shared_ptr<Job>& r_job, int priority);

	void i_assignJobsToAnts(std::vector<Ant*> ants);
	/**/

	/*Ants*/
	std::vector<std::vector<AStarNode>> mapNodes;

	void i_moveAllAnts();
	/**/
};

std::ostream& operator<<(std::ostream& r_os, const Blackboard& r_blackboard);

