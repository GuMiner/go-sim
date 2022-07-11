#pragma once
#include <memory>
#include <vector>
#include "Company.h"
#include "Person.h"

class Population
{
	std::vector<std::unique_ptr<Person>> people;
	std::vector<std::unique_ptr<Company>> companies;

public:
	Population();

	void AddPerson();
	void AddCompany();
	void Simulate();
};

