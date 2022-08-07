#pragma once
#include <vector>
#include "Company.h"
#include "Person.h"

class Population
{
	std::vector<Person*> people;
	std::vector<Company*> companies;

public:
	Population();

	void AddPerson(Person* person);
	void AddCompany();
	void Simulate();

	std::vector<Person*>& GetPeople();
};

