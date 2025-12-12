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

#define DEFAULT_SAVE_PATH "./data/library_data.txt"


class Library {
    std::vector<Book> books;
    std::vector<User> users;
    std::string dataFile;
public:
    Library();
    Library(const std::string& dataFile);

    void addBook(const Book& book);
    void addUser(const User& user);
    void borrowBook(const std::string& userName, const std::string& isbn);
    void returnBook(const std::string& isbn);
    Book* findBookByISBN(const std::string& isbn);
    User* findUserByName(const std::string& name);
    void displayAllBooks() const;
    void displayAllUsers() const;
    void saveToFile() const;
    void saveToFile(const std::string& dataFile);
    void loadFromFile();
    void loadFromFile(const std::string& dataFile);

    void findBooksByAuthor(const std::string& author) const;
    void sortedByYear();
    void sortedByAuthor();
    void sortedByTitle();
};

#endif