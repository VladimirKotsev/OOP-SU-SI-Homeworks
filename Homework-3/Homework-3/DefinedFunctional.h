#pragma once
#include "BaseFunctional.h"

class DefinedFunctional : public BaseFunctional
{
public:
	DefinedFunctional(int32_t* domain, int32_t* range, uint16_t n);

	// Inherited via BaseFunctional
	const Pair<bool, int32_t>& operator()(int32_t x) const override;
};

