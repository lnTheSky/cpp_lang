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

    const inline std::string& getName() const;
    const inline std::string& getUserId() const;
    const inline std::vector<std::string>& getBorrowedBooks() const;
    const inline int& getMaxBooksAllowed() const;

    bool inline canBorrowMore() const;
    void addBook(const std::string& isbn);
    void removeBook(const std::string& isbn);
    void inline displayProfile();
};

#endif