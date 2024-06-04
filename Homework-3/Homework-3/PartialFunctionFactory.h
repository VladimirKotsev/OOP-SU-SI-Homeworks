#pragma once

#include "FunctionalByCriteria.hpp"
#include "MaximumPartial.h"
#include "MinimumPartial.h"
#include "DefinedFunctional.h"
#include "UndefinedFunctional.h"
#include "BooleanFunctional.h"
#include "Utility.h"

class PartialFunctionFactory
{
public:
	static PartialFunction* createFunction(const char*);

private:
	static void readFunctionsFromFile(PartialFunction** functions, char* buffer, int16_t N);

	static PartialFunction* createByType(uint16_t, uint16_t, std::istream&);

	static PartialFunction* createMaxFunction(PartialFunction** functions, uint16_t n);
	static PartialFunction* createMinFunction(PartialFunction** functions, uint16_t n);
};