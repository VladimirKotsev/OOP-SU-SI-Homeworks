#include <iostream>
#include "ModifiableIntegersFunction.h"

int16_t inectionFunc(int16_t x)
{
    return x * x;
}

int16_t surjectionFunc(int16_t x)
{
    return 2 * x;
}

int16_t bijectionFunc(int16_t x)
{
    return abs(2 * x);
}

int16_t func1(int16_t x)
{
    return x * x;
}
int16_t func2(int16_t x)
{
    return x + 2;
}
int16_t plusOne(int16_t x)
{
    return x + 1;
}

int main() //serialiazation and deserialization, print
{
    ModifiableIntegersFunction fd(plusOne);

    //fd.disablePoint();
    fd.printGraph(-10, 0);

    fd.saveToFile("savedFunction.txt");

    ModifiableIntegersFunction inverse = fd.inverse();

    inverse.printGraph(-10, 0);
}
