#pragma once

enum class Shift
{
	First, // Morning
	Second, // Afternoon
	Third, // Night
	Salaried, // Midday
	None, // Anti-salaried
};

enum class TimeOfDay
{
	Morning, // 6 AM - 12
	Afternoon, // 12 - 6 PM
	Evening, // 6 PM - 12
	Night, // 12 - 6 AM
};

enum class Season
{
	Spring, // planting.
	Summer, // growing.
	Fall, // harvesting.
	Winter, // prep / storing.
};

class TimeShifts
{
	float dayScale;
	float seasonScale;

	float lastTime;
	float gameTime;
public:
	TimeShifts();
	void UpdateGameTime(float currentTime);

	Shift GetSalariedShift() const;
	Shift GetHourlyShift() const;
	TimeOfDay GetTimeOfDay() const;
	Season GetSeason() const;
};