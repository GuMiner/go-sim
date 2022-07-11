#include <iostream>
#include "Internet.h"

#include "Person.h"

unsigned int maxSSN = 0;

Person::Person()
	: ssn(++maxSSN),
	health(255), 
	job(nullptr),
	state(PersonState::JobSearching),
	stateChanged(true)
{
}

bool Person::hasStateChanged()
	{ return stateChanged; }

void Person::SearchForJob()
{
	const auto& jobBoard = Internet::Get()->getJobBoard();
	const auto& job = jobBoard->GetJob();
	if (job == nullptr)
	{
		std::cout << this->ssn << ": Unable to find a job!" << std::endl;
	}
	else
	{
		job->PrintDetails();
		std::cout << this->ssn << ": Found a job." << std::endl;
	}
}

void Person::ChangeState()
{
	switch (state)
	{
	case PersonState::JobSearching:
		SearchForJob();
		break;
	default:
		break;
	}
}
