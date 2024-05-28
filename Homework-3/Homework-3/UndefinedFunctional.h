#pragma once
#include "BaseFunctional.h"

class UndefinedFunctional : public BaseFunctional
{
public:
	UndefinedFunctional(int32_t* domain, uint16_t n);

	// Inherited via BaseFunctional
	const Pair<bool, int32_t>& operator()(int32_t x) const override;
};

