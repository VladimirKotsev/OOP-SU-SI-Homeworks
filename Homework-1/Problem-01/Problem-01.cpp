#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#pragma warning( disable : 4996)

namespace GlobalConstants
{
	unsigned const MAX_ROW_COUNT = 300;
	unsigned const MAX_COLUMN_COUNT = 30;
	unsigned const MAX_COLUMN_CHAR_COUNT = 50;
	unsigned const BUFFER_MAX_LENGTH = 1024;
	char const NEWLINE_CHARACTER = '\n';
	char const SPACE_CHARACTER = ' ';
	char const SPECIAL_CHARACTER = '*';
}

namespace UtilityFunctions
{
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

char*** readToMatrix(std::ifstream& inFile)
{
	if (!inFile.is_open())
		return nullptr;

	char*** matrix = new char** [GlobalConstants::MAX_ROW_COUNT];
	char* buffer = new char[GlobalConstants::BUFFER_MAX_LENGTH];

	std::stringstream ss;
	UtilityFunctions::unformatFile(inFile, ss);

	unsigned row = 0;
	unsigned col = 0;
	bool readingRow = false;

	while (!ss.eof())
	{
		ss.get();
		ss.getline(buffer, GlobalConstants::BUFFER_MAX_LENGTH, '>');
		if (strcmp(buffer, "tr") == 0)
		{
			if (readingRow)
			{
				row++;
				readingRow = false;
			}
			else
			{
				readingRow = true;
			}

			matrix[row] = new char* [GlobalConstants::MAX_COLUMN_COUNT];
			for (size_t i = 0; i < GlobalConstants::MAX_COLUMN_COUNT; i++)
			{
				matrix[row][i] = new char[GlobalConstants::MAX_COLUMN_CHAR_COUNT];
			}
		}
		else if (strcmp(buffer, "tr") == 0 && readingRow)
		{
			row++;
			readingRow = false;

		}
		else if (strcmp(buffer, "th") == 0)
		{
			ss.getline(buffer, GlobalConstants::BUFFER_MAX_LENGTH, '<');
			UtilityFunctions::appendToBuffer(buffer);
			//from character entity reference

			strcpy(matrix[row][col++], buffer);
			ss.getline(buffer, GlobalConstants::BUFFER_MAX_LENGTH, '>');
		}
		else if (strcmp(buffer, "td") == 0)
		{
			ss.getline(buffer, GlobalConstants::BUFFER_MAX_LENGTH, '<');

			//from character entity reference

			strcpy(matrix[row][col++], buffer);
			ss.getline(buffer, GlobalConstants::BUFFER_MAX_LENGTH, '>');
		}
	}

	std::cout << ss.str();

	delete[] buffer;
	return matrix;
}

void print(std::ifstream& inFile)
{
	char*** matrix = readToMatrix(inFile);

	for (size_t i = 0; i < GlobalConstants::MAX_ROW_COUNT; i++)
	{
		std::cout << '|';
		for (size_t j = 0; j < GlobalConstants::MAX_COLUMN_COUNT; j++)
		{
			if (matrix[i][j][0] == '*')
			{
				if (j + 1 == GlobalConstants::MAX_COLUMN_COUNT)
					std::cout << std::setw(5) << matrix[i][j] << std::setw(5) << '*';
				else
					std::cout << std::setw(5) << matrix[i][j] << std::setw(5) << "*|";
			}
			else
			{
				if (j + 1 == GlobalConstants::MAX_COLUMN_COUNT)
					std::cout << std::setw(5) << matrix[i][j] << std::setw(5);
				else
					std::cout << std::setw(5) << matrix[i][j] << std::setw(5) << '|';
			}
		}
		std::cout << '|' << std::endl;
	}
}

int main()
{
	//should read file path from console!!!!!!!!!!!!!!!!
	//to validate if there is a table tag!!!
	std::ifstream inFile("html-table.txt");
	//std::ifstream inFile2("html-table-unformated.txt");
	if (inFile.is_open())
	{
		//std::cout << "Formated table" << std::endl;
		print(inFile);
		//std::cout << std::endl << "Unformated table" << std::endl;
		//print(inFile2);
	}
}
