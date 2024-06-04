#pragma once
#include "PartialFunction.h"

class PartialFunctionCollection
{
private:
	PartialFunction** functions;
	size_t capacity;
	size_t size;

	void resize(size_t newCap);
	void copyFrom(const PartialFunctionCollection& other);
	void moveFrom(PartialFunctionCollection other);
	void free();

public:
	PartialFunctionCollection();

	PartialFunctionCollection(const PartialFunctionCollection& other);
	PartialFunctionCollection& operator=(const PartialFunctionCollection& other);

	PartialFunctionCollection(PartialFunctionCollection&& other);
	PartialFunctionCollection& operator=(PartialFunctionCollection&& other);

	~PartialFunctionCollection();

	void addPartialFunctional(PartialFunction* other);
	void addPartialFunctional(const PartialFunction& other);
	//void addPartialFunctional(PartialFunction&& other);

	size_t getSize() const;
	size_t getCapacity() const;

	const PartialFunction& operator[](size_t index) const;
	PartialFunction& operator[](size_t index);
};

