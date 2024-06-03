#include "MinimumPartial.h"

MinimumPartial::MinimumPartial(PartialFunction** funcs, uint16_t n) : Extremes(funcs, n) { }

int32_t MinimumPartial::operator()(int32_t x) const
{
	if (!isDefined(x))
		throw std::logic_error("Functions not defined at given x!");

	int32_t minRangeValue = container[0].operator()(x);

	for (size_t i = 1; i < container.getSize(); i++)
	{
		if (container[i].operator()(x) < minRangeValue)
			minRangeValue = container[i].operator()(x);
	}

	return minRangeValue;
}

PartialFunction* MinimumPartial::clone() const
{
	PartialFunction* cloned = new (std::nothrow) MinimumPartial(*this);
	return cloned;
}
