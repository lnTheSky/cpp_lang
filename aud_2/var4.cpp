/*
#include <cstdio> 

class FileLogger { 
    FILE* file; 
public: 
    FileLogger(const char* name) { 
        file = std::fopen(name, "w"); 
    } 
    void log(const char* msg) { 
        std::fputs(msg, file); 
    } 
};

Имеющиеся проблемы:
    - Отсутствие деструктора, не освобождаются ресурсы
    - Нет обработки случая, если файл открылся некорректно
    - Не реализован конструктор копирования (копирование разрешено, надо запретить)

Ниже исправленный класс
Вместо старого способа запрета копирования (закрытый конструктор, оператор присваивания) используется новый синтаксис
Реализованы закрытие файла в деструкторы и обработка случая некорректного открытия файла.

Копировать нельзя, потому что ресурсом, которым владеет объект может владеть только этот объект (хэндл к файлу),
а логгер не может быть без файла, поэтому и нельзя копировать.

*/

#include <cstdio>
#include <stdexcept> 

class FileLogger { 
    FILE* file; 
public: 
    FileLogger(const char* name) { 
        file = std::fopen(name, "w");
        if (!file) throw std::runtime_error("Filed to open file");
    }

    FileLogger(const FileLogger&) = delete;
    FileLogger& operator=(const FileLogger&) = delete;
    ~FileLogger();
    
    void log(const char* msg) { 
        std::fputs(msg, file); 
    } 
};

FileLogger::~FileLogger()
{
    if (file) std::fclose(file);
}