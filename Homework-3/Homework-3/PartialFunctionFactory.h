#pragma once
#include <iostream>
#include "PartialFunction.h"
#include "BaseFunctional.h"

class PartialFunctionFactory
{
public:
	static PartialFunction* createFunction(const char*);

private:
	static PartialFunction* createByType(uint16_t, uint16_t, std::istream&);

	static PartialFunction* createFunctionByCriteria(const BaseFunctional* obj);
	static PartialFunction* createMaxFunction(const BaseFunctional* obj);
	static PartialFunction* createMinFunction(const BaseFunctional* obj);

};