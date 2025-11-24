#include <iostream>
#include <exception>

#include "dynArray.h"

#define DAYS_MAX     30
#define READINGS_MAX 24

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
    std::string line;

    std::cout << "Enter days count: ";
    std::getline(std::cin, line);
    int days = std::stoi(line);

    // Проверка, что дней не больше допустимого
    if (days > DAYS_MAX) {
        throw std::runtime_error("Supports only up to 30 days");
    }

    array.resize(days);

    std::cout << "Enter readings per day count: ";
    std::getline(std::cin, line);
    int readings = std::stoi(line);

    // Проверка, что измерений не больше допустимого
    if (readings > READINGS_MAX) {
        throw std::runtime_error("Supports only up to 24 readings");
    }

    for (int i = 0; i < days; i++) {
        Array<float> day;
        std::cout << "Day " << i + 1 << ": ";
        std::cin >> day;
        if (day.getSize() > READINGS_MAX) {
            throw std::runtime_error("Supports only up to 24 readings");
        }
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
