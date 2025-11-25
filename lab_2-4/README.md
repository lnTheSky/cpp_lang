# Лабораторные работы №2-4

### Основное техническое задание:

---

- Запрещена стандартная библиотека управления памятью (STL, `std::vector` и т.д.)
- Вся динамическая память через операторы `new` и `delete[]`
- Вместо *индексирования* массивов использовать **арифмиетику указателей**

---

## Моя библиотека dynArray.h

Для удобства работы с памятью и массивами в лабораторных работах 2-4 я решил написать свою собственную мини-библиотеку, которая реализует динамический массив `Array<T>`, с поддержкой любого типа данных благодаря шаблонному программированию.  

Структура класса `Array`:
```cpp
template<typename T>
class Array {
    size_t capacity;
    size_t size;
    T*     data;

    void swap(Array<T>& other);
public:
    Array();
    Array(size_t size);
    Array(const Array<T>& other);
    Array& operator=(const Array<T>& other);
    ~Array();

    void pushBack(const T& element);
    void resize(size_t size);
    void clear();

    inline       T& at(int idx);
    inline const T& at(int idx) const;

    inline       T& operator[](int idx);
    inline const T& operator[](int idx) const;

    inline size_t getSize() const;
    inline size_t getCapacity() const;

};
```

#### Возможности `Array<T>`:

- Автоматическое управление динамической памятью (конструкторы и деструктор, глубокое копирование, `pushBack` с авторасширением массива, `getSize`, `getCapacity`)
- Поддержка любого типа данных
- Индексирование с помощью арифметики указателей благодаря перегрузке оператора `operator[]`
- Можно использовать как обычный массив, без авторасширения, если задать размер вручную (методы `resize`, `at`)
- Перегрузка операторов ввода `>>` и вывода `<<` для удобной работы с потоками ввода-вывода

# Лабораторная работа №2-3

В ней я использовал для работы с памятью только свою написанную библиотеку, которая не является стандартной, со всеми реализациями управления динамической памятью, индексацией посредством арифметики указателей.

Сигнатуры функций были немного отредактированы в соответствии с возможностями моей библиотеки `dynArray.h` и класса `Array`:
```cpp
void          inputData(Array<float>& array);
float         average(const Array<float>& array);
float         minValue(const Array<float>& array);
float         maxValue(const Array<float>& array);
Array<float>  filterAboveAverage(const Array<float>& array);
```

Были соблюдены ограничения по вводимым значениям, магические числа которых заданы макросами. Весь функционал был реализован, пользовательский ввод обрабатывается через получение строки и дальнейшего парсинга строки в нужный тип данных.

# Лабораторная работа №4

В ней также был задействован самодельный класс `Array` для работы с динамическими массивами.

Для этого также были отредактированы сигнатуры основных функций:
```cpp
void          inputData(Array<Array<float>>& array);
float         dayAverage(const Array<float>& array);
float         overallAverage(const Array<Array<float>>& array);
void          showHotDays(const Array<Array<float>>& array);
```

Также соблюдены все установленные ограничения измерений и магические числа этих ограничений определены в начале макросами.