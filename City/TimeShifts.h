#pragma once

enum class Shift
{
	First, // Morning, 6 AM - 2 PM
	Second, // Afternoon, 2 PM - 10 PM
	Third, // Night, 10 PM - 6 AM
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
	MAX_SEASON
};

class TimeShifts
{
	float seasonScale;

	float lastTime;
	float gameTime;

public:
	TimeShifts();
	void UpdateGameTime(float currentTime, bool isPaused);

	int GetHour() const;
	int GetDay() const;
	Shift GetSalariedShift() const;
	Shift GetHourlyShift() const;
	TimeOfDay GetTimeOfDay() const;
	Season GetSeason() const;
};