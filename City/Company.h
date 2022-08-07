#pragma once
#include <memory>
#include <string>
#include <vector>

#include "CompanyType.h"
#include "Job.h"

class Company
{
	CompanyType type;
	unsigned int id;
	std::vector<std::unique_ptr<Job>> jobs;
public:
	Company();
	void AddJob();
};

