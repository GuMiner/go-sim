#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Job.h"

class Company
{
	unsigned int id;
	std::vector<std::unique_ptr<Job>> jobs;
public:
	Company();
	void AddJob();
};

