#include <iostream>
#include "Job.h"

Job::Job(int companyId,
	Resource in, unsigned char amountIn,
	Resource out, unsigned char amountOut)
	: companyId(companyId),
	input(in),
	amountIn(amountIn),
	output(out),
	amountOut(amountOut)
{
}

void Job::PrintDetails() const
{
	std::cout << companyId << ": " << 
		(int)input << "&" << (int)amountIn << " -> " <<
		(int)output << "&" << (int)amountOut << std::endl;
}