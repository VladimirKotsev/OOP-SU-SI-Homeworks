#pragma once
#include <fstream>

namespace UtilityFuncs
{
	size_t getFileSize(std::istream& is)
	{
		size_t currPos = is.tellg();

		is.seekg(0, std::ios::end);
		size_t fileSize = is.tellg();

		is.seekg(currPos);
		return fileSize;
	}

	size_t symbolsToSentinel(const char* buffer)
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

	void readFunctionsFromFile(PartialFunction** functions, char* buffer, int16_t N)
	{
		for (size_t i = 0; i < N; i++)
		{
			std::stringstream ss(buffer);

			size_t fileName = UtilityFuncs::symbolsToSentinel(buffer);
			buffer += fileName + 1;
			char* currentFileName = new char[fileName];

			ss >> currentFileName;

			functions[i] = PartialFunctionFactory::createFunction(currentFileName);
		}
	}
}