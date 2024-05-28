#include <iostream>
#include "MultiSet.h"

int main()
{
    MultiSet set1(7, 3);
    MultiSet set2(5, 5);

    set1.addNumber(1);
    set1.addNumber(1);
    set1.addNumber(5);
    set1.addNumber(5);
    set1.addNumber(5);

    set2.addNumber(1);
    set2.addNumber(5);
    set2.addNumber(5);

    set1.printContained();
    set2.printContained();

    MultiSet intersection = set1 / set2;
    intersection.printContained();

    intersection.printMemoryContent();
}
