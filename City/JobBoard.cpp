#include <iostream>
#include "JobBoard.h"

JobBoard::JobBoard()
	: jobs(std::stack<Job*>())
{

}

void JobBoard::PostJob(Job* job)
{
	jobs.push(job);
	std::cout << "+1: " << jobs.size() << " jobs available." << std::endl;
}

const Job* JobBoard::GetJob()
{
	if (!jobs.empty())
	{
		auto job = jobs.top();
		jobs.pop();

		std::cout << "-1: " << jobs.size() << " jobs available." << std::endl;
		return job;
	}

	std::cout << "0:" << jobs.size() << " jobs available." << std::endl;
	return nullptr;
}

