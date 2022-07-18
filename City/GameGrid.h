#pragma once
#include <unordered_map>

#include "GridCell.h"

class GameGrid
{
	std::unordered_map<int, std::unordered_map<int, GridCell>> grid;

	Resource GetRandomLandResource();
	void Generate(int x, int y);

public:
	GameGrid();
	GridCell& Get(int x, int y);
};

