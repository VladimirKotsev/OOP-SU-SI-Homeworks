#pragma once

#include "Utility.h"
#include "PartialFunctionFactory.h"

class Application
{
private:
	/*static int convertCharToDigit(char ch);

	static int32_t parseToNumber(const char* str);
	static bool areDigits(const char* str);*/

public:
	Application() = default;
	static void run(PartialFunction* func);
};

