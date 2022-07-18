#include "GridCell.h"

GridCell::GridCell() { }

GridCell::GridCell(Resource resource)
	: resource(resource)
{

}

Resource GridCell::GetResource() const
{
	return resource;
}