#include "BooleanFunctional.h"

BooleanFunctional::BooleanFunctional(int32_t* domain, uint16_t n)
{
	//create vector with size n, and fill numbers
	for (size_t i = 0; i < n; i++)
	{
		values.pushBack(domain[i]);
	}

	delete[] domain;
}

const Pair<bool, int32_t>& BooleanFunctional::operator()(int32_t x) const
{
	size_t size = values.getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (values[i] == x)
			return Pair<bool, int32_t>(true, 1);
	}

	return Pair<bool, int32_t>(true, 0);
}

