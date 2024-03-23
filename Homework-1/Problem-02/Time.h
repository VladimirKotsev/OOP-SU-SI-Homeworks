#pragma once

#include <ostream>

class Time
{
private:
	unsigned secondsFromMidnight;
	bool validateAndSet(unsigned lowerBound, unsigned upperBound, unsigned newValue, unsigned oldVlaue, unsigned multiplier);
public:
	Time() = default;
	Time(unsigned hours, unsigned mins, unsigned seconds);

	unsigned getHours() const;
	unsigned getMins() const;
	unsigned getSeconds() const;

	int getTimeInSeconds() const;

	bool setHours(unsigned hours);
	bool setMins(unsigned mins);
	bool setSeconds(unsigned seconds);

	const void print() const;
};