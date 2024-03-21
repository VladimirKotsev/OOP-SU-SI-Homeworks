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

	void unformatFile(std::ifstream& inFile, std::stringstream& ss)
	{
		if (!inFile.is_open())
			return;

		char buffer;
		bool isField = false;
		while (inFile.get(buffer))
		{
			if (buffer == '>')
				isField = true;
			else if (buffer == '<')
				isField = false;

			if ((buffer != GlobalConstants::NEWLINE_CHARACTER && buffer != GlobalConstants::SPACE_CHARACTER) && isField)
				ss << (char)buffer;
		}
	}

	void appendToBuffer(char*& buffer)
	{
		if (!buffer)
			return;

		size_t size = strlen(buffer);

		for (size_t i = size; i > 0; --i)
			buffer[i] = buffer[i - 1];

		buffer[0] = GlobalConstants::SPECIAL_CHARACTER;
		buffer[size + 1] = '\0';
	}

	bool isDigit(char c)
	{
		return c >= '0' && c <= '9';
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
};

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
	Table() = default;
	void print();
};

Table parseFormatedFromFile(std::stringstream& ss, std::istream& ifs)
{
	Table table;
	char buffer[GlobalConstants::BUFFER_MAX_LENGTH];
	ifs.getline(buffer, GlobalConstants::BUFFER_MAX_LENGTH, '<');
	bool isHeader = false;
	size_t currRow = -1;
	size_t currCol = -1;

	while (!ifs.eof())
	{
		ifs.getline(buffer, GlobalConstants::BUFFER_MAX_LENGTH, '>'); //gets the html tag
		if (strcmp(buffer, "tr") == 0)
		{
			currRow++;
		}
		else if (strcmp(buffer, "/tr") == 0)
		{
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

		ifs.getline(buffer, GlobalConstants::BUFFER_MAX_LENGTH, '<'); //gets the text between 2 tags
		
		if (UtilityFunctions::containsNewline(buffer))
			continue;
		Field field(buffer, isHeader);
		Row& row = table.rows[currRow];
		row[currCol] = field;
	}
	
	return table;
}

Table parseFromFile(std::istream& ifs)
{
	Table result;
	char buffer[GlobalConstants::BUFFER_MAX_LENGTH];
	std::stringstream ss;

	ifs.getline(buffer, GlobalConstants::BUFFER_MAX_LENGTH, '\n');
	std::cout << strlen(buffer);
	if (strlen(buffer) == 7 && strcmp(buffer, "<table>") == 0) //formated html table
	{
		result = parseFormatedFromFile(ss, ifs);
	}
	else if (strlen(buffer) > 8) //unformated html table
	{
		
	}

	return result;
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

void Table::print() //To implement
{
	for (size_t i = 0; i < GlobalConstants::MAX_ROW_COUNT; i++)
	{
		std::cout << '|';

		for (size_t j = 0; j < GlobalConstants::MAX_FIELD_COUNT; j++)
		{
			std::cout << this->rows[i][j].getField();
		}

		std::cout << '|' << std::endl;
	}
}

int main()
{
	Table table = parseFromFile("html-table.txt");
	table.print();
}
