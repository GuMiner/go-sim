#pragma once
#include <memory>

#include "Population.h"
#include "GameGrid.h"
#include "Treasury.h"

class Simulation
{
	Population population;
	GameGrid gameGrid;
	Treasury treasury;

	bool isPaused;
	float lastTime;
	float gameTime;

public:
	Simulation();

	GameGrid& GetGrid();
	Treasury& GetTreasury();

	void Update(float currentTime);
	void PauseResume();
};

