#pragma once
#include "GlobalConstants.h"

class Field
{
private:
	char field[GlobalConstants::MAX_FIELD_CHAR_COUNT + 1] = "\0";
	bool isHeader = false;
public:
	Field() = default;
	Field(char* field, bool isHeader);
	Field(char* field);

	size_t getFieldLength();

	void setField(char* field);
	const char* getField() const;

	bool getIsHeader() const;
	void setIsHeader(bool isHeader);
};
