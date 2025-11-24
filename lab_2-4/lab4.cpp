#include <iostream>

#include "dynArray.h"

void          inputData(Array<Array<float>>& array);
float         dayAverage(const Array<float>& array);
float         overallAverage(const Array<Array<float>>& array);
void          showHotDays(const Array<Array<float>>& array);


int main()
{
    Array<Array<float>> data;

    inputData(data);

    std::cout << std::endl;

    float total_avg = overallAverage(data);

    std::cout << "Overall average temperature: " << total_avg << std::endl;

    showHotDays(data);
}


void inputData(Array<Array<float>>& array)
{
    int days;
    std::cout << "Enter days count: ";
    std::cin >> days;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    array.resize(days);

    int readings;
    std::cout << "Enter readings per day count: ";
    std::cin >> readings;

    for (int i = 0; i < days; i++) {
        Array<float> day;

        
        std::cout << "Day " << i + 1 << ": ";
        std::cin >> day;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        array.pushBack(day);
    }
}

float dayAverage(const Array<float>& array)
{
    float average = 0.0f;

    for (size_t i = 0; i < array.getSize(); i++) {
        average += array[i];
    }

    return average / (float)array.getSize();
}

float overallAverage(const Array<Array<float>>& array)
{
    float average = 0.0f;
    int readings = 0;
    for (size_t i = 0; i < array.getSize(); i++) {

        for (size_t j = 0; j < array[i].getSize(); j++) {
            average += array[i][j];
            readings++;
        }
    }

    if (!readings) {
        return 0;
    }

    return average / readings;
}

void showHotDays(const Array<Array<float>>& array)
{
    float total_avg = overallAverage(array);
    
    std::cout << "Hot days:" << std::endl;

    for (int i = 0; i < array.getSize(); i++) {
        float day_avg = dayAverage(array[i]);
        if (day_avg > total_avg) {
            std::cout << "Day " << i + 1 << " (average = " << day_avg << ")" << std::endl;
        }
    }
}
