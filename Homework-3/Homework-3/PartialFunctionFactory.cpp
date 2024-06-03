#include <fstream>
#include <sstream>

#include "PartialFunctionFactory.h"
#include "FunctionalByCriteria.hpp"
#include "MaximumPartial.h"
#include "MinimumPartial.h"
#include "BooleanFunctional.h"
#include "DefinedFunctional.h"
#include "UndefinedFunctional.h"
#include "Utility.h"

PartialFunction* PartialFunctionFactory::createFunction(const char* filename)
{
	if (!filename)
		throw std::invalid_argument("File name cannot be null pointer!");

	std::ifstream ifs(filename, std::ios::binary | std::ios::in);

	if (!ifs.is_open())
		throw std::runtime_error("File not found or cannot be open!");

	uint16_t N;
	uint16_t T;

	ifs.read((char*)&N, sizeof(uint16_t));
	ifs.read((char*)&T, sizeof(uint16_t));

	return createByType(N, T, ifs);
}

PartialFunction* PartialFunctionFactory::createByType(uint16_t N, uint16_t T, std::istream& ifs)
{
	if (N < 0 || N > 32)
		throw std::invalid_argument("Invalid value for N!");

	switch (T)
	{
	case 0:
	{
		int32_t* domain = new int32_t[N];
		int32_t* range = new int32_t[N];

		ifs.read((char*)domain, sizeof(int32_t) * N);
		ifs.read((char*)range, sizeof(int32_t) * N);

		return new FunctionalByCriteria<DefinedFunctional>(DefinedFunctional(domain, range, N));
	}
	case 1:
	{
		int32_t* domain = new int32_t[N];
		ifs.read((char*)domain, sizeof(int32_t) * N);

		return new FunctionalByCriteria<UndefinedFunctional>(UndefinedFunctional(domain, N));
	}
	case 2:
	{
		int32_t* domain = new int32_t[N];
		ifs.read((char*)domain, sizeof(int32_t) * N);

		return new FunctionalByCriteria<BooleanFunctional>(BooleanFunctional(domain, N));
	}
	case 3:
	case 4:
	{
		PartialFunction** functions = new PartialFunction * [N];

		size_t fileSize = UtilityFuncs::getFileSize(ifs);
		fileSize -= sizeof(uint16_t) * 2;

		char* buffer = new char[fileSize];
		ifs.read(buffer, fileSize);

		try
		{
			UtilityFuncs::readFunctionsFromFile(functions, buffer, N);
		}
		catch (const std::runtime_error& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
		catch (const std::invalid_argument& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}

		delete[] buffer;
		return createMaxFunction(functions, N);
	}
	default:
		throw std::invalid_argument("Invalid value for T!");
		break;
	}
}

PartialFunction* PartialFunctionFactory::createMaxFunction(PartialFunction** funcs, uint16_t N)
{
	return new MaximumPartial(funcs, N);
}

PartialFunction* PartialFunctionFactory::createMinFunction(PartialFunction** funcs, uint16_t N)
{
	return new MinimumPartial(funcs, N);
}