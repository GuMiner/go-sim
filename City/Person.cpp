#include <iostream>
#include "Internet.h"

#include "Person.h"

unsigned int maxSSN = 0;

Person::Person()
	: ssn(++maxSSN),
	health(255),
	gameX(0), gameY(0),
	job(nullptr),
	state(PersonState::JobSearching),
	career(Career::CompanyFounder),
	stateChanged(true)
{
}

Person::Person(
	float x, float y) : Person()
{
	gameX = x;
	gameY = y;
}

bool Person::hasStateChanged()
	{ return stateChanged; }

Eigen::Vector2f Person::GetPosition() const { return Eigen::Vector2f(gameX, gameY); }

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
