#pragma once
#include <memory>

#include "Population.h"
#include "GameGrid.h"

class Simulation
{
	Population population;
	GameGrid gameGrid;

	bool isPaused;
	float lastTime;
	float gameTime;

public:
	Simulation();

	GameGrid& GetGrid();

	void Update(float currentTime);
	void PauseResume();
};

