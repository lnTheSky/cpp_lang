#include "User.h"

User::User()
    : name(""), userId(""), maxBooksAllowed(3)
{
}

User::User(const User& other)
    : name(other.name), userId(other.userId), maxBooksAllowed(other.maxBooksAllowed), borrowedBooks(other.borrowedBooks)
{
}

User::User(const std::string& name, const std::string& userId)
    : name(name), userId(userId), maxBooksAllowed(3)
{
}

User::User(const std::string& name, const std::string& userId, int maxBooksAllowed)
    : name(name), userId(userId), maxBooksAllowed(maxBooksAllowed)
{
}

const std::string& User::getName() const
{
    return name;
}

const std::string& User::getUserId() const
{
    return userId;
}

const std::vector<std::string>& User::getBorrowedBooks() const
{
    return borrowedBooks;
}

const int& User::getMaxBooksAllowed() const
{
    return maxBooksAllowed;
}

bool User::canBorrowMore() const
{
    return borrowedBooks.size() < maxBooksAllowed; 
}