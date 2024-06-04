#include "Application.h"

int main()
{
	//To start - change the file name
	PartialFunction* func = PartialFunctionFactory::createFunction("func.dat");
	Application::run(func);
}
