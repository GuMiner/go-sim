#include "Treasury.h"

const int TILE_COST = 5000;

Treasury::Treasury() : balance(100000) { }

int Treasury::GetBalance() const { return balance; }

bool Treasury::BuyTile()
{
	if (balance <= TILE_COST)
	{
		return false;
	}

	balance -= TILE_COST;
	return true;
}