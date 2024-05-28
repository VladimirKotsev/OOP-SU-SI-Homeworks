#include "PartialFunctionCollection.h"

void PartialFunctionCollection::resize(size_t newCap)
{
	PartialFunction** newData = new PartialFunction*[newCap];
	for (size_t i = 0; i < size; i++)
		newData[i] = functions[i];

	delete[] functions;
	functions = newData;
	capacity = newCap;
}

void PartialFunctionCollection::copyFrom(const PartialFunctionCollection& other)
{
	capacity = other.capacity;
	size = other.size;
	functions = new PartialFunction*[capacity];
	for (size_t i = 0; i < other.capacity; i++)
	{
		PartialFunction* cloned = other.functions[i]->clone();

		if (cloned)
			functions[i] = cloned;
	}
}

void PartialFunctionCollection::moveFrom(PartialFunctionCollection other)
{
	functions = other.functions;
	other.functions = nullptr;

	size = other.size;
	capacity = other.capacity;

	other.size = other.capacity = 0;
}

void PartialFunctionCollection::free()
{
	for (size_t i = 0; i < size; i++)
	{
		delete functions[i];
	}

	delete[] functions;
}

PartialFunctionCollection::PartialFunctionCollection()
{
	capacity = 4;
	size = 0;
	functions = new PartialFunction*[capacity];
}

PartialFunctionCollection::PartialFunctionCollection(const PartialFunctionCollection& other)
{
	copyFrom(other);
}

PartialFunctionCollection& PartialFunctionCollection::operator=(const PartialFunctionCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

PartialFunctionCollection::PartialFunctionCollection(PartialFunctionCollection&& other)
{
	moveFrom(other);
}

PartialFunctionCollection& PartialFunctionCollection::operator=(PartialFunctionCollection&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

PartialFunctionCollection::~PartialFunctionCollection()
{
	free();
}

void PartialFunctionCollection::addPartialFunctional(PartialFunction* other)
{
	if (!other)
		throw std::logic_error("Partial function null-pointer!");

	functions[size++] = other;
}

void PartialFunctionCollection::addPartialFunctional(const PartialFunction& other)
{
	PartialFunction* cloned = other.clone();
	addPartialFunctional(cloned);
}

size_t PartialFunctionCollection::getSize() const
{
	return size;
}

size_t PartialFunctionCollection::getCapacity() const
{
	return capacity;
}

const PartialFunction& PartialFunctionCollection::operator[](size_t index) const
{
	return *functions[index];
}

PartialFunction& PartialFunctionCollection::operator[](size_t index)
{
	return *functions[index];
}


