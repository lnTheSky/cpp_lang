#include <iostream>

#include "dynArray.h"


int main() {
    Array<int> array;

    array.pushBack(4);
    array.pushBack(2);
    array.pushBack(1);
    array.pushBack(72);

    std::cout << array << std::endl;

} 