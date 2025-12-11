#ifndef LIBRARY_H
#define LIBRARY_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cctype>

#include "Book.h"
#include "User.h"


class Library {
    std::vector<Book> books;
    std::vector<User> users;
    std::string dataFile;
public:
    Library();
    Library(const std::string& dataFile);

    inline void addBook(const Book& book);
    inline void addUser(const User& user);
    inline void borrowBook(const std::string& userName, const std::string& isbn);
    inline void returnBook(const std::string& isbn);
    inline Book* findBookByISBN(const std::string& isbn);
    inline User* findUserByName(const std::string& name);
    inline void displayAllBooks() const;
    inline void displayAllUsers() const;
    void saveToFile() const;
    inline void saveToFile(const std::string& dataFile);
    void loadFromFile();
    inline void loadFromFile(const std::string& dataFile);
};

#endif