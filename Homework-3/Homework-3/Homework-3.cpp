#include <iostream>
#include "PartialFunctionFactory.h"
//#include "BooleanFunctional.h"
#include "PartialByCriteria.hpp"

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
				std::cout << e.what();
			}
		}
		break;
	case 2:
		int32_t x;
		std::cout << "Enter values for which you want to get the value of the function:" << std::endl;
		while (true)
		{
			std::cin >> x;
			try
			{
				std::cout << "f(" << x << ") = " << (*f)(x) << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		break;
	}
