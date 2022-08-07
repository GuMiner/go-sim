#pragma once
#include <unordered_map>
#include <Eigen\Core>

#include "GridCell.h"

class GameGrid
{
	int minX, minY, maxX, maxY;

	std::unordered_map<int, std::unordered_map<int, GridCell>> grid;

	Resource GetRandomLandResource();
	void UpdateMinMax(int x, int y);
	void Generate(int x, int y);

public:
	GameGrid();
	GridCell& Get(int x, int y);

	Eigen::Vector2i GetRandomEdge() const;
};

