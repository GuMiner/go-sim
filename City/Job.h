#pragma once
#include "Resources.h"

class Job
{
	unsigned int companyId;

	Resource input;
	unsigned char amountIn;
	
	Resource output;
	unsigned char amountOut;
public:
	Job(int companyId,
		Resource in, unsigned char amountIn,
		Resource out, unsigned char amountOut);

	void PrintDetails() const;
};

