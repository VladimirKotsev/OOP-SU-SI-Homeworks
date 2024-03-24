#pragma once

namespace GlobalConstants
{
	unsigned const MAX_ROW_COUNT = 100;
	unsigned const MAX_FIELD_COUNT = 15;
	unsigned const MAX_FIELD_CHAR_COUNT = 50;
	unsigned const BUFFER_MAX_LENGTH = 2048;
	char const NEWLINE_CHARACTER = '\n';
	char const SPACE_CHARACTER = ' ';
	char const SPECIAL_CHARACTER = '*';
}

namespace ErrorMessages
{
	const char INVALID_TABLE_ROW[] = "Invalid table row";
	const char INVALID_TABLE_COL[] = "Invalid table col";
	const char INVALID_TABLE_VALUES[] = "Invalid values to add";
}
