#pragma once
#include "BaseFunctional.h"

class UndefinedFunctional : public BaseFunctional
{
public:
	UndefinedFunctional() = default;
	UndefinedFunctional(int32_t* domain, uint16_t n);

	const Pair<bool, int32_t>& operator()(int32_t x) const override;
};

