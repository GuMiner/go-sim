#include <iostream>
#include <limits>

#include "GameGrid.h"

GameGrid::GameGrid()
	: grid(), 
	minX(INT_MAX), minY(INT_MAX),
	maxX(INT_MIN), maxY(INT_MAX)
{

}

Resource GameGrid::GetRandomLandResource()
{
	return (Resource)(ResourceLimits::LandMin() + 
		(rand() % (ResourceLimits::LandMax() - ResourceLimits::LandMin())));
}

void GameGrid::UpdateMinMax(int x, int y)
{
	if (minX == INT_MAX || x < minX)
	{
		minX = x;
	}

	if (minY == INT_MAX || y < minY)
	{
		minY = y;
	}

	if (maxX == INT_MIN || x > maxX)
	{
		maxX = x;
	}

	if (maxY == INT_MIN || y > maxY)
	{
		maxY = y;
	}
}

void GameGrid::Generate(int x, int y)
{
	// For now, randomly generate resources
	if (grid.count(x) == 0)
	{
		grid[x] = std::unordered_map<int, GridCell>();
	}

	grid[x][y] = GridCell(GetRandomLandResource());
	UpdateMinMax(x, y);
}

GridCell& GameGrid::Get(int x, int y)
{
	if (grid.count(x) == 0 || grid[x].count(y) == 0)
	{
		Generate(x, y);
		// std::cout << "Generated " << x << ", " << y << std::endl;
	}

	return grid[x][y];
}

Eigen::Vector2i GameGrid::GetRandomEdge() const
{
	// Assume generation always includes all sides
	int xDiff = maxX - minX;
	int yDiff = maxY - minY;
	
	// TODO, assume top only
	return Eigen::Vector2i(minX + rand() % xDiff, minY);
}