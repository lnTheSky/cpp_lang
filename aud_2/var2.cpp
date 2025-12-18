/*

Исходная структура Range

Для работы необходимо вручную проверять входит ли конкретное число в данный промежуток.
Мы сами реализуем логику проверки по нижней и верхней грани промежутка. Это неудобно, захламляет код, может быть нарушено.

Необходимо, чтобы выполнялись два условия корректности:
    1. (low < high)
    2. (low <= num && high > num)
Тогда мы сможем корректно работать с данной структурой


struct Range
{
    int low;
    int high;
};

*/

/* Новая реализаци

Здесь мы используем класс, чтобы инкапсулировать поля и методы объекта Range.
1. Вся логика сокрыта внутри методов класса.
2. Есть простой метод проверить что число входит в промежуток
3. Есть проверки на корректность аргументов конструктора Range

*/

#include <stdexcept>

class Range
{
    int low_val;
    int high_val;
public:
    Range(int low, int high);

    const int& low() const;
    const int& high() const;

    bool contains(const int& num) const;
};

Range::Range(int low, int high)
    : low_val(low), high_val(high)
{
    if (low > high) throw std::invalid_argument("Lower value must be equal or less then high value");
}

const int& Range::low() const
{
    return low_val;
}

const int& Range::high() const
{
    return high_val;
}

bool Range::contains(const int& num) const
{
    return low_val <= num && high_val > num;
}


#include <iostream>

int main() {
    Range range(1, 10);

    std::cout << "Is 1 in range: " << range.contains(1) << std::endl;
    std::cout << "Is 2 in range: " << range.contains(2) << std::endl;
    std::cout << "Is 10 in range: " << range.contains(10) << std::endl;
    std::cout << "Is 12 in range: " << range.contains(12) << std::endl;
}
