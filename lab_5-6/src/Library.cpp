#include "Library.h"

// Обрезаем строку от лишних пробелов и т.д.
static inline std::string trim(std::string s) {
    auto l = s.find_first_not_of(" \t\r\n");
    
    if (l == std::string::npos) {
        return {};
    } 
    
    auto r = s.find_last_not_of(" \t\r\n");

    return s.substr(l, r - l + 1);
}

// Разбиваем на пары (ключ, значение) строки вида "Available: yes"
static inline std::pair<std::string, std::string> splitKV(const std::string& line) {
    auto pos = line.find(':');

    // Проверка, что в строке есть ':'
    if (pos == std::string::npos) {
        return {"", ""};
    }

    return { trim(line.substr(0, pos)), trim(line.substr(pos + 1)) };
}


Library::Library()
    : dataFile(DEFAULT_SAVE_PATH)
{
}

Library::Library(const std::string& dataFile)
    : dataFile(dataFile)
{
    loadFromFile();
}

void Library::addBook(const Book& book)
{
    for (const auto& b : books) {
        if (b.getISBN() == book.getISBN()) {
            throw std::runtime_error("ISBN is not unique!");
        }
    }
    books.push_back(book);
}

void Library::addUser(const User& user)
{
    for (const auto& u : users) {
        if (u.getUserId() == user.getUserId()) {
            throw std::runtime_error("UserID is not unique!");
        }
    }
    users.push_back(user);
}

void Library::borrowBook(const std::string& userName, const std::string& isbn)
{
    User* user = findUserByName(userName);
    Book* book = findBookByISBN(isbn);

    if (user == nullptr || book == nullptr) {
        throw std::runtime_error("User or book not found!");
    }

    book->borrowBook(userName);
    user->addBook(isbn);
}

void Library::returnBook(const std::string& isbn)
{
    Book* book = findBookByISBN(isbn);
    User* user = findUserByName(book->getBorrowedBy());

    if (user == nullptr || book == nullptr) {
        throw std::runtime_error("User or book not found!");
    }

    user->removeBook(isbn);
    book->returnBook();
}

Book* Library::findBookByISBN(const std::string& isbn)
{
    for (auto& book : books) {
        if (book.getISBN() == isbn) {
            return &book;
        }
    }

    return nullptr;
}

User* Library::findUserByName(const std::string& name)
{
    for (auto& user : users) {
        if (user.getName() == name) {
            return &user;
        }
    }

    return nullptr;
}

void Library::displayAllBooks() const
{
    for (const auto& book : books) {
        book.displayInfo();
    }
}

void Library::displayAllUsers() const
{
    for (const auto& user : users) {
        user.displayProfile();
    }
}

void Library::saveToFile() const
{
    std::ofstream out{dataFile};

    if (!out) {
        throw std::runtime_error("Cannot open file for writing: " + dataFile);
    }

    for (const auto& b : books) {
        out << "BOOK"                                                << std::endl;
        out << "Title: "      << b.getTitle()                        << std::endl;
        out << "Author: "     << b.getAuthor()                       << std::endl;
        out << "Year: "       << b.getYear()                         << std::endl;
        out << "ISBN: "       << b.getISBN()                         << std::endl;
        out << "Available: "  << (b.getIsAvailable() ? "yes" : "no") << std::endl;
        out << "BorrowedBy: " << b.getBorrowedBy()                   << std::endl << std::endl;
    }

    out << "---USERS---" << std::endl << std::endl;

    for (const auto& u : users) {
        out << "USER"                      << std::endl;
        out << "Name: "   << u.getName()   << std::endl;
        out << "UserID: " << u.getUserId() << std::endl;
        out << "BorrowedBooks: ";

        const std::vector<std::string> borrowedBooks = u.getBorrowedBooks();
        for (size_t i = 0; i < borrowedBooks.size(); i++) {
            if (i) {
                out << "|";
            }

            out << borrowedBooks[i];
        }

        out << std::endl;
        out << "MaxBooks: " << u.getMaxBooksAllowed() << std::endl << std::endl;
    }
}

void Library::saveToFile(const std::string& dataFile)
{
    this->dataFile = dataFile;
    saveToFile();
}

void Library::loadFromFile()
{
    std::ifstream in{dataFile};
    
    if (!in) {
        throw std::runtime_error("Cannot open file: " + dataFile);
    }
    
    books.clear();
    users.clear();

    std::string line;
    bool in_user = false;

    while (std::getline(in, line)) {
        line = trim(line);

        if (line.empty()) continue;

        if (line == "---USERS---") {
            in_user = true;
            continue;
        }

        if (!in_user) {
            if (line != "BOOK") continue;

            std::string title, author, isbn, borrowedBy, isAvailable;
            int year = 0;
            bool ok = true;

            if (!std::getline(in, line)) ok = false;
            else {
                auto kv = splitKV(line);

                if (kv.first != "Title") ok = false;
                else title = kv.second;
            }

            if (!std::getline(in, line)) ok = false;
            else {
                auto kv = splitKV(line);

                if (kv.first != "Author") ok = false;
                else author = kv.second;
            }

            if (!std::getline(in, line)) ok = false;
            else {
                auto kv = splitKV(line);

                if (kv.first != "Year") ok = false;
                else {
                    try { year = std::stoi(kv.second); }
                    catch (...) { ok = false; }
                }
            }

            if (!std::getline(in, line)) ok = false;
            else {
                auto kv = splitKV(line);

                if (kv.first != "ISBN") ok = false;
                else isbn = kv.second;
            }

            if (!std::getline(in, line)) ok = false;
            else {
                auto kv = splitKV(line);

                if (kv.first != "Available") ok = false;
                else isAvailable = kv.second;
            }

            if (!std::getline(in, line)) ok = false;
            else {
                auto kv = splitKV(line);

                if (kv.first != "BorrowedBy") ok = false;
                else borrowedBy = kv.second;
            }

            // Пропускаем пустые строки
            std::streampos cur = in.tellg();
            if (std::getline(in, line)) {
                if (!trim(line).empty()) in.seekg(cur); // откат если не пустая
            }

            if (!ok) continue; // пропускаем невалидный Book

            if (isbn.empty()) continue;

            if (!(isAvailable == "yes" || isAvailable == "no")) continue;

            Book b(title, author, year, isbn, (isAvailable == "yes"), borrowedBy);

            books.push_back(std::move(b));
        }
        else {
            if (line != "USER") continue;

            std::string name, userId, borrowedBooks;
            int maxBooks = 0;
            bool ok = true;

            if (!std::getline(in, line)) ok = false;
            else {
                auto kv = splitKV(line);
                
                if (kv.first != "Name") ok = false;
                else name = kv.second;
            }

            if (!std::getline(in, line)) ok = false;
            else {
                auto kv = splitKV(line);

                if (kv.first != "UserID") ok = false;
                else userId = kv.second;
            }

            if (!std::getline(in, line)) ok = false;
            else {
                auto kv = splitKV(line);
                
                if (kv.first != "BorrowedBooks") ok = false;
                else borrowedBooks = kv.second;
            }

            if (!std::getline(in, line)) ok = false;
            else {
                auto kv = splitKV(line);
                
                if (kv.first != "MaxBooks") ok = false;
                else {
                    try { maxBooks = std::stoi(kv.second); }
                    catch (...) { ok = false; }
                }
            }

            // Пропуск пустые строки
            std::streampos cur = in.tellg();
            if (std::getline(in, line)) {
                if (!trim(line).empty()) in.seekg(cur);
            }

            if (!ok) continue; // пропускаем невалидный User

            if (name.empty() || userId.empty() || maxBooks <= 0) continue;

            User u{name, userId, maxBooks};
            if (!borrowedBooks.empty()) {
                std::stringstream ss{borrowedBooks};
                std::string token;
                while (std::getline(ss, token, '|')) {
                    token = trim(token);
                    if (!token.empty()) u.addBook(token);
                }
            }
            users.push_back(std::move(u));
        }
    }
}

void Library::loadFromFile(const std::string& dataFile)
{
    this->dataFile = dataFile;
    loadFromFile();
}