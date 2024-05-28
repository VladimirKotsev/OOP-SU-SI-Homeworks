#pragma once
#include <iostream>
//#include <cstdint>

class PartialFunction
{
private:


public:
	virtual int32_t operator()(int32_t x) const = 0;
	bool isDefined(int32_t x);

	PartialFunction();

	virtual ~PartialFunction() = default;
};

