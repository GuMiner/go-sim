#pragma once
#include <memory>

#include "Population.h"
#include "GameGrid.h"
#include "Treasury.h"
#include "TimeShifts.h"

class Simulation
{
	Population population;
	GameGrid gameGrid;
	Treasury treasury;

	TimeShifts gameTime;
	bool isPaused;

public:
	Simulation();

	GameGrid& GetGrid();
	Treasury& GetTreasury();
	TimeShifts& GetTime();

	void Update(float currentTime);
	void PauseResume();

	void BuyTile(int x, int y);
};

