#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <exception>
#include <chrono>
#include <format>
#include <iostream>

#define MIN_YEAR 1450

class Book {
    std::string title;
    std::string author;
    int year;
    std::string isbn;

    bool isAvailable;
    
    std::string borrowedBy;
public:
    // Конструкторы класса
    Book();
    Book(const std::string& title, const std::string& author, const int& year, const std::string& isbn);
    Book(const Book& other);

    // Getter-методы для закрытых полей класса
    const inline std::string& getTitle() const;
    // std::string& getTitle();

    const inline std::string& getAuthor() const;
    // std::string& getAuthor();

    const inline int& getYear() const;
    // int& getYear();

    const inline std::string& getISBN() const;
    // std::string& getISBN();

    const inline bool& getIsAvailable() const;
    // bool& getIsAvailable();

    const inline std::string& getBorrowedBy() const;
    // std::string& getBorrowedBy();

    // Функциональные методы
    void borrowBook(const std::string& userName);
    void returnBook();
    void inline displayInfo();
};

#endif