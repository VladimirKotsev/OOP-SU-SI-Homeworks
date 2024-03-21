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
}

class Field
{
private:
	char field[GlobalConstants::MAX_FIELD_CHAR_COUNT + 1] = "\0";
	bool isHeader = false;
public:
	Field() = default;
	Field(char* field, bool isHeader)
	{
		setField(field);
		this->isHeader = isHeader;
	}
	Field(char* field) : Field(field, false) {}

	size_t getFieldLength()
	{
		return strlen(this->getField());
	}

	void setField(char* field)
	{
		size_t size = strlen(field);
		if (size > GlobalConstants::MAX_FIELD_CHAR_COUNT + 1)
		{
			strcpy(this->field, "\0");
			return;
		}

		strcpy(this->field, field);
	}
	const char* getField() const
	{
		return this->field;
	}
	bool getIsHeader() const
	{
		return this->isHeader;
	}
	void setIsHeader(bool isHeader)
	{
		this->isHeader = isHeader;
	}
};

struct Row
{
	Field fields[GlobalConstants::MAX_FIELD_COUNT];
};

struct Table
{
private:		
	void findMaxCharactersForColumn() //calculates the max length for each column
	{
		for (size_t i = 0; i < GlobalConstants::MAX_ROW_COUNT; i++)
		{
			for (size_t j = 0; j < GlobalConstants::MAX_FIELD_COUNT; j++)
			{
				if (this->rows[i].fields[j].getFieldLength() > this->maxLengths[j])
					maxLengths[j] = this->rows[i].fields[j].getFieldLength();
			}
		}
	}
public:
	Row rows[GlobalConstants::MAX_ROW_COUNT];
	size_t rowsCount = 0;
	size_t colsCount = 0;
	unsigned maxLengths[GlobalConstants::MAX_FIELD_COUNT]{ 0 };
	Table() = default;

	void remove(int rowIndex)
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
	void add(int rowIndex, char** values, size_t size)
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
	void edit(int rowIndex, int colIndex, char* newValue)
	{
		this->rows[rowIndex].fields[colIndex].setField(newValue);
	}
	void print()
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

void parseToFile(std::ostream& ofs, const Table& table)
{
	ofs << "<table>\n";
	for (size_t i = 0; i < table.rowsCount; i++)
	{
		ofs << "  <tr>\n";
		for (size_t j = 0; j < table.colsCount; j++)
		{
			const char* field = table.rows[i].fields[j].getField();

			//checks if it is header and if empty don't print
			if (table.rows[i].fields[j].getIsHeader() && strcmp(field, "") != 0) 
				ofs << "    <th>" << field << "</th>\n";
			else if (!table.rows[i].fields[j].getIsHeader() && strcmp(field, "") != 0)
				ofs << "    <td>" << field << "</td>\n";
		}
		ofs << "  </tr>\n";
	}
	ofs << "<table>\n";
}
void parseToFile(const char* fileName, const Table& table)
{
	std::ofstream ofs(fileName);
	if (!ofs.is_open())
	{
		std::cout << "File to write is not open";
		return;
	}

	parseToFile(ofs, table);
	ofs.close();
}

void parseFromFile(std::ifstream& ifs, Table& table)
{
	char buffer[GlobalConstants::BUFFER_MAX_LENGTH];

	bool isHeader = false;
	int currRow = -1;
	int currCol = -1;
	std::stringstream ss;

	convertToUnformated(ss, ifs);
	ss.get();
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
			if (currCol + 1 > table.colsCount)
				table.colsCount = currCol + 1;

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
		table.rows[currRow].fields[currCol].setIsHeader(isHeader);
		table.rows[currRow].fields[currCol].setField(buffer);
	}

	ifs.close();
}
Table parseFromFile(const char* fileName, Table& table)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
		return table;

	parseFromFile(ifs, table);
	return table;
}

int main()
{
	Table table;
	parseFromFile("html-table-unformated.txt", table);

	table.print();
}
