#pragma once
#include "Resources.h"
#include "Zone.h"

class GridCell
{
	Zone zone;
	Resource resource;
public:
	GridCell();
	GridCell(Resource resource);
	
	void SetZone(Zone zone);
	Resource GetResource() const;
	Zone GetZone() const;
};

