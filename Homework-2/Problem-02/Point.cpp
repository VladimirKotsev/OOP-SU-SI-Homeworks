#include "Point.h"

Point::Point(uint16_t y, bool isDefined) : y(y), isDefined(isDefined){}

Point& Point::operator=(const Point& other)
{
	this->y = other.y;
	this->isDefined = other.isDefined;

	return *this;
}

Point& Point::operator+=(const Point& other)
{
	this->y += other.y;
	return *this;
}

Point& Point::operator-=(const Point& other)
{
	this->y -= other.y;
	return *this;
}
