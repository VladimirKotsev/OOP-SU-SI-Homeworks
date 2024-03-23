#include <fstream>
#include <sstream>

#include "GlobalConstants.h"
#include "Utility.h"
#include "Field.h"
#include "Row.h"
#include "Table.h"

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
	char* buffer = new char[GlobalConstants::BUFFER_MAX_LENGTH];

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

	delete[] buffer;
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
	//commands from console!!
	//editing at 3, 3 with empty space!!
	Table table;
	char* fileName;
	std::cin >> fileName;
	parseFromFile(fileName, table);

	std::cout << "'Exit' to exit" << std::endl;
	char* command;
	std::cin >> command;
	while (strcmp(command, "Exit") != 0)
	{
		if (strcmp(command, "print") == 0)
			table.print();
		else if (strcmp(command, "add") == 0)
		{

		}
		
	}


	table.print();
}
