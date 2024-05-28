#pragma once
#include "PartialFunction.h"
#include "Extremes.h"

class MinimumPartial : public Extremes
{
public:
	MinimumPartial(PartialFunction** funcs, uint16_t n);

	int32_t operator()(int32_t x) const override;


	// Inherited via Extremes
	PartialFunction* clone() const override;

};

