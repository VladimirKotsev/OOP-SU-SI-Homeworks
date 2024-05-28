#pragma once
#include "GlobalConstants.h"

class MultiSet
{
private:
	unsigned maxNumber = 0;
	uint8_t bitCount = 1;

	size_t bucketCount = 0;
	uint8_t* buckets = nullptr;

	void setBitCount(uint8_t bitCount);
	void setBucketCount(unsigned maxNumber, uint8_t bitCount);

	uint8_t getMaxContained() const;
	const unsigned getMaxNumber() const;
	const uint8_t getBitCount() const;

	void free();
	void copyFrom(const MultiSet& other);
	void setNumberCount(unsigned numToAdd, unsigned count);

public:
	MultiSet() = default;

	MultiSet(unsigned maxNumber, uint8_t bitCount);
	MultiSet(const MultiSet& other);
	~MultiSet();
	MultiSet& operator=(const MultiSet& other);

	void addNumber(unsigned numToAdd);
	unsigned timesContained(unsigned number) const;
	void printContained() const;
	void printMemoryContent() const;

	void parseFromFile(std::ifstream& ifs);
	void parseFromFile(const char* fileName);

	void saveToFile(std::ofstream& os) const;
	void saveToFile(const char* fileName) const;

	MultiSet& operator~(); // Addition

	friend MultiSet operator&(const MultiSet& lhs, const MultiSet& rhs); // Intersection
	friend MultiSet operator/(const MultiSet& lhs, const MultiSet& rhs); // Difference
};
