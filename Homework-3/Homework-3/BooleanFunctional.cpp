#include "BooleanFunctional.h"

const Pair<bool, int32_t>& BooleanFunctional::operator()(int32_t x) const
{
	size_t size = pairs.getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (pairs[i].getFirst() == x)
			return Pair<bool, int32_t>(true, 1);
	}

	return Pair<bool, int32_t>(true, 0);
}

BooleanFunctional::BooleanFunctional(int32_t* domain, uint16_t n)
{
	//create vector with size n, and fill numbers
	for (size_t i = 0; i < n; i++)
	{
		pairs.pushBack(std::move(Pair<int32_t, int32_t>(domain[i], 1)));
	}

	delete[] domain;
}

