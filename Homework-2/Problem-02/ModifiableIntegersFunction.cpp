#include "ModifiableIntegersFunction.h"
#include <iomanip>

void ModifiableIntegersFunction::free()
{
	delete[] values;
}

void ModifiableIntegersFunction::copyFrom(const ModifiableIntegersFunction& other)
{
	this->values = new Point[ARRAY_SIZE];

	for (size_t index = 0; index < ARRAY_SIZE; index++)
	{
		values[index] = other.values[index];
	}
}

Point ModifiableIntegersFunction::functionOfPower(int16_t index, unsigned k) const
{
	Point result;
	result.y = index;
	result.isDefined = true;
	for (size_t i = 0; i < k; i++)
	{
		result = values[result.y];
	}

	return result;
}

size_t ModifiableIntegersFunction::getIndex(int16_t num) const
{
	return num + MAX_NUMBER + 1;
}

ModifiableIntegersFunction::ModifiableIntegersFunction(int16_t(*func)(int16_t))
{
	this->values = new Point[ARRAY_SIZE];
	for (int16_t i = MIN_NUMBER; i < MAX_NUMBER; i++)
	{
		size_t index = getIndex(i);
		this->values[index] = Point(func(i), true);
	}
}

ModifiableIntegersFunction::ModifiableIntegersFunction(const ModifiableIntegersFunction& other)
{
	copyFrom(other);
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator=(const ModifiableIntegersFunction& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

ModifiableIntegersFunction::~ModifiableIntegersFunction()
{
	free();
}

void ModifiableIntegersFunction::disablePoint(int16_t x)
{
	size_t index = getIndex(x);
	this->values[index].isDefined = false;
}

void ModifiableIntegersFunction::changeValueAtX(int16_t x, int16_t y)
{

	size_t index = getIndex(x);
	this->values[index].y = y;
}

void ModifiableIntegersFunction::printGraph(int16_t x1, int16_t y1) const
{
	int16_t x2 = x1 + 20;
	int16_t y2 = y1 + 20;

	for (int16_t y = y2; y >= y1; y--)
	{
		std::cout << std::setw(6) << y << " |";
		for (int16_t x = x1; x < x2; x++)
		{
			if (!this->values[getIndex(x)].isDefined)
			{
				std::cout << ' ';
				continue;
			}

			if (this->values[getIndex(x)].y == y)
				std::cout << '*';
			else
				std::cout << ' ';
			std::cout << ' ';
		}
		std::cout << '|' << std::endl;
	}

	std::cout << std::setw(9);
	for (size_t i = 0; i < 20; i++)
	{
		std::cout << " _";
	}
	std::cout << std::endl;
}

bool ModifiableIntegersFunction::isInjection() const //TO FIX
{
	bool accuredNumbers[ARRAY_SIZE]{ false };
	for (size_t i = 0; i < ARRAY_SIZE; i++)
	{
		if (accuredNumbers[i])
			return false;
		if (this->values[i].isDefined)
			accuredNumbers[i] = true;
	}

	return true;
}

bool ModifiableIntegersFunction::isSurjection() const
{
	bool accuredNumbers[ARRAY_SIZE]{ false };
	for (size_t i = 0; i < ARRAY_SIZE; i++)
	{
		if (!this->values[i].isDefined)
		{
			size_t index = getIndex(this->values[i].y);
			accuredNumbers[index] = true;
		}
	}

	for (size_t i = 0; i < ARRAY_SIZE; i++)
	{
		if (!accuredNumbers[i])
			return false;
	}

	return true;
}

bool ModifiableIntegersFunction::isBijection() const
{
	return (isBijection() && isSurjection());
}

void ModifiableIntegersFunction::parseFromFile(std::ifstream& ifs)
{
	if (values == nullptr)
		values = new Point[ARRAY_SIZE];

	for (size_t i = 0; i < ARRAY_SIZE; i++)
	{
		ifs.read((char*)&values[i], sizeof(Point));
	}

	ifs.close();
}

void ModifiableIntegersFunction::parseFromFile(const char* fileName)
{
	std::ifstream ifs(fileName, std::ios::binary | std::ios::in);
	if (!ifs.is_open())
		throw std::invalid_argument("File not found!");

	return parseFromFile(ifs);
}

void ModifiableIntegersFunction::saveToFile(std::ofstream& os) const
{
	for (size_t i = 0; i < ARRAY_SIZE; i++)
	{
		os.write((const char*)&this->values[i], sizeof(Point));
	}
}

void ModifiableIntegersFunction::saveToFile(const char* fileName) const
{
	std::ofstream ofs(fileName, std::ios::binary | std::ios::out | std::ios::trunc);
	if (!ofs.is_open())
		throw std::invalid_argument("File not found!");

	saveToFile(ofs);
	ofs.close();
}

const Point& ModifiableIntegersFunction::operator[](size_t index) const
{
	return this->values[index];
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator+=(const ModifiableIntegersFunction& other)
{
	for (int16_t i = MIN_NUMBER; i < MAX_NUMBER; i++)
	{
		size_t index = getIndex(i);
		this->values[index] += other.values[index];
	}

	return *this;
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator-=(const ModifiableIntegersFunction& other)
{
	for (int16_t i = MIN_NUMBER; i < MAX_NUMBER; i++)
	{
		size_t index = getIndex(i);
		this->values[index] -= other.values[index];
	}

	return *this;
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator()(const ModifiableIntegersFunction& other)
{
	for (int16_t i = MIN_NUMBER; i < MAX_NUMBER; i++)
	{
		size_t index = getIndex(i);
		this->values[index].y = this->values[getIndex(other.values[index].y)].y;

		if (this->values[index].isDefined && other.values[index].isDefined)
			this->values[index].isDefined = true;
		else
			this->values[index].isDefined = false;
	}

	return *this;
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator^(unsigned k)
{
	for (int16_t i = MIN_NUMBER; i < MAX_NUMBER; i++)
	{
		size_t index = getIndex(i);
		this->values[index] = functionOfPower(index, k);
	}

	return *this;
}

ModifiableIntegersFunction ModifiableIntegersFunction::inverse() const
{
	if (!this->isInjection())
		throw std::logic_error("Cannot inverse a function which is not injective!");

	ModifiableIntegersFunction result;
	result.values = new Point[ARRAY_SIZE];
	for (int16_t i = MIN_NUMBER; i < MAX_NUMBER; i++)
	{
		size_t index = getIndex(i);

		if (this->values[index].isDefined)
		{
			int16_t x = i;
			int16_t y = this->values[index].y;

			result.values[getIndex(y)] = Point(x, true);
		}
	}

	return result;
}

ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	ModifiableIntegersFunction result(lhs);
	result += rhs;

	return result;
}

ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	ModifiableIntegersFunction result(lhs);
	result -= rhs;

	return result;
}

bool operator<(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int16_t i = MIN_NUMBER; i < MAX_NUMBER; i++)
	{
		size_t index = i + MAX_NUMBER + 1;
		bool lhsIsDefined = lhs[index].isDefined;
		bool rhsIsDefined = rhs[index].isDefined;
		if (lhsIsDefined && rhsIsDefined) // they are equal
		{
			return false;
		}
		else if (rhsIsDefined && (lhs[index].y >= MIN_NUMBER))
		{
			return false;
		}
		else if (lhsIsDefined && (MIN_NUMBER >= rhs[index].y))
		{
			return false;
		}
		else if (lhs[index].y >= lhs[index].y)
		{
			return false;
		}
	}

	return true;
}

bool operator<=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int16_t i = MIN_NUMBER; i < MAX_NUMBER; i++)
	{
		size_t index = i + MAX_NUMBER + 1;
		bool lhsIsDefined = lhs[index].isDefined;
		bool rhsIsDefined = rhs[index].isDefined;
		if (rhsIsDefined && (lhs[index].y > MIN_NUMBER))
		{
			return false;
		}
		else if (lhs[index].y > lhs[index].y)
		{
			return false;
		}
	}

	return true;
}

bool operator>(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int16_t i = MIN_NUMBER; i < MAX_NUMBER; i++)
	{
		size_t index = i + MAX_NUMBER + 1;
		bool lhsIsDefined = lhs[index].isDefined;
		bool rhsIsDefined = rhs[index].isDefined;
		if (lhsIsDefined && rhsIsDefined) // they are equal
		{
			return false;
		}
		else if (lhsIsDefined && (MIN_NUMBER <= rhs[index].y))
		{
			return false;
		}
		else if (rhsIsDefined && (lhs[index].y <= MIN_NUMBER))
		{
			return false;
		}
		else if (lhs[index].y <= lhs[index].y)
		{
			return false;
		}
	}

	return true;
}

bool operator>=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int16_t i = MIN_NUMBER; i < MAX_NUMBER; i++)
	{
		size_t index = i + MAX_NUMBER + 1;
		bool lhsIsDefined = lhs[index].isDefined;
		bool rhsIsDefined = rhs[index].isDefined;
		if (lhsIsDefined && (MIN_NUMBER < rhs[index].y))
		{
			return false;
		}
		else if (lhs[index].y < lhs[index].y)
		{
			return false;
		}
	}

	return true;
}

bool operator||(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{

	int16_t yDifference = 0;
	size_t index = 0;
	for (int16_t i = MIN_NUMBER; i < MAX_NUMBER; i++)
	{
		index = i + MAX_NUMBER + 1;
		bool areDefined = lhs[index].isDefined && rhs[index].isDefined;
		if (areDefined)
		{
			yDifference = lhs[index].y - rhs[index].y;
			break;
		}
	}

	for (int16_t i = MIN_NUMBER; i < MAX_NUMBER; i++)
	{
		index = i + MAX_NUMBER + 1;
		bool lhsDefined = lhs[index].isDefined;
		bool rhsDefined = rhs[index].isDefined;
		if (lhsDefined && rhsDefined && (yDifference != lhs[index].y - rhs[index].y))
			return false;
	}

	return true;
}
