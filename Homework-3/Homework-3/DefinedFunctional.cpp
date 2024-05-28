#include "DefinedFunctional.h"

DefinedFunctional::DefinedFunctional(int32_t* domain, int32_t* range, uint16_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		pairs.pushBack(std::move(Pair<int32_t, int32_t>(domain[i], range[i])));
	}

	delete[] domain;
	delete[] range;
}

const Pair<bool, int32_t>& DefinedFunctional::operator()(int32_t x) const
{
	size_t size = pairs.getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (pairs[i].getFirst() == x)
			return Pair<bool, int32_t>(1, pairs[i].getSecond());
	}

	return Pair<bool, int32_t>(false, 0);
}


