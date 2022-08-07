#include "Internet.h"

#include "Population.h"


Population::Population()
	: people(), companies()
{
	// Turn on global wifi
	Internet::Enable();
}

void Population::AddPerson(Person* person)
{
	people.push_back(person);
}

std::vector<Person*>& Population::GetPeople()
{
	return people;
}


void Population::AddCompany()
{
	Company* company = new Company();
	company->AddJob();
	companies.push_back(company);
}

void Population::Simulate()
{
	for (const auto & person: people)
	{
		if (person->hasStateChanged())
		{
			person->ChangeState();
		}
	}
}