#pragma once
#include <iostream>

class PartialFunction
{
public:
	virtual int32_t operator()(int32_t x) const = 0;
	virtual bool isDefined(int32_t x) const = 0;

	virtual PartialFunction* clone() const = 0;

	virtual ~PartialFunction() = default;
};

