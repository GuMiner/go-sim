#pragma once
#include <map>
#include <stack>
#include <memory>
#include "Job.h"

class JobBoard
{
	std::stack<Job*> jobs;
public:
	JobBoard();
	void PostJob(Job* job);
	const Job* GetJob();
};

