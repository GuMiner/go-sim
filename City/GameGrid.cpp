#include "GameGrid.h"

GameGrid::GameGrid()
	: grid()
{

}

Resource GameGrid::GetRandomLandResource()
{
	return (Resource)(ResourceLimits::LandMin() + 
		(rand() % (ResourceLimits::LandMax() - ResourceLimits::LandMin())));
}

void GameGrid::Generate(int x, int y)
{
	// For now, randomly generate resources
	if (grid.count(x) == 0)
	{
		grid[x] = std::unordered_map<int, GridCell>();
	}

	grid[x][y] = GridCell(GetRandomLandResource());
}

GridCell& GameGrid::Get(int x, int y)
{
	if (grid.count(x) == 0 || grid[x].count(y) == 0)
	{
		Generate(x, y);
	}

	return grid[x][y];
}
