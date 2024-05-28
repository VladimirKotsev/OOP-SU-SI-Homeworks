#pragma once
#include "Extremes.h"

class MaximumPartial : public Extremes
{
public:
	MaximumPartial(PartialFunction** funcs, int16_t n);

	int32_t operator()(int32_t x) const override;


	// Inherited via Extremes
	PartialFunction* clone() const override;

};

