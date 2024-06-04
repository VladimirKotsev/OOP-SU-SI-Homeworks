#pragma once
#include "Vector.hpp"
#include "Pair.hpp"

class BasePairFunctional
{
private:

protected:
	Vector<Pair<int32_t, int32_t>> values;

public:

	virtual const Pair<bool, int32_t>& operator()(int32_t x) const = 0;

	virtual ~BasePairFunctional() = default;
};

