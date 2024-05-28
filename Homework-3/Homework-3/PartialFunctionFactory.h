#pragma once
#include <iostream>
#include "PartialFunction.h"

class PartialFunctionFactory
{
public:
	static PartialFunction* createFunction(const char*);

private:
	static PartialFunction* createByType(uint16_t, uint16_t, std::istream&);

	static PartialFunction* createMaxFunction(PartialFunction** functions, uint16_t n);
	static PartialFunction* createMinFunction(PartialFunction** functions, uint16_t n);
};