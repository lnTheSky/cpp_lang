/*
Вариант №1

Имеющиеся проблемы:
    1. Ограниченный буфер (256 байт), есть риск перезаписать стек, получить UB
    2. При проверке на EOF не освобождаем выделенную память и не закрываем открытый файл. Утечка памяти, повреждение файла
    3. Потенциально опасное использование Си-Строк, может не иметь нулевого символа в конце, приведёт к бесконтрольному чтению памяти, UB и крашу.
    4. C-style код на C++, нет использования STL

Исправления:
    1. Используем std::vector для автоатической работы с памятью для буфера
    2. Используем const std::string&, поскольку Си-Строки потенциально опасны, если не будет нулевого символа в конце строки.
    3. Используем файловые потоки std::ifstream для автоматического и удобного ввода/ввывода в файл, а также безопасной работы с памятью
*/
#include <cstdio> 
#include <stdexcept> 

void process(const char* name) 
{ 
    FILE* f = std::fopen(name, "r"); 
    if (!f) throw std::runtime_error("open failed");

    char* buf = new char[256]; 
    
    int c = std::fgetc(f); 
    if (c == EOF)
        throw std::runtime_error("empty file"); 
    
    // ... 
    delete[] buf; 
    std:fclose(f);
}

// Исправленный вариант
#include <vector> 
#include <fstream>
#include <stdexcept> 
#include <string>

void process_fixed(const std::string& name) 
{ 
    std::ifstream f(name);
    if (!f) throw std::runtime_error("open failed");

    std::vector<char> buf; 
     
    if (f.peek() == EOF)
        throw std::runtime_error("empty file"); 
    
    // ... 
}


int main() {
    process_fixed("test");
}