#pragma once

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
    Array& operator=(const Array<T> other);
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

template<typename T>
Array<T>::Array()
    : capacity(0), size(0), data(nullptr)
{
}

template<typename T>
Array<T>::Array(size_t size)
    : capacity(size), size(0), data(nullptr)
{
    if (size > 0) {
        data = new T[size]();
    }
}

// Выполняем глубокое копирование, нельзя просто делать this->data = other.data, иначе уязвимость use-after-free или double-free (undefined behaviour)
template<typename T>
Array<T>::Array(const Array<T>& other)
    : capacity(other.capacity), size(other.size), data(nullptr)
{
    if (capacity > 0) {
        data = new T[capacity];
        for (size_t i = 0; i < capacity; i++) {
            data[i] = other.data[i];
        }
    }
}

template<typename T>
void Array<T>::swap(Array<T>& other)
{
    std::swap(capacity, other.capacity);
    std::swap(data, other.data);
    std::swap(size, other.size);
}

// Почему так? Функция, то есть оператор присваивания принимает не ссылку на массив, а уже временную копию массива \
   (был вызван Array<T>::Array(const Array<T>& other). Значит можно поменять данные между ними, а временная копия удалится)
template<typename T>
Array<T>& Array<T>::operator=(const Array<T> other)
{
    swap(other);
    return *this;
}

template<typename T>
Array<T>::~Array()
{
    if (data != nullptr) {
        delete[] data;
    }
}

template<typename T>
void Array<T>::pushBack(const T& element)
{
    if (size == capacity)
    {
        size_t new_capacity = (capacity == 0 ? 1 : capacity * 2);
        T* new_data = new T[new_capacity];

        for (size_t i = 0; i < size; i++)
            new_data[i] = data[i];

        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

    data[size] = element;
    size++;
}

template<typename T>
void Array<T>::resize(size_t size)
{
    if (size == this->capacity) { return; }

    if (size == 0) {
        delete[] data;
        data = nullptr;
        this->capacity = 0;
        this->size = 0;
        return;
    }

    if (size > 0) {
        T* new_data = new T[size]();
        
        for (size_t i = 0; i < std::min(size, this->capacity); i++) {
            new_data[i] = data[i];
        }

        delete[] data;

        data = new_data;
        this->size = min(this->size, size);
        this->capacity = size;
    }
}

template<typename T>
void Array<T>::clear()
{
    delete[] data;
    data = nullptr;
    capacity = 0;
    size = 0;
}

template<typename T>
T& Array<T>::at(int idx)
{
    return data[idx];
}

template<typename T>
const T& Array<T>::at(int idx) const
{
    return data[idx];
}

template<typename T>
T& Array<T>::operator[](int idx)
{
    return data[idx];
}

template<typename T>
const T& Array<T>::operator[](int idx) const
{
    return data[idx];
}

template<typename T>
size_t Array<T>::getSize() const
{
    return size;
}
