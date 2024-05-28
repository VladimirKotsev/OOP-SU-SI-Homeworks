#include "MultiSet.h"
#include "Utills.h"

using namespace GlobalConstants;

void MultiSet::setBitCount(uint8_t bitCount)
{
	if (bitCount > 8)
	{
		throw std::invalid_argument("Bit count must be in the range 0 to 8 inclusive");
	}

	this->bitCount = bitCount;
}

void MultiSet::setBucketCount(unsigned maxNumber, uint8_t bitCount)
{
	this->bucketCount = maxNumber* bitCount / BITS_IN_BUCKET + 1;
}

uint8_t MultiSet::getMaxContained() const
{
	return (1 << this->bitCount) - 1;
}

void MultiSet::free()
{
	delete[] this->buckets;
	this->bucketCount = 0;
}

void MultiSet::copyFrom(const MultiSet& other)
{
	this->buckets = new uint8_t[other.bucketCount];

	for (int i = 0; i < other.bucketCount; i++)
		this->buckets[i] = other.buckets[i];

	this->bucketCount = other.bucketCount;
	this->maxNumber = other.maxNumber;
	this->bitCount = other.bitCount;
}

void MultiSet::setNumberCount(unsigned number, unsigned count)
{
	unsigned bucketIndex = number * this->bitCount / BITS_IN_BUCKET;
	unsigned bitIndex = number * this->bitCount % BITS_IN_BUCKET;

	unsigned mask = (1 << (BITS_IN_BUCKET - bitIndex - 1));
	
	for (int i = this->bitCount - 1; i >= 0; i--)
	{
		if (mask == 0) // switches to next bucket
		{
			mask = (1 << 7);
			bucketIndex++;
		}

		bool isBitUp = ((1 << i) & count) == (1 << i); // check if the bit is 1
		if (isBitUp)
		{
			this->buckets[bucketIndex] |= mask; // makes the bit 1
		}
		else
		{
			mask = ~mask;
			this->buckets[bucketIndex] &= mask; // makes the bit 0
			mask = ~mask;
		}
		mask >>= 1;
	}
}

MultiSet::MultiSet(unsigned maxNumber, uint8_t bitCount)
{
	setBitCount(bitCount);
	this->maxNumber = maxNumber;

	setBucketCount(maxNumber, bitCount);
	this->buckets = new uint8_t[bucketCount]{ 0 };
}

MultiSet::MultiSet(const MultiSet& other)
{
	copyFrom(other);
}

MultiSet::~MultiSet()
{
	free();
}

MultiSet& MultiSet::operator=(const MultiSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

const unsigned MultiSet::getMaxNumber() const
{
	return this->maxNumber;
}

const uint8_t MultiSet::getBitCount() const
{
	return this->bitCount;
}

void MultiSet::addNumber(unsigned numToAdd)
{
	if (numToAdd > maxNumber)
	{
		throw std::invalid_argument("Number is beyond max number");
		return;
	}
	uint8_t count = timesContained(numToAdd);

	if (count == getMaxContained()) // max times contained reached
		return;

	count++;
	setNumberCount(numToAdd, count);
}

unsigned MultiSet::timesContained(unsigned number) const
{
	if (number > maxNumber) // Invalid number
		return 0;

	unsigned bucketIndex = number * this->bitCount / BITS_IN_BUCKET;
	unsigned bitIndex = number * this->bitCount % BITS_IN_BUCKET;

	unsigned mask = (1 << (BITS_IN_BUCKET - bitIndex - 1));
	uint8_t count = 0;
	for (int i = this->bitCount - 1; i >= 0; i--)
	{
		if (mask == 0) //switches to next bucket
		{
			mask = (1 << 7);
			bucketIndex++;
		}

		count += ((mask & this->buckets[bucketIndex]) == mask) * (1 << i);
		mask >>= 1;
	}

	return count;
}

void MultiSet::printContained() const
{
	for (size_t i = 0; i < this->maxNumber; i++)
	{
		unsigned count = timesContained(i);

		if (count > 0)
			std::cout << "Number: " << i << " contained: " << count << std::endl;
	}

	std::cout << std::endl;
}

void MultiSet::printMemoryContent() const
{
	for (size_t i = 0; i < bucketCount; i++)
	{
		uint8_t currBucket = buckets[i];
		printNumberBitbyBit(currBucket);
	}

	std::cout << std::endl;
}

void MultiSet::parseFromFile(std::ifstream& ifs)
{
	free();
	ifs.read((char*)&this->bucketCount, sizeof(size_t));
	this->buckets = new uint8_t[this->bucketCount];
	ifs.read((char*)this->buckets, this->bucketCount);
	ifs.read((char*)&this->bitCount, sizeof(uint8_t));
	ifs.read((char*)&this->maxNumber, sizeof(unsigned));

	ifs.close();
}

void MultiSet::parseFromFile(const char* fileName)
{
	std::ifstream ifs(fileName, std::ios::binary | std::ios::in);
	if (!ifs.is_open())
		throw std::invalid_argument("File not found!");

	return parseFromFile(ifs);
}

void MultiSet::saveToFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&this->bucketCount, sizeof(size_t));
	ofs.write((const char*)this->buckets, bucketCount * sizeof(uint8_t));

	ofs.write((const char*)&this->bitCount, sizeof(uint8_t));
	ofs.write((const char*)&this->maxNumber, sizeof(unsigned));
}

void MultiSet::saveToFile(const char* fileName) const
{
	std::ofstream ofs(fileName, std::ios::binary | std::ios::out | std::ios::trunc);
	if (!ofs.is_open())
		throw std::invalid_argument("File not found!");

	saveToFile(ofs);
	ofs.close(); // calls flush()
}

MultiSet& MultiSet::operator~() // Addition
{
	for (size_t i = 0; i < maxNumber; i++)
	{
		uint8_t count = timesContained(i);
		count = (1 << bitCount) - 1 - count; // 2^k - 1 - p
		setNumberCount(i, count);
	}

	return *this;
}

MultiSet operator&(const MultiSet& lhs, const MultiSet& rhs) // Intersection
{
	uint8_t bitCount = 0;
	unsigned maxNumber = 0;
	if (lhs.bitCount < rhs.bitCount)
		bitCount = lhs.bitCount;
	else
		bitCount = rhs.bitCount;

	if (lhs.maxNumber < rhs.maxNumber)
		maxNumber = rhs.maxNumber;
	else
		maxNumber = lhs.maxNumber;


	MultiSet result(maxNumber, bitCount);
	for (unsigned i = 0; i < maxNumber; i++)
	{
		if (lhs.timesContained(i) > 0 && rhs.timesContained(i) > 0)
			result.setNumberCount(i, 1);
	}

	return result;
}

MultiSet operator/(const MultiSet& lhs, const MultiSet& rhs) // Difference
{
	MultiSet result(lhs.maxNumber, lhs.bitCount);
	for (unsigned i = 0; i < lhs.maxNumber; i++)
	{
		int count = lhs.timesContained(i) - rhs.timesContained(i);
		if (count < 0)
			count = 0;

		result.setNumberCount(i, count);
	}

	return result;
}


