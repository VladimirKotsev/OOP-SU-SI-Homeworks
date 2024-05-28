#include "PartialFunctionFactory.h"
#include "PartialByCriteria.h"
#include "MaximumPartial.h"
#include "MinimumPartial.h"
#include "BaseFunctional.h"
#include "BooleanFunctional.h"
#include "DefinedFunctional.h"
#include "UndefinedFunctional.h"
#include <fstream>

PartialFunction* PartialFunctionFactory::createFunction(const char* filename)
{
	if (!filename)
		throw std::invalid_argument("File name cannot be null pointer!");

	std::ifstream is(filename, std::ios::binary | std::ios::in);

	if (!is.is_open())
		throw std::runtime_error("File not found or cannot be open!");

	uint16_t N;
	uint16_t T;

	is.read((char*)&N, sizeof(uint16_t));
	is.read((char*)&T, sizeof(uint16_t));

	return createByType(N, T, is);
}

PartialFunction* PartialFunctionFactory::createByType(uint16_t N, uint16_t T, std::istream& is)
{
	if (N < 0 || N > 32)
		throw std::invalid_argument("Invalid value for N!");

	switch (T)
	{
	case 0:
	{
		int32_t* domain = new int32_t[N];
		int32_t* range = new int32_t[N];

		is.read((char*)domain, sizeof(int32_t) * N);
		is.read((char*)range, sizeof(int32_t) * N);

		return createFunctionByCriteria(new DefinedFunctional(domain, range, N));
	}
	case 1:
	{
		int32_t* domain = new int32_t[N];
		is.read((char*)domain, sizeof(int32_t) * N);

		return createFunctionByCriteria(new UndefinedFunctional(domain, N));
	}
	case 2:
	{
		int32_t* domain = new int32_t[N];
		is.read((char*)domain, sizeof(int32_t) * N);

		return createFunctionByCriteria(new BooleanFunctional(domain, N));
	}
	case 3:
	{
		//return createMaxFunction(N,is);
	}
	case 4:
	{
		//return createMinFunction(N, is);
	}
	default:
		throw std::invalid_argument("Invalid value for T!");
		break;
	}
}

PartialFunction* PartialFunctionFactory::createFunctionByCriteria(const BaseFunctional* obj)
{
	return new PartialByCriteria(obj);
}

PartialFunction* PartialFunctionFactory::createMaxFunction(const BaseFunctional* obj)
{
	return nullptr;
}

PartialFunction* PartialFunctionFactory::createMinFunction(const BaseFunctional* obj)
{
	return nullptr;
}