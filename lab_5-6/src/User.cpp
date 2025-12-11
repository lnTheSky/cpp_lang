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

void User::addBook(const std::string& isbn)
{
    if (!canBorrowMore()) {
        throw std::runtime_error("This user cannot borrow more books!");
    }

    borrowedBooks.push_back(isbn);
}

void User::removeBook(const std::string& isbn)
{
    borrowedBooks.erase(std::find(borrowedBooks.begin(), borrowedBooks.end(), isbn));
}

void User::displayProfile() const
{
    std::cout << "--- User Info ---" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "UserID: " << userId << std::endl;
    std::cout << "Borrowed books: ";
    for (auto isbn : borrowedBooks) {
        std::cout << isbn << " | ";
    }
    std::cout << std::endl << std::endl;
}