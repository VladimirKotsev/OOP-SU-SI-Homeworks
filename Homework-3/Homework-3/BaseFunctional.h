#pragma once
#include <fstream>

#include "Vector.hpp"
#include "Pair.hpp"

class BaseFunctional
{
private:

protected:
	Vector<Pair<int32_t, int32_t>> pairs;

public:

	virtual const Pair<bool, int32_t>& operator()(int32_t x) const = 0;

	virtual ~BaseFunctional() = default;
};

