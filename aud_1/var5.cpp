/*
#include <string>

class Student {
public:
    std::string name; 
    int age; 
};

Почему плохой дизайн ООП:
    - Все поля открыты, методов нет -- это точь-в-точь структура, класс здесь для галочки
    - Открытые поля можно не только прочитать, но и изменить извне.
    - Нет инициализации полей, могут быть с мусором.
    - Нет конструктора. Нет проверок

Почему проверку в класс, а не в main:
    - Если проверку вынести во вне, тогда нарушается принцип инкапсуляции, поля доступны для свободной модификации,
      нарушается принцип абстракции -- мы делаем в main то, что нам знать и делать вообще не обязательно, логика размазывается.

Ниже исправленный вариант
*/

#include <string>
#include <stdexcept>

class Student {
    std::string name; 
    int age; 
public: 
    Student(const std::string& name, int age);

    const std::string& getName() const { return name; }
    const int& getAge() const { return age; }

    void setAge(int age);
};

Student::Student(const std::string& name, int age)
    : name(name), age(age)
{
    if (name.empty()) throw std::invalid_argument("Name is empty");
    if (age < 0) throw std::invalid_argument("Age is less than 0");
}

void Student::setAge(int age)
{
    if (age < 0) throw std::invalid_argument("Age is less than 0");
    this->age = age;
}