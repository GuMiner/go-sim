#pragma once

enum class Resource
{
	Farmland,
	Mineland,
	Rockland,
	Riverland,
	Sealand,
	Food,
};

class ResourceLimits
{
public:
	static int LandMin()
	{
		return (int)Resource::Farmland;
	}

	static int LandMax()
	{
		return (int)Resource::Sealand;
	}
};
