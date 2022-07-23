#include "GridCell.h"

GridCell::GridCell() { }

GridCell::GridCell(Resource resource)
	: resource(resource), zone(Zone::UNINCORPORATED)
{

}

void GridCell::SetZone(Zone zone)
{
	this->zone = zone;
}

Zone GridCell::GetZone() const { return zone; }

Resource GridCell::GetResource() const { return resource; }
