#include "Internet.h"

#include "Company.h"

unsigned int maxCompanyId;

Company::Company()
	: id(++maxCompanyId),
	jobs()
{
}

// Testing
void Company::AddJob()
{
	Job* newJob = new Job(id,
		Resource::Farmland, 10,
		Resource::Food, 1);
	jobs.push_back(std::unique_ptr<Job>(newJob));

	// Auto-post
	const auto& jobBoard = Internet::Get()->getJobBoard();
	jobBoard->PostJob(newJob);
}