#pragma once
#include "PartialFunction.h"
#include "Pair.hpp"

template<typename T>
class FunctionalByCriteria : public PartialFunction
{
private:
	T function;

public:
	FunctionalByCriteria(const T& func);

	int32_t operator()(int32_t x) const override;
	bool isDefined(int32_t x) const override;

	PartialFunction* clone() const override;
};

template<typename T>
FunctionalByCriteria<T>::FunctionalByCriteria(const T& func)
{
	this->function = func;
}

template<typename T>
int32_t FunctionalByCriteria<T>::operator()(int32_t x) const
{
	Pair<bool, int32_t> toReturn = function(x);

	if (!toReturn.getFirst())
		throw std::invalid_argument("Function is not defined at this point!");

	return toReturn.getSecond();
}

template<typename T>
bool FunctionalByCriteria<T>::isDefined(int32_t x) const
{
	return function(x).getFirst();
}

template<typename T>
PartialFunction* FunctionalByCriteria<T>::clone() const
{
	return new FunctionalByCriteria(*this);
}
