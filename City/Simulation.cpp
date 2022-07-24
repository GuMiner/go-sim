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

void Simulation::Update(float currentTime)
{
	gameTime.UpdateGameTime(currentTime, isPaused);
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