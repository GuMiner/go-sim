#pragma once
class Treasury
{
	int balance;
public:
	Treasury();
	int GetBalance() const;
	bool BuyTile();
};

