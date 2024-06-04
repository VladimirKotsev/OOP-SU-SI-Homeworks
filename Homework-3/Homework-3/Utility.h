#pragma once

#include <fstream> //!!!!!!!!!!!
//#include <sstream> //!!!!!!!!!!!
#include <iostream>

class Utility
{
public:
	static size_t getFileSize(std::istream& is);

	static size_t symbolsToSentinel(const char* buffer);

	static bool areDigits(const char* str);

	static int convertCharToDigit(char ch);

	static int32_t parseToNumber(const char* str);

};

