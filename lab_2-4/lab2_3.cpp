#include <iostream>
#include <limits>

#include "dynArray.h"

void          inputData(Array<float>& array);
float         average(const Array<float>& array);
float         minValue(const Array<float>& array);
float         maxValue(const Array<float>& array);
Array<float>  filterAboveAverage(const Array<float>& array);


int main()
{
    Array<float> data;
    
    std::cout << "=== Sensor analysis ===" << std::endl;

    inputData(data);

    std::cout << std::endl;

    float avg = average(data);
    float min = minValue(data);
    float max = maxValue(data);

    std::cout << "Average value: " << avg << std::endl;
    std::cout << "Minimum: " << min << std::endl;
    std::cout << "Maximum: " << max << std::endl;

    Array<float> above_avg = filterAboveAverage(data);

    std::cout << std::endl;

    std::cout << "Values above average:" << std::endl;
    std::cout << above_avg << std::endl;

    // Не нужно очищать память вручную, мой класс Array автоматически вызовет деструктор ~Array() и освободит ресурсы
}


void inputData(Array<float>& array)
{
    int size;
    std::cout << "Enter readings count: ";
    std::cin >> size;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    array.resize(size);

    std::cout << "Enter readings: ";
    std::cin >> array;
}

float average(const Array<float>& array)
{
    float average = 0.0f;

    for (size_t i = 0; i < array.getSize(); i++) {
        average += array[i];
    }

    return average / (float)array.getSize();
}

float minValue(const Array<float>& array)
{
    float min = FLT_MAX;

    for (size_t i = 0; i < array.getSize(); i++) {
        min = std::min(min, array[i]);
    }

    return min;
}

float maxValue(const Array<float>& array)
{
    float max = FLT_MIN;

    for (size_t i = 0; i < array.getSize(); i++) {
        max = std::max(max, array[i]);
    }

    return max;
}

Array<float> filterAboveAverage(const Array<float>& array)
{
    float avg = average(array);
    Array<float> above_avg;

    for (size_t i = 0; i < array.getSize(); i++) {
        if (array[i] > avg) {
            above_avg.pushBack(array[i]);
        }
    }
    return above_avg;
}
