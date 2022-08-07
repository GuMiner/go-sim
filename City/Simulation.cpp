#include <iostream>

#include "Zone.h"

#include "Simulation.h"

Simulation::Simulation()
	: population(), gameGrid(), treasury(),
	  gameTime(), isPaused(false)
{

}

GameGrid& Simulation::GetGrid() { return gameGrid; }
Treasury& Simulation::GetTreasury() { return treasury; }
TimeShifts& Simulation::GetTime() { return gameTime; }
Population& Simulation::GetPopulation() { return population; }

void Simulation::Update(float currentTime)
{
	gameTime.UpdateGameTime(currentTime, isPaused);
	
	if (gameTime.IsNextHour())
	{
		Eigen::Vector2i spawnPoint = gameGrid.GetRandomEdge();
		// TODO assume space in city
		population.AddPerson(
			new Person((float)spawnPoint.x(), (float)spawnPoint.y()));
		std::cout << "Added to" << spawnPoint << std::endl;
	}

	// TODO need to update CEO to form a company on available space.
	// population.Simulate();


	// Residential:
	// - Move in workers.
	// - If people are working remotely, move them in first.

	// Company:
	// - Find local workers.
	// - If none found, hire someone remote.

	// People:
	// - Work to company at shift start
	// - Leave company at shift end
	// - Move off the board or to home.
}

void Simulation::PauseResume()
{
	isPaused = !isPaused;
}

void Simulation::BuyTile(int x, int y)
{
	GridCell& gridCell = gameGrid.Get(x, y);
	if (gridCell.GetZone() == Zone::UNINCORPORATED)
	{
		if (treasury.BuyTile())
		{
			gridCell.SetZone(Zone::BOUGHT);
		}
	}
}