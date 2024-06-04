#pragma once
#include "Vector.hpp"

class BaseIntegerFunctional
{
private:

protected:
	Vector<int32_t> values;

public:
	virtual const Pair<bool, int32_t>& operator()(int32_t x) const = 0;

	virtual ~BaseIntegerFunctional() = default;
};

