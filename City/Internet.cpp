#include "Internet.h"

std::unique_ptr<Internet> globalInternet(nullptr);

Internet::Internet()
{
	jobBoard = std::unique_ptr<JobBoard>(new JobBoard());
}

void Internet::Enable()
{
	globalInternet = std::unique_ptr<Internet>(new Internet());
}

const std::unique_ptr<Internet>& Internet::Get()
	{ return globalInternet; }

const std::unique_ptr<JobBoard>& Internet::getJobBoard()
	{ return jobBoard; }