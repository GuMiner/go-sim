#pragma once
#include "Resources.h"

class GridCell
{
	Resource resource;
public:
	GridCell();
	GridCell(Resource resource);
	Resource GetResource() const;
};

