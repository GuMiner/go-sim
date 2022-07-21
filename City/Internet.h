#pragma once
#include <memory>
#include "JobBoard.h"

class Internet
{
	std::unique_ptr<JobBoard> jobBoard;

public:
	Internet();
	static void Enable();

	static const std::unique_ptr<Internet>& Get();
	const std::unique_ptr<JobBoard>& getJobBoard();
};

