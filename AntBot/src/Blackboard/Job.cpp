#include "Job.h"

unsigned int Job::s_idIndex = 0;

Job::Job(const int priority, const int maxAssignedAnts, const int targetIndex)
	:priority(priority), maxAssignedAnts(maxAssignedAnts), targetIndex(targetIndex)
{
	id = Job::s_idIndex++;
	assignedAnts = std::vector<Ant*>();
	assignedAnts.reserve(maxAssignedAnts);
}

std::ostream& operator<<(std::ostream& r_os, const Job& r_job)
{
	r_os << "Job(" << r_job.id << ")[priority : " << r_job.priority << ", maxAnts : " << r_job.maxAssignedAnts << "] - (";
	for (auto itAnts = r_job.assignedAnts.begin(); itAnts < r_job.assignedAnts.end(); itAnts++)
	{
		r_os << (**itAnts);
		if (itAnts != r_job.assignedAnts.end() - 1) [[likely]]
			r_os << ", ";
	}
	return r_os << ")";
}