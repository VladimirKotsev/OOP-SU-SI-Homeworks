#pragma once
#include "PartialFunctionCollection.h"

class Extremes : public PartialFunction
{
private:
	void fillContainer(PartialFunction** funcs, int16_t n);
protected:
	PartialFunctionCollection container;

public:
	Extremes(PartialFunction** funcs, uint16_t n);

	virtual PartialFunction* clone() const = 0;

	virtual int32_t operator()(int32_t x) const = 0;

	bool isDefined(int32_t x) const override final;
};

