/*
Предложен класс, реализующий автоматический нерасширяемый динамический массив.

class Buffer
{
    int* data ;
    int size;
public:
    Buffer(int n) : data(new int[n]), size(n) {}
    ~Buffer() { delete[] data; }
};

Что и почему произойдёт при Buffer b = a;?
    - Произойдёт копирование по умолчанию, содержимое всех полей будет просто скоипровано в новый объект
    - Новая память не выделится, будет ссылка на старую
    - Уязвимости типа use-after-free и double-free 

Как будем чинить?
    - Сделаем конструктор копирования и напишем в нём правильное, глубокое копирование

*/


class Buffer
{
    int* data;
    int size;
public:
    Buffer(int n) : data(new int[n]), size(n) {}
    Buffer(const Buffer& other);
    ~Buffer() { delete[] data; }
};

Buffer::Buffer(const Buffer& other)
    : size(other.size)
{
    data = new int[size];
    for (int i=0; i < other.size; i++) {
        data[i] = other.data[i];
    }
}

