#pragma once
#include <iostream>

struct Point
{
	int16_t y = 0;
	bool isDefined = true;

	Point() = default;
	Point(uint16_t y, bool isDefined);

	Point& operator=(const Point& other);
	Point& operator+=(const Point& other);
	Point& operator-=(const Point& other);
};