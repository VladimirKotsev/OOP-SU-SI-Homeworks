#include "UndefinedFunctional.h"

UndefinedFunctional::UndefinedFunctional(int32_t* domain, uint16_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		values.pushBack(domain[i]);
	}

	delete[] domain;
}

const Pair<bool, int32_t>& UndefinedFunctional::operator()(int32_t x) const
{
	size_t size = values.getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (values[i] == x)
			return Pair<bool, int32_t>(false, 0);
	}

	return Pair<bool, int32_t>(true, x);
}
