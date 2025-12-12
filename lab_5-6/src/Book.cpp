#include "Book.h"

Book::Book() 
    : title(""), author(""), year(MIN_YEAR), isbn(""), isAvailable(true), borrowedBy("")
{
}

Book::Book(const std::string& title, const std::string& author, const int& year_, const std::string& isbn)
    : title(title), author(author), isbn(isbn), isAvailable(true), borrowedBy("")
{
    const auto now = std::chrono::system_clock::now();
    const std::chrono::sys_days today = std::chrono::floor<std::chrono::days>(now);
    const std::chrono::year_month_day ymd{today};

    if (int(ymd.year()) < year_ || year_ < MIN_YEAR) {
        throw std::runtime_error("Invalid Book year " + std::to_string(year_));
    }

    year = year_;
}

Book::Book(const std::string& title, const std::string& author, const int& year_, const std::string& isbn, bool isAvailable, const std::string& borrowedBy)
    : title(title), author(author), isbn(isbn), isAvailable(isAvailable), borrowedBy(borrowedBy)
{
    const auto now = std::chrono::system_clock::now();
    const std::chrono::sys_days today = std::chrono::floor<std::chrono::days>(now);
    const std::chrono::year_month_day ymd{today};

    if (int(ymd.year()) < year_ || year_ < MIN_YEAR) {
        throw std::runtime_error("Invalid Book year " + std::to_string(year_));
    }

    year = year_;
}

Book::Book(const Book& other)
    : title(other.title), author(other.author), year(other.year), isbn(other.isbn)
{
    // Новая книга, никто не владеет
    isAvailable = true;
    borrowedBy = "";
}

const std::string& Book::getTitle() const
{
    return title;
}

// std::string& Book::getTitle()
// {
//     return title;
// }

const std::string& Book::getAuthor() const
{
    return author;
}

// std::string& Book::getAuthor()
// {
//     return author;
// }

const int& Book::getYear() const
{
    return year;
}

// Опасный метод, нужна проверка на выход за [1450, cur_year]
// int& Book::getYear()
// {
//     return year;
// }

const std::string& Book::getISBN() const
{
    return isbn;
}

// std::string& Book::getISBN()
// {
//     return isbn;
// }

const bool& Book::getIsAvailable() const
{
    return isAvailable;
}

// bool& Book::getIsAvailable()
// {
//     return isAvailable;
// }

const std::string& Book::getBorrowedBy() const
{
    return borrowedBy;
}

// std::string& Book::getBorrowedBy()
// {
//     return borrowedBy;
// }

void Book::borrowBook(const std::string& userName)
{
    if (!isAvailable) {
        throw std::runtime_error("Book is already borrowed by " + borrowedBy);
    }

    isAvailable = false;
    borrowedBy = userName;
}

void Book::returnBook()
{
    borrowedBy = "";
    isAvailable = true;
}

void Book::displayInfo() const
{
    std::cout << "--- Book Info ---" << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "Year: " << year << std::endl;
    std::cout << "ISBN: " << isbn << std::endl;
    std::cout << "Available: " << (isAvailable ? "yes" : "no") << std::endl;;
    std::cout << "Borrowed by: " << borrowedBy << std::endl;
    std::cout << std::endl;
}