#include "Treasury.h"

const int TILE_COST = 5000;

Treasury::Treasury() : balance(100000) { }

int Treasury::GetBalance() { return balance; }

void Treasury::BuyTile()
{
	balance -= TILE_COST;
}