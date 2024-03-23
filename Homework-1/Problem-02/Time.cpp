#include <iostream>
#include <fstream>
#include <iomanip>

#include "Time.h"
#include "GlobalConstants.h"

bool Time::validateAndSet(unsigned lowerBound, unsigned upperBound, unsigned newValue, unsigned oldVlaue, unsigned multiplier)
{

	if (newValue >= lowerBound && newValue <= upperBound)
	{
		(secondsFromMidnight -= (oldVlaue * multiplier)) += (newValue * multiplier);
		return true;
	}
	else
		return false;
}

Time::Time(unsigned hours, unsigned mins, unsigned seconds)
{
	setHours(hours);
	setMins(mins);
	setSeconds(seconds);
}

unsigned Time::getHours() const
{
	return secondsFromMidnight / GlobalConstants::SECONDS_IN_HOURS;
}
unsigned Time::getMins() const
{
	return (secondsFromMidnight / 60) % 60;
}
unsigned Time::getSeconds() const
{
	return secondsFromMidnight % 60;
}

bool Time::setHours(unsigned hours)
{
	return validateAndSet(0, 23, hours, getHours(), GlobalConstants::SECONDS_IN_HOURS);
}
bool Time::setMins(unsigned mins)
{
	return validateAndSet(0, 59, mins, getMins(), GlobalConstants::SECONDS_IN_MINUTE);
}
bool Time::setSeconds(unsigned seconds)
{
	return validateAndSet(0, 59, seconds, getSeconds(), 1);
}

const void Time::print() const
{
	std::cout << std::setfill('0') << std::setw(2) << this->getHours() << ":"
		<< std::setw(2) << this->getMins() << ":"
		<< std::setw(2) << this->getSeconds() << " ";
}
int Time::getTimeInSeconds() const
{
	int seconds = this->getSeconds();
	seconds += this->getMins() * 60;
	seconds += this->getHours() * 3600;
	return seconds;
}