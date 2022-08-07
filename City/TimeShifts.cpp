#include <iostream>

#include "TimeShifts.h"

const int DayScale = 12;

TimeShifts::TimeShifts()
	: seasonScale(10),
	  lastTime(0),
	  gameTime(0),
	lastDay(0),
	lastHour(0),
	dayShift(false),
	hourShift(false)
{

}

int TimeShifts::GetDay() const
{
	return (int)(gameTime / DayScale);
}

int TimeShifts::GetHour() const
{
	return (int)gameTime % DayScale;
}

void TimeShifts::UpdateGameTime(float currentTime, bool isPaused)
{
	if (!isPaused) { gameTime += (currentTime - lastTime); }
	lastTime = currentTime;

	if (lastDay != GetDay())
	{
		lastDay = GetDay();
		dayShift = true;
	}
	else
	{
		dayShift = false;
	}

	if (lastHour != GetHour())
	{
		lastHour = GetHour();
		hourShift = true;
	}
	else
	{
		hourShift = false;
	}
}

Shift TimeShifts::GetHourlyShift() const
{
	int hour = GetHour();
	if (hour < 4) { return Shift::First; }
	if (hour < 8) { return Shift::Second; }
	return Shift::Third;
}

Shift TimeShifts::GetSalariedShift() const
{
	int hour = GetHour();
	if (hour >= 4 && hour <= 8) { return Shift::Salaried; }
	return Shift::None;
}

TimeOfDay TimeShifts::GetTimeOfDay() const
{
	int hour = GetHour();
	if (hour < 3) { return TimeOfDay::Night; }
	if (hour < 6) { return TimeOfDay::Morning; }
	if (hour < 9) { return TimeOfDay::Afternoon; }
	return TimeOfDay::Evening;
}

Season TimeShifts::GetSeason() const
{
	int day = GetDay();
	Season season = (Season)(day % (int)Season::MAX_SEASON);
	return season;
}

bool TimeShifts::IsNextDay() const { return dayShift; }
bool TimeShifts::IsNextHour() const { return hourShift; }