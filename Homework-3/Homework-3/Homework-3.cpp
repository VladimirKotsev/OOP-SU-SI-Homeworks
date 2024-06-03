#include <iostream>
#include "PartialFunctionFactory.h"
#include "BooleanFunctional.h"
#include "FunctionalByCriteria.hpp"

bool areDigits(const char* str)
{
	if (!str)
		return false;

	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return false;

		str++;
	}

	return true;
}

int convertCharToDigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return ch - '0';
	return -1;
}

int32_t parseToNumber(const char* str)
{
	//no need for nullptr check!
	int32_t result = 0;
	while (*str)
	{
		int digit = convertCharToDigit(*str);
		if (digit == -1)
			return 0;
		(result *= 10) += digit;
		str++;
	}
	return result;
}

int main()
{
	PartialFunction* f = PartialFunctionFactory::createFunction("func.dat");

	int mode = 0;
	std::cout << "Choose mode on working (1 or 2): ";

	while (mode != 1 && mode != 2)
		std::cin >> mode;

	switch (mode)
	{
	case 1:
		int32_t a, b;
		std::cout << "Lower bound for printing function: ";
		std::cin >> a;
		std::cout << "Upper bound for printing function: ";
		std::cin >> b;
		if (a > b)
			std::swap(a, b);

		for (int32_t i = a; i <= b; i++)
		{
			try
			{
				std::cout << "f(" << i << ") = " << (*f)(i) << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		break;
	case 2:
		int32_t x;
		char buffer[1024];
		std::cout << "Enter \"exit\" to stop entering values" << std::endl;
		std::cout << "Enter values for which you want to get the value of the function:" << std::endl;
		while (true)
		{
			std::cin >> buffer;
			if (areDigits(buffer))
			{
				x = parseToNumber(buffer);
				try
				{
					std::cout << "f(" << x << ") = " << (*f)(x) << std::endl;
				}
				catch (const std::exception& e)
				{
					std::cout << e.what() << std::endl;
				}
			}
			else
			{
				if (strcmp(buffer, "exit") == 0)
					break;
			}
		}
		break;
	}
}
