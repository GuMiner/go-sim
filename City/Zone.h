#pragma once

enum class Zone
{
	UNINCORPORATED, // Default, also MIN_ZONE
	BOUGHT, // Just purchased, but not usable for anything.
	UNRESTRICTED, // Can be used for anything
	MAX_ZONE 
};