#pragma once
#include <memory>

#include "PersonState.h"
#include "Job.h"

class Person
{
	unsigned int ssn;
	unsigned char health;

	std::unique_ptr<Job> job;

	PersonState state;
	bool stateChanged;

	void SearchForJob();
public:
	Person();

	bool hasStateChanged();
	void ChangeState();
};

