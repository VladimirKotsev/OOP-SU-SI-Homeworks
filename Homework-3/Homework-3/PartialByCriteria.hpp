#pragma once
#include "PartialFunction.h"
//#include "BaseFunctional.h";
#include "UndefinedFunctional.h"
#include "DefinedFunctional.h"
#include "BooleanFunctional.h"

template<typename T>
class PartialFunctionByCriteria : public PartialFunction
{
private:
	T function;

public:
	PartialFunctionByCriteria(const T& func);

	int32_t operator()(int32_t x) const override;
	bool isDefined(int32_t x) const override;

	PartialFunction* clone() const override;
};

template<typename T>
PartialFunctionByCriteria<T>::PartialFunctionByCriteria(const T& func)
{
	this->function = func;
}

template<typename T>
int32_t PartialFunctionByCriteria<T>::operator()(int32_t x) const
{
	Pair<bool, int32_t> toReturn = function(x);

	if (!toReturn.getFirst())
		throw std::invalid_argument("Function is not defined at this point!");

	return toReturn.getSecond();
}

template<typename T>
bool PartialFunctionByCriteria<T>::isDefined(int32_t x) const
{
	return function(x).getFirst();
}

template<typename T>
PartialFunction* PartialFunctionByCriteria<T>::clone() const
{
	return new PartialFunctionByCriteria(*this);
}
