#include "Utills.h"

size_t getFileSize(std::ifstream& file)
{
	size_t currentPos = file.tellg();
	file.seekg(0, std::ios::end);
	size_t fileSize = file.tellg();
	file.seekg(currentPos);
	return fileSize;
}

void printNumberBitbyBit(uint8_t num)
{
	unsigned mask = (1 << 7);
	for (size_t i = 0; i < 8; i++)
	{
		bool currBit = ((mask & num) == mask);
		std::cout << currBit;
		mask >>= 1;
	}
	std::cout << ' ';
}
