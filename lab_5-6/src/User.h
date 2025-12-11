#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>
#include <exception>

class User {
    std::string name;
    std::string userId;
    std::vector<std::string> borrowedBooks;
    int maxBooksAllowed;
public:
    User();
    User(const User& other);
    User(const std::string& name, const std::string& userId);
    User(const std::string& name, const std::string& userId, int maxBooksAllowed);

    const std::string& getName() const;
    const std::string& getUserId() const;
    const std::vector<std::string>& getBorrowedBooks() const;
    const int& getMaxBooksAllowed() const;

    bool canBorrowMore() const;
    void addBook(const std::string& isbn);
    void removeBook(const std::string& isbn);
    void displayProfile();
};

#endif