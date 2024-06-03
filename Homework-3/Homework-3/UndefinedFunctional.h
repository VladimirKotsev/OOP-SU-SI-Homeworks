#pragma once
#include "Pair.hpp"
#include "BaseIntegerFunctional.h"

class UndefinedFunctional : public BaseIntegerFunctional
{
public:
	UndefinedFunctional() = default;
	UndefinedFunctional(int32_t* domain, uint16_t n);

	// Inherited via BaseIntegerFunctional
	const Pair<bool, int32_t>& operator()(int32_t x) const override;
};

