#ifdef PLATFORM_WIN
#include <windows.h>
#endif

#include "Library.h"

inline void showMenu() {
    std::cout << "=== LIBRARY ==="          << std::endl;
    std::cout << "1. Show all books"        << std::endl;
    std::cout << "2. Show all users"        << std::endl;
    std::cout << "3. Add new book"          << std::endl;
    std::cout << "4. Register user"         << std::endl;
    std::cout << "5. Borrow book to user"   << std::endl;
    std::cout << "6. Return book from user" << std::endl;
    std::cout << "7. Find book by ISBN"     << std::endl;
    std::cout << "8. Find books by Author"  << std::endl;
    std::cout << "9. Show user profile"     << std::endl;
    std::cout << "10. Save to file"         << std::endl;
    std::cout << "11. Books sorted by Year" << std::endl;
    std::cout << "12. Books sorted by Author"<< std::endl;
    std::cout << "13. Books sorted by Title"<< std::endl;
    std::cout << "0. Exit"                  << std::endl;
}

inline int getYear() {
    std::string input;
    int choice;
    bool ok = false;
    while (!ok) {
        std::cout << "Year: ";
        if (!std::getline(std::cin, input)) continue;
        try
        {
            choice = std::stoi(input);
            ok = true;
        }
        catch(...)
        {
            std::cout << "Incorrect input, try again!" << std::endl;
        }
    }
    return choice;
}

inline int getMaxBooks() {
    std::string input;
    int choice = 3;
    bool ok = false;
    std::cout << "Max books allowed (def 3): ";
    if (!std::getline(std::cin, input)) return choice;
    try
    {
        choice = std::stoi(input);
        ok = true;
    }
    catch(...)
    {
        std::cout << "Incorrect input, set to 3!" << std::endl;
    }
    return choice;
}

inline int getChoice() {
    std::string input;
    int choice;
    bool ok = false;
    while (!ok) {
        std::cout << "Your choice: ";
        if (!std::getline(std::cin, input)) continue;
        try
        {
            choice = std::stoi(input);
            ok = true;
        }
        catch(...)
        {
            std::cout << "Incorrect input, try again!" << std::endl;
        }
    }
    return choice;
}

void addNewBook(Library& lib) {
    std::string title, author, isbn;
    int year;
    
    std::cout << "Title: ";
    while (!std::getline(std::cin, title)) continue;

    std::cout << "Author: ";
    while (!std::getline(std::cin, author)) continue;

    year = getYear();

    std::cout << "ISBN: ";
    while (!std::getline(std::cin, isbn)) continue;

    try {
        Book b(title, author, year, isbn);
        lib.addBook(b);
    }
    catch (const std::exception& e) {
        std::cout << "Add new book error: " << e.what() << std::endl;
    }
}

void registerUser(Library& lib) {
    std::string name, userId;
    int maxBooksAllowed;

    std::cout << "Name: ";
    while (!std::getline(std::cin, name)) continue;

    while (true) {
        std::cout << "UserID (USR_*): ";
        std::getline(std::cin, userId);
        if (userId.starts_with("USR_")) {
            break;
        }
        std::cout << "Incorrect format" << std::endl;
    }

    maxBooksAllowed = getMaxBooks();

    try {
        User user(name, userId, maxBooksAllowed);
        lib.addUser(user);
    }
    catch (const std::exception& e) {
        std::cout << "Register user error: " << e.what() << std::endl;
    }
}

void borrowBookToUser(Library& lib) {
    std::string name, isbn;

    std::cout << "Name: ";
    while (!std::getline(std::cin, name)) continue;

    std::cout << "ISBN: ";
    while (!std::getline(std::cin, isbn)) continue;

    try {
        lib.borrowBook(name, isbn);
    }
    catch (const std::exception& e) {
        std::cout << "Borrow book to user error: " << e.what() << std::endl;
    }
}

void returnBookFromUser(Library& lib) {
    std::string isbn;

    std::cout << "ISBN: ";
    while (!std::getline(std::cin, isbn)) continue;

    try {
        lib.returnBook(isbn);
    }
    catch (const std::exception& e) {
        std::cout << "Return book from user error: " << e.what() << std::endl;
    }
}

void findBookByISBN(Library& lib) {
    std::string isbn;

    std::cout << "ISBN: ";
    while (!std::getline(std::cin, isbn)) continue;

    try {
        Book* b = lib.findBookByISBN(isbn);
        if (b != nullptr) b->displayInfo();
        else std::cout << "Book not found!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Find book by ISBN error: " << e.what() << std::endl;
    }
}

void findBooksByAuthor(Library& lib) {
    std::string author;

    std::cout << "Author: ";
    while (!std::getline(std::cin, author)) continue;

    try {
        lib.findBooksByAuthor(author);
    }
    catch (const std::exception& e) {
        std::cout << "Find books by author error: " << e.what() << std::endl;
    }
}

void showUserProfile(Library& lib) {
    std::string name;

    std::cout << "Name: ";
    while (!std::getline(std::cin, name)) continue;

    try {
        User* user = lib.findUserByName(name);
        if (user != nullptr) user->displayProfile();
        else std::cout << "User not found!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Find user by name error: " << e.what() << std::endl;
    }
}


int main() {
    #ifdef PLATFORM_WIN
    SetConsoleOutputCP(CP_UTF8);
    #endif

    Library lib;

    try {
        lib = Library(DEFAULT_SAVE_PATH);
    }
    catch (const std::exception& e) {
        std::cout << "An errror occured while trying to load from file: " << e.what() << std::endl;
    }

    try {
        // Мейн ~~кун~~ луп
        int choice;
        while (true) {
            showMenu();
            choice = getChoice();
            std::cout << std::endl;

            switch (choice) {
            case 0:
                return 0;
            case 1:
                lib.displayAllBooks();
                break;
            case 2:
                lib.displayAllUsers();
                break;
            case 3:
                addNewBook(lib);
                break;
            case 4:
                registerUser(lib);
                break;
            case 5:
                borrowBookToUser(lib);
                break;
            case 6:
                returnBookFromUser(lib);
                break;
            case 7:
                findBookByISBN(lib);
                break;
            case 8:
                findBooksByAuthor(lib);
                break;
            case 9:
                showUserProfile(lib);
                break;
            case 10:
                lib.saveToFile();
                break;
            case 11:
                lib.sortedByYear();
                lib.displayAllBooks();
                break;
            case 12:
                lib.sortedByAuthor();
                lib.displayAllBooks();
                break;
            case 13:
                lib.sortedByTitle();
                lib.displayAllBooks();
                break;
            default:
                std::cout << "Invalid choice" << std::endl;
                break;
            }
            std::cout << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
    }
}