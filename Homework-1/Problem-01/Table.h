#pragma once
#include <iostream>
#include <iomanip>

#include "GlobalConstants.h"
#include "Row.h"

struct Table
{
private:
	void findMaxCharactersForColumn();
public:
	Row rows[GlobalConstants::MAX_ROW_COUNT];
	size_t rowsCount = 0;
	size_t colsCount = 0;
	unsigned maxLengths[GlobalConstants::MAX_FIELD_COUNT]{ 0 };
	Table() = default;

	void remove(int rowIndex);
	void add(int rowIndex, char** values, size_t size);
	void edit(int rowIndex, int colIndex, char* newValue);
	void print();
};