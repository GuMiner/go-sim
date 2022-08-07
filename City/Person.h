#pragma once
#include <memory>

#include <Eigen/Core>

#include "Career.h"
#include "PersonState.h"
#include "Job.h"

class Person
{
	unsigned int ssn;
	unsigned char health;
	float gameX, gameY;

	std::unique_ptr<Job> job;

	PersonState state;
	Career career;
	bool stateChanged;

	void SearchForJob();
public:
	Person();
	Person(float x, float y);

	bool hasStateChanged();
	void ChangeState();

	Eigen::Vector2f GetPosition() const;
};

