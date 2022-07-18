#include "Simulation.h"

Simulation::Simulation()
	: population(), gameGrid(),
	  isPaused(false), lastTime(0.0f), gameTime(0.0f)
{

}

GameGrid& Simulation::GetGrid()
{
	return gameGrid;
}

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