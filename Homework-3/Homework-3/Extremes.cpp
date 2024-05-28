#include "Extremes.h"

void Extremes::fillContainer(PartialFunction** funcs, int16_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		container.addPartialFunctional(funcs[i]);
	}
}

Extremes::Extremes(PartialFunction** funcs, uint16_t n)
{
	fillContainer(funcs, n);
}

bool Extremes::isDefined(int32_t x) const
{
	for (size_t i = 0; i < container.getSize(); i++)
	{
		if (!container[i].isDefined(x))
			return false;
	}

	return true;
}
