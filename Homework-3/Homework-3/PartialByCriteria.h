#pragma once
#include "PartialFunction.h"
#include "BaseFunctional.h"

class PartialByCriteria : public PartialFunction
{
private:
	BaseFunctional* baseFunctional;
	Pair<bool, int32_t>& (*function)(int32_t x);

public:
	PartialByCriteria(BaseFunctional* baseFunctional);
	PartialByCriteria(Pair<bool, int32_t>& (*function)(int32_t x));
};

