#pragma once
#include <iostream>
#include <fstream>
#include "Utills.h"
#include "Point.h"

using namespace GlobalConstants;

class ModifiableIntegersFunction
{
private:
	Point* values = nullptr;

	void free();
	void copyFrom(const ModifiableIntegersFunction& other);

	Point functionOfPower(int16_t index, unsigned k) const;
	size_t getIndex(int16_t num) const;
public:
	ModifiableIntegersFunction() = default;
	ModifiableIntegersFunction(int16_t(*func)(int16_t));
	ModifiableIntegersFunction(const ModifiableIntegersFunction& other);
	ModifiableIntegersFunction& operator=(const ModifiableIntegersFunction& other);
	~ModifiableIntegersFunction();

	void disablePoint(int16_t x);
	void changeValueAtX(int16_t x, int16_t y);

	void printGraph(int16_t x1, int16_t y1) const;

	bool isInjection() const;
	bool isSurjection() const;
	bool isBijection() const;

	void parseFromFile(std::ifstream& ifs);
	void parseFromFile(const char* fileName);

	void saveToFile(std::ofstream& os) const;
	void saveToFile(const char* fileName) const;

	const Point& operator[](size_t) const;

	ModifiableIntegersFunction& operator+=(const ModifiableIntegersFunction& other);
	ModifiableIntegersFunction& operator-=(const ModifiableIntegersFunction& other);

	ModifiableIntegersFunction& operator()(const ModifiableIntegersFunction& other); // Composition

	ModifiableIntegersFunction& operator^(unsigned k);

	ModifiableIntegersFunction inverse() const;

	friend bool operator||(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
};

ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);

bool operator<(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
bool operator<=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
bool operator>(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
bool operator>=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
