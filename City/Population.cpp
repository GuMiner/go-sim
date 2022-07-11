#include "Internet.h"

#include "Population.h"


Population::Population()
	: people(), companies()
{
	// Turn on global wifi
	Internet::Enable();
}

void Population::AddPerson()
{
	people.push_back(
		std::unique_ptr<Person>(new Person()));
}

void Population::AddCompany()
{
	Company* company = new Company();
	company->AddJob();
	companies.push_back(std::unique_ptr<Company>(company));
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