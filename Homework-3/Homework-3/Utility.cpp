#include "Utility.h"

size_t Utility::getFileSize(std::istream& is)
{
	size_t currPos = is.tellg();

	is.seekg(0, std::ios::end);
	size_t fileSize = is.tellg();

	is.seekg(currPos);
	return fileSize;
}

size_t Utility::symbolsToSentinel(const char* buffer)
{
	if (!buffer)
		return 0;

	size_t counter = 0;
	while (*buffer)
	{
		counter++;
		buffer++;
	}

	buffer++;
	return counter;
}

bool Utility::areDigits(const char* str)
{
	if (!str)
		return false;

	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return false;

		str++;
	}

	return true;
}

int Utility::convertCharToDigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return ch - '0';
	return -1;
}

int32_t Utility::parseToNumber(const char* str)
{
	//no need for nullptr check!
	int32_t result = 0;
	while (*str)
	{
		int digit = convertCharToDigit(*str);
		if (digit == -1)
			return 0;
		(result *= 10) += digit;
		str++;
	}
	return result;
}
