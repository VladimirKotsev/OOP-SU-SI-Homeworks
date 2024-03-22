#include <iostream>
#include <iomanip>

#include "GlobalConstants.h"
#include "Row.h"
#include "Table.h"

void Table::findMaxCharactersForColumn() //calculates the max length for each column
{
	for (size_t i = 0; i < GlobalConstants::MAX_ROW_COUNT; i++)
	{
		for (size_t j = 0; j < GlobalConstants::MAX_FIELD_COUNT; j++)
		{
			//gets the column max length and places in array
			if (this->rows[i].fields[j].getFieldLength() > this->maxLengths[j])
				this->maxLengths[j] = this->rows[i].fields[j].getFieldLength();
		}
	}
}

void Table::remove(int rowIndex)
{
	if (rowIndex < 0 || rowIndex >= this->rowsCount)
	{
		std::cout << "Invalid index" << std::endl;
		return;
	}

	this->rowsCount--;
	for (int i = rowIndex; i < this->rowsCount; ++i) //shift rows backward by 1
		this->rows[i] = this->rows[i + 1];
}
void Table::add(int rowIndex, char** values, size_t size)
{
	if (!values)
	{
		std::cout << "Invalid values to add" << std::endl;
		return;
	}
	if (rowIndex < 0 || rowIndex >= this->rowsCount + 1)
	{
		std::cout << "Invalid index" << std::endl;
		return;
	}

	this->rowsCount++;
	for (int i = this->rowsCount; i >= rowIndex; i--) //shift rows forward by 1
		this->rows[i] = this->rows[i - 1];

	Row row;
	for (size_t i = 0; i < size; i++)
		row.fields[i].setField(values[i]);

	this->rows[rowIndex] = row;
}
void Table::edit(int rowIndex, int colIndex, char* newValue)
{
	this->rows[rowIndex].fields[colIndex].setField(newValue);
}
void Table::print()
{
	this->findMaxCharactersForColumn();
	for (size_t i = 0; i < this->rowsCount; i++)
	{
		std::cout << '|';

		for (size_t j = 0; j < this->colsCount; j++)
		{
			if (this->rows[i].fields[j].getIsHeader())
				std::cout << '*';
			else
				std::cout << ' ';

			//calculates the offset for table
			int offset = this->maxLengths[j] - strlen(this->rows[i].fields[j].getField());

			std::cout << this->rows[i].fields[j].getField();
			std::cout << std::setw(offset + 1);

			if (this->rows[i].fields[j].getIsHeader())
				std::cout << '*';
			else
				std::cout << ' ';

			if (j != this->colsCount - 1)
				std::cout << '|';
		}

		std::cout << '|' << std::endl;
	}
}