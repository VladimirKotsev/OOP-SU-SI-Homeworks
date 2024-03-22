#include <iostream>
#include "Field.h"
#include "GlobalConstants.h"

Field::Field(char* field, bool isHeader)
{
	setField(field);
	this->isHeader = isHeader;
}
Field::Field(char* field) : Field::Field(field, false) {}

size_t Field::getFieldLength()
{
	return strlen(this->getField());
}

const char* Field::getField() const
{
	return this->field;
}
void Field::setField(char* field)
{
	size_t size = strlen(field);
	if (size > GlobalConstants::MAX_FIELD_CHAR_COUNT + 1)
	{
		strcpy_s(this->field, "\0");
		return;
	}

	strcpy_s(this->field, field);
}

bool Field::getIsHeader() const
{
	return this->isHeader;
}
void Field::setIsHeader(bool isHeader)
{
	this->isHeader = isHeader;
}