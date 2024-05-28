#include "UndefinedFunctional.h"

UndefinedFunctional::UndefinedFunctional(int32_t* domain, uint16_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		pairs.pushBack(std::move(Pair<int32_t, int32_t>(domain[i], 0)));
	}

	delete[] domain;
}

const Pair<bool, int32_t>& UndefinedFunctional::operator()(int32_t x) const
{
	size_t size = pairs.getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (pairs[i].getFirst() == x)
			return Pair<bool, int32_t>(false, 0);
	}

	return Pair<bool, int32_t>(true, x);

}
