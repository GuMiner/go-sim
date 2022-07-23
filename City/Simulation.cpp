#include "Zone.h"

#include "Simulation.h"

Simulation::Simulation()
	: population(), gameGrid(), treasury(),
	  isPaused(false), lastTime(0.0f), gameTime(0.0f)
{

}

GameGrid& Simulation::GetGrid() { return gameGrid; }
Treasury& Simulation::GetTreasury() { return treasury; }

void Simulation::Update(float currentTime)
{
	if (!isPaused)
	{
		gameTime += (currentTime - lastTime);
		
		// Continue the simulation
	}

	lastTime = currentTime;
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