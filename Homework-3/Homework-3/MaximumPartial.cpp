#include "MaximumPartial.h"

MaximumPartial::MaximumPartial(PartialFunction** funcs, int16_t n) : Extremes(funcs, n) { }

int32_t MaximumPartial::operator()(int32_t x) const
{
	if (!isDefined(x))
		std::logic_error("Functions not defined at given x!");

	int32_t maxRangeValue = container[0].operator()(x);

	for (size_t i = 1; i < container.getSize(); i++)
	{
		if (container[i].operator()(x) > maxRangeValue)
			maxRangeValue = container[i].operator()(x);

	}

	return maxRangeValue;
}

PartialFunction* MaximumPartial::clone() const
{
	PartialFunction* cloned = new (std::nothrow) MaximumPartial(*this);
	return cloned;
}
