#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#pragma warning( disable : 4996)

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

namespace UtilityFunctions
{
	bool containsNewline(char* buffer)
	{
		while (*buffer)
		{
			if (*buffer++ == '\n')
				return true;
		}

		return false;
	}

	void decodeEntity(char* str)
	{
		char* ptr = str;
		while (*ptr != '\0')
		{
			if (*ptr == '&' && *(ptr + 1) == '#' && *(ptr + 2) >= '0' && *(ptr + 2) <= '9')
			{
				int code = 0;
				ptr += 2; // Move past "&#" characters
				while (*ptr >= '0' && *ptr <= '9')
				{
					code = code * 10 + (*ptr - '0');
					ptr++;
				}

				*str++ = (char)code;
			}
			else
			{
				*str++ = *ptr++;
			}
		}

		*str = '\0'; // Null-terminate the modified string
	}

	void removeWhitespaces(char* str)
	{
		char* ptr = str;
		char* startPtr = nullptr;
		while (*str)
		{
			if (*str != ' ' || startPtr)
			{
				if (!startPtr)
				{
					startPtr = ptr;
				}
				*ptr++ = *str;
			}
			str++;
		}
		if (startPtr)
		{
			*ptr = '\0'; // Null-terminate the string if there were leading spaces
		}
	}



	/*unsigned getNumberFromString(char* buffer)
	{

	}

	char decodeCharacters(char* buffer)
	{
		if(!buffer)
			return;

		bool flag = false;
		unsigned index = 0;
		while (*buffer)
		{
			if (*buffer == '&')
			{
				flag = true;
			}
			if (*buffer == '#' && flag)
			{
				index++;

			}

			index++;
			*buffer++;
		}
	}*/
}

//typedef char Field[GlobalConstants::MAX_FIELD_CHAR_COUNT];
class Field
{
private:
	char field[GlobalConstants::MAX_FIELD_CHAR_COUNT + 1] = "\0";
	bool isHeader = false;
public:
	Field() = default;
	Field(char* field, bool isHeader);
	Field(char* field);

	void setField(char* field);
	char* getField();
	bool getIsHeader();
	size_t length();
};

size_t Field::length()
{
	return strlen(this->getField());
}
Field::Field(char* field, bool isHeader)
{
	setField(field);
	this->isHeader = isHeader;
}
Field::Field(char* field) : Field(field, false) {}

void Field::setField(char* field)
{
	size_t size = strlen(field);
	if (size > GlobalConstants::MAX_FIELD_CHAR_COUNT + 1)
	{
		strcpy(this->field, "\0");
		return;
	}

	strcpy(this->field, field);
}
char* Field::getField()
{
	return this->field;
}
bool Field::getIsHeader()
{
	return this->isHeader;
}

typedef Field Row[GlobalConstants::MAX_FIELD_COUNT];
class Table
{
public:
	Row rows[GlobalConstants::MAX_ROW_COUNT];
	size_t rowsCount = 0;
	size_t colsCount = 0;
	unsigned maxLengths[GlobalConstants::MAX_FIELD_COUNT]{ 0 };
	void print();
	void findMaxCharactersForColumn();
	void remove(int rowIndex);
	void add(int rowIndex, char** values);
	void edit(int rowIndex, int colIndex, char* newValue);
	void swapRows(Row& row1, Row& row2);
	Table() = default;
};

void convertToUnformated(std::stringstream& ss, std::istream& ifs)
{
	char buffer[GlobalConstants::BUFFER_MAX_LENGTH];

	while (!ifs.eof())
	{
		ifs.getline(buffer, GlobalConstants::BUFFER_MAX_LENGTH);
		UtilityFunctions::removeWhitespaces(buffer);
		ss.write(buffer, strlen(buffer));
	}
}

Table parseFromFile(std::istream& ifs)
{
	Table table;
	char buffer[GlobalConstants::BUFFER_MAX_LENGTH];

	ifs.getline(buffer, GlobalConstants::BUFFER_MAX_LENGTH, '\n');
	bool isHeader = false;
	size_t currRow = -1;
	size_t currCol = -1;
	std::stringstream ss;

	convertToUnformated(ss, ifs);
	ss.ignore();
	while (!ss.eof())
	{
		ss.getline(buffer, GlobalConstants::BUFFER_MAX_LENGTH, '>'); //gets the html tag
		if (strcmp(buffer, "tr") == 0)
		{
			currRow++;
			table.rowsCount++;
		}
		else if (strcmp(buffer, "/tr") == 0)
		{
			if (currCol > table.colsCount)
				table.colsCount = currCol;

			currCol = -1;
		}
		else if (strcmp(buffer, "th") == 0)
		{
			currCol++;
			isHeader = true;
		}
		else if (strcmp(buffer, "td") == 0)
		{
			currCol++;
			isHeader = false;
		}

		ss.getline(buffer, GlobalConstants::BUFFER_MAX_LENGTH, '<'); //gets the text between 2 tags

		if (strlen(buffer) == 0)
			continue;

		UtilityFunctions::decodeEntity(buffer);
		Field field(buffer, isHeader);
		Row& row = table.rows[currRow];
		row[currCol] = field;
	}

	return table;
}

Table parseFromFile(const char* fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		return {};
	}

	return parseFromFile(ifs);
}

void Table::findMaxCharactersForColumn()
{
	for (size_t i = 0; i < GlobalConstants::MAX_ROW_COUNT; i++)
	{
		for (size_t j = 0; j < GlobalConstants::MAX_FIELD_COUNT; j++)
		{
			if (this->rows[i][j].length() > this->maxLengths[j])
				maxLengths[j] = this->rows[i][j].length();
		}
	}
}

void Table::swapRows(Row& row1, Row& row2)
{
	row1 = row2;
}

void Table::remove(int rowIndex)
{
	if (rowIndex < 0 || rowIndex >= this->rowsCount)
	{
		std::cout << "Invalid index\n";
		return;
	}

	this->rowsCount--;
	for (int i = rowIndex; i < this->rowsCount; ++i)
	{
		this->swapRows(this->rows[i], this->rows[i + 1]);
	}
}

void Table::add(int rowIndex, char** values)
{

}

void Table::edit(int rowIdnex, int colIndex, char* newValue)

void Table::print() //To implement
{
	this->findMaxCharactersForColumn();
	for (size_t i = 0; i < this->rowsCount; i++)
	{
		std::cout << '|';

		for (size_t j = 0; j < this->colsCount; j++)
		{
			if (this->rows[i][j].getIsHeader())
				std::cout << '*';
			else
				std::cout << ' ';

			int offset = this->maxLengths[j] - strlen(this->rows[i][j].getField());

			std::cout << this->rows[i][j].getField();
			std::cout << std::setw(offset + 1);

			if (this->rows[i][j].getIsHeader())
				std::cout << '*';
			else
				std::cout << ' ';

			if (j != this->colsCount - 1)
				std::cout << '|';
		}

		std::cout << '|' << std::endl;
	}
}

int main()
{
	Table table = parseFromFile("html-table.txt");
	table.print();
	std::cout << std::endl;
	Table table1 = parseFromFile("html-table-unformated.txt");
	table.print();
}
